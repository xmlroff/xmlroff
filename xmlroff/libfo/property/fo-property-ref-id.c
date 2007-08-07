/* Fo
 * fo-property-ref-id.c: 'ref-id' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
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
#include "property/fo-property-ref-id.h"

/* ref-id */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <idref> | inherit */
/* Initial value: none, value required */

struct _FoPropertyRefId
{
  FoProperty parent_instance;
};

struct _FoPropertyRefIdClass
{
  FoPropertyClass parent_class;
};

static void fo_property_ref_id_init         (FoPropertyRefId      *property_ref_id);
static void fo_property_ref_id_class_init   (FoPropertyRefIdClass *klass);
static void fo_property_ref_id_finalize     (GObject       *object);

static FoDatatype * fo_property_ref_id_resolve_enum (const gchar *token,
                                                     FoContext   *context,
                                                     GError     **error);
static FoDatatype * fo_property_ref_id_validate (FoDatatype *datatype,
                                                 FoContext  *context,
                                                 GError    **error);

static const gchar class_name[] = "ref-id";
static gpointer parent_class;

/**
 * fo_property_ref_id_get_type:
 * 
 * Register the #FoPropertyRefId type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyRefId.
 **/
GType
fo_property_ref_id_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyRefIdClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_ref_id_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyRefId),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_ref_id_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_ref_id_init:
 * @ref_id: #FoPropertyRefId object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyRefId.
 **/
void
fo_property_ref_id_init (FoPropertyRefId *ref_id)
{
  FO_PROPERTY (ref_id)->value = NULL;
}

/**
 * fo_property_ref_id_class_init:
 * @klass: #FoPropertyRefIdClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyRefIdClass.
 **/
void
fo_property_ref_id_class_init (FoPropertyRefIdClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_ref_id_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_ref_id_resolve_enum;
  property_class->validate =
    fo_property_ref_id_validate;
  property_class->get_initial =
    fo_property_ref_id_get_initial;
}

/**
 * fo_property_ref_id_finalize:
 * @object: #FoPropertyRefId object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyRefId.
 **/
void
fo_property_ref_id_finalize (GObject *object)
{
  FoPropertyRefId *ref_id;

  ref_id = FO_PROPERTY_REF_ID (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_ref_id_new:
 * 
 * Creates a new #FoPropertyRefId initialized to default value.
 * 
 * Return value: the new #FoPropertyRefId.
 **/
FoProperty*
fo_property_ref_id_new (void)
{
  FoProperty* ref_id;

  ref_id =
    FO_PROPERTY (g_object_new (fo_property_ref_id_get_type (),
                               NULL));

  return ref_id;
}

/**
 * fo_property_ref_id_resolve_enum:
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
fo_property_ref_id_resolve_enum (const gchar *token,
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
 * fo_property_ref_id_validate:
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
fo_property_ref_id_validate (FoDatatype *datatype,
                             FoContext  *context,
                             GError    **error)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_NAME (datatype))
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
 * fo_property_ref_id_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_ref_id_get_initial (void)
{
  static FoProperty *ref_id = NULL;

  if (ref_id == NULL)
    {
      ref_id =
	fo_property_ref_id_new ();
    }

  return ref_id;
}
