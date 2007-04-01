/* Fo
 * fo-color.c: Color datatype
 *
 * Copyright (C) 2001, 2002 Sun Microsystems
 *
 * $Id: fo-color.c,v 1.6 2005/03/10 17:38:29 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-color.h"
#include "util/fo-hash-table.h"

#define FO_COLOR_VALUE_MAX	0xFFFF

enum {
  PROP_0,
  PROP_RED,
  PROP_GREEN,
  PROP_BLUE
};

struct _FoColor
{
  FoDatatype parent_instance;

  guint16 red;
  guint16 green;
  guint16 blue;
};

struct _FoColorClass
{
  FoDatatypeClass parent_class;

  FoHashTable *colors;
};

static void fo_color_init           (FoColor      *color);
static void fo_color_class_init     (FoColorClass *klass);
static void fo_color_set_property   (GObject      *object,
				     guint         prop_id,
				     const GValue *value,
				     GParamSpec   *pspec);
static void fo_color_get_property   (GObject      *object,
				     guint         prop_id,
				     GValue       *value,
				     GParamSpec   *pspec);
static void fo_color_finalize       (GObject      *object);
static guint fo_color_hash_func     (gconstpointer v);
static gint  fo_color_equal_func    (gconstpointer v1,
				     gconstpointer v2);

FoDatatype * fo_color_copy          (FoDatatype   *datatype);
gchar*       fo_color_sprintf       (FoObject     *object);

static void  fo_color_set_red       (FoDatatype   *color,
				     guint16       new_red);
static void  fo_color_set_green     (FoDatatype   *color,
				     guint16       new_green);
static void  fo_color_set_blue      (FoDatatype   *color,
				     guint16       new_blue);


static gpointer parent_class;

/**
 * fo_color_get_type:
 * @void: 
 * 
 * Register the #FoColor object type.
 * 
 * Return value: #GType value of the #FoColor object type.
 **/
GType
fo_color_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoColorClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_color_class_init,
        NULL,		/* class_finalize */
        NULL,           /* class_data */
        sizeof (FoColor),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_color_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoColor",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_color_init:
 * @color: #FoColor object to initialise
 * 
 * Implements #GInstanceInitFunc for #FoColor
 **/
void
fo_color_init (FoColor *color)
{
  color->red = 0;
  color->green = 0;
  color->blue = 0;
}

/**
 * fo_color_class_init:
 * @klass: #FoColorClass object to initialise
 * 
 * Implements #GClassInitFunc for #FoColorClass
 **/
