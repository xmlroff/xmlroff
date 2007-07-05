/* Fo
 * fo-property-border-bottom-color.c: 'border-bottom-color' property
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
#include "property/fo-property-border-bottom-color.h"
#include "property/fo-property-util.h"

/* border-bottom-color */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <color> | inherit */
/* Initial value: the value of the 'color' property */

struct _FoPropertyBorderBottomColor
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderBottomColorClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_bottom_color_init         (FoPropertyBorderBottomColor      *property_border_bottom_color);
static void fo_property_border_bottom_color_class_init   (FoPropertyBorderBottomColorClass *klass);
static void fo_property_border_bottom_color_finalize     (GObject       *object);

static const gchar class_name[] = "border-bottom-color";
static gpointer parent_class;

/**
 * fo_property_border_bottom_color_get_type:
 * 
 * Register the #FoPropertyBorderBottomColor type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderBottomColor.
 **/
GType
fo_property_border_bottom_color_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderBottomColorClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_bottom_color_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderBottomColor),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_bottom_color_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_bottom_color_init:
 * @border_bottom_color: #FoPropertyBorderBottomColor object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderBottomColor.
 **/
void
fo_property_border_bottom_color_init (FoPropertyBorderBottomColor *border_bottom_color)
{
  FO_PROPERTY (border_bottom_color)->value =
    g_object_ref (fo_property_util_get_color_initial ());
}

/**
 * fo_property_border_bottom_color_class_init:
 * @klass: #FoPropertyBorderBottomColorClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderBottomColorClass.
 **/
void
fo_property_border_bottom_color_class_init (FoPropertyBorderBottomColorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_bottom_color_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_color_enum;
  property_class->validate =
    fo_property_util_validate_color;
  property_class->get_initial =
    fo_property_border_bottom_color_get_initial;
}

/**
 * fo_property_border_bottom_color_finalize:
 * @object: #FoPropertyBorderBottomColor object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderBottomColor.
 **/
void
fo_property_border_bottom_color_finalize (GObject *object)
{
  FoPropertyBorderBottomColor *border_bottom_color;

  border_bottom_color = FO_PROPERTY_BORDER_BOTTOM_COLOR (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_bottom_color_new:
 * 
 * Creates a new #FoPropertyBorderBottomColor initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderBottomColor.
 **/
FoProperty*
fo_property_border_bottom_color_new (void)
{
  FoProperty* border_bottom_color;

  border_bottom_color =
    FO_PROPERTY (g_object_new (fo_property_border_bottom_color_get_type (),
                               NULL));

  return border_bottom_color;
}

/**
 * fo_property_border_bottom_color_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_bottom_color_get_initial (void)
{
  static FoProperty *border_bottom_color = NULL;

  if (border_bottom_color == NULL)
    {
      border_bottom_color =
	fo_property_border_bottom_color_new ();
    }

  return border_bottom_color;
}
