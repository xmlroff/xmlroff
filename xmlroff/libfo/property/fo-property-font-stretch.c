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

struct _FoPropertyFontStretch
{
  FoProperty parent_instance;
};

struct _FoPropertyFontStretchClass
{
  FoPropertyClass parent_class;
};

static void fo_property_font_stretch_init         (FoPropertyFontStretch      *property_font_stretch);
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
        NULL,           /* base_init */
        NULL,           /* base_finalize */
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
    g_object_ref (fo_enum_factory_get_enum_by_nick ("normal"));
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

FoEnumEnum
_wider_font_stretch (FoContext *context)
{
  FoEnumEnum wider;

  FoEnumEnum old_stretch =
    fo_enum_get_value (fo_property_get_value (fo_context_get_font_stretch (context)));

  switch (old_stretch)
    {
    case FO_ENUM_ENUM_ULTRA_CONDENSED:
      wider = FO_ENUM_ENUM_EXTRA_CONDENSED;
      break;

    case FO_ENUM_ENUM_EXTRA_CONDENSED:
      wider = FO_ENUM_ENUM_CONDENSED;
      break;

    case FO_ENUM_ENUM_CONDENSED:
      wider = FO_ENUM_ENUM_SEMI_CONDENSED;
      break;

    case FO_ENUM_ENUM_SEMI_CONDENSED:
      wider = FO_ENUM_ENUM_NORMAL;
      break;

    case FO_ENUM_ENUM_NORMAL:
      wider = FO_ENUM_ENUM_SEMI_EXPANDED;
      break;

    case FO_ENUM_ENUM_SEMI_EXPANDED:
      wider = FO_ENUM_ENUM_EXPANDED;
      break;

    case FO_ENUM_ENUM_EXPANDED:
      wider = FO_ENUM_ENUM_EXTRA_EXPANDED;
      break;

    case FO_ENUM_ENUM_EXTRA_EXPANDED:
      wider = FO_ENUM_ENUM_ULTRA_EXPANDED;
      break;

    case FO_ENUM_ENUM_ULTRA_EXPANDED:
      /* Can't get more expanded. */
      wider = FO_ENUM_ENUM_ULTRA_EXPANDED;
      break;

    default:
      /* When in doubt, use 'normal'. */
      wider = FO_ENUM_ENUM_NORMAL;
      break; 
    }

  return wider;
}

FoEnumEnum
_narrower_font_stretch (FoContext *context)
{
  FoEnumEnum narrower;

  FoEnumEnum old_stretch =
    fo_enum_get_value (fo_property_get_value (fo_context_get_font_stretch (context)));

  switch (old_stretch)
    {
    case FO_ENUM_ENUM_ULTRA_CONDENSED:
      /* Can't get more condensed. */
      narrower = FO_ENUM_ENUM_ULTRA_CONDENSED;
      break;

    case FO_ENUM_ENUM_EXTRA_CONDENSED:
      narrower = FO_ENUM_ENUM_ULTRA_CONDENSED;
      break;

    case FO_ENUM_ENUM_CONDENSED:
      narrower = FO_ENUM_ENUM_EXTRA_CONDENSED;
      break;

    case FO_ENUM_ENUM_SEMI_CONDENSED:
      narrower = FO_ENUM_ENUM_CONDENSED;
      break;

    case FO_ENUM_ENUM_NORMAL:
      narrower = FO_ENUM_ENUM_SEMI_CONDENSED;
      break;

    case FO_ENUM_ENUM_SEMI_EXPANDED:
      narrower = FO_ENUM_ENUM_NORMAL;
      break;

    case FO_ENUM_ENUM_EXPANDED:
      narrower = FO_ENUM_ENUM_SEMI_EXPANDED;
      break;

    case FO_ENUM_ENUM_EXTRA_EXPANDED:
      narrower = FO_ENUM_ENUM_EXPANDED;
      break;

    case FO_ENUM_ENUM_ULTRA_EXPANDED:
      narrower = FO_ENUM_ENUM_EXTRA_EXPANDED;
      break;

    default:
      /* When in doubt, use 'normal'. */
      narrower = FO_ENUM_ENUM_NORMAL;
      break; 
    }

  return narrower;
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
FoDatatype *
fo_property_font_stretch_resolve_enum (const gchar *token,
                                       FoContext   *context,
                                       GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "normal") == 0) ||
      (strcmp (token, "ultra-condensed") == 0) ||
      (strcmp (token, "extra-condensed") == 0) ||
      (strcmp (token, "condensed") == 0) ||
      (strcmp (token, "semi-condensed") == 0) ||
      (strcmp (token, "semi-expanded") == 0) ||
      (strcmp (token, "expanded") == 0) ||
      (strcmp (token, "extra-expanded") == 0) ||
      (strcmp (token, "ultra-expanded") == 0))
    {
      return g_object_ref (fo_enum_factory_get_enum_by_nick (token));
    }
  else if (strcmp (token, "wider") == 0)
    {
      return g_object_ref (fo_enum_factory_get_enum_by_value (_wider_font_stretch (context)));
    }
  else if (strcmp (token, "narrower") == 0)
    {
      return g_object_ref (fo_enum_factory_get_enum_by_value (_narrower_font_stretch (context)));
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
      FoEnumEnum value = fo_enum_get_value (datatype);

      if ((value == FO_ENUM_ENUM_NORMAL) ||
          (value == FO_ENUM_ENUM_WIDER) ||
          (value == FO_ENUM_ENUM_NARROWER) ||
          (value == FO_ENUM_ENUM_ULTRA_CONDENSED) ||
          (value == FO_ENUM_ENUM_EXTRA_CONDENSED) ||
          (value == FO_ENUM_ENUM_CONDENSED) ||
          (value == FO_ENUM_ENUM_SEMI_CONDENSED) ||
          (value == FO_ENUM_ENUM_SEMI_EXPANDED) ||
          (value == FO_ENUM_ENUM_EXPANDED) ||
          (value == FO_ENUM_ENUM_EXTRA_EXPANDED) ||
          (value == FO_ENUM_ENUM_ULTRA_EXPANDED))
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
