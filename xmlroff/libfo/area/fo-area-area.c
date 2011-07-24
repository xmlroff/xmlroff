
/* Fo
 * fo-area-area.c: Area area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area.h"
#include "fo-area-area.h"
#include "fo-area-area-private.h"
#include "fo/fo-block-fo.h"
#include "property/fo-property-keep-with-previous.h"
#include "property/fo-property-keep-with-next.h"

enum {
  PROP_0,
  PROP_X,
  PROP_Y,
  PROP_WIDTH,
  PROP_HEIGHT,
  PROP_BORDER_BEFORE,
  PROP_BORDER_AFTER,
  PROP_BORDER_START,
  PROP_BORDER_END,
  PROP_PADDING_BEFORE,
  PROP_PADDING_AFTER,
  PROP_PADDING_START,
  PROP_PADDING_END
};

static void _base_class_init (FoAreaAreaClass *klass);
static void fo_area_area_class_init  (FoAreaAreaClass *klass);
static void fo_area_area_set_property (GObject         *object,
				       guint            prop_id,
				       const GValue    *value,
				       GParamSpec      *pspec);
static void fo_area_area_get_property   (GObject         *object,
					 guint            prop_id,
					 GValue          *value,
					 GParamSpec      *pspec);
static void fo_area_area_finalize    (GObject           *object);

static void fo_area_area_debug_dump_properties (FoArea *area,
						gint depth);
static FoArea* _split_before_height (FoArea *area,
				     gdouble max_height);
static gboolean _split_before_height_check (FoArea *area,
					    gdouble max_height);
static void fo_area_area_update_after_clone (FoArea *clone,
					     FoArea *original);
static void fo_area_area_resolve_child_ipdim (FoArea *fo_area);

static gpointer parent_class;

GType
fo_area_area_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaAreaClass),
        (GBaseInitFunc) _base_class_init,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_area_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaArea),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA,
                                            "FoAreaArea",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
_base_class_init (FoAreaAreaClass *klass)
{
  FO_AREA_CLASS (klass)->split_before_height = _split_before_height;
  FO_AREA_CLASS (klass)->split_before_height_check =
    _split_before_height_check;
}

static void
fo_area_area_class_init (FoAreaAreaClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoAreaClass *fo_area_class = FO_AREA_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_area_finalize;

  object_class->set_property = fo_area_area_set_property;
  object_class->get_property = fo_area_area_get_property;

  fo_area_class->debug_dump_properties = fo_area_area_debug_dump_properties;
  fo_area_class->update_after_clone = fo_area_area_update_after_clone;

  g_object_class_install_property
    (object_class,
     PROP_X,
     g_param_spec_float ("x",
		       _("x position"),
		       _("x position property"),
			 0,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_Y,
     g_param_spec_float ("y",
		       _("y position"),
		       _("y position property"),
			 0,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_WIDTH,
     g_param_spec_float ("width",
		       _("Area width"),
		       _("Area width property"),
			 0,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_HEIGHT,
     g_param_spec_float ("height",
		       _("Area height"),
		       _("Area height property"),
			 0,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
}

static void
fo_area_area_finalize (GObject *object)
{
  FoAreaArea *fo_area_area;

  fo_area_area = FO_AREA_AREA (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


static void
fo_area_area_set_property (GObject         *object,
			   guint            prop_id,
			   const GValue    *value,
			   GParamSpec      *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_X:
      fo_area_area_set_x (fo_area, g_value_get_float (value));
      break;
    case PROP_Y:
      fo_area_area_set_y (fo_area, g_value_get_float (value));
      break;
    case PROP_WIDTH:
      fo_area_area_set_width (fo_area, g_value_get_float (value));
      break;
    case PROP_HEIGHT:
      fo_area_area_set_height (fo_area, g_value_get_float (value));
      break;
    case PROP_BORDER_BEFORE:
      fo_area_area_set_border_before (fo_area, g_value_get_float (value));
      break;
    case PROP_BORDER_AFTER:
      fo_area_area_set_border_after (fo_area, g_value_get_float (value));
      break;
    case PROP_BORDER_START:
      fo_area_area_set_border_start (fo_area, g_value_get_float (value));
      break;
    case PROP_BORDER_END:
      fo_area_area_set_border_end (fo_area, g_value_get_float (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_area_area_set_padding_before (fo_area, g_value_get_float (value));
      break;
    case PROP_PADDING_AFTER:
      fo_area_area_set_padding_after (fo_area, g_value_get_float (value));
      break;
    case PROP_PADDING_START:
      fo_area_area_set_padding_start (fo_area, g_value_get_float (value));
      break;
    case PROP_PADDING_END:
      fo_area_area_set_padding_end (fo_area, g_value_get_float (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
fo_area_area_get_property (GObject         *object,
			   guint            prop_id,
			   GValue          *value,
			   GParamSpec      *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_X:
      g_value_set_float (value, fo_area_area_get_x (fo_area));
      break;
    case PROP_Y:
      g_value_set_float (value, fo_area_area_get_y (fo_area));
      break;
    case PROP_WIDTH:
      g_value_set_float (value, fo_area_area_get_width (fo_area));
      break;
    case PROP_HEIGHT:
      g_value_set_float (value, fo_area_area_get_height (fo_area));
      break;
    case PROP_BORDER_BEFORE:
      g_value_set_float (value, fo_area_area_get_border_before (fo_area));
      break;
    case PROP_BORDER_AFTER:
      g_value_set_float (value, fo_area_area_get_border_after (fo_area));
      break;
    case PROP_BORDER_START:
      g_value_set_float (value, fo_area_area_get_border_start (fo_area));
      break;
    case PROP_BORDER_END:
      g_value_set_float (value, fo_area_area_get_border_end (fo_area));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_float (value, fo_area_area_get_padding_before (fo_area));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_float (value, fo_area_area_get_padding_before (fo_area));
      break;
    case PROP_PADDING_START:
      g_value_set_float (value, fo_area_area_get_padding_start (fo_area));
      break;
    case PROP_PADDING_END:
      g_value_set_float (value, fo_area_area_get_padding_end (fo_area));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_area_area_new:
 * 
 * Creates a new #FoAreaArea initialized to default value.
 * 
 * Return value: the new #FoAreaArea
 **/
