/* Fo
 * fo-property-page-position.c: 'page-position' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-page-position.h"

/* page-position */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* first | last | rest | any | inherit */
/* Initial value: any */

struct _FoPropertyPagePosition
{
  FoProperty parent_instance;
};

struct _FoPropertyPagePositionClass
{
  FoPropertyClass parent_class;
};

static void fo_property_page_position_init         (FoPropertyPagePosition      *property_page_position);
static void fo_property_page_position_class_init   (FoPropertyPagePositionClass *klass);
static void fo_property_page_position_finalize     (GObject       *object);

static FoDatatype * fo_property_page_position_resolve_enum (const gchar *token,
                                                            FoContext   *context,
                                                            GError     **error);
static FoDatatype * fo_property_page_position_validate (FoDatatype *datatype,
                                                        FoContext  *context,
                                                        GError    **error);

static const gchar class_name[] = "page-position";
static gpointer parent_class;

/**
 * fo_property_page_position_get_type:
 * 
 * Register the #FoPropertyPagePosition type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyPagePosition.
 **/
GType
fo_property_page_position_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyPagePositionClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_page_position_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyPagePosition),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_page_position_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_page_position_init:
 * @page_position: #FoPropertyPagePosition object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyPagePosition.
 **/
void
fo_property_page_position_init (FoPropertyPagePosition *page_position)
{
  FO_PROPERTY (page_position)->value =
    g_object_ref (fo_enum_factory_get_enum_by_nick ("any"));
}

/**
 * fo_property_page_position_class_init:
 * @klass: #FoPropertyPagePositionClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyPagePositionClass.
 **/
void
fo_property_page_position_class_init (FoPropertyPagePositionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_page_position_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_page_position_resolve_enum;
  property_class->validate =
    fo_property_page_position_validate;
  property_class->get_initial =
    fo_property_page_position_get_initial;
}

/**
 * fo_property_page_position_finalize:
 * @object: #FoPropertyPagePosition object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyPagePosition.
 **/
void
fo_property_page_position_finalize (GObject *object)
{
  FoPropertyPagePosition *page_position;

  page_position = FO_PROPERTY_PAGE_POSITION (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_page_position_new:
 * 
 * Creates a new #FoPropertyPagePosition initialized to default value.
 * 
 * Return value: the new #FoPropertyPagePosition.
 **/
FoProperty*
fo_property_page_position_new (void)
{
  FoProperty* page_position;

  page_position =
    FO_PROPERTY (g_object_new (fo_property_page_position_get_type (),
                               NULL));

  return page_position;
}

/**
 * fo_property_page_position_resolve_enum:
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
fo_property_page_position_resolve_enum (const gchar *token,
                                        FoContext   *context,
                                        GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if ((strcmp (token, "first") == 0) ||
      (strcmp (token, "last") == 0) ||
      (strcmp (token, "rest") == 0) ||
      (strcmp (token, "any") == 0))
    {
      return g_object_ref (fo_enum_factory_get_enum_by_nick (token));
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
 * fo_property_page_position_validate:
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
fo_property_page_position_validate (FoDatatype *datatype,
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

      if ((value == FO_ENUM_ENUM_FIRST) ||
          (value == FO_ENUM_ENUM_LAST) ||
          (value == FO_ENUM_ENUM_REST) ||
          (value == FO_ENUM_ENUM_ANY))
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
        fo_property_page_position_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_page_position_resolve_enum (token, context, &tmp_error);

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
 * fo_property_page_position_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_page_position_get_initial (void)
{
  static FoProperty *page_position = NULL;

  if (page_position == NULL)
    {
      page_position =
	fo_property_page_position_new ();
    }

  return page_position;
}
