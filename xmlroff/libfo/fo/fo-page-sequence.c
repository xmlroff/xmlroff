/* Fo
 * fo-page-sequence.c: 'page-sequence' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-page-sequence-private.h"
#include "fo/fo-page-sequence-area.h"
#include "fo/fo-tree.h"
#include "fo/fo-page-master.h"
#include "fo/fo-simple-page-master.h"
#include "fo/fo-page-sequence-master.h"
#include "fo/fo-page-master-reference.h"
#include "fo/fo-repeatable-page-master-alternatives.h"
#include "property/fo-property-country.h"
#include "property/fo-property-force-page-count.h"
#include "property/fo-property-format.h"
#include "property/fo-property-grouping-separator.h"
#include "property/fo-property-grouping-size.h"
#include "property/fo-property-id.h"
#include "property/fo-property-initial-page-number.h"
#include "property/fo-property-language.h"
#include "property/fo-property-letter-value.h"
#include "property/fo-property-master-reference.h"

/**
 * SECTION:fo-page-sequence
 * @short_description: 'page-sequence' formatting object
 *
 * Definition: <ulink url="http://www.w3.org/TR/xsl11/&num;fo_page-sequence">http://www.w3.org/TR/xsl11/&num;fo_page-sequence</ulink>
 */

enum {
  PROP_0,
  PROP_COUNTRY,
  PROP_FORCE_PAGE_COUNT,
  PROP_FORMAT,
  PROP_GROUPING_SEPARATOR,
  PROP_GROUPING_SIZE,
  PROP_ID,
  PROP_INITIAL_PAGE_NUMBER,
  PROP_LANGUAGE,
  PROP_LETTER_VALUE,
  PROP_MASTER_REFERENCE
};

static void _class_init            (FoPageSequenceClass *klass);
static void _dispose              (GObject      *object);
static void _get_property          (GObject      *object,
                                    guint         prop_id,
                                    GValue       *value,
                                    GParamSpec   *pspec);
static void _set_property          (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec);
static gboolean _validate_content  (FoFo         *fo,
                                    GError     **error);
static void _validate              (FoFo         *fo,
                                    FoContext    *current_context,
                                    FoContext    *parent_context,
                                    GError      **error);
static void _update_from_context   (FoFo         *fo,
                                    FoContext    *context);
static void _debug_dump_properties (FoFo         *fo,
                                    gint          depth);
static void _children_properties_resolve (FoFo       *this_fo,
					  FoArea     *this_fo_parent_area,
					  FoArea    **new_area,
					  GHashTable *prop_eval_hash,
					  FoDoc      *fo_doc,
					  gboolean    continue_after_error,
					  FoDebugFlag   debug_level,
					  FoWarningFlag warning_mode,
					  GError    **error);

static gpointer parent_class;

/**
 * fo_page_sequence_get_type:
 * 
 * Register the #FoPageSequence object type.
 * 
 * Return value: #GType value of the #FoPageSequence object type.
 **/
GType
fo_page_sequence_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoPageSequenceClass),
	  NULL,           /* base_init */
	  NULL,           /* base_finalize */
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoPageSequence),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoPageSequence",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * _class_init:
 * @klass: #FoPageSequenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPageSequenceClass.
 **/
