/* Fo
 * fo-property-border-bottom.c: 'border-bottom' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
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
#include "property/fo-property-border-bottom.h"
#include "property/fo-property-util.h"

/* border-bottom */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

struct _FoPropertyBorderBottom
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderBottomClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_bottom_init         (FoPropertyBorderBottom      *property_border_bottom);
static void fo_property_border_bottom_class_init   (FoPropertyBorderBottomClass *klass);
static void fo_property_border_bottom_finalize     (GObject       *object);


static const gchar class_name[] = "border-bottom";
static gpointer parent_class;

/**
 * fo_property_border_bottom_get_type:
 * 
 * Register the #FoPropertyBorderBottom type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderBottom.
 **/
GType
fo_property_border_bottom_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderBottomClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_bottom_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderBottom),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_bottom_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_bottom_init:
 * @border_bottom: #FoPropertyBorderBottom object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderBottom.
 **/
void
fo_property_border_bottom_init (FoPropertyBorderBottom *border_bottom)
{
  FO_PROPERTY (border_bottom)->value =
    NULL;
}

/**
 * fo_property_border_bottom_class_init:
 * @klass: #FoPropertyBorderBottomClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderBottomClass.
 **/
void
fo_property_border_bottom_class_init (FoPropertyBorderBottomClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_bottom_finalize;

  property_class->expr_eval = fo_expr_wsc_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_wsc_enum;
  property_class->validate =
    fo_property_util_validate_wsc;
  property_class->get_initial =
    fo_property_border_bottom_get_initial;
}

/**
 * fo_property_border_bottom_finalize:
 * @object: #FoPropertyBorderBottom object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderBottom.
 **/
void
fo_property_border_bottom_finalize (GObject *object)
{
  FoPropertyBorderBottom *border_bottom;

  border_bottom = FO_PROPERTY_BORDER_BOTTOM (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_bottom_new:
 * 
 * Creates a new #FoPropertyBorderBottom initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderBottom.
 **/
FoProperty*
fo_property_border_bottom_new (void)
{
  FoProperty* border_bottom;

  border_bottom =
    FO_PROPERTY (g_object_new (fo_property_border_bottom_get_type (),
                               NULL));

  return border_bottom;
}

/**
 * fo_property_border_bottom_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_bottom_get_initial (void)
{
  static FoProperty *border_bottom = NULL;

  if (border_bottom == NULL)
    {
      border_bottom =
	fo_property_border_bottom_new ();
    }

  return border_bottom;
}
