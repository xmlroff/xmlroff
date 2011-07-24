/* Fo
 * fo-region.c: Abstract 'region' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo-context-util.h"
#include "fo/fo-region-private.h"
#include "fo/fo-simple-page-master.h"
#include "property/fo-property-background-color.h"
#include "property/fo-property-background-image.h"
#include "property/fo-property-border-after-color.h"
#include "property/fo-property-border-after-style.h"
#include "property/fo-property-border-after-width.h"
#include "property/fo-property-border-before-color.h"
#include "property/fo-property-border-before-style.h"
#include "property/fo-property-border-before-width.h"
#include "property/fo-property-border-bottom-color.h"
#include "property/fo-property-border-bottom-style.h"
#include "property/fo-property-border-bottom-width.h"
#include "property/fo-property-border-end-color.h"
#include "property/fo-property-border-end-style.h"
#include "property/fo-property-border-end-width.h"
#include "property/fo-property-border-left-color.h"
#include "property/fo-property-border-left-style.h"
#include "property/fo-property-border-left-width.h"
#include "property/fo-property-border-right-color.h"
#include "property/fo-property-border-right-style.h"
#include "property/fo-property-border-right-width.h"
#include "property/fo-property-border-start-color.h"
#include "property/fo-property-border-start-style.h"
#include "property/fo-property-border-start-width.h"
#include "property/fo-property-border-top-color.h"
#include "property/fo-property-border-top-style.h"
#include "property/fo-property-border-top-width.h"
#include "property/fo-property-clip.h"
#include "property/fo-property-display-align.h"
#include "property/fo-property-overflow.h"
#include "property/fo-property-padding-after.h"
#include "property/fo-property-padding-before.h"
#include "property/fo-property-padding-bottom.h"
#include "property/fo-property-padding-end.h"
#include "property/fo-property-padding-left.h"
#include "property/fo-property-padding-right.h"
#include "property/fo-property-padding-start.h"
#include "property/fo-property-padding-top.h"
#include "property/fo-property-reference-orientation.h"
#include "property/fo-property-region-name.h"
#include "property/fo-property-writing-mode.h"

enum {
  PROP_0,
  PROP_BACKGROUND_COLOR,
  PROP_BACKGROUND_IMAGE,
  PROP_BORDER_AFTER_COLOR,
  PROP_BORDER_AFTER_STYLE,
  PROP_BORDER_AFTER_WIDTH,
  PROP_BORDER_BEFORE_COLOR,
  PROP_BORDER_BEFORE_STYLE,
  PROP_BORDER_BEFORE_WIDTH,
  PROP_BORDER_BOTTOM_COLOR,
  PROP_BORDER_BOTTOM_STYLE,
  PROP_BORDER_BOTTOM_WIDTH,
  PROP_BORDER_END_COLOR,
  PROP_BORDER_END_STYLE,
  PROP_BORDER_END_WIDTH,
  PROP_BORDER_LEFT_COLOR,
  PROP_BORDER_LEFT_STYLE,
  PROP_BORDER_LEFT_WIDTH,
  PROP_BORDER_RIGHT_COLOR,
  PROP_BORDER_RIGHT_STYLE,
  PROP_BORDER_RIGHT_WIDTH,
  PROP_BORDER_START_COLOR,
  PROP_BORDER_START_STYLE,
  PROP_BORDER_START_WIDTH,
  PROP_BORDER_TOP_COLOR,
  PROP_BORDER_TOP_STYLE,
  PROP_BORDER_TOP_WIDTH,
  PROP_CLIP,
  PROP_DISPLAY_ALIGN,
  PROP_OVERFLOW,
  PROP_PADDING_AFTER,
  PROP_PADDING_BEFORE,
  PROP_PADDING_BOTTOM,
  PROP_PADDING_END,
  PROP_PADDING_LEFT,
  PROP_PADDING_RIGHT,
  PROP_PADDING_START,
  PROP_PADDING_TOP,
  PROP_REFERENCE_ORIENTATION,
  PROP_REGION_NAME,
  PROP_WRITING_MODE
};

static void _base_class_init  (FoRegionClass *klass);
static void _cbpbp_fo_init (FoCBPBPFoIface *iface);
static void _class_init  (FoRegionClass *klass);
static void _get_property (GObject      *object,
				    guint         prop_id,
				    GValue       *value,
				    GParamSpec   *pspec);
static void _set_property (GObject      *object,
				    guint         prop_id,
				    const GValue *value,
				    GParamSpec   *pspec);
static void _finalize    (GObject           *object);
static void _update_from_context (FoFo      *fo,
					   FoContext *context);
static void _debug_dump_properties (FoFo *fo,
					     gint  depth);

static gpointer parent_class;

/**
 * fo_region_get_type:
 * 
 * Register the #FoRegion object type.
 * 
 * Return value: #GType value of the #FoRegion object type.
 **/
GType
fo_region_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoRegionClass),
	  (GBaseInitFunc) _base_class_init,
	  NULL,           /* base_finalize */
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoRegion),
	  0,              /* n_preallocs */
	  NULL,		/* instance_init */
	  NULL		/* value_table */
	};

      static const GInterfaceInfo fo_region_cbpbp_info =
	{
	  (GInterfaceInitFunc) _cbpbp_fo_init,	 /* interface_init */
	  NULL,
	  NULL
	};

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoRegion",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_CBPBP_FO,
                                   &fo_region_cbpbp_info);
    }

  return object_type;
}

/**
 * _base_class_init:
 * @klass: #FoRegionClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoRegionClass.
 **/
void
_base_class_init (FoRegionClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  FoNodeClass *fo_node_class = FO_NODE_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  fo_fo_class->update_from_context = _update_from_context;
  fo_fo_class->debug_dump_properties = _debug_dump_properties;
  fo_fo_class->generate_reference_area = TRUE;
  fo_fo_class->validate_content =
    fo_fo_validate_content_empty;
}

/**
 * _class_init:
 * @klass: #FoRegionClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRegionClass.
 **/
