/* Fo
 * fo-character.c: 'character' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-character.c,v 1.10 2006/03/28 11:18:51 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo/fo-inline-fo.h"
#include "fo/fo-character-private.h"
#include "fo-context-util.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-common-font.h"
#include "property/fo-property-alignment-adjust.h"
#include "property/fo-property-alignment-baseline.h"
#include "property/fo-property-background-color.h"
#include "property/fo-property-background-image.h"
#include "property/fo-property-baseline-shift.h"
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
#include "property/fo-property-character.h"
#include "property/fo-property-color.h"
#include "property/fo-property-dominant-baseline.h"
#include "property/fo-property-font-family.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-stretch.h"
#include "property/fo-property-font-style.h"
#include "property/fo-property-font-variant.h"
#include "property/fo-property-font-weight.h"
#include "property/fo-property-id.h"
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
#include "property/fo-property-score-spaces.h"
#include "property/fo-property-space-end.h"
#include "property/fo-property-space-start.h"

enum {
  PROP_0,
  PROP_ALIGNMENT_ADJUST,
  PROP_ALIGNMENT_BASELINE,
  PROP_BACKGROUND_COLOR,
  PROP_BACKGROUND_IMAGE,
  PROP_BASELINE_SHIFT,
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
  PROP_CHARACTER,
  PROP_COLOR,
  PROP_DOMINANT_BASELINE,
  PROP_FONT_FAMILY,
  PROP_FONT_SIZE,
  PROP_FONT_STRETCH,
  PROP_FONT_STYLE,
  PROP_FONT_VARIANT,
  PROP_FONT_WEIGHT,
  PROP_ID,
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
  PROP_SCORE_SPACES,
  PROP_SPACE_END,
  PROP_SPACE_START
};

static void fo_character_class_init  (FoCharacterClass *klass);
static void fo_character_inline_fo_init (FoInlineFoIface *iface);
static void fo_character_get_property (GObject      *object,
                                       guint         prop_id,
                                       GValue       *value,
                                       GParamSpec   *pspec);
static void fo_character_set_property (GObject      *object,
                                       guint         prop_id,
                                       const GValue *value,
                                       GParamSpec   *pspec);
static void fo_character_finalize    (GObject           *object);
static void fo_character_validate (FoFo      *fo,
                                   FoContext *current_context,
                                   FoContext *parent_context,
                                   GError   **error);
static void fo_character_update_from_context (FoFo      *fo,
                                              FoContext *context);
static void fo_character_debug_dump_properties (FoFo *fo,
                                                gint  depth);
static void fo_character_get_text_attr_list (FoFo *fo_inline_fo,
					     FoDoc   *fo_doc,
					     GString *text,
					     GList **attr_glist,
					     guint debug_level);

static gpointer parent_class;

/**
 * fo_character_get_type:
 * 
 * Register the #FoCharacter object type.
 * 
 * Return value: #GType value of the #FoCharacter object type.
 **/
GType
fo_character_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoCharacterClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_character_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoCharacter),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_inline_fo_info =
      {
	(GInterfaceInitFunc) fo_character_inline_fo_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "fo-character",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &fo_inline_fo_info);
    }

  return object_type;
}

/**
 * fo_character_class_init:
 * @klass: #FoCharacterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoCharacterClass.
 **/
