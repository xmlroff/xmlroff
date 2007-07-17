/* Fo
 * fo-multi-case.c: 'multi-case' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-multi-case-private.h"
#include "property/fo-property-id.h"
#include "property/fo-property-role.h"
#include "property/fo-property-source-document.h"

enum {
  PROP_0,
  PROP_ID,
  PROP_ROLE,
  PROP_SOURCE_DOCUMENT
};

static void fo_multi_case_class_init  (FoMultiCaseClass *klass);
static void fo_multi_case_get_property (GObject      *object,
                                        guint         prop_id,
                                        GValue       *value,
                                        GParamSpec   *pspec);
static void fo_multi_case_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec);
static void fo_multi_case_finalize    (GObject           *object);
static gboolean fo_multi_case_validate_content (FoFo    *fo,
                                                GError **error);
static void fo_multi_case_validate (FoFo      *fo,
                                    FoContext *current_context,
                                    FoContext *parent_context,
                                    GError   **error);
static void fo_multi_case_update_from_context (FoFo      *fo,
                                               FoContext *context);
static void fo_multi_case_debug_dump_properties (FoFo *fo,
                                                 gint  depth);

static gpointer parent_class;

/**
 * fo_multi_case_get_type:
 * 
 * Register the #FoMultiCase object type.
 * 
 * Return value: #GType value of the #FoMultiCase object type.
 **/
GType
fo_multi_case_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoMultiCaseClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_multi_case_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoMultiCase),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "multi-case",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_multi_case_class_init:
 * @klass: #FoMultiCaseClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoMultiCaseClass.
 **/
