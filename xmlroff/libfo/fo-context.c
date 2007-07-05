/* Fo
 * fo-context.c: Context formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-object.h"
#include "datatype/fo-all-datatype.h"
#include "property/fo-all-property.h"
#include "fo-context.h"
#include "fo-context-private.h"

enum {
  PROP_0,
  PROP_ALIGNMENT_ADJUST,
  PROP_ALIGNMENT_BASELINE,
  PROP_BACKGROUND_COLOR,
  PROP_BACKGROUND_IMAGE,
  PROP_BASELINE_SHIFT,
  PROP_BLOCK_PROGRESSION_DIMENSION,
  PROP_BLOCK_PROGRESSION_DIMENSION_MINIMUM,
  PROP_BLOCK_PROGRESSION_DIMENSION_OPTIMUM,
  PROP_BLOCK_PROGRESSION_DIMENSION_MAXIMUM,
  PROP_BORDER,
  PROP_BORDER_AFTER_COLOR,
  PROP_BORDER_AFTER_PRECEDENCE,
  PROP_BORDER_AFTER_STYLE,
  PROP_BORDER_AFTER_WIDTH,
  PROP_BORDER_BEFORE_COLOR,
  PROP_BORDER_BEFORE_PRECEDENCE,
  PROP_BORDER_BEFORE_STYLE,
  PROP_BORDER_BEFORE_WIDTH,
  PROP_BORDER_BOTTOM,
  PROP_BORDER_BOTTOM_COLOR,
  PROP_BORDER_BOTTOM_STYLE,
  PROP_BORDER_BOTTOM_WIDTH,
  PROP_BORDER_COLLAPSE,
  PROP_BORDER_COLOR,
  PROP_BORDER_END_COLOR,
  PROP_BORDER_END_PRECEDENCE,
  PROP_BORDER_END_STYLE,
  PROP_BORDER_END_WIDTH,
  PROP_BORDER_LEFT,
  PROP_BORDER_LEFT_COLOR,
  PROP_BORDER_LEFT_STYLE,
  PROP_BORDER_LEFT_WIDTH,
  PROP_BORDER_RIGHT,
  PROP_BORDER_RIGHT_COLOR,
  PROP_BORDER_RIGHT_STYLE,
  PROP_BORDER_RIGHT_WIDTH,
  PROP_BORDER_SEPARATION,
  PROP_BORDER_START_COLOR,
  PROP_BORDER_START_PRECEDENCE,
  PROP_BORDER_START_STYLE,
  PROP_BORDER_START_WIDTH,
  PROP_BORDER_STYLE,
  PROP_BORDER_TOP,
  PROP_BORDER_TOP_COLOR,
  PROP_BORDER_TOP_STYLE,
  PROP_BORDER_TOP_WIDTH,
  PROP_BORDER_WIDTH,
  PROP_BREAK_AFTER,
  PROP_BREAK_BEFORE,
  PROP_CHARACTER,
  PROP_CLIP,
  PROP_COLOR,
  PROP_COLUMN_NUMBER,
  PROP_COLUMN_WIDTH,
  PROP_CONTENT_HEIGHT,
  PROP_CONTENT_TYPE,
  PROP_CONTENT_WIDTH,
  PROP_DIRECTION,
  PROP_DISPLAY_ALIGN,
  PROP_DOMINANT_BASELINE,
  PROP_END_INDENT,
  PROP_EXTENT,
  PROP_FLOW_NAME,
  PROP_FONT_FAMILY,
  PROP_FONT_SIZE,
  PROP_FONT_STRETCH,
  PROP_FONT_STYLE,
  PROP_FONT_VARIANT,
  PROP_FONT_WEIGHT,
  PROP_FORMAT,
  PROP_GROUPING_SEPARATOR,
  PROP_GROUPING_SIZE,
  PROP_HEIGHT,
  PROP_ID,
  PROP_INLINE_PROGRESSION_DIMENSION,
  PROP_INLINE_PROGRESSION_DIMENSION_MINIMUM,
  PROP_INLINE_PROGRESSION_DIMENSION_OPTIMUM,
  PROP_INLINE_PROGRESSION_DIMENSION_MAXIMUM,
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
  PROP_LETTER_VALUE,
  PROP_LINE_HEIGHT,
  PROP_LINE_STACKING_STRATEGY,
  PROP_LINEFEED_TREATMENT,
  PROP_MARGIN,
  PROP_MARGIN_BOTTOM,
  PROP_MARGIN_LEFT,
  PROP_MARGIN_RIGHT,
  PROP_MARGIN_TOP,
  PROP_MASTER_NAME,
  PROP_MASTER_REFERENCE,
  PROP_MEDIA_USAGE,
  PROP_NUMBER_COLUMNS_REPEATED,
  PROP_NUMBER_COLUMNS_SPANNED,
  PROP_NUMBER_ROWS_SPANNED,
  PROP_ORPHANS,
  PROP_OVERFLOW,
  PROP_PADDING,
  PROP_PADDING_AFTER,
  PROP_PADDING_AFTER_LENGTH,
  PROP_PADDING_AFTER_CONDITY,
  PROP_PADDING_BEFORE,
  PROP_PADDING_BEFORE_LENGTH,
  PROP_PADDING_BEFORE_CONDITY,
  PROP_PADDING_BOTTOM,
  PROP_PADDING_END,
  PROP_PADDING_END_LENGTH,
  PROP_PADDING_END_CONDITY,
  PROP_PADDING_LEFT,
  PROP_PADDING_RIGHT,
  PROP_PADDING_START,
  PROP_PADDING_START_LENGTH,
  PROP_PADDING_START_CONDITY,
  PROP_PADDING_TOP,
  PROP_PAGE_HEIGHT,
  PROP_PAGE_WIDTH,
  PROP_PROVISIONAL_DISTANCE_BETWEEN_STARTS,
  PROP_PROVISIONAL_LABEL_SEPARATION,
  PROP_REF_ID,
  PROP_REGION_NAME,
  PROP_ROLE,
  PROP_SCALING,
  PROP_SCALING_METHOD,
  PROP_SCORE_SPACES,
  PROP_SOURCE_DOCUMENT,
  PROP_SPACE_AFTER,
  PROP_SPACE_AFTER_MINIMUM,
  PROP_SPACE_AFTER_OPTIMUM,
  PROP_SPACE_AFTER_MAXIMUM,
  PROP_SPACE_AFTER_PRECEDENCE,
  PROP_SPACE_AFTER_CONDITY,
  PROP_SPACE_BEFORE,
  PROP_SPACE_BEFORE_MINIMUM,
  PROP_SPACE_BEFORE_OPTIMUM,
  PROP_SPACE_BEFORE_MAXIMUM,
  PROP_SPACE_BEFORE_PRECEDENCE,
  PROP_SPACE_BEFORE_CONDITY,
  PROP_SPACE_END,
  PROP_SPACE_END_MINIMUM,
  PROP_SPACE_END_OPTIMUM,
  PROP_SPACE_END_MAXIMUM,
  PROP_SPACE_END_PRECEDENCE,
  PROP_SPACE_END_CONDITY,
  PROP_SPACE_START,
  PROP_SPACE_START_MINIMUM,
  PROP_SPACE_START_OPTIMUM,
  PROP_SPACE_START_MAXIMUM,
  PROP_SPACE_START_PRECEDENCE,
  PROP_SPACE_START_CONDITY,
  PROP_SPAN,
  PROP_SRC,
  PROP_START_INDENT,
  PROP_TABLE_LAYOUT,
  PROP_TEXT_ALIGN,
  PROP_TEXT_INDENT,
  PROP_UNICODE_BIDI,
  PROP_WHITE_SPACE_COLLAPSE,
  PROP_WHITE_SPACE_TREATMENT,
  PROP_WIDOWS,
  PROP_WIDTH,
  PROP_WRAP_OPTION,
  PROP_WRITING_MODE
};

static void fo_context_class_init  (FoContextClass *klass);
static void fo_context_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_context_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_context_finalize    (GObject           *object);

static void fo_context_property_slist_foreach (gpointer   property,
					       gpointer   context);
static void fo_context_debug_dump             (FoObject  *object,
					       gint       depth);

static FoProperty* fo_context_get_space_before_minimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_before_optimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_before_maximum (FoContext *fo_context);
static FoProperty* fo_context_get_space_before_condity (FoContext *fo_context);
static FoProperty* fo_context_get_space_before_precedence (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_minimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_optimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_maximum (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_condity (FoContext *fo_context);
static FoProperty* fo_context_get_space_after_precedence (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_minimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_optimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_maximum (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_condity (FoContext *fo_context);
static FoProperty* fo_context_get_space_end_precedence (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_minimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_optimum (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_maximum (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_condity (FoContext *fo_context);
static FoProperty* fo_context_get_space_start_precedence (FoContext *fo_context);

static gpointer parent_class;

/**
 * fo_context_get_type:
 * 
 * Register the #FoContext type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoContext.
 **/
GType
fo_context_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoContextClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_context_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoContext),
        0,              /* n_preallocs */
        NULL,           /* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoContext",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_context_initialize:
 * @context: #FoContext to initialize.
 * 
 * Initialize @context with the initial/default value of every property.
 **/
void
fo_context_initialize (FoContext *context)
{
  context->alignment_adjust =
    g_object_ref (fo_property_alignment_adjust_get_initial ());
  context->alignment_baseline =
    g_object_ref (fo_property_alignment_baseline_get_initial ());
  context->background_color =
    g_object_ref (fo_property_background_color_get_initial ());
  context->background_image =
    g_object_ref (fo_property_background_image_get_initial ());
  context->baseline_shift =
    g_object_ref (fo_property_baseline_shift_get_initial ());
  context->block_progression_dimension =
    g_object_ref (fo_property_block_progression_dimension_get_initial ());
  context->block_progression_dimension_minimum = NULL;
  context->block_progression_dimension_optimum = NULL;
  context->block_progression_dimension_maximum = NULL;
  context->border =
    g_object_ref (fo_property_border_get_initial ());
  context->border_after_color =
    g_object_ref (fo_property_border_after_color_get_initial ());
  context->border_after_precedence =
    g_object_ref (fo_property_border_after_precedence_get_initial ());
  context->border_after_style =
    g_object_ref (fo_property_border_after_style_get_initial ());
  context->border_after_width =
    g_object_ref (fo_property_border_after_width_get_initial ());
  context->border_before_color =
    g_object_ref (fo_property_border_before_color_get_initial ());
  context->border_before_precedence =
    g_object_ref (fo_property_border_before_precedence_get_initial ());
  context->border_before_style =
    g_object_ref (fo_property_border_before_style_get_initial ());
  context->border_before_width =
    g_object_ref (fo_property_border_before_width_get_initial ());
  context->border_bottom =
    g_object_ref (fo_property_border_bottom_get_initial ());
  context->border_bottom_color =
    g_object_ref (fo_property_border_bottom_color_get_initial ());
  context->border_bottom_style =
    g_object_ref (fo_property_border_bottom_style_get_initial ());
  context->border_bottom_width =
    g_object_ref (fo_property_border_bottom_width_get_initial ());
  context->border_collapse =
    g_object_ref (fo_property_border_collapse_get_initial ());
  context->border_color =
    g_object_ref (fo_property_border_color_get_initial ());
  context->border_end_color =
    g_object_ref (fo_property_border_end_color_get_initial ());
  context->border_end_precedence =
    g_object_ref (fo_property_border_end_precedence_get_initial ());
  context->border_end_style =
    g_object_ref (fo_property_border_end_style_get_initial ());
  context->border_end_width =
    g_object_ref (fo_property_border_end_width_get_initial ());
  context->border_left =
    g_object_ref (fo_property_border_left_get_initial ());
  context->border_left_color =
    g_object_ref (fo_property_border_left_color_get_initial ());
  context->border_left_style =
    g_object_ref (fo_property_border_left_style_get_initial ());
  context->border_left_width =
    g_object_ref (fo_property_border_left_width_get_initial ());
  context->border_right =
    g_object_ref (fo_property_border_right_get_initial ());
  context->border_right_color =
    g_object_ref (fo_property_border_right_color_get_initial ());
  context->border_right_style =
    g_object_ref (fo_property_border_right_style_get_initial ());
  context->border_right_width =
    g_object_ref (fo_property_border_right_width_get_initial ());
  context->border_separation =
    g_object_ref (fo_property_border_separation_get_initial ());
  context->border_start_color =
    g_object_ref (fo_property_border_start_color_get_initial ());
  context->border_start_precedence =
    g_object_ref (fo_property_border_start_precedence_get_initial ());
  context->border_start_style =
    g_object_ref (fo_property_border_start_style_get_initial ());
  context->border_start_width =
    g_object_ref (fo_property_border_start_width_get_initial ());
  context->border_style =
    g_object_ref (fo_property_border_style_get_initial ());
  context->border_top =
    g_object_ref (fo_property_border_top_get_initial ());
  context->border_top_color =
    g_object_ref (fo_property_border_top_color_get_initial ());
  context->border_top_style =
    g_object_ref (fo_property_border_top_style_get_initial ());
  context->border_top_width =
    g_object_ref (fo_property_border_top_width_get_initial ());
  context->border_width =
    g_object_ref (fo_property_border_width_get_initial ());
  context->break_after =
    g_object_ref (fo_property_break_after_get_initial ());
  context->break_before =
    g_object_ref (fo_property_break_before_get_initial ());
  context->character =
    g_object_ref (fo_property_character_get_initial ());
  context->clip =
    g_object_ref (fo_property_clip_get_initial ());
  context->color =
    g_object_ref (fo_property_color_get_initial ());
  context->column_number =
    g_object_ref (fo_property_column_number_get_initial ());
  context->column_width =
    g_object_ref (fo_property_column_width_get_initial ());
  context->content_height =
    g_object_ref (fo_property_content_height_get_initial ());
  context->content_type =
    g_object_ref (fo_property_content_type_get_initial ());
  context->content_width =
    g_object_ref (fo_property_content_width_get_initial ());
  context->direction =
    g_object_ref (fo_property_direction_get_initial ());
  context->display_align =
    g_object_ref (fo_property_display_align_get_initial ());
  context->dominant_baseline =
    g_object_ref (fo_property_dominant_baseline_get_initial ());
  context->end_indent =
    g_object_ref (fo_property_end_indent_get_initial ());
  context->extent =
    g_object_ref (fo_property_extent_get_initial ());
  context->flow_name =
    g_object_ref (fo_property_flow_name_get_initial ());
  context->font_family =
    g_object_ref (fo_property_font_family_get_initial ());
  context->font_size =
    g_object_ref (fo_property_font_size_get_initial ());
  context->font_stretch =
    g_object_ref (fo_property_font_stretch_get_initial ());
  context->font_style =
    g_object_ref (fo_property_font_style_get_initial ());
  context->font_variant =
    g_object_ref (fo_property_font_variant_get_initial ());
  context->font_weight =
    g_object_ref (fo_property_font_weight_get_initial ());
  context->format =
    g_object_ref (fo_property_format_get_initial ());
  context->grouping_separator =
    g_object_ref (fo_property_grouping_separator_get_initial ());
  context->grouping_size =
    g_object_ref (fo_property_grouping_size_get_initial ());
  context->height =
    g_object_ref (fo_property_height_get_initial ());
  context->id =
    g_object_ref (fo_property_id_get_initial ());
  context->inline_progression_dimension =
    g_object_ref (fo_property_inline_progression_dimension_get_initial ());
  context->inline_progression_dimension_minimum = NULL;
  context->inline_progression_dimension_optimum = NULL;
  context->inline_progression_dimension_maximum = NULL;
  context->keep_together =
    g_object_ref (fo_property_keep_together_get_initial ());
  context->keep_together_within_column =
    g_object_ref (fo_property_keep_together_within_column_get_initial ());
  context->keep_together_within_line =
    g_object_ref (fo_property_keep_together_within_line_get_initial ());
  context->keep_together_within_page =
    g_object_ref (fo_property_keep_together_within_page_get_initial ());
  context->keep_with_next =
    g_object_ref (fo_property_keep_with_next_get_initial ());
  context->keep_with_next_within_column =
    g_object_ref (fo_property_keep_with_next_within_column_get_initial ());
  context->keep_with_next_within_line =
    g_object_ref (fo_property_keep_with_next_within_line_get_initial ());
  context->keep_with_next_within_page =
    g_object_ref (fo_property_keep_with_next_within_page_get_initial ());
  context->keep_with_previous =
    g_object_ref (fo_property_keep_with_previous_get_initial ());
  context->keep_with_previous_within_column =
    g_object_ref (fo_property_keep_with_previous_within_column_get_initial ());
  context->keep_with_previous_within_line =
    g_object_ref (fo_property_keep_with_previous_within_line_get_initial ());
  context->keep_with_previous_within_page =
    g_object_ref (fo_property_keep_with_previous_within_page_get_initial ());
  context->letter_value =
    g_object_ref (fo_property_letter_value_get_initial ());
  context->line_height =
    g_object_ref (fo_property_line_height_get_initial ());
  context->line_stacking_strategy =
    g_object_ref (fo_property_line_stacking_strategy_get_initial ());
  context->linefeed_treatment =
    g_object_ref (fo_property_linefeed_treatment_get_initial ());
  context->margin =
    g_object_ref (fo_property_margin_get_initial ());
  context->margin_bottom =
    g_object_ref (fo_property_margin_bottom_get_initial ());
  context->margin_left =
    g_object_ref (fo_property_margin_left_get_initial ());
  context->margin_right =
    g_object_ref (fo_property_margin_right_get_initial ());
  context->margin_top =
    g_object_ref (fo_property_margin_top_get_initial ());
  context->master_name =
    g_object_ref (fo_property_master_name_get_initial ());
  context->master_reference =
    g_object_ref (fo_property_master_reference_get_initial ());
  context->media_usage =
    g_object_ref (fo_property_media_usage_get_initial ());
  context->number_columns_repeated =
    g_object_ref (fo_property_number_columns_repeated_get_initial ());
  context->number_columns_spanned =
    g_object_ref (fo_property_number_columns_spanned_get_initial ());
  context->number_rows_spanned =
    g_object_ref (fo_property_number_rows_spanned_get_initial ());
  context->orphans =
    g_object_ref (fo_property_orphans_get_initial ());
  context->overflow =
    g_object_ref (fo_property_overflow_get_initial ());
  context->padding =
    g_object_ref (fo_property_padding_get_initial ());
  context->padding_after =
    g_object_ref (fo_property_padding_after_get_initial ());
  context->padding_after_length = NULL;
  context->padding_after_condity =
    g_object_ref (fo_property_padding_after_condity_get_initial ());
  context->padding_before =
    g_object_ref (fo_property_padding_before_get_initial ());
  context->padding_before_length = NULL;
  context->padding_before_condity =
    g_object_ref (fo_property_padding_before_condity_get_initial ());
  context->padding_bottom =
    g_object_ref (fo_property_padding_bottom_get_initial ());
  context->padding_end =
    g_object_ref (fo_property_padding_end_get_initial ());
  context->padding_end_length = NULL;
  context->padding_end_condity =
    g_object_ref (fo_property_padding_end_condity_get_initial ());
  context->padding_left =
    g_object_ref (fo_property_padding_left_get_initial ());
  context->padding_right =
    g_object_ref (fo_property_padding_right_get_initial ());
  context->padding_start =
    g_object_ref (fo_property_padding_start_get_initial ());
  context->padding_start_length = NULL;
  context->padding_start_condity =
    g_object_ref (fo_property_padding_start_condity_get_initial ());
  context->padding_top =
    g_object_ref (fo_property_padding_top_get_initial ());
  context->page_height =
    g_object_ref (fo_property_page_height_get_initial ());
  context->page_width =
    g_object_ref (fo_property_page_width_get_initial ());
  context->provisional_distance_between_starts =
    g_object_ref (fo_property_provisional_distance_between_starts_get_initial ());
  context->provisional_label_separation =
    g_object_ref (fo_property_provisional_label_separation_get_initial ());
  context->ref_id =
    g_object_ref (fo_property_ref_id_get_initial ());
  context->region_name =
    g_object_ref (fo_property_region_name_get_initial ());
  context->role =
    g_object_ref (fo_property_role_get_initial ());
  context->scaling =
    g_object_ref (fo_property_scaling_get_initial ());
  context->scaling_method =
    g_object_ref (fo_property_scaling_method_get_initial ());
  context->score_spaces =
    g_object_ref (fo_property_score_spaces_get_initial ());
  context->source_document =
    g_object_ref (fo_property_source_document_get_initial ());
  context->space_after =
    g_object_ref (fo_property_space_after_get_initial ());
  context->space_after_minimum = NULL;
  context->space_after_optimum = NULL;
  context->space_after_maximum = NULL;
  context->space_after_precedence =
    g_object_ref (fo_property_space_after_precedence_get_initial ());
  context->space_after_condity =
    g_object_ref (fo_property_space_after_condity_get_initial ());
  context->space_before =
    g_object_ref (fo_property_space_before_get_initial ());
  context->space_before_minimum = NULL;
  context->space_before_optimum = NULL;
  context->space_before_maximum = NULL;
  context->space_before_precedence =
    g_object_ref (fo_property_space_before_precedence_get_initial ());
  context->space_before_condity =
    g_object_ref (fo_property_space_before_condity_get_initial ());
  context->space_end =
    g_object_ref (fo_property_space_end_get_initial ());
  context->space_end_minimum = NULL;
  context->space_end_optimum = NULL;
  context->space_end_maximum = NULL;
  context->space_end_precedence =
    g_object_ref (fo_property_space_end_precedence_get_initial ());
  context->space_end_condity =
    g_object_ref (fo_property_space_end_condity_get_initial ());
  context->space_start =
    g_object_ref (fo_property_space_start_get_initial ());
  context->space_start_minimum = NULL;
  context->space_start_optimum = NULL;
  context->space_start_maximum = NULL;
  context->space_start_precedence =
    g_object_ref (fo_property_space_start_precedence_get_initial ());
  context->space_start_condity =
    g_object_ref (fo_property_space_start_condity_get_initial ());
  context->span =
    g_object_ref (fo_property_span_get_initial ());
  context->src =
    g_object_ref (fo_property_src_get_initial ());
  context->start_indent =
    g_object_ref (fo_property_start_indent_get_initial ());
  context->table_layout =
    g_object_ref (fo_property_table_layout_get_initial ());
  context->text_align =
    g_object_ref (fo_property_text_align_get_initial ());
  context->text_indent =
    g_object_ref (fo_property_text_indent_get_initial ());
  context->unicode_bidi =
    g_object_ref (fo_property_unicode_bidi_get_initial ());
  context->white_space_collapse =
    g_object_ref (fo_property_white_space_collapse_get_initial ());
  context->white_space_treatment =
    g_object_ref (fo_property_white_space_treatment_get_initial ());
  context->widows =
    g_object_ref (fo_property_widows_get_initial ());
  context->width =
    g_object_ref (fo_property_width_get_initial ());
  context->wrap_option =
    g_object_ref (fo_property_wrap_option_get_initial ());
  context->writing_mode =
    g_object_ref (fo_property_writing_mode_get_initial ());
}

/**
 * fo_context_init:
 * @klass: #FoContextClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoContextClass.
 **/