void
fo_character_class_init (FoCharacterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_character_finalize;

  object_class->get_property = fo_character_get_property;
  object_class->set_property = fo_character_set_property;

  fofo_class->validate_content =   fo_fo_validate_content_empty;
  fofo_class->validate2 = fo_character_validate;
  fofo_class->update_from_context = fo_character_update_from_context;
  fofo_class->debug_dump_properties = fo_character_debug_dump_properties;

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
     PROP_CHARACTER,
     g_param_spec_object ("character",
			  _("Character"),
			  _("Character property"),
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
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
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
     PROP_SCORE_SPACES,
     g_param_spec_object ("score-spaces",
			  _("Score Spaces"),
			  _("Score Spaces property"),
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
}

/**
 * fo_character_inline_fo_init:
 * @iface: #FoInlineFoIFace structure for this class.
 * 
 * Initialize #FoInlineFoIface interface for this class.
 **/
void
fo_character_inline_fo_init (FoInlineFoIface *iface)
{
  iface->get_text_attr_list = fo_character_get_text_attr_list;
}

/**
 * fo_character_finalize:
 * @object: #FoCharacter object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoCharacter.
 **/
void
fo_character_finalize (GObject *object)
{
  FoCharacter *fo_character;

  fo_character = FO_CHARACTER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_character_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoCharacter.
 **/
void
fo_character_get_property (GObject    *object,
                           guint       prop_id,
                           GValue     *value,
                           GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ALIGNMENT_ADJUST:
      g_value_set_object (value, G_OBJECT (fo_character_get_alignment_adjust (fo_fo)));
      break;
    case PROP_ALIGNMENT_BASELINE:
      g_value_set_object (value, G_OBJECT (fo_character_get_alignment_baseline (fo_fo)));
      break;
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_background_color (fo_fo)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_character_get_background_image (fo_fo)));
      break;
    case PROP_BASELINE_SHIFT:
      g_value_set_object (value, G_OBJECT (fo_character_get_baseline_shift (fo_fo)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_after_color (fo_fo)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_after_style (fo_fo)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_after_width (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_before_color (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_before_style (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_before_width (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_bottom_color (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_bottom_style (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_bottom_width (fo_fo)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_end_color (fo_fo)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_end_style (fo_fo)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_end_width (fo_fo)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_left_color (fo_fo)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_left_style (fo_fo)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_left_width (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_right_color (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_right_style (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_right_width (fo_fo)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_start_color (fo_fo)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_start_style (fo_fo)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_start_width (fo_fo)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_top_color (fo_fo)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_top_style (fo_fo)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_character_get_border_top_width (fo_fo)));
      break;
    case PROP_CHARACTER:
      g_value_set_object (value, G_OBJECT (fo_character_get_character (fo_fo)));
      break;
    case PROP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_character_get_color (fo_fo)));
      break;
    case PROP_DOMINANT_BASELINE:
      g_value_set_object (value, G_OBJECT (fo_character_get_dominant_baseline (fo_fo)));
      break;
    case PROP_FONT_FAMILY:
      g_value_set_object (value, G_OBJECT (fo_character_get_font_family (fo_fo)));
      break;
    case PROP_FONT_SIZE:
      g_value_set_object (value, G_OBJECT (fo_character_get_font_size (fo_fo)));
      break;
    case PROP_FONT_STRETCH:
      g_value_set_object (value, G_OBJECT (fo_character_get_font_stretch (fo_fo)));
      break;
    case PROP_FONT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_character_get_font_style (fo_fo)));
      break;
    case PROP_FONT_VARIANT:
      g_value_set_object (value, G_OBJECT (fo_character_get_font_variant (fo_fo)));
      break;
    case PROP_FONT_WEIGHT:
      g_value_set_object (value, G_OBJECT (fo_character_get_font_weight (fo_fo)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_character_get_id (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT:
      g_value_set_object (value, G_OBJECT (fo_character_get_keep_with_next (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_character_get_keep_with_next_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_character_get_keep_with_next_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_character_get_keep_with_next_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      g_value_set_object (value, G_OBJECT (fo_character_get_keep_with_previous (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_character_get_keep_with_previous_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_character_get_keep_with_previous_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_character_get_keep_with_previous_within_page (fo_fo)));
      break;
    case PROP_LINE_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_character_get_line_height (fo_fo)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_character_get_padding_after (fo_fo)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_character_get_padding_before (fo_fo)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_character_get_padding_bottom (fo_fo)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_character_get_padding_end (fo_fo)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_character_get_padding_left (fo_fo)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_character_get_padding_right (fo_fo)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_character_get_padding_start (fo_fo)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_character_get_padding_top (fo_fo)));
      break;
    case PROP_SCORE_SPACES:
      g_value_set_object (value, G_OBJECT (fo_character_get_score_spaces (fo_fo)));
      break;
    case PROP_SPACE_END:
      g_value_set_object (value, G_OBJECT (fo_character_get_space_end (fo_fo)));
      break;
    case PROP_SPACE_START:
      g_value_set_object (value, G_OBJECT (fo_character_get_space_start (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_character_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoCharacter.
 **/
void
fo_character_set_property (GObject      *object,
                           guint         prop_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ALIGNMENT_ADJUST:
      fo_character_set_alignment_adjust (fo_fo, g_value_get_object (value));
      break;
    case PROP_ALIGNMENT_BASELINE:
      fo_character_set_alignment_baseline (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_COLOR:
      fo_character_set_background_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_character_set_background_image (fo_fo, g_value_get_object (value));
      break;
    case PROP_BASELINE_SHIFT:
      fo_character_set_baseline_shift (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_character_set_border_after_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_character_set_border_after_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_character_set_border_after_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_character_set_border_before_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_character_set_border_before_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_character_set_border_before_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_character_set_border_bottom_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_character_set_border_bottom_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_character_set_border_bottom_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_character_set_border_end_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_character_set_border_end_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_character_set_border_end_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_character_set_border_left_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_character_set_border_left_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_character_set_border_left_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_character_set_border_right_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_character_set_border_right_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_character_set_border_right_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_character_set_border_start_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_character_set_border_start_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_character_set_border_start_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_character_set_border_top_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_character_set_border_top_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_character_set_border_top_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_CHARACTER:
      fo_character_set_character (fo_fo, g_value_get_object (value));
      break;
    case PROP_COLOR:
      fo_character_set_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_DOMINANT_BASELINE:
      fo_character_set_dominant_baseline (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_FAMILY:
      fo_character_set_font_family (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_SIZE:
      fo_character_set_font_size (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_STRETCH:
      fo_character_set_font_stretch (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_STYLE:
      fo_character_set_font_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_VARIANT:
      fo_character_set_font_variant (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_WEIGHT:
      fo_character_set_font_weight (fo_fo, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_character_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT:
      fo_character_set_keep_with_next (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      fo_character_set_keep_with_next_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      fo_character_set_keep_with_next_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      fo_character_set_keep_with_next_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      fo_character_set_keep_with_previous (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      fo_character_set_keep_with_previous_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      fo_character_set_keep_with_previous_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      fo_character_set_keep_with_previous_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_LINE_HEIGHT:
      fo_character_set_line_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_character_set_padding_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_character_set_padding_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_character_set_padding_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_character_set_padding_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_character_set_padding_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_character_set_padding_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_character_set_padding_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_character_set_padding_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_SCORE_SPACES:
      fo_character_set_score_spaces (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_END:
      fo_character_set_space_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_START:
      fo_character_set_space_start (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_character_new:
 * 
 * Creates a new #FoCharacter initialized to default value.
 * 
 * Return value: the new #FoCharacter.
 **/
FoFo*
fo_character_new (void)
{
  return FO_FO (g_object_new (fo_character_get_type (),
			      NULL));
}

/**
 * fo_character_validate:
 * @fo:              #FoCharacter object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_character_validate (FoFo      *fo,
                       FoContext *current_context,
                       FoContext *parent_context,
                       GError   **error)
{
  FoCharacter *fo_character;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_character = FO_CHARACTER (fo);

  fo_context_util_dominant_baseline_resolve (current_context, parent_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_character_set_line_height (fo,
				fo_property_line_height_resolve (fo_character->line_height,
								 fo_character->font_size));
}

/**
 * fo_character_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_character_update_from_context (FoFo      *fo,
                                  FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_character_set_alignment_adjust (fo,
			  fo_context_get_alignment_adjust (context));
  fo_character_set_alignment_baseline (fo,
			  fo_context_get_alignment_baseline (context));
  fo_character_set_background_color (fo,
			  fo_context_get_background_color (context));
  fo_character_set_background_image (fo,
			  fo_context_get_background_image (context));
  fo_character_set_baseline_shift (fo,
			  fo_context_get_baseline_shift (context));
  fo_character_set_border_after_color (fo,
			  fo_context_get_border_after_color (context));
  fo_character_set_border_after_style (fo,
			  fo_context_get_border_after_style (context));
  fo_character_set_border_after_width (fo,
			  fo_context_get_border_after_width (context));
  fo_character_set_border_before_color (fo,
			  fo_context_get_border_before_color (context));
  fo_character_set_border_before_style (fo,
			  fo_context_get_border_before_style (context));
  fo_character_set_border_before_width (fo,
			  fo_context_get_border_before_width (context));
  fo_character_set_border_bottom_color (fo,
			  fo_context_get_border_bottom_color (context));
  fo_character_set_border_bottom_style (fo,
			  fo_context_get_border_bottom_style (context));
  fo_character_set_border_bottom_width (fo,
			  fo_context_get_border_bottom_width (context));
  fo_character_set_border_end_color (fo,
			  fo_context_get_border_end_color (context));
  fo_character_set_border_end_style (fo,
			  fo_context_get_border_end_style (context));
  fo_character_set_border_end_width (fo,
			  fo_context_get_border_end_width (context));
  fo_character_set_border_left_color (fo,
			  fo_context_get_border_left_color (context));
  fo_character_set_border_left_style (fo,
			  fo_context_get_border_left_style (context));
  fo_character_set_border_left_width (fo,
			  fo_context_get_border_left_width (context));
  fo_character_set_border_right_color (fo,
			  fo_context_get_border_right_color (context));
  fo_character_set_border_right_style (fo,
			  fo_context_get_border_right_style (context));
  fo_character_set_border_right_width (fo,
			  fo_context_get_border_right_width (context));
  fo_character_set_border_start_color (fo,
			  fo_context_get_border_start_color (context));
  fo_character_set_border_start_style (fo,
			  fo_context_get_border_start_style (context));
  fo_character_set_border_start_width (fo,
			  fo_context_get_border_start_width (context));
  fo_character_set_border_top_color (fo,
			  fo_context_get_border_top_color (context));
  fo_character_set_border_top_style (fo,
			  fo_context_get_border_top_style (context));
  fo_character_set_border_top_width (fo,
			  fo_context_get_border_top_width (context));
  fo_character_set_character (fo,
			  fo_context_get_character (context));
  fo_character_set_color (fo,
			  fo_context_get_color (context));
  fo_character_set_dominant_baseline (fo,
			  fo_context_get_dominant_baseline (context));
  fo_character_set_font_family (fo,
			  fo_context_get_font_family (context));
  fo_character_set_font_size (fo,
			  fo_context_get_font_size (context));
  fo_character_set_font_stretch (fo,
			  fo_context_get_font_stretch (context));
  fo_character_set_font_style (fo,
			  fo_context_get_font_style (context));
  fo_character_set_font_variant (fo,
			  fo_context_get_font_variant (context));
  fo_character_set_font_weight (fo,
			  fo_context_get_font_weight (context));
  fo_character_set_id (fo,
			  fo_context_get_id (context));
  fo_character_set_keep_with_next (fo,
			  fo_context_get_keep_with_next (context));
  fo_character_set_keep_with_next_within_column (fo,
			  fo_context_get_keep_with_next_within_column (context));
  fo_character_set_keep_with_next_within_line (fo,
			  fo_context_get_keep_with_next_within_line (context));
  fo_character_set_keep_with_next_within_page (fo,
			  fo_context_get_keep_with_next_within_page (context));
  fo_character_set_keep_with_previous (fo,
			  fo_context_get_keep_with_previous (context));
  fo_character_set_keep_with_previous_within_column (fo,
			  fo_context_get_keep_with_previous_within_column (context));
  fo_character_set_keep_with_previous_within_line (fo,
			  fo_context_get_keep_with_previous_within_line (context));
  fo_character_set_keep_with_previous_within_page (fo,
			  fo_context_get_keep_with_previous_within_page (context));
  fo_character_set_line_height (fo,
			  fo_context_get_line_height (context));
  fo_character_set_padding_after (fo,
			  fo_context_get_padding_after (context));
  fo_character_set_padding_before (fo,
			  fo_context_get_padding_before (context));
  fo_character_set_padding_bottom (fo,
			  fo_context_get_padding_bottom (context));
  fo_character_set_padding_end (fo,
			  fo_context_get_padding_end (context));
  fo_character_set_padding_left (fo,
			  fo_context_get_padding_left (context));
  fo_character_set_padding_right (fo,
			  fo_context_get_padding_right (context));
  fo_character_set_padding_start (fo,
			  fo_context_get_padding_start (context));
  fo_character_set_padding_top (fo,
			  fo_context_get_padding_top (context));
  fo_character_set_score_spaces (fo,
			  fo_context_get_score_spaces (context));
  fo_character_set_space_end (fo,
			  fo_context_get_space_end (context));
  fo_character_set_space_start (fo,
			  fo_context_get_space_start (context));
}

/**
 * fo_character_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_character_debug_dump_properties (FoFo *fo,
                                    gint  depth)
{
  FoCharacter *fo_character;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo));

  fo_character = FO_CHARACTER (fo);

  fo_object_debug_dump (fo_character->alignment_adjust, depth);
  fo_object_debug_dump (fo_character->alignment_baseline, depth);
  fo_object_debug_dump (fo_character->background_color, depth);
  fo_object_debug_dump (fo_character->background_image, depth);
  fo_object_debug_dump (fo_character->baseline_shift, depth);
  fo_object_debug_dump (fo_character->border_after_color, depth);
  fo_object_debug_dump (fo_character->border_after_style, depth);
  fo_object_debug_dump (fo_character->border_after_width, depth);
  fo_object_debug_dump (fo_character->border_before_color, depth);
  fo_object_debug_dump (fo_character->border_before_style, depth);
  fo_object_debug_dump (fo_character->border_before_width, depth);
  fo_object_debug_dump (fo_character->border_bottom_color, depth);
  fo_object_debug_dump (fo_character->border_bottom_style, depth);
  fo_object_debug_dump (fo_character->border_bottom_width, depth);
  fo_object_debug_dump (fo_character->border_end_color, depth);
  fo_object_debug_dump (fo_character->border_end_style, depth);
  fo_object_debug_dump (fo_character->border_end_width, depth);
  fo_object_debug_dump (fo_character->border_left_color, depth);
  fo_object_debug_dump (fo_character->border_left_style, depth);
  fo_object_debug_dump (fo_character->border_left_width, depth);
  fo_object_debug_dump (fo_character->border_right_color, depth);
  fo_object_debug_dump (fo_character->border_right_style, depth);
  fo_object_debug_dump (fo_character->border_right_width, depth);
  fo_object_debug_dump (fo_character->border_start_color, depth);
  fo_object_debug_dump (fo_character->border_start_style, depth);
  fo_object_debug_dump (fo_character->border_start_width, depth);
  fo_object_debug_dump (fo_character->border_top_color, depth);
  fo_object_debug_dump (fo_character->border_top_style, depth);
  fo_object_debug_dump (fo_character->border_top_width, depth);
  fo_object_debug_dump (fo_character->character, depth);
  fo_object_debug_dump (fo_character->color, depth);
  fo_object_debug_dump (fo_character->dominant_baseline, depth);
  fo_object_debug_dump (fo_character->font_family, depth);
  fo_object_debug_dump (fo_character->font_size, depth);
  fo_object_debug_dump (fo_character->font_stretch, depth);
  fo_object_debug_dump (fo_character->font_style, depth);
  fo_object_debug_dump (fo_character->font_variant, depth);
  fo_object_debug_dump (fo_character->font_weight, depth);
  fo_object_debug_dump (fo_character->id, depth);
  fo_object_debug_dump (fo_character->keep_with_next, depth);
  fo_object_debug_dump (fo_character->keep_with_next_within_column, depth);
  fo_object_debug_dump (fo_character->keep_with_next_within_line, depth);
  fo_object_debug_dump (fo_character->keep_with_next_within_page, depth);
  fo_object_debug_dump (fo_character->keep_with_previous, depth);
  fo_object_debug_dump (fo_character->keep_with_previous_within_column, depth);
  fo_object_debug_dump (fo_character->keep_with_previous_within_line, depth);
  fo_object_debug_dump (fo_character->keep_with_previous_within_page, depth);
  fo_object_debug_dump (fo_character->line_height, depth);
  fo_object_debug_dump (fo_character->padding_after, depth);
  fo_object_debug_dump (fo_character->padding_before, depth);
  fo_object_debug_dump (fo_character->padding_bottom, depth);
  fo_object_debug_dump (fo_character->padding_end, depth);
  fo_object_debug_dump (fo_character->padding_left, depth);
  fo_object_debug_dump (fo_character->padding_right, depth);
  fo_object_debug_dump (fo_character->padding_start, depth);
  fo_object_debug_dump (fo_character->padding_top, depth);
  fo_object_debug_dump (fo_character->score_spaces, depth);
  fo_object_debug_dump (fo_character->space_end, depth);
  fo_object_debug_dump (fo_character->space_start, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_character_get_text_attr_list:
 * @fo_inline_fo: The #FoInlineFo object.
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO.
 * @attr_glist:   The list of #PangoAttribute for the inline FO.
 * @debug_level:  Debug level.
 * 
 * Gets the text of the inline FO and its associated list of #PangoAttribute.
 **/
void
fo_character_get_text_attr_list (FoFo *fo_inline_fo,
				 FoDoc   *fo_doc,
				 GString *text,
				 GList **attr_glist,
				 guint debug_level)
{
  FoCharacter *fo_character;
  GList *my_attr_glist = NULL;
  gint start_index, end_index;

  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_inline_fo));

  fo_character = FO_CHARACTER (fo_inline_fo);

  start_index = text->len;

  g_string_append (text,
		   fo_char_get_value (fo_property_get_value (fo_character->character)));

  end_index = text->len;

  if (start_index != end_index)
    {
      PangoAttribute *pango_attr;

      my_attr_glist =
	g_list_concat (my_attr_glist,
		       fo_property_common_font_get_pango_attrs (fo_character->font_family,
								fo_character->font_size,
								fo_character->font_stretch,
								fo_character->font_style,
								fo_character->font_variant,
								fo_character->font_weight,
								start_index,
								end_index));

      pango_attr =
	fo_property_text_property_new_attr (fo_character->baseline_shift);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      /*
      pango_attr =
	fo_property_text_property_new_attr (fo_character->line_height);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
      */

      pango_attr =
	fo_property_text_property_new_attr (fo_character->color);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      if (FO_IS_COLOR (fo_property_get_value (fo_character->background_color)))
	{
	  pango_attr =
	    fo_property_text_property_new_attr (fo_character->background_color);
	  pango_attr->start_index = start_index;
	  pango_attr->end_index = end_index;
	  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
	}

      /*
      pango_attr =
	fo_property_text_property_new_attr (fo_character->alignment_adjust);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_character->alignment_baseline);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr_from_context (fo_character->dominant_baseline,
							 fo_fo_get_context (fo_inline_fo));
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_character->keep_with_next_within_line);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_character->keep_with_previous_within_line);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
      */
    }

  *attr_glist = g_list_concat (my_attr_glist,
			       *attr_glist);
}

/**
 * fo_character_get_alignment_adjust:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "alignment-adjust" property of @fo_fo.
 *
 * Return value: The "alignment-adjust" property value.
**/
FoProperty *
fo_character_get_alignment_adjust (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->alignment_adjust;
}

/**
 * fo_character_set_alignment_adjust:
 * @fo_fo: The #FoFo object.
 * @new_alignment_adjust: The new "alignment-adjust" property value.
 * 
 * Sets the "alignment-adjust" property of @fo_fo to @new_alignment_adjust.
 **/
void
fo_character_set_alignment_adjust (FoFo *fo_fo,
		         FoProperty *new_alignment_adjust)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_ALIGNMENT_ADJUST (new_alignment_adjust));

  if (new_alignment_adjust != NULL)
    {
      g_object_ref (new_alignment_adjust);
    }
  if (fo_character->alignment_adjust != NULL)
    {
      g_object_unref (fo_character->alignment_adjust);
    }
  fo_character->alignment_adjust = new_alignment_adjust;
  /*g_object_notify (G_OBJECT (fo_character), "alignment-adjust");*/
}

/**
 * fo_character_get_alignment_baseline:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "alignment-baseline" property of @fo_fo.
 *
 * Return value: The "alignment-baseline" property value.
**/
FoProperty *
fo_character_get_alignment_baseline (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->alignment_baseline;
}

/**
 * fo_character_set_alignment_baseline:
 * @fo_fo: The #FoFo object.
 * @new_alignment_baseline: The new "alignment-baseline" property value.
 * 
 * Sets the "alignment-baseline" property of @fo_fo to @new_alignment_baseline.
 **/
void
fo_character_set_alignment_baseline (FoFo *fo_fo,
		         FoProperty *new_alignment_baseline)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_ALIGNMENT_BASELINE (new_alignment_baseline));

  if (new_alignment_baseline != NULL)
    {
      g_object_ref (new_alignment_baseline);
    }
  if (fo_character->alignment_baseline != NULL)
    {
      g_object_unref (fo_character->alignment_baseline);
    }
  fo_character->alignment_baseline = new_alignment_baseline;
  /*g_object_notify (G_OBJECT (fo_character), "alignment-baseline");*/
}

/**
 * fo_character_get_background_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-color" property of @fo_fo.
 *
 * Return value: The "background-color" property value.
**/
FoProperty *
fo_character_get_background_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->background_color;
}

/**
 * fo_character_set_background_color:
 * @fo_fo: The #FoFo object.
 * @new_background_color: The new "background-color" property value.
 * 
 * Sets the "background-color" property of @fo_fo to @new_background_color.
 **/
void
fo_character_set_background_color (FoFo *fo_fo,
		         FoProperty *new_background_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BACKGROUND_COLOR (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref (new_background_color);
    }
  if (fo_character->background_color != NULL)
    {
      g_object_unref (fo_character->background_color);
    }
  fo_character->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_character), "background-color");*/
}

/**
 * fo_character_get_background_image:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "background-image" property of @fo_fo.
 *
 * Return value: The "background-image" property value.
**/
FoProperty *
fo_character_get_background_image (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->background_image;
}

/**
 * fo_character_set_background_image:
 * @fo_fo: The #FoFo object.
 * @new_background_image: The new "background-image" property value.
 * 
 * Sets the "background-image" property of @fo_fo to @new_background_image.
 **/
void
fo_character_set_background_image (FoFo *fo_fo,
		         FoProperty *new_background_image)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref (new_background_image);
    }
  if (fo_character->background_image != NULL)
    {
      g_object_unref (fo_character->background_image);
    }
  fo_character->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_character), "background-image");*/
}

/**
 * fo_character_get_baseline_shift:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "baseline-shift" property of @fo_fo.
 *
 * Return value: The "baseline-shift" property value.
**/
FoProperty *
fo_character_get_baseline_shift (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->baseline_shift;
}

/**
 * fo_character_set_baseline_shift:
 * @fo_fo: The #FoFo object.
 * @new_baseline_shift: The new "baseline-shift" property value.
 * 
 * Sets the "baseline-shift" property of @fo_fo to @new_baseline_shift.
 **/
void
fo_character_set_baseline_shift (FoFo *fo_fo,
		         FoProperty *new_baseline_shift)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BASELINE_SHIFT (new_baseline_shift));

  if (new_baseline_shift != NULL)
    {
      g_object_ref (new_baseline_shift);
    }
  if (fo_character->baseline_shift != NULL)
    {
      g_object_unref (fo_character->baseline_shift);
    }
  fo_character->baseline_shift = new_baseline_shift;
  /*g_object_notify (G_OBJECT (fo_character), "baseline-shift");*/
}

/**
 * fo_character_get_border_after_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-color" property of @fo_fo.
 *
 * Return value: The "border-after-color" property value.
**/
FoProperty *
fo_character_get_border_after_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_after_color;
}

/**
 * fo_character_set_border_after_color:
 * @fo_fo: The #FoFo object.
 * @new_border_after_color: The new "border-after-color" property value.
 * 
 * Sets the "border-after-color" property of @fo_fo to @new_border_after_color.
 **/
void
fo_character_set_border_after_color (FoFo *fo_fo,
		         FoProperty *new_border_after_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref (new_border_after_color);
    }
  if (fo_character->border_after_color != NULL)
    {
      g_object_unref (fo_character->border_after_color);
    }
  fo_character->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_character), "border-after-color");*/
}

/**
 * fo_character_get_border_after_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-style" property of @fo_fo.
 *
 * Return value: The "border-after-style" property value.
**/
FoProperty *
fo_character_get_border_after_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_after_style;
}

/**
 * fo_character_set_border_after_style:
 * @fo_fo: The #FoFo object.
 * @new_border_after_style: The new "border-after-style" property value.
 * 
 * Sets the "border-after-style" property of @fo_fo to @new_border_after_style.
 **/
void
fo_character_set_border_after_style (FoFo *fo_fo,
		         FoProperty *new_border_after_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref (new_border_after_style);
    }
  if (fo_character->border_after_style != NULL)
    {
      g_object_unref (fo_character->border_after_style);
    }
  fo_character->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_character), "border-after-style");*/
}

/**
 * fo_character_get_border_after_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-after-width" property of @fo_fo.
 *
 * Return value: The "border-after-width" property value.
**/
FoProperty *
fo_character_get_border_after_width (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_after_width;
}

/**
 * fo_character_set_border_after_width:
 * @fo_fo: The #FoFo object.
 * @new_border_after_width: The new "border-after-width" property value.
 * 
 * Sets the "border-after-width" property of @fo_fo to @new_border_after_width.
 **/
void
fo_character_set_border_after_width (FoFo *fo_fo,
		         FoProperty *new_border_after_width)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref (new_border_after_width);
    }
  if (fo_character->border_after_width != NULL)
    {
      g_object_unref (fo_character->border_after_width);
    }
  fo_character->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_character), "border-after-width");*/
}

/**
 * fo_character_get_border_before_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-color" property of @fo_fo.
 *
 * Return value: The "border-before-color" property value.
**/
FoProperty *
fo_character_get_border_before_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_before_color;
}

