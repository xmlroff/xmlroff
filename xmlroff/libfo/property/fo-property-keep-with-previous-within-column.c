/* Fo
 * fo-property-keep-with-previous-within-column.c: 'keep-with-previous-within-column' property
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
#include "property/fo-property-keep-with-previous-within-column.h"
#include "property/fo-property-util.h"

/* keep-with-previous-within-column */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <keep> | inherit */
/* Initial value: .within-line=auto, .within-column=auto, .within-page=auto */

struct _FoPropertyKeepWithPreviousWithinColumn
{
  FoProperty parent_instance;
};

struct _FoPropertyKeepWithPreviousWithinColumnClass
{
  FoPropertyClass parent_class;
};

static void fo_property_keep_with_previous_within_column_init         (FoPropertyKeepWithPreviousWithinColumn      *property_keep_with_previous_within_column);
static void fo_property_keep_with_previous_within_column_class_init   (FoPropertyKeepWithPreviousWithinColumnClass *klass);
static void fo_property_keep_with_previous_within_column_finalize     (GObject       *object);

static FoDatatype* fo_property_keep_with_previous_within_column_validate (FoDatatype *datatype,
                                                                          FoContext  *context,
                                                                          GError    **error);

static const gchar class_name[] = "keep-with-previous-within-column";
static gpointer parent_class;

/**
 * fo_property_keep_with_previous_within_column_get_type:
 * 
 * Register the #FoPropertyKeepWithPreviousWithinColumn type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyKeepWithPreviousWithinColumn.
 **/
GType
fo_property_keep_with_previous_within_column_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyKeepWithPreviousWithinColumnClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_keep_with_previous_within_column_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyKeepWithPreviousWithinColumn),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_keep_with_previous_within_column_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_keep_with_previous_within_column_init:
 * @keep_with_previous_within_column: #FoPropertyKeepWithPreviousWithinColumn object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyKeepWithPreviousWithinColumn.
 **/
void
fo_property_keep_with_previous_within_column_init (FoPropertyKeepWithPreviousWithinColumn *keep_with_previous_within_column)
{
  FO_PROPERTY (keep_with_previous_within_column)->value =
    g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_property_keep_with_previous_within_column_class_init:
 * @klass: #FoPropertyKeepWithPreviousWithinColumnClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyKeepWithPreviousWithinColumnClass.
 **/
void
fo_property_keep_with_previous_within_column_class_init (FoPropertyKeepWithPreviousWithinColumnClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_keep_with_previous_within_column_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_auto_always_enum;
  property_class->validate =
    fo_property_keep_with_previous_within_column_validate;
  property_class->get_initial =
    fo_property_keep_with_previous_within_column_get_initial;
}

/**
 * fo_property_keep_with_previous_within_column_finalize:
 * @object: #FoPropertyKeepWithPreviousWithinColumn object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyKeepWithPreviousWithinColumn.
 **/
void
fo_property_keep_with_previous_within_column_finalize (GObject *object)
{
  FoPropertyKeepWithPreviousWithinColumn *keep_with_previous_within_column;

  keep_with_previous_within_column = FO_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_COLUMN (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_keep_with_previous_within_column_new:
 * 
 * Creates a new #FoPropertyKeepWithPreviousWithinColumn initialized to default value.
 * 
 * Return value: the new #FoPropertyKeepWithPreviousWithinColumn.
 **/
FoProperty*
fo_property_keep_with_previous_within_column_new (void)
{
  FoProperty* keep_with_previous_within_column;

  keep_with_previous_within_column =
    FO_PROPERTY (g_object_new (fo_property_keep_with_previous_within_column_get_type (),
                               NULL));

  return keep_with_previous_within_column;
}

/**
 * fo_property_keep_with_previous_within_column_validate:
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
fo_property_keep_with_previous_within_column_validate (FoDatatype *datatype,
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
        fo_property_util_resolve_auto_always_enum (token, context, &tmp_error);

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
        fo_property_util_resolve_auto_always_enum (token, context, &tmp_error);

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
 * fo_property_keep_with_previous_within_column_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_keep_with_previous_within_column_get_initial (void)
{
  static FoProperty *keep_with_previous_within_column = NULL;

  if (keep_with_previous_within_column == NULL)
    {
      keep_with_previous_within_column =
	fo_property_keep_with_previous_within_column_new ();
    }

  return keep_with_previous_within_column;
}
