/* Fo
 * fo-property-type-condity.c: Abstract parent type of '.conditionality' components.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-type-condity-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-type-condity.h"
#include "property/fo-property-util.h"

/* type-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* discard | retain */
/* Initial value: discard */

static void fo_property_type_condity_base_init    (FoPropertyTypeCondityClass *klass);
static void fo_property_type_condity_class_init   (FoPropertyTypeCondityClass *klass);
static void fo_property_type_condity_finalize     (GObject       *object);

static FoDatatype* fo_property_type_condity_validate (FoDatatype *datatype,
                                                              FoContext  *context,
                                                              GError    **error);

static const gchar class_name[] = "FoProperytTypeCondity";
static gpointer parent_class;

/**
 * fo_property_type_condity_get_type:
 * 
 * Register the #FoPropertyTypeCondity type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyTypeCondity.
 **/
GType
fo_property_type_condity_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyTypeCondityClass),
        (GBaseInitFunc) fo_property_type_condity_base_init,
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_type_condity_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyTypeCondity),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_type_condity_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * fo_property_type_condity_init:
 * @type_condity: #FoPropertyTypeCondity object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyTypeCondity.
 **/
void
fo_property_type_condity_init (FoPropertyTypeCondity *type_condity)
{
  FO_PROPERTY (type_condity)->value =
    g_object_ref (fo_boolean_get_true ());
}

/**
 * fo_property_type_condity_base_init:
 * @klass: #FoPropertyTypeCondityClass object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPropertyTypeCondityClass.
 **/
void
fo_property_type_condity_base_init (FoPropertyTypeCondityClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  FoPropertyClass *fo_property_class = FO_PROPERTY_CLASS (klass);

  fo_property_class->is_inherited = FALSE;
  fo_property_class->is_shorthand = FALSE;
  fo_property_class->resolve_enum = fo_property_util_resolve_condity_enum;
  fo_property_class->validate = fo_property_type_condity_validate;
}

/**
 * fo_property_type_condity_class_init:
 * @klass: #FoPropertyTypeCondityClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyTypeCondityClass.
 **/
void
fo_property_type_condity_class_init (FoPropertyTypeCondityClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_type_condity_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_condity_enum;
  property_class->validate =
    fo_property_type_condity_validate;
}

/**
 * fo_property_type_condity_finalize:
 * @object: #FoPropertyTypeCondity object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyTypeCondity.
 **/
void
fo_property_type_condity_finalize (GObject *object)
{
  FoPropertyTypeCondity *type_condity;

  type_condity = FO_PROPERTY_TYPE_CONDITY (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_type_condity_new:
 * 
 * Creates a new #FoPropertyTypeCondity initialized to default value.
 * 
 * Return value: the new #FoPropertyTypeCondity.
 **/
FoProperty*
fo_property_type_condity_new (void)
{
  FoProperty* type_condity;

  type_condity =
    FO_PROPERTY (g_object_new (fo_property_type_condity_get_type (),
                               NULL));

  return type_condity;
}

/**
 * fo_property_type_condity_validate:
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
fo_property_type_condity_validate (FoDatatype *datatype,
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

  if (FO_IS_BOOLEAN (datatype))
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