FoArea*
fo_area_area_new (void)
{
  return FO_AREA (g_object_new (fo_area_area_get_type (), NULL));
}


void
fo_area_area_resolve_child_ipdim (FoArea *fo_area)
{
  FoAreaArea *fo_area_area;

  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area));

  fo_area_area = FO_AREA_AREA (fo_area);

  fo_area_set_child_available_ipdim (fo_area,
				     MAX (fo_area_area->width -
					  fo_area_area->border_start -
					  fo_area_area->padding_start -
					  fo_area_area->padding_end -
					  fo_area_area->border_end,
					  0));
}

/**
 * fo_area_area_set_x:
 * @fo_area: The #FoAreaArea object
 * @new_x: The new "x" property value
 * 
 * Sets the "x" property of @fo_area to @new_x
**/
void
fo_area_area_set_x (FoArea *fo_area,
		    gdouble new_x)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->x = new_x;
  /*g_object_notify (G_OBJECT (fo_area_area), "x");*/
}

/**
 * fo_area_area_get_x:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "x" property of @fo_area
 *
 * Return value: The "x" property value
**/
gdouble
fo_area_area_get_x (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->x;
}

/**
 * fo_area_area_set_y:
 * @fo_area: The #FoAreaArea object
 * @new_y: The new "y" property value
 * 
 * Sets the "y" property of @fo_area to @new_y
**/
void
fo_area_area_set_y (FoArea *fo_area,
		         gdouble new_y)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->y = new_y;
  /*g_object_notify (G_OBJECT (fo_area_area), "y");*/
}

/**
 * fo_area_area_get_y:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "y" property of @fo_area
 *
 * Return value: The "y" property value
**/
gdouble
fo_area_area_get_y (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->y;
}

/**
 * fo_area_area_set_width:
 * @fo_area: The #FoAreaArea object
 * @new_width: The new "width" property value
 * 
 * Sets the "width" property of @fo_area to @new_width
**/
void
fo_area_area_set_width (FoArea *fo_area,
		         gdouble new_width)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->width = new_width;
  fo_area_area_resolve_child_ipdim (fo_area);
  /*g_object_notify (G_OBJECT (fo_area_area), "width");*/
}

