/* Fo
 * fo-region-before.c: 'region-before' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-region-before-private.h"
#include "fo-context-util.h"
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
#include "property/fo-property-extent.h"
#include "property/fo-property-overflow.h"
#include "property/fo-property-padding-after.h"
#include "property/fo-property-padding-before.h"
#include "property/fo-property-padding-bottom.h"
#include "property/fo-property-padding-end.h"
#include "property/fo-property-padding-left.h"
#include "property/fo-property-padding-right.h"
#include "property/fo-property-padding-start.h"
#include "property/fo-property-padding-top.h"
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
  PROP_EXTENT,
  PROP_OVERFLOW,
  PROP_PADDING_AFTER,
  PROP_PADDING_BEFORE,
  PROP_PADDING_BOTTOM,
  PROP_PADDING_END,
  PROP_PADDING_LEFT,
  PROP_PADDING_RIGHT,
  PROP_PADDING_START,
  PROP_PADDING_TOP,
  PROP_REGION_NAME,
  PROP_WRITING_MODE
};

static void fo_region_before_class_init  (FoRegionBeforeClass *klass);
static void fo_region_before_get_property (GObject      *object,
                                           guint         prop_id,
                                           GValue       *value,
                                           GParamSpec   *pspec);
static void fo_region_before_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);
static void fo_region_before_finalize    (GObject           *object);
static void fo_region_before_validate (FoFo      *fo,
                                       FoContext *current_context,
                                       FoContext *parent_context,
                                       GError   **error);
static void fo_region_before_update_from_context (FoFo      *fo,
                                                  FoContext *context);
static void fo_region_before_debug_dump_properties (FoFo *fo,
                                                    gint  depth);

static gpointer parent_class;

/**
 * fo_region_before_get_type:
 * 
 * Register the #FoRegionBefore object type.
 * 
 * Return value: #GType value of the #FoRegionBefore object type.
 **/
GType
fo_region_before_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoRegionBeforeClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_region_before_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoRegionBefore),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoRegionBefore",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_region_before_class_init:
 * @klass: #FoRegionBeforeClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRegionBeforeClass.
 **/