void
fo_context_class_init (FoContextClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_context_finalize;

  object_class->set_property = fo_context_set_property;
  object_class->get_property = fo_context_get_property;

  fo_object_class->debug_dump = fo_context_debug_dump;

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
     PROP_BLOCK_PROGRESSION_DIMENSION_MINIMUM,
     g_param_spec_object ("block-progression-dimension-minimum",
			  _("Block Progression Dimension Minimum"),
			  _("Block Progression Dimension Minimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BLOCK_PROGRESSION_DIMENSION_OPTIMUM,
     g_param_spec_object ("block-progression-dimension-optimum",
			  _("Block Progression Dimension Optimum"),
			  _("Block Progression Dimension Optimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BLOCK_PROGRESSION_DIMENSION_MAXIMUM,
     g_param_spec_object ("block-progression-dimension-maximum",
			  _("Block Progression Dimension Maximum"),
			  _("Block Progression Dimension Maximum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER,
     g_param_spec_object ("border",
			  _("Border"),
			  _("Border property"),
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
     PROP_BORDER_AFTER_PRECEDENCE,
     g_param_spec_object ("border-after-precedence",
			  _("Border After Precedence"),
			  _("Border After Precedence property"),
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
     PROP_BORDER_BEFORE_PRECEDENCE,
     g_param_spec_object ("border-before-precedence",
			  _("Border Before Precedence"),
			  _("Border Before Precedence property"),
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
     PROP_BORDER_BOTTOM,
     g_param_spec_object ("border-bottom",
			  _("Border Bottom"),
			  _("Border Bottom property"),
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
     PROP_BORDER_COLLAPSE,
     g_param_spec_object ("border-collapse",
			  _("Border Collapse"),
			  _("Border Collapse property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_COLOR,
     g_param_spec_object ("border-color",
			  _("Border Color"),
			  _("Border Color property"),
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
     PROP_BORDER_END_PRECEDENCE,
     g_param_spec_object ("border-end-precedence",
			  _("Border End Precedence"),
			  _("Border End Precedence property"),
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
     PROP_BORDER_LEFT,
     g_param_spec_object ("border-left",
			  _("Border Left"),
			  _("Border Left property"),
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
     PROP_BORDER_RIGHT,
     g_param_spec_object ("border-right",
			  _("Border Right"),
			  _("Border Right property"),
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
     PROP_BORDER_SEPARATION,
     g_param_spec_object ("border-separation",
			  _("Border Separation"),
			  _("Border Separation property"),
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
     PROP_BORDER_START_PRECEDENCE,
     g_param_spec_object ("border-start-precedence",
			  _("Border Start Precedence"),
			  _("Border Start Precedence property"),
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
     PROP_BORDER_STYLE,
     g_param_spec_object ("border-style",
			  _("Border Style"),
			  _("Border Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_BORDER_TOP,
     g_param_spec_object ("border-top",
			  _("Border Top"),
			  _("Border Top property"),
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
     PROP_BORDER_WIDTH,
     g_param_spec_object ("border-width",
			  _("Border Width"),
			  _("Border Width property"),
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
     PROP_CHARACTER,
     g_param_spec_object ("character",
			  _("Character"),
			  _("Character property"),
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
     PROP_COLOR,
     g_param_spec_object ("color",
			  _("Color"),
			  _("Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_COLUMN_NUMBER,
     g_param_spec_object ("column-number",
			  _("Column Number"),
			  _("Column Number property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_COLUMN_WIDTH,
     g_param_spec_object ("column-width",
			  _("Column Width"),
			  _("Column Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_CONTENT_HEIGHT,
     g_param_spec_object ("content-height",
			  _("Content Height"),
			  _("Content Height property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_CONTENT_TYPE,
     g_param_spec_object ("content-type",
			  _("Content Type"),
			  _("Content Type property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_CONTENT_WIDTH,
     g_param_spec_object ("content-width",
			  _("Content Width"),
			  _("Content Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_DIRECTION,
     g_param_spec_object ("direction",
			  _("Direction"),
			  _("Direction property"),
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
     PROP_DOMINANT_BASELINE,
     g_param_spec_object ("dominant-baseline",
			  _("Dominant Baseline"),
			  _("Dominant Baseline property"),
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
     PROP_EXTENT,
     g_param_spec_object ("extent",
			  _("Extent"),
			  _("Extent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FLOW_NAME,
     g_param_spec_object ("flow-name",
			  _("Flow Name"),
			  _("Flow Name property"),
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
     PROP_FORMAT,
     g_param_spec_object ("format",
			  _("Format"),
			  _("Format property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_GROUPING_SEPARATOR,
     g_param_spec_object ("grouping-separator",
			  _("Grouping Separator"),
			  _("Grouping Separator property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_GROUPING_SIZE,
     g_param_spec_object ("grouping-size",
			  _("Grouping Size"),
			  _("Grouping Size property"),
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
     PROP_INLINE_PROGRESSION_DIMENSION_MINIMUM,
     g_param_spec_object ("inline-progression-dimension-minimum",
			  _("Inline Progression Dimension Minimum"),
			  _("Inline Progression Dimension Minimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_INLINE_PROGRESSION_DIMENSION_OPTIMUM,
     g_param_spec_object ("inline-progression-dimension-optimum",
			  _("Inline Progression Dimension Optimum"),
			  _("Inline Progression Dimension Optimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_INLINE_PROGRESSION_DIMENSION_MAXIMUM,
     g_param_spec_object ("inline-progression-dimension-maximum",
			  _("Inline Progression Dimension Maximum"),
			  _("Inline Progression Dimension Maximum property"),
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
     PROP_LETTER_VALUE,
     g_param_spec_object ("letter-value",
			  _("Letter Value"),
			  _("Letter Value property"),
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
     PROP_MARGIN,
     g_param_spec_object ("margin",
			  _("Margin"),
			  _("Margin property"),
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
     PROP_MASTER_NAME,
     g_param_spec_object ("master-name",
			  _("Master Name"),
			  _("Master Name property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MASTER_REFERENCE,
     g_param_spec_object ("master-reference",
			  _("Master Reference"),
			  _("Master Reference property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MEDIA_USAGE,
     g_param_spec_object ("media-usage",
			  _("Media Usage"),
			  _("Media Usage property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_NUMBER_COLUMNS_REPEATED,
     g_param_spec_object ("number-columns-repeated",
			  _("Number Columns Repeated"),
			  _("Number Columns Repeated property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_NUMBER_COLUMNS_SPANNED,
     g_param_spec_object ("number-columns-spanned",
			  _("Number Columns Spanned"),
			  _("Number Columns Spanned property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_NUMBER_ROWS_SPANNED,
     g_param_spec_object ("number-rows-spanned",
			  _("Number Rows Spanned"),
			  _("Number Rows Spanned property"),
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
     PROP_OVERFLOW,
     g_param_spec_object ("overflow",
			  _("Overflow"),
			  _("Overflow property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING,
     g_param_spec_object ("padding",
			  _("Padding"),
			  _("Padding property"),
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
     PROP_PADDING_AFTER_LENGTH,
     g_param_spec_object ("padding-after-length",
			  _("Padding After Length"),
			  _("Padding After Length property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_AFTER_CONDITY,
     g_param_spec_object ("padding-after-conditionality",
			  _("Padding After Conditionality"),
			  _("Padding After Conditionality property"),
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
     PROP_PADDING_BEFORE_LENGTH,
     g_param_spec_object ("padding-before-length",
			  _("Padding Before Length"),
			  _("Padding Before Length property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_BEFORE_CONDITY,
     g_param_spec_object ("padding-before-conditionality",
			  _("Padding Before Conditionality"),
			  _("Padding Before Conditionality property"),
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
     PROP_PADDING_END_LENGTH,
     g_param_spec_object ("padding-end-length",
			  _("Padding End Length"),
			  _("Padding End Length property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_END_CONDITY,
     g_param_spec_object ("padding-end-conditionality",
			  _("Padding End Conditionality"),
			  _("Padding End Conditionality property"),
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
     PROP_PADDING_START_LENGTH,
     g_param_spec_object ("padding-start-length",
			  _("Padding Start Length"),
			  _("Padding Start Length property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PADDING_START_CONDITY,
     g_param_spec_object ("padding-start-conditionality",
			  _("Padding Start Conditionality"),
			  _("Padding Start Conditionality property"),
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
     PROP_PAGE_HEIGHT,
     g_param_spec_object ("page-height",
			  _("Page Height"),
			  _("Page Height property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PAGE_WIDTH,
     g_param_spec_object ("page-width",
			  _("Page Width"),
			  _("Page Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PROVISIONAL_DISTANCE_BETWEEN_STARTS,
     g_param_spec_object ("provisional-distance-between-starts",
			  _("Provisional Distance Between Starts"),
			  _("Provisional Distance Between Starts property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PROVISIONAL_LABEL_SEPARATION,
     g_param_spec_object ("provisional-label-separation",
			  _("Provisional Label Separation"),
			  _("Provisional Label Separation property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_REF_ID,
     g_param_spec_object ("ref-id",
			  _("Ref Id"),
			  _("Ref Id property"),
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
     PROP_ROLE,
     g_param_spec_object ("role",
			  _("Role"),
			  _("Role property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SCALING,
     g_param_spec_object ("scaling",
			  _("Scaling"),
			  _("Scaling property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SCALING_METHOD,
     g_param_spec_object ("scaling-method",
			  _("Scaling Method"),
			  _("Scaling Method property"),
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
     PROP_SPACE_AFTER_MINIMUM,
     g_param_spec_object ("space-after-minimum",
			  _("Space After Minimum"),
			  _("Space After Minimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_AFTER_OPTIMUM,
     g_param_spec_object ("space-after-optimum",
			  _("Space After Optimum"),
			  _("Space After Optimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_AFTER_MAXIMUM,
     g_param_spec_object ("space-after-maximum",
			  _("Space After Maximum"),
			  _("Space After Maximum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_AFTER_PRECEDENCE,
     g_param_spec_object ("space-after-precedence",
			  _("Space After Precedence"),
			  _("Space After Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_AFTER_CONDITY,
     g_param_spec_object ("space-after-conditionality",
			  _("Space After Conditionality"),
			  _("Space After Conditionality property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
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
     PROP_SPACE_BEFORE_MINIMUM,
     g_param_spec_object ("space-before-minimum",
			  _("Space Before Minimum"),
			  _("Space Before Minimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_BEFORE_OPTIMUM,
     g_param_spec_object ("space-before-optimum",
			  _("Space Before Optimum"),
			  _("Space Before Optimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_BEFORE_MAXIMUM,
     g_param_spec_object ("space-before-maximum",
			  _("Space Before Maximum"),
			  _("Space Before Maximum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_BEFORE_PRECEDENCE,
     g_param_spec_object ("space-before-precedence",
			  _("Space Before Precedence"),
			  _("Space Before Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_BEFORE_CONDITY,
     g_param_spec_object ("space-before-conditionality",
			  _("Space Before Conditionality"),
			  _("Space Before Conditionality property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
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
     PROP_SPACE_END_MINIMUM,
     g_param_spec_object ("space-end-minimum",
			  _("Space End Minimum"),
			  _("Space End Minimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_END_OPTIMUM,
     g_param_spec_object ("space-end-optimum",
			  _("Space End Optimum"),
			  _("Space End Optimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_END_MAXIMUM,
     g_param_spec_object ("space-end-maximum",
			  _("Space End Maximum"),
			  _("Space End Maximum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_END_PRECEDENCE,
     g_param_spec_object ("space-end-precedence",
			  _("Space End Precedence"),
			  _("Space End Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_END_CONDITY,
     g_param_spec_object ("space-end-conditionality",
			  _("Space End Conditionality"),
			  _("Space End Conditionality property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
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
     PROP_SPACE_START_MINIMUM,
     g_param_spec_object ("space-start-minimum",
			  _("Space Start Minimum"),
			  _("Space Start Minimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_START_OPTIMUM,
     g_param_spec_object ("space-start-optimum",
			  _("Space Start Optimum"),
			  _("Space Start Optimum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_START_MAXIMUM,
     g_param_spec_object ("space-start-maximum",
			  _("Space Start Maximum"),
			  _("Space Start Maximum property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_START_PRECEDENCE,
     g_param_spec_object ("space-start-precedence",
			  _("Space Start Precedence"),
			  _("Space Start Precedence property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_START_CONDITY,
     g_param_spec_object ("space-start-conditionality",
			  _("Space Start Conditionality"),
			  _("Space Start Conditionality property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_WRITABLE));
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
     PROP_SRC,
     g_param_spec_object ("src",
			  _("Src"),
			  _("Src property"),
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
     PROP_TABLE_LAYOUT,
     g_param_spec_object ("table-layout",
			  _("Table Layout"),
			  _("Table Layout property"),
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
     PROP_UNICODE_BIDI,
     g_param_spec_object ("unicode-bidi",
			  _("Unicode Bidi"),
			  _("Unicode Bidi property"),
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
 * fo_context_finalize:
 * @object: #FoContext object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoContext.
 **/
void
fo_context_finalize (GObject *object)
{
  FoContext *context;

  context = FO_CONTEXT (object);

  g_object_unref (context->alignment_adjust);
  g_object_unref (context->alignment_baseline);
  g_object_unref (context->background_color);
  g_object_unref (context->background_image);
  g_object_unref (context->baseline_shift);
  g_object_unref (context->block_progression_dimension);
  g_object_unref (context->block_progression_dimension_minimum);
  g_object_unref (context->block_progression_dimension_optimum);
  g_object_unref (context->block_progression_dimension_maximum);
  g_object_unref (context->border);
  g_object_unref (context->border_after_color);
  g_object_unref (context->border_after_precedence);
  g_object_unref (context->border_after_style);
  g_object_unref (context->border_after_width);
  g_object_unref (context->border_before_color);
  g_object_unref (context->border_before_precedence);
  g_object_unref (context->border_before_style);
  g_object_unref (context->border_before_width);
  g_object_unref (context->border_bottom);
  g_object_unref (context->border_bottom_color);
  g_object_unref (context->border_bottom_style);
  g_object_unref (context->border_bottom_width);
  g_object_unref (context->border_collapse);
  g_object_unref (context->border_color);
  g_object_unref (context->border_end_color);
  g_object_unref (context->border_end_precedence);
  g_object_unref (context->border_end_style);
  g_object_unref (context->border_end_width);
  g_object_unref (context->border_left);
  g_object_unref (context->border_left_color);
  g_object_unref (context->border_left_style);
  g_object_unref (context->border_left_width);
  g_object_unref (context->border_right);
  g_object_unref (context->border_right_color);
  g_object_unref (context->border_right_style);
  g_object_unref (context->border_right_width);
  g_object_unref (context->border_separation);
  g_object_unref (context->border_start_color);
  g_object_unref (context->border_start_precedence);
  g_object_unref (context->border_start_style);
  g_object_unref (context->border_start_width);
  g_object_unref (context->border_style);
  g_object_unref (context->border_top);
  g_object_unref (context->border_top_color);
  g_object_unref (context->border_top_style);
  g_object_unref (context->border_top_width);
  g_object_unref (context->border_width);
  g_object_unref (context->break_after);
  g_object_unref (context->break_before);
  g_object_unref (context->character);
  g_object_unref (context->clip);
  g_object_unref (context->color);
  g_object_unref (context->column_number);
  g_object_unref (context->column_width);
  g_object_unref (context->content_height);
  g_object_unref (context->content_type);
  g_object_unref (context->content_width);
  g_object_unref (context->direction);
  g_object_unref (context->display_align);
  g_object_unref (context->dominant_baseline);
  g_object_unref (context->end_indent);
  g_object_unref (context->extent);
  g_object_unref (context->flow_name);
  g_object_unref (context->font_family);
  g_object_unref (context->font_size);
  g_object_unref (context->font_stretch);
  g_object_unref (context->font_style);
  g_object_unref (context->font_variant);
  g_object_unref (context->font_weight);
  g_object_unref (context->format);
  g_object_unref (context->grouping_separator);
  g_object_unref (context->grouping_size);
  g_object_unref (context->height);
  g_object_unref (context->id);
  g_object_unref (context->inline_progression_dimension);
  g_object_unref (context->inline_progression_dimension_minimum);
  g_object_unref (context->inline_progression_dimension_optimum);
  g_object_unref (context->inline_progression_dimension_maximum);
  g_object_unref (context->keep_together);
  g_object_unref (context->keep_together_within_column);
  g_object_unref (context->keep_together_within_line);
  g_object_unref (context->keep_together_within_page);
  g_object_unref (context->keep_with_next);
  g_object_unref (context->keep_with_next_within_column);
  g_object_unref (context->keep_with_next_within_line);
  g_object_unref (context->keep_with_next_within_page);
  g_object_unref (context->keep_with_previous);
  g_object_unref (context->keep_with_previous_within_column);
  g_object_unref (context->keep_with_previous_within_line);
  g_object_unref (context->keep_with_previous_within_page);
  g_object_unref (context->letter_value);
  g_object_unref (context->line_height);
  g_object_unref (context->line_stacking_strategy);
  g_object_unref (context->linefeed_treatment);
  g_object_unref (context->margin);
  g_object_unref (context->margin_bottom);
  g_object_unref (context->margin_left);
  g_object_unref (context->margin_right);
  g_object_unref (context->margin_top);
  g_object_unref (context->master_name);
  g_object_unref (context->master_reference);
  g_object_unref (context->media_usage);
  g_object_unref (context->number_columns_repeated);
  g_object_unref (context->number_columns_spanned);
  g_object_unref (context->number_rows_spanned);
  g_object_unref (context->orphans);
  g_object_unref (context->overflow);
  g_object_unref (context->padding);
  g_object_unref (context->padding_after);
  g_object_unref (context->padding_after_length);
  g_object_unref (context->padding_after_condity);
  g_object_unref (context->padding_before);
  g_object_unref (context->padding_before_length);
  g_object_unref (context->padding_before_condity);
  g_object_unref (context->padding_bottom);
  g_object_unref (context->padding_end);
  g_object_unref (context->padding_end_length);
  g_object_unref (context->padding_end_condity);
  g_object_unref (context->padding_left);
  g_object_unref (context->padding_right);
  g_object_unref (context->padding_start);
  g_object_unref (context->padding_start_length);
  g_object_unref (context->padding_start_condity);
  g_object_unref (context->padding_top);
  g_object_unref (context->page_height);
  g_object_unref (context->page_width);
  g_object_unref (context->provisional_distance_between_starts);
  g_object_unref (context->provisional_label_separation);
  g_object_unref (context->ref_id);
  g_object_unref (context->region_name);
  g_object_unref (context->role);
  g_object_unref (context->scaling);
  g_object_unref (context->scaling_method);
  g_object_unref (context->score_spaces);
  g_object_unref (context->source_document);
  g_object_unref (context->space_after);
  g_object_unref (context->space_after_minimum);
  g_object_unref (context->space_after_optimum);
  g_object_unref (context->space_after_maximum);
  g_object_unref (context->space_after_precedence);
  g_object_unref (context->space_after_condity);
  g_object_unref (context->space_before);
  g_object_unref (context->space_before_minimum);
  g_object_unref (context->space_before_optimum);
  g_object_unref (context->space_before_maximum);
  g_object_unref (context->space_before_precedence);
  g_object_unref (context->space_before_condity);
  g_object_unref (context->space_end);
  g_object_unref (context->space_end_minimum);
  g_object_unref (context->space_end_optimum);
  g_object_unref (context->space_end_maximum);
  g_object_unref (context->space_end_precedence);
  g_object_unref (context->space_end_condity);
  g_object_unref (context->space_start);
  g_object_unref (context->space_start_minimum);
  g_object_unref (context->space_start_optimum);
  g_object_unref (context->space_start_maximum);
  g_object_unref (context->space_start_precedence);
  g_object_unref (context->space_start_condity);
  g_object_unref (context->span);
  g_object_unref (context->src);
  g_object_unref (context->start_indent);
  g_object_unref (context->table_layout);
  g_object_unref (context->text_align);
  g_object_unref (context->text_indent);
  g_object_unref (context->unicode_bidi);
  g_object_unref (context->white_space_collapse);
  g_object_unref (context->white_space_treatment);
  g_object_unref (context->widows);
  g_object_unref (context->width);
  g_object_unref (context->wrap_option);
  g_object_unref (context->writing_mode);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_context_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoContext.
 **/
void
fo_context_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue    *value,
                         GParamSpec      *pspec)
{
  FoContext *fo_context;

  fo_context = FO_CONTEXT (object);

  switch (prop_id)
    {
    case PROP_ALIGNMENT_ADJUST:
      fo_context_set_alignment_adjust (fo_context, g_value_get_object (value));
      break;
    case PROP_ALIGNMENT_BASELINE:
      fo_context_set_alignment_baseline (fo_context, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_COLOR:
      fo_context_set_background_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BACKGROUND_IMAGE:
      fo_context_set_background_image (fo_context, g_value_get_object (value));
      break;
    case PROP_BASELINE_SHIFT:
      fo_context_set_baseline_shift (fo_context, g_value_get_object (value));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION:
      fo_context_set_block_progression_dimension (fo_context, g_value_get_object (value));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION_MINIMUM:
      fo_context_set_block_progression_dimension_minimum (fo_context, g_value_get_object (value));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION_OPTIMUM:
      fo_context_set_block_progression_dimension_optimum (fo_context, g_value_get_object (value));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION_MAXIMUM:
      fo_context_set_block_progression_dimension_maximum (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER:
      fo_context_set_border (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_COLOR:
      fo_context_set_border_after_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_PRECEDENCE:
      fo_context_set_border_after_precedence (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_STYLE:
      fo_context_set_border_after_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      fo_context_set_border_after_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      fo_context_set_border_before_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_PRECEDENCE:
      fo_context_set_border_before_precedence (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      fo_context_set_border_before_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      fo_context_set_border_before_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM:
      fo_context_set_border_bottom (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      fo_context_set_border_bottom_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      fo_context_set_border_bottom_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      fo_context_set_border_bottom_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_COLLAPSE:
      fo_context_set_border_collapse (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_COLOR:
      fo_context_set_border_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_END_COLOR:
      fo_context_set_border_end_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_END_PRECEDENCE:
      fo_context_set_border_end_precedence (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_END_STYLE:
      fo_context_set_border_end_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_END_WIDTH:
      fo_context_set_border_end_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT:
      fo_context_set_border_left (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_COLOR:
      fo_context_set_border_left_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_STYLE:
      fo_context_set_border_left_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      fo_context_set_border_left_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT:
      fo_context_set_border_right (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      fo_context_set_border_right_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      fo_context_set_border_right_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      fo_context_set_border_right_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_SEPARATION:
      fo_context_set_border_separation (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_START_COLOR:
      fo_context_set_border_start_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_START_PRECEDENCE:
      fo_context_set_border_start_precedence (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_START_STYLE:
      fo_context_set_border_start_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_START_WIDTH:
      fo_context_set_border_start_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_STYLE:
      fo_context_set_border_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP:
      fo_context_set_border_top (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_COLOR:
      fo_context_set_border_top_color (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_STYLE:
      fo_context_set_border_top_style (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_TOP_WIDTH:
      fo_context_set_border_top_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BORDER_WIDTH:
      fo_context_set_border_width (fo_context, g_value_get_object (value));
      break;
    case PROP_BREAK_AFTER:
      fo_context_set_break_after (fo_context, g_value_get_object (value));
      break;
    case PROP_BREAK_BEFORE:
      fo_context_set_break_before (fo_context, g_value_get_object (value));
      break;
    case PROP_CHARACTER:
      fo_context_set_character (fo_context, g_value_get_object (value));
      break;
    case PROP_CLIP:
      fo_context_set_clip (fo_context, g_value_get_object (value));
      break;
    case PROP_COLOR:
      fo_context_set_color (fo_context, g_value_get_object (value));
      break;
    case PROP_COLUMN_NUMBER:
      fo_context_set_column_number (fo_context, g_value_get_object (value));
      break;
    case PROP_COLUMN_WIDTH:
      fo_context_set_column_width (fo_context, g_value_get_object (value));
      break;
    case PROP_CONTENT_HEIGHT:
      fo_context_set_content_height (fo_context, g_value_get_object (value));
      break;
    case PROP_CONTENT_TYPE:
      fo_context_set_content_type (fo_context, g_value_get_object (value));
      break;
    case PROP_CONTENT_WIDTH:
      fo_context_set_content_width (fo_context, g_value_get_object (value));
      break;
    case PROP_DIRECTION:
      fo_context_set_direction (fo_context, g_value_get_object (value));
      break;
    case PROP_DISPLAY_ALIGN:
      fo_context_set_display_align (fo_context, g_value_get_object (value));
      break;
    case PROP_DOMINANT_BASELINE:
      fo_context_set_dominant_baseline (fo_context, g_value_get_object (value));
      break;
    case PROP_END_INDENT:
      fo_context_set_end_indent (fo_context, g_value_get_object (value));
      break;
    case PROP_EXTENT:
      fo_context_set_extent (fo_context, g_value_get_object (value));
      break;
    case PROP_FLOW_NAME:
      fo_context_set_flow_name (fo_context, g_value_get_object (value));
      break;
    case PROP_FONT_FAMILY:
      fo_context_set_font_family (fo_context, g_value_get_object (value));
      break;
    case PROP_FONT_SIZE:
      fo_context_set_font_size (fo_context, g_value_get_object (value));
      break;
    case PROP_FONT_STRETCH:
      fo_context_set_font_stretch (fo_context, g_value_get_object (value));
      break;
    case PROP_FONT_STYLE:
      fo_context_set_font_style (fo_context, g_value_get_object (value));
      break;
    case PROP_FONT_VARIANT:
      fo_context_set_font_variant (fo_context, g_value_get_object (value));
      break;
    case PROP_FONT_WEIGHT:
      fo_context_set_font_weight (fo_context, g_value_get_object (value));
      break;
    case PROP_FORMAT:
      fo_context_set_format (fo_context, g_value_get_object (value));
      break;
    case PROP_GROUPING_SEPARATOR:
      fo_context_set_grouping_separator (fo_context, g_value_get_object (value));
      break;
    case PROP_GROUPING_SIZE:
      fo_context_set_grouping_size (fo_context, g_value_get_object (value));
      break;
    case PROP_HEIGHT:
      fo_context_set_height (fo_context, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_context_set_id (fo_context, g_value_get_object (value));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION:
      fo_context_set_inline_progression_dimension (fo_context, g_value_get_object (value));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION_MINIMUM:
      fo_context_set_inline_progression_dimension_minimum (fo_context, g_value_get_object (value));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION_OPTIMUM:
      fo_context_set_inline_progression_dimension_optimum (fo_context, g_value_get_object (value));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION_MAXIMUM:
      fo_context_set_inline_progression_dimension_maximum (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER:
      fo_context_set_keep_together (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      fo_context_set_keep_together_within_column (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      fo_context_set_keep_together_within_line (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      fo_context_set_keep_together_within_page (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT:
      fo_context_set_keep_with_next (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      fo_context_set_keep_with_next_within_column (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      fo_context_set_keep_with_next_within_line (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      fo_context_set_keep_with_next_within_page (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      fo_context_set_keep_with_previous (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      fo_context_set_keep_with_previous_within_column (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      fo_context_set_keep_with_previous_within_line (fo_context, g_value_get_object (value));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      fo_context_set_keep_with_previous_within_page (fo_context, g_value_get_object (value));
      break;
    case PROP_LETTER_VALUE:
      fo_context_set_letter_value (fo_context, g_value_get_object (value));
      break;
    case PROP_LINE_HEIGHT:
      fo_context_set_line_height (fo_context, g_value_get_object (value));
      break;
    case PROP_LINE_STACKING_STRATEGY:
      fo_context_set_line_stacking_strategy (fo_context, g_value_get_object (value));
      break;
    case PROP_LINEFEED_TREATMENT:
      fo_context_set_linefeed_treatment (fo_context, g_value_get_object (value));
      break;
    case PROP_MARGIN:
      fo_context_set_margin (fo_context, g_value_get_object (value));
      break;
    case PROP_MARGIN_BOTTOM:
      fo_context_set_margin_bottom (fo_context, g_value_get_object (value));
      break;
    case PROP_MARGIN_LEFT:
      fo_context_set_margin_left (fo_context, g_value_get_object (value));
      break;
    case PROP_MARGIN_RIGHT:
      fo_context_set_margin_right (fo_context, g_value_get_object (value));
      break;
    case PROP_MARGIN_TOP:
      fo_context_set_margin_top (fo_context, g_value_get_object (value));
      break;
    case PROP_MASTER_NAME:
      fo_context_set_master_name (fo_context, g_value_get_object (value));
      break;
    case PROP_MASTER_REFERENCE:
      fo_context_set_master_reference (fo_context, g_value_get_object (value));
      break;
    case PROP_MEDIA_USAGE:
      fo_context_set_media_usage (fo_context, g_value_get_object (value));
      break;
    case PROP_NUMBER_COLUMNS_REPEATED:
      fo_context_set_number_columns_repeated (fo_context, g_value_get_object (value));
      break;
    case PROP_NUMBER_COLUMNS_SPANNED:
      fo_context_set_number_columns_spanned (fo_context, g_value_get_object (value));
      break;
    case PROP_NUMBER_ROWS_SPANNED:
      fo_context_set_number_rows_spanned (fo_context, g_value_get_object (value));
      break;
    case PROP_ORPHANS:
      fo_context_set_orphans (fo_context, g_value_get_object (value));
      break;
    case PROP_OVERFLOW:
      fo_context_set_overflow (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING:
      fo_context_set_padding (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER:
      fo_context_set_padding_after (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER_LENGTH:
      fo_context_set_padding_after_length (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_AFTER_CONDITY:
      fo_context_set_padding_after_condity (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE:
      fo_context_set_padding_before (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE_LENGTH:
      fo_context_set_padding_before_length (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_BEFORE_CONDITY:
      fo_context_set_padding_before_condity (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_BOTTOM:
      fo_context_set_padding_bottom (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_END:
      fo_context_set_padding_end (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_END_LENGTH:
      fo_context_set_padding_end_length (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_END_CONDITY:
      fo_context_set_padding_end_condity (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_LEFT:
      fo_context_set_padding_left (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_RIGHT:
      fo_context_set_padding_right (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_START:
      fo_context_set_padding_start (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_START_LENGTH:
      fo_context_set_padding_start_length (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_START_CONDITY:
      fo_context_set_padding_start_condity (fo_context, g_value_get_object (value));
      break;
    case PROP_PADDING_TOP:
      fo_context_set_padding_top (fo_context, g_value_get_object (value));
      break;
    case PROP_PAGE_HEIGHT:
      fo_context_set_page_height (fo_context, g_value_get_object (value));
      break;
    case PROP_PAGE_WIDTH:
      fo_context_set_page_width (fo_context, g_value_get_object (value));
      break;
    case PROP_PROVISIONAL_DISTANCE_BETWEEN_STARTS:
      fo_context_set_provisional_distance_between_starts (fo_context, g_value_get_object (value));
      break;
    case PROP_PROVISIONAL_LABEL_SEPARATION:
      fo_context_set_provisional_label_separation (fo_context, g_value_get_object (value));
      break;
    case PROP_REF_ID:
      fo_context_set_ref_id (fo_context, g_value_get_object (value));
      break;
    case PROP_REGION_NAME:
      fo_context_set_region_name (fo_context, g_value_get_object (value));
      break;
    case PROP_ROLE:
      fo_context_set_role (fo_context, g_value_get_object (value));
      break;
    case PROP_SCALING:
      fo_context_set_scaling (fo_context, g_value_get_object (value));
      break;
    case PROP_SCALING_METHOD:
      fo_context_set_scaling_method (fo_context, g_value_get_object (value));
      break;
    case PROP_SCORE_SPACES:
      fo_context_set_score_spaces (fo_context, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_context_set_source_document (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER:
      fo_context_set_space_after (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER_MINIMUM:
      fo_context_set_space_after_minimum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER_OPTIMUM:
      fo_context_set_space_after_optimum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER_MAXIMUM:
      fo_context_set_space_after_maximum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER_PRECEDENCE:
      fo_context_set_space_after_precedence (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER_CONDITY:
      fo_context_set_space_after_condity (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE:
      fo_context_set_space_before (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE_MINIMUM:
      fo_context_set_space_before_minimum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE_OPTIMUM:
      fo_context_set_space_before_optimum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE_MAXIMUM:
      fo_context_set_space_before_maximum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE_PRECEDENCE:
      fo_context_set_space_before_precedence (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE_CONDITY:
      fo_context_set_space_before_condity (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_END:
      fo_context_set_space_end (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_END_MINIMUM:
      fo_context_set_space_end_minimum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_END_OPTIMUM:
      fo_context_set_space_end_optimum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_END_MAXIMUM:
      fo_context_set_space_end_maximum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_END_PRECEDENCE:
      fo_context_set_space_end_precedence (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_END_CONDITY:
      fo_context_set_space_end_condity (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_START:
      fo_context_set_space_start (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_START_MINIMUM:
      fo_context_set_space_start_minimum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_START_OPTIMUM:
      fo_context_set_space_start_optimum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_START_MAXIMUM:
      fo_context_set_space_start_maximum (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_START_PRECEDENCE:
      fo_context_set_space_start_precedence (fo_context, g_value_get_object (value));
      break;
    case PROP_SPACE_START_CONDITY:
      fo_context_set_space_start_condity (fo_context, g_value_get_object (value));
      break;
    case PROP_SPAN:
      fo_context_set_span (fo_context, g_value_get_object (value));
      break;
    case PROP_SRC:
      fo_context_set_src (fo_context, g_value_get_object (value));
      break;
    case PROP_START_INDENT:
      fo_context_set_start_indent (fo_context, g_value_get_object (value));
      break;
    case PROP_TABLE_LAYOUT:
      fo_context_set_table_layout (fo_context, g_value_get_object (value));
      break;
    case PROP_TEXT_ALIGN:
      fo_context_set_text_align (fo_context, g_value_get_object (value));
      break;
    case PROP_TEXT_INDENT:
      fo_context_set_text_indent (fo_context, g_value_get_object (value));
      break;
    case PROP_UNICODE_BIDI:
      fo_context_set_unicode_bidi (fo_context, g_value_get_object (value));
      break;
    case PROP_WHITE_SPACE_COLLAPSE:
      fo_context_set_white_space_collapse (fo_context, g_value_get_object (value));
      break;
    case PROP_WHITE_SPACE_TREATMENT:
      fo_context_set_white_space_treatment (fo_context, g_value_get_object (value));
      break;
    case PROP_WIDOWS:
      fo_context_set_widows (fo_context, g_value_get_object (value));
      break;
    case PROP_WIDTH:
      fo_context_set_width (fo_context, g_value_get_object (value));
      break;
    case PROP_WRAP_OPTION:
      fo_context_set_wrap_option (fo_context, g_value_get_object (value));
      break;
    case PROP_WRITING_MODE:
      fo_context_set_writing_mode (fo_context, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_context_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoContext.
 **/
void
fo_context_get_property (GObject         *object,
                         guint            prop_id,
                         GValue          *value,
                         GParamSpec      *pspec)
{
  FoContext *fo_context;

  fo_context = FO_CONTEXT (object);

  switch (prop_id)
    {
    case PROP_ALIGNMENT_ADJUST:
      g_value_set_object (value, G_OBJECT (fo_context_get_alignment_adjust (fo_context)));
      break;
    case PROP_ALIGNMENT_BASELINE:
      g_value_set_object (value, G_OBJECT (fo_context_get_alignment_baseline (fo_context)));
      break;
    case PROP_BACKGROUND_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_background_color (fo_context)));
      break;
    case PROP_BACKGROUND_IMAGE:
      g_value_set_object (value, G_OBJECT (fo_context_get_background_image (fo_context)));
      break;
    case PROP_BASELINE_SHIFT:
      g_value_set_object (value, G_OBJECT (fo_context_get_baseline_shift (fo_context)));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION:
      g_value_set_object (value, G_OBJECT (fo_context_get_block_progression_dimension (fo_context)));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION_MINIMUM:
      g_value_set_object (value, G_OBJECT (fo_context_get_block_progression_dimension_minimum (fo_context)));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION_OPTIMUM:
      g_value_set_object (value, G_OBJECT (fo_context_get_block_progression_dimension_optimum (fo_context)));
      break;
    case PROP_BLOCK_PROGRESSION_DIMENSION_MAXIMUM:
      g_value_set_object (value, G_OBJECT (fo_context_get_block_progression_dimension_maximum (fo_context)));
      break;
    case PROP_BORDER:
      g_value_set_object (value, G_OBJECT (fo_context_get_border (fo_context)));
      break;
    case PROP_BORDER_AFTER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_after_color (fo_context)));
      break;
    case PROP_BORDER_AFTER_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_after_precedence (fo_context)));
      break;
    case PROP_BORDER_AFTER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_after_style (fo_context)));
      break;
    case PROP_BORDER_AFTER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_after_width (fo_context)));
      break;
    case PROP_BORDER_BEFORE_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_before_color (fo_context)));
      break;
    case PROP_BORDER_BEFORE_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_before_precedence (fo_context)));
      break;
    case PROP_BORDER_BEFORE_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_before_style (fo_context)));
      break;
    case PROP_BORDER_BEFORE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_before_width (fo_context)));
      break;
    case PROP_BORDER_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_bottom (fo_context)));
      break;
    case PROP_BORDER_BOTTOM_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_bottom_color (fo_context)));
      break;
    case PROP_BORDER_BOTTOM_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_bottom_style (fo_context)));
      break;
    case PROP_BORDER_BOTTOM_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_bottom_width (fo_context)));
      break;
    case PROP_BORDER_COLLAPSE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_collapse (fo_context)));
      break;
    case PROP_BORDER_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_color (fo_context)));
      break;
    case PROP_BORDER_END_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_end_color (fo_context)));
      break;
    case PROP_BORDER_END_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_end_precedence (fo_context)));
      break;
    case PROP_BORDER_END_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_end_style (fo_context)));
      break;
    case PROP_BORDER_END_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_end_width (fo_context)));
      break;
    case PROP_BORDER_LEFT:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_left (fo_context)));
      break;
    case PROP_BORDER_LEFT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_left_color (fo_context)));
      break;
    case PROP_BORDER_LEFT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_left_style (fo_context)));
      break;
    case PROP_BORDER_LEFT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_left_width (fo_context)));
      break;
    case PROP_BORDER_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_right (fo_context)));
      break;
    case PROP_BORDER_RIGHT_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_right_color (fo_context)));
      break;
    case PROP_BORDER_RIGHT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_right_style (fo_context)));
      break;
    case PROP_BORDER_RIGHT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_right_width (fo_context)));
      break;
    case PROP_BORDER_SEPARATION:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_separation (fo_context)));
      break;
    case PROP_BORDER_START_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_start_color (fo_context)));
      break;
    case PROP_BORDER_START_PRECEDENCE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_start_precedence (fo_context)));
      break;
    case PROP_BORDER_START_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_start_style (fo_context)));
      break;
    case PROP_BORDER_START_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_start_width (fo_context)));
      break;
    case PROP_BORDER_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_style (fo_context)));
      break;
    case PROP_BORDER_TOP:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_top (fo_context)));
      break;
    case PROP_BORDER_TOP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_top_color (fo_context)));
      break;
    case PROP_BORDER_TOP_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_top_style (fo_context)));
      break;
    case PROP_BORDER_TOP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_top_width (fo_context)));
      break;
    case PROP_BORDER_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_border_width (fo_context)));
      break;
    case PROP_BREAK_AFTER:
      g_value_set_object (value, G_OBJECT (fo_context_get_break_after (fo_context)));
      break;
    case PROP_BREAK_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_context_get_break_before (fo_context)));
      break;
    case PROP_CHARACTER:
      g_value_set_object (value, G_OBJECT (fo_context_get_character (fo_context)));
      break;
    case PROP_CLIP:
      g_value_set_object (value, G_OBJECT (fo_context_get_clip (fo_context)));
      break;
    case PROP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_color (fo_context)));
      break;
    case PROP_COLUMN_NUMBER:
      g_value_set_object (value, G_OBJECT (fo_context_get_column_number (fo_context)));
      break;
    case PROP_COLUMN_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_column_width (fo_context)));
      break;
    case PROP_CONTENT_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_context_get_content_height (fo_context)));
      break;
    case PROP_CONTENT_TYPE:
      g_value_set_object (value, G_OBJECT (fo_context_get_content_type (fo_context)));
      break;
    case PROP_CONTENT_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_content_width (fo_context)));
      break;
    case PROP_DIRECTION:
      g_value_set_object (value, G_OBJECT (fo_context_get_direction (fo_context)));
      break;
    case PROP_DISPLAY_ALIGN:
      g_value_set_object (value, G_OBJECT (fo_context_get_display_align (fo_context)));
      break;
    case PROP_DOMINANT_BASELINE:
      g_value_set_object (value, G_OBJECT (fo_context_get_dominant_baseline (fo_context)));
      break;
    case PROP_END_INDENT:
      g_value_set_object (value, G_OBJECT (fo_context_get_end_indent (fo_context)));
      break;
    case PROP_EXTENT:
      g_value_set_object (value, G_OBJECT (fo_context_get_extent (fo_context)));
      break;
    case PROP_FLOW_NAME:
      g_value_set_object (value, G_OBJECT (fo_context_get_flow_name (fo_context)));
      break;
    case PROP_FONT_FAMILY:
      g_value_set_object (value, G_OBJECT (fo_context_get_font_family (fo_context)));
      break;
    case PROP_FONT_SIZE:
      g_value_set_object (value, G_OBJECT (fo_context_get_font_size (fo_context)));
      break;
    case PROP_FONT_STRETCH:
      g_value_set_object (value, G_OBJECT (fo_context_get_font_stretch (fo_context)));
      break;
    case PROP_FONT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_font_style (fo_context)));
      break;
    case PROP_FONT_VARIANT:
      g_value_set_object (value, G_OBJECT (fo_context_get_font_variant (fo_context)));
      break;
    case PROP_FONT_WEIGHT:
      g_value_set_object (value, G_OBJECT (fo_context_get_font_weight (fo_context)));
      break;
    case PROP_FORMAT:
      g_value_set_object (value, G_OBJECT (fo_context_get_format (fo_context)));
      break;
    case PROP_GROUPING_SEPARATOR:
      g_value_set_object (value, G_OBJECT (fo_context_get_grouping_separator (fo_context)));
      break;
    case PROP_GROUPING_SIZE:
      g_value_set_object (value, G_OBJECT (fo_context_get_grouping_size (fo_context)));
      break;
    case PROP_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_context_get_height (fo_context)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_context_get_id (fo_context)));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION:
      g_value_set_object (value, G_OBJECT (fo_context_get_inline_progression_dimension (fo_context)));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION_MINIMUM:
      g_value_set_object (value, G_OBJECT (fo_context_get_inline_progression_dimension_minimum (fo_context)));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION_OPTIMUM:
      g_value_set_object (value, G_OBJECT (fo_context_get_inline_progression_dimension_optimum (fo_context)));
      break;
    case PROP_INLINE_PROGRESSION_DIMENSION_MAXIMUM:
      g_value_set_object (value, G_OBJECT (fo_context_get_inline_progression_dimension_maximum (fo_context)));
      break;
    case PROP_KEEP_TOGETHER:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_together (fo_context)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_together_within_column (fo_context)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_together_within_line (fo_context)));
      break;
    case PROP_KEEP_TOGETHER_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_together_within_page (fo_context)));
      break;
    case PROP_KEEP_WITH_NEXT:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_with_next (fo_context)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_with_next_within_column (fo_context)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_with_next_within_line (fo_context)));
      break;
    case PROP_KEEP_WITH_NEXT_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_with_next_within_page (fo_context)));
      break;
    case PROP_KEEP_WITH_PREVIOUS:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_with_previous (fo_context)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_COLUMN:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_with_previous_within_column (fo_context)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_LINE:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_with_previous_within_line (fo_context)));
      break;
    case PROP_KEEP_WITH_PREVIOUS_WITHIN_PAGE:
      g_value_set_object (value, G_OBJECT (fo_context_get_keep_with_previous_within_page (fo_context)));
      break;
    case PROP_LETTER_VALUE:
      g_value_set_object (value, G_OBJECT (fo_context_get_letter_value (fo_context)));
      break;
    case PROP_LINE_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_context_get_line_height (fo_context)));
      break;
    case PROP_LINE_STACKING_STRATEGY:
      g_value_set_object (value, G_OBJECT (fo_context_get_line_stacking_strategy (fo_context)));
      break;
    case PROP_LINEFEED_TREATMENT:
      g_value_set_object (value, G_OBJECT (fo_context_get_linefeed_treatment (fo_context)));
      break;
    case PROP_MARGIN:
      g_value_set_object (value, G_OBJECT (fo_context_get_margin (fo_context)));
      break;
    case PROP_MARGIN_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_context_get_margin_bottom (fo_context)));
      break;
    case PROP_MARGIN_LEFT:
      g_value_set_object (value, G_OBJECT (fo_context_get_margin_left (fo_context)));
      break;
    case PROP_MARGIN_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_context_get_margin_right (fo_context)));
      break;
    case PROP_MARGIN_TOP:
      g_value_set_object (value, G_OBJECT (fo_context_get_margin_top (fo_context)));
      break;
    case PROP_MASTER_NAME:
      g_value_set_object (value, G_OBJECT (fo_context_get_master_name (fo_context)));
      break;
    case PROP_MASTER_REFERENCE:
      g_value_set_object (value, G_OBJECT (fo_context_get_master_reference (fo_context)));
      break;
    case PROP_MEDIA_USAGE:
      g_value_set_object (value, G_OBJECT (fo_context_get_media_usage (fo_context)));
      break;
    case PROP_NUMBER_COLUMNS_REPEATED:
      g_value_set_object (value, G_OBJECT (fo_context_get_number_columns_repeated (fo_context)));
      break;
    case PROP_NUMBER_COLUMNS_SPANNED:
      g_value_set_object (value, G_OBJECT (fo_context_get_number_columns_spanned (fo_context)));
      break;
    case PROP_NUMBER_ROWS_SPANNED:
      g_value_set_object (value, G_OBJECT (fo_context_get_number_rows_spanned (fo_context)));
      break;
    case PROP_ORPHANS:
      g_value_set_object (value, G_OBJECT (fo_context_get_orphans (fo_context)));
      break;
    case PROP_OVERFLOW:
      g_value_set_object (value, G_OBJECT (fo_context_get_overflow (fo_context)));
      break;
    case PROP_PADDING:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding (fo_context)));
      break;
    case PROP_PADDING_AFTER:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_after (fo_context)));
      break;
    case PROP_PADDING_AFTER_LENGTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_after_length (fo_context)));
      break;
    case PROP_PADDING_AFTER_CONDITY:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_after_condity (fo_context)));
      break;
    case PROP_PADDING_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_before (fo_context)));
      break;
    case PROP_PADDING_BEFORE_LENGTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_before_length (fo_context)));
      break;
    case PROP_PADDING_BEFORE_CONDITY:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_before_condity (fo_context)));
      break;
    case PROP_PADDING_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_bottom (fo_context)));
      break;
    case PROP_PADDING_END:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_end (fo_context)));
      break;
    case PROP_PADDING_END_LENGTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_end_length (fo_context)));
      break;
    case PROP_PADDING_END_CONDITY:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_end_condity (fo_context)));
      break;
    case PROP_PADDING_LEFT:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_left (fo_context)));
      break;
    case PROP_PADDING_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_right (fo_context)));
      break;
    case PROP_PADDING_START:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_start (fo_context)));
      break;
    case PROP_PADDING_START_LENGTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_start_length (fo_context)));
      break;
    case PROP_PADDING_START_CONDITY:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_start_condity (fo_context)));
      break;
    case PROP_PADDING_TOP:
      g_value_set_object (value, G_OBJECT (fo_context_get_padding_top (fo_context)));
      break;
    case PROP_PAGE_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_context_get_page_height (fo_context)));
      break;
    case PROP_PAGE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_page_width (fo_context)));
      break;
    case PROP_PROVISIONAL_DISTANCE_BETWEEN_STARTS:
      g_value_set_object (value, G_OBJECT (fo_context_get_provisional_distance_between_starts (fo_context)));
      break;
    case PROP_PROVISIONAL_LABEL_SEPARATION:
      g_value_set_object (value, G_OBJECT (fo_context_get_provisional_label_separation (fo_context)));
      break;
    case PROP_REF_ID:
      g_value_set_object (value, G_OBJECT (fo_context_get_ref_id (fo_context)));
      break;
    case PROP_REGION_NAME:
      g_value_set_object (value, G_OBJECT (fo_context_get_region_name (fo_context)));
      break;
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_context_get_role (fo_context)));
      break;
    case PROP_SCALING:
      g_value_set_object (value, G_OBJECT (fo_context_get_scaling (fo_context)));
      break;
    case PROP_SCALING_METHOD:
      g_value_set_object (value, G_OBJECT (fo_context_get_scaling_method (fo_context)));
      break;
    case PROP_SCORE_SPACES:
      g_value_set_object (value, G_OBJECT (fo_context_get_score_spaces (fo_context)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_context_get_source_document (fo_context)));
      break;
    case PROP_SPACE_AFTER:
      g_value_set_object (value, G_OBJECT (fo_context_get_space_after (fo_context)));
      break;
    case PROP_SPACE_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_context_get_space_before (fo_context)));
      break;
    case PROP_SPACE_END:
      g_value_set_object (value, G_OBJECT (fo_context_get_space_end (fo_context)));
      break;
    case PROP_SPACE_START:
      g_value_set_object (value, G_OBJECT (fo_context_get_space_start (fo_context)));
      break;
    case PROP_SPAN:
      g_value_set_object (value, G_OBJECT (fo_context_get_span (fo_context)));
      break;
    case PROP_SRC:
      g_value_set_object (value, G_OBJECT (fo_context_get_src (fo_context)));
      break;
    case PROP_START_INDENT:
      g_value_set_object (value, G_OBJECT (fo_context_get_start_indent (fo_context)));
      break;
    case PROP_TABLE_LAYOUT:
      g_value_set_object (value, G_OBJECT (fo_context_get_table_layout (fo_context)));
      break;
    case PROP_TEXT_ALIGN:
      g_value_set_object (value, G_OBJECT (fo_context_get_text_align (fo_context)));
      break;
    case PROP_TEXT_INDENT:
      g_value_set_object (value, G_OBJECT (fo_context_get_text_indent (fo_context)));
      break;
    case PROP_UNICODE_BIDI:
      g_value_set_object (value, G_OBJECT (fo_context_get_unicode_bidi (fo_context)));
      break;
    case PROP_WHITE_SPACE_COLLAPSE:
      g_value_set_object (value, G_OBJECT (fo_context_get_white_space_collapse (fo_context)));
      break;
    case PROP_WHITE_SPACE_TREATMENT:
      g_value_set_object (value, G_OBJECT (fo_context_get_white_space_treatment (fo_context)));
      break;
    case PROP_WIDOWS:
      g_value_set_object (value, G_OBJECT (fo_context_get_widows (fo_context)));
      break;
    case PROP_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_context_get_width (fo_context)));
      break;
    case PROP_WRAP_OPTION:
      g_value_set_object (value, G_OBJECT (fo_context_get_wrap_option (fo_context)));
      break;
    case PROP_WRITING_MODE:
      g_value_set_object (value, G_OBJECT (fo_context_get_writing_mode (fo_context)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_context_new:
 * 
 * Creates a new #FoContext initialized to default value.
 * 
 * Return value: the new #FoContext.
 **/
FoContext *
fo_context_new (void)
{
  FoContext *context;

  context = FO_CONTEXT (g_object_new (fo_context_get_type (),
                        NULL));
  
  return context;
}

/**
 * fo_context_get_alignment_adjust:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "alignment-adjust" property of @fo_context.
 *
 * Return value: The "alignment-adjust" property value.
**/
FoProperty *
fo_context_get_alignment_adjust (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->alignment_adjust;
}

/**
 * fo_context_set_alignment_adjust:
 * @fo_context: The #FoContext object.
 * @new_alignment_adjust: The new "alignment-adjust" property value.
 * 
 * Sets the "alignment-adjust" property of @fo_context to @new_alignment_adjust.
 **/
void
fo_context_set_alignment_adjust (FoContext *fo_context,
		         FoProperty *new_alignment_adjust)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_alignment_adjust == NULL || FO_IS_PROPERTY_ALIGNMENT_ADJUST (new_alignment_adjust));

  if (new_alignment_adjust != NULL)
    {
      g_object_ref (new_alignment_adjust);
    }
  if (fo_context->alignment_adjust != NULL)
    {
      g_object_unref (fo_context->alignment_adjust);
    }
  fo_context->alignment_adjust = new_alignment_adjust;
  /*g_object_notify (G_OBJECT (fo_context), "alignment-adjust");*/
}

/**
 * fo_context_get_alignment_baseline:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "alignment-baseline" property of @fo_context.
 *
 * Return value: The "alignment-baseline" property value.
**/
FoProperty *
fo_context_get_alignment_baseline (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->alignment_baseline;
}

/**
 * fo_context_set_alignment_baseline:
 * @fo_context: The #FoContext object.
 * @new_alignment_baseline: The new "alignment-baseline" property value.
 * 
 * Sets the "alignment-baseline" property of @fo_context to @new_alignment_baseline.
 **/
void
fo_context_set_alignment_baseline (FoContext *fo_context,
		         FoProperty *new_alignment_baseline)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_alignment_baseline == NULL || FO_IS_PROPERTY_ALIGNMENT_BASELINE (new_alignment_baseline));

  if (new_alignment_baseline != NULL)
    {
      g_object_ref (new_alignment_baseline);
    }
  if (fo_context->alignment_baseline != NULL)
    {
      g_object_unref (fo_context->alignment_baseline);
    }
  fo_context->alignment_baseline = new_alignment_baseline;
  /*g_object_notify (G_OBJECT (fo_context), "alignment-baseline");*/
}

/**
 * fo_context_get_background_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "background-color" property of @fo_context.
 *
 * Return value: The "background-color" property value.
**/
FoProperty *
fo_context_get_background_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->background_color;
}

/**
 * fo_context_set_background_color:
 * @fo_context: The #FoContext object.
 * @new_background_color: The new "background-color" property value.
 * 
 * Sets the "background-color" property of @fo_context to @new_background_color.
 **/
void
fo_context_set_background_color (FoContext *fo_context,
		         FoProperty *new_background_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_background_color == NULL || FO_IS_PROPERTY_BACKGROUND_COLOR (new_background_color));

  if (new_background_color != NULL)
    {
      g_object_ref (new_background_color);
    }
  if (fo_context->background_color != NULL)
    {
      g_object_unref (fo_context->background_color);
    }
  fo_context->background_color = new_background_color;
  /*g_object_notify (G_OBJECT (fo_context), "background-color");*/
}

/**
 * fo_context_get_background_image:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "background-image" property of @fo_context.
 *
 * Return value: The "background-image" property value.
**/
FoProperty *
fo_context_get_background_image (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->background_image;
}

/**
 * fo_context_set_background_image:
 * @fo_context: The #FoContext object.
 * @new_background_image: The new "background-image" property value.
 * 
 * Sets the "background-image" property of @fo_context to @new_background_image.
 **/
void
fo_context_set_background_image (FoContext *fo_context,
		         FoProperty *new_background_image)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_background_image == NULL || FO_IS_PROPERTY_BACKGROUND_IMAGE (new_background_image));

  if (new_background_image != NULL)
    {
      g_object_ref (new_background_image);
    }
  if (fo_context->background_image != NULL)
    {
      g_object_unref (fo_context->background_image);
    }
  fo_context->background_image = new_background_image;
  /*g_object_notify (G_OBJECT (fo_context), "background-image");*/
}

/**
 * fo_context_get_baseline_shift:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "baseline-shift" property of @fo_context.
 *
 * Return value: The "baseline-shift" property value.
**/
FoProperty *
fo_context_get_baseline_shift (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->baseline_shift;
}

/**
 * fo_context_set_baseline_shift:
 * @fo_context: The #FoContext object.
 * @new_baseline_shift: The new "baseline-shift" property value.
 * 
 * Sets the "baseline-shift" property of @fo_context to @new_baseline_shift.
 **/
void
fo_context_set_baseline_shift (FoContext *fo_context,
		         FoProperty *new_baseline_shift)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_baseline_shift == NULL || FO_IS_PROPERTY_BASELINE_SHIFT (new_baseline_shift));

  if (new_baseline_shift != NULL)
    {
      g_object_ref (new_baseline_shift);
    }
  if (fo_context->baseline_shift != NULL)
    {
      g_object_unref (fo_context->baseline_shift);
    }
  fo_context->baseline_shift = new_baseline_shift;
  /*g_object_notify (G_OBJECT (fo_context), "baseline-shift");*/
}

/**
 * fo_context_get_block_progression_dimension:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "block-progression-dimension" property of @fo_context.
 *
 * Return value: The "block-progression-dimension" property value.
**/
FoProperty *
fo_context_get_block_progression_dimension (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->block_progression_dimension;
}

/**
 * fo_context_set_block_progression_dimension:
 * @fo_context: The #FoContext object.
 * @new_block_progression_dimension: The new "block-progression-dimension" property value.
 * 
 * Sets the "block-progression-dimension" property of @fo_context to @new_block_progression_dimension.
 **/
void
fo_context_set_block_progression_dimension (FoContext *fo_context,
		         FoProperty *new_block_progression_dimension)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_block_progression_dimension == NULL || FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION (new_block_progression_dimension));

  if (new_block_progression_dimension != NULL)
    {
      g_object_ref (new_block_progression_dimension);
    }
  if (fo_context->block_progression_dimension != NULL)
    {
      g_object_unref (fo_context->block_progression_dimension);
    }
  fo_context->block_progression_dimension = new_block_progression_dimension;
  /*g_object_notify (G_OBJECT (fo_context), "block-progression-dimension");*/
}

/**
 * fo_context_get_block_progression_dimension_minimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "block-progression-dimension-minimum" property of @fo_context.
 *
 * Return value: The "block-progression-dimension-minimum" property value.
**/
FoProperty *
fo_context_get_block_progression_dimension_minimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->block_progression_dimension_minimum;
}

/**
 * fo_context_set_block_progression_dimension_minimum:
 * @fo_context: The #FoContext object.
 * @new_block_progression_dimension_minimum: The new "block-progression-dimension-minimum" property value.
 * 
 * Sets the "block-progression-dimension-minimum" property of @fo_context to @new_block_progression_dimension_minimum.
 **/
void
fo_context_set_block_progression_dimension_minimum (FoContext *fo_context,
		         FoProperty *new_block_progression_dimension_minimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_block_progression_dimension_minimum == NULL || FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM (new_block_progression_dimension_minimum));

  if (new_block_progression_dimension_minimum != NULL)
    {
      g_object_ref (new_block_progression_dimension_minimum);
    }
  if (fo_context->block_progression_dimension_minimum != NULL)
    {
      g_object_unref (fo_context->block_progression_dimension_minimum);
    }
  fo_context->block_progression_dimension_minimum = new_block_progression_dimension_minimum;
  /*g_object_notify (G_OBJECT (fo_context), "block-progression-dimension-minimum");*/
}

/**
 * fo_context_get_block_progression_dimension_optimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "block-progression-dimension-optimum" property of @fo_context.
 *
 * Return value: The "block-progression-dimension-optimum" property value.
**/
FoProperty *
fo_context_get_block_progression_dimension_optimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->block_progression_dimension_optimum;
}

/**
 * fo_context_set_block_progression_dimension_optimum:
 * @fo_context: The #FoContext object.
 * @new_block_progression_dimension_optimum: The new "block-progression-dimension-optimum" property value.
 * 
 * Sets the "block-progression-dimension-optimum" property of @fo_context to @new_block_progression_dimension_optimum.
 **/
void
fo_context_set_block_progression_dimension_optimum (FoContext *fo_context,
		         FoProperty *new_block_progression_dimension_optimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_block_progression_dimension_optimum == NULL || FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_OPTIMUM (new_block_progression_dimension_optimum));

  if (new_block_progression_dimension_optimum != NULL)
    {
      g_object_ref (new_block_progression_dimension_optimum);
    }
  if (fo_context->block_progression_dimension_optimum != NULL)
    {
      g_object_unref (fo_context->block_progression_dimension_optimum);
    }
  fo_context->block_progression_dimension_optimum = new_block_progression_dimension_optimum;
  /*g_object_notify (G_OBJECT (fo_context), "block-progression-dimension-optimum");*/
}

/**
 * fo_context_get_block_progression_dimension_maximum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "block-progression-dimension-maximum" property of @fo_context.
 *
 * Return value: The "block-progression-dimension-maximum" property value.
**/
FoProperty *
fo_context_get_block_progression_dimension_maximum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->block_progression_dimension_maximum;
}

/**
 * fo_context_set_block_progression_dimension_maximum:
 * @fo_context: The #FoContext object.
 * @new_block_progression_dimension_maximum: The new "block-progression-dimension-maximum" property value.
 * 
 * Sets the "block-progression-dimension-maximum" property of @fo_context to @new_block_progression_dimension_maximum.
 **/
void
fo_context_set_block_progression_dimension_maximum (FoContext *fo_context,
		         FoProperty *new_block_progression_dimension_maximum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_block_progression_dimension_maximum == NULL || FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM (new_block_progression_dimension_maximum));

  if (new_block_progression_dimension_maximum != NULL)
    {
      g_object_ref (new_block_progression_dimension_maximum);
    }
  if (fo_context->block_progression_dimension_maximum != NULL)
    {
      g_object_unref (fo_context->block_progression_dimension_maximum);
    }
  fo_context->block_progression_dimension_maximum = new_block_progression_dimension_maximum;
  /*g_object_notify (G_OBJECT (fo_context), "block-progression-dimension-maximum");*/
}

/**
 * fo_context_get_border:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border" property of @fo_context.
 *
 * Return value: The "border" property value.
**/
FoProperty *
fo_context_get_border (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border;
}

/**
 * fo_context_set_border:
 * @fo_context: The #FoContext object.
 * @new_border: The new "border" property value.
 * 
 * Sets the "border" property of @fo_context to @new_border.
 **/
void
fo_context_set_border (FoContext *fo_context,
		         FoProperty *new_border)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border == NULL || FO_IS_PROPERTY_BORDER (new_border));

  if (new_border != NULL)
    {
      g_object_ref (new_border);
    }
  if (fo_context->border != NULL)
    {
      g_object_unref (fo_context->border);
    }
  fo_context->border = new_border;
  /*g_object_notify (G_OBJECT (fo_context), "border");*/
}

/**
 * fo_context_get_border_after_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-after-color" property of @fo_context.
 *
 * Return value: The "border-after-color" property value.
**/
FoProperty *
fo_context_get_border_after_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_after_color;
}

/**
 * fo_context_set_border_after_color:
 * @fo_context: The #FoContext object.
 * @new_border_after_color: The new "border-after-color" property value.
 * 
 * Sets the "border-after-color" property of @fo_context to @new_border_after_color.
 **/
void
fo_context_set_border_after_color (FoContext *fo_context,
		         FoProperty *new_border_after_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_after_color == NULL || FO_IS_PROPERTY_BORDER_AFTER_COLOR (new_border_after_color));

  if (new_border_after_color != NULL)
    {
      g_object_ref (new_border_after_color);
    }
  if (fo_context->border_after_color != NULL)
    {
      g_object_unref (fo_context->border_after_color);
    }
  fo_context->border_after_color = new_border_after_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-after-color");*/
}

/**
 * fo_context_get_border_after_precedence:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-after-precedence" property of @fo_context.
 *
 * Return value: The "border-after-precedence" property value.
**/
FoProperty *
fo_context_get_border_after_precedence (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_after_precedence;
}

/**
 * fo_context_set_border_after_precedence:
 * @fo_context: The #FoContext object.
 * @new_border_after_precedence: The new "border-after-precedence" property value.
 * 
 * Sets the "border-after-precedence" property of @fo_context to @new_border_after_precedence.
 **/
void
fo_context_set_border_after_precedence (FoContext *fo_context,
		         FoProperty *new_border_after_precedence)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_after_precedence == NULL || FO_IS_PROPERTY_BORDER_AFTER_PRECEDENCE (new_border_after_precedence));

  if (new_border_after_precedence != NULL)
    {
      g_object_ref (new_border_after_precedence);
    }
  if (fo_context->border_after_precedence != NULL)
    {
      g_object_unref (fo_context->border_after_precedence);
    }
  fo_context->border_after_precedence = new_border_after_precedence;
  /*g_object_notify (G_OBJECT (fo_context), "border-after-precedence");*/
}

/**
 * fo_context_get_border_after_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-after-style" property of @fo_context.
 *
 * Return value: The "border-after-style" property value.
**/
FoProperty *
fo_context_get_border_after_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_after_style;
}

/**
 * fo_context_set_border_after_style:
 * @fo_context: The #FoContext object.
 * @new_border_after_style: The new "border-after-style" property value.
 * 
 * Sets the "border-after-style" property of @fo_context to @new_border_after_style.
 **/
void
fo_context_set_border_after_style (FoContext *fo_context,
		         FoProperty *new_border_after_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_after_style == NULL || FO_IS_PROPERTY_BORDER_AFTER_STYLE (new_border_after_style));

  if (new_border_after_style != NULL)
    {
      g_object_ref (new_border_after_style);
    }
  if (fo_context->border_after_style != NULL)
    {
      g_object_unref (fo_context->border_after_style);
    }
  fo_context->border_after_style = new_border_after_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-after-style");*/
}

/**
 * fo_context_get_border_after_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-after-width" property of @fo_context.
 *
 * Return value: The "border-after-width" property value.
**/
FoProperty *
fo_context_get_border_after_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_after_width;
}

/**
 * fo_context_set_border_after_width:
 * @fo_context: The #FoContext object.
 * @new_border_after_width: The new "border-after-width" property value.
 * 
 * Sets the "border-after-width" property of @fo_context to @new_border_after_width.
 **/
void
fo_context_set_border_after_width (FoContext *fo_context,
		         FoProperty *new_border_after_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_after_width == NULL || FO_IS_PROPERTY_BORDER_AFTER_WIDTH (new_border_after_width));

  if (new_border_after_width != NULL)
    {
      g_object_ref (new_border_after_width);
    }
  if (fo_context->border_after_width != NULL)
    {
      g_object_unref (fo_context->border_after_width);
    }
  fo_context->border_after_width = new_border_after_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-after-width");*/
}

/**
 * fo_context_get_border_before_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-before-color" property of @fo_context.
 *
 * Return value: The "border-before-color" property value.
**/
FoProperty *
fo_context_get_border_before_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_before_color;
}

/**
 * fo_context_set_border_before_color:
 * @fo_context: The #FoContext object.
 * @new_border_before_color: The new "border-before-color" property value.
 * 
 * Sets the "border-before-color" property of @fo_context to @new_border_before_color.
 **/
void
fo_context_set_border_before_color (FoContext *fo_context,
		         FoProperty *new_border_before_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_before_color == NULL || FO_IS_PROPERTY_BORDER_BEFORE_COLOR (new_border_before_color));

  if (new_border_before_color != NULL)
    {
      g_object_ref (new_border_before_color);
    }
  if (fo_context->border_before_color != NULL)
    {
      g_object_unref (fo_context->border_before_color);
    }
  fo_context->border_before_color = new_border_before_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-before-color");*/
}

/**
 * fo_context_get_border_before_precedence:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-before-precedence" property of @fo_context.
 *
 * Return value: The "border-before-precedence" property value.
**/
FoProperty *
fo_context_get_border_before_precedence (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_before_precedence;
}

/**
 * fo_context_set_border_before_precedence:
 * @fo_context: The #FoContext object.
 * @new_border_before_precedence: The new "border-before-precedence" property value.
 * 
 * Sets the "border-before-precedence" property of @fo_context to @new_border_before_precedence.
 **/
void
fo_context_set_border_before_precedence (FoContext *fo_context,
		         FoProperty *new_border_before_precedence)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_before_precedence == NULL || FO_IS_PROPERTY_BORDER_BEFORE_PRECEDENCE (new_border_before_precedence));

  if (new_border_before_precedence != NULL)
    {
      g_object_ref (new_border_before_precedence);
    }
  if (fo_context->border_before_precedence != NULL)
    {
      g_object_unref (fo_context->border_before_precedence);
    }
  fo_context->border_before_precedence = new_border_before_precedence;
  /*g_object_notify (G_OBJECT (fo_context), "border-before-precedence");*/
}

/**
 * fo_context_get_border_before_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-before-style" property of @fo_context.
 *
 * Return value: The "border-before-style" property value.
**/
FoProperty *
fo_context_get_border_before_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_before_style;
}

/**
 * fo_context_set_border_before_style:
 * @fo_context: The #FoContext object.
 * @new_border_before_style: The new "border-before-style" property value.
 * 
 * Sets the "border-before-style" property of @fo_context to @new_border_before_style.
 **/
void
fo_context_set_border_before_style (FoContext *fo_context,
		         FoProperty *new_border_before_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_before_style == NULL || FO_IS_PROPERTY_BORDER_BEFORE_STYLE (new_border_before_style));

  if (new_border_before_style != NULL)
    {
      g_object_ref (new_border_before_style);
    }
  if (fo_context->border_before_style != NULL)
    {
      g_object_unref (fo_context->border_before_style);
    }
  fo_context->border_before_style = new_border_before_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-before-style");*/
}

/**
 * fo_context_get_border_before_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-before-width" property of @fo_context.
 *
 * Return value: The "border-before-width" property value.
**/
FoProperty *
fo_context_get_border_before_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_before_width;
}

/**
 * fo_context_set_border_before_width:
 * @fo_context: The #FoContext object.
 * @new_border_before_width: The new "border-before-width" property value.
 * 
 * Sets the "border-before-width" property of @fo_context to @new_border_before_width.
 **/
void
fo_context_set_border_before_width (FoContext *fo_context,
		         FoProperty *new_border_before_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_before_width == NULL || FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (new_border_before_width));

  if (new_border_before_width != NULL)
    {
      g_object_ref (new_border_before_width);
    }
  if (fo_context->border_before_width != NULL)
    {
      g_object_unref (fo_context->border_before_width);
    }
  fo_context->border_before_width = new_border_before_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-before-width");*/
}

/**
 * fo_context_get_border_bottom:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-bottom" property of @fo_context.
 *
 * Return value: The "border-bottom" property value.
**/
FoProperty *
fo_context_get_border_bottom (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_bottom;
}

/**
 * fo_context_set_border_bottom:
 * @fo_context: The #FoContext object.
 * @new_border_bottom: The new "border-bottom" property value.
 * 
 * Sets the "border-bottom" property of @fo_context to @new_border_bottom.
 **/
void
fo_context_set_border_bottom (FoContext *fo_context,
		         FoProperty *new_border_bottom)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_bottom == NULL || FO_IS_PROPERTY_BORDER_BOTTOM (new_border_bottom));

  if (new_border_bottom != NULL)
    {
      g_object_ref (new_border_bottom);
    }
  if (fo_context->border_bottom != NULL)
    {
      g_object_unref (fo_context->border_bottom);
    }
  fo_context->border_bottom = new_border_bottom;
  /*g_object_notify (G_OBJECT (fo_context), "border-bottom");*/
}

/**
 * fo_context_get_border_bottom_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-bottom-color" property of @fo_context.
 *
 * Return value: The "border-bottom-color" property value.
**/
FoProperty *
fo_context_get_border_bottom_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_bottom_color;
}

/**
 * fo_context_set_border_bottom_color:
 * @fo_context: The #FoContext object.
 * @new_border_bottom_color: The new "border-bottom-color" property value.
 * 
 * Sets the "border-bottom-color" property of @fo_context to @new_border_bottom_color.
 **/
void
fo_context_set_border_bottom_color (FoContext *fo_context,
		         FoProperty *new_border_bottom_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_bottom_color == NULL || FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (new_border_bottom_color));

  if (new_border_bottom_color != NULL)
    {
      g_object_ref (new_border_bottom_color);
    }
  if (fo_context->border_bottom_color != NULL)
    {
      g_object_unref (fo_context->border_bottom_color);
    }
  fo_context->border_bottom_color = new_border_bottom_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-bottom-color");*/
}

/**
 * fo_context_get_border_bottom_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-bottom-style" property of @fo_context.
 *
 * Return value: The "border-bottom-style" property value.
**/
FoProperty *
fo_context_get_border_bottom_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_bottom_style;
}

/**
 * fo_context_set_border_bottom_style:
 * @fo_context: The #FoContext object.
 * @new_border_bottom_style: The new "border-bottom-style" property value.
 * 
 * Sets the "border-bottom-style" property of @fo_context to @new_border_bottom_style.
 **/
void
fo_context_set_border_bottom_style (FoContext *fo_context,
		         FoProperty *new_border_bottom_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_bottom_style == NULL || FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (new_border_bottom_style));

  if (new_border_bottom_style != NULL)
    {
      g_object_ref (new_border_bottom_style);
    }
  if (fo_context->border_bottom_style != NULL)
    {
      g_object_unref (fo_context->border_bottom_style);
    }
  fo_context->border_bottom_style = new_border_bottom_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-bottom-style");*/
}

/**
 * fo_context_get_border_bottom_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-bottom-width" property of @fo_context.
 *
 * Return value: The "border-bottom-width" property value.
**/
FoProperty *
fo_context_get_border_bottom_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_bottom_width;
}

/**
 * fo_context_set_border_bottom_width:
 * @fo_context: The #FoContext object.
 * @new_border_bottom_width: The new "border-bottom-width" property value.
 * 
 * Sets the "border-bottom-width" property of @fo_context to @new_border_bottom_width.
 **/
void
fo_context_set_border_bottom_width (FoContext *fo_context,
		         FoProperty *new_border_bottom_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_bottom_width == NULL || FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (new_border_bottom_width));

  if (new_border_bottom_width != NULL)
    {
      g_object_ref (new_border_bottom_width);
    }
  if (fo_context->border_bottom_width != NULL)
    {
      g_object_unref (fo_context->border_bottom_width);
    }
  fo_context->border_bottom_width = new_border_bottom_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-bottom-width");*/
}

/**
 * fo_context_get_border_collapse:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-collapse" property of @fo_context.
 *
 * Return value: The "border-collapse" property value.
**/
FoProperty *
fo_context_get_border_collapse (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_collapse;
}

/**
 * fo_context_set_border_collapse:
 * @fo_context: The #FoContext object.
 * @new_border_collapse: The new "border-collapse" property value.
 * 
 * Sets the "border-collapse" property of @fo_context to @new_border_collapse.
 **/
void
fo_context_set_border_collapse (FoContext *fo_context,
		         FoProperty *new_border_collapse)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_collapse == NULL || FO_IS_PROPERTY_BORDER_COLLAPSE (new_border_collapse));

  if (new_border_collapse != NULL)
    {
      g_object_ref (new_border_collapse);
    }
  if (fo_context->border_collapse != NULL)
    {
      g_object_unref (fo_context->border_collapse);
    }
  fo_context->border_collapse = new_border_collapse;
  /*g_object_notify (G_OBJECT (fo_context), "border-collapse");*/
}

/**
 * fo_context_get_border_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-color" property of @fo_context.
 *
 * Return value: The "border-color" property value.
**/
FoProperty *
fo_context_get_border_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_color;
}

/**
 * fo_context_set_border_color:
 * @fo_context: The #FoContext object.
 * @new_border_color: The new "border-color" property value.
 * 
 * Sets the "border-color" property of @fo_context to @new_border_color.
 **/
void
fo_context_set_border_color (FoContext *fo_context,
		         FoProperty *new_border_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_color == NULL || FO_IS_PROPERTY_BORDER_COLOR (new_border_color));

  if (new_border_color != NULL)
    {
      g_object_ref (new_border_color);
    }
  if (fo_context->border_color != NULL)
    {
      g_object_unref (fo_context->border_color);
    }
  fo_context->border_color = new_border_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-color");*/
}

/**
 * fo_context_get_border_end_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-end-color" property of @fo_context.
 *
 * Return value: The "border-end-color" property value.
**/
FoProperty *
fo_context_get_border_end_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_end_color;
}

/**
 * fo_context_set_border_end_color:
 * @fo_context: The #FoContext object.
 * @new_border_end_color: The new "border-end-color" property value.
 * 
 * Sets the "border-end-color" property of @fo_context to @new_border_end_color.
 **/
void
fo_context_set_border_end_color (FoContext *fo_context,
		         FoProperty *new_border_end_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_end_color == NULL || FO_IS_PROPERTY_BORDER_END_COLOR (new_border_end_color));

  if (new_border_end_color != NULL)
    {
      g_object_ref (new_border_end_color);
    }
  if (fo_context->border_end_color != NULL)
    {
      g_object_unref (fo_context->border_end_color);
    }
  fo_context->border_end_color = new_border_end_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-end-color");*/
}

/**
 * fo_context_get_border_end_precedence:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-end-precedence" property of @fo_context.
 *
 * Return value: The "border-end-precedence" property value.
**/
FoProperty *
fo_context_get_border_end_precedence (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_end_precedence;
}

/**
 * fo_context_set_border_end_precedence:
 * @fo_context: The #FoContext object.
 * @new_border_end_precedence: The new "border-end-precedence" property value.
 * 
 * Sets the "border-end-precedence" property of @fo_context to @new_border_end_precedence.
 **/
void
fo_context_set_border_end_precedence (FoContext *fo_context,
		         FoProperty *new_border_end_precedence)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_end_precedence == NULL || FO_IS_PROPERTY_BORDER_END_PRECEDENCE (new_border_end_precedence));

  if (new_border_end_precedence != NULL)
    {
      g_object_ref (new_border_end_precedence);
    }
  if (fo_context->border_end_precedence != NULL)
    {
      g_object_unref (fo_context->border_end_precedence);
    }
  fo_context->border_end_precedence = new_border_end_precedence;
  /*g_object_notify (G_OBJECT (fo_context), "border-end-precedence");*/
}

