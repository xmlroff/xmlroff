/* Fo
 * fo-block.c: 'block' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-block-fo-private.h"
#include "fo/fo-block-private.h"
#include "fo/fo-inline-fo.h"
#include "fo/fo-neutral-fo.h"
#include "fo-context-util.h"
#include "fo/fo-wrapper.h"
#include "fo/fo-text.h"
#include "fo/fo-block-area.h"
#include "fo/fo-block-block.h"
#include "fo/fo-block-layout.h"
#include "fo/fo-block-whitespace.h"
#include "fo/fo-wrapper-block.h"
#include "fo/fo-wrapper-inline.h"
#include "fo/fo-wrapper-inline-empty.h"
#include "fo/fo-wrapper-whitespace.h"
#include "property/fo-property-border.h"
#include "property/fo-property-margin.h"
#include "property/fo-property-padding.h"
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
#include "property/fo-property-break-after.h"
#include "property/fo-property-break-before.h"
#include "property/fo-property-color.h"
#include "property/fo-property-end-indent.h"
#include "property/fo-property-font-family.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-stretch.h"
#include "property/fo-property-font-style.h"
#include "property/fo-property-font-variant.h"
#include "property/fo-property-font-weight.h"
#include "property/fo-property-id.h"
#include "property/fo-property-keep-together.h"
#include "property/fo-property-keep-together-within-column.h"
#include "property/fo-property-keep-together-within-line.h"
#include "property/fo-property-keep-together-within-page.h"
#include "property/fo-property-keep-with-next.h"
#include "property/fo-property-keep-with-next-within-column.h"
#include "property/fo-property-keep-with-next-within-line.h"
#include "property/fo-property-keep-with-next-within-page.h"
#include "property/fo-property-keep-with-previous.h"
#include "property/fo-property-keep-with-previous-within-column.h"
#include "property/fo-property-keep-with-previous-within-line.h"
#include "property/fo-property-keep-with-previous-within-page.h"
#include "property/fo-property-line-height.h"
#include "property/fo-property-line-stacking-strategy.h"
#include "property/fo-property-linefeed-treatment.h"
#include "property/fo-property-margin-bottom.h"
#include "property/fo-property-margin-left.h"
#include "property/fo-property-margin-right.h"
#include "property/fo-property-margin-top.h"
#include "property/fo-property-orphans.h"
#include "property/fo-property-padding-after.h"
#include "property/fo-property-padding-before.h"
#include "property/fo-property-padding-bottom.h"
#include "property/fo-property-padding-end.h"
#include "property/fo-property-padding-left.h"
#include "property/fo-property-padding-right.h"
#include "property/fo-property-padding-start.h"
#include "property/fo-property-padding-top.h"
#include "property/fo-property-role.h"
#include "property/fo-property-source-document.h"
#include "property/fo-property-space-after.h"
#include "property/fo-property-space-before.h"
#include "property/fo-property-span.h"
#include "property/fo-property-start-indent.h"
#include "property/fo-property-text-align.h"
#include "property/fo-property-text-indent.h"
#include "property/fo-property-white-space-collapse.h"
#include "property/fo-property-white-space-treatment.h"
#include "property/fo-property-widows.h"
#include "property/fo-property-wrap-option.h"

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
  PROP_BREAK_AFTER,
  PROP_BREAK_BEFORE,
  PROP_COLOR,
  PROP_END_INDENT,
  PROP_FONT_FAMILY,
  PROP_FONT_SIZE,
  PROP_FONT_STRETCH,
  PROP_FONT_STYLE,
  PROP_FONT_VARIANT,
  PROP_FONT_WEIGHT,
  PROP_ID,
  PROP_KEEP_TOGETHER,
  PROP_KEEP_TOGETHER_WITHIN_COLUMN,
  PROP_KEEP_TOGETHER_WITHIN_LINE,
  PROP_KEEP_TOGETHER_WITHIN_PAGE,
  PROP_KEEP_WITH_NEXT,
  PROP_KEEP_WITH_NEXT_WITHIN_COLUMN,
  PROP_KEEP_WITH_NEXT_WITHIN_LINE,
  PROP_KEEP_WITH_NEXT_WITHIN_PAGE,
  PROP_KEEP_WITH_PREVIOUS,
  PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN,
  PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE,
  PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE,
  PROP_LINE_HEIGHT,
  PROP_LINE_STACKING_STRATEGY,
  PROP_LINEFEED_TREATMENT,
  PROP_MARGIN_BOTTOM,
  PROP_MARGIN_LEFT,
  PROP_MARGIN_RIGHT,
  PROP_MARGIN_TOP,
  PROP_ORPHANS,
  PROP_PADDING_AFTER,
  PROP_PADDING_BEFORE,
  PROP_PADDING_BOTTOM,
  PROP_PADDING_END,
  PROP_PADDING_LEFT,
  PROP_PADDING_RIGHT,
  PROP_PADDING_START,
  PROP_PADDING_TOP,
  PROP_ROLE,
  PROP_SOURCE_DOCUMENT,
  PROP_SPACE_AFTER,
  PROP_SPACE_BEFORE,
  PROP_SPAN,
  PROP_START_INDENT,
  PROP_TEXT_ALIGN,
  PROP_TEXT_INDENT,
  PROP_WHITE_SPACE_COLLAPSE,
  PROP_WHITE_SPACE_TREATMENT,
  PROP_WIDOWS,
  PROP_WRAP_OPTION
};

static void fo_block_base_class_init  (FoBlockClass *klass);
static void fo_block_class_init  (FoBlockClass *klass);
static void fo_block_block_fo_init (FoBlockFoIface *iface);
static void fo_block_get_property (GObject      *object,
                                   guint         prop_id,
                                   GValue       *value,
                                   GParamSpec   *pspec);
static void fo_block_set_property (GObject      *object,
                                   guint         prop_id,
                                   const GValue *value,
                                   GParamSpec   *pspec);
static void fo_block_finalize    (GObject           *object);
static gboolean fo_block_validate_content (FoFo    *fo,
                                           GError **error);
static void fo_block_validate (FoFo      *fo,
                               FoContext *current_context,
                               FoContext *parent_context,
                               GError   **error);
static void fo_block_update_from_context (FoFo      *fo,
                                          FoContext *context);
static void fo_block_debug_dump_properties (FoFo *fo,
                                            gint  depth);

static gpointer parent_class;

/**
 * fo_block_get_type:
 * 
 * Register the #FoBlock object type.
 * 
 * Return value: #GType value of the #FoBlock object type.
 **/
GType
fo_block_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoBlockClass),
        (GBaseInitFunc) fo_block_base_class_init,
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_block_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoBlock),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_block_fo_info =
      {
	(GInterfaceInitFunc) fo_block_block_fo_init,	 /* interface_init */
	NULL,			                         /* interface_finalize */
	NULL			                         /* interface_data */
      };

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "FoBlock",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_BLOCK_FO,
                                   &fo_block_fo_info);
    }

  return object_type;
}

/**
 * fo_block_base_class_init:
 * @klass: #FoBlockClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoBlockClass.
 **/
void
fo_block_base_class_init (FoBlockClass *klass)
{
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  fo_fo_class->debug_dump_properties = fo_block_debug_dump_properties;
  fo_fo_class->update_from_context = fo_block_update_from_context;
  fo_fo_class->validate_content = fo_block_validate_content;
  fo_fo_class->validate2 = fo_block_validate;
  fo_fo_class->area_new = fo_block_area_new3;
  fo_fo_class->area_new2 = fo_block_area_new2;
  fo_fo_class->allow_mixed_content = TRUE;
}

/**
 * fo_block_class_init:
 * @klass: #FoBlockClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoBlockClass.
 **/