static void
_class_init (FoPageSequenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->dispose = _dispose;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  fofo_class->validate_content =
    _validate_content;
  fofo_class->validate2 = _validate;
  fofo_class->update_from_context = _update_from_context;
  fofo_class->debug_dump_properties = _debug_dump_properties;
  fofo_class->area_new2 =
    fo_page_sequence_area_new;
  /*fofo_class->children_properties_resolve =
    _children_properties_resolve;*/

  g_object_class_install_property
    (object_class,
     PROP_COUNTRY,
     g_param_spec_object ("country",
			  _("Country"),
			  _("Country property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FORCE_PAGE_COUNT,
     g_param_spec_object ("force-page-count",
			  _("Force Page Count"),
			  _("Force Page Count property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FORMAT,
     g_param_spec_object ("format",
			  _("Format"),
			  _("Format property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_GROUPING_SEPARATOR,
     g_param_spec_object ("grouping-separator",
			  _("Grouping Separator"),
			  _("Grouping Separator property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_GROUPING_SIZE,
     g_param_spec_object ("grouping-size",
			  _("Grouping Size"),
			  _("Grouping Size property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_INITIAL_PAGE_NUMBER,
     g_param_spec_object ("initial-page-number",
			  _("Initial Page Number"),
			  _("Initial Page Number property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_LANGUAGE,
     g_param_spec_object ("language",
			  _("Language"),
			  _("Language property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_LETTER_VALUE,
     g_param_spec_object ("letter-value",
			  _("Letter Value"),
			  _("Letter Value property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MASTER_REFERENCE,
     g_param_spec_object ("master-reference",
			  _("Master Reference"),
			  _("Master Reference property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * _dispose:
 * @object: #FoPageSequence object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoPageSequence.
 **/
static void
_dispose (GObject *object)
{
  FoFo *fo = FO_FO (object);

  g_object_unref (FO_PAGE_SEQUENCE (fo)->walker);

  /* Release references to all property objects. */
  fo_page_sequence_set_country (fo, NULL);
  fo_page_sequence_set_force_page_count (fo, NULL);
  fo_page_sequence_set_format (fo, NULL);
  fo_page_sequence_set_grouping_separator (fo, NULL);
  fo_page_sequence_set_grouping_size (fo, NULL);
  fo_page_sequence_set_id (fo, NULL);
  fo_page_sequence_set_initial_page_number (fo, NULL);
  fo_page_sequence_set_language (fo, NULL);
  fo_page_sequence_set_letter_value (fo, NULL);
  fo_page_sequence_set_master_reference (fo, NULL);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * _get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoPageSequence.
 **/
static void
_get_property (GObject    *object,
               guint       prop_id,
               GValue     *value,
               GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_COUNTRY:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_country (fo_fo)));
      break;
    case PROP_FORCE_PAGE_COUNT:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_force_page_count (fo_fo)));
      break;
    case PROP_FORMAT:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_format (fo_fo)));
      break;
    case PROP_GROUPING_SEPARATOR:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_grouping_separator (fo_fo)));
      break;
    case PROP_GROUPING_SIZE:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_grouping_size (fo_fo)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_id (fo_fo)));
      break;
    case PROP_INITIAL_PAGE_NUMBER:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_initial_page_number (fo_fo)));
      break;
    case PROP_LANGUAGE:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_language (fo_fo)));
      break;
    case PROP_LETTER_VALUE:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_letter_value (fo_fo)));
      break;
    case PROP_MASTER_REFERENCE:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_get_master_reference (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * _set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoPageSequence.
 **/
static void
_set_property (GObject      *object,
               guint         prop_id,
               const GValue *value,
               GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_COUNTRY:
      fo_page_sequence_set_country (fo_fo, g_value_get_object (value));
      break;
    case PROP_FORCE_PAGE_COUNT:
      fo_page_sequence_set_force_page_count (fo_fo, g_value_get_object (value));
      break;
    case PROP_FORMAT:
      fo_page_sequence_set_format (fo_fo, g_value_get_object (value));
      break;
    case PROP_GROUPING_SEPARATOR:
      fo_page_sequence_set_grouping_separator (fo_fo, g_value_get_object (value));
      break;
    case PROP_GROUPING_SIZE:
      fo_page_sequence_set_grouping_size (fo_fo, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_page_sequence_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_INITIAL_PAGE_NUMBER:
      fo_page_sequence_set_initial_page_number (fo_fo, g_value_get_object (value));
      break;
    case PROP_LANGUAGE:
      fo_page_sequence_set_language (fo_fo, g_value_get_object (value));
      break;
    case PROP_LETTER_VALUE:
      fo_page_sequence_set_letter_value (fo_fo, g_value_get_object (value));
      break;
    case PROP_MASTER_REFERENCE:
      fo_page_sequence_set_master_reference (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_page_sequence_new:
 * 
 * Creates a new #FoPageSequence initialized to default value.
 * 
 * Return value: the new #FoPageSequence.
 **/
FoFo*
fo_page_sequence_new (void)
{
  return FO_FO (g_object_new (fo_page_sequence_get_type (),
                              NULL));
}

/**
 * _validate_content:
 * @fo:    #FoPageSequence object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
_validate_content (FoFo    *fo,
                   GError **error)
{
  /*GError *tmp_error = NULL;*/

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  return FALSE;

/*
error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (fo));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
*/
}

/**
 * _validate:
 * @fo:              #FoPageSequence object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
static void
_validate (FoFo      *fo,
           FoContext *current_context,
           FoContext *parent_context,
           GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  FoPageSequence *fo_page_sequence = FO_PAGE_SEQUENCE (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_fo_register_id (fo,
                     fo_property_get_value (fo_page_sequence->id));

  gchar *master_name =
    fo_name_get_value (
    fo_property_get_value (fo_page_sequence_get_master_reference (fo)));

  FoFo *tree = fo->tree;

  FoFo *page_master = fo_tree_master_name_get (tree, master_name);
  if (page_master == NULL)
    {
      page_master = fo_tree_default_master_get (tree);
    }
  /* Free master_name to avoid leaking memory. */
  g_free (master_name);

  fo_page_sequence->walker =
    g_object_ref_sink (fo_page_master_new_walker (page_master,
						  NULL));
  g_print ("Walker: %s\n", fo_object_sprintf (fo_page_sequence->walker));

  fo_context_set_writing_mode (current_context,
			       fo_simple_page_master_get_writing_mode (fo_page_sequence_walker_next_page_master (fo_page_sequence->walker,
														 NULL)));

}

static void
_children_properties_resolve (FoFo         *this_fo,
			      FoArea       *this_fo_parent_area,
			      FoArea      **new_area,
			      GHashTable   *prop_eval_hash,
			      FoDoc        *fo_doc,
			      gboolean      continue_after_error,
			      FoDebugFlag   debug_level,
			      FoWarningFlag warning_mode,
			      GError      **error)
{
  g_return_if_fail (FO_IS_FO (this_fo));
  g_return_if_fail (FO_IS_AREA (this_fo_parent_area));
  g_return_if_fail (*new_area == NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  FoPropertyResolveContext prop_context;
  prop_context.reference_area       = fo_area_get_reference (this_fo_parent_area);
  prop_context.prop_eval_hash       = prop_eval_hash;
  prop_context.continue_after_error = continue_after_error;
  prop_context.debug_level          = debug_level;
  prop_context.warning_mode         = warning_mode;
  prop_context.error                = NULL;

  fo_node_traverse (FO_NODE (this_fo),
		    G_PRE_ORDER,
		    G_TRAVERSE_ALL,
		    -1,
		    fo_fo_resolve_property_attributes,
		    &prop_context);

  *new_area = NULL;
}

/**
 * _update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
static void
_update_from_context (FoFo      *fo,
                      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_page_sequence_set_country (fo,
			  fo_context_get_country (context));
  fo_page_sequence_set_force_page_count (fo,
			  fo_context_get_force_page_count (context));
  fo_page_sequence_set_format (fo,
			  fo_context_get_format (context));
  fo_page_sequence_set_grouping_separator (fo,
			  fo_context_get_grouping_separator (context));
  fo_page_sequence_set_grouping_size (fo,
			  fo_context_get_grouping_size (context));
  fo_page_sequence_set_id (fo,
			  fo_context_get_id (context));
  fo_page_sequence_set_initial_page_number (fo,
			  fo_context_get_initial_page_number (context));
  fo_page_sequence_set_language (fo,
			  fo_context_get_language (context));
  fo_page_sequence_set_letter_value (fo,
			  fo_context_get_letter_value (context));
  fo_page_sequence_set_master_reference (fo,
			  fo_context_get_master_reference (context));
}

/**
 * _debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
static void
_debug_dump_properties (FoFo *fo,
                        gint  depth)
{
  FoPageSequence *fo_page_sequence;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo));

  fo_page_sequence = FO_PAGE_SEQUENCE (fo);

  fo_object_debug_dump (fo_page_sequence->country, depth);
  fo_object_debug_dump (fo_page_sequence->force_page_count, depth);
  fo_object_debug_dump (fo_page_sequence->format, depth);
  fo_object_debug_dump (fo_page_sequence->grouping_separator, depth);
  fo_object_debug_dump (fo_page_sequence->grouping_size, depth);
  fo_object_debug_dump (fo_page_sequence->id, depth);
  fo_object_debug_dump (fo_page_sequence->initial_page_number, depth);
  fo_object_debug_dump (fo_page_sequence->language, depth);
  fo_object_debug_dump (fo_page_sequence->letter_value, depth);
  fo_object_debug_dump (fo_page_sequence->master_reference, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_page_sequence_get_page_master:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the page-master of @fo_fo.
 *
 * Return value: The page-master of @fo_fo.
**/
FoFo *
fo_page_sequence_get_page_master (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->page_master;
}

/*
 * These get/set functions are completely auto-generated.
 */

/**
 * fo_page_sequence_get_country:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "country" property of @fo_fo.
 *
 * Return value: The "country" property value.
**/
FoProperty *
fo_page_sequence_get_country (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->country;
}

/**
 * fo_page_sequence_set_country:
 * @fo_fo: The #FoFo object.
 * @new_country: The new "country" property value.
 * 
 * Sets the "country" property of @fo_fo to @new_country.
 **/
void
fo_page_sequence_set_country (FoFo *fo_fo,
		         FoProperty *new_country)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_country == NULL) ||
		    FO_IS_PROPERTY_COUNTRY (new_country));

  if (new_country != NULL)
    {
      g_object_ref_sink (new_country);
    }
  if (fo_page_sequence->country != NULL)
    {
      g_object_unref (fo_page_sequence->country);
    }
  fo_page_sequence->country = new_country;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "country");*/
}

/**
 * fo_page_sequence_get_force_page_count:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "force-page-count" property of @fo_fo.
 *
 * Return value: The "force-page-count" property value.
**/
FoProperty *
fo_page_sequence_get_force_page_count (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->force_page_count;
}

/**
 * fo_page_sequence_set_force_page_count:
 * @fo_fo: The #FoFo object.
 * @new_force_page_count: The new "force-page-count" property value.
 * 
 * Sets the "force-page-count" property of @fo_fo to @new_force_page_count.
 **/
void
fo_page_sequence_set_force_page_count (FoFo *fo_fo,
		         FoProperty *new_force_page_count)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_force_page_count == NULL) ||
		    FO_IS_PROPERTY_FORCE_PAGE_COUNT (new_force_page_count));

  if (new_force_page_count != NULL)
    {
      g_object_ref_sink (new_force_page_count);
    }
  if (fo_page_sequence->force_page_count != NULL)
    {
      g_object_unref (fo_page_sequence->force_page_count);
    }
  fo_page_sequence->force_page_count = new_force_page_count;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "force-page-count");*/
}

/**
 * fo_page_sequence_get_format:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "format" property of @fo_fo.
 *
 * Return value: The "format" property value.
**/
FoProperty *
fo_page_sequence_get_format (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->format;
}

/**
 * fo_page_sequence_set_format:
 * @fo_fo: The #FoFo object.
 * @new_format: The new "format" property value.
 * 
 * Sets the "format" property of @fo_fo to @new_format.
 **/
void
fo_page_sequence_set_format (FoFo *fo_fo,
		         FoProperty *new_format)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_format == NULL) ||
		    FO_IS_PROPERTY_FORMAT (new_format));

  if (new_format != NULL)
    {
      g_object_ref_sink (new_format);
    }
  if (fo_page_sequence->format != NULL)
    {
      g_object_unref (fo_page_sequence->format);
    }
  fo_page_sequence->format = new_format;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "format");*/
}