void
_class_init (FoRegionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = _finalize;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  g_object_class_install_property
    (object_class,
     PROP_BACKGROUND_COLOR,
     g_param_spec_object ("background-color",
			  _("Background Color"),
			  _("Background Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BACKGROUND_IMAGE,
     g_param_spec_object ("background-image",
			  _("Background Image"),
			  _("Background Image property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_COLOR,
     g_param_spec_object ("border-after-color",
			  _("Border After Color"),
			  _("Border After Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_STYLE,
     g_param_spec_object ("border-after-style",
			  _("Border After Style"),
			  _("Border After Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_AFTER_WIDTH,
     g_param_spec_object ("border-after-width",
			  _("Border After Width"),
			  _("Border After Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_COLOR,
     g_param_spec_object ("border-before-color",
			  _("Border Before Color"),
			  _("Border Before Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_STYLE,
     g_param_spec_object ("border-before-style",
			  _("Border Before Style"),
			  _("Border Before Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BEFORE_WIDTH,
     g_param_spec_object ("border-before-width",
			  _("Border Before Width"),
			  _("Border Before Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_COLOR,
     g_param_spec_object ("border-bottom-color",
			  _("Border Bottom Color"),
			  _("Border Bottom Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_STYLE,
     g_param_spec_object ("border-bottom-style",
			  _("Border Bottom Style"),
			  _("Border Bottom Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_BOTTOM_WIDTH,
     g_param_spec_object ("border-bottom-width",
			  _("Border Bottom Width"),
			  _("Border Bottom Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_COLOR,
     g_param_spec_object ("border-end-color",
			  _("Border End Color"),
			  _("Border End Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_STYLE,
     g_param_spec_object ("border-end-style",
			  _("Border End Style"),
			  _("Border End Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_END_WIDTH,
     g_param_spec_object ("border-end-width",
			  _("Border End Width"),
			  _("Border End Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_COLOR,
     g_param_spec_object ("border-left-color",
			  _("Border Left Color"),
			  _("Border Left Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_STYLE,
     g_param_spec_object ("border-left-style",
			  _("Border Left Style"),
			  _("Border Left Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_LEFT_WIDTH,
     g_param_spec_object ("border-left-width",
			  _("Border Left Width"),
			  _("Border Left Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_COLOR,
     g_param_spec_object ("border-right-color",
			  _("Border Right Color"),
			  _("Border Right Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_STYLE,
     g_param_spec_object ("border-right-style",
			  _("Border Right Style"),
			  _("Border Right Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_RIGHT_WIDTH,
     g_param_spec_object ("border-right-width",
			  _("Border Right Width"),
			  _("Border Right Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_COLOR,
     g_param_spec_object ("border-start-color",
			  _("Border Start Color"),
			  _("Border Start Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_STYLE,
     g_param_spec_object ("border-start-style",
			  _("Border Start Style"),
			  _("Border Start Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_START_WIDTH,
     g_param_spec_object ("border-start-width",
			  _("Border Start Width"),
			  _("Border Start Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_COLOR,
     g_param_spec_object ("border-top-color",
			  _("Border Top Color"),
			  _("Border Top Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_STYLE,
     g_param_spec_object ("border-top-style",
			  _("Border Top Style"),
			  _("Border Top Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP_WIDTH,
     g_param_spec_object ("border-top-width",
			  _("Border Top Width"),
			  _("Border Top Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_CLIP,
     g_param_spec_object ("clip",
			  _("Clip"),
			  _("Clip property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_DISPLAY_ALIGN,
     g_param_spec_object ("display-align",
			  _("Display Align"),
			  _("Display Align property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_OVERFLOW,
     g_param_spec_object ("overflow",
			  _("Overflow"),
			  _("Overflow property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_AFTER,
     g_param_spec_object ("padding-after",
			  _("Padding After"),
			  _("Padding After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_BEFORE,
     g_param_spec_object ("padding-before",
			  _("Padding Before"),
			  _("Padding Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_BOTTOM,
     g_param_spec_object ("padding-bottom",
			  _("Padding Bottom"),
			  _("Padding Bottom property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_END,
     g_param_spec_object ("padding-end",
			  _("Padding End"),
			  _("Padding End property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_LEFT,
     g_param_spec_object ("padding-left",
			  _("Padding Left"),
			  _("Padding Left property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_RIGHT,
     g_param_spec_object ("padding-right",
			  _("Padding Right"),
			  _("Padding Right property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_START,
     g_param_spec_object ("padding-start",
			  _("Padding Start"),
			  _("Padding Start property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_TOP,
     g_param_spec_object ("padding-top",
			  _("Padding Top"),
			  _("Padding Top property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_REFERENCE_ORIENTATION,
     g_param_spec_object ("reference-orientation",
			  _("Reference Orientation"),
			  _("Reference Orientation property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_REGION_NAME,
     g_param_spec_object ("region-name",
			  _("Region Name"),
			  _("Region Name property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WRITING_MODE,
     g_param_spec_object ("writing-mode",
			  _("Writing Mode"),
			  _("Writing Mode property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * _cbpbp_fo_init:
 * @iface: #FoCBPBPFoIFace structure for this class.
 * 
 * Initialize #FoCBPBPFoIface interface for this class.
 **/
void
_cbpbp_fo_init (FoCBPBPFoIface *iface)
{
  iface->get_background_color = fo_region_get_background_color;
  iface->set_background_color = fo_region_set_background_color;
  iface->get_border_after_color = fo_region_get_border_after_color;
  iface->set_border_after_color = fo_region_set_border_after_color;
  iface->get_border_after_style = fo_region_get_border_after_style;
  iface->set_border_after_style = fo_region_set_border_after_style;
  iface->get_border_after_width = fo_region_get_border_after_width;
  iface->set_border_after_width = fo_region_set_border_after_width;
  iface->get_border_before_color = fo_region_get_border_before_color;
  iface->set_border_before_color = fo_region_set_border_before_color;
  iface->get_border_before_style = fo_region_get_border_before_style;
  iface->set_border_before_style = fo_region_set_border_before_style;
  iface->get_border_before_width = fo_region_get_border_before_width;
  iface->set_border_before_width = fo_region_set_border_before_width;
  iface->set_border_bottom_color = fo_region_set_border_bottom_color;
  iface->set_border_bottom_style = fo_region_set_border_bottom_style;
  iface->set_border_bottom_width = fo_region_set_border_bottom_width;
  iface->get_border_end_color = fo_region_get_border_end_color;
  iface->set_border_end_color = fo_region_set_border_end_color;
  iface->get_border_end_style = fo_region_get_border_end_style;
  iface->set_border_end_style = fo_region_set_border_end_style;
  iface->get_border_end_width = fo_region_get_border_end_width;
  iface->set_border_end_width = fo_region_set_border_end_width;
  iface->set_border_left_color = fo_region_set_border_left_color;
  iface->set_border_left_style = fo_region_set_border_left_style;
  iface->set_border_left_width = fo_region_set_border_left_width;
  iface->set_border_right_color = fo_region_set_border_right_color;
  iface->set_border_right_style = fo_region_set_border_right_style;
  iface->set_border_right_width = fo_region_set_border_right_width;
  iface->get_border_start_color = fo_region_get_border_start_color;
  iface->set_border_start_color = fo_region_set_border_start_color;
  iface->get_border_start_style = fo_region_get_border_start_style;
  iface->set_border_start_style = fo_region_set_border_start_style;
  iface->get_border_start_width = fo_region_get_border_start_width;
  iface->set_border_start_width = fo_region_set_border_start_width;
  iface->set_border_top_color = fo_region_set_border_top_color;
  iface->set_border_top_style = fo_region_set_border_top_style;
  iface->set_border_top_width = fo_region_set_border_top_width;
  iface->get_padding_after = fo_region_get_padding_after;
  iface->set_padding_after = fo_region_set_padding_after;
  iface->get_padding_before = fo_region_get_padding_before;
  iface->set_padding_before = fo_region_set_padding_before;
  iface->set_padding_bottom = fo_region_set_padding_bottom;
  iface->get_padding_end = fo_region_get_padding_end;
  iface->set_padding_end = fo_region_set_padding_end;
  iface->set_padding_left = fo_region_set_padding_left;
  iface->set_padding_right = fo_region_set_padding_right;
  iface->get_padding_start = fo_region_get_padding_start;
  iface->set_padding_start = fo_region_set_padding_start;
  iface->set_padding_top = fo_region_set_padding_top;
}

/**
 * _finalize:
 * @object: #FoRegion object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoRegion.
 **/
void
_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_cbpbp_fo_finalize (fo);
  fo_region_set_background_image (fo, NULL);
  fo_region_set_clip (fo, NULL);
  fo_region_set_display_align (fo, NULL);
  fo_region_set_overflow (fo, NULL);
  fo_region_set_reference_orientation (fo, NULL);
  fo_region_set_region_name (fo, NULL);
  fo_region_set_writing_mode (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * _get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoRegion.
 **/
void
_get_property (GObject    *object,
	       guint       prop_id,
	       GValue     *value,
	       GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_background_color (fo_fo)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_region_get_background_image (fo_fo)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_after_color (fo_fo)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_after_style (fo_fo)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_after_width (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_before_color (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_before_style (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_before_width (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_bottom_color (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_bottom_style (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_bottom_width (fo_fo)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_end_color (fo_fo)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_end_style (fo_fo)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_end_width (fo_fo)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_left_color (fo_fo)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_left_style (fo_fo)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_left_width (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_right_color (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_right_style (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_right_width (fo_fo)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_start_color (fo_fo)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_start_style (fo_fo)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_start_width (fo_fo)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_top_color (fo_fo)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_top_style (fo_fo)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_get_border_top_width (fo_fo)));
      break;
    case PROP_CLIP:
      g_value_set_object (value, G_OBJECT (fo_region_get_clip (fo_fo)));
      break;
    case PROP_DISPLAY_ALIGN:
      g_value_set_object (value, G_OBJECT (fo_region_get_display_align (fo_fo)));
      break;
    case PROP_OVERFLOW:
      g_value_set_object (value, G_OBJECT (fo_region_get_overflow (fo_fo)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_region_get_padding_after (fo_fo)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_region_get_padding_before (fo_fo)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_region_get_padding_bottom (fo_fo)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_region_get_padding_end (fo_fo)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_region_get_padding_left (fo_fo)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_region_get_padding_right (fo_fo)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_region_get_padding_start (fo_fo)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_region_get_padding_top (fo_fo)));
      break;
    case PROP_REFERENCE_ORIENTATION:
      g_value_set_object (value, G_OBJECT (fo_region_get_reference_orientation (fo_fo)));
      break;
    case PROP_REGION_NAME:
      g_value_set_object (value, G_OBJECT (fo_region_get_region_name (fo_fo)));
      break;
    case PROP_WRITING_MODE:
      g_value_set_object (value, G_OBJECT (fo_region_get_writing_mode (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * _set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoRegion.
 **/
void
_set_property (GObject      *object,
			guint         prop_id,
			const GValue *value,
			GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      fo_region_set_background_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_region_set_background_image (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_region_set_border_after_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_region_set_border_after_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_region_set_border_after_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_region_set_border_before_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_region_set_border_before_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_region_set_border_before_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_region_set_border_bottom_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_region_set_border_bottom_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_region_set_border_bottom_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_region_set_border_end_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_region_set_border_end_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_region_set_border_end_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_region_set_border_left_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_region_set_border_left_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_region_set_border_left_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_region_set_border_right_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_region_set_border_right_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_region_set_border_right_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_region_set_border_start_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_region_set_border_start_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_region_set_border_start_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_region_set_border_top_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_region_set_border_top_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_region_set_border_top_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_CLIP:
      fo_region_set_clip (fo_fo, g_value_get_object (value));
      break;
    case PROP_DISPLAY_ALIGN:
      fo_region_set_display_align (fo_fo, g_value_get_object (value));
      break;
    case PROP_OVERFLOW:
      fo_region_set_overflow (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_region_set_padding_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_region_set_padding_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_region_set_padding_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_region_set_padding_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_region_set_padding_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_region_set_padding_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_region_set_padding_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_region_set_padding_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_REFERENCE_ORIENTATION:
      fo_region_set_reference_orientation (fo_fo, g_value_get_object (value));
      break;
    case PROP_REGION_NAME:
      fo_region_set_region_name (fo_fo, g_value_get_object (value));
      break;
    case PROP_WRITING_MODE:
      fo_region_set_writing_mode (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_new:
 * 
 * Creates a new #FoRegion initialized to default value.
 * 
 * Return value: the new #FoRegion.
 **/
FoFo*
fo_region_new (void)
{
  return FO_FO (g_object_new (fo_region_get_type (),
                              NULL));
}

/**
 * _update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
_update_from_context (FoFo      *fo,
			       FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_cbpbp_fo_update_from_context (fo,
				   context);

  /*  fo_region_set_background_color (fo,
				  fo_context_get_background_color (context));
  */
  fo_region_set_background_image (fo,
				  fo_context_get_background_image (context));
  /*
  fo_region_set_border_after_color (fo,
				    fo_context_get_border_after_color (context));
  fo_region_set_border_after_style (fo,
				    fo_context_get_border_after_style (context));
  fo_region_set_border_after_width (fo,
				    fo_context_get_border_after_width (context));
  fo_region_set_border_before_color (fo,
				     fo_context_get_border_before_color (context));
  fo_region_set_border_before_style (fo,
				     fo_context_get_border_before_style (context));
  fo_region_set_border_before_width (fo,
				     fo_context_get_border_before_width (context));
  fo_region_set_border_end_color (fo,
				  fo_context_get_border_end_color (context));
  fo_region_set_border_end_style (fo,
				  fo_context_get_border_end_style (context));
  fo_region_set_border_end_width (fo,
				  fo_context_get_border_end_width (context));
  fo_region_set_border_start_color (fo,
				    fo_context_get_border_start_color (context));
  fo_region_set_border_start_style (fo,
				    fo_context_get_border_start_style (context));
  fo_region_set_border_start_width (fo,
				    fo_context_get_border_start_width (context));
  fo_region_set_border_bottom_color (fo,
				     fo_context_get_border_bottom_color (context));
  fo_region_set_border_bottom_style (fo,
				     fo_context_get_border_bottom_style (context));
  fo_region_set_border_bottom_width (fo,
				     fo_context_get_border_bottom_width (context));
  fo_region_set_border_left_color (fo,
				   fo_context_get_border_left_color (context));
  fo_region_set_border_left_style (fo,
				   fo_context_get_border_left_style (context));
  fo_region_set_border_left_width (fo,
				   fo_context_get_border_left_width (context));
  fo_region_set_border_right_color (fo,
				    fo_context_get_border_right_color (context));
  fo_region_set_border_right_style (fo,
				    fo_context_get_border_right_style (context));
  fo_region_set_border_right_width (fo,
				    fo_context_get_border_right_width (context));
  fo_region_set_border_top_color (fo,
				  fo_context_get_border_top_color (context));
  fo_region_set_border_top_style (fo,
				  fo_context_get_border_top_style (context));
  fo_region_set_border_top_width (fo,
				  fo_context_get_border_top_width (context));
  */
  fo_region_set_clip (fo,
		      fo_context_get_clip (context));
  fo_region_set_display_align (fo,
		      fo_context_get_display_align (context));
  fo_region_set_overflow (fo,
			  fo_context_get_overflow (context));
  /*
  fo_region_set_padding_after (fo,
			       fo_context_get_padding_after (context));
  fo_region_set_padding_before (fo,
				fo_context_get_padding_before (context));
  fo_region_set_padding_end (fo,
			     fo_context_get_padding_end (context));
  fo_region_set_padding_start (fo,
			       fo_context_get_padding_start (context));
  fo_region_set_padding_bottom (fo,
				fo_context_get_padding_bottom (context));
  fo_region_set_padding_left (fo,
			      fo_context_get_padding_left (context));
  fo_region_set_padding_right (fo,
			       fo_context_get_padding_right (context));
  fo_region_set_padding_top (fo,
			     fo_context_get_padding_top (context));
  */
  fo_region_set_reference_orientation (fo,
				       fo_context_get_reference_orientation (context));
  fo_region_set_region_name (fo,
			     fo_context_get_region_name (context));
  fo_region_set_writing_mode (fo,
			      fo_context_get_writing_mode (context));
}

/**
 * _debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
_debug_dump_properties (FoFo *fo,
				 gint  depth)
{
  FoRegion *fo_region;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION (fo));

  fo_region = FO_REGION (fo);

  fo_object_debug_dump (fo_region->background_color, depth);
  fo_object_debug_dump (fo_region->background_image, depth);
  fo_object_debug_dump (fo_region->border_after_color, depth);
  fo_object_debug_dump (fo_region->border_after_style, depth);
  fo_object_debug_dump (fo_region->border_after_width, depth);
  fo_object_debug_dump (fo_region->border_before_color, depth);
  fo_object_debug_dump (fo_region->border_before_style, depth);
  fo_object_debug_dump (fo_region->border_before_width, depth);
  fo_object_debug_dump (fo_region->border_bottom_color, depth);
  fo_object_debug_dump (fo_region->border_bottom_style, depth);
  fo_object_debug_dump (fo_region->border_bottom_width, depth);
  fo_object_debug_dump (fo_region->border_end_color, depth);
  fo_object_debug_dump (fo_region->border_end_style, depth);
  fo_object_debug_dump (fo_region->border_end_width, depth);
  fo_object_debug_dump (fo_region->border_left_color, depth);
  fo_object_debug_dump (fo_region->border_left_style, depth);
  fo_object_debug_dump (fo_region->border_left_width, depth);
  fo_object_debug_dump (fo_region->border_right_color, depth);
  fo_object_debug_dump (fo_region->border_right_style, depth);
  fo_object_debug_dump (fo_region->border_right_width, depth);
  fo_object_debug_dump (fo_region->border_start_color, depth);
  fo_object_debug_dump (fo_region->border_start_style, depth);
  fo_object_debug_dump (fo_region->border_start_width, depth);
  fo_object_debug_dump (fo_region->border_top_color, depth);
  fo_object_debug_dump (fo_region->border_top_style, depth);
  fo_object_debug_dump (fo_region->border_top_width, depth);
  fo_object_debug_dump (fo_region->clip, depth);
  fo_object_debug_dump (fo_region->display_align, depth);
  fo_object_debug_dump (fo_region->overflow, depth);
  fo_object_debug_dump (fo_region->padding_after, depth);
  fo_object_debug_dump (fo_region->padding_before, depth);
  fo_object_debug_dump (fo_region->padding_bottom, depth);
  fo_object_debug_dump (fo_region->padding_end, depth);
  fo_object_debug_dump (fo_region->padding_left, depth);
  fo_object_debug_dump (fo_region->padding_right, depth);
  fo_object_debug_dump (fo_region->padding_start, depth);
  fo_object_debug_dump (fo_region->padding_top, depth);
  fo_object_debug_dump (fo_region->reference_orientation, depth);
  fo_object_debug_dump (fo_region->region_name, depth);
  fo_object_debug_dump (fo_region->writing_mode, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_region_get_background_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-color" property of @fo_fo.
 *
 * Return value: The "background-color" property value.
 **/
FoProperty *
fo_region_get_background_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->background_color;
}

/**
 * fo_region_set_background_color:
 * @fo_fo: The #FoFo object.
 * @new_background_color: The new "background-color" property value.
 * 
 * Sets the "background-color" property of @fo_fo to @new_background_color.
 **/
void
fo_region_set_background_color (FoFo *fo_fo,
				FoProperty *new_background_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_background_color == NULL) ||
		    FO_IS_PROPERTY_BACKGROUND_COLOR (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref (new_background_color);
    }
  if (fo_region->background_color != NULL)
    {
      g_object_unref (fo_region->background_color);
    }
  fo_region->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_region), "background-color");*/
}

/**
 * fo_region_get_background_image:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-image" property of @fo_fo.
 *
 * Return value: The "background-image" property value.
 **/
FoProperty *
fo_region_get_background_image (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->background_image;
}

/**
 * fo_region_set_background_image:
 * @fo_fo: The #FoFo object.
 * @new_background_image: The new "background-image" property value.
 * 
 * Sets the "background-image" property of @fo_fo to @new_background_image.
 **/
void
fo_region_set_background_image (FoFo *fo_fo,
				FoProperty *new_background_image)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_background_image == NULL) ||
		    FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref (new_background_image);
    }
  if (fo_region->background_image != NULL)
    {
      g_object_unref (fo_region->background_image);
    }
  fo_region->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_region), "background-image");*/
}

/**
 * fo_region_get_border_after_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-color" property of @fo_fo.
 *
 * Return value: The "border-after-color" property value.
 **/
FoProperty *
fo_region_get_border_after_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_after_color;
}

/**
 * fo_region_set_border_after_color:
 * @fo_fo: The #FoFo object.
 * @new_border_after_color: The new "border-after-color" property value.
 * 
 * Sets the "border-after-color" property of @fo_fo to @new_border_after_color.
 **/
void
fo_region_set_border_after_color (FoFo *fo_fo,
				  FoProperty *new_border_after_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_after_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref (new_border_after_color);
    }
  if (fo_region->border_after_color != NULL)
    {
      g_object_unref (fo_region->border_after_color);
    }
  fo_region->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_region), "border-after-color");*/
}

/**
 * fo_region_get_border_after_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-style" property of @fo_fo.
 *
 * Return value: The "border-after-style" property value.
 **/
FoProperty *
fo_region_get_border_after_style (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_after_style;
}

/**
 * fo_region_set_border_after_style:
 * @fo_fo: The #FoFo object.
 * @new_border_after_style: The new "border-after-style" property value.
 * 
 * Sets the "border-after-style" property of @fo_fo to @new_border_after_style.
 **/
void
fo_region_set_border_after_style (FoFo *fo_fo,
				  FoProperty *new_border_after_style)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_after_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref (new_border_after_style);
    }
  if (fo_region->border_after_style != NULL)
    {
      g_object_unref (fo_region->border_after_style);
    }
  fo_region->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_region), "border-after-style");*/
}

/**
 * fo_region_get_border_after_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-width" property of @fo_fo.
 *
 * Return value: The "border-after-width" property value.
 **/
FoProperty *
fo_region_get_border_after_width (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_after_width;
}

/**
 * fo_region_set_border_after_width:
 * @fo_fo: The #FoFo object.
 * @new_border_after_width: The new "border-after-width" property value.
 * 
 * Sets the "border-after-width" property of @fo_fo to @new_border_after_width.
 **/
void
fo_region_set_border_after_width (FoFo *fo_fo,
				  FoProperty *new_border_after_width)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_after_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref (new_border_after_width);
    }
  if (fo_region->border_after_width != NULL)
    {
      g_object_unref (fo_region->border_after_width);
    }
  fo_region->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_region), "border-after-width");*/
}

/**
 * fo_region_get_border_before_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-color" property of @fo_fo.
 *
 * Return value: The "border-before-color" property value.
 **/
FoProperty *
fo_region_get_border_before_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_before_color;
}

/**
 * fo_region_set_border_before_color:
 * @fo_fo: The #FoFo object.
 * @new_border_before_color: The new "border-before-color" property value.
 * 
 * Sets the "border-before-color" property of @fo_fo to @new_border_before_color.
 **/
void
fo_region_set_border_before_color (FoFo *fo_fo,
				   FoProperty *new_border_before_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_before_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref (new_border_before_color);
    }
  if (fo_region->border_before_color != NULL)
    {
      g_object_unref (fo_region->border_before_color);
    }
  fo_region->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_region), "border-before-color");*/
}

/**
 * fo_region_get_border_before_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-style" property of @fo_fo.
 *
 * Return value: The "border-before-style" property value.
 **/
FoProperty *
fo_region_get_border_before_style (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_before_style;
}

/**
 * fo_region_set_border_before_style:
 * @fo_fo: The #FoFo object.
 * @new_border_before_style: The new "border-before-style" property value.
 * 
 * Sets the "border-before-style" property of @fo_fo to @new_border_before_style.
 **/
void
fo_region_set_border_before_style (FoFo *fo_fo,
				   FoProperty *new_border_before_style)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_before_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref (new_border_before_style);
    }
  if (fo_region->border_before_style != NULL)
    {
      g_object_unref (fo_region->border_before_style);
    }
  fo_region->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_region), "border-before-style");*/
}

/**
 * fo_region_get_border_before_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-width" property of @fo_fo.
 *
 * Return value: The "border-before-width" property value.
 **/
FoProperty *
fo_region_get_border_before_width (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_before_width;
}

/**
 * fo_region_set_border_before_width:
 * @fo_fo: The #FoFo object.
 * @new_border_before_width: The new "border-before-width" property value.
 * 
 * Sets the "border-before-width" property of @fo_fo to @new_border_before_width.
 **/
void
fo_region_set_border_before_width (FoFo *fo_fo,
				   FoProperty *new_border_before_width)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_before_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref (new_border_before_width);
    }
  if (fo_region->border_before_width != NULL)
    {
      g_object_unref (fo_region->border_before_width);
    }
  fo_region->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_region), "border-before-width");*/
}

/**
 * fo_region_get_border_bottom_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-color" property of @fo_fo.
 *
 * Return value: The "border-bottom-color" property value.
 **/
FoProperty *
fo_region_get_border_bottom_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_bottom_color;
}

/**
 * fo_region_set_border_bottom_color:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_color: The new "border-bottom-color" property value.
 * 
 * Sets the "border-bottom-color" property of @fo_fo to @new_border_bottom_color.
 **/
void
fo_region_set_border_bottom_color (FoFo *fo_fo,
				   FoProperty *new_border_bottom_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_bottom_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref (new_border_bottom_color);
    }
  if (fo_region->border_bottom_color != NULL)
    {
      g_object_unref (fo_region->border_bottom_color);
    }
  fo_region->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_region), "border-bottom-color");*/
}

/**
 * fo_region_get_border_bottom_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-style" property of @fo_fo.
 *
 * Return value: The "border-bottom-style" property value.
 **/
FoProperty *
fo_region_get_border_bottom_style (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_bottom_style;
}

/**
 * fo_region_set_border_bottom_style:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_style: The new "border-bottom-style" property value.
 * 
 * Sets the "border-bottom-style" property of @fo_fo to @new_border_bottom_style.
 **/
void
fo_region_set_border_bottom_style (FoFo *fo_fo,
				   FoProperty *new_border_bottom_style)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_bottom_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref (new_border_bottom_style);
    }
  if (fo_region->border_bottom_style != NULL)
    {
      g_object_unref (fo_region->border_bottom_style);
    }
  fo_region->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_region), "border-bottom-style");*/
}

/**
 * fo_region_get_border_bottom_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-width" property of @fo_fo.
 *
 * Return value: The "border-bottom-width" property value.
 **/
FoProperty *
fo_region_get_border_bottom_width (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_bottom_width;
}

/**
 * fo_region_set_border_bottom_width:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_width: The new "border-bottom-width" property value.
 * 
 * Sets the "border-bottom-width" property of @fo_fo to @new_border_bottom_width.
 **/
void
fo_region_set_border_bottom_width (FoFo *fo_fo,
				   FoProperty *new_border_bottom_width)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_bottom_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref (new_border_bottom_width);
    }
  if (fo_region->border_bottom_width != NULL)
    {
      g_object_unref (fo_region->border_bottom_width);
    }
  fo_region->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_region), "border-bottom-width");*/
}

/**
 * fo_region_get_border_end_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-color" property of @fo_fo.
 *
 * Return value: The "border-end-color" property value.
 **/
FoProperty *
fo_region_get_border_end_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_end_color;
}

/**
 * fo_region_set_border_end_color:
 * @fo_fo: The #FoFo object.
 * @new_border_end_color: The new "border-end-color" property value.
 * 
 * Sets the "border-end-color" property of @fo_fo to @new_border_end_color.
 **/
void
fo_region_set_border_end_color (FoFo *fo_fo,
				FoProperty *new_border_end_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_end_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref (new_border_end_color);
    }
  if (fo_region->border_end_color != NULL)
    {
      g_object_unref (fo_region->border_end_color);
    }
  fo_region->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_region), "border-end-color");*/
}

/**
 * fo_region_get_border_end_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-style" property of @fo_fo.
 *
 * Return value: The "border-end-style" property value.
 **/
FoProperty *
fo_region_get_border_end_style (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_end_style;
}

/**
 * fo_region_set_border_end_style:
 * @fo_fo: The #FoFo object.
 * @new_border_end_style: The new "border-end-style" property value.
 * 
 * Sets the "border-end-style" property of @fo_fo to @new_border_end_style.
 **/
void
fo_region_set_border_end_style (FoFo *fo_fo,
				FoProperty *new_border_end_style)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_end_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref (new_border_end_style);
    }
  if (fo_region->border_end_style != NULL)
    {
      g_object_unref (fo_region->border_end_style);
    }
  fo_region->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_region), "border-end-style");*/
}

/**
 * fo_region_get_border_end_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-width" property of @fo_fo.
 *
 * Return value: The "border-end-width" property value.
 **/
FoProperty *
fo_region_get_border_end_width (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_end_width;
}

/**
 * fo_region_set_border_end_width:
 * @fo_fo: The #FoFo object.
 * @new_border_end_width: The new "border-end-width" property value.
 * 
 * Sets the "border-end-width" property of @fo_fo to @new_border_end_width.
 **/
void
fo_region_set_border_end_width (FoFo *fo_fo,
				FoProperty *new_border_end_width)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_end_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref (new_border_end_width);
    }
  if (fo_region->border_end_width != NULL)
    {
      g_object_unref (fo_region->border_end_width);
    }
  fo_region->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_region), "border-end-width");*/
}

/**
 * fo_region_get_border_left_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-color" property of @fo_fo.
 *
 * Return value: The "border-left-color" property value.
 **/
FoProperty *
fo_region_get_border_left_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_left_color;
}

/**
 * fo_region_set_border_left_color:
 * @fo_fo: The #FoFo object.
 * @new_border_left_color: The new "border-left-color" property value.
 * 
 * Sets the "border-left-color" property of @fo_fo to @new_border_left_color.
 **/
void
fo_region_set_border_left_color (FoFo *fo_fo,
				 FoProperty *new_border_left_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_left_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref (new_border_left_color);
    }
  if (fo_region->border_left_color != NULL)
    {
      g_object_unref (fo_region->border_left_color);
    }
  fo_region->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_region), "border-left-color");*/
}

/**
 * fo_region_get_border_left_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-style" property of @fo_fo.
 *
 * Return value: The "border-left-style" property value.
 **/
FoProperty *
fo_region_get_border_left_style (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_left_style;
}

/**
 * fo_region_set_border_left_style:
 * @fo_fo: The #FoFo object.
 * @new_border_left_style: The new "border-left-style" property value.
 * 
 * Sets the "border-left-style" property of @fo_fo to @new_border_left_style.
 **/
void
fo_region_set_border_left_style (FoFo *fo_fo,
				 FoProperty *new_border_left_style)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_left_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref (new_border_left_style);
    }
  if (fo_region->border_left_style != NULL)
    {
      g_object_unref (fo_region->border_left_style);
    }
  fo_region->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_region), "border-left-style");*/
}

/**
 * fo_region_get_border_left_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-width" property of @fo_fo.
 *
 * Return value: The "border-left-width" property value.
 **/
FoProperty *
fo_region_get_border_left_width (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_left_width;
}

/**
 * fo_region_set_border_left_width:
 * @fo_fo: The #FoFo object.
 * @new_border_left_width: The new "border-left-width" property value.
 * 
 * Sets the "border-left-width" property of @fo_fo to @new_border_left_width.
 **/
void
fo_region_set_border_left_width (FoFo *fo_fo,
				 FoProperty *new_border_left_width)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_left_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref (new_border_left_width);
    }
  if (fo_region->border_left_width != NULL)
    {
      g_object_unref (fo_region->border_left_width);
    }
  fo_region->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_region), "border-left-width");*/
}

/**
 * fo_region_get_border_right_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-color" property of @fo_fo.
 *
 * Return value: The "border-right-color" property value.
 **/
FoProperty *
fo_region_get_border_right_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_right_color;
}

/**
 * fo_region_set_border_right_color:
 * @fo_fo: The #FoFo object.
 * @new_border_right_color: The new "border-right-color" property value.
 * 
 * Sets the "border-right-color" property of @fo_fo to @new_border_right_color.
 **/
void
fo_region_set_border_right_color (FoFo *fo_fo,
				  FoProperty *new_border_right_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_right_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref (new_border_right_color);
    }
  if (fo_region->border_right_color != NULL)
    {
      g_object_unref (fo_region->border_right_color);
    }
  fo_region->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_region), "border-right-color");*/
}

/**
 * fo_region_get_border_right_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-style" property of @fo_fo.
 *
 * Return value: The "border-right-style" property value.
 **/
FoProperty *
fo_region_get_border_right_style (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_right_style;
}

/**
 * fo_region_set_border_right_style:
 * @fo_fo: The #FoFo object.
 * @new_border_right_style: The new "border-right-style" property value.
 * 
 * Sets the "border-right-style" property of @fo_fo to @new_border_right_style.
 **/
void
fo_region_set_border_right_style (FoFo *fo_fo,
				  FoProperty *new_border_right_style)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_right_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref (new_border_right_style);
    }
  if (fo_region->border_right_style != NULL)
    {
      g_object_unref (fo_region->border_right_style);
    }
  fo_region->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_region), "border-right-style");*/
}

/**
 * fo_region_get_border_right_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-width" property of @fo_fo.
 *
 * Return value: The "border-right-width" property value.
 **/
FoProperty *
fo_region_get_border_right_width (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_right_width;
}

/**
 * fo_region_set_border_right_width:
 * @fo_fo: The #FoFo object.
 * @new_border_right_width: The new "border-right-width" property value.
 * 
 * Sets the "border-right-width" property of @fo_fo to @new_border_right_width.
 **/
void
fo_region_set_border_right_width (FoFo *fo_fo,
				  FoProperty *new_border_right_width)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_right_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref (new_border_right_width);
    }
  if (fo_region->border_right_width != NULL)
    {
      g_object_unref (fo_region->border_right_width);
    }
  fo_region->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_region), "border-right-width");*/
}

/**
 * fo_region_get_border_start_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-color" property of @fo_fo.
 *
 * Return value: The "border-start-color" property value.
 **/
FoProperty *
fo_region_get_border_start_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_start_color;
}

/**
 * fo_region_set_border_start_color:
 * @fo_fo: The #FoFo object.
 * @new_border_start_color: The new "border-start-color" property value.
 * 
 * Sets the "border-start-color" property of @fo_fo to @new_border_start_color.
 **/
void
fo_region_set_border_start_color (FoFo *fo_fo,
				  FoProperty *new_border_start_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_start_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref (new_border_start_color);
    }
  if (fo_region->border_start_color != NULL)
    {
      g_object_unref (fo_region->border_start_color);
    }
  fo_region->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_region), "border-start-color");*/
}

/**
 * fo_region_get_border_start_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-style" property of @fo_fo.
 *
 * Return value: The "border-start-style" property value.
 **/
FoProperty *
fo_region_get_border_start_style (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_start_style;
}

/**
 * fo_region_set_border_start_style:
 * @fo_fo: The #FoFo object.
 * @new_border_start_style: The new "border-start-style" property value.
 * 
 * Sets the "border-start-style" property of @fo_fo to @new_border_start_style.
 **/
void
fo_region_set_border_start_style (FoFo *fo_fo,
				  FoProperty *new_border_start_style)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_start_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref (new_border_start_style);
    }
  if (fo_region->border_start_style != NULL)
    {
      g_object_unref (fo_region->border_start_style);
    }
  fo_region->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_region), "border-start-style");*/
}

/**
 * fo_region_get_border_start_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-width" property of @fo_fo.
 *
 * Return value: The "border-start-width" property value.
 **/
FoProperty *
fo_region_get_border_start_width (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_start_width;
}

/**
 * fo_region_set_border_start_width:
 * @fo_fo: The #FoFo object.
 * @new_border_start_width: The new "border-start-width" property value.
 * 
 * Sets the "border-start-width" property of @fo_fo to @new_border_start_width.
 **/
void
fo_region_set_border_start_width (FoFo *fo_fo,
				  FoProperty *new_border_start_width)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_start_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref (new_border_start_width);
    }
  if (fo_region->border_start_width != NULL)
    {
      g_object_unref (fo_region->border_start_width);
    }
  fo_region->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_region), "border-start-width");*/
}

/**
 * fo_region_get_border_top_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-color" property of @fo_fo.
 *
 * Return value: The "border-top-color" property value.
 **/
FoProperty *
fo_region_get_border_top_color (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_top_color;
}

/**
 * fo_region_set_border_top_color:
 * @fo_fo: The #FoFo object.
 * @new_border_top_color: The new "border-top-color" property value.
 * 
 * Sets the "border-top-color" property of @fo_fo to @new_border_top_color.
 **/
void
fo_region_set_border_top_color (FoFo *fo_fo,
				FoProperty *new_border_top_color)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_top_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref (new_border_top_color);
    }
  if (fo_region->border_top_color != NULL)
    {
      g_object_unref (fo_region->border_top_color);
    }
  fo_region->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_region), "border-top-color");*/
}

