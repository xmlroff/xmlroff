/* Fo
 * fo-pcw.c: Proportional-column-width datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-object.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-numeric.h"
#include "fo-pcw.h"


enum {
  PROP_0,
  PROP_VALUE
};

struct _FoPcw
{
  FoDatatype parent_instance;

  gdouble value;
};

struct _FoPcwClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_pcw_init         (FoPcw      *pcw);
static void fo_pcw_class_init   (FoPcwClass *klass);
static void fo_pcw_set_property (GObject        *object,
				     guint           prop_id,
				     const GValue   *value,
				     GParamSpec     *pspec);
static void fo_pcw_get_property (GObject        *object,
				     guint           prop_id,
				     GValue         *value,
				     GParamSpec     *pspec);
static void fo_pcw_finalize     (GObject        *object);

static FoDatatype* fo_pcw_copy         (FoDatatype     *datatype);
static gchar*      fo_pcw_sprintf      (FoObject       *object);
static void fo_pcw_set_value    (FoDatatype     *pcw,
				     gdouble            new_value);

static gpointer parent_class;

/**
 * fo_pcw_get_type:
 * @void: 
 * 
 * Register the #FoPcw object type.
 * 
 * Return value: GType value of the #FoPcw object type.
 **/
GType
fo_pcw_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoPcwClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_pcw_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoPcw),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_pcw_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoPcw",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_pcw_init:
 * @pcw: #FoPcw object to initialise
 * 
 * Implements GInstanceInitFunc for #FoPcw
 **/
void
fo_pcw_init (FoPcw *pcw)
{
  pcw->value = 0;
}

/**
 * fo_pcw_class_init:
 * @klass: FoPcwClass object to initialise
 * 
 * Implements GClassInitFunc for FoPcwClass
 **/
void
fo_pcw_class_init (FoPcwClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_pcw_finalize;

  object_class->set_property = fo_pcw_set_property;
  object_class->get_property = fo_pcw_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_pcw_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_pcw_copy;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_double ("value",
							_("Value"),
							_("Pcw value"),
							-G_MAXDOUBLE,
							G_MAXDOUBLE,
							0,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));
}

/**
 * fo_pcw_finalize:
 * @object: FoPcw object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoPcw
 **/
void
fo_pcw_finalize (GObject *object)
{
  FoPcw *pcw;

  pcw = FO_PCW (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_pcw_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoPcw
 **/
void
fo_pcw_set_property (GObject         *object,
		     guint            prop_id,
		     const GValue    *value,
		     GParamSpec      *pspec)
{
  FoDatatype *pcw;

  pcw = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_pcw_set_value (pcw, g_value_get_double (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_pcw_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoPcw
 **/
void
fo_pcw_get_property (GObject         *object,
		     guint            prop_id,
		     GValue          *value,
		     GParamSpec      *pspec)
{
  FoDatatype *pcw;

  pcw = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_double (value, fo_pcw_get_value (pcw));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_pcw_new:
 * 
 * Creates a new #FoPcw initialized to default value.
 * 
 * Return value: the new #FoPcw
 **/
FoDatatype *
fo_pcw_new (void)
{
  FoDatatype *pcw;

  pcw = FO_DATATYPE (g_object_new (fo_pcw_get_type (), NULL));
  
  return pcw;
}

/**
 * fo_pcw_new_with_value:
 * @value: Value of the new #FoPcw
 * 
 * Creates a new #FoPcw set to @value
 * 
 * Return value: The new #FoPcw
 **/
FoDatatype*
fo_pcw_new_with_value (gdouble value)
{
  FoDatatype *pcw = fo_pcw_new ();

  fo_pcw_set_value (pcw, value);

  return pcw;
}

/**
 * fo_pcw_set_value:
 * @pcw:    #FoPcw
 * @new_value: New value for @pcw
 * 
 * Set the value of @pcw
 **/
void
fo_pcw_set_value (FoDatatype *pcw,
		  gdouble new_value)
{
  g_return_if_fail (pcw != NULL);
  g_return_if_fail (FO_IS_PCW (pcw));

  FO_PCW (pcw)->value = new_value;
  /*g_object_notify(G_OBJECT(pcw), "value");*/
}

/**
 * fo_pcw_get_value:
 * @pcw: #FoPcw
 * 
 * Get the value of @pcw
 * 
 * Return value: Numeric value of @pcw
 **/
gdouble
fo_pcw_get_value (FoDatatype *pcw)
{
  g_return_val_if_fail (pcw != NULL, 0);
  g_return_val_if_fail (FO_IS_PCW (pcw), 0);

  return FO_PCW(pcw)->value;
}

/**
 * fo_pcw_copy:
 * @datatype: #FoPcw to be copied
 * 
 * Create a copy of @datatype
 * 
 * Return value: New #FoPcw
 **/
FoDatatype*
fo_pcw_copy (FoDatatype *datatype)
{
  FoDatatype* pcw;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_PCW (datatype), NULL);

  pcw = fo_pcw_new ();
  FO_PCW (pcw)->value = FO_PCW (datatype)->value;

  return (pcw);
}

/**
 * fo_pcw_sprintf:
 * @object: #FoPcw to be printed
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object
 **/
gchar*
fo_pcw_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_PCW (object), NULL);

  return (g_strdup_printf("%0g", FO_PCW (object)->value));
}

/**
 * fo_pcw_get_pcw_zero:
 * 
 * Create and return an #FoPcw with the well-known value 0.
 *
 * This saves creation of multiple #FoPcw objects that all have the
 * value 0.0.
 * 
 * Return value: #FoPcw with value 0
 **/
FoDatatype*
fo_pcw_get_pcw_zero (void)
{
  static FoDatatype *pcw = NULL;

  if (pcw == NULL)
    {
      pcw = fo_pcw_new ();
      FO_PCW (pcw)->value = 0.0;
    }

  return pcw;
}
