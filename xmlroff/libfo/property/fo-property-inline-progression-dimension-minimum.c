/* Fo
 * fo-property-inline-progression-dimension-minimum.c: 'inline-progression-dimension-minimum' property
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
#include "property/fo-property-inline-progression-dimension-minimum.h"
#include "property/fo-property-util.h"

/* inline-progression-dimension-minimum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | <length> */
/* Initial value: auto */

struct _FoPropertyInlineProgressionDimensionMinimum
{
  FoProperty parent_instance;
};

struct _FoPropertyInlineProgressionDimensionMinimumClass
{
  FoPropertyClass parent_class;
};

static void fo_property_inline_progression_dimension_minimum_init         (FoPropertyInlineProgressionDimensionMinimum      *property_inline_progression_dimension_minimum);
static void fo_property_inline_progression_dimension_minimum_class_init   (FoPropertyInlineProgressionDimensionMinimumClass *klass);
static void fo_property_inline_progression_dimension_minimum_finalize     (GObject       *object);

static FoDatatype* fo_property_inline_progression_dimension_minimum_validate (FoDatatype *datatype,
                                                                              FoContext  *context,
                                                                              GError    **error);

static const gchar class_name[] = "FoPropertyInlineProgressionDimensionMinimum";
static gpointer parent_class;

/**
 * fo_property_inline_progression_dimension_minimum_get_type:
 * 
 * Register the #FoPropertyInlineProgressionDimensionMinimum type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyInlineProgressionDimensionMinimum.
 **/
GType
fo_property_inline_progression_dimension_minimum_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyInlineProgressionDimensionMinimumClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_inline_progression_dimension_minimum_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyInlineProgressionDimensionMinimum),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_inline_progression_dimension_minimum_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_inline_progression_dimension_minimum_init:
 * @inline_progression_dimension_minimum: #FoPropertyInlineProgressionDimensionMinimum object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyInlineProgressionDimensionMinimum.
 **/
void
fo_property_inline_progression_dimension_minimum_init (FoPropertyInlineProgressionDimensionMinimum *inline_progression_dimension_minimum)
{
  FO_PROPERTY (inline_progression_dimension_minimum)->value =
    g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_property_inline_progression_dimension_minimum_class_init:
 * @klass: #FoPropertyInlineProgressionDimensionMinimumClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyInlineProgressionDimensionMinimumClass.
 **/
void
fo_property_inline_progression_dimension_minimum_class_init (FoPropertyInlineProgressionDimensionMinimumClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_inline_progression_dimension_minimum_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_auto_enum;
  property_class->validate =
    fo_property_inline_progression_dimension_minimum_validate;
  property_class->get_initial =
    fo_property_inline_progression_dimension_minimum_get_initial;
}

/**
 * fo_property_inline_progression_dimension_minimum_finalize:
 * @object: #FoPropertyInlineProgressionDimensionMinimum object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyInlineProgressionDimensionMinimum.
 **/
void
fo_property_inline_progression_dimension_minimum_finalize (GObject *object)
{
  FoPropertyInlineProgressionDimensionMinimum *inline_progression_dimension_minimum;

  inline_progression_dimension_minimum = FO_PROPERTY_INLINE_PROGRESSION_DIMENSION_MINIMUM (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_inline_progression_dimension_minimum_new:
 * 
 * Creates a new #FoPropertyInlineProgressionDimensionMinimum initialized to default value.
 * 
 * Return value: the new #FoPropertyInlineProgressionDimensionMinimum.
 **/
FoProperty*
fo_property_inline_progression_dimension_minimum_new (void)
{
  FoProperty* inline_progression_dimension_minimum;

  inline_progression_dimension_minimum =
    FO_PROPERTY (g_object_new (fo_property_inline_progression_dimension_minimum_get_type (),
                               NULL));

  return inline_progression_dimension_minimum;
}

/**
 * fo_property_inline_progression_dimension_minimum_validate:
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
fo_property_inline_progression_dimension_minimum_validate (FoDatatype *datatype,
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
        fo_property_util_resolve_auto_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_util_resolve_auto_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_LENGTH (datatype))
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
 * fo_property_inline_progression_dimension_minimum_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_inline_progression_dimension_minimum_get_initial (void)
{
  static FoProperty *inline_progression_dimension_minimum = NULL;

  if (inline_progression_dimension_minimum == NULL)
    {
      inline_progression_dimension_minimum =
	fo_property_inline_progression_dimension_minimum_new ();
    }

  return inline_progression_dimension_minimum;
}
