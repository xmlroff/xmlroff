/* Fo
 * fo-property-border-before-style.c: 'border-before-style' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-before-style.c,v 1.3 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-border-before-style.h"
#include "property/fo-property-util.h"

/* border-before-style */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-style> | inherit */
/* Initial value: none */

struct _FoPropertyBorderBeforeStyle
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderBeforeStyleClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_before_style_init         (FoPropertyBorderBeforeStyle      *property_border_before_style);
static void fo_property_border_before_style_class_init   (FoPropertyBorderBeforeStyleClass *klass);
static void fo_property_border_before_style_finalize     (GObject       *object);

static const gchar class_name[] = "border-before-style";
static gpointer parent_class;

/**
 * fo_property_border_before_style_get_type:
 * 
 * Register the #FoPropertyBorderBeforeStyle type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderBeforeStyle.
 **/
GType
fo_property_border_before_style_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderBeforeStyleClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_before_style_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderBeforeStyle),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_before_style_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_before_style_init:
 * @border_before_style: #FoPropertyBorderBeforeStyle object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderBeforeStyle.
 **/
void
fo_property_border_before_style_init (FoPropertyBorderBeforeStyle *border_before_style)
{
  FO_PROPERTY (border_before_style)->value =
    g_object_ref (fo_property_util_get_style_initial ());
}

/**
 * fo_property_border_before_style_class_init:
 * @klass: #FoPropertyBorderBeforeStyleClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderBeforeStyleClass.
 **/
void
fo_property_border_before_style_class_init (FoPropertyBorderBeforeStyleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_before_style_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_style_enum;
  property_class->validate =
    fo_property_util_validate_style;
  property_class->get_initial =
    fo_property_border_before_style_get_initial;
}

/**
 * fo_property_border_before_style_finalize:
 * @object: #FoPropertyBorderBeforeStyle object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderBeforeStyle.
 **/
void
fo_property_border_before_style_finalize (GObject *object)
{
  FoPropertyBorderBeforeStyle *border_before_style;

  border_before_style = FO_PROPERTY_BORDER_BEFORE_STYLE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_before_style_new:
 * 
 * Creates a new #FoPropertyBorderBeforeStyle initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderBeforeStyle.
 **/
FoProperty*
fo_property_border_before_style_new (void)
{
  FoProperty* border_before_style;

  border_before_style =
    FO_PROPERTY (g_object_new (fo_property_border_before_style_get_type (),
                               NULL));

  return border_before_style;
}

/**
 * fo_property_border_before_style_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_before_style_get_initial (void)
{
  static FoProperty *border_before_style = NULL;

  if (border_before_style == NULL)
    {
      border_before_style =
	fo_property_border_before_style_new ();
    }

  return border_before_style;
}
