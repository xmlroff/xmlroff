/* Fo
 * fo-property-border-right.c: 'border-right' property
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
#include "property/fo-property-border-right.h"
#include "property/fo-property-util.h"

/* border-right */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

struct _FoPropertyBorderRight
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderRightClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_right_init         (FoPropertyBorderRight      *property_border_right);
static void fo_property_border_right_class_init   (FoPropertyBorderRightClass *klass);
static void fo_property_border_right_finalize     (GObject       *object);


static const gchar class_name[] = "border-right";
static gpointer parent_class;

/**
 * fo_property_border_right_get_type:
 * 
 * Register the #FoPropertyBorderRight type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderRight.
 **/
GType
fo_property_border_right_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderRightClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_right_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderRight),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_right_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_right_init:
 * @border_right: #FoPropertyBorderRight object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderRight.
 **/
void
fo_property_border_right_init (FoPropertyBorderRight *border_right)
{
  FO_PROPERTY (border_right)->value =
    NULL;
}

/**
 * fo_property_border_right_class_init:
 * @klass: #FoPropertyBorderRightClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderRightClass.
 **/
void
fo_property_border_right_class_init (FoPropertyBorderRightClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_right_finalize;

  property_class->expr_eval = fo_expr_wsc_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_wsc_enum;
  property_class->validate =
    fo_property_util_validate_wsc;
  property_class->get_initial =
    fo_property_border_right_get_initial;
}

/**
 * fo_property_border_right_finalize:
 * @object: #FoPropertyBorderRight object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderRight.
 **/
void
fo_property_border_right_finalize (GObject *object)
{
  FoPropertyBorderRight *border_right;

  border_right = FO_PROPERTY_BORDER_RIGHT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_right_new:
 * 
 * Creates a new #FoPropertyBorderRight initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderRight.
 **/
FoProperty*
fo_property_border_right_new (void)
{
  FoProperty* border_right;

  border_right =
    FO_PROPERTY (g_object_new (fo_property_border_right_get_type (),
                               NULL));

  return border_right;
}

/**
 * fo_property_border_right_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_right_get_initial (void)
{
  static FoProperty *border_right = NULL;

  if (border_right == NULL)
    {
      border_right =
	fo_property_border_right_new ();
    }

  return border_right;
}
