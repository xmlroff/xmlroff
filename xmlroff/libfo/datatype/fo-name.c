/* Fo
 * fo-name.c: Name datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-name.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoName
{
  FoDatatype parent_instance;

  gchar *value;
};

struct _FoNameClass
{
  FoDatatypeClass parent_class;
};

static void fo_name_class_init   (FoNameClass *klass);
static void fo_name_get_property (GObject       *object,
				  guint          prop_id,
				  GValue        *value,
				  GParamSpec    *pspec);
static void fo_name_set_property (GObject       *object,
				  guint          prop_id,
				  const GValue  *value,
				  GParamSpec    *pspec);

static FoDatatype * fo_name_copy      (FoDatatype  *datatype);
static gchar*       fo_name_sprintf   (FoObject    *object);
static void         fo_name_set_value (FoDatatype  *name,
				       const gchar* new_value);

static gpointer parent_class;

/**
 * fo_name_get_type:
 * 
 * Register the #FoName object type.
 * 
 * Return value: #GType value of the #FoName object type.
 **/
GType
fo_name_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoNameClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_name_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoName),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoName",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_name_class_init:
 * @klass: #FoNameClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoNameClass.
 **/
void
fo_name_class_init (FoNameClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->set_property = fo_name_set_property;
  object_class->get_property = fo_name_get_property;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_string ("value",
							_("Value"),
							_("Name value"),
							NULL,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  FO_DATATYPE_CLASS (klass)->copy = fo_name_copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = fo_name_sprintf;
}

/**
 * fo_name_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoName.
 **/
void
fo_name_get_property (GObject         *object,
		      guint            prop_id,
		      GValue          *value,
		      GParamSpec      *pspec)
{
  FoDatatype *name;

  name = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_string (value, fo_name_get_value (name));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_name_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoName.
 **/
void
fo_name_set_property (GObject         *object,
		      guint            prop_id,
		      const GValue    *value,
		      GParamSpec      *pspec)
{
  FoDatatype *name;

  name = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_name_set_value (name, g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_name_new:
 * 
 * Creates a new #FoName initialized to default value.
 * 
 * Return value: the new #FoName.
 **/
FoDatatype *
fo_name_new (void)
{
  return FO_DATATYPE (g_object_new (fo_name_get_type (),
				    NULL));
}

/**
 * fo_name_new_with_value:
 * @value: Value of the new #FoName.
 * 
 * Creates a new #FoName set to @value.
 * 
 * Return value: The new #FoName.
 **/
FoDatatype*
fo_name_new_with_value (const gchar* value)
{
  FoDatatype *name = fo_name_new ();

  fo_name_set_value (name, value);

  return name;
}

/**
 * fo_name_get_value:
 * @name: #FoName.
 * 
 * Get the value of @name.
 * 
 * Return value: String value of @name.  String must be freed by caller.
 **/
gchar*
fo_name_get_value (FoDatatype *name)
{
  g_return_val_if_fail (name != NULL, NULL);
  g_return_val_if_fail (FO_IS_NAME (name), NULL);

  return g_strdup (FO_NAME (name)->value);
}

/**
 * fo_name_set_value:
 * @name:      #FoName.
 * @new_value: New value for @name.
 * 
 * Set the value of @name.
 **/
void
fo_name_set_value (FoDatatype  *name,
		   const gchar* new_value)
{
  g_return_if_fail (name != NULL);
  g_return_if_fail (FO_IS_NAME (name));

  FO_NAME (name)->value = g_strdup (new_value);
  /*g_object_notify (G_OBJECT(name), "value");*/
}

/**
 * fo_name_copy:
 * @datatype: #FoName to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoName.
 **/
FoDatatype*
fo_name_copy(FoDatatype *datatype)
{
  FoDatatype* name;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_NAME (datatype), NULL);

  name = fo_name_new ();
  FO_NAME (name)->value = g_strdup (FO_NAME (datatype)->value);

  return (FO_DATATYPE(name));
}

/**
 * fo_name_sprintf:
 * @object: #FoName to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
gchar*
fo_name_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_NAME (object), NULL);

  return (g_strdup_printf ("%s", FO_NAME (object)->value));
}

/**
 * fo_name_get_name_empty:
 * 
 * Get an #FoName with the well-known value of an empty string.
 * 
 * Return value: The #FoName.
 **/
FoDatatype *
fo_name_get_name_empty (void)
{
  static FoDatatype *name = NULL;

  if (!name)
    {
      name = fo_name_new_with_value ("");
    }

  return name;
}
