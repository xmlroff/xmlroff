/* Fo
 * fo-property-role.c: 'role' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-role.c,v 1.5 2005/08/14 19:31:56 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-role.h"

/* role */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <string> | <uri-specification> | none | inherit */
/* Initial value: none */

struct _FoPropertyRole
{
  FoProperty parent_instance;
};

struct _FoPropertyRoleClass
{
  FoPropertyClass parent_class;
};

static void fo_property_role_init         (FoPropertyRole      *property_role);
static void fo_property_role_class_init   (FoPropertyRoleClass *klass);
static void fo_property_role_finalize     (GObject       *object);

static FoDatatype * fo_property_role_resolve_enum (const gchar *token,
                                                    FoContext   *context,
                                                    GError     **error);
static FoDatatype * fo_property_role_validate (FoDatatype *datatype,
                                               FoContext  *context,
                                               GError    **error);

static const gchar class_name[] = "role";
static gpointer parent_class;

/**
 * fo_property_role_get_type:
 * 
 * Register the #FoPropertyRole type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyRole.
 **/
GType
fo_property_role_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyRoleClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_role_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyRole),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_role_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_role_init:
 * @role: #FoPropertyRole object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyRole.
 **/
void
fo_property_role_init (FoPropertyRole *role)
{
  FO_PROPERTY (role)->value =
    g_object_ref (fo_enum_get_enum_by_nick ("none"));
}

/**
 * fo_property_role_class_init:
 * @klass: #FoPropertyRoleClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyRoleClass.
 **/
void
fo_property_role_class_init (FoPropertyRoleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_role_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_role_resolve_enum;
  property_class->validate =
    fo_property_role_validate;
  property_class->get_initial =
    fo_property_role_get_initial;
}

/**
 * fo_property_role_finalize:
 * @object: #FoPropertyRole object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyRole.
 **/
void
fo_property_role_finalize (GObject *object)
{
  FoPropertyRole *role;

  role = FO_PROPERTY_ROLE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_role_new:
 * 
 * Creates a new #FoPropertyRole initialized to default value.
 * 
 * Return value: the new #FoPropertyRole.
 **/
FoProperty*
fo_property_role_new (void)
{
  FoProperty* role;

  role =
    FO_PROPERTY (g_object_new (fo_property_role_get_type (),
                               NULL));

  return role;
}

/**
 * fo_property_role_resolve_enum:
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
fo_property_role_resolve_enum (const gchar *token,
                               FoContext   *context,
                               GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (strcmp (token, "none") == 0)
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
 * fo_property_role_validate:
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
fo_property_role_validate (FoDatatype *datatype,
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

  if (FO_IS_STRING (datatype))
    {
      return datatype;
    }
  else if (FO_IS_URI_SPECIFICATION (datatype))
    {
      return datatype;
    }
  else if (FO_IS_ENUM (datatype))
    {
      FoEnumEnum value = fo_enum_get_value (datatype);

      if ((value == FO_ENUM_ENUM_NONE))
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
        fo_property_role_resolve_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_role_resolve_enum (token, context, &tmp_error);

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
 * fo_property_role_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_role_get_initial (void)
{
  static FoProperty *role = NULL;

  if (role == NULL)
    {
      role =
	fo_property_role_new ();
    }

  return role;
}
