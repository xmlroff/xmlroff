/* Fo
 * fo-length-range.c: length-range datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-length-range.h"
#include "fo-length-range-private.h"
#include "fo-enum.h"
#include "fo-length.h"
#include "fo-percentage.h"

enum {
  PROP_0,
  PROP_MINIMUM,
  PROP_OPTIMUM,
  PROP_MAXIMUM
};

static void fo_length_range_init         (FoLengthRange      *length_range);
static void fo_length_range_class_init   (FoLengthRangeClass *klass);
static void fo_length_range_set_property (GObject       *object,
					  guint          prop_id,
					  const GValue  *value,
					  GParamSpec    *pspec);
static void fo_length_range_get_property (GObject       *object,
					  guint          prop_id,
					  GValue        *value,
					  GParamSpec    *pspec);
static void fo_length_range_finalize     (GObject       *object);

static gchar*      fo_length_range_sprintf     (FoObject *object);
static FoDatatype* fo_length_range_copy        (FoDatatype *datatype);
static void        fo_length_range_set_minimum (FoDatatype *datatype,
						FoDatatype *new_minimum);
static void        fo_length_range_set_optimum (FoDatatype *datatype,
						FoDatatype *new_optimum);
static void        fo_length_range_set_maximum (FoDatatype *datatype,
						FoDatatype *new_maximum);

static gpointer parent_class;

/**
 * fo_length_range_get_type:
 * 
 * Register the #FoLengthRange object type.
 * 
 * Return value: GType value of the #FoLengthRange object type.
 **/
GType
fo_length_range_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLengthRangeClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_length_range_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLengthRange),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_length_range_init,
	NULL
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoLengthRange",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_length_range_init:
 * @keep: #FoLengthRange object to initialise
 * 
 * Implements GInstanceInitFunc for #FoLengthRange
 **/
void
fo_length_range_init (FoLengthRange *length_range)
{
  length_range->minimum = g_object_ref (fo_length_get_length_zero());
  length_range->optimum = g_object_ref (fo_length_get_length_zero());
  length_range->maximum = g_object_ref (fo_length_get_length_zero());
}

/**
 * fo_length_range_class_init:
 * @klass: #FoLengthRangeClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoLengthRangeClass.
 **/