/**
 * fo_context_get_border_end_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-end-style" property of @fo_context.
 *
 * Return value: The "border-end-style" property value.
**/
FoProperty *
fo_context_get_border_end_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_end_style;
}

/**
 * fo_context_set_border_end_style:
 * @fo_context: The #FoContext object.
 * @new_border_end_style: The new "border-end-style" property value.
 * 
 * Sets the "border-end-style" property of @fo_context to @new_border_end_style.
 **/
void
fo_context_set_border_end_style (FoContext *fo_context,
		         FoProperty *new_border_end_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_end_style == NULL || FO_IS_PROPERTY_BORDER_END_STYLE (new_border_end_style));

  if (new_border_end_style != NULL)
    {
      g_object_ref (new_border_end_style);
    }
  if (fo_context->border_end_style != NULL)
    {
      g_object_unref (fo_context->border_end_style);
    }
  fo_context->border_end_style = new_border_end_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-end-style");*/
}

/**
 * fo_context_get_border_end_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-end-width" property of @fo_context.
 *
 * Return value: The "border-end-width" property value.
**/
FoProperty *
fo_context_get_border_end_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_end_width;
}

/**
 * fo_context_set_border_end_width:
 * @fo_context: The #FoContext object.
 * @new_border_end_width: The new "border-end-width" property value.
 * 
 * Sets the "border-end-width" property of @fo_context to @new_border_end_width.
 **/
void
fo_context_set_border_end_width (FoContext *fo_context,
		         FoProperty *new_border_end_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_end_width == NULL || FO_IS_PROPERTY_BORDER_END_WIDTH (new_border_end_width));

  if (new_border_end_width != NULL)
    {
      g_object_ref (new_border_end_width);
    }
  if (fo_context->border_end_width != NULL)
    {
      g_object_unref (fo_context->border_end_width);
    }
  fo_context->border_end_width = new_border_end_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-end-width");*/
}

/**
 * fo_context_get_border_left:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-left" property of @fo_context.
 *
 * Return value: The "border-left" property value.
**/
FoProperty *
fo_context_get_border_left (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_left;
}

/**
 * fo_context_set_border_left:
 * @fo_context: The #FoContext object.
 * @new_border_left: The new "border-left" property value.
 * 
 * Sets the "border-left" property of @fo_context to @new_border_left.
 **/
void
fo_context_set_border_left (FoContext *fo_context,
		         FoProperty *new_border_left)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_left == NULL || FO_IS_PROPERTY_BORDER_LEFT (new_border_left));

  if (new_border_left != NULL)
    {
      g_object_ref (new_border_left);
    }
  if (fo_context->border_left != NULL)
    {
      g_object_unref (fo_context->border_left);
    }
  fo_context->border_left = new_border_left;
  /*g_object_notify (G_OBJECT (fo_context), "border-left");*/
}

/**
 * fo_context_get_border_left_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-left-color" property of @fo_context.
 *
 * Return value: The "border-left-color" property value.
**/
FoProperty *
fo_context_get_border_left_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_left_color;
}

/**
 * fo_context_set_border_left_color:
 * @fo_context: The #FoContext object.
 * @new_border_left_color: The new "border-left-color" property value.
 * 
 * Sets the "border-left-color" property of @fo_context to @new_border_left_color.
 **/
void
fo_context_set_border_left_color (FoContext *fo_context,
		         FoProperty *new_border_left_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_left_color == NULL || FO_IS_PROPERTY_BORDER_LEFT_COLOR (new_border_left_color));

  if (new_border_left_color != NULL)
    {
      g_object_ref (new_border_left_color);
    }
  if (fo_context->border_left_color != NULL)
    {
      g_object_unref (fo_context->border_left_color);
    }
  fo_context->border_left_color = new_border_left_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-left-color");*/
}

/**
 * fo_context_get_border_left_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-left-style" property of @fo_context.
 *
 * Return value: The "border-left-style" property value.
**/
FoProperty *
fo_context_get_border_left_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_left_style;
}

/**
 * fo_context_set_border_left_style:
 * @fo_context: The #FoContext object.
 * @new_border_left_style: The new "border-left-style" property value.
 * 
 * Sets the "border-left-style" property of @fo_context to @new_border_left_style.
 **/
void
fo_context_set_border_left_style (FoContext *fo_context,
		         FoProperty *new_border_left_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_left_style == NULL || FO_IS_PROPERTY_BORDER_LEFT_STYLE (new_border_left_style));

  if (new_border_left_style != NULL)
    {
      g_object_ref (new_border_left_style);
    }
  if (fo_context->border_left_style != NULL)
    {
      g_object_unref (fo_context->border_left_style);
    }
  fo_context->border_left_style = new_border_left_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-left-style");*/
}

/**
 * fo_context_get_border_left_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-left-width" property of @fo_context.
 *
 * Return value: The "border-left-width" property value.
**/
FoProperty *
fo_context_get_border_left_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_left_width;
}

/**
 * fo_context_set_border_left_width:
 * @fo_context: The #FoContext object.
 * @new_border_left_width: The new "border-left-width" property value.
 * 
 * Sets the "border-left-width" property of @fo_context to @new_border_left_width.
 **/
void
fo_context_set_border_left_width (FoContext *fo_context,
		         FoProperty *new_border_left_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_left_width == NULL || FO_IS_PROPERTY_BORDER_LEFT_WIDTH (new_border_left_width));

  if (new_border_left_width != NULL)
    {
      g_object_ref (new_border_left_width);
    }
  if (fo_context->border_left_width != NULL)
    {
      g_object_unref (fo_context->border_left_width);
    }
  fo_context->border_left_width = new_border_left_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-left-width");*/
}

/**
 * fo_context_get_border_right:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-right" property of @fo_context.
 *
 * Return value: The "border-right" property value.
**/
FoProperty *
fo_context_get_border_right (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_right;
}

/**
 * fo_context_set_border_right:
 * @fo_context: The #FoContext object.
 * @new_border_right: The new "border-right" property value.
 * 
 * Sets the "border-right" property of @fo_context to @new_border_right.
 **/
void
fo_context_set_border_right (FoContext *fo_context,
		         FoProperty *new_border_right)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_right == NULL || FO_IS_PROPERTY_BORDER_RIGHT (new_border_right));

  if (new_border_right != NULL)
    {
      g_object_ref (new_border_right);
    }
  if (fo_context->border_right != NULL)
    {
      g_object_unref (fo_context->border_right);
    }
  fo_context->border_right = new_border_right;
  /*g_object_notify (G_OBJECT (fo_context), "border-right");*/
}

/**
 * fo_context_get_border_right_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-right-color" property of @fo_context.
 *
 * Return value: The "border-right-color" property value.
**/
FoProperty *
fo_context_get_border_right_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_right_color;
}

/**
 * fo_context_set_border_right_color:
 * @fo_context: The #FoContext object.
 * @new_border_right_color: The new "border-right-color" property value.
 * 
 * Sets the "border-right-color" property of @fo_context to @new_border_right_color.
 **/
void
fo_context_set_border_right_color (FoContext *fo_context,
		         FoProperty *new_border_right_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_right_color == NULL || FO_IS_PROPERTY_BORDER_RIGHT_COLOR (new_border_right_color));

  if (new_border_right_color != NULL)
    {
      g_object_ref (new_border_right_color);
    }
  if (fo_context->border_right_color != NULL)
    {
      g_object_unref (fo_context->border_right_color);
    }
  fo_context->border_right_color = new_border_right_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-right-color");*/
}

/**
 * fo_context_get_border_right_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-right-style" property of @fo_context.
 *
 * Return value: The "border-right-style" property value.
**/
FoProperty *
fo_context_get_border_right_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_right_style;
}

/**
 * fo_context_set_border_right_style:
 * @fo_context: The #FoContext object.
 * @new_border_right_style: The new "border-right-style" property value.
 * 
 * Sets the "border-right-style" property of @fo_context to @new_border_right_style.
 **/
void
fo_context_set_border_right_style (FoContext *fo_context,
		         FoProperty *new_border_right_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_right_style == NULL || FO_IS_PROPERTY_BORDER_RIGHT_STYLE (new_border_right_style));

  if (new_border_right_style != NULL)
    {
      g_object_ref (new_border_right_style);
    }
  if (fo_context->border_right_style != NULL)
    {
      g_object_unref (fo_context->border_right_style);
    }
  fo_context->border_right_style = new_border_right_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-right-style");*/
}

/**
 * fo_context_get_border_right_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-right-width" property of @fo_context.
 *
 * Return value: The "border-right-width" property value.
**/
FoProperty *
fo_context_get_border_right_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_right_width;
}

/**
 * fo_context_set_border_right_width:
 * @fo_context: The #FoContext object.
 * @new_border_right_width: The new "border-right-width" property value.
 * 
 * Sets the "border-right-width" property of @fo_context to @new_border_right_width.
 **/
void
fo_context_set_border_right_width (FoContext *fo_context,
		         FoProperty *new_border_right_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_right_width == NULL || FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (new_border_right_width));

  if (new_border_right_width != NULL)
    {
      g_object_ref (new_border_right_width);
    }
  if (fo_context->border_right_width != NULL)
    {
      g_object_unref (fo_context->border_right_width);
    }
  fo_context->border_right_width = new_border_right_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-right-width");*/
}

/**
 * fo_context_get_border_separation:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-separation" property of @fo_context.
 *
 * Return value: The "border-separation" property value.
**/
FoProperty *
fo_context_get_border_separation (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_separation;
}

/**
 * fo_context_set_border_separation:
 * @fo_context: The #FoContext object.
 * @new_border_separation: The new "border-separation" property value.
 * 
 * Sets the "border-separation" property of @fo_context to @new_border_separation.
 **/
void
fo_context_set_border_separation (FoContext *fo_context,
		         FoProperty *new_border_separation)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_separation == NULL || FO_IS_PROPERTY_BORDER_SEPARATION (new_border_separation));

  if (new_border_separation != NULL)
    {
      g_object_ref (new_border_separation);
    }
  if (fo_context->border_separation != NULL)
    {
      g_object_unref (fo_context->border_separation);
    }
  fo_context->border_separation = new_border_separation;
  /*g_object_notify (G_OBJECT (fo_context), "border-separation");*/
}

/**
 * fo_context_get_border_start_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-start-color" property of @fo_context.
 *
 * Return value: The "border-start-color" property value.
**/
FoProperty *
fo_context_get_border_start_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_start_color;
}

/**
 * fo_context_set_border_start_color:
 * @fo_context: The #FoContext object.
 * @new_border_start_color: The new "border-start-color" property value.
 * 
 * Sets the "border-start-color" property of @fo_context to @new_border_start_color.
 **/
void
fo_context_set_border_start_color (FoContext *fo_context,
		         FoProperty *new_border_start_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_start_color == NULL || FO_IS_PROPERTY_BORDER_START_COLOR (new_border_start_color));

  if (new_border_start_color != NULL)
    {
      g_object_ref (new_border_start_color);
    }
  if (fo_context->border_start_color != NULL)
    {
      g_object_unref (fo_context->border_start_color);
    }
  fo_context->border_start_color = new_border_start_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-start-color");*/
}

/**
 * fo_context_get_border_start_precedence:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-start-precedence" property of @fo_context.
 *
 * Return value: The "border-start-precedence" property value.
**/
FoProperty *
fo_context_get_border_start_precedence (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_start_precedence;
}

/**
 * fo_context_set_border_start_precedence:
 * @fo_context: The #FoContext object.
 * @new_border_start_precedence: The new "border-start-precedence" property value.
 * 
 * Sets the "border-start-precedence" property of @fo_context to @new_border_start_precedence.
 **/
void
fo_context_set_border_start_precedence (FoContext *fo_context,
		         FoProperty *new_border_start_precedence)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_start_precedence == NULL || FO_IS_PROPERTY_BORDER_START_PRECEDENCE (new_border_start_precedence));

  if (new_border_start_precedence != NULL)
    {
      g_object_ref (new_border_start_precedence);
    }
  if (fo_context->border_start_precedence != NULL)
    {
      g_object_unref (fo_context->border_start_precedence);
    }
  fo_context->border_start_precedence = new_border_start_precedence;
  /*g_object_notify (G_OBJECT (fo_context), "border-start-precedence");*/
}

/**
 * fo_context_get_border_start_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-start-style" property of @fo_context.
 *
 * Return value: The "border-start-style" property value.
**/
FoProperty *
fo_context_get_border_start_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_start_style;
}

/**
 * fo_context_set_border_start_style:
 * @fo_context: The #FoContext object.
 * @new_border_start_style: The new "border-start-style" property value.
 * 
 * Sets the "border-start-style" property of @fo_context to @new_border_start_style.
 **/
void
fo_context_set_border_start_style (FoContext *fo_context,
		         FoProperty *new_border_start_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_start_style == NULL || FO_IS_PROPERTY_BORDER_START_STYLE (new_border_start_style));

  if (new_border_start_style != NULL)
    {
      g_object_ref (new_border_start_style);
    }
  if (fo_context->border_start_style != NULL)
    {
      g_object_unref (fo_context->border_start_style);
    }
  fo_context->border_start_style = new_border_start_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-start-style");*/
}

/**
 * fo_context_get_border_start_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-start-width" property of @fo_context.
 *
 * Return value: The "border-start-width" property value.
**/
FoProperty *
fo_context_get_border_start_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_start_width;
}

/**
 * fo_context_set_border_start_width:
 * @fo_context: The #FoContext object.
 * @new_border_start_width: The new "border-start-width" property value.
 * 
 * Sets the "border-start-width" property of @fo_context to @new_border_start_width.
 **/
void
fo_context_set_border_start_width (FoContext *fo_context,
		         FoProperty *new_border_start_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_start_width == NULL || FO_IS_PROPERTY_BORDER_START_WIDTH (new_border_start_width));

  if (new_border_start_width != NULL)
    {
      g_object_ref (new_border_start_width);
    }
  if (fo_context->border_start_width != NULL)
    {
      g_object_unref (fo_context->border_start_width);
    }
  fo_context->border_start_width = new_border_start_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-start-width");*/
}

/**
 * fo_context_get_border_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-style" property of @fo_context.
 *
 * Return value: The "border-style" property value.
**/
FoProperty *
fo_context_get_border_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_style;
}

/**
 * fo_context_set_border_style:
 * @fo_context: The #FoContext object.
 * @new_border_style: The new "border-style" property value.
 * 
 * Sets the "border-style" property of @fo_context to @new_border_style.
 **/
void
fo_context_set_border_style (FoContext *fo_context,
		         FoProperty *new_border_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_style == NULL || FO_IS_PROPERTY_BORDER_STYLE (new_border_style));

  if (new_border_style != NULL)
    {
      g_object_ref (new_border_style);
    }
  if (fo_context->border_style != NULL)
    {
      g_object_unref (fo_context->border_style);
    }
  fo_context->border_style = new_border_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-style");*/
}

/**
 * fo_context_get_border_top:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-top" property of @fo_context.
 *
 * Return value: The "border-top" property value.
**/
FoProperty *
fo_context_get_border_top (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_top;
}

/**
 * fo_context_set_border_top:
 * @fo_context: The #FoContext object.
 * @new_border_top: The new "border-top" property value.
 * 
 * Sets the "border-top" property of @fo_context to @new_border_top.
 **/
void
fo_context_set_border_top (FoContext *fo_context,
		         FoProperty *new_border_top)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_top == NULL || FO_IS_PROPERTY_BORDER_TOP (new_border_top));

  if (new_border_top != NULL)
    {
      g_object_ref (new_border_top);
    }
  if (fo_context->border_top != NULL)
    {
      g_object_unref (fo_context->border_top);
    }
  fo_context->border_top = new_border_top;
  /*g_object_notify (G_OBJECT (fo_context), "border-top");*/
}

/**
 * fo_context_get_border_top_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-top-color" property of @fo_context.
 *
 * Return value: The "border-top-color" property value.
**/
FoProperty *
fo_context_get_border_top_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_top_color;
}

