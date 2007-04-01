/* Fo
 * fo-property-padding.c: 'padding' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-padding.c,v 1.5 2004/05/02 22:53:14 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-padding.h"
#include "property/fo-property-util.h"

/* padding */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* <padding-width>{1,4} | inherit */
/* Initial value: not defined for shorthand properties */

struct _FoPropertyPadding
{
  FoProperty parent_instance;
};

struct _FoPropertyPaddingClass
{
  FoPropertyClass parent_class;
};

static void fo_property_padding_init         (FoPropertyPadding      *property_padding);
static void fo_property_padding_class_init   (FoPropertyPaddingClass *klass);
static void fo_property_padding_finalize     (GObject       *object);

static FoDatatype* fo_property_padding_validate (FoDatatype *datatype,
                                                 FoContext  *context,
                                                 GError    **error);

static const gchar class_name[] = "padding";
static gpointer parent_class;

/**
 * fo_property_padding_get_type:
 * 
 * Register the #FoPropertyPadding type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyPadding.
 **/
GType
fo_property_padding_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyPaddingClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_padding_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyPadding),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_padding_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_padding_init:
 * @padding: #FoPropertyPadding object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyPadding.
 **/
void
fo_property_padding_init (FoPropertyPadding *padding)
{
  FO_PROPERTY (padding)->value =
    NULL;
}

/**
 * fo_property_padding_class_init:
 * @klass: #FoPropertyPaddingClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyPaddingClass.
 **/
void
fo_property_padding_class_init (FoPropertyPaddingClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_padding_finalize;

  property_class->expr_eval = fo_expr_padding_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->resolve_percent =
    fo_property_util_resolve_ipdim_percent;
  property_class->validate =
    fo_property_padding_validate;
  property_class->get_initial =
    fo_property_padding_get_initial;
}

/**
 * fo_property_padding_finalize:
 * @object: #FoPropertyPadding object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyPadding.
 **/
void
fo_property_padding_finalize (GObject *object)
{
  FoPropertyPadding *padding;

  padding = FO_PROPERTY_PADDING (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_padding_new:
 * 
 * Creates a new #FoPropertyPadding initialized to default value.
 * 
 * Return value: the new #FoPropertyPadding.
 **/
FoProperty*
fo_property_padding_new (void)
{
  FoProperty* padding;

  padding =
    FO_PROPERTY (g_object_new (fo_property_padding_get_type (),
                               NULL));

  return padding;
}

/**
 * fo_property_padding_validate:
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
fo_property_padding_validate (FoDatatype *datatype,
                              FoContext  *context,
                              GError    **error)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_TBLR (datatype))
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
 * fo_property_padding_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_padding_get_initial (void)
{
  static FoProperty *padding = NULL;

  if (padding == NULL)
    {
      padding =
	fo_property_padding_new ();
    }

  return padding;
}
