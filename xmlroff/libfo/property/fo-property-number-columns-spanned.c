/* Fo
 * fo-property-number-columns-spanned.c: number-columns-spanned property
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
#include "property/fo-property-number-columns-spanned.h"
#include "property/fo-property-util.h"

/* number-columns-spanned */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <number> */
/* Initial value: 1 */

struct _FoPropertyNumberColumnsSpanned
{
  FoProperty parent_instance;
};

struct _FoPropertyNumberColumnsSpannedClass
{
  FoPropertyClass parent_class;
};

static void fo_property_number_columns_spanned_init         (FoPropertyNumberColumnsSpanned      *property_number_columns_spanned);
static void fo_property_number_columns_spanned_class_init   (FoPropertyNumberColumnsSpannedClass *klass);
static void fo_property_number_columns_spanned_finalize     (GObject       *object);

static FoDatatype* fo_property_number_columns_spanned_validate (FoDatatype *datatype,
                                                                FoContext  *context,
                                                                GError    **error);

static const gchar class_name[] = "number-columns-spanned";
static gpointer parent_class;

/**
 * fo_property_number_columns_spanned_get_type:
 * 
 * Register the #FoPropertyNumberColumnsSpanned type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyNumberColumnsSpanned.
 **/
GType
fo_property_number_columns_spanned_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyNumberColumnsSpannedClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_number_columns_spanned_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyNumberColumnsSpanned),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_number_columns_spanned_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_number_columns_spanned_init:
 * @number_columns_spanned: #FoPropertyNumberColumnsSpanned object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyNumberColumnsSpanned.
 **/
void
fo_property_number_columns_spanned_init (FoPropertyNumberColumnsSpanned *number_columns_spanned)
{
  FO_PROPERTY (number_columns_spanned)->value =
    g_object_ref (fo_integer_get_integer_one ());
}

/**
 * fo_property_number_columns_spanned_class_init:
 * @klass: #FoPropertyNumberColumnsSpannedClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyNumberColumnsSpannedClass.
 **/
void
fo_property_number_columns_spanned_class_init (FoPropertyNumberColumnsSpannedClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_number_columns_spanned_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->validate =
    fo_property_number_columns_spanned_validate;
  property_class->get_initial =
    fo_property_number_columns_spanned_get_initial;
}

/**
 * fo_property_number_columns_spanned_finalize:
 * @object: #FoPropertyNumberColumnsSpanned object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyNumberColumnsSpanned.
 **/
void
fo_property_number_columns_spanned_finalize (GObject *object)
{
  FoPropertyNumberColumnsSpanned *number_columns_spanned;

  number_columns_spanned = FO_PROPERTY_NUMBER_COLUMNS_SPANNED (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_number_columns_spanned_new:
 * 
 * Creates a new #FoPropertyNumberColumnsSpanned initialized to default value.
 * 
 * Return value: the new #FoPropertyNumberColumnsSpanned.
 **/
FoProperty*
fo_property_number_columns_spanned_new (void)
{
  FoProperty* number_columns_spanned;

  number_columns_spanned =
    FO_PROPERTY (g_object_new (fo_property_number_columns_spanned_get_type (),
                               NULL));

  return number_columns_spanned;
}

/**
 * fo_property_number_columns_spanned_validate:
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
fo_property_number_columns_spanned_validate (FoDatatype *datatype,
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
 * fo_property_number_columns_spanned_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_number_columns_spanned_get_initial (void)
{
  static FoProperty *number_columns_spanned = NULL;

  if (number_columns_spanned == NULL)
    {
      number_columns_spanned =
	fo_property_number_columns_spanned_new ();
    }

  return number_columns_spanned;
}