/**
 * fo_region_get_border_top_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-style" property of @fo_fo.
 *
 * Return value: The "border-top-style" property value.
 **/
FoProperty *
fo_region_get_border_top_style (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_top_style;
}

/**
 * fo_region_set_border_top_style:
 * @fo_fo: The #FoFo object.
 * @new_border_top_style: The new "border-top-style" property value.
 * 
 * Sets the "border-top-style" property of @fo_fo to @new_border_top_style.
 **/
void
fo_region_set_border_top_style (FoFo *fo_fo,
				FoProperty *new_border_top_style)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_top_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref (new_border_top_style);
    }
  if (fo_region->border_top_style != NULL)
    {
      g_object_unref (fo_region->border_top_style);
    }
  fo_region->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_region), "border-top-style");*/
}

/**
 * fo_region_get_border_top_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-width" property of @fo_fo.
 *
 * Return value: The "border-top-width" property value.
 **/
FoProperty *
fo_region_get_border_top_width (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->border_top_width;
}

/**
 * fo_region_set_border_top_width:
 * @fo_fo: The #FoFo object.
 * @new_border_top_width: The new "border-top-width" property value.
 * 
 * Sets the "border-top-width" property of @fo_fo to @new_border_top_width.
 **/
void
fo_region_set_border_top_width (FoFo *fo_fo,
				FoProperty *new_border_top_width)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_border_top_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref (new_border_top_width);
    }
  if (fo_region->border_top_width != NULL)
    {
      g_object_unref (fo_region->border_top_width);
    }
  fo_region->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_region), "border-top-width");*/
}

