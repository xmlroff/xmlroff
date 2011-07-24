/* Fo
 * fo-region-before-after.c: Abstract 'outer region' formatting object
 *
 * Copyright (C) 2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-region-before-after-private.h"
#include "fo-context-util.h"
#include "property/fo-property-extent.h"

enum {
  PROP_0,
  PROP_EXTENT
};

static void fo_region_outer_base_class_init  (FoRegionOuterClass *klass);
static void fo_region_outer_class_init  (FoRegionOuterClass *klass);
static void fo_region_outer_get_property (GObject      *object,
                                           guint         prop_id,
                                           GValue       *value,
                                           GParamSpec   *pspec);
static void fo_region_outer_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);
static void fo_region_outer_finalize    (GObject           *object);
static void fo_region_outer_validate (FoFo      *fo,
                                       FoContext *current_context,
                                       FoContext *parent_context,
                                       GError   **error);
static void fo_region_outer_update_from_context (FoFo      *fo,
                                                  FoContext *context);
static void fo_region_outer_debug_dump_properties (FoFo *fo,
                                                    gint  depth);

static gpointer parent_class;

/**
 * fo_region_outer_get_type:
 * 
 * Register the #FoRegionOuter object type.
 * 
 * Return value: #GType value of the #FoRegionOuter object type.
 **/
GType
fo_region_outer_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoRegionOuterClass),
	  (GBaseInitFunc) fo_region_outer_base_class_init,
	  NULL,           /* base_finalize */
	  (GClassInitFunc) fo_region_outer_class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoRegionOuter),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_REGION,
                                            "FoRegionOuter",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * fo_region_outer_base_class_init:
 * @klass: #FoRegionBaseClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoRegionBaseClass.
 **/
void
fo_region_outer_base_class_init (FoRegionOuterClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  FoNodeClass *fo_node_class = FO_NODE_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  fofo_class->update_from_context = fo_region_outer_update_from_context;
  fofo_class->debug_dump_properties = fo_region_outer_debug_dump_properties;
}

/**
 * fo_region_outer_class_init:
 * @klass: #FoRegionOuterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRegionOuterClass.
 **/
void
fo_region_outer_class_init (FoRegionOuterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_region_outer_finalize;

  object_class->get_property = fo_region_outer_get_property;
  object_class->set_property = fo_region_outer_set_property;

  fofo_class->validate2 =
    fo_region_outer_validate;
  fofo_class->update_from_context = fo_region_outer_update_from_context;
  fofo_class->debug_dump_properties = fo_region_outer_debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_EXTENT,
     g_param_spec_object ("extent",
			  _("Extent"),
			  _("Extent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_region_outer_finalize:
 * @object: #FoRegionOuter object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoRegionOuter.
 **/
void
fo_region_outer_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_region_outer_set_extent (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_region_outer_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoRegionOuter.
 **/
void
fo_region_outer_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_EXTENT:
      g_value_set_object (value, G_OBJECT (fo_region_outer_get_extent (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_outer_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoRegionOuter.
 **/
void
fo_region_outer_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_EXTENT:
      fo_region_outer_set_extent (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_outer_new:
 * 
 * Creates a new #FoRegionOuter initialized to default value.
 * 
 * Return value: the new #FoRegionOuter.
 **/
FoFo*
fo_region_outer_new (void)
{
  return FO_FO (g_object_new (fo_region_outer_get_type (),
                              NULL));
}

/**
 * fo_region_outer_validate:
 * @fo:              #FoRegionOuter object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_region_outer_validate (FoFo      *fo,
			  FoContext *current_context,
			  FoContext *parent_context,
			  GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_OUTER (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);
}

/**
 * fo_region_outer_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_region_outer_update_from_context (FoFo      *fo,
				     FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_OUTER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);

  fo_region_outer_set_extent (fo,
			      fo_context_get_extent (context));
}

/**
 * fo_region_outer_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_region_outer_debug_dump_properties (FoFo *fo,
				       gint  depth)
{
  FoRegionOuter *fo_region_outer;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_OUTER (fo));

  fo_region_outer = FO_REGION_OUTER (fo);

  fo_object_debug_dump (fo_region_outer->extent, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_region_outer_get_extent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "extent" property of @fo_fo.
 *
 * Return value: The "extent" property value.
**/
FoProperty *
fo_region_outer_get_extent (FoFo *fo_fo)
{
  FoRegionOuter *fo_region_outer = (FoRegionOuter *) fo_fo;

  g_return_val_if_fail (fo_region_outer != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_OUTER (fo_region_outer), NULL);

  return fo_region_outer->extent;
}

/**
 * fo_region_outer_set_extent:
 * @fo_fo: The #FoFo object.
 * @new_extent: The new "extent" property value.
 * 
 * Sets the "extent" property of @fo_fo to @new_extent.
 **/
void
fo_region_outer_set_extent (FoFo *fo_fo,
			    FoProperty *new_extent)
{
  FoRegionOuter *fo_region_outer = (FoRegionOuter *) fo_fo;

  g_return_if_fail (fo_region_outer != NULL);
  g_return_if_fail (FO_IS_REGION_OUTER (fo_region_outer));
  g_return_if_fail ((new_extent == NULL) ||
		    FO_IS_PROPERTY_EXTENT (new_extent));

  if (new_extent != NULL)
    {
      g_object_ref (new_extent);
    }
  if (fo_region_outer->extent != NULL)
    {
      g_object_unref (fo_region_outer->extent);
    }
  fo_region_outer->extent = new_extent;
  /*g_object_notify (G_OBJECT (fo_region_outer), "extent");*/
}
