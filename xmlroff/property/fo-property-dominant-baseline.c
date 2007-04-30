/* Fo
 * fo-property-dominant-baseline.c: 'dominant-baseline' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-dominant-baseline.c,v 1.8 2005/05/03 22:46:48 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
/*
#include "property/fo-property-text-property.h"
*/
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-style.h"
#include "property/fo-property-dominant-baseline.h"

/* dominant-baseline */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | use-script | no-change | reset-size | ideographic | alphabetic | hanging | mathematical | central | middle | text-after-edge | text-before-edge | inherit */
/* Initial value: auto */

struct _FoPropertyDominantBaseline
{
  FoProperty parent_instance;
};

struct _FoPropertyDominantBaselineClass
{
  FoPropertyClass parent_class;
};

static void fo_property_dominant_baseline_init         (FoPropertyDominantBaseline      *property_dominant_baseline);
static void fo_property_dominant_baseline_class_init   (FoPropertyDominantBaselineClass *klass);
static void fo_property_dominant_baseline_finalize     (GObject       *object);

static FoDatatype* fo_property_dominant_baseline_resolve_enum (const gchar *token,
                                                               FoContext   *context,
                                                               GError     **error);
static FoDatatype* fo_property_dominant_baseline_validate (FoDatatype *datatype,
                                                           FoContext  *context,
                                                           GError    **error);
/*
static void fo_property_dominant_baseline_text_property_init (FoPropertyTextPropertyIface *iface);
PangoAttribute * fo_property_dominant_baseline_new_attr_from_context (FoProperty *property,
								      FoContext  *context);
*/
static const gchar class_name[] = "dominant-baseline";
static gpointer parent_class;

/**
 * fo_property_dominant_baseline_get_type:
 * 
 * Register the #FoPropertyDominantBaseline type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyDominantBaseline.
 **/
GType
fo_property_dominant_baseline_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyDominantBaselineClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_dominant_baseline_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyDominantBaseline),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_dominant_baseline_init,
	NULL		/* value_table */
      };
      /*
      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_dominant_baseline_text_property_init, / * interface_init * /
        NULL,
        NULL
      };
      */
      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
      /*
      g_type_add_interface_static (object_type,
                                   FO_TYPE_PROPERTY_TEXT_PROPERTY,
                                   &fo_property_text_property_info);
      */
    }

  return object_type;
}

/**
 * fo_property_dominant_baseline_init:
 * @dominant_baseline: #FoPropertyDominantBaseline object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyDominantBaseline.
 **/