/**
 * fo_area_area_get_width:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "width" property of @fo_area
 *
 * Return value: The "width" property value
**/
gdouble
fo_area_area_get_width (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->width;
}

/**
 * fo_area_area_set_height:
 * @fo_area: The #FoAreaArea object
 * @new_height: The new "height" property value
 * 
 * Sets the "height" property of @fo_area to @new_height
**/
void
fo_area_area_set_height (FoArea *fo_area,
		         gdouble new_height)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->height = new_height;
  /*g_object_notify (G_OBJECT (fo_area_area), "height");*/
}

/**
 * fo_area_area_get_height:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "height" property of @fo_area
 *
 * Return value: The "height" property value
**/
gdouble
fo_area_area_get_height (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->height;
}

/**
 * fo_area_area_set_border_before:
 * @fo_area: The #FoAreaArea object
 * @new_border_before: The new "border-before" property value
 * 
 * Sets the "border-before" property of @fo_area to @new_border_before
**/
void
fo_area_area_set_border_before (FoArea *fo_area,
	       gdouble new_border_before)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->border_before = new_border_before;
  /*g_object_notify (G_OBJECT (fo_area_area), "border-before");*/
}

/**
 * fo_area_area_get_border_before:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "border-before" property of @fo_area
 *
 * Return value: The "border_before" property value
**/
gdouble
fo_area_area_get_border_before (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->border_before;
}

/**
 * fo_area_area_set_border_after:
 * @fo_area: The #FoAreaArea object
 * @new_border_after: The new "border-after" property value
 * 
 * Sets the "border-after" property of @fo_area to @new_border_after
**/
void
fo_area_area_set_border_after (FoArea *fo_area,
	       gdouble new_border_after)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->border_after = new_border_after;
  /*g_object_notify (G_OBJECT (fo_area_area), "border-after");*/
}

/**
 * fo_area_area_get_border_after:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "border-after" property of @fo_area
 *
 * Return value: The "border_after" property value
**/
gdouble
fo_area_area_get_border_after (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->border_after;
}

/**
 * fo_area_area_set_border_start:
 * @fo_area: The #FoAreaArea object
 * @new_border_start: The new "border-start" property value
 * 
 * Sets the "border-start" property of @fo_area to @new_border_start
**/
void
fo_area_area_set_border_start (FoArea *fo_area,
	       gdouble new_border_start)
{
  FoAreaArea *fo_area_area;

  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area));

  fo_area_area = FO_AREA_AREA (fo_area);

  fo_area_area->border_start = new_border_start;
  fo_area_area_resolve_child_ipdim (fo_area);
  /*g_object_notify (G_OBJECT (fo_area_area), "border-start");*/
}

/**
 * fo_area_area_get_border_start:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "border-start" property of @fo_area
 *
 * Return value: The "border_start" property value
**/
gdouble
fo_area_area_get_border_start (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->border_start;
}

/**
 * fo_area_area_set_border_end:
 * @fo_area: The #FoAreaArea object
 * @new_border_end: The new "border-end" property value
 * 
 * Sets the "border-end" property of @fo_area to @new_border_end
**/
void
fo_area_area_set_border_end (FoArea *fo_area,
	       gdouble new_border_end)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->border_end = new_border_end;
  fo_area_area_resolve_child_ipdim (fo_area);
  /*g_object_notify (G_OBJECT (fo_area_area), "border-end");*/
}

/**
 * fo_area_area_get_border_end:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "border-end" property of @fo_area
 *
 * Return value: The "border_end" property value
**/
gdouble
fo_area_area_get_border_end (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->border_end;
}

/**
 * fo_area_area_set_padding_before:
 * @fo_area: The #FoAreaArea object
 * @new_padding_before: The new "padding-before" property value
 * 
 * Sets the "padding-before" property of @fo_area to @new_padding_before
**/
void
fo_area_area_set_padding_before (FoArea *fo_area,
	       gdouble new_padding_before)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_area_area), "padding-before");*/
}

/**
 * fo_area_area_get_padding_before:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "padding-before" property of @fo_area
 *
 * Return value: The "padding_before" property value
**/
gdouble
fo_area_area_get_padding_before (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->padding_before;
}

