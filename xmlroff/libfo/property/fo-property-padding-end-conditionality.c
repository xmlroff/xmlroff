/* Fo
 * fo-property-padding-end-conditionality.c: 'padding-end-conditionality' property
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
#include "property/fo-property-padding-end-conditionality.h"

/* padding-end-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* discard | retain */
/* Initial value: discard */

struct _FoPropertyPaddingEndCondity
{
  FoPropertyTypeCondity parent_instance;
};

struct _FoPropertyPaddingEndCondityClass
{
  FoPropertyTypeCondityClass parent_class;
};

static void fo_property_padding_end_condity_class_init   (FoPropertyPaddingEndCondityClass *klass);

static const gchar class_name[] = "FoPropertyPaddingEndCondity";

/**
 * fo_property_padding_end_condity_get_type:
 * 
 * Register the #FoPropertyPaddingEndCondity type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyPaddingEndCondity.
 **/
GType
fo_property_padding_end_condity_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyPaddingEndCondityClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_padding_end_condity_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyPaddingEndCondity),
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
 * fo_property_padding_end_condity_class_init:
 * @klass: #FoPropertyPaddingEndCondityClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyPaddingEndCondityClass.
 **/
void
fo_property_padding_end_condity_class_init (FoPropertyPaddingEndCondityClass *klass)
{
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  property_class->get_initial =
    fo_property_padding_end_condity_get_initial;
}

/**
 * fo_property_padding_end_condity_new:
 * 
 * Creates a new #FoPropertyPaddingEndCondity initialized to default value.
 * 
 * Return value: the new #FoPropertyPaddingEndCondity.
 **/
FoProperty*
fo_property_padding_end_condity_new (void)
{
  FoProperty* padding_end_condity;

  padding_end_condity =
    FO_PROPERTY (g_object_new (fo_property_padding_end_condity_get_type (),
                               NULL));

  return padding_end_condity;
}

/**
 * fo_property_padding_end_condity_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_padding_end_condity_get_initial (void)
{
  static FoProperty *padding_end_condity = NULL;

  if (padding_end_condity == NULL)
    {
      padding_end_condity =
	fo_property_padding_end_condity_new ();
    }

  return padding_end_condity;
}
