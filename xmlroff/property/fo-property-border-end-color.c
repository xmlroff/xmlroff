/* Fo
 * fo-property-border-end-color.c: 'border-end-color' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-end-color.c,v 1.4 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-border-end-color.h"
#include "property/fo-property-util.h"

/* border-end-color */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <color> | inherit */
/* Initial value: the value of the 'color' property */

struct _FoPropertyBorderEndColor
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderEndColorClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_end_color_init         (FoPropertyBorderEndColor      *property_border_end_color);
static void fo_property_border_end_color_class_init   (FoPropertyBorderEndColorClass *klass);
static void fo_property_border_end_color_finalize     (GObject       *object);

static const gchar class_name[] = "border-end-color";
static gpointer parent_class;

/**
 * fo_property_border_end_color_get_type:
 * 
 * Register the #FoPropertyBorderEndColor type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderEndColor.
 **/
GType
fo_property_border_end_color_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderEndColorClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_end_color_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderEndColor),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_end_color_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_end_color_init:
 * @border_end_color: #FoPropertyBorderEndColor object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderEndColor.
 **/
void
fo_property_border_end_color_init (FoPropertyBorderEndColor *border_end_color)
{
  FO_PROPERTY (border_end_color)->value =
    g_object_ref (fo_property_util_get_color_initial ());
}

/**
 * fo_property_border_end_color_class_init:
 * @klass: #FoPropertyBorderEndColorClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderEndColorClass.
 **/
void
fo_property_border_end_color_class_init (FoPropertyBorderEndColorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_end_color_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_color_enum;
  property_class->validate =
    fo_property_util_validate_color;
  property_class->get_initial =
    fo_property_border_end_color_get_initial;
}

/**
 * fo_property_border_end_color_finalize:
 * @object: #FoPropertyBorderEndColor object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderEndColor.
 **/
void
fo_property_border_end_color_finalize (GObject *object)
{
  FoPropertyBorderEndColor *border_end_color;

  border_end_color = FO_PROPERTY_BORDER_END_COLOR (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_end_color_new:
 * 
 * Creates a new #FoPropertyBorderEndColor initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderEndColor.
 **/
FoProperty*
fo_property_border_end_color_new (void)
{
  FoProperty* border_end_color;

  border_end_color =
    FO_PROPERTY (g_object_new (fo_property_border_end_color_get_type (),
                               NULL));

  return border_end_color;
}

/**
 * fo_property_border_end_color_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_end_color_get_initial (void)
{
  static FoProperty *border_end_color = NULL;

  if (border_end_color == NULL)
    {
      border_end_color =
	fo_property_border_end_color_new ();
    }

  return border_end_color;
}