/**
 * fo_area_area_set_padding_after:
 * @fo_area: The #FoAreaArea object
 * @new_padding_after: The new "padding-after" property value
 * 
 * Sets the "padding-after" property of @fo_area to @new_padding_after
**/
void
fo_area_area_set_padding_after (FoArea *fo_area,
	       gdouble new_padding_after)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_area_area), "padding-after");*/
}

/**
 * fo_area_area_get_padding_after:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "padding-after" property of @fo_area
 *
 * Return value: The "padding_after" property value
**/
gdouble
fo_area_area_get_padding_after (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->padding_after;
}

/**
 * fo_area_area_set_padding_start:
 * @fo_area: The #FoAreaArea object
 * @new_padding_start: The new "padding-start" property value
 * 
 * Sets the "padding-start" property of @fo_area to @new_padding_start
**/
void
fo_area_area_set_padding_start (FoArea *fo_area,
	       gdouble new_padding_start)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->padding_start = new_padding_start;
  fo_area_area_resolve_child_ipdim (fo_area);
  /*g_object_notify (G_OBJECT (fo_area_area), "padding-start");*/
}

/**
 * fo_area_area_get_padding_start:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "padding-start" property of @fo_area
 *
 * Return value: The "padding_start" property value
**/
gdouble
fo_area_area_get_padding_start (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->padding_start;
}

/**
 * fo_area_area_set_padding_end:
 * @fo_area: The #FoAreaArea object
 * @new_padding_end: The new "padding-end" property value
 * 
 * Sets the "padding-end" property of @fo_area to @new_padding_end
**/
void
fo_area_area_set_padding_end (FoArea *fo_area,
	       gdouble new_padding_end)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->padding_end = new_padding_end;
  fo_area_area_resolve_child_ipdim (fo_area);
  /*g_object_notify (G_OBJECT (fo_area_area), "padding-end");*/
}

/**
 * fo_area_area_get_padding_end:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "padding-end" property of @fo_area
 *
 * Return value: The "padding_end" property value
**/
gdouble
fo_area_area_get_padding_end (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->padding_end;
}

/**
 * fo_area_area_set_start_indent:
 * @fo_area: The #FoAreaArea object
 * @new_start_indent: The new "start-indent" property value
 * 
 * Sets the "start-indent" property of @fo_area to @new_start_indent
**/
void
fo_area_area_set_start_indent (FoArea *fo_area,
			       gdouble new_start_indent)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->start_indent = new_start_indent;
  /*g_object_notify (G_OBJECT (fo_area_area), "start-indent");*/
}

/**
 * fo_area_area_get_start_indent:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "start-indent" property of @fo_area
 *
 * Return value: The "start_indent" property value
**/
gdouble
fo_area_area_get_start_indent (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->start_indent;
}

/**
 * fo_area_area_set_end_indent:
 * @fo_area: The #FoAreaArea object
 * @new_end_indent: The new "end-indent" property value
 * 
 * Sets the "end-indent" property of @fo_area to @new_end_indent
**/
void
fo_area_area_set_end_indent (FoArea *fo_area,
			     gdouble new_end_indent)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->end_indent = new_end_indent;
  /*g_object_notify (G_OBJECT (fo_area_area), "end-indent");*/
}

/**
 * fo_area_area_get_end_indent:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "end-indent" property of @fo_area
 *
 * Return value: The "end_indent" property value
**/
gdouble
fo_area_area_get_end_indent (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->end_indent;
}

/**
 * fo_area_area_set_space_before:
 * @fo_area: The #FoAreaArea object
 * @new_space_before: The new "space-before" property value
 * 
 * Sets the "space-before" property of @fo_area to @new_space_before
**/
void
fo_area_area_set_space_before (FoArea *fo_area,
			       gdouble new_space_before)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->space_before = new_space_before;
  /*g_object_notify (G_OBJECT (fo_area_area), "space-before");*/
}

/**
 * fo_area_area_get_space_before:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "space-before" property of @fo_area
 *
 * Return value: The "space_before" property value
**/
gdouble
fo_area_area_get_space_before (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->space_before;
}

/**
 * fo_area_area_set_space_after:
 * @fo_area: The #FoAreaArea object
 * @new_space_after: The new "space-after" property value
 * 
 * Sets the "space-after" property of @fo_area to @new_space_after
**/
void
fo_area_area_set_space_after (FoArea *fo_area,
			     gdouble new_space_after)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_if_fail (fo_area_area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (fo_area_area));

  fo_area_area->space_after = new_space_after;
  /*g_object_notify (G_OBJECT (fo_area_area), "space-after");*/
}

