/* Fo
 * fo-inline.c: 'inline' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-fo.h"
#include "fo-fo-private.h"
#include "fo-inline-fo.h"
#include "fo-inline.h"
#include "fo-inline-private.h"
#include "fo-context-util.h"
#include "property/fo-property-common-font.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-alignment-adjust.h"
#include "property/fo-property-alignment-baseline.h"
#include "property/fo-property-background-color.h"
#include "property/fo-property-background-image.h"
#include "property/fo-property-baseline-shift.h"
#include "property/fo-property-block-progression-dimension.h"
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
#include "property/fo-property-color.h"
#include "property/fo-property-dominant-baseline.h"
#include "property/fo-property-font-family.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-stretch.h"
#include "property/fo-property-font-style.h"
#include "property/fo-property-font-variant.h"
#include "property/fo-property-font-weight.h"
#include "property/fo-property-height.h"
#include "property/fo-property-id.h"
#include "property/fo-property-inline-progression-dimension.h"
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
#include "property/fo-property-space-end.h"
#include "property/fo-property-space-start.h"
#include "property/fo-property-width.h"
#include "property/fo-property-wrap-option.h"

enum {
  PROP_0,
  PROP_ALIGNMENT_ADJUST,
  PROP_ALIGNMENT_BASELINE,
  PROP_BACKGROUND_COLOR,
  PROP_BACKGROUND_IMAGE,
  PROP_BASELINE_SHIFT,
  PROP_BLOCK_PROGRESSION_DIMENSION,
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
  PROP_COLOR,
  PROP_DOMINANT_BASELINE,
  PROP_FONT_FAMILY,
  PROP_FONT_SIZE,
  PROP_FONT_STRETCH,
  PROP_FONT_STYLE,
  PROP_FONT_VARIANT,
  PROP_FONT_WEIGHT,
  PROP_HEIGHT,
  PROP_ID,
  PROP_INLINE_PROGRESSION_DIMENSION,
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
  PROP_SPACE_END,
  PROP_SPACE_START,
  PROP_WIDTH,
  PROP_WRAP_OPTION
};

static void fo_inline_class_init  (FoInlineClass *klass);
static void fo_inline_inline_fo_init (FoInlineFoIface *iface);
static void fo_inline_get_property (GObject      *object,
                                    guint         prop_id,
                                    GValue       *value,
                                    GParamSpec   *pspec);
static void fo_inline_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec);
static void fo_inline_finalize    (GObject           *object);
static gboolean fo_inline_validate_content (FoFo    *fo,
                                            GError **error);
static void fo_inline_validate (FoFo      *fo,
                                FoContext *current_context,
                                FoContext *parent_context,
                                GError   **error);
static void fo_inline_update_from_context (FoFo      *fo,
                                           FoContext *context);
static void fo_inline_debug_dump_properties (FoFo *fo,
                                             gint  depth);
static void fo_inline_get_text_attr_list (FoFo *fo_inline_fo,
					  FoDoc   *fo_doc,
					  GString *text,
					  GList **attr_glist,
					  guint debug_level);

static gpointer parent_class;

/**
 * fo_inline_get_type:
 * 
 * Register the #FoInline object type.
 * 
 * Return value: #GType value of the #FoInline object type.
 **/
GType
fo_inline_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoInlineClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_inline_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoInline),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_inline_fo_info =
      {
	(GInterfaceInitFunc) fo_inline_inline_fo_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "inline",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &fo_inline_fo_info);
    }

  return object_type;
}

/**
 * fo_inline_class_init:
 * @klass: #FoInlineClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoInlineClass.
 **/
