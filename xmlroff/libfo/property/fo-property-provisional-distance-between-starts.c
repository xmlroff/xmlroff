/* Fo
 * fo-property-provisional-distance-between-starts.c: 'provisional-distance-between-starts' property
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
#include "property/fo-property-provisional-distance-between-starts.h"
#include "property/fo-property-util.h"

/* provisional-distance-between-starts */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <length> | <percentage> | inherit */
/* Initial value: 24.0pt */

struct _FoPropertyProvisionalDistanceBetweenStarts
{
  FoProperty parent_instance;
};

struct _FoPropertyProvisionalDistanceBetweenStartsClass
{
  FoPropertyClass parent_class;
};

static void fo_property_provisional_distance_between_starts_init         (FoPropertyProvisionalDistanceBetweenStarts      *property_provisional_distance_between_starts);
static void fo_property_provisional_distance_between_starts_class_init   (FoPropertyProvisionalDistanceBetweenStartsClass *klass);
static void fo_property_provisional_distance_between_starts_finalize     (GObject       *object);

static FoDatatype* fo_property_provisional_distance_between_starts_validate (FoDatatype *datatype,
                                                                             FoContext  *context,
                                                                             GError    **error);

static const gchar class_name[] = "provisional-distance-between-starts";
static gpointer parent_class;

/**
 * fo_property_provisional_distance_between_starts_get_type:
 * 
 * Register the #FoPropertyProvisionalDistanceBetweenStarts type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyProvisionalDistanceBetweenStarts.
 **/
GType
fo_property_provisional_distance_between_starts_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyProvisionalDistanceBetweenStartsClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_provisional_distance_between_starts_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyProvisionalDistanceBetweenStarts),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_provisional_distance_between_starts_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_provisional_distance_between_starts_init:
 * @provisional_distance_between_starts: #FoPropertyProvisionalDistanceBetweenStarts object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyProvisionalDistanceBetweenStarts.
 **/
void
fo_property_provisional_distance_between_starts_init (FoPropertyProvisionalDistanceBetweenStarts *provisional_distance_between_starts)
{
  FO_PROPERTY (provisional_distance_between_starts)->value =
    g_object_ref (fo_length_get_length_24 ());
}

/**
 * fo_property_provisional_distance_between_starts_class_init:
 * @klass: #FoPropertyProvisionalDistanceBetweenStartsClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyProvisionalDistanceBetweenStartsClass.
 **/
void
fo_property_provisional_distance_between_starts_class_init (FoPropertyProvisionalDistanceBetweenStartsClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_provisional_distance_between_starts_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->validate =
    fo_property_provisional_distance_between_starts_validate;
  property_class->get_initial =
    fo_property_provisional_distance_between_starts_get_initial;
}

/**
 * fo_property_provisional_distance_between_starts_finalize:
 * @object: #FoPropertyProvisionalDistanceBetweenStarts object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyProvisionalDistanceBetweenStarts.
 **/
void
fo_property_provisional_distance_between_starts_finalize (GObject *object)
{
  FoPropertyProvisionalDistanceBetweenStarts *provisional_distance_between_starts;

  provisional_distance_between_starts = FO_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_provisional_distance_between_starts_new:
 * 
 * Creates a new #FoPropertyProvisionalDistanceBetweenStarts initialized to default value.
 * 
 * Return value: the new #FoPropertyProvisionalDistanceBetweenStarts.
 **/
FoProperty*
fo_property_provisional_distance_between_starts_new (void)
{
  FoProperty* provisional_distance_between_starts;

  provisional_distance_between_starts =
    FO_PROPERTY (g_object_new (fo_property_provisional_distance_between_starts_get_type (),
                               NULL));

  return provisional_distance_between_starts;
}

/**
 * fo_property_provisional_distance_between_starts_validate:
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
fo_property_provisional_distance_between_starts_validate (FoDatatype *datatype,
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
 * fo_property_provisional_distance_between_starts_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_provisional_distance_between_starts_get_initial (void)
{
  static FoProperty *provisional_distance_between_starts = NULL;

  if (provisional_distance_between_starts == NULL)
    {
      provisional_distance_between_starts =
	fo_property_provisional_distance_between_starts_new ();
    }

  return provisional_distance_between_starts;
}
