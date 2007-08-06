/* Fo
 * fo-property-border-end-width.c: 'border-end-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-border-end-width.h"
#include "property/fo-property-util.h"

/* border-end-width */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-width> | <length-conditional> | inherit */
/* Initial value: medium */

struct _FoPropertyBorderEndWidth
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderEndWidthClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_end_width_init         (FoPropertyBorderEndWidth      *property_border_end_width);
static void fo_property_border_end_width_class_init   (FoPropertyBorderEndWidthClass *klass);
static void fo_property_border_end_width_finalize     (GObject       *object);

static const gchar class_name[] = "FoPropertyBorderEndWidth";
static gpointer parent_class;

/**
 * fo_property_border_end_width_get_type:
 * 
 * Register the #FoPropertyBorderEndWidth type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderEndWidth.
 **/
GType
fo_property_border_end_width_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderEndWidthClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_end_width_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderEndWidth),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_end_width_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_end_width_init:
 * @border_end_width: #FoPropertyBorderEndWidth object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderEndWidth.
 **/
void
fo_property_border_end_width_init (FoPropertyBorderEndWidth *border_end_width)
{
  FO_PROPERTY (border_end_width)->value =
    g_object_ref (fo_property_util_get_width_initial ());
}

/**
 * fo_property_border_end_width_class_init:
 * @klass: #FoPropertyBorderEndWidthClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderEndWidthClass.
 **/
void
fo_property_border_end_width_class_init (FoPropertyBorderEndWidthClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_end_width_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_width_enum;
  property_class->validate =
    fo_property_util_validate_width;
  property_class->get_initial =
    fo_property_border_end_width_get_initial;
}

/**
 * fo_property_border_end_width_finalize:
 * @object: #FoPropertyBorderEndWidth object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderEndWidth.
 **/
void
fo_property_border_end_width_finalize (GObject *object)
{
  FoPropertyBorderEndWidth *border_end_width;

  border_end_width = FO_PROPERTY_BORDER_END_WIDTH (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_end_width_new:
 * 
 * Creates a new #FoPropertyBorderEndWidth initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderEndWidth.
 **/
FoProperty*
fo_property_border_end_width_new (void)
{
  FoProperty* border_end_width;

  border_end_width =
    FO_PROPERTY (g_object_new (fo_property_border_end_width_get_type (),
                               NULL));

  return border_end_width;
}

/**
 * fo_property_border_end_width_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_end_width_get_initial (void)
{
  static FoProperty *border_end_width = NULL;

  if (border_end_width == NULL)
    {
      border_end_width =
	fo_property_border_end_width_new ();
    }

  return border_end_width;
}
