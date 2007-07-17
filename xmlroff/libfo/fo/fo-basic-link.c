/* Fo
 * fo-basic-link.c: 'basic-link' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-inline-fo.h"
#include "fo-basic-link.h"
#include "fo-basic-link-private.h"
#include "property/fo-property-text-property.h"
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
#include "property/fo-property-dominant-baseline.h"
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
  PROP_DOMINANT_BASELINE,
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
  PROP_SPACE_START
};

static void fo_basic_link_class_init  (FoBasicLinkClass *klass);
static void fo_basic_link_inline_fo_init (FoInlineFoIface *iface);
static void fo_basic_link_get_property (GObject      *object,
                                        guint         prop_id,
                                        GValue       *value,
                                        GParamSpec   *pspec);
static void fo_basic_link_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec);
static void fo_basic_link_finalize    (GObject           *object);
static gboolean fo_basic_link_validate_content (FoFo    *fo,
                                                GError **error);
static void fo_basic_link_validate (FoFo      *fo,
                                    FoContext *current_context,
                                    FoContext *parent_context,
                                    GError   **error);
static void fo_basic_link_update_from_context (FoFo      *fo,
                                               FoContext *context);
static void fo_basic_link_debug_dump_properties (FoFo *fo,
                                                 gint  depth);
static void fo_basic_link_get_text_attr_list (FoFo    *fo_inline_fo,
					      FoDoc   *fo_doc,
					      GString *text,
					      GList  **attr_glist,
					      guint    debug_level);

static gpointer parent_class;

/**
 * fo_basic_link_get_type:
 * 
 * Register the #FoBasicLink object type.
 * 
 * Return value: #GType value of the #FoBasicLink object type.
 **/
GType
fo_basic_link_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoBasicLinkClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_basic_link_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoBasicLink),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      static const GInterfaceInfo fo_inline_fo_info =
      {
	(GInterfaceInitFunc) fo_basic_link_inline_fo_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "basic-link",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &fo_inline_fo_info);
    }

  return object_type;
}

/**
 * fo_basic_link_class_init:
 * @klass: #FoBasicLinkClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoBasicLinkClass.
 **/
