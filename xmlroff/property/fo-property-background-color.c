/* Fo
 * fo-property-background-color.c: 'background-color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-background-color.c,v 1.9 2005/02/28 11:53:40 tonygraham Exp $
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
#include "property/fo-property-background-color.h"
#include "property/fo-property-util.h"

/* background-color */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <color> | transparent | inherit */
/* Initial value: transparent */

struct _FoPropertyBackgroundColor
{
  FoProperty parent_instance;
};

struct _FoPropertyBackgroundColorClass
{
  FoPropertyClass parent_class;
};

static void fo_property_background_color_init         (FoPropertyBackgroundColor      *property_background_color);
static void fo_property_background_color_class_init   (FoPropertyBackgroundColorClass *klass);
static void fo_property_background_color_finalize     (GObject       *object);
static void fo_property_background_color_text_property_init (FoPropertyTextPropertyIface *iface);

static PangoAttribute * fo_property_background_color_new_attr (FoProperty *property);

static const gchar class_name[] = "background-color";
static gpointer parent_class;

/**
 * fo_property_background_color_get_type:
 * 
 * Register the #FoPropertyBackgroundColor type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBackgroundColor.
 **/
GType
fo_property_background_color_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBackgroundColorClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_background_color_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBackgroundColor),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_background_color_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_background_color_text_property_init, /* interface_init */
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
 * fo_property_background_color_init:
 * @background_color: #FoPropertyBackgroundColor object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBackgroundColor.
 **/
void
fo_property_background_color_init (FoPropertyBackgroundColor *background_color)
{
  FO_PROPERTY (background_color)->value =
    g_object_ref (fo_enum_get_enum_by_nick ("transparent"));
}

/**
 * fo_property_background_color_class_init:
 * @klass: #FoPropertyBackgroundColorClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBackgroundColorClass.
 **/
void
fo_property_background_color_class_init (FoPropertyBackgroundColorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_background_color_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_color_transparent_enum;
  property_class->validate =
    fo_property_util_validate_color_transparent;
  property_class->get_initial =
    fo_property_background_color_get_initial;
}

/**
 * fo_property_background_color_finalize:
 * @object: #FoPropertyBackgroundColor object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBackgroundColor.
 **/
void
fo_property_background_color_finalize (GObject *object)
{
  FoPropertyBackgroundColor *background_color;

  background_color = FO_PROPERTY_BACKGROUND_COLOR (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_background_color_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
void
fo_property_background_color_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_background_color_new_attr;
}

/**
 * fo_property_background_color_new:
 * 
 * Creates a new #FoPropertyBackgroundColor initialized to default value.
 * 
 * Return value: the new #FoPropertyBackgroundColor.
 **/
FoProperty*
fo_property_background_color_new (void)
{
  FoProperty* background_color;

  background_color =
    FO_PROPERTY (g_object_new (fo_property_background_color_get_type (),
                               NULL));

  return background_color;
}

/**
 * fo_property_background_color_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_background_color_get_initial (void)
{
  static FoProperty *background_color = NULL;

  if (background_color == NULL)
    {
      background_color =
	fo_property_background_color_new ();
    }

  return background_color;
}

/**
 * fo_property_background_color_new_attr:
 * @datatype: #FoDatatype from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the current property.
 * 
 * Return value: New #PangoAttribute.
 **/
PangoAttribute *
fo_property_background_color_new_attr (FoProperty *property)
{
  guint16 background_red;
  guint16 background_green;
  guint16 background_blue;

  g_return_val_if_fail (FO_IS_PROPERTY_BACKGROUND_COLOR (property), NULL);
  g_return_val_if_fail (FO_IS_COLOR (property->value), NULL);

  background_red =
    fo_color_get_red (property->value);
  background_green =
    fo_color_get_green (property->value);
  background_blue =
    fo_color_get_blue (property->value);

  return pango_attr_background_new (background_red,
				    background_green,
				    background_blue);
}