/**
 * fo_character_set_border_before_color:
 * @fo_fo: The #FoFo object.
 * @new_border_before_color: The new "border-before-color" property value.
 * 
 * Sets the "border-before-color" property of @fo_fo to @new_border_before_color.
 **/
void
fo_character_set_border_before_color (FoFo *fo_fo,
		         FoProperty *new_border_before_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref (new_border_before_color);
    }
  if (fo_character->border_before_color != NULL)
    {
      g_object_unref (fo_character->border_before_color);
    }
  fo_character->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_character), "border-before-color");*/
}

/**
 * fo_character_get_border_before_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-style" property of @fo_fo.
 *
 * Return value: The "border-before-style" property value.
**/
FoProperty *
fo_character_get_border_before_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_before_style;
}

/**
 * fo_character_set_border_before_style:
 * @fo_fo: The #FoFo object.
 * @new_border_before_style: The new "border-before-style" property value.
 * 
 * Sets the "border-before-style" property of @fo_fo to @new_border_before_style.
 **/
void
fo_character_set_border_before_style (FoFo *fo_fo,
		         FoProperty *new_border_before_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref (new_border_before_style);
    }
  if (fo_character->border_before_style != NULL)
    {
      g_object_unref (fo_character->border_before_style);
    }
  fo_character->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_character), "border-before-style");*/
}