void
fo_basic_link_class_init (FoBasicLinkClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_basic_link_finalize;

  object_class->get_property = fo_basic_link_get_property;
  object_class->set_property = fo_basic_link_set_property;

  fofo_class->validate_content = fo_basic_link_validate_content;
  fofo_class->validate2 = fo_basic_link_validate;
  fofo_class->update_from_context = fo_basic_link_update_from_context;
  fofo_class->debug_dump_properties = fo_basic_link_debug_dump_properties;
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
     PROP_DOMINANT_BASELINE,
     g_param_spec_object ("dominant-baseline",
			  _("Dominant Baseline"),
			  _("Dominant Baseline property"),
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
}

/**
 * fo_basic_link_inline_fo_init:
 * @iface: #FoInlineFoIFace structure for this class.
 * 
 * Initialize #FoInlineFoIface interface for this class.
 **/
void
fo_basic_link_inline_fo_init (FoInlineFoIface *iface)
{
  iface->get_text_attr_list = fo_basic_link_get_text_attr_list;
}

/**
 * fo_basic_link_finalize:
 * @object: #FoBasicLink object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoBasicLink.
 **/
void
fo_basic_link_finalize (GObject *object)
{
  FoBasicLink *fo_basic_link;

  fo_basic_link = FO_BASIC_LINK (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_basic_link_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoBasicLink.
 **/
void
fo_basic_link_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ALIGNMENT_ADJUST:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_alignment_adjust (fo_fo)));
      break;
    case PROP_ALIGNMENT_BASELINE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_alignment_baseline (fo_fo)));
      break;
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_background_color (fo_fo)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_background_image (fo_fo)));
      break;
    case PROP_BASELINE_SHIFT:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_baseline_shift (fo_fo)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_after_color (fo_fo)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_after_style (fo_fo)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_after_width (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_before_color (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_before_style (fo_fo)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_before_width (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_bottom_color (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_bottom_style (fo_fo)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_bottom_width (fo_fo)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_end_color (fo_fo)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_end_style (fo_fo)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_end_width (fo_fo)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_left_color (fo_fo)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_left_style (fo_fo)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_left_width (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_right_color (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_right_style (fo_fo)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_right_width (fo_fo)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_start_color (fo_fo)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_start_style (fo_fo)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_start_width (fo_fo)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_top_color (fo_fo)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_top_style (fo_fo)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_border_top_width (fo_fo)));
      break;
    case PROP_DOMINANT_BASELINE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_dominant_baseline (fo_fo)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_id (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_together (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_together_within_column (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_together_within_line (fo_fo)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_together_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_with_next (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_with_next_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_with_next_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_with_next_within_page (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_with_previous (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_with_previous_within_column (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_with_previous_within_line (fo_fo)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_keep_with_previous_within_page (fo_fo)));
      break;
    case PROP_LINE_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_line_height (fo_fo)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_padding_after (fo_fo)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_padding_before (fo_fo)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_padding_bottom (fo_fo)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_padding_end (fo_fo)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_padding_left (fo_fo)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_padding_right (fo_fo)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_padding_start (fo_fo)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_padding_top (fo_fo)));
      break;
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_role (fo_fo)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_source_document (fo_fo)));
      break;
    case PROP_SPACE_END:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_space_end (fo_fo)));
      break;
    case PROP_SPACE_START:
      g_value_set_object (value, G_OBJECT (fo_basic_link_get_space_start (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_basic_link_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoBasicLink.
 **/
void
fo_basic_link_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ALIGNMENT_ADJUST:
      fo_basic_link_set_alignment_adjust (fo_fo, g_value_get_object (value));
      break;
    case PROP_ALIGNMENT_BASELINE:
      fo_basic_link_set_alignment_baseline (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_COLOR:
      fo_basic_link_set_background_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_basic_link_set_background_image (fo_fo, g_value_get_object (value));
      break;
    case PROP_BASELINE_SHIFT:
      fo_basic_link_set_baseline_shift (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_basic_link_set_border_after_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_basic_link_set_border_after_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_basic_link_set_border_after_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_basic_link_set_border_before_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_basic_link_set_border_before_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_basic_link_set_border_before_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_basic_link_set_border_bottom_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_basic_link_set_border_bottom_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_basic_link_set_border_bottom_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_basic_link_set_border_end_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_basic_link_set_border_end_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_basic_link_set_border_end_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_basic_link_set_border_left_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_basic_link_set_border_left_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_basic_link_set_border_left_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_basic_link_set_border_right_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_basic_link_set_border_right_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_basic_link_set_border_right_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_basic_link_set_border_start_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_basic_link_set_border_start_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_basic_link_set_border_start_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_basic_link_set_border_top_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_basic_link_set_border_top_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_basic_link_set_border_top_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_DOMINANT_BASELINE:
      fo_basic_link_set_dominant_baseline (fo_fo, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_basic_link_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER:
      fo_basic_link_set_keep_together (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      fo_basic_link_set_keep_together_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      fo_basic_link_set_keep_together_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      fo_basic_link_set_keep_together_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT:
      fo_basic_link_set_keep_with_next (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      fo_basic_link_set_keep_with_next_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      fo_basic_link_set_keep_with_next_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      fo_basic_link_set_keep_with_next_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      fo_basic_link_set_keep_with_previous (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      fo_basic_link_set_keep_with_previous_within_column (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      fo_basic_link_set_keep_with_previous_within_line (fo_fo, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      fo_basic_link_set_keep_with_previous_within_page (fo_fo, g_value_get_object (value));
      break;
    case PROP_LINE_HEIGHT:
      fo_basic_link_set_line_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_basic_link_set_padding_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_basic_link_set_padding_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_basic_link_set_padding_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_basic_link_set_padding_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_basic_link_set_padding_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_basic_link_set_padding_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_basic_link_set_padding_start (fo_fo, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_basic_link_set_padding_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_ROLE:
      fo_basic_link_set_role (fo_fo, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_basic_link_set_source_document (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_END:
      fo_basic_link_set_space_end (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_START:
      fo_basic_link_set_space_start (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_basic_link_new:
 * 
 * Creates a new #FoBasicLink initialized to default value.
 * 
 * Return value: the new #FoBasicLink.
 **/
FoFo*
fo_basic_link_new (void)
{
  return FO_FO (g_object_new (fo_basic_link_get_type (), NULL));
}

/**
 * fo_basic_link_validate_content:
 * @fo:    #FoBasicLink object to validate.
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
fo_basic_link_validate_content (FoFo    *fo,
                                GError **error)
{
  /*GError *tmp_error;*/

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo), TRUE);
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
 * fo_basic_link_validate:
 * @fo:              #FoBasicLink object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_basic_link_validate (FoFo      *fo,
                        FoContext *current_context,
                        FoContext *parent_context,
                        GError   **error)
{
  FoBasicLink *fo_basic_link;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_basic_link = FO_BASIC_LINK (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_basic_link_set_line_height (fo,
				 fo_property_line_height_resolve (fo_basic_link_get_line_height (fo),
								  fo_context_get_font_size (fo->context)));
}

/**
 * fo_basic_link_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_basic_link_update_from_context (FoFo *fo,
                                   FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_basic_link_set_alignment_adjust (fo,
			  fo_context_get_alignment_adjust (context));
  fo_basic_link_set_alignment_baseline (fo,
			  fo_context_get_alignment_baseline (context));
  fo_basic_link_set_background_color (fo,
			  fo_context_get_background_color (context));
  fo_basic_link_set_background_image (fo,
			  fo_context_get_background_image (context));
  fo_basic_link_set_baseline_shift (fo,
			  fo_context_get_baseline_shift (context));
  fo_basic_link_set_border_after_color (fo,
			  fo_context_get_border_after_color (context));
  fo_basic_link_set_border_after_style (fo,
			  fo_context_get_border_after_style (context));
  fo_basic_link_set_border_after_width (fo,
			  fo_context_get_border_after_width (context));
  fo_basic_link_set_border_before_color (fo,
			  fo_context_get_border_before_color (context));
  fo_basic_link_set_border_before_style (fo,
			  fo_context_get_border_before_style (context));
  fo_basic_link_set_border_before_width (fo,
			  fo_context_get_border_before_width (context));
  fo_basic_link_set_border_bottom_color (fo,
			  fo_context_get_border_bottom_color (context));
  fo_basic_link_set_border_bottom_style (fo,
			  fo_context_get_border_bottom_style (context));
  fo_basic_link_set_border_bottom_width (fo,
			  fo_context_get_border_bottom_width (context));
  fo_basic_link_set_border_end_color (fo,
			  fo_context_get_border_end_color (context));
  fo_basic_link_set_border_end_style (fo,
			  fo_context_get_border_end_style (context));
  fo_basic_link_set_border_end_width (fo,
			  fo_context_get_border_end_width (context));
  fo_basic_link_set_border_left_color (fo,
			  fo_context_get_border_left_color (context));
  fo_basic_link_set_border_left_style (fo,
			  fo_context_get_border_left_style (context));
  fo_basic_link_set_border_left_width (fo,
			  fo_context_get_border_left_width (context));
  fo_basic_link_set_border_right_color (fo,
			  fo_context_get_border_right_color (context));
  fo_basic_link_set_border_right_style (fo,
			  fo_context_get_border_right_style (context));
  fo_basic_link_set_border_right_width (fo,
			  fo_context_get_border_right_width (context));
  fo_basic_link_set_border_start_color (fo,
			  fo_context_get_border_start_color (context));
  fo_basic_link_set_border_start_style (fo,
			  fo_context_get_border_start_style (context));
  fo_basic_link_set_border_start_width (fo,
			  fo_context_get_border_start_width (context));
  fo_basic_link_set_border_top_color (fo,
			  fo_context_get_border_top_color (context));
  fo_basic_link_set_border_top_style (fo,
			  fo_context_get_border_top_style (context));
  fo_basic_link_set_border_top_width (fo,
			  fo_context_get_border_top_width (context));
  fo_basic_link_set_dominant_baseline (fo,
			  fo_context_get_dominant_baseline (context));
  fo_basic_link_set_id (fo,
			  fo_context_get_id (context));
  fo_basic_link_set_keep_together (fo,
			  fo_context_get_keep_together (context));
  fo_basic_link_set_keep_together_within_column (fo,
			  fo_context_get_keep_together_within_column (context));
  fo_basic_link_set_keep_together_within_line (fo,
			  fo_context_get_keep_together_within_line (context));
  fo_basic_link_set_keep_together_within_page (fo,
			  fo_context_get_keep_together_within_page (context));
  fo_basic_link_set_keep_with_next (fo,
			  fo_context_get_keep_with_next (context));
  fo_basic_link_set_keep_with_next_within_column (fo,
			  fo_context_get_keep_with_next_within_column (context));
  fo_basic_link_set_keep_with_next_within_line (fo,
			  fo_context_get_keep_with_next_within_line (context));
  fo_basic_link_set_keep_with_next_within_page (fo,
			  fo_context_get_keep_with_next_within_page (context));
  fo_basic_link_set_keep_with_previous (fo,
			  fo_context_get_keep_with_previous (context));
  fo_basic_link_set_keep_with_previous_within_column (fo,
			  fo_context_get_keep_with_previous_within_column (context));
  fo_basic_link_set_keep_with_previous_within_line (fo,
			  fo_context_get_keep_with_previous_within_line (context));
  fo_basic_link_set_keep_with_previous_within_page (fo,
			  fo_context_get_keep_with_previous_within_page (context));
  fo_basic_link_set_line_height (fo,
			  fo_context_get_line_height (context));
  fo_basic_link_set_padding_after (fo,
			  fo_context_get_padding_after (context));
  fo_basic_link_set_padding_before (fo,
			  fo_context_get_padding_before (context));
  fo_basic_link_set_padding_bottom (fo,
			  fo_context_get_padding_bottom (context));
  fo_basic_link_set_padding_end (fo,
			  fo_context_get_padding_end (context));
  fo_basic_link_set_padding_left (fo,
			  fo_context_get_padding_left (context));
  fo_basic_link_set_padding_right (fo,
			  fo_context_get_padding_right (context));
  fo_basic_link_set_padding_start (fo,
			  fo_context_get_padding_start (context));
  fo_basic_link_set_padding_top (fo,
			  fo_context_get_padding_top (context));
  fo_basic_link_set_role (fo,
			  fo_context_get_role (context));
  fo_basic_link_set_source_document (fo,
			  fo_context_get_source_document (context));
  fo_basic_link_set_space_end (fo,
			  fo_context_get_space_end (context));
  fo_basic_link_set_space_start (fo,
			  fo_context_get_space_start (context));
}

/**
 * fo_basic_link_debug_dump_properties:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_basic_link_debug_dump_properties (FoFo *fo, gint depth)
{
  FoBasicLink *fo_basic_link;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo));

  fo_basic_link = FO_BASIC_LINK (fo);

  fo_object_debug_dump (fo_basic_link->alignment_adjust, depth);
  fo_object_debug_dump (fo_basic_link->alignment_baseline, depth);
  fo_object_debug_dump (fo_basic_link->background_color, depth);
  fo_object_debug_dump (fo_basic_link->background_image, depth);
  fo_object_debug_dump (fo_basic_link->baseline_shift, depth);
  fo_object_debug_dump (fo_basic_link->border_after_color, depth);
  fo_object_debug_dump (fo_basic_link->border_after_style, depth);
  fo_object_debug_dump (fo_basic_link->border_after_width, depth);
  fo_object_debug_dump (fo_basic_link->border_before_color, depth);
  fo_object_debug_dump (fo_basic_link->border_before_style, depth);
  fo_object_debug_dump (fo_basic_link->border_before_width, depth);
  fo_object_debug_dump (fo_basic_link->border_bottom_color, depth);
  fo_object_debug_dump (fo_basic_link->border_bottom_style, depth);
  fo_object_debug_dump (fo_basic_link->border_bottom_width, depth);
  fo_object_debug_dump (fo_basic_link->border_end_color, depth);
  fo_object_debug_dump (fo_basic_link->border_end_style, depth);
  fo_object_debug_dump (fo_basic_link->border_end_width, depth);
  fo_object_debug_dump (fo_basic_link->border_left_color, depth);
  fo_object_debug_dump (fo_basic_link->border_left_style, depth);
  fo_object_debug_dump (fo_basic_link->border_left_width, depth);
  fo_object_debug_dump (fo_basic_link->border_right_color, depth);
  fo_object_debug_dump (fo_basic_link->border_right_style, depth);
  fo_object_debug_dump (fo_basic_link->border_right_width, depth);
  fo_object_debug_dump (fo_basic_link->border_start_color, depth);
  fo_object_debug_dump (fo_basic_link->border_start_style, depth);
  fo_object_debug_dump (fo_basic_link->border_start_width, depth);
  fo_object_debug_dump (fo_basic_link->border_top_color, depth);
  fo_object_debug_dump (fo_basic_link->border_top_style, depth);
  fo_object_debug_dump (fo_basic_link->border_top_width, depth);
  fo_object_debug_dump (fo_basic_link->dominant_baseline, depth);
  fo_object_debug_dump (fo_basic_link->id, depth);
  fo_object_debug_dump (fo_basic_link->keep_together, depth);
  fo_object_debug_dump (fo_basic_link->keep_together_within_column, depth);
  fo_object_debug_dump (fo_basic_link->keep_together_within_line, depth);
  fo_object_debug_dump (fo_basic_link->keep_together_within_page, depth);
  fo_object_debug_dump (fo_basic_link->keep_with_next, depth);
  fo_object_debug_dump (fo_basic_link->keep_with_next_within_column, depth);
  fo_object_debug_dump (fo_basic_link->keep_with_next_within_line, depth);
  fo_object_debug_dump (fo_basic_link->keep_with_next_within_page, depth);
  fo_object_debug_dump (fo_basic_link->keep_with_previous, depth);
  fo_object_debug_dump (fo_basic_link->keep_with_previous_within_column, depth);
  fo_object_debug_dump (fo_basic_link->keep_with_previous_within_line, depth);
  fo_object_debug_dump (fo_basic_link->keep_with_previous_within_page, depth);
  fo_object_debug_dump (fo_basic_link->line_height, depth);
  fo_object_debug_dump (fo_basic_link->padding_after, depth);
  fo_object_debug_dump (fo_basic_link->padding_before, depth);
  fo_object_debug_dump (fo_basic_link->padding_bottom, depth);
  fo_object_debug_dump (fo_basic_link->padding_end, depth);
  fo_object_debug_dump (fo_basic_link->padding_left, depth);
  fo_object_debug_dump (fo_basic_link->padding_right, depth);
  fo_object_debug_dump (fo_basic_link->padding_start, depth);
  fo_object_debug_dump (fo_basic_link->padding_top, depth);
  fo_object_debug_dump (fo_basic_link->role, depth);
  fo_object_debug_dump (fo_basic_link->source_document, depth);
  fo_object_debug_dump (fo_basic_link->space_end, depth);
  fo_object_debug_dump (fo_basic_link->space_start, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_basic_link_get_text_attr_list:
 * @fo_inline_fo: The #FoInlineFo object.
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO.
 * @attr_glist:   The list of #PangoAttribute for the inline FO.
 * @debug_level:  Debug level.
 * 
 * Gets the text of the inline FO and its associated list of #PangoAttribute.
 **/
void
fo_basic_link_get_text_attr_list (FoFo    *fo_inline_fo,
				  FoDoc   *fo_doc,
				  GString *text,
				  GList  **attr_glist,
				  guint    debug_level)
{
  FoNode *fo_child_node;
  FoBasicLink *fo_basic_link;
  GList *my_attr_glist = NULL;
  gint start_index, end_index;

  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_inline_fo));

  fo_basic_link = FO_BASIC_LINK (fo_inline_fo);

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
      /* FIXME: what is supposed to happen here? */

      PangoAttribute *pango_attr G_GNUC_UNUSED;

    }

  *attr_glist = g_list_concat (my_attr_glist,
			       *attr_glist);
}

/**
 * fo_basic_link_get_alignment_adjust:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "alignment-adjust" property of @fo_fo
 *
 * Return value: The "alignment-adjust" property value
**/
FoProperty*
fo_basic_link_get_alignment_adjust (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->alignment_adjust;
}

/**
 * fo_basic_link_set_alignment_adjust:
 * @fo_fo: The #FoFo object
 * @new_alignment_adjust: The new "alignment-adjust" property value
 * 
 * Sets the "alignment-adjust" property of @fo_fo to @new_alignment_adjust
 **/
void
fo_basic_link_set_alignment_adjust (FoFo *fo_fo,
		         FoProperty *new_alignment_adjust)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_ALIGNMENT_ADJUST (new_alignment_adjust));

  if (new_alignment_adjust != NULL)
    {
      g_object_ref (new_alignment_adjust);
    }
  if (fo_basic_link->alignment_adjust != NULL)
    {
      g_object_unref (fo_basic_link->alignment_adjust);
    }
  fo_basic_link->alignment_adjust = new_alignment_adjust;
  /*g_object_notify (G_OBJECT (fo_basic_link), "alignment-adjust");*/
}

/**
 * fo_basic_link_get_alignment_baseline:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "alignment-baseline" property of @fo_fo
 *
 * Return value: The "alignment-baseline" property value
**/
FoProperty*
fo_basic_link_get_alignment_baseline (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->alignment_baseline;
}

/**
 * fo_basic_link_set_alignment_baseline:
 * @fo_fo: The #FoFo object
 * @new_alignment_baseline: The new "alignment-baseline" property value
 * 
 * Sets the "alignment-baseline" property of @fo_fo to @new_alignment_baseline
 **/
void
fo_basic_link_set_alignment_baseline (FoFo *fo_fo,
		         FoProperty *new_alignment_baseline)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_ALIGNMENT_BASELINE (new_alignment_baseline));

  if (new_alignment_baseline != NULL)
    {
      g_object_ref (new_alignment_baseline);
    }
  if (fo_basic_link->alignment_baseline != NULL)
    {
      g_object_unref (fo_basic_link->alignment_baseline);
    }
  fo_basic_link->alignment_baseline = new_alignment_baseline;
  /*g_object_notify (G_OBJECT (fo_basic_link), "alignment-baseline");*/
}

/**
 * fo_basic_link_get_background_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "background-color" property of @fo_fo
 *
 * Return value: The "background-color" property value
**/
FoProperty *
fo_basic_link_get_background_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->background_color;
}

/**
 * fo_basic_link_set_background_color:
 * @fo_fo: The #FoFo object
 * @new_background_color: The new "background-color" property value
 * 
 * Sets the "background-color" property of @fo_fo to @new_background_color
 **/
void
fo_basic_link_set_background_color (FoFo *fo_fo,
		         FoProperty *new_background_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref (new_background_color);
    }
  if (fo_basic_link->background_color != NULL)
    {
      g_object_unref (fo_basic_link->background_color);
    }
  fo_basic_link->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "background-color");*/
}

/**
 * fo_basic_link_get_background_image:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "background-image" property of @fo_fo
 *
 * Return value: The "background-image" property value
**/
FoProperty*
fo_basic_link_get_background_image (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->background_image;
}

/**
 * fo_basic_link_set_background_image:
 * @fo_fo: The #FoFo object
 * @new_background_image: The new "background-image" property value
 * 
 * Sets the "background-image" property of @fo_fo to @new_background_image
 **/
void
fo_basic_link_set_background_image (FoFo *fo_fo,
		         FoProperty *new_background_image)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref (new_background_image);
    }
  if (fo_basic_link->background_image != NULL)
    {
      g_object_unref (fo_basic_link->background_image);
    }
  fo_basic_link->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_basic_link), "background-image");*/
}

/**
 * fo_basic_link_get_baseline_shift:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "baseline-shift" property of @fo_fo
 *
 * Return value: The "baseline-shift" property value
**/
FoProperty*
fo_basic_link_get_baseline_shift (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->baseline_shift;
}

/**
 * fo_basic_link_set_baseline_shift:
 * @fo_fo: The #FoFo object
 * @new_baseline_shift: The new "baseline-shift" property value
 * 
 * Sets the "baseline-shift" property of @fo_fo to @new_baseline_shift
 **/
void
fo_basic_link_set_baseline_shift (FoFo *fo_fo,
		         FoProperty *new_baseline_shift)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BASELINE_SHIFT (new_baseline_shift));

  if (new_baseline_shift != NULL)
    {
      g_object_ref (new_baseline_shift);
    }
  if (fo_basic_link->baseline_shift != NULL)
    {
      g_object_unref (fo_basic_link->baseline_shift);
    }
  fo_basic_link->baseline_shift = new_baseline_shift;
  /*g_object_notify (G_OBJECT (fo_basic_link), "baseline-shift");*/
}

/**
 * fo_basic_link_get_border_after_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-after-color" property of @fo_fo
 *
 * Return value: The "border-after-color" property value
**/
FoProperty*
fo_basic_link_get_border_after_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_after_color;
}