/**
 * fo_page_sequence_get_grouping_separator:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "grouping-separator" property of @fo_fo.
 *
 * Return value: The "grouping-separator" property value.
**/
FoProperty *
fo_page_sequence_get_grouping_separator (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->grouping_separator;
}

/**
 * fo_page_sequence_set_grouping_separator:
 * @fo_fo: The #FoFo object.
 * @new_grouping_separator: The new "grouping-separator" property value.
 * 
 * Sets the "grouping-separator" property of @fo_fo to @new_grouping_separator.
 **/
void
fo_page_sequence_set_grouping_separator (FoFo *fo_fo,
		         FoProperty *new_grouping_separator)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_grouping_separator == NULL) ||
		    FO_IS_PROPERTY_GROUPING_SEPARATOR (new_grouping_separator));

  if (new_grouping_separator != NULL)
    {
      g_object_ref_sink (new_grouping_separator);
    }
  if (fo_page_sequence->grouping_separator != NULL)
    {
      g_object_unref (fo_page_sequence->grouping_separator);
    }
  fo_page_sequence->grouping_separator = new_grouping_separator;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "grouping-separator");*/
}

/**
 * fo_page_sequence_get_grouping_size:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "grouping-size" property of @fo_fo.
 *
 * Return value: The "grouping-size" property value.
**/
FoProperty *
fo_page_sequence_get_grouping_size (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->grouping_size;
}

