/* Fo
 * fo-page-sequence.c: 'page-sequence' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-page-sequence.c,v 1.4 2006/04/07 11:06:57 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo/fo-page-sequence-private.h"
#include "fo/fo-page-sequence-area.h"
#include "fo/fo-tree.h"
#include "fo/fo-simple-page-master.h"
#include "property/fo-property-format.h"
#include "property/fo-property-grouping-separator.h"
#include "property/fo-property-grouping-size.h"
#include "property/fo-property-id.h"
#include "property/fo-property-letter-value.h"
#include "property/fo-property-master-reference.h"

enum {
  PROP_0,
  PROP_FORMAT,
  PROP_GROUPING_SEPARATOR,
  PROP_GROUPING_SIZE,
  PROP_ID,
  PROP_LETTER_VALUE,
  PROP_MASTER_REFERENCE
};

static void fo_page_sequence_class_init  (FoPageSequenceClass *klass);
static void fo_page_sequence_get_property (GObject      *object,
                                           guint         prop_id,
                                           GValue       *value,
                                           GParamSpec   *pspec);
static void fo_page_sequence_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);
static void fo_page_sequence_finalize    (GObject           *object);
static gboolean fo_page_sequence_validate_content (FoFo    *fo,
                                                   GError **error);
static void fo_page_sequence_validate (FoFo      *fo,
                                       FoContext *current_context,
                                       FoContext *parent_context,
                                       GError   **error);
static void fo_page_sequence_update_from_context (FoFo      *fo,
                                                  FoContext *context);
static void fo_page_sequence_debug_dump_properties (FoFo *fo,
                                                    gint  depth);

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
        (GClassInitFunc) fo_page_sequence_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPageSequence),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "page-sequence",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_page_sequence_class_init:
 * @klass: #FoPageSequenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPageSequenceClass.
 **/
void
fo_page_sequence_class_init (FoPageSequenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_page_sequence_finalize;

  object_class->get_property = fo_page_sequence_get_property;
  object_class->set_property = fo_page_sequence_set_property;

  fofo_class->validate_content =
    fo_page_sequence_validate_content;
  fofo_class->validate2 =
    fo_page_sequence_validate;
  fofo_class->update_from_context = fo_page_sequence_update_from_context;
  fofo_class->debug_dump_properties = fo_page_sequence_debug_dump_properties;
  fofo_class->area_new2 =
    fo_page_sequence_area_new2;

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
 * fo_page_sequence_finalize:
 * @object: #FoPageSequence object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPageSequence.
 **/
void
fo_page_sequence_finalize (GObject *object)
{
  FoPageSequence *fo_page_sequence;

  fo_page_sequence = FO_PAGE_SEQUENCE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_page_sequence_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoPageSequence.
 **/
void
fo_page_sequence_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
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
 * fo_page_sequence_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoPageSequence.
 **/
void
fo_page_sequence_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
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
 * fo_page_sequence_validate_content:
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
fo_page_sequence_validate_content (FoFo    *fo,
                                   GError **error)
{
  GError *tmp_error = NULL;

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
 * fo_page_sequence_validate:
 * @fo:              #FoPageSequence object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_page_sequence_validate (FoFo      *fo,
                           FoContext *current_context,
                           FoContext *parent_context,
                           GError   **error)
{
  FoPageSequence *fo_page_sequence;
  FoFo *tree;
  FoFo *page_master;
  gchar *master_name;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_page_sequence = FO_PAGE_SEQUENCE (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_fo_register_id (fo,
                     fo_property_get_value (fo_page_sequence->id));

  master_name =
    fo_name_get_value (
    fo_property_get_value (fo_page_sequence_get_master_reference (fo)));

  tree = fo->tree;

  if (tree != NULL)
    {
      page_master = fo_tree_master_name_get (tree, master_name);
      /*
      g_print ("Master: %s\n", fo_object_sprintf (page_master));

      fo_object_debug_dump (page_master, 0);
      */
      if (page_master != NULL)
	fo_page_sequence->page_master = page_master;
      else
	fo_page_sequence->page_master = fo_tree_default_master_get (tree);
    }

  fo_context_set_writing_mode (current_context,
			       fo_simple_page_master_get_writing_mode (fo_page_sequence->page_master));

}

/**
 * fo_page_sequence_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_page_sequence_update_from_context (FoFo      *fo,
                                      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_page_sequence_set_format (fo,
			  fo_context_get_format (context));
  fo_page_sequence_set_grouping_separator (fo,
			  fo_context_get_grouping_separator (context));
  fo_page_sequence_set_grouping_size (fo,
			  fo_context_get_grouping_size (context));
  fo_page_sequence_set_id (fo,
			  fo_context_get_id (context));
  fo_page_sequence_set_letter_value (fo,
			  fo_context_get_letter_value (context));
  fo_page_sequence_set_master_reference (fo,
			  fo_context_get_master_reference (context));
}

/**
 * fo_page_sequence_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_page_sequence_debug_dump_properties (FoFo *fo,
                                        gint  depth)
{
  FoPageSequence *fo_page_sequence;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE (fo));

  fo_page_sequence = FO_PAGE_SEQUENCE (fo);

  fo_object_debug_dump (fo_page_sequence->format, depth);
  fo_object_debug_dump (fo_page_sequence->grouping_separator, depth);
  fo_object_debug_dump (fo_page_sequence->grouping_size, depth);
  fo_object_debug_dump (fo_page_sequence->id, depth);
  fo_object_debug_dump (fo_page_sequence->letter_value, depth);
  fo_object_debug_dump (fo_page_sequence->master_reference, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_page_sequence_get_format:
 * @fo_fo: The @FoFo object.
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
  g_return_if_fail (FO_IS_PROPERTY_FORMAT (new_format));

  if (new_format != NULL)
    {
      g_object_ref (new_format);
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
 * @fo_fo: The @FoFo object.
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
  g_return_if_fail (FO_IS_PROPERTY_GROUPING_SEPARATOR (new_grouping_separator));

  if (new_grouping_separator != NULL)
    {
      g_object_ref (new_grouping_separator);
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
 * @fo_fo: The @FoFo object.
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
  g_return_if_fail (FO_IS_PROPERTY_GROUPING_SIZE (new_grouping_size));

  if (new_grouping_size != NULL)
    {
      g_object_ref (new_grouping_size);
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
 * @fo_fo: The @FoFo object.
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
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_page_sequence->id != NULL)
    {
      g_object_unref (fo_page_sequence->id);
    }
  fo_page_sequence->id = new_id;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "id");*/
}

/**
 * fo_page_sequence_get_letter_value:
 * @fo_fo: The @FoFo object.
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
  g_return_if_fail (FO_IS_PROPERTY_LETTER_VALUE (new_letter_value));

  if (new_letter_value != NULL)
    {
      g_object_ref (new_letter_value);
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
 * @fo_fo: The @FoFo object.
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
  g_return_if_fail (FO_IS_PROPERTY_MASTER_REFERENCE (new_master_reference));

  if (new_master_reference != NULL)
    {
      g_object_ref (new_master_reference);
    }
  if (fo_page_sequence->master_reference != NULL)
    {
      g_object_unref (fo_page_sequence->master_reference);
    }
  fo_page_sequence->master_reference = new_master_reference;
  /*g_object_notify (G_OBJECT (fo_page_sequence), "master-reference");*/
}
