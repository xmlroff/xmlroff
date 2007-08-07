/* Fo
 * fo-property-border-width.c: 'border-width' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
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
#include "property/fo-property-border-width.h"
#include "property/fo-property-util.h"

/* border-width */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* <border-width>{1,4} | inherit */
/* Initial value: see individual properties */

struct _FoPropertyBorderWidth
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderWidthClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_width_init         (FoPropertyBorderWidth      *property_border_width);
static void fo_property_border_width_class_init   (FoPropertyBorderWidthClass *klass);
static void fo_property_border_width_finalize     (GObject       *object);

static FoDatatype * fo_property_border_width_validate (FoDatatype *datatype,
                                                       FoContext  *context,
                                                       GError    **error);

static const gchar class_name[] = "border-width";
static gpointer parent_class;

/**
 * fo_property_border_width_get_type:
 * 
 * Register the #FoPropertyBorderWidth type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderWidth.
 **/
GType
fo_property_border_width_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderWidthClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_width_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderWidth),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_width_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_width_init:
 * @border_width: #FoPropertyBorderWidth object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderWidth.
 **/
void
fo_property_border_width_init (FoPropertyBorderWidth *border_width)
{
  FO_PROPERTY (border_width)->value =
    NULL;
}

/**
 * fo_property_border_width_class_init:
 * @klass: #FoPropertyBorderWidthClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderWidthClass.
 **/
void
fo_property_border_width_class_init (FoPropertyBorderWidthClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_width_finalize;

  property_class->expr_eval = fo_expr_padding_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_width_enum;
  property_class->validate =
    fo_property_border_width_validate;
  property_class->get_initial =
    fo_property_border_width_get_initial;
}

/**
 * fo_property_border_width_finalize:
 * @object: #FoPropertyBorderWidth object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderWidth.
 **/
void
fo_property_border_width_finalize (GObject *object)
{
  FoPropertyBorderWidth *border_width;

  border_width = FO_PROPERTY_BORDER_WIDTH (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_width_new:
 * 
 * Creates a new #FoPropertyBorderWidth initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderWidth.
 **/
FoProperty*
fo_property_border_width_new (void)
{
  FoProperty* border_width;

  border_width =
    FO_PROPERTY (g_object_new (fo_property_border_width_get_type (),
                               NULL));

  return border_width;
}

/**
 * fo_property_border_width_validate:
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
fo_property_border_width_validate (FoDatatype *datatype,
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
 * fo_property_border_width_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_width_get_initial (void)
{
  static FoProperty *border_width = NULL;

  if (border_width == NULL)
    {
      border_width =
	fo_property_border_width_new ();
    }

  return border_width;
}