void
fo_inline_class_init (FoInlineClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_inline_finalize;

  object_class->get_property = fo_inline_get_property;
  object_class->set_property = fo_inline_set_property;

  fofo_class->validate_content = fo_inline_validate_content;
  fofo_class->validate2 = fo_inline_validate;
  fofo_class->update_from_context = fo_inline_update_from_context;
  fofo_class->debug_dump_properties = fo_inline_debug_dump_properties;
  fofo_class->allow_mixed_content = TRUE;

  g_object_class_install_property
    (object_class,
     PROP_ALIGNMENT_ADJUST,
     g_param_spec_object ("alignment-adjust",
			  _("Alignment Adjust"),
			  _("Alignment Adjust property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ALIGNMENT_BASELINE,
     g_param_spec_object ("alignment-baseline",
			  _("Alignment Baseline"),
			  _("Alignment Baseline property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
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
     PROP_BASELINE_SHIFT,
     g_param_spec_object ("baseline-shift",
			  _("Baseline Shift"),
			  _("Baseline Shift property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BLOCK_PROGRESSION_DIMENSION,
     g_param_spec_object ("block-progression-dimension",
			  _("Block Progression Dimension"),
			  _("Block Progression Dimension property"),
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
     PROP_COLOR,
     g_param_spec_object ("color",
			  _("Color"),
			  _("Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_DOMINANT_BASELINE,
     g_param_spec_object ("dominant-baseline",
			  _("Dominant Baseline"),
			  _("Dominant Baseline property"),
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
     PROP_HEIGHT,
     g_param_spec_object ("height",
			  _("Height"),
			  _("Height property"),
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
     PROP_INLINE_PROGRESSION_DIMENSION,
     g_param_spec_object ("inline-progression-dimension",
			  _("Inline Progression Dimension"),
			  _("Inline Progression Dimension property"),
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
     PROP_SPACE_END,
     g_param_spec_object ("space-end",
			  _("Space End"),
			  _("Space End property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_START,
     g_param_spec_object ("space-start",
			  _("Space Start"),
			  _("Space Start property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WIDTH,
     g_param_spec_object ("width",
			  _("Width"),
			  _("Width property"),
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
 * fo_inline_inline_fo_init:
 * @iface: #FoInlineFoIFace structure for this class.
 * 
 * Initialize #FoInlineFoIface interface for this class.
 **/
void
fo_inline_inline_fo_init (FoInlineFoIface *iface)
{
  iface->get_text_attr_list = fo_inline_get_text_attr_list;
}

/**
 * fo_inline_finalize:
 * @object: #FoInline object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoInline.
 **/
void
fo_inline_finalize (GObject *object)
{
  FoInline *fo_inline;

  fo_inline = FO_INLINE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_inline_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoInline.
 **/
void
fo_inline_get_property (GObject    *object,
                        guint       prop_id,
                        GValue     *value,
                        GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ALIGNMENT_ADJUST:
      g_value_set_object (value, G_OBJECT (fo_inline_get_alignment_adjust (fo_fo)));
      break;
    case PROP_ALIGNMENT_BASELINE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_alignment_baseline (fo_fo)));
      break;
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_background_color (fo_fo)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_background_image (fo_fo)));
      break;
    case PROP_BASELINE_SHIFT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_baseline_shift (fo_fo)));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION:
      g_value_set_object (value, G_OBJECT (fo_inline_get_block_progression_dimension (fo_fo)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_after_color (fo_fo)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_after_style (fo_fo)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_after_width (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_before_color (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_before_style (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_before_width (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_bottom_color (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_bottom_style (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_bottom_width (fo_fo)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_end_color (fo_fo)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_end_style (fo_fo)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_end_width (fo_fo)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_left_color (fo_fo)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_left_style (fo_fo)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_left_width (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_right_color (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_right_style (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_right_width (fo_fo)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_start_color (fo_fo)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_start_style (fo_fo)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_start_width (fo_fo)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_top_color (fo_fo)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_top_style (fo_fo)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_border_top_width (fo_fo)));
      break;
    case PROP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_inline_get_color (fo_fo)));
      break;
    case PROP_DOMINANT_BASELINE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_dominant_baseline (fo_fo)));
      break;
    case PROP_FONT_FAMILY:
      g_value_set_object (value, G_OBJECT (fo_inline_get_font_family (fo_fo)));
      break;
    case PROP_FONT_SIZE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_font_size (fo_fo)));
      break;
    case PROP_FONT_STRETCH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_font_stretch (fo_fo)));
      break;
    case PROP_FONT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_font_style (fo_fo)));
      break;
    case PROP_FONT_VARIANT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_font_variant (fo_fo)));
      break;
    case PROP_FONT_WEIGHT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_font_weight (fo_fo)));
      break;
    case PROP_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_height (fo_fo)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_inline_get_id (fo_fo)));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION:
      g_value_set_object (value, G_OBJECT (fo_inline_get_inline_progression_dimension (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_together (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_together_within_column (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_together_within_line (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_together_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_with_next (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_with_next_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_with_next_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_with_next_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_with_previous (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_with_previous_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_with_previous_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_keep_with_previous_within_page (fo_fo)));
      break;
    case PROP_LINE_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_line_height (fo_fo)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_inline_get_padding_after (fo_fo)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_padding_before (fo_fo)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_inline_get_padding_bottom (fo_fo)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_inline_get_padding_end (fo_fo)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_padding_left (fo_fo)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_padding_right (fo_fo)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_inline_get_padding_start (fo_fo)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_inline_get_padding_top (fo_fo)));
      break;
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_inline_get_role (fo_fo)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_inline_get_source_document (fo_fo)));
      break;
    case PROP_SPACE_END:
      g_value_set_object (value, G_OBJECT (fo_inline_get_space_end (fo_fo)));
      break;
    case PROP_SPACE_START:
      g_value_set_object (value, G_OBJECT (fo_inline_get_space_start (fo_fo)));
      break;
    case PROP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_inline_get_width (fo_fo)));
      break;
    case PROP_WRAP_OPTION:
      g_value_set_object (value, G_OBJECT (fo_inline_get_wrap_option (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_inline_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoInline.
 **/
void
fo_inline_set_property (GObject      *object,
                        guint         prop_id,
                        const GValue *value,
                        GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ALIGNMENT_ADJUST:
      fo_inline_set_alignment_adjust (fo_fo, g_value_get_object (value));
      break;
    case PROP_ALIGNMENT_BASELINE:
      fo_inline_set_alignment_baseline (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_COLOR:
      fo_inline_set_background_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_inline_set_background_image (fo_fo, g_value_get_object (value));
      break;
    case PROP_BASELINE_SHIFT:
      fo_inline_set_baseline_shift (fo_fo, g_value_get_object (value));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION:
      fo_inline_set_block_progression_dimension (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_inline_set_border_after_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_inline_set_border_after_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_inline_set_border_after_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_inline_set_border_before_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_inline_set_border_before_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_inline_set_border_before_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_inline_set_border_bottom_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_inline_set_border_bottom_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_inline_set_border_bottom_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_inline_set_border_end_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_inline_set_border_end_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_inline_set_border_end_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_inline_set_border_left_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_inline_set_border_left_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_inline_set_border_left_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_inline_set_border_right_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_inline_set_border_right_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_inline_set_border_right_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_inline_set_border_start_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_inline_set_border_start_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_inline_set_border_start_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_inline_set_border_top_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_inline_set_border_top_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_inline_set_border_top_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_COLOR:
      fo_inline_set_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_DOMINANT_BASELINE:
      fo_inline_set_dominant_baseline (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_FAMILY:
      fo_inline_set_font_family (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_SIZE:
      fo_inline_set_font_size (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_STRETCH:
      fo_inline_set_font_stretch (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_STYLE:
      fo_inline_set_font_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_VARIANT:
      fo_inline_set_font_variant (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_WEIGHT:
      fo_inline_set_font_weight (fo_fo, g_value_get_object (value));
      break;
    case PROP_HEIGHT:
      fo_inline_set_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_inline_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION:
      fo_inline_set_inline_progression_dimension (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER:
      fo_inline_set_keep_together (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      fo_inline_set_keep_together_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      fo_inline_set_keep_together_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      fo_inline_set_keep_together_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT:
      fo_inline_set_keep_with_next (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      fo_inline_set_keep_with_next_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      fo_inline_set_keep_with_next_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      fo_inline_set_keep_with_next_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      fo_inline_set_keep_with_previous (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      fo_inline_set_keep_with_previous_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      fo_inline_set_keep_with_previous_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      fo_inline_set_keep_with_previous_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_LINE_HEIGHT:
      fo_inline_set_line_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_inline_set_padding_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_inline_set_padding_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_inline_set_padding_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_inline_set_padding_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_inline_set_padding_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_inline_set_padding_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_inline_set_padding_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_inline_set_padding_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_ROLE:
      fo_inline_set_role (fo_fo, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_inline_set_source_document (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_END:
      fo_inline_set_space_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_START:
      fo_inline_set_space_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_WIDTH:
      fo_inline_set_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_WRAP_OPTION:
      fo_inline_set_wrap_option (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_inline_new:
 * 
 * Creates a new #FoInline initialized to default value.
 * 
 * Return value: the new #FoInline.
 **/
FoFo*
fo_inline_new (void)
{
  return FO_FO (g_object_new (fo_inline_get_type (), NULL));
}

/**
 * fo_inline_validate_content:
 * @fo:    #FoInline object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: FALSE indicates
 * content model is correct, or TRUE indicates an error.  When used
 * with fo_node_traverse(), returning TRUE stops the traversal.
 * 
 * Return value: FALSE if content model okay, TRUE if not.
 **/
gboolean
fo_inline_validate_content (FoFo    *fo,
                            GError **error)
{
  GError *tmp_error;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_INLINE (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  return FALSE;

/*
error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (fo));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
*/
}

/**
 * fo_inline_validate:
 * @fo:              #FoInline object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_inline_validate (FoFo      *fo,
                    FoContext *current_context,
                    FoContext *parent_context,
                    GError   **error)
{
  FoInline *fo_inline;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_INLINE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_inline = FO_INLINE (fo);

  fo_context_util_dominant_baseline_resolve (current_context, parent_context);
  fo_context_util_height_width_resolve (current_context, parent_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_inline_set_line_height (fo,
			     fo_property_line_height_resolve (fo_inline->line_height,
							      fo_inline->font_size));
}

/**
 * fo_inline_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_inline_update_from_context (FoFo *fo,
                               FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_INLINE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_inline_set_alignment_adjust (fo,
			  fo_context_get_alignment_adjust (context));
  fo_inline_set_alignment_baseline (fo,
			  fo_context_get_alignment_baseline (context));
  fo_inline_set_background_color (fo,
			  fo_context_get_background_color (context));
  fo_inline_set_background_image (fo,
			  fo_context_get_background_image (context));
  fo_inline_set_baseline_shift (fo,
			  fo_context_get_baseline_shift (context));
  fo_inline_set_block_progression_dimension (fo,
			  fo_context_get_block_progression_dimension (context));
  fo_inline_set_border_after_color (fo,
			  fo_context_get_border_after_color (context));
  fo_inline_set_border_after_style (fo,
			  fo_context_get_border_after_style (context));
  fo_inline_set_border_after_width (fo,
			  fo_context_get_border_after_width (context));
  fo_inline_set_border_before_color (fo,
			  fo_context_get_border_before_color (context));
  fo_inline_set_border_before_style (fo,
			  fo_context_get_border_before_style (context));
  fo_inline_set_border_before_width (fo,
			  fo_context_get_border_before_width (context));
  fo_inline_set_border_bottom_color (fo,
			  fo_context_get_border_bottom_color (context));
  fo_inline_set_border_bottom_style (fo,
			  fo_context_get_border_bottom_style (context));
  fo_inline_set_border_bottom_width (fo,
			  fo_context_get_border_bottom_width (context));
  fo_inline_set_border_end_color (fo,
			  fo_context_get_border_end_color (context));
  fo_inline_set_border_end_style (fo,
			  fo_context_get_border_end_style (context));
  fo_inline_set_border_end_width (fo,
			  fo_context_get_border_end_width (context));
  fo_inline_set_border_left_color (fo,
			  fo_context_get_border_left_color (context));
  fo_inline_set_border_left_style (fo,
			  fo_context_get_border_left_style (context));
  fo_inline_set_border_left_width (fo,
			  fo_context_get_border_left_width (context));
  fo_inline_set_border_right_color (fo,
			  fo_context_get_border_right_color (context));
  fo_inline_set_border_right_style (fo,
			  fo_context_get_border_right_style (context));
  fo_inline_set_border_right_width (fo,
			  fo_context_get_border_right_width (context));
  fo_inline_set_border_start_color (fo,
			  fo_context_get_border_start_color (context));
  fo_inline_set_border_start_style (fo,
			  fo_context_get_border_start_style (context));
  fo_inline_set_border_start_width (fo,
			  fo_context_get_border_start_width (context));
  fo_inline_set_border_top_color (fo,
			  fo_context_get_border_top_color (context));
  fo_inline_set_border_top_style (fo,
			  fo_context_get_border_top_style (context));
  fo_inline_set_border_top_width (fo,
			  fo_context_get_border_top_width (context));
  fo_inline_set_color (fo,
			  fo_context_get_color (context));
  fo_inline_set_dominant_baseline (fo,
			  fo_context_get_dominant_baseline (context));
  fo_inline_set_font_family (fo,
			  fo_context_get_font_family (context));
  fo_inline_set_font_size (fo,
			  fo_context_get_font_size (context));
  fo_inline_set_font_stretch (fo,
			  fo_context_get_font_stretch (context));
  fo_inline_set_font_style (fo,
			  fo_context_get_font_style (context));
  fo_inline_set_font_variant (fo,
			  fo_context_get_font_variant (context));
  fo_inline_set_font_weight (fo,
			  fo_context_get_font_weight (context));
  fo_inline_set_height (fo,
			  fo_context_get_height (context));
  fo_inline_set_id (fo,
			  fo_context_get_id (context));
  fo_inline_set_inline_progression_dimension (fo,
			  fo_context_get_inline_progression_dimension (context));
  fo_inline_set_keep_together (fo,
			  fo_context_get_keep_together (context));
  fo_inline_set_keep_together_within_column (fo,
			  fo_context_get_keep_together_within_column (context));
  fo_inline_set_keep_together_within_line (fo,
			  fo_context_get_keep_together_within_line (context));
  fo_inline_set_keep_together_within_page (fo,
			  fo_context_get_keep_together_within_page (context));
  fo_inline_set_keep_with_next (fo,
			  fo_context_get_keep_with_next (context));
  fo_inline_set_keep_with_next_within_column (fo,
			  fo_context_get_keep_with_next_within_column (context));
  fo_inline_set_keep_with_next_within_line (fo,
			  fo_context_get_keep_with_next_within_line (context));
  fo_inline_set_keep_with_next_within_page (fo,
			  fo_context_get_keep_with_next_within_page (context));
  fo_inline_set_keep_with_previous (fo,
			  fo_context_get_keep_with_previous (context));
  fo_inline_set_keep_with_previous_within_column (fo,
			  fo_context_get_keep_with_previous_within_column (context));
  fo_inline_set_keep_with_previous_within_line (fo,
			  fo_context_get_keep_with_previous_within_line (context));
  fo_inline_set_keep_with_previous_within_page (fo,
			  fo_context_get_keep_with_previous_within_page (context));
  fo_inline_set_line_height (fo,
			  fo_context_get_line_height (context));
  fo_inline_set_padding_after (fo,
			  fo_context_get_padding_after (context));
  fo_inline_set_padding_before (fo,
			  fo_context_get_padding_before (context));
  fo_inline_set_padding_bottom (fo,
			  fo_context_get_padding_bottom (context));
  fo_inline_set_padding_end (fo,
			  fo_context_get_padding_end (context));
  fo_inline_set_padding_left (fo,
			  fo_context_get_padding_left (context));
  fo_inline_set_padding_right (fo,
			  fo_context_get_padding_right (context));
  fo_inline_set_padding_start (fo,
			  fo_context_get_padding_start (context));
  fo_inline_set_padding_top (fo,
			  fo_context_get_padding_top (context));
  fo_inline_set_role (fo,
			  fo_context_get_role (context));
  fo_inline_set_source_document (fo,
			  fo_context_get_source_document (context));
  fo_inline_set_space_end (fo,
			  fo_context_get_space_end (context));
  fo_inline_set_space_start (fo,
			  fo_context_get_space_start (context));
  fo_inline_set_width (fo,
			  fo_context_get_width (context));
  fo_inline_set_wrap_option (fo,
			  fo_context_get_wrap_option (context));
}

/**
 * fo_inline_debug_dump_properties:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_inline_debug_dump_properties (FoFo *fo, gint depth)
{
  FoInline *fo_inline;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_INLINE (fo));

  fo_inline = FO_INLINE (fo);

  fo_object_debug_dump (fo_inline->alignment_adjust, depth);
  fo_object_debug_dump (fo_inline->alignment_baseline, depth);
  fo_object_debug_dump (fo_inline->background_color, depth);
  fo_object_debug_dump (fo_inline->background_image, depth);
  fo_object_debug_dump (fo_inline->baseline_shift, depth);
  fo_object_debug_dump (fo_inline->block_progression_dimension, depth);
  fo_object_debug_dump (fo_inline->border_after_color, depth);
  fo_object_debug_dump (fo_inline->border_after_style, depth);
  fo_object_debug_dump (fo_inline->border_after_width, depth);
  fo_object_debug_dump (fo_inline->border_before_color, depth);
  fo_object_debug_dump (fo_inline->border_before_style, depth);
  fo_object_debug_dump (fo_inline->border_before_width, depth);
  fo_object_debug_dump (fo_inline->border_bottom_color, depth);
  fo_object_debug_dump (fo_inline->border_bottom_style, depth);
  fo_object_debug_dump (fo_inline->border_bottom_width, depth);
  fo_object_debug_dump (fo_inline->border_end_color, depth);
  fo_object_debug_dump (fo_inline->border_end_style, depth);
  fo_object_debug_dump (fo_inline->border_end_width, depth);
  fo_object_debug_dump (fo_inline->border_left_color, depth);
  fo_object_debug_dump (fo_inline->border_left_style, depth);
  fo_object_debug_dump (fo_inline->border_left_width, depth);
  fo_object_debug_dump (fo_inline->border_right_color, depth);
  fo_object_debug_dump (fo_inline->border_right_style, depth);
  fo_object_debug_dump (fo_inline->border_right_width, depth);
  fo_object_debug_dump (fo_inline->border_start_color, depth);
  fo_object_debug_dump (fo_inline->border_start_style, depth);
  fo_object_debug_dump (fo_inline->border_start_width, depth);
  fo_object_debug_dump (fo_inline->border_top_color, depth);
  fo_object_debug_dump (fo_inline->border_top_style, depth);
  fo_object_debug_dump (fo_inline->border_top_width, depth);
  fo_object_debug_dump (fo_inline->color, depth);
  fo_object_debug_dump (fo_inline->dominant_baseline, depth);
  fo_object_debug_dump (fo_inline->font_family, depth);
  fo_object_debug_dump (fo_inline->font_size, depth);
  fo_object_debug_dump (fo_inline->font_stretch, depth);
  fo_object_debug_dump (fo_inline->font_style, depth);
  fo_object_debug_dump (fo_inline->font_variant, depth);
  fo_object_debug_dump (fo_inline->font_weight, depth);
  fo_object_debug_dump (fo_inline->height, depth);
  fo_object_debug_dump (fo_inline->id, depth);
  fo_object_debug_dump (fo_inline->inline_progression_dimension, depth);
  fo_object_debug_dump (fo_inline->keep_together, depth);
  fo_object_debug_dump (fo_inline->keep_together_within_column, depth);
  fo_object_debug_dump (fo_inline->keep_together_within_line, depth);
  fo_object_debug_dump (fo_inline->keep_together_within_page, depth);
  fo_object_debug_dump (fo_inline->keep_with_next, depth);
  fo_object_debug_dump (fo_inline->keep_with_next_within_column, depth);
  fo_object_debug_dump (fo_inline->keep_with_next_within_line, depth);
  fo_object_debug_dump (fo_inline->keep_with_next_within_page, depth);
  fo_object_debug_dump (fo_inline->keep_with_previous, depth);
  fo_object_debug_dump (fo_inline->keep_with_previous_within_column, depth);
  fo_object_debug_dump (fo_inline->keep_with_previous_within_line, depth);
  fo_object_debug_dump (fo_inline->keep_with_previous_within_page, depth);
  fo_object_debug_dump (fo_inline->line_height, depth);
  fo_object_debug_dump (fo_inline->padding_after, depth);
  fo_object_debug_dump (fo_inline->padding_before, depth);
  fo_object_debug_dump (fo_inline->padding_bottom, depth);
  fo_object_debug_dump (fo_inline->padding_end, depth);
  fo_object_debug_dump (fo_inline->padding_left, depth);
  fo_object_debug_dump (fo_inline->padding_right, depth);
  fo_object_debug_dump (fo_inline->padding_start, depth);
  fo_object_debug_dump (fo_inline->padding_top, depth);
  fo_object_debug_dump (fo_inline->role, depth);
  fo_object_debug_dump (fo_inline->source_document, depth);
  fo_object_debug_dump (fo_inline->space_end, depth);
  fo_object_debug_dump (fo_inline->space_start, depth);
  fo_object_debug_dump (fo_inline->width, depth);
  fo_object_debug_dump (fo_inline->wrap_option, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_inline_get_text_attr_list:
 * @fo_inline_fo: The #FoInlineFo object.
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO.
 * @attr_glist:   The list of #PangoAttribute for the inline FO.
 * @debug_level:  Debug level.
 * 
 * Gets the text of the inline FO and its associated list of #PangoAttribute.
 **/
void
fo_inline_get_text_attr_list (FoFo *fo_inline_fo,
			      FoDoc   *fo_doc,
			      GString *text,
			      GList **attr_glist,
			      guint debug_level)
{
  FoNode *fo_child_node;
  FoInline *fo_inline;
  GList *my_attr_glist = NULL;
  gint start_index, end_index;

  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline_fo));

  fo_inline = FO_INLINE (fo_inline_fo);

  start_index = text->len;

  fo_child_node = fo_node_first_child (FO_NODE (fo_inline_fo));

  while (fo_child_node)
    {
      fo_inline_fo_get_text_attr_list (FO_FO (fo_child_node),
				       fo_doc,
				       text,
				       &my_attr_glist,
				       debug_level);
      fo_child_node = fo_node_next_sibling (fo_child_node);
    }

  end_index = text->len;

  if (start_index != end_index)
    {
      PangoAttribute *pango_attr;

      my_attr_glist =
	g_list_concat (my_attr_glist,
		       fo_property_common_font_get_pango_attrs (fo_inline->font_family,
								fo_inline->font_size,
								fo_inline->font_stretch,
								fo_inline->font_style,
								fo_inline->font_variant,
								fo_inline->font_weight,
								start_index,
								end_index));
      pango_attr =
	fo_property_text_property_new_attr (fo_inline->baseline_shift);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
      /*
      pango_attr =
	fo_property_text_property_new_attr (fo_inline->line_height);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
      */
      pango_attr =
	fo_property_text_property_new_attr (fo_inline->color);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      if (FO_IS_COLOR (fo_property_get_value (fo_inline->background_color)))
	{
	  pango_attr =
	    fo_property_text_property_new_attr (fo_inline->background_color);
	  pango_attr->start_index = start_index;
	  pango_attr->end_index = end_index;
	  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
	}
      /*
      pango_attr =
	fo_property_text_property_new_attr (fo_inline->alignment_adjust);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_inline->alignment_baseline);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr_from_context (fo_inline->dominant_baseline,
							 fo_fo_get_context (fo_inline_fo));
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_inline->keep_together_within_line);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_inline->keep_with_next_within_line);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_inline->keep_with_previous_within_line);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
      */
    }

  *attr_glist = g_list_concat (my_attr_glist,
			       *attr_glist);
}

/**
 * fo_inline_get_alignment_adjust:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "alignment-adjust" property of @fo_fo
 *
 * Return value: The "alignment-adjust" property value
**/
FoProperty*
fo_inline_get_alignment_adjust (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->alignment_adjust;
}

/**
 * fo_inline_set_alignment_adjust:
 * @fo_fo: The #FoFo object
 * @new_alignment_adjust: The new "alignment-adjust" property value
 * 
 * Sets the "alignment-adjust" property of @fo_fo to @new_alignment_adjust
 **/
void
fo_inline_set_alignment_adjust (FoFo *fo_fo,
		         FoProperty *new_alignment_adjust)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_ALIGNMENT_ADJUST (new_alignment_adjust));

  if (new_alignment_adjust != NULL)
    {
      g_object_ref (new_alignment_adjust);
    }
  if (fo_inline->alignment_adjust != NULL)
    {
      g_object_unref (fo_inline->alignment_adjust);
    }
  fo_inline->alignment_adjust = new_alignment_adjust;
  /*g_object_notify (G_OBJECT (fo_inline), "alignment-adjust");*/
}

/**
 * fo_inline_get_alignment_baseline:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "alignment-baseline" property of @fo_fo
 *
 * Return value: The "alignment-baseline" property value
**/
FoProperty*
fo_inline_get_alignment_baseline (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->alignment_baseline;
}

/**
 * fo_inline_set_alignment_baseline:
 * @fo_fo: The #FoFo object
 * @new_alignment_baseline: The new "alignment-baseline" property value
 * 
 * Sets the "alignment-baseline" property of @fo_fo to @new_alignment_baseline
 **/
void
fo_inline_set_alignment_baseline (FoFo *fo_fo,
		         FoProperty *new_alignment_baseline)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_ALIGNMENT_BASELINE (new_alignment_baseline));

  if (new_alignment_baseline != NULL)
    {
      g_object_ref (new_alignment_baseline);
    }
  if (fo_inline->alignment_baseline != NULL)
    {
      g_object_unref (fo_inline->alignment_baseline);
    }
  fo_inline->alignment_baseline = new_alignment_baseline;
  /*g_object_notify (G_OBJECT (fo_inline), "alignment-baseline");*/
}

/**
 * fo_inline_get_background_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "background-color" property of @fo_fo
 *
 * Return value: The "background-color" property value
**/
FoProperty*
fo_inline_get_background_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->background_color;
}

/**
 * fo_inline_set_background_color:
 * @fo_fo: The #FoFo object
 * @new_background_color: The new "background-color" property value
 * 
 * Sets the "background-color" property of @fo_fo to @new_background_color
 **/
void
fo_inline_set_background_color (FoFo *fo_fo,
		         FoProperty *new_background_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref (new_background_color);
    }
  if (fo_inline->background_color != NULL)
    {
      g_object_unref (fo_inline->background_color);
    }
  fo_inline->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_inline), "background-color");*/
}

/**
 * fo_inline_get_background_image:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "background-image" property of @fo_fo
 *
 * Return value: The "background-image" property value
**/
FoProperty*
fo_inline_get_background_image (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->background_image;
}

/**
 * fo_inline_set_background_image:
 * @fo_fo: The #FoFo object
 * @new_background_image: The new "background-image" property value
 * 
 * Sets the "background-image" property of @fo_fo to @new_background_image
 **/
void
fo_inline_set_background_image (FoFo *fo_fo,
		         FoProperty *new_background_image)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref (new_background_image);
    }
  if (fo_inline->background_image != NULL)
    {
      g_object_unref (fo_inline->background_image);
    }
  fo_inline->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_inline), "background-image");*/
}

/**
 * fo_inline_get_baseline_shift:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "baseline-shift" property of @fo_fo
 *
 * Return value: The "baseline-shift" property value
**/
FoProperty*
fo_inline_get_baseline_shift (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->baseline_shift;
}

/**
 * fo_inline_set_baseline_shift:
 * @fo_fo: The #FoFo object
 * @new_baseline_shift: The new "baseline-shift" property value
 * 
 * Sets the "baseline-shift" property of @fo_fo to @new_baseline_shift
 **/
void
fo_inline_set_baseline_shift (FoFo *fo_fo,
		         FoProperty *new_baseline_shift)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BASELINE_SHIFT (new_baseline_shift));

  if (new_baseline_shift != NULL)
    {
      g_object_ref (new_baseline_shift);
    }
  if (fo_inline->baseline_shift != NULL)
    {
      g_object_unref (fo_inline->baseline_shift);
    }
  fo_inline->baseline_shift = new_baseline_shift;
  /*g_object_notify (G_OBJECT (fo_inline), "baseline-shift");*/
}

/**
 * fo_inline_get_block_progression_dimension:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "block-progression-dimension" property of @fo_fo
 *
 * Return value: The "block-progression-dimension" property value
**/
FoProperty*
fo_inline_get_block_progression_dimension (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->block_progression_dimension;
}

/**
 * fo_inline_set_block_progression_dimension:
 * @fo_fo: The #FoFo object
 * @new_block_progression_dimension: The new "block-progression-dimension" property value
 * 
 * Sets the "block-progression-dimension" property of @fo_fo to @new_block_progression_dimension
 **/
void
fo_inline_set_block_progression_dimension (FoFo *fo_fo,
		         FoProperty *new_block_progression_dimension)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION (new_block_progression_dimension));

  if (new_block_progression_dimension != NULL)
    {
      g_object_ref (new_block_progression_dimension);
    }
  if (fo_inline->block_progression_dimension != NULL)
    {
      g_object_unref (fo_inline->block_progression_dimension);
    }
  fo_inline->block_progression_dimension = new_block_progression_dimension;
  /*g_object_notify (G_OBJECT (fo_inline), "block-progression-dimension");*/
}

/**
 * fo_inline_get_border_after_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-after-color" property of @fo_fo
 *
 * Return value: The "border-after-color" property value
**/
FoProperty*
fo_inline_get_border_after_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_after_color;
}

/**
 * fo_inline_set_border_after_color:
 * @fo_fo: The #FoFo object
 * @new_border_after_color: The new "border-after-color" property value
 * 
 * Sets the "border-after-color" property of @fo_fo to @new_border_after_color
 **/
void
fo_inline_set_border_after_color (FoFo *fo_fo,
		         FoProperty *new_border_after_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref (new_border_after_color);
    }
  if (fo_inline->border_after_color != NULL)
    {
      g_object_unref (fo_inline->border_after_color);
    }
  fo_inline->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_inline), "border-after-color");*/
}

/**
 * fo_inline_get_border_after_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-after-style" property of @fo_fo
 *
 * Return value: The "border-after-style" property value
**/
FoProperty*
fo_inline_get_border_after_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_after_style;
}

/**
 * fo_inline_set_border_after_style:
 * @fo_fo: The #FoFo object
 * @new_border_after_style: The new "border-after-style" property value
 * 
 * Sets the "border-after-style" property of @fo_fo to @new_border_after_style
 **/
void
fo_inline_set_border_after_style (FoFo *fo_fo,
		         FoProperty *new_border_after_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref (new_border_after_style);
    }
  if (fo_inline->border_after_style != NULL)
    {
      g_object_unref (fo_inline->border_after_style);
    }
  fo_inline->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_inline), "border-after-style");*/
}

/**
 * fo_inline_get_border_after_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-after-width" property of @fo_fo
 *
 * Return value: The "border-after-width" property value
**/
FoProperty*
fo_inline_get_border_after_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_after_width;
}