void
fo_region_before_class_init (FoRegionBeforeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_region_before_finalize;

  object_class->get_property = fo_region_before_get_property;
  object_class->set_property = fo_region_before_set_property;

  fofo_class->validate_content = fo_fo_validate_content_empty;
  fofo_class->validate2 = fo_region_before_validate;
  fofo_class->update_from_context = fo_region_before_update_from_context;
  fofo_class->debug_dump_properties = fo_region_before_debug_dump_properties;
  fofo_class->generate_reference_area = TRUE;

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
     PROP_EXTENT,
     g_param_spec_object ("extent",
			  _("Extent"),
			  _("Extent property"),
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
 * fo_region_before_finalize:
 * @object: #FoRegionBefore object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoRegionBefore.
 **/
void
fo_region_before_finalize (GObject *object)
{
  FoRegionBefore *fo_region_before;

  fo_region_before = FO_REGION_BEFORE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_region_before_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoRegionBefore.
 **/
void
fo_region_before_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_background_color (fo_fo)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_background_image (fo_fo)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_after_color (fo_fo)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_after_style (fo_fo)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_after_width (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_before_color (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_before_style (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_before_width (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_bottom_color (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_bottom_style (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_bottom_width (fo_fo)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_end_color (fo_fo)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_end_style (fo_fo)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_end_width (fo_fo)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_left_color (fo_fo)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_left_style (fo_fo)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_left_width (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_right_color (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_right_style (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_right_width (fo_fo)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_start_color (fo_fo)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_start_style (fo_fo)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_start_width (fo_fo)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_top_color (fo_fo)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_top_style (fo_fo)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_border_top_width (fo_fo)));
      break;
    case PROP_CLIP:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_clip (fo_fo)));
      break;
    case PROP_DISPLAY_ALIGN:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_display_align (fo_fo)));
      break;
    case PROP_EXTENT:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_extent (fo_fo)));
      break;
    case PROP_OVERFLOW:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_overflow (fo_fo)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_padding_after (fo_fo)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_padding_before (fo_fo)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_padding_bottom (fo_fo)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_padding_end (fo_fo)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_padding_left (fo_fo)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_padding_right (fo_fo)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_padding_start (fo_fo)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_padding_top (fo_fo)));
      break;
    case PROP_REGION_NAME:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_region_name (fo_fo)));
      break;
    case PROP_WRITING_MODE:
      g_value_set_object (value, G_OBJECT (fo_region_before_get_writing_mode (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_before_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoRegionBefore.
 **/
void
fo_region_before_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      fo_region_before_set_background_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_region_before_set_background_image (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_region_before_set_border_after_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_region_before_set_border_after_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_region_before_set_border_after_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_region_before_set_border_before_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_region_before_set_border_before_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_region_before_set_border_before_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_region_before_set_border_bottom_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_region_before_set_border_bottom_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_region_before_set_border_bottom_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_region_before_set_border_end_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_region_before_set_border_end_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_region_before_set_border_end_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_region_before_set_border_left_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_region_before_set_border_left_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_region_before_set_border_left_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_region_before_set_border_right_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_region_before_set_border_right_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_region_before_set_border_right_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_region_before_set_border_start_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_region_before_set_border_start_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_region_before_set_border_start_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_region_before_set_border_top_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_region_before_set_border_top_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_region_before_set_border_top_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_CLIP:
      fo_region_before_set_clip (fo_fo, g_value_get_object (value));
      break;
    case PROP_DISPLAY_ALIGN:
      fo_region_before_set_display_align (fo_fo, g_value_get_object (value));
      break;
    case PROP_EXTENT:
      fo_region_before_set_extent (fo_fo, g_value_get_object (value));
      break;
    case PROP_OVERFLOW:
      fo_region_before_set_overflow (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_region_before_set_padding_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_region_before_set_padding_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_region_before_set_padding_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_region_before_set_padding_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_region_before_set_padding_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_region_before_set_padding_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_region_before_set_padding_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_region_before_set_padding_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_REGION_NAME:
      fo_region_before_set_region_name (fo_fo, g_value_get_object (value));
      break;
    case PROP_WRITING_MODE:
      fo_region_before_set_writing_mode (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_region_before_new:
 * 
 * Creates a new #FoRegionBefore initialized to default value.
 * 
 * Return value: the new #FoRegionBefore.
 **/
FoFo*
fo_region_before_new (void)
{
  return FO_FO (g_object_new (fo_region_before_get_type (),
			      NULL));
}

/**
 * fo_region_before_validate:
 * @fo:              #FoRegionBefore object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_region_before_validate (FoFo      *fo,
                           FoContext *current_context,
                           FoContext *parent_context,
                           GError   **error)
{
  FoFo *simple_page_master = NULL;
  gchar *region_name;
  FoDatatype *region_name_datatype = NULL;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_context_util_border_resolve (current_context, parent_context);
  fo_context_util_paddings_resolve (current_context, parent_context);
  fo_context_util_margins_indents_resolve (fo,
					   current_context,
					   parent_context);
  fo_context_util_margins_resolve (current_context, parent_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  region_name_datatype =
    fo_property_get_value (fo_region_before_get_region_name (fo));

  if (region_name_datatype != NULL)
    {
      region_name =
	fo_name_get_value (region_name_datatype);
    }
  else
    {
      region_name = g_strdup ("xsl-region-before");
    }

    simple_page_master = FO_FO (fo_node_parent (FO_NODE (fo)));

  if (simple_page_master != NULL)
    {
      fo_simple_page_master_region_name_add (simple_page_master,
					     region_name,
					     fo);
      g_free (region_name);
    }
  else
    {
      g_assert_not_reached();
    }
}

/**
 * fo_region_before_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_region_before_update_from_context (FoFo      *fo,
                                      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_region_before_set_background_color (fo,
			  fo_context_get_background_color (context));
  fo_region_before_set_background_image (fo,
			  fo_context_get_background_image (context));
  fo_region_before_set_border_after_color (fo,
			  fo_context_get_border_after_color (context));
  fo_region_before_set_border_after_style (fo,
			  fo_context_get_border_after_style (context));
  fo_region_before_set_border_after_width (fo,
			  fo_context_get_border_after_width (context));
  fo_region_before_set_border_before_color (fo,
			  fo_context_get_border_before_color (context));
  fo_region_before_set_border_before_style (fo,
			  fo_context_get_border_before_style (context));
  fo_region_before_set_border_before_width (fo,
			  fo_context_get_border_before_width (context));
  fo_region_before_set_border_bottom_color (fo,
			  fo_context_get_border_bottom_color (context));
  fo_region_before_set_border_bottom_style (fo,
			  fo_context_get_border_bottom_style (context));
  fo_region_before_set_border_bottom_width (fo,
			  fo_context_get_border_bottom_width (context));
  fo_region_before_set_border_end_color (fo,
			  fo_context_get_border_end_color (context));
  fo_region_before_set_border_end_style (fo,
			  fo_context_get_border_end_style (context));
  fo_region_before_set_border_end_width (fo,
			  fo_context_get_border_end_width (context));
  fo_region_before_set_border_left_color (fo,
			  fo_context_get_border_left_color (context));
  fo_region_before_set_border_left_style (fo,
			  fo_context_get_border_left_style (context));
  fo_region_before_set_border_left_width (fo,
			  fo_context_get_border_left_width (context));
  fo_region_before_set_border_right_color (fo,
			  fo_context_get_border_right_color (context));
  fo_region_before_set_border_right_style (fo,
			  fo_context_get_border_right_style (context));
  fo_region_before_set_border_right_width (fo,
			  fo_context_get_border_right_width (context));
  fo_region_before_set_border_start_color (fo,
			  fo_context_get_border_start_color (context));
  fo_region_before_set_border_start_style (fo,
			  fo_context_get_border_start_style (context));
  fo_region_before_set_border_start_width (fo,
			  fo_context_get_border_start_width (context));
  fo_region_before_set_border_top_color (fo,
			  fo_context_get_border_top_color (context));
  fo_region_before_set_border_top_style (fo,
			  fo_context_get_border_top_style (context));
  fo_region_before_set_border_top_width (fo,
			  fo_context_get_border_top_width (context));
  fo_region_before_set_clip (fo,
			  fo_context_get_clip (context));
  fo_region_before_set_display_align (fo,
			  fo_context_get_display_align (context));
  fo_region_before_set_extent (fo,
			  fo_context_get_extent (context));
  fo_region_before_set_overflow (fo,
			  fo_context_get_overflow (context));
  fo_region_before_set_padding_after (fo,
			  fo_context_get_padding_after (context));
  fo_region_before_set_padding_before (fo,
			  fo_context_get_padding_before (context));
  fo_region_before_set_padding_bottom (fo,
			  fo_context_get_padding_bottom (context));
  fo_region_before_set_padding_end (fo,
			  fo_context_get_padding_end (context));
  fo_region_before_set_padding_left (fo,
			  fo_context_get_padding_left (context));
  fo_region_before_set_padding_right (fo,
			  fo_context_get_padding_right (context));
  fo_region_before_set_padding_start (fo,
			  fo_context_get_padding_start (context));
  fo_region_before_set_padding_top (fo,
			  fo_context_get_padding_top (context));
  fo_region_before_set_region_name (fo,
			  fo_context_get_region_name (context));
  fo_region_before_set_writing_mode (fo,
			  fo_context_get_writing_mode (context));
}

/**
 * fo_region_before_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_region_before_debug_dump_properties (FoFo *fo,
                                        gint  depth)
{
  FoRegionBefore *fo_region_before;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo));

  fo_region_before = FO_REGION_BEFORE (fo);

  fo_object_debug_dump (fo_region_before->background_color, depth);
  fo_object_debug_dump (fo_region_before->background_image, depth);
  fo_object_debug_dump (fo_region_before->border_after_color, depth);
  fo_object_debug_dump (fo_region_before->border_after_style, depth);
  fo_object_debug_dump (fo_region_before->border_after_width, depth);
  fo_object_debug_dump (fo_region_before->border_before_color, depth);
  fo_object_debug_dump (fo_region_before->border_before_style, depth);
  fo_object_debug_dump (fo_region_before->border_before_width, depth);
  fo_object_debug_dump (fo_region_before->border_bottom_color, depth);
  fo_object_debug_dump (fo_region_before->border_bottom_style, depth);
  fo_object_debug_dump (fo_region_before->border_bottom_width, depth);
  fo_object_debug_dump (fo_region_before->border_end_color, depth);
  fo_object_debug_dump (fo_region_before->border_end_style, depth);
  fo_object_debug_dump (fo_region_before->border_end_width, depth);
  fo_object_debug_dump (fo_region_before->border_left_color, depth);
  fo_object_debug_dump (fo_region_before->border_left_style, depth);
  fo_object_debug_dump (fo_region_before->border_left_width, depth);
  fo_object_debug_dump (fo_region_before->border_right_color, depth);
  fo_object_debug_dump (fo_region_before->border_right_style, depth);
  fo_object_debug_dump (fo_region_before->border_right_width, depth);
  fo_object_debug_dump (fo_region_before->border_start_color, depth);
  fo_object_debug_dump (fo_region_before->border_start_style, depth);
  fo_object_debug_dump (fo_region_before->border_start_width, depth);
  fo_object_debug_dump (fo_region_before->border_top_color, depth);
  fo_object_debug_dump (fo_region_before->border_top_style, depth);
  fo_object_debug_dump (fo_region_before->border_top_width, depth);
  fo_object_debug_dump (fo_region_before->clip, depth);
  fo_object_debug_dump (fo_region_before->display_align, depth);
  fo_object_debug_dump (fo_region_before->extent, depth);
  fo_object_debug_dump (fo_region_before->overflow, depth);
  fo_object_debug_dump (fo_region_before->padding_after, depth);
  fo_object_debug_dump (fo_region_before->padding_before, depth);
  fo_object_debug_dump (fo_region_before->padding_bottom, depth);
  fo_object_debug_dump (fo_region_before->padding_end, depth);
  fo_object_debug_dump (fo_region_before->padding_left, depth);
  fo_object_debug_dump (fo_region_before->padding_right, depth);
  fo_object_debug_dump (fo_region_before->padding_start, depth);
  fo_object_debug_dump (fo_region_before->padding_top, depth);
  fo_object_debug_dump (fo_region_before->region_name, depth);
  fo_object_debug_dump (fo_region_before->writing_mode, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_region_before_get_background_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-color" property of @fo_fo.
 *
 * Return value: The "background-color" property value.
**/
FoProperty*
fo_region_before_get_background_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->background_color;
}

/**
 * fo_region_before_set_background_color:
 * @fo_fo: The #FoFo object.
 * @new_background_color: The new "background-color" property value.
 * 
 * Sets the "background-color" property of @fo_fo to @new_background_color.
 **/
void
fo_region_before_set_background_color (FoFo *fo_fo,
		         FoProperty *new_background_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BACKGROUND_COLOR (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref (new_background_color);
    }
  if (fo_region_before->background_color != NULL)
    {
      g_object_unref (fo_region_before->background_color);
    }
  fo_region_before->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "background-color");*/
}

/**
 * fo_region_before_get_background_image:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-image" property of @fo_fo.
 *
 * Return value: The "background-image" property value.
**/
FoProperty*
fo_region_before_get_background_image (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->background_image;
}

/**
 * fo_region_before_set_background_image:
 * @fo_fo: The #FoFo object.
 * @new_background_image: The new "background-image" property value.
 * 
 * Sets the "background-image" property of @fo_fo to @new_background_image.
 **/
void
fo_region_before_set_background_image (FoFo *fo_fo,
		         FoProperty *new_background_image)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref (new_background_image);
    }
  if (fo_region_before->background_image != NULL)
    {
      g_object_unref (fo_region_before->background_image);
    }
  fo_region_before->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_region_before), "background-image");*/
}

