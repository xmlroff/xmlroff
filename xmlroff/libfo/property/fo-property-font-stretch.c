/* Fo
 * fo-property-font-stretch.c: 'font-stretch' property
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
#include "property/fo-property-text-property.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-stretch.h"

/* Inherited: TRUE */
/* Shorthand: FALSE */
/* font-stretch */
/* normal | wider | narrower | ultra-condensed | extra-condensed | condensed | semi-condensed | semi-expanded | expanded | extra-expanded | ultra-expanded | inherit */
/* Reordered to match Pango enumerations for common values */
GType
fo_enum_font_stretch_get_type (void)
{
  static GType etype = 0;
  if (etype == 0)
    {
      static const GEnumValue values[] = {
        { FO_ENUM_FONT_STRETCH_ULTRA_CONDENSED, "FO_ENUM_FONT_STRETCH_ULTRA_CONDENSED", "ultra-condensed" },
        { FO_ENUM_FONT_STRETCH_EXTRA_CONDENSED, "FO_ENUM_FONT_STRETCH_EXTRA_CONDENSED", "extra-condensed" },
        { FO_ENUM_FONT_STRETCH_CONDENSED, "FO_ENUM_FONT_STRETCH_CONDENSED", "condensed" },
        { FO_ENUM_FONT_STRETCH_SEMI_CONDENSED, "FO_ENUM_FONT_STRETCH_SEMI_CONDENSED", "semi-condensed" },
        { FO_ENUM_FONT_STRETCH_NORMAL, "FO_ENUM_FONT_STRETCH_NORMAL", "normal" },
        { FO_ENUM_FONT_STRETCH_SEMI_EXPANDED, "FO_ENUM_FONT_STRETCH_SEMI_EXPANDED", "semi-expanded" },
        { FO_ENUM_FONT_STRETCH_EXPANDED, "FO_ENUM_FONT_STRETCH_EXPANDED", "expanded" },
        { FO_ENUM_FONT_STRETCH_EXTRA_EXPANDED, "FO_ENUM_FONT_STRETCH_EXTRA_EXPANDED", "extra-expanded" },
        { FO_ENUM_FONT_STRETCH_ULTRA_EXPANDED, "FO_ENUM_FONT_STRETCH_ULTRA_EXPANDED", "ultra-expanded" },
        { FO_ENUM_FONT_STRETCH_WIDER, "FO_ENUM_FONT_STRETCH_WIDER", "wider" },
        { FO_ENUM_FONT_STRETCH_NARROWER, "FO_ENUM_FONT_STRETCH_NARROWER", "narrower" },
        { 0, NULL, NULL }
      };
      etype = g_enum_register_static ("FoEnumFontStretch", values);
    }
  return etype;
}

struct _FoPropertyFontStretch
{
  FoProperty parent_instance;
};

struct _FoPropertyFontStretchClass
{
  FoPropertyClass parent_class;
};

static void fo_property_font_stretch_init         (FoPropertyFontStretch      *property_font_stretch);
static void fo_property_font_stretch_base_init   (FoPropertyFontStretchClass *klass);
static void fo_property_font_stretch_base_finalize   (FoPropertyFontStretchClass *klass);
static void fo_property_font_stretch_class_init   (FoPropertyFontStretchClass *klass);
static void fo_property_font_stretch_finalize     (GObject       *object);
static void fo_property_font_stretch_text_property_init (FoPropertyTextPropertyIface *iface);

static FoDatatype* fo_property_font_stretch_resolve_enum (const gchar *token,
                                                          FoContext   *context,
                                                          GError     **error);
static FoDatatype* fo_property_font_stretch_validate (FoDatatype *datatype,
                                                      FoContext  *context,
                                                      GError    **error);
static PangoAttribute * fo_property_font_stretch_new_attr (FoProperty *property);

static const gchar class_name[] = "font-stretch";
static gpointer parent_class;
static FoDatatype *enum_normal;
static FoDatatype *enum_wider;
static FoDatatype *enum_narrower;
static FoDatatype *enum_ultra_condensed;
static FoDatatype *enum_extra_condensed;
static FoDatatype *enum_condensed;
static FoDatatype *enum_semi_condensed;
static FoDatatype *enum_semi_expanded;
static FoDatatype *enum_expanded;
static FoDatatype *enum_extra_expanded;
static FoDatatype *enum_ultra_expanded;

/**
 * fo_property_font_stretch_get_type:
 * 
 * Register the #FoPropertyFontStretch type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyFontStretch.
 **/
GType
fo_property_font_stretch_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyFontStretchClass),
        (GBaseInitFunc) fo_property_font_stretch_base_init,
        (GBaseFinalizeFunc) fo_property_font_stretch_base_finalize,
        (GClassInitFunc) fo_property_font_stretch_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyFontStretch),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_font_stretch_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_font_stretch_text_property_init, /* interface_init */
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
 * fo_property_font_stretch_init:
 * @font_stretch: #FoPropertyFontStretch object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyFontStretch.
 **/
void
fo_property_font_stretch_init (FoPropertyFontStretch *font_stretch)
{
  FO_PROPERTY (font_stretch)->value =
    g_object_ref (enum_normal);
}

/**
 * fo_property_font_stretch_base_init:
 * @klass: #FoPropertyFontStretchClass object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPropertyFontStretchClass.
 **/
