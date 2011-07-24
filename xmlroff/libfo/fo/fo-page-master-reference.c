/* Fo
 * fo-page-master-reference.c: '-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-page-master-reference-private.h"
#include "property/fo-property-blank-or-not-blank.h"
#include "property/fo-property-master-reference.h"
#include "property/fo-property-odd-or-even.h"
#include "property/fo-property-page-position.h"

enum {
  PROP_0,
  PROP_MASTER_REFERENCE
};

static void _base_class_init  (FoPageMasterReferenceClass *klass);
static void _class_init       (FoPageMasterReferenceClass *klass);
static void fo_page_master_reference_get_property (GObject      *object,
						   guint         prop_id,
						   GValue       *value,
						   GParamSpec   *pspec);
static void fo_page_master_reference_set_property (GObject      *object,
						   guint         prop_id,
						   const GValue *value,
						   GParamSpec   *pspec);
static void _dispose               (GObject   *object);
static void _validate              (FoFo      *fo,
				    FoContext *current_context,
				    FoContext *parent_context,
				    GError   **error);
static void _update_from_context   (FoFo      *fo,
				    FoContext *context);
static void _debug_dump_properties (FoFo      *fo,
				    gint       depth);

static gpointer parent_class;

/**
 * fo_page_master_reference_get_type:
 * 
 * Register the #FoPageMasterReference object type.
 * 
 * Return value: #GType value of the #FoPageMasterReference object type.
 **/
GType
fo_page_master_reference_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoPageMasterReferenceClass),
	  (GBaseInitFunc)  _base_class_init,
	  NULL,            /* base_finalize */
	  (GClassInitFunc) _class_init,
	  NULL,            /* class_finalize */
	  NULL,            /* class_data */
	  sizeof (FoPageMasterReference),
	  0,               /* n_preallocs */
	  NULL,		   /* instance_init */
	  NULL		   /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoPageMasterReference",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * _base_class_init:
 * @klass: #FoPageMasterReferenceClass base class
 *         object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPageMasterReferenceClass.
 **/
static void
_base_class_init (FoPageMasterReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->dispose = _dispose;

  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  fo_fo_class->debug_dump_properties = _debug_dump_properties;
  fo_fo_class->update_from_context = _update_from_context;
  fo_fo_class->validate_content =
    fo_fo_validate_content_empty;
}

/**
 * _class_init:
 * @klass: #FoPageMasterReferenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPageMasterReferenceClass.
 **/
void
_class_init (FoPageMasterReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->get_property = fo_page_master_reference_get_property;
  object_class->set_property = fo_page_master_reference_set_property;

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
 * _dispose:
 * @object: #FoPageMasterReference object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoPageMasterReference.
 **/
void
_dispose (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_page_master_reference_set_master_reference (fo, NULL);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * fo_page_master_reference_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoPageMasterReference.
 **/
void
fo_page_master_reference_get_property (GObject    *object,
				       guint       prop_id,
				       GValue     *value,
				       GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MASTER_REFERENCE:
      g_value_set_object (value, G_OBJECT (fo_page_master_reference_get_master_reference (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_page_master_reference_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoPageMasterReference.
 **/
void
fo_page_master_reference_set_property (GObject      *object,
				       guint         prop_id,
				       const GValue *value,
				       GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MASTER_REFERENCE:
      fo_page_master_reference_set_master_reference (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_page_master_reference_new:
 * 
 * Creates a new #FoPageMasterReference initialized to default value.
 * 
 * Return value: the new #FoPageMasterReference.
 **/
FoFo *
fo_page_master_reference_new (void)
{
  return FO_FO (g_object_new (fo_page_master_reference_get_type (),
                              NULL));
}

/**
 * _validate:
 * @fo:              #FoPageMasterReference object to validate.
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
  FoPageMasterReference *fo_page_master_reference;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_MASTER_REFERENCE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_page_master_reference = FO_PAGE_MASTER_REFERENCE (fo);

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
  g_return_if_fail (FO_IS_PAGE_MASTER_REFERENCE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_page_master_reference_set_master_reference (fo,
			  fo_context_get_master_reference (context));
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
  FoPageMasterReference *fo_page_master_reference;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_MASTER_REFERENCE (fo));

  fo_page_master_reference = FO_PAGE_MASTER_REFERENCE (fo);

  fo_object_debug_dump (fo_page_master_reference->master_reference, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_page_master_reference_get_master_reference:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "master-reference" property of @fo_fo.
 *
 * Return value: The "master-reference" property value.
**/
FoProperty *
fo_page_master_reference_get_master_reference (FoFo *fo_fo)
{
  FoPageMasterReference *fo_page_master_reference = (FoPageMasterReference *) fo_fo;

  g_return_val_if_fail (fo_page_master_reference != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_MASTER_REFERENCE (fo_page_master_reference), NULL);

  return fo_page_master_reference->master_reference;
}

/**
 * fo_page_master_reference_set_master_reference:
 * @fo_fo: The #FoFo object.
 * @new_master_reference: The new "master-reference" property value.
 * 
 * Sets the "master-reference" property of @fo_fo to @new_master_reference.
 **/
void
fo_page_master_reference_set_master_reference (FoFo *fo_fo,
		         FoProperty *new_master_reference)
{
  FoPageMasterReference *fo_page_master_reference = (FoPageMasterReference *) fo_fo;

  g_return_if_fail (fo_page_master_reference != NULL);
  g_return_if_fail (FO_IS_PAGE_MASTER_REFERENCE (fo_page_master_reference));
  g_return_if_fail ((new_master_reference == NULL) ||
		    FO_IS_PROPERTY_MASTER_REFERENCE (new_master_reference));

  if (new_master_reference != NULL)
    {
      g_object_ref (new_master_reference);
    }
  if (fo_page_master_reference->master_reference != NULL)
    {
      g_object_unref (fo_page_master_reference->master_reference);
    }
  fo_page_master_reference->master_reference = new_master_reference;
  /*g_object_notify (G_OBJECT (fo_page_master_reference), "master-reference");*/
}
