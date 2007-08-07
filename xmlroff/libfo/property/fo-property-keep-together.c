/* Fo
 * fo-property-keep-together.c: 'keep-together' property
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
#include "property/fo-property-font-size.h"
#include "property/fo-property-keep-together.h"

struct _FoPropertyKeepTogether
{
  FoProperty parent_instance;
};

struct _FoPropertyKeepTogetherClass
{
  FoPropertyClass parent_class;
};

static void fo_property_keep_together_init         (FoPropertyKeepTogether      *property_keep_together);
static void fo_property_keep_together_base_init   (FoPropertyKeepTogetherClass *klass);
static void fo_property_keep_together_base_finalize   (FoPropertyKeepTogetherClass *klass);
static void fo_property_keep_together_class_init   (FoPropertyKeepTogetherClass *klass);
static void fo_property_keep_together_finalize     (GObject       *object);

static FoDatatype* fo_property_keep_together_resolve_enum (const gchar *token,
                                                           FoContext   *context,
                                                           GError     **error);
static FoDatatype* fo_property_keep_together_validate (FoDatatype *datatype,
                                                       FoContext  *context,
                                                       GError    **error);

static const gchar class_name[] = "keep-together";
static gpointer parent_class;
static FoDatatype *enum_auto;
static FoDatatype *enum_always;

/**
 * fo_property_keep_together_get_type:
 * 
 * Register the #FoPropertyKeepTogether type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyKeepTogether.
 **/
GType
fo_property_keep_together_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyKeepTogetherClass),
        (GBaseInitFunc) fo_property_keep_together_base_init,
        (GBaseFinalizeFunc) fo_property_keep_together_base_finalize,
        (GClassInitFunc) fo_property_keep_together_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyKeepTogether),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_keep_together_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_keep_together_init:
 * @keep_together: #FoPropertyKeepTogether object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyKeepTogether.
 **/
void
fo_property_keep_together_init (FoPropertyKeepTogether *keep_together)
{
  FO_PROPERTY (keep_together)->value =
    g_object_ref (fo_keep_get_keep_auto ());
}

/**
 * fo_property_keep_together_base_init:
 * @klass: #FoPropertyKeepTogetherClass object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPropertyKeepTogetherClass.
 **/
void
fo_property_keep_together_base_init (FoPropertyKeepTogetherClass *klass G_GNUC_UNUSED)
{
  enum_auto =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_ENUM),
                  "value",
                  FO_ENUM_ENUM_AUTO,
                  NULL);
  enum_always =
    g_object_new (FO_TYPE_ENUM,
                  "enum-class",
                  g_type_class_ref (FO_TYPE_ENUM_ENUM),
                  "value",
                  FO_ENUM_ENUM_ALWAYS,
                  NULL);
}

/**
 * fo_property_keep_together_base_finalize:
 * @klass: #FoPropertyKeepTogetherClass object to finalise.
 * 
 * Implements #GBaseFinalizeFunc for #FoPropertyKeepTogetherClass.
 **/
void
fo_property_keep_together_base_finalize (FoPropertyKeepTogetherClass *klass G_GNUC_UNUSED)
{
  g_object_unref (enum_auto);
  g_object_unref (enum_always);
}

/**
 * fo_property_keep_together_class_init:
 * @klass: #FoPropertyKeepTogetherClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyKeepTogetherClass.
 **/
void
fo_property_keep_together_class_init (FoPropertyKeepTogetherClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_keep_together_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_keep_together_resolve_enum;
  property_class->validate =
    fo_property_keep_together_validate;
  property_class->get_initial =
    fo_property_keep_together_get_initial;
}

/**
 * fo_property_keep_together_finalize:
 * @object: #FoPropertyKeepTogether object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyKeepTogether.
 **/
void
fo_property_keep_together_finalize (GObject *object)
{
  FoPropertyKeepTogether *keep_together;

  keep_together = FO_PROPERTY_KEEP_TOGETHER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_keep_together_new:
 * 
 * Creates a new #FoPropertyKeepTogether initialized to default value.
 * 
 * Return value: the new #FoPropertyKeepTogether.
 **/
FoProperty*
fo_property_keep_together_new (void)
{
  FoProperty* keep_together;

  keep_together =
    FO_PROPERTY (g_object_new (fo_property_keep_together_get_type (),
                               NULL));

  return keep_together;
}

/**
 * fo_property_keep_together_resolve_enum:
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
fo_property_keep_together_resolve_enum (const gchar *token,
                                        FoContext   *context,
                                        GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "auto") == 0)
    {
      return g_object_ref (fo_keep_get_keep_auto ());
    }
  else if (strcmp (token, "always") == 0)
    {
      return g_object_ref (fo_keep_get_keep_always ());
    }
  else if (strcmp (token, "inherit") == 0)
    {
      return g_object_ref (fo_context_get_keep_together (context));
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
 * fo_property_keep_together_validate:
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
fo_property_keep_together_validate (FoDatatype *datatype,
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

  if (FO_IS_KEEP (datatype))
    {
      return datatype;
    }
  else if (FO_IS_ENUM (datatype))
    {
      if ((fo_enum_get_value (datatype) == FO_ENUM_ENUM_AUTO) ||
	  (fo_enum_get_value (datatype) == FO_ENUM_ENUM_ALWAYS))
	{
	  new_datatype = fo_keep_new_with_value (datatype);

	  g_object_unref (datatype);

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
  else if (FO_IS_STRING (datatype))
    {
      token = fo_string_get_value (datatype);

      new_datatype =
        fo_property_keep_together_resolve_enum (token, context, &tmp_error);

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
        fo_property_keep_together_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      if (tmp_error != NULL)
	{
	  g_propagate_error (error, tmp_error);
	  return NULL;
	}

      return new_datatype;
    }
  else if (FO_IS_INTEGER (datatype))
    {
      new_datatype = fo_keep_new_with_value (datatype);

      g_object_unref (datatype);

      return new_datatype;
    }
  else if (FO_IS_NUMBER (datatype))
    {
      FoDatatype *integer_datatype =
	fo_integer_new_with_value (fo_number_get_value (datatype));

      g_object_unref (datatype);

      new_datatype = fo_keep_new_with_value (integer_datatype);

      g_object_unref (integer_datatype);

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
 * fo_property_keep_together_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_keep_together_get_initial (void)
{
  static FoProperty *keep_together = NULL;

  if (keep_together == NULL)
    {
      keep_together = fo_property_keep_together_new ();
    }

  return keep_together;
}
