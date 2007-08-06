/* Fo
 * fo-property-keep-with-previous-within-page.c: 'keep-with-previous-within-page' property
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
#include "property/fo-property-keep-with-previous-within-page.h"
#include "property/fo-property-util.h"

/* keep-with-previous-within-page */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <keep> | inherit */
/* Initial value: .within-line=auto, .within-column=auto, .within-page=auto */

struct _FoPropertyKeepWithPreviousWithinPage
{
  FoProperty parent_instance;
};

struct _FoPropertyKeepWithPreviousWithinPageClass
{
  FoPropertyClass parent_class;
};

static void fo_property_keep_with_previous_within_page_init         (FoPropertyKeepWithPreviousWithinPage      *property_keep_with_previous_within_page);
static void fo_property_keep_with_previous_within_page_class_init   (FoPropertyKeepWithPreviousWithinPageClass *klass);
static void fo_property_keep_with_previous_within_page_finalize     (GObject       *object);

static FoDatatype* fo_property_keep_with_previous_within_page_validate (FoDatatype *datatype,
                                                                        FoContext  *context,
                                                                        GError    **error);

static const gchar class_name[] = "FoPropertyKeepWithPreviousWithinPage";
static gpointer parent_class;

/**
 * fo_property_keep_with_previous_within_page_get_type:
 * 
 * Register the #FoPropertyKeepWithPreviousWithinPage type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyKeepWithPreviousWithinPage.
 **/
GType
fo_property_keep_with_previous_within_page_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyKeepWithPreviousWithinPageClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_keep_with_previous_within_page_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyKeepWithPreviousWithinPage),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_keep_with_previous_within_page_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_keep_with_previous_within_page_init:
 * @keep_with_previous_within_page: #FoPropertyKeepWithPreviousWithinPage object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyKeepWithPreviousWithinPage.
 **/
void
fo_property_keep_with_previous_within_page_init (FoPropertyKeepWithPreviousWithinPage *keep_with_previous_within_page)
{
  FO_PROPERTY (keep_with_previous_within_page)->value =
    g_object_ref (fo_enum_get_enum_auto ());
}

/**
 * fo_property_keep_with_previous_within_page_class_init:
 * @klass: #FoPropertyKeepWithPreviousWithinPageClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyKeepWithPreviousWithinPageClass.
 **/
void
fo_property_keep_with_previous_within_page_class_init (FoPropertyKeepWithPreviousWithinPageClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_keep_with_previous_within_page_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_auto_always_enum;
  property_class->validate =
    fo_property_keep_with_previous_within_page_validate;
  property_class->get_initial =
    fo_property_keep_with_previous_within_page_get_initial;
}

/**
 * fo_property_keep_with_previous_within_page_finalize:
 * @object: #FoPropertyKeepWithPreviousWithinPage object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyKeepWithPreviousWithinPage.
 **/
void
fo_property_keep_with_previous_within_page_finalize (GObject *object)
{
  FoPropertyKeepWithPreviousWithinPage *keep_with_previous_within_page;

  keep_with_previous_within_page = FO_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_keep_with_previous_within_page_new:
 * 
 * Creates a new #FoPropertyKeepWithPreviousWithinPage initialized to default value.
 * 
 * Return value: the new #FoPropertyKeepWithPreviousWithinPage.
 **/
FoProperty*
fo_property_keep_with_previous_within_page_new (void)
{
  FoProperty* keep_with_previous_within_page;

  keep_with_previous_within_page =
    FO_PROPERTY (g_object_new (fo_property_keep_with_previous_within_page_get_type (),
                               NULL));

  return keep_with_previous_within_page;
}

/**
 * fo_property_keep_with_previous_within_page_validate:
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
fo_property_keep_with_previous_within_page_validate (FoDatatype *datatype,
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
 * fo_property_keep_with_previous_within_page_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_keep_with_previous_within_page_get_initial (void)
{
  static FoProperty *keep_with_previous_within_page = NULL;

  if (keep_with_previous_within_page == NULL)
    {
      keep_with_previous_within_page =
	fo_property_keep_with_previous_within_page_new ();
    }

  return keep_with_previous_within_page;
}