/**
 * fo_region_before_get_border_after_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-color" property of @fo_fo.
 *
 * Return value: The "border-after-color" property value.
**/
FoProperty*
fo_region_before_get_border_after_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_after_color;
}

/**
 * fo_region_before_set_border_after_color:
 * @fo_fo: The #FoFo object.
 * @new_border_after_color: The new "border-after-color" property value.
 * 
 * Sets the "border-after-color" property of @fo_fo to @new_border_after_color.
 **/
void
fo_region_before_set_border_after_color (FoFo *fo_fo,
		         FoProperty *new_border_after_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref (new_border_after_color);
    }
  if (fo_region_before->border_after_color != NULL)
    {
      g_object_unref (fo_region_before->border_after_color);
    }
  fo_region_before->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-after-color");*/
}

/**
 * fo_region_before_get_border_after_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-style" property of @fo_fo.
 *
 * Return value: The "border-after-style" property value.
**/
FoProperty*
fo_region_before_get_border_after_style (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_after_style;
}

/**
 * fo_region_before_set_border_after_style:
 * @fo_fo: The #FoFo object.
 * @new_border_after_style: The new "border-after-style" property value.
 * 
 * Sets the "border-after-style" property of @fo_fo to @new_border_after_style.
 **/
void
fo_region_before_set_border_after_style (FoFo *fo_fo,
		         FoProperty *new_border_after_style)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref (new_border_after_style);
    }
  if (fo_region_before->border_after_style != NULL)
    {
      g_object_unref (fo_region_before->border_after_style);
    }
  fo_region_before->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-after-style");*/
}

/**
 * fo_region_before_get_border_after_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-width" property of @fo_fo.
 *
 * Return value: The "border-after-width" property value.
**/
FoProperty*
fo_region_before_get_border_after_width (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_after_width;
}

