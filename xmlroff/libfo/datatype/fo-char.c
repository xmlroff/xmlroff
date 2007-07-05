/* Fo
 * fo-char.c: Character datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-char.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoChar
{
  FoDatatype parent_instance;

  gchar* value;
};

struct _FoCharClass
{
  FoDatatypeClass parent_class;
};

static void fo_char_init        (FoChar      *fo_char);
static void fo_char_class_init  (FoCharClass *klass);
static void fo_char_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_char_get_property (GObject         *object,
				  guint            prop_id,
				  GValue          *value,
				  GParamSpec      *pspec);
static void fo_char_finalize    (GObject           *object);

static gchar*       fo_char_sprintf   (FoObject   *fo_object);
static FoDatatype * fo_char_copy      (FoDatatype *datatype);
static void         fo_char_set_value (FoDatatype  *fo_char,
				       const gchar *new_value);

static gpointer parent_class;

/**
 * fo_char_get_type:
 * 
 * Register the #FoChar object type.
 * 
 * Return value: #GType value of the #FoChar object type.
 **/
GType
fo_char_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoCharClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_char_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoChar),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_char_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoChar",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_char_init:
 * @char: #FoChar object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoChar.
 **/
void
fo_char_init (FoChar *fo_char)
{
  fo_char->value = NULL;
}

/**
 * fo_char_class_init:
 * @klass: #FoCharClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoCharClass.
 **/
void
fo_char_class_init (FoCharClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_char_finalize;

  object_class->set_property = fo_char_set_property;
  object_class->get_property = fo_char_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_char_sprintf;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_string ("value",
							_("Value"),
							_("FoChar value"),
							NULL,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  FO_DATATYPE_CLASS (klass)->copy = fo_char_copy;
}

/**
 * fo_char_finalize:
 * @object: #FoChar object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoChar.
 **/
void
fo_char_finalize (GObject *object)
{
  FoChar *fo_char;

  fo_char = FO_CHAR (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_char_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoChar.
 **/
void
fo_char_get_property (GObject         *object,
		      guint            prop_id,
		      GValue          *value,
		      GParamSpec      *pspec)
{
  FoDatatype *fo_char;

  fo_char = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_string (value, fo_char_get_value (fo_char));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_char_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoChar.
 **/
void
fo_char_set_property (GObject         *object,
		      guint            prop_id,
		      const GValue    *value,
		      GParamSpec      *pspec)
{
  FoDatatype *fo_char;

  fo_char = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_char_set_value (fo_char, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_char_new:
 * 
 * Creates a new #FoChar initialized to default value.
 * 
 * Return value: the new #FoChar.
 **/
FoDatatype *
fo_char_new (void)
{
  FoDatatype *fo_char;

  fo_char = FO_DATATYPE (g_object_new (fo_char_get_type (), NULL));
  
  return fo_char;
}

/**
 * fo_char_new_with_value:
 * @value: String value of the new #FoChar.
 * 
 * Creates a new #FoChar set to @value.
 * 
 * Return value: The new #FoChar.
 **/
FoDatatype*
fo_char_new_with_value (const gchar *value)
{
  FoDatatype *fo_char = fo_char_new ();

  fo_char_set_value (fo_char, value);

  return fo_char;
}

/**
 * fo_char_get_value:
 * @fo_char: #FoChar.
 * 
 * Get the value of @fo_char.
 * 
 * Return value: String value of @fo_char.
 **/
const gchar*
fo_char_get_value (FoDatatype *fo_char)
{
  g_return_val_if_fail (fo_char != NULL, 0);
  g_return_val_if_fail (FO_IS_CHAR (fo_char), 0);

  return FO_CHAR (fo_char)->value;
}

/**
 * fo_char_set_value:
 * @fo_char:    #FoChar.
 * @new_value: New value for @fo_char.
 * 
 * Set the value of @fo_char.
 **/
void
fo_char_set_value (FoDatatype *fo_char,
		   const gchar *new_value)
{
  g_return_if_fail (fo_char != NULL);
  g_return_if_fail (FO_IS_CHAR (fo_char));

  FO_CHAR (fo_char)->value = g_strdup (new_value);
  /*g_object_notify (G_OBJECT (fo_char), "value");*/
}

/**
 * fo_char_copy:
 * @datatype: #FoChar to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoChar.
 **/
FoDatatype*
fo_char_copy (FoDatatype *datatype)
{
  FoDatatype *fo_char;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHAR (datatype), NULL);

  fo_char = fo_char_new ();
  FO_CHAR (fo_char)->value = FO_CHAR (datatype)->value;

  return fo_char;
}

/**
 * fo_char_sprintf:
 * @object: #FoChar to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
gchar*
fo_char_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHAR (object), NULL);

  return (g_strdup_printf(_("'%s'"), FO_CHAR (object)->value));
}

