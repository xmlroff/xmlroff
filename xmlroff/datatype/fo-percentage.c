/* Fo
 * fo-percentage.c: Percentage datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-percentage.c,v 1.6 2005/03/10 17:38:30 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-numeric-private.h"
#include "fo-percentage.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoPercentage
{
  FoDatatype parent_instance;

  gdouble value;
};

struct _FoPercentageClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_percentage_init         (FoPercentage      *percentage);
static void fo_percentage_class_init   (FoPercentageClass *klass);
static void fo_percentage_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_percentage_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_percentage_finalize     (GObject       *object);

static FoDatatype* fo_percentage_copy (FoDatatype *datatype);
static gchar*      fo_percentage_sprintf (FoObject *object);

static gpointer parent_class;

/**
 * fo_percentage_get_type:
 * 
 * Register the #FoPercentage object type.
 * 
 * Return value: #GType value of the #FoPercentage object type.
 **/
GType
fo_percentage_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPercentageClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_percentage_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPercentage),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_percentage_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoPercentage",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_percentage_init:
 * @percentage: #FoPercentage object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoPercentage.
 **/
void
fo_percentage_init (FoPercentage *percentage)
{
  percentage->value = 0;
}

/**
 * fo_percentage_class_init:
 * @klass: #FoPercentageClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPercentageClass.
 **/
void
fo_percentage_class_init (FoPercentageClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_percentage_finalize;

  object_class->set_property = fo_percentage_set_property;
  object_class->get_property = fo_percentage_get_property;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_double ("value",
						       _("Value"),
						       _("Percentage value"),
						       -G_MAXDOUBLE,
						       G_MAXDOUBLE,
						       0,
						       G_PARAM_READWRITE));

  FO_DATATYPE_CLASS (klass)->copy = fo_percentage_copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = fo_percentage_sprintf;
}

/**
 * fo_percentage_finalize:
 * @object: #FoPercentage object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoPercentage.
 **/
void
fo_percentage_finalize (GObject *object)
{
  FoPercentage *percentage;

  percentage = FO_PERCENTAGE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_percentage_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoPercentage.
 **/
void
fo_percentage_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *percentage;

  percentage = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_double (value, fo_percentage_get_value (percentage));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_percentage_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoPercentage.
 **/
void
fo_percentage_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *percentage;

  percentage = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_percentage_set_value (percentage, g_value_get_double (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_percentage_new:
 * 
 * Creates a new #FoPercentage initialized to default value.
 * 
 * Return value: the new #FoPercentage.
 **/
FoDatatype *
fo_percentage_new (void)
{
  FoDatatype *percentage;

  percentage = FO_DATATYPE (g_object_new (fo_percentage_get_type (),
					  NULL));
  
  return percentage;
}

/**
 * fo_percentage_new_with_value:
 * @value: Value of new #FoPercentage.
 * 
 * Creates a new #FoPercentage initialized to value of @value.  For
 * example, fo_percentage_new_with_value(100) creates a new
 * #FoPercentage with value equal to 100%.
 * 
 * Return value: the new #FoPercentage.
 **/
FoDatatype *
fo_percentage_new_with_value (gdouble value)
{
  FoDatatype *percentage;

  percentage = fo_percentage_new ();

  fo_percentage_set_value (percentage, value);
  
  return percentage;
}

/**
 * fo_percentage_get_value:
 * @percentage: #FoPercentage.
 * 
 * Get the value of @percentage.
 * 
 * Return value: Numeric value of @percentage.
 **/
gdouble
fo_percentage_get_value (FoDatatype *percentage)
{
  g_return_val_if_fail (percentage != NULL, 0);
  g_return_val_if_fail (FO_IS_PERCENTAGE (percentage), 0);

  return ((FoPercentage *) percentage)->value;
}

/**
 * fo_percentage_set_value:
 * @percentage:    #FoPercentage.
 * @new_value: New value for @percentage.
 * 
 * Set the value of @percentage.
 **/
void
fo_percentage_set_value (FoDatatype *percentage,
		       gdouble new_value)
{
  g_return_if_fail (percentage != NULL);
  g_return_if_fail (FO_IS_PERCENTAGE (percentage));

  ((FoPercentage *) percentage)->value = new_value;
  /*g_object_notify(G_OBJECT(percentage), "value");*/
}

/**
 * fo_percentage_copy:
 * @datatype: #FoPercentage to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoPercentage.
 **/
FoDatatype*
fo_percentage_copy(FoDatatype *datatype)
{
  FoDatatype* percentage;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_PERCENTAGE (datatype), NULL);

  percentage = fo_percentage_new ();
  FO_PERCENTAGE (percentage)->value = FO_PERCENTAGE (datatype)->value;

  return (percentage);
}

/**
 * fo_percentage_sprintf:
 * @object: #FoPercentage to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
gchar*
fo_percentage_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_PERCENTAGE (object), NULL);

  return (g_strdup_printf("%0g%%", FO_PERCENTAGE (object)->value));
}

/**
 * fo_percentage_get_percentage_hundred:
 * 
 * Get an #FoPercentage with the well-known value of 100%.
 * 
 * Return value: The #FoPercentage.
 **/
FoDatatype*
fo_percentage_get_percentage_hundred (void)
{
  static FoDatatype *percentage = NULL;

  if (percentage == NULL)
    {
      percentage = fo_percentage_new_with_value (100.0);
    }

  return percentage;
}