/**
 * fo_character_get_border_before_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-before-width" property of @fo_fo.
 *
 * Return value: The "border-before-width" property value.
**/
FoProperty *
fo_character_get_border_before_width (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_before_width;
}

/**
 * fo_character_set_border_before_width:
 * @fo_fo: The #FoFo object.
 * @new_border_before_width: The new "border-before-width" property value.
 * 
 * Sets the "border-before-width" property of @fo_fo to @new_border_before_width.
 **/
void
fo_character_set_border_before_width (FoFo *fo_fo,
		         FoProperty *new_border_before_width)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref (new_border_before_width);
    }
  if (fo_character->border_before_width != NULL)
    {
      g_object_unref (fo_character->border_before_width);
    }
  fo_character->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_character), "border-before-width");*/
}

/**
 * fo_character_get_border_bottom_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-color" property of @fo_fo.
 *
 * Return value: The "border-bottom-color" property value.
**/
FoProperty *
fo_character_get_border_bottom_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_bottom_color;
}

/**
 * fo_character_set_border_bottom_color:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_color: The new "border-bottom-color" property value.
 * 
 * Sets the "border-bottom-color" property of @fo_fo to @new_border_bottom_color.
 **/
void
fo_character_set_border_bottom_color (FoFo *fo_fo,
		         FoProperty *new_border_bottom_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref (new_border_bottom_color);
    }
  if (fo_character->border_bottom_color != NULL)
    {
      g_object_unref (fo_character->border_bottom_color);
    }
  fo_character->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_character), "border-bottom-color");*/
}

/**
 * fo_character_get_border_bottom_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-style" property of @fo_fo.
 *
 * Return value: The "border-bottom-style" property value.
**/
FoProperty *
fo_character_get_border_bottom_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_bottom_style;
}

/**
 * fo_character_set_border_bottom_style:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_style: The new "border-bottom-style" property value.
 * 
 * Sets the "border-bottom-style" property of @fo_fo to @new_border_bottom_style.
 **/
void
fo_character_set_border_bottom_style (FoFo *fo_fo,
		         FoProperty *new_border_bottom_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref (new_border_bottom_style);
    }
  if (fo_character->border_bottom_style != NULL)
    {
      g_object_unref (fo_character->border_bottom_style);
    }
  fo_character->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_character), "border-bottom-style");*/
}

/**
 * fo_character_get_border_bottom_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-bottom-width" property of @fo_fo.
 *
 * Return value: The "border-bottom-width" property value.
**/
FoProperty *
fo_character_get_border_bottom_width (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_bottom_width;
}

/**
 * fo_character_set_border_bottom_width:
 * @fo_fo: The #FoFo object.
 * @new_border_bottom_width: The new "border-bottom-width" property value.
 * 
 * Sets the "border-bottom-width" property of @fo_fo to @new_border_bottom_width.
 **/
void
fo_character_set_border_bottom_width (FoFo *fo_fo,
		         FoProperty *new_border_bottom_width)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref (new_border_bottom_width);
    }
  if (fo_character->border_bottom_width != NULL)
    {
      g_object_unref (fo_character->border_bottom_width);
    }
  fo_character->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_character), "border-bottom-width");*/
}

/**
 * fo_character_get_border_end_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-color" property of @fo_fo.
 *
 * Return value: The "border-end-color" property value.
**/
FoProperty *
fo_character_get_border_end_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_end_color;
}

/**
 * fo_character_set_border_end_color:
 * @fo_fo: The #FoFo object.
 * @new_border_end_color: The new "border-end-color" property value.
 * 
 * Sets the "border-end-color" property of @fo_fo to @new_border_end_color.
 **/
void
fo_character_set_border_end_color (FoFo *fo_fo,
		         FoProperty *new_border_end_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref (new_border_end_color);
    }
  if (fo_character->border_end_color != NULL)
    {
      g_object_unref (fo_character->border_end_color);
    }
  fo_character->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_character), "border-end-color");*/
}

/**
 * fo_character_get_border_end_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-style" property of @fo_fo.
 *
 * Return value: The "border-end-style" property value.
**/
FoProperty *
fo_character_get_border_end_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_end_style;
}

/**
 * fo_character_set_border_end_style:
 * @fo_fo: The #FoFo object.
 * @new_border_end_style: The new "border-end-style" property value.
 * 
 * Sets the "border-end-style" property of @fo_fo to @new_border_end_style.
 **/
void
fo_character_set_border_end_style (FoFo *fo_fo,
		         FoProperty *new_border_end_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref (new_border_end_style);
    }
  if (fo_character->border_end_style != NULL)
    {
      g_object_unref (fo_character->border_end_style);
    }
  fo_character->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_character), "border-end-style");*/
}

/**
 * fo_character_get_border_end_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-end-width" property of @fo_fo.
 *
 * Return value: The "border-end-width" property value.
**/
FoProperty *
fo_character_get_border_end_width (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_end_width;
}

