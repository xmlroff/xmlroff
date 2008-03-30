/* Fo
 * fo-error.c: Error datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-datatype-private.h"
#include "fo-error.h"

enum {
  PROP_0,
  PROP_VALUE
};

struct _FoError
{
  FoDatatype parent_instance;

  GError *value;
};

struct _FoErrorClass
{
  FoDatatypeClass parent_class;
};

static void fo_error_class_init    (FoErrorClass *klass);
static void fo_error_set_property  (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_error_get_property  (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_error_finalize      (GObject       *object);

static FoDatatype* fo_error_copy      (FoDatatype *datatype);
static gchar*      fo_error_sprintf   (FoObject   *object);
static void        fo_error_set_value (FoDatatype *error,
				       GError     *new_value);

static gpointer parent_class;

/**
 * fo_error_get_type:
 * @void: 
 * 
 * Register the #FoError object type.
 * 
 * Return value: GType value of the #FoError object type.
 **/
GType
fo_error_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoErrorClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_error_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoError),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoError",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_error_class_init:
 * @klass: FoErrorClass object to initialise.
 * 
 * Implements GClassInitFunc for FoErrorClass.
 **/
void
fo_error_class_init (FoErrorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_error_finalize;

  object_class->set_property = fo_error_set_property;
  object_class->get_property = fo_error_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_error_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_error_copy;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_pointer ("value",
							 _("Value"),
							 _("Error value"),
							 G_PARAM_READWRITE |
							 G_PARAM_CONSTRUCT_ONLY));
}

/**
 * fo_error_finalize:
 * @object: #FoError object to finalize
 * 
 * Implements #GObjectFinalizeFunc for #FoError
 **/
void
fo_error_finalize (GObject *object)
{
  FoError *error;

  error = FO_ERROR (object);

  if (error->value)
    {
      g_error_free (error->value);
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_error_set_property:
 * @object:  #GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for #FoError
 **/
void
fo_error_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *error;

  error = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_error_set_value (error, g_value_get_pointer (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_error_get_property:
 * @object:  #GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   #GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for #FoError
 **/
void
fo_error_get_property (GObject         *object,
		       guint            prop_id,
		       GValue          *value,
		       GParamSpec      *pspec)
{
  FoDatatype *error;

  error = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_pointer (value, fo_error_get_value (error));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_error_new:
 * 
 * Creates a new #FoError initialized to default value.
 * 
 * Return value: The new #FoError
 **/
FoDatatype*
fo_error_new (void)
{
  FoDatatype* error;

  error = FO_DATATYPE (g_object_new (fo_error_get_type (), NULL));
  
  return error;
}

/**
 * fo_error_new_with_value:
 * @value: Error of the new #FoError
 * 
 * Creates a new #FoError set to @value
 * 
 * Return value: The new #FoError
 **/
FoDatatype*
fo_error_new_with_value (GError *value)
{
  FoDatatype *error = fo_error_new ();

  fo_error_set_value (error, value);

  return error;
}

/**
 * fo_error_set_value:
 * @error:    #FoError
 * @new_value: New value for @error
 * 
 * Set the value of @error
 **/
void
fo_error_set_value (FoDatatype *error,
		     GError *new_value)
{
  g_return_if_fail (error != NULL);
  g_return_if_fail (FO_IS_ERROR (error));

  ((FoError *) error)->value = new_value;
  /*g_object_notify (G_OBJECT (error), "value");*/
}

/**
 * fo_error_get_value:
 * @error: #FoError
 * 
 * Get the value of @error
 * 
 * Return value: #GError
 **/
GError*
fo_error_get_value (FoDatatype *error)
{
  g_return_val_if_fail (error != NULL, NULL);
  g_return_val_if_fail (FO_IS_ERROR (error), NULL);

  return FO_ERROR (error)->value;
}

/**
 * fo_error_copy:
 * @datatype: #FoError to be copied
 * 
 * Create a copy of @datatype
 * 
 * Return value: New #FoError
 **/
FoDatatype*
fo_error_copy (FoDatatype *datatype)
{
  FoDatatype* error;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_ERROR (datatype), NULL);

  error = fo_error_new ();
  FO_ERROR (error)->value = g_error_copy (FO_ERROR (datatype)->value);

  return (error);
}

/**
 * fo_error_sprintf:
 * @object: #FoError to be printed
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object
 **/
gchar*
fo_error_sprintf (FoObject *object)
{
  GError *error;

  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_ERROR (object), NULL);

  error = FO_ERROR (object)->value;

  return (g_strdup_printf ("%s: %s",
			   g_quark_to_string (error->domain),
			   error->message));
}
