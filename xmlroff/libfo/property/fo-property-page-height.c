/* Fo
 * fo-property-page-height.c: 'page-height' property
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
#include "property/fo-property-page-height.h"

/* page-height */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | indefinite | <length> | inherit */
/* Initial value: auto */

struct _FoPropertyPageHeight
{
  FoProperty parent_instance;
};

struct _FoPropertyPageHeightClass
{
  FoPropertyClass parent_class;
};

static void fo_property_page_height_init         (FoPropertyPageHeight      *property_page_height);
static void fo_property_page_height_class_init   (FoPropertyPageHeightClass *klass);
static void fo_property_page_height_finalize     (GObject       *object);

static FoDatatype* fo_property_page_height_resolve_enum (const gchar *token,
                                                         FoContext   *context,
                                                         GError     **error);
static FoDatatype* fo_property_page_height_validate (FoDatatype *datatype,
                                                     FoContext  *context,
                                                     GError    **error);

static const gchar class_name[] = "page-height";
static gpointer parent_class;

/**
 * fo_property_page_height_get_type:
 * 
 * Register the #FoPropertyPageHeight type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyPageHeight.
 **/
GType
fo_property_page_height_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyPageHeightClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_page_height_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyPageHeight),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_page_height_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_page_height_init:
 * @page_height: #FoPropertyPageHeight object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyPageHeight.
 **/
void
fo_property_page_height_init (FoPropertyPageHeight *page_height)
{
  FO_PROPERTY (page_height)->value =
    g_object_ref (fo_length_get_length_A4_height ());
}

/**
 * fo_property_page_height_class_init:
 * @klass: #FoPropertyPageHeightClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyPageHeightClass.
 **/
void
fo_property_page_height_class_init (FoPropertyPageHeightClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_page_height_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_page_height_resolve_enum;
  property_class->validate =
    fo_property_page_height_validate;
  property_class->get_initial =
    fo_property_page_height_get_initial;
}

/**
 * fo_property_page_height_finalize:
 * @object: #FoPropertyPageHeight object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyPageHeight.
 **/
void
fo_property_page_height_finalize (GObject *object)
{
  FoPropertyPageHeight *page_height;

  page_height = FO_PROPERTY_PAGE_HEIGHT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_page_height_new:
 * 
 * Creates a new #FoPropertyPageHeight initialized to default value.
 * 
 * Return value: the new #FoPropertyPageHeight.
 **/
FoProperty*
fo_property_page_height_new (void)
{
  FoProperty* page_height;

  page_height =
    FO_PROPERTY (g_object_new (fo_property_page_height_get_type (),
                               NULL));

  return page_height;
}

/**
 * fo_property_page_height_resolve_enum:
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
fo_property_page_height_resolve_enum (const gchar *token,
                                      FoContext   *context,
                                      GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "auto") == 0)
    {
      return g_object_ref (fo_length_get_length_A4_height ());
    }
  else if (strcmp (token, "indefinite") == 0)
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
 * fo_property_page_height_validate:
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
fo_property_page_height_validate (FoDatatype *datatype,
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
        fo_property_page_height_resolve_enum (token, context, &tmp_error);

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
        fo_property_page_height_resolve_enum (token, context, &tmp_error);

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
 * fo_property_page_height_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_page_height_get_initial (void)
{
  static FoProperty *page_height = NULL;

  if (page_height == NULL)
    {
      page_height =
	fo_property_page_height_new ();
    }

  return page_height;
}
