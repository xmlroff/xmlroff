/* Fo
 * fo-property-writing-mode.c: 'writing-mode' property
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
#include "property/fo-property-font-size.h"
#include "property/fo-property-writing-mode.h"

/* writing-mode */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* lr-tb | rl-tb | tb-rl | lr | rl | tb | inherit */
/* Initial value: lr-tb */

struct _FoPropertyWritingMode
{
  FoProperty parent_instance;
};

struct _FoPropertyWritingModeClass
{
  FoPropertyClass parent_class;
};

static void fo_property_writing_mode_init         (FoPropertyWritingMode      *property_writing_mode);
static void fo_property_writing_mode_class_init   (FoPropertyWritingModeClass *klass);
static void fo_property_writing_mode_finalize     (GObject       *object);

static FoDatatype * fo_property_writing_mode_resolve_enum (const gchar *token,
                                                            FoContext   *context,
                                                            GError     **error);
static FoDatatype * fo_property_writing_mode_validate (FoDatatype *datatype,
                                                       FoContext  *context,
                                                       GError    **error);

static const gchar class_name[] = "writing-mode";
static gpointer parent_class;

/**
 * fo_property_writing_mode_get_type:
 * 
 * Register the #FoPropertyWritingMode type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyWritingMode.
 **/
GType
fo_property_writing_mode_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyWritingModeClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_writing_mode_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyWritingMode),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_writing_mode_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_writing_mode_init:
 * @writing_mode: #FoPropertyWritingMode object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyWritingMode.
 **/
void
fo_property_writing_mode_init (FoPropertyWritingMode *writing_mode)
{
  FO_PROPERTY (writing_mode)->value =
    g_object_ref (fo_enum_factory_get_enum_by_nick("lr-tb"));
}

/**
 * fo_property_writing_mode_class_init:
 * @klass: #FoPropertyWritingModeClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyWritingModeClass.
 **/
void
fo_property_writing_mode_class_init (FoPropertyWritingModeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_writing_mode_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_writing_mode_resolve_enum;
  property_class->validate =
    fo_property_writing_mode_validate;
  property_class->get_initial =
    fo_property_writing_mode_get_initial;
}

/**
 * fo_property_writing_mode_finalize:
 * @object: #FoPropertyWritingMode object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyWritingMode.
 **/
