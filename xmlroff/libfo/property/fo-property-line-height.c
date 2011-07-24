/* Fo
 * fo-property-line-height.c: 'line-height' property
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
/*
#include "property/fo-property-text-property.h"
*/
#include "property/fo-property-font-size.h"
#include "property/fo-property-line-height.h"


#define FO_PROPERTY_LINE_HEIGHT_NORMAL_MULTIPLIER 1.2
/* line-height */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* normal | <length> | <number> | <percentage> | <space> | inherit */
/* Initial value: normal */

struct _FoPropertyLineHeight
{
  FoProperty parent_instance;
};

struct _FoPropertyLineHeightClass
{
  FoPropertyClass parent_class;
};

static void fo_property_line_height_init         (FoPropertyLineHeight      *property_line_height);
static void fo_property_line_height_class_init   (FoPropertyLineHeightClass *klass);
static void fo_property_line_height_finalize     (GObject       *object);

static FoDatatype* fo_property_line_height_resolve_enum (const gchar *token,
                                                         FoContext   *context,
                                                         GError     **error);
static FoDatatype* fo_property_line_height_validate (FoDatatype *datatype,
                                                     FoContext  *context,
                                                     GError    **error);
/*
static void fo_property_line_height_text_property_init (FoPropertyTextPropertyIface *iface);
static PangoAttribute * fo_property_line_height_new_attr (FoProperty *property);
*/
static const gchar class_name[] = "line-height";
static gpointer parent_class;

/**
 * fo_property_line_height_get_type:
 * 
 * Register the #FoPropertyLineHeight type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyLineHeight.
 **/
GType
fo_property_line_height_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyLineHeightClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_line_height_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyLineHeight),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_line_height_init,
	NULL		/* value_table */
      };
      /*
      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_line_height_text_property_init, / * interface_init * /
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
 * fo_property_line_height_init:
 * @line_height: #FoPropertyLineHeight object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyLineHeight.
 **/
void
fo_property_line_height_init (FoPropertyLineHeight *line_height)
{
  FO_PROPERTY (line_height)->value =
    g_object_ref (fo_enum_factory_get_enum_by_nick ("normal"));
}

/**
 * fo_property_line_height_class_init:
 * @klass: #FoPropertyLineHeightClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyLineHeightClass.
 **/
void
fo_property_line_height_class_init (FoPropertyLineHeightClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_line_height_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_line_height_resolve_enum;
  property_class->validate =
    fo_property_line_height_validate;
  property_class->get_initial =
    fo_property_line_height_get_initial;
}

/**
 * fo_property_line_height_finalize:
 * @object: #FoPropertyLineHeight object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyLineHeight.
 **/
void
fo_property_line_height_finalize (GObject *object)
{
  FoPropertyLineHeight *line_height;

  line_height = FO_PROPERTY_LINE_HEIGHT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_line_height_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
/*
void
fo_property_line_height_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_line_height_new_attr;
}
*/

/**
 * fo_property_line_height_new:
 * 
 * Creates a new #FoPropertyLineHeight initialized to default value.
 * 
 * Return value: the new #FoPropertyLineHeight.
 **/
FoProperty*
fo_property_line_height_new (void)
{
  FoProperty* line_height;

  line_height =
    FO_PROPERTY (g_object_new (fo_property_line_height_get_type (),
                               NULL));

  return line_height;
}

/**
 * fo_property_line_height_resolve_enum:
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
fo_property_line_height_resolve_enum (const gchar *token,
                                      FoContext   *context,
                                      GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "normal") == 0)
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
 * fo_property_line_height_validate:
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
fo_property_line_height_validate (FoDatatype *datatype,
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

      if (value == FO_ENUM_ENUM_NORMAL)
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
        fo_property_line_height_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_line_height_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_LENGTH (datatype))
    {
      return datatype;
    }
  else if (FO_IS_NUMBER (datatype))
    {
      return datatype;
    }
  else if (FO_IS_PERCENTAGE (datatype))
    {
      return datatype;
    }
  else if (FO_IS_SPACE (datatype))
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
 * fo_property_line_height_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_line_height_get_initial (void)
{
  static FoProperty *line_height = NULL;

  if (line_height == NULL)
    {
      line_height =
	fo_property_line_height_new ();
    }

  return line_height;
}

/**
 * fo_property_line_height_resolve:
 * @line_height: 'line-height' property.
 * @font_size:   'font-size' property.
 * 
 * Determine the computed value of the 'line-height' based on
 * @line_height and @font_size.
 * 
 * Return value: #FoProperty with the computed value of @line_height.
 **/
FoProperty*
fo_property_line_height_resolve (FoProperty *line_height,
				 FoProperty *font_size)
{
  FoDatatype *line_height_value;

  g_return_val_if_fail (FO_IS_PROPERTY_LINE_HEIGHT (line_height), NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_FONT_SIZE (font_size), NULL);

  line_height_value = fo_property_get_value (line_height);

  if (FO_IS_LENGTH (line_height_value))
    {
      return line_height;
    }
  else
    {
      FoDatatype *new_value = NULL;
      FoProperty *new_line_height = fo_property_line_height_new ();

      gfloat font_size_value =
	fo_length_get_value (fo_property_get_value (font_size));

      /* FIXME Doesn't handle space case */
      if (FO_IS_ENUM (line_height_value))
	{
	  FoEnumEnum enum_value = fo_enum_get_value (line_height_value);

	  if (enum_value == FO_ENUM_ENUM_NORMAL)
	    {
	      new_value =
		fo_length_new_with_value (font_size_value *
					  FO_PROPERTY_LINE_HEIGHT_NORMAL_MULTIPLIER);
	    }
	}
      else if (FO_IS_NUMBER (line_height_value))
	{
	  new_value =
	    fo_length_new_with_value (fo_number_get_value (line_height_value) *
				      font_size_value);
	}
      else if (FO_IS_PERCENTAGE (line_height_value))
	{
	  new_value =
	    fo_length_new_with_value (fo_percentage_get_value (line_height_value) *
				      font_size_value / 100);
	}

      fo_property_set_value (new_line_height, new_value);
      return new_line_height;
    }
}

/**
 * fo_property_line_height_new_attr:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the current property.
 * 
 * Return value: New #PangoAttribute.
 **/
/*
PangoAttribute*
fo_property_line_height_new_attr (FoProperty *property)
{
  gint pango_line_height;

  g_return_val_if_fail (FO_IS_PROPERTY_LINE_HEIGHT (property), NULL);

  pango_line_height =
    (int) (fo_length_get_value (property->value) *
	   PANGO_SCALE);

  return pango_attr_line_height_new (pango_line_height);
}
*/
