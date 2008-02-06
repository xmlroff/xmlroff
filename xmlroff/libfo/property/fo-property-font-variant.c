/* Fo
 * fo-property-font-variant.c: 'font-variant' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-variant.h"

/* font-variant */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* normal | small-caps | inherit */
/* Initial value: normal */

struct _FoPropertyFontVariant
{
  FoProperty parent_instance;
};

struct _FoPropertyFontVariantClass
{
  FoPropertyClass parent_class;
};

static void fo_property_font_variant_init         (FoPropertyFontVariant      *property_font_variant);
static void fo_property_font_variant_class_init   (FoPropertyFontVariantClass *klass);
static void fo_property_font_variant_finalize     (GObject       *object);
static void fo_property_font_variant_text_property_init (FoPropertyTextPropertyIface *iface);

static FoDatatype * fo_property_font_variant_resolve_enum (const gchar *token,
                                                           FoContext   *context,
                                                           GError     **error);
static FoDatatype * fo_property_font_variant_validate (FoDatatype *datatype,
                                                       FoContext  *context,
                                                       GError    **error);
static PangoAttribute * fo_property_font_variant_new_attr (FoProperty *property);

static const gchar class_name[] = "font-variant";
static gpointer parent_class;

/**
 * fo_property_font_variant_get_type:
 * 
 * Register the #FoPropertyFontVariant type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyFontVariant.
 **/
GType
fo_property_font_variant_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyFontVariantClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_font_variant_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyFontVariant),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_font_variant_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_font_variant_text_property_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);

      g_type_add_interface_static (object_type,
                                   FO_TYPE_PROPERTY_TEXT_PROPERTY,
                                   &fo_property_text_property_info);
    }

  return object_type;
}

/**
 * fo_property_font_variant_init:
 * @font_variant: #FoPropertyFontVariant object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyFontVariant.
 **/
void
fo_property_font_variant_init (FoPropertyFontVariant *font_variant)
{
  FO_PROPERTY (font_variant)->value =
    g_object_ref (fo_enum_get_enum_by_nick ("normal"));
}

/**
 * fo_property_font_variant_class_init:
 * @klass: #FoPropertyFontVariantClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyFontVariantClass.
 **/
void
fo_property_font_variant_class_init (FoPropertyFontVariantClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_font_variant_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_font_variant_resolve_enum;
  property_class->validate =
    fo_property_font_variant_validate;
  property_class->get_initial =
    fo_property_font_variant_get_initial;
}

/**
 * fo_property_font_variant_finalize:
 * @object: #FoPropertyFontVariant object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyFontVariant.
 **/
void
fo_property_font_variant_finalize (GObject *object)
{
  FoPropertyFontVariant *font_variant;

  font_variant = FO_PROPERTY_FONT_VARIANT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_font_variant_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
void
fo_property_font_variant_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_font_variant_new_attr;
}

/**
 * fo_property_font_variant_new:
 * 
 * Creates a new #FoPropertyFontVariant initialized to default value.
 * 
 * Return value: the new #FoPropertyFontVariant.
 **/
FoProperty*
fo_property_font_variant_new (void)
{
  FoProperty* font_variant;

  font_variant =
    FO_PROPERTY (g_object_new (fo_property_font_variant_get_type (),
                               NULL));

  return font_variant;
}

/**
 * fo_property_font_variant_resolve_enum:
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
fo_property_font_variant_resolve_enum (const gchar *token,
                                       FoContext   *context,
                                       GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "normal") == 0) ||
      (strcmp (token, "small-caps") == 0))
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
 * fo_property_font_variant_validate:
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
fo_property_font_variant_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_NORMAL) ||
          (value == FO_ENUM_ENUM_SMALL_CAPS))
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
        fo_property_font_variant_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_font_variant_resolve_enum (token, context, &tmp_error);

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
 * fo_property_font_variant_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_font_variant_get_initial (void)
{
  static FoProperty *font_variant = NULL;

  if (font_variant == NULL)
    {
      font_variant =
	fo_property_font_variant_new ();
    }

  return font_variant;
}

static PangoVariant
fo_property_font_variant_to_pango_variant (FoProperty *property)
{
  FoEnumEnum font_variant;
  PangoVariant pango_font_variant = PANGO_VARIANT_NORMAL;

  /* No 'invalid' font variant so default to 'normal' if fail */
  g_return_val_if_fail (FO_IS_PROPERTY_FONT_VARIANT (property),
			pango_font_variant);


  font_variant = fo_enum_get_value (property->value);

  if (font_variant == FO_ENUM_ENUM_SMALL_CAPS)
    {
      pango_font_variant = PANGO_VARIANT_SMALL_CAPS;
    }

  return pango_font_variant;
}

/**
 * fo_property_font_variant_new_attr:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the current property.
 * 
 * Return value: New #PangoAttribute.
 **/
PangoAttribute*
fo_property_font_variant_new_attr (FoProperty *property)
{
  PangoVariant pango_font_variant;

  g_return_val_if_fail (FO_IS_PROPERTY_FONT_VARIANT (property), NULL);

  pango_font_variant =
    fo_property_font_variant_to_pango_variant (property);

  return pango_attr_variant_new (pango_font_variant);
}