void
fo_block_class_init (FoBlockClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_block_finalize;

  object_class->get_property = fo_block_get_property;
  object_class->set_property = fo_block_set_property;

  /* Class functions are set in fo_block_base_class_init() */

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
     PROP_BREAK_AFTER,
     g_param_spec_object ("break-after",
			  _("Break After"),
			  _("Break After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BREAK_BEFORE,
     g_param_spec_object ("break-before",
			  _("Break Before"),
			  _("Break Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_COLOR,
     g_param_spec_object ("color",
			  _("Color"),
			  _("Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_END_INDENT,
     g_param_spec_object ("end-indent",
			  _("End Indent"),
			  _("End Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_FAMILY,
     g_param_spec_object ("font-family",
			  _("Font Family"),
			  _("Font Family property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_SIZE,
     g_param_spec_object ("font-size",
			  _("Font Size"),
			  _("Font Size property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_STRETCH,
     g_param_spec_object ("font-stretch",
			  _("Font Stretch"),
			  _("Font Stretch property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_STYLE,
     g_param_spec_object ("font-style",
			  _("Font Style"),
			  _("Font Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_VARIANT,
     g_param_spec_object ("font-variant",
			  _("Font Variant"),
			  _("Font Variant property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_WEIGHT,
     g_param_spec_object ("font-weight",
			  _("Font Weight"),
			  _("Font Weight property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER,
     g_param_spec_object ("keep-together",
			  _("Keep Together"),
			  _("Keep Together property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_COLUMN,
     g_param_spec_object ("keep-together-within-column",
			  _("Keep Together Within Column"),
			  _("Keep Together Within Column property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_LINE,
     g_param_spec_object ("keep-together-within-line",
			  _("Keep Together Within Line"),
			  _("Keep Together Within Line property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_TOGETHER_WITHIN_PAGE,
     g_param_spec_object ("keep-together-within-page",
			  _("Keep Together Within Page"),
			  _("Keep Together Within Page property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_NEXT,
     g_param_spec_object ("keep-with-next",
			  _("Keep With Next"),
			  _("Keep With Next property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_NEXT_WITHIN_COLUMN,
     g_param_spec_object ("keep-with-next-within-column",
			  _("Keep With Next Within Column"),
			  _("Keep With Next Within Column property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_NEXT_WITHIN_LINE,
     g_param_spec_object ("keep-with-next-within-line",
			  _("Keep With Next Within Line"),
			  _("Keep With Next Within Line property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_NEXT_WITHIN_PAGE,
     g_param_spec_object ("keep-with-next-within-page",
			  _("Keep With Next Within Page"),
			  _("Keep With Next Within Page property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_PREVIOUS,
     g_param_spec_object ("keep-with-previous",
			  _("Keep With Previous"),
			  _("Keep With Previous property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN,
     g_param_spec_object ("keep-with-previous-within-column",
			  _("Keep With Previous Within Column"),
			  _("Keep With Previous Within Column property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE,
     g_param_spec_object ("keep-with-previous-within-line",
			  _("Keep With Previous Within Line"),
			  _("Keep With Previous Within Line property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE,
     g_param_spec_object ("keep-with-previous-within-page",
			  _("Keep With Previous Within Page"),
			  _("Keep With Previous Within Page property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_LINE_HEIGHT,
     g_param_spec_object ("line-height",
			  _("Line Height"),
			  _("Line Height property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_LINE_STACKING_STRATEGY,
     g_param_spec_object ("line-stacking-strategy",
			  _("Line Stacking Strategy"),
			  _("Line Stacking Strategy property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_LINEFEED_TREATMENT,
     g_param_spec_object ("linefeed-treatment",
			  _("Linefeed Treatment"),
			  _("Linefeed Treatment property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_BOTTOM,
     g_param_spec_object ("margin-bottom",
			  _("Margin Bottom"),
			  _("Margin Bottom property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_LEFT,
     g_param_spec_object ("margin-left",
			  _("Margin Left"),
			  _("Margin Left property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_RIGHT,
     g_param_spec_object ("margin-right",
			  _("Margin Right"),
			  _("Margin Right property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_TOP,
     g_param_spec_object ("margin-top",
			  _("Margin Top"),
			  _("Margin Top property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ORPHANS,
     g_param_spec_object ("orphans",
			  _("Orphans"),
			  _("Orphans property"),
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
     PROP_ROLE,
     g_param_spec_object ("role",
			  _("Role"),
			  _("Role property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SOURCE_DOCUMENT,
     g_param_spec_object ("source-document",
			  _("Source Document"),
			  _("Source Document property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_AFTER,
     g_param_spec_object ("space-after",
			  _("Space After"),
			  _("Space After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_BEFORE,
     g_param_spec_object ("space-before",
			  _("Space Before"),
			  _("Space Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPAN,
     g_param_spec_object ("span",
			  _("Span"),
			  _("Span property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_START_INDENT,
     g_param_spec_object ("start-indent",
			  _("Start Indent"),
			  _("Start Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_TEXT_ALIGN,
     g_param_spec_object ("text-align",
			  _("Text Align"),
			  _("Text Align property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_TEXT_INDENT,
     g_param_spec_object ("text-indent",
			  _("Text Indent"),
			  _("Text Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WHITE_SPACE_COLLAPSE,
     g_param_spec_object ("white-space-collapse",
			  _("White Space Collapse"),
			  _("White Space Collapse property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WHITE_SPACE_TREATMENT,
     g_param_spec_object ("white-space-treatment",
			  _("White Space Treatment"),
			  _("White Space Treatment property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WIDOWS,
     g_param_spec_object ("widows",
			  _("Widows"),
			  _("Widows property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WRAP_OPTION,
     g_param_spec_object ("wrap-option",
			  _("Wrap Option"),
			  _("Wrap Option property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_block_block_fo_init:
 * @iface: #FoBlockFoIFace structure for this class.
 * 
 * Initialize #FoBlockFoIface interface for this class.
 **/
void
fo_block_block_fo_init (FoBlockFoIface *iface)
{
  iface->get_background_color = fo_block_get_background_color;
  iface->get_border_after_color = fo_block_get_border_after_color;
  iface->get_border_after_style = fo_block_get_border_after_style;
  iface->get_border_after_width = fo_block_get_border_after_width;
  iface->get_border_before_color = fo_block_get_border_before_color;
  iface->get_border_before_style = fo_block_get_border_before_style;
  iface->get_border_before_width = fo_block_get_border_before_width;
  iface->get_border_end_color = fo_block_get_border_end_color;
  iface->get_border_end_style = fo_block_get_border_end_style;
  iface->get_border_end_width = fo_block_get_border_end_width;
  iface->get_border_start_color = fo_block_get_border_start_color;
  iface->get_border_start_style = fo_block_get_border_start_style;
  iface->get_border_start_width = fo_block_get_border_start_width;
  iface->get_keep_with_previous = fo_block_get_keep_with_previous;
  iface->get_keep_with_next = fo_block_get_keep_with_next;
  iface->get_keep_together = fo_block_get_keep_together;
  iface->get_padding_after = fo_block_get_padding_after;
  iface->get_padding_before = fo_block_get_padding_before;
  iface->get_padding_end = fo_block_get_padding_end;
  iface->get_padding_start = fo_block_get_padding_start;
  iface->get_space_before = fo_block_get_space_before;
  iface->get_space_after = fo_block_get_space_after;
  iface->get_start_indent = fo_block_get_start_indent;
  iface->get_end_indent = fo_block_get_end_indent;
}

/**
 * fo_block_finalize:
 * @object: #FoBlock object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoBlock.
 **/
void
fo_block_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_block_set_background_color (fo, NULL);
  fo_block_set_background_image (fo, NULL);
  fo_block_set_border_after_color (fo, NULL);
  fo_block_set_border_after_style (fo, NULL);
  fo_block_set_border_after_width (fo, NULL);
  fo_block_set_border_before_color (fo, NULL);
  fo_block_set_border_before_style (fo, NULL);
  fo_block_set_border_before_width (fo, NULL);
  fo_block_set_border_bottom_color (fo, NULL);
  fo_block_set_border_bottom_style (fo, NULL);
  fo_block_set_border_bottom_width (fo, NULL);
  fo_block_set_border_end_color (fo, NULL);
  fo_block_set_border_end_style (fo, NULL);
  fo_block_set_border_end_width (fo, NULL);
  fo_block_set_border_left_color (fo, NULL);
  fo_block_set_border_left_style (fo, NULL);
  fo_block_set_border_left_width (fo, NULL);
  fo_block_set_border_right_color (fo, NULL);
  fo_block_set_border_right_style (fo, NULL);
  fo_block_set_border_right_width (fo, NULL);
  fo_block_set_border_start_color (fo, NULL);
  fo_block_set_border_start_style (fo, NULL);
  fo_block_set_border_start_width (fo, NULL);
  fo_block_set_border_top_color (fo, NULL);
  fo_block_set_border_top_style (fo, NULL);
  fo_block_set_border_top_width (fo, NULL);
  fo_block_set_break_after (fo, NULL);
  fo_block_set_break_before (fo, NULL);
  fo_block_set_color (fo, NULL);
  fo_block_set_end_indent (fo, NULL);
  fo_block_set_font_family (fo, NULL);
  fo_block_set_font_size (fo, NULL);
  fo_block_set_font_stretch (fo, NULL);
  fo_block_set_font_style (fo, NULL);
  fo_block_set_font_variant (fo, NULL);
  fo_block_set_font_weight (fo, NULL);
  fo_block_set_id (fo, NULL);
  fo_block_set_keep_together (fo, NULL);
  fo_block_set_keep_together_within_column (fo, NULL);
  fo_block_set_keep_together_within_line (fo, NULL);
  fo_block_set_keep_together_within_page (fo, NULL);
  fo_block_set_keep_with_next (fo, NULL);
  fo_block_set_keep_with_next_within_column (fo, NULL);
  fo_block_set_keep_with_next_within_line (fo, NULL);
  fo_block_set_keep_with_next_within_page (fo, NULL);
  fo_block_set_keep_with_previous (fo, NULL);
  fo_block_set_keep_with_previous_within_column (fo, NULL);
  fo_block_set_keep_with_previous_within_line (fo, NULL);
  fo_block_set_keep_with_previous_within_page (fo, NULL);
  fo_block_set_line_height (fo, NULL);
  fo_block_set_line_stacking_strategy (fo, NULL);
  fo_block_set_linefeed_treatment (fo, NULL);
  fo_block_set_margin_bottom (fo, NULL);
  fo_block_set_margin_left (fo, NULL);
  fo_block_set_margin_right (fo, NULL);
  fo_block_set_margin_top (fo, NULL);
  fo_block_set_orphans (fo, NULL);
  fo_block_set_padding_after (fo, NULL);
  fo_block_set_padding_before (fo, NULL);
  fo_block_set_padding_bottom (fo, NULL);
  fo_block_set_padding_end (fo, NULL);
  fo_block_set_padding_left (fo, NULL);
  fo_block_set_padding_right (fo, NULL);
  fo_block_set_padding_start (fo, NULL);
  fo_block_set_padding_top (fo, NULL);
  fo_block_set_role (fo, NULL);
  fo_block_set_source_document (fo, NULL);
  fo_block_set_space_after (fo, NULL);
  fo_block_set_space_before (fo, NULL);
  fo_block_set_span (fo, NULL);
  fo_block_set_start_indent (fo, NULL);
  fo_block_set_text_align (fo, NULL);
  fo_block_set_text_indent (fo, NULL);
  fo_block_set_white_space_collapse (fo, NULL);
  fo_block_set_white_space_treatment (fo, NULL);
  fo_block_set_widows (fo, NULL);
  fo_block_set_wrap_option (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_block_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoBlock.
 **/
void
fo_block_get_property (GObject    *object,
                       guint       prop_id,
                       GValue     *value,
                       GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_background_color (fo_fo)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_block_get_background_image (fo_fo)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_after_color (fo_fo)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_after_style (fo_fo)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_after_width (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_before_color (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_before_style (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_before_width (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_bottom_color (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_bottom_style (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_bottom_width (fo_fo)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_end_color (fo_fo)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_end_style (fo_fo)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_end_width (fo_fo)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_left_color (fo_fo)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_left_style (fo_fo)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_left_width (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_right_color (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_right_style (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_right_width (fo_fo)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_start_color (fo_fo)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_start_style (fo_fo)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_start_width (fo_fo)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_top_color (fo_fo)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_top_style (fo_fo)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_block_get_border_top_width (fo_fo)));
      break;
    case PROP_BREAK_AFTER:
      g_value_set_object (value, G_OBJECT (fo_block_get_break_after (fo_fo)));
      break;
    case PROP_BREAK_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_block_get_break_before (fo_fo)));
      break;
    case PROP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_block_get_color (fo_fo)));
      break;
    case PROP_END_INDENT:
      g_value_set_object (value, G_OBJECT (fo_block_get_end_indent (fo_fo)));
      break;
    case PROP_FONT_FAMILY:
      g_value_set_object (value, G_OBJECT (fo_block_get_font_family (fo_fo)));
      break;
    case PROP_FONT_SIZE:
      g_value_set_object (value, G_OBJECT (fo_block_get_font_size (fo_fo)));
      break;
    case PROP_FONT_STRETCH:
      g_value_set_object (value, G_OBJECT (fo_block_get_font_stretch (fo_fo)));
      break;
    case PROP_FONT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_font_style (fo_fo)));
      break;
    case PROP_FONT_VARIANT:
      g_value_set_object (value, G_OBJECT (fo_block_get_font_variant (fo_fo)));
      break;
    case PROP_FONT_WEIGHT:
      g_value_set_object (value, G_OBJECT (fo_block_get_font_weight (fo_fo)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_block_get_id (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_together (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_together_within_column (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_together_within_line (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_together_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_with_next (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_with_next_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_with_next_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_with_next_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_with_previous (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_with_previous_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_with_previous_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_block_get_keep_with_previous_within_page (fo_fo)));
      break;
    case PROP_LINE_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_block_get_line_height (fo_fo)));
      break;
    case PROP_LINE_STACKING_STRATEGY:
      g_value_set_object (value, G_OBJECT (fo_block_get_line_stacking_strategy (fo_fo)));
      break;
    case PROP_LINEFEED_TREATMENT:
      g_value_set_object (value, G_OBJECT (fo_block_get_linefeed_treatment (fo_fo)));
      break;
    case PROP_MARGIN_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_block_get_margin_bottom (fo_fo)));
      break;
    case PROP_MARGIN_LEFT:
      g_value_set_object (value, G_OBJECT (fo_block_get_margin_left (fo_fo)));
      break;
    case PROP_MARGIN_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_block_get_margin_right (fo_fo)));
      break;
    case PROP_MARGIN_TOP:
      g_value_set_object (value, G_OBJECT (fo_block_get_margin_top (fo_fo)));
      break;
    case PROP_ORPHANS:
      g_value_set_object (value, G_OBJECT (fo_block_get_orphans (fo_fo)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_block_get_padding_after (fo_fo)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_block_get_padding_before (fo_fo)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_block_get_padding_bottom (fo_fo)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_block_get_padding_end (fo_fo)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_block_get_padding_left (fo_fo)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_block_get_padding_right (fo_fo)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_block_get_padding_start (fo_fo)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_block_get_padding_top (fo_fo)));
      break;
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_block_get_role (fo_fo)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_block_get_source_document (fo_fo)));
      break;
    case PROP_SPACE_AFTER:
      g_value_set_object (value, G_OBJECT (fo_block_get_space_after (fo_fo)));
      break;
    case PROP_SPACE_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_block_get_space_before (fo_fo)));
      break;
    case PROP_SPAN:
      g_value_set_object (value, G_OBJECT (fo_block_get_span (fo_fo)));
      break;
    case PROP_START_INDENT:
      g_value_set_object (value, G_OBJECT (fo_block_get_start_indent (fo_fo)));
      break;
    case PROP_TEXT_ALIGN:
      g_value_set_object (value, G_OBJECT (fo_block_get_text_align (fo_fo)));
      break;
    case PROP_TEXT_INDENT:
      g_value_set_object (value, G_OBJECT (fo_block_get_text_indent (fo_fo)));
      break;
    case PROP_WHITE_SPACE_COLLAPSE:
      g_value_set_object (value, G_OBJECT (fo_block_get_white_space_collapse (fo_fo)));
      break;
    case PROP_WHITE_SPACE_TREATMENT:
      g_value_set_object (value, G_OBJECT (fo_block_get_white_space_treatment (fo_fo)));
      break;
    case PROP_WIDOWS:
      g_value_set_object (value, G_OBJECT (fo_block_get_widows (fo_fo)));
      break;
    case PROP_WRAP_OPTION:
      g_value_set_object (value, G_OBJECT (fo_block_get_wrap_option (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_block_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoBlock.
 **/
void
fo_block_set_property (GObject      *object,
                       guint         prop_id,
                       const GValue *value,
                       GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_BACKGROUND_COLOR:
      fo_block_set_background_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_block_set_background_image (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_block_set_border_after_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_block_set_border_after_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_block_set_border_after_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_block_set_border_before_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_block_set_border_before_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_block_set_border_before_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_block_set_border_bottom_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_block_set_border_bottom_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_block_set_border_bottom_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_block_set_border_end_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_block_set_border_end_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_block_set_border_end_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_block_set_border_left_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_block_set_border_left_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_block_set_border_left_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_block_set_border_right_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_block_set_border_right_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_block_set_border_right_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_block_set_border_start_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_block_set_border_start_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_block_set_border_start_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_block_set_border_top_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_block_set_border_top_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_block_set_border_top_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BREAK_AFTER:
      fo_block_set_break_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_BREAK_BEFORE:
      fo_block_set_break_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_COLOR:
      fo_block_set_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_END_INDENT:
      fo_block_set_end_indent (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_FAMILY:
      fo_block_set_font_family (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_SIZE:
      fo_block_set_font_size (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_STRETCH:
      fo_block_set_font_stretch (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_STYLE:
      fo_block_set_font_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_VARIANT:
      fo_block_set_font_variant (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_WEIGHT:
      fo_block_set_font_weight (fo_fo, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_block_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER:
      fo_block_set_keep_together (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      fo_block_set_keep_together_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      fo_block_set_keep_together_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      fo_block_set_keep_together_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT:
      fo_block_set_keep_with_next (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      fo_block_set_keep_with_next_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      fo_block_set_keep_with_next_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      fo_block_set_keep_with_next_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      fo_block_set_keep_with_previous (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      fo_block_set_keep_with_previous_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      fo_block_set_keep_with_previous_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      fo_block_set_keep_with_previous_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_LINE_HEIGHT:
      fo_block_set_line_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_LINE_STACKING_STRATEGY:
      fo_block_set_line_stacking_strategy (fo_fo, g_value_get_object (value));
      break;
    case PROP_LINEFEED_TREATMENT:
      fo_block_set_linefeed_treatment (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_BOTTOM:
      fo_block_set_margin_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_LEFT:
      fo_block_set_margin_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_RIGHT:
      fo_block_set_margin_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_TOP:
      fo_block_set_margin_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_ORPHANS:
      fo_block_set_orphans (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_block_set_padding_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_block_set_padding_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_block_set_padding_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_block_set_padding_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_block_set_padding_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_block_set_padding_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_block_set_padding_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_block_set_padding_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_ROLE:
      fo_block_set_role (fo_fo, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_block_set_source_document (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER:
      fo_block_set_space_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE:
      fo_block_set_space_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPAN:
      fo_block_set_span (fo_fo, g_value_get_object (value));
      break;
    case PROP_START_INDENT:
      fo_block_set_start_indent (fo_fo, g_value_get_object (value));
      break;
    case PROP_TEXT_ALIGN:
      fo_block_set_text_align (fo_fo, g_value_get_object (value));
      break;
    case PROP_TEXT_INDENT:
      fo_block_set_text_indent (fo_fo, g_value_get_object (value));
      break;
    case PROP_WHITE_SPACE_COLLAPSE:
      fo_block_set_white_space_collapse (fo_fo, g_value_get_object (value));
      break;
    case PROP_WHITE_SPACE_TREATMENT:
      fo_block_set_white_space_treatment (fo_fo, g_value_get_object (value));
      break;
    case PROP_WIDOWS:
      fo_block_set_widows (fo_fo, g_value_get_object (value));
      break;
    case PROP_WRAP_OPTION:
      fo_block_set_wrap_option (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_block_new:
 * 
 * Creates a new #FoBlock initialized to default value.
 * 
 * Return value: the new #FoBlock.
 **/
FoFo*
fo_block_new (void)
{
  return FO_FO (g_object_new (fo_block_get_type (),
                              NULL));
}

/**
 * fo_block_validate_content:
 * @fo:    #FoBlock object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
fo_block_validate_content (FoFo    *fo,
                           GError **error)
{
  GError *tmp_error;
  gboolean parent_result = FALSE;
  gboolean is_not_pcdata_inline_block_neutral = FALSE;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_BLOCK (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  parent_result = FO_FO_CLASS (parent_class)->validate_content (fo, error);

  if (parent_result == TRUE)
    {
      return parent_result;
    }

  /* FIXME: doesn't account for markers or initial-property-set */
  fo_node_children_foreach (FO_NODE (fo),
			    G_TRAVERSE_ALL,
			    fo_fo_validate_pcdata_inline_block_neutral,
			    &is_not_pcdata_inline_block_neutral);

  if (is_not_pcdata_inline_block_neutral)
    {
      tmp_error = g_error_new (FO_FO_ERROR,
			       1,
			       "FO children do not match allowed content");

      return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					       error,
					       tmp_error);
    }

  if (fo_node_n_children (FO_NODE (fo)) != 0)
    {
      FoNode *child_node = fo_node_first_child (FO_NODE (fo));
      FoFo *use_parent = fo;

      while (child_node)
	{
	  FoNode *next_node = fo_node_next_sibling (child_node);

	  if ((FO_IS_TEXT (child_node) &&
	       fo_text_get_whitespace_only (FO_FO (child_node))) ||
	      FO_IS_WRAPPER_WHITESPACE (child_node))
	    {
	      if (FO_IS_BLOCK_LAYOUT (use_parent))
		{
		  child_node = next_node;
		  continue;
		}
	      else if (!FO_IS_BLOCK_WHITESPACE (use_parent))
		{
		  FoFo *new_parent;

		  if (next_node &&
		      (FO_IS_INLINE_FO (next_node) ||
		       FO_IS_WRAPPER_INLINE (next_node)))
		    {
		      new_parent = fo_block_layout_new ();
		    }
		  else
		    {
		      new_parent = fo_block_whitespace_new ();
		    }

		  fo_fo_set_element (new_parent,
				     fo_fo_get_element (use_parent));

		  fo_node_insert_after (fo_node_parent (FO_NODE (use_parent)),
					FO_NODE (use_parent),
					FO_NODE (new_parent));

		  fo_node_unlink_with_next_siblings (child_node);
		  fo_node_insert_with_next_siblings (FO_NODE (new_parent),
						     0,
						     child_node);
		  use_parent = new_parent;
		}
	    }
	  else if (FO_IS_INLINE_FO (child_node) ||
		   FO_IS_WRAPPER_INLINE (child_node))
	    {
	      if (!FO_IS_BLOCK_LAYOUT (use_parent))
		{
		  FoFo *new_parent = fo_block_layout_new ();
		  fo_fo_set_element (new_parent,
				     fo_fo_get_element (use_parent));

		  fo_node_insert_after (fo_node_parent (FO_NODE (use_parent)),
					FO_NODE (use_parent),
					FO_NODE (new_parent));

		  fo_node_unlink_with_next_siblings (child_node);
		  fo_node_insert_with_next_siblings (FO_NODE (new_parent),
						     0,
						     child_node);
		  use_parent = new_parent;
		}
	    }
	  else if (FO_IS_BLOCK_FO (child_node) ||
		   FO_IS_WRAPPER_BLOCK (child_node))
	    {
	      if (!FO_IS_BLOCK_BLOCK (use_parent))
		{
		  FoFo *new_parent = fo_block_block_new ();
		  fo_fo_set_element (new_parent,
				     fo_fo_get_element (use_parent));

		  fo_node_insert_after (fo_node_parent (FO_NODE (use_parent)),
					FO_NODE (use_parent),
					FO_NODE (new_parent));

		  fo_node_unlink_with_next_siblings (child_node);
		  fo_node_insert_with_next_siblings (FO_NODE (new_parent),
						     0,
						     child_node);
		  use_parent = new_parent;
		}
	    }
	  else if (FO_IS_WRAPPER (child_node))
	    {
	      FoFo *new_child = fo_wrapper_inline_empty_new ();
	      fo_fo_update_after_clone (new_child,
					FO_FO (child_node));
	      fo_node_insert_after (FO_NODE (use_parent),
				    child_node,
				    FO_NODE (new_child));
	      fo_node_unlink (child_node);
	      g_object_unref (child_node);

	      child_node = FO_NODE (new_child);

	      if (!FO_IS_BLOCK_LAYOUT (use_parent))
		{
		  FoFo *new_parent = fo_block_layout_new ();
		  fo_fo_set_element (new_parent,
				     fo_fo_get_element (use_parent));

		  fo_node_insert_after (fo_node_parent (FO_NODE (use_parent)),
					FO_NODE (use_parent),
					FO_NODE (new_parent));

		  fo_node_unlink_with_next_siblings (child_node);
		  fo_node_insert_with_next_siblings (FO_NODE (new_parent),
						     0,
						     child_node);
		  use_parent = new_parent;
		}
	    }
	  else
	    {
	      tmp_error = g_error_new (FO_FO_ERROR,
				       1,
				       "Cannot rewrite fo:block content.");

	      return fo_object_log_or_propagate_error (FO_OBJECT (fo),
						       error,
						       tmp_error);
	    }

	  child_node = next_node;
	}

      g_assert (fo_node_n_children (FO_NODE (fo)) == 0);
      fo_node_unlink (FO_NODE (fo));
      g_object_unref (fo);
    }
  return FALSE;
}

/**
 * fo_block_validate:
 * @fo:              #FoBlock object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_block_validate (FoFo      *fo,
                   FoContext *current_context,
                   FoContext *parent_context,
                   GError   **error)
{
  FoBlock *fo_block;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_block = FO_BLOCK (fo);

  fo_context_util_keeps_resolve (current_context, parent_context);
  fo_context_util_border_resolve (current_context, parent_context);
  fo_context_util_paddings_resolve (current_context, parent_context);
  fo_context_util_margins_indents_resolve (fo,
					   current_context,
					   parent_context);
  fo_context_util_margins_resolve (current_context, parent_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_block_set_line_height (fo,
			    fo_property_line_height_resolve (fo_block->line_height,
							     fo_block->font_size));
  fo_fo_register_id (fo,
		     fo_property_get_value (fo_block->id));
  FO_FO_CLASS (parent_class)->validate (fo, current_context, parent_context);
}

/**
 * fo_block_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_block_update_from_context (FoFo      *fo,
                              FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_block_set_background_color (fo,
			  fo_context_get_background_color (context));
  fo_block_set_background_image (fo,
			  fo_context_get_background_image (context));
  fo_block_set_border_after_color (fo,
			  fo_context_get_border_after_color (context));
  fo_block_set_border_after_style (fo,
			  fo_context_get_border_after_style (context));
  fo_block_set_border_after_width (fo,
			  fo_context_get_border_after_width (context));
  fo_block_set_border_before_color (fo,
			  fo_context_get_border_before_color (context));
  fo_block_set_border_before_style (fo,
			  fo_context_get_border_before_style (context));
  fo_block_set_border_before_width (fo,
			  fo_context_get_border_before_width (context));
  fo_block_set_border_bottom_color (fo,
			  fo_context_get_border_bottom_color (context));
  fo_block_set_border_bottom_style (fo,
			  fo_context_get_border_bottom_style (context));
  fo_block_set_border_bottom_width (fo,
			  fo_context_get_border_bottom_width (context));
  fo_block_set_border_end_color (fo,
			  fo_context_get_border_end_color (context));
  fo_block_set_border_end_style (fo,
			  fo_context_get_border_end_style (context));
  fo_block_set_border_end_width (fo,
			  fo_context_get_border_end_width (context));
  fo_block_set_border_left_color (fo,
			  fo_context_get_border_left_color (context));
  fo_block_set_border_left_style (fo,
			  fo_context_get_border_left_style (context));
  fo_block_set_border_left_width (fo,
			  fo_context_get_border_left_width (context));
  fo_block_set_border_right_color (fo,
			  fo_context_get_border_right_color (context));
  fo_block_set_border_right_style (fo,
			  fo_context_get_border_right_style (context));
  fo_block_set_border_right_width (fo,
			  fo_context_get_border_right_width (context));
  fo_block_set_border_start_color (fo,
			  fo_context_get_border_start_color (context));
  fo_block_set_border_start_style (fo,
			  fo_context_get_border_start_style (context));
  fo_block_set_border_start_width (fo,
			  fo_context_get_border_start_width (context));
  fo_block_set_border_top_color (fo,
			  fo_context_get_border_top_color (context));
  fo_block_set_border_top_style (fo,
			  fo_context_get_border_top_style (context));
  fo_block_set_border_top_width (fo,
			  fo_context_get_border_top_width (context));
  fo_block_set_break_after (fo,
			  fo_context_get_break_after (context));
  fo_block_set_break_before (fo,
			  fo_context_get_break_before (context));
  fo_block_set_color (fo,
			  fo_context_get_color (context));
  fo_block_set_end_indent (fo,
			  fo_context_get_end_indent (context));
  fo_block_set_font_family (fo,
			  fo_context_get_font_family (context));
  fo_block_set_font_size (fo,
			  fo_context_get_font_size (context));
  fo_block_set_font_stretch (fo,
			  fo_context_get_font_stretch (context));
  fo_block_set_font_style (fo,
			  fo_context_get_font_style (context));
  fo_block_set_font_variant (fo,
			  fo_context_get_font_variant (context));
  fo_block_set_font_weight (fo,
			  fo_context_get_font_weight (context));
  fo_block_set_id (fo,
			  fo_context_get_id (context));
  fo_block_set_keep_together (fo,
			  fo_context_get_keep_together (context));
  fo_block_set_keep_together_within_column (fo,
			  fo_context_get_keep_together_within_column (context));
  fo_block_set_keep_together_within_line (fo,
			  fo_context_get_keep_together_within_line (context));
  fo_block_set_keep_together_within_page (fo,
			  fo_context_get_keep_together_within_page (context));
  fo_block_set_keep_with_next (fo,
			  fo_context_get_keep_with_next (context));
  fo_block_set_keep_with_next_within_column (fo,
			  fo_context_get_keep_with_next_within_column (context));
  fo_block_set_keep_with_next_within_line (fo,
			  fo_context_get_keep_with_next_within_line (context));
  fo_block_set_keep_with_next_within_page (fo,
			  fo_context_get_keep_with_next_within_page (context));
  fo_block_set_keep_with_previous (fo,
			  fo_context_get_keep_with_previous (context));
  fo_block_set_keep_with_previous_within_column (fo,
			  fo_context_get_keep_with_previous_within_column (context));
  fo_block_set_keep_with_previous_within_line (fo,
			  fo_context_get_keep_with_previous_within_line (context));
  fo_block_set_keep_with_previous_within_page (fo,
			  fo_context_get_keep_with_previous_within_page (context));
  fo_block_set_line_height (fo,
			  fo_context_get_line_height (context));
  fo_block_set_line_stacking_strategy (fo,
			  fo_context_get_line_stacking_strategy (context));
  fo_block_set_linefeed_treatment (fo,
			  fo_context_get_linefeed_treatment (context));
  fo_block_set_margin_bottom (fo,
			  fo_context_get_margin_bottom (context));
  fo_block_set_margin_left (fo,
			  fo_context_get_margin_left (context));
  fo_block_set_margin_right (fo,
			  fo_context_get_margin_right (context));
  fo_block_set_margin_top (fo,
			  fo_context_get_margin_top (context));
  fo_block_set_orphans (fo,
			  fo_context_get_orphans (context));
  fo_block_set_padding_after (fo,
			  fo_context_get_padding_after (context));
  fo_block_set_padding_before (fo,
			  fo_context_get_padding_before (context));
  fo_block_set_padding_bottom (fo,
			  fo_context_get_padding_bottom (context));
  fo_block_set_padding_end (fo,
			  fo_context_get_padding_end (context));
  fo_block_set_padding_left (fo,
			  fo_context_get_padding_left (context));
  fo_block_set_padding_right (fo,
			  fo_context_get_padding_right (context));
  fo_block_set_padding_start (fo,
			  fo_context_get_padding_start (context));
  fo_block_set_padding_top (fo,
			  fo_context_get_padding_top (context));
  fo_block_set_role (fo,
			  fo_context_get_role (context));
  fo_block_set_source_document (fo,
			  fo_context_get_source_document (context));
  fo_block_set_space_after (fo,
			  fo_context_get_space_after (context));
  fo_block_set_space_before (fo,
			  fo_context_get_space_before (context));
  fo_block_set_span (fo,
			  fo_context_get_span (context));
  fo_block_set_start_indent (fo,
			  fo_context_get_start_indent (context));
  fo_block_set_text_align (fo,
			  fo_context_get_text_align (context));
  fo_block_set_text_indent (fo,
			  fo_context_get_text_indent (context));
  fo_block_set_white_space_collapse (fo,
			  fo_context_get_white_space_collapse (context));
  fo_block_set_white_space_treatment (fo,
			  fo_context_get_white_space_treatment (context));
  fo_block_set_widows (fo,
			  fo_context_get_widows (context));
  fo_block_set_wrap_option (fo,
			  fo_context_get_wrap_option (context));
}

/**
 * fo_block_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_block_debug_dump_properties (FoFo *fo,
                                gint  depth)
{
  FoBlock *fo_block;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo));

  fo_block = FO_BLOCK (fo);

  fo_object_debug_dump (fo_block->background_color, depth);
  fo_object_debug_dump (fo_block->background_image, depth);
  fo_object_debug_dump (fo_block->border_after_color, depth);
  fo_object_debug_dump (fo_block->border_after_style, depth);
  fo_object_debug_dump (fo_block->border_after_width, depth);
  fo_object_debug_dump (fo_block->border_before_color, depth);
  fo_object_debug_dump (fo_block->border_before_style, depth);
  fo_object_debug_dump (fo_block->border_before_width, depth);
  fo_object_debug_dump (fo_block->border_bottom_color, depth);
  fo_object_debug_dump (fo_block->border_bottom_style, depth);
  fo_object_debug_dump (fo_block->border_bottom_width, depth);
  fo_object_debug_dump (fo_block->border_end_color, depth);
  fo_object_debug_dump (fo_block->border_end_style, depth);
  fo_object_debug_dump (fo_block->border_end_width, depth);
  fo_object_debug_dump (fo_block->border_left_color, depth);
  fo_object_debug_dump (fo_block->border_left_style, depth);
  fo_object_debug_dump (fo_block->border_left_width, depth);
  fo_object_debug_dump (fo_block->border_right_color, depth);
  fo_object_debug_dump (fo_block->border_right_style, depth);
  fo_object_debug_dump (fo_block->border_right_width, depth);
  fo_object_debug_dump (fo_block->border_start_color, depth);
  fo_object_debug_dump (fo_block->border_start_style, depth);
  fo_object_debug_dump (fo_block->border_start_width, depth);
  fo_object_debug_dump (fo_block->border_top_color, depth);
  fo_object_debug_dump (fo_block->border_top_style, depth);
  fo_object_debug_dump (fo_block->border_top_width, depth);
  fo_object_debug_dump (fo_block->break_after, depth);
  fo_object_debug_dump (fo_block->break_before, depth);
  fo_object_debug_dump (fo_block->color, depth);
  fo_object_debug_dump (fo_block->end_indent, depth);
  fo_object_debug_dump (fo_block->font_family, depth);
  fo_object_debug_dump (fo_block->font_size, depth);
  fo_object_debug_dump (fo_block->font_stretch, depth);
  fo_object_debug_dump (fo_block->font_style, depth);
  fo_object_debug_dump (fo_block->font_variant, depth);
  fo_object_debug_dump (fo_block->font_weight, depth);
  fo_object_debug_dump (fo_block->id, depth);
  fo_object_debug_dump (fo_block->keep_together, depth);
  fo_object_debug_dump (fo_block->keep_together_within_column, depth);
  fo_object_debug_dump (fo_block->keep_together_within_line, depth);
  fo_object_debug_dump (fo_block->keep_together_within_page, depth);
  fo_object_debug_dump (fo_block->keep_with_next, depth);
  fo_object_debug_dump (fo_block->keep_with_next_within_column, depth);
  fo_object_debug_dump (fo_block->keep_with_next_within_line, depth);
  fo_object_debug_dump (fo_block->keep_with_next_within_page, depth);
  fo_object_debug_dump (fo_block->keep_with_previous, depth);
  fo_object_debug_dump (fo_block->keep_with_previous_within_column, depth);
  fo_object_debug_dump (fo_block->keep_with_previous_within_line, depth);
  fo_object_debug_dump (fo_block->keep_with_previous_within_page, depth);
  fo_object_debug_dump (fo_block->line_height, depth);
  fo_object_debug_dump (fo_block->line_stacking_strategy, depth);
  fo_object_debug_dump (fo_block->linefeed_treatment, depth);
  fo_object_debug_dump (fo_block->margin_bottom, depth);
  fo_object_debug_dump (fo_block->margin_left, depth);
  fo_object_debug_dump (fo_block->margin_right, depth);
  fo_object_debug_dump (fo_block->margin_top, depth);
  fo_object_debug_dump (fo_block->orphans, depth);
  fo_object_debug_dump (fo_block->padding_after, depth);
  fo_object_debug_dump (fo_block->padding_before, depth);
  fo_object_debug_dump (fo_block->padding_bottom, depth);
  fo_object_debug_dump (fo_block->padding_end, depth);
  fo_object_debug_dump (fo_block->padding_left, depth);
  fo_object_debug_dump (fo_block->padding_right, depth);
  fo_object_debug_dump (fo_block->padding_start, depth);
  fo_object_debug_dump (fo_block->padding_top, depth);
  fo_object_debug_dump (fo_block->role, depth);
  fo_object_debug_dump (fo_block->source_document, depth);
  fo_object_debug_dump (fo_block->space_after, depth);
  fo_object_debug_dump (fo_block->space_before, depth);
  fo_object_debug_dump (fo_block->span, depth);
  fo_object_debug_dump (fo_block->start_indent, depth);
  fo_object_debug_dump (fo_block->text_align, depth);
  fo_object_debug_dump (fo_block->text_indent, depth);
  fo_object_debug_dump (fo_block->white_space_collapse, depth);
  fo_object_debug_dump (fo_block->white_space_treatment, depth);
  fo_object_debug_dump (fo_block->widows, depth);
  fo_object_debug_dump (fo_block->wrap_option, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_block_get_background_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-color" property of @fo_fo.
 *
 * Return value: The "background-color" property value.
**/
FoProperty *
fo_block_get_background_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->background_color;
}

/**
 * fo_block_set_background_color:
 * @fo_fo: The #FoFo object.
 * @new_background_color: The new "background-color" property value.
 * 
 * Sets the "background-color" property of @fo_fo to @new_background_color.
 **/
void
fo_block_set_background_color (FoFo *fo_fo,
		         FoProperty *new_background_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_background_color == NULL) ||
		    FO_IS_PROPERTY_BACKGROUND_COLOR (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref (new_background_color);
    }
  if (fo_block->background_color != NULL)
    {
      g_object_unref (fo_block->background_color);
    }
  fo_block->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_block), "background-color");*/
}

/**
 * fo_block_get_background_image:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-image" property of @fo_fo.
 *
 * Return value: The "background-image" property value.
**/
FoProperty *
fo_block_get_background_image (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->background_image;
}

/**
 * fo_block_set_background_image:
 * @fo_fo: The #FoFo object.
 * @new_background_image: The new "background-image" property value.
 * 
 * Sets the "background-image" property of @fo_fo to @new_background_image.
 **/
void
fo_block_set_background_image (FoFo *fo_fo,
		         FoProperty *new_background_image)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_background_image == NULL) ||
		    FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref (new_background_image);
    }
  if (fo_block->background_image != NULL)
    {
      g_object_unref (fo_block->background_image);
    }
  fo_block->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_block), "background-image");*/
}

/**
 * fo_block_get_border_after_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-color" property of @fo_fo.
 *
 * Return value: The "border-after-color" property value.
**/
FoProperty *
fo_block_get_border_after_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_after_color;
}

/**
 * fo_block_set_border_after_color:
 * @fo_fo: The #FoFo object.
 * @new_border_after_color: The new "border-after-color" property value.
 * 
 * Sets the "border-after-color" property of @fo_fo to @new_border_after_color.
 **/
void
fo_block_set_border_after_color (FoFo *fo_fo,
		         FoProperty *new_border_after_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_after_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref (new_border_after_color);
    }
  if (fo_block->border_after_color != NULL)
    {
      g_object_unref (fo_block->border_after_color);
    }
  fo_block->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_block), "border-after-color");*/
}

/**
 * fo_block_get_border_after_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-style" property of @fo_fo.
 *
 * Return value: The "border-after-style" property value.
**/
FoProperty *
fo_block_get_border_after_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_after_style;
}

/**
 * fo_block_set_border_after_style:
 * @fo_fo: The #FoFo object.
 * @new_border_after_style: The new "border-after-style" property value.
 * 
 * Sets the "border-after-style" property of @fo_fo to @new_border_after_style.
 **/
void
fo_block_set_border_after_style (FoFo *fo_fo,
		         FoProperty *new_border_after_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_after_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref (new_border_after_style);
    }
  if (fo_block->border_after_style != NULL)
    {
      g_object_unref (fo_block->border_after_style);
    }
  fo_block->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_block), "border-after-style");*/
}

/**
 * fo_block_get_border_after_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-width" property of @fo_fo.
 *
 * Return value: The "border-after-width" property value.
**/
FoProperty *
fo_block_get_border_after_width (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_after_width;
}

/**
 * fo_block_set_border_after_width:
 * @fo_fo: The #FoFo object.
 * @new_border_after_width: The new "border-after-width" property value.
 * 
 * Sets the "border-after-width" property of @fo_fo to @new_border_after_width.
 **/
void
fo_block_set_border_after_width (FoFo *fo_fo,
		         FoProperty *new_border_after_width)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_after_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref (new_border_after_width);
    }
  if (fo_block->border_after_width != NULL)
    {
      g_object_unref (fo_block->border_after_width);
    }
  fo_block->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_block), "border-after-width");*/
}

/**
 * fo_block_get_border_before_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-color" property of @fo_fo.
 *
 * Return value: The "border-before-color" property value.
**/
FoProperty *
fo_block_get_border_before_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_before_color;
}

/**
 * fo_block_set_border_before_color:
 * @fo_fo: The #FoFo object.
 * @new_border_before_color: The new "border-before-color" property value.
 * 
 * Sets the "border-before-color" property of @fo_fo to @new_border_before_color.
 **/
void
fo_block_set_border_before_color (FoFo *fo_fo,
		         FoProperty *new_border_before_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_before_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref (new_border_before_color);
    }
  if (fo_block->border_before_color != NULL)
    {
      g_object_unref (fo_block->border_before_color);
    }
  fo_block->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_block), "border-before-color");*/
}

/**
 * fo_block_get_border_before_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-style" property of @fo_fo.
 *
 * Return value: The "border-before-style" property value.
**/
FoProperty *
fo_block_get_border_before_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_before_style;
}

/**
 * fo_block_set_border_before_style:
 * @fo_fo: The #FoFo object.
 * @new_border_before_style: The new "border-before-style" property value.
 * 
 * Sets the "border-before-style" property of @fo_fo to @new_border_before_style.
 **/
void
fo_block_set_border_before_style (FoFo *fo_fo,
		         FoProperty *new_border_before_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_before_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref (new_border_before_style);
    }
  if (fo_block->border_before_style != NULL)
    {
      g_object_unref (fo_block->border_before_style);
    }
  fo_block->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_block), "border-before-style");*/
}

/**
 * fo_block_get_border_before_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-width" property of @fo_fo.
 *
 * Return value: The "border-before-width" property value.
**/
FoProperty *
fo_block_get_border_before_width (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_before_width;
}

/**
 * fo_block_set_border_before_width:
 * @fo_fo: The #FoFo object.
 * @new_border_before_width: The new "border-before-width" property value.
 * 
 * Sets the "border-before-width" property of @fo_fo to @new_border_before_width.
 **/
void
fo_block_set_border_before_width (FoFo *fo_fo,
		         FoProperty *new_border_before_width)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_before_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref (new_border_before_width);
    }
  if (fo_block->border_before_width != NULL)
    {
      g_object_unref (fo_block->border_before_width);
    }
  fo_block->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_block), "border-before-width");*/
}

/**
 * fo_block_get_border_bottom_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-color" property of @fo_fo.
 *
 * Return value: The "border-bottom-color" property value.
**/
FoProperty *
fo_block_get_border_bottom_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_bottom_color;
}

/**
 * fo_block_set_border_bottom_color:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_color: The new "border-bottom-color" property value.
 * 
 * Sets the "border-bottom-color" property of @fo_fo to @new_border_bottom_color.
 **/
void
fo_block_set_border_bottom_color (FoFo *fo_fo,
		         FoProperty *new_border_bottom_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_bottom_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref (new_border_bottom_color);
    }
  if (fo_block->border_bottom_color != NULL)
    {
      g_object_unref (fo_block->border_bottom_color);
    }
  fo_block->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_block), "border-bottom-color");*/
}

/**
 * fo_block_get_border_bottom_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-style" property of @fo_fo.
 *
 * Return value: The "border-bottom-style" property value.
**/
FoProperty *
fo_block_get_border_bottom_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_bottom_style;
}

/**
 * fo_block_set_border_bottom_style:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_style: The new "border-bottom-style" property value.
 * 
 * Sets the "border-bottom-style" property of @fo_fo to @new_border_bottom_style.
 **/
void
fo_block_set_border_bottom_style (FoFo *fo_fo,
		         FoProperty *new_border_bottom_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_bottom_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref (new_border_bottom_style);
    }
  if (fo_block->border_bottom_style != NULL)
    {
      g_object_unref (fo_block->border_bottom_style);
    }
  fo_block->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_block), "border-bottom-style");*/
}

/**
 * fo_block_get_border_bottom_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-width" property of @fo_fo.
 *
 * Return value: The "border-bottom-width" property value.
**/
FoProperty *
fo_block_get_border_bottom_width (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_bottom_width;
}

/**
 * fo_block_set_border_bottom_width:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_width: The new "border-bottom-width" property value.
 * 
 * Sets the "border-bottom-width" property of @fo_fo to @new_border_bottom_width.
 **/
void
fo_block_set_border_bottom_width (FoFo *fo_fo,
		         FoProperty *new_border_bottom_width)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_bottom_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref (new_border_bottom_width);
    }
  if (fo_block->border_bottom_width != NULL)
    {
      g_object_unref (fo_block->border_bottom_width);
    }
  fo_block->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_block), "border-bottom-width");*/
}

/**
 * fo_block_get_border_end_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-color" property of @fo_fo.
 *
 * Return value: The "border-end-color" property value.
**/
FoProperty *
fo_block_get_border_end_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_end_color;
}

/**
 * fo_block_set_border_end_color:
 * @fo_fo: The #FoFo object.
 * @new_border_end_color: The new "border-end-color" property value.
 * 
 * Sets the "border-end-color" property of @fo_fo to @new_border_end_color.
 **/
void
fo_block_set_border_end_color (FoFo *fo_fo,
		         FoProperty *new_border_end_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_end_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref (new_border_end_color);
    }
  if (fo_block->border_end_color != NULL)
    {
      g_object_unref (fo_block->border_end_color);
    }
  fo_block->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_block), "border-end-color");*/
}

/**
 * fo_block_get_border_end_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-style" property of @fo_fo.
 *
 * Return value: The "border-end-style" property value.
**/
FoProperty *
fo_block_get_border_end_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_end_style;
}

/**
 * fo_block_set_border_end_style:
 * @fo_fo: The #FoFo object.
 * @new_border_end_style: The new "border-end-style" property value.
 * 
 * Sets the "border-end-style" property of @fo_fo to @new_border_end_style.
 **/
void
fo_block_set_border_end_style (FoFo *fo_fo,
		         FoProperty *new_border_end_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_end_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref (new_border_end_style);
    }
  if (fo_block->border_end_style != NULL)
    {
      g_object_unref (fo_block->border_end_style);
    }
  fo_block->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_block), "border-end-style");*/
}

/**
 * fo_block_get_border_end_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-width" property of @fo_fo.
 *
 * Return value: The "border-end-width" property value.
**/
FoProperty *
fo_block_get_border_end_width (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_end_width;
}

/**
 * fo_block_set_border_end_width:
 * @fo_fo: The #FoFo object.
 * @new_border_end_width: The new "border-end-width" property value.
 * 
 * Sets the "border-end-width" property of @fo_fo to @new_border_end_width.
 **/
void
fo_block_set_border_end_width (FoFo *fo_fo,
		         FoProperty *new_border_end_width)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_end_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref (new_border_end_width);
    }
  if (fo_block->border_end_width != NULL)
    {
      g_object_unref (fo_block->border_end_width);
    }
  fo_block->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_block), "border-end-width");*/
}

/**
 * fo_block_get_border_left_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-color" property of @fo_fo.
 *
 * Return value: The "border-left-color" property value.
**/
FoProperty *
fo_block_get_border_left_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_left_color;
}

/**
 * fo_block_set_border_left_color:
 * @fo_fo: The #FoFo object.
 * @new_border_left_color: The new "border-left-color" property value.
 * 
 * Sets the "border-left-color" property of @fo_fo to @new_border_left_color.
 **/
void
fo_block_set_border_left_color (FoFo *fo_fo,
		         FoProperty *new_border_left_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_left_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref (new_border_left_color);
    }
  if (fo_block->border_left_color != NULL)
    {
      g_object_unref (fo_block->border_left_color);
    }
  fo_block->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_block), "border-left-color");*/
}

/**
 * fo_block_get_border_left_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-style" property of @fo_fo.
 *
 * Return value: The "border-left-style" property value.
**/
FoProperty *
fo_block_get_border_left_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_left_style;
}

/**
 * fo_block_set_border_left_style:
 * @fo_fo: The #FoFo object.
 * @new_border_left_style: The new "border-left-style" property value.
 * 
 * Sets the "border-left-style" property of @fo_fo to @new_border_left_style.
 **/
void
fo_block_set_border_left_style (FoFo *fo_fo,
		         FoProperty *new_border_left_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_left_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref (new_border_left_style);
    }
  if (fo_block->border_left_style != NULL)
    {
      g_object_unref (fo_block->border_left_style);
    }
  fo_block->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_block), "border-left-style");*/
}

/**
 * fo_block_get_border_left_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-width" property of @fo_fo.
 *
 * Return value: The "border-left-width" property value.
**/
FoProperty *
fo_block_get_border_left_width (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_left_width;
}

/**
 * fo_block_set_border_left_width:
 * @fo_fo: The #FoFo object.
 * @new_border_left_width: The new "border-left-width" property value.
 * 
 * Sets the "border-left-width" property of @fo_fo to @new_border_left_width.
 **/
void
fo_block_set_border_left_width (FoFo *fo_fo,
		         FoProperty *new_border_left_width)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_left_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref (new_border_left_width);
    }
  if (fo_block->border_left_width != NULL)
    {
      g_object_unref (fo_block->border_left_width);
    }
  fo_block->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_block), "border-left-width");*/
}

/**
 * fo_block_get_border_right_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-color" property of @fo_fo.
 *
 * Return value: The "border-right-color" property value.
**/
FoProperty *
fo_block_get_border_right_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_right_color;
}

/**
 * fo_block_set_border_right_color:
 * @fo_fo: The #FoFo object.
 * @new_border_right_color: The new "border-right-color" property value.
 * 
 * Sets the "border-right-color" property of @fo_fo to @new_border_right_color.
 **/
void
fo_block_set_border_right_color (FoFo *fo_fo,
		         FoProperty *new_border_right_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_right_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref (new_border_right_color);
    }
  if (fo_block->border_right_color != NULL)
    {
      g_object_unref (fo_block->border_right_color);
    }
  fo_block->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_block), "border-right-color");*/
}

/**
 * fo_block_get_border_right_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-style" property of @fo_fo.
 *
 * Return value: The "border-right-style" property value.
**/
FoProperty *
fo_block_get_border_right_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_right_style;
}

/**
 * fo_block_set_border_right_style:
 * @fo_fo: The #FoFo object.
 * @new_border_right_style: The new "border-right-style" property value.
 * 
 * Sets the "border-right-style" property of @fo_fo to @new_border_right_style.
 **/
void
fo_block_set_border_right_style (FoFo *fo_fo,
		         FoProperty *new_border_right_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_right_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref (new_border_right_style);
    }
  if (fo_block->border_right_style != NULL)
    {
      g_object_unref (fo_block->border_right_style);
    }
  fo_block->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_block), "border-right-style");*/
}

/**
 * fo_block_get_border_right_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-width" property of @fo_fo.
 *
 * Return value: The "border-right-width" property value.
**/
FoProperty *
fo_block_get_border_right_width (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_right_width;
}

/**
 * fo_block_set_border_right_width:
 * @fo_fo: The #FoFo object.
 * @new_border_right_width: The new "border-right-width" property value.
 * 
 * Sets the "border-right-width" property of @fo_fo to @new_border_right_width.
 **/
void
fo_block_set_border_right_width (FoFo *fo_fo,
		         FoProperty *new_border_right_width)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_right_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref (new_border_right_width);
    }
  if (fo_block->border_right_width != NULL)
    {
      g_object_unref (fo_block->border_right_width);
    }
  fo_block->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_block), "border-right-width");*/
}

/**
 * fo_block_get_border_start_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-color" property of @fo_fo.
 *
 * Return value: The "border-start-color" property value.
**/
FoProperty *
fo_block_get_border_start_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_start_color;
}

/**
 * fo_block_set_border_start_color:
 * @fo_fo: The #FoFo object.
 * @new_border_start_color: The new "border-start-color" property value.
 * 
 * Sets the "border-start-color" property of @fo_fo to @new_border_start_color.
 **/
void
fo_block_set_border_start_color (FoFo *fo_fo,
		         FoProperty *new_border_start_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_start_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref (new_border_start_color);
    }
  if (fo_block->border_start_color != NULL)
    {
      g_object_unref (fo_block->border_start_color);
    }
  fo_block->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_block), "border-start-color");*/
}

/**
 * fo_block_get_border_start_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-style" property of @fo_fo.
 *
 * Return value: The "border-start-style" property value.
**/
FoProperty *
fo_block_get_border_start_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_start_style;
}

/**
 * fo_block_set_border_start_style:
 * @fo_fo: The #FoFo object.
 * @new_border_start_style: The new "border-start-style" property value.
 * 
 * Sets the "border-start-style" property of @fo_fo to @new_border_start_style.
 **/
void
fo_block_set_border_start_style (FoFo *fo_fo,
		         FoProperty *new_border_start_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_start_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref (new_border_start_style);
    }
  if (fo_block->border_start_style != NULL)
    {
      g_object_unref (fo_block->border_start_style);
    }
  fo_block->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_block), "border-start-style");*/
}

/**
 * fo_block_get_border_start_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-width" property of @fo_fo.
 *
 * Return value: The "border-start-width" property value.
**/
FoProperty *
fo_block_get_border_start_width (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_start_width;
}

/**
 * fo_block_set_border_start_width:
 * @fo_fo: The #FoFo object.
 * @new_border_start_width: The new "border-start-width" property value.
 * 
 * Sets the "border-start-width" property of @fo_fo to @new_border_start_width.
 **/
void
fo_block_set_border_start_width (FoFo *fo_fo,
		         FoProperty *new_border_start_width)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_start_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref (new_border_start_width);
    }
  if (fo_block->border_start_width != NULL)
    {
      g_object_unref (fo_block->border_start_width);
    }
  fo_block->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_block), "border-start-width");*/
}

/**
 * fo_block_get_border_top_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-color" property of @fo_fo.
 *
 * Return value: The "border-top-color" property value.
**/
FoProperty *
fo_block_get_border_top_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_top_color;
}

/**
 * fo_block_set_border_top_color:
 * @fo_fo: The #FoFo object.
 * @new_border_top_color: The new "border-top-color" property value.
 * 
 * Sets the "border-top-color" property of @fo_fo to @new_border_top_color.
 **/
void
fo_block_set_border_top_color (FoFo *fo_fo,
		         FoProperty *new_border_top_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_top_color == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref (new_border_top_color);
    }
  if (fo_block->border_top_color != NULL)
    {
      g_object_unref (fo_block->border_top_color);
    }
  fo_block->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_block), "border-top-color");*/
}

/**
 * fo_block_get_border_top_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-style" property of @fo_fo.
 *
 * Return value: The "border-top-style" property value.
**/
FoProperty *
fo_block_get_border_top_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_top_style;
}

/**
 * fo_block_set_border_top_style:
 * @fo_fo: The #FoFo object.
 * @new_border_top_style: The new "border-top-style" property value.
 * 
 * Sets the "border-top-style" property of @fo_fo to @new_border_top_style.
 **/
void
fo_block_set_border_top_style (FoFo *fo_fo,
		         FoProperty *new_border_top_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_top_style == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref (new_border_top_style);
    }
  if (fo_block->border_top_style != NULL)
    {
      g_object_unref (fo_block->border_top_style);
    }
  fo_block->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_block), "border-top-style");*/
}