/**
 * fo_region_before_set_border_after_width:
 * @fo_fo: The #FoFo object.
 * @new_border_after_width: The new "border-after-width" property value.
 * 
 * Sets the "border-after-width" property of @fo_fo to @new_border_after_width.
 **/
void
fo_region_before_set_border_after_width (FoFo *fo_fo,
		         FoProperty *new_border_after_width)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref (new_border_after_width);
    }
  if (fo_region_before->border_after_width != NULL)
    {
      g_object_unref (fo_region_before->border_after_width);
    }
  fo_region_before->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-after-width");*/
}

/**
 * fo_region_before_get_border_before_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-color" property of @fo_fo.
 *
 * Return value: The "border-before-color" property value.
**/
FoProperty*
fo_region_before_get_border_before_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_before_color;
}

/**
 * fo_region_before_set_border_before_color:
 * @fo_fo: The #FoFo object.
 * @new_border_before_color: The new "border-before-color" property value.
 * 
 * Sets the "border-before-color" property of @fo_fo to @new_border_before_color.
 **/
void
fo_region_before_set_border_before_color (FoFo *fo_fo,
		         FoProperty *new_border_before_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref (new_border_before_color);
    }
  if (fo_region_before->border_before_color != NULL)
    {
      g_object_unref (fo_region_before->border_before_color);
    }
  fo_region_before->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-before-color");*/
}

/**
 * fo_region_before_get_border_before_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-style" property of @fo_fo.
 *
 * Return value: The "border-before-style" property value.
**/
FoProperty*
fo_region_before_get_border_before_style (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_before_style;
}

/**
 * fo_region_before_set_border_before_style:
 * @fo_fo: The #FoFo object.
 * @new_border_before_style: The new "border-before-style" property value.
 * 
 * Sets the "border-before-style" property of @fo_fo to @new_border_before_style.
 **/
void
fo_region_before_set_border_before_style (FoFo *fo_fo,
		         FoProperty *new_border_before_style)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref (new_border_before_style);
    }
  if (fo_region_before->border_before_style != NULL)
    {
      g_object_unref (fo_region_before->border_before_style);
    }
  fo_region_before->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-before-style");*/
}

/**
 * fo_region_before_get_border_before_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-width" property of @fo_fo.
 *
 * Return value: The "border-before-width" property value.
**/
FoProperty*
fo_region_before_get_border_before_width (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_before_width;
}

/**
 * fo_region_before_set_border_before_width:
 * @fo_fo: The #FoFo object.
 * @new_border_before_width: The new "border-before-width" property value.
 * 
 * Sets the "border-before-width" property of @fo_fo to @new_border_before_width.
 **/
void
fo_region_before_set_border_before_width (FoFo *fo_fo,
		         FoProperty *new_border_before_width)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref (new_border_before_width);
    }
  if (fo_region_before->border_before_width != NULL)
    {
      g_object_unref (fo_region_before->border_before_width);
    }
  fo_region_before->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-before-width");*/
}

/**
 * fo_region_before_get_border_bottom_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-color" property of @fo_fo.
 *
 * Return value: The "border-bottom-color" property value.
**/
FoProperty*
fo_region_before_get_border_bottom_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_bottom_color;
}

/**
 * fo_region_before_set_border_bottom_color:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_color: The new "border-bottom-color" property value.
 * 
 * Sets the "border-bottom-color" property of @fo_fo to @new_border_bottom_color.
 **/
void
fo_region_before_set_border_bottom_color (FoFo *fo_fo,
		         FoProperty *new_border_bottom_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref (new_border_bottom_color);
    }
  if (fo_region_before->border_bottom_color != NULL)
    {
      g_object_unref (fo_region_before->border_bottom_color);
    }
  fo_region_before->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-bottom-color");*/
}

/**
 * fo_region_before_get_border_bottom_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-style" property of @fo_fo.
 *
 * Return value: The "border-bottom-style" property value.
**/
FoProperty*
fo_region_before_get_border_bottom_style (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_bottom_style;
}

/**
 * fo_region_before_set_border_bottom_style:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_style: The new "border-bottom-style" property value.
 * 
 * Sets the "border-bottom-style" property of @fo_fo to @new_border_bottom_style.
 **/
void
fo_region_before_set_border_bottom_style (FoFo *fo_fo,
		         FoProperty *new_border_bottom_style)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref (new_border_bottom_style);
    }
  if (fo_region_before->border_bottom_style != NULL)
    {
      g_object_unref (fo_region_before->border_bottom_style);
    }
  fo_region_before->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-bottom-style");*/
}

/**
 * fo_region_before_get_border_bottom_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-width" property of @fo_fo.
 *
 * Return value: The "border-bottom-width" property value.
**/
FoProperty*
fo_region_before_get_border_bottom_width (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_bottom_width;
}

/**
 * fo_region_before_set_border_bottom_width:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_width: The new "border-bottom-width" property value.
 * 
 * Sets the "border-bottom-width" property of @fo_fo to @new_border_bottom_width.
 **/
void
fo_region_before_set_border_bottom_width (FoFo *fo_fo,
		         FoProperty *new_border_bottom_width)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref (new_border_bottom_width);
    }
  if (fo_region_before->border_bottom_width != NULL)
    {
      g_object_unref (fo_region_before->border_bottom_width);
    }
  fo_region_before->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-bottom-width");*/
}

/**
 * fo_region_before_get_border_end_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-color" property of @fo_fo.
 *
 * Return value: The "border-end-color" property value.
**/
FoProperty*
fo_region_before_get_border_end_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_end_color;
}

/**
 * fo_region_before_set_border_end_color:
 * @fo_fo: The #FoFo object.
 * @new_border_end_color: The new "border-end-color" property value.
 * 
 * Sets the "border-end-color" property of @fo_fo to @new_border_end_color.
 **/
