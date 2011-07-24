/* Fo
 * fo-enum.c: Enum datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-enum.h"


enum {
  PROP_0,
  PROP_ENUM_CLASS,
  PROP_VALUE
};

struct _FoEnum
{
  FoDatatype parent_instance;

  GEnumClass *enum_class;
  FoEnumEnum  value;
};

struct _FoEnumClass
{
  FoDatatypeClass parent_class;
};

static void fo_enum_init         (FoEnum      *fo_enum);
static void fo_enum_class_init   (FoEnumClass *klass);
static void fo_enum_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_enum_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void _finalize     (GObject       *object);

static FoDatatype * fo_enum_copy           (FoDatatype       *datatype);
static gchar*       _sprintf        (FoObject         *object);
static void         fo_enum_set_enum_class (FoDatatype       *fo_enum,
					    const GEnumClass *new_enum_class);
static void         fo_enum_set_value      (FoDatatype       *fo_enum,
					    const FoEnumEnum  new_value);

static gpointer parent_class;

static FoDatatype *enum_alphabetic = NULL;
static FoDatatype *enum_always = NULL;
static FoDatatype *enum_traditional = NULL;

/**
 * fo_enum_get_type:
 * 
 * Register the #FoEnum object type.
 * 
 * Return value: #GType value of the #FoEnum object type.
 **/
GType
fo_enum_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoEnumClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_enum_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoEnum),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_enum_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoEnum",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_enum_init:
 * @fo_enum: #FoEnum object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoEnum.
 **/
void
fo_enum_init (FoEnum *fo_enum)
{
  fo_enum->enum_class = NULL;
  fo_enum->value = FO_ENUM_ENUM_UNSPECIFIED;
}

/**
 * fo_enum_class_init:
 * @klass: #FoEnumClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoEnumClass.
 **/
