/* Fo
 * fo-property-color.c: 'color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-color.c,v 1.7 2004/10/12 14:51:39 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include <pangoxsl/pango-xsl-attributes.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-color.h"
#include "property/fo-property-util.h"

/* color */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <color> | inherit */
/* Initial value: depends on user agent */

struct _FoPropertyColor
{
  FoProperty parent_instance;
};

struct _FoPropertyColorClass
{
  FoPropertyClass parent_class;
};

static void fo_property_color_init         (FoPropertyColor      *property_color);
static void fo_property_color_class_init   (FoPropertyColorClass *klass);
static void fo_property_color_finalize     (GObject       *object);
static void fo_property_color_text_property_init (FoPropertyTextPropertyIface *iface);

static PangoAttribute * fo_property_color_new_attr (FoProperty *property);

static const gchar class_name[] = "color";
static gpointer parent_class;

/**
 * fo_property_color_get_type:
 * 
 * Register the #FoPropertyColor type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyColor.
 **/
GType
fo_property_color_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyColorClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_color_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyColor),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_color_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_color_text_property_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);

      g_type_add_interface_static (object_type,
                                   FO_TYPE_PROPERTY_TEXT_PROPERTY,
                                   &fo_property_text_property_info);
    }

  return object_type;
}

/**
 * fo_property_color_init:
 * @color: #FoPropertyColor object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyColor.
 **/
void
fo_property_color_init (FoPropertyColor *color)
{
  FO_PROPERTY (color)->value =
    g_object_ref (fo_property_util_get_color_initial ());
}

/**
 * fo_property_color_class_init:
 * @klass: #FoPropertyColorClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyColorClass.
 **/
void
fo_property_color_class_init (FoPropertyColorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_color_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_color_enum;
  property_class->validate =
    fo_property_util_validate_color;
  property_class->get_initial =
    fo_property_color_get_initial;
}

/**
 * fo_property_color_finalize:
 * @object: #FoPropertyColor object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyColor.
 **/
void
fo_property_color_finalize (GObject *object)
{
  FoPropertyColor *color;

  color = FO_PROPERTY_COLOR (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_color_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
void
fo_property_color_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_color_new_attr;
}

/**
 * fo_property_color_new:
 * 
 * Creates a new #FoPropertyColor initialized to default value.
 * 
 * Return value: the new #FoPropertyColor.
 **/
FoProperty*
fo_property_color_new (void)
{
  FoProperty* color;

  color =
    FO_PROPERTY (g_object_new (fo_property_color_get_type (),
                               NULL));

  return color;
}

/**
 * fo_property_color_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_color_get_initial (void)
{
  static FoProperty *color = NULL;

  if (color == NULL)
    {
      color =
	fo_property_color_new ();
    }

  return color;
}

/**
 * fo_property_color_new_attr:
 * @property: Property from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the current property.
 * 
 * Returns: New #PangoAttribute.
 **/
PangoAttribute*
fo_property_color_new_attr (FoProperty *property)
{
  guint16 foreground_red;
  guint16 foreground_green;
  guint16 foreground_blue;

  g_return_val_if_fail (FO_IS_PROPERTY_COLOR (property), NULL);

  foreground_red =
    fo_color_get_red (property->value);
  foreground_green =
    fo_color_get_green (property->value);
  foreground_blue =
    fo_color_get_blue (property->value);

  return pango_attr_foreground_new (foreground_red,
				    foreground_green,
				    foreground_blue);
}
