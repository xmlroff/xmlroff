/* Fo
 * fo-property-border-start-style.c: 'border-start-style' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-start-style.c,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-border-start-style.h"
#include "property/fo-property-util.h"

/* border-start-style */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-style> | inherit */
/* Initial value: none */

struct _FoPropertyBorderStartStyle
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderStartStyleClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_start_style_init         (FoPropertyBorderStartStyle      *property_border_start_style);
static void fo_property_border_start_style_class_init   (FoPropertyBorderStartStyleClass *klass);
static void fo_property_border_start_style_finalize     (GObject       *object);

static const gchar class_name[] = "border-start-style";
static gpointer parent_class;

/**
 * fo_property_border_start_style_get_type:
 * 
 * Register the #FoPropertyBorderStartStyle type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderStartStyle.
 **/
GType
fo_property_border_start_style_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderStartStyleClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_start_style_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderStartStyle),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_start_style_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_start_style_init:
 * @border_start_style: #FoPropertyBorderStartStyle object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderStartStyle.
 **/
void
fo_property_border_start_style_init (FoPropertyBorderStartStyle *border_start_style)
{
  FO_PROPERTY (border_start_style)->value =
    g_object_ref (fo_property_util_get_style_initial ());
}

/**
 * fo_property_border_start_style_class_init:
 * @klass: #FoPropertyBorderStartStyleClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderStartStyleClass.
 **/
void
fo_property_border_start_style_class_init (FoPropertyBorderStartStyleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_start_style_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_style_enum;
  property_class->validate =
    fo_property_util_validate_style;
  property_class->get_initial =
    fo_property_border_start_style_get_initial;
}

/**
 * fo_property_border_start_style_finalize:
 * @object: #FoPropertyBorderStartStyle object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderStartStyle.
 **/
void
fo_property_border_start_style_finalize (GObject *object)
{
  FoPropertyBorderStartStyle *border_start_style;

  border_start_style = FO_PROPERTY_BORDER_START_STYLE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_start_style_new:
 * 
 * Creates a new #FoPropertyBorderStartStyle initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderStartStyle.
 **/
FoProperty*
fo_property_border_start_style_new (void)
{
  FoProperty* border_start_style;

  border_start_style =
    FO_PROPERTY (g_object_new (fo_property_border_start_style_get_type (),
                               NULL));

  return border_start_style;
}

/**
 * fo_property_border_start_style_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_start_style_get_initial (void)
{
  static FoProperty *border_start_style = NULL;

  if (border_start_style == NULL)
    {
      border_start_style =
	fo_property_border_start_style_new ();
    }

  return border_start_style;
}