void
fo_region_before_set_border_end_color (FoFo *fo_fo,
		         FoProperty *new_border_end_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref (new_border_end_color);
    }
  if (fo_region_before->border_end_color != NULL)
    {
      g_object_unref (fo_region_before->border_end_color);
    }
  fo_region_before->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-end-color");*/
}

/**
 * fo_region_before_get_border_end_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-style" property of @fo_fo.
 *
 * Return value: The "border-end-style" property value.
**/
FoProperty*
fo_region_before_get_border_end_style (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_end_style;
}

/**
 * fo_region_before_set_border_end_style:
 * @fo_fo: The #FoFo object.
 * @new_border_end_style: The new "border-end-style" property value.
 * 
 * Sets the "border-end-style" property of @fo_fo to @new_border_end_style.
 **/
void
fo_region_before_set_border_end_style (FoFo *fo_fo,
		         FoProperty *new_border_end_style)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref (new_border_end_style);
    }
  if (fo_region_before->border_end_style != NULL)
    {
      g_object_unref (fo_region_before->border_end_style);
    }
  fo_region_before->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-end-style");*/
}

/**
 * fo_region_before_get_border_end_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-width" property of @fo_fo.
 *
 * Return value: The "border-end-width" property value.
**/
FoProperty*
fo_region_before_get_border_end_width (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_end_width;
}

/**
 * fo_region_before_set_border_end_width:
 * @fo_fo: The #FoFo object.
 * @new_border_end_width: The new "border-end-width" property value.
 * 
 * Sets the "border-end-width" property of @fo_fo to @new_border_end_width.
 **/
void
fo_region_before_set_border_end_width (FoFo *fo_fo,
		         FoProperty *new_border_end_width)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref (new_border_end_width);
    }
  if (fo_region_before->border_end_width != NULL)
    {
      g_object_unref (fo_region_before->border_end_width);
    }
  fo_region_before->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-end-width");*/
}

/**
 * fo_region_before_get_border_left_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-color" property of @fo_fo.
 *
 * Return value: The "border-left-color" property value.
**/
FoProperty*
fo_region_before_get_border_left_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_left_color;
}

/**
 * fo_region_before_set_border_left_color:
 * @fo_fo: The #FoFo object.
 * @new_border_left_color: The new "border-left-color" property value.
 * 
 * Sets the "border-left-color" property of @fo_fo to @new_border_left_color.
 **/
void
fo_region_before_set_border_left_color (FoFo *fo_fo,
		         FoProperty *new_border_left_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref (new_border_left_color);
    }
  if (fo_region_before->border_left_color != NULL)
    {
      g_object_unref (fo_region_before->border_left_color);
    }
  fo_region_before->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-left-color");*/
}

/**
 * fo_region_before_get_border_left_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-style" property of @fo_fo.
 *
 * Return value: The "border-left-style" property value.
**/
FoProperty*
fo_region_before_get_border_left_style (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_left_style;
}

/**
 * fo_region_before_set_border_left_style:
 * @fo_fo: The #FoFo object.
 * @new_border_left_style: The new "border-left-style" property value.
 * 
 * Sets the "border-left-style" property of @fo_fo to @new_border_left_style.
 **/
void
fo_region_before_set_border_left_style (FoFo *fo_fo,
		         FoProperty *new_border_left_style)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref (new_border_left_style);
    }
  if (fo_region_before->border_left_style != NULL)
    {
      g_object_unref (fo_region_before->border_left_style);
    }
  fo_region_before->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-left-style");*/
}

/**
 * fo_region_before_get_border_left_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-width" property of @fo_fo.
 *
 * Return value: The "border-left-width" property value.
**/
FoProperty*
fo_region_before_get_border_left_width (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_left_width;
}

/**
 * fo_region_before_set_border_left_width:
 * @fo_fo: The #FoFo object.
 * @new_border_left_width: The new "border-left-width" property value.
 * 
 * Sets the "border-left-width" property of @fo_fo to @new_border_left_width.
 **/
void
fo_region_before_set_border_left_width (FoFo *fo_fo,
		         FoProperty *new_border_left_width)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref (new_border_left_width);
    }
  if (fo_region_before->border_left_width != NULL)
    {
      g_object_unref (fo_region_before->border_left_width);
    }
  fo_region_before->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-left-width");*/
}

/**
 * fo_region_before_get_border_right_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-color" property of @fo_fo.
 *
 * Return value: The "border-right-color" property value.
**/
FoProperty*
fo_region_before_get_border_right_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_right_color;
}

/**
 * fo_region_before_set_border_right_color:
 * @fo_fo: The #FoFo object.
 * @new_border_right_color: The new "border-right-color" property value.
 * 
 * Sets the "border-right-color" property of @fo_fo to @new_border_right_color.
 **/
void
fo_region_before_set_border_right_color (FoFo *fo_fo,
		         FoProperty *new_border_right_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref (new_border_right_color);
    }
  if (fo_region_before->border_right_color != NULL)
    {
      g_object_unref (fo_region_before->border_right_color);
    }
  fo_region_before->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-right-color");*/
}

/**
 * fo_region_before_get_border_right_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-style" property of @fo_fo.
 *
 * Return value: The "border-right-style" property value.
**/
FoProperty*
fo_region_before_get_border_right_style (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_right_style;
}

/**
 * fo_region_before_set_border_right_style:
 * @fo_fo: The #FoFo object.
 * @new_border_right_style: The new "border-right-style" property value.
 * 
 * Sets the "border-right-style" property of @fo_fo to @new_border_right_style.
 **/
void
fo_region_before_set_border_right_style (FoFo *fo_fo,
		         FoProperty *new_border_right_style)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref (new_border_right_style);
    }
  if (fo_region_before->border_right_style != NULL)
    {
      g_object_unref (fo_region_before->border_right_style);
    }
  fo_region_before->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-right-style");*/
}

/**
 * fo_region_before_get_border_right_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-width" property of @fo_fo.
 *
 * Return value: The "border-right-width" property value.
**/
FoProperty*
fo_region_before_get_border_right_width (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_right_width;
}

