/* Fo
 * fo-property-block-progression-dimension.c: 'block-progression-dimension' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-block-progression-dimension.c,v 1.5 2004/05/02 22:52:19 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-block-progression-dimension.h"

/* block-progression-dimension */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | <length> | <percentage> | <length-range> | inherit */
/* Initial value: auto */

struct _FoPropertyBlockProgressionDimension
{
  FoProperty parent_instance;
};

struct _FoPropertyBlockProgressionDimensionClass
{
  FoPropertyClass parent_class;
};

static void fo_property_block_progression_dimension_init         (FoPropertyBlockProgressionDimension      *property_block_progression_dimension);
static void fo_property_block_progression_dimension_class_init   (FoPropertyBlockProgressionDimensionClass *klass);
static void fo_property_block_progression_dimension_finalize     (GObject       *object);

static FoDatatype* fo_property_block_progression_dimension_resolve_enum (const gchar *token,
                                                                         FoContext   *context,
                                                                         GError     **error);
static FoDatatype* fo_property_block_progression_dimension_validate (FoDatatype *datatype,
                                                                     FoContext  *context,
                                                                     GError    **error);

static const gchar class_name[] = "block-progression-dimension";
static gpointer parent_class;

/**
 * fo_property_block_progression_dimension_get_type:
 * 
 * Register the #FoPropertyBlockProgressionDimension type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBlockProgressionDimension.
 **/
GType
fo_property_block_progression_dimension_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBlockProgressionDimensionClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_block_progression_dimension_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBlockProgressionDimension),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_block_progression_dimension_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_block_progression_dimension_init:
 * @block_progression_dimension: #FoPropertyBlockProgressionDimension object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBlockProgressionDimension.
 **/
void
fo_property_block_progression_dimension_init (FoPropertyBlockProgressionDimension *block_progression_dimension)
{
  FO_PROPERTY (block_progression_dimension)->value =
    g_object_ref (fo_length_range_new_auto ());
}

/**
 * fo_property_block_progression_dimension_class_init:
 * @klass: #FoPropertyBlockProgressionDimensionClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBlockProgressionDimensionClass.
 **/
void
fo_property_block_progression_dimension_class_init (FoPropertyBlockProgressionDimensionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_block_progression_dimension_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_block_progression_dimension_resolve_enum;
  property_class->validate =
    fo_property_block_progression_dimension_validate;
  property_class->get_initial =
    fo_property_block_progression_dimension_get_initial;
}

/**
 * fo_property_block_progression_dimension_finalize:
 * @object: #FoPropertyBlockProgressionDimension object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBlockProgressionDimension.
 **/
void
fo_property_block_progression_dimension_finalize (GObject *object)
{
  FoPropertyBlockProgressionDimension *block_progression_dimension;

  block_progression_dimension = FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_block_progression_dimension_new:
 * 
 * Creates a new #FoPropertyBlockProgressionDimension initialized to default value.
 * 
 * Return value: the new #FoPropertyBlockProgressionDimension.
 **/
FoProperty*
fo_property_block_progression_dimension_new (void)
{
  FoProperty* block_progression_dimension;

  block_progression_dimension =
    FO_PROPERTY (g_object_new (fo_property_block_progression_dimension_get_type (),
                               NULL));

  return block_progression_dimension;
}

/**
 * fo_property_block_progression_dimension_resolve_enum:
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
fo_property_block_progression_dimension_resolve_enum (const gchar *token,
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
 * fo_property_block_progression_dimension_validate:
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
fo_property_block_progression_dimension_validate (FoDatatype *datatype,
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
        fo_property_block_progression_dimension_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_block_progression_dimension_resolve_enum (token, context, &tmp_error);

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
 * fo_property_block_progression_dimension_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_block_progression_dimension_get_initial (void)
{
  static FoProperty *block_progression_dimension = NULL;

  if (block_progression_dimension == NULL)
    {
      block_progression_dimension =
	fo_property_block_progression_dimension_new ();
    }

  return block_progression_dimension;
}
