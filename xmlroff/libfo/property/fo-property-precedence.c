/* Fo
 * fo-property-precedence.c: 'precedence' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-precedence.h"
#include "property/fo-property-util.h"

/**
 * SECTION:fo-property-precedence
 * @short_description: 'precedence' property
 *
 * Inherited: FALSE
 *
 * Shorthand: FALSE
 *
 * Value: true | false | inherit
 *
 * Initial value: false
 *
 * Definition: <ulink url="http://www.w3.org/TR/xsl11/&num;precedence">http://www.w3.org/TR/xsl11/&num;precedence</ulink>
 */

struct _FoPropertyPrecedence
{
  FoProperty parent_instance;
};

struct _FoPropertyPrecedenceClass
{
  FoPropertyClass parent_class;
};

static void _init         (FoPropertyPrecedence      *property_precedence);
static void _class_init   (FoPropertyPrecedenceClass *klass);

static FoDatatype * _resolve_enum (const gchar *token,
                                   FoContext   *context,
                                   GError     **error);
static FoDatatype * _validate     (FoDatatype  *datatype,
                                   FoContext   *context,
                                   GError     **error);

static const gchar class_name[] = "precedence";
static gpointer parent_class;

/**
 * fo_property_precedence_get_type:
 * 
 * Register the #FoPropertyPrecedence type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyPrecedence.
 **/
GType
fo_property_precedence_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyPrecedenceClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) _class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyPrecedence),
        0,              /* n_preallocs */
        (GInstanceInitFunc) _init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * _init:
 * @precedence: #FoPropertyPrecedence object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyPrecedence.
 **/
static void
_init (FoPropertyPrecedence *precedence)
{
  FO_PROPERTY (precedence)->value =
    g_object_ref (fo_boolean_get_false ());
}

/**
 * _class_init:
 * @klass: #FoPropertyPrecedenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyPrecedenceClass.
 **/
static void
_class_init (FoPropertyPrecedenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);


  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_true_false_enum;
  property_class->validate =
    fo_property_util_validate_boolean;
  property_class->get_initial =
    fo_property_precedence_get_initial;
}


/**
 * fo_property_precedence_new:
 * 
 * Creates a new #FoPropertyPrecedence initialized to default value.
 * 
 * Return value: the new #FoPropertyPrecedence.
 **/
FoProperty*
fo_property_precedence_new (void)
{
  FoProperty* precedence;

  precedence =
    FO_PROPERTY (g_object_new (fo_property_precedence_get_type (),
                               NULL));

  return precedence;
}

/**
 * fo_property_precedence_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_precedence_get_initial (void)
{
  static FoProperty *precedence = NULL;

  if (precedence == NULL)
    {
      precedence =
	fo_property_precedence_new ();
    }

  return precedence;
}