/**
 * fo_context_set_border_top_color:
 * @fo_context: The #FoContext object.
 * @new_border_top_color: The new "border-top-color" property value.
 * 
 * Sets the "border-top-color" property of @fo_context to @new_border_top_color.
 **/
void
fo_context_set_border_top_color (FoContext *fo_context,
		         FoProperty *new_border_top_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_top_color == NULL || FO_IS_PROPERTY_BORDER_TOP_COLOR (new_border_top_color));

  if (new_border_top_color != NULL)
    {
      g_object_ref (new_border_top_color);
    }
  if (fo_context->border_top_color != NULL)
    {
      g_object_unref (fo_context->border_top_color);
    }
  fo_context->border_top_color = new_border_top_color;
  /*g_object_notify (G_OBJECT (fo_context), "border-top-color");*/
}

/**
 * fo_context_get_border_top_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-top-style" property of @fo_context.
 *
 * Return value: The "border-top-style" property value.
**/
FoProperty *
fo_context_get_border_top_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_top_style;
}

/**
 * fo_context_set_border_top_style:
 * @fo_context: The #FoContext object.
 * @new_border_top_style: The new "border-top-style" property value.
 * 
 * Sets the "border-top-style" property of @fo_context to @new_border_top_style.
 **/
void
fo_context_set_border_top_style (FoContext *fo_context,
		         FoProperty *new_border_top_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_top_style == NULL || FO_IS_PROPERTY_BORDER_TOP_STYLE (new_border_top_style));

  if (new_border_top_style != NULL)
    {
      g_object_ref (new_border_top_style);
    }
  if (fo_context->border_top_style != NULL)
    {
      g_object_unref (fo_context->border_top_style);
    }
  fo_context->border_top_style = new_border_top_style;
  /*g_object_notify (G_OBJECT (fo_context), "border-top-style");*/
}

/**
 * fo_context_get_border_top_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-top-width" property of @fo_context.
 *
 * Return value: The "border-top-width" property value.
**/
FoProperty *
fo_context_get_border_top_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_top_width;
}

/**
 * fo_context_set_border_top_width:
 * @fo_context: The #FoContext object.
 * @new_border_top_width: The new "border-top-width" property value.
 * 
 * Sets the "border-top-width" property of @fo_context to @new_border_top_width.
 **/
void
fo_context_set_border_top_width (FoContext *fo_context,
		         FoProperty *new_border_top_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_top_width == NULL || FO_IS_PROPERTY_BORDER_TOP_WIDTH (new_border_top_width));

  if (new_border_top_width != NULL)
    {
      g_object_ref (new_border_top_width);
    }
  if (fo_context->border_top_width != NULL)
    {
      g_object_unref (fo_context->border_top_width);
    }
  fo_context->border_top_width = new_border_top_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-top-width");*/
}

/**
 * fo_context_get_border_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "border-width" property of @fo_context.
 *
 * Return value: The "border-width" property value.
**/
FoProperty *
fo_context_get_border_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->border_width;
}

/**
 * fo_context_set_border_width:
 * @fo_context: The #FoContext object.
 * @new_border_width: The new "border-width" property value.
 * 
 * Sets the "border-width" property of @fo_context to @new_border_width.
 **/
void
fo_context_set_border_width (FoContext *fo_context,
		         FoProperty *new_border_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_border_width == NULL || FO_IS_PROPERTY_BORDER_WIDTH (new_border_width));

  if (new_border_width != NULL)
    {
      g_object_ref (new_border_width);
    }
  if (fo_context->border_width != NULL)
    {
      g_object_unref (fo_context->border_width);
    }
  fo_context->border_width = new_border_width;
  /*g_object_notify (G_OBJECT (fo_context), "border-width");*/
}

/**
 * fo_context_get_break_after:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "break-after" property of @fo_context.
 *
 * Return value: The "break-after" property value.
**/
FoProperty *
fo_context_get_break_after (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->break_after;
}

/**
 * fo_context_set_break_after:
 * @fo_context: The #FoContext object.
 * @new_break_after: The new "break-after" property value.
 * 
 * Sets the "break-after" property of @fo_context to @new_break_after.
 **/
void
fo_context_set_break_after (FoContext *fo_context,
		         FoProperty *new_break_after)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_break_after == NULL || FO_IS_PROPERTY_BREAK_AFTER (new_break_after));

  if (new_break_after != NULL)
    {
      g_object_ref (new_break_after);
    }
  if (fo_context->break_after != NULL)
    {
      g_object_unref (fo_context->break_after);
    }
  fo_context->break_after = new_break_after;
  /*g_object_notify (G_OBJECT (fo_context), "break-after");*/
}

/**
 * fo_context_get_break_before:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "break-before" property of @fo_context.
 *
 * Return value: The "break-before" property value.
**/
FoProperty *
fo_context_get_break_before (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->break_before;
}

/**
 * fo_context_set_break_before:
 * @fo_context: The #FoContext object.
 * @new_break_before: The new "break-before" property value.
 * 
 * Sets the "break-before" property of @fo_context to @new_break_before.
 **/
void
fo_context_set_break_before (FoContext *fo_context,
		         FoProperty *new_break_before)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_break_before == NULL || FO_IS_PROPERTY_BREAK_BEFORE (new_break_before));

  if (new_break_before != NULL)
    {
      g_object_ref (new_break_before);
    }
  if (fo_context->break_before != NULL)
    {
      g_object_unref (fo_context->break_before);
    }
  fo_context->break_before = new_break_before;
  /*g_object_notify (G_OBJECT (fo_context), "break-before");*/
}

/**
 * fo_context_get_character:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "character" property of @fo_context.
 *
 * Return value: The "character" property value.
**/
FoProperty *
fo_context_get_character (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->character;
}

/**
 * fo_context_set_character:
 * @fo_context: The #FoContext object.
 * @new_character: The new "character" property value.
 * 
 * Sets the "character" property of @fo_context to @new_character.
 **/
void
fo_context_set_character (FoContext *fo_context,
		         FoProperty *new_character)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_character == NULL || FO_IS_PROPERTY_CHARACTER (new_character));

  if (new_character != NULL)
    {
      g_object_ref (new_character);
    }
  if (fo_context->character != NULL)
    {
      g_object_unref (fo_context->character);
    }
  fo_context->character = new_character;
  /*g_object_notify (G_OBJECT (fo_context), "character");*/
}

/**
 * fo_context_get_clip:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "clip" property of @fo_context.
 *
 * Return value: The "clip" property value.
**/
FoProperty *
fo_context_get_clip (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->clip;
}

/**
 * fo_context_set_clip:
 * @fo_context: The #FoContext object.
 * @new_clip: The new "clip" property value.
 * 
 * Sets the "clip" property of @fo_context to @new_clip.
 **/
void
fo_context_set_clip (FoContext *fo_context,
		         FoProperty *new_clip)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_clip == NULL || FO_IS_PROPERTY_CLIP (new_clip));

  if (new_clip != NULL)
    {
      g_object_ref (new_clip);
    }
  if (fo_context->clip != NULL)
    {
      g_object_unref (fo_context->clip);
    }
  fo_context->clip = new_clip;
  /*g_object_notify (G_OBJECT (fo_context), "clip");*/
}

/**
 * fo_context_get_color:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "color" property of @fo_context.
 *
 * Return value: The "color" property value.
**/
FoProperty *
fo_context_get_color (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->color;
}

/**
 * fo_context_set_color:
 * @fo_context: The #FoContext object.
 * @new_color: The new "color" property value.
 * 
 * Sets the "color" property of @fo_context to @new_color.
 **/
void
fo_context_set_color (FoContext *fo_context,
		         FoProperty *new_color)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_color == NULL || FO_IS_PROPERTY_COLOR (new_color));

  if (new_color != NULL)
    {
      g_object_ref (new_color);
    }
  if (fo_context->color != NULL)
    {
      g_object_unref (fo_context->color);
    }
  fo_context->color = new_color;
  /*g_object_notify (G_OBJECT (fo_context), "color");*/
}

/**
 * fo_context_get_column_number:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "column-number" property of @fo_context.
 *
 * Return value: The "column-number" property value.
**/
FoProperty *
fo_context_get_column_number (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->column_number;
}

/**
 * fo_context_set_column_number:
 * @fo_context: The #FoContext object.
 * @new_column_number: The new "column-number" property value.
 * 
 * Sets the "column-number" property of @fo_context to @new_column_number.
 **/
void
fo_context_set_column_number (FoContext *fo_context,
		         FoProperty *new_column_number)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_column_number == NULL || FO_IS_PROPERTY_COLUMN_NUMBER (new_column_number));

  if (new_column_number != NULL)
    {
      g_object_ref (new_column_number);
    }
  if (fo_context->column_number != NULL)
    {
      g_object_unref (fo_context->column_number);
    }
  fo_context->column_number = new_column_number;
  /*g_object_notify (G_OBJECT (fo_context), "column-number");*/
}

/**
 * fo_context_get_column_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "column-width" property of @fo_context.
 *
 * Return value: The "column-width" property value.
**/
FoProperty *
fo_context_get_column_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->column_width;
}

/**
 * fo_context_set_column_width:
 * @fo_context: The #FoContext object.
 * @new_column_width: The new "column-width" property value.
 * 
 * Sets the "column-width" property of @fo_context to @new_column_width.
 **/
void
fo_context_set_column_width (FoContext *fo_context,
		         FoProperty *new_column_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_column_width == NULL || FO_IS_PROPERTY_COLUMN_WIDTH (new_column_width));

  if (new_column_width != NULL)
    {
      g_object_ref (new_column_width);
    }
  if (fo_context->column_width != NULL)
    {
      g_object_unref (fo_context->column_width);
    }
  fo_context->column_width = new_column_width;
  /*g_object_notify (G_OBJECT (fo_context), "column-width");*/
}

/**
 * fo_context_get_content_height:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "content-height" property of @fo_context.
 *
 * Return value: The "content-height" property value.
**/
FoProperty *
fo_context_get_content_height (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->content_height;
}

/**
 * fo_context_set_content_height:
 * @fo_context: The #FoContext object.
 * @new_content_height: The new "content-height" property value.
 * 
 * Sets the "content-height" property of @fo_context to @new_content_height.
 **/
void
fo_context_set_content_height (FoContext *fo_context,
		         FoProperty *new_content_height)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_content_height == NULL || FO_IS_PROPERTY_CONTENT_HEIGHT (new_content_height));

  if (new_content_height != NULL)
    {
      g_object_ref (new_content_height);
    }
  if (fo_context->content_height != NULL)
    {
      g_object_unref (fo_context->content_height);
    }
  fo_context->content_height = new_content_height;
  /*g_object_notify (G_OBJECT (fo_context), "content-height");*/
}

/**
 * fo_context_get_content_type:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "content-type" property of @fo_context.
 *
 * Return value: The "content-type" property value.
**/
FoProperty *
fo_context_get_content_type (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->content_type;
}

/**
 * fo_context_set_content_type:
 * @fo_context: The #FoContext object.
 * @new_content_type: The new "content-type" property value.
 * 
 * Sets the "content-type" property of @fo_context to @new_content_type.
 **/
void
fo_context_set_content_type (FoContext *fo_context,
		         FoProperty *new_content_type)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_content_type == NULL || FO_IS_PROPERTY_CONTENT_TYPE (new_content_type));

  if (new_content_type != NULL)
    {
      g_object_ref (new_content_type);
    }
  if (fo_context->content_type != NULL)
    {
      g_object_unref (fo_context->content_type);
    }
  fo_context->content_type = new_content_type;
  /*g_object_notify (G_OBJECT (fo_context), "content-type");*/
}

/**
 * fo_context_get_content_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "content-width" property of @fo_context.
 *
 * Return value: The "content-width" property value.
**/
FoProperty *
fo_context_get_content_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->content_width;
}

/**
 * fo_context_set_content_width:
 * @fo_context: The #FoContext object.
 * @new_content_width: The new "content-width" property value.
 * 
 * Sets the "content-width" property of @fo_context to @new_content_width.
 **/
void
fo_context_set_content_width (FoContext *fo_context,
		         FoProperty *new_content_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_content_width == NULL || FO_IS_PROPERTY_CONTENT_WIDTH (new_content_width));

  if (new_content_width != NULL)
    {
      g_object_ref (new_content_width);
    }
  if (fo_context->content_width != NULL)
    {
      g_object_unref (fo_context->content_width);
    }
  fo_context->content_width = new_content_width;
  /*g_object_notify (G_OBJECT (fo_context), "content-width");*/
}

/**
 * fo_context_get_direction:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "direction" property of @fo_context.
 *
 * Return value: The "direction" property value.
**/
FoProperty *
fo_context_get_direction (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->direction;
}

/**
 * fo_context_set_direction:
 * @fo_context: The #FoContext object.
 * @new_direction: The new "direction" property value.
 * 
 * Sets the "direction" property of @fo_context to @new_direction.
 **/
void
fo_context_set_direction (FoContext *fo_context,
		         FoProperty *new_direction)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_direction == NULL || FO_IS_PROPERTY_DIRECTION (new_direction));

  if (new_direction != NULL)
    {
      g_object_ref (new_direction);
    }
  if (fo_context->direction != NULL)
    {
      g_object_unref (fo_context->direction);
    }
  fo_context->direction = new_direction;
  /*g_object_notify (G_OBJECT (fo_context), "direction");*/
}

/**
 * fo_context_get_display_align:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "display-align" property of @fo_context.
 *
 * Return value: The "display-align" property value.
**/
FoProperty *
fo_context_get_display_align (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->display_align;
}

/**
 * fo_context_set_display_align:
 * @fo_context: The #FoContext object.
 * @new_display_align: The new "display-align" property value.
 * 
 * Sets the "display-align" property of @fo_context to @new_display_align.
 **/
void
fo_context_set_display_align (FoContext *fo_context,
		         FoProperty *new_display_align)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_display_align == NULL || FO_IS_PROPERTY_DISPLAY_ALIGN (new_display_align));

  if (new_display_align != NULL)
    {
      g_object_ref (new_display_align);
    }
  if (fo_context->display_align != NULL)
    {
      g_object_unref (fo_context->display_align);
    }
  fo_context->display_align = new_display_align;
  /*g_object_notify (G_OBJECT (fo_context), "display-align");*/
}

/**
 * fo_context_get_dominant_baseline:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "dominant-baseline" property of @fo_context.
 *
 * Return value: The "dominant-baseline" property value.
**/
FoProperty *
fo_context_get_dominant_baseline (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->dominant_baseline;
}

/**
 * fo_context_set_dominant_baseline:
 * @fo_context: The #FoContext object.
 * @new_dominant_baseline: The new "dominant-baseline" property value.
 * 
 * Sets the "dominant-baseline" property of @fo_context to @new_dominant_baseline.
 **/
void
fo_context_set_dominant_baseline (FoContext *fo_context,
		         FoProperty *new_dominant_baseline)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_dominant_baseline == NULL || FO_IS_PROPERTY_DOMINANT_BASELINE (new_dominant_baseline));

  if (new_dominant_baseline != NULL)
    {
      g_object_ref (new_dominant_baseline);
    }
  if (fo_context->dominant_baseline != NULL)
    {
      g_object_unref (fo_context->dominant_baseline);
    }
  fo_context->dominant_baseline = new_dominant_baseline;
  /*g_object_notify (G_OBJECT (fo_context), "dominant-baseline");*/
}

/**
 * fo_context_get_end_indent:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "end-indent" property of @fo_context.
 *
 * Return value: The "end-indent" property value.
**/
FoProperty *
fo_context_get_end_indent (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->end_indent;
}

/**
 * fo_context_set_end_indent:
 * @fo_context: The #FoContext object.
 * @new_end_indent: The new "end-indent" property value.
 * 
 * Sets the "end-indent" property of @fo_context to @new_end_indent.
 **/
void
fo_context_set_end_indent (FoContext *fo_context,
		         FoProperty *new_end_indent)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_end_indent == NULL || FO_IS_PROPERTY_END_INDENT (new_end_indent));

  if (new_end_indent != NULL)
    {
      g_object_ref (new_end_indent);
    }
  if (fo_context->end_indent != NULL)
    {
      g_object_unref (fo_context->end_indent);
    }
  fo_context->end_indent = new_end_indent;
  /*g_object_notify (G_OBJECT (fo_context), "end-indent");*/
}

/**
 * fo_context_get_extent:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "extent" property of @fo_context.
 *
 * Return value: The "extent" property value.
**/
FoProperty *
fo_context_get_extent (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->extent;
}

/**
 * fo_context_set_extent:
 * @fo_context: The #FoContext object.
 * @new_extent: The new "extent" property value.
 * 
 * Sets the "extent" property of @fo_context to @new_extent.
 **/
void
fo_context_set_extent (FoContext *fo_context,
		         FoProperty *new_extent)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_extent == NULL || FO_IS_PROPERTY_EXTENT (new_extent));

  if (new_extent != NULL)
    {
      g_object_ref (new_extent);
    }
  if (fo_context->extent != NULL)
    {
      g_object_unref (fo_context->extent);
    }
  fo_context->extent = new_extent;
  /*g_object_notify (G_OBJECT (fo_context), "extent");*/
}

/**
 * fo_context_get_flow_name:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "flow-name" property of @fo_context.
 *
 * Return value: The "flow-name" property value.
**/
FoProperty *
fo_context_get_flow_name (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->flow_name;
}

/**
 * fo_context_set_flow_name:
 * @fo_context: The #FoContext object.
 * @new_flow_name: The new "flow-name" property value.
 * 
 * Sets the "flow-name" property of @fo_context to @new_flow_name.
 **/
void
fo_context_set_flow_name (FoContext *fo_context,
		         FoProperty *new_flow_name)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_flow_name == NULL || FO_IS_PROPERTY_FLOW_NAME (new_flow_name));

  if (new_flow_name != NULL)
    {
      g_object_ref (new_flow_name);
    }
  if (fo_context->flow_name != NULL)
    {
      g_object_unref (fo_context->flow_name);
    }
  fo_context->flow_name = new_flow_name;
  /*g_object_notify (G_OBJECT (fo_context), "flow-name");*/
}

/**
 * fo_context_get_font_family:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "font-family" property of @fo_context.
 *
 * Return value: The "font-family" property value.
**/
FoProperty *
fo_context_get_font_family (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->font_family;
}

/**
 * fo_context_set_font_family:
 * @fo_context: The #FoContext object.
 * @new_font_family: The new "font-family" property value.
 * 
 * Sets the "font-family" property of @fo_context to @new_font_family.
 **/
void
fo_context_set_font_family (FoContext *fo_context,
		         FoProperty *new_font_family)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_font_family == NULL || FO_IS_PROPERTY_FONT_FAMILY (new_font_family));

  if (new_font_family != NULL)
    {
      g_object_ref (new_font_family);
    }
  if (fo_context->font_family != NULL)
    {
      g_object_unref (fo_context->font_family);
    }
  fo_context->font_family = new_font_family;
  /*g_object_notify (G_OBJECT (fo_context), "font-family");*/
}

/**
 * fo_context_get_font_size:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "font-size" property of @fo_context.
 *
 * Return value: The "font-size" property value.
**/
FoProperty *
fo_context_get_font_size (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->font_size;
}

/**
 * fo_context_set_font_size:
 * @fo_context: The #FoContext object.
 * @new_font_size: The new "font-size" property value.
 * 
 * Sets the "font-size" property of @fo_context to @new_font_size.
 **/
void
fo_context_set_font_size (FoContext *fo_context,
		         FoProperty *new_font_size)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_font_size == NULL || FO_IS_PROPERTY_FONT_SIZE (new_font_size));

  if (new_font_size != NULL)
    {
      g_object_ref (new_font_size);
    }
  if (fo_context->font_size != NULL)
    {
      g_object_unref (fo_context->font_size);
    }
  fo_context->font_size = new_font_size;
  /*g_object_notify (G_OBJECT (fo_context), "font-size");*/
}

/**
 * fo_context_get_font_stretch:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "font-stretch" property of @fo_context.
 *
 * Return value: The "font-stretch" property value.
**/
FoProperty *
fo_context_get_font_stretch (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->font_stretch;
}

/**
 * fo_context_set_font_stretch:
 * @fo_context: The #FoContext object.
 * @new_font_stretch: The new "font-stretch" property value.
 * 
 * Sets the "font-stretch" property of @fo_context to @new_font_stretch.
 **/
void
fo_context_set_font_stretch (FoContext *fo_context,
		         FoProperty *new_font_stretch)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_font_stretch == NULL || FO_IS_PROPERTY_FONT_STRETCH (new_font_stretch));

  if (new_font_stretch != NULL)
    {
      g_object_ref (new_font_stretch);
    }
  if (fo_context->font_stretch != NULL)
    {
      g_object_unref (fo_context->font_stretch);
    }
  fo_context->font_stretch = new_font_stretch;
  /*g_object_notify (G_OBJECT (fo_context), "font-stretch");*/
}

/**
 * fo_context_get_font_style:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "font-style" property of @fo_context.
 *
 * Return value: The "font-style" property value.
**/
FoProperty *
fo_context_get_font_style (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->font_style;
}

/**
 * fo_context_set_font_style:
 * @fo_context: The #FoContext object.
 * @new_font_style: The new "font-style" property value.
 * 
 * Sets the "font-style" property of @fo_context to @new_font_style.
 **/
void
fo_context_set_font_style (FoContext *fo_context,
		         FoProperty *new_font_style)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_font_style == NULL || FO_IS_PROPERTY_FONT_STYLE (new_font_style));

  if (new_font_style != NULL)
    {
      g_object_ref (new_font_style);
    }
  if (fo_context->font_style != NULL)
    {
      g_object_unref (fo_context->font_style);
    }
  fo_context->font_style = new_font_style;
  /*g_object_notify (G_OBJECT (fo_context), "font-style");*/
}

/**
 * fo_context_get_font_variant:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "font-variant" property of @fo_context.
 *
 * Return value: The "font-variant" property value.
**/
FoProperty *
fo_context_get_font_variant (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->font_variant;
}

/**
 * fo_context_set_font_variant:
 * @fo_context: The #FoContext object.
 * @new_font_variant: The new "font-variant" property value.
 * 
 * Sets the "font-variant" property of @fo_context to @new_font_variant.
 **/
void
fo_context_set_font_variant (FoContext *fo_context,
		         FoProperty *new_font_variant)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_font_variant == NULL || FO_IS_PROPERTY_FONT_VARIANT (new_font_variant));

  if (new_font_variant != NULL)
    {
      g_object_ref (new_font_variant);
    }
  if (fo_context->font_variant != NULL)
    {
      g_object_unref (fo_context->font_variant);
    }
  fo_context->font_variant = new_font_variant;
  /*g_object_notify (G_OBJECT (fo_context), "font-variant");*/
}

/**
 * fo_context_get_font_weight:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "font-weight" property of @fo_context.
 *
 * Return value: The "font-weight" property value.
**/
FoProperty *
fo_context_get_font_weight (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->font_weight;
}

/**
 * fo_context_set_font_weight:
 * @fo_context: The #FoContext object.
 * @new_font_weight: The new "font-weight" property value.
 * 
 * Sets the "font-weight" property of @fo_context to @new_font_weight.
 **/
void
fo_context_set_font_weight (FoContext *fo_context,
		         FoProperty *new_font_weight)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_font_weight == NULL || FO_IS_PROPERTY_FONT_WEIGHT (new_font_weight));

  if (new_font_weight != NULL)
    {
      g_object_ref (new_font_weight);
    }
  if (fo_context->font_weight != NULL)
    {
      g_object_unref (fo_context->font_weight);
    }
  fo_context->font_weight = new_font_weight;
  /*g_object_notify (G_OBJECT (fo_context), "font-weight");*/
}

/**
 * fo_context_get_format:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "format" property of @fo_context.
 *
 * Return value: The "format" property value.
**/
FoProperty *
fo_context_get_format (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->format;
}

/**
 * fo_context_set_format:
 * @fo_context: The #FoContext object.
 * @new_format: The new "format" property value.
 * 
 * Sets the "format" property of @fo_context to @new_format.
 **/
void
fo_context_set_format (FoContext *fo_context,
		         FoProperty *new_format)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_format == NULL || FO_IS_PROPERTY_FORMAT (new_format));

  if (new_format != NULL)
    {
      g_object_ref (new_format);
    }
  if (fo_context->format != NULL)
    {
      g_object_unref (fo_context->format);
    }
  fo_context->format = new_format;
  /*g_object_notify (G_OBJECT (fo_context), "format");*/
}

/**
 * fo_context_get_grouping_separator:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "grouping-separator" property of @fo_context.
 *
 * Return value: The "grouping-separator" property value.
**/
FoProperty *
fo_context_get_grouping_separator (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->grouping_separator;
}

/**
 * fo_context_set_grouping_separator:
 * @fo_context: The #FoContext object.
 * @new_grouping_separator: The new "grouping-separator" property value.
 * 
 * Sets the "grouping-separator" property of @fo_context to @new_grouping_separator.
 **/
void
fo_context_set_grouping_separator (FoContext *fo_context,
		         FoProperty *new_grouping_separator)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_grouping_separator == NULL || FO_IS_PROPERTY_GROUPING_SEPARATOR (new_grouping_separator));

  if (new_grouping_separator != NULL)
    {
      g_object_ref (new_grouping_separator);
    }
  if (fo_context->grouping_separator != NULL)
    {
      g_object_unref (fo_context->grouping_separator);
    }
  fo_context->grouping_separator = new_grouping_separator;
  /*g_object_notify (G_OBJECT (fo_context), "grouping-separator");*/
}

/**
 * fo_context_get_grouping_size:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "grouping-size" property of @fo_context.
 *
 * Return value: The "grouping-size" property value.
**/
FoProperty *
fo_context_get_grouping_size (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->grouping_size;
}

/**
 * fo_context_set_grouping_size:
 * @fo_context: The #FoContext object.
 * @new_grouping_size: The new "grouping-size" property value.
 * 
 * Sets the "grouping-size" property of @fo_context to @new_grouping_size.
 **/
void
fo_context_set_grouping_size (FoContext *fo_context,
		         FoProperty *new_grouping_size)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_grouping_size == NULL || FO_IS_PROPERTY_GROUPING_SIZE (new_grouping_size));

  if (new_grouping_size != NULL)
    {
      g_object_ref (new_grouping_size);
    }
  if (fo_context->grouping_size != NULL)
    {
      g_object_unref (fo_context->grouping_size);
    }
  fo_context->grouping_size = new_grouping_size;
  /*g_object_notify (G_OBJECT (fo_context), "grouping-size");*/
}

/**
 * fo_context_get_height:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "height" property of @fo_context.
 *
 * Return value: The "height" property value.
**/
FoProperty *
fo_context_get_height (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->height;
}

/**
 * fo_context_set_height:
 * @fo_context: The #FoContext object.
 * @new_height: The new "height" property value.
 * 
 * Sets the "height" property of @fo_context to @new_height.
 **/
void
fo_context_set_height (FoContext *fo_context,
		         FoProperty *new_height)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_height == NULL || FO_IS_PROPERTY_HEIGHT (new_height));

  if (new_height != NULL)
    {
      g_object_ref (new_height);
    }
  if (fo_context->height != NULL)
    {
      g_object_unref (fo_context->height);
    }
  fo_context->height = new_height;
  /*g_object_notify (G_OBJECT (fo_context), "height");*/
}

/**
 * fo_context_get_id:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "id" property of @fo_context.
 *
 * Return value: The "id" property value.
**/
FoProperty *
fo_context_get_id (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->id;
}

/**
 * fo_context_set_id:
 * @fo_context: The #FoContext object.
 * @new_id: The new "id" property value.
 * 
 * Sets the "id" property of @fo_context to @new_id.
 **/
void
fo_context_set_id (FoContext *fo_context,
		         FoProperty *new_id)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_id == NULL || FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_context->id != NULL)
    {
      g_object_unref (fo_context->id);
    }
  fo_context->id = new_id;
  /*g_object_notify (G_OBJECT (fo_context), "id");*/
}

/**
 * fo_context_get_inline_progression_dimension:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "inline-progression-dimension" property of @fo_context.
 *
 * Return value: The "inline-progression-dimension" property value.
**/
FoProperty *
fo_context_get_inline_progression_dimension (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->inline_progression_dimension;
}

/**
 * fo_context_set_inline_progression_dimension:
 * @fo_context: The #FoContext object.
 * @new_inline_progression_dimension: The new "inline-progression-dimension" property value.
 * 
 * Sets the "inline-progression-dimension" property of @fo_context to @new_inline_progression_dimension.
 **/
void
fo_context_set_inline_progression_dimension (FoContext *fo_context,
		         FoProperty *new_inline_progression_dimension)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_inline_progression_dimension == NULL || FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION (new_inline_progression_dimension));

  if (new_inline_progression_dimension != NULL)
    {
      g_object_ref (new_inline_progression_dimension);
    }
  if (fo_context->inline_progression_dimension != NULL)
    {
      g_object_unref (fo_context->inline_progression_dimension);
    }
  fo_context->inline_progression_dimension = new_inline_progression_dimension;
  /*g_object_notify (G_OBJECT (fo_context), "inline-progression-dimension");*/
}

/**
 * fo_context_get_inline_progression_dimension_minimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "inline-progression-dimension-minimum" property of @fo_context.
 *
 * Return value: The "inline-progression-dimension-minimum" property value.
**/
FoProperty *
fo_context_get_inline_progression_dimension_minimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->inline_progression_dimension_minimum;
}

/**
 * fo_context_set_inline_progression_dimension_minimum:
 * @fo_context: The #FoContext object.
 * @new_inline_progression_dimension_minimum: The new "inline-progression-dimension-minimum" property value.
 * 
 * Sets the "inline-progression-dimension-minimum" property of @fo_context to @new_inline_progression_dimension_minimum.
 **/
void
fo_context_set_inline_progression_dimension_minimum (FoContext *fo_context,
		         FoProperty *new_inline_progression_dimension_minimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_inline_progression_dimension_minimum == NULL || FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION_MINIMUM (new_inline_progression_dimension_minimum));

  if (new_inline_progression_dimension_minimum != NULL)
    {
      g_object_ref (new_inline_progression_dimension_minimum);
    }
  if (fo_context->inline_progression_dimension_minimum != NULL)
    {
      g_object_unref (fo_context->inline_progression_dimension_minimum);
    }
  fo_context->inline_progression_dimension_minimum = new_inline_progression_dimension_minimum;
  /*g_object_notify (G_OBJECT (fo_context), "inline-progression-dimension-minimum");*/
}

/**
 * fo_context_get_inline_progression_dimension_optimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "inline-progression-dimension-optimum" property of @fo_context.
 *
 * Return value: The "inline-progression-dimension-optimum" property value.
**/
FoProperty *
fo_context_get_inline_progression_dimension_optimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->inline_progression_dimension_optimum;
}

/**
 * fo_context_set_inline_progression_dimension_optimum:
 * @fo_context: The #FoContext object.
 * @new_inline_progression_dimension_optimum: The new "inline-progression-dimension-optimum" property value.
 * 
 * Sets the "inline-progression-dimension-optimum" property of @fo_context to @new_inline_progression_dimension_optimum.
 **/
void
fo_context_set_inline_progression_dimension_optimum (FoContext *fo_context,
		         FoProperty *new_inline_progression_dimension_optimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_inline_progression_dimension_optimum == NULL || FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM (new_inline_progression_dimension_optimum));

  if (new_inline_progression_dimension_optimum != NULL)
    {
      g_object_ref (new_inline_progression_dimension_optimum);
    }
  if (fo_context->inline_progression_dimension_optimum != NULL)
    {
      g_object_unref (fo_context->inline_progression_dimension_optimum);
    }
  fo_context->inline_progression_dimension_optimum = new_inline_progression_dimension_optimum;
  /*g_object_notify (G_OBJECT (fo_context), "inline-progression-dimension-optimum");*/
}

/**
 * fo_context_get_inline_progression_dimension_maximum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "inline-progression-dimension-maximum" property of @fo_context.
 *
 * Return value: The "inline-progression-dimension-maximum" property value.
**/
FoProperty *
fo_context_get_inline_progression_dimension_maximum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->inline_progression_dimension_maximum;
}

/**
 * fo_context_set_inline_progression_dimension_maximum:
 * @fo_context: The #FoContext object.
 * @new_inline_progression_dimension_maximum: The new "inline-progression-dimension-maximum" property value.
 * 
 * Sets the "inline-progression-dimension-maximum" property of @fo_context to @new_inline_progression_dimension_maximum.
 **/
void
fo_context_set_inline_progression_dimension_maximum (FoContext *fo_context,
		         FoProperty *new_inline_progression_dimension_maximum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_inline_progression_dimension_maximum == NULL || FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION_MAXIMUM (new_inline_progression_dimension_maximum));

  if (new_inline_progression_dimension_maximum != NULL)
    {
      g_object_ref (new_inline_progression_dimension_maximum);
    }
  if (fo_context->inline_progression_dimension_maximum != NULL)
    {
      g_object_unref (fo_context->inline_progression_dimension_maximum);
    }
  fo_context->inline_progression_dimension_maximum = new_inline_progression_dimension_maximum;
  /*g_object_notify (G_OBJECT (fo_context), "inline-progression-dimension-maximum");*/
}

/**
 * fo_context_get_keep_together:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-together" property of @fo_context.
 *
 * Return value: The "keep-together" property value.
**/
FoProperty *
fo_context_get_keep_together (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_together;
}

/**
 * fo_context_set_keep_together:
 * @fo_context: The #FoContext object.
 * @new_keep_together: The new "keep-together" property value.
 * 
 * Sets the "keep-together" property of @fo_context to @new_keep_together.
 **/
void
fo_context_set_keep_together (FoContext *fo_context,
		         FoProperty *new_keep_together)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_together == NULL || FO_IS_PROPERTY_KEEP_TOGETHER (new_keep_together));

  if (new_keep_together != NULL)
    {
      g_object_ref (new_keep_together);
    }
  if (fo_context->keep_together != NULL)
    {
      g_object_unref (fo_context->keep_together);
    }
  fo_context->keep_together = new_keep_together;
  /*g_object_notify (G_OBJECT (fo_context), "keep-together");*/
}

/**
 * fo_context_get_keep_together_within_column:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-together-within-column" property of @fo_context.
 *
 * Return value: The "keep-together-within-column" property value.
**/
FoProperty *
fo_context_get_keep_together_within_column (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_together_within_column;
}

/**
 * fo_context_set_keep_together_within_column:
 * @fo_context: The #FoContext object.
 * @new_keep_together_within_column: The new "keep-together-within-column" property value.
 * 
 * Sets the "keep-together-within-column" property of @fo_context to @new_keep_together_within_column.
 **/
void
fo_context_set_keep_together_within_column (FoContext *fo_context,
		         FoProperty *new_keep_together_within_column)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_together_within_column == NULL || FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN (new_keep_together_within_column));

  if (new_keep_together_within_column != NULL)
    {
      g_object_ref (new_keep_together_within_column);
    }
  if (fo_context->keep_together_within_column != NULL)
    {
      g_object_unref (fo_context->keep_together_within_column);
    }
  fo_context->keep_together_within_column = new_keep_together_within_column;
  /*g_object_notify (G_OBJECT (fo_context), "keep-together-within-column");*/
}

/**
 * fo_context_get_keep_together_within_line:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-together-within-line" property of @fo_context.
 *
 * Return value: The "keep-together-within-line" property value.
**/
FoProperty *
fo_context_get_keep_together_within_line (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_together_within_line;
}

/**
 * fo_context_set_keep_together_within_line:
 * @fo_context: The #FoContext object.
 * @new_keep_together_within_line: The new "keep-together-within-line" property value.
 * 
 * Sets the "keep-together-within-line" property of @fo_context to @new_keep_together_within_line.
 **/
void
fo_context_set_keep_together_within_line (FoContext *fo_context,
		         FoProperty *new_keep_together_within_line)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_together_within_line == NULL || FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_LINE (new_keep_together_within_line));

  if (new_keep_together_within_line != NULL)
    {
      g_object_ref (new_keep_together_within_line);
    }
  if (fo_context->keep_together_within_line != NULL)
    {
      g_object_unref (fo_context->keep_together_within_line);
    }
  fo_context->keep_together_within_line = new_keep_together_within_line;
  /*g_object_notify (G_OBJECT (fo_context), "keep-together-within-line");*/
}

/**
 * fo_context_get_keep_together_within_page:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-together-within-page" property of @fo_context.
 *
 * Return value: The "keep-together-within-page" property value.
**/
FoProperty *
fo_context_get_keep_together_within_page (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_together_within_page;
}

/**
 * fo_context_set_keep_together_within_page:
 * @fo_context: The #FoContext object.
 * @new_keep_together_within_page: The new "keep-together-within-page" property value.
 * 
 * Sets the "keep-together-within-page" property of @fo_context to @new_keep_together_within_page.
 **/
void
fo_context_set_keep_together_within_page (FoContext *fo_context,
		         FoProperty *new_keep_together_within_page)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_together_within_page == NULL || FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE (new_keep_together_within_page));

  if (new_keep_together_within_page != NULL)
    {
      g_object_ref (new_keep_together_within_page);
    }
  if (fo_context->keep_together_within_page != NULL)
    {
      g_object_unref (fo_context->keep_together_within_page);
    }
  fo_context->keep_together_within_page = new_keep_together_within_page;
  /*g_object_notify (G_OBJECT (fo_context), "keep-together-within-page");*/
}

/**
 * fo_context_get_keep_with_next:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-with-next" property of @fo_context.
 *
 * Return value: The "keep-with-next" property value.
**/
FoProperty *
fo_context_get_keep_with_next (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_with_next;
}

/**
 * fo_context_set_keep_with_next:
 * @fo_context: The #FoContext object.
 * @new_keep_with_next: The new "keep-with-next" property value.
 * 
 * Sets the "keep-with-next" property of @fo_context to @new_keep_with_next.
 **/
void
fo_context_set_keep_with_next (FoContext *fo_context,
		         FoProperty *new_keep_with_next)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_with_next == NULL || FO_IS_PROPERTY_KEEP_WITH_NEXT (new_keep_with_next));

  if (new_keep_with_next != NULL)
    {
      g_object_ref (new_keep_with_next);
    }
  if (fo_context->keep_with_next != NULL)
    {
      g_object_unref (fo_context->keep_with_next);
    }
  fo_context->keep_with_next = new_keep_with_next;
  /*g_object_notify (G_OBJECT (fo_context), "keep-with-next");*/
}

/**
 * fo_context_get_keep_with_next_within_column:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-with-next-within-column" property of @fo_context.
 *
 * Return value: The "keep-with-next-within-column" property value.
**/
FoProperty *
fo_context_get_keep_with_next_within_column (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_with_next_within_column;
}

/**
 * fo_context_set_keep_with_next_within_column:
 * @fo_context: The #FoContext object.
 * @new_keep_with_next_within_column: The new "keep-with-next-within-column" property value.
 * 
 * Sets the "keep-with-next-within-column" property of @fo_context to @new_keep_with_next_within_column.
 **/
