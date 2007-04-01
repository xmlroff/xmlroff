/* Fo
 * fo-property-space-start.c: 'space-start' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-space-start.c,v 1.3 2003/12/16 17:10:43 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-space-start.h"

/* Inherited: FALSE */
/* Shorthand: FALSE */
/* space-start */
/* <space> | <percentage> | inherit */
/* NO ENUMERATED VALUE */


struct _FoPropertySpaceStart
{
  FoProperty parent_instance;
};

struct _FoPropertySpaceStartClass
{
  FoPropertyClass parent_class;
};

static void fo_property_space_start_init         (FoPropertySpaceStart      *property_space_start);
static void fo_property_space_start_class_init   (FoPropertySpaceStartClass *klass);
static void fo_property_space_start_finalize     (GObject       *object);

static FoDatatype* fo_property_space_start_resolve_enum (const gchar *token,
                                                       FoContext   *context,
                                                       GError     **error);
static FoDatatype* fo_property_space_start_validate (FoDatatype *datatype,
                                                   FoContext  *context,
                                                   GError    **error);

static const gchar class_name[] = "space-start";
static gpointer parent_class;

/**
 * fo_property_space_start_get_type:
 * 
 * Register the #FoPropertySpaceStart type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertySpaceStart.
 **/
GType
fo_property_space_start_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertySpaceStartClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_space_start_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertySpaceStart),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_space_start_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_space_start_init:
 * @space_start: #FoPropertySpaceStart object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertySpaceStart.
 **/
void
fo_property_space_start_init (FoPropertySpaceStart *space_start)
{
  FO_PROPERTY (space_start)->value =
    g_object_ref (fo_space_get_space_0pt ());
}

/**
 * fo_property_space_start_class_init:
 * @klass: #FoPropertySpaceStartClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertySpaceStartClass.
 **/
void
fo_property_space_start_class_init (FoPropertySpaceStartClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_space_start_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_space_start_resolve_enum;
  property_class->validate =
    fo_property_space_start_validate;
  property_class->get_initial =
    fo_property_space_start_get_initial;
}

/**
 * fo_property_space_start_finalize:
 * @object: #FoPropertySpaceStart object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertySpaceStart.
 **/
void
fo_property_space_start_finalize (GObject *object)
{
  FoPropertySpaceStart *space_start;

  space_start = FO_PROPERTY_SPACE_START (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_space_start_new:
 * 
 * Creates a new #FoPropertySpaceStart initialized to default value.
 * 
 * Return value: the new #FoPropertySpaceStart.
 **/
FoProperty*
fo_property_space_start_new (void)
{
  FoProperty* space_start;

  space_start =
    FO_PROPERTY (g_object_new (fo_property_space_start_get_type (),
                               NULL));

  return space_start;
}

/**
 * fo_property_space_start_resolve_enum:
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
fo_property_space_start_resolve_enum (const gchar *token,
                                    FoContext   *context,
                                    GError     **error)
{
  g_return_val_if_fail (token != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

      g_set_error (error,
		   FO_FO_ERROR,
		   FO_FO_ERROR_ENUMERATION_TOKEN,
		   _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		   class_name,
		   token);
      return NULL;
}

/**
 * fo_property_space_start_validate:
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
fo_property_space_start_validate (FoDatatype *datatype,
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

  if (FO_IS_SPACE (datatype))
    {
      return datatype;
    }
  else if (FO_IS_LENGTH (datatype))
    {
      new_datatype = fo_space_new_from_length (datatype);

      g_object_unref (datatype);

      return new_datatype;
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
 * fo_property_space_start_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_space_start_get_initial (void)
{
  static FoProperty *space_start = NULL;

  if (space_start == NULL)
    {
      space_start = fo_property_space_start_new ();
    }

  return space_start;
}
