/* Fo
 * fo-property-alignment-adjust.c: 'alignment-adjust' property
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
#include "property/fo-property-alignment-adjust.h"

/* alignment-adjust */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | baseline | before-edge | text-before-edge | middle | central | after-edge | text-after-edge | ideographic | alphabetic | hanging | mathematical | <percentage> | <length> | inherit */
/* Initial value: auto */

struct _FoPropertyAlignmentAdjust
{
  FoProperty parent_instance;
};

struct _FoPropertyAlignmentAdjustClass
{
  FoPropertyClass parent_class;
};

static void fo_property_alignment_adjust_init         (FoPropertyAlignmentAdjust      *property_alignment_adjust);
static void fo_property_alignment_adjust_class_init   (FoPropertyAlignmentAdjustClass *klass);
static void fo_property_alignment_adjust_finalize     (GObject       *object);

static FoDatatype* fo_property_alignment_adjust_resolve_enum (const gchar *token,
                                                              FoContext   *context,
                                                              GError     **error);
static FoDatatype* fo_property_alignment_adjust_validate (FoDatatype *datatype,
                                                          FoContext  *context,
                                                          GError    **error);
/*
static PangoAttribute* fo_property_alignment_adjust_new_attr (FoProperty *property);
static void fo_property_alignment_adjust_text_property_init (FoPropertyTextPropertyIface *iface);
*/

static const gchar class_name[] = "alignment-adjust";
static gpointer parent_class;

/**
 * fo_property_alignment_adjust_get_type:
 * 
 * Register the #FoPropertyAlignmentAdjust type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyAlignmentAdjust.
 **/
GType
fo_property_alignment_adjust_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyAlignmentAdjustClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_alignment_adjust_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyAlignmentAdjust),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_alignment_adjust_init,
	NULL		/* value_table */
      };
      /*
      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_alignment_adjust_text_property_init, / * interface_init * /
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
 * fo_property_alignment_adjust_init:
 * @alignment_adjust: #FoPropertyAlignmentAdjust object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyAlignmentAdjust.
 **/