/**
 * fo_inline_set_border_after_width:
 * @fo_fo: The #FoFo object
 * @new_border_after_width: The new "border-after-width" property value
 * 
 * Sets the "border-after-width" property of @fo_fo to @new_border_after_width
 **/
void
fo_inline_set_border_after_width (FoFo *fo_fo,
		         FoProperty *new_border_after_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref (new_border_after_width);
    }
  if (fo_inline->border_after_width != NULL)
    {
      g_object_unref (fo_inline->border_after_width);
    }
  fo_inline->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_inline), "border-after-width");*/
}

/**
 * fo_inline_get_border_before_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-before-color" property of @fo_fo
 *
 * Return value: The "border-before-color" property value
**/
FoProperty*
fo_inline_get_border_before_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_before_color;
}

/**
 * fo_inline_set_border_before_color:
 * @fo_fo: The #FoFo object
 * @new_border_before_color: The new "border-before-color" property value
 * 
 * Sets the "border-before-color" property of @fo_fo to @new_border_before_color
 **/
void
fo_inline_set_border_before_color (FoFo *fo_fo,
		         FoProperty *new_border_before_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref (new_border_before_color);
    }
  if (fo_inline->border_before_color != NULL)
    {
      g_object_unref (fo_inline->border_before_color);
    }
  fo_inline->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_inline), "border-before-color");*/
}

