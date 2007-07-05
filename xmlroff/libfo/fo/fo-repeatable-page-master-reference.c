/* Fo
 * fo-repeatable-page-master-reference.c: 'repeatable-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-repeatable-page-master-reference-private.h"
#include "property/fo-property-master-reference.h"

enum {
  PROP_0,
  PROP_MASTER_REFERENCE
};

static void fo_repeatable_page_master_reference_class_init  (FoRepeatablePageMasterReferenceClass *klass);
static void fo_repeatable_page_master_reference_get_property (GObject      *object,
                                                              guint         prop_id,
                                                              GValue       *value,
                                                              GParamSpec   *pspec);
static void fo_repeatable_page_master_reference_set_property (GObject      *object,
                                                              guint         prop_id,
                                                              const GValue *value,
                                                              GParamSpec   *pspec);
static void fo_repeatable_page_master_reference_finalize    (GObject           *object);
static gboolean fo_repeatable_page_master_reference_validate_content (FoFo    *fo,
                                                                      GError **error);
static void fo_repeatable_page_master_reference_validate (FoFo      *fo,
                                                          FoContext *current_context,
                                                          FoContext *parent_context,
                                                          GError   **error);
static void fo_repeatable_page_master_reference_update_from_context (FoFo      *fo,
                                                                     FoContext *context);
static void fo_repeatable_page_master_reference_debug_dump_properties (FoFo *fo,
                                                                       gint  depth);

static gpointer parent_class;

/**
 * fo_repeatable_page_master_reference_get_type:
 * 
 * Register the #FoRepeatablePageMasterReference object type.
 * 
 * Return value: #GType value of the #FoRepeatablePageMasterReference object type.
 **/
GType
fo_repeatable_page_master_reference_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoRepeatablePageMasterReferenceClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_repeatable_page_master_reference_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoRepeatablePageMasterReference),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "repeatable-page-master-reference",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_repeatable_page_master_reference_class_init:
 * @klass: #FoRepeatablePageMasterReferenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRepeatablePageMasterReferenceClass.
 **/
void
fo_repeatable_page_master_reference_class_init (FoRepeatablePageMasterReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_repeatable_page_master_reference_finalize;

  object_class->get_property = fo_repeatable_page_master_reference_get_property;
  object_class->set_property = fo_repeatable_page_master_reference_set_property;

  fofo_class->validate_content = fo_repeatable_page_master_reference_validate_content;
  fofo_class->validate2 = fo_repeatable_page_master_reference_validate;
  fofo_class->update_from_context = fo_repeatable_page_master_reference_update_from_context;
  fofo_class->debug_dump_properties = fo_repeatable_page_master_reference_debug_dump_properties;

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
 * fo_repeatable_page_master_reference_finalize:
 * @object: #FoRepeatablePageMasterReference object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoRepeatablePageMasterReference.
 **/
void
fo_repeatable_page_master_reference_finalize (GObject *object)
{
  FoRepeatablePageMasterReference *fo_repeatable_page_master_reference;

  fo_repeatable_page_master_reference = FO_REPEATABLE_PAGE_MASTER_REFERENCE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_repeatable_page_master_reference_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoRepeatablePageMasterReference.
 **/
void
fo_repeatable_page_master_reference_get_property (GObject    *object,
                                                  guint       prop_id,
                                                  GValue     *value,
                                                  GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MASTER_REFERENCE:
      g_value_set_object (value, G_OBJECT (fo_repeatable_page_master_reference_get_master_reference (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_repeatable_page_master_reference_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoRepeatablePageMasterReference.
 **/
void
fo_repeatable_page_master_reference_set_property (GObject      *object,
                                                  guint         prop_id,
                                                  const GValue *value,
                                                  GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MASTER_REFERENCE:
      fo_repeatable_page_master_reference_set_master_reference (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_repeatable_page_master_reference_new:
 * 
 * Creates a new #FoRepeatablePageMasterReference initialized to default value.
 * 
 * Return value: the new #FoRepeatablePageMasterReference.
 **/
FoFo*
fo_repeatable_page_master_reference_new (void)
{
  return FO_FO (g_object_new (fo_repeatable_page_master_reference_get_type (),
                              NULL));
}

/**
 * fo_repeatable_page_master_reference_validate_content:
 * @fo:    #FoRepeatablePageMasterReference object to validate.
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
fo_repeatable_page_master_reference_validate_content (FoFo    *fo,
                                                      GError **error)
{
  GError *tmp_error = NULL;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo), TRUE);
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
 * fo_repeatable_page_master_reference_validate:
 * @fo:              #FoRepeatablePageMasterReference object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_repeatable_page_master_reference_validate (FoFo      *fo,
                                              FoContext *current_context,
                                              FoContext *parent_context,
                                              GError   **error)
{
  FoRepeatablePageMasterReference *fo_repeatable_page_master_reference;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_repeatable_page_master_reference = FO_REPEATABLE_PAGE_MASTER_REFERENCE (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_repeatable_page_master_reference_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_repeatable_page_master_reference_update_from_context (FoFo      *fo,
                                                         FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_repeatable_page_master_reference_set_master_reference (fo,
			  fo_context_get_master_reference (context));
}

/**
 * fo_repeatable_page_master_reference_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_repeatable_page_master_reference_debug_dump_properties (FoFo *fo,
                                                           gint  depth)
{
  FoRepeatablePageMasterReference *fo_repeatable_page_master_reference;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo));

  fo_repeatable_page_master_reference = FO_REPEATABLE_PAGE_MASTER_REFERENCE (fo);

  fo_object_debug_dump (fo_repeatable_page_master_reference->master_reference, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_repeatable_page_master_reference_get_master_reference:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "master-reference" property of @fo_fo.
 *
 * Return value: The "master-reference" property value.
**/
FoProperty*
fo_repeatable_page_master_reference_get_master_reference (FoFo *fo_fo)
{
  FoRepeatablePageMasterReference *fo_repeatable_page_master_reference = (FoRepeatablePageMasterReference *) fo_fo;

  g_return_val_if_fail (fo_repeatable_page_master_reference != NULL, NULL);
  g_return_val_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo_repeatable_page_master_reference), NULL);

  return fo_repeatable_page_master_reference->master_reference;
}

/**
 * fo_repeatable_page_master_reference_set_master_reference:
 * @fo_fo: The #FoFo object
 * @new_master_reference: The new "master-reference" property value
 * 
 * Sets the "master-reference" property of @fo_fo to @new_master_reference
 **/
void
fo_repeatable_page_master_reference_set_master_reference (FoFo *fo_fo,
		         FoProperty *new_master_reference)
{
  FoRepeatablePageMasterReference *fo_repeatable_page_master_reference = (FoRepeatablePageMasterReference *) fo_fo;

  g_return_if_fail (fo_repeatable_page_master_reference != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo_repeatable_page_master_reference));
  g_return_if_fail (FO_IS_PROPERTY_MASTER_REFERENCE (new_master_reference));

  if (new_master_reference != NULL)
    {
      g_object_ref (new_master_reference);
    }
  if (fo_repeatable_page_master_reference->master_reference != NULL)
    {
      g_object_unref (fo_repeatable_page_master_reference->master_reference);
    }
  fo_repeatable_page_master_reference->master_reference = new_master_reference;
  /*g_object_notify (G_OBJECT (fo_repeatable_page_master_reference), "master-reference");*/
}
