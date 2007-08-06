/* Fo
 * fo-property-border.c: 'border' property
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
#include "property/fo-property-border.h"
#include "property/fo-property-util.h"

/* border */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

struct _FoPropertyBorder
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_init         (FoPropertyBorder      *property_border);
static void fo_property_border_class_init   (FoPropertyBorderClass *klass);
static void fo_property_border_finalize     (GObject       *object);


static const gchar class_name[] = "FoPropertyBorder";
static gpointer parent_class;

/**
 * fo_property_border_get_type:
 * 
 * Register the #FoPropertyBorder type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorder.
 **/
GType
fo_property_border_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorder),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_init:
 * @border: #FoPropertyBorder object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorder.
 **/
void
fo_property_border_init (FoPropertyBorder *border)
{
  FO_PROPERTY (border)->value =
    NULL;
}

/**
 * fo_property_border_class_init:
 * @klass: #FoPropertyBorderClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderClass.
 **/
void
fo_property_border_class_init (FoPropertyBorderClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_finalize;

  property_class->expr_eval = fo_expr_wsc_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_wsc_enum;
  property_class->validate =
    fo_property_util_validate_wsc;
  property_class->get_initial =
    fo_property_border_get_initial;
}

/**
 * fo_property_border_finalize:
 * @object: #FoPropertyBorder object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorder.
 **/
void
fo_property_border_finalize (GObject *object)
{
  FoPropertyBorder *border;

  border = FO_PROPERTY_BORDER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_new:
 * 
 * Creates a new #FoPropertyBorder initialized to default value.
 * 
 * Return value: the new #FoPropertyBorder.
 **/
FoProperty*
fo_property_border_new (void)
{
  FoProperty* border;

  border =
    FO_PROPERTY (g_object_new (fo_property_border_get_type (),
                               NULL));

  return border;
}

/**
 * fo_property_border_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_get_initial (void)
{
  static FoProperty *border = NULL;

  if (border == NULL)
    {
      border =
	fo_property_border_new ();
    }

  return border;
}
