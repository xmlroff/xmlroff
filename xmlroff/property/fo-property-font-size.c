/* Fo
 * fo-property-font-size.c: 'font-size' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-font-size.c,v 1.6 2004/10/12 14:51:39 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-font-size.h"


/* font-size */
/* Enumerated font sizes derive from "medium" font size and font size step */
#ifndef FO_FONT_SIZE_STEP
#define FO_FONT_SIZE_STEP	1.2
#endif	/* !FO_FONT_SIZE_STEP */

#ifndef FO_FONT_SIZE_MEDIUM
#define FO_FONT_SIZE_MEDIUM	12.0
#endif	/* !FO_FONT_SIZE_MEDIUM */

#define FO_FONT_SIZE_SMALL	FO_FONT_SIZE_MEDIUM / FO_FONT_SIZE_STEP
#define FO_FONT_SIZE_X_SMALL	FO_FONT_SIZE_SMALL / FO_FONT_SIZE_STEP
#define FO_FONT_SIZE_XX_SMALL	FO_FONT_SIZE_X_SMALL / FO_FONT_SIZE_STEP

#define FO_FONT_SIZE_LARGE	FO_FONT_SIZE_MEDIUM * FO_FONT_SIZE_STEP
#define FO_FONT_SIZE_X_LARGE	FO_FONT_SIZE_LARGE * FO_FONT_SIZE_STEP
#define FO_FONT_SIZE_XX_LARGE	FO_FONT_SIZE_X_LARGE * FO_FONT_SIZE_STEP

/* font-size */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <absolute-size> | <relative-size> | <length> | <percentage> | inherit */
/* Initial value: medium */

struct _FoPropertyFontSize
{
  FoProperty parent_instance;
};

struct _FoPropertyFontSizeClass
{
  FoPropertyClass parent_class;
};

static void fo_property_font_size_init         (FoPropertyFontSize      *property_font_size);
static void fo_property_font_size_base_init   (FoPropertyFontSizeClass *klass);
static void fo_property_font_size_base_finalize   (FoPropertyFontSizeClass *klass);
static void fo_property_font_size_class_init   (FoPropertyFontSizeClass *klass);
static void fo_property_font_size_finalize     (GObject       *object);
static void fo_property_font_size_text_property_init (FoPropertyTextPropertyIface *iface);

static FoDatatype* fo_property_font_size_resolve_enum (const gchar *token,
                                                       FoContext   *context,
                                                       GError     **error);
static FoDatatype* fo_property_font_size_validate (FoDatatype *datatype,
                                                   FoContext  *context,
                                                   GError    **error);
static PangoAttribute * fo_property_font_size_new_attr (FoProperty *property);

static const gchar class_name[] = "font-size";
static gpointer parent_class;
static FoDatatype *xx_small;
static FoDatatype *x_small;
static FoDatatype *small;
static FoDatatype *medium;
static FoDatatype *large;
static FoDatatype *x_large;
static FoDatatype *xx_large;
static FoDatatype *size_step;

/**
 * fo_property_font_size_get_type:
 * 
 * Register the #FoPropertyFontSize type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyFontSize.
 **/
GType
fo_property_font_size_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyFontSizeClass),
        (GBaseInitFunc) fo_property_font_size_base_init,
        (GBaseFinalizeFunc) fo_property_font_size_base_finalize,
        (GClassInitFunc) fo_property_font_size_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyFontSize),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_font_size_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_font_size_text_property_init, /* interface_init */
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
 * fo_property_font_size_init:
 * @font_size: #FoPropertyFontSize object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyFontSize.
 **/
void
fo_property_font_size_init (FoPropertyFontSize *font_size)
{
  FO_PROPERTY (font_size)->value =
    g_object_ref (medium);
}

/**
 * fo_property_font_size_base_init:
 * @klass: #FoPropertyFontSizeClass object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPropertyFontSizeClass.
 **/
void
fo_property_font_size_base_init (FoPropertyFontSizeClass *klass)
{
  xx_small =
    fo_length_new_with_value (FO_FONT_SIZE_XX_SMALL);
  x_small =
    fo_length_new_with_value (FO_FONT_SIZE_X_SMALL);
  small =
    fo_length_new_with_value (FO_FONT_SIZE_SMALL);
  medium =
    fo_length_new_with_value (FO_FONT_SIZE_MEDIUM);
  large =
    fo_length_new_with_value (FO_FONT_SIZE_LARGE);
  x_large =
    fo_length_new_with_value (FO_FONT_SIZE_X_LARGE);
  xx_large =
    fo_length_new_with_value (FO_FONT_SIZE_XX_LARGE);
  size_step =
    g_object_new (FO_TYPE_NUMBER,
		  "value",
		  FO_FONT_SIZE_STEP,
		  NULL);
}

/**
 * fo_property_font_size_base_finalize:
 * @klass: #FoPropertyFontSizeClass object to finalise.
 * 
 * Implements #GBaseFinalizeFunc for #FoPropertyFontSizeClass.
 **/
