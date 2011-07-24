/* Fo
 * fo-property-initial-page-number.c: 'initial-page-number' property
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
#include "property/fo-property-initial-page-number.h"

/**
 * SECTION:fo-property-initial-page-number
 * @short_description: 'initial-page-number' property
 *
 * Inherited: FALSE
 *
 * Shorthand: FALSE
 *
 * Value: auto | auto-odd | auto-even | &lt;number> | inherit
 *
 * Initial value: auto
 *
 * Definition: <ulink url="http://www.w3.org/TR/xsl11/&num;initial-page-number">http://www.w3.org/TR/xsl11/&num;initial-page-number</ulink>
 */

struct _FoPropertyInitialPageNumber
{
  FoProperty parent_instance;
};

struct _FoPropertyInitialPageNumberClass
{
  FoPropertyClass parent_class;
};

static void _init         (FoPropertyInitialPageNumber      *property_initial_page_number);
static void _class_init   (FoPropertyInitialPageNumberClass *klass);

static FoDatatype * _resolve_enum (const gchar *token,
                                   FoContext   *context,
                                   GError     **error);
static FoDatatype * _validate     (FoDatatype  *datatype,
                                   FoContext   *context,
                                   GError     **error);

static const gchar class_name[] = "initial-page-number";
static gpointer parent_class;

/**
 * fo_property_initial_page_number_get_type:
 * 
 * Register the #FoPropertyInitialPageNumber type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyInitialPageNumber.
 **/
GType
fo_property_initial_page_number_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyInitialPageNumberClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) _class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyInitialPageNumber),
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
 * @initial_page_number: #FoPropertyInitialPageNumber object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyInitialPageNumber.
 **/
static void
_init (FoPropertyInitialPageNumber *initial_page_number)
{
  FO_PROPERTY (initial_page_number)->value =
    g_object_ref (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_AUTO));
}

/**
 * _class_init:
 * @klass: #FoPropertyInitialPageNumberClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyInitialPageNumberClass.
 **/
static void
_class_init (FoPropertyInitialPageNumberClass *klass)
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
    fo_property_initial_page_number_get_initial;
}


/**
 * fo_property_initial_page_number_new:
 * 
 * Creates a new #FoPropertyInitialPageNumber initialized to default value.
 * 
 * Return value: the new #FoPropertyInitialPageNumber.
 **/
FoProperty*
fo_property_initial_page_number_new (void)
{
  FoProperty* initial_page_number;

  initial_page_number =
    FO_PROPERTY (g_object_new (fo_property_initial_page_number_get_type (),
                               NULL));

  return initial_page_number;
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

  if ((strcmp (token, "auto") == 0) ||
      (strcmp (token, "auto-odd") == 0) ||
      (strcmp (token, "auto-even") == 0))
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

      if ((value == FO_ENUM_ENUM_AUTO) ||
          (value == FO_ENUM_ENUM_AUTO_ODD) ||
          (value == FO_ENUM_ENUM_AUTO_EVEN))
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
  else if (FO_IS_NUMBER (datatype))
    {
      return datatype;
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
 * fo_property_initial_page_number_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_initial_page_number_get_initial (void)
{
  static FoProperty *initial_page_number = NULL;

  if (initial_page_number == NULL)
    {
      initial_page_number =
	fo_property_initial_page_number_new ();
    }

  return initial_page_number;
}
