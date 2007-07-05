/* Fo
 * fo-space.c: Space datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-space.h"
#include "fo-length.h"
#include "fo-integer.h"
#include "fo-percentage.h"
#include "fo-boolean.h"

enum {
  PROP_0,
  PROP_MINIMUM,
  PROP_OPTIMUM,
  PROP_MAXIMUM,
  PROP_PRECEDENCE,
  PROP_CONDITY
};

struct _FoSpace
{
  FoDatatype parent_instance;

  gfloat minimum;
  gfloat optimum;
  gfloat maximum;
  gint precedence;
  gboolean retain;
};

struct _FoSpaceClass
{
  FoDatatypeClass parent_class;
  
};

static void fo_space_init         (FoSpace      *space);
static void fo_space_class_init   (FoSpaceClass *klass);
static void fo_space_set_property (GObject      *object,
				   guint         prop_id,
				   const GValue *value,
				   GParamSpec   *pspec);
static void fo_space_get_property (GObject      *object,
				   guint         prop_id,
				   GValue       *value,
				   GParamSpec   *pspec);
static void fo_space_finalize     (GObject      *object);

gchar*      fo_space_sprintf      (FoObject     *object);
FoDatatype* fo_space_copy         (FoDatatype   *datatype);

static gpointer parent_class;

/**
 * fo_space_get_type:
 * @void: 
 * 
 * Register the #FoSpace object type.
 * 
 * Return value: GType value of the #FoSpace object type.
 **/
GType
fo_space_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoSpaceClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_space_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoSpace),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_space_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoSpace",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_space_init:
 * @space: #FoSpace object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoSpace.
 **/
void
fo_space_init (FoSpace *space)
{
  space->minimum = 0.0;
  space->optimum = 0.0;
  space->maximum = 0.0;
  space->precedence = 0;
  space->retain = FALSE;
}

/**
 * fo_space_class_init:
 * @klass: FoSpaceClass object to initialise
 * 
 * Implements GClassInitFunc for FoSpaceClass
 **/