/**
 * fo_block_get_border_top_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-width" property of @fo_fo.
 *
 * Return value: The "border-top-width" property value.
**/
FoProperty *
fo_block_get_border_top_width (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->border_top_width;
}

/**
 * fo_block_set_border_top_width:
 * @fo_fo: The #FoFo object.
 * @new_border_top_width: The new "border-top-width" property value.
 * 
 * Sets the "border-top-width" property of @fo_fo to @new_border_top_width.
 **/
void
fo_block_set_border_top_width (FoFo *fo_fo,
		         FoProperty *new_border_top_width)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_border_top_width == NULL) ||
		    FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref (new_border_top_width);
    }
  if (fo_block->border_top_width != NULL)
    {
      g_object_unref (fo_block->border_top_width);
    }
  fo_block->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_block), "border-top-width");*/
}

/**
 * fo_block_get_break_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "break-after" property of @fo_fo.
 *
 * Return value: The "break-after" property value.
**/
FoProperty *
fo_block_get_break_after (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->break_after;
}

/**
 * fo_block_set_break_after:
 * @fo_fo: The #FoFo object.
 * @new_break_after: The new "break-after" property value.
 * 
 * Sets the "break-after" property of @fo_fo to @new_break_after.
 **/
void
fo_block_set_break_after (FoFo *fo_fo,
		         FoProperty *new_break_after)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_break_after == NULL) ||
		    FO_IS_PROPERTY_BREAK_AFTER (new_break_after));

  if (new_break_after != NULL)
    {
      g_object_ref (new_break_after);
    }
  if (fo_block->break_after != NULL)
    {
      g_object_unref (fo_block->break_after);
    }
  fo_block->break_after = new_break_after;
  /*g_object_notify (G_OBJECT (fo_block), "break-after");*/
}

