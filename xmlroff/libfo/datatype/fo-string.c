/* Fo
 * fo-datatype-string.c: String datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-string.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoString
{
  FoDatatype parent_instance;

  gchar *value;
};

struct _FoStringClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_string_init         (FoString      *string);
static void fo_string_class_init   (FoStringClass *klass);
static void fo_string_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_string_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_string_finalize     (GObject       *object);

static FoDatatype * fo_string_copy  (FoDatatype    *datatype);
static gchar* fo_string_sprintf     (FoObject      *object);
static void   fo_string_set_value   (FoDatatype    *string,
				     const gchar*   new_value);

static gpointer parent_class;

/**
 * fo_string_get_type:
 * 
 * Register the #FoString object type.
 * 
 * Return value: GType value of the #FoString object type.
 **/
GType
fo_string_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoStringClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_string_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoString),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_string_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoString",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_string_init:
 * @string: #FoString object to initialise
 * 
 * Implements #GInstanceInitFunc for #FoString
 **/
static void
fo_string_init (FoString *string)
{
  string->value = NULL;
}

/**
 * fo_string_class_init:
 * @klass: #FoStringClass object to initialise
 * 
 * Implements #GClassInitFunc for FoStringClass
 **/
static void
fo_string_class_init (FoStringClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_string_finalize;

  object_class->set_property = fo_string_set_property;
  object_class->get_property = fo_string_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_string_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_string_copy;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_string ("value",
							_("Value"),
							_("String value"),
							NULL,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  FO_DATATYPE_CLASS (klass)->copy = fo_string_copy;
}

/**
 * fo_string_finalize:
 * @object: #FoString object to finalize
 * 
 * Implements #GObjectFinalizeFunc for #FoString
 **/
static void
fo_string_finalize (GObject *object)
{
  FoString *string;

  string = FO_STRING (object);

  if (string->value != NULL)
    {
      g_free(string->value);
      string->value == NULL;
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_string_get_property:
 * @object:  #GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for #FoString
 **/
static void
fo_string_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *string;

  string = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_string (value, fo_string_get_value (string));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_string_set_property:
 * @object:  #GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for #FoString
 **/
static void
fo_string_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *string;

  string = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_string_set_value (string, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_string_new:
 * 
 * Creates a new #FoString initialized to default value.
 * 
 * Return value: the new #FoString
 **/
FoDatatype *
fo_string_new (void)
{
  FoDatatype *string;

  string = FO_DATATYPE (g_object_new (fo_string_get_type (), NULL));
  
  return string;
}

/**
 * fo_string_new_with_value:
 * @value: String of the new #FoString.
 * 
 * Creates a new #FoString set to @value.
 * 
 * Return value: The new #FoString.
 **/
FoDatatype*
fo_string_new_with_value (const gchar* value)
{
  FoDatatype *string = fo_string_new ();

  fo_string_set_value (string, value);

  return string;
}

/**
 * fo_string_get_value:
 * @string: #FoString.
 * 
 * Get the value of @string.
 * 
 * Return value: Numeric value of @string.
 **/
gchar*
fo_string_get_value (FoDatatype *string)
{
  g_return_val_if_fail (string != NULL, NULL);
  g_return_val_if_fail (FO_IS_STRING (string), NULL);

  return g_strdup (FO_STRING (string)->value);
}

/**
 * fo_string_set_value:
 * @string:    #FoString.
 * @new_value: New value for @string.
 * 
 * Set the value of @string.
 **/
void
fo_string_set_value (FoDatatype   *string,
		     const gchar*  new_value)
{
  g_return_if_fail (string != NULL);
  g_return_if_fail (FO_IS_STRING (string));

  FO_STRING (string)->value = g_strdup (new_value);
  /*g_object_notify(G_OBJECT(string), "value");*/
}

/**
 * fo_string_copy:
 * @datatype: #FoString to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoString.
 **/
FoDatatype*
fo_string_copy (FoDatatype *datatype)
{
  FoDatatype *string;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_STRING (datatype), NULL);

  string = fo_string_new ();
  FO_STRING (string)->value = g_strdup (FO_STRING (datatype)->value);

  return (string);
}

/**
 * fo_string_sprintf:
 * @object: #FoString to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
gchar*
fo_string_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_STRING (object), NULL);

  return (g_strdup_printf ("\"%s\"", FO_STRING (object)->value));
}

/**
 * fo_string_get_string_one:
 * 
 * Create and return an #FoString with the well-known value "1".
 *
 * This saves creation of multiple #FoString objects that all have the
 * value "1".
 * 
 * Return value: 
 **/
FoDatatype*
fo_string_get_string_one (void)
{
  static FoDatatype *string = NULL;

  if (!string)
    {
      string = fo_string_new ();
      FO_STRING (string)->value = g_strdup("1");
    }

  return string;
}