/**
 * fo_inline_get_border_before_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-before-style" property of @fo_fo
 *
 * Return value: The "border-before-style" property value
**/
FoProperty*
fo_inline_get_border_before_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_before_style;
}

/**
 * fo_inline_set_border_before_style:
 * @fo_fo: The #FoFo object
 * @new_border_before_style: The new "border-before-style" property value
 * 
 * Sets the "border-before-style" property of @fo_fo to @new_border_before_style
 **/
void
fo_inline_set_border_before_style (FoFo *fo_fo,
		         FoProperty *new_border_before_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref (new_border_before_style);
    }
  if (fo_inline->border_before_style != NULL)
    {
      g_object_unref (fo_inline->border_before_style);
    }
  fo_inline->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_inline), "border-before-style");*/
}

/**
 * fo_inline_get_border_before_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-before-width" property of @fo_fo
 *
 * Return value: The "border-before-width" property value
**/
FoProperty*
fo_inline_get_border_before_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_before_width;
}

/**
 * fo_inline_set_border_before_width:
 * @fo_fo: The #FoFo object
 * @new_border_before_width: The new "border-before-width" property value
 * 
 * Sets the "border-before-width" property of @fo_fo to @new_border_before_width
 **/
void
fo_inline_set_border_before_width (FoFo *fo_fo,
		         FoProperty *new_border_before_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref (new_border_before_width);
    }
  if (fo_inline->border_before_width != NULL)
    {
      g_object_unref (fo_inline->border_before_width);
    }
  fo_inline->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_inline), "border-before-width");*/
}

/**
 * fo_inline_get_border_bottom_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-bottom-color" property of @fo_fo
 *
 * Return value: The "border-bottom-color" property value
**/
FoProperty*
fo_inline_get_border_bottom_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_bottom_color;
}

/**
 * fo_inline_set_border_bottom_color:
 * @fo_fo: The #FoFo object
 * @new_border_bottom_color: The new "border-bottom-color" property value
 * 
 * Sets the "border-bottom-color" property of @fo_fo to @new_border_bottom_color
 **/
void
fo_inline_set_border_bottom_color (FoFo *fo_fo,
		         FoProperty *new_border_bottom_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref (new_border_bottom_color);
    }
  if (fo_inline->border_bottom_color != NULL)
    {
      g_object_unref (fo_inline->border_bottom_color);
    }
  fo_inline->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_inline), "border-bottom-color");*/
}

/**
 * fo_inline_get_border_bottom_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-bottom-style" property of @fo_fo
 *
 * Return value: The "border-bottom-style" property value
**/
FoProperty*
fo_inline_get_border_bottom_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_bottom_style;
}

/**
 * fo_inline_set_border_bottom_style:
 * @fo_fo: The #FoFo object
 * @new_border_bottom_style: The new "border-bottom-style" property value
 * 
 * Sets the "border-bottom-style" property of @fo_fo to @new_border_bottom_style
 **/
void
fo_inline_set_border_bottom_style (FoFo *fo_fo,
		         FoProperty *new_border_bottom_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref (new_border_bottom_style);
    }
  if (fo_inline->border_bottom_style != NULL)
    {
      g_object_unref (fo_inline->border_bottom_style);
    }
  fo_inline->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_inline), "border-bottom-style");*/
}

/**
 * fo_inline_get_border_bottom_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-bottom-width" property of @fo_fo
 *
 * Return value: The "border-bottom-width" property value
**/
FoProperty*
fo_inline_get_border_bottom_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_bottom_width;
}

/**
 * fo_inline_set_border_bottom_width:
 * @fo_fo: The #FoFo object
 * @new_border_bottom_width: The new "border-bottom-width" property value
 * 
 * Sets the "border-bottom-width" property of @fo_fo to @new_border_bottom_width
 **/
void
fo_inline_set_border_bottom_width (FoFo *fo_fo,
		         FoProperty *new_border_bottom_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref (new_border_bottom_width);
    }
  if (fo_inline->border_bottom_width != NULL)
    {
      g_object_unref (fo_inline->border_bottom_width);
    }
  fo_inline->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_inline), "border-bottom-width");*/
}

/**
 * fo_inline_get_border_end_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-end-color" property of @fo_fo
 *
 * Return value: The "border-end-color" property value
**/
FoProperty*
fo_inline_get_border_end_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_end_color;
}

/**
 * fo_inline_set_border_end_color:
 * @fo_fo: The #FoFo object
 * @new_border_end_color: The new "border-end-color" property value
 * 
 * Sets the "border-end-color" property of @fo_fo to @new_border_end_color
 **/
void
fo_inline_set_border_end_color (FoFo *fo_fo,
		         FoProperty *new_border_end_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref (new_border_end_color);
    }
  if (fo_inline->border_end_color != NULL)
    {
      g_object_unref (fo_inline->border_end_color);
    }
  fo_inline->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_inline), "border-end-color");*/
}

/**
 * fo_inline_get_border_end_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-end-style" property of @fo_fo
 *
 * Return value: The "border-end-style" property value
**/
FoProperty*
fo_inline_get_border_end_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_end_style;
}

/**
 * fo_inline_set_border_end_style:
 * @fo_fo: The #FoFo object
 * @new_border_end_style: The new "border-end-style" property value
 * 
 * Sets the "border-end-style" property of @fo_fo to @new_border_end_style
 **/
void
fo_inline_set_border_end_style (FoFo *fo_fo,
		         FoProperty *new_border_end_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref (new_border_end_style);
    }
  if (fo_inline->border_end_style != NULL)
    {
      g_object_unref (fo_inline->border_end_style);
    }
  fo_inline->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_inline), "border-end-style");*/
}

/**
 * fo_inline_get_border_end_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-end-width" property of @fo_fo
 *
 * Return value: The "border-end-width" property value
**/
FoProperty*
fo_inline_get_border_end_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_end_width;
}

/**
 * fo_inline_set_border_end_width:
 * @fo_fo: The #FoFo object
 * @new_border_end_width: The new "border-end-width" property value
 * 
 * Sets the "border-end-width" property of @fo_fo to @new_border_end_width
 **/
void
fo_inline_set_border_end_width (FoFo *fo_fo,
		         FoProperty *new_border_end_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref (new_border_end_width);
    }
  if (fo_inline->border_end_width != NULL)
    {
      g_object_unref (fo_inline->border_end_width);
    }
  fo_inline->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_inline), "border-end-width");*/
}

/**
 * fo_inline_get_border_left_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-left-color" property of @fo_fo
 *
 * Return value: The "border-left-color" property value
**/
FoProperty*
fo_inline_get_border_left_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_left_color;
}

