/* Fo
 * fo-property-border-left.c: 'border-left' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-border-left.c,v 1.3 2005/04/07 17:56:42 jrosse1 Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-border-left.h"
#include "property/fo-property-util.h"

/* border-left */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

struct _FoPropertyBorderLeft
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderLeftClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_left_init         (FoPropertyBorderLeft      *property_border_left);
static void fo_property_border_left_class_init   (FoPropertyBorderLeftClass *klass);
static void fo_property_border_left_finalize     (GObject       *object);


static const gchar class_name[] = "border-left";
static gpointer parent_class;

/**
 * fo_property_border_left_get_type:
 * 
 * Register the #FoPropertyBorderLeft type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderLeft.
 **/
GType
fo_property_border_left_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderLeftClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_left_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderLeft),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_left_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_left_init:
 * @border_left: #FoPropertyBorderLeft object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderLeft.
 **/
void
fo_property_border_left_init (FoPropertyBorderLeft *border_left)
{
  FO_PROPERTY (border_left)->value =
    NULL;
}

/**
 * fo_property_border_left_class_init:
 * @klass: #FoPropertyBorderLeftClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderLeftClass.
 **/
void
fo_property_border_left_class_init (FoPropertyBorderLeftClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_left_finalize;

  property_class->expr_eval = fo_expr_wsc_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_wsc_enum;
  property_class->validate =
    fo_property_util_validate_wsc;
  property_class->get_initial =
    fo_property_border_left_get_initial;
}

/**
 * fo_property_border_left_finalize:
 * @object: #FoPropertyBorderLeft object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderLeft.
 **/
void
fo_property_border_left_finalize (GObject *object)
{
  FoPropertyBorderLeft *border_left;

  border_left = FO_PROPERTY_BORDER_LEFT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_left_new:
 * 
 * Creates a new #FoPropertyBorderLeft initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderLeft.
 **/
FoProperty*
fo_property_border_left_new (void)
{
  FoProperty* border_left;

  border_left =
    FO_PROPERTY (g_object_new (fo_property_border_left_get_type (),
                               NULL));

  return border_left;
}

/**
 * fo_property_border_left_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_left_get_initial (void)
{
  static FoProperty *border_left = NULL;

  if (border_left == NULL)
    {
      border_left =
	fo_property_border_left_new ();
    }

  return border_left;
}
