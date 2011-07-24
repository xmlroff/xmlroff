/* Fo
 * fo-property-block-progression-dimension-maximum.c: 'block-progression-dimension-maximum' property
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
#include "property/fo-property-block-progression-dimension-maximum.h"
#include "property/fo-property-util.h"

/* block-progression-dimension-maximum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <length> */
/* Initial value: auto */

struct _FoPropertyBlockProgressionDimensionMaximum
{
  FoProperty parent_instance;
};

struct _FoPropertyBlockProgressionDimensionMaximumClass
{
  FoPropertyClass parent_class;
};

static void fo_property_block_progression_dimension_maximum_init         (FoPropertyBlockProgressionDimensionMaximum      *property_block_progression_dimension_maximum);
static void fo_property_block_progression_dimension_maximum_class_init   (FoPropertyBlockProgressionDimensionMaximumClass *klass);
static void fo_property_block_progression_dimension_maximum_finalize     (GObject       *object);

static FoDatatype* fo_property_block_progression_dimension_maximum_validate (FoDatatype *datatype,
                                                                             FoContext  *context,
                                                                             GError    **error);

static const gchar class_name[] = "block-progression-dimension-maximum";
static gpointer parent_class;

/**
 * fo_property_block_progression_dimension_maximum_get_type:
 * 
 * Register the #FoPropertyBlockProgressionDimensionMaximum type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBlockProgressionDimensionMaximum.
 **/
GType
fo_property_block_progression_dimension_maximum_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBlockProgressionDimensionMaximumClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_block_progression_dimension_maximum_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBlockProgressionDimensionMaximum),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_block_progression_dimension_maximum_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_block_progression_dimension_maximum_init:
 * @block_progression_dimension_maximum: #FoPropertyBlockProgressionDimensionMaximum object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBlockProgressionDimensionMaximum.
 **/
void
fo_property_block_progression_dimension_maximum_init (FoPropertyBlockProgressionDimensionMaximum *block_progression_dimension_maximum)
{
  FO_PROPERTY (block_progression_dimension_maximum)->value =
    g_object_ref (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_AUTO));
}

/**
 * fo_property_block_progression_dimension_maximum_class_init:
 * @klass: #FoPropertyBlockProgressionDimensionMaximumClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBlockProgressionDimensionMaximumClass.
 **/
void
fo_property_block_progression_dimension_maximum_class_init (FoPropertyBlockProgressionDimensionMaximumClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_block_progression_dimension_maximum_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_auto_enum;
  property_class->validate =
    fo_property_block_progression_dimension_maximum_validate;
  property_class->get_initial =
    fo_property_block_progression_dimension_maximum_get_initial;
}

/**
 * fo_property_block_progression_dimension_maximum_finalize:
 * @object: #FoPropertyBlockProgressionDimensionMaximum object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBlockProgressionDimensionMaximum.
 **/
void
fo_property_block_progression_dimension_maximum_finalize (GObject *object)
{
  FoPropertyBlockProgressionDimensionMaximum *block_progression_dimension_maximum;

  block_progression_dimension_maximum = FO_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_block_progression_dimension_maximum_new:
 * 
 * Creates a new #FoPropertyBlockProgressionDimensionMaximum initialized to default value.
 * 
 * Return value: the new #FoPropertyBlockProgressionDimensionMaximum.
 **/
FoProperty*
fo_property_block_progression_dimension_maximum_new (void)
{
  FoProperty* block_progression_dimension_maximum;

  block_progression_dimension_maximum =
    FO_PROPERTY (g_object_new (fo_property_block_progression_dimension_maximum_get_type (),
                               NULL));

  return block_progression_dimension_maximum;
}

/**
 * fo_property_block_progression_dimension_maximum_validate:
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
fo_property_block_progression_dimension_maximum_validate (FoDatatype *datatype,
                                                          FoContext  *context,
                                                          GError    **error)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_LENGTH (datatype))
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
 * fo_property_block_progression_dimension_maximum_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_block_progression_dimension_maximum_get_initial (void)
{
  static FoProperty *block_progression_dimension_maximum = NULL;

  if (block_progression_dimension_maximum == NULL)
    {
      block_progression_dimension_maximum =
	fo_property_block_progression_dimension_maximum_new ();
    }

  return block_progression_dimension_maximum;
}