/**
 * fo_region_before_set_border_right_width:
 * @fo_fo: The #FoFo object.
 * @new_border_right_width: The new "border-right-width" property value.
 * 
 * Sets the "border-right-width" property of @fo_fo to @new_border_right_width.
 **/
void
fo_region_before_set_border_right_width (FoFo *fo_fo,
		         FoProperty *new_border_right_width)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref (new_border_right_width);
    }
  if (fo_region_before->border_right_width != NULL)
    {
      g_object_unref (fo_region_before->border_right_width);
    }
  fo_region_before->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-right-width");*/
}

/**
 * fo_region_before_get_border_start_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-color" property of @fo_fo.
 *
 * Return value: The "border-start-color" property value.
**/
FoProperty*
fo_region_before_get_border_start_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_start_color;
}

/**
 * fo_region_before_set_border_start_color:
 * @fo_fo: The #FoFo object.
 * @new_border_start_color: The new "border-start-color" property value.
 * 
 * Sets the "border-start-color" property of @fo_fo to @new_border_start_color.
 **/
void
fo_region_before_set_border_start_color (FoFo *fo_fo,
		         FoProperty *new_border_start_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref (new_border_start_color);
    }
  if (fo_region_before->border_start_color != NULL)
    {
      g_object_unref (fo_region_before->border_start_color);
    }
  fo_region_before->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-start-color");*/
}

/**
 * fo_region_before_get_border_start_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-style" property of @fo_fo.
 *
 * Return value: The "border-start-style" property value.
**/
FoProperty*
fo_region_before_get_border_start_style (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_start_style;
}

/**
 * fo_region_before_set_border_start_style:
 * @fo_fo: The #FoFo object.
 * @new_border_start_style: The new "border-start-style" property value.
 * 
 * Sets the "border-start-style" property of @fo_fo to @new_border_start_style.
 **/
void
fo_region_before_set_border_start_style (FoFo *fo_fo,
		         FoProperty *new_border_start_style)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref (new_border_start_style);
    }
  if (fo_region_before->border_start_style != NULL)
    {
      g_object_unref (fo_region_before->border_start_style);
    }
  fo_region_before->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-start-style");*/
}

/**
 * fo_region_before_get_border_start_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-width" property of @fo_fo.
 *
 * Return value: The "border-start-width" property value.
**/
FoProperty*
fo_region_before_get_border_start_width (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_start_width;
}

/**
 * fo_region_before_set_border_start_width:
 * @fo_fo: The #FoFo object.
 * @new_border_start_width: The new "border-start-width" property value.
 * 
 * Sets the "border-start-width" property of @fo_fo to @new_border_start_width.
 **/
void
fo_region_before_set_border_start_width (FoFo *fo_fo,
		         FoProperty *new_border_start_width)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref (new_border_start_width);
    }
  if (fo_region_before->border_start_width != NULL)
    {
      g_object_unref (fo_region_before->border_start_width);
    }
  fo_region_before->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-start-width");*/
}

/**
 * fo_region_before_get_border_top_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-color" property of @fo_fo.
 *
 * Return value: The "border-top-color" property value.
**/
FoProperty*
fo_region_before_get_border_top_color (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_top_color;
}

/**
 * fo_region_before_set_border_top_color:
 * @fo_fo: The #FoFo object.
 * @new_border_top_color: The new "border-top-color" property value.
 * 
 * Sets the "border-top-color" property of @fo_fo to @new_border_top_color.
 **/
void
fo_region_before_set_border_top_color (FoFo *fo_fo,
		         FoProperty *new_border_top_color)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref (new_border_top_color);
    }
  if (fo_region_before->border_top_color != NULL)
    {
      g_object_unref (fo_region_before->border_top_color);
    }
  fo_region_before->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-top-color");*/
}

/**
 * fo_region_before_get_border_top_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-style" property of @fo_fo.
 *
 * Return value: The "border-top-style" property value.
**/
FoProperty*
fo_region_before_get_border_top_style (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_top_style;
}

/**
 * fo_region_before_set_border_top_style:
 * @fo_fo: The #FoFo object.
 * @new_border_top_style: The new "border-top-style" property value.
 * 
 * Sets the "border-top-style" property of @fo_fo to @new_border_top_style.
 **/
void
fo_region_before_set_border_top_style (FoFo *fo_fo,
		         FoProperty *new_border_top_style)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref (new_border_top_style);
    }
  if (fo_region_before->border_top_style != NULL)
    {
      g_object_unref (fo_region_before->border_top_style);
    }
  fo_region_before->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-top-style");*/
}

/**
 * fo_region_before_get_border_top_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-width" property of @fo_fo.
 *
 * Return value: The "border-top-width" property value.
**/
FoProperty*
fo_region_before_get_border_top_width (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->border_top_width;
}

/**
 * fo_region_before_set_border_top_width:
 * @fo_fo: The #FoFo object.
 * @new_border_top_width: The new "border-top-width" property value.
 * 
 * Sets the "border-top-width" property of @fo_fo to @new_border_top_width.
 **/
void
fo_region_before_set_border_top_width (FoFo *fo_fo,
		         FoProperty *new_border_top_width)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref (new_border_top_width);
    }
  if (fo_region_before->border_top_width != NULL)
    {
      g_object_unref (fo_region_before->border_top_width);
    }
  fo_region_before->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_region_before), "border-top-width");*/
}

/**
 * fo_region_before_get_clip:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "clip" property of @fo_fo.
 *
 * Return value: The "clip" property value.
**/
FoProperty*
fo_region_before_get_clip (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->clip;
}

/**
 * fo_region_before_set_clip:
 * @fo_fo: The #FoFo object.
 * @new_clip: The new "clip" property value.
 * 
 * Sets the "clip" property of @fo_fo to @new_clip.
 **/