/**
 * fo_basic_link_set_border_after_color:
 * @fo_fo: The #FoFo object
 * @new_border_after_color: The new "border-after-color" property value
 * 
 * Sets the "border-after-color" property of @fo_fo to @new_border_after_color
 **/
void
fo_basic_link_set_border_after_color (FoFo *fo_fo,
		         FoProperty *new_border_after_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref (new_border_after_color);
    }
  if (fo_basic_link->border_after_color != NULL)
    {
      g_object_unref (fo_basic_link->border_after_color);
    }
  fo_basic_link->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-after-color");*/
}

/**
 * fo_basic_link_get_border_after_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-after-style" property of @fo_fo
 *
 * Return value: The "border-after-style" property value
**/
FoProperty*
fo_basic_link_get_border_after_style (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_after_style;
}

/**
 * fo_basic_link_set_border_after_style:
 * @fo_fo: The #FoFo object
 * @new_border_after_style: The new "border-after-style" property value
 * 
 * Sets the "border-after-style" property of @fo_fo to @new_border_after_style
 **/
void
fo_basic_link_set_border_after_style (FoFo *fo_fo,
		         FoProperty *new_border_after_style)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref (new_border_after_style);
    }
  if (fo_basic_link->border_after_style != NULL)
    {
      g_object_unref (fo_basic_link->border_after_style);
    }
  fo_basic_link->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-after-style");*/
}

