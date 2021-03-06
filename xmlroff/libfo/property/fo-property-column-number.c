/* Fo
 * fo-property-column-number.c: 'column-number' property
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
#include "property/fo-property-column-number.h"
#include "property/fo-property-util.h"

/* column-number */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <number> */
/* Initial value: see prose */

struct _FoPropertyColumnNumber
{
  FoProperty parent_instance;
};

struct _FoPropertyColumnNumberClass
{
  FoPropertyClass parent_class;
};

static void fo_property_column_number_init         (FoPropertyColumnNumber      *property_column_number);
static void fo_property_column_number_class_init   (FoPropertyColumnNumberClass *klass);
static void fo_property_column_number_finalize     (GObject       *object);

static FoDatatype* fo_property_column_number_validate (FoDatatype *datatype,
                                                       FoContext  *context,
                                                       GError    **error);

static const gchar class_name[] = "column-number";
static gpointer parent_class;

/**
 * fo_property_column_number_get_type:
 * 
 * Register the #FoPropertyColumnNumber type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyColumnNumber.
 **/
GType
fo_property_column_number_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyColumnNumberClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_column_number_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyColumnNumber),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_column_number_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_column_number_init:
 * @column_number: #FoPropertyColumnNumber object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyColumnNumber.
 **/
void
fo_property_column_number_init (FoPropertyColumnNumber *column_number)
{
  FO_PROPERTY (column_number)->value =
    NULL;
}

/**
 * fo_property_column_number_class_init:
 * @klass: #FoPropertyColumnNumberClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyColumnNumberClass.
 **/
void
fo_property_column_number_class_init (FoPropertyColumnNumberClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_column_number_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->validate =
    fo_property_column_number_validate;
  property_class->get_initial =
    fo_property_column_number_get_initial;
}

/**
 * fo_property_column_number_finalize:
 * @object: #FoPropertyColumnNumber object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyColumnNumber.
 **/
void
fo_property_column_number_finalize (GObject *object)
{
  FoPropertyColumnNumber *column_number;

  column_number = FO_PROPERTY_COLUMN_NUMBER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_column_number_new:
 * 
 * Creates a new #FoPropertyColumnNumber initialized to default value.
 * 
 * Return value: the new #FoPropertyColumnNumber.
 **/
FoProperty*
fo_property_column_number_new (void)
{
  FoProperty* column_number;

  column_number =
    FO_PROPERTY (g_object_new (fo_property_column_number_get_type (),
                               NULL));

  return column_number;
}

/**
 * fo_property_column_number_validate:
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
fo_property_column_number_validate (FoDatatype *datatype,
                                    FoContext  *context,
                                    GError    **error)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_NUMBER (datatype))
    {
      FoDatatype *new_datatype;
      gfloat number_value = fo_number_get_value (datatype);
      /* FIXME: There has to be a better way to do this conversion. */
      gint integer_value = number_value + 0.5;

      g_object_unref (datatype);

      new_datatype = fo_integer_new_with_value (MAX (integer_value, 1));

      return new_datatype;
    }
  else if (FO_IS_INTEGER (datatype))
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
 * fo_property_column_number_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_column_number_get_initial (void)
{
  static FoProperty *column_number = NULL;

  if (column_number == NULL)
    {
      column_number =
	fo_property_column_number_new ();
    }

  return column_number;
}
