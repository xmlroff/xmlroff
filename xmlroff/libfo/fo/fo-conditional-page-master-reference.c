/* Fo
 * fo-conditional-page-master-reference.c: 'conditional-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-conditional-page-master-reference-private.h"
#include "property/fo-property-blank-or-not-blank.h"
#include "property/fo-property-odd-or-even.h"
#include "property/fo-property-page-position.h"

enum {
  PROP_0,
  PROP_BLANK_OR_NOT_BLANK,
  PROP_ODD_OR_EVEN,
  PROP_PAGE_POSITION
};

static void _class_init  (FoConditionalPageMasterReferenceClass *klass);
static void fo_conditional_page_master_reference_get_property (GObject      *object,
                                                               guint         prop_id,
                                                               GValue       *value,
                                                               GParamSpec   *pspec);
static void fo_conditional_page_master_reference_set_property (GObject      *object,
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
 * fo_conditional_page_master_reference_get_type:
 * 
 * Register the #FoConditionalPageMasterReference object type.
 * 
 * Return value: #GType value of the #FoConditionalPageMasterReference object type.
 **/
GType
fo_conditional_page_master_reference_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoConditionalPageMasterReferenceClass),
	  NULL,           /* base_init */
	  NULL,           /* base_finalize */
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoConditionalPageMasterReference),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_PAGE_MASTER_REFERENCE,
                                            "FoConditionalPageMasterReference",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * _class_init:
 * @klass: #FoConditionalPageMasterReferenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoConditionalPageMasterReferenceClass.
 **/