/**
 * fo_inline_set_border_left_color:
 * @fo_fo: The #FoFo object
 * @new_border_left_color: The new "border-left-color" property value
 * 
 * Sets the "border-left-color" property of @fo_fo to @new_border_left_color
 **/
void
fo_inline_set_border_left_color (FoFo *fo_fo,
		         FoProperty *new_border_left_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref (new_border_left_color);
    }
  if (fo_inline->border_left_color != NULL)
    {
      g_object_unref (fo_inline->border_left_color);
    }
  fo_inline->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_inline), "border-left-color");*/
}

/**
 * fo_inline_get_border_left_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-left-style" property of @fo_fo
 *
 * Return value: The "border-left-style" property value
**/
FoProperty*
fo_inline_get_border_left_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_left_style;
}

/**
 * fo_inline_set_border_left_style:
 * @fo_fo: The #FoFo object
 * @new_border_left_style: The new "border-left-style" property value
 * 
 * Sets the "border-left-style" property of @fo_fo to @new_border_left_style
 **/
void
fo_inline_set_border_left_style (FoFo *fo_fo,
		         FoProperty *new_border_left_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref (new_border_left_style);
    }
  if (fo_inline->border_left_style != NULL)
    {
      g_object_unref (fo_inline->border_left_style);
    }
  fo_inline->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_inline), "border-left-style");*/
}

/**
 * fo_inline_get_border_left_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-left-width" property of @fo_fo
 *
 * Return value: The "border-left-width" property value
**/
FoProperty*
fo_inline_get_border_left_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_left_width;
}

/**
 * fo_inline_set_border_left_width:
 * @fo_fo: The #FoFo object
 * @new_border_left_width: The new "border-left-width" property value
 * 
 * Sets the "border-left-width" property of @fo_fo to @new_border_left_width
 **/
void
fo_inline_set_border_left_width (FoFo *fo_fo,
		         FoProperty *new_border_left_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref (new_border_left_width);
    }
  if (fo_inline->border_left_width != NULL)
    {
      g_object_unref (fo_inline->border_left_width);
    }
  fo_inline->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_inline), "border-left-width");*/
}

/**
 * fo_inline_get_border_right_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-right-color" property of @fo_fo
 *
 * Return value: The "border-right-color" property value
**/
FoProperty*
fo_inline_get_border_right_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_right_color;
}

/**
 * fo_inline_set_border_right_color:
 * @fo_fo: The #FoFo object
 * @new_border_right_color: The new "border-right-color" property value
 * 
 * Sets the "border-right-color" property of @fo_fo to @new_border_right_color
 **/
void
fo_inline_set_border_right_color (FoFo *fo_fo,
		         FoProperty *new_border_right_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref (new_border_right_color);
    }
  if (fo_inline->border_right_color != NULL)
    {
      g_object_unref (fo_inline->border_right_color);
    }
  fo_inline->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_inline), "border-right-color");*/
}

/**
 * fo_inline_get_border_right_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-right-style" property of @fo_fo
 *
 * Return value: The "border-right-style" property value
**/
FoProperty*
fo_inline_get_border_right_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_right_style;
}

/**
 * fo_inline_set_border_right_style:
 * @fo_fo: The #FoFo object
 * @new_border_right_style: The new "border-right-style" property value
 * 
 * Sets the "border-right-style" property of @fo_fo to @new_border_right_style
 **/
void
fo_inline_set_border_right_style (FoFo *fo_fo,
		         FoProperty *new_border_right_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref (new_border_right_style);
    }
  if (fo_inline->border_right_style != NULL)
    {
      g_object_unref (fo_inline->border_right_style);
    }
  fo_inline->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_inline), "border-right-style");*/
}

/**
 * fo_inline_get_border_right_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-right-width" property of @fo_fo
 *
 * Return value: The "border-right-width" property value
**/
FoProperty*
fo_inline_get_border_right_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_right_width;
}

/**
 * fo_inline_set_border_right_width:
 * @fo_fo: The #FoFo object
 * @new_border_right_width: The new "border-right-width" property value
 * 
 * Sets the "border-right-width" property of @fo_fo to @new_border_right_width
 **/
void
fo_inline_set_border_right_width (FoFo *fo_fo,
		         FoProperty *new_border_right_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref (new_border_right_width);
    }
  if (fo_inline->border_right_width != NULL)
    {
      g_object_unref (fo_inline->border_right_width);
    }
  fo_inline->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_inline), "border-right-width");*/
}

/**
 * fo_inline_get_border_start_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-start-color" property of @fo_fo
 *
 * Return value: The "border-start-color" property value
**/
FoProperty*
fo_inline_get_border_start_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_start_color;
}

/**
 * fo_inline_set_border_start_color:
 * @fo_fo: The #FoFo object
 * @new_border_start_color: The new "border-start-color" property value
 * 
 * Sets the "border-start-color" property of @fo_fo to @new_border_start_color
 **/
void
fo_inline_set_border_start_color (FoFo *fo_fo,
		         FoProperty *new_border_start_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref (new_border_start_color);
    }
  if (fo_inline->border_start_color != NULL)
    {
      g_object_unref (fo_inline->border_start_color);
    }
  fo_inline->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_inline), "border-start-color");*/
}

/**
 * fo_inline_get_border_start_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-start-style" property of @fo_fo
 *
 * Return value: The "border-start-style" property value
**/
FoProperty*
fo_inline_get_border_start_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_start_style;
}

/**
 * fo_inline_set_border_start_style:
 * @fo_fo: The #FoFo object
 * @new_border_start_style: The new "border-start-style" property value
 * 
 * Sets the "border-start-style" property of @fo_fo to @new_border_start_style
 **/
void
fo_inline_set_border_start_style (FoFo *fo_fo,
		         FoProperty *new_border_start_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref (new_border_start_style);
    }
  if (fo_inline->border_start_style != NULL)
    {
      g_object_unref (fo_inline->border_start_style);
    }
  fo_inline->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_inline), "border-start-style");*/
}

/**
 * fo_inline_get_border_start_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-start-width" property of @fo_fo
 *
 * Return value: The "border-start-width" property value
**/
FoProperty*
fo_inline_get_border_start_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_start_width;
}

/**
 * fo_inline_set_border_start_width:
 * @fo_fo: The #FoFo object
 * @new_border_start_width: The new "border-start-width" property value
 * 
 * Sets the "border-start-width" property of @fo_fo to @new_border_start_width
 **/
void
fo_inline_set_border_start_width (FoFo *fo_fo,
		         FoProperty *new_border_start_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref (new_border_start_width);
    }
  if (fo_inline->border_start_width != NULL)
    {
      g_object_unref (fo_inline->border_start_width);
    }
  fo_inline->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_inline), "border-start-width");*/
}

/**
 * fo_inline_get_border_top_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-top-color" property of @fo_fo
 *
 * Return value: The "border-top-color" property value
**/
FoProperty*
fo_inline_get_border_top_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_top_color;
}

/**
 * fo_inline_set_border_top_color:
 * @fo_fo: The #FoFo object
 * @new_border_top_color: The new "border-top-color" property value
 * 
 * Sets the "border-top-color" property of @fo_fo to @new_border_top_color
 **/
void
fo_inline_set_border_top_color (FoFo *fo_fo,
		         FoProperty *new_border_top_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref (new_border_top_color);
    }
  if (fo_inline->border_top_color != NULL)
    {
      g_object_unref (fo_inline->border_top_color);
    }
  fo_inline->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_inline), "border-top-color");*/
}

/**
 * fo_inline_get_border_top_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-top-style" property of @fo_fo
 *
 * Return value: The "border-top-style" property value
**/
FoProperty*
fo_inline_get_border_top_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_top_style;
}

/**
 * fo_inline_set_border_top_style:
 * @fo_fo: The #FoFo object
 * @new_border_top_style: The new "border-top-style" property value
 * 
 * Sets the "border-top-style" property of @fo_fo to @new_border_top_style
 **/
void
fo_inline_set_border_top_style (FoFo *fo_fo,
		         FoProperty *new_border_top_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref (new_border_top_style);
    }
  if (fo_inline->border_top_style != NULL)
    {
      g_object_unref (fo_inline->border_top_style);
    }
  fo_inline->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_inline), "border-top-style");*/
}

/**
 * fo_inline_get_border_top_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-top-width" property of @fo_fo
 *
 * Return value: The "border-top-width" property value
**/
FoProperty*
fo_inline_get_border_top_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->border_top_width;
}

/**
 * fo_inline_set_border_top_width:
 * @fo_fo: The #FoFo object
 * @new_border_top_width: The new "border-top-width" property value
 * 
 * Sets the "border-top-width" property of @fo_fo to @new_border_top_width
 **/
void
fo_inline_set_border_top_width (FoFo *fo_fo,
		         FoProperty *new_border_top_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref (new_border_top_width);
    }
  if (fo_inline->border_top_width != NULL)
    {
      g_object_unref (fo_inline->border_top_width);
    }
  fo_inline->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_inline), "border-top-width");*/
}

/**
 * fo_inline_get_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "color" property of @fo_fo
 *
 * Return value: The "color" property value
**/
FoProperty*
fo_inline_get_color (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->color;
}

/**
 * fo_inline_set_color:
 * @fo_fo: The #FoFo object
 * @new_color: The new "color" property value
 * 
 * Sets the "color" property of @fo_fo to @new_color
 **/
void
fo_inline_set_color (FoFo *fo_fo,
		         FoProperty *new_color)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_COLOR (new_color));

  if (new_color != NULL)
    {
      g_object_ref (new_color);
    }
  if (fo_inline->color != NULL)
    {
      g_object_unref (fo_inline->color);
    }
  fo_inline->color = new_color;
  /*g_object_notify (G_OBJECT (fo_inline), "color");*/
}

/**
 * fo_inline_get_dominant_baseline:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "dominant-baseline" property of @fo_fo
 *
 * Return value: The "dominant-baseline" property value
**/
FoProperty*
fo_inline_get_dominant_baseline (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->dominant_baseline;
}

/**
 * fo_inline_set_dominant_baseline:
 * @fo_fo: The #FoFo object
 * @new_dominant_baseline: The new "dominant-baseline" property value
 * 
 * Sets the "dominant-baseline" property of @fo_fo to @new_dominant_baseline
 **/
void
fo_inline_set_dominant_baseline (FoFo *fo_fo,
		         FoProperty *new_dominant_baseline)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_DOMINANT_BASELINE (new_dominant_baseline));

  if (new_dominant_baseline != NULL)
    {
      g_object_ref (new_dominant_baseline);
    }
  if (fo_inline->dominant_baseline != NULL)
    {
      g_object_unref (fo_inline->dominant_baseline);
    }
  fo_inline->dominant_baseline = new_dominant_baseline;
  /*g_object_notify (G_OBJECT (fo_inline), "dominant-baseline");*/
}