void
fo_property_font_size_base_finalize (FoPropertyFontSizeClass *klass)
{
  g_object_unref (xx_small);
  g_object_unref (x_small);
  g_object_unref (small);
  g_object_unref (medium);
  g_object_unref (large);
  g_object_unref (x_large);
  g_object_unref (xx_large);
  g_object_unref (size_step);
}

/**
 * fo_property_font_size_class_init:
 * @klass: #FoPropertyFontSizeClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyFontSizeClass.
 **/
void
fo_property_font_size_class_init (FoPropertyFontSizeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_font_size_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_font_size_resolve_enum;
  property_class->validate =
    fo_property_font_size_validate;
  property_class->get_initial =
    fo_property_font_size_get_initial;
}

/**
 * fo_property_font_size_finalize:
 * @object: #FoPropertyFontSize object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyFontSize.
 **/
void
fo_property_font_size_finalize (GObject *object)
{
  FoPropertyFontSize *font_size;

  font_size = FO_PROPERTY_FONT_SIZE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_font_size_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
void
fo_property_font_size_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_font_size_new_attr;
}

/**
 * fo_property_font_size_new:
 * 
 * Creates a new #FoPropertyFontSize initialized to default value.
 * 
 * Return value: the new #FoPropertyFontSize.
 **/
FoProperty*
fo_property_font_size_new (void)
{
  FoProperty* font_size;

  font_size =
    FO_PROPERTY (g_object_new (fo_property_font_size_get_type (),
                               NULL));

  return font_size;
}

/**
 * fo_property_font_size_resolve_enum:
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
fo_property_font_size_resolve_enum (const gchar *token,
                                    FoContext   *context,
                                    GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "medium") == 0)
    {
      return g_object_ref (medium);
    }
  else if (strcmp (token, "small") == 0)
    {
      return g_object_ref (small);
    }
  else if (strcmp (token, "large") == 0)
    {
      return g_object_ref (large);
    }
  else if (strcmp (token, "x-small") == 0)
    {
      return g_object_ref (x_small);
    }
  else if (strcmp (token, "x-large") == 0)
    {
      return g_object_ref (x_large);
    }
  else if (strcmp (token, "xx-small") == 0)
    {
      return g_object_ref (xx_small);
    }
  else if (strcmp (token, "xx-large") == 0)
    {
      return g_object_ref (xx_large);
    }
  else if (strcmp (token, "larger") == 0)
    {
      return fo_datatype_mul (g_object_ref (fo_property_get_value (fo_context_get_font_size (context))),
			      g_object_ref (size_step));
    }
  else if (strcmp (token, "smaller") == 0)
    {
      return fo_datatype_div (g_object_ref (fo_property_get_value (fo_context_get_font_size (context))),
			      g_object_ref (size_step));
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
 * fo_property_font_size_validate:
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
fo_property_font_size_validate (FoDatatype *datatype,
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

  if (FO_IS_LENGTH (datatype))
    {
      gdouble font_size = fo_length_get_value (datatype);

      if (font_size < 0)
	{
	  gchar *datatype_sprintf = fo_object_sprintf (datatype);

	  g_set_error (error,
		       FO_FO_ERROR,
		       FO_PROPERTY_ERROR_ILLEGAL_NEGATIVE,
		       _(fo_property_error_messages[FO_PROPERTY_ERROR_ILLEGAL_NEGATIVE]),
		       class_name,
		       datatype_sprintf);

	  g_object_unref (datatype);
	  datatype = NULL;

	  g_free (datatype_sprintf);
	}

      return datatype;
    }
  else if (FO_IS_STRING (datatype))
    {
      token = fo_string_get_value (datatype);

      new_datatype =
        fo_property_font_size_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_font_size_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_PERCENTAGE (datatype))
    {
      gdouble percentage = fo_percentage_get_value (datatype);

      if (percentage < 0)
	{
	  gchar *datatype_sprintf = fo_object_sprintf (datatype);

	  g_set_error (error,
		       FO_FO_ERROR,
		       FO_PROPERTY_ERROR_ILLEGAL_NEGATIVE,
		       _(fo_property_error_messages[FO_PROPERTY_ERROR_ILLEGAL_NEGATIVE]),
		       class_name,
		       datatype_sprintf);

	  g_object_unref (datatype);

	  g_free (datatype_sprintf);

	  return NULL;
	}
      else
	{
	  new_datatype =
	    fo_datatype_mul (g_object_ref (fo_property_get_value (fo_context_get_font_size (context))),
			     datatype);

	  return new_datatype;
	}
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
 * fo_property_font_size_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_font_size_get_initial (void)
{
  static FoProperty *font_size = NULL;

  if (font_size == NULL)
    {
      font_size =
	fo_property_font_size_new ();
    }

  return font_size;
}

/**
 * fo_property_font_size_new_attr:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the current property.
 * 
 * Return value: New #PangoAttribute.
 **/
PangoAttribute*
fo_property_font_size_new_attr (FoProperty *property)
{
  gfloat pango_font_size;

  g_return_val_if_fail (FO_IS_PROPERTY_FONT_SIZE (property), NULL);

  pango_font_size =
    fo_length_get_value (property->value);

  return pango_attr_size_new (pango_font_size * PANGO_SCALE);
}
