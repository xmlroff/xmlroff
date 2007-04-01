/* Fo
 * fo-property-border-separation.c: 'border-separation' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-separation.c,v 1.3 2003/07/02 10:39:38 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-border-separation.h"

/* Inherited: TRUE */
/* Shorthand: FALSE */
/* border-separation */
/* <length-bp-ip-direction> | inherit */
/* NO ENUMERATED VALUE */


struct _FoPropertyBorderSeparation
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderSeparationClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_separation_init         (FoPropertyBorderSeparation      *property_border_separation);
static void fo_property_border_separation_class_init   (FoPropertyBorderSeparationClass *klass);
static void fo_property_border_separation_finalize     (GObject       *object);

static FoDatatype* fo_property_border_separation_resolve_enum (const gchar *token,
                                                               FoContext   *context,
                                                               GError     **error);
static FoDatatype* fo_property_border_separation_validate (FoDatatype *datatype,
                                                           FoContext  *context,
                                                           GError    **error);

static const gchar class_name[] = "border-separation";
static gpointer parent_class;

/**
 * fo_property_border_separation_get_type:
 * 
 * Register the #FoPropertyBorderSeparation type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderSeparation.
 **/
GType
fo_property_border_separation_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderSeparationClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_separation_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderSeparation),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_separation_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_separation_init:
 * @border_separation: #FoPropertyBorderSeparation object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderSeparation.
 **/
void
fo_property_border_separation_init (FoPropertyBorderSeparation *border_separation)
{
  FO_PROPERTY (border_separation)->value =
    NULL;
}

/**
 * fo_property_border_separation_class_init:
 * @klass: #FoPropertyBorderSeparationClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderSeparationClass.
 **/
void
fo_property_border_separation_class_init (FoPropertyBorderSeparationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_separation_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_border_separation_resolve_enum;
  property_class->validate =
    fo_property_border_separation_validate;
  property_class->get_initial =
    fo_property_border_separation_get_initial;
}

/**
 * fo_property_border_separation_finalize:
 * @object: #FoPropertyBorderSeparation object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderSeparation.
 **/
void
fo_property_border_separation_finalize (GObject *object)
{
  FoPropertyBorderSeparation *border_separation;

  border_separation = FO_PROPERTY_BORDER_SEPARATION (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_separation_new:
 * 
 * Creates a new #FoPropertyBorderSeparation initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderSeparation.
 **/
FoProperty*
fo_property_border_separation_new (void)
{
  FoProperty* border_separation;

  border_separation =
    FO_PROPERTY (g_object_new (fo_property_border_separation_get_type (),
                               NULL));

  return border_separation;
}

/**
 * fo_property_border_separation_resolve_enum:
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
fo_property_border_separation_resolve_enum (const gchar *token,
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
 * fo_property_border_separation_validate:
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
fo_property_border_separation_validate (FoDatatype *datatype,
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

  if (FO_IS_LENGTH_BP_IP_D (datatype))
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
 * fo_property_border_separation_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_separation_get_initial (void)
{
  static FoProperty *border_separation = NULL;

  if (border_separation == NULL)
    {
      border_separation = fo_property_border_separation_new ();
    }

  return border_separation;
}