/**
 * fo_inline_get_font_family:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "font-family" property of @fo_fo
 *
 * Return value: The "font-family" property value
**/
FoProperty*
fo_inline_get_font_family (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->font_family;
}

/**
 * fo_inline_set_font_family:
 * @fo_fo: The #FoFo object
 * @new_font_family: The new "font-family" property value
 * 
 * Sets the "font-family" property of @fo_fo to @new_font_family
 **/
void
fo_inline_set_font_family (FoFo *fo_fo,
		         FoProperty *new_font_family)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_FONT_FAMILY (new_font_family));

  if (new_font_family != NULL)
    {
      g_object_ref (new_font_family);
    }
  if (fo_inline->font_family != NULL)
    {
      g_object_unref (fo_inline->font_family);
    }
  fo_inline->font_family = new_font_family;
  /*g_object_notify (G_OBJECT (fo_inline), "font-family");*/
}

/**
 * fo_inline_get_font_size:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "font-size" property of @fo_fo
 *
 * Return value: The "font-size" property value
**/
FoProperty*
fo_inline_get_font_size (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->font_size;
}

/**
 * fo_inline_set_font_size:
 * @fo_fo: The #FoFo object
 * @new_font_size: The new "font-size" property value
 * 
 * Sets the "font-size" property of @fo_fo to @new_font_size
 **/
void
fo_inline_set_font_size (FoFo *fo_fo,
		         FoProperty *new_font_size)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_FONT_SIZE (new_font_size));

  if (new_font_size != NULL)
    {
      g_object_ref (new_font_size);
    }
  if (fo_inline->font_size != NULL)
    {
      g_object_unref (fo_inline->font_size);
    }
  fo_inline->font_size = new_font_size;
  /*g_object_notify (G_OBJECT (fo_inline), "font-size");*/
}

/**
 * fo_inline_get_font_stretch:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "font-stretch" property of @fo_fo
 *
 * Return value: The "font-stretch" property value
**/
FoProperty*
fo_inline_get_font_stretch (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->font_stretch;
}

/**
 * fo_inline_set_font_stretch:
 * @fo_fo: The #FoFo object
 * @new_font_stretch: The new "font-stretch" property value
 * 
 * Sets the "font-stretch" property of @fo_fo to @new_font_stretch
 **/
void
fo_inline_set_font_stretch (FoFo *fo_fo,
		         FoProperty *new_font_stretch)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_FONT_STRETCH (new_font_stretch));

  if (new_font_stretch != NULL)
    {
      g_object_ref (new_font_stretch);
    }
  if (fo_inline->font_stretch != NULL)
    {
      g_object_unref (fo_inline->font_stretch);
    }
  fo_inline->font_stretch = new_font_stretch;
  /*g_object_notify (G_OBJECT (fo_inline), "font-stretch");*/
}

/**
 * fo_inline_get_font_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "font-style" property of @fo_fo
 *
 * Return value: The "font-style" property value
**/
FoProperty*
fo_inline_get_font_style (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->font_style;
}

/**
 * fo_inline_set_font_style:
 * @fo_fo: The #FoFo object
 * @new_font_style: The new "font-style" property value
 * 
 * Sets the "font-style" property of @fo_fo to @new_font_style
 **/
void
fo_inline_set_font_style (FoFo *fo_fo,
		         FoProperty *new_font_style)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_FONT_STYLE (new_font_style));

  if (new_font_style != NULL)
    {
      g_object_ref (new_font_style);
    }
  if (fo_inline->font_style != NULL)
    {
      g_object_unref (fo_inline->font_style);
    }
  fo_inline->font_style = new_font_style;
  /*g_object_notify (G_OBJECT (fo_inline), "font-style");*/
}

/**
 * fo_inline_get_font_variant:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "font-variant" property of @fo_fo
 *
 * Return value: The "font-variant" property value
**/
FoProperty*
fo_inline_get_font_variant (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->font_variant;
}

/**
 * fo_inline_set_font_variant:
 * @fo_fo: The #FoFo object
 * @new_font_variant: The new "font-variant" property value
 * 
 * Sets the "font-variant" property of @fo_fo to @new_font_variant
 **/
void
fo_inline_set_font_variant (FoFo *fo_fo,
		         FoProperty *new_font_variant)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_FONT_VARIANT (new_font_variant));

  if (new_font_variant != NULL)
    {
      g_object_ref (new_font_variant);
    }
  if (fo_inline->font_variant != NULL)
    {
      g_object_unref (fo_inline->font_variant);
    }
  fo_inline->font_variant = new_font_variant;
  /*g_object_notify (G_OBJECT (fo_inline), "font-variant");*/
}

/**
 * fo_inline_get_font_weight:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "font-weight" property of @fo_fo
 *
 * Return value: The "font-weight" property value
**/
FoProperty*
fo_inline_get_font_weight (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->font_weight;
}

/**
 * fo_inline_set_font_weight:
 * @fo_fo: The #FoFo object
 * @new_font_weight: The new "font-weight" property value
 * 
 * Sets the "font-weight" property of @fo_fo to @new_font_weight
 **/
void
fo_inline_set_font_weight (FoFo *fo_fo,
		         FoProperty *new_font_weight)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_FONT_WEIGHT (new_font_weight));

  if (new_font_weight != NULL)
    {
      g_object_ref (new_font_weight);
    }
  if (fo_inline->font_weight != NULL)
    {
      g_object_unref (fo_inline->font_weight);
    }
  fo_inline->font_weight = new_font_weight;
  /*g_object_notify (G_OBJECT (fo_inline), "font-weight");*/
}

/**
 * fo_inline_get_height:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "height" property of @fo_fo
 *
 * Return value: The "height" property value
**/
FoProperty*
fo_inline_get_height (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->height;
}

/**
 * fo_inline_set_height:
 * @fo_fo: The #FoFo object
 * @new_height: The new "height" property value
 * 
 * Sets the "height" property of @fo_fo to @new_height
 **/
void
fo_inline_set_height (FoFo *fo_fo,
		         FoProperty *new_height)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_HEIGHT (new_height));

  if (new_height != NULL)
    {
      g_object_ref (new_height);
    }
  if (fo_inline->height != NULL)
    {
      g_object_unref (fo_inline->height);
    }
  fo_inline->height = new_height;
  /*g_object_notify (G_OBJECT (fo_inline), "height");*/
}

/**
 * fo_inline_get_id:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "id" property of @fo_fo
 *
 * Return value: The "id" property value
**/
FoProperty*
fo_inline_get_id (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->id;
}

/**
 * fo_inline_set_id:
 * @fo_fo: The #FoFo object
 * @new_id: The new "id" property value
 * 
 * Sets the "id" property of @fo_fo to @new_id
 **/
void
fo_inline_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_inline->id != NULL)
    {
      g_object_unref (fo_inline->id);
    }
  fo_inline->id = new_id;
  /*g_object_notify (G_OBJECT (fo_inline), "id");*/
}

/**
 * fo_inline_get_inline_progression_dimension:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "inline-progression-dimension" property of @fo_fo
 *
 * Return value: The "inline-progression-dimension" property value
**/
FoProperty*
fo_inline_get_inline_progression_dimension (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->inline_progression_dimension;
}

/**
 * fo_inline_set_inline_progression_dimension:
 * @fo_fo: The #FoFo object
 * @new_inline_progression_dimension: The new "inline-progression-dimension" property value
 * 
 * Sets the "inline-progression-dimension" property of @fo_fo to @new_inline_progression_dimension
 **/
void
fo_inline_set_inline_progression_dimension (FoFo *fo_fo,
		         FoProperty *new_inline_progression_dimension)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION (new_inline_progression_dimension));

  if (new_inline_progression_dimension != NULL)
    {
      g_object_ref (new_inline_progression_dimension);
    }
  if (fo_inline->inline_progression_dimension != NULL)
    {
      g_object_unref (fo_inline->inline_progression_dimension);
    }
  fo_inline->inline_progression_dimension = new_inline_progression_dimension;
  /*g_object_notify (G_OBJECT (fo_inline), "inline-progression-dimension");*/
}

/**
 * fo_inline_get_keep_together:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together" property of @fo_fo
 *
 * Return value: The "keep-together" property value
**/
FoProperty*
fo_inline_get_keep_together (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_together;
}

/**
 * fo_inline_set_keep_together:
 * @fo_fo: The #FoFo object
 * @new_keep_together: The new "keep-together" property value
 * 
 * Sets the "keep-together" property of @fo_fo to @new_keep_together
 **/
void
fo_inline_set_keep_together (FoFo *fo_fo,
		         FoProperty *new_keep_together)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER (new_keep_together));

  if (new_keep_together != NULL)
    {
      g_object_ref (new_keep_together);
    }
  if (fo_inline->keep_together != NULL)
    {
      g_object_unref (fo_inline->keep_together);
    }
  fo_inline->keep_together = new_keep_together;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-together");*/
}

/**
 * fo_inline_get_keep_together_within_column:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-column" property of @fo_fo
 *
 * Return value: The "keep-together-within-column" property value
**/
FoProperty*
fo_inline_get_keep_together_within_column (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_together_within_column;
}

/**
 * fo_inline_set_keep_together_within_column:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_column: The new "keep-together-within-column" property value
 * 
 * Sets the "keep-together-within-column" property of @fo_fo to @new_keep_together_within_column
 **/
void
fo_inline_set_keep_together_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_column)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN (new_keep_together_within_column));

  if (new_keep_together_within_column != NULL)
    {
      g_object_ref (new_keep_together_within_column);
    }
  if (fo_inline->keep_together_within_column != NULL)
    {
      g_object_unref (fo_inline->keep_together_within_column);
    }
  fo_inline->keep_together_within_column = new_keep_together_within_column;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-together-within-column");*/
}

/**
 * fo_inline_get_keep_together_within_line:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-line" property of @fo_fo
 *
 * Return value: The "keep-together-within-line" property value
**/
FoProperty*
fo_inline_get_keep_together_within_line (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_together_within_line;
}

/**
 * fo_inline_set_keep_together_within_line:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_line: The new "keep-together-within-line" property value
 * 
 * Sets the "keep-together-within-line" property of @fo_fo to @new_keep_together_within_line
 **/
void
fo_inline_set_keep_together_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_line)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_LINE (new_keep_together_within_line));

  if (new_keep_together_within_line != NULL)
    {
      g_object_ref (new_keep_together_within_line);
    }
  if (fo_inline->keep_together_within_line != NULL)
    {
      g_object_unref (fo_inline->keep_together_within_line);
    }
  fo_inline->keep_together_within_line = new_keep_together_within_line;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-together-within-line");*/
}

