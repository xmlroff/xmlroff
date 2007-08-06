/* Fo
 * fo-property-font-weight.c: 'font-weight' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
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
#include "property/fo-property-font-weight.h"

#ifndef FO_FONT_WEIGHT_NORMAL
#define FO_FONT_WEIGHT_NORMAL	400
#endif	/* !FO_FONT_WEIGHT_NORMAL */

#ifndef FO_FONT_WEIGHT_BOLD
#define FO_FONT_WEIGHT_BOLD	700
#endif	/* !FO_FONT_WEIGHT_BOLD */

#ifndef FO_FONT_WEIGHT_STEP
#define FO_FONT_WEIGHT_STEP	100
#endif	/* !FO_FONT_WEIGHT_STEP */

#ifndef FO_FONT_WEIGHT_MAX
#define FO_FONT_WEIGHT_MAX	900
#endif	/* !FO_FONT_WEIGHT_MAX */

#ifndef FO_FONT_WEIGHT_MIN
#define FO_FONT_WEIGHT_MIN	100
#endif	/* !FO_FONT_WEIGHT_MIN */

/* font-weight */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* normal | bold | bolder | lighter | 100 | 200 | 300 | 400 | 500 | 600 | 700 | 800 | 900 | inherit */
/* Initial value: normal */

struct _FoPropertyFontWeight
{
  FoProperty parent_instance;
};

struct _FoPropertyFontWeightClass
{
  FoPropertyClass parent_class;
};

static void fo_property_font_weight_init         (FoPropertyFontWeight      *property_font_weight);
static void fo_property_font_weight_class_init   (FoPropertyFontWeightClass *klass);
static void fo_property_font_weight_finalize     (GObject       *object);
static void fo_property_font_weight_text_property_init (FoPropertyTextPropertyIface *iface);

static FoDatatype * fo_property_font_weight_resolve_enum (const gchar *token,
                                                           FoContext   *context,
                                                           GError     **error);
static FoDatatype * fo_property_font_weight_validate (FoDatatype *datatype,
                                                      FoContext  *context,
                                                      GError    **error);
static PangoAttribute * fo_property_font_weight_new_attr (FoProperty *property);

static const gchar class_name[] = "FoPropertyFontWeight";
static gpointer parent_class;

/**
 * fo_property_font_weight_get_type:
 * 
 * Register the #FoPropertyFontWeight type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyFontWeight.
 **/
GType
fo_property_font_weight_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyFontWeightClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_font_weight_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyFontWeight),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_font_weight_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_font_weight_text_property_init, /* interface_init */
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
 * fo_property_font_weight_init:
 * @font_weight: #FoPropertyFontWeight object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyFontWeight.
 **/
void
fo_property_font_weight_init (FoPropertyFontWeight *font_weight)
{
  FO_PROPERTY (font_weight)->value =
    g_object_ref (fo_integer_new_with_value (FO_FONT_WEIGHT_NORMAL));
}

/**
 * fo_property_font_weight_class_init:
 * @klass: #FoPropertyFontWeightClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyFontWeightClass.
 **/
void
fo_property_font_weight_class_init (FoPropertyFontWeightClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_font_weight_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_font_weight_resolve_enum;
  property_class->validate =
    fo_property_font_weight_validate;
  property_class->get_initial =
    fo_property_font_weight_get_initial;
}

/**
 * fo_property_font_weight_finalize:
 * @object: #FoPropertyFontWeight object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyFontWeight.
 **/
void
fo_property_font_weight_finalize (GObject *object)
{
  FoPropertyFontWeight *font_weight;

  font_weight = FO_PROPERTY_FONT_WEIGHT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_font_weight_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
void
fo_property_font_weight_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_font_weight_new_attr;
}

/**
 * fo_property_font_weight_new:
 * 
 * Creates a new #FoPropertyFontWeight initialized to default value.
 * 
 * Return value: the new #FoPropertyFontWeight.
 **/
FoProperty*
fo_property_font_weight_new (void)
{
  FoProperty* font_weight;

  font_weight =
    FO_PROPERTY (g_object_new (fo_property_font_weight_get_type (),
                               NULL));

  return font_weight;
}