/**
 * fo_basic_link_get_border_after_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-after-width" property of @fo_fo
 *
 * Return value: The "border-after-width" property value
**/
FoProperty*
fo_basic_link_get_border_after_width (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_after_width;
}

/**
 * fo_basic_link_set_border_after_width:
 * @fo_fo: The #FoFo object
 * @new_border_after_width: The new "border-after-width" property value
 * 
 * Sets the "border-after-width" property of @fo_fo to @new_border_after_width
 **/
void
fo_basic_link_set_border_after_width (FoFo *fo_fo,
		         FoProperty *new_border_after_width)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref (new_border_after_width);
    }
  if (fo_basic_link->border_after_width != NULL)
    {
      g_object_unref (fo_basic_link->border_after_width);
    }
  fo_basic_link->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-after-width");*/
}

/**
 * fo_basic_link_get_border_before_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-before-color" property of @fo_fo
 *
 * Return value: The "border-before-color" property value
**/
FoProperty*
fo_basic_link_get_border_before_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_before_color;
}

/**
 * fo_basic_link_set_border_before_color:
 * @fo_fo: The #FoFo object
 * @new_border_before_color: The new "border-before-color" property value
 * 
 * Sets the "border-before-color" property of @fo_fo to @new_border_before_color
 **/
void
fo_basic_link_set_border_before_color (FoFo *fo_fo,
		         FoProperty *new_border_before_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref (new_border_before_color);
    }
  if (fo_basic_link->border_before_color != NULL)
    {
      g_object_unref (fo_basic_link->border_before_color);
    }
  fo_basic_link->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-before-color");*/
}

/**
 * fo_basic_link_get_border_before_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-before-style" property of @fo_fo
 *
 * Return value: The "border-before-style" property value
**/
FoProperty*
fo_basic_link_get_border_before_style (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_before_style;
}

/**
 * fo_basic_link_set_border_before_style:
 * @fo_fo: The #FoFo object
 * @new_border_before_style: The new "border-before-style" property value
 * 
 * Sets the "border-before-style" property of @fo_fo to @new_border_before_style
 **/
void
fo_basic_link_set_border_before_style (FoFo *fo_fo,
		         FoProperty *new_border_before_style)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref (new_border_before_style);
    }
  if (fo_basic_link->border_before_style != NULL)
    {
      g_object_unref (fo_basic_link->border_before_style);
    }
  fo_basic_link->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-before-style");*/
}

/**
 * fo_basic_link_get_border_before_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-before-width" property of @fo_fo
 *
 * Return value: The "border-before-width" property value
**/
FoProperty*
fo_basic_link_get_border_before_width (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_before_width;
}

/**
 * fo_basic_link_set_border_before_width:
 * @fo_fo: The #FoFo object
 * @new_border_before_width: The new "border-before-width" property value
 * 
 * Sets the "border-before-width" property of @fo_fo to @new_border_before_width
 **/
void
fo_basic_link_set_border_before_width (FoFo *fo_fo,
		         FoProperty *new_border_before_width)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref (new_border_before_width);
    }
  if (fo_basic_link->border_before_width != NULL)
    {
      g_object_unref (fo_basic_link->border_before_width);
    }
  fo_basic_link->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-before-width");*/
}

/**
 * fo_basic_link_get_border_bottom_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-bottom-color" property of @fo_fo
 *
 * Return value: The "border-bottom-color" property value
**/
FoProperty*
fo_basic_link_get_border_bottom_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_bottom_color;
}

/**
 * fo_basic_link_set_border_bottom_color:
 * @fo_fo: The #FoFo object
 * @new_border_bottom_color: The new "border-bottom-color" property value
 * 
 * Sets the "border-bottom-color" property of @fo_fo to @new_border_bottom_color
 **/
void
fo_basic_link_set_border_bottom_color (FoFo *fo_fo,
		         FoProperty *new_border_bottom_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref (new_border_bottom_color);
    }
  if (fo_basic_link->border_bottom_color != NULL)
    {
      g_object_unref (fo_basic_link->border_bottom_color);
    }
  fo_basic_link->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-bottom-color");*/
}

/**
 * fo_basic_link_get_border_bottom_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-bottom-style" property of @fo_fo
 *
 * Return value: The "border-bottom-style" property value
**/
FoProperty*
fo_basic_link_get_border_bottom_style (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_bottom_style;
}

/**
 * fo_basic_link_set_border_bottom_style:
 * @fo_fo: The #FoFo object
 * @new_border_bottom_style: The new "border-bottom-style" property value
 * 
 * Sets the "border-bottom-style" property of @fo_fo to @new_border_bottom_style
 **/
void
fo_basic_link_set_border_bottom_style (FoFo *fo_fo,
		         FoProperty *new_border_bottom_style)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref (new_border_bottom_style);
    }
  if (fo_basic_link->border_bottom_style != NULL)
    {
      g_object_unref (fo_basic_link->border_bottom_style);
    }
  fo_basic_link->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-bottom-style");*/
}

/**
 * fo_basic_link_get_border_bottom_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-bottom-width" property of @fo_fo
 *
 * Return value: The "border-bottom-width" property value
**/
FoProperty*
fo_basic_link_get_border_bottom_width (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_bottom_width;
}

/**
 * fo_basic_link_set_border_bottom_width:
 * @fo_fo: The #FoFo object
 * @new_border_bottom_width: The new "border-bottom-width" property value
 * 
 * Sets the "border-bottom-width" property of @fo_fo to @new_border_bottom_width
 **/
void
fo_basic_link_set_border_bottom_width (FoFo *fo_fo,
		         FoProperty *new_border_bottom_width)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref (new_border_bottom_width);
    }
  if (fo_basic_link->border_bottom_width != NULL)
    {
      g_object_unref (fo_basic_link->border_bottom_width);
    }
  fo_basic_link->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-bottom-width");*/
}

/**
 * fo_basic_link_get_border_end_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-end-color" property of @fo_fo
 *
 * Return value: The "border-end-color" property value
**/
FoProperty*
fo_basic_link_get_border_end_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_end_color;
}

/**
 * fo_basic_link_set_border_end_color:
 * @fo_fo: The #FoFo object
 * @new_border_end_color: The new "border-end-color" property value
 * 
 * Sets the "border-end-color" property of @fo_fo to @new_border_end_color
 **/
void
fo_basic_link_set_border_end_color (FoFo *fo_fo,
		         FoProperty *new_border_end_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref (new_border_end_color);
    }
  if (fo_basic_link->border_end_color != NULL)
    {
      g_object_unref (fo_basic_link->border_end_color);
    }
  fo_basic_link->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-end-color");*/
}

/**
 * fo_basic_link_get_border_end_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-end-style" property of @fo_fo
 *
 * Return value: The "border-end-style" property value
**/
FoProperty*
fo_basic_link_get_border_end_style (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_end_style;
}

/**
 * fo_basic_link_set_border_end_style:
 * @fo_fo: The #FoFo object
 * @new_border_end_style: The new "border-end-style" property value
 * 
 * Sets the "border-end-style" property of @fo_fo to @new_border_end_style
 **/
void
fo_basic_link_set_border_end_style (FoFo *fo_fo,
		         FoProperty *new_border_end_style)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref (new_border_end_style);
    }
  if (fo_basic_link->border_end_style != NULL)
    {
      g_object_unref (fo_basic_link->border_end_style);
    }
  fo_basic_link->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-end-style");*/
}

/**
 * fo_basic_link_get_border_end_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-end-width" property of @fo_fo
 *
 * Return value: The "border-end-width" property value
**/
FoProperty*
fo_basic_link_get_border_end_width (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_end_width;
}

/**
 * fo_basic_link_set_border_end_width:
 * @fo_fo: The #FoFo object
 * @new_border_end_width: The new "border-end-width" property value
 * 
 * Sets the "border-end-width" property of @fo_fo to @new_border_end_width
 **/
void
fo_basic_link_set_border_end_width (FoFo *fo_fo,
		         FoProperty *new_border_end_width)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref (new_border_end_width);
    }
  if (fo_basic_link->border_end_width != NULL)
    {
      g_object_unref (fo_basic_link->border_end_width);
    }
  fo_basic_link->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-end-width");*/
}

/**
 * fo_basic_link_get_border_left_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-left-color" property of @fo_fo
 *
 * Return value: The "border-left-color" property value
**/
FoProperty*
fo_basic_link_get_border_left_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_left_color;
}

