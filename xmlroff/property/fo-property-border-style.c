/* Fo
 * fo-property-border-style.c: 'border-style' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-border-style.c,v 1.3 2005/03/10 11:46:36 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "fo-context.h"
#include "datatype/fo-datatype.h"
#include "property/fo-property-private.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-border-style.h"
#include "property/fo-property-util.h"

/* border-style */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* <border-style>{1,4} | inherit */
/* Initial value: see individual properties */

struct _FoPropertyBorderStyle
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderStyleClass
{
  FoPropertyClass parent_class;
};

static void fo_property_border_style_init         (FoPropertyBorderStyle      *property_border_style);
static void fo_property_border_style_class_init   (FoPropertyBorderStyleClass *klass);
static void fo_property_border_style_finalize     (GObject       *object);

static FoDatatype * fo_property_border_style_validate (FoDatatype *datatype,
                                                       FoContext  *context,
                                                       GError    **error);

static const gchar class_name[] = "border-style";
static gpointer parent_class;

/**
 * fo_property_border_style_get_type:
 * 
 * Register the #FoPropertyBorderStyle type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyBorderStyle.
 **/
GType
fo_property_border_style_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyBorderStyleClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_border_style_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyBorderStyle),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_border_style_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_border_style_init:
 * @border_style: #FoPropertyBorderStyle object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyBorderStyle.
 **/
void
fo_property_border_style_init (FoPropertyBorderStyle *border_style)
{
  FO_PROPERTY (border_style)->value =
    NULL;
}

/**
 * fo_property_border_style_class_init:
 * @klass: #FoPropertyBorderStyleClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyBorderStyleClass.
 **/
void
fo_property_border_style_class_init (FoPropertyBorderStyleClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_border_style_finalize;

  property_class->expr_eval = fo_expr_border_style_eval;
  property_class->is_inherited = FALSE;
  property_class->is_shorthand = TRUE;
  property_class->resolve_enum =
    fo_property_util_resolve_style_enum;
  property_class->validate =
    fo_property_border_style_validate;
  property_class->get_initial =
    fo_property_border_style_get_initial;
}

/**
 * fo_property_border_style_finalize:
 * @object: #FoPropertyBorderStyle object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyBorderStyle.
 **/
void
fo_property_border_style_finalize (GObject *object)
{
  FoPropertyBorderStyle *border_style;

  border_style = FO_PROPERTY_BORDER_STYLE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_border_style_new:
 * 
 * Creates a new #FoPropertyBorderStyle initialized to default value.
 * 
 * Return value: the new #FoPropertyBorderStyle.
 **/
FoProperty*
fo_property_border_style_new (void)
{
  FoProperty* border_style;

  border_style =
    FO_PROPERTY (g_object_new (fo_property_border_style_get_type (),
                               NULL));

  return border_style;
}

/**
 * fo_property_border_style_validate:
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
fo_property_border_style_validate (FoDatatype *datatype,
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
 * fo_property_border_style_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_border_style_get_initial (void)
{
  static FoProperty *border_style = NULL;

  if (border_style == NULL)
    {
      border_style =
	fo_property_border_style_new ();
    }

  return border_style;
}