void
fo_enum_class_init (FoEnumClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = _finalize;

  object_class->set_property = fo_enum_set_property;
  object_class->get_property = fo_enum_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = _sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_enum_copy;

  g_object_class_install_property
    (object_class,
     PROP_ENUM_CLASS,
     g_param_spec_pointer ("enum-class",
			   _("enum-class"),
			   _("Enumeration class"),
			   G_PARAM_READWRITE |
			   G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property
    (object_class,
     PROP_VALUE,
     g_param_spec_int ("value",
		       _("Value"),
		       _("Enum value"),
		       0,
		       FO_ENUM_ENUM_LIMIT,
		       FO_ENUM_ENUM_UNSPECIFIED,
		       G_PARAM_READWRITE |
		       G_PARAM_CONSTRUCT_ONLY));
}

/**
 * _finalize:
 * @object: #FoEnum object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoEnum.
 **/
static void
_finalize (GObject *object)
{
  FoEnum *fo_enum;

  fo_enum = FO_ENUM (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_enum_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoEnum.
 **/
void
fo_enum_get_property (GObject         *object,
		      guint            prop_id,
		      GValue          *value,
		      GParamSpec      *pspec)
{
  FoDatatype *fo_enum;

  fo_enum = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_ENUM_CLASS:
      g_value_set_pointer (value, fo_enum_get_enum_class (fo_enum));
      break;
    case PROP_VALUE:
      g_value_set_int (value, fo_enum_get_value (fo_enum));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_enum_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoEnum.
 **/
void
fo_enum_set_property (GObject         *object,
		      guint            prop_id,
		      const GValue    *value,
		      GParamSpec      *pspec)
{
  FoDatatype *fo_enum;

  fo_enum = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_ENUM_CLASS:
      fo_enum_set_enum_class (fo_enum, g_value_get_pointer (value));
      break;
    case PROP_VALUE:
      fo_enum_set_value (fo_enum, g_value_get_int (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_enum_new:
 * 
 * Creates a new #FoEnum initialized to default value.
 * 
 * Return value: The new #FoEnum.
 **/
FoDatatype *
fo_enum_new (void)
{
  FoDatatype *fo_enum;

  fo_enum = FO_DATATYPE (g_object_new (fo_enum_get_type (), NULL));
  
  return fo_enum;
}

/**
 * fo_enum_new_with_value:
 * @enum_class: #GEnumClass of the new #FoEnum.
 * @value:      Value of the new #FoEnum.
 * 
 * Creates a new #FoEnum set to @value and @enum_class.
 * 
 * Return value: The new #FoEnum.
 **/
FoDatatype*
fo_enum_new_with_value (const GEnumClass *enum_class,
			const FoEnumEnum  value)
{
  FoDatatype *fo_enum = fo_enum_new ();

  fo_enum_set_enum_class (fo_enum, enum_class);
  fo_enum_set_value (fo_enum, value);

  return fo_enum;
}

/**
 * fo_enum_get_enum_class:
 * @fo_enum: #FoEnum.
 * 
 * Get the enumeration class of @fo_enum.
 * 
 * Return value: Enumeration class of @fo_enum.
 **/
GEnumClass*
fo_enum_get_enum_class (FoDatatype *fo_enum)
{
  g_return_val_if_fail (fo_enum != NULL, 0);
  g_return_val_if_fail (FO_IS_ENUM (fo_enum), 0);

  return FO_ENUM (fo_enum)->enum_class;
}

/**
 * fo_enum_set_value:
 * @fo_enum:    #FoEnum.
 * @new_enum_class: New #GEnumClass for @fo_enum.
 * 
 * Set the #GEnumClass of @fo_enum.
 **/
void
fo_enum_set_enum_class (FoDatatype       *fo_enum,
			const GEnumClass *new_enum_class)
{
  g_return_if_fail (fo_enum != NULL);
  g_return_if_fail (FO_IS_ENUM (fo_enum));

  FO_ENUM (fo_enum)->enum_class = (GEnumClass *) new_enum_class;
  /*g_object_notify(G_OBJECT (fo_enum), "enum_class");*/
}

/**
 * fo_enum_get_value:
 * @fo_enum: #FoEnum.
 * 
 * Get the value of @fo_enum.
 * 
 * Return value: Numeric value of @fo_enum.
 **/
FoEnumEnum
fo_enum_get_value (FoDatatype *fo_enum)
{
  g_return_val_if_fail (fo_enum != NULL, 0);
  g_return_val_if_fail (FO_IS_ENUM (fo_enum), 0);

  return FO_ENUM (fo_enum)->value;
}

/**
 * fo_enum_get_nick:
 * @fo_enum: The #FoEnum.
 * 
 * Gets the 'nickname' string of @fo_enum.
 *
 * The result should not be freed.
 *
 * Return value: The 'nickname' of @fo_enum.
 **/
const gchar*
fo_enum_get_nick (FoDatatype *fo_enum)
{
  g_return_val_if_fail (fo_enum != NULL, 0);
  g_return_val_if_fail (FO_IS_ENUM (fo_enum), 0);

  return
    ((GEnumValue *) g_enum_get_value (FO_ENUM (fo_enum)->enum_class,
				      FO_ENUM (fo_enum)->value))->value_nick;
}

/**
 * fo_enum_set_value:
 * @fo_enum:    #FoEnum.
 * @new_value: New value for @fo_enum.
 * 
 * Set the value of @fo_enum.
 **/
void
fo_enum_set_value (FoDatatype      *fo_enum,
		   const FoEnumEnum new_value)
{
  g_return_if_fail (fo_enum != NULL);
  g_return_if_fail (FO_IS_ENUM (fo_enum));

  FO_ENUM (fo_enum)->value = new_value;
  /*g_object_notify(G_OBJECT (fo_enum), "value");*/
}

/**
 * fo_enum_copy:
 * @datatype: #FoEnum to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoEnum.
 **/
FoDatatype *
fo_enum_copy (FoDatatype *datatype)
{
  FoDatatype* fo_enum;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_ENUM (datatype), NULL);

  fo_enum = fo_enum_new ();
  FO_ENUM (fo_enum)->value = FO_ENUM (datatype)->value;

  return (FO_DATATYPE (fo_enum));
}

/**
 * _sprintf:
 * @object: #FoEnum to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
static gchar*
_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_ENUM (object), NULL);

  return (g_strdup_printf("%s",
			  ((GEnumValue *) g_enum_get_value (FO_ENUM (object)->enum_class,
							    FO_ENUM (object)->value))
			   ->value_nick));
}
