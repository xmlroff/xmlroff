/* Fo
 * fo-integer.c: Integer datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-integer.c,v 1.6 2005/06/13 22:21:03 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-object.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-numeric.h"
#include "fo-number.h"
#include "fo-integer.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoInteger
{
  FoDatatype parent_instance;

  gint value;
};

struct _FoIntegerClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_integer_init         (FoInteger      *integer);
static void fo_integer_class_init   (FoIntegerClass *klass);
static void fo_integer_set_property (GObject        *object,
				     guint           prop_id,
				     const GValue   *value,
				     GParamSpec     *pspec);
static void fo_integer_get_property (GObject        *object,
				     guint           prop_id,
				     GValue         *value,
				     GParamSpec     *pspec);
static void fo_integer_finalize     (GObject        *object);

static FoDatatype* fo_integer_copy         (FoDatatype     *datatype);
static gchar*      fo_integer_sprintf      (FoObject       *object);
static void fo_integer_set_value    (FoDatatype     *integer,
				     gint            new_value);

static gpointer parent_class;

/**
 * fo_integer_get_type:
 * @void: 
 * 
 * Register the #FoInteger object type.
 * 
 * Return value: GType value of the #FoInteger object type.
 **/
GType
fo_integer_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoIntegerClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_integer_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoInteger),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_integer_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoInteger",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_integer_init:
 * @integer: #FoInteger object to initialise
 * 
 * Implements GInstanceInitFunc for #FoInteger
 **/
void
fo_integer_init (FoInteger *integer)
{
  integer->value = 0;
}

/**
 * fo_integer_class_init:
 * @klass: FoIntegerClass object to initialise
 * 
 * Implements GClassInitFunc for FoIntegerClass
 **/
void
fo_integer_class_init (FoIntegerClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_integer_finalize;

  object_class->set_property = fo_integer_set_property;
  object_class->get_property = fo_integer_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_integer_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_integer_copy;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_int ("value",
						     _("Value"),
						     _("Integer value"),
						     G_MININT,
						     G_MAXINT,
						     0,
						     G_PARAM_READWRITE |
						     G_PARAM_CONSTRUCT_ONLY));
}

/**
 * fo_integer_finalize:
 * @object: FoInteger object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoInteger
 **/