/**
 * fo_inline_get_keep_together_within_page:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-page" property of @fo_fo
 *
 * Return value: The "keep-together-within-page" property value
**/
FoProperty*
fo_inline_get_keep_together_within_page (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_together_within_page;
}

/**
 * fo_inline_set_keep_together_within_page:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_page: The new "keep-together-within-page" property value
 * 
 * Sets the "keep-together-within-page" property of @fo_fo to @new_keep_together_within_page
 **/
void
fo_inline_set_keep_together_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_page)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE (new_keep_together_within_page));

  if (new_keep_together_within_page != NULL)
    {
      g_object_ref (new_keep_together_within_page);
    }
  if (fo_inline->keep_together_within_page != NULL)
    {
      g_object_unref (fo_inline->keep_together_within_page);
    }
  fo_inline->keep_together_within_page = new_keep_together_within_page;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-together-within-page");*/
}

/**
 * fo_inline_get_keep_with_next:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-next" property of @fo_fo
 *
 * Return value: The "keep-with-next" property value
**/
FoProperty*
fo_inline_get_keep_with_next (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_with_next;
}

/**
 * fo_inline_set_keep_with_next:
 * @fo_fo: The #FoFo object
 * @new_keep_with_next: The new "keep-with-next" property value
 * 
 * Sets the "keep-with-next" property of @fo_fo to @new_keep_with_next
 **/
void
fo_inline_set_keep_with_next (FoFo *fo_fo,
		         FoProperty *new_keep_with_next)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT (new_keep_with_next));

  if (new_keep_with_next != NULL)
    {
      g_object_ref (new_keep_with_next);
    }
  if (fo_inline->keep_with_next != NULL)
    {
      g_object_unref (fo_inline->keep_with_next);
    }
  fo_inline->keep_with_next = new_keep_with_next;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-with-next");*/
}

/**
 * fo_inline_get_keep_with_next_within_column:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-next-within-column" property of @fo_fo
 *
 * Return value: The "keep-with-next-within-column" property value
**/
FoProperty*
fo_inline_get_keep_with_next_within_column (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_with_next_within_column;
}

/**
 * fo_inline_set_keep_with_next_within_column:
 * @fo_fo: The #FoFo object
 * @new_keep_with_next_within_column: The new "keep-with-next-within-column" property value
 * 
 * Sets the "keep-with-next-within-column" property of @fo_fo to @new_keep_with_next_within_column
 **/
void
fo_inline_set_keep_with_next_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_column)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_COLUMN (new_keep_with_next_within_column));

  if (new_keep_with_next_within_column != NULL)
    {
      g_object_ref (new_keep_with_next_within_column);
    }
  if (fo_inline->keep_with_next_within_column != NULL)
    {
      g_object_unref (fo_inline->keep_with_next_within_column);
    }
  fo_inline->keep_with_next_within_column = new_keep_with_next_within_column;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-with-next-within-column");*/
}

/**
 * fo_inline_get_keep_with_next_within_line:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-next-within-line" property of @fo_fo
 *
 * Return value: The "keep-with-next-within-line" property value
**/
FoProperty*
fo_inline_get_keep_with_next_within_line (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_with_next_within_line;
}

/**
 * fo_inline_set_keep_with_next_within_line:
 * @fo_fo: The #FoFo object
 * @new_keep_with_next_within_line: The new "keep-with-next-within-line" property value
 * 
 * Sets the "keep-with-next-within-line" property of @fo_fo to @new_keep_with_next_within_line
 **/
void
fo_inline_set_keep_with_next_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_line)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (new_keep_with_next_within_line));

  if (new_keep_with_next_within_line != NULL)
    {
      g_object_ref (new_keep_with_next_within_line);
    }
  if (fo_inline->keep_with_next_within_line != NULL)
    {
      g_object_unref (fo_inline->keep_with_next_within_line);
    }
  fo_inline->keep_with_next_within_line = new_keep_with_next_within_line;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-with-next-within-line");*/
}

/**
 * fo_inline_get_keep_with_next_within_page:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-next-within-page" property of @fo_fo
 *
 * Return value: The "keep-with-next-within-page" property value
**/
FoProperty*
fo_inline_get_keep_with_next_within_page (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_with_next_within_page;
}

/**
 * fo_inline_set_keep_with_next_within_page:
 * @fo_fo: The #FoFo object
 * @new_keep_with_next_within_page: The new "keep-with-next-within-page" property value
 * 
 * Sets the "keep-with-next-within-page" property of @fo_fo to @new_keep_with_next_within_page
 **/
void
fo_inline_set_keep_with_next_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_page)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE (new_keep_with_next_within_page));

  if (new_keep_with_next_within_page != NULL)
    {
      g_object_ref (new_keep_with_next_within_page);
    }
  if (fo_inline->keep_with_next_within_page != NULL)
    {
      g_object_unref (fo_inline->keep_with_next_within_page);
    }
  fo_inline->keep_with_next_within_page = new_keep_with_next_within_page;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-with-next-within-page");*/
}

/**
 * fo_inline_get_keep_with_previous:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-previous" property of @fo_fo
 *
 * Return value: The "keep-with-previous" property value
**/
FoProperty*
fo_inline_get_keep_with_previous (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_with_previous;
}

/**
 * fo_inline_set_keep_with_previous:
 * @fo_fo: The #FoFo object
 * @new_keep_with_previous: The new "keep-with-previous" property value
 * 
 * Sets the "keep-with-previous" property of @fo_fo to @new_keep_with_previous
 **/
void
fo_inline_set_keep_with_previous (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS (new_keep_with_previous));

  if (new_keep_with_previous != NULL)
    {
      g_object_ref (new_keep_with_previous);
    }
  if (fo_inline->keep_with_previous != NULL)
    {
      g_object_unref (fo_inline->keep_with_previous);
    }
  fo_inline->keep_with_previous = new_keep_with_previous;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-with-previous");*/
}

/**
 * fo_inline_get_keep_with_previous_within_column:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-previous-within-column" property of @fo_fo
 *
 * Return value: The "keep-with-previous-within-column" property value
**/
FoProperty*
fo_inline_get_keep_with_previous_within_column (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_with_previous_within_column;
}

/**
 * fo_inline_set_keep_with_previous_within_column:
 * @fo_fo: The #FoFo object
 * @new_keep_with_previous_within_column: The new "keep-with-previous-within-column" property value
 * 
 * Sets the "keep-with-previous-within-column" property of @fo_fo to @new_keep_with_previous_within_column
 **/
void
fo_inline_set_keep_with_previous_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_column)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_COLUMN (new_keep_with_previous_within_column));

  if (new_keep_with_previous_within_column != NULL)
    {
      g_object_ref (new_keep_with_previous_within_column);
    }
  if (fo_inline->keep_with_previous_within_column != NULL)
    {
      g_object_unref (fo_inline->keep_with_previous_within_column);
    }
  fo_inline->keep_with_previous_within_column = new_keep_with_previous_within_column;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-with-previous-within-column");*/
}

/**
 * fo_inline_get_keep_with_previous_within_line:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-previous-within-line" property of @fo_fo
 *
 * Return value: The "keep-with-previous-within-line" property value
**/
FoProperty*
fo_inline_get_keep_with_previous_within_line (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_with_previous_within_line;
}

/**
 * fo_inline_set_keep_with_previous_within_line:
 * @fo_fo: The #FoFo object
 * @new_keep_with_previous_within_line: The new "keep-with-previous-within-line" property value
 * 
 * Sets the "keep-with-previous-within-line" property of @fo_fo to @new_keep_with_previous_within_line
 **/
void
fo_inline_set_keep_with_previous_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_line)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_LINE (new_keep_with_previous_within_line));

  if (new_keep_with_previous_within_line != NULL)
    {
      g_object_ref (new_keep_with_previous_within_line);
    }
  if (fo_inline->keep_with_previous_within_line != NULL)
    {
      g_object_unref (fo_inline->keep_with_previous_within_line);
    }
  fo_inline->keep_with_previous_within_line = new_keep_with_previous_within_line;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-with-previous-within-line");*/
}

/**
 * fo_inline_get_keep_with_previous_within_page:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-previous-within-page" property of @fo_fo
 *
 * Return value: The "keep-with-previous-within-page" property value
**/
FoProperty*
fo_inline_get_keep_with_previous_within_page (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->keep_with_previous_within_page;
}

/**
 * fo_inline_set_keep_with_previous_within_page:
 * @fo_fo: The #FoFo object
 * @new_keep_with_previous_within_page: The new "keep-with-previous-within-page" property value
 * 
 * Sets the "keep-with-previous-within-page" property of @fo_fo to @new_keep_with_previous_within_page
 **/
void
fo_inline_set_keep_with_previous_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_page)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE (new_keep_with_previous_within_page));

  if (new_keep_with_previous_within_page != NULL)
    {
      g_object_ref (new_keep_with_previous_within_page);
    }
  if (fo_inline->keep_with_previous_within_page != NULL)
    {
      g_object_unref (fo_inline->keep_with_previous_within_page);
    }
  fo_inline->keep_with_previous_within_page = new_keep_with_previous_within_page;
  /*g_object_notify (G_OBJECT (fo_inline), "keep-with-previous-within-page");*/
}

/**
 * fo_inline_get_line_height:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "line-height" property of @fo_fo
 *
 * Return value: The "line-height" property value
**/
FoProperty*
fo_inline_get_line_height (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->line_height;
}

/**
 * fo_inline_set_line_height:
 * @fo_fo: The #FoFo object
 * @new_line_height: The new "line-height" property value
 * 
 * Sets the "line-height" property of @fo_fo to @new_line_height
 **/
void
fo_inline_set_line_height (FoFo *fo_fo,
		         FoProperty *new_line_height)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_LINE_HEIGHT (new_line_height));

  if (new_line_height != NULL)
    {
      g_object_ref (new_line_height);
    }
  if (fo_inline->line_height != NULL)
    {
      g_object_unref (fo_inline->line_height);
    }
  fo_inline->line_height = new_line_height;
  /*g_object_notify (G_OBJECT (fo_inline), "line-height");*/
}

/**
 * fo_inline_get_padding_after:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-after" property of @fo_fo
 *
 * Return value: The "padding-after" property value
**/
FoProperty*
fo_inline_get_padding_after (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->padding_after;
}

/**
 * fo_inline_set_padding_after:
 * @fo_fo: The #FoFo object
 * @new_padding_after: The new "padding-after" property value
 * 
 * Sets the "padding-after" property of @fo_fo to @new_padding_after
 **/
void
fo_inline_set_padding_after (FoFo *fo_fo,
		         FoProperty *new_padding_after)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref (new_padding_after);
    }
  if (fo_inline->padding_after != NULL)
    {
      g_object_unref (fo_inline->padding_after);
    }
  fo_inline->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_inline), "padding-after");*/
}

