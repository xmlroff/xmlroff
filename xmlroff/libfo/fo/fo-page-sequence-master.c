/* Fo
 * fo-page-sequence-master.c: Page Sequence Master formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-fo.h"
#include "fo-fo-private.h"
#include "fo-page-sequence-master.h"
#include "fo-page-sequence-master-private.h"
#include "fo-tree.h"
#include "fo-single-page-master-reference.h"
#include "fo-repeatable-page-master-reference.h"
#include "fo-repeatable-page-master-alternatives.h"
#include "property/fo-property-master-name.h"

enum {
  PROP_0,
  PROP_MASTER_NAME
};

static void fo_page_sequence_master_class_init  (FoPageSequenceMasterClass *klass);
static void fo_page_sequence_master_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_page_sequence_master_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_page_sequence_master_finalize    (GObject           *object);
static gboolean fo_page_sequence_master_validate_content (FoFo    *fo,
                                                          GError **error);
static void fo_page_sequence_master_validate (FoFo      *fo,
                                              FoContext *current_context,
                                              FoContext *parent_context);
static void fo_page_sequence_master_update_from_context (FoFo      *fo,
                                                         FoContext *context);
static void fo_page_sequence_master_debug_dump_properties (FoFo *fo,
                                                           gint  depth);

static gpointer parent_class;

/**
 * fo_page_sequence_master_get_type:
 * @void: 
 * 
 * Register the FoPageSequenceMaster object type.
 * 
 * Return value: GType value of the FoPageSequenceMaster object type.
 **/
GType
fo_page_sequence_master_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPageSequenceMasterClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_page_sequence_master_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPageSequenceMaster),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_FO,
                                            "page-sequence-master",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_page_sequence_master_class_init:
 * @klass: FoPageSequenceMasterClass object to initialise
 * 
 * Implements GClassInitFunc for FoPageSequenceMasterClass
 **/