/**
 * fo_area_area_get_space_after:
 * @fo_area: The #FoAreaArea object
 *
 * Gets the "space-after" property of @fo_area
 *
 * Return value: The "space_after" property value
**/
gdouble
fo_area_area_get_space_after (FoArea *fo_area)
{
  FoAreaArea *fo_area_area = (FoAreaArea *) fo_area;

  g_return_val_if_fail (fo_area_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_area), 0);

  return fo_area_area->space_after;
}

void
fo_area_area_debug_dump_properties (FoArea *area, gint depth)
{
  FoAreaArea *area_area;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (area));

  area_area = FO_AREA_AREA (area);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sx:              %g pt", indent, area_area->x);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sy:              %g pt", indent, area_area->y);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%swidth:          %g pt", indent, area_area->width);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sheight:         %g pt", indent, area_area->height);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sborder-before:  %g pt", indent, area_area->border_before);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sborder-after:   %g pt", indent, area_area->border_after);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sborder-start:   %g pt", indent, area_area->border_start);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sborder-end:     %g pt", indent, area_area->border_end);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spadding-before: %g pt", indent, area_area->padding_before);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spadding-after:  %g pt", indent, area_area->padding_after);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spadding-start:  %g pt", indent, area_area->padding_start);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spadding-end:    %g pt", indent, area_area->padding_end);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sstart-indent:   %g pt", indent, area_area->start_indent);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%send-indent:     %g pt", indent, area_area->end_indent);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sspace-before:   %g pt", indent, area_area->space_before);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sspace-after:    %g pt", indent, area_area->space_after);

  g_free (indent);

  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

/**
 * fo_area_area_update_after_clone:
 * @clone:    New object cloned from @original
 * @original: Original area object
 * 
 * Update the FoAreaArea-specific instance variables of @clone to
 * match those of @original
 **/
