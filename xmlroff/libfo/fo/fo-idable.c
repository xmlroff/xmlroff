/* Fo
 * fo-idable.c: Formatting object that is parent of possible fo:marker
 *
 * Copyright (C) 2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-idable-private.h"
#include "property/fo-property-id.h"

enum {
  PROP_0,
  PROP_ID
};

static void     fo_idable_class_init (FoIdableClass *klass);
static void     fo_idable_finalize   (GObject       *object);
static void fo_idable_get_property (GObject      *object,
				    guint         prop_id,
				    GValue       *value,
				    GParamSpec   *pspec);
static void fo_idable_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec);
static void fo_idable_validate (FoFo      *fo,
				FoContext *current_context,
				FoContext *parent_context,
				GError   **error);
static void fo_idable_update_from_context (FoFo      *fo,
					   FoContext *context);
static void fo_idable_debug_dump_properties (FoFo *fo,
                                            gint  depth);
FoProperty * fo_idable_get_id (FoFo *fo_fo);
void         fo_idable_set_id (FoFo *fo_fo,
			       FoProperty *new_id);

static gpointer parent_class;

GType
fo_idable_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoIdableClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_idable_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoIdable),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoIdable",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * fo_idable_class_init:
 * @klass: #FoIdableClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoIdable.
 **/
void
fo_idable_class_init (FoIdableClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->set_property = fo_idable_set_property;
  object_class->get_property = fo_idable_get_property;

  object_class->finalize = fo_idable_finalize;

  fo_fo_class->validate2 = fo_idable_validate;

  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

static void
fo_idable_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_idable_set_id (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_idable_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoIdable.
 **/
void
fo_idable_get_property (GObject    *object,
                       guint       prop_id,
                       GValue     *value,
                       GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_idable_get_id (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_idable_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoIdable.
 **/
void
fo_idable_set_property (GObject      *object,
                       guint         prop_id,
                       const GValue *value,
                       GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      fo_idable_set_id (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_idable_new:
 * 
 * Creates a new #FoIdable initialized to default value.
 * 
 * Return value: the new #FoIdable.
 **/
FoFo*
fo_idable_new (void)
{
  return FO_FO (g_object_new (fo_idable_get_type (),
			      NULL));
}

/**
 * fo_idable_validate:
 * @fo:              #FoIdable object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_idable_validate (FoFo      *fo,
		    FoContext *current_context,
		    FoContext *parent_context,
		    GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_IDABLE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_fo_register_id (fo,
		     fo_property_get_value (FO_IDABLE (fo)->id));
}

/**
 * fo_idable_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_idable_update_from_context (FoFo      *fo,
                              FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_IDABLE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_idable_set_id (fo,
			  fo_context_get_id (context));
}

/**
 * fo_idable_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_idable_debug_dump_properties (FoFo *fo,
                                gint  depth)
{
  FoIdable *fo_idable;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_IDABLE (fo));

  fo_idable = FO_IDABLE (fo);

  fo_object_debug_dump (fo_idable->id, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_idable_get_id:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "id" property of @fo_fo.
 *
 * Return value: The "id" property value.
**/
FoProperty *
fo_idable_get_id (FoFo *fo_fo)
{
  FoIdable *fo_idable = (FoIdable *) fo_fo;

  g_return_val_if_fail (fo_idable != NULL, NULL);
  g_return_val_if_fail (FO_IS_IDABLE (fo_idable), NULL);

  return fo_idable->id;
}

/**
 * fo_idable_set_id:
 * @fo_fo: The #FoFo object.
 * @new_id: The new "id" property value.
 * 
 * Sets the "id" property of @fo_fo to @new_id.
 **/
void
fo_idable_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoIdable *fo_idable = (FoIdable *) fo_fo;

  g_return_if_fail (fo_idable != NULL);
  g_return_if_fail (FO_IS_IDABLE (fo_idable));
  g_return_if_fail ((new_id == NULL) ||
		    FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_idable->id != NULL)
    {
      g_object_unref (fo_idable->id);
    }
  fo_idable->id = new_id;
  /*g_object_notify (G_OBJECT (fo_idable), "id");*/
}