/**
 * fo_block_get_break_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "break-before" property of @fo_fo.
 *
 * Return value: The "break-before" property value.
**/
FoProperty *
fo_block_get_break_before (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->break_before;
}

/**
 * fo_block_set_break_before:
 * @fo_fo: The #FoFo object.
 * @new_break_before: The new "break-before" property value.
 * 
 * Sets the "break-before" property of @fo_fo to @new_break_before.
 **/
void
fo_block_set_break_before (FoFo *fo_fo,
		         FoProperty *new_break_before)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_break_before == NULL) ||
		    FO_IS_PROPERTY_BREAK_BEFORE (new_break_before));

  if (new_break_before != NULL)
    {
      g_object_ref (new_break_before);
    }
  if (fo_block->break_before != NULL)
    {
      g_object_unref (fo_block->break_before);
    }
  fo_block->break_before = new_break_before;
  /*g_object_notify (G_OBJECT (fo_block), "break-before");*/
}

/**
 * fo_block_get_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "color" property of @fo_fo.
 *
 * Return value: The "color" property value.
**/
FoProperty *
fo_block_get_color (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->color;
}

/**
 * fo_block_set_color:
 * @fo_fo: The #FoFo object.
 * @new_color: The new "color" property value.
 * 
 * Sets the "color" property of @fo_fo to @new_color.
 **/
