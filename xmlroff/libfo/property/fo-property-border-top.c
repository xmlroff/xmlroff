/* Fo
 * fo-property-border-top.c: 'border-top' property
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
#include "property/fo-property-border-top.h"
#include "property/fo-property-util.h"

/* border-top */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

struct _FoPropertyBorderTop
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderTopClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_top_init         (FoPropertyBorderTop      *property_border_top);
static void fo_property_border_top_class_init   (FoPropertyBorderTopClass *klass);
static void fo_property_border_top_finalize     (GObject       *object);


static const gchar class_name[] = "border-top";
static gpointer parent_class;

/**
 * fo_property_border_top_get_type:
 * 
 * Register the #FoPropertyBorderTop type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderTop.
 **/
GType
fo_property_border_top_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderTopClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_top_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderTop),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_top_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_top_init:
 * @border_top: #FoPropertyBorderTop object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderTop.
 **/
void
fo_property_border_top_init (FoPropertyBorderTop *border_top)
{
  FO_PROPERTY (border_top)->value =
    NULL;
}

/**
 * fo_property_border_top_class_init:
 * @klass: #FoPropertyBorderTopClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderTopClass.
 **/
void
fo_property_border_top_class_init (FoPropertyBorderTopClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_top_finalize;

  property_class->expr_eval = fo_expr_wsc_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_wsc_enum;
  property_class->validate =
    fo_property_util_validate_wsc;
  property_class->get_initial =
    fo_property_border_top_get_initial;
}

/**
 * fo_property_border_top_finalize:
 * @object: #FoPropertyBorderTop object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderTop.
 **/
void
fo_property_border_top_finalize (GObject *object)
{
  FoPropertyBorderTop *border_top;

  border_top = FO_PROPERTY_BORDER_TOP (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_top_new:
 * 
 * Creates a new #FoPropertyBorderTop initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderTop.
 **/
FoProperty*
fo_property_border_top_new (void)
{
  FoProperty* border_top;

  border_top =
    FO_PROPERTY (g_object_new (fo_property_border_top_get_type (),
                               NULL));

  return border_top;
}

/**
 * fo_property_border_top_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_top_get_initial (void)
{
  static FoProperty *border_top = NULL;

  if (border_top == NULL)
    {
      border_top =
	fo_property_border_top_new ();
    }

  return border_top;
}
