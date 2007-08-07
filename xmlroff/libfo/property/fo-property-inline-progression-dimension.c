/* Fo
 * fo-property-inline-progression-dimension.c: 'inline-progression-dimension' property
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
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-inline-progression-dimension.h"

/* inline-progression-dimension */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | <length> | <percentage> | <length-range> | inherit */
/* Initial value: auto */

struct _FoPropertyInlineProgressionDimension
{
  FoProperty parent_instance;
};

struct _FoPropertyInlineProgressionDimensionClass
{
  FoPropertyClass parent_class;
};

static void fo_property_inline_progression_dimension_init         (FoPropertyInlineProgressionDimension      *property_inline_progression_dimension);
static void fo_property_inline_progression_dimension_class_init   (FoPropertyInlineProgressionDimensionClass *klass);
static void fo_property_inline_progression_dimension_finalize     (GObject       *object);

static FoDatatype* fo_property_inline_progression_dimension_resolve_enum (const gchar *token,
                                                                          FoContext   *context,
                                                                          GError     **error);
static FoDatatype* fo_property_inline_progression_dimension_validate (FoDatatype *datatype,
                                                                      FoContext  *context,
                                                                      GError    **error);

static const gchar class_name[] = "inline-progression-dimension";
static gpointer parent_class;

/**
 * fo_property_inline_progression_dimension_get_type:
 * 
 * Register the #FoPropertyInlineProgressionDimension type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyInlineProgressionDimension.
 **/
GType
fo_property_inline_progression_dimension_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyInlineProgressionDimensionClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_inline_progression_dimension_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyInlineProgressionDimension),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_inline_progression_dimension_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_inline_progression_dimension_init:
 * @inline_progression_dimension: #FoPropertyInlineProgressionDimension object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyInlineProgressionDimension.
 **/
void
fo_property_inline_progression_dimension_init (FoPropertyInlineProgressionDimension *inline_progression_dimension)
{
  FO_PROPERTY (inline_progression_dimension)->value = fo_length_range_new_auto ();
}

/**
 * fo_property_inline_progression_dimension_class_init:
 * @klass: #FoPropertyInlineProgressionDimensionClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyInlineProgressionDimensionClass.
 **/
void
fo_property_inline_progression_dimension_class_init (FoPropertyInlineProgressionDimensionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_inline_progression_dimension_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_inline_progression_dimension_resolve_enum;
  property_class->validate =
    fo_property_inline_progression_dimension_validate;
  property_class->get_initial =
    fo_property_inline_progression_dimension_get_initial;
}

/**
 * fo_property_inline_progression_dimension_finalize:
 * @object: #FoPropertyInlineProgressionDimension object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyInlineProgressionDimension.
 **/
void
fo_property_inline_progression_dimension_finalize (GObject *object)
{
  FoPropertyInlineProgressionDimension *inline_progression_dimension;

  inline_progression_dimension = FO_PROPERTY_INLINE_PROGRESSION_DIMENSION (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_inline_progression_dimension_new:
 * 
 * Creates a new #FoPropertyInlineProgressionDimension initialized to default value.
 * 
 * Return value: the new #FoPropertyInlineProgressionDimension.
 **/
FoProperty*
fo_property_inline_progression_dimension_new (void)
{
  FoProperty* inline_progression_dimension;

  inline_progression_dimension =
    FO_PROPERTY (g_object_new (fo_property_inline_progression_dimension_get_type (),
                               NULL));

  return inline_progression_dimension;
}

/**
 * fo_property_inline_progression_dimension_resolve_enum:
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
fo_property_inline_progression_dimension_resolve_enum (const gchar *token,
                                                       FoContext   *context,
                                                       GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "auto") == 0)
    {
      return g_object_ref (fo_length_range_new_auto ());
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
 * fo_property_inline_progression_dimension_validate:
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
fo_property_inline_progression_dimension_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_AUTO))
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
        fo_property_inline_progression_dimension_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_inline_progression_dimension_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_LENGTH (datatype))
    {
      return datatype;
    }
  else if (FO_IS_PERCENTAGE (datatype))
    {
      return datatype;
    }
  else if (FO_IS_LENGTH_RANGE (datatype))
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
 * fo_property_inline_progression_dimension_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_inline_progression_dimension_get_initial (void)
{
  static FoProperty *inline_progression_dimension = NULL;

  if (inline_progression_dimension == NULL)
    {
      inline_progression_dimension =
	fo_property_inline_progression_dimension_new ();
    }

  return inline_progression_dimension;
}