void
fo_block_set_color (FoFo *fo_fo,
		         FoProperty *new_color)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_color == NULL) ||
		    FO_IS_PROPERTY_COLOR (new_color));

  if (new_color != NULL)
    {
      g_object_ref (new_color);
    }
  if (fo_block->color != NULL)
    {
      g_object_unref (fo_block->color);
    }
  fo_block->color = new_color;
  /*g_object_notify (G_OBJECT (fo_block), "color");*/
}

/**
 * fo_block_get_end_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "end-indent" property of @fo_fo.
 *
 * Return value: The "end-indent" property value.
**/
FoProperty *
fo_block_get_end_indent (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->end_indent;
}

/**
 * fo_block_set_end_indent:
 * @fo_fo: The #FoFo object.
 * @new_end_indent: The new "end-indent" property value.
 * 
 * Sets the "end-indent" property of @fo_fo to @new_end_indent.
 **/
void
fo_block_set_end_indent (FoFo *fo_fo,
		         FoProperty *new_end_indent)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_end_indent == NULL) ||
		    FO_IS_PROPERTY_END_INDENT (new_end_indent));

  if (new_end_indent != NULL)
    {
      g_object_ref (new_end_indent);
    }
  if (fo_block->end_indent != NULL)
    {
      g_object_unref (fo_block->end_indent);
    }
  fo_block->end_indent = new_end_indent;
  /*g_object_notify (G_OBJECT (fo_block), "end-indent");*/
}

/**
 * fo_block_get_font_family:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-family" property of @fo_fo.
 *
 * Return value: The "font-family" property value.
**/
FoProperty *
fo_block_get_font_family (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->font_family;
}

/**
 * fo_block_set_font_family:
 * @fo_fo: The #FoFo object.
 * @new_font_family: The new "font-family" property value.
 * 
 * Sets the "font-family" property of @fo_fo to @new_font_family.
 **/
void
fo_block_set_font_family (FoFo *fo_fo,
		         FoProperty *new_font_family)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_font_family == NULL) ||
		    FO_IS_PROPERTY_FONT_FAMILY (new_font_family));

  if (new_font_family != NULL)
    {
      g_object_ref (new_font_family);
    }
  if (fo_block->font_family != NULL)
    {
      g_object_unref (fo_block->font_family);
    }
  fo_block->font_family = new_font_family;
  /*g_object_notify (G_OBJECT (fo_block), "font-family");*/
}

/**
 * fo_block_get_font_size:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-size" property of @fo_fo.
 *
 * Return value: The "font-size" property value.
**/
FoProperty *
fo_block_get_font_size (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->font_size;
}

/**
 * fo_block_set_font_size:
 * @fo_fo: The #FoFo object.
 * @new_font_size: The new "font-size" property value.
 * 
 * Sets the "font-size" property of @fo_fo to @new_font_size.
 **/