void
fo_color_class_init (FoColorClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  
  /*
   * Initialise the hash table for FoColor instances.
   */
  klass->colors = fo_hash_table_new ();

  parent_class = g_type_class_peek_parent (klass);
  
  /*
   * Set the class-specific 'equal' and 'hash' functions.
   */
  fo_object_class->equal_func = fo_color_equal_func;
  fo_object_class->hash_func = fo_color_hash_func;

  object_class->finalize = fo_color_finalize;

  object_class->set_property = fo_color_set_property;
  object_class->get_property = fo_color_get_property;

  g_object_class_install_property (object_class,
                                   PROP_RED,
                                   g_param_spec_uint ("red",
						     _("Red"),
						     _("Color red value"),
						     0,
						     FO_COLOR_VALUE_MAX,
						     0,
						     G_PARAM_READWRITE |
						      G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_GREEN,
                                   g_param_spec_uint ("green",
						      _("Green"),
						      _("Color green value"),
						      0,
						      FO_COLOR_VALUE_MAX,
						      0,
						      G_PARAM_READWRITE |
						      G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_BLUE,
                                   g_param_spec_uint ("blue",
						      _("Blue"),
						      _("Color blue value"),
						      0,
						      FO_COLOR_VALUE_MAX,
						      0,
						      G_PARAM_READWRITE |
						      G_PARAM_CONSTRUCT_ONLY));

  FO_DATATYPE_CLASS (klass)->copy = fo_color_copy;
  FO_OBJECT_CLASS (klass)->print_sprintf = fo_color_sprintf;
}

/**
 * fo_color_finalize:
 * @object: #FoColor object to finalize
 * 
 * Implements #GObjectFinalizeFunc for #FoColor
 **/
void
fo_color_finalize (GObject *object)
{
  FoColor *color;

  color = FO_COLOR (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_color_set_property:
 * @object:  #GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for #FoColor
 **/
void
fo_color_set_property (GObject         *object,
		       guint            prop_id,
		       const GValue    *value,
		       GParamSpec      *pspec)
{
  FoDatatype *color;

  color = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_RED:
      fo_color_set_red (color, g_value_get_uint (value));
      break;
    case PROP_GREEN:
      fo_color_set_green (color, g_value_get_uint (value));
      break;
    case PROP_BLUE:
      fo_color_set_blue (color, g_value_get_uint (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_color_get_property:
 * @object:  #GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   #GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for #FoColor
 **/
void
fo_color_get_property (GObject         *object,
		       guint            prop_id,
		       GValue          *value,
		       GParamSpec      *pspec)
{
  FoDatatype *color;

  color = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_RED:
      g_value_set_uint (value, fo_color_get_red (color));
      break;
    case PROP_GREEN:
      g_value_set_uint (value, fo_color_get_green (color));
      break;
    case PROP_BLUE:
      g_value_set_uint (value, fo_color_get_blue (color));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_color_new:
 * 
 * Creates a new #FoColor initialized to default value.
 * 
 * Return value: the new #FoColor.
 **/
FoDatatype *
fo_color_new (void)
{
  FoDatatype *color;

  color = FO_DATATYPE (g_object_new (fo_color_get_type (), NULL));
  
  return color;
}

/**
 * fo_color_new_with_value:
 * @red:   Red component of new #FoColor.
 * @green: Green component of new #FoColor.
 * @blue:  Blue component of new #FoColor.
 * 
 * Creates a new #FoColor with specified values.
 * 
 * Return value: New #FoColor.
 **/
FoDatatype *
fo_color_new_with_value (guint red,
			 guint green,
			 guint blue)
{
    FoDatatype *color = fo_color_new ();

    fo_color_set_red (color, red);
    fo_color_set_blue (color, blue);
    fo_color_set_green (color, green);

    FoDatatype *hashed_color =
	(FoDatatype *) fo_hash_table_lookup (FO_COLOR_GET_CLASS(color)->colors,
					     FO_OBJECT (color),
					     NULL);

    if (hashed_color == NULL)
    {
	fo_hash_table_insert (FO_COLOR_GET_CLASS(color)->colors,
			      FO_OBJECT (color),
			      FO_OBJECT (color),
			      NULL);

	hashed_color = color;
    }

    /*
    g_log(G_LOG_DOMAIN,
	  G_LOG_LEVEL_DEBUG,
	  "FoColor count: %d",
	  fo_hash_table_size (FO_COLOR_GET_CLASS (hashed_color)->colors));
    */

    return hashed_color;
}

/**
 * fo_color_hash_func:
 * @v: #FoColor to hash
 * 
 * Create hash code for @v.
 * 
 * Return value: Hash code for object.
 **/
guint
fo_color_hash_func (gconstpointer v)
{
    FoColor *color = (FoColor *) v;

    return (((color->red & 0xFF00) << 8) |
	    (color->green & 0xFF) |
	    ((color->blue & 0xFF) >> 8));
}

/**
 * fo_color_equal_func:
 * @v1: First #FoColor to compare.
 * @v2: Second #FoColor to compare.
 * 
 * Compare two #FoColor for equality.
 * 
 * Return value: %TRUE if objects are equal.
 **/
gboolean
fo_color_equal_func (gconstpointer v1,
		     gconstpointer v2)
{
    gint equal = FALSE;

    FoColor *color1 = (FoColor *) v1;
    FoColor *color2 = (FoColor *) v2;

    if ((color1->red == color2->red) &&
	(color1->green == color2->green) &&
	(color1->blue == color2->blue))
    {
	equal = TRUE;
    }

    return equal;
}

/**
 * fo_color_get_red:
 * @color: #FoColor.
 * 
 * Gets the 'red' component of @color.
 * 
 * Return value: 'red' component of @color.
 **/
guint16
fo_color_get_red (FoDatatype *color)
{
  g_return_val_if_fail (color != NULL, 0);
  g_return_val_if_fail (FO_IS_COLOR (color), 0);

  return FO_COLOR (color)->red;
}

/**
 * fo_color_set_red:
 * @color:   #FoColor.
 * @new_red: New value of 'red' component of @color.
 * 
 * Sets the 'red' component of @color.
 **/
void
fo_color_set_red (FoDatatype *color,
		  guint16 new_red)
{
  g_return_if_fail (color != NULL);
  g_return_if_fail (FO_IS_COLOR (color));

  FO_COLOR (color)->red = new_red;
  /*g_object_notify (G_OBJECT (color), "red");*/
}

/**
 * fo_color_get_green:
 * @color: #FoColor.
 * 
 * Gets the 'green' component of @color.
 * 
 * Return value: 'green' component of @color.
 **/
guint16
fo_color_get_green (FoDatatype *color)
{
  g_return_val_if_fail (color != NULL, 0);
  g_return_val_if_fail (FO_IS_COLOR (color), 0);

  return FO_COLOR (color)->green;
}

/**
 * fo_color_set_green:
 * @color:     #FoColor.
 * @new_green: New value of 'green' component of @color.
 * 
 * Sets the 'green' component of @color.
 **/
void
fo_color_set_green (FoDatatype *color,
		    guint16 new_green)
{
  g_return_if_fail (color != NULL);
  g_return_if_fail (FO_IS_COLOR (color));

  FO_COLOR (color)->green = new_green;
  /*g_object_notify (G_OBJECT (color), "green");*/
}

/**
 * fo_color_get_blue:
 * @color: #FoColor.
 * 
 * Gets the 'blue' component of @color.
 * 
 * Return value: 'blue' component of @color.
 **/
guint16
fo_color_get_blue (FoDatatype *color)
{
  g_return_val_if_fail (color != NULL, 0);
  g_return_val_if_fail (FO_IS_COLOR (color), 0);

  return FO_COLOR (color)->blue;
}

/**
 * fo_color_set_blue:
 * @color:    #FoColor.
 * @new_blue: New value of 'blue' component of @color.
 * 
 * Sets the 'blue' component of @color.
 **/
void
fo_color_set_blue (FoDatatype *color,
		   guint16 new_blue)
{
  g_return_if_fail (color != NULL);
  g_return_if_fail (FO_IS_COLOR (color));

  FO_COLOR (color)->blue = new_blue;
  /*g_object_notify (G_OBJECT (color), "blue");*/
}

/**
 * fo_color_copy:
 * @datatype: #FoColor to be copied
 * 
 * Create a copy of @datatype
 * 
 * Return value: New #FoColor
 **/
FoDatatype*
fo_color_copy (FoDatatype *datatype)
{
  FoDatatype *fo_color;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_COLOR (datatype), NULL);

  fo_color = fo_color_new ();
  FO_COLOR (fo_color)->red = FO_COLOR (datatype)->red;
  FO_COLOR (fo_color)->green = FO_COLOR (datatype)->green;
  FO_COLOR (fo_color)->blue = FO_COLOR (datatype)->blue;

  return fo_color;
}

/**
 * fo_color_sprintf:
 * @object: #FoColor to be printed
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object
 **/
gchar*
fo_color_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_COLOR (object), NULL);

  return (g_strdup_printf("#%04x%04x%04x",
			  FO_COLOR (object)->red,
			  FO_COLOR (object)->green,
			  FO_COLOR (object)->blue));
}

/**
 * fo_color_get_color_black:
 * 
 * Get an #FoColor with the well-known value for the color 'black'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_black (void)
{
  static FoDatatype *black = NULL;

  if (!black)
    {
	black = fo_color_new_with_value (0x0000, 0x0000, 0x0000);
    }

  return black;
}

/**
 * fo_color_get_color_silver:
 * 
 * Get an #FoColor with the well-known value for the color 'silver'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_silver (void)
{
  static FoDatatype *silver = NULL;

  if (silver == NULL)
    {
	silver = fo_color_new_with_value (0xC000, 0xC000, 0xC000);
    }

  return silver;
}

/**
 * fo_color_get_color_gray:
 * 
 * Get an #FoColor with the well-known value for the color 'gray'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_gray (void)
{
  static FoDatatype *gray = NULL;

  if (!gray)
    {
	gray = fo_color_new_with_value(0x8000, 0x8000, 0x8000);
    }

  return gray;
}

/**
 * fo_color_get_color_white:
 * 
 * Get an #FoColor with the well-known value for the color 'white'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_white (void)
{
  static FoDatatype *white = NULL;

  if (!white)
    {
	white = fo_color_new_with_value (0xFFFF, 0xFFFF, 0xFFFF);
    }

  return white;
}

/**
 * fo_color_get_color_maroon:
 * 
 * Get an #FoColor with the well-known value for the color 'maroon'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_maroon (void)
{
  static FoDatatype *maroon = NULL;

  if (!maroon)
    {
	maroon = fo_color_new_with_value (0x8000, 0x0000, 0x0000);
    }

  return maroon;
}

/**
 * fo_color_get_color_red:
 * 
 * Get an #FoColor with the well-known value for the color 'red'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_red (void)
{
  static FoDatatype *red = NULL;

  if (!red)
    {
	red = fo_color_new_with_value (0xFFFF, 0x0000, 0x0000);
    }

  return red;
}

/**
 * fo_color_get_color_purple:
 * 
 * Get an #FoColor with the well-known value for the color 'purple'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_purple (void)
{
  static FoDatatype *purple = NULL;

  if (!purple)
    {
	purple = fo_color_new_with_value (0x8000, 0x0000, 0x8000);
    }

  return purple;
}

/**
 * fo_color_get_color_fuchsia:
 * 
 * Get an #FoColor with the well-known value for the color 'fuchsia'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_fuchsia (void)
{
  static FoDatatype *fuchsia = NULL;

  if (!fuchsia)
    {
	fuchsia = fo_color_new_with_value (0xFFFF, 0x0000, 0xFFFF);
    }

  return fuchsia;
}

/**
 * fo_color_get_color_green:
 * 
 * Get an #FoColor with the well-known value for the color 'green'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_green (void)
{
  static FoDatatype *green = NULL;

  if (!green)
    {
      green = fo_color_new_with_value (0x0000, 0x8000, 0x0000);
    }

  return green;
}

/**
 * fo_color_get_color_lime:
 * 
 * Get an #FoColor with the well-known value for the color 'lime'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_lime (void)
{
  static FoDatatype *lime = NULL;

  if (!lime)
    {
	lime = fo_color_new_with_value (0x0000, 0xFFFF, 0x0000);
    }

  return lime;
}

/**
 * fo_color_get_color_olive:
 * 
 * Get an #FoColor with the well-known value for the color 'olive'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_olive (void)
{
  static FoDatatype *olive = NULL;

  if (!olive)
    {
	olive = fo_color_new_with_value (0x8000, 0x8000, 0x0000);
    }

  return olive;
}

/**
 * fo_color_get_color_yellow:
 * 
 * Get an #FoColor with the well-known value for the color 'yellow'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_yellow (void)
{
  static FoDatatype *yellow = NULL;

  if (!yellow)
    {
	yellow = fo_color_new_with_value (0xFFFF, 0xFFFF, 0x0000);
    }

  return yellow;
}

/**
 * fo_color_get_color_navy:
 * 
 * Get an #FoColor with the well-known value for the color 'navy'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_navy (void)
{
  static FoDatatype *navy = NULL;

  if (!navy)
    {
	navy = fo_color_new_with_value (0x0000, 0x0000, 0x8000);
    }

  return navy;
}

/**
 * fo_color_get_color_blue:
 * 
 * Get an #FoColor with the well-known value for the color 'blue'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_blue (void)
{
  static FoDatatype *blue = NULL;

  if (!blue)
    {
	blue = fo_color_new_with_value (0x0000, 0x0000, 0xFFFF);
    }

  return blue;
}

/**
 * fo_color_get_color_teal:
 * 
 * Get an #FoColor with the well-known value for the color 'teal'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_teal (void)
{
  static FoDatatype *teal = NULL;

  if (!teal)
    {
	teal = fo_color_new_with_value (0x0000, 0x8000, 0x8000);
    }

  return teal;
}

/**
 * fo_color_get_color_aqua:
 * 
 * Get an #FoColor with the well-known value for the color 'aqua'.
 * 
 * Return value: The #FoColor.
 **/
FoDatatype*
fo_color_get_color_aqua (void)
{
  static FoDatatype *aqua = NULL;

  if (!aqua)
    {
	aqua = fo_color_new_with_value (0x0000, 0xFFFF,  0xFFFF);
    }

  return aqua;
}

/**
 * fo_color_get_color_one_half:
 * @color: Original color.
 * 
 * Get an #FoColor that is one-half the intensity of @color.
 * 
 * Return value: A color with one-half the intensity of @color.
 **/
FoDatatype*
fo_color_get_color_one_half (FoDatatype *color)
{
  FoDatatype *new_color;

  g_return_val_if_fail (FO_IS_COLOR (color), NULL);

  new_color = fo_color_new_with_value (FO_COLOR (color)->red >> 1,
				       FO_COLOR (color)->green >> 1,
				       FO_COLOR (color)->blue >> 1);

  return new_color;
}

/**
 * fo_color_get_color_three_quarter:
 * @color: Original color.
 * 
 * Get an #FoColor that is three-quarters of the intensity of @color.
 * 
 * Return value: A color with three-quarters of the intensity of @color.
 **/
FoDatatype*
fo_color_get_color_three_quarter (FoDatatype *color)
{
  FoDatatype *new_color;

  g_return_val_if_fail (FO_IS_COLOR (color), NULL);

  new_color =
      fo_color_new_with_value ((FO_COLOR (color)->red   >> 1) + (FO_COLOR (color)->red   >> 2),
			       (FO_COLOR (color)->green >> 1) + (FO_COLOR (color)->green >> 2),
			       (FO_COLOR (color)->blue  >> 1) + (FO_COLOR (color)->blue  >> 2));

  return new_color;
}

/**
 * fo_color_get_color_one_quarter:
 * @color: Original color.
 * 
 * Get an #FoColor that is one-quarter the intensity of @color.
 * 
 * Return value: A color with one-quarter the intensity of @color.
 **/
FoDatatype*
fo_color_get_color_one_quarter (FoDatatype *color)
{
  FoDatatype *new_color;

  g_return_val_if_fail (FO_IS_COLOR (color), NULL);

  new_color =
      fo_color_new_with_value (FO_COLOR (color)->red >> 2,
			       FO_COLOR (color)->green >> 2,
			       FO_COLOR (color)->blue >> 2);

  return new_color;
}