void
fo_integer_finalize (GObject *object)
{
  FoInteger *integer;

  integer = FO_INTEGER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_integer_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoInteger
 **/
void
fo_integer_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *integer;

  integer = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_integer_set_value (integer, g_value_get_int (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_integer_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoInteger
 **/
void
fo_integer_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *integer;

  integer = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_int (value, fo_integer_get_value (integer));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_integer_new:
 * 
 * Creates a new #FoInteger initialized to default value.
 * 
 * Return value: the new #FoInteger.
 **/
FoDatatype *
fo_integer_new (void)
{
  FoDatatype *integer;

  integer = FO_DATATYPE (g_object_new (fo_integer_get_type (), NULL));
  
  return integer;
}

/**
 * fo_integer_new_with_value:
 * @value: Value of the new #FoInteger.
 * 
 * Creates a new #FoInteger set to @value.
 * 
 * Return value: The new #FoInteger.
 **/
FoDatatype*
fo_integer_new_with_value (gint value)
{
  FoDatatype *integer = fo_integer_new ();

  fo_integer_set_value (integer, value);

  return integer;
}

/**
 * fo_integer_get_value:
 * @integer: #FoInteger.
 * 
 * Get the value of @integer.
 * 
 * Return value: Numeric value of @integer.
 **/
gint
fo_integer_get_value (FoDatatype *integer)
{
  g_return_val_if_fail (integer != NULL, 0);
  g_return_val_if_fail (FO_IS_INTEGER (integer) || FO_IS_NUMBER (integer), 0);

  if (FO_IS_INTEGER (integer))
    { 
      return FO_INTEGER (integer)->value;
    }
  else
    {
      return ((int) fo_number_get_value (integer));
    }
}

/**
 * fo_integer_set_value:
 * @integer:    #FoInteger.
 * @new_value: New value for @integer.
 * 
 * Set the value of @integer.
 **/
void
fo_integer_set_value (FoDatatype *integer,
		      gint        new_value)
{
  g_return_if_fail (integer != NULL);
  g_return_if_fail (FO_IS_INTEGER (integer));

  FO_INTEGER (integer)->value = new_value;
  /*g_object_notify(G_OBJECT(integer), "value");*/
}

/**
 * fo_integer_copy:
 * @datatype: #FoInteger to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoInteger.
 **/
FoDatatype*
fo_integer_copy(FoDatatype *datatype)
{
  FoDatatype* integer;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_INTEGER (datatype), NULL);

  integer = fo_integer_new ();
  FO_INTEGER (integer)->value = FO_INTEGER (datatype)->value;

  return (integer);
}

/**
 * fo_integer_sprintf:
 * @object: #FoInteger to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
gchar*
fo_integer_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_INTEGER (object), NULL);

  return (g_strdup_printf("%0d", FO_INTEGER (object)->value));
}

/**
 * fo_integer_get_integer_zero:
 * 
 * Create and return an #FoInteger with the well-known value 0.
 *
 * This saves creation of multiple #FoInteger objects that all have the
 * value 0.
 * 
 * Return value: #FoInteger with value 0.
 **/
FoDatatype*
fo_integer_get_integer_zero (void)
{
  static FoDatatype *integer = NULL;

  if (!integer)
    {
      integer = fo_integer_new ();
      FO_INTEGER (integer)->value = 0;
    }

  return integer;
}

/**
 * fo_integer_get_integer_one:
 * 
 * Create and return an #FoInteger with the well-known value 1.
 *
 * This saves creation of multiple #FoInteger objects that all have the
 * value 1.
 * 
 * Return value: #FoInteger with value 1.
 **/
FoDatatype*
fo_integer_get_integer_one (void)
{
  static FoDatatype *integer = NULL;

  if (!integer)
    {
      integer = fo_integer_new ();
      FO_INTEGER (integer)->value = 1;
    }

  return integer;
}

/**
 * fo_integer_get_integer_two:
 * 
 * Create and return an #FoInteger with the well-known value 2.
 *
 * This saves creation of multiple #FoInteger objects that all have the
 * value 2.
 * 
 * Return value: #FoInteger with value 2.
 **/
FoDatatype*
fo_integer_get_integer_two (void)
{
  static FoDatatype *integer = NULL;

  if (!integer)
    {
      integer = fo_integer_new ();
      FO_INTEGER (integer)->value = 2;
    }

  return integer;
}

/**
 * fo_integer_get_integer_three:
 * 
 * Create and return an #FoInteger with the well-known value 3.
 *
 * This saves creation of multiple #FoInteger objects that all have the
 * value 3.
 * 
 * Return value: #FoInteger with value 3.
 **/
FoDatatype*
fo_integer_get_integer_three (void)
{
  static FoDatatype *integer = NULL;

  if (!integer)
    {
      integer = fo_integer_new ();
      FO_INTEGER (integer)->value = 3;
    }

  return integer;
}

/**
 * fo_integer_get_integer_four:
 * 
 * Create and return an #FoInteger with the well-known value 4.
 *
 * This saves creation of multiple #FoInteger objects that all have the
 * value 4.
 * 
 * Return value: #FoInteger with value 4.
 **/
FoDatatype*
fo_integer_get_integer_four (void)
{
  static FoDatatype *integer = NULL;

  if (!integer)
    {
      integer = fo_integer_new ();
      FO_INTEGER (integer)->value = 4;
    }

  return integer;
}

/**
 * fo_integer_get_integer_five:
 * 
 * Create and return an #FoInteger with the well-known value 5.
 *
 * This saves creation of multiple #FoInteger objects that all have the
 * value 5.
 * 
 * Return value: #FoInteger with value 5.
 **/
FoDatatype*
fo_integer_get_integer_five (void)
{
  static FoDatatype *integer = NULL;

  if (!integer)
    {
      integer = fo_integer_new ();
      FO_INTEGER (integer)->value = 5;
    }

  return integer;
}

/**
 * fo_integer_get_integer_six:
 * 
 * Create and return an #FoInteger with the well-known value 6.
 *
 * This saves creation of multiple #FoInteger objects that all have the
 * value 6.
 * 
 * Return value: #FoInteger with value 6.
 **/
FoDatatype*
fo_integer_get_integer_six (void)
{
  static FoDatatype *integer = NULL;

  if (!integer)
    {
      integer = fo_integer_new ();
      FO_INTEGER (integer)->value = 6;
    }

  return integer;
}