void
fo_area_area_update_after_clone (FoArea *clone,
				 FoArea *original)
{
  FoAreaArea *original_area_area, *clone_area_area;

  g_return_if_fail (clone != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (clone));
  g_return_if_fail (original != NULL);
  g_return_if_fail (FO_IS_AREA_AREA (original));

  FO_AREA_CLASS (parent_class)->update_after_clone (clone, original);

  original_area_area = FO_AREA_AREA (original);
  clone_area_area = FO_AREA_AREA (clone);

  fo_area_area_set_x (clone, original_area_area->x);
  fo_area_area_set_y (clone, original_area_area->y);
  fo_area_area_set_height (clone, original_area_area->height);
  fo_area_area_set_width (clone, original_area_area->width);

  fo_area_area_set_border_before (clone, original_area_area->border_before);
  fo_area_area_set_border_after (clone, original_area_area->border_after);
  fo_area_area_set_border_start (clone, original_area_area->border_start);
  fo_area_area_set_border_end (clone, original_area_area->border_end);

  fo_area_area_set_padding_before (clone, original_area_area->padding_before);
  fo_area_area_set_padding_after (clone, original_area_area->padding_after);
  fo_area_area_set_padding_start (clone, original_area_area->padding_start);
  fo_area_area_set_padding_end (clone, original_area_area->padding_end);

  fo_area_area_set_start_indent (clone, original_area_area->start_indent);
  fo_area_area_set_end_indent (clone, original_area_area->end_indent);

  fo_area_area_set_space_before (clone, original_area_area->space_before);
  fo_area_area_set_space_after (clone, original_area_area->space_after);
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
static FoArea *
_split_before_height (FoArea *area,
		      gdouble  max_height)
{
  gdouble total_child_height = 0;

  g_return_val_if_fail (FO_IS_AREA_AREA (area), NULL);
  g_return_val_if_fail (max_height > 0, NULL);

#if defined(LIBFO_DEBUG) && 0
  g_message ("area_split_before_height:: area: %s; generated by: %s; max_height: %f",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (area->generated_by),
	     max_height);
#endif
#if defined(LIBFO_DEBUG) && 0
  g_message ("area_split_before_height:: area: %s; parent: %s",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (fo_area_parent (area)));
#endif

  FoAreaArea *area_area = (FoAreaArea *) area;
  /* if the current area is less than max height, then no new area */
  if (fo_area_area_get_height (area) < max_height)
    return NULL;

  FoArea *use_child_area =
     fo_area_first_child (area);

  while (use_child_area != NULL)
    {
      /* area->y <= 0, so invert so calculations look sensible */
      gdouble minus_child_y = - fo_area_area_get_y (use_child_area);
      gdouble child_height = fo_area_area_get_height (use_child_area);


      if (minus_child_y >= max_height)
	{
	  /* max_height falls before use_child_area,
	     i.e. in space between areas */

#if defined(LIBFO_DEBUG) && 1
	  if (FO_IS_BLOCK_FO (fo_area_get_generated_by (use_child_area)))
	    {
	      g_message ("area_area_split_before_height:: area: %s; block fo: %s",
			 fo_object_debug_sprintf (use_child_area),
			 fo_object_debug_sprintf (fo_area_get_generated_by (use_child_area)));
	    }
#endif

	  if (use_child_area == fo_area_first_child (area))
	    {
	      return NULL;
	    }
	  else
	    {
	      FoFo *child_fo =
		fo_area_get_generated_by (use_child_area);
	      FoDatatype *child_kwpwp_datatype =
		fo_keep_get_within_page (fo_property_get_value (fo_block_fo_get_keep_with_previous (child_fo)));
	      FoDatatype *child_kwpwc_datatype =
		fo_keep_get_within_column (fo_property_get_value (fo_block_fo_get_keep_with_previous (child_fo)));

	      FoFo *prev_child_fo =
		fo_area_get_generated_by (fo_area_prev_sibling (use_child_area));
	      FoDatatype *prev_child_kwnwp_datatype =
		fo_keep_get_within_page (fo_property_get_value (fo_block_fo_get_keep_with_next (prev_child_fo)));
	      FoDatatype *prev_child_kwnwc_datatype =
		fo_keep_get_within_column (fo_property_get_value (fo_block_fo_get_keep_with_next (prev_child_fo)));

	      /* FIXME: Need to handle integer keeps */
	      if ((FO_IS_ENUM (prev_child_kwnwp_datatype) &&
		   fo_enum_get_value (prev_child_kwnwp_datatype) == FO_ENUM_ENUM_AUTO) &&
		  (FO_IS_ENUM (prev_child_kwnwc_datatype) &&
		   fo_enum_get_value (prev_child_kwnwc_datatype) == FO_ENUM_ENUM_AUTO)  &&
		  (FO_IS_ENUM (child_kwpwp_datatype) &&
		   fo_enum_get_value (child_kwpwp_datatype) == FO_ENUM_ENUM_AUTO) &&
		  (FO_IS_ENUM (child_kwpwc_datatype) &&
		   fo_enum_get_value (child_kwpwc_datatype) == FO_ENUM_ENUM_AUTO))
		{
		  /* If got to here, all relevant keeps are 'auto' */
		  FoArea *clone = fo_area_clone (area);

		  fo_area_unlink_with_next_siblings (use_child_area);
		  fo_area_insert_with_next_siblings (clone, 0, use_child_area);

		  return clone;
		}
	      else
		{
		  gdouble minus_prev_y =
		    fo_area_area_get_y (fo_area_prev_sibling (use_child_area));
		  gdouble prev_height =
		    fo_area_area_get_height (fo_area_prev_sibling (use_child_area));
		  /* If can't split between use_child_area and previous, maybe
		     can split at lower height */
		  return _split_before_height (area,
					       minus_prev_y +
					       prev_height);
		}
	    }
	}
      else if (minus_child_y + child_height >= max_height)
	{
	  FoArea *split_child;

#if defined(LIBFO_DEBUG) && 0
  g_message ("area_split_before_height:: splitting:: area: %s; generated by: %s; y: %f; height: %f",
	     fo_object_debug_sprintf (use_child_area),
	     fo_object_debug_sprintf (use_child_area->generated_by),
	     ((FoAreaArea *) use_child_area)->y,
	     ((FoAreaArea *) use_child_area)->height);
#endif

	  split_child = fo_area_split_before_height (use_child_area,
						     max_height -
						     minus_child_y);
	  if (split_child == NULL)
	    {
#if defined(LIBFO_DEBUG) && 0
		  g_message ("area_split_before_height:: child didn't split:: child: %s; generated by: %s; area: %s; generated by: %s",
			     fo_object_debug_sprintf (use_child_area),
			     fo_object_debug_sprintf (use_child_area->generated_by),
			     fo_object_debug_sprintf (area),
			     fo_object_debug_sprintf (area->generated_by));
#endif
	      if (use_child_area == fo_area_first_child (area))
		{
#if defined(LIBFO_DEBUG) && 0
		  g_message ("area_split_before_height:: non-split child is first child:: child: %s; generated by: %s; area: %s; generated by: %s",
			     fo_object_debug_sprintf (use_child_area),
			     fo_object_debug_sprintf (use_child_area->generated_by),
			     fo_object_debug_sprintf (area),
			     fo_object_debug_sprintf (area->generated_by));
#endif
		  return NULL;
		}
	      else
		{
		  FoArea *clone = fo_area_clone (area);

#if defined(LIBFO_DEBUG) && 0
		  g_message ("area_split_before_height:: split area but child didn't split:: child: %s; generated by: %s; area: %s; generated by: %s; clone: %s; generated by: %s",
			     fo_object_debug_sprintf (use_child_area),
			     fo_object_debug_sprintf (use_child_area->generated_by),
			     fo_object_debug_sprintf (area),
			     fo_object_debug_sprintf (area->generated_by),
			     fo_object_debug_sprintf (clone),
			     fo_object_debug_sprintf (clone->generated_by));
#endif

		  clone->is_first = FALSE;
		  area->is_last = FALSE;
		  
		  /* Do not include area_area->border_after in height since
		     area_area is not last */
		  area_area->border_after = 0;
		  area_area->height =
		    total_child_height +
		    area_area->border_before +
		    area_area->padding_before +
		    area_area->padding_after;

		  /* Do not include clone->border_before in height since
		     clone is not first */
		  ((FoAreaArea *)clone)->border_before = 0;
		  ((FoAreaArea *) clone)->height =
		    ((FoAreaArea *) use_child_area)->height +
		    ((FoAreaArea *) clone)->padding_before +
		    ((FoAreaArea *) clone)->padding_after +
		    ((FoAreaArea *) clone)->border_after;

		  fo_area_unlink_with_next_siblings (use_child_area);
		  fo_area_insert_with_next_siblings (clone, 0, use_child_area);

		  return clone;
		}
	    }
	  else
	    {
	      FoArea *clone = fo_area_clone (area);

#if defined(LIBFO_DEBUG) && 0
		  g_message ("area_split_before_height:: child split:: child: %s; generated by: %s; split child: %s; generated by: %s; area: %s; generated by: %s; clone: %s; generated by: %s",
			     fo_object_debug_sprintf (use_child_area),
			     fo_object_debug_sprintf (use_child_area->generated_by),
			     fo_object_debug_sprintf (split_child),
			     fo_object_debug_sprintf (split_child->generated_by),
			     fo_object_debug_sprintf (area),
			     fo_object_debug_sprintf (area->generated_by),
			     fo_object_debug_sprintf (clone),
			     fo_object_debug_sprintf (clone->generated_by));
#endif
	      clone->is_first = FALSE;
	      area->is_last = FALSE;

	      /* Do not include area_area->border_after in height since
		 area_area is not last */
	      area_area->border_after = 0;
	      area_area->height =
		total_child_height +
		((FoAreaArea *) use_child_area)->height +
		area_area->border_before +
		area_area->padding_before +
		area_area->padding_after;

	      /* Do not include clone->border_before in height since
		 clone is not first */
	      /* FIXME: should handle length-conditional here */
	      ((FoAreaArea *)clone)->border_before = 0;
	      ((FoAreaArea *) clone)->height =
		((FoAreaArea *) split_child)->height +
		((FoAreaArea *) clone)->padding_before +
		((FoAreaArea *) clone)->padding_after +
		((FoAreaArea *) clone)->border_after;

	      fo_area_unlink_with_next_siblings (split_child);
	      fo_area_insert_with_next_siblings (clone, 0, split_child);

	      ((FoAreaArea *) split_child)->y = 0;
	      fo_area_set_next_y (clone, ((FoAreaArea *) split_child)->height);
	      fo_area_set_available_height (clone, 0);
	      /* FIXME: clone should work out its own child_available_bpdim */
	      fo_area_set_child_available_bpdim (clone, 0);

	      return clone;
	    }
	}
      else
	{
	  total_child_height = minus_child_y + child_height;
	}

      use_child_area = fo_area_next_sibling (use_child_area);
    }

  return NULL;
}

/* return %TRUE if the area will split within the height */
static gboolean
_split_before_height_check (FoArea *area,
			    gdouble  max_height)
{
  FoAreaArea *area_area;
  FoArea *use_child_area;
  gdouble total_child_height = 0;

  g_return_val_if_fail (FO_IS_AREA_AREA (area), FALSE);
  g_return_val_if_fail (max_height > 0, FALSE);

#if defined(LIBFO_DEBUG) && 0
  g_message ("area_split_before_height_check:: area: %s; generated by: %s; max_height: %f",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (area->generated_by),
	     max_height);
#endif
#if defined(LIBFO_DEBUG) && 0
  g_message ("area_split_before_height_check:: area: %s; parent: %s",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (fo_area_parent (area)));
#endif

  area_area = (FoAreaArea *) area;
  /* if the current area is less than max height, then no new area */
  if (area_area->height < max_height)
    {
      return FALSE;
    }

  use_child_area = fo_area_first_child (area);

  while (use_child_area)
    {
      /* area->y <= 0, so invert so calculations look sensible */
      gdouble minus_child_y = -((FoAreaArea *) use_child_area)->y;
      gdouble child_height = ((FoAreaArea *) use_child_area)->height;


      if (minus_child_y + child_height > max_height)
	{
#if defined(LIBFO_DEBUG) && 0
	  g_message ("area_split_before_height_check:: checking:: area: %s; generated by: %s; y: %f; height: %f",
		     fo_object_debug_sprintf (use_child_area),
		     fo_object_debug_sprintf (use_child_area->generated_by),
		     ((FoAreaArea *) use_child_area)->y,
		     ((FoAreaArea *) use_child_area)->height);
#endif

	  if (!fo_area_split_before_height_check (use_child_area,
						  max_height -
						  minus_child_y))
	    {
#if defined(LIBFO_DEBUG) && 0
	      g_message ("area_split_before_height_check:: child won't split:: child: %s; generated by: %s; area: %s; generated by: %s",
			 fo_object_debug_sprintf (use_child_area),
			 fo_object_debug_sprintf (use_child_area->generated_by),
			 fo_object_debug_sprintf (area),
			 fo_object_debug_sprintf (area->generated_by));
#endif
	      if (use_child_area == fo_area_first_child (area))
		{
#if defined(LIBFO_DEBUG) && 0
		  g_message ("area_split_before_height_check:: non-splitting child is first child:: child: %s; generated by: %s; area: %s; generated by: %s",
			     fo_object_debug_sprintf (use_child_area),
			     fo_object_debug_sprintf (use_child_area->generated_by),
			     fo_object_debug_sprintf (area),
			     fo_object_debug_sprintf (area->generated_by));
#endif
		  return FALSE;
		}
	      else
		{
#if defined(LIBFO_DEBUG) && 0
		  g_message ("area_split_before_height_check:: can split area but child won't split:: child: %s; generated by: %s; area: %s; generated by: %s",
			     fo_object_debug_sprintf (use_child_area),
			     fo_object_debug_sprintf (use_child_area->generated_by),
			     fo_object_debug_sprintf (area),
			     fo_object_debug_sprintf (area->generated_by));
#endif

		  return TRUE;
		}
	    }
	  else
	    {

#if defined(LIBFO_DEBUG) && 0
	      g_message ("area_split_before_height_check:: child can split:: child: %s; generated by: %s; area: %s; generated by: %s",
			 fo_object_debug_sprintf (use_child_area),
			 fo_object_debug_sprintf (use_child_area->generated_by),
			 fo_object_debug_sprintf (area),
			 fo_object_debug_sprintf (area->generated_by));
#endif
	      return TRUE;
	    }
	}
      else
	{
	  total_child_height = minus_child_y + child_height;
	}

      use_child_area = fo_area_next_sibling (use_child_area);
    }

  return FALSE;
}
