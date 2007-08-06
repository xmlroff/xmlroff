/* Fo
 * fo-multi-property-set.c: 'multi-property-set' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-fo.h"
#include "fo-fo-private.h"
#include "fo-multi-property-set.h"
#include "fo-multi-property-set-private.h"
#include "property/fo-property-id.h"

enum {
  PROP_0,
  PROP_ID
};

static void fo_multi_property_set_class_init  (FoMultiPropertySetClass *klass);
static void fo_multi_property_set_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_multi_property_set_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_multi_property_set_finalize    (GObject           *object);
static gboolean fo_multi_property_set_validate_content (FoFo    *fo,
                                                        GError **error);
static void fo_multi_property_set_validate (FoFo      *fo,
                                            FoContext *current_context,
                                            FoContext *parent_context,
                                            GError   **error);
static void fo_multi_property_set_update_from_context (FoFo      *fo,
                                                       FoContext *context);
static void fo_multi_property_set_debug_dump_properties (FoFo *fo,
                                                         gint  depth);

static gpointer parent_class;

/**
 * fo_multi_property_set_get_type:
 * @void: 
 * 
 * Register the FoMultiPropertySet object type.
 * 
 * Return value: GType value of the FoMultiPropertySet object type.
 **/
GType
fo_multi_property_set_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoMultiPropertySetClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_multi_property_set_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoMultiPropertySet),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoMultiPropertySet",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_multi_property_set_class_init:
 * @klass: FoMultiPropertySetClass object to initialise
 * 
 * Implements GClassInitFunc for FoMultiPropertySetClass
 **/
void
fo_multi_property_set_class_init (FoMultiPropertySetClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_multi_property_set_finalize;

  object_class->set_property = fo_multi_property_set_set_property;
  object_class->get_property = fo_multi_property_set_get_property;

  fofo_class->validate_content = fo_multi_property_set_validate_content;
  fofo_class->validate2 = fo_multi_property_set_validate;
  fofo_class->update_from_context = fo_multi_property_set_update_from_context;
  fofo_class->debug_dump_properties = fo_multi_property_set_debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_multi_property_set_finalize:
 * @object: FoMultiPropertySet object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoMultiPropertySet
 **/
void
fo_multi_property_set_finalize (GObject *object)
{
  FoMultiPropertySet *fo_multi_property_set;

  fo_multi_property_set = FO_MULTI_PROPERTY_SET (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_multi_property_set_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoMultiPropertySet
 **/
void
fo_multi_property_set_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      fo_multi_property_set_set_id (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_multi_property_set_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoMultiPropertySet
 **/
void
fo_multi_property_set_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_multi_property_set_get_id (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_multi_property_set_new:
 * 
 * Creates a new #FoMultiPropertySet initialized to default value.
 * 
 * Return value: the new #FoMultiPropertySet
 **/
FoFo*
fo_multi_property_set_new (void)
{
  return FO_FO (g_object_new (fo_multi_property_set_get_type (), NULL));
}

/**
 * fo_multi_property_set_validate_content:
 * @fo:    FoMultiPropertySet object to validate
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
fo_multi_property_set_validate_content (FoFo    *fo,
                                        GError **error)
{
  /*GError *tmp_error;*/

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_MULTI_PROPERTY_SET (fo), TRUE);
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
 * fo_multi_property_set_validate:
 * @fo:              FoMultiPropertySet object to validate
 * @current_context: FoContext associated with current object
 * @parent_context:  FoContext associated with parent FO
 * @error:           Information about any error that has occurred
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_multi_property_set_validate (FoFo      *fo,
                                FoContext *current_context,
                                FoContext *parent_context,
                                GError   **error)
{
  FoMultiPropertySet *fo_multi_property_set;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MULTI_PROPERTY_SET (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_multi_property_set = FO_MULTI_PROPERTY_SET (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_multi_property_set_update_from_context:
 * @fo:      The #FoFo object
 * @context: The #FoContext object from which to update the properties of @fo
 * 
 * Sets the properties of @fo to the corresponding property values in @context
 **/
void
fo_multi_property_set_update_from_context (FoFo *fo,
                                           FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MULTI_PROPERTY_SET (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_multi_property_set_set_id (fo,
			  fo_context_get_id (context));
}

/**
 * fo_multi_property_set_debug_dump_properties:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_multi_property_set_debug_dump_properties (FoFo *fo, gint depth)
{
  FoMultiPropertySet *fo_multi_property_set;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MULTI_PROPERTY_SET (fo));

  fo_multi_property_set = FO_MULTI_PROPERTY_SET (fo);

  fo_object_debug_dump (fo_multi_property_set->id, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_multi_property_set_set_id:
 * @fo_fo: The @FoFo object
 * @new_id: The new "id" property value
 * 
 * Sets the #id property of @multi_property_set to @new_id
 **/
void
fo_multi_property_set_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoMultiPropertySet *fo_multi_property_set = (FoMultiPropertySet *) fo_fo;

  g_return_if_fail (fo_multi_property_set != NULL);
  g_return_if_fail (FO_IS_MULTI_PROPERTY_SET (fo_multi_property_set));
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id)
    g_object_ref (G_OBJECT (new_id));
  if (fo_multi_property_set->id)
    g_object_unref (G_OBJECT (fo_multi_property_set->id));
  fo_multi_property_set->id = new_id;
  /*g_object_notify (G_OBJECT (fo_multi_property_set), "id");*/
}

/**
 * fo_multi_property_set_get_id:
 * @fo_fo: The @FoFo object
 *
 * Gets the #id property of @multi_property_set
 *
 * Return value: The "id" property value
**/
FoProperty*
fo_multi_property_set_get_id (FoFo *fo_fo)
{
  FoMultiPropertySet *fo_multi_property_set = (FoMultiPropertySet *) fo_fo;

  g_return_val_if_fail (fo_multi_property_set != NULL, NULL);
  g_return_val_if_fail (FO_IS_MULTI_PROPERTY_SET (fo_multi_property_set), NULL);

  return fo_multi_property_set->id;
}