/**
 * fo_region_get_clip:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "clip" property of @fo_fo.
 *
 * Return value: The "clip" property value.
 **/
FoProperty *
fo_region_get_clip (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->clip;
}

/**
 * fo_region_set_clip:
 * @fo_fo: The #FoFo object.
 * @new_clip: The new "clip" property value.
 * 
 * Sets the "clip" property of @fo_fo to @new_clip.
 **/
void
fo_region_set_clip (FoFo *fo_fo,
		    FoProperty *new_clip)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_clip == NULL) ||
		    FO_IS_PROPERTY_CLIP (new_clip));

  if (new_clip != NULL)
    {
      g_object_ref (new_clip);
    }
  if (fo_region->clip != NULL)
    {
      g_object_unref (fo_region->clip);
    }
  fo_region->clip = new_clip;
  /*g_object_notify (G_OBJECT (fo_region), "clip");*/
}

/**
 * fo_region_get_display_align:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "display-align" property of @fo_fo.
 *
 * Return value: The "display-align" property value.
 **/
FoProperty *
fo_region_get_display_align (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->display_align;
}

/**
 * fo_region_set_display_align:
 * @fo_fo: The #FoFo object.
 * @new_display_align: The new "display-align" property value.
 * 
 * Sets the "display_align" property of @fo_fo to @new_display_align.
 **/
