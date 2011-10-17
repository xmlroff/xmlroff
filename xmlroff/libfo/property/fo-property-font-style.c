/* Fo
 * fo-property-font-style.c: 'font-style' property
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
#include "property/fo-property-text-property.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-style.h"

/**
 * SECTION:fo-property-font-style
 * @short_description: 'font-style' property
 *
 * Inherited: TRUE
 *
 * Shorthand: FALSE
 *
 * Value: normal | italic | oblique | backslant | inherit
 *
 * Initial value: normal
 *
 * Definition: <ulink url="http://www.w3.org/TR/xsl11/&num;font-style">http://www.w3.org/TR/xsl11/&num;font-style</ulink>
 */

struct _FoPropertyFontStyle
{
  FoProperty parent_instance;
};

struct _FoPropertyFontStyleClass
{
  FoPropertyClass parent_class;
};

static void _init         (FoPropertyFontStyle      *property_font_style);
static void _class_init   (FoPropertyFontStyleClass *klass);
static void _text_property_init (FoPropertyTextPropertyIface *iface);

static FoDatatype * _resolve_enum (const gchar *token,
                                   FoContext   *context,
                                   GError     **error);
static FoDatatype * _validate     (FoDatatype  *datatype,
                                   FoContext   *context,
                                   GError     **error);
static PangoAttribute * fo_property_font_style_new_attr (FoProperty *property);

static const gchar class_name[] = "font-style";
static gpointer parent_class;

/**
 * fo_property_font_style_get_type:
 * 
 * Register the #FoPropertyFontStyle type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyFontStyle.
 **/
GType
fo_property_font_style_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyFontStyleClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) _class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyFontStyle),
        0,              /* n_preallocs */
        (GInstanceInitFunc) _init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) _text_property_init, /* interface_init */
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
 * _init:
 * @font_style: #FoPropertyFontStyle object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyFontStyle.
 **/
static void
_init (FoPropertyFontStyle *font_style)
{
  FO_PROPERTY (font_style)->value =
    g_object_ref (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_NORMAL));
}

/**
 * _class_init:
 * @klass: #FoPropertyFontStyleClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyFontStyleClass.
 **/
static void
_class_init (FoPropertyFontStyleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);


  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    _resolve_enum;
  property_class->validate =
    _validate;
  property_class->get_initial =
    fo_property_font_style_get_initial;
}

/**
 * _text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
static void
_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_font_style_new_attr;
}

/**
 * fo_property_font_style_new:
 * 
 * Creates a new #FoPropertyFontStyle initialized to default value.
 * 
 * Return value: the new #FoPropertyFontStyle.
 **/
FoProperty*
fo_property_font_style_new (void)
{
  FoProperty* font_style;

  font_style =
    FO_PROPERTY (g_object_new (fo_property_font_style_get_type (),
                               NULL));

  return font_style;
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

  if ((strcmp (token, "normal") == 0) ||
      (strcmp (token, "italic") == 0) ||
      (strcmp (token, "oblique") == 0) ||
      (strcmp (token, "backslant") == 0))
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

      if ((value == FO_ENUM_ENUM_NORMAL) ||
          (value == FO_ENUM_ENUM_ITALIC) ||
          (value == FO_ENUM_ENUM_OBLIQUE) ||
          (value == FO_ENUM_ENUM_BACKSLANT))
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
 * fo_property_font_style_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_font_style_get_initial (void)
{
  static FoProperty *font_style = NULL;

  if (font_style == NULL)
    {
      font_style =
	fo_property_font_style_new ();
    }

  return font_style;
}

/**
 * fo_property_font_style_to_pango_style:
 * @property: 'font-style' property
 * 
 * Get the #PangoStyle enumerated value corresponding to the value of
 * @property.
 * 
 * Return value: #PangoStyle value.
 **/
static PangoStyle
fo_property_font_style_to_pango_style (FoProperty *property)
{
  FoEnumEnum font_style;
  PangoStyle pango_font_style = PANGO_STYLE_NORMAL;

  /* No 'invalid' font style so default to 'normal' if fail */
  g_return_val_if_fail (FO_IS_PROPERTY_FONT_STYLE (property),
			pango_font_style);


  font_style = fo_enum_get_value (property->value);

  /* Pango doesn't support 'backslant' styles */
  if (font_style == FO_ENUM_FONT_STYLE_ITALIC)
    {
      pango_font_style = PANGO_STYLE_ITALIC;
    }
  else if (font_style == FO_ENUM_FONT_STYLE_OBLIQUE)
    {
      pango_font_style = PANGO_STYLE_OBLIQUE;
    }

  return pango_font_style;
}

/**
 * fo_property_font_style_new_attr:
 * @property: Property from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the current property.
 * 
 * Return value: New #PangoAttribute.
 **/
PangoAttribute*
fo_property_font_style_new_attr (FoProperty *property)
{
  PangoStyle pango_font_style;

  g_return_val_if_fail (FO_IS_PROPERTY_FONT_STYLE (property), NULL);

  pango_font_style =
    fo_property_font_style_to_pango_style (property);

  return pango_attr_style_new (pango_font_style);
}