void
fo_block_set_font_size (FoFo *fo_fo,
		         FoProperty *new_font_size)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_font_size == NULL) ||
		    FO_IS_PROPERTY_FONT_SIZE (new_font_size));

  if (new_font_size != NULL)
    {
      g_object_ref (new_font_size);
    }
  if (fo_block->font_size != NULL)
    {
      g_object_unref (fo_block->font_size);
    }
  fo_block->font_size = new_font_size;
  /*g_object_notify (G_OBJECT (fo_block), "font-size");*/
}

/**
 * fo_block_get_font_stretch:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-stretch" property of @fo_fo.
 *
 * Return value: The "font-stretch" property value.
**/
FoProperty *
fo_block_get_font_stretch (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->font_stretch;
}

/**
 * fo_block_set_font_stretch:
 * @fo_fo: The #FoFo object.
 * @new_font_stretch: The new "font-stretch" property value.
 * 
 * Sets the "font-stretch" property of @fo_fo to @new_font_stretch.
 **/
void
fo_block_set_font_stretch (FoFo *fo_fo,
		         FoProperty *new_font_stretch)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_font_stretch == NULL) ||
		    FO_IS_PROPERTY_FONT_STRETCH (new_font_stretch));

  if (new_font_stretch != NULL)
    {
      g_object_ref (new_font_stretch);
    }
  if (fo_block->font_stretch != NULL)
    {
      g_object_unref (fo_block->font_stretch);
    }
  fo_block->font_stretch = new_font_stretch;
  /*g_object_notify (G_OBJECT (fo_block), "font-stretch");*/
}

/**
 * fo_block_get_font_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-style" property of @fo_fo.
 *
 * Return value: The "font-style" property value.
**/
FoProperty *
fo_block_get_font_style (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->font_style;
}

/**
 * fo_block_set_font_style:
 * @fo_fo: The #FoFo object.
 * @new_font_style: The new "font-style" property value.
 * 
 * Sets the "font-style" property of @fo_fo to @new_font_style.
 **/
void
fo_block_set_font_style (FoFo *fo_fo,
		         FoProperty *new_font_style)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_font_style == NULL) ||
		    FO_IS_PROPERTY_FONT_STYLE (new_font_style));

  if (new_font_style != NULL)
    {
      g_object_ref (new_font_style);
    }
  if (fo_block->font_style != NULL)
    {
      g_object_unref (fo_block->font_style);
    }
  fo_block->font_style = new_font_style;
  /*g_object_notify (G_OBJECT (fo_block), "font-style");*/
}

/**
 * fo_block_get_font_variant:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-variant" property of @fo_fo.
 *
 * Return value: The "font-variant" property value.
**/
FoProperty *
fo_block_get_font_variant (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->font_variant;
}

/**
 * fo_block_set_font_variant:
 * @fo_fo: The #FoFo object.
 * @new_font_variant: The new "font-variant" property value.
 * 
 * Sets the "font-variant" property of @fo_fo to @new_font_variant.
 **/
void
fo_block_set_font_variant (FoFo *fo_fo,
		         FoProperty *new_font_variant)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_font_variant == NULL) ||
		    FO_IS_PROPERTY_FONT_VARIANT (new_font_variant));

  if (new_font_variant != NULL)
    {
      g_object_ref (new_font_variant);
    }
  if (fo_block->font_variant != NULL)
    {
      g_object_unref (fo_block->font_variant);
    }
  fo_block->font_variant = new_font_variant;
  /*g_object_notify (G_OBJECT (fo_block), "font-variant");*/
}

/**
 * fo_block_get_font_weight:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-weight" property of @fo_fo.
 *
 * Return value: The "font-weight" property value.
**/
FoProperty *
fo_block_get_font_weight (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->font_weight;
}

/**
 * fo_block_set_font_weight:
 * @fo_fo: The #FoFo object.
 * @new_font_weight: The new "font-weight" property value.
 * 
 * Sets the "font-weight" property of @fo_fo to @new_font_weight.
 **/
void
fo_block_set_font_weight (FoFo *fo_fo,
		         FoProperty *new_font_weight)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_font_weight == NULL) ||
		    FO_IS_PROPERTY_FONT_WEIGHT (new_font_weight));

  if (new_font_weight != NULL)
    {
      g_object_ref (new_font_weight);
    }
  if (fo_block->font_weight != NULL)
    {
      g_object_unref (fo_block->font_weight);
    }
  fo_block->font_weight = new_font_weight;
  /*g_object_notify (G_OBJECT (fo_block), "font-weight");*/
}

/**
 * fo_block_get_id:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "id" property of @fo_fo.
 *
 * Return value: The "id" property value.
**/
FoProperty *
fo_block_get_id (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->id;
}

/**
 * fo_block_set_id:
 * @fo_fo: The #FoFo object.
 * @new_id: The new "id" property value.
 * 
 * Sets the "id" property of @fo_fo to @new_id.
 **/
void
fo_block_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_id == NULL) ||
		    FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_block->id != NULL)
    {
      g_object_unref (fo_block->id);
    }
  fo_block->id = new_id;
  /*g_object_notify (G_OBJECT (fo_block), "id");*/
}

/**
 * fo_block_get_keep_together:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-together" property of @fo_fo.
 *
 * Return value: The "keep-together" property value.
**/
FoProperty *
fo_block_get_keep_together (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_together;
}

/**
 * fo_block_set_keep_together:
 * @fo_fo: The #FoFo object.
 * @new_keep_together: The new "keep-together" property value.
 * 
 * Sets the "keep-together" property of @fo_fo to @new_keep_together.
 **/
void
fo_block_set_keep_together (FoFo *fo_fo,
		         FoProperty *new_keep_together)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_together == NULL) ||
		    FO_IS_PROPERTY_KEEP_TOGETHER (new_keep_together));

  if (new_keep_together != NULL)
    {
      g_object_ref (new_keep_together);
    }
  if (fo_block->keep_together != NULL)
    {
      g_object_unref (fo_block->keep_together);
    }
  fo_block->keep_together = new_keep_together;
  /*g_object_notify (G_OBJECT (fo_block), "keep-together");*/
}

/**
 * fo_block_get_keep_together_within_column:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-together-within-column" property of @fo_fo.
 *
 * Return value: The "keep-together-within-column" property value.
**/
FoProperty *
fo_block_get_keep_together_within_column (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_together_within_column;
}

/**
 * fo_block_set_keep_together_within_column:
 * @fo_fo: The #FoFo object.
 * @new_keep_together_within_column: The new "keep-together-within-column" property value.
 * 
 * Sets the "keep-together-within-column" property of @fo_fo to @new_keep_together_within_column.
 **/
void
fo_block_set_keep_together_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_column)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_together_within_column == NULL) ||
		    FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN (new_keep_together_within_column));

  if (new_keep_together_within_column != NULL)
    {
      g_object_ref (new_keep_together_within_column);
    }
  if (fo_block->keep_together_within_column != NULL)
    {
      g_object_unref (fo_block->keep_together_within_column);
    }
  fo_block->keep_together_within_column = new_keep_together_within_column;
  /*g_object_notify (G_OBJECT (fo_block), "keep-together-within-column");*/
}

/**
 * fo_block_get_keep_together_within_line:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-together-within-line" property of @fo_fo.
 *
 * Return value: The "keep-together-within-line" property value.
**/
FoProperty *
fo_block_get_keep_together_within_line (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_together_within_line;
}

/**
 * fo_block_set_keep_together_within_line:
 * @fo_fo: The #FoFo object.
 * @new_keep_together_within_line: The new "keep-together-within-line" property value.
 * 
 * Sets the "keep-together-within-line" property of @fo_fo to @new_keep_together_within_line.
 **/
void
fo_block_set_keep_together_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_line)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_together_within_line == NULL) ||
		    FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_LINE (new_keep_together_within_line));

  if (new_keep_together_within_line != NULL)
    {
      g_object_ref (new_keep_together_within_line);
    }
  if (fo_block->keep_together_within_line != NULL)
    {
      g_object_unref (fo_block->keep_together_within_line);
    }
  fo_block->keep_together_within_line = new_keep_together_within_line;
  /*g_object_notify (G_OBJECT (fo_block), "keep-together-within-line");*/
}

/**
 * fo_block_get_keep_together_within_page:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-together-within-page" property of @fo_fo.
 *
 * Return value: The "keep-together-within-page" property value.
**/
FoProperty *
fo_block_get_keep_together_within_page (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_together_within_page;
}

/**
 * fo_block_set_keep_together_within_page:
 * @fo_fo: The #FoFo object.
 * @new_keep_together_within_page: The new "keep-together-within-page" property value.
 * 
 * Sets the "keep-together-within-page" property of @fo_fo to @new_keep_together_within_page.
 **/
void
fo_block_set_keep_together_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_page)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_together_within_page == NULL) ||
		    FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE (new_keep_together_within_page));

  if (new_keep_together_within_page != NULL)
    {
      g_object_ref (new_keep_together_within_page);
    }
  if (fo_block->keep_together_within_page != NULL)
    {
      g_object_unref (fo_block->keep_together_within_page);
    }
  fo_block->keep_together_within_page = new_keep_together_within_page;
  /*g_object_notify (G_OBJECT (fo_block), "keep-together-within-page");*/
}

/**
 * fo_block_get_keep_with_next:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next" property of @fo_fo.
 *
 * Return value: The "keep-with-next" property value.
**/
FoProperty *
fo_block_get_keep_with_next (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_with_next;
}

/**
 * fo_block_set_keep_with_next:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next: The new "keep-with-next" property value.
 * 
 * Sets the "keep-with-next" property of @fo_fo to @new_keep_with_next.
 **/
void
fo_block_set_keep_with_next (FoFo *fo_fo,
		         FoProperty *new_keep_with_next)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_with_next == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_NEXT (new_keep_with_next));

  if (new_keep_with_next != NULL)
    {
      g_object_ref (new_keep_with_next);
    }
  if (fo_block->keep_with_next != NULL)
    {
      g_object_unref (fo_block->keep_with_next);
    }
  fo_block->keep_with_next = new_keep_with_next;
  /*g_object_notify (G_OBJECT (fo_block), "keep-with-next");*/
}

/**
 * fo_block_get_keep_with_next_within_column:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-column" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-column" property value.
**/
FoProperty *
fo_block_get_keep_with_next_within_column (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_with_next_within_column;
}

/**
 * fo_block_set_keep_with_next_within_column:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_column: The new "keep-with-next-within-column" property value.
 * 
 * Sets the "keep-with-next-within-column" property of @fo_fo to @new_keep_with_next_within_column.
 **/
void
fo_block_set_keep_with_next_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_column)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_with_next_within_column == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_COLUMN (new_keep_with_next_within_column));

  if (new_keep_with_next_within_column != NULL)
    {
      g_object_ref (new_keep_with_next_within_column);
    }
  if (fo_block->keep_with_next_within_column != NULL)
    {
      g_object_unref (fo_block->keep_with_next_within_column);
    }
  fo_block->keep_with_next_within_column = new_keep_with_next_within_column;
  /*g_object_notify (G_OBJECT (fo_block), "keep-with-next-within-column");*/
}

/**
 * fo_block_get_keep_with_next_within_line:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-line" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-line" property value.
**/
FoProperty *
fo_block_get_keep_with_next_within_line (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_with_next_within_line;
}

/**
 * fo_block_set_keep_with_next_within_line:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_line: The new "keep-with-next-within-line" property value.
 * 
 * Sets the "keep-with-next-within-line" property of @fo_fo to @new_keep_with_next_within_line.
 **/
void
fo_block_set_keep_with_next_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_line)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_with_next_within_line == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (new_keep_with_next_within_line));

  if (new_keep_with_next_within_line != NULL)
    {
      g_object_ref (new_keep_with_next_within_line);
    }
  if (fo_block->keep_with_next_within_line != NULL)
    {
      g_object_unref (fo_block->keep_with_next_within_line);
    }
  fo_block->keep_with_next_within_line = new_keep_with_next_within_line;
  /*g_object_notify (G_OBJECT (fo_block), "keep-with-next-within-line");*/
}

/**
 * fo_block_get_keep_with_next_within_page:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-page" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-page" property value.
**/
FoProperty *
fo_block_get_keep_with_next_within_page (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_with_next_within_page;
}

/**
 * fo_block_set_keep_with_next_within_page:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_page: The new "keep-with-next-within-page" property value.
 * 
 * Sets the "keep-with-next-within-page" property of @fo_fo to @new_keep_with_next_within_page.
 **/
void
fo_block_set_keep_with_next_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_page)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_with_next_within_page == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE (new_keep_with_next_within_page));

  if (new_keep_with_next_within_page != NULL)
    {
      g_object_ref (new_keep_with_next_within_page);
    }
  if (fo_block->keep_with_next_within_page != NULL)
    {
      g_object_unref (fo_block->keep_with_next_within_page);
    }
  fo_block->keep_with_next_within_page = new_keep_with_next_within_page;
  /*g_object_notify (G_OBJECT (fo_block), "keep-with-next-within-page");*/
}

/**
 * fo_block_get_keep_with_previous:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous" property of @fo_fo.
 *
 * Return value: The "keep-with-previous" property value.
**/
FoProperty *
fo_block_get_keep_with_previous (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_with_previous;
}

/**
 * fo_block_set_keep_with_previous:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous: The new "keep-with-previous" property value.
 * 
 * Sets the "keep-with-previous" property of @fo_fo to @new_keep_with_previous.
 **/
void
fo_block_set_keep_with_previous (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_with_previous == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_PREVIOUS (new_keep_with_previous));

  if (new_keep_with_previous != NULL)
    {
      g_object_ref (new_keep_with_previous);
    }
  if (fo_block->keep_with_previous != NULL)
    {
      g_object_unref (fo_block->keep_with_previous);
    }
  fo_block->keep_with_previous = new_keep_with_previous;
  /*g_object_notify (G_OBJECT (fo_block), "keep-with-previous");*/
}

/**
 * fo_block_get_keep_with_previous_within_column:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-column" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-column" property value.
**/
FoProperty *
fo_block_get_keep_with_previous_within_column (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_with_previous_within_column;
}

/**
 * fo_block_set_keep_with_previous_within_column:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_column: The new "keep-with-previous-within-column" property value.
 * 
 * Sets the "keep-with-previous-within-column" property of @fo_fo to @new_keep_with_previous_within_column.
 **/
