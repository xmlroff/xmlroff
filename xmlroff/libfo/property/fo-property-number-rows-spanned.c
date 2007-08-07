/* Fo
 * fo-property-number-rows-spanned.c: 'number-rows-spanned' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <math.h>
#include <string.h>
#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-number-rows-spanned.h"
#include "property/fo-property-util.h"

/* number-rows-spanned */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <number> */
/* Initial value: 1 */

struct _FoPropertyNumberRowsSpanned
{
  FoProperty parent_instance;
};

struct _FoPropertyNumberRowsSpannedClass
{
  FoPropertyClass parent_class;
};

static void fo_property_number_rows_spanned_init         (FoPropertyNumberRowsSpanned      *property_number_rows_spanned);
static void fo_property_number_rows_spanned_class_init   (FoPropertyNumberRowsSpannedClass *klass);
static void fo_property_number_rows_spanned_finalize     (GObject       *object);

static FoDatatype* fo_property_number_rows_spanned_validate (FoDatatype *datatype,
                                                             FoContext  *context,
                                                             GError    **error);

static const gchar class_name[] = "number-rows-spanned";
static gpointer parent_class;

/**
 * fo_property_number_rows_spanned_get_type:
 * 
 * Register the #FoPropertyNumberRowsSpanned type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyNumberRowsSpanned.
 **/
GType
fo_property_number_rows_spanned_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyNumberRowsSpannedClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_number_rows_spanned_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyNumberRowsSpanned),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_number_rows_spanned_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_number_rows_spanned_init:
 * @number_rows_spanned: #FoPropertyNumberRowsSpanned object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyNumberRowsSpanned.
 **/
void
fo_property_number_rows_spanned_init (FoPropertyNumberRowsSpanned *number_rows_spanned)
{
  FO_PROPERTY (number_rows_spanned)->value =
    g_object_ref (fo_integer_get_integer_one ());
}

/**
 * fo_property_number_rows_spanned_class_init:
 * @klass: #FoPropertyNumberRowsSpannedClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyNumberRowsSpannedClass.
 **/
void
fo_property_number_rows_spanned_class_init (FoPropertyNumberRowsSpannedClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_number_rows_spanned_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->validate =
    fo_property_number_rows_spanned_validate;
  property_class->get_initial =
    fo_property_number_rows_spanned_get_initial;
}

/**
 * fo_property_number_rows_spanned_finalize:
 * @object: #FoPropertyNumberRowsSpanned object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyNumberRowsSpanned.
 **/
void
fo_property_number_rows_spanned_finalize (GObject *object)
{
  FoPropertyNumberRowsSpanned *number_rows_spanned;

  number_rows_spanned = FO_PROPERTY_NUMBER_ROWS_SPANNED (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_number_rows_spanned_new:
 * 
 * Creates a new #FoPropertyNumberRowsSpanned initialized to default value.
 * 
 * Return value: the new #FoPropertyNumberRowsSpanned.
 **/
FoProperty*
fo_property_number_rows_spanned_new (void)
{
  FoProperty* number_rows_spanned;

  number_rows_spanned =
    FO_PROPERTY (g_object_new (fo_property_number_rows_spanned_get_type (),
                               NULL));

  return number_rows_spanned;
}

/**
 * fo_property_number_rows_spanned_validate:
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
fo_property_number_rows_spanned_validate (FoDatatype *datatype,
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
 * fo_property_number_rows_spanned_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_number_rows_spanned_get_initial (void)
{
  static FoProperty *number_rows_spanned = NULL;

  if (number_rows_spanned == NULL)
    {
      number_rows_spanned =
	fo_property_number_rows_spanned_new ();
    }

  return number_rows_spanned;
}