void
fo_length_range_class_init (FoLengthRangeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_length_range_finalize;

  object_class->set_property = fo_length_range_set_property;
  object_class->get_property = fo_length_range_get_property;

  FO_DATATYPE_CLASS (klass)->copy = fo_length_range_copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = fo_length_range_sprintf;

  g_object_class_install_property (object_class,
                                   PROP_MINIMUM,
				   g_param_spec_object ("minimum",
							_("Minimum"),
							_("Length range minimum value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_OPTIMUM,
                                   g_param_spec_object ("optimum",
							_("Optimum"),
							_("Length range optimum value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_MAXIMUM,
                                   g_param_spec_object ("maximum",
							_("Maximum"),
							_("Length range maximum value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));
}

/**
 * fo_length_range_finalize:
 * @object: #FoLengthRange object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoLengthRange.
 **/
void
fo_length_range_finalize (GObject *object)
{
  FoLengthRange *length_range;

  length_range = FO_LENGTH_RANGE (object);

  g_object_unref (length_range->minimum);
  g_object_unref (length_range->optimum);
  g_object_unref (length_range->maximum);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_length_range_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoLengthRange.
 **/
void
fo_length_range_set_property (GObject         *object,
			      guint            prop_id,
			      const GValue    *value,
			      GParamSpec      *pspec)
{
  FoDatatype *length_range;

  length_range = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_MINIMUM:
      fo_length_range_set_minimum (length_range, g_value_get_object (value));
      break;
    case PROP_OPTIMUM:
      fo_length_range_set_optimum (length_range, g_value_get_object (value));
      break;
    case PROP_MAXIMUM:
      fo_length_range_set_maximum (length_range, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_length_range_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoLengthRange.
 **/
void
fo_length_range_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *length_range;

  length_range = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_MINIMUM:
      g_value_set_object (value, fo_length_range_get_minimum (length_range));
      break;
    case PROP_OPTIMUM:
      g_value_set_object (value, fo_length_range_get_optimum (length_range));
      break;
    case PROP_MAXIMUM:
      g_value_set_object (value, fo_length_range_get_maximum (length_range));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_length_range_new:
 * 
 * Creates a new #FoLengthRange initialized to default value.
 * 
 * Return value: the new #FoLengthRange.
 **/
FoDatatype*
fo_length_range_new (void)
{
  FoDatatype *length_range;

  length_range = FO_DATATYPE (g_object_new (fo_length_range_get_type (),
					    "minimum",
					    fo_length_get_length_zero (),
					    "optimum",
					    fo_length_get_length_zero (),
					    "maximum",
					    fo_length_get_length_zero (),
					    NULL));

  return length_range;
}

/**
 * fo_length_range_new_auto:
 * 
 * Creates a new #FoLengthRange with all components initialized to "auto".
 * 
 * Return value: the new #FoLengthRange
 **/
FoDatatype*
fo_length_range_new_auto (void)
{
  FoDatatype *length_range;

  length_range = fo_length_range_new ();

  fo_length_range_set_minimum (length_range, fo_enum_get_enum_auto());
  fo_length_range_set_optimum (length_range, fo_enum_get_enum_auto());
  fo_length_range_set_maximum (length_range, fo_enum_get_enum_auto());
  
  return length_range;
}

/**
 * fo_length_range_new_with_value:
 * @datatype: Value for .minimum, .optimum, and .maximum values of the
 *            new #FoLengthRange.
 * 
 * Creates a new #FoLengthRange set to @value.
 * 
 * Return value: The new #FoLengthRange.
 **/
FoDatatype*
fo_length_range_new_with_value (FoDatatype *datatype)
{
  FoDatatype *length_range = fo_length_range_new ();

  g_return_val_if_fail (length_range != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH (datatype) ||
			FO_IS_PERCENTAGE (datatype) ||
			FO_IS_ENUM (datatype),
			NULL);

  fo_length_range_set_minimum (length_range, datatype);
  fo_length_range_set_optimum (length_range, datatype);
  fo_length_range_set_maximum (length_range, datatype);

  return length_range;
}

/**
 * fo_length_range_set_minimum:
 * @datatype:     #FoLengthRange
 * @new_minimum:  New .minimum value
 * 
 * Sets the .minimum component of @datatype
 **/
void
fo_length_range_set_minimum (FoDatatype *datatype,
			     FoDatatype *new_minimum)
{
  FoLengthRange *length_range = (FoLengthRange *) datatype;

  g_return_if_fail (length_range != NULL);
  g_return_if_fail (FO_IS_LENGTH_RANGE (length_range));
  g_return_if_fail (FO_IS_DATATYPE (new_minimum));

  if (new_minimum)
    g_object_ref (G_OBJECT (new_minimum));
  if (length_range->minimum)
    g_object_unref (G_OBJECT (length_range->minimum));
  length_range->minimum = new_minimum;
  /*g_object_notify(G_OBJECT(length_range), "minimum");*/
}

/**
 * fo_length_range_get_minimum:
 * @datatype: #FoLengthRange
 * 
 * Gets the .minimum component value of @datatype
 * 
 * Return value: The .minimum value of @datatype
 **/
FoDatatype*
fo_length_range_get_minimum (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_RANGE (datatype), 0);

  return FO_LENGTH_RANGE (datatype)->minimum;
}

/**
 * fo_length_range_set_optimum:
 * @datatype:     #FoLengthRange
 * @new_optimum:  New .optimum value
 * 
 * Sets the .optimum component of @datatype
 **/
void
fo_length_range_set_optimum (FoDatatype *datatype,
			     FoDatatype *new_optimum)
{
  FoLengthRange *length_range = (FoLengthRange *) datatype;

  g_return_if_fail (length_range != NULL);
  g_return_if_fail (FO_IS_LENGTH_RANGE (length_range));
  g_return_if_fail (FO_IS_DATATYPE (new_optimum));

  if (new_optimum)
    g_object_ref (G_OBJECT (new_optimum));
  if (length_range->optimum)
    g_object_unref (G_OBJECT (length_range->optimum));
  length_range->optimum = new_optimum;
  /*g_object_notify(G_OBJECT(length_range), "optimum");*/
}

/**
 * fo_length_range_get_optimum:
 * @datatype: #FoLengthRange
 * 
 * Gets the .optimum component value of @datatype
 * 
 * Return value: The .optimum value of @datatype
 **/
FoDatatype*
fo_length_range_get_optimum (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_RANGE (datatype), 0);

  return FO_LENGTH_RANGE (datatype)->optimum;
}

/**
 * fo_length_range_set_maximum:
 * @datatype:     #FoLengthRange
 * @new_maximum:  New .maximum value
 * 
 * Sets the .maximum component of @datatype
 **/
void
fo_length_range_set_maximum (FoDatatype *datatype,
			     FoDatatype *new_maximum)
{
  FoLengthRange *length_range = (FoLengthRange *) datatype;

  g_return_if_fail (length_range != NULL);
  g_return_if_fail (FO_IS_LENGTH_RANGE (length_range));
  g_return_if_fail (FO_IS_DATATYPE (new_maximum));

  if (new_maximum)
    g_object_ref (G_OBJECT (new_maximum));
  if (length_range->maximum)
    g_object_unref (G_OBJECT (length_range->maximum));
  length_range->maximum = new_maximum;
  /*g_object_notify(G_OBJECT(length_range), "maximum");*/
}

/**
 * fo_length_range_get_maximum:
 * @datatype: #FoLengthRange
 * 
 * Gets the .maximum component value of @datatype
 * 
 * Return value: The .maximum value of @datatype
 **/
FoDatatype*
fo_length_range_get_maximum (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_RANGE (datatype), 0);

  return FO_LENGTH_RANGE (datatype)->maximum;
}

/**
 * fo_length_range_sprintf:
 * @object: #FoLengthRange whose value is to be printed
 * 
 * Create and return a string representation of the value of @object,
 * which must be an #FoLengthRange.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of value of @object
 **/
gchar*
fo_length_range_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_RANGE (object), NULL);

  return g_strdup_printf ("min: %s; opt: %s; max: %s",
			  fo_object_sprintf (FO_LENGTH_RANGE (object)->minimum),
			  fo_object_sprintf (FO_LENGTH_RANGE (object)->optimum),
			  fo_object_sprintf (FO_LENGTH_RANGE (object)->maximum));
}

/**
 * fo_length_range_copy:
 * @datatype: Source #FoLengthRange
 * 
 * Creates a copy of @datatype
 * 
 * Return value: Copy of @datatype
 **/
FoDatatype*
fo_length_range_copy (FoDatatype *datatype)
{
  FoDatatype* length_range;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH_RANGE (datatype), NULL);

  length_range = fo_length_range_new ();
  FO_LENGTH_RANGE (length_range)->minimum =
    FO_LENGTH_RANGE (datatype)->minimum;
  FO_LENGTH_RANGE (length_range)->optimum =
    FO_LENGTH_RANGE (datatype)->optimum;
  FO_LENGTH_RANGE (length_range)->maximum =
    FO_LENGTH_RANGE (datatype)->maximum;

  return (length_range);
}

/**
 * fo_length_range_resolve:
 * @shortform:       Single-value short form of the length-range, or
 *                     NULL
 * @minimum:         .minimum component of the length-range, or NULL
 * @optimum:         .optimum component of the length-range, or NULL
 * @maximum:         .maximum component of the length-range, or NULL
 * @hundred_percent: Length to use as 100% when components expressed as
 *                     percentages
 * @error:           GError used for reporting errors
 * 
 * Resolve the shortform and components of the length-range in
 * accordance with Section 5.11, Datatypes, of the XSL 1.0
 * Recommendation.
 *
 * Does not change the ref-count of any FoDatatype arguments.
 *
 * Return value: Compound length-range datatype, or NULL if an error
 *               occurred
 **/
FoDatatype*
fo_length_range_resolve (FoDatatype *shortform,
			 FoDatatype *minimum,
			 FoDatatype *optimum,
			 FoDatatype *maximum,
			 gfloat      hundred_percent,
			 GError    **error G_GNUC_UNUSED)
{
  FoDatatype *use_length_range = NULL;
  gfloat use_shortform_value;
  FoDatatype *use_optimum;
  gfloat use_optimum_value = 0.0;

  g_return_val_if_fail (shortform == NULL ||
			FO_IS_LENGTH_RANGE (shortform) ||
			FO_IS_LENGTH (shortform) ||
			FO_IS_PERCENTAGE (shortform),
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

  if (FO_IS_LENGTH_RANGE (shortform) &&
      minimum == NULL &&
      optimum == NULL &&
      maximum == NULL)
    {
      return fo_length_range_copy (shortform);
    }

  if (shortform == NULL)
    {
      use_length_range = fo_length_range_new ();
    }
  else if (FO_IS_LENGTH_RANGE (shortform))
    {
      use_length_range = fo_length_range_copy (shortform);
    }
  else if (FO_IS_PERCENTAGE (shortform))
    {
      FoDatatype *new_component;

      use_shortform_value =
	fo_percentage_get_value (shortform) * 0.01 *
	hundred_percent;

      use_length_range = fo_length_range_new ();

      new_component = fo_length_new_with_value (use_shortform_value);

      fo_length_range_set_minimum (use_length_range, new_component);
      fo_length_range_set_optimum (use_length_range, new_component);
      fo_length_range_set_maximum (use_length_range, new_component);
    }
  else if (FO_IS_LENGTH (shortform))
    {
      use_length_range = fo_length_range_new ();

      fo_length_range_set_minimum (use_length_range, shortform);
      fo_length_range_set_optimum (use_length_range, shortform);
      fo_length_range_set_maximum (use_length_range, shortform);
    }
  else
    {
      g_assert_not_reached ();
    }

  if (minimum != NULL)
    {
      if (FO_IS_LENGTH (minimum))
	{
	  fo_length_range_set_minimum (use_length_range, minimum);
	}
      else if (FO_IS_PERCENTAGE (minimum))
	{
	  fo_length_range_set_minimum (use_length_range,
				       g_object_new (FO_TYPE_LENGTH,
						     "value",
						     fo_percentage_get_value (minimum) * 0.01 *
						     hundred_percent,
						     NULL));
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
	  fo_length_range_set_maximum (use_length_range, maximum);
	}
      else if (FO_IS_PERCENTAGE (maximum))
	{
	  fo_length_range_set_maximum (use_length_range,
				       g_object_new (FO_TYPE_LENGTH,
						     "value",
						     fo_percentage_get_value (maximum) * 0.01 *
						     hundred_percent,
						     NULL));
	}
      else
	{
	  g_assert_not_reached ();
	}
    }

  if (optimum != NULL)
    {
      use_optimum = optimum;

      if (FO_IS_LENGTH (optimum))
	{
	  use_optimum_value = fo_length_get_value (optimum);
	  fo_length_range_set_optimum (use_length_range, optimum);
	}
      else if (FO_IS_PERCENTAGE (optimum))
	{
	  use_optimum_value =
	    fo_percentage_get_value (optimum) * 0.01 *
	    hundred_percent;

	  fo_length_range_set_optimum (use_length_range,
				       g_object_new (FO_TYPE_LENGTH,
						     "value",
						     use_optimum_value,
						     NULL));
	}
      else
	{
	  g_assert_not_reached ();
	}
    }
  else
    {
      use_optimum = fo_length_range_get_optimum (use_length_range);
      if (FO_IS_LENGTH (use_optimum))
	{
	  use_optimum_value = fo_length_get_value (use_optimum);
	}
      else if (FO_IS_PERCENTAGE (use_optimum))
	{
	  use_optimum_value =
	    fo_percentage_get_value (use_optimum) * 0.01 *
	    hundred_percent;
	}
      else
	{
	  g_assert_not_reached ();
	}
    }

  if (use_optimum_value <=
      fo_length_get_value (fo_length_range_get_minimum (use_length_range)))
    {
      fo_length_range_set_minimum (use_length_range,
				   use_optimum);
    }

  if (use_optimum_value >=
      fo_length_get_value (fo_length_range_get_maximum (use_length_range)))
    {
      fo_length_range_set_maximum (use_length_range,
				   use_optimum);
    }


  return use_length_range;
}

/**
 * fo_length_range_resolve_allow_auto:
 * @shortform:       Single-value short form of the length-range, or
 *                     NULL
 * @minimum:         .minimum component of the length-range, or NULL
 * @optimum:         .optimum component of the length-range, or NULL
 * @maximum:         .maximum component of the length-range, or NULL
 * @hundred_percent: Length to use as 100% when components expressed as
 *                     percentages
 * @error:           GError used for reporting errors
 * 
 * Resolve the shortform and components of the length-range in
 * accordance with the definitions of block-progression-dimension and
 * inline-progression-dimension in Section 7.14, Area Dimension
 * Properties, of the XSL 1.0 Recommendation.
 *
 * Use this when "auto" is an allowed value and percentages are
 * computed into lengths.
 *
 * Does not change the ref-count of any FoDatatype arguments.
 *
 * Return value: Compound length-range datatype, or NULL if an error
 *               occurred
 **/
FoDatatype*
fo_length_range_resolve_allow_auto (FoDatatype *shortform,
				    FoDatatype *minimum,
				    FoDatatype *optimum,
				    FoDatatype *maximum,
				    gfloat      hundred_percent,
				    GError    **error G_GNUC_UNUSED)
{
  FoDatatype *use_length_range = NULL;
  FoDatatype *use_optimum;
  gfloat use_optimum_value = 0.0;

  g_return_val_if_fail (shortform == NULL ||
			(FO_IS_ENUM (shortform) &&
			 (fo_enum_get_value (shortform) ==
			  FO_ENUM_ENUM_AUTO)) ||
			FO_IS_LENGTH (shortform) ||
			FO_IS_PERCENTAGE (shortform),
			NULL);
  g_return_val_if_fail (minimum == NULL ||
			(FO_IS_ENUM (minimum) &&
			 (fo_enum_get_value (minimum) ==
			  FO_ENUM_ENUM_AUTO)) ||
			FO_IS_LENGTH (minimum) ||
			FO_IS_PERCENTAGE (minimum),
			NULL);
  g_return_val_if_fail (optimum == NULL ||
			(FO_IS_ENUM (optimum) &&
			 (fo_enum_get_value (optimum) ==
			  FO_ENUM_ENUM_AUTO)) ||
			FO_IS_LENGTH (optimum) ||
			FO_IS_PERCENTAGE (optimum),
			NULL);
  g_return_val_if_fail (maximum == NULL ||
			(FO_IS_ENUM (maximum) &&
			 (fo_enum_get_value (maximum) ==
			  FO_ENUM_ENUM_AUTO)) ||
			FO_IS_LENGTH (maximum) ||
			FO_IS_PERCENTAGE (maximum),
			NULL);

#if defined(LIBFO_DEBUG) && 0
  g_message ("length_range_resolve_with_auto:: shortform: %s; minimum: %s; optimum: %s; maximum: %s; hundred_percent: %gpt; error: %p",
	     fo_object_sprintf (shortform),
	     fo_object_sprintf (minimum),
	     fo_object_sprintf (optimum),
	     fo_object_sprintf (maximum),
	     hundred_percent,
	     error);
#endif

  if (FO_IS_LENGTH_RANGE (shortform) &&
      minimum == NULL &&
      optimum == NULL &&
      maximum == NULL)
    {
      return fo_length_range_copy (shortform);
    }

  if (shortform == NULL)
    {
      use_length_range = fo_length_range_new_auto ();
    }
  else if (FO_IS_LENGTH_RANGE (shortform))
    {
      use_length_range = fo_length_range_copy (shortform);
    }
  else if (FO_IS_PERCENTAGE (shortform) ||
	   FO_IS_LENGTH (shortform))
    {
      use_length_range = fo_length_range_new ();

      fo_length_range_set_minimum (use_length_range, shortform);
      fo_length_range_set_optimum (use_length_range, shortform);
      fo_length_range_set_maximum (use_length_range, shortform);
    }
  else
    {
      g_assert_not_reached ();
    }

  if (minimum != NULL)
    {
      if (FO_IS_LENGTH (minimum) ||
	  FO_IS_ENUM (minimum))
	{
	  fo_length_range_set_minimum (use_length_range, minimum);
	}
      else if (FO_IS_PERCENTAGE (minimum))
	{
	  fo_length_range_set_minimum (use_length_range,
				       g_object_new (FO_TYPE_LENGTH,
						     "value",
						     fo_percentage_get_value (minimum) * 0.01 *
						     hundred_percent,
						     NULL));
	}
      else
	{
	  g_assert_not_reached ();
	}
    }

  if (maximum != NULL)
    {
      if (FO_IS_LENGTH (maximum) ||
	  FO_IS_ENUM (maximum))
	{
	  fo_length_range_set_maximum (use_length_range, maximum);
	}
      else if (FO_IS_PERCENTAGE (maximum))
	{
	  fo_length_range_set_maximum (use_length_range,
				       g_object_new (FO_TYPE_LENGTH,
						     "value",
						     fo_percentage_get_value (maximum) * 0.01 *
						     hundred_percent,
						     NULL));
	}
      else 
	{
	  g_assert_not_reached ();
	}
    }

  if (optimum != NULL)
    {
      use_optimum = optimum;

      if (FO_IS_LENGTH (optimum))
	{
	  use_optimum_value = fo_length_get_value (optimum);
	  fo_length_range_set_optimum (use_length_range, optimum);
	}
      else if (FO_IS_PERCENTAGE (optimum))
	{
	  use_optimum_value =
	    fo_percentage_get_value (optimum) * 0.01 *
	    hundred_percent;

	  fo_length_range_set_optimum (use_length_range,
				       g_object_new (FO_TYPE_LENGTH,
						     "value",
						     use_optimum_value,
						     NULL));
	}
      else if (FO_IS_ENUM (optimum))
	{
	  fo_length_range_set_optimum (use_length_range, optimum);
	}
      else
	{
	  g_assert_not_reached ();
	}
    }
  else
    {
      use_optimum = fo_length_range_get_optimum (use_length_range);
      if (FO_IS_LENGTH (use_optimum))
	{
	  use_optimum_value = fo_length_get_value (use_optimum);
	}
      else if (FO_IS_PERCENTAGE (use_optimum))
	{
	  use_optimum_value =
	    fo_percentage_get_value (use_optimum) * 0.01 *
	    hundred_percent;
	}
      else if (!FO_IS_ENUM (use_optimum))
	{
	  g_assert_not_reached ();
	}
    }

  if (!FO_IS_ENUM (use_optimum) &&
      !FO_IS_ENUM (fo_length_range_get_minimum (use_length_range)))
    {
      FoDatatype *use_minimum = fo_length_range_get_minimum (use_length_range);
      gfloat use_minimum_value = 0.0;

      if (FO_IS_LENGTH (use_minimum))
	{
	  use_minimum_value = fo_length_get_value (use_minimum);
	}
      else if (FO_IS_PERCENTAGE (use_minimum))
	{
	  use_minimum_value =
	    fo_percentage_get_value (use_minimum) * 0.01 *
	    hundred_percent;
	}
      else
	{
	  g_assert_not_reached ();
	}

      if (use_optimum_value < use_minimum_value)
	fo_length_range_set_minimum (use_length_range,
				     use_optimum);
    }

  if (!FO_IS_ENUM (use_optimum) &&
      !FO_IS_ENUM (fo_length_range_get_maximum (use_length_range)))
    {
      FoDatatype *use_maximum = fo_length_range_get_maximum (use_length_range);
      gfloat use_maximum_value = 0.0;

      if (FO_IS_LENGTH (use_maximum))
	{
	  use_maximum_value = fo_length_get_value (use_maximum);
	}
      else if (FO_IS_PERCENTAGE (use_maximum))
	{
	  use_maximum_value =
	    fo_percentage_get_value (use_maximum) * 0.01 *
	    hundred_percent;
	}
      else
	{
	  g_assert_not_reached ();
	}

      if (use_optimum_value > use_maximum_value)
	fo_length_range_set_maximum (use_length_range,
				     use_optimum);
    }

  return use_length_range;
}

/**
 * fo_length_range_get_length_range_hundred_percent:
 * 
 * Get an #FoLengthRange with the well-known value of 100%.
 * 
 * Return value: The #FoLengthRange.
 **/
FoDatatype *
fo_length_range_get_length_range_hundred_percent (void)
{
  static FoDatatype *length_range = NULL;

  if (length_range == NULL)
    {
      length_range =
	fo_length_range_new_with_value (fo_percentage_get_percentage_hundred ());
    }

  return length_range;
}
