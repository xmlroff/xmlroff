/* Fo
 * fo-property-text-property.c: Inline formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-text-property.c,v 1.1 2003/02/28 01:50:02 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-property-text-property.h"

static void fo_property_text_property_base_init  (FoPropertyTextPropertyIface *klass);
static PangoAttribute* fo_property_text_property_new_attr_default (FoProperty *property);
static PangoAttribute* fo_property_text_property_new_attr_from_context_default (FoProperty *property,
										FoContext  *context);

/**
 * fo_property_text_property_get_type:
 * 
 * Register the #FoPropertyTextProperty type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyTextProperty.
 **/
GType
fo_property_text_property_get_type (void)
{
  static GType text_property_type = 0;

  if (!text_property_type)
    {
      static const GTypeInfo text_property_info =
      {
        sizeof (FoPropertyTextPropertyIface), /* class_size */
	(GBaseInitFunc) fo_property_text_property_base_init,   	/* base_init */
	NULL,		/* base_finalize */
	NULL,
	NULL,		/* class_finalize */
	NULL,		/* class_data */
	0,
	0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      text_property_type = g_type_register_static (G_TYPE_INTERFACE,
						   "FoPropertyTextPropertyIface",
						   &text_property_info, 0);
      g_type_interface_add_prerequisite (text_property_type, FO_TYPE_PROPERTY);
    }

  return text_property_type;
}

/**
 * fo_property_text_property_base_init:
 * @klass: #FoPropertyTextPropertyClass object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPropertyTextPropertyClass.
 **/
void
fo_property_text_property_base_init  (FoPropertyTextPropertyIface *klass)
{
  klass->new_attr =
    fo_property_text_property_new_attr_default;
  klass->new_attr_from_context =
    fo_property_text_property_new_attr_from_context_default;
}

/**
 * fo_property_text_property_new_attr:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the value of @property.
 * 
 * Return value: New #PangoAttribute for @property.
 **/
PangoAttribute *
fo_property_text_property_new_attr (FoProperty *property)
{
  g_return_val_if_fail (property != NULL, NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_TEXT_PROPERTY (property), NULL);

  return FO_PROPERTY_TEXT_PROPERTY_GET_IFACE (property)->new_attr (property);
}

/**
 * fo_property_text_property_new_attr_default:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * 
 * Makes a new #PangoAttribute representing the value of @property.
 * 
 * Return value: New #PangoAttribute for @property.
 **/
PangoAttribute*
fo_property_text_property_new_attr_default (FoProperty *property)
{
  g_return_val_if_fail (property != NULL, NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_TEXT_PROPERTY (property), NULL);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'new_attr' function."),
	 fo_object_sprintf (property));

  return NULL;
}

/**
 * fo_property_text_property_new_attr_from_context:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * @context:  #FoContext from which to take additional property values.
 * 
 * Makes a new #PangoAttribute representing the value of @property.
 * 
 * Return value: New #PangoAttribute for @property.
 **/
PangoAttribute *
fo_property_text_property_new_attr_from_context (FoProperty *property,
						 FoContext  *context)
{
  g_return_val_if_fail (property != NULL, NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_TEXT_PROPERTY (property), NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);

  return FO_PROPERTY_TEXT_PROPERTY_GET_IFACE (property)->new_attr_from_context (property,
										context);
}

/**
 * fo_property_text_property_new_attr_from_context_default:
 * @property: #FoProperty from which to create a #PangoAttribute.
 * @context:  #FoContext from which to take additional property values.
 * 
 * Makes a new #PangoAttribute representing the value of @property.
 * 
 * Return value: New #PangoAttribute for @property.
 **/
PangoAttribute*
fo_property_text_property_new_attr_from_context_default (FoProperty *property,
							 FoContext  *context)
{
  g_return_val_if_fail (property != NULL, NULL);
  g_return_val_if_fail (FO_IS_PROPERTY_TEXT_PROPERTY (property), NULL);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'new_attr_from_context' function."),
	 fo_object_sprintf (property));

  return NULL;
}