/**
 * fo_basic_link_set_border_left_color:
 * @fo_fo: The #FoFo object
 * @new_border_left_color: The new "border-left-color" property value
 * 
 * Sets the "border-left-color" property of @fo_fo to @new_border_left_color
 **/
void
fo_basic_link_set_border_left_color (FoFo *fo_fo,
		         FoProperty *new_border_left_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref (new_border_left_color);
    }
  if (fo_basic_link->border_left_color != NULL)
    {
      g_object_unref (fo_basic_link->border_left_color);
    }
  fo_basic_link->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-left-color");*/
}

/**
 * fo_basic_link_get_border_left_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-left-style" property of @fo_fo
 *
 * Return value: The "border-left-style" property value
**/
FoProperty*
fo_basic_link_get_border_left_style (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_left_style;
}

/**
 * fo_basic_link_set_border_left_style:
 * @fo_fo: The #FoFo object
 * @new_border_left_style: The new "border-left-style" property value
 * 
 * Sets the "border-left-style" property of @fo_fo to @new_border_left_style
 **/
void
fo_basic_link_set_border_left_style (FoFo *fo_fo,
		         FoProperty *new_border_left_style)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref (new_border_left_style);
    }
  if (fo_basic_link->border_left_style != NULL)
    {
      g_object_unref (fo_basic_link->border_left_style);
    }
  fo_basic_link->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-left-style");*/
}

/**
 * fo_basic_link_get_border_left_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-left-width" property of @fo_fo
 *
 * Return value: The "border-left-width" property value
**/
FoProperty*
fo_basic_link_get_border_left_width (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_left_width;
}

/**
 * fo_basic_link_set_border_left_width:
 * @fo_fo: The #FoFo object
 * @new_border_left_width: The new "border-left-width" property value
 * 
 * Sets the "border-left-width" property of @fo_fo to @new_border_left_width
 **/
void
fo_basic_link_set_border_left_width (FoFo *fo_fo,
		         FoProperty *new_border_left_width)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref (new_border_left_width);
    }
  if (fo_basic_link->border_left_width != NULL)
    {
      g_object_unref (fo_basic_link->border_left_width);
    }
  fo_basic_link->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-left-width");*/
}

/**
 * fo_basic_link_get_border_right_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-right-color" property of @fo_fo
 *
 * Return value: The "border-right-color" property value
**/
FoProperty*
fo_basic_link_get_border_right_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_right_color;
}

/**
 * fo_basic_link_set_border_right_color:
 * @fo_fo: The #FoFo object
 * @new_border_right_color: The new "border-right-color" property value
 * 
 * Sets the "border-right-color" property of @fo_fo to @new_border_right_color
 **/
void
fo_basic_link_set_border_right_color (FoFo *fo_fo,
		         FoProperty *new_border_right_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref (new_border_right_color);
    }
  if (fo_basic_link->border_right_color != NULL)
    {
      g_object_unref (fo_basic_link->border_right_color);
    }
  fo_basic_link->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-right-color");*/
}

/**
 * fo_basic_link_get_border_right_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-right-style" property of @fo_fo
 *
 * Return value: The "border-right-style" property value
**/
FoProperty*
fo_basic_link_get_border_right_style (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_right_style;
}

/**
 * fo_basic_link_set_border_right_style:
 * @fo_fo: The #FoFo object
 * @new_border_right_style: The new "border-right-style" property value
 * 
 * Sets the "border-right-style" property of @fo_fo to @new_border_right_style
 **/
void
fo_basic_link_set_border_right_style (FoFo *fo_fo,
		         FoProperty *new_border_right_style)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref (new_border_right_style);
    }
  if (fo_basic_link->border_right_style != NULL)
    {
      g_object_unref (fo_basic_link->border_right_style);
    }
  fo_basic_link->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-right-style");*/
}

/**
 * fo_basic_link_get_border_right_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-right-width" property of @fo_fo
 *
 * Return value: The "border-right-width" property value
**/
FoProperty*
fo_basic_link_get_border_right_width (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_right_width;
}

/**
 * fo_basic_link_set_border_right_width:
 * @fo_fo: The #FoFo object
 * @new_border_right_width: The new "border-right-width" property value
 * 
 * Sets the "border-right-width" property of @fo_fo to @new_border_right_width
 **/
void
fo_basic_link_set_border_right_width (FoFo *fo_fo,
		         FoProperty *new_border_right_width)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref (new_border_right_width);
    }
  if (fo_basic_link->border_right_width != NULL)
    {
      g_object_unref (fo_basic_link->border_right_width);
    }
  fo_basic_link->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-right-width");*/
}

/**
 * fo_basic_link_get_border_start_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-start-color" property of @fo_fo
 *
 * Return value: The "border-start-color" property value
**/
FoProperty*
fo_basic_link_get_border_start_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_start_color;
}

/**
 * fo_basic_link_set_border_start_color:
 * @fo_fo: The #FoFo object
 * @new_border_start_color: The new "border-start-color" property value
 * 
 * Sets the "border-start-color" property of @fo_fo to @new_border_start_color
 **/
void
fo_basic_link_set_border_start_color (FoFo *fo_fo,
		         FoProperty *new_border_start_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref (new_border_start_color);
    }
  if (fo_basic_link->border_start_color != NULL)
    {
      g_object_unref (fo_basic_link->border_start_color);
    }
  fo_basic_link->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-start-color");*/
}

/**
 * fo_basic_link_get_border_start_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-start-style" property of @fo_fo
 *
 * Return value: The "border-start-style" property value
**/
FoProperty*
fo_basic_link_get_border_start_style (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_start_style;
}

/**
 * fo_basic_link_set_border_start_style:
 * @fo_fo: The #FoFo object
 * @new_border_start_style: The new "border-start-style" property value
 * 
 * Sets the "border-start-style" property of @fo_fo to @new_border_start_style
 **/
void
fo_basic_link_set_border_start_style (FoFo *fo_fo,
		         FoProperty *new_border_start_style)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref (new_border_start_style);
    }
  if (fo_basic_link->border_start_style != NULL)
    {
      g_object_unref (fo_basic_link->border_start_style);
    }
  fo_basic_link->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-start-style");*/
}

/**
 * fo_basic_link_get_border_start_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-start-width" property of @fo_fo
 *
 * Return value: The "border-start-width" property value
**/
FoProperty*
fo_basic_link_get_border_start_width (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_start_width;
}

/**
 * fo_basic_link_set_border_start_width:
 * @fo_fo: The #FoFo object
 * @new_border_start_width: The new "border-start-width" property value
 * 
 * Sets the "border-start-width" property of @fo_fo to @new_border_start_width
 **/
void
fo_basic_link_set_border_start_width (FoFo *fo_fo,
		         FoProperty *new_border_start_width)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref (new_border_start_width);
    }
  if (fo_basic_link->border_start_width != NULL)
    {
      g_object_unref (fo_basic_link->border_start_width);
    }
  fo_basic_link->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-start-width");*/
}

/**
 * fo_basic_link_get_border_top_color:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-top-color" property of @fo_fo
 *
 * Return value: The "border-top-color" property value
**/
FoProperty*
fo_basic_link_get_border_top_color (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_top_color;
}

/**
 * fo_basic_link_set_border_top_color:
 * @fo_fo: The #FoFo object
 * @new_border_top_color: The new "border-top-color" property value
 * 
 * Sets the "border-top-color" property of @fo_fo to @new_border_top_color
 **/
void
fo_basic_link_set_border_top_color (FoFo *fo_fo,
		         FoProperty *new_border_top_color)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref (new_border_top_color);
    }
  if (fo_basic_link->border_top_color != NULL)
    {
      g_object_unref (fo_basic_link->border_top_color);
    }
  fo_basic_link->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-top-color");*/
}

/**
 * fo_basic_link_get_border_top_style:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-top-style" property of @fo_fo
 *
 * Return value: The "border-top-style" property value
**/
FoProperty*
fo_basic_link_get_border_top_style (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_top_style;
}

/**
 * fo_basic_link_set_border_top_style:
 * @fo_fo: The #FoFo object
 * @new_border_top_style: The new "border-top-style" property value
 * 
 * Sets the "border-top-style" property of @fo_fo to @new_border_top_style
 **/
void
fo_basic_link_set_border_top_style (FoFo *fo_fo,
		         FoProperty *new_border_top_style)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref (new_border_top_style);
    }
  if (fo_basic_link->border_top_style != NULL)
    {
      g_object_unref (fo_basic_link->border_top_style);
    }
  fo_basic_link->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-top-style");*/
}

