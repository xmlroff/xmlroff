/* Fo
 * fo-property-break-after.c: 'break-after' property
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
#include "property/fo-property-break-after.h"

/* break-after */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | column | page | even-page | odd-page | inherit */
/* Initial value: auto */

struct _FoPropertyBreakAfter
{
  FoProperty parent_instance;
};

struct _FoPropertyBreakAfterClass
{
  FoPropertyClass parent_class;
};

static void fo_property_break_after_init         (FoPropertyBreakAfter      *property_break_after);
static void fo_property_break_after_class_init   (FoPropertyBreakAfterClass *klass);
static void fo_property_break_after_finalize     (GObject       *object);

static FoDatatype* fo_property_break_after_resolve_enum (const gchar *token,
                                                         FoContext   *context,
                                                         GError     **error);
static FoDatatype* fo_property_break_after_validate (FoDatatype *datatype,
                                                     FoContext  *context,
                                                     GError    **error);
static const gchar class_name[] = "break-after";
static gpointer parent_class;

/**
 * fo_property_break_after_get_type:
 * 
 * Register the #FoPropertyBreakAfter type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBreakAfter.
 **/
GType
fo_property_break_after_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBreakAfterClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_break_after_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBreakAfter),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_break_after_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_break_after_init:
 * @break_after: #FoPropertyBreakAfter object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBreakAfter.
 **/
void
fo_property_break_after_init (FoPropertyBreakAfter *break_after)
{
  FO_PROPERTY (break_after)->value =
    g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_property_break_after_class_init:
 * @klass: #FoPropertyBreakAfterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBreakAfterClass.
 **/
void
fo_property_break_after_class_init (FoPropertyBreakAfterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_break_after_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_break_after_resolve_enum;
  property_class->validate =
    fo_property_break_after_validate;
  property_class->get_initial =
    fo_property_break_after_get_initial;
}

/**
 * fo_property_break_after_finalize:
 * @object: #FoPropertyBreakAfter object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBreakAfter.
 **/
void
fo_property_break_after_finalize (GObject *object)
{
  FoPropertyBreakAfter *break_after;

  break_after = FO_PROPERTY_BREAK_AFTER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_break_after_new:
 * 
 * Creates a new #FoPropertyBreakAfter initialized to default value.
 * 
 * Return value: the new #FoPropertyBreakAfter.
 **/
FoProperty*
fo_property_break_after_new (void)
{
  FoProperty* break_after;

  break_after =
    FO_PROPERTY (g_object_new (fo_property_break_after_get_type (),
                               NULL));

  return break_after;
}

/**
 * fo_property_break_after_resolve_enum:
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
fo_property_break_after_resolve_enum (const gchar *token,
                                      FoContext   *context,
                                      GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "auto") == 0) ||
      (strcmp (token, "column") == 0) ||
      (strcmp (token, "page") == 0) ||
      (strcmp (token, "even-page") == 0) ||
      (strcmp (token, "odd-page") == 0))
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
 * fo_property_break_after_validate:
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
fo_property_break_after_validate (FoDatatype *datatype,
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
          (value == FO_ENUM_ENUM_COLUMN) ||
          (value == FO_ENUM_ENUM_PAGE) ||
          (value == FO_ENUM_ENUM_EVEN_PAGE) ||
          (value == FO_ENUM_ENUM_ODD_PAGE))
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
        fo_property_break_after_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_break_after_resolve_enum (token, context, &tmp_error);

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
 * fo_property_break_after_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_break_after_get_initial (void)
{
  static FoProperty *break_after = NULL;

  if (break_after == NULL)
    {
      break_after =
	fo_property_break_after_new ();
    }

  return break_after;
}
