/* Fo
 * fo-property-provisional-label-separation.c: 'provisional-label-separation' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-provisional-label-separation.c,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-provisional-label-separation.h"
#include "property/fo-property-util.h"

/* provisional-label-separation */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* <length> | <percentage> | inherit */
/* Initial value: 6.0pt */

struct _FoPropertyProvisionalLabelSeparation
{
  FoProperty parent_instance;
};

struct _FoPropertyProvisionalLabelSeparationClass
{
  FoPropertyClass parent_class;
};

static void fo_property_provisional_label_separation_init         (FoPropertyProvisionalLabelSeparation      *property_provisional_label_separation);
static void fo_property_provisional_label_separation_class_init   (FoPropertyProvisionalLabelSeparationClass *klass);
static void fo_property_provisional_label_separation_finalize     (GObject       *object);

static FoDatatype* fo_property_provisional_label_separation_validate (FoDatatype *datatype,
                                                                      FoContext  *context,
                                                                      GError    **error);

static const gchar class_name[] = "provisional-label-separation";
static gpointer parent_class;

/**
 * fo_property_provisional_label_separation_get_type:
 * 
 * Register the #FoPropertyProvisionalLabelSeparation type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyProvisionalLabelSeparation.
 **/
GType
fo_property_provisional_label_separation_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyProvisionalLabelSeparationClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_provisional_label_separation_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyProvisionalLabelSeparation),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_provisional_label_separation_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_provisional_label_separation_init:
 * @provisional_label_separation: #FoPropertyProvisionalLabelSeparation object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyProvisionalLabelSeparation.
 **/
void
fo_property_provisional_label_separation_init (FoPropertyProvisionalLabelSeparation *provisional_label_separation)
{
  FO_PROPERTY (provisional_label_separation)->value =
    g_object_ref (fo_length_get_length_6pt ());
}

/**
 * fo_property_provisional_label_separation_class_init:
 * @klass: #FoPropertyProvisionalLabelSeparationClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyProvisionalLabelSeparationClass.
 **/
void
fo_property_provisional_label_separation_class_init (FoPropertyProvisionalLabelSeparationClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_provisional_label_separation_finalize;

  property_class->is_inherited = TRUE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->validate =
    fo_property_provisional_label_separation_validate;
  property_class->get_initial =
    fo_property_provisional_label_separation_get_initial;
}

/**
 * fo_property_provisional_label_separation_finalize:
 * @object: #FoPropertyProvisionalLabelSeparation object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyProvisionalLabelSeparation.
 **/
void
fo_property_provisional_label_separation_finalize (GObject *object)
{
  FoPropertyProvisionalLabelSeparation *provisional_label_separation;

  provisional_label_separation = FO_PROPERTY_PROVISIONAL_LABEL_SEPARATION (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_provisional_label_separation_new:
 * 
 * Creates a new #FoPropertyProvisionalLabelSeparation initialized to default value.
 * 
 * Return value: the new #FoPropertyProvisionalLabelSeparation.
 **/
FoProperty*
fo_property_provisional_label_separation_new (void)
{
  FoProperty* provisional_label_separation;

  provisional_label_separation =
    FO_PROPERTY (g_object_new (fo_property_provisional_label_separation_get_type (),
                               NULL));

  return provisional_label_separation;
}

/**
 * fo_property_provisional_label_separation_validate:
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
fo_property_provisional_label_separation_validate (FoDatatype *datatype,
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
 * fo_property_provisional_label_separation_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_provisional_label_separation_get_initial (void)
{
  static FoProperty *provisional_label_separation = NULL;

  if (provisional_label_separation == NULL)
    {
      provisional_label_separation =
	fo_property_provisional_label_separation_new ();
    }

  return provisional_label_separation;
}