void
fo_property_dominant_baseline_init (FoPropertyDominantBaseline *dominant_baseline)
{
  FO_PROPERTY (dominant_baseline)->value =
    g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_property_dominant_baseline_class_init:
 * @klass: #FoPropertyDominantBaselineClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyDominantBaselineClass.
 **/
void
fo_property_dominant_baseline_class_init (FoPropertyDominantBaselineClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_dominant_baseline_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_dominant_baseline_resolve_enum;
  property_class->validate =
    fo_property_dominant_baseline_validate;
  property_class->get_initial =
    fo_property_dominant_baseline_get_initial;
}

/**
 * fo_property_dominant_baseline_finalize:
 * @object: #FoPropertyDominantBaseline object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyDominantBaseline.
 **/
void
fo_property_dominant_baseline_finalize (GObject *object)
{
  FoPropertyDominantBaseline *dominant_baseline;

  dominant_baseline = FO_PROPERTY_DOMINANT_BASELINE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_dominant_baseline_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
/*
void
fo_property_dominant_baseline_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr_from_context = fo_property_dominant_baseline_new_attr_from_context;
}
*/

/**
 * fo_property_dominant_baseline_new:
 * 
 * Creates a new #FoPropertyDominantBaseline initialized to default value.
 * 
 * Return value: the new #FoPropertyDominantBaseline.
 **/
FoProperty*
fo_property_dominant_baseline_new (void)
{
  FoProperty* dominant_baseline;

  dominant_baseline =
    FO_PROPERTY (g_object_new (fo_property_dominant_baseline_get_type (),
                               NULL));

  return dominant_baseline;
}

/**
 * fo_property_dominant_baseline_resolve_enum:
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
fo_property_dominant_baseline_resolve_enum (const gchar *token,
                                            FoContext   *context,
                                            GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "auto") == 0) ||
      (strcmp (token, "use-script") == 0) ||
      (strcmp (token, "no-change") == 0) ||
      (strcmp (token, "reset-size") == 0) ||
      (strcmp (token, "ideographic") == 0) ||
      (strcmp (token, "alphabetic") == 0) ||
      (strcmp (token, "hanging") == 0) ||
      (strcmp (token, "mathematical") == 0) ||
      (strcmp (token, "central") == 0) ||
      (strcmp (token, "middle") == 0) ||
      (strcmp (token, "text-after-edge") == 0) ||
      (strcmp (token, "text-before-edge") == 0))
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
 * fo_property_dominant_baseline_validate:
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
fo_property_dominant_baseline_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_AUTO) ||
          (value == FO_ENUM_ENUM_USE_SCRIPT) ||
          (value == FO_ENUM_ENUM_NO_CHANGE) ||
          (value == FO_ENUM_ENUM_RESET_SIZE) ||
          (value == FO_ENUM_ENUM_IDEOGRAPHIC) ||
          (value == FO_ENUM_ENUM_ALPHABETIC) ||
          (value == FO_ENUM_ENUM_HANGING) ||
          (value == FO_ENUM_ENUM_MATHEMATICAL) ||
          (value == FO_ENUM_ENUM_CENTRAL) ||
          (value == FO_ENUM_ENUM_MIDDLE) ||
          (value == FO_ENUM_ENUM_TEXT_AFTER_EDGE) ||
          (value == FO_ENUM_ENUM_TEXT_BEFORE_EDGE))
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
        fo_property_dominant_baseline_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_dominant_baseline_resolve_enum (token, context, &tmp_error);

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
 * fo_property_dominant_baseline_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_dominant_baseline_get_initial (void)
{
  static FoProperty *dominant_baseline = NULL;

  if (dominant_baseline == NULL)
    {
      dominant_baseline =
	fo_property_dominant_baseline_new ();
    }

  return dominant_baseline;
}

/**
 * fo_property_dominant_baseline_to_pango_baseline:
 * @baseline: #FoEnumDominantBaseline to convert to #PangoBaseline value.
 * 
 * Gets the #PangoBaseline value corresponding to the value of
 * @baseline.
 * 
 * Return value: A #PangoBaseline value, which could be
 * #PANGO_BASELINE_INVALID.
 **/
/*
static PangoBaseline
fo_property_dominant_baseline_to_pango_baseline (FoEnumEnum baseline)
{
  switch (baseline)
    {
    case FO_ENUM_ENUM_AUTO:
      return PANGO_BASELINE_AUTO;
    case FO_ENUM_ENUM_RESET_SIZE:
      return PANGO_BASELINE_RESET_SIZE;
    case FO_ENUM_ENUM_USE_SCRIPT:
      return PANGO_BASELINE_USE_SCRIPT;
    case FO_ENUM_ENUM_IDEOGRAPHIC:
      return PANGO_BASELINE_IDEOGRAPHIC;
    case FO_ENUM_ENUM_ALPHABETIC:
      return PANGO_BASELINE_ALPHABETIC;
    case FO_ENUM_ENUM_HANGING:
      return PANGO_BASELINE_HANGING;
    case FO_ENUM_ENUM_MATHEMATICAL:
      return PANGO_BASELINE_MATHEMATICAL;
    case FO_ENUM_ENUM_CENTRAL:
      return PANGO_BASELINE_CENTRAL;
    case FO_ENUM_ENUM_MIDDLE:
      return PANGO_BASELINE_MIDDLE;
    case FO_ENUM_ENUM_TEXT_BEFORE_EDGE:
      return PANGO_BASELINE_TEXT_BEFORE_EDGE;
    case FO_ENUM_ENUM_TEXT_AFTER_EDGE:
      return PANGO_BASELINE_TEXT_AFTER_EDGE;
    default:
      return PANGO_BASELINE_INVALID;
    }
}

static PangoStyle
fo_font_style_to_pango_style (gint font_style)
{
  gint pango_font_style = PANGO_STYLE_NORMAL;

  / * Pango doesn't support 'backslant' styles * /
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
*/

/**
 * fo_property_dominant_baseline_new_attr_from_context:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * @context:  #FoContext from which to take additional property values.
 * 
 * Makes a new #PangoAttribute representing the value of @property.
 * 
 * Return value: New #PangoAttribute for @property.
 **/
/*
PangoAttribute*
fo_property_dominant_baseline_new_attr_from_context (FoProperty *property,
						     FoContext  *context)
{
  PangoFontDescription *font_desc = NULL;
  FoEnumEnum dominant_baseline;

  g_return_val_if_fail (FO_IS_PROPERTY_DOMINANT_BASELINE (property), NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);

  dominant_baseline =
    fo_enum_get_value (fo_property_get_value (property));

  if (dominant_baseline != FO_ENUM_ENUM_RESET_SIZE)
    {
      PangoBaseline pango_dominant_baseline =
	fo_property_dominant_baseline_to_pango_baseline (dominant_baseline);
  
      font_desc = pango_font_description_new ();

      gchar *font_family = fo_string_get_value (fo_property_get_value (fo_context_get_font_family (context)));
      pango_font_description_set_family (font_desc, font_family);
      g_free (font_family);

      pango_font_description_set_size (font_desc,
				       fo_length_get_value (fo_property_get_value (fo_context_get_font_size (context))) * PANGO_SCALE);
      pango_font_description_set_weight (font_desc,
					 fo_integer_get_value (fo_property_get_value (fo_context_get_font_weight (context))));
      pango_font_description_set_style (font_desc,
					fo_font_style_to_pango_style (fo_enum_get_value (fo_property_get_value (fo_context_get_font_style (context)))));
      pango_font_description_set_stretch (font_desc,
					  fo_enum_get_value (fo_property_get_value (fo_context_get_font_stretch (context))));
      pango_font_description_set_variant (font_desc,
					  fo_enum_get_value (fo_property_get_value (fo_context_get_font_variant (context))));

      PangoAttribute *pango_attr = pango_attr_dominant_baseline_new (pango_dominant_baseline,
								     font_desc);
      pango_font_description_free (font_desc);
      return pango_attr;
    }
  else
    {
      return pango_attr_db_reset_size_new (TRUE);
    }
}      
*/
