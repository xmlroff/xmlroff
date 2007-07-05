/* Fo
 * fo-length.c: Length datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-numeric.h"
#include "fo-length.h"
#include "fo-length-conditional.h"
#include "fo-length-range.h"
#include "fo-space.h"

#ifndef FO_LENGTH_WIDTH_THIN
#define FO_LENGTH_WIDTH_THIN	0.5
#endif

#ifndef FO_LENGTH_WIDTH_MEDIUM
#define FO_LENGTH_WIDTH_MEDIUM	2.0
#endif

#ifndef FO_LENGTH_WIDTH_THICK
#define FO_LENGTH_WIDTH_THICK	4.0
#endif

#define FO_LENGTH_A4_WIDTH ((210.0 / 25.4) * 72.0)
#define FO_LENGTH_A4_HEIGHT ((297.0 / 25.4) * 72.0)

#ifndef PIXEL2DEVICE
#define PIXEL2DEVICE(x)		((x) * 72 / PIXELS_PER_INCH)
#endif

enum {
  PROP_0,
  PROP_VALUE
};

struct _FoLength
{
  FoDatatype parent_instance;

  gdouble value;
};

struct _FoLengthClass
{
  FoDatatypeClass parent_class;
  
  FoDatatype *length_zero;
};

static void fo_length_init          (FoLength      *length);
static void fo_length_class_init    (FoLengthClass *klass);
static void fo_length_set_property  (GObject       *object,
				     guint          prop_id,
				     const GValue  *value,
				     GParamSpec    *pspec);
static void fo_length_get_property  (GObject       *object,
				     guint          prop_id,
				     GValue        *value,
				     GParamSpec    *pspec);
static void fo_length_finalize      (GObject       *object);

static FoDatatype * fo_length_copy    (FoDatatype *datatype);
static gchar*       fo_length_sprintf (FoObject   *object);
static void fo_length_set_value (FoDatatype *length,
				 gdouble new_value);

static gpointer parent_class;

static FoDatatype *width_thin = NULL;
static FoDatatype *width_medium = NULL;
static FoDatatype *width_thick = NULL;

/**
 * fo_length_get_type:
 * 
 * Register the #FoLength object type.
 * 
 * Return value: #GType value of the #FoLength object type.
 **/
GType
fo_length_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLengthClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_length_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLength),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_length_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoLength",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_length_init:
 * @length: #FoLength object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoLength.
 **/
void
fo_length_init (FoLength *length)
{
  length->value = 0;
}

/**
 * fo_length_class_init:
 * @klass: #FoLengthClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoLengthClass.
 **/
void
fo_length_class_init (FoLengthClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_length_finalize;

  object_class->set_property = fo_length_set_property;
  object_class->get_property = fo_length_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_length_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_length_copy;

  g_object_class_install_property (object_class,
                                   PROP_VALUE,
                                   g_param_spec_double ("value",
						       _("Value"),
						       _("Length value"),
						       -G_MAXDOUBLE,
						       G_MAXDOUBLE,
						       0.0,
						       G_PARAM_READWRITE |
						       G_PARAM_CONSTRUCT_ONLY));
}

/**
 * fo_length_finalize:
 * @object: #FoLength object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoLength.
 **/
