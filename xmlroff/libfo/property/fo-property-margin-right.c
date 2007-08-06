/* Fo
 * fo-property-margin-right.c: 'margin-right' property
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
#include "property/fo-property-margin-right.h"
#include "property/fo-property-util.h"

/* margin-right */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <margin-width> | inherit */
/* Initial value: 0pt */

struct _FoPropertyMarginRight
{
  FoProperty parent_instance;
};

struct _FoPropertyMarginRightClass
{
  FoPropertyClass parent_class;
};

static void fo_property_margin_right_init         (FoPropertyMarginRight      *property_margin_right);
static void fo_property_margin_right_class_init   (FoPropertyMarginRightClass *klass);
static void fo_property_margin_right_finalize     (GObject       *object);

static FoDatatype* fo_property_margin_right_validate (FoDatatype *datatype,
                                                      FoContext  *context,
                                                      GError    **error);

static const gchar class_name[] = "FoPropertyMarginRight";
static gpointer parent_class;

/**
 * fo_property_margin_right_get_type:
 * 
 * Register the #FoPropertyMarginRight type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyMarginRight.
 **/
GType
fo_property_margin_right_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyMarginRightClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_margin_right_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyMarginRight),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_margin_right_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_margin_right_init:
 * @margin_right: #FoPropertyMarginRight object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyMarginRight.
 **/
void
fo_property_margin_right_init (FoPropertyMarginRight *margin_right)
{
  FO_PROPERTY (margin_right)->value =
    g_object_ref (fo_length_get_length_zero ());
}

/**
 * fo_property_margin_right_class_init:
 * @klass: #FoPropertyMarginRightClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyMarginRightClass.
 **/
void
fo_property_margin_right_class_init (FoPropertyMarginRightClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_margin_right_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_auto_enum;
  property_class->validate =
    fo_property_margin_right_validate;
  property_class->get_initial =
    fo_property_margin_right_get_initial;
}

/**
 * fo_property_margin_right_finalize:
 * @object: #FoPropertyMarginRight object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyMarginRight.
 **/
void
fo_property_margin_right_finalize (GObject *object)
{
  FoPropertyMarginRight *margin_right;

  margin_right = FO_PROPERTY_MARGIN_RIGHT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_margin_right_new:
 * 
 * Creates a new #FoPropertyMarginRight initialized to default value.
 * 
 * Return value: the new #FoPropertyMarginRight.
 **/
FoProperty*
fo_property_margin_right_new (void)
{
  FoProperty* margin_right;

  margin_right =
    FO_PROPERTY (g_object_new (fo_property_margin_right_get_type (),
                               NULL));

  return margin_right;
}

/**
 * fo_property_margin_right_validate:
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
fo_property_margin_right_validate (FoDatatype *datatype,
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
      return datatype;
    }
  else if (FO_IS_STRING (datatype))
    {
      token = fo_string_get_value (datatype);

      new_datatype =
        fo_property_util_resolve_auto_enum (token, context, &tmp_error);

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
        fo_property_util_resolve_auto_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      if (tmp_error != NULL)
	{
	  g_propagate_error (error, tmp_error);
	  return NULL;
	}

      return new_datatype;
    }
  else if (FO_IS_LENGTH (datatype))
    {
      return datatype;
    }
  else if (FO_IS_PERCENTAGE (datatype))
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
 * fo_property_margin_right_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_margin_right_get_initial (void)
{
  static FoProperty *margin_right = NULL;

  if (margin_right == NULL)
    {
      margin_right = fo_property_margin_right_new ();
    }

  return margin_right;
}
