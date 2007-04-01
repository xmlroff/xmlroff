/* Fo
 * fo-property-baseline-shift.c: 'baseline-shift' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-baseline-shift.c,v 1.8 2004/10/12 14:51:39 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include <pangoxsl/pango-xsl-attributes.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-baseline-shift.h"

/* baseline-shift */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* baseline | sub | super | <percentage> | <length> | inherit */
/* Initial value: baseline */

struct _FoPropertyBaselineShift
{
  FoProperty parent_instance;
};

struct _FoPropertyBaselineShiftClass
{
  FoPropertyClass parent_class;
};

static void fo_property_baseline_shift_init         (FoPropertyBaselineShift      *property_baseline_shift);
static void fo_property_baseline_shift_class_init   (FoPropertyBaselineShiftClass *klass);
static void fo_property_baseline_shift_finalize     (GObject       *object);
static void fo_property_baseline_shift_text_property_init (FoPropertyTextPropertyIface *iface);

static FoDatatype* fo_property_baseline_shift_resolve_enum (const gchar *token,
                                                            FoContext   *context,
                                                            GError     **error);
static FoDatatype* fo_property_baseline_shift_validate (FoDatatype *datatype,
                                                        FoContext  *context,
                                                        GError    **error);
static PangoAttribute * fo_property_baseline_shift_new_attr (FoProperty *property);

static const gchar class_name[] = "baseline-shift";
static gpointer parent_class;

/**
 * fo_property_baseline_shift_get_type:
 * 
 * Register the #FoPropertyBaselineShift type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBaselineShift.
 **/
GType
fo_property_baseline_shift_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBaselineShiftClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_baseline_shift_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBaselineShift),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_baseline_shift_init,
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_property_text_property_info =
      {
	(GInterfaceInitFunc) fo_property_baseline_shift_text_property_init, /* interface_init */
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
 * fo_property_baseline_shift_init:
 * @baseline_shift: #FoPropertyBaselineShift object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBaselineShift.
 **/
void
fo_property_baseline_shift_init (FoPropertyBaselineShift *baseline_shift)
{
  FO_PROPERTY (baseline_shift)->value =
    g_object_ref (fo_length_get_length_zero ());
}

/**
 * fo_property_baseline_shift_class_init:
 * @klass: #FoPropertyBaselineShiftClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBaselineShiftClass.
 **/
void
fo_property_baseline_shift_class_init (FoPropertyBaselineShiftClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_baseline_shift_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_baseline_shift_resolve_enum;
  property_class->validate =
    fo_property_baseline_shift_validate;
  property_class->get_initial =
    fo_property_baseline_shift_get_initial;
}

/**
 * fo_property_baseline_shift_finalize:
 * @object: #FoPropertyBaselineShift object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBaselineShift.
 **/
void
fo_property_baseline_shift_finalize (GObject *object)
{
  FoPropertyBaselineShift *baseline_shift;

  baseline_shift = FO_PROPERTY_BASELINE_SHIFT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_property_baseline_shift_text_property_init:
 * @iface: #FoPropertyTextPropertyIFace structure for this class.
 * 
 * Initialize #FoPropertyTextPropertyIface interface for this class.
 **/
void
fo_property_baseline_shift_text_property_init (FoPropertyTextPropertyIface *iface)
{
  iface->new_attr = fo_property_baseline_shift_new_attr;
}

/**
 * fo_property_baseline_shift_new:
 * 
 * Creates a new #FoPropertyBaselineShift initialized to default value.
 * 
 * Return value: the new #FoPropertyBaselineShift.
 **/
FoProperty*
fo_property_baseline_shift_new (void)
{
  FoProperty* baseline_shift;

  baseline_shift =
    FO_PROPERTY (g_object_new (fo_property_baseline_shift_get_type (),
                               NULL));

  return baseline_shift;
}

/**
 * fo_property_baseline_shift_resolve_enum:
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
fo_property_baseline_shift_resolve_enum (const gchar *token,
                                         FoContext   *context,
                                         GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "baseline") == 0)
    {
      return g_object_ref (fo_length_get_length_zero ());
    }
  else if (strcmp (token, "sub") == 0)
    {
      return g_object_ref (fo_length_get_length_minus_3pt ());
    }
  else if (strcmp (token, "super") == 0)
    {
      return g_object_ref (fo_length_get_length_3pt ());
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
 * fo_property_baseline_shift_validate:
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
fo_property_baseline_shift_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_BASELINE) ||
          (value == FO_ENUM_ENUM_SUB) ||
          (value == FO_ENUM_ENUM_SUPER))
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
        fo_property_baseline_shift_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_baseline_shift_resolve_enum (token, context, &tmp_error);

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
 * fo_property_baseline_shift_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_baseline_shift_get_initial (void)
{
  static FoProperty *baseline_shift = NULL;

  if (baseline_shift == NULL)
    {
      baseline_shift =
	fo_property_baseline_shift_new ();
    }

  return baseline_shift;
}

/**
 * fo_property_baseline_shift_new_attr:
 * @property: Property from which to create a PangoAttribute
 * 
 * Makes a new PangoAttribute representing the current property
 * 
 * Return value: New PangoAttribute
 **/
PangoAttribute*
fo_property_baseline_shift_new_attr (FoProperty *property)
{
  gint pango_baseline_shift;

  g_return_val_if_fail (FO_IS_PROPERTY_BASELINE_SHIFT (property), NULL);

  pango_baseline_shift =
    (int) (fo_length_get_value (property->value) *
	   PANGO_SCALE);

  return pango_attr_rise_new (pango_baseline_shift);
}