void
fo_region_before_set_clip (FoFo *fo_fo,
		         FoProperty *new_clip)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_CLIP (new_clip));

  if (new_clip != NULL)
    {
      g_object_ref (new_clip);
    }
  if (fo_region_before->clip != NULL)
    {
      g_object_unref (fo_region_before->clip);
    }
  fo_region_before->clip = new_clip;
  /*g_object_notify (G_OBJECT (fo_region_before), "clip");*/
}

/**
 * fo_region_before_get_display_align:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "display-align" property of @fo_fo.
 *
 * Return value: The "display-align" property value.
**/
FoProperty*
fo_region_before_get_display_align (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->display_align;
}

/**
 * fo_region_before_set_display_align:
 * @fo_fo: The #FoFo object.
 * @new_display_align: The new "display-align" property value.
 * 
 * Sets the "display-align" property of @fo_fo to @new_display_align.
 **/
void
fo_region_before_set_display_align (FoFo *fo_fo,
		         FoProperty *new_display_align)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_DISPLAY_ALIGN (new_display_align));

  if (new_display_align != NULL)
    {
      g_object_ref (new_display_align);
    }
  if (fo_region_before->display_align != NULL)
    {
      g_object_unref (fo_region_before->display_align);
    }
  fo_region_before->display_align = new_display_align;
  /*g_object_notify (G_OBJECT (fo_region_before), "display-align");*/
}

/**
 * fo_region_before_get_extent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "extent" property of @fo_fo.
 *
 * Return value: The "extent" property value.
**/
FoProperty*
fo_region_before_get_extent (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->extent;
}

/**
 * fo_region_before_set_extent:
 * @fo_fo: The #FoFo object.
 * @new_extent: The new "extent" property value.
 * 
 * Sets the "extent" property of @fo_fo to @new_extent.
 **/
void
fo_region_before_set_extent (FoFo *fo_fo,
		         FoProperty *new_extent)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_EXTENT (new_extent));

  if (new_extent != NULL)
    {
      g_object_ref (new_extent);
    }
  if (fo_region_before->extent != NULL)
    {
      g_object_unref (fo_region_before->extent);
    }
  fo_region_before->extent = new_extent;
  /*g_object_notify (G_OBJECT (fo_region_before), "extent");*/
}

/**
 * fo_region_before_get_overflow:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "overflow" property of @fo_fo.
 *
 * Return value: The "overflow" property value.
**/
FoProperty*
fo_region_before_get_overflow (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->overflow;
}

/**
 * fo_region_before_set_overflow:
 * @fo_fo: The #FoFo object.
 * @new_overflow: The new "overflow" property value.
 * 
 * Sets the "overflow" property of @fo_fo to @new_overflow.
 **/
void
fo_region_before_set_overflow (FoFo *fo_fo,
		         FoProperty *new_overflow)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_OVERFLOW (new_overflow));

  if (new_overflow != NULL)
    {
      g_object_ref (new_overflow);
    }
  if (fo_region_before->overflow != NULL)
    {
      g_object_unref (fo_region_before->overflow);
    }
  fo_region_before->overflow = new_overflow;
  /*g_object_notify (G_OBJECT (fo_region_before), "overflow");*/
}

/**
 * fo_region_before_get_padding_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-after" property of @fo_fo.
 *
 * Return value: The "padding-after" property value.
**/
FoProperty*
fo_region_before_get_padding_after (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->padding_after;
}

/**
 * fo_region_before_set_padding_after:
 * @fo_fo: The #FoFo object.
 * @new_padding_after: The new "padding-after" property value.
 * 
 * Sets the "padding-after" property of @fo_fo to @new_padding_after.
 **/
void
fo_region_before_set_padding_after (FoFo *fo_fo,
		         FoProperty *new_padding_after)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref (new_padding_after);
    }
  if (fo_region_before->padding_after != NULL)
    {
      g_object_unref (fo_region_before->padding_after);
    }
  fo_region_before->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_region_before), "padding-after");*/
}

/**
 * fo_region_before_get_padding_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-before" property of @fo_fo.
 *
 * Return value: The "padding-before" property value.
**/
FoProperty*
fo_region_before_get_padding_before (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->padding_before;
}

/**
 * fo_region_before_set_padding_before:
 * @fo_fo: The #FoFo object.
 * @new_padding_before: The new "padding-before" property value.
 * 
 * Sets the "padding-before" property of @fo_fo to @new_padding_before.
 **/
void
fo_region_before_set_padding_before (FoFo *fo_fo,
		         FoProperty *new_padding_before)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref (new_padding_before);
    }
  if (fo_region_before->padding_before != NULL)
    {
      g_object_unref (fo_region_before->padding_before);
    }
  fo_region_before->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_region_before), "padding-before");*/
}

/**
 * fo_region_before_get_padding_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-bottom" property of @fo_fo.
 *
 * Return value: The "padding-bottom" property value.
**/
FoProperty*
fo_region_before_get_padding_bottom (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->padding_bottom;
}

/**
 * fo_region_before_set_padding_bottom:
 * @fo_fo: The #FoFo object.
 * @new_padding_bottom: The new "padding-bottom" property value.
 * 
 * Sets the "padding-bottom" property of @fo_fo to @new_padding_bottom.
 **/
void
fo_region_before_set_padding_bottom (FoFo *fo_fo,
		         FoProperty *new_padding_bottom)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref (new_padding_bottom);
    }
  if (fo_region_before->padding_bottom != NULL)
    {
      g_object_unref (fo_region_before->padding_bottom);
    }
  fo_region_before->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_region_before), "padding-bottom");*/
}

/**
 * fo_region_before_get_padding_end:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-end" property of @fo_fo.
 *
 * Return value: The "padding-end" property value.
**/
FoProperty*
fo_region_before_get_padding_end (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->padding_end;
}

/**
 * fo_region_before_set_padding_end:
 * @fo_fo: The #FoFo object.
 * @new_padding_end: The new "padding-end" property value.
 * 
 * Sets the "padding-end" property of @fo_fo to @new_padding_end.
 **/