/**
 * fo_page_sequence_set_grouping_size:
 * @fo_fo: The #FoFo object.
 * @new_grouping_size: The new "grouping-size" property value.
 * 
 * Sets the "grouping-size" property of @fo_fo to @new_grouping_size.
 **/
void
fo_page_sequence_set_grouping_size (FoFo *fo_fo,
		         FoProperty *new_grouping_size)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_grouping_size == NULL) ||
		    FO_IS_PROPERTY_GROUPING_SIZE (new_grouping_size));

  if (new_grouping_size != NULL)
    {
      g_object_ref_sink (new_grouping_size);
    }
  if (fo_page_sequence->grouping_size != NULL)
    {
      g_object_unref (fo_page_sequence->grouping_size);
    }
  fo_page_sequence->grouping_size = new_grouping_size;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "grouping-size");*/
}

/**
 * fo_page_sequence_get_id:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "id" property of @fo_fo.
 *
 * Return value: The "id" property value.
**/
FoProperty *
fo_page_sequence_get_id (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->id;
}

/**
 * fo_page_sequence_set_id:
 * @fo_fo: The #FoFo object.
 * @new_id: The new "id" property value.
 * 
 * Sets the "id" property of @fo_fo to @new_id.
 **/
void
fo_page_sequence_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_id == NULL) ||
		    FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref_sink (new_id);
    }
  if (fo_page_sequence->id != NULL)
    {
      g_object_unref (fo_page_sequence->id);
    }
  fo_page_sequence->id = new_id;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "id");*/
}