void
fo_property_font_stretch_base_init (FoPropertyFontStretchClass *klass G_GNUC_UNUSED)
{
  enum_normal =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_NORMAL,
                  NULL);
  enum_wider =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_WIDER,
                  NULL);
  enum_narrower =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_NARROWER,
                  NULL);
  enum_ultra_condensed =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_ULTRA_CONDENSED,
                  NULL);
  enum_extra_condensed =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_EXTRA_CONDENSED,
                  NULL);
  enum_condensed =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_CONDENSED,
                  NULL);
  enum_semi_condensed =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_SEMI_CONDENSED,
                  NULL);
  enum_semi_expanded =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_SEMI_EXPANDED,
                  NULL);
  enum_expanded =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_EXPANDED,
                  NULL);
  enum_extra_expanded =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_EXTRA_EXPANDED,
                  NULL);
  enum_ultra_expanded =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_FONT_STRETCH),
                  "value",
                  FO_ENUM_FONT_STRETCH_ULTRA_EXPANDED,
                  NULL);
}

/**
 * fo_property_font_stretch_base_finalize:
 * @klass: #FoPropertyFontStretchClass object to finalise.
 * 
 * Implements #GBaseFinalizeFunc for #FoPropertyFontStretchClass.
 **/
void
fo_property_font_stretch_base_finalize (FoPropertyFontStretchClass *klass G_GNUC_UNUSED)
{
  g_object_unref (enum_normal);
  g_object_unref (enum_wider);
  g_object_unref (enum_narrower);
  g_object_unref (enum_ultra_condensed);
  g_object_unref (enum_extra_condensed);
  g_object_unref (enum_condensed);
  g_object_unref (enum_semi_condensed);
  g_object_unref (enum_semi_expanded);
  g_object_unref (enum_expanded);
  g_object_unref (enum_extra_expanded);
  g_object_unref (enum_ultra_expanded);
}

/**
 * fo_property_font_stretch_class_init:
 * @klass: #FoPropertyFontStretchClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyFontStretchClass.
 **/
void
fo_property_font_stretch_class_init (FoPropertyFontStretchClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_font_stretch_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_font_stretch_resolve_enum;
  property_class->validate =
    fo_property_font_stretch_validate;
  property_class->get_initial =
    fo_property_font_stretch_get_initial;
}

/**
 * fo_property_font_stretch_finalize:
 * @object: #FoPropertyFontStretch object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyFontStretch.
 **/
void
fo_property_font_stretch_finalize (GObject *object)
{
  FoPropertyFontStretch *font_stretch;

  font_stretch = FO_PROPERTY_FONT_STRETCH (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_font_stretch_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class
 **/
void
fo_property_font_stretch_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_font_stretch_new_attr;
}


/**
 * fo_property_font_stretch_new:
 * 
 * Creates a new #FoPropertyFontStretch initialized to default value.
 * 
 * Return value: the new #FoPropertyFontStretch.
 **/
FoProperty*
fo_property_font_stretch_new (void)
{
  FoProperty* font_stretch;

  font_stretch =
    FO_PROPERTY (g_object_new (fo_property_font_stretch_get_type (),
                               NULL));

  return font_stretch;
}

/**
 * fo_property_font_stretch_resolve_enum:
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
fo_property_font_stretch_resolve_enum (const gchar *token,
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
  else if (strcmp (token, "wider") == 0)
    {
      return g_object_ref (enum_wider);
    }
  else if (strcmp (token, "narrower") == 0)
    {
      return g_object_ref (enum_narrower);
    }
  else if (strcmp (token, "ultra-condensed") == 0)
    {
      return g_object_ref (enum_ultra_condensed);
    }
  else if (strcmp (token, "extra-condensed") == 0)
    {
      return g_object_ref (enum_extra_condensed);
    }
  else if (strcmp (token, "condensed") == 0)
    {
      return g_object_ref (enum_condensed);
    }
  else if (strcmp (token, "semi-condensed") == 0)
    {
      return g_object_ref (enum_semi_condensed);
    }
  else if (strcmp (token, "semi-expanded") == 0)
    {
      return g_object_ref (enum_semi_expanded);
    }
  else if (strcmp (token, "expanded") == 0)
    {
      return g_object_ref (enum_expanded);
    }
  else if (strcmp (token, "extra-expanded") == 0)
    {
      return g_object_ref (enum_extra_expanded);
    }
  else if (strcmp (token, "ultra-expanded") == 0)
    {
      return g_object_ref (enum_ultra_expanded);
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
 * fo_property_font_stretch_validate:
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
fo_property_font_stretch_validate (FoDatatype *datatype,
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
           == FO_TYPE_ENUM_FONT_STRETCH) &&
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
        fo_property_font_stretch_resolve_enum (token, context, &tmp_error);

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
        fo_property_font_stretch_resolve_enum (token, context, &tmp_error);

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
 * fo_property_font_stretch_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_font_stretch_get_initial (void)
{
  static FoProperty *font_stretch = NULL;

  if (font_stretch == NULL)
    {
      font_stretch = fo_property_font_stretch_new ();
    }

  return font_stretch;
}

/**
 * fo_property_font_stretch_new_attr:
 * @property: Property from which to create a PangoAttribute
 * 
 * Makes a new PangoAttribute representing the current property
 * 
 * Return value: New PangoAttribute
 **/
PangoAttribute*
fo_property_font_stretch_new_attr (FoProperty *property)
{
  gint pango_font_stretch;

  g_return_val_if_fail (FO_IS_PROPERTY_FONT_STRETCH (property), NULL);

  pango_font_stretch =
    fo_enum_get_value (property->value);

  return pango_attr_stretch_new (pango_font_stretch);
}