void
fo_region_before_set_padding_end (FoFo *fo_fo,
		         FoProperty *new_padding_end)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref (new_padding_end);
    }
  if (fo_region_before->padding_end != NULL)
    {
      g_object_unref (fo_region_before->padding_end);
    }
  fo_region_before->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_region_before), "padding-end");*/
}

/**
 * fo_region_before_get_padding_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-left" property of @fo_fo.
 *
 * Return value: The "padding-left" property value.
**/
FoProperty*
fo_region_before_get_padding_left (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->padding_left;
}

/**
 * fo_region_before_set_padding_left:
 * @fo_fo: The #FoFo object.
 * @new_padding_left: The new "padding-left" property value.
 * 
 * Sets the "padding-left" property of @fo_fo to @new_padding_left.
 **/
void
fo_region_before_set_padding_left (FoFo *fo_fo,
		         FoProperty *new_padding_left)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref (new_padding_left);
    }
  if (fo_region_before->padding_left != NULL)
    {
      g_object_unref (fo_region_before->padding_left);
    }
  fo_region_before->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_region_before), "padding-left");*/
}

/**
 * fo_region_before_get_padding_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-right" property of @fo_fo.
 *
 * Return value: The "padding-right" property value.
**/
FoProperty*
fo_region_before_get_padding_right (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->padding_right;
}

/**
 * fo_region_before_set_padding_right:
 * @fo_fo: The #FoFo object.
 * @new_padding_right: The new "padding-right" property value.
 * 
 * Sets the "padding-right" property of @fo_fo to @new_padding_right.
 **/
void
fo_region_before_set_padding_right (FoFo *fo_fo,
		         FoProperty *new_padding_right)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref (new_padding_right);
    }
  if (fo_region_before->padding_right != NULL)
    {
      g_object_unref (fo_region_before->padding_right);
    }
  fo_region_before->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_region_before), "padding-right");*/
}

/**
 * fo_region_before_get_padding_start:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-start" property of @fo_fo.
 *
 * Return value: The "padding-start" property value.
**/
FoProperty*
fo_region_before_get_padding_start (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->padding_start;
}

/**
 * fo_region_before_set_padding_start:
 * @fo_fo: The #FoFo object.
 * @new_padding_start: The new "padding-start" property value.
 * 
 * Sets the "padding-start" property of @fo_fo to @new_padding_start.
 **/
void
fo_region_before_set_padding_start (FoFo *fo_fo,
		         FoProperty *new_padding_start)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref (new_padding_start);
    }
  if (fo_region_before->padding_start != NULL)
    {
      g_object_unref (fo_region_before->padding_start);
    }
  fo_region_before->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_region_before), "padding-start");*/
}

/**
 * fo_region_before_get_padding_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-top" property of @fo_fo.
 *
 * Return value: The "padding-top" property value.
**/
FoProperty*
fo_region_before_get_padding_top (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->padding_top;
}

/**
 * fo_region_before_set_padding_top:
 * @fo_fo: The #FoFo object.
 * @new_padding_top: The new "padding-top" property value.
 * 
 * Sets the "padding-top" property of @fo_fo to @new_padding_top.
 **/
void
fo_region_before_set_padding_top (FoFo *fo_fo,
		         FoProperty *new_padding_top)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref (new_padding_top);
    }
  if (fo_region_before->padding_top != NULL)
    {
      g_object_unref (fo_region_before->padding_top);
    }
  fo_region_before->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_region_before), "padding-top");*/
}

/**
 * fo_region_before_get_region_name:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "region-name" property of @fo_fo.
 *
 * Return value: The "region-name" property value.
**/
FoProperty*
fo_region_before_get_region_name (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->region_name;
}

/**
 * fo_region_before_set_region_name:
 * @fo_fo: The #FoFo object.
 * @new_region_name: The new "region-name" property value.
 * 
 * Sets the "region-name" property of @fo_fo to @new_region_name.
 **/
void
fo_region_before_set_region_name (FoFo *fo_fo,
		         FoProperty *new_region_name)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_REGION_NAME (new_region_name));

  if (new_region_name != NULL)
    {
      g_object_ref (new_region_name);
    }
  if (fo_region_before->region_name != NULL)
    {
      g_object_unref (fo_region_before->region_name);
    }
  fo_region_before->region_name = new_region_name;
  /*g_object_notify (G_OBJECT (fo_region_before), "region-name");*/
}

/**
 * fo_region_before_get_writing_mode:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "writing-mode" property of @fo_fo.
 *
 * Return value: The "writing-mode" property value.
**/
FoProperty*
fo_region_before_get_writing_mode (FoFo *fo_fo)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_val_if_fail (fo_region_before != NULL, NULL);
  g_return_val_if_fail (FO_IS_REGION_BEFORE (fo_region_before), NULL);

  return fo_region_before->writing_mode;
}

/**
 * fo_region_before_set_writing_mode:
 * @fo_fo: The #FoFo object.
 * @new_writing_mode: The new "writing-mode" property value.
 * 
 * Sets the "writing-mode" property of @fo_fo to @new_writing_mode.
 **/
void
fo_region_before_set_writing_mode (FoFo *fo_fo,
		         FoProperty *new_writing_mode)
{
  FoRegionBefore *fo_region_before = (FoRegionBefore *) fo_fo;

  g_return_if_fail (fo_region_before != NULL);
  g_return_if_fail (FO_IS_REGION_BEFORE (fo_region_before));
  g_return_if_fail (FO_IS_PROPERTY_WRITING_MODE (new_writing_mode));

  if (new_writing_mode != NULL)
    {
      g_object_ref (new_writing_mode);
    }
  if (fo_region_before->writing_mode != NULL)
    {
      g_object_unref (fo_region_before->writing_mode);
    }
  fo_region_before->writing_mode = new_writing_mode;
  /*g_object_notify (G_OBJECT (fo_region_before), "writing-mode");*/
}