void
fo_property_alignment_adjust_init (FoPropertyAlignmentAdjust *alignment_adjust)
{
  FO_PROPERTY (alignment_adjust)->value =
    g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_property_alignment_adjust_class_init:
 * @klass: #FoPropertyAlignmentAdjustClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyAlignmentAdjustClass.
 **/
void
fo_property_alignment_adjust_class_init (FoPropertyAlignmentAdjustClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_alignment_adjust_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_alignment_adjust_resolve_enum;
  property_class->validate =
    fo_property_alignment_adjust_validate;
  property_class->get_initial =
    fo_property_alignment_adjust_get_initial;
}

/**
 * fo_property_alignment_adjust_finalize:
 * @object: #FoPropertyAlignmentAdjust object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyAlignmentAdjust.
 **/
void
fo_property_alignment_adjust_finalize (GObject *object)
{
  FoPropertyAlignmentAdjust *alignment_adjust;

  alignment_adjust = FO_PROPERTY_ALIGNMENT_ADJUST (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_alignment_adjust_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
/*
void
fo_property_alignment_adjust_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_alignment_adjust_new_attr;
}
*/

/**
 * fo_property_alignment_adjust_new:
 * 
 * Creates a new #FoPropertyAlignmentAdjust initialized to default value.
 * 
 * Return value: the new #FoPropertyAlignmentAdjust.
 **/
FoProperty*
fo_property_alignment_adjust_new (void)
{
  FoProperty* alignment_adjust;

  alignment_adjust =
    FO_PROPERTY (g_object_new (fo_property_alignment_adjust_get_type (),
                               NULL));

  return alignment_adjust;
}

/**
 * fo_property_alignment_adjust_resolve_enum:
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
fo_property_alignment_adjust_resolve_enum (const gchar *token,
                                           FoContext   *context,
                                           GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "auto") == 0) ||
      (strcmp (token, "baseline") == 0) ||
      (strcmp (token, "before-edge") == 0) ||
      (strcmp (token, "text-before-edge") == 0) ||
      (strcmp (token, "middle") == 0) ||
      (strcmp (token, "central") == 0) ||
      (strcmp (token, "after-edge") == 0) ||
      (strcmp (token, "text-after-edge") == 0) ||
      (strcmp (token, "ideographic") == 0) ||
      (strcmp (token, "alphabetic") == 0) ||
      (strcmp (token, "hanging") == 0) ||
      (strcmp (token, "mathematical") == 0))
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
 * fo_property_alignment_adjust_validate:
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
fo_property_alignment_adjust_validate (FoDatatype *datatype,
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
      gint value = fo_enum_get_value (datatype);

      if ((value == FO_ENUM_ENUM_AUTO) ||
          (value == FO_ENUM_ENUM_BASELINE) ||
          (value == FO_ENUM_ENUM_BEFORE_EDGE) ||
          (value == FO_ENUM_ENUM_TEXT_BEFORE_EDGE) ||
          (value == FO_ENUM_ENUM_MIDDLE) ||
          (value == FO_ENUM_ENUM_CENTRAL) ||
          (value == FO_ENUM_ENUM_AFTER_EDGE) ||
          (value == FO_ENUM_ENUM_TEXT_AFTER_EDGE) ||
          (value == FO_ENUM_ENUM_IDEOGRAPHIC) ||
          (value == FO_ENUM_ENUM_ALPHABETIC) ||
          (value == FO_ENUM_ENUM_HANGING) ||
          (value == FO_ENUM_ENUM_MATHEMATICAL))
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
        fo_property_alignment_adjust_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_alignment_adjust_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_PERCENTAGE (datatype))
    {
      return datatype;
    }
  else if (FO_IS_LENGTH (datatype))
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
 * fo_property_alignment_adjust_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_alignment_adjust_get_initial (void)
{
  static FoProperty *alignment_adjust = NULL;

  if (alignment_adjust == NULL)
    {
      alignment_adjust =
	fo_property_alignment_adjust_new ();
    }

  return alignment_adjust;
}

/**
 * fo_property_alignment_adjust_to_pango_baseline:
 * @adjust: #FoEnumAlignmentAdjust to convert to #PangoBaseline value.
 * 
 * Gets the #PangoBaseline value corresponding to the value of
 * @adjust.
 * 
 * Return value: A #PangoBaseline value, which could be
 * #PANGO_BASELINE_INVALID.
 **/
/*
static PangoBaseline
fo_property_alignment_adjust_to_pango_baseline (FoEnumEnum adjust)
{
  switch (adjust)
    {
    case FO_ENUM_ENUM_AUTO:
      return PANGO_BASELINE_AUTO;
    case FO_ENUM_ENUM_BASELINE:
      return PANGO_BASELINE_BASELINE;
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
    case FO_ENUM_ENUM_BEFORE_EDGE:
      return PANGO_BASELINE_BEFORE_EDGE;
    case FO_ENUM_ENUM_AFTER_EDGE:
      return PANGO_BASELINE_AFTER_EDGE;
    default:
      return PANGO_BASELINE_INVALID;
    }
}
*/
/**
 * fo_property_alignment_adjust_new_attr:
 * @property: Property from which to create a PangoAttribute
 * 
 * Makes a new PangoAttribute representing the current property
 * 
 * Return value: New PangoAttribute
 **/
/*
PangoAttribute*
fo_property_alignment_adjust_new_attr (FoProperty *property)
{
  PangoBaseline pango_alignment_adjust;

  g_return_val_if_fail (FO_IS_PROPERTY_ALIGNMENT_ADJUST (property), NULL);

  pango_alignment_adjust =
    fo_property_alignment_adjust_to_pango_baseline (fo_enum_get_value (property->value));

  return pango_attr_alignment_adjust_new (pango_alignment_adjust);
}
*/
