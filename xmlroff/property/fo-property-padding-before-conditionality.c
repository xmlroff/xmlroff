/* Fo
 * fo-property-padding-before-conditionality.c: 'padding-before-conditionality' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-padding-before-conditionality.c,v 1.1 2004/05/29 04:42:15 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-type-condity-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-padding-before-conditionality.h"

/* padding-before-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* discard | retain */
/* Initial value: discard */

struct _FoPropertyPaddingBeforeCondity
{
  FoPropertyTypeCondity parent_instance;
};

struct _FoPropertyPaddingBeforeCondityClass
{
  FoPropertyTypeCondityClass parent_class;
};

static void fo_property_padding_before_condity_class_init   (FoPropertyPaddingBeforeCondityClass *klass);

static const gchar class_name[] = "padding-before-condity";

/**
 * fo_property_padding_before_condity_get_type:
 * 
 * Register the #FoPropertyPaddingBeforeCondity type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyPaddingBeforeCondity.
 **/
GType
fo_property_padding_before_condity_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyPaddingBeforeCondityClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_padding_before_condity_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyPaddingBeforeCondity),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_type_condity_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY_TYPE_CONDITY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_padding_before_condity_class_init:
 * @klass: #FoPropertyPaddingBeforeCondityClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyPaddingBeforeCondityClass.
 **/
void
fo_property_padding_before_condity_class_init (FoPropertyPaddingBeforeCondityClass *klass)
{
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  property_class->get_initial =
    fo_property_padding_before_condity_get_initial;
}

/**
 * fo_property_padding_before_condity_new:
 * 
 * Creates a new #FoPropertyPaddingBeforeCondity initialized to default value.
 * 
 * Return value: the new #FoPropertyPaddingBeforeCondity.
 **/
FoProperty*
fo_property_padding_before_condity_new (void)
{
  FoProperty* padding_before_condity;

  padding_before_condity =
    FO_PROPERTY (g_object_new (fo_property_padding_before_condity_get_type (),
                               NULL));

  return padding_before_condity;
}

/**
 * fo_property_padding_before_condity_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_padding_before_condity_get_initial (void)
{
  static FoProperty *padding_before_condity = NULL;

  if (padding_before_condity == NULL)
    {
      padding_before_condity =
	fo_property_padding_before_condity_new ();
    }

  return padding_before_condity;
}