void
fo_length_finalize (GObject *object)
{
  FoLength *length;

  length = FO_LENGTH (object);

  /* This was giving "assertion `object->ref_count > 0' failed" messages.
  if (width_thin != NULL)
    {
      g_object_unref (width_thin);
      width_thin = NULL;
    }

  if (width_medium != NULL)
    {
      g_object_unref (width_medium);
      width_medium = NULL;
    }

  if (width_thick != NULL)
    {
      g_object_unref (width_thick);
      width_thick = NULL;
    }
  */
  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_length_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoLength.
 **/
void
fo_length_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoDatatype *length;

  length = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      g_value_set_double (value, fo_length_get_value (length));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_length_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoLength.
 **/
void
fo_length_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoDatatype *length;

  length = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_VALUE:
      fo_length_set_value (length, g_value_get_double (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_length_new:
 * 
 * Creates a new #FoLength initialized to default value.
 * 
 * Return value: The new #FoLength.
 **/
FoDatatype*
fo_length_new (void)
{
  FoDatatype* length;

  length = FO_DATATYPE (g_object_new (fo_length_get_type (), NULL));
  
  return length;
}

/**
 * fo_length_new_with_value:
 * @value: Length of the new #FoLength.
 * 
 * Creates a new #FoLength set to @value.
 * 
 * Return value: The new #FoLength.
 **/
FoDatatype*
fo_length_new_with_value (gdouble value)
{
  FoDatatype *length = fo_length_new ();

  fo_length_set_value (length, value);

  return length;
}

/**
 * fo_length_new_from_pixels:
 * @count: Number of pixels of the new #FoLength.
 * 
 * Creates a new #FoLength set to the intrinsic length of @count pixels.
 * 
 * Return value: The new #FoLength.
 **/
FoDatatype*
fo_length_new_from_pixels (gint count)
{
  FoDatatype *length = fo_length_new ();

  fo_length_set_value (length, PIXEL2DEVICE(((gdouble) count)));

  return length;
}

/**
 * fo_length_get_value:
 * @length: #FoLength.
 * 
 * Get the value of @length.
 * 
 * Return value: Numeric value of @length.
 **/
gdouble
fo_length_get_value (FoDatatype *length)
{
  g_return_val_if_fail (length != NULL, 0);
  g_return_val_if_fail (FO_IS_LENGTH (length) ||
			FO_IS_LENGTH_RANGE (length) ||
			FO_IS_LENGTH_COND (length) ||
			FO_IS_SPACE (length), 0);

  if (FO_IS_LENGTH (length))
    return FO_LENGTH (length)->value;
  else if (FO_IS_LENGTH_COND (length))
    return fo_length_cond_get_length (length);
  else if (FO_IS_LENGTH_RANGE (length))
    return fo_length_get_value (fo_length_range_get_optimum (length));
  else if (FO_IS_SPACE (length))
    return fo_space_get_optimum (length);
  else
    {
      g_assert_not_reached ();
      return 0.0;
    }
}

/**
 * fo_length_set_value:
 * @length:    #FoLength.
 * @new_value: New value for @length.
 * 
 * Set the value of @length.
 **/
void
fo_length_set_value (FoDatatype *length,
		     gdouble new_value)
{
  g_return_if_fail (length != NULL);
  g_return_if_fail (FO_IS_LENGTH (length));

  ((FoLength *) length)->value = new_value;
  /*g_object_notify (G_OBJECT (length), "value");*/
}

/**
 * fo_length_copy:
 * @datatype: #FoLength to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoLength.
 **/
FoDatatype*
fo_length_copy (FoDatatype *datatype)
{
  FoDatatype* length;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH (datatype), NULL);

  length = fo_length_new ();
  FO_LENGTH (length)->value = FO_LENGTH (datatype)->value;

  return length;
}

/**
 * fo_length_sprintf:
 * @object: #FoLength to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
gchar*
fo_length_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_LENGTH (object), NULL);

  return g_strdup_printf("%0gpt",
			 FO_LENGTH (object)->value);
}

/**
 * fo_length_get_length_minus_3pt:
 * 
 * Get an #FoLength with the well-known value of 3pt.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_length_minus_3pt (void)
{
  static FoDatatype *length = NULL;

  if (length == NULL)
    {
      length = fo_length_new_with_value (-3.0);
    }

  return length;
}

/**
 * fo_length_get_length_zero:
 * 
 * Get an #FoLength with the well-known value of 0pt.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_length_zero (void)
{
  static FoDatatype *length = NULL;

  if (length == NULL)
    {
      length = fo_length_new ();
    }

  return length;
}

/**
 * fo_length_get_length_3pt:
 * 
 * Get an #FoLength with the well-known value of 3pt.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_length_3pt (void)
{
  static FoDatatype *length = NULL;

  if (length == NULL)
    {
      length = fo_length_new_with_value (3.0);
    }

  return length;
}

/**
 * fo_length_get_length_6pt:
 * 
 * Get an #FoLength with the well-known value of 6pt.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_length_6pt (void)
{
  static FoDatatype *length = NULL;

  if (length == NULL)
    {
      length = fo_length_new_with_value (6.0);
    }

  return length;
}

/**
 * fo_length_get_length_12:
 * 
 * Get an #FoLength with the well-known value of 12pt.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_length_12 (void)
{
  static FoDatatype *length = NULL;

  if (length == NULL)
    {
      length = fo_length_new_with_value (12.0);
    }

  return length;
}

/**
 * fo_length_get_length_24:
 * 
 * Get an #FoLength with the well-known value of 24pt.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_length_24 (void)
{
  static FoDatatype *length = NULL;

  if (length == NULL)
    {
      length = fo_length_new_with_value (24.0);
    }

  return length;
}

/**
 * fo_length_get_length_A4_width:
 * 
 * Get an #FoLength with the well-known value of the width of an A4
 * page.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_length_A4_width (void)
{
  static FoDatatype *length = NULL;

  if (length == NULL)
    {
      length = fo_length_new_with_value (FO_LENGTH_A4_WIDTH);
    }

  return length;
}

/**
 * fo_length_get_length_A4_width:
 * 
 * Get an #FoLength with the well-known value of the width of an A4
 * page.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_length_A4_height (void)
{
  static FoDatatype *length = NULL;

  if (length == NULL)
    {
      length = fo_length_new_with_value (FO_LENGTH_A4_HEIGHT);
    }

  return length;
}

/**
 * fo_length_get_width_thin:
 * 
 * Get an #FoLength for the well-known width value of 'thin'.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_width_thin (void)
{
  if (width_thin == NULL)
    {
      width_thin = fo_length_new_with_value (FO_LENGTH_WIDTH_THIN);
    }

  return width_thin;
}

/**
 * fo_length_get_width_medium:
 * 
 * Get an #FoLength for the well-known width value of 'medium'.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_width_medium (void)
{
  if (width_medium == NULL)
    {
      width_medium = fo_length_new_with_value (FO_LENGTH_WIDTH_MEDIUM);
    }

  return width_medium;
}

/**
 * fo_length_get_width_thick:
 * 
 * Get an #FoLength for the well-known width value of 'thick'.
 * 
 * Return value: The #FoLength.
 **/
FoDatatype*
fo_length_get_width_thick (void)
{
  if (width_thick == NULL)
    {
      width_thick = fo_length_new_with_value (FO_LENGTH_WIDTH_THICK);
    }

  return width_thick;
}
