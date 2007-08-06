/* Fo
 * fo-layout-master-set.c: 'layout-master-set' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-layout-master-set-private.h"
#include "fo/fo-simple-page-master.h"
#include "fo/fo-page-sequence-master.h"

static void fo_layout_master_set_class_init  (FoLayoutMasterSetClass *klass);
static void fo_layout_master_set_finalize    (GObject           *object);
static gboolean fo_layout_master_set_validate_content (FoFo    *fo,
                                                       GError **error);
static void fo_layout_master_set_validate (FoFo      *fo,
                                           FoContext *current_context,
                                           FoContext *parent_context,
                                           GError   **error);
static void fo_layout_master_set_update_from_context (FoFo      *fo,
                                                      FoContext *context);
static void fo_layout_master_set_debug_dump_properties (FoFo *fo,
                                                        gint  depth);

static gpointer parent_class;

/**
 * fo_layout_master_set_get_type:
 * 
 * Register the #FoLayoutMasterSet object type.
 * 
 * Return value: #GType value of the #FoLayoutMasterSet object type.
 **/
GType
fo_layout_master_set_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLayoutMasterSetClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_layout_master_set_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLayoutMasterSet),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoLayoutMasterSet",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_layout_master_set_class_init:
 * @klass: #FoLayoutMasterSetClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoLayoutMasterSetClass.
 **/
void
fo_layout_master_set_class_init (FoLayoutMasterSetClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_layout_master_set_finalize;

  fofo_class->validate_content = fo_layout_master_set_validate_content;
  fofo_class->validate2 = fo_layout_master_set_validate;
  fofo_class->update_from_context = fo_layout_master_set_update_from_context;
  fofo_class->debug_dump_properties = fo_layout_master_set_debug_dump_properties;

}

/**
 * fo_layout_master_set_finalize:
 * @object: #FoLayoutMasterSet object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoLayoutMasterSet.
 **/
void
fo_layout_master_set_finalize (GObject *object)
{
  FoLayoutMasterSet *fo_layout_master_set;

  fo_layout_master_set = FO_LAYOUT_MASTER_SET (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_layout_master_set_new:
 * 
 * Creates a new #FoLayoutMasterSet initialized to default value.
 * 
 * Return value: the new #FoLayoutMasterSet.
 **/
FoFo*
fo_layout_master_set_new (void)
{
  return FO_FO (g_object_new (fo_layout_master_set_get_type (),
                              NULL));
}

/**
 * fo_layout_master_set_validate_content:
 * @fo:    #FoLayoutMasterSet object to validate.
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
fo_layout_master_set_validate_content (FoFo    *fo,
                                       GError **error)
{
  GError *tmp_error;
  FoNode *fo_node;
  FoNode *child_node;
  gint n_children;

  g_return_val_if_fail (FO_IS_LAYOUT_MASTER_SET (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_node = FO_NODE (fo);

  fo_fo_trim_whitespace_children (fo);

  n_children = fo_node_n_children (fo_node);

  if (n_children == 0)
    {
      tmp_error = g_error_new (FO_FO_ERROR,
			       FO_FO_ERROR_EMPTY,
			       _(fo_fo_error_messages[FO_FO_ERROR_EMPTY]),
			       fo_object_sprintf (FO_OBJECT (fo)));

      return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					       error,
					       tmp_error);
    }

  child_node = fo_node_first_child (fo_node);

  while (child_node)
    {
      if (FO_IS_SIMPLE_PAGE_MASTER (child_node) ||
	  FO_IS_PAGE_SEQUENCE_MASTER (child_node))
	{
	  child_node = fo_node_next_sibling (child_node);
	}
      else
	{
	  tmp_error = g_error_new (FO_FO_ERROR,
				   FO_FO_ERROR_INVALID_CONTENT,
				   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
				   fo_object_sprintf (fo));

	  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
						   error,
						   tmp_error);
	}
    }

  return FALSE;
}

/**
 * fo_layout_master_set_validate:
 * @fo:              #FoLayoutMasterSet object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_layout_master_set_validate (FoFo      *fo,
                               FoContext *current_context,
                               FoContext *parent_context,
                               GError   **error)
{
  FoLayoutMasterSet *fo_layout_master_set;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_LAYOUT_MASTER_SET (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_layout_master_set = FO_LAYOUT_MASTER_SET (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_layout_master_set_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_layout_master_set_update_from_context (FoFo      *fo,
                                          FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_LAYOUT_MASTER_SET (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

}

/**
 * fo_layout_master_set_debug_dump_properties:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_layout_master_set_debug_dump_properties (FoFo *fo, gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_LAYOUT_MASTER_SET (fo));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s(No properties)",
	 indent);

  g_free (indent);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}