void
fo_region_set_display_align (FoFo *fo_fo,
		    FoProperty *new_display_align)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_display_align == NULL) ||
		    FO_IS_PROPERTY_DISPLAY_ALIGN (new_display_align));

  if (new_display_align != NULL)
    {
      g_object_ref (new_display_align);
    }
  if (fo_region->display_align != NULL)
    {
      g_object_unref (fo_region->display_align);
    }
  fo_region->display_align = new_display_align;
  /*g_object_notify (G_OBJECT (fo_region), "display-align");*/
}

/**
 * fo_region_get_overflow:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "overflow" property of @fo_fo.
 *
 * Return value: The "overflow" property value.
 **/
FoProperty *
fo_region_get_overflow (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->overflow;
}

/**
 * fo_region_set_overflow:
 * @fo_fo: The #FoFo object.
 * @new_overflow: The new "overflow" property value.
 * 
 * Sets the "overflow" property of @fo_fo to @new_overflow.
 **/
void
fo_region_set_overflow (FoFo *fo_fo,
			FoProperty *new_overflow)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_overflow == NULL) ||
		    FO_IS_PROPERTY_OVERFLOW (new_overflow));

  if (new_overflow != NULL)
    {
      g_object_ref (new_overflow);
    }
  if (fo_region->overflow != NULL)
    {
      g_object_unref (fo_region->overflow);
    }
  fo_region->overflow = new_overflow;
  /*g_object_notify (G_OBJECT (fo_region), "overflow");*/
}

