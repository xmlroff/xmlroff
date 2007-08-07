/* Fo
 * fo-property-src.c: 'src' property
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
#include "property/fo-property-src.h"
#include "property/fo-property-util.h"

/* src */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <uri-specification> | inherit */
/* Initial value: none, value required */

struct _FoPropertySrc
{
  FoProperty parent_instance;
};

struct _FoPropertySrcClass
{
  FoPropertyClass parent_class;
};

static void fo_property_src_init         (FoPropertySrc      *property_src);
static void fo_property_src_class_init   (FoPropertySrcClass *klass);
static void fo_property_src_finalize     (GObject       *object);

static FoDatatype * fo_property_src_validate (FoDatatype *datatype,
                                              FoContext  *context,
                                              GError    **error);

static const gchar class_name[] = "src";
static gpointer parent_class;

/**
 * fo_property_src_get_type:
 * 
 * Register the #FoPropertySrc type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertySrc.
 **/
GType
fo_property_src_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertySrcClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_src_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertySrc),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_src_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_src_init:
 * @src: #FoPropertySrc object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertySrc.
 **/
void
fo_property_src_init (FoPropertySrc *src)
{
  FO_PROPERTY (src)->value =
    NULL;
}

/**
 * fo_property_src_class_init:
 * @klass: #FoPropertySrcClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertySrcClass.
 **/
void
fo_property_src_class_init (FoPropertySrcClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_src_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->validate =
    fo_property_src_validate;
  property_class->get_initial =
    fo_property_src_get_initial;
}

/**
 * fo_property_src_finalize:
 * @object: #FoPropertySrc object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertySrc.
 **/
void
fo_property_src_finalize (GObject *object)
{
  FoPropertySrc *src;

  src = FO_PROPERTY_SRC (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_src_new:
 * 
 * Creates a new #FoPropertySrc initialized to default value.
 * 
 * Return value: the new #FoPropertySrc.
 **/
FoProperty*
fo_property_src_new (void)
{
  FoProperty* src;

  src =
    FO_PROPERTY (g_object_new (fo_property_src_get_type (),
                               NULL));

  return src;
}

/**
 * fo_property_src_validate:
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
fo_property_src_validate (FoDatatype *datatype,
                          FoContext  *context,
                          GError    **error)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_URI_SPECIFICATION (datatype))
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
 * fo_property_src_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_src_get_initial (void)
{
  static FoProperty *src = NULL;

  if (src == NULL)
    {
      src =
	fo_property_src_new ();
    }

  return src;
}