/**
 * fo_basic_link_get_border_top_width:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "border-top-width" property of @fo_fo
 *
 * Return value: The "border-top-width" property value
**/
FoProperty*
fo_basic_link_get_border_top_width (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->border_top_width;
}

/**
 * fo_basic_link_set_border_top_width:
 * @fo_fo: The #FoFo object
 * @new_border_top_width: The new "border-top-width" property value
 * 
 * Sets the "border-top-width" property of @fo_fo to @new_border_top_width
 **/
void
fo_basic_link_set_border_top_width (FoFo *fo_fo,
		         FoProperty *new_border_top_width)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref (new_border_top_width);
    }
  if (fo_basic_link->border_top_width != NULL)
    {
      g_object_unref (fo_basic_link->border_top_width);
    }
  fo_basic_link->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_basic_link), "border-top-width");*/
}

/**
 * fo_basic_link_get_dominant_baseline:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "dominant-baseline" property of @fo_fo
 *
 * Return value: The "dominant-baseline" property value
**/
FoProperty*
fo_basic_link_get_dominant_baseline (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->dominant_baseline;
}

/**
 * fo_basic_link_set_dominant_baseline:
 * @fo_fo: The #FoFo object
 * @new_dominant_baseline: The new "dominant-baseline" property value
 * 
 * Sets the "dominant-baseline" property of @fo_fo to @new_dominant_baseline
 **/
void
fo_basic_link_set_dominant_baseline (FoFo *fo_fo,
		         FoProperty *new_dominant_baseline)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_DOMINANT_BASELINE (new_dominant_baseline));

  if (new_dominant_baseline != NULL)
    {
      g_object_ref (new_dominant_baseline);
    }
  if (fo_basic_link->dominant_baseline != NULL)
    {
      g_object_unref (fo_basic_link->dominant_baseline);
    }
  fo_basic_link->dominant_baseline = new_dominant_baseline;
  /*g_object_notify (G_OBJECT (fo_basic_link), "dominant-baseline");*/
}

/**
 * fo_basic_link_get_id:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "id" property of @fo_fo
 *
 * Return value: The "id" property value
**/
FoProperty*
fo_basic_link_get_id (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->id;
}

/**
 * fo_basic_link_set_id:
 * @fo_fo: The #FoFo object
 * @new_id: The new "id" property value
 * 
 * Sets the "id" property of @fo_fo to @new_id
 **/
void
fo_basic_link_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_basic_link->id != NULL)
    {
      g_object_unref (fo_basic_link->id);
    }
  fo_basic_link->id = new_id;
  /*g_object_notify (G_OBJECT (fo_basic_link), "id");*/
}

/**
 * fo_basic_link_get_keep_together:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together" property of @fo_fo
 *
 * Return value: The "keep-together" property value
**/
FoProperty*
fo_basic_link_get_keep_together (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_together;
}

/**
 * fo_basic_link_set_keep_together:
 * @fo_fo: The #FoFo object
 * @new_keep_together: The new "keep-together" property value
 * 
 * Sets the "keep-together" property of @fo_fo to @new_keep_together
 **/
void
fo_basic_link_set_keep_together (FoFo *fo_fo,
		         FoProperty *new_keep_together)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER (new_keep_together));

  if (new_keep_together != NULL)
    {
      g_object_ref (new_keep_together);
    }
  if (fo_basic_link->keep_together != NULL)
    {
      g_object_unref (fo_basic_link->keep_together);
    }
  fo_basic_link->keep_together = new_keep_together;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-together");*/
}

/**
 * fo_basic_link_get_keep_together_within_column:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-column" property of @fo_fo
 *
 * Return value: The "keep-together-within-column" property value
**/
FoProperty*
fo_basic_link_get_keep_together_within_column (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_together_within_column;
}

/**
 * fo_basic_link_set_keep_together_within_column:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_column: The new "keep-together-within-column" property value
 * 
 * Sets the "keep-together-within-column" property of @fo_fo to @new_keep_together_within_column
 **/
void
fo_basic_link_set_keep_together_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_column)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN (new_keep_together_within_column));

  if (new_keep_together_within_column != NULL)
    {
      g_object_ref (new_keep_together_within_column);
    }
  if (fo_basic_link->keep_together_within_column != NULL)
    {
      g_object_unref (fo_basic_link->keep_together_within_column);
    }
  fo_basic_link->keep_together_within_column = new_keep_together_within_column;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-together-within-column");*/
}

/**
 * fo_basic_link_get_keep_together_within_line:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-line" property of @fo_fo
 *
 * Return value: The "keep-together-within-line" property value
**/
FoProperty*
fo_basic_link_get_keep_together_within_line (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_together_within_line;
}

/**
 * fo_basic_link_set_keep_together_within_line:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_line: The new "keep-together-within-line" property value
 * 
 * Sets the "keep-together-within-line" property of @fo_fo to @new_keep_together_within_line
 **/
void
fo_basic_link_set_keep_together_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_line)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_LINE (new_keep_together_within_line));

  if (new_keep_together_within_line != NULL)
    {
      g_object_ref (new_keep_together_within_line);
    }
  if (fo_basic_link->keep_together_within_line != NULL)
    {
      g_object_unref (fo_basic_link->keep_together_within_line);
    }
  fo_basic_link->keep_together_within_line = new_keep_together_within_line;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-together-within-line");*/
}

/**
 * fo_basic_link_get_keep_together_within_page:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-together-within-page" property of @fo_fo
 *
 * Return value: The "keep-together-within-page" property value
**/
FoProperty*
fo_basic_link_get_keep_together_within_page (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_together_within_page;
}

/**
 * fo_basic_link_set_keep_together_within_page:
 * @fo_fo: The #FoFo object
 * @new_keep_together_within_page: The new "keep-together-within-page" property value
 * 
 * Sets the "keep-together-within-page" property of @fo_fo to @new_keep_together_within_page
 **/
void
fo_basic_link_set_keep_together_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_together_within_page)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE (new_keep_together_within_page));

  if (new_keep_together_within_page != NULL)
    {
      g_object_ref (new_keep_together_within_page);
    }
  if (fo_basic_link->keep_together_within_page != NULL)
    {
      g_object_unref (fo_basic_link->keep_together_within_page);
    }
  fo_basic_link->keep_together_within_page = new_keep_together_within_page;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-together-within-page");*/
}

/**
 * fo_basic_link_get_keep_with_next:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-next" property of @fo_fo
 *
 * Return value: The "keep-with-next" property value
**/
FoProperty*
fo_basic_link_get_keep_with_next (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_with_next;
}

/**
 * fo_basic_link_set_keep_with_next:
 * @fo_fo: The #FoFo object
 * @new_keep_with_next: The new "keep-with-next" property value
 * 
 * Sets the "keep-with-next" property of @fo_fo to @new_keep_with_next
 **/
void
fo_basic_link_set_keep_with_next (FoFo *fo_fo,
		         FoProperty *new_keep_with_next)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT (new_keep_with_next));

  if (new_keep_with_next != NULL)
    {
      g_object_ref (new_keep_with_next);
    }
  if (fo_basic_link->keep_with_next != NULL)
    {
      g_object_unref (fo_basic_link->keep_with_next);
    }
  fo_basic_link->keep_with_next = new_keep_with_next;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-with-next");*/
}

/**
 * fo_basic_link_get_keep_with_next_within_column:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-next-within-column" property of @fo_fo
 *
 * Return value: The "keep-with-next-within-column" property value
**/
FoProperty*
fo_basic_link_get_keep_with_next_within_column (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_with_next_within_column;
}

/**
 * fo_basic_link_set_keep_with_next_within_column:
 * @fo_fo: The #FoFo object
 * @new_keep_with_next_within_column: The new "keep-with-next-within-column" property value
 * 
 * Sets the "keep-with-next-within-column" property of @fo_fo to @new_keep_with_next_within_column
 **/
void
fo_basic_link_set_keep_with_next_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_column)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_COLUMN (new_keep_with_next_within_column));

  if (new_keep_with_next_within_column != NULL)
    {
      g_object_ref (new_keep_with_next_within_column);
    }
  if (fo_basic_link->keep_with_next_within_column != NULL)
    {
      g_object_unref (fo_basic_link->keep_with_next_within_column);
    }
  fo_basic_link->keep_with_next_within_column = new_keep_with_next_within_column;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-with-next-within-column");*/
}

/**
 * fo_basic_link_get_keep_with_next_within_line:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-next-within-line" property of @fo_fo
 *
 * Return value: The "keep-with-next-within-line" property value
**/
FoProperty*
fo_basic_link_get_keep_with_next_within_line (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_with_next_within_line;
}

/**
 * fo_basic_link_set_keep_with_next_within_line:
 * @fo_fo: The #FoFo object
 * @new_keep_with_next_within_line: The new "keep-with-next-within-line" property value
 * 
 * Sets the "keep-with-next-within-line" property of @fo_fo to @new_keep_with_next_within_line
 **/
