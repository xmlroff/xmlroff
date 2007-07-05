/* Fo
 * fo-property-space-before-conditionality.c: 'space-before-conditionality' property
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
#include "property/fo-property-space-before-conditionality.h"
#include "property/fo-property-util.h"

/* space-before-conditionality */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

struct _FoPropertySpaceBeforeCondity
{
  FoProperty parent_instance;
};

struct _FoPropertySpaceBeforeCondityClass
{
  FoPropertyClass parent_class;
};

static void fo_property_space_before_condity_init         (FoPropertySpaceBeforeCondity      *property_space_before_condity);
static void fo_property_space_before_condity_class_init   (FoPropertySpaceBeforeCondityClass *klass);
static void fo_property_space_before_condity_finalize     (GObject       *object);

static FoDatatype* fo_property_space_before_condity_validate (FoDatatype *datatype,
                                                              FoContext  *context,
                                                              GError    **error);

static const gchar class_name[] = "space-before-conditionality";
static gpointer parent_class;

/**
 * fo_property_space_before_condity_get_type:
 * 
 * Register the #FoPropertySpaceBeforeCondity type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertySpaceBeforeCondity.
 **/
GType
fo_property_space_before_condity_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertySpaceBeforeCondityClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_space_before_condity_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertySpaceBeforeCondity),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_space_before_condity_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_space_before_condity_init:
 * @space_before_condity: #FoPropertySpaceBeforeCondity object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertySpaceBeforeCondity.
 **/
void
fo_property_space_before_condity_init (FoPropertySpaceBeforeCondity *space_before_condity)
{
  FO_PROPERTY (space_before_condity)->value =
    g_object_ref (fo_boolean_get_true ());
}

/**
 * fo_property_space_before_condity_class_init:
 * @klass: #FoPropertySpaceBeforeCondityClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertySpaceBeforeCondityClass.
 **/
void
fo_property_space_before_condity_class_init (FoPropertySpaceBeforeCondityClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_space_before_condity_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_condity_enum;
  property_class->validate =
    fo_property_space_before_condity_validate;
  property_class->get_initial =
    fo_property_space_before_condity_get_initial;
}

/**
 * fo_property_space_before_condity_finalize:
 * @object: #FoPropertySpaceBeforeCondity object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertySpaceBeforeCondity.
 **/
void
fo_property_space_before_condity_finalize (GObject *object)
{
  FoPropertySpaceBeforeCondity *space_before_condity;

  space_before_condity = FO_PROPERTY_SPACE_BEFORE_CONDITY (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_space_before_condity_new:
 * 
 * Creates a new #FoPropertySpaceBeforeCondity initialized to default value.
 * 
 * Return value: the new #FoPropertySpaceBeforeCondity.
 **/
FoProperty*
fo_property_space_before_condity_new (void)
{
  FoProperty* space_before_condity;

  space_before_condity =
    FO_PROPERTY (g_object_new (fo_property_space_before_condity_get_type (),
                               NULL));

  return space_before_condity;
}

/**
 * fo_property_space_before_condity_validate:
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
fo_property_space_before_condity_validate (FoDatatype *datatype,
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

/**
 * fo_property_space_before_condity_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_space_before_condity_get_initial (void)
{
  static FoProperty *space_before_condity = NULL;

  if (space_before_condity == NULL)
    {
      space_before_condity =
	fo_property_space_before_condity_new ();
    }

  return space_before_condity;
}
