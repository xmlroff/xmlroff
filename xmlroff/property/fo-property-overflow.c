/* Fo
 * fo-property-overflow.c: 'overflow' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-overflow.c,v 1.5 2005/11/04 13:54:11 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-overflow.h"

/* overflow */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* visible | hidden | scroll | error-if-overflow | auto | inherit */
/* Initial value: auto */

struct _FoPropertyOverflow
{
  FoProperty parent_instance;
};

struct _FoPropertyOverflowClass
{
  FoPropertyClass parent_class;
};

static void fo_property_overflow_init         (FoPropertyOverflow      *property_overflow);
static void fo_property_overflow_class_init   (FoPropertyOverflowClass *klass);
static void fo_property_overflow_finalize     (GObject       *object);

static FoDatatype * fo_property_overflow_resolve_enum (const gchar *token,
                                                        FoContext   *context,
                                                        GError     **error);
static FoDatatype * fo_property_overflow_validate (FoDatatype *datatype,
                                                   FoContext  *context,
                                                   GError    **error);

static const gchar class_name[] = "overflow";
static gpointer parent_class;

/**
 * fo_property_overflow_get_type:
 * 
 * Register the #FoPropertyOverflow type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyOverflow.
 **/
GType
fo_property_overflow_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyOverflowClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_overflow_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyOverflow),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_overflow_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_overflow_init:
 * @overflow: #FoPropertyOverflow object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyOverflow.
 **/
void
fo_property_overflow_init (FoPropertyOverflow *overflow)
{
  FO_PROPERTY (overflow)->value =
    g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_property_overflow_class_init:
 * @klass: #FoPropertyOverflowClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyOverflowClass.
 **/
void
fo_property_overflow_class_init (FoPropertyOverflowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_overflow_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_overflow_resolve_enum;
  property_class->validate =
    fo_property_overflow_validate;
  property_class->get_initial =
    fo_property_overflow_get_initial;
}

/**
 * fo_property_overflow_finalize:
 * @object: #FoPropertyOverflow object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyOverflow.
 **/
void
fo_property_overflow_finalize (GObject *object)
{
  FoPropertyOverflow *overflow;

  overflow = FO_PROPERTY_OVERFLOW (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_overflow_new:
 * 
 * Creates a new #FoPropertyOverflow initialized to default value.
 * 
 * Return value: the new #FoPropertyOverflow.
 **/
FoProperty*
fo_property_overflow_new (void)
{
  FoProperty* overflow;

  overflow =
    FO_PROPERTY (g_object_new (fo_property_overflow_get_type (),
                               NULL));

  return overflow;
}

/**
 * fo_property_overflow_resolve_enum:
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
FoDatatype*
fo_property_overflow_resolve_enum (const gchar *token,
                                   FoContext   *context,
                                   GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "visible") == 0) ||
      (strcmp (token, "hidden") == 0) ||
      (strcmp (token, "scroll") == 0) ||
      (strcmp (token, "error-if-overflow") == 0) ||
      (strcmp (token, "auto") == 0))
    {
      return g_object_ref (fo_enum_get_enum_by_nick (token));
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
 * fo_property_overflow_validate:
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
fo_property_overflow_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_VISIBLE) ||
          (value == FO_ENUM_ENUM_HIDDEN) ||
          (value == FO_ENUM_ENUM_SCROLL) ||
          (value == FO_ENUM_ENUM_ERROR_IF_OVERFLOW) ||
          (value == FO_ENUM_ENUM_AUTO))
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
        fo_property_overflow_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_overflow_resolve_enum (token, context, &tmp_error);

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
 * fo_property_overflow_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_overflow_get_initial (void)
{
  static FoProperty *overflow = NULL;

  if (overflow == NULL)
    {
      overflow =
	fo_property_overflow_new ();
    }

  return overflow;
}