void
fo_basic_link_set_keep_with_next_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_line)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (new_keep_with_next_within_line));

  if (new_keep_with_next_within_line != NULL)
    {
      g_object_ref (new_keep_with_next_within_line);
    }
  if (fo_basic_link->keep_with_next_within_line != NULL)
    {
      g_object_unref (fo_basic_link->keep_with_next_within_line);
    }
  fo_basic_link->keep_with_next_within_line = new_keep_with_next_within_line;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-with-next-within-line");*/
}

/**
 * fo_basic_link_get_keep_with_next_within_page:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-next-within-page" property of @fo_fo
 *
 * Return value: The "keep-with-next-within-page" property value
**/
FoProperty*
fo_basic_link_get_keep_with_next_within_page (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_with_next_within_page;
}

/**
 * fo_basic_link_set_keep_with_next_within_page:
 * @fo_fo: The #FoFo object
 * @new_keep_with_next_within_page: The new "keep-with-next-within-page" property value
 * 
 * Sets the "keep-with-next-within-page" property of @fo_fo to @new_keep_with_next_within_page
 **/
void
fo_basic_link_set_keep_with_next_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_next_within_page)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE (new_keep_with_next_within_page));

  if (new_keep_with_next_within_page != NULL)
    {
      g_object_ref (new_keep_with_next_within_page);
    }
  if (fo_basic_link->keep_with_next_within_page != NULL)
    {
      g_object_unref (fo_basic_link->keep_with_next_within_page);
    }
  fo_basic_link->keep_with_next_within_page = new_keep_with_next_within_page;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-with-next-within-page");*/
}

/**
 * fo_basic_link_get_keep_with_previous:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-previous" property of @fo_fo
 *
 * Return value: The "keep-with-previous" property value
**/
FoProperty*
fo_basic_link_get_keep_with_previous (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_with_previous;
}

/**
 * fo_basic_link_set_keep_with_previous:
 * @fo_fo: The #FoFo object
 * @new_keep_with_previous: The new "keep-with-previous" property value
 * 
 * Sets the "keep-with-previous" property of @fo_fo to @new_keep_with_previous
 **/
void
fo_basic_link_set_keep_with_previous (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS (new_keep_with_previous));

  if (new_keep_with_previous != NULL)
    {
      g_object_ref (new_keep_with_previous);
    }
  if (fo_basic_link->keep_with_previous != NULL)
    {
      g_object_unref (fo_basic_link->keep_with_previous);
    }
  fo_basic_link->keep_with_previous = new_keep_with_previous;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-with-previous");*/
}

/**
 * fo_basic_link_get_keep_with_previous_within_column:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-previous-within-column" property of @fo_fo
 *
 * Return value: The "keep-with-previous-within-column" property value
**/
FoProperty*
fo_basic_link_get_keep_with_previous_within_column (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_with_previous_within_column;
}

/**
 * fo_basic_link_set_keep_with_previous_within_column:
 * @fo_fo: The #FoFo object
 * @new_keep_with_previous_within_column: The new "keep-with-previous-within-column" property value
 * 
 * Sets the "keep-with-previous-within-column" property of @fo_fo to @new_keep_with_previous_within_column
 **/
void
fo_basic_link_set_keep_with_previous_within_column (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_column)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_COLUMN (new_keep_with_previous_within_column));

  if (new_keep_with_previous_within_column != NULL)
    {
      g_object_ref (new_keep_with_previous_within_column);
    }
  if (fo_basic_link->keep_with_previous_within_column != NULL)
    {
      g_object_unref (fo_basic_link->keep_with_previous_within_column);
    }
  fo_basic_link->keep_with_previous_within_column = new_keep_with_previous_within_column;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-with-previous-within-column");*/
}

/**
 * fo_basic_link_get_keep_with_previous_within_line:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-previous-within-line" property of @fo_fo
 *
 * Return value: The "keep-with-previous-within-line" property value
**/
FoProperty*
fo_basic_link_get_keep_with_previous_within_line (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_with_previous_within_line;
}

/**
 * fo_basic_link_set_keep_with_previous_within_line:
 * @fo_fo: The #FoFo object
 * @new_keep_with_previous_within_line: The new "keep-with-previous-within-line" property value
 * 
 * Sets the "keep-with-previous-within-line" property of @fo_fo to @new_keep_with_previous_within_line
 **/
void
fo_basic_link_set_keep_with_previous_within_line (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_line)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_LINE (new_keep_with_previous_within_line));

  if (new_keep_with_previous_within_line != NULL)
    {
      g_object_ref (new_keep_with_previous_within_line);
    }
  if (fo_basic_link->keep_with_previous_within_line != NULL)
    {
      g_object_unref (fo_basic_link->keep_with_previous_within_line);
    }
  fo_basic_link->keep_with_previous_within_line = new_keep_with_previous_within_line;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-with-previous-within-line");*/
}

/**
 * fo_basic_link_get_keep_with_previous_within_page:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "keep-with-previous-within-page" property of @fo_fo
 *
 * Return value: The "keep-with-previous-within-page" property value
**/
FoProperty*
fo_basic_link_get_keep_with_previous_within_page (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->keep_with_previous_within_page;
}

/**
 * fo_basic_link_set_keep_with_previous_within_page:
 * @fo_fo: The #FoFo object
 * @new_keep_with_previous_within_page: The new "keep-with-previous-within-page" property value
 * 
 * Sets the "keep-with-previous-within-page" property of @fo_fo to @new_keep_with_previous_within_page
 **/
void
fo_basic_link_set_keep_with_previous_within_page (FoFo *fo_fo,
		         FoProperty *new_keep_with_previous_within_page)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE (new_keep_with_previous_within_page));

  if (new_keep_with_previous_within_page != NULL)
    {
      g_object_ref (new_keep_with_previous_within_page);
    }
  if (fo_basic_link->keep_with_previous_within_page != NULL)
    {
      g_object_unref (fo_basic_link->keep_with_previous_within_page);
    }
  fo_basic_link->keep_with_previous_within_page = new_keep_with_previous_within_page;
  /*g_object_notify (G_OBJECT (fo_basic_link), "keep-with-previous-within-page");*/
}

/**
 * fo_basic_link_get_line_height:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "line-height" property of @fo_fo
 *
 * Return value: The "line-height" property value
**/
FoProperty*
fo_basic_link_get_line_height (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->line_height;
}

/**
 * fo_basic_link_set_line_height:
 * @fo_fo: The #FoFo object
 * @new_line_height: The new "line-height" property value
 * 
 * Sets the "line-height" property of @fo_fo to @new_line_height
 **/
void
fo_basic_link_set_line_height (FoFo *fo_fo,
		         FoProperty *new_line_height)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_LINE_HEIGHT (new_line_height));

  if (new_line_height != NULL)
    {
      g_object_ref (new_line_height);
    }
  if (fo_basic_link->line_height != NULL)
    {
      g_object_unref (fo_basic_link->line_height);
    }
  fo_basic_link->line_height = new_line_height;
  /*g_object_notify (G_OBJECT (fo_basic_link), "line-height");*/
}

/**
 * fo_basic_link_get_padding_after:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-after" property of @fo_fo
 *
 * Return value: The "padding-after" property value
**/
FoProperty*
fo_basic_link_get_padding_after (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->padding_after;
}

/**
 * fo_basic_link_set_padding_after:
 * @fo_fo: The #FoFo object
 * @new_padding_after: The new "padding-after" property value
 * 
 * Sets the "padding-after" property of @fo_fo to @new_padding_after
 **/
void
fo_basic_link_set_padding_after (FoFo *fo_fo,
		         FoProperty *new_padding_after)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref (new_padding_after);
    }
  if (fo_basic_link->padding_after != NULL)
    {
      g_object_unref (fo_basic_link->padding_after);
    }
  fo_basic_link->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_basic_link), "padding-after");*/
}

/**
 * fo_basic_link_get_padding_before:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-before" property of @fo_fo
 *
 * Return value: The "padding-before" property value
**/
FoProperty*
fo_basic_link_get_padding_before (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->padding_before;
}

/**
 * fo_basic_link_set_padding_before:
 * @fo_fo: The #FoFo object
 * @new_padding_before: The new "padding-before" property value
 * 
 * Sets the "padding-before" property of @fo_fo to @new_padding_before
 **/
void
fo_basic_link_set_padding_before (FoFo *fo_fo,
		         FoProperty *new_padding_before)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref (new_padding_before);
    }
  if (fo_basic_link->padding_before != NULL)
    {
      g_object_unref (fo_basic_link->padding_before);
    }
  fo_basic_link->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_basic_link), "padding-before");*/
}