/**
 * fo_character_set_border_end_width:
 * @fo_fo: The #FoFo object.
 * @new_border_end_width: The new "border-end-width" property value.
 * 
 * Sets the "border-end-width" property of @fo_fo to @new_border_end_width.
 **/
void
fo_character_set_border_end_width (FoFo *fo_fo,
		         FoProperty *new_border_end_width)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref (new_border_end_width);
    }
  if (fo_character->border_end_width != NULL)
    {
      g_object_unref (fo_character->border_end_width);
    }
  fo_character->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_character), "border-end-width");*/
}

/**
 * fo_character_get_border_left_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-color" property of @fo_fo.
 *
 * Return value: The "border-left-color" property value.
**/
FoProperty *
fo_character_get_border_left_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_left_color;
}

/**
 * fo_character_set_border_left_color:
 * @fo_fo: The #FoFo object.
 * @new_border_left_color: The new "border-left-color" property value.
 * 
 * Sets the "border-left-color" property of @fo_fo to @new_border_left_color.
 **/
void
fo_character_set_border_left_color (FoFo *fo_fo,
		         FoProperty *new_border_left_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref (new_border_left_color);
    }
  if (fo_character->border_left_color != NULL)
    {
      g_object_unref (fo_character->border_left_color);
    }
  fo_character->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_character), "border-left-color");*/
}

/**
 * fo_character_get_border_left_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-style" property of @fo_fo.
 *
 * Return value: The "border-left-style" property value.
**/
FoProperty *
fo_character_get_border_left_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_left_style;
}

/**
 * fo_character_set_border_left_style:
 * @fo_fo: The #FoFo object.
 * @new_border_left_style: The new "border-left-style" property value.
 * 
 * Sets the "border-left-style" property of @fo_fo to @new_border_left_style.
 **/
void
fo_character_set_border_left_style (FoFo *fo_fo,
		         FoProperty *new_border_left_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref (new_border_left_style);
    }
  if (fo_character->border_left_style != NULL)
    {
      g_object_unref (fo_character->border_left_style);
    }
  fo_character->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_character), "border-left-style");*/
}

/**
 * fo_character_get_border_left_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-left-width" property of @fo_fo.
 *
 * Return value: The "border-left-width" property value.
**/
FoProperty *
fo_character_get_border_left_width (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_left_width;
}

/**
 * fo_character_set_border_left_width:
 * @fo_fo: The #FoFo object.
 * @new_border_left_width: The new "border-left-width" property value.
 * 
 * Sets the "border-left-width" property of @fo_fo to @new_border_left_width.
 **/
void
fo_character_set_border_left_width (FoFo *fo_fo,
		         FoProperty *new_border_left_width)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref (new_border_left_width);
    }
  if (fo_character->border_left_width != NULL)
    {
      g_object_unref (fo_character->border_left_width);
    }
  fo_character->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_character), "border-left-width");*/
}

/**
 * fo_character_get_border_right_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-color" property of @fo_fo.
 *
 * Return value: The "border-right-color" property value.
**/
FoProperty *
fo_character_get_border_right_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_right_color;
}

/**
 * fo_character_set_border_right_color:
 * @fo_fo: The #FoFo object.
 * @new_border_right_color: The new "border-right-color" property value.
 * 
 * Sets the "border-right-color" property of @fo_fo to @new_border_right_color.
 **/
void
fo_character_set_border_right_color (FoFo *fo_fo,
		         FoProperty *new_border_right_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref (new_border_right_color);
    }
  if (fo_character->border_right_color != NULL)
    {
      g_object_unref (fo_character->border_right_color);
    }
  fo_character->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_character), "border-right-color");*/
}

/**
 * fo_character_get_border_right_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-style" property of @fo_fo.
 *
 * Return value: The "border-right-style" property value.
**/
FoProperty *
fo_character_get_border_right_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_right_style;
}

/**
 * fo_character_set_border_right_style:
 * @fo_fo: The #FoFo object.
 * @new_border_right_style: The new "border-right-style" property value.
 * 
 * Sets the "border-right-style" property of @fo_fo to @new_border_right_style.
 **/
void
fo_character_set_border_right_style (FoFo *fo_fo,
		         FoProperty *new_border_right_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref (new_border_right_style);
    }
  if (fo_character->border_right_style != NULL)
    {
      g_object_unref (fo_character->border_right_style);
    }
  fo_character->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_character), "border-right-style");*/
}

/**
 * fo_character_get_border_right_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-right-width" property of @fo_fo.
 *
 * Return value: The "border-right-width" property value.
**/
FoProperty *
fo_character_get_border_right_width (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_right_width;
}

/**
 * fo_character_set_border_right_width:
 * @fo_fo: The #FoFo object.
 * @new_border_right_width: The new "border-right-width" property value.
 * 
 * Sets the "border-right-width" property of @fo_fo to @new_border_right_width.
 **/
void
fo_character_set_border_right_width (FoFo *fo_fo,
		         FoProperty *new_border_right_width)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref (new_border_right_width);
    }
  if (fo_character->border_right_width != NULL)
    {
      g_object_unref (fo_character->border_right_width);
    }
  fo_character->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_character), "border-right-width");*/
}

/**
 * fo_character_get_border_start_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-color" property of @fo_fo.
 *
 * Return value: The "border-start-color" property value.
**/
FoProperty *
fo_character_get_border_start_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_start_color;
}

/**
 * fo_character_set_border_start_color:
 * @fo_fo: The #FoFo object.
 * @new_border_start_color: The new "border-start-color" property value.
 * 
 * Sets the "border-start-color" property of @fo_fo to @new_border_start_color.
 **/
void
fo_character_set_border_start_color (FoFo *fo_fo,
		         FoProperty *new_border_start_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref (new_border_start_color);
    }
  if (fo_character->border_start_color != NULL)
    {
      g_object_unref (fo_character->border_start_color);
    }
  fo_character->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_character), "border-start-color");*/
}

/**
 * fo_character_get_border_start_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-style" property of @fo_fo.
 *
 * Return value: The "border-start-style" property value.
**/
FoProperty *
fo_character_get_border_start_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_start_style;
}

/**
 * fo_character_set_border_start_style:
 * @fo_fo: The #FoFo object.
 * @new_border_start_style: The new "border-start-style" property value.
 * 
 * Sets the "border-start-style" property of @fo_fo to @new_border_start_style.
 **/
void
fo_character_set_border_start_style (FoFo *fo_fo,
		         FoProperty *new_border_start_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref (new_border_start_style);
    }
  if (fo_character->border_start_style != NULL)
    {
      g_object_unref (fo_character->border_start_style);
    }
  fo_character->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_character), "border-start-style");*/
}

/**
 * fo_character_get_border_start_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-start-width" property of @fo_fo.
 *
 * Return value: The "border-start-width" property value.
**/
FoProperty *
fo_character_get_border_start_width (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_start_width;
}

/**
 * fo_character_set_border_start_width:
 * @fo_fo: The #FoFo object.
 * @new_border_start_width: The new "border-start-width" property value.
 * 
 * Sets the "border-start-width" property of @fo_fo to @new_border_start_width.
 **/
void
fo_character_set_border_start_width (FoFo *fo_fo,
		         FoProperty *new_border_start_width)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref (new_border_start_width);
    }
  if (fo_character->border_start_width != NULL)
    {
      g_object_unref (fo_character->border_start_width);
    }
  fo_character->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_character), "border-start-width");*/
}

/**
 * fo_character_get_border_top_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-color" property of @fo_fo.
 *
 * Return value: The "border-top-color" property value.
**/
FoProperty *
fo_character_get_border_top_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_top_color;
}

/**
 * fo_character_set_border_top_color:
 * @fo_fo: The #FoFo object.
 * @new_border_top_color: The new "border-top-color" property value.
 * 
 * Sets the "border-top-color" property of @fo_fo to @new_border_top_color.
 **/
void
fo_character_set_border_top_color (FoFo *fo_fo,
		         FoProperty *new_border_top_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref (new_border_top_color);
    }
  if (fo_character->border_top_color != NULL)
    {
      g_object_unref (fo_character->border_top_color);
    }
  fo_character->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_character), "border-top-color");*/
}

/**
 * fo_character_get_border_top_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-style" property of @fo_fo.
 *
 * Return value: The "border-top-style" property value.
**/
FoProperty *
fo_character_get_border_top_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_top_style;
}

/**
 * fo_character_set_border_top_style:
 * @fo_fo: The #FoFo object.
 * @new_border_top_style: The new "border-top-style" property value.
 * 
 * Sets the "border-top-style" property of @fo_fo to @new_border_top_style.
 **/
void
fo_character_set_border_top_style (FoFo *fo_fo,
		         FoProperty *new_border_top_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref (new_border_top_style);
    }
  if (fo_character->border_top_style != NULL)
    {
      g_object_unref (fo_character->border_top_style);
    }
  fo_character->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_character), "border-top-style");*/
}

