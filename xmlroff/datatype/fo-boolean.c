/* Fo
 * fo-boolean.c: Boolean datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-boolean.c,v 1.8 2006/03/21 23:30:46 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-boolean.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoBoolean
{
  FoDatatype parent_instance;

  gboolean value;
};

struct _FoBooleanClass
{
  FoDatatypeClass parent_class;
};

static void fo_boolean_init        (FoBoolean      *boolean);
static void fo_boolean_class_init  (FoBooleanClass *klass);
static void fo_boolean_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_boolean_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_boolean_finalize    (GObject           *object);

static FoDatatype * fo_boolean_copy          (FoDatatype *datatype);
static gchar*       fo_boolean_sprintf       (FoObject   *object);
static void         fo_boolean_set_value     (FoDatatype *boolean,
					      gboolean    new_value);

static gpointer parent_class;

/**
 * fo_boolean_get_type:
 * 
 * Register the #FoBoolean object type.
 * 
 * Return value: #GType value of the #FoBoolean object type.
 **/
GType
fo_boolean_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoBooleanClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_boolean_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoBoolean),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_boolean_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoBoolean",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_boolean_init:
 * @boolean: #FoBoolean object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoBoolean.
 **/
static void
fo_boolean_init (FoBoolean *boolean)
{
  boolean->value = FALSE;
}

/**
 * fo_boolean_class_init:
 * @klass: #FoBooleanClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoBooleanClass.
 **/
void
fo_boolean_class_init (FoBooleanClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_boolean_finalize;

  object_class->set_property = fo_boolean_set_property;
  object_class->get_property = fo_boolean_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_boolean_sprintf;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_boolean ("value",
							 _("Value"),
							 _("Boolean value"),
							 FALSE,
							 G_PARAM_READWRITE |
							 G_PARAM_CONSTRUCT_ONLY));

  FO_DATATYPE_CLASS (klass)->copy = fo_boolean_copy;
}

/**
 * fo_boolean_finalize:
 * @object: #FoBoolean object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoBoolean.
 **/
void
fo_boolean_finalize (GObject *object)
{
  FoBoolean *boolean;

  boolean = FO_BOOLEAN (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_boolean_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoBoolean.
 **/
void
fo_boolean_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *boolean;

  boolean = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_boolean (value, fo_boolean_get_value (boolean));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_boolean_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoBoolean.
 **/
void
fo_boolean_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *boolean;

  boolean = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_boolean_set_value (boolean, g_value_get_boolean (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_boolean_new:
 * 
 * Creates a new #FoBoolean initialized to default value.
 * 
 * Return value: the new #FoBoolean.
 **/
FoDatatype *
fo_boolean_new (void)
{
  FoDatatype *boolean;

  boolean = FO_DATATYPE (g_object_new (fo_boolean_get_type (), NULL));
  
  return boolean;
}

/**
 * fo_boolean_new_with_value:
 * @value: gboolean of the new #FoBoolean.
 * 
 * Creates a new #FoBoolean set to @value.
 * 
 * Return value: The new #FoBoolean.
 **/
FoDatatype*
fo_boolean_new_with_value (gboolean value)
{
  FoDatatype *boolean = fo_boolean_new ();

  fo_boolean_set_value (boolean, value);

  return boolean;
}

/**
 * fo_boolean_get_value:
 * @boolean: #FoBoolean.
 * 
 * Get the value of @boolean.
 * 
 * Return value: #gboolean value of @boolean.
 **/
gboolean
fo_boolean_get_value (FoDatatype *boolean)
{
  g_return_val_if_fail (boolean != NULL, 0);
  g_return_val_if_fail (FO_IS_BOOLEAN (boolean), 0);

  return FO_BOOLEAN (boolean)->value;
}

/**
 * fo_boolean_set_value:
 * @boolean:    #FoBoolean.
 * @new_value: New value for @boolean.
 * 
 * Set the value of @boolean.
 **/
void
fo_boolean_set_value (FoDatatype *boolean,
		      gboolean    new_value)
{
  g_return_if_fail (boolean != NULL);
  g_return_if_fail (FO_IS_BOOLEAN (boolean));

  FO_BOOLEAN (boolean)->value = new_value;
  /*g_object_notify(G_OBJECT (boolean), "value");*/
}

/**
 * fo_boolean_sprintf:
 * @object: #FoBoolean whose value is to be printed.
 * 
 * Create and return a string representation of the value of @object,
 * which must be an #FoBoolean.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of value of @object.
 **/
gchar*
fo_boolean_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_BOOLEAN (object), NULL);

  return g_strdup_printf (FO_BOOLEAN (object)->value ? "true" : "false");
}

/**
 * fo_boolean_copy:
 * @datatype: #FoBoolean to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoBoolean.
 **/
FoDatatype*
fo_boolean_copy (FoDatatype *datatype)
{
  FoDatatype *boolean;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_BOOLEAN (datatype), NULL);

  boolean = fo_boolean_new ();
  FO_BOOLEAN (boolean)->value = FO_BOOLEAN (datatype)->value;

  return boolean;
}

/**
 * fo_boolean_get_true:
 * 
 * Create and return an #FoBoolean with the well-known value %true.
 *
 * This saves creation of multiple #FoBoolean objects that all have the
 * value %true.
 * 
 * Return value: #FoBoolean with value %true.
 **/
FoDatatype*
fo_boolean_get_true (void)
{
  static FoDatatype *boolean = NULL;

  if (!boolean)
    {
      boolean = fo_boolean_new ();
      FO_BOOLEAN (boolean)->value = TRUE;
    }

  return boolean;
}

/**
 * fo_boolean_get_false:
 * 
 * Create and return an #FoBoolean with the well-known value %false.
 *
 * This saves creation of multiple #FoBoolean objects that all have the
 * value %false.
 * 
 * Return value: #FoBoolean with value %false.
 **/
FoDatatype*
fo_boolean_get_false (void)
{
  static FoDatatype *boolean = NULL;

  if (!boolean)
    {
      boolean = fo_boolean_new ();
      FO_BOOLEAN (boolean)->value = FALSE;
    }

  return boolean;
}

