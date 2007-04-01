/* Fo
 * fo-wsc.c: 'width-style-color' datatype
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-wsc.c,v 1.2 2005/03/20 12:17:13 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-wsc.h"
#include "fo-length.h"
#include "fo-color.h"

enum {
  PROP_0,
  PROP_WIDTH,
  PROP_STYLE,
  PROP_COLOR
};

struct _FoWsc
{
  FoDatatype parent_instance;

  FoDatatype *width;
  FoDatatype *style;
  FoDatatype *color;
};

struct _FoWscClass
{
  FoDatatypeClass parent_class;
};

static void fo_wsc_class_init   (FoWscClass    *klass);
static void fo_wsc_set_property (GObject       *object,
				 guint          prop_id,
				 const GValue  *value,
				 GParamSpec    *pspec);
static void fo_wsc_get_property (GObject       *object,
				 guint          prop_id,
				 GValue        *value,
				 GParamSpec    *pspec);
static void fo_wsc_finalize     (GObject       *object);

gchar*      fo_wsc_sprintf      (FoObject      *object);
FoDatatype* fo_wsc_copy         (FoDatatype    *datatype);

static void fo_wsc_set_width    (FoDatatype    *datatype,
				 FoDatatype    *new_width);
static void fo_wsc_set_style    (FoDatatype    *datatype,
				 FoDatatype    *new_style);
static void fo_wsc_set_color    (FoDatatype    *datatype,
				 FoDatatype    *new_color);

static gpointer parent_class;

/**
 * fo_wsc_get_type:
 * @void: 
 * 
 * Register the #FoWsc object type.
 * 
 * Return value: GType value of the #FoWsc object type.
 **/
GType
fo_wsc_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoWscClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_wsc_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoWsc),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoWsc",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_wsc_class_init:
 * @klass: FoWscClass object to initialise
 * 
 * Implements GClassInitFunc for FoWscClass
 **/