/**
 * fo_character_get_border_top_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "border-top-width" property of @fo_fo.
 *
 * Return value: The "border-top-width" property value.
**/
FoProperty *
fo_character_get_border_top_width (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->border_top_width;
}

/**
 * fo_character_set_border_top_width:
 * @fo_fo: The #FoFo object.
 * @new_border_top_width: The new "border-top-width" property value.
 * 
 * Sets the "border-top-width" property of @fo_fo to @new_border_top_width.
 **/
void
fo_character_set_border_top_width (FoFo *fo_fo,
		         FoProperty *new_border_top_width)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref (new_border_top_width);
    }
  if (fo_character->border_top_width != NULL)
    {
      g_object_unref (fo_character->border_top_width);
    }
  fo_character->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_character), "border-top-width");*/
}

/**
 * fo_character_get_character:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "character" property of @fo_fo.
 *
 * Return value: The "character" property value.
**/
FoProperty *
fo_character_get_character (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->character;
}

/**
 * fo_character_set_character:
 * @fo_fo: The #FoFo object.
 * @new_character: The new "character" property value.
 * 
 * Sets the "character" property of @fo_fo to @new_character.
 **/
void
fo_character_set_character (FoFo *fo_fo,
		         FoProperty *new_character)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_CHARACTER (new_character));

  if (new_character != NULL)
    {
      g_object_ref (new_character);
    }
  if (fo_character->character != NULL)
    {
      g_object_unref (fo_character->character);
    }
  fo_character->character = new_character;
  /*g_object_notify (G_OBJECT (fo_character), "character");*/
}

/**
 * fo_character_get_color:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "color" property of @fo_fo.
 *
 * Return value: The "color" property value.
**/
FoProperty *
fo_character_get_color (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->color;
}

/**
 * fo_character_set_color:
 * @fo_fo: The #FoFo object.
 * @new_color: The new "color" property value.
 * 
 * Sets the "color" property of @fo_fo to @new_color.
 **/
void
fo_character_set_color (FoFo *fo_fo,
		         FoProperty *new_color)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_COLOR (new_color));

  if (new_color != NULL)
    {
      g_object_ref (new_color);
    }
  if (fo_character->color != NULL)
    {
      g_object_unref (fo_character->color);
    }
  fo_character->color = new_color;
  /*g_object_notify (G_OBJECT (fo_character), "color");*/
}

/**
 * fo_character_get_dominant_baseline:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "dominant-baseline" property of @fo_fo.
 *
 * Return value: The "dominant-baseline" property value.
**/
FoProperty *
fo_character_get_dominant_baseline (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->dominant_baseline;
}

/**
 * fo_character_set_dominant_baseline:
 * @fo_fo: The #FoFo object.
 * @new_dominant_baseline: The new "dominant-baseline" property value.
 * 
 * Sets the "dominant-baseline" property of @fo_fo to @new_dominant_baseline.
 **/
void
fo_character_set_dominant_baseline (FoFo *fo_fo,
		         FoProperty *new_dominant_baseline)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_DOMINANT_BASELINE (new_dominant_baseline));

  if (new_dominant_baseline != NULL)
    {
      g_object_ref (new_dominant_baseline);
    }
  if (fo_character->dominant_baseline != NULL)
    {
      g_object_unref (fo_character->dominant_baseline);
    }
  fo_character->dominant_baseline = new_dominant_baseline;
  /*g_object_notify (G_OBJECT (fo_character), "dominant-baseline");*/
}

/**
 * fo_character_get_font_family:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-family" property of @fo_fo.
 *
 * Return value: The "font-family" property value.
**/
FoProperty *
fo_character_get_font_family (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->font_family;
}

/**
 * fo_character_set_font_family:
 * @fo_fo: The #FoFo object.
 * @new_font_family: The new "font-family" property value.
 * 
 * Sets the "font-family" property of @fo_fo to @new_font_family.
 **/
void
fo_character_set_font_family (FoFo *fo_fo,
		         FoProperty *new_font_family)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_FONT_FAMILY (new_font_family));

  if (new_font_family != NULL)
    {
      g_object_ref (new_font_family);
    }
  if (fo_character->font_family != NULL)
    {
      g_object_unref (fo_character->font_family);
    }
  fo_character->font_family = new_font_family;
  /*g_object_notify (G_OBJECT (fo_character), "font-family");*/
}

/**
 * fo_character_get_font_size:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-size" property of @fo_fo.
 *
 * Return value: The "font-size" property value.
**/
FoProperty *
fo_character_get_font_size (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->font_size;
}

/**
 * fo_character_set_font_size:
 * @fo_fo: The #FoFo object.
 * @new_font_size: The new "font-size" property value.
 * 
 * Sets the "font-size" property of @fo_fo to @new_font_size.
 **/
void
fo_character_set_font_size (FoFo *fo_fo,
		         FoProperty *new_font_size)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_FONT_SIZE (new_font_size));

  if (new_font_size != NULL)
    {
      g_object_ref (new_font_size);
    }
  if (fo_character->font_size != NULL)
    {
      g_object_unref (fo_character->font_size);
    }
  fo_character->font_size = new_font_size;
  /*g_object_notify (G_OBJECT (fo_character), "font-size");*/
}

/**
 * fo_character_get_font_stretch:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-stretch" property of @fo_fo.
 *
 * Return value: The "font-stretch" property value.
**/
FoProperty *
fo_character_get_font_stretch (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->font_stretch;
}

/**
 * fo_character_set_font_stretch:
 * @fo_fo: The #FoFo object.
 * @new_font_stretch: The new "font-stretch" property value.
 * 
 * Sets the "font-stretch" property of @fo_fo to @new_font_stretch.
 **/
void
fo_character_set_font_stretch (FoFo *fo_fo,
		         FoProperty *new_font_stretch)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_FONT_STRETCH (new_font_stretch));

  if (new_font_stretch != NULL)
    {
      g_object_ref (new_font_stretch);
    }
  if (fo_character->font_stretch != NULL)
    {
      g_object_unref (fo_character->font_stretch);
    }
  fo_character->font_stretch = new_font_stretch;
  /*g_object_notify (G_OBJECT (fo_character), "font-stretch");*/
}

/**
 * fo_character_get_font_style:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-style" property of @fo_fo.
 *
 * Return value: The "font-style" property value.
**/
FoProperty *
fo_character_get_font_style (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->font_style;
}

/**
 * fo_character_set_font_style:
 * @fo_fo: The #FoFo object.
 * @new_font_style: The new "font-style" property value.
 * 
 * Sets the "font-style" property of @fo_fo to @new_font_style.
 **/
void
fo_character_set_font_style (FoFo *fo_fo,
		         FoProperty *new_font_style)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_FONT_STYLE (new_font_style));

  if (new_font_style != NULL)
    {
      g_object_ref (new_font_style);
    }
  if (fo_character->font_style != NULL)
    {
      g_object_unref (fo_character->font_style);
    }
  fo_character->font_style = new_font_style;
  /*g_object_notify (G_OBJECT (fo_character), "font-style");*/
}

/**
 * fo_character_get_font_variant:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-variant" property of @fo_fo.
 *
 * Return value: The "font-variant" property value.
**/
FoProperty *
fo_character_get_font_variant (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->font_variant;
}

/**
 * fo_character_set_font_variant:
 * @fo_fo: The #FoFo object.
 * @new_font_variant: The new "font-variant" property value.
 * 
 * Sets the "font-variant" property of @fo_fo to @new_font_variant.
 **/
void
fo_character_set_font_variant (FoFo *fo_fo,
		         FoProperty *new_font_variant)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_FONT_VARIANT (new_font_variant));

  if (new_font_variant != NULL)
    {
      g_object_ref (new_font_variant);
    }
  if (fo_character->font_variant != NULL)
    {
      g_object_unref (fo_character->font_variant);
    }
  fo_character->font_variant = new_font_variant;
  /*g_object_notify (G_OBJECT (fo_character), "font-variant");*/
}

/**
 * fo_character_get_font_weight:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "font-weight" property of @fo_fo.
 *
 * Return value: The "font-weight" property value.
**/
FoProperty *
fo_character_get_font_weight (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->font_weight;
}

/**
 * fo_character_set_font_weight:
 * @fo_fo: The #FoFo object.
 * @new_font_weight: The new "font-weight" property value.
 * 
 * Sets the "font-weight" property of @fo_fo to @new_font_weight.
 **/
void
fo_character_set_font_weight (FoFo *fo_fo,
		         FoProperty *new_font_weight)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_FONT_WEIGHT (new_font_weight));

  if (new_font_weight != NULL)
    {
      g_object_ref (new_font_weight);
    }
  if (fo_character->font_weight != NULL)
    {
      g_object_unref (fo_character->font_weight);
    }
  fo_character->font_weight = new_font_weight;
  /*g_object_notify (G_OBJECT (fo_character), "font-weight");*/
}

/**
 * fo_character_get_id:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "id" property of @fo_fo.
 *
 * Return value: The "id" property value.
**/
FoProperty *
fo_character_get_id (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->id;
}

/**
 * fo_character_set_id:
 * @fo_fo: The #FoFo object.
 * @new_id: The new "id" property value.
 * 
 * Sets the "id" property of @fo_fo to @new_id.
 **/
