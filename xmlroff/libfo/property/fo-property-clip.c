/* Fo
 * fo-property-clip.c: 'clip' property
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
#include "property/fo-property-clip.h"
#include "property/fo-property-util.h"

/* clip */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <shape> | auto | inherit */
/* Initial value: auto */

struct _FoPropertyClip
{
  FoProperty parent_instance;
};

struct _FoPropertyClipClass
{
  FoPropertyClass parent_class;
};

static void fo_property_clip_init         (FoPropertyClip      *property_clip);
static void fo_property_clip_class_init   (FoPropertyClipClass *klass);
static void fo_property_clip_finalize     (GObject       *object);

static FoDatatype* fo_property_clip_validate (FoDatatype *datatype,
                                              FoContext  *context,
                                              GError    **error);

static const gchar class_name[] = "clip";
static gpointer parent_class;

/**
 * fo_property_clip_get_type:
 * 
 * Register the #FoPropertyClip type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyClip.
 **/
GType
fo_property_clip_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyClipClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_clip_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyClip),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_clip_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_clip_init:
 * @clip: #FoPropertyClip object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyClip.
 **/
void
fo_property_clip_init (FoPropertyClip *clip)
{
  FO_PROPERTY (clip)->value =
    g_object_ref (fo_enum_factory_get_enum_by_value (FO_ENUM_ENUM_AUTO));
}

/**
 * fo_property_clip_class_init:
 * @klass: #FoPropertyClipClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyClipClass.
 **/
void
fo_property_clip_class_init (FoPropertyClipClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_clip_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_auto_enum;
  property_class->validate =
    fo_property_clip_validate;
  property_class->get_initial =
    fo_property_clip_get_initial;
}

/**
 * fo_property_clip_finalize:
 * @object: #FoPropertyClip object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyClip.
 **/
void
fo_property_clip_finalize (GObject *object)
{
  FoPropertyClip *clip;

  clip = FO_PROPERTY_CLIP (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_clip_new:
 * 
 * Creates a new #FoPropertyClip initialized to default value.
 * 
 * Return value: the new #FoPropertyClip.
 **/
FoProperty*
fo_property_clip_new (void)
{
  FoProperty* clip;

  clip =
    FO_PROPERTY (g_object_new (fo_property_clip_get_type (),
                               NULL));

  return clip;
}

/**
 * fo_property_clip_validate:
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
fo_property_clip_validate (FoDatatype *datatype,
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

    if (FO_IS_ENUM (datatype))
    {
      FoEnumEnum value = fo_enum_get_value (datatype);

      if ((value == FO_ENUM_ENUM_AUTO))
	{
	  return datatype;
	}
      else
	{
	  gchar *datatype_sprintf = fo_object_sprintf (datatype);

	  g_set_error (error,
		       FO_FO_ERROR,
		       FO_FO_ERROR_ENUMERATION_TOKEN,
		       _(fo_fo_error_messages[FO_FO_ERROR_ENUMERATION_TOKEN]),
		       class_name,
		       datatype_sprintf,
		       g_type_name (G_TYPE_FROM_INSTANCE (datatype)));

	  g_object_unref (datatype);

	  g_free (datatype_sprintf);

	  return NULL;
	}
    }
  else if (FO_IS_STRING (datatype))
    {
      token = fo_string_get_value (datatype);

      new_datatype =
        fo_property_util_resolve_auto_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      token = fo_name_get_value (datatype);

      new_datatype =
        fo_property_util_resolve_auto_enum (token, context, &tmp_error);

      g_object_unref (datatype);

      fo_propagate_and_return_val_if_error (error, tmp_error, NULL);

      return new_datatype;
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
 * fo_property_clip_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_clip_get_initial (void)
{
  static FoProperty *clip = NULL;

  if (clip == NULL)
    {
      clip =
	fo_property_clip_new ();
    }

  return clip;
}