void
fo_page_sequence_master_class_init (FoPageSequenceMasterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_page_sequence_master_finalize;

  object_class->set_property = fo_page_sequence_master_set_property;
  object_class->get_property = fo_page_sequence_master_get_property;

  FO_FO_CLASS (klass)->validate_content = fo_page_sequence_master_validate_content;
  FO_FO_CLASS (klass)->validate = fo_page_sequence_master_validate;
  FO_FO_CLASS (klass)->update_from_context = fo_page_sequence_master_update_from_context;
  FO_FO_CLASS (klass)->debug_dump_properties = fo_page_sequence_master_debug_dump_properties;
  FO_FO_CLASS (klass)->area_new2 = NULL;

  g_object_class_install_property
    (object_class,
     PROP_MASTER_NAME,
     g_param_spec_object ("master-name",
			  _("Master Name"),
			  _("Master Name property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_page_sequence_master_finalize:
 * @object: FoPageSequenceMaster object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoPageSequenceMaster
 **/
void
fo_page_sequence_master_finalize (GObject *object)
{
  FoPageSequenceMaster *fo_page_sequence_master;

  fo_page_sequence_master = FO_PAGE_SEQUENCE_MASTER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_page_sequence_master_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoPageSequenceMaster
 **/
void
fo_page_sequence_master_set_property (GObject      *object,
                                      guint         prop_id,
                                      const GValue *value,
                                      GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MASTER_NAME:
      fo_page_sequence_master_set_master_name (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_page_sequence_master_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoPageSequenceMaster
 **/
void
fo_page_sequence_master_get_property (GObject    *object,
                                      guint       prop_id,
                                      GValue     *value,
                                      GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MASTER_NAME:
      g_value_set_object (value, G_OBJECT (fo_page_sequence_master_get_master_name (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_page_sequence_master_new:
 * 
 * Creates a new #FoPageSequenceMaster initialized to default value.
 * 
 * Return value: the new #FoPageSequenceMaster
 **/
FoFo*
fo_page_sequence_master_new (void)
{
  return FO_FO (g_object_new (fo_page_sequence_master_get_type (), NULL));
}

/**
 * fo_page_sequence_master_validate_content:
 * @fo:    FoPageSequenceMaster object to validate
 * @error: GError indicating error condition, if any
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches GNodeTraverseFunc model: FALSE indicates
 * content model is correct, or TRUE indicates an error.  When used
 * with fo_node_traverse(), returning TRUE stops the traversal.
 * 
 * Return value: FALSE if content model okay, TRUE if not
 **/
gboolean
fo_page_sequence_master_validate_content (FoFo    *fo,
                                          GError **error)
{
  GError *tmp_error;
  FoNode *fo_node;
  FoNode *child_node;
  gint n_children;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE_MASTER (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_node = FO_NODE (fo);

  fo_fo_trim_whitespace_children (fo);

  n_children = fo_node_n_children (fo_node);

  if (n_children == 0)
    {
      goto error;
    }

  child_node = fo_node_first_child (fo_node);

  while (child_node)
    {
      if (FO_IS_SINGLE_PAGE_MASTER_REFERENCE (child_node) ||
	  FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (child_node) ||
	  FO_IS_REPEATABLE_PAGE_MASTER_ALTERNATIVES (child_node))
	{
	  child_node = fo_node_next_sibling (child_node);
	}
      else
	{
	  goto error;
	}
    }

  return FALSE;

 error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (FO_OBJECT (fo)));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
}

/**
 * fo_page_sequence_master_validate:
 * @fo:              FoPageSequenceMaster object to validate
 * @current_context: FoContext associated with current object
 * @parent_context:  FoContext associated with parent FO
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values
 **/
void
fo_page_sequence_master_validate (FoFo      *fo,
                                  FoContext *current_context,
                                  FoContext *parent_context)
{
  FoFo *tree;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE_MASTER (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  tree = fo->tree;

  if (tree != NULL)
    {
      gchar *master_name =
	fo_name_get_value
	(fo_property_get_value
	 (fo_page_sequence_master_get_master_name (fo)));

      fo_tree_page_sequence_master_name_add (tree,
					     master_name,
					     fo);
      g_free (master_name);
    }
  else
    {
      g_assert_not_reached();
    }
}

/**
 * fo_page_sequence_master_update_from_context:
 * @fo:      The #FoFo object
 * @context: The #FoContext object from which to update the properties of @fo
 * 
 * Sets the properties of @fo to the corresponding property values in @context
 **/
void
fo_page_sequence_master_update_from_context (FoFo *fo,
                                             FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE_MASTER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_page_sequence_master_set_master_name (fo,
			  fo_context_get_master_name (context));
}

/**
 * fo_page_sequence_master_debug_dump_properties:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_page_sequence_master_debug_dump_properties (FoFo *fo, gint depth)
{
  FoPageSequenceMaster *fo_page_sequence_master;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE_MASTER (fo));

  fo_page_sequence_master = FO_PAGE_SEQUENCE_MASTER (fo);

  fo_object_debug_dump (fo_page_sequence_master->master_name, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_page_sequence_master_set_master_name:
 * @fo_fo: The @FoFo object
 * @new_master_name: The new "master-name" property value
 * 
 * Sets the #master-name property of @page_sequence_master to @new_master_name
 **/
void
fo_page_sequence_master_set_master_name (FoFo *fo_fo,
		         FoProperty *new_master_name)
{
  FoPageSequenceMaster *fo_page_sequence_master = (FoPageSequenceMaster *) fo_fo;

  g_return_if_fail (fo_page_sequence_master != NULL);
  g_return_if_fail (FO_IS_PAGE_SEQUENCE_MASTER (fo_page_sequence_master));
  g_return_if_fail (FO_IS_PROPERTY_MASTER_NAME (new_master_name));

  if (new_master_name)
    g_object_ref (G_OBJECT (new_master_name));
  if (fo_page_sequence_master->master_name)
    g_object_unref (G_OBJECT (fo_page_sequence_master->master_name));
  fo_page_sequence_master->master_name = new_master_name;
  /*g_object_notify (G_OBJECT (fo_page_sequence_master), "master-name");*/
}

/**
 * fo_page_sequence_master_get_master_name:
 * @fo_fo: The @FoFo object
 *
 * Gets the #master-name property of @page_sequence_master
 *
 * Return value: The "master-name" property value
**/
FoProperty*
fo_page_sequence_master_get_master_name (FoFo *fo_fo)
{
  FoPageSequenceMaster *fo_page_sequence_master = (FoPageSequenceMaster *) fo_fo;

  g_return_val_if_fail (fo_page_sequence_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_SEQUENCE_MASTER (fo_page_sequence_master), NULL);

  return fo_page_sequence_master->master_name;
}
