/* Fo
 * fo-property-region-name.c: 'region-name' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-region-name.c,v 1.4 2004/05/02 22:54:00 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-region-name.h"

/* region-name */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* xsl-region-body | xsl-region-start | xsl-region-end | xsl-region-before | xsl-region-after | xsl-before-float-separator | xsl-footnote-separator | <name> */
/* Initial value: see prose */

struct _FoPropertyRegionName
{
  FoProperty parent_instance;
};

struct _FoPropertyRegionNameClass
{
  FoPropertyClass parent_class;
};

static void fo_property_region_name_init         (FoPropertyRegionName      *property_region_name);
static void fo_property_region_name_class_init   (FoPropertyRegionNameClass *klass);
static void fo_property_region_name_finalize     (GObject       *object);

static FoDatatype* fo_property_region_name_resolve_enum (const gchar *token,
                                                         FoContext   *context,
                                                         GError     **error);
static FoDatatype* fo_property_region_name_validate (FoDatatype *datatype,
                                                     FoContext  *context,
                                                     GError    **error);

static const gchar class_name[] = "region-name";
static gpointer parent_class;

/**
 * fo_property_region_name_get_type:
 * 
 * Register the #FoPropertyRegionName type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyRegionName.
 **/
GType
fo_property_region_name_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyRegionNameClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_region_name_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyRegionName),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_region_name_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_region_name_init:
 * @region_name: #FoPropertyRegionName object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyRegionName.
 **/
void
fo_property_region_name_init (FoPropertyRegionName *region_name)
{
  FO_PROPERTY (region_name)->value =
    NULL;
}

/**
 * fo_property_region_name_class_init:
 * @klass: #FoPropertyRegionNameClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyRegionNameClass.
 **/
void
fo_property_region_name_class_init (FoPropertyRegionNameClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_region_name_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_region_name_resolve_enum;
  property_class->validate =
    fo_property_region_name_validate;
  property_class->get_initial =
    fo_property_region_name_get_initial;
}

/**
 * fo_property_region_name_finalize:
 * @object: #FoPropertyRegionName object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyRegionName.
 **/
void
fo_property_region_name_finalize (GObject *object)
{
  FoPropertyRegionName *region_name;

  region_name = FO_PROPERTY_REGION_NAME (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_region_name_new:
 * 
 * Creates a new #FoPropertyRegionName initialized to default value.
 * 
 * Return value: the new #FoPropertyRegionName.
 **/
FoProperty*
fo_property_region_name_new (void)
{
  FoProperty* region_name;

  region_name =
    FO_PROPERTY (g_object_new (fo_property_region_name_get_type (),
                               NULL));

  return region_name;
}

/**
 * fo_property_region_name_resolve_enum:
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
fo_property_region_name_resolve_enum (const gchar *token,
                                      FoContext   *context,
                                      GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "xsl-region-body") == 0) ||
      (strcmp (token, "xsl-region-start") == 0) ||
      (strcmp (token, "xsl-region-end") == 0) ||
      (strcmp (token, "xsl-region-before") == 0) ||
      (strcmp (token, "xsl-region-after") == 0) ||
      (strcmp (token, "xsl-before-float-separator") == 0) ||
      (strcmp (token, "xsl-footnote-separator") == 0))
    {
      return fo_name_new_with_value(token);
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
 * fo_property_region_name_validate:
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
fo_property_region_name_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_XSL_REGION_BODY) ||
          (value == FO_ENUM_ENUM_XSL_REGION_START) ||
          (value == FO_ENUM_ENUM_XSL_REGION_END) ||
          (value == FO_ENUM_ENUM_XSL_REGION_BEFORE) ||
          (value == FO_ENUM_ENUM_XSL_REGION_AFTER) ||
          (value == FO_ENUM_ENUM_XSL_BEFORE_FLOAT_SEPARATOR) ||
          (value == FO_ENUM_ENUM_XSL_FOOTNOTE_SEPARATOR))
	{
	  return fo_name_new_with_value(fo_enum_get_nick(datatype));
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
        fo_property_region_name_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
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
 * fo_property_region_name_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_region_name_get_initial (void)
{
  static FoProperty *region_name = NULL;

  if (region_name == NULL)
    {
      region_name =
	fo_property_region_name_new ();
    }

  return region_name;
}
