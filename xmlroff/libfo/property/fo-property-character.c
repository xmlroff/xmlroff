/* Fo
 * fo-property-character.c: 'character' property
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
#include "property/fo-property-character.h"
#include "property/fo-property-util.h"

/* character */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <character> */
/* Initial value: N/A, value is required */

struct _FoPropertyCharacter
{
  FoProperty parent_instance;
};

struct _FoPropertyCharacterClass
{
  FoPropertyClass parent_class;
};

static void fo_property_character_init         (FoPropertyCharacter      *property_character);
static void fo_property_character_class_init   (FoPropertyCharacterClass *klass);
static void fo_property_character_finalize     (GObject       *object);

static FoDatatype* fo_property_character_validate (FoDatatype *datatype,
                                                   FoContext  *context,
                                                   GError    **error);

static const gchar class_name[] = "character";
static gpointer parent_class;

/**
 * fo_property_character_get_type:
 * 
 * Register the #FoPropertyCharacter type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoPropertyCharacter.
 **/
GType
fo_property_character_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPropertyCharacterClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_property_character_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPropertyCharacter),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_property_character_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PROPERTY,
                                            class_name,
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_property_character_init:
 * @character: #FoPropertyCharacter object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPropertyCharacter.
 **/
void
fo_property_character_init (FoPropertyCharacter *character)
{
  FO_PROPERTY (character)->value =
    NULL;
}

/**
 * fo_property_character_class_init:
 * @klass: #FoPropertyCharacterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPropertyCharacterClass.
 **/
void
fo_property_character_class_init (FoPropertyCharacterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoPropertyClass *property_class = FO_PROPERTY_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_property_character_finalize;

  property_class->is_inherited = FALSE;
  property_class->is_shorthand = FALSE;
  property_class->resolve_enum =
    fo_property_util_resolve_no_enum;
  property_class->validate =
    fo_property_character_validate;
  property_class->get_initial =
    fo_property_character_get_initial;
}

/**
 * fo_property_character_finalize:
 * @object: #FoPropertyCharacter object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPropertyCharacter.
 **/
void
fo_property_character_finalize (GObject *object)
{
  FoPropertyCharacter *character;

  character = FO_PROPERTY_CHARACTER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_property_character_new:
 * 
 * Creates a new #FoPropertyCharacter initialized to default value.
 * 
 * Return value: the new #FoPropertyCharacter.
 **/
FoProperty*
fo_property_character_new (void)
{
  FoProperty* character;

  character =
    FO_PROPERTY (g_object_new (fo_property_character_get_type (),
                               NULL));

  return character;
}

/**
 * fo_property_character_validate:
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
fo_property_character_validate (FoDatatype *datatype,
                                FoContext  *context,
                                GError    **error)
{
  FoDatatype *new_datatype;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_DATATYPE (datatype), NULL);
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (context), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (FO_IS_CHAR (datatype))
    {
      return datatype;
    }
  else if (FO_IS_NAME (datatype))
    {
      new_datatype = fo_char_new_with_value (fo_name_get_value (datatype));

      g_object_unref (datatype);

      return (new_datatype);
    }
  else if (FO_IS_STRING (datatype))
    {
      new_datatype = fo_char_new_with_value (fo_string_get_value (datatype));

      g_object_unref (datatype);

      return (new_datatype);
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
 * fo_property_character_get_initial:
 * 
 * Get an instance of the property with the correct initial value.
 * 
 * Return value: An instance of the property.
 **/
FoProperty*
fo_property_character_get_initial (void)
{
  static FoProperty *character = NULL;

  if (character == NULL)
    {
      character =
	fo_property_character_new ();
    }

  return character;
}
