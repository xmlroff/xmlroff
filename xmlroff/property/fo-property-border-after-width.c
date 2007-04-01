/* Fo
 * fo-property-border-after-width.c: 'border-after-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-after-width.c,v 1.3 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-border-after-width.h"
#include "property/fo-property-util.h"

/* border-after-width */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <border-width> | <length-conditional> | inherit */
/* Initial value: medium */

struct _FoPropertyBorderAfterWidth
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderAfterWidthClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_after_width_init         (FoPropertyBorderAfterWidth      *property_border_after_width);
static void fo_property_border_after_width_class_init   (FoPropertyBorderAfterWidthClass *klass);
static void fo_property_border_after_width_finalize     (GObject       *object);

static const gchar class_name[] = "border-after-width";
static gpointer parent_class;

/**
 * fo_property_border_after_width_get_type:
 * 
 * Register the #FoPropertyBorderAfterWidth type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderAfterWidth.
 **/
GType
fo_property_border_after_width_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderAfterWidthClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_after_width_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderAfterWidth),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_after_width_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_after_width_init:
 * @border_after_width: #FoPropertyBorderAfterWidth object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderAfterWidth.
 **/
void
fo_property_border_after_width_init (FoPropertyBorderAfterWidth *border_after_width)
{
  FO_PROPERTY (border_after_width)->value =
    g_object_ref (fo_property_util_get_width_initial ());
}

/**
 * fo_property_border_after_width_class_init:
 * @klass: #FoPropertyBorderAfterWidthClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderAfterWidthClass.
 **/
void
fo_property_border_after_width_class_init (FoPropertyBorderAfterWidthClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_after_width_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_width_enum;
  property_class->validate =
    fo_property_util_validate_width;
  property_class->get_initial =
    fo_property_border_after_width_get_initial;
}

/**
 * fo_property_border_after_width_finalize:
 * @object: #FoPropertyBorderAfterWidth object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderAfterWidth.
 **/
void
fo_property_border_after_width_finalize (GObject *object)
{
  FoPropertyBorderAfterWidth *border_after_width;

  border_after_width = FO_PROPERTY_BORDER_AFTER_WIDTH (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_after_width_new:
 * 
 * Creates a new #FoPropertyBorderAfterWidth initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderAfterWidth.
 **/
FoProperty*
fo_property_border_after_width_new (void)
{
  FoProperty* border_after_width;

  border_after_width =
    FO_PROPERTY (g_object_new (fo_property_border_after_width_get_type (),
                               NULL));

  return border_after_width;
}

/**
 * fo_property_border_after_width_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_after_width_get_initial (void)
{
  static FoProperty *border_after_width = NULL;

  if (border_after_width == NULL)
    {
      border_after_width =
	fo_property_border_after_width_new ();
    }

  return border_after_width;
}