void
fo_space_class_init (FoSpaceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_space_finalize;

  object_class->set_property = fo_space_set_property;
  object_class->get_property = fo_space_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_space_sprintf;

  g_object_class_install_property (object_class,
                                   PROP_MINIMUM,
                                   g_param_spec_float ("minimum",
						       _("Minimum"),
						       _("Space range minimum value"),
						       -G_MAXFLOAT,
						       G_MAXFLOAT,
						       0,
						       G_PARAM_READWRITE |
						       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property (object_class,
                                   PROP_OPTIMUM,
                                   g_param_spec_float ("optimum",
						       _("Optimum"),
						       _("Space range optimum value"),
						       -G_MAXFLOAT,
						       G_MAXFLOAT,
						       0,
						       G_PARAM_READWRITE |
						       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property (object_class,
                                   PROP_MAXIMUM,
                                   g_param_spec_float ("maximum",
						       _("Maximum"),
						       _("Space range maximum value"),
						       -G_MAXFLOAT,
						       G_MAXFLOAT,
						       0,
						       G_PARAM_READWRITE |
						       G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property (object_class,
                                   PROP_PRECEDENCE,
                                   g_param_spec_int ("precedence",
						     _("Precedence"),
						     _("Precedence of this space compared to others"),
						     G_MININT,
						     G_MAXINT,
						     0,
						     G_PARAM_READWRITE |
						     G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property (object_class,
                                   PROP_CONDITY,
                                   g_param_spec_boolean ("conditionality",
							 _("Conditionality"),
							 _("Whether or not the space must always be retained"),
							 FALSE,
							 G_PARAM_READWRITE |
							 G_PARAM_CONSTRUCT_ONLY));
  FO_DATATYPE_CLASS (klass)->copy = fo_space_copy;
}

/**
 * fo_space_finalize:
 * @object: FoSpace object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoSpace
 **/
void
fo_space_finalize (GObject *object)
{
  FoSpace *space;

  space = FO_SPACE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_space_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoSpace
 **/
void
fo_space_get_property (GObject         *object,
		       guint            prop_id,
		       GValue          *value,
		       GParamSpec      *pspec)
{
  FoDatatype *datatype;

  datatype = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_MINIMUM:
      g_value_set_float (value, fo_space_get_minimum (datatype));
      break;
    case PROP_OPTIMUM:
      g_value_set_float (value, fo_space_get_optimum (datatype));
      break;
    case PROP_MAXIMUM:
      g_value_set_float (value, fo_space_get_maximum (datatype));
      break;
    case PROP_PRECEDENCE:
      g_value_set_int (value, fo_space_get_precedence (datatype));
      break;
    case PROP_CONDITY:
      g_value_set_boolean (value, fo_space_get_condity (datatype));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_space_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoSpace
 **/
void
fo_space_set_property (GObject         *object,
		       guint            prop_id,
		       const GValue    *value,
		       GParamSpec      *pspec)
{
  FoDatatype *space;

  space = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_MINIMUM:
      fo_space_set_minimum (space, g_value_get_float (value));
      break;
    case PROP_OPTIMUM:
      fo_space_set_optimum (space, g_value_get_float (value));
      break;
    case PROP_MAXIMUM:
      fo_space_set_maximum (space, g_value_get_float (value));
      break;
    case PROP_PRECEDENCE:
      fo_space_set_precedence (space, g_value_get_int (value));
      break;
    case PROP_CONDITY:
      fo_space_set_condity (space, g_value_get_boolean (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_space_new:
 * 
 * Creates a new #FoSpace initialized to default value.
 * 
 * Return value: the new #FoSpace
 **/
FoDatatype *
fo_space_new (void)
{
  FoDatatype *space;

  space = FO_DATATYPE (g_object_new (fo_space_get_type (),
				     NULL));
  
  return space;
}

/**
 * fo_space_new_from_length:
 * @length: #FoLength to use as initial value
 * 
 * Creates a new #FoSpace with .minimum, .optimum, and .maximum
 * components set to @length and .conditionality and .precedence
 * components set to default values.
 * 
 * Return value: New #FoSpace
 **/
FoDatatype*
fo_space_new_from_length (FoDatatype *length)
{
  FoDatatype *space;
  gfloat length_val;

  g_return_val_if_fail (FO_IS_LENGTH (length), NULL);

  length_val = fo_length_get_value (length);

  space = fo_space_new ();

  fo_space_set_minimum (space, length_val);
  fo_space_set_optimum (space, length_val);
  fo_space_set_maximum (space, length_val);

  return space;
}

/**
 * fo_space_set_minimum:
 * @datatype:     #FoSpace
 * @new_minimum:  New .minimum value
 * 
 * Sets the .minimum component of @datatype
 **/
void
fo_space_set_minimum (FoDatatype *datatype,
		      gfloat      new_minimum)
{
  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_SPACE (datatype));

  FO_SPACE (datatype)->minimum = new_minimum;
  /*g_object_notify(G_OBJECT(datatype), "minimum");*/
}

/**
 * fo_space_get_minimum:
 * @datatype: #FoSpace
 * 
 * Gets the .minimum component value of @datatype
 * 
 * Return value: The .minimum value of @datatype
 **/
gfloat
fo_space_get_minimum (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_SPACE (datatype), 0);

  return FO_SPACE (datatype)->minimum;
}

/**
 * fo_space_set_optimum:
 * @datatype:     #FoSpace
 * @new_optimum:  New .optimum value
 * 
 * Sets the .optimum component of @datatype
 **/
void
fo_space_set_optimum (FoDatatype *datatype,
		      gfloat      new_optimum)
{
  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_SPACE (datatype));

  FO_SPACE (datatype)->optimum = new_optimum;
  /*g_object_notify(G_OBJECT(datatype), "optimum");*/
}

/**
 * fo_space_get_optimum:
 * @datatype: #FoSpace
 * 
 * Gets the .optimum component value of @datatype
 * 
 * Return value: The .optimum value of @datatype
 **/
gfloat
fo_space_get_optimum (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_SPACE (datatype), 0);

  return FO_SPACE (datatype)->optimum;
}

/**
 * fo_space_set_maximum:
 * @datatype:     #FoSpace
 * @new_maximum:  New .maximum value
 * 
 * Sets the .maximum component of @datatype
 **/
void
fo_space_set_maximum (FoDatatype *datatype,
		      gfloat      new_maximum)
{
  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_SPACE (datatype));

  FO_SPACE (datatype)->maximum = new_maximum;
  /*g_object_notify(G_OBJECT(datatype), "maximum");*/
}

/**
 * fo_space_get_maximum:
 * @datatype: #FoSpace
 * 
 * Gets the .maximum component value of @datatype
 * 
 * Return value: The .maximum value of @datatype
 **/
gfloat
fo_space_get_maximum (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_SPACE (datatype), 0);

  return FO_SPACE (datatype)->maximum;
}

/**
 * fo_space_set_precedence:
 * @datatype:     #FoSpace
 * @new_precedence:  New .precedence value
 * 
 * Sets the .precedence component of @datatype
 **/
void
fo_space_set_precedence (FoDatatype *datatype,
			 gint        new_precedence)
{
  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_SPACE (datatype));

  FO_SPACE (datatype)->precedence = new_precedence;
  /*g_object_notify(G_OBJECT(datatype), "precedence");*/
}

/**
 * fo_space_get_precedence:
 * @datatype: #FoSpace
 * 
 * Gets the .precedence component value of @datatype
 * 
 * Return value: The .precedence value of @datatype
 **/
gint
fo_space_get_precedence (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_SPACE (datatype), 0);

  return FO_SPACE (datatype)->precedence;
}

/**
 * fo_space_set_condity:
 * @datatype:    #FoSpace.
 * @new_condity: New .conditionality component value.
 * 
 * Sets the .conditionality component value of @datatype
 **/
void
fo_space_set_condity (FoDatatype *datatype,
		      gboolean    new_condity)
{
  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_SPACE (datatype));

  FO_SPACE (datatype)->retain = new_condity;
  /*g_object_notify(G_OBJECT(datatype), "conditionality");*/
}

/**
 * fo_space_get_condity:
 * @datatype: #FoSpace
 * 
 * Gets the .conditionality component value of @datatype
 * 
 * Return value: The .conditionality value of @datatype
 **/
gboolean
fo_space_get_condity (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, 0);
  g_return_val_if_fail (FO_IS_SPACE (datatype), 0);

  return FO_SPACE (datatype)->retain;
}

/**
 * fo_space_sprintf:
 * @object: #FoSpace whose value is to be printed
 * 
 * Create and return a string representation of the value of @object,
 * which must be an #FoSpace.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of value of @object
 **/
gchar*
fo_space_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_SPACE (object), NULL);

  return 
    g_strdup_printf ("min: %0gpt; opt: %0gpt; max: %0gpt; prec: %d; cond: %s",
		     FO_SPACE (object)->minimum,
		     FO_SPACE (object)->optimum,
		     FO_SPACE (object)->maximum,
		     FO_SPACE (object)->precedence,
		     FO_SPACE (object)->retain ? "retain" : "discard");
}

/**
 * fo_space_copy:
 * @datatype: Source #FoSpace
 * 
 * Creates a copy of @datatype
 * 
 * Return value: Copy of @datatype
 **/
FoDatatype*
fo_space_copy (FoDatatype *datatype)
{
  FoDatatype *space;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_SPACE (datatype), NULL);

  space = fo_space_new ();
  FO_SPACE (space)->minimum = FO_SPACE (datatype)->minimum;
  FO_SPACE (space)->optimum = FO_SPACE (datatype)->optimum;
  FO_SPACE (space)->maximum = FO_SPACE (datatype)->maximum;
  FO_SPACE (space)->precedence = FO_SPACE (datatype)->precedence;
  FO_SPACE (space)->retain = FO_SPACE (datatype)->retain;

  return space;
}