void
fo_context_set_keep_with_next_within_column (FoContext *fo_context,
		         FoProperty *new_keep_with_next_within_column)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_with_next_within_column == NULL || FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_COLUMN (new_keep_with_next_within_column));

  if (new_keep_with_next_within_column != NULL)
    {
      g_object_ref (new_keep_with_next_within_column);
    }
  if (fo_context->keep_with_next_within_column != NULL)
    {
      g_object_unref (fo_context->keep_with_next_within_column);
    }
  fo_context->keep_with_next_within_column = new_keep_with_next_within_column;
  /*g_object_notify (G_OBJECT (fo_context), "keep-with-next-within-column");*/
}

/**
 * fo_context_get_keep_with_next_within_line:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-with-next-within-line" property of @fo_context.
 *
 * Return value: The "keep-with-next-within-line" property value.
**/
FoProperty *
fo_context_get_keep_with_next_within_line (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_with_next_within_line;
}

/**
 * fo_context_set_keep_with_next_within_line:
 * @fo_context: The #FoContext object.
 * @new_keep_with_next_within_line: The new "keep-with-next-within-line" property value.
 * 
 * Sets the "keep-with-next-within-line" property of @fo_context to @new_keep_with_next_within_line.
 **/
void
fo_context_set_keep_with_next_within_line (FoContext *fo_context,
		         FoProperty *new_keep_with_next_within_line)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_with_next_within_line == NULL || FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (new_keep_with_next_within_line));

  if (new_keep_with_next_within_line != NULL)
    {
      g_object_ref (new_keep_with_next_within_line);
    }
  if (fo_context->keep_with_next_within_line != NULL)
    {
      g_object_unref (fo_context->keep_with_next_within_line);
    }
  fo_context->keep_with_next_within_line = new_keep_with_next_within_line;
  /*g_object_notify (G_OBJECT (fo_context), "keep-with-next-within-line");*/
}

/**
 * fo_context_get_keep_with_next_within_page:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-with-next-within-page" property of @fo_context.
 *
 * Return value: The "keep-with-next-within-page" property value.
**/
FoProperty *
fo_context_get_keep_with_next_within_page (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_with_next_within_page;
}

/**
 * fo_context_set_keep_with_next_within_page:
 * @fo_context: The #FoContext object.
 * @new_keep_with_next_within_page: The new "keep-with-next-within-page" property value.
 * 
 * Sets the "keep-with-next-within-page" property of @fo_context to @new_keep_with_next_within_page.
 **/
void
fo_context_set_keep_with_next_within_page (FoContext *fo_context,
		         FoProperty *new_keep_with_next_within_page)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_with_next_within_page == NULL || FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE (new_keep_with_next_within_page));

  if (new_keep_with_next_within_page != NULL)
    {
      g_object_ref (new_keep_with_next_within_page);
    }
  if (fo_context->keep_with_next_within_page != NULL)
    {
      g_object_unref (fo_context->keep_with_next_within_page);
    }
  fo_context->keep_with_next_within_page = new_keep_with_next_within_page;
  /*g_object_notify (G_OBJECT (fo_context), "keep-with-next-within-page");*/
}

/**
 * fo_context_get_keep_with_previous:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-with-previous" property of @fo_context.
 *
 * Return value: The "keep-with-previous" property value.
**/
FoProperty *
fo_context_get_keep_with_previous (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_with_previous;
}

/**
 * fo_context_set_keep_with_previous:
 * @fo_context: The #FoContext object.
 * @new_keep_with_previous: The new "keep-with-previous" property value.
 * 
 * Sets the "keep-with-previous" property of @fo_context to @new_keep_with_previous.
 **/
void
fo_context_set_keep_with_previous (FoContext *fo_context,
		         FoProperty *new_keep_with_previous)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_with_previous == NULL || FO_IS_PROPERTY_KEEP_WITH_PREVIOUS (new_keep_with_previous));

  if (new_keep_with_previous != NULL)
    {
      g_object_ref (new_keep_with_previous);
    }
  if (fo_context->keep_with_previous != NULL)
    {
      g_object_unref (fo_context->keep_with_previous);
    }
  fo_context->keep_with_previous = new_keep_with_previous;
  /*g_object_notify (G_OBJECT (fo_context), "keep-with-previous");*/
}

/**
 * fo_context_get_keep_with_previous_within_column:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-with-previous-within-column" property of @fo_context.
 *
 * Return value: The "keep-with-previous-within-column" property value.
**/
FoProperty *
fo_context_get_keep_with_previous_within_column (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_with_previous_within_column;
}

/**
 * fo_context_set_keep_with_previous_within_column:
 * @fo_context: The #FoContext object.
 * @new_keep_with_previous_within_column: The new "keep-with-previous-within-column" property value.
 * 
 * Sets the "keep-with-previous-within-column" property of @fo_context to @new_keep_with_previous_within_column.
 **/
void
fo_context_set_keep_with_previous_within_column (FoContext *fo_context,
		         FoProperty *new_keep_with_previous_within_column)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_with_previous_within_column == NULL || FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_COLUMN (new_keep_with_previous_within_column));

  if (new_keep_with_previous_within_column != NULL)
    {
      g_object_ref (new_keep_with_previous_within_column);
    }
  if (fo_context->keep_with_previous_within_column != NULL)
    {
      g_object_unref (fo_context->keep_with_previous_within_column);
    }
  fo_context->keep_with_previous_within_column = new_keep_with_previous_within_column;
  /*g_object_notify (G_OBJECT (fo_context), "keep-with-previous-within-column");*/
}

/**
 * fo_context_get_keep_with_previous_within_line:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-with-previous-within-line" property of @fo_context.
 *
 * Return value: The "keep-with-previous-within-line" property value.
**/
FoProperty *
fo_context_get_keep_with_previous_within_line (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_with_previous_within_line;
}

/**
 * fo_context_set_keep_with_previous_within_line:
 * @fo_context: The #FoContext object.
 * @new_keep_with_previous_within_line: The new "keep-with-previous-within-line" property value.
 * 
 * Sets the "keep-with-previous-within-line" property of @fo_context to @new_keep_with_previous_within_line.
 **/
void
fo_context_set_keep_with_previous_within_line (FoContext *fo_context,
		         FoProperty *new_keep_with_previous_within_line)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_with_previous_within_line == NULL || FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_LINE (new_keep_with_previous_within_line));

  if (new_keep_with_previous_within_line != NULL)
    {
      g_object_ref (new_keep_with_previous_within_line);
    }
  if (fo_context->keep_with_previous_within_line != NULL)
    {
      g_object_unref (fo_context->keep_with_previous_within_line);
    }
  fo_context->keep_with_previous_within_line = new_keep_with_previous_within_line;
  /*g_object_notify (G_OBJECT (fo_context), "keep-with-previous-within-line");*/
}

/**
 * fo_context_get_keep_with_previous_within_page:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "keep-with-previous-within-page" property of @fo_context.
 *
 * Return value: The "keep-with-previous-within-page" property value.
**/
FoProperty *
fo_context_get_keep_with_previous_within_page (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->keep_with_previous_within_page;
}

/**
 * fo_context_set_keep_with_previous_within_page:
 * @fo_context: The #FoContext object.
 * @new_keep_with_previous_within_page: The new "keep-with-previous-within-page" property value.
 * 
 * Sets the "keep-with-previous-within-page" property of @fo_context to @new_keep_with_previous_within_page.
 **/
void
fo_context_set_keep_with_previous_within_page (FoContext *fo_context,
		         FoProperty *new_keep_with_previous_within_page)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_keep_with_previous_within_page == NULL || FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE (new_keep_with_previous_within_page));

  if (new_keep_with_previous_within_page != NULL)
    {
      g_object_ref (new_keep_with_previous_within_page);
    }
  if (fo_context->keep_with_previous_within_page != NULL)
    {
      g_object_unref (fo_context->keep_with_previous_within_page);
    }
  fo_context->keep_with_previous_within_page = new_keep_with_previous_within_page;
  /*g_object_notify (G_OBJECT (fo_context), "keep-with-previous-within-page");*/
}

/**
 * fo_context_get_letter_value:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "letter-value" property of @fo_context.
 *
 * Return value: The "letter-value" property value.
**/
FoProperty *
fo_context_get_letter_value (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->letter_value;
}

/**
 * fo_context_set_letter_value:
 * @fo_context: The #FoContext object.
 * @new_letter_value: The new "letter-value" property value.
 * 
 * Sets the "letter-value" property of @fo_context to @new_letter_value.
 **/
void
fo_context_set_letter_value (FoContext *fo_context,
		         FoProperty *new_letter_value)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_letter_value == NULL || FO_IS_PROPERTY_LETTER_VALUE (new_letter_value));

  if (new_letter_value != NULL)
    {
      g_object_ref (new_letter_value);
    }
  if (fo_context->letter_value != NULL)
    {
      g_object_unref (fo_context->letter_value);
    }
  fo_context->letter_value = new_letter_value;
  /*g_object_notify (G_OBJECT (fo_context), "letter-value");*/
}

/**
 * fo_context_get_line_height:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "line-height" property of @fo_context.
 *
 * Return value: The "line-height" property value.
**/
FoProperty *
fo_context_get_line_height (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->line_height;
}

/**
 * fo_context_set_line_height:
 * @fo_context: The #FoContext object.
 * @new_line_height: The new "line-height" property value.
 * 
 * Sets the "line-height" property of @fo_context to @new_line_height.
 **/
void
fo_context_set_line_height (FoContext *fo_context,
		         FoProperty *new_line_height)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_line_height == NULL || FO_IS_PROPERTY_LINE_HEIGHT (new_line_height));

  if (new_line_height != NULL)
    {
      g_object_ref (new_line_height);
    }
  if (fo_context->line_height != NULL)
    {
      g_object_unref (fo_context->line_height);
    }
  fo_context->line_height = new_line_height;
  /*g_object_notify (G_OBJECT (fo_context), "line-height");*/
}

/**
 * fo_context_get_line_stacking_strategy:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "line-stacking-strategy" property of @fo_context.
 *
 * Return value: The "line-stacking-strategy" property value.
**/
FoProperty *
fo_context_get_line_stacking_strategy (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->line_stacking_strategy;
}

/**
 * fo_context_set_line_stacking_strategy:
 * @fo_context: The #FoContext object.
 * @new_line_stacking_strategy: The new "line-stacking-strategy" property value.
 * 
 * Sets the "line-stacking-strategy" property of @fo_context to @new_line_stacking_strategy.
 **/
void
fo_context_set_line_stacking_strategy (FoContext *fo_context,
		         FoProperty *new_line_stacking_strategy)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_line_stacking_strategy == NULL || FO_IS_PROPERTY_LINE_STACKING_STRATEGY (new_line_stacking_strategy));

  if (new_line_stacking_strategy != NULL)
    {
      g_object_ref (new_line_stacking_strategy);
    }
  if (fo_context->line_stacking_strategy != NULL)
    {
      g_object_unref (fo_context->line_stacking_strategy);
    }
  fo_context->line_stacking_strategy = new_line_stacking_strategy;
  /*g_object_notify (G_OBJECT (fo_context), "line-stacking-strategy");*/
}

/**
 * fo_context_get_linefeed_treatment:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "linefeed-treatment" property of @fo_context.
 *
 * Return value: The "linefeed-treatment" property value.
**/
FoProperty *
fo_context_get_linefeed_treatment (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->linefeed_treatment;
}

/**
 * fo_context_set_linefeed_treatment:
 * @fo_context: The #FoContext object.
 * @new_linefeed_treatment: The new "linefeed-treatment" property value.
 * 
 * Sets the "linefeed-treatment" property of @fo_context to @new_linefeed_treatment.
 **/
void
fo_context_set_linefeed_treatment (FoContext *fo_context,
		         FoProperty *new_linefeed_treatment)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_linefeed_treatment == NULL || FO_IS_PROPERTY_LINEFEED_TREATMENT (new_linefeed_treatment));

  if (new_linefeed_treatment != NULL)
    {
      g_object_ref (new_linefeed_treatment);
    }
  if (fo_context->linefeed_treatment != NULL)
    {
      g_object_unref (fo_context->linefeed_treatment);
    }
  fo_context->linefeed_treatment = new_linefeed_treatment;
  /*g_object_notify (G_OBJECT (fo_context), "linefeed-treatment");*/
}

/**
 * fo_context_get_margin:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "margin" property of @fo_context.
 *
 * Return value: The "margin" property value.
**/
FoProperty *
fo_context_get_margin (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->margin;
}

/**
 * fo_context_set_margin:
 * @fo_context: The #FoContext object.
 * @new_margin: The new "margin" property value.
 * 
 * Sets the "margin" property of @fo_context to @new_margin.
 **/
void
fo_context_set_margin (FoContext *fo_context,
		         FoProperty *new_margin)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_margin == NULL || FO_IS_PROPERTY_MARGIN (new_margin));

  if (new_margin != NULL)
    {
      g_object_ref (new_margin);
    }
  if (fo_context->margin != NULL)
    {
      g_object_unref (fo_context->margin);
    }
  fo_context->margin = new_margin;
  /*g_object_notify (G_OBJECT (fo_context), "margin");*/
}

/**
 * fo_context_get_margin_bottom:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "margin-bottom" property of @fo_context.
 *
 * Return value: The "margin-bottom" property value.
**/
FoProperty *
fo_context_get_margin_bottom (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->margin_bottom;
}

/**
 * fo_context_set_margin_bottom:
 * @fo_context: The #FoContext object.
 * @new_margin_bottom: The new "margin-bottom" property value.
 * 
 * Sets the "margin-bottom" property of @fo_context to @new_margin_bottom.
 **/
void
fo_context_set_margin_bottom (FoContext *fo_context,
		         FoProperty *new_margin_bottom)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_margin_bottom == NULL || FO_IS_PROPERTY_MARGIN_BOTTOM (new_margin_bottom));

  if (new_margin_bottom != NULL)
    {
      g_object_ref (new_margin_bottom);
    }
  if (fo_context->margin_bottom != NULL)
    {
      g_object_unref (fo_context->margin_bottom);
    }
  fo_context->margin_bottom = new_margin_bottom;
  /*g_object_notify (G_OBJECT (fo_context), "margin-bottom");*/
}

/**
 * fo_context_get_margin_left:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "margin-left" property of @fo_context.
 *
 * Return value: The "margin-left" property value.
**/
FoProperty *
fo_context_get_margin_left (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->margin_left;
}

/**
 * fo_context_set_margin_left:
 * @fo_context: The #FoContext object.
 * @new_margin_left: The new "margin-left" property value.
 * 
 * Sets the "margin-left" property of @fo_context to @new_margin_left.
 **/
void
fo_context_set_margin_left (FoContext *fo_context,
		         FoProperty *new_margin_left)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_margin_left == NULL || FO_IS_PROPERTY_MARGIN_LEFT (new_margin_left));

  if (new_margin_left != NULL)
    {
      g_object_ref (new_margin_left);
    }
  if (fo_context->margin_left != NULL)
    {
      g_object_unref (fo_context->margin_left);
    }
  fo_context->margin_left = new_margin_left;
  /*g_object_notify (G_OBJECT (fo_context), "margin-left");*/
}

/**
 * fo_context_get_margin_right:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "margin-right" property of @fo_context.
 *
 * Return value: The "margin-right" property value.
**/
FoProperty *
fo_context_get_margin_right (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->margin_right;
}

/**
 * fo_context_set_margin_right:
 * @fo_context: The #FoContext object.
 * @new_margin_right: The new "margin-right" property value.
 * 
 * Sets the "margin-right" property of @fo_context to @new_margin_right.
 **/
void
fo_context_set_margin_right (FoContext *fo_context,
		         FoProperty *new_margin_right)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_margin_right == NULL || FO_IS_PROPERTY_MARGIN_RIGHT (new_margin_right));

  if (new_margin_right != NULL)
    {
      g_object_ref (new_margin_right);
    }
  if (fo_context->margin_right != NULL)
    {
      g_object_unref (fo_context->margin_right);
    }
  fo_context->margin_right = new_margin_right;
  /*g_object_notify (G_OBJECT (fo_context), "margin-right");*/
}

/**
 * fo_context_get_margin_top:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "margin-top" property of @fo_context.
 *
 * Return value: The "margin-top" property value.
**/
FoProperty *
fo_context_get_margin_top (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->margin_top;
}

/**
 * fo_context_set_margin_top:
 * @fo_context: The #FoContext object.
 * @new_margin_top: The new "margin-top" property value.
 * 
 * Sets the "margin-top" property of @fo_context to @new_margin_top.
 **/
void
fo_context_set_margin_top (FoContext *fo_context,
		         FoProperty *new_margin_top)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_margin_top == NULL || FO_IS_PROPERTY_MARGIN_TOP (new_margin_top));

  if (new_margin_top != NULL)
    {
      g_object_ref (new_margin_top);
    }
  if (fo_context->margin_top != NULL)
    {
      g_object_unref (fo_context->margin_top);
    }
  fo_context->margin_top = new_margin_top;
  /*g_object_notify (G_OBJECT (fo_context), "margin-top");*/
}

/**
 * fo_context_get_master_name:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "master-name" property of @fo_context.
 *
 * Return value: The "master-name" property value.
**/
FoProperty *
fo_context_get_master_name (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->master_name;
}

/**
 * fo_context_set_master_name:
 * @fo_context: The #FoContext object.
 * @new_master_name: The new "master-name" property value.
 * 
 * Sets the "master-name" property of @fo_context to @new_master_name.
 **/
void
fo_context_set_master_name (FoContext *fo_context,
		         FoProperty *new_master_name)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_master_name == NULL || FO_IS_PROPERTY_MASTER_NAME (new_master_name));

  if (new_master_name != NULL)
    {
      g_object_ref (new_master_name);
    }
  if (fo_context->master_name != NULL)
    {
      g_object_unref (fo_context->master_name);
    }
  fo_context->master_name = new_master_name;
  /*g_object_notify (G_OBJECT (fo_context), "master-name");*/
}

/**
 * fo_context_get_master_reference:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "master-reference" property of @fo_context.
 *
 * Return value: The "master-reference" property value.
**/
FoProperty *
fo_context_get_master_reference (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->master_reference;
}

/**
 * fo_context_set_master_reference:
 * @fo_context: The #FoContext object.
 * @new_master_reference: The new "master-reference" property value.
 * 
 * Sets the "master-reference" property of @fo_context to @new_master_reference.
 **/
void
fo_context_set_master_reference (FoContext *fo_context,
		         FoProperty *new_master_reference)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_master_reference == NULL || FO_IS_PROPERTY_MASTER_REFERENCE (new_master_reference));

  if (new_master_reference != NULL)
    {
      g_object_ref (new_master_reference);
    }
  if (fo_context->master_reference != NULL)
    {
      g_object_unref (fo_context->master_reference);
    }
  fo_context->master_reference = new_master_reference;
  /*g_object_notify (G_OBJECT (fo_context), "master-reference");*/
}

/**
 * fo_context_get_media_usage:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "media-usage" property of @fo_context.
 *
 * Return value: The "media-usage" property value.
**/
FoProperty *
fo_context_get_media_usage (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->media_usage;
}

/**
 * fo_context_set_media_usage:
 * @fo_context: The #FoContext object.
 * @new_media_usage: The new "media-usage" property value.
 * 
 * Sets the "media-usage" property of @fo_context to @new_media_usage.
 **/
void
fo_context_set_media_usage (FoContext *fo_context,
		         FoProperty *new_media_usage)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_media_usage == NULL || FO_IS_PROPERTY_MEDIA_USAGE (new_media_usage));

  if (new_media_usage != NULL)
    {
      g_object_ref (new_media_usage);
    }
  if (fo_context->media_usage != NULL)
    {
      g_object_unref (fo_context->media_usage);
    }
  fo_context->media_usage = new_media_usage;
  /*g_object_notify (G_OBJECT (fo_context), "media-usage");*/
}

/**
 * fo_context_get_number_columns_repeated:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "number-columns-repeated" property of @fo_context.
 *
 * Return value: The "number-columns-repeated" property value.
**/
FoProperty *
fo_context_get_number_columns_repeated (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->number_columns_repeated;
}

/**
 * fo_context_set_number_columns_repeated:
 * @fo_context: The #FoContext object.
 * @new_number_columns_repeated: The new "number-columns-repeated" property value.
 * 
 * Sets the "number-columns-repeated" property of @fo_context to @new_number_columns_repeated.
 **/
void
fo_context_set_number_columns_repeated (FoContext *fo_context,
		         FoProperty *new_number_columns_repeated)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_number_columns_repeated == NULL || FO_IS_PROPERTY_NUMBER_COLUMNS_REPEATED (new_number_columns_repeated));

  if (new_number_columns_repeated != NULL)
    {
      g_object_ref (new_number_columns_repeated);
    }
  if (fo_context->number_columns_repeated != NULL)
    {
      g_object_unref (fo_context->number_columns_repeated);
    }
  fo_context->number_columns_repeated = new_number_columns_repeated;
  /*g_object_notify (G_OBJECT (fo_context), "number-columns-repeated");*/
}

/**
 * fo_context_get_number_columns_spanned:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "number-columns-spanned" property of @fo_context.
 *
 * Return value: The "number-columns-spanned" property value.
**/
FoProperty *
fo_context_get_number_columns_spanned (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->number_columns_spanned;
}

/**
 * fo_context_set_number_columns_spanned:
 * @fo_context: The #FoContext object.
 * @new_number_columns_spanned: The new "number-columns-spanned" property value.
 * 
 * Sets the "number-columns-spanned" property of @fo_context to @new_number_columns_spanned.
 **/
void
fo_context_set_number_columns_spanned (FoContext *fo_context,
		         FoProperty *new_number_columns_spanned)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_number_columns_spanned == NULL || FO_IS_PROPERTY_NUMBER_COLUMNS_SPANNED (new_number_columns_spanned));

  if (new_number_columns_spanned != NULL)
    {
      g_object_ref (new_number_columns_spanned);
    }
  if (fo_context->number_columns_spanned != NULL)
    {
      g_object_unref (fo_context->number_columns_spanned);
    }
  fo_context->number_columns_spanned = new_number_columns_spanned;
  /*g_object_notify (G_OBJECT (fo_context), "number-columns-spanned");*/
}

/**
 * fo_context_get_number_rows_spanned:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "number-rows-spanned" property of @fo_context.
 *
 * Return value: The "number-rows-spanned" property value.
**/
FoProperty *
fo_context_get_number_rows_spanned (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->number_rows_spanned;
}

/**
 * fo_context_set_number_rows_spanned:
 * @fo_context: The #FoContext object.
 * @new_number_rows_spanned: The new "number-rows-spanned" property value.
 * 
 * Sets the "number-rows-spanned" property of @fo_context to @new_number_rows_spanned.
 **/
void
fo_context_set_number_rows_spanned (FoContext *fo_context,
		         FoProperty *new_number_rows_spanned)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_number_rows_spanned == NULL || FO_IS_PROPERTY_NUMBER_ROWS_SPANNED (new_number_rows_spanned));

  if (new_number_rows_spanned != NULL)
    {
      g_object_ref (new_number_rows_spanned);
    }
  if (fo_context->number_rows_spanned != NULL)
    {
      g_object_unref (fo_context->number_rows_spanned);
    }
  fo_context->number_rows_spanned = new_number_rows_spanned;
  /*g_object_notify (G_OBJECT (fo_context), "number-rows-spanned");*/
}

/**
 * fo_context_get_orphans:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "orphans" property of @fo_context.
 *
 * Return value: The "orphans" property value.
**/
FoProperty *
fo_context_get_orphans (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->orphans;
}

/**
 * fo_context_set_orphans:
 * @fo_context: The #FoContext object.
 * @new_orphans: The new "orphans" property value.
 * 
 * Sets the "orphans" property of @fo_context to @new_orphans.
 **/
void
fo_context_set_orphans (FoContext *fo_context,
		         FoProperty *new_orphans)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_orphans == NULL || FO_IS_PROPERTY_ORPHANS (new_orphans));

  if (new_orphans != NULL)
    {
      g_object_ref (new_orphans);
    }
  if (fo_context->orphans != NULL)
    {
      g_object_unref (fo_context->orphans);
    }
  fo_context->orphans = new_orphans;
  /*g_object_notify (G_OBJECT (fo_context), "orphans");*/
}

/**
 * fo_context_get_overflow:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "overflow" property of @fo_context.
 *
 * Return value: The "overflow" property value.
**/
FoProperty *
fo_context_get_overflow (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->overflow;
}

/**
 * fo_context_set_overflow:
 * @fo_context: The #FoContext object.
 * @new_overflow: The new "overflow" property value.
 * 
 * Sets the "overflow" property of @fo_context to @new_overflow.
 **/
void
fo_context_set_overflow (FoContext *fo_context,
		         FoProperty *new_overflow)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_overflow == NULL || FO_IS_PROPERTY_OVERFLOW (new_overflow));

  if (new_overflow != NULL)
    {
      g_object_ref (new_overflow);
    }
  if (fo_context->overflow != NULL)
    {
      g_object_unref (fo_context->overflow);
    }
  fo_context->overflow = new_overflow;
  /*g_object_notify (G_OBJECT (fo_context), "overflow");*/
}

/**
 * fo_context_get_padding:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding" property of @fo_context.
 *
 * Return value: The "padding" property value.
**/
FoProperty *
fo_context_get_padding (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding;
}

/**
 * fo_context_set_padding:
 * @fo_context: The #FoContext object.
 * @new_padding: The new "padding" property value.
 * 
 * Sets the "padding" property of @fo_context to @new_padding.
 **/
void
fo_context_set_padding (FoContext *fo_context,
		         FoProperty *new_padding)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding == NULL || FO_IS_PROPERTY_PADDING (new_padding));

  if (new_padding != NULL)
    {
      g_object_ref (new_padding);
    }
  if (fo_context->padding != NULL)
    {
      g_object_unref (fo_context->padding);
    }
  fo_context->padding = new_padding;
  /*g_object_notify (G_OBJECT (fo_context), "padding");*/
}

/**
 * fo_context_get_padding_after:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-after" property of @fo_context.
 *
 * Return value: The "padding-after" property value.
**/
FoProperty *
fo_context_get_padding_after (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_after;
}

/**
 * fo_context_set_padding_after:
 * @fo_context: The #FoContext object.
 * @new_padding_after: The new "padding-after" property value.
 * 
 * Sets the "padding-after" property of @fo_context to @new_padding_after.
 **/
void
fo_context_set_padding_after (FoContext *fo_context,
		         FoProperty *new_padding_after)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_after == NULL || FO_IS_PROPERTY_PADDING_AFTER (new_padding_after));

  if (new_padding_after != NULL)
    {
      g_object_ref (new_padding_after);
    }
  if (fo_context->padding_after != NULL)
    {
      g_object_unref (fo_context->padding_after);
    }
  fo_context->padding_after = new_padding_after;
  /*g_object_notify (G_OBJECT (fo_context), "padding-after");*/
}

/**
 * fo_context_get_padding_after_length:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-after-length" property of @fo_context.
 *
 * Return value: The "padding-after-length" property value.
**/
FoProperty *
fo_context_get_padding_after_length (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_after_length;
}

/**
 * fo_context_set_padding_after_length:
 * @fo_context: The #FoContext object.
 * @new_padding_after_length: The new "padding-after-length" property value.
 * 
 * Sets the "padding-after-length" property of @fo_context to @new_padding_after_length.
 **/
void
fo_context_set_padding_after_length (FoContext *fo_context,
		         FoProperty *new_padding_after_length)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_after_length == NULL || FO_IS_PROPERTY_PADDING_AFTER_LENGTH (new_padding_after_length));

  if (new_padding_after_length != NULL)
    {
      g_object_ref (new_padding_after_length);
    }
  if (fo_context->padding_after_length != NULL)
    {
      g_object_unref (fo_context->padding_after_length);
    }
  fo_context->padding_after_length = new_padding_after_length;
  /*g_object_notify (G_OBJECT (fo_context), "padding-after-length");*/
}

/**
 * fo_context_get_padding_after_condity:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-after-conditionality" property of @fo_context.
 *
 * Return value: The "padding-after-conditionality" property value.
**/
FoProperty *
fo_context_get_padding_after_condity (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_after_condity;
}

/**
 * fo_context_set_padding_after_condity:
 * @fo_context: The #FoContext object.
 * @new_padding_after_condity: The new "padding-after-conditionality" property value.
 * 
 * Sets the "padding-after-conditionality" property of @fo_context to @new_padding_after_condity.
 **/
void
fo_context_set_padding_after_condity (FoContext *fo_context,
		         FoProperty *new_padding_after_condity)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_after_condity == NULL || FO_IS_PROPERTY_PADDING_AFTER_CONDITY (new_padding_after_condity));

  if (new_padding_after_condity != NULL)
    {
      g_object_ref (new_padding_after_condity);
    }
  if (fo_context->padding_after_condity != NULL)
    {
      g_object_unref (fo_context->padding_after_condity);
    }
  fo_context->padding_after_condity = new_padding_after_condity;
  /*g_object_notify (G_OBJECT (fo_context), "padding-after-conditionality");*/
}

/**
 * fo_context_get_padding_before:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-before" property of @fo_context.
 *
 * Return value: The "padding-before" property value.
**/
FoProperty *
fo_context_get_padding_before (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_before;
}

/**
 * fo_context_set_padding_before:
 * @fo_context: The #FoContext object.
 * @new_padding_before: The new "padding-before" property value.
 * 
 * Sets the "padding-before" property of @fo_context to @new_padding_before.
 **/
void
fo_context_set_padding_before (FoContext *fo_context,
		         FoProperty *new_padding_before)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_before == NULL || FO_IS_PROPERTY_PADDING_BEFORE (new_padding_before));

  if (new_padding_before != NULL)
    {
      g_object_ref (new_padding_before);
    }
  if (fo_context->padding_before != NULL)
    {
      g_object_unref (fo_context->padding_before);
    }
  fo_context->padding_before = new_padding_before;
  /*g_object_notify (G_OBJECT (fo_context), "padding-before");*/
}

/**
 * fo_context_get_padding_before_length:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-before-length" property of @fo_context.
 *
 * Return value: The "padding-before-length" property value.
**/
FoProperty *
fo_context_get_padding_before_length (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_before_length;
}

/**
 * fo_context_set_padding_before_length:
 * @fo_context: The #FoContext object.
 * @new_padding_before_length: The new "padding-before-length" property value.
 * 
 * Sets the "padding-before-length" property of @fo_context to @new_padding_before_length.
 **/
void
fo_context_set_padding_before_length (FoContext *fo_context,
		         FoProperty *new_padding_before_length)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_before_length == NULL || FO_IS_PROPERTY_PADDING_BEFORE_LENGTH (new_padding_before_length));

  if (new_padding_before_length != NULL)
    {
      g_object_ref (new_padding_before_length);
    }
  if (fo_context->padding_before_length != NULL)
    {
      g_object_unref (fo_context->padding_before_length);
    }
  fo_context->padding_before_length = new_padding_before_length;
  /*g_object_notify (G_OBJECT (fo_context), "padding-before-length");*/
}

/**
 * fo_context_get_padding_before_condity:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-before-conditionality" property of @fo_context.
 *
 * Return value: The "padding-before-conditionality" property value.
**/
FoProperty *
fo_context_get_padding_before_condity (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_before_condity;
}

/**
 * fo_context_set_padding_before_condity:
 * @fo_context: The #FoContext object.
 * @new_padding_before_condity: The new "padding-before-conditionality" property value.
 * 
 * Sets the "padding-before-conditionality" property of @fo_context to @new_padding_before_condity.
 **/
void
fo_context_set_padding_before_condity (FoContext *fo_context,
		         FoProperty *new_padding_before_condity)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_before_condity == NULL || FO_IS_PROPERTY_PADDING_BEFORE_CONDITY (new_padding_before_condity));

  if (new_padding_before_condity != NULL)
    {
      g_object_ref (new_padding_before_condity);
    }
  if (fo_context->padding_before_condity != NULL)
    {
      g_object_unref (fo_context->padding_before_condity);
    }
  fo_context->padding_before_condity = new_padding_before_condity;
  /*g_object_notify (G_OBJECT (fo_context), "padding-before-conditionality");*/
}

/**
 * fo_context_get_padding_bottom:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-bottom" property of @fo_context.
 *
 * Return value: The "padding-bottom" property value.
**/
FoProperty *
fo_context_get_padding_bottom (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_bottom;
}

/**
 * fo_context_set_padding_bottom:
 * @fo_context: The #FoContext object.
 * @new_padding_bottom: The new "padding-bottom" property value.
 * 
 * Sets the "padding-bottom" property of @fo_context to @new_padding_bottom.
 **/
void
fo_context_set_padding_bottom (FoContext *fo_context,
		         FoProperty *new_padding_bottom)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_bottom == NULL || FO_IS_PROPERTY_PADDING_BOTTOM (new_padding_bottom));

  if (new_padding_bottom != NULL)
    {
      g_object_ref (new_padding_bottom);
    }
  if (fo_context->padding_bottom != NULL)
    {
      g_object_unref (fo_context->padding_bottom);
    }
  fo_context->padding_bottom = new_padding_bottom;
  /*g_object_notify (G_OBJECT (fo_context), "padding-bottom");*/
}

/**
 * fo_context_get_padding_end:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-end" property of @fo_context.
 *
 * Return value: The "padding-end" property value.
**/
FoProperty *
fo_context_get_padding_end (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_end;
}

/**
 * fo_context_set_padding_end:
 * @fo_context: The #FoContext object.
 * @new_padding_end: The new "padding-end" property value.
 * 
 * Sets the "padding-end" property of @fo_context to @new_padding_end.
 **/
void
fo_context_set_padding_end (FoContext *fo_context,
		         FoProperty *new_padding_end)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_end == NULL || FO_IS_PROPERTY_PADDING_END (new_padding_end));

  if (new_padding_end != NULL)
    {
      g_object_ref (new_padding_end);
    }
  if (fo_context->padding_end != NULL)
    {
      g_object_unref (fo_context->padding_end);
    }
  fo_context->padding_end = new_padding_end;
  /*g_object_notify (G_OBJECT (fo_context), "padding-end");*/
}

/**
 * fo_context_get_padding_end_length:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-end-length" property of @fo_context.
 *
 * Return value: The "padding-end-length" property value.
**/
FoProperty *
fo_context_get_padding_end_length (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_end_length;
}

/**
 * fo_context_set_padding_end_length:
 * @fo_context: The #FoContext object.
 * @new_padding_end_length: The new "padding-end-length" property value.
 * 
 * Sets the "padding-end-length" property of @fo_context to @new_padding_end_length.
 **/
void
fo_context_set_padding_end_length (FoContext *fo_context,
		         FoProperty *new_padding_end_length)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_end_length == NULL || FO_IS_PROPERTY_PADDING_END_LENGTH (new_padding_end_length));

  if (new_padding_end_length != NULL)
    {
      g_object_ref (new_padding_end_length);
    }
  if (fo_context->padding_end_length != NULL)
    {
      g_object_unref (fo_context->padding_end_length);
    }
  fo_context->padding_end_length = new_padding_end_length;
  /*g_object_notify (G_OBJECT (fo_context), "padding-end-length");*/
}

/**
 * fo_context_get_padding_end_condity:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-end-conditionality" property of @fo_context.
 *
 * Return value: The "padding-end-conditionality" property value.
**/
FoProperty *
fo_context_get_padding_end_condity (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_end_condity;
}

/**
 * fo_context_set_padding_end_condity:
 * @fo_context: The #FoContext object.
 * @new_padding_end_condity: The new "padding-end-conditionality" property value.
 * 
 * Sets the "padding-end-conditionality" property of @fo_context to @new_padding_end_condity.
 **/
void
fo_context_set_padding_end_condity (FoContext *fo_context,
		         FoProperty *new_padding_end_condity)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_end_condity == NULL || FO_IS_PROPERTY_PADDING_END_CONDITY (new_padding_end_condity));

  if (new_padding_end_condity != NULL)
    {
      g_object_ref (new_padding_end_condity);
    }
  if (fo_context->padding_end_condity != NULL)
    {
      g_object_unref (fo_context->padding_end_condity);
    }
  fo_context->padding_end_condity = new_padding_end_condity;
  /*g_object_notify (G_OBJECT (fo_context), "padding-end-conditionality");*/
}

/**
 * fo_context_get_padding_left:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-left" property of @fo_context.
 *
 * Return value: The "padding-left" property value.
**/
FoProperty *
fo_context_get_padding_left (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_left;
}

/**
 * fo_context_set_padding_left:
 * @fo_context: The #FoContext object.
 * @new_padding_left: The new "padding-left" property value.
 * 
 * Sets the "padding-left" property of @fo_context to @new_padding_left.
 **/
void
fo_context_set_padding_left (FoContext *fo_context,
		         FoProperty *new_padding_left)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_left == NULL || FO_IS_PROPERTY_PADDING_LEFT (new_padding_left));

  if (new_padding_left != NULL)
    {
      g_object_ref (new_padding_left);
    }
  if (fo_context->padding_left != NULL)
    {
      g_object_unref (fo_context->padding_left);
    }
  fo_context->padding_left = new_padding_left;
  /*g_object_notify (G_OBJECT (fo_context), "padding-left");*/
}

/**
 * fo_context_get_padding_right:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-right" property of @fo_context.
 *
 * Return value: The "padding-right" property value.
**/
FoProperty *
fo_context_get_padding_right (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_right;
}

/**
 * fo_context_set_padding_right:
 * @fo_context: The #FoContext object.
 * @new_padding_right: The new "padding-right" property value.
 * 
 * Sets the "padding-right" property of @fo_context to @new_padding_right.
 **/
void
fo_context_set_padding_right (FoContext *fo_context,
		         FoProperty *new_padding_right)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_right == NULL || FO_IS_PROPERTY_PADDING_RIGHT (new_padding_right));

  if (new_padding_right != NULL)
    {
      g_object_ref (new_padding_right);
    }
  if (fo_context->padding_right != NULL)
    {
      g_object_unref (fo_context->padding_right);
    }
  fo_context->padding_right = new_padding_right;
  /*g_object_notify (G_OBJECT (fo_context), "padding-right");*/
}

/**
 * fo_context_get_padding_start:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-start" property of @fo_context.
 *
 * Return value: The "padding-start" property value.
**/
FoProperty *
fo_context_get_padding_start (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_start;
}

/**
 * fo_context_set_padding_start:
 * @fo_context: The #FoContext object.
 * @new_padding_start: The new "padding-start" property value.
 * 
 * Sets the "padding-start" property of @fo_context to @new_padding_start.
 **/
void
fo_context_set_padding_start (FoContext *fo_context,
		         FoProperty *new_padding_start)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_start == NULL || FO_IS_PROPERTY_PADDING_START (new_padding_start));

  if (new_padding_start != NULL)
    {
      g_object_ref (new_padding_start);
    }
  if (fo_context->padding_start != NULL)
    {
      g_object_unref (fo_context->padding_start);
    }
  fo_context->padding_start = new_padding_start;
  /*g_object_notify (G_OBJECT (fo_context), "padding-start");*/
}