/**
 * fo_property_font_weight_resolve_enum:
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
fo_property_font_weight_resolve_enum (const gchar *token,
                                      FoContext   *context,
                                      GError     **error)
{
  gint old_font_weight_value;

  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "normal") == 0)
    {
      return fo_integer_new_with_value (FO_FONT_WEIGHT_NORMAL);
    }
  else if (strcmp (token, "bold") == 0)
    {
      return fo_integer_new_with_value (FO_FONT_WEIGHT_BOLD);
    }
  else if (strcmp (token, "bolder") == 0)
    {
      /* FIXME: Redo with fo_datatype_max(), etc. */
      old_font_weight_value =
	fo_integer_get_value (fo_property_get_value (fo_context_get_font_weight (context)));

      return fo_integer_new_with_value (MIN (old_font_weight_value + FO_FONT_WEIGHT_STEP,
					     FO_FONT_WEIGHT_MAX));
    }
  else if (strcmp (token, "lighter") == 0)
    {
      old_font_weight_value =
	fo_integer_get_value (fo_property_get_value (fo_context_get_font_weight (context)));

      return fo_integer_new_with_value (MAX (old_font_weight_value - FO_FONT_WEIGHT_STEP,
					     FO_FONT_WEIGHT_MIN));
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
 * fo_property_font_weight_validate:
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
fo_property_font_weight_validate (FoDatatype *datatype,
                                  FoContext  *context,
                                  GError    **error)
{
  FoDatatype *new_datatype;
  GError     *tmp_error = NULL;
  gchar      *token;
  gint        int_value;
  gfloat      float_value;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_ENUM (datatype))
    {
      FoEnumEnum value = fo_enum_get_value (datatype);

      if (value == FO_ENUM_ENUM_NORMAL)
	{
	  return fo_integer_new_with_value (FO_FONT_WEIGHT_NORMAL);
	}
      else if (value == FO_ENUM_ENUM_BOLD)
	{
	  return fo_integer_new_with_value (FO_FONT_WEIGHT_BOLD);
	}
      else if ((value == FO_ENUM_ENUM_BOLDER) ||
	       (value == FO_ENUM_ENUM_LIGHTER))
	{
	  return datatype;
	}
      else if (value == FO_ENUM_ENUM_100)
	{
	  return fo_integer_new_with_value (100);
	}
      else if (value == FO_ENUM_ENUM_200)
	{
	  return fo_integer_new_with_value (200);
	}
      else if (value == FO_ENUM_ENUM_300)
	{
	  return fo_integer_new_with_value (300);
	}
      else if (value == FO_ENUM_ENUM_400)
	{
	  return fo_integer_new_with_value (400);
	}
      else if (value == FO_ENUM_ENUM_500)
	{
	  return fo_integer_new_with_value (500);
	}
      else if (value == FO_ENUM_ENUM_600)
	{
	  return fo_integer_new_with_value (600);
	}
      else if (value == FO_ENUM_ENUM_700)
	{
	  return fo_integer_new_with_value (700);
	}
      else if (value == FO_ENUM_ENUM_800)
	{
	  return fo_integer_new_with_value (800);
	}
      else if (value == FO_ENUM_ENUM_900)
	{
	  return fo_integer_new_with_value (900);
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
        fo_property_font_weight_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_font_weight_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NUMBER (datatype))
    {
      float_value = fo_number_get_value (datatype);

      if ((float_value == 100) || (float_value == 200) ||
	  (float_value == 300) || (float_value == 400) ||
	  (float_value == 500) || (float_value == 600) ||
	  (float_value == 700) || (float_value == 800) ||
	  (float_value == 900))
	{
	  new_datatype = fo_integer_new_with_value ((int) float_value);
	  g_object_unref (datatype);

	  return new_datatype;
	}
      else
	{
	  g_warning ("Incorrect font-weight: %g", float_value);

	  int_value = (int) float_value / 100;

	  int_value = CLAMP (int_value, 1, 9) * 100;

	  new_datatype = fo_integer_new_with_value (int_value);

	  g_object_unref (datatype);

	  return new_datatype;
	}
    }
  else if (FO_IS_INTEGER (datatype))
    {
      int_value = fo_integer_get_value (datatype);

      if ((int_value == 100) || (int_value == 200) ||
	  (int_value == 300) || (int_value == 400) ||
	  (int_value == 500) || (int_value == 600) ||
	  (int_value == 700) || (int_value == 800) ||
	  (int_value == 900))
	{
	  return datatype;
	}
      else
	{
	  g_warning ("Incorrect font-weight: %d", int_value);

	  int_value = CLAMP (int_value / 100, 1, 9) * 100;

	  new_datatype = fo_integer_new_with_value (int_value);

	  g_object_unref (datatype);

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
 * fo_property_font_weight_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_font_weight_get_initial (void)
{
  static FoProperty *font_weight = NULL;

  if (font_weight == NULL)
    {
      font_weight =
	fo_property_font_weight_new ();
    }

  return font_weight;
}

/**
 * fo_property_font_weight_new_attr:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the current property.
 * 
 * Return value: New #PangoAttribute.
 **/
PangoAttribute*
fo_property_font_weight_new_attr (FoProperty *property)
{
  gint pango_font_weight;

  g_return_val_if_fail (FO_IS_PROPERTY_FONT_WEIGHT (property), NULL);

  pango_font_weight =
    fo_integer_get_value (property->value);

  return pango_attr_weight_new (pango_font_weight);
}