/**
 * fo_page_sequence_get_initial_page_number:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "initial-page-number" property of @fo_fo.
 *
 * Return value: The "initial-page-number" property value.
**/
FoProperty *
fo_page_sequence_get_initial_page_number (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->initial_page_number;
}

/**
 * fo_page_sequence_set_initial_page_number:
 * @fo_fo: The #FoFo object.
 * @new_initial_page_number: The new "initial-page-number" property value.
 * 
 * Sets the "initial-page-number" property of @fo_fo to @new_initial_page_number.
 **/
void
fo_page_sequence_set_initial_page_number (FoFo *fo_fo,
		         FoProperty *new_initial_page_number)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_initial_page_number == NULL) ||
		    FO_IS_PROPERTY_INITIAL_PAGE_NUMBER (new_initial_page_number));

  if (new_initial_page_number != NULL)
    {
      g_object_ref_sink (new_initial_page_number);
    }
  if (fo_page_sequence->initial_page_number != NULL)
    {
      g_object_unref (fo_page_sequence->initial_page_number);
    }
  fo_page_sequence->initial_page_number = new_initial_page_number;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "initial-page-number");*/
}

/**
 * fo_page_sequence_get_language:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "language" property of @fo_fo.
 *
 * Return value: The "language" property value.
**/
FoProperty *
fo_page_sequence_get_language (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->language;
}

