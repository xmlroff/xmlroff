/* Fo
 * fo-number.c: Number datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-numeric.h"
#include "fo-number.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoNumber
{
  FoDatatype parent_instance;

  gdouble value;
};

struct _FoNumberClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_number_init         (FoNumber      *number);
static void fo_number_class_init   (FoNumberClass *klass);
static void fo_number_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_number_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_number_finalize     (GObject       *object);

static FoDatatype * fo_number_copy      (FoDatatype *datatype);
static gchar*       fo_number_sprintf   (FoObject   *object);
static void         fo_number_set_value (FoDatatype *length,
					 gdouble     new_value);

static gpointer parent_class;

/**
 * fo_number_get_type:
 * @void: 
 * 
 * Register the #FoNumber object type.
 * 
 * Return value: GType value of the #FoNumber object type.
 **/
GType
fo_number_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoNumberClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_number_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoNumber),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_number_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoNumber",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_number_init:
 * @number: #FoNumber object to initialise
 * 
 * Implements #GInstanceInitFunc for #FoNumber
 **/
void
fo_number_init (FoNumber *number)
{
  number->value = 0;
}

/**
 * fo_number_class_init:
 * @klass: #FoNumberClass object to initialise
 * 
 * Implements #GClassInitFunc for #FoNumberClass
 **/
void
fo_number_class_init (FoNumberClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_number_finalize;

  object_class->set_property = fo_number_set_property;
  object_class->get_property = fo_number_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_number_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_number_copy;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_double ("value",
							_("Value"),
							_("Number value"),
							-G_MAXDOUBLE,
							G_MAXDOUBLE,
							0,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));
}

/**
 * fo_number_finalize:
 * @object: #FoNumber object to finalize
 * 
 * Implements GObjectFinalizeFunc for #FoNumber
 **/
void
fo_number_finalize (GObject *object)
{
  FoNumber *number;

  number = FO_NUMBER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_number_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for #FoNumber
 **/
void
fo_number_set_property (GObject         *object,
			guint            prop_id,
			const GValue    *value,
			GParamSpec      *pspec)
{
  FoDatatype *number;

  number = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_number_set_value (number, g_value_get_double (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_number_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoNumber
 **/
void
fo_number_get_property (GObject         *object,
			guint            prop_id,
			GValue          *value,
			GParamSpec      *pspec)
{
  FoDatatype *number;

  number = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_double (value, fo_number_get_value (number));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_number_new:
 * 
 * Creates a new #FoNumber initialized to default value.
 * 
 * Return value: the new #FoNumber
 **/
FoDatatype *
fo_number_new (void)
{
  FoDatatype *number;

  number = FO_DATATYPE (g_object_new (fo_number_get_type (), NULL));
  
  return number;
}

/**
 * fo_number_new_with_value:
 * @value: Value of the new #FoNumber.
 * 
 * Creates a new #FoNumber set to @value.
 * 
 * Return value: The new #FoNumber.
 **/
FoDatatype*
fo_number_new_with_value (gdouble value)
{
  FoDatatype *number = fo_number_new ();

  fo_number_set_value (number, value);

  return number;
}

/**
 * fo_number_get_value:
 * @number: #FoNumber
 * 
 * Get the value of @number
 * 
 * Return value: Numeric value of @number
 **/
gdouble
fo_number_get_value (FoDatatype *number)
{
  g_return_val_if_fail (number != NULL, 0);
  g_return_val_if_fail (FO_IS_NUMBER (number), 0);

  return FO_NUMBER (number)->value;
}

/**
 * fo_number_set_value:
 * @number:    #FoNumber
 * @new_value: New value for @number
 * 
 * Set the value of @number
 **/
void
fo_number_set_value (FoDatatype *number,
		     gdouble new_value)
{
  g_return_if_fail (number != NULL);
  g_return_if_fail (FO_IS_NUMBER (number));

  FO_NUMBER (number)->value = new_value;
  /*g_object_notify(G_OBJECT(number), "value");*/
}

/**
 * fo_number_copy:
 * @datatype: #FoNumber to be copied
 * 
 * Create a copy of @datatype
 * 
 * Return value: New #FoNumber
 **/
FoDatatype*
fo_number_copy(FoDatatype *datatype)
{
  FoDatatype* number;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_NUMBER (datatype), NULL);

  number = fo_number_new ();
  FO_NUMBER (number)->value = FO_NUMBER (datatype)->value;

  return number;
}

/**
 * fo_number_sprintf:
 * @object: #FoNumber to be printed
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object
 **/
gchar*
fo_number_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_NUMBER (object), NULL);

  return (g_strdup_printf("%0g", FO_NUMBER (object)->value));
}

/**
 * fo_number_get_number_one:
 * 
 * Create and return an #FoNumber with the well-known value 1.0.
 *
 * This saves creation of multiple #FoNumber objects that all have the
 * value 1.0.
 * 
 * Return value: 
 **/
FoDatatype*
fo_number_get_number_one (void)
{
  static FoDatatype *number = NULL;

  if (!number)
    {
      number = fo_number_new ();
      FO_NUMBER (number)->value = 1.0;
    }

  return number;
}