/**
 * fo_region_get_padding_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-after" property of @fo_fo.
 *
 * Return value: The "padding-after" property value.
 **/
FoProperty *
fo_region_get_padding_after (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->padding_after;
}

/**
 * fo_region_set_padding_after:
 * @fo_fo: The #FoFo object.
 * @new_padding_after: The new "padding-after" property value.
 * 
 * Sets the "padding-after" property of @fo_fo to @new_padding_after.
 **/
void
fo_region_set_padding_after (FoFo *fo_fo,
			     FoProperty *new_padding_after)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_padding_after == NULL) ||
		    FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref (new_padding_after);
    }
  if (fo_region->padding_after != NULL)
    {
      g_object_unref (fo_region->padding_after);
    }
  fo_region->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_region), "padding-after");*/
}

/**
 * fo_region_get_padding_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-before" property of @fo_fo.
 *
 * Return value: The "padding-before" property value.
 **/
FoProperty *
fo_region_get_padding_before (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->padding_before;
}

/**
 * fo_region_set_padding_before:
 * @fo_fo: The #FoFo object.
 * @new_padding_before: The new "padding-before" property value.
 * 
 * Sets the "padding-before" property of @fo_fo to @new_padding_before.
 **/
void
fo_region_set_padding_before (FoFo *fo_fo,
			      FoProperty *new_padding_before)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_padding_before == NULL) ||
		    FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref (new_padding_before);
    }
  if (fo_region->padding_before != NULL)
    {
      g_object_unref (fo_region->padding_before);
    }
  fo_region->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_region), "padding-before");*/
}