/**
 * fo_page_sequence_set_language:
 * @fo_fo: The #FoFo object.
 * @new_language: The new "language" property value.
 * 
 * Sets the "language" property of @fo_fo to @new_language.
 **/
void
fo_page_sequence_set_language (FoFo *fo_fo,
		         FoProperty *new_language)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_language == NULL) ||
		    FO_IS_PROPERTY_LANGUAGE (new_language));

  if (new_language != NULL)
    {
      g_object_ref_sink (new_language);
    }
  if (fo_page_sequence->language != NULL)
    {
      g_object_unref (fo_page_sequence->language);
    }
  fo_page_sequence->language = new_language;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "language");*/
}

/**
 * fo_page_sequence_get_letter_value:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "letter-value" property of @fo_fo.
 *
 * Return value: The "letter-value" property value.
**/
FoProperty *
fo_page_sequence_get_letter_value (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->letter_value;
}

/**
 * fo_page_sequence_set_letter_value:
 * @fo_fo: The #FoFo object.
 * @new_letter_value: The new "letter-value" property value.
 * 
 * Sets the "letter-value" property of @fo_fo to @new_letter_value.
 **/
void
fo_page_sequence_set_letter_value (FoFo *fo_fo,
		         FoProperty *new_letter_value)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_letter_value == NULL) ||
		    FO_IS_PROPERTY_LETTER_VALUE (new_letter_value));

  if (new_letter_value != NULL)
    {
      g_object_ref_sink (new_letter_value);
    }
  if (fo_page_sequence->letter_value != NULL)
    {
      g_object_unref (fo_page_sequence->letter_value);
    }
  fo_page_sequence->letter_value = new_letter_value;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "letter-value");*/
}

/**
 * fo_page_sequence_get_master_reference:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "master-reference" property of @fo_fo.
 *
 * Return value: The "master-reference" property value.
**/
FoProperty *
fo_page_sequence_get_master_reference (FoFo *fo_fo)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_val_if_fail (fo_page_sequence != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence), NULL);

  return fo_page_sequence->master_reference;
}

/**
 * fo_page_sequence_set_master_reference:
 * @fo_fo: The #FoFo object.
 * @new_master_reference: The new "master-reference" property value.
 * 
 * Sets the "master-reference" property of @fo_fo to @new_master_reference.
 **/
void
fo_page_sequence_set_master_reference (FoFo *fo_fo,
		         FoProperty *new_master_reference)
{
  FoPageSequence *fo_page_sequence = (FoPageSequence *) fo_fo;

  g_return_if_fail (fo_page_sequence != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo_page_sequence));
  g_return_if_fail ((new_master_reference == NULL) ||
		    FO_IS_PROPERTY_MASTER_REFERENCE (new_master_reference));

  if (new_master_reference != NULL)
    {
      g_object_ref_sink (new_master_reference);
    }
  if (fo_page_sequence->master_reference != NULL)
    {
      g_object_unref (fo_page_sequence->master_reference);
    }
  fo_page_sequence->master_reference = new_master_reference;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "master-reference");*/
}