void
fo_property_writing_mode_finalize (GObject *object)
{
  FoPropertyWritingMode *writing_mode;

  writing_mode = FO_PROPERTY_WRITING_MODE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_writing_mode_new:
 * 
 * Creates a new #FoPropertyWritingMode initialized to default value.
 * 
 * Return value: the new #FoPropertyWritingMode.
 **/
FoProperty*
fo_property_writing_mode_new (void)
{
  FoProperty* writing_mode;

  writing_mode =
    FO_PROPERTY (g_object_new (fo_property_writing_mode_get_type (),
                               NULL));

  return writing_mode;
}

/**
 * fo_property_writing_mode_resolve_enum:
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
fo_property_writing_mode_resolve_enum (const gchar *token,
                                       FoContext   *context,
                                       GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "lr-tb") == 0) ||
      (strcmp (token, "rl-tb") == 0) ||
      (strcmp (token, "tb-rl") == 0) ||
      (strcmp (token, "lr") == 0) ||
      (strcmp (token, "rl") == 0) ||
      (strcmp (token, "tb") == 0))
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
 * fo_property_writing_mode_validate:
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
fo_property_writing_mode_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_LR_TB) ||
          (value == FO_ENUM_ENUM_RL_TB) ||
          (value == FO_ENUM_ENUM_TB_RL))
	{
	  return datatype;
	}
      else if (value == FO_ENUM_ENUM_LR)
	{
	  new_datatype = g_object_ref (fo_enum_factory_get_enum_by_nick ("lr-tb"));

	  g_object_unref (datatype);

	  return new_datatype;
	}
      else if (value == FO_ENUM_ENUM_RL)
	{
	  new_datatype = g_object_ref (fo_enum_factory_get_enum_by_nick ("rl-tb"));

	  g_object_unref (datatype);

	  return new_datatype;
	}
      else if (value == FO_ENUM_ENUM_TB)
	{
	  new_datatype = g_object_ref (fo_enum_factory_get_enum_by_nick ("tb-rl"));

	  g_object_unref (datatype);

	  return new_datatype;
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
        fo_property_writing_mode_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_writing_mode_resolve_enum (token, context, &tmp_error);

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
 * fo_property_writing_mode_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_writing_mode_get_initial (void)
{
  static FoProperty *writing_mode = NULL;

  if (writing_mode == NULL)
    {
      writing_mode =
	fo_property_writing_mode_new ();
    }

  return writing_mode;
}

/**
 * fo_property_writing_mode_to_bpd:
 * @writing_mode: #FoPropertyWritingMode
 * @error:        #GError
 * 
 * Determine the block-progression-direction for the current value of
 * @writing_mode
 * 
 * Return value: #FoEnumAreaDirection indicating block-progression-direction
 **/
FoEnumAreaDirection
fo_property_writing_mode_to_bpd (FoProperty  *writing_mode,
				 GError     **error)
{
  gint writing_mode_value;
  FoEnumAreaDirection bpd = FO_ENUM_AREA_DIRECTION_UNKNOWN;

  g_return_val_if_fail (writing_mode != NULL,
			FO_ENUM_AREA_DIRECTION_UNKNOWN);
  g_return_val_if_fail (FO_IS_PROPERTY_WRITING_MODE (writing_mode),
			FO_ENUM_AREA_DIRECTION_UNKNOWN);
  g_return_val_if_fail (error == NULL || *error == NULL,
			FO_ENUM_AREA_DIRECTION_UNKNOWN);

  writing_mode_value =
    fo_enum_get_value (writing_mode->value);

  if (writing_mode_value == FO_ENUM_ENUM_LR_TB)
    {
      bpd = FO_ENUM_AREA_DIRECTION_TB;
    }
  else if (writing_mode_value == FO_ENUM_ENUM_RL_TB)
    {
      bpd = FO_ENUM_AREA_DIRECTION_TB;
    }
  else if (writing_mode_value == FO_ENUM_ENUM_TB_RL)
    {
      bpd = FO_ENUM_AREA_DIRECTION_RL;
    }
  else
    {
      g_assert_not_reached ();
    }

  return bpd;
}

/**
 * fo_property_writing_mode_to_ipd:
 * @writing_mode: #FoPropertyWritingMode
 * @error:        #GError
 * 
 * Determine the inline-progression-direction for the current value of
 * @writing_mode
 * 
 * Return value: #FoEnumAreaDirection indicating inline-progression-direction
 **/
FoEnumAreaDirection
fo_property_writing_mode_to_ipd (FoProperty  *writing_mode,
				 GError     **error)
{
  gint writing_mode_value;
  FoEnumAreaDirection ipd = FO_ENUM_AREA_DIRECTION_UNKNOWN;

  g_return_val_if_fail (writing_mode != NULL,
			FO_ENUM_AREA_DIRECTION_UNKNOWN);
  g_return_val_if_fail (FO_IS_PROPERTY_WRITING_MODE (writing_mode),
			FO_ENUM_AREA_DIRECTION_UNKNOWN);
  g_return_val_if_fail (error == NULL || *error == NULL,
			FO_ENUM_AREA_DIRECTION_UNKNOWN);

  writing_mode_value =
    fo_enum_get_value (writing_mode->value);

  if (writing_mode_value == FO_ENUM_ENUM_LR_TB)
    {
      ipd = FO_ENUM_AREA_DIRECTION_LR;
    }
  else if (writing_mode_value == FO_ENUM_ENUM_RL_TB)
    {
      ipd = FO_ENUM_AREA_DIRECTION_RL;
    }
  else if (writing_mode_value == FO_ENUM_ENUM_TB_RL)
    {
      ipd = FO_ENUM_AREA_DIRECTION_TB;
    }
  else
    {
      g_assert_not_reached ();
    }

  return ipd;
}

/**
 * fo_property_writing_mode_to_sd:
 * @writing_mode: #FoPropertyWritingMode
 * @error:        #GError
 * 
 * Determine the shift-direction for the current value of
 * @writing_mode
 * 
 * Return value: #FoEnumAreaDirection indicating shift-direction
 **/
FoEnumAreaDirection
fo_property_writing_mode_to_sd (FoProperty  *writing_mode,
				 GError     **error)
{
  gint writing_mode_value;
  FoEnumAreaDirection sd = FO_ENUM_AREA_DIRECTION_UNKNOWN;

  g_return_val_if_fail (writing_mode != NULL,
			FO_ENUM_AREA_DIRECTION_UNKNOWN);
  g_return_val_if_fail (FO_IS_PROPERTY_WRITING_MODE (writing_mode),
			FO_ENUM_AREA_DIRECTION_UNKNOWN);
  g_return_val_if_fail (error == NULL || *error == NULL,
			FO_ENUM_AREA_DIRECTION_UNKNOWN);

  writing_mode_value =
    fo_enum_get_value (writing_mode->value);

  if (writing_mode_value == FO_ENUM_ENUM_LR_TB)
    {
      sd = FO_ENUM_AREA_DIRECTION_BT;
    }
  else if (writing_mode_value == FO_ENUM_ENUM_RL_TB)
    {
      sd = FO_ENUM_AREA_DIRECTION_BT;
    }
  else if (writing_mode_value == FO_ENUM_ENUM_TB_RL)
    {
      sd = FO_ENUM_AREA_DIRECTION_LR;
    }
  else
    {
      g_assert_not_reached ();
    }

  return sd;
}

