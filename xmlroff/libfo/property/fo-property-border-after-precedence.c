/* Fo
 * fo-property-border-after-precedence.c: 'border-after-precedence' property
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
#include "property/fo-property-border-after-precedence.h"
#include "property/fo-property-util.h"

/* border-after-precedence */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* force | <integer> | inherit */
/* Initial value: fo:table: 6, fo:table-cell: 5, fo:table-column: 4, fo:table-row: 3, fo:table-body: 2, fo:table-header: 1, fo:table-footer: 0 */

struct _FoPropertyBorderAfterPrecedence
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderAfterPrecedenceClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_after_precedence_init         (FoPropertyBorderAfterPrecedence      *property_border_after_precedence);
static void fo_property_border_after_precedence_class_init   (FoPropertyBorderAfterPrecedenceClass *klass);
static void fo_property_border_after_precedence_finalize     (GObject       *object);

static FoDatatype* fo_property_border_after_precedence_validate (FoDatatype *datatype,
                                                                 FoContext  *context,
                                                                 GError    **error);

static const gchar class_name[] = "border-after-precedence";
static gpointer parent_class;

/**
 * fo_property_border_after_precedence_get_type:
 * 
 * Register the #FoPropertyBorderAfterPrecedence type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderAfterPrecedence.
 **/
GType
fo_property_border_after_precedence_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderAfterPrecedenceClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_after_precedence_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderAfterPrecedence),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_after_precedence_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_after_precedence_init:
 * @border_after_precedence: #FoPropertyBorderAfterPrecedence object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderAfterPrecedence.
 **/
void
fo_property_border_after_precedence_init (FoPropertyBorderAfterPrecedence *border_after_precedence)
{
  FO_PROPERTY (border_after_precedence)->value =
    NULL;
}

/**
 * fo_property_border_after_precedence_class_init:
 * @klass: #FoPropertyBorderAfterPrecedenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderAfterPrecedenceClass.
 **/
void
fo_property_border_after_precedence_class_init (FoPropertyBorderAfterPrecedenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_after_precedence_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_force_enum;
  property_class->validate =
    fo_property_border_after_precedence_validate;
  property_class->get_initial =
    fo_property_border_after_precedence_get_initial;
}

/**
 * fo_property_border_after_precedence_finalize:
 * @object: #FoPropertyBorderAfterPrecedence object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderAfterPrecedence.
 **/
void
fo_property_border_after_precedence_finalize (GObject *object)
{
  FoPropertyBorderAfterPrecedence *border_after_precedence;

  border_after_precedence = FO_PROPERTY_BORDER_AFTER_PRECEDENCE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_after_precedence_new:
 * 
 * Creates a new #FoPropertyBorderAfterPrecedence initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderAfterPrecedence.
 **/
FoProperty*
fo_property_border_after_precedence_new (void)
{
  FoProperty* border_after_precedence;

  border_after_precedence =
    FO_PROPERTY (g_object_new (fo_property_border_after_precedence_get_type (),
                               NULL));

  return border_after_precedence;
}

/**
 * fo_property_border_after_precedence_validate:
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
fo_property_border_after_precedence_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_FORCE))
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
        fo_property_util_resolve_force_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_util_resolve_force_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_INTEGER (datatype))
    {
      return datatype;
    }
  else if (FO_IS_NUMBER (datatype))
    {
      new_datatype =
        fo_integer_new_with_value ((gint) fo_number_get_value (datatype));

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

/**
 * fo_property_border_after_precedence_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_after_precedence_get_initial (void)
{
  static FoProperty *border_after_precedence = NULL;

  if (border_after_precedence == NULL)
    {
      border_after_precedence =
	fo_property_border_after_precedence_new ();
    }

  return border_after_precedence;
}
