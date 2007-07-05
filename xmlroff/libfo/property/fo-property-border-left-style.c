/* Fo
 * fo-property-border-left-style.c: 'border-left-style' property
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
#include "property/fo-property-border-left-style.h"
#include "property/fo-property-util.h"

/* border-left-style */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-style> | inherit */
/* Initial value: none */

struct _FoPropertyBorderLeftStyle
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderLeftStyleClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_left_style_init         (FoPropertyBorderLeftStyle      *property_border_left_style);
static void fo_property_border_left_style_class_init   (FoPropertyBorderLeftStyleClass *klass);
static void fo_property_border_left_style_finalize     (GObject       *object);

static const gchar class_name[] = "border-left-style";
static gpointer parent_class;

/**
 * fo_property_border_left_style_get_type:
 * 
 * Register the #FoPropertyBorderLeftStyle type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderLeftStyle.
 **/
GType
fo_property_border_left_style_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderLeftStyleClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_left_style_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderLeftStyle),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_left_style_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_left_style_init:
 * @border_left_style: #FoPropertyBorderLeftStyle object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderLeftStyle.
 **/
void
fo_property_border_left_style_init (FoPropertyBorderLeftStyle *border_left_style)
{
  FO_PROPERTY (border_left_style)->value =
    g_object_ref (fo_property_util_get_style_initial ());
}

/**
 * fo_property_border_left_style_class_init:
 * @klass: #FoPropertyBorderLeftStyleClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderLeftStyleClass.
 **/
void
fo_property_border_left_style_class_init (FoPropertyBorderLeftStyleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_left_style_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_style_enum;
  property_class->validate =
    fo_property_util_validate_style;
  property_class->get_initial =
    fo_property_border_left_style_get_initial;
}

/**
 * fo_property_border_left_style_finalize:
 * @object: #FoPropertyBorderLeftStyle object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderLeftStyle.
 **/
void
fo_property_border_left_style_finalize (GObject *object)
{
  FoPropertyBorderLeftStyle *border_left_style;

  border_left_style = FO_PROPERTY_BORDER_LEFT_STYLE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_left_style_new:
 * 
 * Creates a new #FoPropertyBorderLeftStyle initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderLeftStyle.
 **/
FoProperty*
fo_property_border_left_style_new (void)
{
  FoProperty* border_left_style;

  border_left_style =
    FO_PROPERTY (g_object_new (fo_property_border_left_style_get_type (),
                               NULL));

  return border_left_style;
}

/**
 * fo_property_border_left_style_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_left_style_get_initial (void)
{
  static FoProperty *border_left_style = NULL;

  if (border_left_style == NULL)
    {
      border_left_style =
	fo_property_border_left_style_new ();
    }

  return border_left_style;
}
