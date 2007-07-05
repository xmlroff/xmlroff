/* Fo
 * fo-property-flow-name.c: 'flow-name' property
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
#include "property/fo-property-flow-name.h"
#include "property/fo-property-util.h"

/* flow-name */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <name> */
/* Initial value: an empty name */

struct _FoPropertyFlowName
{
  FoProperty parent_instance;
};

struct _FoPropertyFlowNameClass
{
  FoPropertyClass parent_class;
};

static void fo_property_flow_name_init         (FoPropertyFlowName      *property_flow_name);
static void fo_property_flow_name_class_init   (FoPropertyFlowNameClass *klass);
static void fo_property_flow_name_finalize     (GObject       *object);

static FoDatatype* fo_property_flow_name_validate (FoDatatype *datatype,
                                                   FoContext  *context,
                                                   GError    **error);

static const gchar class_name[] = "flow-name";
static gpointer parent_class;

/**
 * fo_property_flow_name_get_type:
 * 
 * Register the #FoPropertyFlowName type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyFlowName.
 **/
GType
fo_property_flow_name_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyFlowNameClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_flow_name_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyFlowName),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_flow_name_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_flow_name_init:
 * @flow_name: #FoPropertyFlowName object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyFlowName.
 **/
void
fo_property_flow_name_init (FoPropertyFlowName *flow_name)
{
  FO_PROPERTY (flow_name)->value =
    NULL;
}

/**
 * fo_property_flow_name_class_init:
 * @klass: #FoPropertyFlowNameClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyFlowNameClass.
 **/
void
fo_property_flow_name_class_init (FoPropertyFlowNameClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_flow_name_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_auto_enum;
  property_class->validate =
    fo_property_flow_name_validate;
  property_class->get_initial =
    fo_property_flow_name_get_initial;
}

/**
 * fo_property_flow_name_finalize:
 * @object: #FoPropertyFlowName object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyFlowName.
 **/
void
fo_property_flow_name_finalize (GObject *object)
{
  FoPropertyFlowName *flow_name;

  flow_name = FO_PROPERTY_FLOW_NAME (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_flow_name_new:
 * 
 * Creates a new #FoPropertyFlowName initialized to default value.
 * 
 * Return value: the new #FoPropertyFlowName.
 **/
FoProperty*
fo_property_flow_name_new (void)
{
  FoProperty* flow_name;

  flow_name =
    FO_PROPERTY (g_object_new (fo_property_flow_name_get_type (),
                               NULL));

  return flow_name;
}

/**
 * fo_property_flow_name_validate:
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
fo_property_flow_name_validate (FoDatatype *datatype,
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
 * fo_property_flow_name_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_flow_name_get_initial (void)
{
  static FoProperty *flow_name = NULL;

  if (flow_name == NULL)
    {
      flow_name =
	fo_property_flow_name_new ();
    }

  return flow_name;
}