/**
 * fo_context_get_padding_start_length:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-start-length" property of @fo_context.
 *
 * Return value: The "padding-start-length" property value.
**/
FoProperty *
fo_context_get_padding_start_length (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_start_length;
}

/**
 * fo_context_set_padding_start_length:
 * @fo_context: The #FoContext object.
 * @new_padding_start_length: The new "padding-start-length" property value.
 * 
 * Sets the "padding-start-length" property of @fo_context to @new_padding_start_length.
 **/
void
fo_context_set_padding_start_length (FoContext *fo_context,
		         FoProperty *new_padding_start_length)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_start_length == NULL || FO_IS_PROPERTY_PADDING_START_LENGTH (new_padding_start_length));

  if (new_padding_start_length != NULL)
    {
      g_object_ref (new_padding_start_length);
    }
  if (fo_context->padding_start_length != NULL)
    {
      g_object_unref (fo_context->padding_start_length);
    }
  fo_context->padding_start_length = new_padding_start_length;
  /*g_object_notify (G_OBJECT (fo_context), "padding-start-length");*/
}

/**
 * fo_context_get_padding_start_condity:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-start-conditionality" property of @fo_context.
 *
 * Return value: The "padding-start-conditionality" property value.
**/
FoProperty *
fo_context_get_padding_start_condity (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_start_condity;
}

/**
 * fo_context_set_padding_start_condity:
 * @fo_context: The #FoContext object.
 * @new_padding_start_condity: The new "padding-start-conditionality" property value.
 * 
 * Sets the "padding-start-conditionality" property of @fo_context to @new_padding_start_condity.
 **/
void
fo_context_set_padding_start_condity (FoContext *fo_context,
		         FoProperty *new_padding_start_condity)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_start_condity == NULL || FO_IS_PROPERTY_PADDING_START_CONDITY (new_padding_start_condity));

  if (new_padding_start_condity != NULL)
    {
      g_object_ref (new_padding_start_condity);
    }
  if (fo_context->padding_start_condity != NULL)
    {
      g_object_unref (fo_context->padding_start_condity);
    }
  fo_context->padding_start_condity = new_padding_start_condity;
  /*g_object_notify (G_OBJECT (fo_context), "padding-start-conditionality");*/
}

/**
 * fo_context_get_padding_top:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "padding-top" property of @fo_context.
 *
 * Return value: The "padding-top" property value.
**/
FoProperty *
fo_context_get_padding_top (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->padding_top;
}

/**
 * fo_context_set_padding_top:
 * @fo_context: The #FoContext object.
 * @new_padding_top: The new "padding-top" property value.
 * 
 * Sets the "padding-top" property of @fo_context to @new_padding_top.
 **/
void
fo_context_set_padding_top (FoContext *fo_context,
		         FoProperty *new_padding_top)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_padding_top == NULL || FO_IS_PROPERTY_PADDING_TOP (new_padding_top));

  if (new_padding_top != NULL)
    {
      g_object_ref (new_padding_top);
    }
  if (fo_context->padding_top != NULL)
    {
      g_object_unref (fo_context->padding_top);
    }
  fo_context->padding_top = new_padding_top;
  /*g_object_notify (G_OBJECT (fo_context), "padding-top");*/
}

/**
 * fo_context_get_page_height:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "page-height" property of @fo_context.
 *
 * Return value: The "page-height" property value.
**/
FoProperty *
fo_context_get_page_height (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->page_height;
}

/**
 * fo_context_set_page_height:
 * @fo_context: The #FoContext object.
 * @new_page_height: The new "page-height" property value.
 * 
 * Sets the "page-height" property of @fo_context to @new_page_height.
 **/
void
fo_context_set_page_height (FoContext *fo_context,
		         FoProperty *new_page_height)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_page_height == NULL || FO_IS_PROPERTY_PAGE_HEIGHT (new_page_height));

  if (new_page_height != NULL)
    {
      g_object_ref (new_page_height);
    }
  if (fo_context->page_height != NULL)
    {
      g_object_unref (fo_context->page_height);
    }
  fo_context->page_height = new_page_height;
  /*g_object_notify (G_OBJECT (fo_context), "page-height");*/
}

/**
 * fo_context_get_page_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "page-width" property of @fo_context.
 *
 * Return value: The "page-width" property value.
**/
FoProperty *
fo_context_get_page_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->page_width;
}

/**
 * fo_context_set_page_width:
 * @fo_context: The #FoContext object.
 * @new_page_width: The new "page-width" property value.
 * 
 * Sets the "page-width" property of @fo_context to @new_page_width.
 **/
void
fo_context_set_page_width (FoContext *fo_context,
		         FoProperty *new_page_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_page_width == NULL || FO_IS_PROPERTY_PAGE_WIDTH (new_page_width));

  if (new_page_width != NULL)
    {
      g_object_ref (new_page_width);
    }
  if (fo_context->page_width != NULL)
    {
      g_object_unref (fo_context->page_width);
    }
  fo_context->page_width = new_page_width;
  /*g_object_notify (G_OBJECT (fo_context), "page-width");*/
}

/**
 * fo_context_get_provisional_distance_between_starts:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "provisional-distance-between-starts" property of @fo_context.
 *
 * Return value: The "provisional-distance-between-starts" property value.
**/
FoProperty *
fo_context_get_provisional_distance_between_starts (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->provisional_distance_between_starts;
}

/**
 * fo_context_set_provisional_distance_between_starts:
 * @fo_context: The #FoContext object.
 * @new_provisional_distance_between_starts: The new "provisional-distance-between-starts" property value.
 * 
 * Sets the "provisional-distance-between-starts" property of @fo_context to @new_provisional_distance_between_starts.
 **/
void
fo_context_set_provisional_distance_between_starts (FoContext *fo_context,
		         FoProperty *new_provisional_distance_between_starts)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_provisional_distance_between_starts == NULL || FO_IS_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS (new_provisional_distance_between_starts));

  if (new_provisional_distance_between_starts != NULL)
    {
      g_object_ref (new_provisional_distance_between_starts);
    }
  if (fo_context->provisional_distance_between_starts != NULL)
    {
      g_object_unref (fo_context->provisional_distance_between_starts);
    }
  fo_context->provisional_distance_between_starts = new_provisional_distance_between_starts;
  /*g_object_notify (G_OBJECT (fo_context), "provisional-distance-between-starts");*/
}

/**
 * fo_context_get_provisional_label_separation:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "provisional-label-separation" property of @fo_context.
 *
 * Return value: The "provisional-label-separation" property value.
**/
FoProperty *
fo_context_get_provisional_label_separation (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->provisional_label_separation;
}

/**
 * fo_context_set_provisional_label_separation:
 * @fo_context: The #FoContext object.
 * @new_provisional_label_separation: The new "provisional-label-separation" property value.
 * 
 * Sets the "provisional-label-separation" property of @fo_context to @new_provisional_label_separation.
 **/
void
fo_context_set_provisional_label_separation (FoContext *fo_context,
		         FoProperty *new_provisional_label_separation)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_provisional_label_separation == NULL || FO_IS_PROPERTY_PROVISIONAL_LABEL_SEPARATION (new_provisional_label_separation));

  if (new_provisional_label_separation != NULL)
    {
      g_object_ref (new_provisional_label_separation);
    }
  if (fo_context->provisional_label_separation != NULL)
    {
      g_object_unref (fo_context->provisional_label_separation);
    }
  fo_context->provisional_label_separation = new_provisional_label_separation;
  /*g_object_notify (G_OBJECT (fo_context), "provisional-label-separation");*/
}

/**
 * fo_context_get_ref_id:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "ref-id" property of @fo_context.
 *
 * Return value: The "ref-id" property value.
**/
FoProperty *
fo_context_get_ref_id (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->ref_id;
}

/**
 * fo_context_set_ref_id:
 * @fo_context: The #FoContext object.
 * @new_ref_id: The new "ref-id" property value.
 * 
 * Sets the "ref-id" property of @fo_context to @new_ref_id.
 **/
void
fo_context_set_ref_id (FoContext *fo_context,
		         FoProperty *new_ref_id)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_ref_id == NULL || FO_IS_PROPERTY_REF_ID (new_ref_id));

  if (new_ref_id != NULL)
    {
      g_object_ref (new_ref_id);
    }
  if (fo_context->ref_id != NULL)
    {
      g_object_unref (fo_context->ref_id);
    }
  fo_context->ref_id = new_ref_id;
  /*g_object_notify (G_OBJECT (fo_context), "ref-id");*/
}

/**
 * fo_context_get_region_name:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "region-name" property of @fo_context.
 *
 * Return value: The "region-name" property value.
**/
FoProperty *
fo_context_get_region_name (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->region_name;
}

/**
 * fo_context_set_region_name:
 * @fo_context: The #FoContext object.
 * @new_region_name: The new "region-name" property value.
 * 
 * Sets the "region-name" property of @fo_context to @new_region_name.
 **/
void
fo_context_set_region_name (FoContext *fo_context,
		         FoProperty *new_region_name)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_region_name == NULL || FO_IS_PROPERTY_REGION_NAME (new_region_name));

  if (new_region_name != NULL)
    {
      g_object_ref (new_region_name);
    }
  if (fo_context->region_name != NULL)
    {
      g_object_unref (fo_context->region_name);
    }
  fo_context->region_name = new_region_name;
  /*g_object_notify (G_OBJECT (fo_context), "region-name");*/
}

/**
 * fo_context_get_role:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "role" property of @fo_context.
 *
 * Return value: The "role" property value.
**/
FoProperty *
fo_context_get_role (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->role;
}

/**
 * fo_context_set_role:
 * @fo_context: The #FoContext object.
 * @new_role: The new "role" property value.
 * 
 * Sets the "role" property of @fo_context to @new_role.
 **/
void
fo_context_set_role (FoContext *fo_context,
		         FoProperty *new_role)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_role == NULL || FO_IS_PROPERTY_ROLE (new_role));

  if (new_role != NULL)
    {
      g_object_ref (new_role);
    }
  if (fo_context->role != NULL)
    {
      g_object_unref (fo_context->role);
    }
  fo_context->role = new_role;
  /*g_object_notify (G_OBJECT (fo_context), "role");*/
}

/**
 * fo_context_get_scaling:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "scaling" property of @fo_context.
 *
 * Return value: The "scaling" property value.
**/
FoProperty *
fo_context_get_scaling (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->scaling;
}

/**
 * fo_context_set_scaling:
 * @fo_context: The #FoContext object.
 * @new_scaling: The new "scaling" property value.
 * 
 * Sets the "scaling" property of @fo_context to @new_scaling.
 **/
void
fo_context_set_scaling (FoContext *fo_context,
		         FoProperty *new_scaling)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_scaling == NULL || FO_IS_PROPERTY_SCALING (new_scaling));

  if (new_scaling != NULL)
    {
      g_object_ref (new_scaling);
    }
  if (fo_context->scaling != NULL)
    {
      g_object_unref (fo_context->scaling);
    }
  fo_context->scaling = new_scaling;
  /*g_object_notify (G_OBJECT (fo_context), "scaling");*/
}

/**
 * fo_context_get_scaling_method:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "scaling-method" property of @fo_context.
 *
 * Return value: The "scaling-method" property value.
**/
FoProperty *
fo_context_get_scaling_method (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->scaling_method;
}

/**
 * fo_context_set_scaling_method:
 * @fo_context: The #FoContext object.
 * @new_scaling_method: The new "scaling-method" property value.
 * 
 * Sets the "scaling-method" property of @fo_context to @new_scaling_method.
 **/
void
fo_context_set_scaling_method (FoContext *fo_context,
		         FoProperty *new_scaling_method)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_scaling_method == NULL || FO_IS_PROPERTY_SCALING_METHOD (new_scaling_method));

  if (new_scaling_method != NULL)
    {
      g_object_ref (new_scaling_method);
    }
  if (fo_context->scaling_method != NULL)
    {
      g_object_unref (fo_context->scaling_method);
    }
  fo_context->scaling_method = new_scaling_method;
  /*g_object_notify (G_OBJECT (fo_context), "scaling-method");*/
}

/**
 * fo_context_get_score_spaces:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "score-spaces" property of @fo_context.
 *
 * Return value: The "score-spaces" property value.
**/
FoProperty *
fo_context_get_score_spaces (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->score_spaces;
}

/**
 * fo_context_set_score_spaces:
 * @fo_context: The #FoContext object.
 * @new_score_spaces: The new "score-spaces" property value.
 * 
 * Sets the "score-spaces" property of @fo_context to @new_score_spaces.
 **/
void
fo_context_set_score_spaces (FoContext *fo_context,
		         FoProperty *new_score_spaces)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_score_spaces == NULL || FO_IS_PROPERTY_SCORE_SPACES (new_score_spaces));

  if (new_score_spaces != NULL)
    {
      g_object_ref (new_score_spaces);
    }
  if (fo_context->score_spaces != NULL)
    {
      g_object_unref (fo_context->score_spaces);
    }
  fo_context->score_spaces = new_score_spaces;
  /*g_object_notify (G_OBJECT (fo_context), "score-spaces");*/
}

/**
 * fo_context_get_source_document:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "source-document" property of @fo_context.
 *
 * Return value: The "source-document" property value.
**/
FoProperty *
fo_context_get_source_document (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->source_document;
}

/**
 * fo_context_set_source_document:
 * @fo_context: The #FoContext object.
 * @new_source_document: The new "source-document" property value.
 * 
 * Sets the "source-document" property of @fo_context to @new_source_document.
 **/
void
fo_context_set_source_document (FoContext *fo_context,
		         FoProperty *new_source_document)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_source_document == NULL || FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document != NULL)
    {
      g_object_ref (new_source_document);
    }
  if (fo_context->source_document != NULL)
    {
      g_object_unref (fo_context->source_document);
    }
  fo_context->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_context), "source-document");*/
}

/**
 * fo_context_get_space_after:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-after" property of @fo_context.
 *
 * Return value: The "space-after" property value.
**/
FoProperty *
fo_context_get_space_after (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_after;
}

/**
 * fo_context_set_space_after:
 * @fo_context: The #FoContext object.
 * @new_space_after: The new "space-after" property value.
 * 
 * Sets the "space-after" property of @fo_context to @new_space_after.
 **/
void
fo_context_set_space_after (FoContext *fo_context,
		         FoProperty *new_space_after)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_after == NULL || FO_IS_PROPERTY_SPACE_AFTER (new_space_after));

  if (new_space_after != NULL)
    {
      g_object_ref (new_space_after);
    }
  if (fo_context->space_after != NULL)
    {
      g_object_unref (fo_context->space_after);
    }
  fo_context->space_after = new_space_after;
  /*g_object_notify (G_OBJECT (fo_context), "space-after");*/
}

/**
 * fo_context_get_space_after_minimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-after-minimum" property of @fo_context.
 *
 * Return value: The "space-after-minimum" property value.
**/
FoProperty *
fo_context_get_space_after_minimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_after_minimum;
}

/**
 * fo_context_set_space_after_minimum:
 * @fo_context: The #FoContext object.
 * @new_space_after_minimum: The new "space-after-minimum" property value.
 * 
 * Sets the "space-after-minimum" property of @fo_context to @new_space_after_minimum.
 **/
void
fo_context_set_space_after_minimum (FoContext *fo_context,
		         FoProperty *new_space_after_minimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_after_minimum == NULL || FO_IS_PROPERTY_SPACE_AFTER_MINIMUM (new_space_after_minimum));

  if (new_space_after_minimum != NULL)
    {
      g_object_ref (new_space_after_minimum);
    }
  if (fo_context->space_after_minimum != NULL)
    {
      g_object_unref (fo_context->space_after_minimum);
    }
  fo_context->space_after_minimum = new_space_after_minimum;
  /*g_object_notify (G_OBJECT (fo_context), "space-after-minimum");*/
}

/**
 * fo_context_get_space_after_optimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-after-optimum" property of @fo_context.
 *
 * Return value: The "space-after-optimum" property value.
**/
FoProperty *
fo_context_get_space_after_optimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_after_optimum;
}

/**
 * fo_context_set_space_after_optimum:
 * @fo_context: The #FoContext object.
 * @new_space_after_optimum: The new "space-after-optimum" property value.
 * 
 * Sets the "space-after-optimum" property of @fo_context to @new_space_after_optimum.
 **/
void
fo_context_set_space_after_optimum (FoContext *fo_context,
		         FoProperty *new_space_after_optimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_after_optimum == NULL || FO_IS_PROPERTY_SPACE_AFTER_OPTIMUM (new_space_after_optimum));

  if (new_space_after_optimum != NULL)
    {
      g_object_ref (new_space_after_optimum);
    }
  if (fo_context->space_after_optimum != NULL)
    {
      g_object_unref (fo_context->space_after_optimum);
    }
  fo_context->space_after_optimum = new_space_after_optimum;
  /*g_object_notify (G_OBJECT (fo_context), "space-after-optimum");*/
}

/**
 * fo_context_get_space_after_maximum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-after-maximum" property of @fo_context.
 *
 * Return value: The "space-after-maximum" property value.
**/
FoProperty *
fo_context_get_space_after_maximum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_after_maximum;
}

/**
 * fo_context_set_space_after_maximum:
 * @fo_context: The #FoContext object.
 * @new_space_after_maximum: The new "space-after-maximum" property value.
 * 
 * Sets the "space-after-maximum" property of @fo_context to @new_space_after_maximum.
 **/
void
fo_context_set_space_after_maximum (FoContext *fo_context,
		         FoProperty *new_space_after_maximum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_after_maximum == NULL || FO_IS_PROPERTY_SPACE_AFTER_MAXIMUM (new_space_after_maximum));

  if (new_space_after_maximum != NULL)
    {
      g_object_ref (new_space_after_maximum);
    }
  if (fo_context->space_after_maximum != NULL)
    {
      g_object_unref (fo_context->space_after_maximum);
    }
  fo_context->space_after_maximum = new_space_after_maximum;
  /*g_object_notify (G_OBJECT (fo_context), "space-after-maximum");*/
}

/**
 * fo_context_get_space_after_precedence:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-after-precedence" property of @fo_context.
 *
 * Return value: The "space-after-precedence" property value.
**/
FoProperty *
fo_context_get_space_after_precedence (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_after_precedence;
}

/**
 * fo_context_set_space_after_precedence:
 * @fo_context: The #FoContext object.
 * @new_space_after_precedence: The new "space-after-precedence" property value.
 * 
 * Sets the "space-after-precedence" property of @fo_context to @new_space_after_precedence.
 **/
void
fo_context_set_space_after_precedence (FoContext *fo_context,
		         FoProperty *new_space_after_precedence)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_after_precedence == NULL || FO_IS_PROPERTY_SPACE_AFTER_PRECEDENCE (new_space_after_precedence));

  if (new_space_after_precedence != NULL)
    {
      g_object_ref (new_space_after_precedence);
    }
  if (fo_context->space_after_precedence != NULL)
    {
      g_object_unref (fo_context->space_after_precedence);
    }
  fo_context->space_after_precedence = new_space_after_precedence;
  /*g_object_notify (G_OBJECT (fo_context), "space-after-precedence");*/
}

/**
 * fo_context_get_space_after_condity:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-after-conditionality" property of @fo_context.
 *
 * Return value: The "space-after-conditionality" property value.
**/
FoProperty *
fo_context_get_space_after_condity (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_after_condity;
}

/**
 * fo_context_set_space_after_condity:
 * @fo_context: The #FoContext object.
 * @new_space_after_condity: The new "space-after-conditionality" property value.
 * 
 * Sets the "space-after-conditionality" property of @fo_context to @new_space_after_condity.
 **/
void
fo_context_set_space_after_condity (FoContext *fo_context,
		         FoProperty *new_space_after_condity)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_after_condity == NULL || FO_IS_PROPERTY_SPACE_AFTER_CONDITY (new_space_after_condity));

  if (new_space_after_condity != NULL)
    {
      g_object_ref (new_space_after_condity);
    }
  if (fo_context->space_after_condity != NULL)
    {
      g_object_unref (fo_context->space_after_condity);
    }
  fo_context->space_after_condity = new_space_after_condity;
  /*g_object_notify (G_OBJECT (fo_context), "space-after-conditionality");*/
}

/**
 * fo_context_get_space_before:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-before" property of @fo_context.
 *
 * Return value: The "space-before" property value.
**/
FoProperty *
fo_context_get_space_before (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_before;
}

/**
 * fo_context_set_space_before:
 * @fo_context: The #FoContext object.
 * @new_space_before: The new "space-before" property value.
 * 
 * Sets the "space-before" property of @fo_context to @new_space_before.
 **/
void
fo_context_set_space_before (FoContext *fo_context,
		         FoProperty *new_space_before)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_before == NULL || FO_IS_PROPERTY_SPACE_BEFORE (new_space_before));

  if (new_space_before != NULL)
    {
      g_object_ref (new_space_before);
    }
  if (fo_context->space_before != NULL)
    {
      g_object_unref (fo_context->space_before);
    }
  fo_context->space_before = new_space_before;
  /*g_object_notify (G_OBJECT (fo_context), "space-before");*/
}

/**
 * fo_context_get_space_before_minimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-before-minimum" property of @fo_context.
 *
 * Return value: The "space-before-minimum" property value.
**/
FoProperty *
fo_context_get_space_before_minimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_before_minimum;
}

/**
 * fo_context_set_space_before_minimum:
 * @fo_context: The #FoContext object.
 * @new_space_before_minimum: The new "space-before-minimum" property value.
 * 
 * Sets the "space-before-minimum" property of @fo_context to @new_space_before_minimum.
 **/
void
fo_context_set_space_before_minimum (FoContext *fo_context,
		         FoProperty *new_space_before_minimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_before_minimum == NULL || FO_IS_PROPERTY_SPACE_BEFORE_MINIMUM (new_space_before_minimum));

  if (new_space_before_minimum != NULL)
    {
      g_object_ref (new_space_before_minimum);
    }
  if (fo_context->space_before_minimum != NULL)
    {
      g_object_unref (fo_context->space_before_minimum);
    }
  fo_context->space_before_minimum = new_space_before_minimum;
  /*g_object_notify (G_OBJECT (fo_context), "space-before-minimum");*/
}

/**
 * fo_context_get_space_before_optimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-before-optimum" property of @fo_context.
 *
 * Return value: The "space-before-optimum" property value.
**/
FoProperty *
fo_context_get_space_before_optimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_before_optimum;
}

/**
 * fo_context_set_space_before_optimum:
 * @fo_context: The #FoContext object.
 * @new_space_before_optimum: The new "space-before-optimum" property value.
 * 
 * Sets the "space-before-optimum" property of @fo_context to @new_space_before_optimum.
 **/
void
fo_context_set_space_before_optimum (FoContext *fo_context,
		         FoProperty *new_space_before_optimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_before_optimum == NULL || FO_IS_PROPERTY_SPACE_BEFORE_OPTIMUM (new_space_before_optimum));

  if (new_space_before_optimum != NULL)
    {
      g_object_ref (new_space_before_optimum);
    }
  if (fo_context->space_before_optimum != NULL)
    {
      g_object_unref (fo_context->space_before_optimum);
    }
  fo_context->space_before_optimum = new_space_before_optimum;
  /*g_object_notify (G_OBJECT (fo_context), "space-before-optimum");*/
}

/**
 * fo_context_get_space_before_maximum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-before-maximum" property of @fo_context.
 *
 * Return value: The "space-before-maximum" property value.
**/
FoProperty *
fo_context_get_space_before_maximum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_before_maximum;
}

/**
 * fo_context_set_space_before_maximum:
 * @fo_context: The #FoContext object.
 * @new_space_before_maximum: The new "space-before-maximum" property value.
 * 
 * Sets the "space-before-maximum" property of @fo_context to @new_space_before_maximum.
 **/
void
fo_context_set_space_before_maximum (FoContext *fo_context,
		         FoProperty *new_space_before_maximum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_before_maximum == NULL || FO_IS_PROPERTY_SPACE_BEFORE_MAXIMUM (new_space_before_maximum));

  if (new_space_before_maximum != NULL)
    {
      g_object_ref (new_space_before_maximum);
    }
  if (fo_context->space_before_maximum != NULL)
    {
      g_object_unref (fo_context->space_before_maximum);
    }
  fo_context->space_before_maximum = new_space_before_maximum;
  /*g_object_notify (G_OBJECT (fo_context), "space-before-maximum");*/
}

/**
 * fo_context_get_space_before_precedence:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-before-precedence" property of @fo_context.
 *
 * Return value: The "space-before-precedence" property value.
**/
FoProperty *
fo_context_get_space_before_precedence (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_before_precedence;
}

/**
 * fo_context_set_space_before_precedence:
 * @fo_context: The #FoContext object.
 * @new_space_before_precedence: The new "space-before-precedence" property value.
 * 
 * Sets the "space-before-precedence" property of @fo_context to @new_space_before_precedence.
 **/
void
fo_context_set_space_before_precedence (FoContext *fo_context,
		         FoProperty *new_space_before_precedence)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_before_precedence == NULL || FO_IS_PROPERTY_SPACE_BEFORE_PRECEDENCE (new_space_before_precedence));

  if (new_space_before_precedence != NULL)
    {
      g_object_ref (new_space_before_precedence);
    }
  if (fo_context->space_before_precedence != NULL)
    {
      g_object_unref (fo_context->space_before_precedence);
    }
  fo_context->space_before_precedence = new_space_before_precedence;
  /*g_object_notify (G_OBJECT (fo_context), "space-before-precedence");*/
}

/**
 * fo_context_get_space_before_condity:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-before-conditionality" property of @fo_context.
 *
 * Return value: The "space-before-conditionality" property value.
**/
FoProperty *
fo_context_get_space_before_condity (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_before_condity;
}

/**
 * fo_context_set_space_before_condity:
 * @fo_context: The #FoContext object.
 * @new_space_before_condity: The new "space-before-conditionality" property value.
 * 
 * Sets the "space-before-conditionality" property of @fo_context to @new_space_before_condity.
 **/
void
fo_context_set_space_before_condity (FoContext *fo_context,
		         FoProperty *new_space_before_condity)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_before_condity == NULL || FO_IS_PROPERTY_SPACE_BEFORE_CONDITY (new_space_before_condity));

  if (new_space_before_condity != NULL)
    {
      g_object_ref (new_space_before_condity);
    }
  if (fo_context->space_before_condity != NULL)
    {
      g_object_unref (fo_context->space_before_condity);
    }
  fo_context->space_before_condity = new_space_before_condity;
  /*g_object_notify (G_OBJECT (fo_context), "space-before-conditionality");*/
}

/**
 * fo_context_get_space_end:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-end" property of @fo_context.
 *
 * Return value: The "space-end" property value.
**/
FoProperty *
fo_context_get_space_end (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_end;
}

/**
 * fo_context_set_space_end:
 * @fo_context: The #FoContext object.
 * @new_space_end: The new "space-end" property value.
 * 
 * Sets the "space-end" property of @fo_context to @new_space_end.
 **/
void
fo_context_set_space_end (FoContext *fo_context,
		         FoProperty *new_space_end)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_end == NULL || FO_IS_PROPERTY_SPACE_END (new_space_end));

  if (new_space_end != NULL)
    {
      g_object_ref (new_space_end);
    }
  if (fo_context->space_end != NULL)
    {
      g_object_unref (fo_context->space_end);
    }
  fo_context->space_end = new_space_end;
  /*g_object_notify (G_OBJECT (fo_context), "space-end");*/
}

/**
 * fo_context_get_space_end_minimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-end-minimum" property of @fo_context.
 *
 * Return value: The "space-end-minimum" property value.
**/
FoProperty *
fo_context_get_space_end_minimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_end_minimum;
}

/**
 * fo_context_set_space_end_minimum:
 * @fo_context: The #FoContext object.
 * @new_space_end_minimum: The new "space-end-minimum" property value.
 * 
 * Sets the "space-end-minimum" property of @fo_context to @new_space_end_minimum.
 **/
void
fo_context_set_space_end_minimum (FoContext *fo_context,
		         FoProperty *new_space_end_minimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_end_minimum == NULL || FO_IS_PROPERTY_SPACE_END_MINIMUM (new_space_end_minimum));

  if (new_space_end_minimum != NULL)
    {
      g_object_ref (new_space_end_minimum);
    }
  if (fo_context->space_end_minimum != NULL)
    {
      g_object_unref (fo_context->space_end_minimum);
    }
  fo_context->space_end_minimum = new_space_end_minimum;
  /*g_object_notify (G_OBJECT (fo_context), "space-end-minimum");*/
}

/**
 * fo_context_get_space_end_optimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-end-optimum" property of @fo_context.
 *
 * Return value: The "space-end-optimum" property value.
**/
FoProperty *
fo_context_get_space_end_optimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_end_optimum;
}

/**
 * fo_context_set_space_end_optimum:
 * @fo_context: The #FoContext object.
 * @new_space_end_optimum: The new "space-end-optimum" property value.
 * 
 * Sets the "space-end-optimum" property of @fo_context to @new_space_end_optimum.
 **/
void
fo_context_set_space_end_optimum (FoContext *fo_context,
		         FoProperty *new_space_end_optimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_end_optimum == NULL || FO_IS_PROPERTY_SPACE_END_OPTIMUM (new_space_end_optimum));

  if (new_space_end_optimum != NULL)
    {
      g_object_ref (new_space_end_optimum);
    }
  if (fo_context->space_end_optimum != NULL)
    {
      g_object_unref (fo_context->space_end_optimum);
    }
  fo_context->space_end_optimum = new_space_end_optimum;
  /*g_object_notify (G_OBJECT (fo_context), "space-end-optimum");*/
}

/**
 * fo_context_get_space_end_maximum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-end-maximum" property of @fo_context.
 *
 * Return value: The "space-end-maximum" property value.
**/
FoProperty *
fo_context_get_space_end_maximum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_end_maximum;
}

/**
 * fo_context_set_space_end_maximum:
 * @fo_context: The #FoContext object.
 * @new_space_end_maximum: The new "space-end-maximum" property value.
 * 
 * Sets the "space-end-maximum" property of @fo_context to @new_space_end_maximum.
 **/
void
fo_context_set_space_end_maximum (FoContext *fo_context,
		         FoProperty *new_space_end_maximum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_end_maximum == NULL || FO_IS_PROPERTY_SPACE_END_MAXIMUM (new_space_end_maximum));

  if (new_space_end_maximum != NULL)
    {
      g_object_ref (new_space_end_maximum);
    }
  if (fo_context->space_end_maximum != NULL)
    {
      g_object_unref (fo_context->space_end_maximum);
    }
  fo_context->space_end_maximum = new_space_end_maximum;
  /*g_object_notify (G_OBJECT (fo_context), "space-end-maximum");*/
}

/**
 * fo_context_get_space_end_precedence:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-end-precedence" property of @fo_context.
 *
 * Return value: The "space-end-precedence" property value.
**/
FoProperty *
fo_context_get_space_end_precedence (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_end_precedence;
}

/**
 * fo_context_set_space_end_precedence:
 * @fo_context: The #FoContext object.
 * @new_space_end_precedence: The new "space-end-precedence" property value.
 * 
 * Sets the "space-end-precedence" property of @fo_context to @new_space_end_precedence.
 **/
void
fo_context_set_space_end_precedence (FoContext *fo_context,
		         FoProperty *new_space_end_precedence)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_end_precedence == NULL || FO_IS_PROPERTY_SPACE_END_PRECEDENCE (new_space_end_precedence));

  if (new_space_end_precedence != NULL)
    {
      g_object_ref (new_space_end_precedence);
    }
  if (fo_context->space_end_precedence != NULL)
    {
      g_object_unref (fo_context->space_end_precedence);
    }
  fo_context->space_end_precedence = new_space_end_precedence;
  /*g_object_notify (G_OBJECT (fo_context), "space-end-precedence");*/
}

/**
 * fo_context_get_space_end_condity:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-end-conditionality" property of @fo_context.
 *
 * Return value: The "space-end-conditionality" property value.
**/
FoProperty *
fo_context_get_space_end_condity (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_end_condity;
}

/**
 * fo_context_set_space_end_condity:
 * @fo_context: The #FoContext object.
 * @new_space_end_condity: The new "space-end-conditionality" property value.
 * 
 * Sets the "space-end-conditionality" property of @fo_context to @new_space_end_condity.
 **/
void
fo_context_set_space_end_condity (FoContext *fo_context,
		         FoProperty *new_space_end_condity)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_end_condity == NULL || FO_IS_PROPERTY_SPACE_END_CONDITY (new_space_end_condity));

  if (new_space_end_condity != NULL)
    {
      g_object_ref (new_space_end_condity);
    }
  if (fo_context->space_end_condity != NULL)
    {
      g_object_unref (fo_context->space_end_condity);
    }
  fo_context->space_end_condity = new_space_end_condity;
  /*g_object_notify (G_OBJECT (fo_context), "space-end-conditionality");*/
}

/**
 * fo_context_get_space_start:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-start" property of @fo_context.
 *
 * Return value: The "space-start" property value.
**/
FoProperty *
fo_context_get_space_start (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_start;
}

/**
 * fo_context_set_space_start:
 * @fo_context: The #FoContext object.
 * @new_space_start: The new "space-start" property value.
 * 
 * Sets the "space-start" property of @fo_context to @new_space_start.
 **/
void
fo_context_set_space_start (FoContext *fo_context,
		         FoProperty *new_space_start)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_start == NULL || FO_IS_PROPERTY_SPACE_START (new_space_start));

  if (new_space_start != NULL)
    {
      g_object_ref (new_space_start);
    }
  if (fo_context->space_start != NULL)
    {
      g_object_unref (fo_context->space_start);
    }
  fo_context->space_start = new_space_start;
  /*g_object_notify (G_OBJECT (fo_context), "space-start");*/
}

/**
 * fo_context_get_space_start_minimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-start-minimum" property of @fo_context.
 *
 * Return value: The "space-start-minimum" property value.
**/
FoProperty *
fo_context_get_space_start_minimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_start_minimum;
}

/**
 * fo_context_set_space_start_minimum:
 * @fo_context: The #FoContext object.
 * @new_space_start_minimum: The new "space-start-minimum" property value.
 * 
 * Sets the "space-start-minimum" property of @fo_context to @new_space_start_minimum.
 **/
void
fo_context_set_space_start_minimum (FoContext *fo_context,
		         FoProperty *new_space_start_minimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_start_minimum == NULL || FO_IS_PROPERTY_SPACE_START_MINIMUM (new_space_start_minimum));

  if (new_space_start_minimum != NULL)
    {
      g_object_ref (new_space_start_minimum);
    }
  if (fo_context->space_start_minimum != NULL)
    {
      g_object_unref (fo_context->space_start_minimum);
    }
  fo_context->space_start_minimum = new_space_start_minimum;
  /*g_object_notify (G_OBJECT (fo_context), "space-start-minimum");*/
}

/**
 * fo_context_get_space_start_optimum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-start-optimum" property of @fo_context.
 *
 * Return value: The "space-start-optimum" property value.
**/
FoProperty *
fo_context_get_space_start_optimum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_start_optimum;
}

/**
 * fo_context_set_space_start_optimum:
 * @fo_context: The #FoContext object.
 * @new_space_start_optimum: The new "space-start-optimum" property value.
 * 
 * Sets the "space-start-optimum" property of @fo_context to @new_space_start_optimum.
 **/
void
fo_context_set_space_start_optimum (FoContext *fo_context,
		         FoProperty *new_space_start_optimum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_start_optimum == NULL || FO_IS_PROPERTY_SPACE_START_OPTIMUM (new_space_start_optimum));

  if (new_space_start_optimum != NULL)
    {
      g_object_ref (new_space_start_optimum);
    }
  if (fo_context->space_start_optimum != NULL)
    {
      g_object_unref (fo_context->space_start_optimum);
    }
  fo_context->space_start_optimum = new_space_start_optimum;
  /*g_object_notify (G_OBJECT (fo_context), "space-start-optimum");*/
}

/**
 * fo_context_get_space_start_maximum:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-start-maximum" property of @fo_context.
 *
 * Return value: The "space-start-maximum" property value.
**/
FoProperty *
fo_context_get_space_start_maximum (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_start_maximum;
}

/**
 * fo_context_set_space_start_maximum:
 * @fo_context: The #FoContext object.
 * @new_space_start_maximum: The new "space-start-maximum" property value.
 * 
 * Sets the "space-start-maximum" property of @fo_context to @new_space_start_maximum.
 **/
void
fo_context_set_space_start_maximum (FoContext *fo_context,
		         FoProperty *new_space_start_maximum)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_start_maximum == NULL || FO_IS_PROPERTY_SPACE_START_MAXIMUM (new_space_start_maximum));

  if (new_space_start_maximum != NULL)
    {
      g_object_ref (new_space_start_maximum);
    }
  if (fo_context->space_start_maximum != NULL)
    {
      g_object_unref (fo_context->space_start_maximum);
    }
  fo_context->space_start_maximum = new_space_start_maximum;
  /*g_object_notify (G_OBJECT (fo_context), "space-start-maximum");*/
}

/**
 * fo_context_get_space_start_precedence:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-start-precedence" property of @fo_context.
 *
 * Return value: The "space-start-precedence" property value.
**/
FoProperty *
fo_context_get_space_start_precedence (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_start_precedence;
}

/**
 * fo_context_set_space_start_precedence:
 * @fo_context: The #FoContext object.
 * @new_space_start_precedence: The new "space-start-precedence" property value.
 * 
 * Sets the "space-start-precedence" property of @fo_context to @new_space_start_precedence.
 **/
void
fo_context_set_space_start_precedence (FoContext *fo_context,
		         FoProperty *new_space_start_precedence)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_start_precedence == NULL || FO_IS_PROPERTY_SPACE_START_PRECEDENCE (new_space_start_precedence));

  if (new_space_start_precedence != NULL)
    {
      g_object_ref (new_space_start_precedence);
    }
  if (fo_context->space_start_precedence != NULL)
    {
      g_object_unref (fo_context->space_start_precedence);
    }
  fo_context->space_start_precedence = new_space_start_precedence;
  /*g_object_notify (G_OBJECT (fo_context), "space-start-precedence");*/
}

/**
 * fo_context_get_space_start_condity:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "space-start-conditionality" property of @fo_context.
 *
 * Return value: The "space-start-conditionality" property value.
**/
FoProperty *
fo_context_get_space_start_condity (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->space_start_condity;
}

/**
 * fo_context_set_space_start_condity:
 * @fo_context: The #FoContext object.
 * @new_space_start_condity: The new "space-start-conditionality" property value.
 * 
 * Sets the "space-start-conditionality" property of @fo_context to @new_space_start_condity.
 **/
void
fo_context_set_space_start_condity (FoContext *fo_context,
		         FoProperty *new_space_start_condity)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_space_start_condity == NULL || FO_IS_PROPERTY_SPACE_START_CONDITY (new_space_start_condity));

  if (new_space_start_condity != NULL)
    {
      g_object_ref (new_space_start_condity);
    }
  if (fo_context->space_start_condity != NULL)
    {
      g_object_unref (fo_context->space_start_condity);
    }
  fo_context->space_start_condity = new_space_start_condity;
  /*g_object_notify (G_OBJECT (fo_context), "space-start-conditionality");*/
}