void
fo_multi_case_class_init (FoMultiCaseClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_multi_case_finalize;

  object_class->get_property = fo_multi_case_get_property;
  object_class->set_property = fo_multi_case_set_property;

  fofo_class->validate_content = fo_multi_case_validate_content;
  fofo_class->validate2 = fo_multi_case_validate;
  fofo_class->update_from_context = fo_multi_case_update_from_context;
  fofo_class->debug_dump_properties = fo_multi_case_debug_dump_properties;
  fofo_class->allow_mixed_content = TRUE;

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
     PROP_ROLE,
     g_param_spec_object ("role",
			  _("Role"),
			  _("Role property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SOURCE_DOCUMENT,
     g_param_spec_object ("source-document",
			  _("Source Document"),
			  _("Source Document property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_multi_case_finalize:
 * @object: #FoMultiCase object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoMultiCase.
 **/
void
fo_multi_case_finalize (GObject *object)
{
  FoMultiCase *fo_multi_case;

  fo_multi_case = FO_MULTI_CASE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_multi_case_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoMultiCase.
 **/
void
fo_multi_case_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_multi_case_get_id (fo_fo)));
      break;
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_multi_case_get_role (fo_fo)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_multi_case_get_source_document (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_multi_case_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoMultiCase.
 **/
void
fo_multi_case_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      fo_multi_case_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_ROLE:
      fo_multi_case_set_role (fo_fo, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_multi_case_set_source_document (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_multi_case_new:
 * 
 * Creates a new #FoMultiCase initialized to default value.
 * 
 * Return value: the new #FoMultiCase.
 **/
FoFo*
fo_multi_case_new (void)
{
  return FO_FO (g_object_new (fo_multi_case_get_type (),
                              NULL));
}

/**
 * fo_multi_case_validate_content:
 * @fo:    #FoMultiCase object to validate.
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
fo_multi_case_validate_content (FoFo    *fo,
                                GError **error)
{
  /*GError *tmp_error = NULL;*/

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_MULTI_CASE (fo), TRUE);
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
 * fo_multi_case_validate:
 * @fo:              #FoMultiCase object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_multi_case_validate (FoFo      *fo,
                        FoContext *current_context,
                        FoContext *parent_context,
                        GError   **error)
{
  FoMultiCase *fo_multi_case;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MULTI_CASE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_multi_case = FO_MULTI_CASE (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_multi_case_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_multi_case_update_from_context (FoFo      *fo,
                                   FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MULTI_CASE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_multi_case_set_id (fo,
			  fo_context_get_id (context));
  fo_multi_case_set_role (fo,
			  fo_context_get_role (context));
  fo_multi_case_set_source_document (fo,
			  fo_context_get_source_document (context));
}

/**
 * fo_multi_case_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_multi_case_debug_dump_properties (FoFo *fo,
                                     gint  depth)
{
  FoMultiCase *fo_multi_case;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MULTI_CASE (fo));

  fo_multi_case = FO_MULTI_CASE (fo);

  fo_object_debug_dump (fo_multi_case->id, depth);
  fo_object_debug_dump (fo_multi_case->role, depth);
  fo_object_debug_dump (fo_multi_case->source_document, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_multi_case_get_id:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "id" property of @fo_fo.
 *
 * Return value: The "id" property value.
**/
FoProperty*
fo_multi_case_get_id (FoFo *fo_fo)
{
  FoMultiCase *fo_multi_case = (FoMultiCase *) fo_fo;

  g_return_val_if_fail (fo_multi_case != NULL, NULL);
  g_return_val_if_fail (FO_IS_MULTI_CASE (fo_multi_case), NULL);

  return fo_multi_case->id;
}

/**
 * fo_multi_case_set_id:
 * @fo_fo: The #FoFo object
 * @new_id: The new "id" property value
 * 
 * Sets the "id" property of @fo_fo to @new_id
 **/
void
fo_multi_case_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoMultiCase *fo_multi_case = (FoMultiCase *) fo_fo;

  g_return_if_fail (fo_multi_case != NULL);
  g_return_if_fail (FO_IS_MULTI_CASE (fo_multi_case));
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_multi_case->id != NULL)
    {
      g_object_unref (fo_multi_case->id);
    }
  fo_multi_case->id = new_id;
  /*g_object_notify (G_OBJECT (fo_multi_case), "id");*/
}

/**
 * fo_multi_case_get_role:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "role" property of @fo_fo.
 *
 * Return value: The "role" property value.
**/
FoProperty*
fo_multi_case_get_role (FoFo *fo_fo)
{
  FoMultiCase *fo_multi_case = (FoMultiCase *) fo_fo;

  g_return_val_if_fail (fo_multi_case != NULL, NULL);
  g_return_val_if_fail (FO_IS_MULTI_CASE (fo_multi_case), NULL);

  return fo_multi_case->role;
}

/**
 * fo_multi_case_set_role:
 * @fo_fo: The #FoFo object
 * @new_role: The new "role" property value
 * 
 * Sets the "role" property of @fo_fo to @new_role
 **/
void
fo_multi_case_set_role (FoFo *fo_fo,
		         FoProperty *new_role)
{
  FoMultiCase *fo_multi_case = (FoMultiCase *) fo_fo;

  g_return_if_fail (fo_multi_case != NULL);
  g_return_if_fail (FO_IS_MULTI_CASE (fo_multi_case));
  g_return_if_fail (FO_IS_PROPERTY_ROLE (new_role));

  if (new_role != NULL)
    {
      g_object_ref (new_role);
    }
  if (fo_multi_case->role != NULL)
    {
      g_object_unref (fo_multi_case->role);
    }
  fo_multi_case->role = new_role;
  /*g_object_notify (G_OBJECT (fo_multi_case), "role");*/
}

/**
 * fo_multi_case_get_source_document:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "source-document" property of @fo_fo.
 *
 * Return value: The "source-document" property value.
**/
FoProperty*
fo_multi_case_get_source_document (FoFo *fo_fo)
{
  FoMultiCase *fo_multi_case = (FoMultiCase *) fo_fo;

  g_return_val_if_fail (fo_multi_case != NULL, NULL);
  g_return_val_if_fail (FO_IS_MULTI_CASE (fo_multi_case), NULL);

  return fo_multi_case->source_document;
}

/**
 * fo_multi_case_set_source_document:
 * @fo_fo: The #FoFo object
 * @new_source_document: The new "source-document" property value
 * 
 * Sets the "source-document" property of @fo_fo to @new_source_document
 **/
void
fo_multi_case_set_source_document (FoFo *fo_fo,
		         FoProperty *new_source_document)
{
  FoMultiCase *fo_multi_case = (FoMultiCase *) fo_fo;

  g_return_if_fail (fo_multi_case != NULL);
  g_return_if_fail (FO_IS_MULTI_CASE (fo_multi_case));
  g_return_if_fail (FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document != NULL)
    {
      g_object_ref (new_source_document);
    }
  if (fo_multi_case->source_document != NULL)
    {
      g_object_unref (fo_multi_case->source_document);
    }
  fo_multi_case->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_multi_case), "source-document");*/
}
