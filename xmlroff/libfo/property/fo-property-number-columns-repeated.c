/* Fo
 * fo-property-number-columns-repeated.c: 'number-columns-repeated' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <math.h>
#include <string.h>
#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-number-columns-repeated.h"

/* Inherited: FALSE */
/* Shorthand: FALSE */
/* number-columns-repeated */
/* <number> */
/* NO ENUMERATED VALUE */


struct _FoPropertyNumberColumnsRepeated
{
  FoProperty parent_instance;
};

struct _FoPropertyNumberColumnsRepeatedClass
{
  FoPropertyClass parent_class;
};

static void fo_property_number_columns_repeated_init         (FoPropertyNumberColumnsRepeated      *property_number_columns_repeated);
static void fo_property_number_columns_repeated_class_init   (FoPropertyNumberColumnsRepeatedClass *klass);
static void fo_property_number_columns_repeated_finalize     (GObject       *object);

static FoDatatype* fo_property_number_columns_repeated_resolve_enum (const gchar *token,
                                                                     FoContext   *context,
                                                                     GError     **error);
static FoDatatype* fo_property_number_columns_repeated_validate (FoDatatype *datatype,
                                                                 FoContext  *context,
                                                                 GError    **error);

static const gchar class_name[] = "FoPropertyNumberColumnsRepeated";
static gpointer parent_class;

/**
 * fo_property_number_columns_repeated_get_type:
 * 
 * Register the #FoPropertyNumberColumnsRepeated type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyNumberColumnsRepeated.
 **/
GType
fo_property_number_columns_repeated_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyNumberColumnsRepeatedClass),
        NULL,           /* base_class_finalize */
        NULL,           /* base_class_finalize */
        (GClassInitFunc) fo_property_number_columns_repeated_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyNumberColumnsRepeated),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_number_columns_repeated_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_number_columns_repeated_init:
 * @number_columns_repeated: #FoPropertyNumberColumnsRepeated object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyNumberColumnsRepeated.
 **/
void
fo_property_number_columns_repeated_init (FoPropertyNumberColumnsRepeated *number_columns_repeated)
{
  FO_PROPERTY (number_columns_repeated)->value =
    g_object_ref (fo_integer_get_integer_one ());
}

/**
 * fo_property_number_columns_repeated_class_init:
 * @klass: #FoPropertyNumberColumnsRepeatedClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyNumberColumnsRepeatedClass.
 **/
void
fo_property_number_columns_repeated_class_init (FoPropertyNumberColumnsRepeatedClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_number_columns_repeated_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_number_columns_repeated_resolve_enum;
  property_class->validate =
    fo_property_number_columns_repeated_validate;
  property_class->get_initial =
    fo_property_number_columns_repeated_get_initial;
}

/**
 * fo_property_number_columns_repeated_finalize:
 * @object: #FoPropertyNumberColumnsRepeated object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyNumberColumnsRepeated.
 **/
void
fo_property_number_columns_repeated_finalize (GObject *object)
{
  FoPropertyNumberColumnsRepeated *number_columns_repeated;

  number_columns_repeated = FO_PROPERTY_NUMBER_COLUMNS_REPEATED (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_number_columns_repeated_new:
 * 
 * Creates a new #FoPropertyNumberColumnsRepeated initialized to default value.
 * 
 * Return value: the new #FoPropertyNumberColumnsRepeated.
 **/
FoProperty*
fo_property_number_columns_repeated_new (void)
{
  FoProperty* number_columns_repeated;

  number_columns_repeated =
    FO_PROPERTY (g_object_new (fo_property_number_columns_repeated_get_type (),
                               NULL));

  return number_columns_repeated;
}

/**
 * fo_property_number_columns_repeated_resolve_enum:
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
fo_property_number_columns_repeated_resolve_enum (const gchar *token,
                                                  FoContext   *context,
                                                  GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_ENUMERATION_TOKEN,
		   _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		   class_name,
		   token);
      return NULL;
}

/**
 * fo_property_number_columns_repeated_validate:
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
fo_property_number_columns_repeated_validate (FoDatatype *datatype,
                                              FoContext  *context,
                                              GError    **error)
{
  FoDatatype *new_datatype;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_NUMBER (datatype))
    {
      gfloat number_value = fo_number_get_value (datatype);
      gint integer_value = number_value + 0.5;

      g_object_unref (datatype);

      new_datatype = fo_integer_new_with_value (MAX (integer_value, 1));

      return new_datatype;
    }
  else if (FO_IS_INTEGER (datatype))
    {
      return datatype;
    }
  else
    {
      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_DATATYPE,
		   _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE]),
		   class_name,
		   fo_object_sprintf (datatype),
		   g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

      g_object_unref (datatype);

      return NULL;
    }
}

/**
 * fo_property_number_columns_repeated_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_number_columns_repeated_get_initial (void)
{
  static FoProperty *number_columns_repeated = NULL;

  if (number_columns_repeated == NULL)
    {
      number_columns_repeated = fo_property_number_columns_repeated_new ();
    }

  return number_columns_repeated;
}