void
fo_character_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_character->id != NULL)
    {
      g_object_unref (fo_character->id);
    }
  fo_character->id = new_id;
  /*g_object_notify (G_OBJECT (fo_character), "id");*/
}

/**
 * fo_character_get_keep_with_next:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next" property of @fo_fo.
 *
 * Return value: The "keep-with-next" property value.
**/
FoProperty *
fo_character_get_keep_with_next (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->keep_with_next;
}

/**
 * fo_character_set_keep_with_next:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next: The new "keep-with-next" property value.
 * 
 * Sets the "keep-with-next" property of @fo_fo to @new_keep_with_next.
 **/
void
fo_character_set_keep_with_next (FoFo *fo_fo,
		         FoProperty *new_keep_with_next)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT (new_keep_with_next));

  if (new_keep_with_next != NULL)
    {
      g_object_ref (new_keep_with_next);
    }
  if (fo_character->keep_with_next != NULL)
    {
      g_object_unref (fo_character->keep_with_next);
    }
  fo_character->keep_with_next = new_keep_with_next;
  /*g_object_notify (G_OBJECT (fo_character), "keep-with-next");*/
}

/**
 * fo_character_get_keep_with_next_within_column:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-column" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-column" property value.
**/
FoProperty *
fo_character_get_keep_with_next_within_column (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->keep_with_next_within_column;
}

/**
 * fo_character_set_keep_with_next_within_column:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_column: The new "keep-with-next-within-column" property value.
 * 
 * Sets the "keep-with-next-within-column" property of @fo_fo to @new_keep_with_next_within_column.
 **/
void
fo_character_set_keep_with_next_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_column)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_COLUMN (new_keep_with_next_within_column));

  if (new_keep_with_next_within_column != NULL)
    {
      g_object_ref (new_keep_with_next_within_column);
    }
  if (fo_character->keep_with_next_within_column != NULL)
    {
      g_object_unref (fo_character->keep_with_next_within_column);
    }
  fo_character->keep_with_next_within_column = new_keep_with_next_within_column;
  /*g_object_notify (G_OBJECT (fo_character), "keep-with-next-within-column");*/
}

/**
 * fo_character_get_keep_with_next_within_line:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-line" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-line" property value.
**/
FoProperty *
fo_character_get_keep_with_next_within_line (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->keep_with_next_within_line;
}

/**
 * fo_character_set_keep_with_next_within_line:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_line: The new "keep-with-next-within-line" property value.
 * 
 * Sets the "keep-with-next-within-line" property of @fo_fo to @new_keep_with_next_within_line.
 **/
void
fo_character_set_keep_with_next_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_line)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (new_keep_with_next_within_line));

  if (new_keep_with_next_within_line != NULL)
    {
      g_object_ref (new_keep_with_next_within_line);
    }
  if (fo_character->keep_with_next_within_line != NULL)
    {
      g_object_unref (fo_character->keep_with_next_within_line);
    }
  fo_character->keep_with_next_within_line = new_keep_with_next_within_line;
  /*g_object_notify (G_OBJECT (fo_character), "keep-with-next-within-line");*/
}

/**
 * fo_character_get_keep_with_next_within_page:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-next-within-page" property of @fo_fo.
 *
 * Return value: The "keep-with-next-within-page" property value.
**/
FoProperty *
fo_character_get_keep_with_next_within_page (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->keep_with_next_within_page;
}

/**
 * fo_character_set_keep_with_next_within_page:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_next_within_page: The new "keep-with-next-within-page" property value.
 * 
 * Sets the "keep-with-next-within-page" property of @fo_fo to @new_keep_with_next_within_page.
 **/
void
fo_character_set_keep_with_next_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_page)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE (new_keep_with_next_within_page));

  if (new_keep_with_next_within_page != NULL)
    {
      g_object_ref (new_keep_with_next_within_page);
    }
  if (fo_character->keep_with_next_within_page != NULL)
    {
      g_object_unref (fo_character->keep_with_next_within_page);
    }
  fo_character->keep_with_next_within_page = new_keep_with_next_within_page;
  /*g_object_notify (G_OBJECT (fo_character), "keep-with-next-within-page");*/
}

/**
 * fo_character_get_keep_with_previous:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous" property of @fo_fo.
 *
 * Return value: The "keep-with-previous" property value.
**/
FoProperty *
fo_character_get_keep_with_previous (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->keep_with_previous;
}

/**
 * fo_character_set_keep_with_previous:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous: The new "keep-with-previous" property value.
 * 
 * Sets the "keep-with-previous" property of @fo_fo to @new_keep_with_previous.
 **/
void
fo_character_set_keep_with_previous (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS (new_keep_with_previous));

  if (new_keep_with_previous != NULL)
    {
      g_object_ref (new_keep_with_previous);
    }
  if (fo_character->keep_with_previous != NULL)
    {
      g_object_unref (fo_character->keep_with_previous);
    }
  fo_character->keep_with_previous = new_keep_with_previous;
  /*g_object_notify (G_OBJECT (fo_character), "keep-with-previous");*/
}

/**
 * fo_character_get_keep_with_previous_within_column:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-column" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-column" property value.
**/
FoProperty *
fo_character_get_keep_with_previous_within_column (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->keep_with_previous_within_column;
}

/**
 * fo_character_set_keep_with_previous_within_column:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_column: The new "keep-with-previous-within-column" property value.
 * 
 * Sets the "keep-with-previous-within-column" property of @fo_fo to @new_keep_with_previous_within_column.
 **/
void
fo_character_set_keep_with_previous_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_column)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_COLUMN (new_keep_with_previous_within_column));

  if (new_keep_with_previous_within_column != NULL)
    {
      g_object_ref (new_keep_with_previous_within_column);
    }
  if (fo_character->keep_with_previous_within_column != NULL)
    {
      g_object_unref (fo_character->keep_with_previous_within_column);
    }
  fo_character->keep_with_previous_within_column = new_keep_with_previous_within_column;
  /*g_object_notify (G_OBJECT (fo_character), "keep-with-previous-within-column");*/
}

/**
 * fo_character_get_keep_with_previous_within_line:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-line" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-line" property value.
**/
FoProperty *
fo_character_get_keep_with_previous_within_line (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->keep_with_previous_within_line;
}

/**
 * fo_character_set_keep_with_previous_within_line:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_line: The new "keep-with-previous-within-line" property value.
 * 
 * Sets the "keep-with-previous-within-line" property of @fo_fo to @new_keep_with_previous_within_line.
 **/
void
fo_character_set_keep_with_previous_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_line)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_LINE (new_keep_with_previous_within_line));

  if (new_keep_with_previous_within_line != NULL)
    {
      g_object_ref (new_keep_with_previous_within_line);
    }
  if (fo_character->keep_with_previous_within_line != NULL)
    {
      g_object_unref (fo_character->keep_with_previous_within_line);
    }
  fo_character->keep_with_previous_within_line = new_keep_with_previous_within_line;
  /*g_object_notify (G_OBJECT (fo_character), "keep-with-previous-within-line");*/
}

/**
 * fo_character_get_keep_with_previous_within_page:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "keep-with-previous-within-page" property of @fo_fo.
 *
 * Return value: The "keep-with-previous-within-page" property value.
**/
FoProperty *
fo_character_get_keep_with_previous_within_page (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->keep_with_previous_within_page;
}

/**
 * fo_character_set_keep_with_previous_within_page:
 * @fo_fo: The #FoFo object.
 * @new_keep_with_previous_within_page: The new "keep-with-previous-within-page" property value.
 * 
 * Sets the "keep-with-previous-within-page" property of @fo_fo to @new_keep_with_previous_within_page.
 **/
void
fo_character_set_keep_with_previous_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_page)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE (new_keep_with_previous_within_page));

  if (new_keep_with_previous_within_page != NULL)
    {
      g_object_ref (new_keep_with_previous_within_page);
    }
  if (fo_character->keep_with_previous_within_page != NULL)
    {
      g_object_unref (fo_character->keep_with_previous_within_page);
    }
  fo_character->keep_with_previous_within_page = new_keep_with_previous_within_page;
  /*g_object_notify (G_OBJECT (fo_character), "keep-with-previous-within-page");*/
}

/**
 * fo_character_get_line_height:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "line-height" property of @fo_fo.
 *
 * Return value: The "line-height" property value.
**/
FoProperty *
fo_character_get_line_height (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->line_height;
}

/**
 * fo_character_set_line_height:
 * @fo_fo: The #FoFo object.
 * @new_line_height: The new "line-height" property value.
 * 
 * Sets the "line-height" property of @fo_fo to @new_line_height.
 **/
void
fo_character_set_line_height (FoFo *fo_fo,
		         FoProperty *new_line_height)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_LINE_HEIGHT (new_line_height));

  if (new_line_height != NULL)
    {
      g_object_ref (new_line_height);
    }
  if (fo_character->line_height != NULL)
    {
      g_object_unref (fo_character->line_height);
    }
  fo_character->line_height = new_line_height;
  /*g_object_notify (G_OBJECT (fo_character), "line-height");*/
}