/**
 * fo_context_get_span:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "span" property of @fo_context.
 *
 * Return value: The "span" property value.
**/
FoProperty *
fo_context_get_span (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->span;
}

/**
 * fo_context_set_span:
 * @fo_context: The #FoContext object.
 * @new_span: The new "span" property value.
 * 
 * Sets the "span" property of @fo_context to @new_span.
 **/
void
fo_context_set_span (FoContext *fo_context,
		         FoProperty *new_span)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_span == NULL || FO_IS_PROPERTY_SPAN (new_span));

  if (new_span != NULL)
    {
      g_object_ref (new_span);
    }
  if (fo_context->span != NULL)
    {
      g_object_unref (fo_context->span);
    }
  fo_context->span = new_span;
  /*g_object_notify (G_OBJECT (fo_context), "span");*/
}

/**
 * fo_context_get_src:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "src" property of @fo_context.
 *
 * Return value: The "src" property value.
**/
FoProperty *
fo_context_get_src (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->src;
}

/**
 * fo_context_set_src:
 * @fo_context: The #FoContext object.
 * @new_src: The new "src" property value.
 * 
 * Sets the "src" property of @fo_context to @new_src.
 **/
void
fo_context_set_src (FoContext *fo_context,
		         FoProperty *new_src)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_src == NULL || FO_IS_PROPERTY_SRC (new_src));

  if (new_src != NULL)
    {
      g_object_ref (new_src);
    }
  if (fo_context->src != NULL)
    {
      g_object_unref (fo_context->src);
    }
  fo_context->src = new_src;
  /*g_object_notify (G_OBJECT (fo_context), "src");*/
}

/**
 * fo_context_get_start_indent:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "start-indent" property of @fo_context.
 *
 * Return value: The "start-indent" property value.
**/
FoProperty *
fo_context_get_start_indent (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->start_indent;
}

/**
 * fo_context_set_start_indent:
 * @fo_context: The #FoContext object.
 * @new_start_indent: The new "start-indent" property value.
 * 
 * Sets the "start-indent" property of @fo_context to @new_start_indent.
 **/
void
fo_context_set_start_indent (FoContext *fo_context,
		         FoProperty *new_start_indent)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_start_indent == NULL || FO_IS_PROPERTY_START_INDENT (new_start_indent));

  if (new_start_indent != NULL)
    {
      g_object_ref (new_start_indent);
    }
  if (fo_context->start_indent != NULL)
    {
      g_object_unref (fo_context->start_indent);
    }
  fo_context->start_indent = new_start_indent;
  /*g_object_notify (G_OBJECT (fo_context), "start-indent");*/
}

/**
 * fo_context_get_table_layout:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "table-layout" property of @fo_context.
 *
 * Return value: The "table-layout" property value.
**/
FoProperty *
fo_context_get_table_layout (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->table_layout;
}

/**
 * fo_context_set_table_layout:
 * @fo_context: The #FoContext object.
 * @new_table_layout: The new "table-layout" property value.
 * 
 * Sets the "table-layout" property of @fo_context to @new_table_layout.
 **/
void
fo_context_set_table_layout (FoContext *fo_context,
		         FoProperty *new_table_layout)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_table_layout == NULL || FO_IS_PROPERTY_TABLE_LAYOUT (new_table_layout));

  if (new_table_layout != NULL)
    {
      g_object_ref (new_table_layout);
    }
  if (fo_context->table_layout != NULL)
    {
      g_object_unref (fo_context->table_layout);
    }
  fo_context->table_layout = new_table_layout;
  /*g_object_notify (G_OBJECT (fo_context), "table-layout");*/
}

/**
 * fo_context_get_text_align:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "text-align" property of @fo_context.
 *
 * Return value: The "text-align" property value.
**/
FoProperty *
fo_context_get_text_align (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->text_align;
}

/**
 * fo_context_set_text_align:
 * @fo_context: The #FoContext object.
 * @new_text_align: The new "text-align" property value.
 * 
 * Sets the "text-align" property of @fo_context to @new_text_align.
 **/
void
fo_context_set_text_align (FoContext *fo_context,
		         FoProperty *new_text_align)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_text_align == NULL || FO_IS_PROPERTY_TEXT_ALIGN (new_text_align));

  if (new_text_align != NULL)
    {
      g_object_ref (new_text_align);
    }
  if (fo_context->text_align != NULL)
    {
      g_object_unref (fo_context->text_align);
    }
  fo_context->text_align = new_text_align;
  /*g_object_notify (G_OBJECT (fo_context), "text-align");*/
}

/**
 * fo_context_get_text_indent:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "text-indent" property of @fo_context.
 *
 * Return value: The "text-indent" property value.
**/
FoProperty *
fo_context_get_text_indent (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->text_indent;
}

/**
 * fo_context_set_text_indent:
 * @fo_context: The #FoContext object.
 * @new_text_indent: The new "text-indent" property value.
 * 
 * Sets the "text-indent" property of @fo_context to @new_text_indent.
 **/
void
fo_context_set_text_indent (FoContext *fo_context,
		         FoProperty *new_text_indent)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_text_indent == NULL || FO_IS_PROPERTY_TEXT_INDENT (new_text_indent));

  if (new_text_indent != NULL)
    {
      g_object_ref (new_text_indent);
    }
  if (fo_context->text_indent != NULL)
    {
      g_object_unref (fo_context->text_indent);
    }
  fo_context->text_indent = new_text_indent;
  /*g_object_notify (G_OBJECT (fo_context), "text-indent");*/
}

/**
 * fo_context_get_unicode_bidi:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "unicode-bidi" property of @fo_context.
 *
 * Return value: The "unicode-bidi" property value.
**/
FoProperty *
fo_context_get_unicode_bidi (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->unicode_bidi;
}

/**
 * fo_context_set_unicode_bidi:
 * @fo_context: The #FoContext object.
 * @new_unicode_bidi: The new "unicode-bidi" property value.
 * 
 * Sets the "unicode-bidi" property of @fo_context to @new_unicode_bidi.
 **/
void
fo_context_set_unicode_bidi (FoContext *fo_context,
		         FoProperty *new_unicode_bidi)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_unicode_bidi == NULL || FO_IS_PROPERTY_UNICODE_BIDI (new_unicode_bidi));

  if (new_unicode_bidi != NULL)
    {
      g_object_ref (new_unicode_bidi);
    }
  if (fo_context->unicode_bidi != NULL)
    {
      g_object_unref (fo_context->unicode_bidi);
    }
  fo_context->unicode_bidi = new_unicode_bidi;
  /*g_object_notify (G_OBJECT (fo_context), "unicode-bidi");*/
}

/**
 * fo_context_get_white_space_collapse:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "white-space-collapse" property of @fo_context.
 *
 * Return value: The "white-space-collapse" property value.
**/
FoProperty *
fo_context_get_white_space_collapse (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->white_space_collapse;
}

/**
 * fo_context_set_white_space_collapse:
 * @fo_context: The #FoContext object.
 * @new_white_space_collapse: The new "white-space-collapse" property value.
 * 
 * Sets the "white-space-collapse" property of @fo_context to @new_white_space_collapse.
 **/
void
fo_context_set_white_space_collapse (FoContext *fo_context,
		         FoProperty *new_white_space_collapse)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_white_space_collapse == NULL || FO_IS_PROPERTY_WHITE_SPACE_COLLAPSE (new_white_space_collapse));

  if (new_white_space_collapse != NULL)
    {
      g_object_ref (new_white_space_collapse);
    }
  if (fo_context->white_space_collapse != NULL)
    {
      g_object_unref (fo_context->white_space_collapse);
    }
  fo_context->white_space_collapse = new_white_space_collapse;
  /*g_object_notify (G_OBJECT (fo_context), "white-space-collapse");*/
}

/**
 * fo_context_get_white_space_treatment:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "white-space-treatment" property of @fo_context.
 *
 * Return value: The "white-space-treatment" property value.
**/
FoProperty *
fo_context_get_white_space_treatment (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->white_space_treatment;
}

/**
 * fo_context_set_white_space_treatment:
 * @fo_context: The #FoContext object.
 * @new_white_space_treatment: The new "white-space-treatment" property value.
 * 
 * Sets the "white-space-treatment" property of @fo_context to @new_white_space_treatment.
 **/
void
fo_context_set_white_space_treatment (FoContext *fo_context,
		         FoProperty *new_white_space_treatment)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_white_space_treatment == NULL || FO_IS_PROPERTY_WHITE_SPACE_TREATMENT (new_white_space_treatment));

  if (new_white_space_treatment != NULL)
    {
      g_object_ref (new_white_space_treatment);
    }
  if (fo_context->white_space_treatment != NULL)
    {
      g_object_unref (fo_context->white_space_treatment);
    }
  fo_context->white_space_treatment = new_white_space_treatment;
  /*g_object_notify (G_OBJECT (fo_context), "white-space-treatment");*/
}

/**
 * fo_context_get_widows:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "widows" property of @fo_context.
 *
 * Return value: The "widows" property value.
**/
FoProperty *
fo_context_get_widows (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->widows;
}

/**
 * fo_context_set_widows:
 * @fo_context: The #FoContext object.
 * @new_widows: The new "widows" property value.
 * 
 * Sets the "widows" property of @fo_context to @new_widows.
 **/
void
fo_context_set_widows (FoContext *fo_context,
		         FoProperty *new_widows)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_widows == NULL || FO_IS_PROPERTY_WIDOWS (new_widows));

  if (new_widows != NULL)
    {
      g_object_ref (new_widows);
    }
  if (fo_context->widows != NULL)
    {
      g_object_unref (fo_context->widows);
    }
  fo_context->widows = new_widows;
  /*g_object_notify (G_OBJECT (fo_context), "widows");*/
}

/**
 * fo_context_get_width:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "width" property of @fo_context.
 *
 * Return value: The "width" property value.
**/
FoProperty *
fo_context_get_width (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->width;
}

/**
 * fo_context_set_width:
 * @fo_context: The #FoContext object.
 * @new_width: The new "width" property value.
 * 
 * Sets the "width" property of @fo_context to @new_width.
 **/
void
fo_context_set_width (FoContext *fo_context,
		         FoProperty *new_width)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_width == NULL || FO_IS_PROPERTY_WIDTH (new_width));

  if (new_width != NULL)
    {
      g_object_ref (new_width);
    }
  if (fo_context->width != NULL)
    {
      g_object_unref (fo_context->width);
    }
  fo_context->width = new_width;
  /*g_object_notify (G_OBJECT (fo_context), "width");*/
}

/**
 * fo_context_get_wrap_option:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "wrap-option" property of @fo_context.
 *
 * Return value: The "wrap-option" property value.
**/
FoProperty *
fo_context_get_wrap_option (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->wrap_option;
}

/**
 * fo_context_set_wrap_option:
 * @fo_context: The #FoContext object.
 * @new_wrap_option: The new "wrap-option" property value.
 * 
 * Sets the "wrap-option" property of @fo_context to @new_wrap_option.
 **/
void
fo_context_set_wrap_option (FoContext *fo_context,
		         FoProperty *new_wrap_option)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_wrap_option == NULL || FO_IS_PROPERTY_WRAP_OPTION (new_wrap_option));

  if (new_wrap_option != NULL)
    {
      g_object_ref (new_wrap_option);
    }
  if (fo_context->wrap_option != NULL)
    {
      g_object_unref (fo_context->wrap_option);
    }
  fo_context->wrap_option = new_wrap_option;
  /*g_object_notify (G_OBJECT (fo_context), "wrap-option");*/
}

/**
 * fo_context_get_writing_mode:
 * @fo_context: The @FoContext object.
 * 
 * Gets the "writing-mode" property of @fo_context.
 *
 * Return value: The "writing-mode" property value.
**/
FoProperty *
fo_context_get_writing_mode (FoContext *fo_context)
{
  g_return_val_if_fail (fo_context != NULL, NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);

  return fo_context->writing_mode;
}

/**
 * fo_context_set_writing_mode:
 * @fo_context: The #FoContext object.
 * @new_writing_mode: The new "writing-mode" property value.
 * 
 * Sets the "writing-mode" property of @fo_context to @new_writing_mode.
 **/
void
fo_context_set_writing_mode (FoContext *fo_context,
		         FoProperty *new_writing_mode)
{
  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));
  g_return_if_fail (new_writing_mode == NULL || FO_IS_PROPERTY_WRITING_MODE (new_writing_mode));

  if (new_writing_mode != NULL)
    {
      g_object_ref (new_writing_mode);
    }
  if (fo_context->writing_mode != NULL)
    {
      g_object_unref (fo_context->writing_mode);
    }
  fo_context->writing_mode = new_writing_mode;
  /*g_object_notify (G_OBJECT (fo_context), "writing-mode");*/
}

/**
 * fo_context_copy:
 * @src: #FoContext to be copied.
 * 
 * Make a copy of @src.
 * 
 * Return value: Copy of @src.
 **/
FoContext*
fo_context_copy (FoContext *src)
{
  FoContext *context;

  context = fo_context_new ();

  fo_context_set_alignment_adjust (context,
      fo_context_get_alignment_adjust (src));
  fo_context_set_alignment_baseline (context,
      fo_context_get_alignment_baseline (src));
  fo_context_set_background_color (context,
      fo_context_get_background_color (src));
  fo_context_set_background_image (context,
      fo_context_get_background_image (src));
  fo_context_set_baseline_shift (context,
      fo_context_get_baseline_shift (src));
  fo_context_set_block_progression_dimension (context,
      fo_context_get_block_progression_dimension (src));
  fo_context_set_block_progression_dimension_minimum (context,
      fo_context_get_block_progression_dimension_minimum (src));
  fo_context_set_block_progression_dimension_optimum (context,
      fo_context_get_block_progression_dimension_optimum (src));
  fo_context_set_block_progression_dimension_maximum (context,
      fo_context_get_block_progression_dimension_maximum (src));
  fo_context_set_border (context,
      fo_context_get_border (src));
  fo_context_set_border_after_color (context,
      fo_context_get_border_after_color (src));
  fo_context_set_border_after_precedence (context,
      fo_context_get_border_after_precedence (src));
  fo_context_set_border_after_style (context,
      fo_context_get_border_after_style (src));
  fo_context_set_border_after_width (context,
      fo_context_get_border_after_width (src));
  fo_context_set_border_before_color (context,
      fo_context_get_border_before_color (src));
  fo_context_set_border_before_precedence (context,
      fo_context_get_border_before_precedence (src));
  fo_context_set_border_before_style (context,
      fo_context_get_border_before_style (src));
  fo_context_set_border_before_width (context,
      fo_context_get_border_before_width (src));
  fo_context_set_border_bottom (context,
      fo_context_get_border_bottom (src));
  fo_context_set_border_bottom_color (context,
      fo_context_get_border_bottom_color (src));
  fo_context_set_border_bottom_style (context,
      fo_context_get_border_bottom_style (src));
  fo_context_set_border_bottom_width (context,
      fo_context_get_border_bottom_width (src));
  fo_context_set_border_collapse (context,
      fo_context_get_border_collapse (src));
  fo_context_set_border_color (context,
      fo_context_get_border_color (src));
  fo_context_set_border_end_color (context,
      fo_context_get_border_end_color (src));
  fo_context_set_border_end_precedence (context,
      fo_context_get_border_end_precedence (src));
  fo_context_set_border_end_style (context,
      fo_context_get_border_end_style (src));
  fo_context_set_border_end_width (context,
      fo_context_get_border_end_width (src));
  fo_context_set_border_left (context,
      fo_context_get_border_left (src));
  fo_context_set_border_left_color (context,
      fo_context_get_border_left_color (src));
  fo_context_set_border_left_style (context,
      fo_context_get_border_left_style (src));
  fo_context_set_border_left_width (context,
      fo_context_get_border_left_width (src));
  fo_context_set_border_right (context,
      fo_context_get_border_right (src));
  fo_context_set_border_right_color (context,
      fo_context_get_border_right_color (src));
  fo_context_set_border_right_style (context,
      fo_context_get_border_right_style (src));
  fo_context_set_border_right_width (context,
      fo_context_get_border_right_width (src));
  fo_context_set_border_separation (context,
      fo_context_get_border_separation (src));
  fo_context_set_border_start_color (context,
      fo_context_get_border_start_color (src));
  fo_context_set_border_start_precedence (context,
      fo_context_get_border_start_precedence (src));
  fo_context_set_border_start_style (context,
      fo_context_get_border_start_style (src));
  fo_context_set_border_start_width (context,
      fo_context_get_border_start_width (src));
  fo_context_set_border_style (context,
      fo_context_get_border_style (src));
  fo_context_set_border_top (context,
      fo_context_get_border_top (src));
  fo_context_set_border_top_color (context,
      fo_context_get_border_top_color (src));
  fo_context_set_border_top_style (context,
      fo_context_get_border_top_style (src));
  fo_context_set_border_top_width (context,
      fo_context_get_border_top_width (src));
  fo_context_set_border_width (context,
      fo_context_get_border_width (src));
  fo_context_set_break_after (context,
      fo_context_get_break_after (src));
  fo_context_set_break_before (context,
      fo_context_get_break_before (src));
  fo_context_set_character (context,
      fo_context_get_character (src));
  fo_context_set_clip (context,
      fo_context_get_clip (src));
  fo_context_set_color (context,
      fo_context_get_color (src));
  fo_context_set_column_number (context,
      fo_context_get_column_number (src));
  fo_context_set_column_width (context,
      fo_context_get_column_width (src));
  fo_context_set_content_height (context,
      fo_context_get_content_height (src));
  fo_context_set_content_type (context,
      fo_context_get_content_type (src));
  fo_context_set_content_width (context,
      fo_context_get_content_width (src));
  fo_context_set_direction (context,
      fo_context_get_direction (src));
  fo_context_set_display_align (context,
      fo_context_get_display_align (src));
  fo_context_set_dominant_baseline (context,
      fo_context_get_dominant_baseline (src));
  fo_context_set_end_indent (context,
      fo_context_get_end_indent (src));
  fo_context_set_extent (context,
      fo_context_get_extent (src));
  fo_context_set_flow_name (context,
      fo_context_get_flow_name (src));
  fo_context_set_font_family (context,
      fo_context_get_font_family (src));
  fo_context_set_font_size (context,
      fo_context_get_font_size (src));
  fo_context_set_font_stretch (context,
      fo_context_get_font_stretch (src));
  fo_context_set_font_style (context,
      fo_context_get_font_style (src));
  fo_context_set_font_variant (context,
      fo_context_get_font_variant (src));
  fo_context_set_font_weight (context,
      fo_context_get_font_weight (src));
  fo_context_set_format (context,
      fo_context_get_format (src));
  fo_context_set_grouping_separator (context,
      fo_context_get_grouping_separator (src));
  fo_context_set_grouping_size (context,
      fo_context_get_grouping_size (src));
  fo_context_set_height (context,
      fo_context_get_height (src));
  fo_context_set_id (context,
      fo_context_get_id (src));
  fo_context_set_inline_progression_dimension (context,
      fo_context_get_inline_progression_dimension (src));
  fo_context_set_inline_progression_dimension_minimum (context,
      fo_context_get_inline_progression_dimension_minimum (src));
  fo_context_set_inline_progression_dimension_optimum (context,
      fo_context_get_inline_progression_dimension_optimum (src));
  fo_context_set_inline_progression_dimension_maximum (context,
      fo_context_get_inline_progression_dimension_maximum (src));
  fo_context_set_keep_together (context,
      fo_context_get_keep_together (src));
  fo_context_set_keep_together_within_column (context,
      fo_context_get_keep_together_within_column (src));
  fo_context_set_keep_together_within_line (context,
      fo_context_get_keep_together_within_line (src));
  fo_context_set_keep_together_within_page (context,
      fo_context_get_keep_together_within_page (src));
  fo_context_set_keep_with_next (context,
      fo_context_get_keep_with_next (src));
  fo_context_set_keep_with_next_within_column (context,
      fo_context_get_keep_with_next_within_column (src));
  fo_context_set_keep_with_next_within_line (context,
      fo_context_get_keep_with_next_within_line (src));
  fo_context_set_keep_with_next_within_page (context,
      fo_context_get_keep_with_next_within_page (src));
  fo_context_set_keep_with_previous (context,
      fo_context_get_keep_with_previous (src));
  fo_context_set_keep_with_previous_within_column (context,
      fo_context_get_keep_with_previous_within_column (src));
  fo_context_set_keep_with_previous_within_line (context,
      fo_context_get_keep_with_previous_within_line (src));
  fo_context_set_keep_with_previous_within_page (context,
      fo_context_get_keep_with_previous_within_page (src));
  fo_context_set_letter_value (context,
      fo_context_get_letter_value (src));
  fo_context_set_line_height (context,
      fo_context_get_line_height (src));
  fo_context_set_line_stacking_strategy (context,
      fo_context_get_line_stacking_strategy (src));
  fo_context_set_linefeed_treatment (context,
      fo_context_get_linefeed_treatment (src));
  fo_context_set_margin (context,
      fo_context_get_margin (src));
  fo_context_set_margin_bottom (context,
      fo_context_get_margin_bottom (src));
  fo_context_set_margin_left (context,
      fo_context_get_margin_left (src));
  fo_context_set_margin_right (context,
      fo_context_get_margin_right (src));
  fo_context_set_margin_top (context,
      fo_context_get_margin_top (src));
  fo_context_set_master_name (context,
      fo_context_get_master_name (src));
  fo_context_set_master_reference (context,
      fo_context_get_master_reference (src));
  fo_context_set_media_usage (context,
      fo_context_get_media_usage (src));
  fo_context_set_number_columns_repeated (context,
      fo_context_get_number_columns_repeated (src));
  fo_context_set_number_columns_spanned (context,
      fo_context_get_number_columns_spanned (src));
  fo_context_set_number_rows_spanned (context,
      fo_context_get_number_rows_spanned (src));
  fo_context_set_orphans (context,
      fo_context_get_orphans (src));
  fo_context_set_overflow (context,
      fo_context_get_overflow (src));
  fo_context_set_padding (context,
      fo_context_get_padding (src));
  fo_context_set_padding_after (context,
      fo_context_get_padding_after (src));
  fo_context_set_padding_after_length (context,
      fo_context_get_padding_after_length (src));
  fo_context_set_padding_after_condity (context,
      fo_context_get_padding_after_condity (src));
  fo_context_set_padding_before (context,
      fo_context_get_padding_before (src));
  fo_context_set_padding_before_length (context,
      fo_context_get_padding_before_length (src));
  fo_context_set_padding_before_condity (context,
      fo_context_get_padding_before_condity (src));
  fo_context_set_padding_bottom (context,
      fo_context_get_padding_bottom (src));
  fo_context_set_padding_end (context,
      fo_context_get_padding_end (src));
  fo_context_set_padding_end_length (context,
      fo_context_get_padding_end_length (src));
  fo_context_set_padding_end_condity (context,
      fo_context_get_padding_end_condity (src));
  fo_context_set_padding_left (context,
      fo_context_get_padding_left (src));
  fo_context_set_padding_right (context,
      fo_context_get_padding_right (src));
  fo_context_set_padding_start (context,
      fo_context_get_padding_start (src));
  fo_context_set_padding_start_length (context,
      fo_context_get_padding_start_length (src));
  fo_context_set_padding_start_condity (context,
      fo_context_get_padding_start_condity (src));
  fo_context_set_padding_top (context,
      fo_context_get_padding_top (src));
  fo_context_set_page_height (context,
      fo_context_get_page_height (src));
  fo_context_set_page_width (context,
      fo_context_get_page_width (src));
  fo_context_set_provisional_distance_between_starts (context,
      fo_context_get_provisional_distance_between_starts (src));
  fo_context_set_provisional_label_separation (context,
      fo_context_get_provisional_label_separation (src));
  fo_context_set_ref_id (context,
      fo_context_get_ref_id (src));
  fo_context_set_region_name (context,
      fo_context_get_region_name (src));
  fo_context_set_role (context,
      fo_context_get_role (src));
  fo_context_set_scaling (context,
      fo_context_get_scaling (src));
  fo_context_set_scaling_method (context,
      fo_context_get_scaling_method (src));
  fo_context_set_score_spaces (context,
      fo_context_get_score_spaces (src));
  fo_context_set_source_document (context,
      fo_context_get_source_document (src));
  fo_context_set_space_after (context,
      fo_context_get_space_after (src));
  fo_context_set_space_before (context,
      fo_context_get_space_before (src));
  fo_context_set_space_end (context,
      fo_context_get_space_end (src));
  fo_context_set_space_start (context,
      fo_context_get_space_start (src));
  fo_context_set_span (context,
      fo_context_get_span (src));
  fo_context_set_src (context,
      fo_context_get_src (src));
  fo_context_set_start_indent (context,
      fo_context_get_start_indent (src));
  fo_context_set_table_layout (context,
      fo_context_get_table_layout (src));
  fo_context_set_text_align (context,
      fo_context_get_text_align (src));
  fo_context_set_text_indent (context,
      fo_context_get_text_indent (src));
  fo_context_set_unicode_bidi (context,
      fo_context_get_unicode_bidi (src));
  fo_context_set_white_space_collapse (context,
      fo_context_get_white_space_collapse (src));
  fo_context_set_white_space_treatment (context,
      fo_context_get_white_space_treatment (src));
  fo_context_set_widows (context,
      fo_context_get_widows (src));
  fo_context_set_width (context,
      fo_context_get_width (src));
  fo_context_set_wrap_option (context,
      fo_context_get_wrap_option (src));
  fo_context_set_writing_mode (context,
      fo_context_get_writing_mode (src));

  return context;
}

/**
 * fo_context_merge:
 * @primary:   Primary #FoContext.
 * @secondary: Secondary #FoContext.
 * 
 * Merge @primary and @secondary.
 *
 * When a property does not exist in @primary but does in @secondary,
 * set the property value in @primary to that in @secondary.
 **/
void
fo_context_merge (FoContext *primary, FoContext *secondary)
{
  if (primary == NULL && secondary != NULL)
    {
      primary = g_object_ref (secondary);
    }

  if (primary->alignment_adjust == NULL)
    {
      primary->alignment_adjust =
        g_object_ref (fo_property_alignment_adjust_get_initial ());
    }
  if (primary->alignment_baseline == NULL)
    {
      primary->alignment_baseline =
        g_object_ref (fo_property_alignment_baseline_get_initial ());
    }
  if (primary->background_color == NULL)
    {
      primary->background_color =
        g_object_ref (fo_property_background_color_get_initial ());
    }
  if (primary->background_image == NULL)
    {
      primary->background_image =
        g_object_ref (fo_property_background_image_get_initial ());
    }
  if (primary->baseline_shift == NULL)
    {
      primary->baseline_shift =
        g_object_ref (fo_property_baseline_shift_get_initial ());
    }
  if (primary->block_progression_dimension == NULL)
    {
      primary->block_progression_dimension =
        g_object_ref (fo_property_block_progression_dimension_get_initial ());
    }
  if (primary->border == NULL)
    {
      primary->border =
        g_object_ref (fo_property_border_get_initial ());
    }
  if (primary->border_after_color == NULL)
    {
      primary->border_after_color =
        g_object_ref (fo_property_border_after_color_get_initial ());
    }
  if (primary->border_after_precedence == NULL)
    {
      primary->border_after_precedence =
        g_object_ref (fo_property_border_after_precedence_get_initial ());
    }
  if (primary->border_after_style == NULL)
    {
      primary->border_after_style =
        g_object_ref (fo_property_border_after_style_get_initial ());
    }
  if (primary->border_after_width == NULL)
    {
      primary->border_after_width =
        g_object_ref (fo_property_border_after_width_get_initial ());
    }
  if (primary->border_before_color == NULL)
    {
      primary->border_before_color =
        g_object_ref (fo_property_border_before_color_get_initial ());
    }
  if (primary->border_before_precedence == NULL)
    {
      primary->border_before_precedence =
        g_object_ref (fo_property_border_before_precedence_get_initial ());
    }
  if (primary->border_before_style == NULL)
    {
      primary->border_before_style =
        g_object_ref (fo_property_border_before_style_get_initial ());
    }
  if (primary->border_before_width == NULL)
    {
      primary->border_before_width =
        g_object_ref (fo_property_border_before_width_get_initial ());
    }
  if (primary->border_bottom == NULL)
    {
      primary->border_bottom =
        g_object_ref (fo_property_border_bottom_get_initial ());
    }
  if (primary->border_bottom_color == NULL)
    {
      primary->border_bottom_color =
        g_object_ref (fo_property_border_bottom_color_get_initial ());
    }
  if (primary->border_bottom_style == NULL)
    {
      primary->border_bottom_style =
        g_object_ref (fo_property_border_bottom_style_get_initial ());
    }
  if (primary->border_bottom_width == NULL)
    {
      primary->border_bottom_width =
        g_object_ref (fo_property_border_bottom_width_get_initial ());
    }
  if (primary->border_collapse == NULL &&
      secondary->border_collapse != NULL)
    {
      primary->border_collapse =
        g_object_ref (secondary->border_collapse);
    }
  if (primary->border_color == NULL)
    {
      primary->border_color =
        g_object_ref (fo_property_border_color_get_initial ());
    }
  if (primary->border_end_color == NULL)
    {
      primary->border_end_color =
        g_object_ref (fo_property_border_end_color_get_initial ());
    }
  if (primary->border_end_precedence == NULL)
    {
      primary->border_end_precedence =
        g_object_ref (fo_property_border_end_precedence_get_initial ());
    }
  if (primary->border_end_style == NULL)
    {
      primary->border_end_style =
        g_object_ref (fo_property_border_end_style_get_initial ());
    }
  if (primary->border_end_width == NULL)
    {
      primary->border_end_width =
        g_object_ref (fo_property_border_end_width_get_initial ());
    }
  if (primary->border_left == NULL)
    {
      primary->border_left =
        g_object_ref (fo_property_border_left_get_initial ());
    }
  if (primary->border_left_color == NULL)
    {
      primary->border_left_color =
        g_object_ref (fo_property_border_left_color_get_initial ());
    }
  if (primary->border_left_style == NULL)
    {
      primary->border_left_style =
        g_object_ref (fo_property_border_left_style_get_initial ());
    }
  if (primary->border_left_width == NULL)
    {
      primary->border_left_width =
        g_object_ref (fo_property_border_left_width_get_initial ());
    }
  if (primary->border_right == NULL)
    {
      primary->border_right =
        g_object_ref (fo_property_border_right_get_initial ());
    }
  if (primary->border_right_color == NULL)
    {
      primary->border_right_color =
        g_object_ref (fo_property_border_right_color_get_initial ());
    }
  if (primary->border_right_style == NULL)
    {
      primary->border_right_style =
        g_object_ref (fo_property_border_right_style_get_initial ());
    }
  if (primary->border_right_width == NULL)
    {
      primary->border_right_width =
        g_object_ref (fo_property_border_right_width_get_initial ());
    }
  if (primary->border_separation == NULL &&
      secondary->border_separation != NULL)
    {
      primary->border_separation =
        g_object_ref (secondary->border_separation);
    }
  if (primary->border_start_color == NULL)
    {
      primary->border_start_color =
        g_object_ref (fo_property_border_start_color_get_initial ());
    }
  if (primary->border_start_precedence == NULL)
    {
      primary->border_start_precedence =
        g_object_ref (fo_property_border_start_precedence_get_initial ());
    }
  if (primary->border_start_style == NULL)
    {
      primary->border_start_style =
        g_object_ref (fo_property_border_start_style_get_initial ());
    }
  if (primary->border_start_width == NULL)
    {
      primary->border_start_width =
        g_object_ref (fo_property_border_start_width_get_initial ());
    }
  if (primary->border_style == NULL)
    {
      primary->border_style =
        g_object_ref (fo_property_border_style_get_initial ());
    }
  if (primary->border_top == NULL)
    {
      primary->border_top =
        g_object_ref (fo_property_border_top_get_initial ());
    }
  if (primary->border_top_color == NULL)
    {
      primary->border_top_color =
        g_object_ref (fo_property_border_top_color_get_initial ());
    }
  if (primary->border_top_style == NULL)
    {
      primary->border_top_style =
        g_object_ref (fo_property_border_top_style_get_initial ());
    }
  if (primary->border_top_width == NULL)
    {
      primary->border_top_width =
        g_object_ref (fo_property_border_top_width_get_initial ());
    }
  if (primary->border_width == NULL)
    {
      primary->border_width =
        g_object_ref (fo_property_border_width_get_initial ());
    }
  if (primary->break_after == NULL)
    {
      primary->break_after =
        g_object_ref (fo_property_break_after_get_initial ());
    }
  if (primary->break_before == NULL)
    {
      primary->break_before =
        g_object_ref (fo_property_break_before_get_initial ());
    }
  if (primary->character == NULL)
    {
      primary->character =
        g_object_ref (fo_property_character_get_initial ());
    }
  if (primary->clip == NULL)
    {
      primary->clip =
        g_object_ref (fo_property_clip_get_initial ());
    }
  if (primary->color == NULL &&
      secondary->color != NULL)
    {
      primary->color =
        g_object_ref (secondary->color);
    }
  if (primary->column_number == NULL)
    {
      primary->column_number =
        g_object_ref (fo_property_column_number_get_initial ());
    }
  if (primary->column_width == NULL)
    {
      primary->column_width =
        g_object_ref (fo_property_column_width_get_initial ());
    }
  if (primary->content_height == NULL)
    {
      primary->content_height =
        g_object_ref (fo_property_content_height_get_initial ());
    }
  if (primary->content_type == NULL)
    {
      primary->content_type =
        g_object_ref (fo_property_content_type_get_initial ());
    }
  if (primary->content_width == NULL)
    {
      primary->content_width =
        g_object_ref (fo_property_content_width_get_initial ());
    }
  if (primary->direction == NULL &&
      secondary->direction != NULL)
    {
      primary->direction =
        g_object_ref (secondary->direction);
    }
  if (primary->display_align == NULL &&
      secondary->display_align != NULL)
    {
      primary->display_align =
        g_object_ref (secondary->display_align);
    }
  if (primary->dominant_baseline == NULL)
    {
      primary->dominant_baseline =
        g_object_ref (fo_property_dominant_baseline_get_initial ());
    }
  if (primary->end_indent == NULL &&
      secondary->end_indent != NULL)
    {
      primary->end_indent =
        g_object_ref (secondary->end_indent);
    }
  if (primary->extent == NULL)
    {
      primary->extent =
        g_object_ref (fo_property_extent_get_initial ());
    }
  if (primary->flow_name == NULL)
    {
      primary->flow_name =
        g_object_ref (fo_property_flow_name_get_initial ());
    }
  if (primary->font_family == NULL &&
      secondary->font_family != NULL)
    {
      primary->font_family =
        g_object_ref (secondary->font_family);
    }
  if (primary->font_size == NULL &&
      secondary->font_size != NULL)
    {
      primary->font_size =
        g_object_ref (secondary->font_size);
    }
  if (primary->font_stretch == NULL &&
      secondary->font_stretch != NULL)
    {
      primary->font_stretch =
        g_object_ref (secondary->font_stretch);
    }
  if (primary->font_style == NULL &&
      secondary->font_style != NULL)
    {
      primary->font_style =
        g_object_ref (secondary->font_style);
    }
  if (primary->font_variant == NULL &&
      secondary->font_variant != NULL)
    {
      primary->font_variant =
        g_object_ref (secondary->font_variant);
    }
  if (primary->font_weight == NULL &&
      secondary->font_weight != NULL)
    {
      primary->font_weight =
        g_object_ref (secondary->font_weight);
    }
  if (primary->format == NULL)
    {
      primary->format =
        g_object_ref (fo_property_format_get_initial ());
    }
  if (primary->grouping_separator == NULL)
    {
      primary->grouping_separator =
        g_object_ref (fo_property_grouping_separator_get_initial ());
    }
  if (primary->grouping_size == NULL)
    {
      primary->grouping_size =
        g_object_ref (fo_property_grouping_size_get_initial ());
    }
  if (primary->height == NULL)
    {
      primary->height =
        g_object_ref (fo_property_height_get_initial ());
    }
  if (primary->id == NULL)
    {
      primary->id =
        g_object_ref (fo_property_id_get_initial ());
    }
  if (primary->inline_progression_dimension == NULL)
    {
      primary->inline_progression_dimension =
	g_object_ref (fo_property_inline_progression_dimension_get_initial ());
    }
  if (primary->keep_together == NULL &&
      secondary->keep_together != NULL)
    {
      primary->keep_together =
        g_object_ref (secondary->keep_together);
    }
  if (primary->keep_together_within_column == NULL)
    {
      primary->keep_together_within_column =
        g_object_ref (fo_property_keep_together_within_column_get_initial ());
    }
  if (primary->keep_together_within_line == NULL)
    {
      primary->keep_together_within_line =
        g_object_ref (fo_property_keep_together_within_line_get_initial ());
    }
  if (primary->keep_together_within_page == NULL)
    {
      primary->keep_together_within_page =
        g_object_ref (fo_property_keep_together_within_page_get_initial ());
    }
  if (primary->keep_with_next == NULL)
    {
      primary->keep_with_next =
        g_object_ref (fo_property_keep_with_next_get_initial ());
    }
  if (primary->keep_with_next_within_column == NULL)
    {
      primary->keep_with_next_within_column =
        g_object_ref (fo_property_keep_with_next_within_column_get_initial ());
    }
  if (primary->keep_with_next_within_line == NULL)
    {
      primary->keep_with_next_within_line =
        g_object_ref (fo_property_keep_with_next_within_line_get_initial ());
    }
  if (primary->keep_with_next_within_page == NULL)
    {
      primary->keep_with_next_within_page =
        g_object_ref (fo_property_keep_with_next_within_page_get_initial ());
    }
  if (primary->keep_with_previous == NULL)
    {
      primary->keep_with_previous =
        g_object_ref (fo_property_keep_with_previous_get_initial ());
    }
  if (primary->keep_with_previous_within_column == NULL)
    {
      primary->keep_with_previous_within_column =
        g_object_ref (fo_property_keep_with_previous_within_column_get_initial ());
    }
  if (primary->keep_with_previous_within_line == NULL)
    {
      primary->keep_with_previous_within_line =
        g_object_ref (fo_property_keep_with_previous_within_line_get_initial ());
    }
  if (primary->keep_with_previous_within_page == NULL)
    {
      primary->keep_with_previous_within_page =
        g_object_ref (fo_property_keep_with_previous_within_page_get_initial ());
    }
  if (primary->letter_value == NULL)
    {
      primary->letter_value =
        g_object_ref (fo_property_letter_value_get_initial ());
    }
  if (primary->line_height == NULL &&
      secondary->line_height != NULL)
    {
      primary->line_height =
        g_object_ref (secondary->line_height);
    }
  if (primary->line_stacking_strategy == NULL &&
      secondary->line_stacking_strategy != NULL)
    {
      primary->line_stacking_strategy =
        g_object_ref (secondary->line_stacking_strategy);
    }
  if (primary->linefeed_treatment == NULL &&
      secondary->linefeed_treatment != NULL)
    {
      primary->linefeed_treatment =
        g_object_ref (secondary->linefeed_treatment);
    }
  if (primary->margin == NULL)
    {
      primary->margin =
        g_object_ref (fo_property_margin_get_initial ());
    }
  if (primary->margin_bottom == NULL)
    {
      primary->margin_bottom =
        g_object_ref (fo_property_margin_bottom_get_initial ());
    }
  if (primary->margin_left == NULL)
    {
      primary->margin_left =
        g_object_ref (fo_property_margin_left_get_initial ());
    }
  if (primary->margin_right == NULL)
    {
      primary->margin_right =
        g_object_ref (fo_property_margin_right_get_initial ());
    }
  if (primary->margin_top == NULL)
    {
      primary->margin_top =
        g_object_ref (fo_property_margin_top_get_initial ());
    }
  if (primary->master_name == NULL)
    {
      primary->master_name =
        g_object_ref (fo_property_master_name_get_initial ());
    }
  if (primary->master_reference == NULL)
    {
      primary->master_reference =
        g_object_ref (fo_property_master_reference_get_initial ());
    }
  if (primary->media_usage == NULL)
    {
      primary->media_usage =
        g_object_ref (fo_property_media_usage_get_initial ());
    }
  if (primary->number_columns_repeated == NULL)
    {
      primary->number_columns_repeated =
        g_object_ref (fo_property_number_columns_repeated_get_initial ());
    }
  if (primary->number_columns_spanned == NULL)
    {
      primary->number_columns_spanned =
        g_object_ref (fo_property_number_columns_spanned_get_initial ());
    }
  if (primary->number_rows_spanned == NULL)
    {
      primary->number_rows_spanned =
        g_object_ref (fo_property_number_rows_spanned_get_initial ());
    }
  if (primary->orphans == NULL &&
      secondary->orphans != NULL)
    {
      primary->orphans =
        g_object_ref (secondary->orphans);
    }
  if (primary->overflow == NULL)
    {
      primary->overflow =
        g_object_ref (fo_property_overflow_get_initial ());
    }
  if (primary->padding == NULL)
    {
      primary->padding =
        g_object_ref (fo_property_padding_get_initial ());
    }
  if (primary->padding_after == NULL)
    {
      primary->padding_after =
        g_object_ref (fo_property_padding_after_get_initial ());
    }
  if (primary->padding_after_length == NULL)
    {
      primary->padding_after_length =
        g_object_ref (fo_property_padding_after_length_get_initial ());
    }
  if (primary->padding_after_condity == NULL)
    {
      primary->padding_after_condity =
        g_object_ref (fo_property_padding_after_condity_get_initial ());
    }
  if (primary->padding_before == NULL)
    {
      primary->padding_before =
        g_object_ref (fo_property_padding_before_get_initial ());
    }
  if (primary->padding_before_length == NULL)
    {
      primary->padding_before_length =
        g_object_ref (fo_property_padding_before_length_get_initial ());
    }
  if (primary->padding_before_condity == NULL)
    {
      primary->padding_before_condity =
        g_object_ref (fo_property_padding_before_condity_get_initial ());
    }
  if (primary->padding_bottom == NULL)
    {
      primary->padding_bottom =
        g_object_ref (fo_property_padding_bottom_get_initial ());
    }
  if (primary->padding_end == NULL)
    {
      primary->padding_end =
        g_object_ref (fo_property_padding_end_get_initial ());
    }
  if (primary->padding_end_length == NULL)
    {
      primary->padding_end_length =
        g_object_ref (fo_property_padding_end_length_get_initial ());
    }
  if (primary->padding_end_condity == NULL)
    {
      primary->padding_end_condity =
        g_object_ref (fo_property_padding_end_condity_get_initial ());
    }
  if (primary->padding_left == NULL)
    {
      primary->padding_left =
        g_object_ref (fo_property_padding_left_get_initial ());
    }
  if (primary->padding_right == NULL)
    {
      primary->padding_right =
        g_object_ref (fo_property_padding_right_get_initial ());
    }
  if (primary->padding_start == NULL)
    {
      primary->padding_start =
        g_object_ref (fo_property_padding_start_get_initial ());
    }
  if (primary->padding_start_length == NULL)
    {
      primary->padding_start_length =
        g_object_ref (fo_property_padding_start_length_get_initial ());
    }
  if (primary->padding_start_condity == NULL)
    {
      primary->padding_start_condity =
        g_object_ref (fo_property_padding_start_condity_get_initial ());
    }
  if (primary->padding_top == NULL)
    {
      primary->padding_top =
        g_object_ref (fo_property_padding_top_get_initial ());
    }
  if (primary->page_height == NULL)
    {
      primary->page_height =
        g_object_ref (fo_property_page_height_get_initial ());
    }
  if (primary->page_width == NULL)
    {
      primary->page_width =
        g_object_ref (fo_property_page_width_get_initial ());
    }
  if (primary->provisional_distance_between_starts == NULL &&
      secondary->provisional_distance_between_starts != NULL)
    {
      primary->provisional_distance_between_starts =
        g_object_ref (secondary->provisional_distance_between_starts);
    }
  if (primary->provisional_label_separation == NULL &&
      secondary->provisional_label_separation != NULL)
    {
      primary->provisional_label_separation =
        g_object_ref (secondary->provisional_label_separation);
    }
  if (primary->ref_id == NULL)
    {
      primary->ref_id =
        g_object_ref (fo_property_ref_id_get_initial ());
    }
  if (primary->region_name == NULL)
    {
      primary->region_name =
        g_object_ref (fo_property_region_name_get_initial ());
    }
  if (primary->role == NULL)
    {
      primary->role =
        g_object_ref (fo_property_role_get_initial ());
    }
  if (primary->scaling == NULL)
    {
      primary->scaling =
        g_object_ref (fo_property_scaling_get_initial ());
    }
  if (primary->scaling_method == NULL)
    {
      primary->scaling_method =
        g_object_ref (fo_property_scaling_method_get_initial ());
    }
  if (primary->score_spaces == NULL &&
      secondary->score_spaces != NULL)
    {
      primary->score_spaces =
        g_object_ref (secondary->score_spaces);
    }
  if (primary->source_document == NULL)
    {
      primary->source_document =
        g_object_ref (fo_property_source_document_get_initial ());
    }
  if (primary->space_after == NULL)
    {
      primary->space_after =
	g_object_ref (fo_property_space_after_get_initial ());
    }
  if (primary->space_before == NULL)
    {
      primary->space_before =
	g_object_ref (fo_property_space_before_get_initial ());
    }
  if (primary->space_end == NULL)
    {
      primary->space_end =
	g_object_ref (fo_property_space_end_get_initial ());
    }
  if (primary->space_start == NULL)
    {
      primary->space_start =
	g_object_ref (fo_property_space_start_get_initial ());
    }
  if (primary->span == NULL)
    {
      primary->span =
        g_object_ref (fo_property_span_get_initial ());
    }
  if (primary->src == NULL)
    {
      primary->src =
        g_object_ref (fo_property_src_get_initial ());
    }
  if (primary->start_indent == NULL &&
      secondary->start_indent != NULL)
    {
      primary->start_indent =
        g_object_ref (secondary->start_indent);
    }
  if (primary->table_layout == NULL)
    {
      primary->table_layout =
        g_object_ref (fo_property_table_layout_get_initial ());
    }
  if (primary->text_align == NULL &&
      secondary->text_align != NULL)
    {
      primary->text_align =
        g_object_ref (secondary->text_align);
    }
  if (primary->text_indent == NULL &&
      secondary->text_indent != NULL)
    {
      primary->text_indent =
        g_object_ref (secondary->text_indent);
    }
  if (primary->unicode_bidi == NULL)
    {
      primary->unicode_bidi =
        g_object_ref (fo_property_unicode_bidi_get_initial ());
    }
  if (primary->white_space_collapse == NULL &&
      secondary->white_space_collapse != NULL)
    {
      primary->white_space_collapse =
        g_object_ref (secondary->white_space_collapse);
    }
  if (primary->white_space_treatment == NULL &&
      secondary->white_space_treatment != NULL)
    {
      primary->white_space_treatment =
        g_object_ref (secondary->white_space_treatment);
    }
  if (primary->widows == NULL &&
      secondary->widows != NULL)
    {
      primary->widows =
        g_object_ref (secondary->widows);
    }
  if (primary->width == NULL)
    {
      primary->width =
        g_object_ref (fo_property_width_get_initial ());
    }
  if (primary->wrap_option == NULL &&
      secondary->wrap_option != NULL)
    {
      primary->wrap_option =
        g_object_ref (secondary->wrap_option);
    }
  if (primary->writing_mode == NULL &&
      secondary->writing_mode != NULL)
    {
      primary->writing_mode =
        g_object_ref (secondary->writing_mode);
    }
}