void
_class_init (FoConditionalPageMasterReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->dispose = _dispose;

  object_class->get_property = fo_conditional_page_master_reference_get_property;
  object_class->set_property = fo_conditional_page_master_reference_set_property;

  fofo_class->validate_content =
    fo_fo_validate_content_empty;
  fofo_class->validate2 =
    _validate;
  fofo_class->update_from_context = _update_from_context;
  fofo_class->debug_dump_properties = _debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_BLANK_OR_NOT_BLANK,
     g_param_spec_object ("blank-or-not-blank",
			  _("Blank Or Not Blank"),
			  _("Blank Or Not Blank property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ODD_OR_EVEN,
     g_param_spec_object ("odd-or-even",
			  _("Odd Or Even"),
			  _("Odd Or Even property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PAGE_POSITION,
     g_param_spec_object ("page-position",
			  _("Page Position"),
			  _("Page Position property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * _dispose:
 * @object: #FoConditionalPageMasterReference object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoConditionalPageMasterReference.
 **/
void
_dispose (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_conditional_page_master_reference_set_blank_or_not_blank (fo, NULL);
  fo_conditional_page_master_reference_set_odd_or_even (fo, NULL);
  fo_conditional_page_master_reference_set_page_position (fo, NULL);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * fo_conditional_page_master_reference_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoConditionalPageMasterReference.
 **/
void
fo_conditional_page_master_reference_get_property (GObject    *object,
                                                   guint       prop_id,
                                                   GValue     *value,
                                                   GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BLANK_OR_NOT_BLANK:
      g_value_set_object (value, G_OBJECT (fo_conditional_page_master_reference_get_blank_or_not_blank (fo_fo)));
      break;
    case PROP_ODD_OR_EVEN:
      g_value_set_object (value, G_OBJECT (fo_conditional_page_master_reference_get_odd_or_even (fo_fo)));
      break;
    case PROP_PAGE_POSITION:
      g_value_set_object (value, G_OBJECT (fo_conditional_page_master_reference_get_page_position (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_conditional_page_master_reference_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoConditionalPageMasterReference.
 **/
void
fo_conditional_page_master_reference_set_property (GObject      *object,
                                                   guint         prop_id,
                                                   const GValue *value,
                                                   GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BLANK_OR_NOT_BLANK:
      fo_conditional_page_master_reference_set_blank_or_not_blank (fo_fo, g_value_get_object (value));
      break;
    case PROP_ODD_OR_EVEN:
      fo_conditional_page_master_reference_set_odd_or_even (fo_fo, g_value_get_object (value));
      break;
    case PROP_PAGE_POSITION:
      fo_conditional_page_master_reference_set_page_position (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_conditional_page_master_reference_new:
 * 
 * Creates a new #FoConditionalPageMasterReference initialized to default value.
 * 
 * Return value: the new #FoConditionalPageMasterReference.
 **/
FoFo *
fo_conditional_page_master_reference_new (void)
{
  return FO_FO (g_object_new (fo_conditional_page_master_reference_get_type (),
                              NULL));
}

/**
 * _validate:
 * @fo:              #FoConditionalPageMasterReference object to validate.
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
  FoConditionalPageMasterReference *fo_conditional_page_master_reference;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_conditional_page_master_reference = FO_CONDITIONAL_PAGE_MASTER_REFERENCE (fo);

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
  g_return_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_conditional_page_master_reference_set_blank_or_not_blank (fo,
			  fo_context_get_blank_or_not_blank (context));
  fo_conditional_page_master_reference_set_odd_or_even (fo,
			  fo_context_get_odd_or_even (context));
  fo_conditional_page_master_reference_set_page_position (fo,
			  fo_context_get_page_position (context));

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
  FoConditionalPageMasterReference *fo_conditional_page_master_reference;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo));

  fo_conditional_page_master_reference = FO_CONDITIONAL_PAGE_MASTER_REFERENCE (fo);

  fo_object_debug_dump (fo_conditional_page_master_reference->blank_or_not_blank, depth);
  fo_object_debug_dump (fo_conditional_page_master_reference->odd_or_even, depth);
  fo_object_debug_dump (fo_conditional_page_master_reference->page_position, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/*
 * The remainder of this file is completely auto-generated.
 */

/**
 * fo_conditional_page_master_reference_get_blank_or_not_blank:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "blank-or-not-blank" property of @fo_fo.
 *
 * Return value: The "blank-or-not-blank" property value.
**/
FoProperty *
fo_conditional_page_master_reference_get_blank_or_not_blank (FoFo *fo_fo)
{
  FoConditionalPageMasterReference *fo_conditional_page_master_reference = (FoConditionalPageMasterReference *) fo_fo;

  g_return_val_if_fail (fo_conditional_page_master_reference != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo_conditional_page_master_reference), NULL);

  return fo_conditional_page_master_reference->blank_or_not_blank;
}

/**
 * fo_conditional_page_master_reference_set_blank_or_not_blank:
 * @fo_fo: The #FoFo object.
 * @new_blank_or_not_blank: The new "blank-or-not-blank" property value.
 * 
 * Sets the "blank-or-not-blank" property of @fo_fo to @new_blank_or_not_blank.
 **/
void
fo_conditional_page_master_reference_set_blank_or_not_blank (FoFo *fo_fo,
		         FoProperty *new_blank_or_not_blank)
{
  FoConditionalPageMasterReference *fo_conditional_page_master_reference = (FoConditionalPageMasterReference *) fo_fo;

  g_return_if_fail (fo_conditional_page_master_reference != NULL);
  g_return_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo_conditional_page_master_reference));
  g_return_if_fail ((new_blank_or_not_blank == NULL) ||
		    FO_IS_PROPERTY_BLANK_OR_NOT_BLANK (new_blank_or_not_blank));

  if (new_blank_or_not_blank != NULL)
    {
      g_object_ref (new_blank_or_not_blank);
    }
  if (fo_conditional_page_master_reference->blank_or_not_blank != NULL)
    {
      g_object_unref (fo_conditional_page_master_reference->blank_or_not_blank);
    }
  fo_conditional_page_master_reference->blank_or_not_blank = new_blank_or_not_blank;
  /*g_object_notify (G_OBJECT (fo_conditional_page_master_reference), "blank-or-not-blank");*/
}

/**
 * fo_conditional_page_master_reference_get_odd_or_even:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "odd-or-even" property of @fo_fo.
 *
 * Return value: The "odd-or-even" property value.
**/
FoProperty *
fo_conditional_page_master_reference_get_odd_or_even (FoFo *fo_fo)
{
  FoConditionalPageMasterReference *fo_conditional_page_master_reference = (FoConditionalPageMasterReference *) fo_fo;

  g_return_val_if_fail (fo_conditional_page_master_reference != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo_conditional_page_master_reference), NULL);

  return fo_conditional_page_master_reference->odd_or_even;
}

/**
 * fo_conditional_page_master_reference_set_odd_or_even:
 * @fo_fo: The #FoFo object.
 * @new_odd_or_even: The new "odd-or-even" property value.
 * 
 * Sets the "odd-or-even" property of @fo_fo to @new_odd_or_even.
 **/
void
fo_conditional_page_master_reference_set_odd_or_even (FoFo *fo_fo,
		         FoProperty *new_odd_or_even)
{
  FoConditionalPageMasterReference *fo_conditional_page_master_reference = (FoConditionalPageMasterReference *) fo_fo;

  g_return_if_fail (fo_conditional_page_master_reference != NULL);
  g_return_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo_conditional_page_master_reference));
  g_return_if_fail ((new_odd_or_even == NULL) ||
		    FO_IS_PROPERTY_ODD_OR_EVEN (new_odd_or_even));

  if (new_odd_or_even != NULL)
    {
      g_object_ref (new_odd_or_even);
    }
  if (fo_conditional_page_master_reference->odd_or_even != NULL)
    {
      g_object_unref (fo_conditional_page_master_reference->odd_or_even);
    }
  fo_conditional_page_master_reference->odd_or_even = new_odd_or_even;
  /*g_object_notify (G_OBJECT (fo_conditional_page_master_reference), "odd-or-even");*/
}

/**
 * fo_conditional_page_master_reference_get_page_position:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "page-position" property of @fo_fo.
 *
 * Return value: The "page-position" property value.
**/
FoProperty *
fo_conditional_page_master_reference_get_page_position (FoFo *fo_fo)
{
  FoConditionalPageMasterReference *fo_conditional_page_master_reference = (FoConditionalPageMasterReference *) fo_fo;

  g_return_val_if_fail (fo_conditional_page_master_reference != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo_conditional_page_master_reference), NULL);

  return fo_conditional_page_master_reference->page_position;
}

/**
 * fo_conditional_page_master_reference_set_page_position:
 * @fo_fo: The #FoFo object.
 * @new_page_position: The new "page-position" property value.
 * 
 * Sets the "page-position" property of @fo_fo to @new_page_position.
 **/
void
fo_conditional_page_master_reference_set_page_position (FoFo *fo_fo,
		         FoProperty *new_page_position)
{
  FoConditionalPageMasterReference *fo_conditional_page_master_reference = (FoConditionalPageMasterReference *) fo_fo;

  g_return_if_fail (fo_conditional_page_master_reference != NULL);
  g_return_if_fail (FO_IS_CONDITIONAL_PAGE_MASTER_REFERENCE (fo_conditional_page_master_reference));
  g_return_if_fail ((new_page_position == NULL) ||
		    FO_IS_PROPERTY_PAGE_POSITION (new_page_position));

  if (new_page_position != NULL)
    {
      g_object_ref (new_page_position);
    }
  if (fo_conditional_page_master_reference->page_position != NULL)
    {
      g_object_unref (fo_conditional_page_master_reference->page_position);
    }
  fo_conditional_page_master_reference->page_position = new_page_position;
  /*g_object_notify (G_OBJECT (fo_conditional_page_master_reference), "page-position");*/
}
