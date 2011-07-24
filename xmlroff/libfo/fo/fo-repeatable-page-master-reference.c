/* Fo
 * fo-repeatable-page-master-reference.c: 'repeatable-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-repeatable-page-master-reference-private.h"
#include "property/fo-property-master-reference.h"
#include "property/fo-property-maximum-repeats.h"

enum {
  PROP_0,
  PROP_MAXIMUM_REPEATS
};

static void _class_init  (FoRepeatablePageMasterReferenceClass *klass);
static void _get_property (GObject      *object,
                                                              guint         prop_id,
                                                              GValue       *value,
                                                              GParamSpec   *pspec);
static void _set_property (GObject      *object,
                                                              guint         prop_id,
                                                              const GValue *value,
                                                              GParamSpec   *pspec);
static void _dispose    (GObject           *object);
static void _validate (FoFo      *fo,
                                                          FoContext *current_context,
                                                          FoContext *parent_context,
                                                          GError   **error);
static void _update_from_context (FoFo      *fo,
                                                                     FoContext *context);
static void _debug_dump_properties (FoFo *fo,
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
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoRepeatablePageMasterReference),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_PAGE_MASTER_REFERENCE,
                                            "FoRepeatablePageMasterReference",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * _class_init:
 * @klass: #FoRepeatablePageMasterReferenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRepeatablePageMasterReferenceClass.
 **/
void
_class_init (FoRepeatablePageMasterReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->dispose = _dispose;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  fofo_class->validate2 = _validate;
  fofo_class->update_from_context = _update_from_context;
  fofo_class->debug_dump_properties = _debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_MAXIMUM_REPEATS,
     g_param_spec_object ("maximum-repeats",
			  _("Maximum Repeats"),
			  _("Maximum Repeats property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * _dispose:
 * @object: #FoRepeatablePageMasterReference object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoRepeatablePageMasterReference.
 **/
void
_dispose (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_repeatable_page_master_reference_set_maximum_repeats (fo, NULL);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * _get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoRepeatablePageMasterReference.
 **/
void
_get_property (GObject    *object,
	       guint       prop_id,
	       GValue     *value,
	       GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MAXIMUM_REPEATS:
      g_value_set_object (value, G_OBJECT (fo_repeatable_page_master_reference_get_maximum_repeats (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * _set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoRepeatablePageMasterReference.
 **/
void
_set_property (GObject      *object,
	       guint         prop_id,
	       const GValue *value,
	       GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MAXIMUM_REPEATS:
      fo_repeatable_page_master_reference_set_maximum_repeats (fo_fo, g_value_get_object (value));
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
 * _validate:
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
_validate (FoFo      *fo,
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
 * _update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
_update_from_context (FoFo      *fo,
		      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_repeatable_page_master_reference_set_maximum_repeats (fo,
			  fo_context_get_maximum_repeats (context));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);
}

/**
 * _debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
_debug_dump_properties (FoFo *fo,
			gint  depth)
{
  FoRepeatablePageMasterReference *fo_repeatable_page_master_reference;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo));

  fo_repeatable_page_master_reference = FO_REPEATABLE_PAGE_MASTER_REFERENCE (fo);

  fo_object_debug_dump (fo_repeatable_page_master_reference->maximum_repeats, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/*
 * The remainder of this file is completely auto-generated.
 */

/**
 * fo_repeatable_page_master_reference_get_maximum_repeats:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "maximum-repeats" property of @fo_fo.
 *
 * Return value: The "maximum-repeats" property value.
**/
FoProperty *
fo_repeatable_page_master_reference_get_maximum_repeats (FoFo *fo_fo)
{
  FoRepeatablePageMasterReference *fo_repeatable_page_master_reference = (FoRepeatablePageMasterReference *) fo_fo;

  g_return_val_if_fail (fo_repeatable_page_master_reference != NULL, NULL);
  g_return_val_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo_repeatable_page_master_reference), NULL);

  return fo_repeatable_page_master_reference->maximum_repeats;
}

/**
 * fo_repeatable_page_master_reference_set_maximum_repeats:
 * @fo_fo: The #FoFo object.
 * @new_maximum_repeats: The new "maximum-repeats" property value.
 * 
 * Sets the "maximum-repeats" property of @fo_fo to @new_maximum_repeats.
 **/
void
fo_repeatable_page_master_reference_set_maximum_repeats (FoFo *fo_fo,
		         FoProperty *new_maximum_repeats)
{
  FoRepeatablePageMasterReference *fo_repeatable_page_master_reference = (FoRepeatablePageMasterReference *) fo_fo;

  g_return_if_fail (fo_repeatable_page_master_reference != NULL);
  g_return_if_fail (FO_IS_REPEATABLE_PAGE_MASTER_REFERENCE (fo_repeatable_page_master_reference));
  g_return_if_fail ((new_maximum_repeats == NULL) ||
		    FO_IS_PROPERTY_MAXIMUM_REPEATS (new_maximum_repeats));

  if (new_maximum_repeats != NULL)
    {
      g_object_ref (new_maximum_repeats);
    }
  if (fo_repeatable_page_master_reference->maximum_repeats != NULL)
    {
      g_object_unref (fo_repeatable_page_master_reference->maximum_repeats);
    }
  fo_repeatable_page_master_reference->maximum_repeats = new_maximum_repeats;
  /*g_object_notify (G_OBJECT (fo_repeatable_page_master_reference), "maximum-repeats");*/
}
