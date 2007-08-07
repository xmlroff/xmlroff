/* Fo
 * fo-property-padding-after-conditionality.c: 'padding-after-conditionality' property
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
#include "property/fo-property-type-condity-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-padding-after-conditionality.h"

/* padding-after-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* discard | retain */
/* Initial value: discard */

struct _FoPropertyPaddingAfterCondity
{
  FoPropertyTypeCondity parent_instance;
};

struct _FoPropertyPaddingAfterCondityClass
{
  FoPropertyTypeCondityClass parent_class;
};

static void fo_property_padding_after_condity_class_init   (FoPropertyPaddingAfterCondityClass *klass);

static const gchar class_name[] = "padding-after-condity";

/**
 * fo_property_padding_after_condity_get_type:
 * 
 * Register the #FoPropertyPaddingAfterCondity type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyPaddingAfterCondity.
 **/
GType
fo_property_padding_after_condity_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyPaddingAfterCondityClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_padding_after_condity_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyPaddingAfterCondity),
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
 * fo_property_padding_after_condity_class_init:
 * @klass: #FoPropertyPaddingAfterCondityClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyPaddingAfterCondityClass.
 **/
void
fo_property_padding_after_condity_class_init (FoPropertyPaddingAfterCondityClass *klass)
{
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  property_class->get_initial =
    fo_property_padding_after_condity_get_initial;
}

/**
 * fo_property_padding_after_condity_new:
 * 
 * Creates a new #FoPropertyPaddingAfterCondity initialized to default value.
 * 
 * Return value: the new #FoPropertyPaddingAfterCondity.
 **/
FoProperty*
fo_property_padding_after_condity_new (void)
{
  FoProperty* padding_after_condity;

  padding_after_condity =
    FO_PROPERTY (g_object_new (fo_property_padding_after_condity_get_type (),
                               NULL));

  return padding_after_condity;
}

/**
 * fo_property_padding_after_condity_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_padding_after_condity_get_initial (void)
{
  static FoProperty *padding_after_condity = NULL;

  if (padding_after_condity == NULL)
    {
      padding_after_condity =
	fo_property_padding_after_condity_new ();
    }

  return padding_after_condity;
}
