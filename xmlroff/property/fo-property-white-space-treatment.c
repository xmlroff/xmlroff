/* Fo
 * fo-property-white-space-treatment.c: 'white-space-treatment' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-property-white-space-treatment.c,v 1.3 2006/03/22 23:31:29 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-white-space-treatment.h"

/* white-space-treatment */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* ignore | preserve | ignore-if-before-linefeed | ignore-if-after-linefeed | ignore-if-surrounding-linefeed | inherit */
/* Initial value: ignore-if-surrounding-linefeed */

struct _FoPropertyWhiteSpaceTreatment
{
  FoProperty parent_instance;
};

struct _FoPropertyWhiteSpaceTreatmentClass
{
  FoPropertyClass parent_class;
};

static void fo_property_white_space_treatment_init         (FoPropertyWhiteSpaceTreatment      *property_white_space_treatment);
static void fo_property_white_space_treatment_class_init   (FoPropertyWhiteSpaceTreatmentClass *klass);
static void fo_property_white_space_treatment_finalize     (GObject       *object);

static FoDatatype * fo_property_white_space_treatment_resolve_enum (const gchar *token,
                                                                    FoContext   *context,
                                                                    GError     **error);
static FoDatatype * fo_property_white_space_treatment_validate (FoDatatype *datatype,
                                                                FoContext  *context,
                                                                GError    **error);

static const gchar class_name[] = "white-space-treatment";
static gpointer parent_class;

/**
 * fo_property_white_space_treatment_get_type:
 * 
 * Register the #FoPropertyWhiteSpaceTreatment type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyWhiteSpaceTreatment.
 **/
GType
fo_property_white_space_treatment_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyWhiteSpaceTreatmentClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_white_space_treatment_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyWhiteSpaceTreatment),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_white_space_treatment_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_white_space_treatment_init:
 * @white_space_treatment: #FoPropertyWhiteSpaceTreatment object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyWhiteSpaceTreatment.
 **/
void
fo_property_white_space_treatment_init (FoPropertyWhiteSpaceTreatment *white_space_treatment)
{
  FO_PROPERTY (white_space_treatment)->value =
    g_object_ref (fo_enum_get_enum_by_nick ("ignore-if-surrounding-linefeed"));
}

/**
 * fo_property_white_space_treatment_class_init:
 * @klass: #FoPropertyWhiteSpaceTreatmentClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyWhiteSpaceTreatmentClass.
 **/
void
fo_property_white_space_treatment_class_init (FoPropertyWhiteSpaceTreatmentClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_white_space_treatment_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_white_space_treatment_resolve_enum;
  property_class->validate =
    fo_property_white_space_treatment_validate;
  property_class->get_initial =
    fo_property_white_space_treatment_get_initial;
}

/**
 * fo_property_white_space_treatment_finalize:
 * @object: #FoPropertyWhiteSpaceTreatment object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyWhiteSpaceTreatment.
 **/
void
fo_property_white_space_treatment_finalize (GObject *object)
{
  FoPropertyWhiteSpaceTreatment *white_space_treatment;

  white_space_treatment = FO_PROPERTY_WHITE_SPACE_TREATMENT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_white_space_treatment_new:
 * 
 * Creates a new #FoPropertyWhiteSpaceTreatment initialized to default value.
 * 
 * Return value: the new #FoPropertyWhiteSpaceTreatment.
 **/
FoProperty*
fo_property_white_space_treatment_new (void)
{
  FoProperty* white_space_treatment;

  white_space_treatment =
    FO_PROPERTY (g_object_new (fo_property_white_space_treatment_get_type (),
                               NULL));

  return white_space_treatment;
}

/**
 * fo_property_white_space_treatment_resolve_enum:
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
fo_property_white_space_treatment_resolve_enum (const gchar *token,
                                                FoContext   *context,
                                                GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "ignore") == 0) ||
      (strcmp (token, "preserve") == 0) ||
      (strcmp (token, "ignore-if-before-linefeed") == 0) ||
      (strcmp (token, "ignore-if-after-linefeed") == 0) ||
      (strcmp (token, "ignore-if-surrounding-linefeed") == 0))
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
 * fo_property_white_space_treatment_validate:
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
fo_property_white_space_treatment_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_IGNORE) ||
          (value == FO_ENUM_ENUM_PRESERVE) ||
          (value == FO_ENUM_ENUM_IGNORE_IF_BEFORE_LINEFEED) ||
          (value == FO_ENUM_ENUM_IGNORE_IF_AFTER_LINEFEED) ||
          (value == FO_ENUM_ENUM_IGNORE_IF_SURROUNDING_LINEFEED))
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
        fo_property_white_space_treatment_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_white_space_treatment_resolve_enum (token, context, &tmp_error);

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
 * fo_property_white_space_treatment_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_white_space_treatment_get_initial (void)
{
  static FoProperty *white_space_treatment = NULL;

  if (white_space_treatment == NULL)
    {
      white_space_treatment =
	fo_property_white_space_treatment_new ();
    }

  return white_space_treatment;
}