void
fo_block_set_keep_with_previous_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_column)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_with_previous_within_column == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_COLUMN (new_keep_with_previous_within_column));

  if (new_keep_with_previous_within_column != NULL)
    {
      g_object_ref (new_keep_with_previous_within_column);
    }
  if (fo_block->keep_with_previous_within_column != NULL)
    {
      g_object_unref (fo_block->keep_with_previous_within_column);
    }
  fo_block->keep_with_previous_within_column = new_keep_with_previous_within_column;
  /*g_object_notify (G_OBJECT (fo_block), "keep-with-previous-within-column");*/
}

/**
 * fo_block_get_keep_with_previous_within_line:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-line" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-line" property value.
**/
FoProperty *
fo_block_get_keep_with_previous_within_line (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_with_previous_within_line;
}

/**
 * fo_block_set_keep_with_previous_within_line:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_line: The new "keep-with-previous-within-line" property value.
 * 
 * Sets the "keep-with-previous-within-line" property of @fo_fo to @new_keep_with_previous_within_line.
 **/
void
fo_block_set_keep_with_previous_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_line)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_with_previous_within_line == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_LINE (new_keep_with_previous_within_line));

  if (new_keep_with_previous_within_line != NULL)
    {
      g_object_ref (new_keep_with_previous_within_line);
    }
  if (fo_block->keep_with_previous_within_line != NULL)
    {
      g_object_unref (fo_block->keep_with_previous_within_line);
    }
  fo_block->keep_with_previous_within_line = new_keep_with_previous_within_line;
  /*g_object_notify (G_OBJECT (fo_block), "keep-with-previous-within-line");*/
}

/**
 * fo_block_get_keep_with_previous_within_page:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-page" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-page" property value.
**/
FoProperty *
fo_block_get_keep_with_previous_within_page (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->keep_with_previous_within_page;
}

/**
 * fo_block_set_keep_with_previous_within_page:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_page: The new "keep-with-previous-within-page" property value.
 * 
 * Sets the "keep-with-previous-within-page" property of @fo_fo to @new_keep_with_previous_within_page.
 **/
void
fo_block_set_keep_with_previous_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_page)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_keep_with_previous_within_page == NULL) ||
		    FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE (new_keep_with_previous_within_page));

  if (new_keep_with_previous_within_page != NULL)
    {
      g_object_ref (new_keep_with_previous_within_page);
    }
  if (fo_block->keep_with_previous_within_page != NULL)
    {
      g_object_unref (fo_block->keep_with_previous_within_page);
    }
  fo_block->keep_with_previous_within_page = new_keep_with_previous_within_page;
  /*g_object_notify (G_OBJECT (fo_block), "keep-with-previous-within-page");*/
}

/**
 * fo_block_get_line_height:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "line-height" property of @fo_fo.
 *
 * Return value: The "line-height" property value.
**/
FoProperty *
fo_block_get_line_height (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->line_height;
}

/**
 * fo_block_set_line_height:
 * @fo_fo: The #FoFo object.
 * @new_line_height: The new "line-height" property value.
 * 
 * Sets the "line-height" property of @fo_fo to @new_line_height.
 **/
void
fo_block_set_line_height (FoFo *fo_fo,
		         FoProperty *new_line_height)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_line_height == NULL) ||
		    FO_IS_PROPERTY_LINE_HEIGHT (new_line_height));

  if (new_line_height != NULL)
    {
      g_object_ref (new_line_height);
    }
  if (fo_block->line_height != NULL)
    {
      g_object_unref (fo_block->line_height);
    }
  fo_block->line_height = new_line_height;
  /*g_object_notify (G_OBJECT (fo_block), "line-height");*/
}

/**
 * fo_block_get_line_stacking_strategy:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "line-stacking-strategy" property of @fo_fo.
 *
 * Return value: The "line-stacking-strategy" property value.
**/
FoProperty *
fo_block_get_line_stacking_strategy (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->line_stacking_strategy;
}

/**
 * fo_block_set_line_stacking_strategy:
 * @fo_fo: The #FoFo object.
 * @new_line_stacking_strategy: The new "line-stacking-strategy" property value.
 * 
 * Sets the "line-stacking-strategy" property of @fo_fo to @new_line_stacking_strategy.
 **/
void
fo_block_set_line_stacking_strategy (FoFo *fo_fo,
		         FoProperty *new_line_stacking_strategy)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_line_stacking_strategy == NULL) ||
		    FO_IS_PROPERTY_LINE_STACKING_STRATEGY (new_line_stacking_strategy));

  if (new_line_stacking_strategy != NULL)
    {
      g_object_ref (new_line_stacking_strategy);
    }
  if (fo_block->line_stacking_strategy != NULL)
    {
      g_object_unref (fo_block->line_stacking_strategy);
    }
  fo_block->line_stacking_strategy = new_line_stacking_strategy;
  /*g_object_notify (G_OBJECT (fo_block), "line-stacking-strategy");*/
}

/**
 * fo_block_get_linefeed_treatment:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "linefeed-treatment" property of @fo_fo.
 *
 * Return value: The "linefeed-treatment" property value.
**/
FoProperty *
fo_block_get_linefeed_treatment (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->linefeed_treatment;
}

/**
 * fo_block_set_linefeed_treatment:
 * @fo_fo: The #FoFo object.
 * @new_linefeed_treatment: The new "linefeed-treatment" property value.
 * 
 * Sets the "linefeed-treatment" property of @fo_fo to @new_linefeed_treatment.
 **/
void
fo_block_set_linefeed_treatment (FoFo *fo_fo,
		         FoProperty *new_linefeed_treatment)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_linefeed_treatment == NULL) ||
		    FO_IS_PROPERTY_LINEFEED_TREATMENT (new_linefeed_treatment));

  if (new_linefeed_treatment != NULL)
    {
      g_object_ref (new_linefeed_treatment);
    }
  if (fo_block->linefeed_treatment != NULL)
    {
      g_object_unref (fo_block->linefeed_treatment);
    }
  fo_block->linefeed_treatment = new_linefeed_treatment;
  /*g_object_notify (G_OBJECT (fo_block), "linefeed-treatment");*/
}

/**
 * fo_block_get_margin_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-bottom" property of @fo_fo.
 *
 * Return value: The "margin-bottom" property value.
**/
FoProperty *
fo_block_get_margin_bottom (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->margin_bottom;
}

/**
 * fo_block_set_margin_bottom:
 * @fo_fo: The #FoFo object.
 * @new_margin_bottom: The new "margin-bottom" property value.
 * 
 * Sets the "margin-bottom" property of @fo_fo to @new_margin_bottom.
 **/
void
fo_block_set_margin_bottom (FoFo *fo_fo,
		         FoProperty *new_margin_bottom)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_margin_bottom == NULL) ||
		    FO_IS_PROPERTY_MARGIN_BOTTOM (new_margin_bottom));

  if (new_margin_bottom != NULL)
    {
      g_object_ref (new_margin_bottom);
    }
  if (fo_block->margin_bottom != NULL)
    {
      g_object_unref (fo_block->margin_bottom);
    }
  fo_block->margin_bottom = new_margin_bottom;
  /*g_object_notify (G_OBJECT (fo_block), "margin-bottom");*/
}

/**
 * fo_block_get_margin_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-left" property of @fo_fo.
 *
 * Return value: The "margin-left" property value.
**/
FoProperty *
fo_block_get_margin_left (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->margin_left;
}

/**
 * fo_block_set_margin_left:
 * @fo_fo: The #FoFo object.
 * @new_margin_left: The new "margin-left" property value.
 * 
 * Sets the "margin-left" property of @fo_fo to @new_margin_left.
 **/
void
fo_block_set_margin_left (FoFo *fo_fo,
		         FoProperty *new_margin_left)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_margin_left == NULL) ||
		    FO_IS_PROPERTY_MARGIN_LEFT (new_margin_left));

  if (new_margin_left != NULL)
    {
      g_object_ref (new_margin_left);
    }
  if (fo_block->margin_left != NULL)
    {
      g_object_unref (fo_block->margin_left);
    }
  fo_block->margin_left = new_margin_left;
  /*g_object_notify (G_OBJECT (fo_block), "margin-left");*/
}

/**
 * fo_block_get_margin_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-right" property of @fo_fo.
 *
 * Return value: The "margin-right" property value.
**/
FoProperty *
fo_block_get_margin_right (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->margin_right;
}

/**
 * fo_block_set_margin_right:
 * @fo_fo: The #FoFo object.
 * @new_margin_right: The new "margin-right" property value.
 * 
 * Sets the "margin-right" property of @fo_fo to @new_margin_right.
 **/
void
fo_block_set_margin_right (FoFo *fo_fo,
		         FoProperty *new_margin_right)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_margin_right == NULL) ||
		    FO_IS_PROPERTY_MARGIN_RIGHT (new_margin_right));

  if (new_margin_right != NULL)
    {
      g_object_ref (new_margin_right);
    }
  if (fo_block->margin_right != NULL)
    {
      g_object_unref (fo_block->margin_right);
    }
  fo_block->margin_right = new_margin_right;
  /*g_object_notify (G_OBJECT (fo_block), "margin-right");*/
}

/**
 * fo_block_get_margin_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-top" property of @fo_fo.
 *
 * Return value: The "margin-top" property value.
**/
FoProperty *
fo_block_get_margin_top (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->margin_top;
}

/**
 * fo_block_set_margin_top:
 * @fo_fo: The #FoFo object.
 * @new_margin_top: The new "margin-top" property value.
 * 
 * Sets the "margin-top" property of @fo_fo to @new_margin_top.
 **/
void
fo_block_set_margin_top (FoFo *fo_fo,
		         FoProperty *new_margin_top)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_margin_top == NULL) ||
		    FO_IS_PROPERTY_MARGIN_TOP (new_margin_top));

  if (new_margin_top != NULL)
    {
      g_object_ref (new_margin_top);
    }
  if (fo_block->margin_top != NULL)
    {
      g_object_unref (fo_block->margin_top);
    }
  fo_block->margin_top = new_margin_top;
  /*g_object_notify (G_OBJECT (fo_block), "margin-top");*/
}

/**
 * fo_block_get_orphans:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "orphans" property of @fo_fo.
 *
 * Return value: The "orphans" property value.
**/
FoProperty *
fo_block_get_orphans (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->orphans;
}

/**
 * fo_block_set_orphans:
 * @fo_fo: The #FoFo object.
 * @new_orphans: The new "orphans" property value.
 * 
 * Sets the "orphans" property of @fo_fo to @new_orphans.
 **/
void
fo_block_set_orphans (FoFo *fo_fo,
		         FoProperty *new_orphans)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_orphans == NULL) ||
		    FO_IS_PROPERTY_ORPHANS (new_orphans));

  if (new_orphans != NULL)
    {
      g_object_ref (new_orphans);
    }
  if (fo_block->orphans != NULL)
    {
      g_object_unref (fo_block->orphans);
    }
  fo_block->orphans = new_orphans;
  /*g_object_notify (G_OBJECT (fo_block), "orphans");*/
}

/**
 * fo_block_get_padding_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-after" property of @fo_fo.
 *
 * Return value: The "padding-after" property value.
**/
FoProperty *
fo_block_get_padding_after (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->padding_after;
}

/**
 * fo_block_set_padding_after:
 * @fo_fo: The #FoFo object.
 * @new_padding_after: The new "padding-after" property value.
 * 
 * Sets the "padding-after" property of @fo_fo to @new_padding_after.
 **/
void
fo_block_set_padding_after (FoFo *fo_fo,
		         FoProperty *new_padding_after)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_padding_after == NULL) ||
		    FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref (new_padding_after);
    }
  if (fo_block->padding_after != NULL)
    {
      g_object_unref (fo_block->padding_after);
    }
  fo_block->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_block), "padding-after");*/
}

/**
 * fo_block_get_padding_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-before" property of @fo_fo.
 *
 * Return value: The "padding-before" property value.
**/
FoProperty *
fo_block_get_padding_before (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->padding_before;
}

/**
 * fo_block_set_padding_before:
 * @fo_fo: The #FoFo object.
 * @new_padding_before: The new "padding-before" property value.
 * 
 * Sets the "padding-before" property of @fo_fo to @new_padding_before.
 **/
void
fo_block_set_padding_before (FoFo *fo_fo,
		         FoProperty *new_padding_before)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_padding_before == NULL) ||
		    FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref (new_padding_before);
    }
  if (fo_block->padding_before != NULL)
    {
      g_object_unref (fo_block->padding_before);
    }
  fo_block->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_block), "padding-before");*/
}

/**
 * fo_block_get_padding_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-bottom" property of @fo_fo.
 *
 * Return value: The "padding-bottom" property value.
**/
FoProperty *
fo_block_get_padding_bottom (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->padding_bottom;
}

/**
 * fo_block_set_padding_bottom:
 * @fo_fo: The #FoFo object.
 * @new_padding_bottom: The new "padding-bottom" property value.
 * 
 * Sets the "padding-bottom" property of @fo_fo to @new_padding_bottom.
 **/
void
fo_block_set_padding_bottom (FoFo *fo_fo,
		         FoProperty *new_padding_bottom)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_padding_bottom == NULL) ||
		    FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref (new_padding_bottom);
    }
  if (fo_block->padding_bottom != NULL)
    {
      g_object_unref (fo_block->padding_bottom);
    }
  fo_block->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_block), "padding-bottom");*/
}

/**
 * fo_block_get_padding_end:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-end" property of @fo_fo.
 *
 * Return value: The "padding-end" property value.
**/
FoProperty *
fo_block_get_padding_end (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->padding_end;
}

/**
 * fo_block_set_padding_end:
 * @fo_fo: The #FoFo object.
 * @new_padding_end: The new "padding-end" property value.
 * 
 * Sets the "padding-end" property of @fo_fo to @new_padding_end.
 **/
void
fo_block_set_padding_end (FoFo *fo_fo,
		         FoProperty *new_padding_end)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_padding_end == NULL) ||
		    FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref (new_padding_end);
    }
  if (fo_block->padding_end != NULL)
    {
      g_object_unref (fo_block->padding_end);
    }
  fo_block->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_block), "padding-end");*/
}

/**
 * fo_block_get_padding_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-left" property of @fo_fo.
 *
 * Return value: The "padding-left" property value.
**/
FoProperty *
fo_block_get_padding_left (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->padding_left;
}

/**
 * fo_block_set_padding_left:
 * @fo_fo: The #FoFo object.
 * @new_padding_left: The new "padding-left" property value.
 * 
 * Sets the "padding-left" property of @fo_fo to @new_padding_left.
 **/
