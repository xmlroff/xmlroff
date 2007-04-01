/* Fo
 * fo-declarations.c: 'declarations' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-declarations.c,v 1.3 2003/05/16 12:48:20 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo/fo-declarations-private.h"

static void fo_declarations_class_init  (FoDeclarationsClass *klass);
static void fo_declarations_finalize    (GObject           *object);
static gboolean fo_declarations_validate_content (FoFo    *fo,
                                                  GError **error);
static void fo_declarations_validate (FoFo      *fo,
                                      FoContext *current_context,
                                      FoContext *parent_context,
                                      GError   **error);
static void fo_declarations_update_from_context (FoFo      *fo,
                                                 FoContext *context);
static void fo_declarations_debug_dump_properties (FoFo *fo,
                                                   gint  depth);

static gpointer parent_class;

/**
 * fo_declarations_get_type:
 * 
 * Register the #FoDeclarations object type.
 * 
 * Return value: #GType value of the #FoDeclarations object type.
 **/
GType
fo_declarations_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoDeclarationsClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_declarations_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoDeclarations),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "declarations",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_declarations_class_init:
 * @klass: #FoDeclarationsClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoDeclarationsClass.
 **/
void
fo_declarations_class_init (FoDeclarationsClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_declarations_finalize;

  fofo_class->validate_content = fo_declarations_validate_content;
  fofo_class->validate2 = fo_declarations_validate;
  fofo_class->update_from_context = fo_declarations_update_from_context;
  fofo_class->debug_dump_properties = fo_declarations_debug_dump_properties;
}

/**
 * fo_declarations_finalize:
 * @object: #FoDeclarations object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoDeclarations.
 **/
void
fo_declarations_finalize (GObject *object)
{
  FoDeclarations *fo_declarations;

  fo_declarations = FO_DECLARATIONS (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_declarations_new:
 * 
 * Creates a new #FoDeclarations initialized to default value.
 * 
 * Return value: the new #FoDeclarations.
 **/
FoFo*
fo_declarations_new (void)
{
  return FO_FO (g_object_new (fo_declarations_get_type (),
                              NULL));
}

/**
 * fo_declarations_validate_content:
 * @fo:    #FoDeclarations object to validate.
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
fo_declarations_validate_content (FoFo    *fo,
                                  GError **error)
{
  GError *tmp_error = NULL;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_DECLARATIONS (fo), TRUE);
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
 * fo_declarations_validate:
 * @fo:              #FoDeclarations object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_declarations_validate (FoFo      *fo,
                          FoContext *current_context,
                          FoContext *parent_context,
                          GError   **error)
{
  FoDeclarations *fo_declarations;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_DECLARATIONS (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_declarations = FO_DECLARATIONS (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_declarations_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_declarations_update_from_context (FoFo      *fo,
                                     FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_DECLARATIONS (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

}

/**
 * fo_declarations_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_declarations_debug_dump_properties (FoFo *fo,
                                       gint  depth)
{
  FoDeclarations *fo_declarations;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_DECLARATIONS (fo));

  fo_declarations = FO_DECLARATIONS (fo);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
         "(No properties)");

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}