/**
 * fo_inline_get_padding_before:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-before" property of @fo_fo
 *
 * Return value: The "padding-before" property value
**/
FoProperty*
fo_inline_get_padding_before (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->padding_before;
}

/**
 * fo_inline_set_padding_before:
 * @fo_fo: The #FoFo object
 * @new_padding_before: The new "padding-before" property value
 * 
 * Sets the "padding-before" property of @fo_fo to @new_padding_before
 **/
void
fo_inline_set_padding_before (FoFo *fo_fo,
		         FoProperty *new_padding_before)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref (new_padding_before);
    }
  if (fo_inline->padding_before != NULL)
    {
      g_object_unref (fo_inline->padding_before);
    }
  fo_inline->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_inline), "padding-before");*/
}

/**
 * fo_inline_get_padding_bottom:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-bottom" property of @fo_fo
 *
 * Return value: The "padding-bottom" property value
**/
FoProperty*
fo_inline_get_padding_bottom (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->padding_bottom;
}

/**
 * fo_inline_set_padding_bottom:
 * @fo_fo: The #FoFo object
 * @new_padding_bottom: The new "padding-bottom" property value
 * 
 * Sets the "padding-bottom" property of @fo_fo to @new_padding_bottom
 **/
void
fo_inline_set_padding_bottom (FoFo *fo_fo,
		         FoProperty *new_padding_bottom)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref (new_padding_bottom);
    }
  if (fo_inline->padding_bottom != NULL)
    {
      g_object_unref (fo_inline->padding_bottom);
    }
  fo_inline->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_inline), "padding-bottom");*/
}

/**
 * fo_inline_get_padding_end:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-end" property of @fo_fo
 *
 * Return value: The "padding-end" property value
**/
FoProperty*
fo_inline_get_padding_end (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->padding_end;
}

/**
 * fo_inline_set_padding_end:
 * @fo_fo: The #FoFo object
 * @new_padding_end: The new "padding-end" property value
 * 
 * Sets the "padding-end" property of @fo_fo to @new_padding_end
 **/
void
fo_inline_set_padding_end (FoFo *fo_fo,
		         FoProperty *new_padding_end)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref (new_padding_end);
    }
  if (fo_inline->padding_end != NULL)
    {
      g_object_unref (fo_inline->padding_end);
    }
  fo_inline->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_inline), "padding-end");*/
}

/**
 * fo_inline_get_padding_left:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-left" property of @fo_fo
 *
 * Return value: The "padding-left" property value
**/
FoProperty*
fo_inline_get_padding_left (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->padding_left;
}

/**
 * fo_inline_set_padding_left:
 * @fo_fo: The #FoFo object
 * @new_padding_left: The new "padding-left" property value
 * 
 * Sets the "padding-left" property of @fo_fo to @new_padding_left
 **/
void
fo_inline_set_padding_left (FoFo *fo_fo,
		         FoProperty *new_padding_left)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref (new_padding_left);
    }
  if (fo_inline->padding_left != NULL)
    {
      g_object_unref (fo_inline->padding_left);
    }
  fo_inline->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_inline), "padding-left");*/
}

/**
 * fo_inline_get_padding_right:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-right" property of @fo_fo
 *
 * Return value: The "padding-right" property value
**/
FoProperty*
fo_inline_get_padding_right (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->padding_right;
}

/**
 * fo_inline_set_padding_right:
 * @fo_fo: The #FoFo object
 * @new_padding_right: The new "padding-right" property value
 * 
 * Sets the "padding-right" property of @fo_fo to @new_padding_right
 **/
void
fo_inline_set_padding_right (FoFo *fo_fo,
		         FoProperty *new_padding_right)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref (new_padding_right);
    }
  if (fo_inline->padding_right != NULL)
    {
      g_object_unref (fo_inline->padding_right);
    }
  fo_inline->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_inline), "padding-right");*/
}

/**
 * fo_inline_get_padding_start:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-start" property of @fo_fo
 *
 * Return value: The "padding-start" property value
**/
FoProperty*
fo_inline_get_padding_start (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->padding_start;
}

/**
 * fo_inline_set_padding_start:
 * @fo_fo: The #FoFo object
 * @new_padding_start: The new "padding-start" property value
 * 
 * Sets the "padding-start" property of @fo_fo to @new_padding_start
 **/
void
fo_inline_set_padding_start (FoFo *fo_fo,
		         FoProperty *new_padding_start)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref (new_padding_start);
    }
  if (fo_inline->padding_start != NULL)
    {
      g_object_unref (fo_inline->padding_start);
    }
  fo_inline->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_inline), "padding-start");*/
}

/**
 * fo_inline_get_padding_top:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-top" property of @fo_fo
 *
 * Return value: The "padding-top" property value
**/
FoProperty*
fo_inline_get_padding_top (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->padding_top;
}

/**
 * fo_inline_set_padding_top:
 * @fo_fo: The #FoFo object
 * @new_padding_top: The new "padding-top" property value
 * 
 * Sets the "padding-top" property of @fo_fo to @new_padding_top
 **/
void
fo_inline_set_padding_top (FoFo *fo_fo,
		         FoProperty *new_padding_top)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref (new_padding_top);
    }
  if (fo_inline->padding_top != NULL)
    {
      g_object_unref (fo_inline->padding_top);
    }
  fo_inline->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_inline), "padding-top");*/
}

/**
 * fo_inline_get_role:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "role" property of @fo_fo
 *
 * Return value: The "role" property value
**/
FoProperty*
fo_inline_get_role (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->role;
}

/**
 * fo_inline_set_role:
 * @fo_fo: The #FoFo object
 * @new_role: The new "role" property value
 * 
 * Sets the "role" property of @fo_fo to @new_role
 **/
void
fo_inline_set_role (FoFo *fo_fo,
		         FoProperty *new_role)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_ROLE (new_role));

  if (new_role != NULL)
    {
      g_object_ref (new_role);
    }
  if (fo_inline->role != NULL)
    {
      g_object_unref (fo_inline->role);
    }
  fo_inline->role = new_role;
  /*g_object_notify (G_OBJECT (fo_inline), "role");*/
}

/**
 * fo_inline_get_source_document:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "source-document" property of @fo_fo
 *
 * Return value: The "source-document" property value
**/
FoProperty*
fo_inline_get_source_document (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->source_document;
}

/**
 * fo_inline_set_source_document:
 * @fo_fo: The #FoFo object
 * @new_source_document: The new "source-document" property value
 * 
 * Sets the "source-document" property of @fo_fo to @new_source_document
 **/
void
fo_inline_set_source_document (FoFo *fo_fo,
		         FoProperty *new_source_document)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document != NULL)
    {
      g_object_ref (new_source_document);
    }
  if (fo_inline->source_document != NULL)
    {
      g_object_unref (fo_inline->source_document);
    }
  fo_inline->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_inline), "source-document");*/
}

/**
 * fo_inline_get_space_end:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "space-end" property of @fo_fo
 *
 * Return value: The "space-end" property value
**/
FoProperty*
fo_inline_get_space_end (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->space_end;
}

/**
 * fo_inline_set_space_end:
 * @fo_fo: The #FoFo object
 * @new_space_end: The new "space-end" property value
 * 
 * Sets the "space-end" property of @fo_fo to @new_space_end
 **/
void
fo_inline_set_space_end (FoFo *fo_fo,
		         FoProperty *new_space_end)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_SPACE_END (new_space_end));

  if (new_space_end != NULL)
    {
      g_object_ref (new_space_end);
    }
  if (fo_inline->space_end != NULL)
    {
      g_object_unref (fo_inline->space_end);
    }
  fo_inline->space_end = new_space_end;
  /*g_object_notify (G_OBJECT (fo_inline), "space-end");*/
}

/**
 * fo_inline_get_space_start:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "space-start" property of @fo_fo
 *
 * Return value: The "space-start" property value
**/
FoProperty*
fo_inline_get_space_start (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->space_start;
}

/**
 * fo_inline_set_space_start:
 * @fo_fo: The #FoFo object
 * @new_space_start: The new "space-start" property value
 * 
 * Sets the "space-start" property of @fo_fo to @new_space_start
 **/
void
fo_inline_set_space_start (FoFo *fo_fo,
		         FoProperty *new_space_start)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_SPACE_START (new_space_start));

  if (new_space_start != NULL)
    {
      g_object_ref (new_space_start);
    }
  if (fo_inline->space_start != NULL)
    {
      g_object_unref (fo_inline->space_start);
    }
  fo_inline->space_start = new_space_start;
  /*g_object_notify (G_OBJECT (fo_inline), "space-start");*/
}

/**
 * fo_inline_get_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "width" property of @fo_fo
 *
 * Return value: The "width" property value
**/
FoProperty*
fo_inline_get_width (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->width;
}

/**
 * fo_inline_set_width:
 * @fo_fo: The #FoFo object
 * @new_width: The new "width" property value
 * 
 * Sets the "width" property of @fo_fo to @new_width
 **/
void
fo_inline_set_width (FoFo *fo_fo,
		         FoProperty *new_width)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_WIDTH (new_width));

  if (new_width != NULL)
    {
      g_object_ref (new_width);
    }
  if (fo_inline->width != NULL)
    {
      g_object_unref (fo_inline->width);
    }
  fo_inline->width = new_width;
  /*g_object_notify (G_OBJECT (fo_inline), "width");*/
}

/**
 * fo_inline_get_wrap_option:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "wrap-option" property of @fo_fo
 *
 * Return value: The "wrap-option" property value
**/
FoProperty*
fo_inline_get_wrap_option (FoFo *fo_fo)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_val_if_fail (fo_inline != NULL, NULL);
  g_return_val_if_fail (FO_IS_INLINE (fo_inline), NULL);

  return fo_inline->wrap_option;
}

/**
 * fo_inline_set_wrap_option:
 * @fo_fo: The #FoFo object
 * @new_wrap_option: The new "wrap-option" property value
 * 
 * Sets the "wrap-option" property of @fo_fo to @new_wrap_option
 **/
void
fo_inline_set_wrap_option (FoFo *fo_fo,
		         FoProperty *new_wrap_option)
{
  FoInline *fo_inline = (FoInline *) fo_fo;

  g_return_if_fail (fo_inline != NULL);
  g_return_if_fail (FO_IS_INLINE (fo_inline));
  g_return_if_fail (FO_IS_PROPERTY_WRAP_OPTION (new_wrap_option));

  if (new_wrap_option != NULL)
    {
      g_object_ref (new_wrap_option);
    }
  if (fo_inline->wrap_option != NULL)
    {
      g_object_unref (fo_inline->wrap_option);
    }
  fo_inline->wrap_option = new_wrap_option;
  /*g_object_notify (G_OBJECT (fo_inline), "wrap-option");*/
}