/**
 * fo_space_get_space_0pt:
 * 
 * Create and return an #FoSpace with the well-known value 0pt.
 *
 * This saves creation of multiple #FoSpace objects that all have the
 * value 0pt.
 * 
 * Return value: #FoSpace with value 0pt.
 **/
FoDatatype*
fo_space_get_space_0pt (void)
{
  static FoDatatype *space = NULL;

  if (!space)
    {
      space = fo_space_new ();
    }

  return space;
}

/**
 * fo_space_resolve:
 * @shortform:       Single-value short form of the space, or NULL
 * @minimum:         .minimum component of the space, or NULL
 * @optimum:         .optimum component of the space, or NULL
 * @maximum:         .maximum component of the space, or NULL
 * @precedence:      .precedence component of the space, or NULL
 * @condity:  .conditionality component of the space, or NULL
 * @hundred_percent: Length to use as 100% when components expressed as
 *                   percentages
 * @error:           GError used for reporting errors
 * 
 * Resolve the shortform and components of the space in accordance
 * with Section 5.11, Datatypes, of the XSL 1.0 Recommendation.
 * 
 * Return value: Compound space datatype, or NULL if an error occurred
 **/
FoDatatype*
fo_space_resolve (FoDatatype *shortform,
		  FoDatatype *minimum,
		  FoDatatype *optimum,
		  FoDatatype *maximum,
		  FoDatatype *precedence,
		  FoDatatype *condity,
		  gfloat hundred_percent,
		  GError **error)
{
  FoDatatype *use_space = NULL;
  gfloat use_shortform = 0.0;
  gfloat use_optimum = 0.0;

  g_return_val_if_fail (shortform == NULL ||
			FO_IS_LENGTH (shortform) ||
			FO_IS_PERCENTAGE (shortform) ||
			FO_IS_SPACE (shortform),
			NULL);
  g_return_val_if_fail (minimum == NULL ||
			FO_IS_LENGTH (minimum) ||
			FO_IS_PERCENTAGE (minimum),
			NULL);
  g_return_val_if_fail (optimum == NULL ||
			FO_IS_LENGTH (optimum) ||
			FO_IS_PERCENTAGE (optimum),
			NULL);
  g_return_val_if_fail (maximum == NULL ||
			FO_IS_LENGTH (maximum) ||
			FO_IS_PERCENTAGE (maximum),
			NULL);
  g_return_val_if_fail (precedence == NULL || FO_IS_INTEGER (precedence),
			NULL);
  g_return_val_if_fail (condity == NULL ||
			FO_IS_BOOLEAN (condity), NULL);

  if (FO_IS_SPACE (shortform) &&
      minimum == NULL &&
      optimum == NULL &&
      maximum == NULL &&
      precedence == NULL &&
      condity == NULL)
    {
      return fo_space_copy (shortform);
    }

  if (shortform == NULL)
    {
      use_space = fo_space_new ();
    }
  else if (FO_IS_SPACE (shortform))
    {
      use_space = fo_space_copy (shortform);
    }
  else if (FO_IS_PERCENTAGE (shortform))
    {
      use_shortform =
	fo_percentage_get_value (shortform) * 0.01 *
	hundred_percent;

      use_space = fo_space_new ();

      fo_space_set_minimum (use_space, use_shortform);
      fo_space_set_optimum (use_space, use_shortform);
      fo_space_set_maximum (use_space, use_shortform);
    }
  else if (FO_IS_LENGTH (shortform))
    {
      use_shortform = fo_length_get_value (shortform);

      use_space = fo_space_new ();

      fo_space_set_minimum (use_space, use_shortform);
      fo_space_set_optimum (use_space, use_shortform);
      fo_space_set_maximum (use_space, use_shortform);
    }
  else
    {
      g_assert_not_reached ();
    }

  if (minimum != NULL)
    {
      if (FO_IS_LENGTH (minimum))
	{
	  fo_space_set_minimum (use_space, fo_length_get_value (minimum));
	}
      else if (FO_IS_PERCENTAGE (minimum))
	{
	  fo_space_set_minimum (use_space,
				fo_percentage_get_value (minimum) * 0.01 *
				hundred_percent);
	}
      else
	{
	  g_assert_not_reached ();
	}
    }

  if (maximum != NULL)
    {
      if (FO_IS_LENGTH (maximum))
	{
	  fo_space_set_maximum (use_space, fo_length_get_value (maximum));
	}
      else if (FO_IS_PERCENTAGE (maximum))
	{
	  fo_space_set_maximum (use_space,
				fo_percentage_get_value (maximum) * 0.01 *
				hundred_percent);
	}
      else
	{
	  g_assert_not_reached ();
	}
    }

  if (optimum != NULL)
    {
      if (FO_IS_LENGTH (optimum))
	{
	  use_optimum = fo_length_get_value (optimum);
	}
      else if (FO_IS_PERCENTAGE (optimum))
	{
	  use_optimum =
	    fo_percentage_get_value (optimum) * 0.01 *
	    hundred_percent;
	}
      else
	{
	  g_assert_not_reached ();
	}

      fo_space_set_minimum (use_space, MIN (fo_space_get_minimum (use_space),
					    use_optimum));
      fo_space_set_optimum (use_space, use_optimum);
      fo_space_set_maximum (use_space, MAX (fo_space_get_maximum (use_space),
					    use_optimum));
    }

  if (precedence != NULL)
    {
      fo_space_set_precedence (use_space, fo_integer_get_value (precedence));
    }

  if (condity != NULL)
    {
      fo_space_set_condity (use_space, fo_boolean_get_value (condity));
    }

  return use_space;
}