/**
 * fo_region_get_padding_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-bottom" property of @fo_fo.
 *
 * Return value: The "padding-bottom" property value.
 **/
FoProperty *
fo_region_get_padding_bottom (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->padding_bottom;
}

/**
 * fo_region_set_padding_bottom:
 * @fo_fo: The #FoFo object.
 * @new_padding_bottom: The new "padding-bottom" property value.
 * 
 * Sets the "padding-bottom" property of @fo_fo to @new_padding_bottom.
 **/
void
fo_region_set_padding_bottom (FoFo *fo_fo,
			      FoProperty *new_padding_bottom)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_padding_bottom == NULL) ||
		    FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref (new_padding_bottom);
    }
  if (fo_region->padding_bottom != NULL)
    {
      g_object_unref (fo_region->padding_bottom);
    }
  fo_region->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_region), "padding-bottom");*/
}

/**
 * fo_region_get_padding_end:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-end" property of @fo_fo.
 *
 * Return value: The "padding-end" property value.
 **/
FoProperty *
fo_region_get_padding_end (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->padding_end;
}

/**
 * fo_region_set_padding_end:
 * @fo_fo: The #FoFo object.
 * @new_padding_end: The new "padding-end" property value.
 * 
 * Sets the "padding-end" property of @fo_fo to @new_padding_end.
 **/
