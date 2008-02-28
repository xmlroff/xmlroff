/* Fo
 * fo-property-font-style.c: 'font-style' property
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
#include "property/fo-property-text-property.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-style.h"

/* Inherited: TRUE */
/* Shorthand: FALSE */
/* font-style */
/* normal | italic | oblique | backslant | inherit */
GType
fo_enum_font_style_get_type (void)
{
  static GType etype = 0;
  if (etype == 0)
    {
      static const GEnumValue values[] = {
        { FO_ENUM_FONT_STYLE_NORMAL, "FO_ENUM_FONT_STYLE_NORMAL", "normal" },
        { FO_ENUM_FONT_STYLE_ITALIC, "FO_ENUM_FONT_STYLE_ITALIC", "italic" },
        { FO_ENUM_FONT_STYLE_OBLIQUE, "FO_ENUM_FONT_STYLE_OBLIQUE", "oblique" },
        { FO_ENUM_FONT_STYLE_BACKSLANT, "FO_ENUM_FONT_STYLE_BACKSLANT", "backslant" },
        { 0, NULL, NULL }
      };
      etype = g_enum_register_static ("FoEnumFontStyle", values);
    }
  return etype;
}

struct _FoPropertyFontStyle
{
  FoProperty parent_instance;
};

struct _FoPropertyFontStyleClass
{
  FoPropertyClass parent_class;
};

static void fo_property_font_style_init         (FoPropertyFontStyle      *property_font_style);
static void fo_property_font_style_base_init   (FoPropertyFontStyleClass *klass);
static void fo_property_font_style_base_finalize   (FoPropertyFontStyleClass *klass);
static void fo_property_font_style_class_init   (FoPropertyFontStyleClass *klass);
static void fo_property_font_style_finalize     (GObject       *object);
static void fo_property_font_style_text_property_init (FoPropertyTextPropertyIface *iface);

static FoDatatype* fo_property_font_style_resolve_enum (const gchar *token,
                                                        FoContext   *context,
                                                        GError     **error);
static FoDatatype* fo_property_font_style_validate (FoDatatype *datatype,
                                                    FoContext  *context,
                                                    GError    **error);
static PangoAttribute * fo_property_font_style_new_attr (FoProperty *property);

static const gchar class_name[] = "font-style";
static gpointer parent_class;
static FoDatatype *enum_normal;
static FoDatatype *enum_italic;
static FoDatatype *enum_oblique;
static FoDatatype *enum_backslant;

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
        (GBaseInitFunc) fo_property_font_style_base_init,
        (GBaseFinalizeFunc) fo_property_font_style_base_finalize,
        (GClassInitFunc) fo_property_font_style_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyFontStyle),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_font_style_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_font_style_text_property_init, /* interface_init */
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
 * fo_property_font_style_init:
 * @font_style: #FoPropertyFontStyle object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyFontStyle.
 **/
void
fo_property_font_style_init (FoPropertyFontStyle *font_style)
{
  FO_PROPERTY (font_style)->value =
    g_object_ref (enum_normal);
}

/**
 * fo_property_font_style_base_init:
 * @klass: #FoPropertyFontStyleClass object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPropertyFontStyleClass.
 **/
void
fo_property_font_style_base_init (FoPropertyFontStyleClass *klass G_GNUC_UNUSED)
{
  enum_normal =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STYLE),
                  "value",
                  FO_ENUM_FONT_STYLE_NORMAL,
                  NULL);
  enum_italic =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STYLE),
                  "value",
                  FO_ENUM_FONT_STYLE_ITALIC,
                  NULL);
  enum_oblique =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STYLE),
                  "value",
                  FO_ENUM_FONT_STYLE_OBLIQUE,
                  NULL);
  enum_backslant =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STYLE),
                  "value",
                  FO_ENUM_FONT_STYLE_BACKSLANT,
                  NULL);
}

/**
 * fo_property_font_style_base_finalize:
 * @klass: #FoPropertyFontStyleClass object to finalise.
 * 
 * Implements #GBaseFinalizeFunc for #FoPropertyFontStyleClass.
 **/
void
fo_property_font_style_base_finalize (FoPropertyFontStyleClass *klass G_GNUC_UNUSED)
{
  g_object_unref (enum_normal);
  g_object_unref (enum_italic);
  g_object_unref (enum_oblique);
  g_object_unref (enum_backslant);
}

/**
 * fo_property_font_style_class_init:
 * @klass: #FoPropertyFontStyleClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyFontStyleClass.
 **/
void
fo_property_font_style_class_init (FoPropertyFontStyleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_font_style_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_font_style_resolve_enum;
  property_class->validate =
    fo_property_font_style_validate;
  property_class->get_initial =
    fo_property_font_style_get_initial;
}

/**
 * fo_property_font_style_finalize:
 * @object: #FoPropertyFontStyle object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyFontStyle.
 **/
void
fo_property_font_style_finalize (GObject *object)
{
  FoPropertyFontStyle *font_style;

  font_style = FO_PROPERTY_FONT_STYLE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_font_style_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class
 **/
void
fo_property_font_style_text_property_init (FoPropertyTextPropertyIface *iface)
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
 * fo_property_font_style_resolve_enum:
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
fo_property_font_style_resolve_enum (const gchar *token,
                                     FoContext   *context,
                                     GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "normal") == 0)
    {
      return g_object_ref (enum_normal);
    }
  else if (strcmp (token, "italic") == 0)
    {
      return g_object_ref (enum_italic);
    }
  else if (strcmp (token, "oblique") == 0)
    {
      return g_object_ref (enum_oblique);
    }
  else if (strcmp (token, "backslant") == 0)
    {
      return g_object_ref (enum_backslant);
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
 * fo_property_font_style_validate:
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
fo_property_font_style_validate (FoDatatype *datatype,
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
      if ((G_ENUM_CLASS_TYPE (fo_enum_get_enum_class (datatype))
           == FO_TYPE_ENUM_FONT_STYLE) &&
	  (g_enum_get_value (fo_enum_get_enum_class (datatype),
			     fo_enum_get_value (datatype)) != NULL))
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
  else if (FO_IS_STRING (datatype))
    {
      token = fo_string_get_value (datatype);

      new_datatype =
        fo_property_font_style_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      if (tmp_error != NULL)
	{
	  g_propagate_error (error, tmp_error);
	  return NULL;
	}

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_font_style_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      if (tmp_error != NULL)
	{
	  g_propagate_error (error, tmp_error);
	  return NULL;
	}

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
      font_style = fo_property_font_style_new ();
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