/**
 * fo_basic_link_get_padding_bottom:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-bottom" property of @fo_fo
 *
 * Return value: The "padding-bottom" property value
**/
FoProperty*
fo_basic_link_get_padding_bottom (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->padding_bottom;
}

/**
 * fo_basic_link_set_padding_bottom:
 * @fo_fo: The #FoFo object
 * @new_padding_bottom: The new "padding-bottom" property value
 * 
 * Sets the "padding-bottom" property of @fo_fo to @new_padding_bottom
 **/
void
fo_basic_link_set_padding_bottom (FoFo *fo_fo,
		         FoProperty *new_padding_bottom)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref (new_padding_bottom);
    }
  if (fo_basic_link->padding_bottom != NULL)
    {
      g_object_unref (fo_basic_link->padding_bottom);
    }
  fo_basic_link->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_basic_link), "padding-bottom");*/
}

/**
 * fo_basic_link_get_padding_end:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-end" property of @fo_fo
 *
 * Return value: The "padding-end" property value
**/
FoProperty*
fo_basic_link_get_padding_end (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->padding_end;
}

/**
 * fo_basic_link_set_padding_end:
 * @fo_fo: The #FoFo object
 * @new_padding_end: The new "padding-end" property value
 * 
 * Sets the "padding-end" property of @fo_fo to @new_padding_end
 **/
void
fo_basic_link_set_padding_end (FoFo *fo_fo,
		         FoProperty *new_padding_end)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref (new_padding_end);
    }
  if (fo_basic_link->padding_end != NULL)
    {
      g_object_unref (fo_basic_link->padding_end);
    }
  fo_basic_link->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_basic_link), "padding-end");*/
}

/**
 * fo_basic_link_get_padding_left:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-left" property of @fo_fo
 *
 * Return value: The "padding-left" property value
**/
FoProperty*
fo_basic_link_get_padding_left (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->padding_left;
}

/**
 * fo_basic_link_set_padding_left:
 * @fo_fo: The #FoFo object
 * @new_padding_left: The new "padding-left" property value
 * 
 * Sets the "padding-left" property of @fo_fo to @new_padding_left
 **/
void
fo_basic_link_set_padding_left (FoFo *fo_fo,
		         FoProperty *new_padding_left)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref (new_padding_left);
    }
  if (fo_basic_link->padding_left != NULL)
    {
      g_object_unref (fo_basic_link->padding_left);
    }
  fo_basic_link->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_basic_link), "padding-left");*/
}

/**
 * fo_basic_link_get_padding_right:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-right" property of @fo_fo
 *
 * Return value: The "padding-right" property value
**/
FoProperty*
fo_basic_link_get_padding_right (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->padding_right;
}

/**
 * fo_basic_link_set_padding_right:
 * @fo_fo: The #FoFo object
 * @new_padding_right: The new "padding-right" property value
 * 
 * Sets the "padding-right" property of @fo_fo to @new_padding_right
 **/
void
fo_basic_link_set_padding_right (FoFo *fo_fo,
		         FoProperty *new_padding_right)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref (new_padding_right);
    }
  if (fo_basic_link->padding_right != NULL)
    {
      g_object_unref (fo_basic_link->padding_right);
    }
  fo_basic_link->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_basic_link), "padding-right");*/
}

/**
 * fo_basic_link_get_padding_start:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-start" property of @fo_fo
 *
 * Return value: The "padding-start" property value
**/
FoProperty*
fo_basic_link_get_padding_start (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->padding_start;
}

/**
 * fo_basic_link_set_padding_start:
 * @fo_fo: The #FoFo object
 * @new_padding_start: The new "padding-start" property value
 * 
 * Sets the "padding-start" property of @fo_fo to @new_padding_start
 **/
void
fo_basic_link_set_padding_start (FoFo *fo_fo,
		         FoProperty *new_padding_start)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref (new_padding_start);
    }
  if (fo_basic_link->padding_start != NULL)
    {
      g_object_unref (fo_basic_link->padding_start);
    }
  fo_basic_link->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_basic_link), "padding-start");*/
}

/**
 * fo_basic_link_get_padding_top:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "padding-top" property of @fo_fo
 *
 * Return value: The "padding-top" property value
**/
FoProperty*
fo_basic_link_get_padding_top (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->padding_top;
}

/**
 * fo_basic_link_set_padding_top:
 * @fo_fo: The #FoFo object
 * @new_padding_top: The new "padding-top" property value
 * 
 * Sets the "padding-top" property of @fo_fo to @new_padding_top
 **/
void
fo_basic_link_set_padding_top (FoFo *fo_fo,
		         FoProperty *new_padding_top)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref (new_padding_top);
    }
  if (fo_basic_link->padding_top != NULL)
    {
      g_object_unref (fo_basic_link->padding_top);
    }
  fo_basic_link->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_basic_link), "padding-top");*/
}

/**
 * fo_basic_link_get_role:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "role" property of @fo_fo
 *
 * Return value: The "role" property value
**/
FoProperty*
fo_basic_link_get_role (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->role;
}

/**
 * fo_basic_link_set_role:
 * @fo_fo: The #FoFo object
 * @new_role: The new "role" property value
 * 
 * Sets the "role" property of @fo_fo to @new_role
 **/
void
fo_basic_link_set_role (FoFo *fo_fo,
		         FoProperty *new_role)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_ROLE (new_role));

  if (new_role != NULL)
    {
      g_object_ref (new_role);
    }
  if (fo_basic_link->role != NULL)
    {
      g_object_unref (fo_basic_link->role);
    }
  fo_basic_link->role = new_role;
  /*g_object_notify (G_OBJECT (fo_basic_link), "role");*/
}

/**
 * fo_basic_link_get_source_document:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "source-document" property of @fo_fo
 *
 * Return value: The "source-document" property value
**/
FoProperty*
fo_basic_link_get_source_document (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->source_document;
}

/**
 * fo_basic_link_set_source_document:
 * @fo_fo: The #FoFo object
 * @new_source_document: The new "source-document" property value
 * 
 * Sets the "source-document" property of @fo_fo to @new_source_document
 **/
void
fo_basic_link_set_source_document (FoFo *fo_fo,
		         FoProperty *new_source_document)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document != NULL)
    {
      g_object_ref (new_source_document);
    }
  if (fo_basic_link->source_document != NULL)
    {
      g_object_unref (fo_basic_link->source_document);
    }
  fo_basic_link->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_basic_link), "source-document");*/
}

/**
 * fo_basic_link_get_space_end:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "space-end" property of @fo_fo
 *
 * Return value: The "space-end" property value
**/
FoProperty*
fo_basic_link_get_space_end (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->space_end;
}

/**
 * fo_basic_link_set_space_end:
 * @fo_fo: The #FoFo object
 * @new_space_end: The new "space-end" property value
 * 
 * Sets the "space-end" property of @fo_fo to @new_space_end
 **/
void
fo_basic_link_set_space_end (FoFo *fo_fo,
		         FoProperty *new_space_end)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_SPACE_END (new_space_end));

  if (new_space_end != NULL)
    {
      g_object_ref (new_space_end);
    }
  if (fo_basic_link->space_end != NULL)
    {
      g_object_unref (fo_basic_link->space_end);
    }
  fo_basic_link->space_end = new_space_end;
  /*g_object_notify (G_OBJECT (fo_basic_link), "space-end");*/
}

/**
 * fo_basic_link_get_space_start:
 * @fo_fo: The @FoFo object
 * 
 * Gets the "space-start" property of @fo_fo
 *
 * Return value: The "space-start" property value
**/
FoProperty*
fo_basic_link_get_space_start (FoFo *fo_fo)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_val_if_fail (fo_basic_link != NULL, NULL);
  g_return_val_if_fail (FO_IS_BASIC_LINK (fo_basic_link), NULL);

  return fo_basic_link->space_start;
}

/**
 * fo_basic_link_set_space_start:
 * @fo_fo: The #FoFo object
 * @new_space_start: The new "space-start" property value
 * 
 * Sets the "space-start" property of @fo_fo to @new_space_start
 **/
void
fo_basic_link_set_space_start (FoFo *fo_fo,
		         FoProperty *new_space_start)
{
  FoBasicLink *fo_basic_link = (FoBasicLink *) fo_fo;

  g_return_if_fail (fo_basic_link != NULL);
  g_return_if_fail (FO_IS_BASIC_LINK (fo_basic_link));
  g_return_if_fail (FO_IS_PROPERTY_SPACE_START (new_space_start));

  if (new_space_start != NULL)
    {
      g_object_ref (new_space_start);
    }
  if (fo_basic_link->space_start != NULL)
    {
      g_object_unref (fo_basic_link->space_start);
    }
  fo_basic_link->space_start = new_space_start;
  /*g_object_notify (G_OBJECT (fo_basic_link), "space-start");*/
}