void
fo_wsc_class_init (FoWscClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_wsc_finalize;

  object_class->set_property = fo_wsc_set_property;
  object_class->get_property = fo_wsc_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_wsc_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_wsc_copy;

  g_object_class_install_property (object_class,
                                   PROP_WIDTH,
                                   g_param_spec_object ("width",
							_("Width"),
							_("Wsc width value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_STYLE,
                                   g_param_spec_object ("style",
							_("Style"),
							_("Wsc style value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

  g_object_class_install_property (object_class,
                                   PROP_COLOR,
                                   g_param_spec_object ("color",
							_("Color"),
							_("Wsc color value"),
							FO_TYPE_DATATYPE,
							G_PARAM_READWRITE |
							G_PARAM_CONSTRUCT_ONLY));

}

/**
 * fo_wsc_finalize:
 * @object: FoWsc object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoWsc
 **/
void
fo_wsc_finalize (GObject *object)
{
  FoWsc *wsc;

  wsc = FO_WSC (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_wsc_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoWsc
 **/
void
fo_wsc_set_property (GObject         *object,
		     guint            prop_id,
		     const GValue    *value,
		     GParamSpec      *pspec)
{
  FoDatatype *wsc;

  wsc = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_WIDTH:
      fo_wsc_set_width (wsc, g_value_get_object (value));
      break;
    case PROP_STYLE:
      fo_wsc_set_style (wsc, g_value_get_object (value));
      break;
    case PROP_COLOR:
      fo_wsc_set_color (wsc, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_wsc_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoWsc
 **/
void
fo_wsc_get_property (GObject         *object,
		     guint            prop_id,
		     GValue          *value,
		     GParamSpec      *pspec)
{
  FoDatatype *datatype;

  datatype = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_WIDTH:
      g_value_set_object (value, fo_wsc_get_width (datatype));
      break;
    case PROP_STYLE:
      g_value_set_object (value, fo_wsc_get_style (datatype));
      break;
    case PROP_COLOR:
      g_value_set_object (value, fo_wsc_get_color (datatype));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_wsc_new:
 * 
 * Creates a new #FoWsc initialized to default value.
 * 
 * Return value: the new #FoWsc
 **/
FoDatatype *
fo_wsc_new (void)
{
  FoDatatype *wsc;

  wsc = FO_DATATYPE (g_object_new (fo_wsc_get_type (),
				   "width",
				   NULL,
				   "style",
				   NULL,
				   "color",
				   NULL,
				   NULL));
  
  return wsc;
}

/**
 * fo_wsc_new_from_values:
 * @width: #FoDatatype to use as width value
 * @style: #FoDatatype to use as style value
 * @color: #FoDatatype to use as color value
 * 
 * Creates a new #FoWsc with width, style, and color components set to
 * provided values.
 * 
 * Return value: New #FoWsc
 **/
FoDatatype*
fo_wsc_new_from_values (FoDatatype *width,
			FoDatatype *style,
			FoDatatype *color)
{
  FoDatatype *wsc;

  g_return_val_if_fail ((width == NULL) || FO_IS_DATATYPE (width), NULL);
  g_return_val_if_fail ((style == NULL) || FO_IS_DATATYPE (style), NULL);
  g_return_val_if_fail ((color == NULL) || FO_IS_DATATYPE (color), NULL);


  wsc = fo_wsc_new ();

  fo_wsc_set_width (wsc, width);
  fo_wsc_set_style (wsc, style);
  fo_wsc_set_color (wsc, color);

  return wsc;
}

/**
 * fo_wsc_get_width:
 * @datatype: #FoWsc
 * 
 * Gets the width component value of @datatype.
 * 
 * Return value: The width value of @datatype.
 **/
FoDatatype *
fo_wsc_get_width (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_WSC (datatype), NULL);

  return FO_WSC (datatype)->width;
}

/**
 * fo_wsc_set_width:
 * @datatype:  #FoWsc
 * @new_width: New width value
 * 
 * Sets the width component of @datatype
 **/
void
fo_wsc_set_width (FoDatatype *datatype,
		  FoDatatype *new_width)
{
  FoWsc *wsc = (FoWsc *) datatype;

  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_WSC (datatype));
  g_return_if_fail ((new_width == NULL) || FO_IS_DATATYPE (new_width));

  if (new_width != NULL)
    g_object_ref (G_OBJECT (new_width));
  if (wsc->width != NULL)
    g_object_unref (G_OBJECT (wsc->width));
  wsc->width = new_width;
  /*g_object_notify(G_OBJECT(datatype), "width");*/
}

/**
 * fo_wsc_get_style:
 * @datatype: #FoWsc
 * 
 * Gets the style component value of @datatype
 * 
 * Return value: The style value of @datatype
 **/
FoDatatype *
fo_wsc_get_style (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_WSC (datatype), NULL);

  return FO_WSC (datatype)->style;
}

/**
 * fo_wsc_set_style:
 * @datatype:  #FoWsc
 * @new_style: New style value
 * 
 * Sets the style component of @datatype
 **/
void
fo_wsc_set_style (FoDatatype *datatype,
		  FoDatatype *new_style)
{
  FoWsc *wsc = (FoWsc *) datatype;

  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_WSC (datatype));
  g_return_if_fail ((new_style == NULL) || FO_IS_DATATYPE (new_style));

  if (new_style != NULL)
    g_object_ref (G_OBJECT (new_style));
  if (wsc->style != NULL)
    g_object_unref (G_OBJECT (wsc->style));
  wsc->style = new_style;
  /*g_object_notify(G_OBJECT(datatype), "style");*/
}

/**
 * fo_wsc_get_color:
 * @datatype: #FoWsc
 * 
 * Gets the color component value of @datatype
 * 
 * Return value: The color value of @datatype
 **/
FoDatatype *
fo_wsc_get_color (FoDatatype *datatype)
{
  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_WSC (datatype), NULL);

  return FO_WSC (datatype)->color;
}

/**
 * fo_wsc_set_color:
 * @datatype:  #FoWsc
 * @new_color: New color value
 * 
 * Sets the color component of @datatype
 **/
void
fo_wsc_set_color (FoDatatype *datatype,
		  FoDatatype *new_color)
{
  FoWsc *wsc = (FoWsc *) datatype;

  g_return_if_fail (datatype != NULL);
  g_return_if_fail (FO_IS_WSC (datatype));
  g_return_if_fail ((new_color == NULL) || FO_IS_DATATYPE (new_color));

  if (new_color != NULL)
    g_object_ref (G_OBJECT (new_color));
  if (wsc->color != NULL)
    g_object_unref (G_OBJECT (wsc->color));
  wsc->color = new_color;
  /*g_object_notify(G_OBJECT(datatype), "color");*/
}

/**
 * fo_wsc_sprintf:
 * @object: #FoWsc whose value is to be printed
 * 
 * Create and return a string representation of the value of @object,
 * which must be an #FoWsc.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of value of @object
 **/
gchar*
fo_wsc_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_WSC (object), NULL);

  return (g_strdup_printf("width: %s; style: %s; color: %s",
			  fo_object_sprintf (FO_WSC (object)->width),
			  fo_object_sprintf (FO_WSC (object)->style),
			  fo_object_sprintf (FO_WSC (object)->color)));
}

/**
 * fo_wsc_copy:
 * @datatype: Source #FoWsc.
 * 
 * Creates a copy of @datatype.
 * 
 * Return value: Copy of @datatype.
 **/
FoDatatype*
fo_wsc_copy (FoDatatype *datatype)
{
  FoDatatype *wsc;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_WSC (datatype), NULL);

  wsc = fo_wsc_new ();
  fo_wsc_set_width (wsc,
		    FO_WSC(datatype)->width);
  fo_wsc_set_style (wsc,
		    FO_WSC(datatype)->style);
  fo_wsc_set_color (wsc,
		    FO_WSC(datatype)->color);

  return (wsc);
}
