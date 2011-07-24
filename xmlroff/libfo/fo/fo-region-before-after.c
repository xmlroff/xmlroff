/* Fo
 * fo-region-before-after.c: Abstract 'before or after region' formatting object
 *
 * Copyright (C) 2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-region-before-after-private.h"
#include "fo-context-util.h"
#include "property/fo-property-precedence.h"

enum {
  PROP_0,
  PROP_PRECEDENCE
};

static void fo_region_before_after_base_class_init  (FoRegionBeforeAfterClass *klass);
static void fo_region_before_after_class_init  (FoRegionBeforeAfterClass *klass);
static void fo_region_before_after_get_property (GObject      *object,
                                           guint         prop_id,
                                           GValue       *value,
                                           GParamSpec   *pspec);
static void fo_region_before_after_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);
static void fo_region_before_after_finalize    (GObject           *object);
static void fo_region_before_after_validate (FoFo      *fo,
                                       FoContext *current_context,
                                       FoContext *parent_context,
                                       GError   **error);
static void fo_region_before_after_update_from_context (FoFo      *fo,
                                                  FoContext *context);
static void fo_region_before_after_debug_dump_properties (FoFo *fo,
                                                    gint  depth);

static gpointer parent_class;

/**
 * fo_region_before_after_get_type:
 * 
 * Register the #FoRegionBeforeAfter object type.
 * 
 * Return value: #GType value of the #FoRegionBeforeAfter object type.
 **/
GType
fo_region_before_after_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoRegionBeforeAfterClass),
	  (GBaseInitFunc) fo_region_before_after_base_class_init,
	  NULL,           /* base_finalize */
	  (GClassInitFunc) fo_region_before_after_class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoRegionBeforeAfter),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_REGION_OUTER,
                                            "FoRegionBeforeAfter",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * fo_region_before_after_base_class_init:
 * @klass: #FoRegionBaseClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoRegionBaseClass.
 **/
void
fo_region_before_after_base_class_init (FoRegionBeforeAfterClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  FoNodeClass *fo_node_class = FO_NODE_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  fofo_class->update_from_context = fo_region_before_after_update_from_context;
  fofo_class->debug_dump_properties = fo_region_before_after_debug_dump_properties;
}

/**
 * fo_region_before_after_class_init:
 * @klass: #FoRegionBeforeAfterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRegionBeforeAfterClass.
 **/
void
fo_region_before_after_class_init (FoRegionBeforeAfterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_region_before_after_finalize;

  object_class->get_property = fo_region_before_after_get_property;
  object_class->set_property = fo_region_before_after_set_property;

  fofo_class->validate2 =
    fo_region_before_after_validate;
  fofo_class->update_from_context = fo_region_before_after_update_from_context;
  fofo_class->debug_dump_properties = fo_region_before_after_debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_PRECEDENCE,
     g_param_spec_object ("precedence",
			  _("Precedence"),
			  _("Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_region_before_after_finalize:
 * @object: #FoRegionBeforeAfter object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoRegionBeforeAfter.
 **/
void
fo_region_before_after_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_region_before_after_set_precedence (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_region_before_after_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoRegionBeforeAfter.
 **/
void
fo_region_before_after_get_property (GObject    *object,
				     guint       prop_id,
				     GValue     *value,
				     GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_region_before_after_get_precedence (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_before_after_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoRegionBeforeAfter.
 **/
void
fo_region_before_after_set_property (GObject      *object,
				     guint         prop_id,
				     const GValue *value,
				     GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_PRECEDENCE:
      fo_region_before_after_set_precedence (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_before_after_new:
 * 
 * Creates a new #FoRegionBeforeAfter initialized to default value.
 * 
 * Return value: the new #FoRegionBeforeAfter.
 **/
FoFo*
fo_region_before_after_new (void)
{
  return FO_FO (g_object_new (fo_region_before_after_get_type (),
                              NULL));
}

/**
 * fo_region_before_after_validate:
 * @fo:              #FoRegionBeforeAfter object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_region_before_after_validate (FoFo      *fo,
				 FoContext *current_context,
				 FoContext *parent_context,
				 GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE_AFTER (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);
}

/**
 * fo_region_before_after_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_region_before_after_update_from_context (FoFo      *fo,
					    FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE_AFTER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);

  fo_region_before_after_set_precedence (fo,
			      fo_context_get_precedence (context));
}

/**
 * fo_region_before_after_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_region_before_after_debug_dump_properties (FoFo *fo,
					      gint  depth)
{
  FoRegionBeforeAfter *fo_region_before_after;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE_AFTER (fo));

  fo_region_before_after = FO_REGION_BEFORE_AFTER (fo);

  fo_object_debug_dump (fo_region_before_after->precedence, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_region_before_after_get_precedence:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "precedence" property of @fo_fo.
 *
 * Return value: The "precedence" property value.
**/
FoProperty *
fo_region_before_after_get_precedence (FoFo *fo_fo)
{
  FoRegionBeforeAfter *fo_region_before_after = (FoRegionBeforeAfter *) fo_fo;

  g_return_val_if_fail (fo_region_before_after != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE_AFTER (fo_region_before_after), NULL);

  return fo_region_before_after->precedence;
}

/**
 * fo_region_before_after_set_precedence:
 * @fo_fo: The #FoFo object.
 * @new_precedence: The new "precedence" property value.
 * 
 * Sets the "precedence" property of @fo_fo to @new_precedence.
 **/
void
fo_region_before_after_set_precedence (FoFo *fo_fo,
				       FoProperty *new_precedence)
{
  FoRegionBeforeAfter *fo_region_before_after = (FoRegionBeforeAfter *) fo_fo;

  g_return_if_fail (fo_region_before_after != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE_AFTER (fo_region_before_after));
  g_return_if_fail ((new_precedence == NULL) ||
		    FO_IS_PROPERTY_PRECEDENCE (new_precedence));

  if (new_precedence != NULL)
    {
      g_object_ref (new_precedence);
    }
  if (fo_region_before_after->precedence != NULL)
    {
      g_object_unref (fo_region_before_after->precedence);
    }
  fo_region_before_after->precedence = new_precedence;
  /*g_object_notify (G_OBJECT (fo_region_before_after), "precedence");*/
}