/**
 * fo_context_property_slist_foreach:
 * @property: #FoProperty object.
 * @context:  #FoContext.
 * 
 * Add @property to @context.
 **/
void
fo_context_property_slist_foreach (gpointer property,
				   gpointer context)
{
  if (FO_IS_PROPERTY_ALIGNMENT_ADJUST (property))
    {
      fo_context_set_alignment_adjust (context, property);
    }
  else if (FO_IS_PROPERTY_ALIGNMENT_BASELINE (property))
    {
      fo_context_set_alignment_baseline (context, property);
    }
  else if (FO_IS_PROPERTY_BACKGROUND_COLOR (property))
    {
      fo_context_set_background_color (context, property);
    }
  else if (FO_IS_PROPERTY_BACKGROUND_IMAGE (property))
    {
      fo_context_set_background_image (context, property);
    }
  else if (FO_IS_PROPERTY_BASELINE_SHIFT (property))
    {
      fo_context_set_baseline_shift (context, property);
    }
  else if (FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION (property))
    {
      fo_context_set_block_progression_dimension (context, property);
    }
  else if (FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MINIMUM (property))
    {
      fo_context_set_block_progression_dimension_minimum (context, property);
    }
  else if (FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_OPTIMUM (property))
    {
      fo_context_set_block_progression_dimension_optimum (context, property);
    }
  else if (FO_IS_PROPERTY_BLOCK_PROGRESSION_DIMENSION_MAXIMUM (property))
    {
      fo_context_set_block_progression_dimension_maximum (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER (property))
    {
      fo_context_set_border (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_AFTER_COLOR (property))
    {
      fo_context_set_border_after_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_AFTER_PRECEDENCE (property))
    {
      fo_context_set_border_after_precedence (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_AFTER_STYLE (property))
    {
      fo_context_set_border_after_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_AFTER_WIDTH (property))
    {
      fo_context_set_border_after_width (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_BEFORE_COLOR (property))
    {
      fo_context_set_border_before_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_BEFORE_PRECEDENCE (property))
    {
      fo_context_set_border_before_precedence (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_BEFORE_STYLE (property))
    {
      fo_context_set_border_before_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_BEFORE_WIDTH (property))
    {
      fo_context_set_border_before_width (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_BOTTOM (property))
    {
      fo_context_set_border_bottom (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_BOTTOM_COLOR (property))
    {
      fo_context_set_border_bottom_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_BOTTOM_STYLE (property))
    {
      fo_context_set_border_bottom_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_BOTTOM_WIDTH (property))
    {
      fo_context_set_border_bottom_width (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_COLLAPSE (property))
    {
      fo_context_set_border_collapse (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_COLOR (property))
    {
      fo_context_set_border_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_END_COLOR (property))
    {
      fo_context_set_border_end_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_END_PRECEDENCE (property))
    {
      fo_context_set_border_end_precedence (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_END_STYLE (property))
    {
      fo_context_set_border_end_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_END_WIDTH (property))
    {
      fo_context_set_border_end_width (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_LEFT (property))
    {
      fo_context_set_border_left (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_LEFT_COLOR (property))
    {
      fo_context_set_border_left_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_LEFT_STYLE (property))
    {
      fo_context_set_border_left_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_LEFT_WIDTH (property))
    {
      fo_context_set_border_left_width (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_RIGHT (property))
    {
      fo_context_set_border_right (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_RIGHT_COLOR (property))
    {
      fo_context_set_border_right_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_RIGHT_STYLE (property))
    {
      fo_context_set_border_right_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_RIGHT_WIDTH (property))
    {
      fo_context_set_border_right_width (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_SEPARATION (property))
    {
      fo_context_set_border_separation (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_START_COLOR (property))
    {
      fo_context_set_border_start_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_START_PRECEDENCE (property))
    {
      fo_context_set_border_start_precedence (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_START_STYLE (property))
    {
      fo_context_set_border_start_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_START_WIDTH (property))
    {
      fo_context_set_border_start_width (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_STYLE (property))
    {
      fo_context_set_border_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_TOP (property))
    {
      fo_context_set_border_top (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_TOP_COLOR (property))
    {
      fo_context_set_border_top_color (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_TOP_STYLE (property))
    {
      fo_context_set_border_top_style (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_TOP_WIDTH (property))
    {
      fo_context_set_border_top_width (context, property);
    }
  else if (FO_IS_PROPERTY_BORDER_WIDTH (property))
    {
      fo_context_set_border_width (context, property);
    }
  else if (FO_IS_PROPERTY_BREAK_AFTER (property))
    {
      fo_context_set_break_after (context, property);
    }
  else if (FO_IS_PROPERTY_BREAK_BEFORE (property))
    {
      fo_context_set_break_before (context, property);
    }
  else if (FO_IS_PROPERTY_CHARACTER (property))
    {
      fo_context_set_character (context, property);
    }
  else if (FO_IS_PROPERTY_CLIP (property))
    {
      fo_context_set_clip (context, property);
    }
  else if (FO_IS_PROPERTY_COLOR (property))
    {
      fo_context_set_color (context, property);
    }
  else if (FO_IS_PROPERTY_COLUMN_NUMBER (property))
    {
      fo_context_set_column_number (context, property);
    }
  else if (FO_IS_PROPERTY_COLUMN_WIDTH (property))
    {
      fo_context_set_column_width (context, property);
    }
  else if (FO_IS_PROPERTY_CONTENT_HEIGHT (property))
    {
      fo_context_set_content_height (context, property);
    }
  else if (FO_IS_PROPERTY_CONTENT_TYPE (property))
    {
      fo_context_set_content_type (context, property);
    }
  else if (FO_IS_PROPERTY_CONTENT_WIDTH (property))
    {
      fo_context_set_content_width (context, property);
    }
  else if (FO_IS_PROPERTY_DIRECTION (property))
    {
      fo_context_set_direction (context, property);
    }
  else if (FO_IS_PROPERTY_DISPLAY_ALIGN (property))
    {
      fo_context_set_display_align (context, property);
    }
  else if (FO_IS_PROPERTY_DOMINANT_BASELINE (property))
    {
      fo_context_set_dominant_baseline (context, property);
    }
  else if (FO_IS_PROPERTY_END_INDENT (property))
    {
      fo_context_set_end_indent (context, property);
    }
  else if (FO_IS_PROPERTY_EXTENT (property))
    {
      fo_context_set_extent (context, property);
    }
  else if (FO_IS_PROPERTY_FLOW_NAME (property))
    {
      fo_context_set_flow_name (context, property);
    }
  else if (FO_IS_PROPERTY_FONT_FAMILY (property))
    {
      fo_context_set_font_family (context, property);
    }
  else if (FO_IS_PROPERTY_FONT_SIZE (property))
    {
      fo_context_set_font_size (context, property);
    }
  else if (FO_IS_PROPERTY_FONT_STRETCH (property))
    {
      fo_context_set_font_stretch (context, property);
    }
  else if (FO_IS_PROPERTY_FONT_STYLE (property))
    {
      fo_context_set_font_style (context, property);
    }
  else if (FO_IS_PROPERTY_FONT_VARIANT (property))
    {
      fo_context_set_font_variant (context, property);
    }
  else if (FO_IS_PROPERTY_FONT_WEIGHT (property))
    {
      fo_context_set_font_weight (context, property);
    }
  else if (FO_IS_PROPERTY_FORMAT (property))
    {
      fo_context_set_format (context, property);
    }
  else if (FO_IS_PROPERTY_GROUPING_SEPARATOR (property))
    {
      fo_context_set_grouping_separator (context, property);
    }
  else if (FO_IS_PROPERTY_GROUPING_SIZE (property))
    {
      fo_context_set_grouping_size (context, property);
    }
  else if (FO_IS_PROPERTY_HEIGHT (property))
    {
      fo_context_set_height (context, property);
    }
  else if (FO_IS_PROPERTY_ID (property))
    {
      fo_context_set_id (context, property);
    }
  else if (FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION (property))
    {
      fo_context_set_inline_progression_dimension (context, property);
    }
  else if (FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION_MINIMUM (property))
    {
      fo_context_set_inline_progression_dimension_minimum (context, property);
    }
  else if (FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION_OPTIMUM (property))
    {
      fo_context_set_inline_progression_dimension_optimum (context, property);
    }
  else if (FO_IS_PROPERTY_INLINE_PROGRESSION_DIMENSION_MAXIMUM (property))
    {
      fo_context_set_inline_progression_dimension_maximum (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_TOGETHER (property))
    {
      fo_context_set_keep_together (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_COLUMN (property))
    {
      fo_context_set_keep_together_within_column (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_LINE (property))
    {
      fo_context_set_keep_together_within_line (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_TOGETHER_WITHIN_PAGE (property))
    {
      fo_context_set_keep_together_within_page (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_WITH_NEXT (property))
    {
      fo_context_set_keep_with_next (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_COLUMN (property))
    {
      fo_context_set_keep_with_next_within_column (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE (property))
    {
      fo_context_set_keep_with_next_within_line (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_PAGE (property))
    {
      fo_context_set_keep_with_next_within_page (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS (property))
    {
      fo_context_set_keep_with_previous (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_COLUMN (property))
    {
      fo_context_set_keep_with_previous_within_column (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_LINE (property))
    {
      fo_context_set_keep_with_previous_within_line (context, property);
    }
  else if (FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_WITHIN_PAGE (property))
    {
      fo_context_set_keep_with_previous_within_page (context, property);
    }
  else if (FO_IS_PROPERTY_LETTER_VALUE (property))
    {
      fo_context_set_letter_value (context, property);
    }
  else if (FO_IS_PROPERTY_LINE_HEIGHT (property))
    {
      fo_context_set_line_height (context, property);
    }
  else if (FO_IS_PROPERTY_LINE_STACKING_STRATEGY (property))
    {
      fo_context_set_line_stacking_strategy (context, property);
    }
  else if (FO_IS_PROPERTY_LINEFEED_TREATMENT (property))
    {
      fo_context_set_linefeed_treatment (context, property);
    }
  else if (FO_IS_PROPERTY_MARGIN (property))
    {
      fo_context_set_margin (context, property);
    }
  else if (FO_IS_PROPERTY_MARGIN_BOTTOM (property))
    {
      fo_context_set_margin_bottom (context, property);
    }
  else if (FO_IS_PROPERTY_MARGIN_LEFT (property))
    {
      fo_context_set_margin_left (context, property);
    }
  else if (FO_IS_PROPERTY_MARGIN_RIGHT (property))
    {
      fo_context_set_margin_right (context, property);
    }
  else if (FO_IS_PROPERTY_MARGIN_TOP (property))
    {
      fo_context_set_margin_top (context, property);
    }
  else if (FO_IS_PROPERTY_MASTER_NAME (property))
    {
      fo_context_set_master_name (context, property);
    }
  else if (FO_IS_PROPERTY_MASTER_REFERENCE (property))
    {
      fo_context_set_master_reference (context, property);
    }
  else if (FO_IS_PROPERTY_MEDIA_USAGE (property))
    {
      fo_context_set_media_usage (context, property);
    }
  else if (FO_IS_PROPERTY_NUMBER_COLUMNS_REPEATED (property))
    {
      fo_context_set_number_columns_repeated (context, property);
    }
  else if (FO_IS_PROPERTY_NUMBER_COLUMNS_SPANNED (property))
    {
      fo_context_set_number_columns_spanned (context, property);
    }
  else if (FO_IS_PROPERTY_NUMBER_ROWS_SPANNED (property))
    {
      fo_context_set_number_rows_spanned (context, property);
    }
  else if (FO_IS_PROPERTY_ORPHANS (property))
    {
      fo_context_set_orphans (context, property);
    }
  else if (FO_IS_PROPERTY_OVERFLOW (property))
    {
      fo_context_set_overflow (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING (property))
    {
      fo_context_set_padding (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_AFTER (property))
    {
      fo_context_set_padding_after (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_AFTER_LENGTH (property))
    {
      fo_context_set_padding_after_length (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_AFTER_CONDITY (property))
    {
      fo_context_set_padding_after_condity (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_BEFORE (property))
    {
      fo_context_set_padding_before (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_BEFORE_LENGTH (property))
    {
      fo_context_set_padding_before_length (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_BEFORE_CONDITY (property))
    {
      fo_context_set_padding_before_condity (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_BOTTOM (property))
    {
      fo_context_set_padding_bottom (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_END (property))
    {
      fo_context_set_padding_end (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_END_LENGTH (property))
    {
      fo_context_set_padding_end_length (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_END_CONDITY (property))
    {
      fo_context_set_padding_end_condity (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_LEFT (property))
    {
      fo_context_set_padding_left (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_RIGHT (property))
    {
      fo_context_set_padding_right (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_START (property))
    {
      fo_context_set_padding_start (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_START_LENGTH (property))
    {
      fo_context_set_padding_start_length (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_START_CONDITY (property))
    {
      fo_context_set_padding_start_condity (context, property);
    }
  else if (FO_IS_PROPERTY_PADDING_TOP (property))
    {
      fo_context_set_padding_top (context, property);
    }
  else if (FO_IS_PROPERTY_PAGE_HEIGHT (property))
    {
      fo_context_set_page_height (context, property);
    }
  else if (FO_IS_PROPERTY_PAGE_WIDTH (property))
    {
      fo_context_set_page_width (context, property);
    }
  else if (FO_IS_PROPERTY_PROVISIONAL_DISTANCE_BETWEEN_STARTS (property))
    {
      fo_context_set_provisional_distance_between_starts (context, property);
    }
  else if (FO_IS_PROPERTY_PROVISIONAL_LABEL_SEPARATION (property))
    {
      fo_context_set_provisional_label_separation (context, property);
    }
  else if (FO_IS_PROPERTY_REF_ID (property))
    {
      fo_context_set_ref_id (context, property);
    }
  else if (FO_IS_PROPERTY_REGION_NAME (property))
    {
      fo_context_set_region_name (context, property);
    }
  else if (FO_IS_PROPERTY_ROLE (property))
    {
      fo_context_set_role (context, property);
    }
  else if (FO_IS_PROPERTY_SCALING (property))
    {
      fo_context_set_scaling (context, property);
    }
  else if (FO_IS_PROPERTY_SCALING_METHOD (property))
    {
      fo_context_set_scaling_method (context, property);
    }
  else if (FO_IS_PROPERTY_SCORE_SPACES (property))
    {
      fo_context_set_score_spaces (context, property);
    }
  else if (FO_IS_PROPERTY_SOURCE_DOCUMENT (property))
    {
      fo_context_set_source_document (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_AFTER (property))
    {
      fo_context_set_space_after (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_AFTER_MINIMUM (property))
    {
      fo_context_set_space_after_minimum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_AFTER_OPTIMUM (property))
    {
      fo_context_set_space_after_optimum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_AFTER_MAXIMUM (property))
    {
      fo_context_set_space_after_maximum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_AFTER_PRECEDENCE (property))
    {
      fo_context_set_space_after_precedence (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_AFTER_CONDITY (property))
    {
      fo_context_set_space_after_condity (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_BEFORE (property))
    {
      fo_context_set_space_before (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_BEFORE_MINIMUM (property))
    {
      fo_context_set_space_before_minimum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_BEFORE_OPTIMUM (property))
    {
      fo_context_set_space_before_optimum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_BEFORE_MAXIMUM (property))
    {
      fo_context_set_space_before_maximum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_BEFORE_PRECEDENCE (property))
    {
      fo_context_set_space_before_precedence (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_BEFORE_CONDITY (property))
    {
      fo_context_set_space_before_condity (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_END (property))
    {
      fo_context_set_space_end (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_END_MINIMUM (property))
    {
      fo_context_set_space_end_minimum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_END_OPTIMUM (property))
    {
      fo_context_set_space_end_optimum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_END_MAXIMUM (property))
    {
      fo_context_set_space_end_maximum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_END_PRECEDENCE (property))
    {
      fo_context_set_space_end_precedence (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_END_CONDITY (property))
    {
      fo_context_set_space_end_condity (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_START (property))
    {
      fo_context_set_space_start (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_START_MINIMUM (property))
    {
      fo_context_set_space_start_minimum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_START_OPTIMUM (property))
    {
      fo_context_set_space_start_optimum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_START_MAXIMUM (property))
    {
      fo_context_set_space_start_maximum (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_START_PRECEDENCE (property))
    {
      fo_context_set_space_start_precedence (context, property);
    }
  else if (FO_IS_PROPERTY_SPACE_START_CONDITY (property))
    {
      fo_context_set_space_start_condity (context, property);
    }
  else if (FO_IS_PROPERTY_SPAN (property))
    {
      fo_context_set_span (context, property);
    }
  else if (FO_IS_PROPERTY_SRC (property))
    {
      fo_context_set_src (context, property);
    }
  else if (FO_IS_PROPERTY_START_INDENT (property))
    {
      fo_context_set_start_indent (context, property);
    }
  else if (FO_IS_PROPERTY_TABLE_LAYOUT (property))
    {
      fo_context_set_table_layout (context, property);
    }
  else if (FO_IS_PROPERTY_TEXT_ALIGN (property))
    {
      fo_context_set_text_align (context, property);
    }
  else if (FO_IS_PROPERTY_TEXT_INDENT (property))
    {
      fo_context_set_text_indent (context, property);
    }
  else if (FO_IS_PROPERTY_UNICODE_BIDI (property))
    {
      fo_context_set_unicode_bidi (context, property);
    }
  else if (FO_IS_PROPERTY_WHITE_SPACE_COLLAPSE (property))
    {
      fo_context_set_white_space_collapse (context, property);
    }
  else if (FO_IS_PROPERTY_WHITE_SPACE_TREATMENT (property))
    {
      fo_context_set_white_space_treatment (context, property);
    }
  else if (FO_IS_PROPERTY_WIDOWS (property))
    {
      fo_context_set_widows (context, property);
    }
  else if (FO_IS_PROPERTY_WIDTH (property))
    {
      fo_context_set_width (context, property);
    }
  else if (FO_IS_PROPERTY_WRAP_OPTION (property))
    {
      fo_context_set_wrap_option (context, property);
    }
  else if (FO_IS_PROPERTY_WRITING_MODE (property))
    {
      fo_context_set_writing_mode (context, property);
    }
  else
    {
      gchar *property_dump = fo_object_debug_sprintf (property);

      g_warning (_("Unsupported property: %s"),
		 property_dump);

      g_free (property_dump);
    }
}

/**
 * fo_context_update_from_slist:
 * @context:       #FoContext to be updated.
 * @property_list: #GSList of #FoProperty objects.
 * 
 * Add each #FoProperty in @property_list to @context.
 **/
void
fo_context_update_from_slist (FoContext *context,
			      GSList *property_list)
{
  g_slist_foreach (property_list,
		   fo_context_property_slist_foreach,
		   (gpointer) context);
}

/**
 * fo_context_debug_dump:
 * @object: #FoContext instance to be dumped.
 * @depth:  Relative indent to apply to the output.
 * 
 * Dump information about @object and its properties.
 **/
void
fo_context_debug_dump (FoObject *object,
		       gint      depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* object_sprintf;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_CONTEXT (object));

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);
  g_free (indent);

  fo_context_debug_dump_properties (FO_CONTEXT (object),
				    depth + 2);
}

/**
 * fo_context_debug_dump_properties:
 * @fo_context: The #FoContext object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_context_debug_dump_properties (FoContext *fo_context,
                                  gint  depth)
{

  g_return_if_fail (fo_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (fo_context));

  fo_object_debug_dump (fo_context->alignment_adjust, depth);
  fo_object_debug_dump (fo_context->alignment_baseline, depth);
  fo_object_debug_dump (fo_context->background_color, depth);
  fo_object_debug_dump (fo_context->background_image, depth);
  fo_object_debug_dump (fo_context->baseline_shift, depth);
  fo_object_debug_dump (fo_context->block_progression_dimension, depth);
  fo_object_debug_dump (fo_context->block_progression_dimension_minimum, depth);
  fo_object_debug_dump (fo_context->block_progression_dimension_optimum, depth);
  fo_object_debug_dump (fo_context->block_progression_dimension_maximum, depth);
  fo_object_debug_dump (fo_context->border, depth);
  fo_object_debug_dump (fo_context->border_after_color, depth);
  fo_object_debug_dump (fo_context->border_after_precedence, depth);
  fo_object_debug_dump (fo_context->border_after_style, depth);
  fo_object_debug_dump (fo_context->border_after_width, depth);
  fo_object_debug_dump (fo_context->border_before_color, depth);
  fo_object_debug_dump (fo_context->border_before_precedence, depth);
  fo_object_debug_dump (fo_context->border_before_style, depth);
  fo_object_debug_dump (fo_context->border_before_width, depth);
  fo_object_debug_dump (fo_context->border_bottom, depth);
  fo_object_debug_dump (fo_context->border_bottom_color, depth);
  fo_object_debug_dump (fo_context->border_bottom_style, depth);
  fo_object_debug_dump (fo_context->border_bottom_width, depth);
  fo_object_debug_dump (fo_context->border_collapse, depth);
  fo_object_debug_dump (fo_context->border_color, depth);
  fo_object_debug_dump (fo_context->border_end_color, depth);
  fo_object_debug_dump (fo_context->border_end_precedence, depth);
  fo_object_debug_dump (fo_context->border_end_style, depth);
  fo_object_debug_dump (fo_context->border_end_width, depth);
  fo_object_debug_dump (fo_context->border_left, depth);
  fo_object_debug_dump (fo_context->border_left_color, depth);
  fo_object_debug_dump (fo_context->border_left_style, depth);
  fo_object_debug_dump (fo_context->border_left_width, depth);
  fo_object_debug_dump (fo_context->border_right, depth);
  fo_object_debug_dump (fo_context->border_right_color, depth);
  fo_object_debug_dump (fo_context->border_right_style, depth);
  fo_object_debug_dump (fo_context->border_right_width, depth);
  fo_object_debug_dump (fo_context->border_separation, depth);
  fo_object_debug_dump (fo_context->border_start_color, depth);
  fo_object_debug_dump (fo_context->border_start_precedence, depth);
  fo_object_debug_dump (fo_context->border_start_style, depth);
  fo_object_debug_dump (fo_context->border_start_width, depth);
  fo_object_debug_dump (fo_context->border_style, depth);
  fo_object_debug_dump (fo_context->border_top, depth);
  fo_object_debug_dump (fo_context->border_top_color, depth);
  fo_object_debug_dump (fo_context->border_top_style, depth);
  fo_object_debug_dump (fo_context->border_top_width, depth);
  fo_object_debug_dump (fo_context->border_width, depth);
  fo_object_debug_dump (fo_context->break_after, depth);
  fo_object_debug_dump (fo_context->break_before, depth);
  fo_object_debug_dump (fo_context->character, depth);
  fo_object_debug_dump (fo_context->clip, depth);
  fo_object_debug_dump (fo_context->color, depth);
  fo_object_debug_dump (fo_context->column_number, depth);
  fo_object_debug_dump (fo_context->column_width, depth);
  fo_object_debug_dump (fo_context->content_height, depth);
  fo_object_debug_dump (fo_context->content_type, depth);
  fo_object_debug_dump (fo_context->content_width, depth);
  fo_object_debug_dump (fo_context->direction, depth);
  fo_object_debug_dump (fo_context->display_align, depth);
  fo_object_debug_dump (fo_context->dominant_baseline, depth);
  fo_object_debug_dump (fo_context->end_indent, depth);
  fo_object_debug_dump (fo_context->extent, depth);
  fo_object_debug_dump (fo_context->flow_name, depth);
  fo_object_debug_dump (fo_context->font_family, depth);
  fo_object_debug_dump (fo_context->font_size, depth);
  fo_object_debug_dump (fo_context->font_stretch, depth);
  fo_object_debug_dump (fo_context->font_style, depth);
  fo_object_debug_dump (fo_context->font_variant, depth);
  fo_object_debug_dump (fo_context->font_weight, depth);
  fo_object_debug_dump (fo_context->format, depth);
  fo_object_debug_dump (fo_context->grouping_separator, depth);
  fo_object_debug_dump (fo_context->grouping_size, depth);
  fo_object_debug_dump (fo_context->height, depth);
  fo_object_debug_dump (fo_context->id, depth);
  fo_object_debug_dump (fo_context->inline_progression_dimension, depth);
  fo_object_debug_dump (fo_context->inline_progression_dimension_minimum, depth);
  fo_object_debug_dump (fo_context->inline_progression_dimension_optimum, depth);
  fo_object_debug_dump (fo_context->inline_progression_dimension_maximum, depth);
  fo_object_debug_dump (fo_context->keep_together, depth);
  fo_object_debug_dump (fo_context->keep_together_within_column, depth);
  fo_object_debug_dump (fo_context->keep_together_within_line, depth);
  fo_object_debug_dump (fo_context->keep_together_within_page, depth);
  fo_object_debug_dump (fo_context->keep_with_next, depth);
  fo_object_debug_dump (fo_context->keep_with_next_within_column, depth);
  fo_object_debug_dump (fo_context->keep_with_next_within_line, depth);
  fo_object_debug_dump (fo_context->keep_with_next_within_page, depth);
  fo_object_debug_dump (fo_context->keep_with_previous, depth);
  fo_object_debug_dump (fo_context->keep_with_previous_within_column, depth);
  fo_object_debug_dump (fo_context->keep_with_previous_within_line, depth);
  fo_object_debug_dump (fo_context->keep_with_previous_within_page, depth);
  fo_object_debug_dump (fo_context->letter_value, depth);
  fo_object_debug_dump (fo_context->line_height, depth);
  fo_object_debug_dump (fo_context->line_stacking_strategy, depth);
  fo_object_debug_dump (fo_context->linefeed_treatment, depth);
  fo_object_debug_dump (fo_context->margin, depth);
  fo_object_debug_dump (fo_context->margin_bottom, depth);
  fo_object_debug_dump (fo_context->margin_left, depth);
  fo_object_debug_dump (fo_context->margin_right, depth);
  fo_object_debug_dump (fo_context->margin_top, depth);
  fo_object_debug_dump (fo_context->master_name, depth);
  fo_object_debug_dump (fo_context->master_reference, depth);
  fo_object_debug_dump (fo_context->media_usage, depth);
  fo_object_debug_dump (fo_context->number_columns_repeated, depth);
  fo_object_debug_dump (fo_context->number_columns_spanned, depth);
  fo_object_debug_dump (fo_context->number_rows_spanned, depth);
  fo_object_debug_dump (fo_context->orphans, depth);
  fo_object_debug_dump (fo_context->overflow, depth);
  fo_object_debug_dump (fo_context->padding, depth);
  fo_object_debug_dump (fo_context->padding_after, depth);
  fo_object_debug_dump (fo_context->padding_before, depth);
  fo_object_debug_dump (fo_context->padding_before_length, depth);
  fo_object_debug_dump (fo_context->padding_before_condity, depth);
  fo_object_debug_dump (fo_context->padding_bottom, depth);
  fo_object_debug_dump (fo_context->padding_end, depth);
  fo_object_debug_dump (fo_context->padding_left, depth);
  fo_object_debug_dump (fo_context->padding_right, depth);
  fo_object_debug_dump (fo_context->padding_start, depth);
  fo_object_debug_dump (fo_context->padding_top, depth);
  fo_object_debug_dump (fo_context->page_height, depth);
  fo_object_debug_dump (fo_context->page_width, depth);
  fo_object_debug_dump (fo_context->provisional_distance_between_starts, depth);
  fo_object_debug_dump (fo_context->provisional_label_separation, depth);
  fo_object_debug_dump (fo_context->ref_id, depth);
  fo_object_debug_dump (fo_context->region_name, depth);
  fo_object_debug_dump (fo_context->role, depth);
  fo_object_debug_dump (fo_context->scaling, depth);
  fo_object_debug_dump (fo_context->scaling_method, depth);
  fo_object_debug_dump (fo_context->score_spaces, depth);
  fo_object_debug_dump (fo_context->source_document, depth);
  fo_object_debug_dump (fo_context->space_after, depth);
  fo_object_debug_dump (fo_context->space_after_minimum, depth);
  fo_object_debug_dump (fo_context->space_after_optimum, depth);
  fo_object_debug_dump (fo_context->space_after_maximum, depth);
  fo_object_debug_dump (fo_context->space_after_precedence, depth);
  fo_object_debug_dump (fo_context->space_after_condity, depth);
  fo_object_debug_dump (fo_context->space_before, depth);
  fo_object_debug_dump (fo_context->space_before_minimum, depth);
  fo_object_debug_dump (fo_context->space_before_optimum, depth);
  fo_object_debug_dump (fo_context->space_before_maximum, depth);
  fo_object_debug_dump (fo_context->space_before_precedence, depth);
  fo_object_debug_dump (fo_context->space_before_condity, depth);
  fo_object_debug_dump (fo_context->space_end, depth);
  fo_object_debug_dump (fo_context->space_end_minimum, depth);
  fo_object_debug_dump (fo_context->space_end_optimum, depth);
  fo_object_debug_dump (fo_context->space_end_maximum, depth);
  fo_object_debug_dump (fo_context->space_end_precedence, depth);
  fo_object_debug_dump (fo_context->space_end_condity, depth);
  fo_object_debug_dump (fo_context->space_start, depth);
  fo_object_debug_dump (fo_context->space_start_minimum, depth);
  fo_object_debug_dump (fo_context->space_start_optimum, depth);
  fo_object_debug_dump (fo_context->space_start_maximum, depth);
  fo_object_debug_dump (fo_context->space_start_precedence, depth);
  fo_object_debug_dump (fo_context->space_start_condity, depth);
  fo_object_debug_dump (fo_context->span, depth);
  fo_object_debug_dump (fo_context->src, depth);
  fo_object_debug_dump (fo_context->start_indent, depth);
  fo_object_debug_dump (fo_context->table_layout, depth);
  fo_object_debug_dump (fo_context->text_align, depth);
  fo_object_debug_dump (fo_context->text_indent, depth);
  fo_object_debug_dump (fo_context->unicode_bidi, depth);
  fo_object_debug_dump (fo_context->white_space_collapse, depth);
  fo_object_debug_dump (fo_context->white_space_treatment, depth);
  fo_object_debug_dump (fo_context->widows, depth);
  fo_object_debug_dump (fo_context->width, depth);
  fo_object_debug_dump (fo_context->wrap_option, depth);
  fo_object_debug_dump (fo_context->writing_mode, depth);
}