/**
 * fo_character_get_padding_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-after" property of @fo_fo.
 *
 * Return value: The "padding-after" property value.
**/
FoProperty *
fo_character_get_padding_after (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->padding_after;
}

/**
 * fo_character_set_padding_after:
 * @fo_fo: The #FoFo object.
 * @new_padding_after: The new "padding-after" property value.
 * 
 * Sets the "padding-after" property of @fo_fo to @new_padding_after.
 **/
void
fo_character_set_padding_after (FoFo *fo_fo,
		         FoProperty *new_padding_after)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref (new_padding_after);
    }
  if (fo_character->padding_after != NULL)
    {
      g_object_unref (fo_character->padding_after);
    }
  fo_character->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_character), "padding-after");*/
}

/**
 * fo_character_get_padding_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-before" property of @fo_fo.
 *
 * Return value: The "padding-before" property value.
**/
FoProperty *
fo_character_get_padding_before (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->padding_before;
}

/**
 * fo_character_set_padding_before:
 * @fo_fo: The #FoFo object.
 * @new_padding_before: The new "padding-before" property value.
 * 
 * Sets the "padding-before" property of @fo_fo to @new_padding_before.
 **/
void
fo_character_set_padding_before (FoFo *fo_fo,
		         FoProperty *new_padding_before)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref (new_padding_before);
    }
  if (fo_character->padding_before != NULL)
    {
      g_object_unref (fo_character->padding_before);
    }
  fo_character->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_character), "padding-before");*/
}

/**
 * fo_character_get_padding_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-bottom" property of @fo_fo.
 *
 * Return value: The "padding-bottom" property value.
**/
FoProperty *
fo_character_get_padding_bottom (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->padding_bottom;
}

/**
 * fo_character_set_padding_bottom:
 * @fo_fo: The #FoFo object.
 * @new_padding_bottom: The new "padding-bottom" property value.
 * 
 * Sets the "padding-bottom" property of @fo_fo to @new_padding_bottom.
 **/
void
fo_character_set_padding_bottom (FoFo *fo_fo,
		         FoProperty *new_padding_bottom)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref (new_padding_bottom);
    }
  if (fo_character->padding_bottom != NULL)
    {
      g_object_unref (fo_character->padding_bottom);
    }
  fo_character->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_character), "padding-bottom");*/
}

/**
 * fo_character_get_padding_end:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-end" property of @fo_fo.
 *
 * Return value: The "padding-end" property value.
**/
FoProperty *
fo_character_get_padding_end (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->padding_end;
}

/**
 * fo_character_set_padding_end:
 * @fo_fo: The #FoFo object.
 * @new_padding_end: The new "padding-end" property value.
 * 
 * Sets the "padding-end" property of @fo_fo to @new_padding_end.
 **/
void
fo_character_set_padding_end (FoFo *fo_fo,
		         FoProperty *new_padding_end)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref (new_padding_end);
    }
  if (fo_character->padding_end != NULL)
    {
      g_object_unref (fo_character->padding_end);
    }
  fo_character->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_character), "padding-end");*/
}

/**
 * fo_character_get_padding_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-left" property of @fo_fo.
 *
 * Return value: The "padding-left" property value.
**/
FoProperty *
fo_character_get_padding_left (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->padding_left;
}

/**
 * fo_character_set_padding_left:
 * @fo_fo: The #FoFo object.
 * @new_padding_left: The new "padding-left" property value.
 * 
 * Sets the "padding-left" property of @fo_fo to @new_padding_left.
 **/
void
fo_character_set_padding_left (FoFo *fo_fo,
		         FoProperty *new_padding_left)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref (new_padding_left);
    }
  if (fo_character->padding_left != NULL)
    {
      g_object_unref (fo_character->padding_left);
    }
  fo_character->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_character), "padding-left");*/
}

/**
 * fo_character_get_padding_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-right" property of @fo_fo.
 *
 * Return value: The "padding-right" property value.
**/
FoProperty *
fo_character_get_padding_right (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->padding_right;
}

/**
 * fo_character_set_padding_right:
 * @fo_fo: The #FoFo object.
 * @new_padding_right: The new "padding-right" property value.
 * 
 * Sets the "padding-right" property of @fo_fo to @new_padding_right.
 **/
void
fo_character_set_padding_right (FoFo *fo_fo,
		         FoProperty *new_padding_right)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref (new_padding_right);
    }
  if (fo_character->padding_right != NULL)
    {
      g_object_unref (fo_character->padding_right);
    }
  fo_character->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_character), "padding-right");*/
}

/**
 * fo_character_get_padding_start:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-start" property of @fo_fo.
 *
 * Return value: The "padding-start" property value.
**/
FoProperty *
fo_character_get_padding_start (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->padding_start;
}

/**
 * fo_character_set_padding_start:
 * @fo_fo: The #FoFo object.
 * @new_padding_start: The new "padding-start" property value.
 * 
 * Sets the "padding-start" property of @fo_fo to @new_padding_start.
 **/
void
fo_character_set_padding_start (FoFo *fo_fo,
		         FoProperty *new_padding_start)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref (new_padding_start);
    }
  if (fo_character->padding_start != NULL)
    {
      g_object_unref (fo_character->padding_start);
    }
  fo_character->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_character), "padding-start");*/
}

/**
 * fo_character_get_padding_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "padding-top" property of @fo_fo.
 *
 * Return value: The "padding-top" property value.
**/
FoProperty *
fo_character_get_padding_top (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->padding_top;
}

/**
 * fo_character_set_padding_top:
 * @fo_fo: The #FoFo object.
 * @new_padding_top: The new "padding-top" property value.
 * 
 * Sets the "padding-top" property of @fo_fo to @new_padding_top.
 **/
void
fo_character_set_padding_top (FoFo *fo_fo,
		         FoProperty *new_padding_top)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref (new_padding_top);
    }
  if (fo_character->padding_top != NULL)
    {
      g_object_unref (fo_character->padding_top);
    }
  fo_character->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_character), "padding-top");*/
}

/**
 * fo_character_get_score_spaces:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "score-spaces" property of @fo_fo.
 *
 * Return value: The "score-spaces" property value.
**/
FoProperty *
fo_character_get_score_spaces (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->score_spaces;
}

/**
 * fo_character_set_score_spaces:
 * @fo_fo: The #FoFo object.
 * @new_score_spaces: The new "score-spaces" property value.
 * 
 * Sets the "score-spaces" property of @fo_fo to @new_score_spaces.
 **/
void
fo_character_set_score_spaces (FoFo *fo_fo,
		         FoProperty *new_score_spaces)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_SCORE_SPACES (new_score_spaces));

  if (new_score_spaces != NULL)
    {
      g_object_ref (new_score_spaces);
    }
  if (fo_character->score_spaces != NULL)
    {
      g_object_unref (fo_character->score_spaces);
    }
  fo_character->score_spaces = new_score_spaces;
  /*g_object_notify (G_OBJECT (fo_character), "score-spaces");*/
}

/**
 * fo_character_get_space_end:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-end" property of @fo_fo.
 *
 * Return value: The "space-end" property value.
**/
FoProperty *
fo_character_get_space_end (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->space_end;
}

/**
 * fo_character_set_space_end:
 * @fo_fo: The #FoFo object.
 * @new_space_end: The new "space-end" property value.
 * 
 * Sets the "space-end" property of @fo_fo to @new_space_end.
 **/
void
fo_character_set_space_end (FoFo *fo_fo,
		         FoProperty *new_space_end)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_SPACE_END (new_space_end));

  if (new_space_end != NULL)
    {
      g_object_ref (new_space_end);
    }
  if (fo_character->space_end != NULL)
    {
      g_object_unref (fo_character->space_end);
    }
  fo_character->space_end = new_space_end;
  /*g_object_notify (G_OBJECT (fo_character), "space-end");*/
}

/**
 * fo_character_get_space_start:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-start" property of @fo_fo.
 *
 * Return value: The "space-start" property value.
**/
FoProperty *
fo_character_get_space_start (FoFo *fo_fo)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_val_if_fail (fo_character != NULL, NULL);
  g_return_val_if_fail (FO_IS_CHARACTER (fo_character), NULL);

  return fo_character->space_start;
}

/**
 * fo_character_set_space_start:
 * @fo_fo: The #FoFo object.
 * @new_space_start: The new "space-start" property value.
 * 
 * Sets the "space-start" property of @fo_fo to @new_space_start.
 **/
void
fo_character_set_space_start (FoFo *fo_fo,
		         FoProperty *new_space_start)
{
  FoCharacter *fo_character = (FoCharacter *) fo_fo;

  g_return_if_fail (fo_character != NULL);
  g_return_if_fail (FO_IS_CHARACTER (fo_character));
  g_return_if_fail (FO_IS_PROPERTY_SPACE_START (new_space_start));

  if (new_space_start != NULL)
    {
      g_object_ref (new_space_start);
    }
  if (fo_character->space_start != NULL)
    {
      g_object_unref (fo_character->space_start);
    }
  fo_character->space_start = new_space_start;
  /*g_object_notify (G_OBJECT (fo_character), "space-start");*/
}