void
fo_region_set_padding_end (FoFo *fo_fo,
			   FoProperty *new_padding_end)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_padding_end == NULL) ||
		    FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref (new_padding_end);
    }
  if (fo_region->padding_end != NULL)
    {
      g_object_unref (fo_region->padding_end);
    }
  fo_region->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_region), "padding-end");*/
}

/**
 * fo_region_get_padding_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-left" property of @fo_fo.
 *
 * Return value: The "padding-left" property value.
 **/
FoProperty *
fo_region_get_padding_left (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->padding_left;
}

/**
 * fo_region_set_padding_left:
 * @fo_fo: The #FoFo object.
 * @new_padding_left: The new "padding-left" property value.
 * 
 * Sets the "padding-left" property of @fo_fo to @new_padding_left.
 **/
void
fo_region_set_padding_left (FoFo *fo_fo,
			    FoProperty *new_padding_left)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_padding_left == NULL) ||
		    FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref (new_padding_left);
    }
  if (fo_region->padding_left != NULL)
    {
      g_object_unref (fo_region->padding_left);
    }
  fo_region->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_region), "padding-left");*/
}

/**
 * fo_region_get_padding_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-right" property of @fo_fo.
 *
 * Return value: The "padding-right" property value.
 **/
FoProperty *
fo_region_get_padding_right (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->padding_right;
}

/**
 * fo_region_set_padding_right:
 * @fo_fo: The #FoFo object.
 * @new_padding_right: The new "padding-right" property value.
 * 
 * Sets the "padding-right" property of @fo_fo to @new_padding_right.
 **/
void
fo_region_set_padding_right (FoFo *fo_fo,
			     FoProperty *new_padding_right)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_padding_right == NULL) ||
		    FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref (new_padding_right);
    }
  if (fo_region->padding_right != NULL)
    {
      g_object_unref (fo_region->padding_right);
    }
  fo_region->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_region), "padding-right");*/
}

/**
 * fo_region_get_padding_start:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-start" property of @fo_fo.
 *
 * Return value: The "padding-start" property value.
 **/
FoProperty *
fo_region_get_padding_start (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->padding_start;
}

/**
 * fo_region_set_padding_start:
 * @fo_fo: The #FoFo object.
 * @new_padding_start: The new "padding-start" property value.
 * 
 * Sets the "padding-start" property of @fo_fo to @new_padding_start.
 **/
void
fo_region_set_padding_start (FoFo *fo_fo,
			     FoProperty *new_padding_start)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_padding_start == NULL) ||
		    FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref (new_padding_start);
    }
  if (fo_region->padding_start != NULL)
    {
      g_object_unref (fo_region->padding_start);
    }
  fo_region->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_region), "padding-start");*/
}

/**
 * fo_region_get_padding_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-top" property of @fo_fo.
 *
 * Return value: The "padding-top" property value.
 **/
FoProperty *
fo_region_get_padding_top (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->padding_top;
}

/**
 * fo_region_set_padding_top:
 * @fo_fo: The #FoFo object.
 * @new_padding_top: The new "padding-top" property value.
 * 
 * Sets the "padding-top" property of @fo_fo to @new_padding_top.
 **/
void
fo_region_set_padding_top (FoFo *fo_fo,
			   FoProperty *new_padding_top)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_padding_top == NULL) ||
		    FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref (new_padding_top);
    }
  if (fo_region->padding_top != NULL)
    {
      g_object_unref (fo_region->padding_top);
    }
  fo_region->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_region), "padding-top");*/
}

/**
 * fo_region_get_reference_orientation:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "reference-orientation" property of @fo_fo.
 *
 * Return value: The "reference-orientation" property value.
 **/
FoProperty *
fo_region_get_reference_orientation (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->reference_orientation;
}

/**
 * fo_region_set_reference_orientation:
 * @fo_fo: The #FoFo object.
 * @new_reference_orientation: The new "reference-orientation" property value.
 * 
 * Sets the "reference-orientation" property of @fo_fo to @new_reference_orientation.
 **/
void
fo_region_set_reference_orientation (FoFo *fo_fo,
				     FoProperty *new_reference_orientation)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_reference_orientation == NULL) ||
		    FO_IS_PROPERTY_REFERENCE_ORIENTATION (new_reference_orientation));

  if (new_reference_orientation != NULL)
    {
      g_object_ref (new_reference_orientation);
    }
  if (fo_region->reference_orientation != NULL)
    {
      g_object_unref (fo_region->reference_orientation);
    }
  fo_region->reference_orientation = new_reference_orientation;
  /*g_object_notify (G_OBJECT (fo_region), "reference-orientation");*/
}

/**
 * fo_region_get_region_name:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "region-name" property of @fo_fo.
 *
 * Return value: The "region-name" property value.
 **/
FoProperty *
fo_region_get_region_name (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->region_name;
}

/**
 * fo_region_set_region_name:
 * @fo_fo: The #FoFo object.
 * @new_region_name: The new "region-name" property value.
 * 
 * Sets the "region-name" property of @fo_fo to @new_region_name.
 **/
void
fo_region_set_region_name (FoFo *fo_fo,
			   FoProperty *new_region_name)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_region_name == NULL) ||
		    FO_IS_PROPERTY_REGION_NAME (new_region_name));

  if (new_region_name != NULL)
    {
      g_object_ref (new_region_name);
    }
  if (fo_region->region_name != NULL)
    {
      g_object_unref (fo_region->region_name);
    }
  fo_region->region_name = new_region_name;
  /*g_object_notify (G_OBJECT (fo_region), "region-name");*/
}

/**
 * fo_region_get_writing_mode:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "writing-mode" property of @fo_fo.
 *
 * Return value: The "writing-mode" property value.
 **/
FoProperty *
fo_region_get_writing_mode (FoFo *fo_fo)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_val_if_fail (fo_region != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION (fo_region), NULL);

  return fo_region->writing_mode;
}

/**
 * fo_region_set_writing_mode:
 * @fo_fo: The #FoFo object.
 * @new_writing_mode: The new "writing-mode" property value.
 * 
 * Sets the "writing-mode" property of @fo_fo to @new_writing_mode.
 **/
void
fo_region_set_writing_mode (FoFo *fo_fo,
			    FoProperty *new_writing_mode)
{
  FoRegion *fo_region = (FoRegion *) fo_fo;

  g_return_if_fail (fo_region != NULL);
  g_return_if_fail (FO_IS_REGION (fo_region));
  g_return_if_fail ((new_writing_mode == NULL) ||
		    FO_IS_PROPERTY_WRITING_MODE (new_writing_mode));

  if (new_writing_mode != NULL)
    {
      g_object_ref (new_writing_mode);
    }
  if (fo_region->writing_mode != NULL)
    {
      g_object_unref (fo_region->writing_mode);
    }
  fo_region->writing_mode = new_writing_mode;
  /*g_object_notify (G_OBJECT (fo_region), "writing-mode");*/
}
