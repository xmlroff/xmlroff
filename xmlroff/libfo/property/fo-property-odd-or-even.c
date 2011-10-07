/* Fo
 * fo-property-odd-or-even.c: 'odd-or-even' property
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
#include "property/fo-property-odd-or-even.h"

/**
 * SECTION:fo-property-odd-or-even
 * @short_description: 'odd-or-even' property
 *
 * Inherited: FALSE
 *
 * Shorthand: FALSE
 *
 * Value: odd | even | any | inherit
 *
 * Initial value: any
 *
 * Definition: <ulink url="http://www.w3.org/TR/xsl11/&num;odd-or-even">http://www.w3.org/TR/xsl11/&num;odd-or-even</ulink>
 */

struct _FoPropertyOddOrEven
{
  FoProperty parent_instance;
};

struct _FoPropertyOddOrEvenClass
{
  FoPropertyClass parent_class;
};

static void _init         (FoPropertyOddOrEven      *property_odd_or_even);
static void _class_init   (FoPropertyOddOrEvenClass *klass);

static FoDatatype * _resolve_enum (const gchar *token,
                                   FoContext   *context,
                                   GError     **error);
static FoDatatype * _validate     (FoDatatype  *datatype,
                                   FoContext   *context,
                                   GError     **error);

static const gchar class_name[] = "odd-or-even";
static gpointer parent_class;

/**
 * fo_property_odd_or_even_get_type:
 * 
 * Register the #FoPropertyOddOrEven type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyOddOrEven.
 **/
GType
fo_property_odd_or_even_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyOddOrEvenClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) _class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyOddOrEven),
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
 * @odd_or_even: #FoPropertyOddOrEven object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyOddOrEven.
 **/
static void
_init (FoPropertyOddOrEven *odd_or_even)
{
  FO_PROPERTY (odd_or_even)->value =
    g_object_ref (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_ANY));
}

/**
 * _class_init:
 * @klass: #FoPropertyOddOrEvenClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyOddOrEvenClass.
 **/
static void
_class_init (FoPropertyOddOrEvenClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);


  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    _resolve_enum;
  property_class->validate =
    _validate;
  property_class->get_initial =
    fo_property_odd_or_even_get_initial;
}


/**
 * fo_property_odd_or_even_new:
 * 
 * Creates a new #FoPropertyOddOrEven initialized to default value.
 * 
 * Return value: the new #FoPropertyOddOrEven.
 **/
FoProperty*
fo_property_odd_or_even_new (void)
{
  FoProperty* odd_or_even;

  odd_or_even =
    FO_PROPERTY (g_object_new (fo_property_odd_or_even_get_type (),
                               NULL));

  return odd_or_even;
}

/**
 * _resolve_enum:
 * @token:   Token from the XML attribute value to be evaluated as an
 *           enumeration token.
 * @context: #FoContext object from which to possibly inherit values.
 * @error:   Information about any error that has occurred.
 * 
 * Compare @token against the enumeration tokens that are valid for the
 * current FO property.  If @token is valid, returns either an #FoEnum datatype
 * representing the enumeration token or a different datatype representing
 * the enumeration token's resolved value.  If @token is not valid,
 * sets @error and returns NULL.
 * 
 * Return value: Resolved enumeration value or NULL.
 **/
static FoDatatype *
_resolve_enum (const gchar *token,
               FoContext   *context,
               GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "odd") == 0) ||
      (strcmp (token, "even") == 0) ||
      (strcmp (token, "any") == 0))
    {
      return g_object_ref (fo_enum_factory_get_enum_by_nick (token));
    }
  else
    {
      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_ENUMERATION_TOKEN,
		   _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		   class_name,
		   token);
      return NULL;
    }
}

/**
 * _validate:
 * @datatype: #FoDatatype to be validated against allowed datatypes and
 *            values for current property.
 * @context:  #FoContext object from which to possibly inherit values.
 * @error:    Information about any error that has occurred.
 * 
 * Validates @datatype against allowed values.  Returns @datatype, a
 * replacement datatype value, or NULL if validation failed.
 * 
 * Return value: Valid datatype value or NULL.
 **/
FoDatatype*
_validate (FoDatatype *datatype,
           FoContext  *context,
           GError    **error)
{
  FoDatatype *new_datatype;
  GError     *tmp_error = NULL;
  gchar      *token;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_ENUM (datatype))
    {
      FoEnumEnum value = fo_enum_get_value (datatype);

      if ((value == FO_ENUM_ENUM_ODD) ||
          (value == FO_ENUM_ENUM_EVEN) ||
          (value == FO_ENUM_ENUM_ANY))
	{
	  return datatype;
	}
      else
	{
	  gchar *datatype_sprintf = fo_object_sprintf (datatype);

	  g_set_error (error,
		       FO_FO_ERROR,
		       FO_FO_ERROR_ENUMERATION_TOKEN,
		       _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		       class_name,
		       datatype_sprintf,
		       g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

	  g_object_unref (datatype);

	  g_free (datatype_sprintf);

	  return NULL;
	}
    }
  else if (FO_IS_STRING (datatype))
    {
      token = fo_string_get_value (datatype);

      new_datatype =
        _resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        _resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else
    {
      gchar *datatype_sprintf = fo_object_sprintf (datatype);

      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_DATATYPE,
		   _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE]),
		   class_name,
		   datatype_sprintf,
		   g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

      g_object_unref (datatype);

      g_free (datatype_sprintf);

      return NULL;
    }
}

/**
 * fo_property_odd_or_even_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_odd_or_even_get_initial (void)
{
  static FoProperty *odd_or_even = NULL;

  if (odd_or_even == NULL)
    {
      odd_or_even =
	fo_property_odd_or_even_new ();
    }

  return odd_or_even;
}