void
fo_block_set_padding_left (FoFo *fo_fo,
		         FoProperty *new_padding_left)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_padding_left == NULL) ||
		    FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref (new_padding_left);
    }
  if (fo_block->padding_left != NULL)
    {
      g_object_unref (fo_block->padding_left);
    }
  fo_block->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_block), "padding-left");*/
}

/**
 * fo_block_get_padding_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-right" property of @fo_fo.
 *
 * Return value: The "padding-right" property value.
**/
FoProperty *
fo_block_get_padding_right (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->padding_right;
}

/**
 * fo_block_set_padding_right:
 * @fo_fo: The #FoFo object.
 * @new_padding_right: The new "padding-right" property value.
 * 
 * Sets the "padding-right" property of @fo_fo to @new_padding_right.
 **/
void
fo_block_set_padding_right (FoFo *fo_fo,
		         FoProperty *new_padding_right)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_padding_right == NULL) ||
		    FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref (new_padding_right);
    }
  if (fo_block->padding_right != NULL)
    {
      g_object_unref (fo_block->padding_right);
    }
  fo_block->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_block), "padding-right");*/
}

/**
 * fo_block_get_padding_start:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-start" property of @fo_fo.
 *
 * Return value: The "padding-start" property value.
**/
FoProperty *
fo_block_get_padding_start (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->padding_start;
}

/**
 * fo_block_set_padding_start:
 * @fo_fo: The #FoFo object.
 * @new_padding_start: The new "padding-start" property value.
 * 
 * Sets the "padding-start" property of @fo_fo to @new_padding_start.
 **/
void
fo_block_set_padding_start (FoFo *fo_fo,
		         FoProperty *new_padding_start)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_padding_start == NULL) ||
		    FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref (new_padding_start);
    }
  if (fo_block->padding_start != NULL)
    {
      g_object_unref (fo_block->padding_start);
    }
  fo_block->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_block), "padding-start");*/
}

/**
 * fo_block_get_padding_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-top" property of @fo_fo.
 *
 * Return value: The "padding-top" property value.
**/
FoProperty *
fo_block_get_padding_top (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->padding_top;
}

/**
 * fo_block_set_padding_top:
 * @fo_fo: The #FoFo object.
 * @new_padding_top: The new "padding-top" property value.
 * 
 * Sets the "padding-top" property of @fo_fo to @new_padding_top.
 **/
void
fo_block_set_padding_top (FoFo *fo_fo,
		         FoProperty *new_padding_top)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_padding_top == NULL) ||
		    FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref (new_padding_top);
    }
  if (fo_block->padding_top != NULL)
    {
      g_object_unref (fo_block->padding_top);
    }
  fo_block->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_block), "padding-top");*/
}

/**
 * fo_block_get_role:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "role" property of @fo_fo.
 *
 * Return value: The "role" property value.
**/
FoProperty *
fo_block_get_role (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->role;
}

/**
 * fo_block_set_role:
 * @fo_fo: The #FoFo object.
 * @new_role: The new "role" property value.
 * 
 * Sets the "role" property of @fo_fo to @new_role.
 **/
void
fo_block_set_role (FoFo *fo_fo,
		         FoProperty *new_role)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_role == NULL) ||
		    FO_IS_PROPERTY_ROLE (new_role));

  if (new_role != NULL)
    {
      g_object_ref (new_role);
    }
  if (fo_block->role != NULL)
    {
      g_object_unref (fo_block->role);
    }
  fo_block->role = new_role;
  /*g_object_notify (G_OBJECT (fo_block), "role");*/
}

/**
 * fo_block_get_source_document:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "source-document" property of @fo_fo.
 *
 * Return value: The "source-document" property value.
**/
FoProperty *
fo_block_get_source_document (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->source_document;
}

/**
 * fo_block_set_source_document:
 * @fo_fo: The #FoFo object.
 * @new_source_document: The new "source-document" property value.
 * 
 * Sets the "source-document" property of @fo_fo to @new_source_document.
 **/
void
fo_block_set_source_document (FoFo *fo_fo,
		         FoProperty *new_source_document)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_source_document == NULL) ||
		    FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document != NULL)
    {
      g_object_ref (new_source_document);
    }
  if (fo_block->source_document != NULL)
    {
      g_object_unref (fo_block->source_document);
    }
  fo_block->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_block), "source-document");*/
}

/**
 * fo_block_get_space_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-after" property of @fo_fo.
 *
 * Return value: The "space-after" property value.
**/
FoProperty *
fo_block_get_space_after (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->space_after;
}

/**
 * fo_block_set_space_after:
 * @fo_fo: The #FoFo object.
 * @new_space_after: The new "space-after" property value.
 * 
 * Sets the "space-after" property of @fo_fo to @new_space_after.
 **/
void
fo_block_set_space_after (FoFo *fo_fo,
		         FoProperty *new_space_after)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_space_after == NULL) ||
		    FO_IS_PROPERTY_SPACE_AFTER (new_space_after));

  if (new_space_after != NULL)
    {
      g_object_ref (new_space_after);
    }
  if (fo_block->space_after != NULL)
    {
      g_object_unref (fo_block->space_after);
    }
  fo_block->space_after = new_space_after;
  /*g_object_notify (G_OBJECT (fo_block), "space-after");*/
}

/**
 * fo_block_get_space_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-before" property of @fo_fo.
 *
 * Return value: The "space-before" property value.
**/
FoProperty *
fo_block_get_space_before (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->space_before;
}

/**
 * fo_block_set_space_before:
 * @fo_fo: The #FoFo object.
 * @new_space_before: The new "space-before" property value.
 * 
 * Sets the "space-before" property of @fo_fo to @new_space_before.
 **/
void
fo_block_set_space_before (FoFo *fo_fo,
		         FoProperty *new_space_before)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_space_before == NULL) ||
		    FO_IS_PROPERTY_SPACE_BEFORE (new_space_before));

  if (new_space_before != NULL)
    {
      g_object_ref (new_space_before);
    }
  if (fo_block->space_before != NULL)
    {
      g_object_unref (fo_block->space_before);
    }
  fo_block->space_before = new_space_before;
  /*g_object_notify (G_OBJECT (fo_block), "space-before");*/
}

/**
 * fo_block_get_span:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "span" property of @fo_fo.
 *
 * Return value: The "span" property value.
**/
FoProperty *
fo_block_get_span (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->span;
}

/**
 * fo_block_set_span:
 * @fo_fo: The #FoFo object.
 * @new_span: The new "span" property value.
 * 
 * Sets the "span" property of @fo_fo to @new_span.
 **/
void
fo_block_set_span (FoFo *fo_fo,
		         FoProperty *new_span)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_span == NULL) ||
		    FO_IS_PROPERTY_SPAN (new_span));

  if (new_span != NULL)
    {
      g_object_ref (new_span);
    }
  if (fo_block->span != NULL)
    {
      g_object_unref (fo_block->span);
    }
  fo_block->span = new_span;
  /*g_object_notify (G_OBJECT (fo_block), "span");*/
}

/**
 * fo_block_get_start_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "start-indent" property of @fo_fo.
 *
 * Return value: The "start-indent" property value.
**/
FoProperty *
fo_block_get_start_indent (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->start_indent;
}

/**
 * fo_block_set_start_indent:
 * @fo_fo: The #FoFo object.
 * @new_start_indent: The new "start-indent" property value.
 * 
 * Sets the "start-indent" property of @fo_fo to @new_start_indent.
 **/
void
fo_block_set_start_indent (FoFo *fo_fo,
		         FoProperty *new_start_indent)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_start_indent == NULL) ||
		    FO_IS_PROPERTY_START_INDENT (new_start_indent));

  if (new_start_indent != NULL)
    {
      g_object_ref (new_start_indent);
    }
  if (fo_block->start_indent != NULL)
    {
      g_object_unref (fo_block->start_indent);
    }
  fo_block->start_indent = new_start_indent;
  /*g_object_notify (G_OBJECT (fo_block), "start-indent");*/
}

/**
 * fo_block_get_text_align:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "text-align" property of @fo_fo.
 *
 * Return value: The "text-align" property value.
**/
FoProperty *
fo_block_get_text_align (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->text_align;
}

/**
 * fo_block_set_text_align:
 * @fo_fo: The #FoFo object.
 * @new_text_align: The new "text-align" property value.
 * 
 * Sets the "text-align" property of @fo_fo to @new_text_align.
 **/
void
fo_block_set_text_align (FoFo *fo_fo,
		         FoProperty *new_text_align)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_text_align == NULL) ||
		    FO_IS_PROPERTY_TEXT_ALIGN (new_text_align));

  if (new_text_align != NULL)
    {
      g_object_ref (new_text_align);
    }
  if (fo_block->text_align != NULL)
    {
      g_object_unref (fo_block->text_align);
    }
  fo_block->text_align = new_text_align;
  /*g_object_notify (G_OBJECT (fo_block), "text-align");*/
}

/**
 * fo_block_get_text_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "text-indent" property of @fo_fo.
 *
 * Return value: The "text-indent" property value.
**/
FoProperty *
fo_block_get_text_indent (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->text_indent;
}

/**
 * fo_block_set_text_indent:
 * @fo_fo: The #FoFo object.
 * @new_text_indent: The new "text-indent" property value.
 * 
 * Sets the "text-indent" property of @fo_fo to @new_text_indent.
 **/
void
fo_block_set_text_indent (FoFo *fo_fo,
		         FoProperty *new_text_indent)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_text_indent == NULL) ||
		    FO_IS_PROPERTY_TEXT_INDENT (new_text_indent));

  if (new_text_indent != NULL)
    {
      g_object_ref (new_text_indent);
    }
  if (fo_block->text_indent != NULL)
    {
      g_object_unref (fo_block->text_indent);
    }
  fo_block->text_indent = new_text_indent;
  /*g_object_notify (G_OBJECT (fo_block), "text-indent");*/
}

/**
 * fo_block_get_white_space_collapse:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "white-space-collapse" property of @fo_fo.
 *
 * Return value: The "white-space-collapse" property value.
**/
FoProperty *
fo_block_get_white_space_collapse (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->white_space_collapse;
}

/**
 * fo_block_set_white_space_collapse:
 * @fo_fo: The #FoFo object.
 * @new_white_space_collapse: The new "white-space-collapse" property value.
 * 
 * Sets the "white-space-collapse" property of @fo_fo to @new_white_space_collapse.
 **/
void
fo_block_set_white_space_collapse (FoFo *fo_fo,
		         FoProperty *new_white_space_collapse)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_white_space_collapse == NULL) ||
		    FO_IS_PROPERTY_WHITE_SPACE_COLLAPSE (new_white_space_collapse));

  if (new_white_space_collapse != NULL)
    {
      g_object_ref (new_white_space_collapse);
    }
  if (fo_block->white_space_collapse != NULL)
    {
      g_object_unref (fo_block->white_space_collapse);
    }
  fo_block->white_space_collapse = new_white_space_collapse;
  /*g_object_notify (G_OBJECT (fo_block), "white-space-collapse");*/
}

/**
 * fo_block_get_white_space_treatment:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "white-space-treatment" property of @fo_fo.
 *
 * Return value: The "white-space-treatment" property value.
**/
FoProperty *
fo_block_get_white_space_treatment (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->white_space_treatment;
}

/**
 * fo_block_set_white_space_treatment:
 * @fo_fo: The #FoFo object.
 * @new_white_space_treatment: The new "white-space-treatment" property value.
 * 
 * Sets the "white-space-treatment" property of @fo_fo to @new_white_space_treatment.
 **/
void
fo_block_set_white_space_treatment (FoFo *fo_fo,
		         FoProperty *new_white_space_treatment)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_white_space_treatment == NULL) ||
		    FO_IS_PROPERTY_WHITE_SPACE_TREATMENT (new_white_space_treatment));

  if (new_white_space_treatment != NULL)
    {
      g_object_ref (new_white_space_treatment);
    }
  if (fo_block->white_space_treatment != NULL)
    {
      g_object_unref (fo_block->white_space_treatment);
    }
  fo_block->white_space_treatment = new_white_space_treatment;
  /*g_object_notify (G_OBJECT (fo_block), "white-space-treatment");*/
}

/**
 * fo_block_get_widows:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "widows" property of @fo_fo.
 *
 * Return value: The "widows" property value.
**/
FoProperty *
fo_block_get_widows (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->widows;
}

/**
 * fo_block_set_widows:
 * @fo_fo: The #FoFo object.
 * @new_widows: The new "widows" property value.
 * 
 * Sets the "widows" property of @fo_fo to @new_widows.
 **/
void
fo_block_set_widows (FoFo *fo_fo,
		         FoProperty *new_widows)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_widows == NULL) ||
		    FO_IS_PROPERTY_WIDOWS (new_widows));

  if (new_widows != NULL)
    {
      g_object_ref (new_widows);
    }
  if (fo_block->widows != NULL)
    {
      g_object_unref (fo_block->widows);
    }
  fo_block->widows = new_widows;
  /*g_object_notify (G_OBJECT (fo_block), "widows");*/
}

/**
 * fo_block_get_wrap_option:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "wrap-option" property of @fo_fo.
 *
 * Return value: The "wrap-option" property value.
**/
FoProperty *
fo_block_get_wrap_option (FoFo *fo_fo)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_val_if_fail (fo_block != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK (fo_block), NULL);

  return fo_block->wrap_option;
}

/**
 * fo_block_set_wrap_option:
 * @fo_fo: The #FoFo object.
 * @new_wrap_option: The new "wrap-option" property value.
 * 
 * Sets the "wrap-option" property of @fo_fo to @new_wrap_option.
 **/
void
fo_block_set_wrap_option (FoFo *fo_fo,
		         FoProperty *new_wrap_option)
{
  FoBlock *fo_block = (FoBlock *) fo_fo;

  g_return_if_fail (fo_block != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo_block));
  g_return_if_fail ((new_wrap_option == NULL) ||
		    FO_IS_PROPERTY_WRAP_OPTION (new_wrap_option));

  if (new_wrap_option != NULL)
    {
      g_object_ref (new_wrap_option);
    }
  if (fo_block->wrap_option != NULL)
    {
      g_object_unref (fo_block->wrap_option);
    }
  fo_block->wrap_option = new_wrap_option;
  /*g_object_notify (G_OBJECT (fo_block), "wrap-option");*/
}
