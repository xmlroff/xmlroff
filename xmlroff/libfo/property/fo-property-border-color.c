/* Fo
 * fo-property-border-color.c: 'border-color' property
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
#include "property/fo-property-border-color.h"
#include "property/fo-property-util.h"

/* border-color */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <color> | transparent ]{1,4} | inherit */
/* Initial value: see individual properties */

struct _FoPropertyBorderColor
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderColorClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_color_init         (FoPropertyBorderColor      *property_border_color);
static void fo_property_border_color_class_init   (FoPropertyBorderColorClass *klass);
static void fo_property_border_color_finalize     (GObject       *object);

static FoDatatype * fo_property_border_color_validate (FoDatatype *datatype,
						       FoContext  *context,
						       GError    **error);

static const gchar class_name[] = "FoPropertyBorderColor";
static gpointer parent_class;

/**
 * fo_property_border_color_get_type:
 * 
 * Register the #FoPropertyBorderColor type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderColor.
 **/
GType
fo_property_border_color_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderColorClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_color_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderColor),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_color_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_color_init:
 * @border_color: #FoPropertyBorderColor object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderColor.
 **/
void
fo_property_border_color_init (FoPropertyBorderColor *border_color)
{
  FO_PROPERTY (border_color)->value =
      NULL;
}

/**
 * fo_property_border_color_class_init:
 * @klass: #FoPropertyBorderColorClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderColorClass.
 **/
void
fo_property_border_color_class_init (FoPropertyBorderColorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_color_finalize;

  property_class->expr_eval = fo_expr_border_color_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_color_transparent_enum;
  property_class->validate =
    fo_property_border_color_validate;
  property_class->get_initial =
    fo_property_border_color_get_initial;
}

/**
 * fo_property_border_color_finalize:
 * @object: #FoPropertyBorderColor object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderColor.
 **/
void
fo_property_border_color_finalize (GObject *object)
{
  FoPropertyBorderColor *border_color;

  border_color = FO_PROPERTY_BORDER_COLOR (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_color_new:
 * 
 * Creates a new #FoPropertyBorderColor initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderColor.
 **/
FoProperty*
fo_property_border_color_new (void)
{
  FoProperty* border_color;

  border_color =
    FO_PROPERTY (g_object_new (fo_property_border_color_get_type (),
                               NULL));

  return border_color;
}

/**
 * fo_property_border_color_validate:
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
fo_property_border_color_validate (FoDatatype *datatype,
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
 * fo_property_border_color_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_color_get_initial (void)
{
  static FoProperty *border_color = NULL;

  if (border_color == NULL)
    {
      border_color =
	fo_property_border_color_new ();
    }

  return border_color;
}
