/* Fo
 * fo-property-eval.c: Functions that relate property attributes to the
 *                     procedures for evaluating them.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#include "fo-property-eval.h"
#include "fo-all-property.h"

/**
 * fo_property_eval_init_hash:
 * @hash: Null #GHashTable pointer
 * 
 * Initialises @hash and inserts 'get_type' function for
 * every property.
 * 
 * Return value: Initialised #GHashTable
 **/
GHashTable *
fo_property_eval_init_hash (GHashTable *hash)
{

  g_return_val_if_fail (hash == NULL, NULL);

  hash = g_hash_table_new (g_str_hash, g_str_equal);

  g_hash_table_insert (hash, "alignment-adjust", &fo_property_alignment_adjust_get_type);
  g_hash_table_insert (hash, "alignment-baseline", &fo_property_alignment_baseline_get_type);
  g_hash_table_insert (hash, "background-color", &fo_property_background_color_get_type);
  g_hash_table_insert (hash, "background-image", &fo_property_background_image_get_type);
  g_hash_table_insert (hash, "baseline-shift", &fo_property_baseline_shift_get_type);
  g_hash_table_insert (hash, "block-progression-dimension", &fo_property_block_progression_dimension_get_type);
  g_hash_table_insert (hash, "block-progression-dimension.minimum", &fo_property_block_progression_dimension_minimum_get_type);
  g_hash_table_insert (hash, "block-progression-dimension.optimum", &fo_property_block_progression_dimension_optimum_get_type);
  g_hash_table_insert (hash, "block-progression-dimension.maximum", &fo_property_block_progression_dimension_maximum_get_type);
  g_hash_table_insert (hash, "border", &fo_property_border_get_type);
  g_hash_table_insert (hash, "border-after-color", &fo_property_border_after_color_get_type);
  g_hash_table_insert (hash, "border-after-precedence", &fo_property_border_after_precedence_get_type);
  g_hash_table_insert (hash, "border-after-style", &fo_property_border_after_style_get_type);
  g_hash_table_insert (hash, "border-after-width", &fo_property_border_after_width_get_type);
  g_hash_table_insert (hash, "border-before-color", &fo_property_border_before_color_get_type);
  g_hash_table_insert (hash, "border-before-precedence", &fo_property_border_before_precedence_get_type);
  g_hash_table_insert (hash, "border-before-style", &fo_property_border_before_style_get_type);
  g_hash_table_insert (hash, "border-before-width", &fo_property_border_before_width_get_type);
  g_hash_table_insert (hash, "border-bottom", &fo_property_border_bottom_get_type);
  g_hash_table_insert (hash, "border-bottom-color", &fo_property_border_bottom_color_get_type);
  g_hash_table_insert (hash, "border-bottom-style", &fo_property_border_bottom_style_get_type);
  g_hash_table_insert (hash, "border-bottom-width", &fo_property_border_bottom_width_get_type);
  g_hash_table_insert (hash, "border-collapse", &fo_property_border_collapse_get_type);
  g_hash_table_insert (hash, "border-color", &fo_property_border_color_get_type);
  g_hash_table_insert (hash, "border-end-color", &fo_property_border_end_color_get_type);
  g_hash_table_insert (hash, "border-end-precedence", &fo_property_border_end_precedence_get_type);
  g_hash_table_insert (hash, "border-end-style", &fo_property_border_end_style_get_type);
  g_hash_table_insert (hash, "border-end-width", &fo_property_border_end_width_get_type);
  g_hash_table_insert (hash, "border-left", &fo_property_border_left_get_type);
  g_hash_table_insert (hash, "border-left-color", &fo_property_border_left_color_get_type);
  g_hash_table_insert (hash, "border-left-style", &fo_property_border_left_style_get_type);
  g_hash_table_insert (hash, "border-left-width", &fo_property_border_left_width_get_type);
  g_hash_table_insert (hash, "border-right", &fo_property_border_right_get_type);
  g_hash_table_insert (hash, "border-right-color", &fo_property_border_right_color_get_type);
  g_hash_table_insert (hash, "border-right-style", &fo_property_border_right_style_get_type);
  g_hash_table_insert (hash, "border-right-width", &fo_property_border_right_width_get_type);
  g_hash_table_insert (hash, "border-separation", &fo_property_border_separation_get_type);
  g_hash_table_insert (hash, "border-start-color", &fo_property_border_start_color_get_type);
  g_hash_table_insert (hash, "border-start-precedence", &fo_property_border_start_precedence_get_type);
  g_hash_table_insert (hash, "border-start-style", &fo_property_border_start_style_get_type);
  g_hash_table_insert (hash, "border-start-width", &fo_property_border_start_width_get_type);
  g_hash_table_insert (hash, "border-style", &fo_property_border_style_get_type);
  g_hash_table_insert (hash, "border-top", &fo_property_border_top_get_type);
  g_hash_table_insert (hash, "border-top-color", &fo_property_border_top_color_get_type);
  g_hash_table_insert (hash, "border-top-style", &fo_property_border_top_style_get_type);
  g_hash_table_insert (hash, "border-top-width", &fo_property_border_top_width_get_type);
  g_hash_table_insert (hash, "border-width", &fo_property_border_width_get_type);
  g_hash_table_insert (hash, "break-after", &fo_property_break_after_get_type);
  g_hash_table_insert (hash, "break-before", &fo_property_break_before_get_type);
  g_hash_table_insert (hash, "character", &fo_property_character_get_type);
  g_hash_table_insert (hash, "clip", &fo_property_clip_get_type);
  g_hash_table_insert (hash, "color", &fo_property_color_get_type);
  g_hash_table_insert (hash, "column-number", &fo_property_column_number_get_type);
  g_hash_table_insert (hash, "column-width", &fo_property_column_width_get_type);
  g_hash_table_insert (hash, "content-height", &fo_property_content_height_get_type);
  g_hash_table_insert (hash, "content-type", &fo_property_content_type_get_type);
  g_hash_table_insert (hash, "content-width", &fo_property_content_width_get_type);
  g_hash_table_insert (hash, "direction", &fo_property_direction_get_type);
  g_hash_table_insert (hash, "display-align", &fo_property_display_align_get_type);
  g_hash_table_insert (hash, "dominant-baseline", &fo_property_dominant_baseline_get_type);
  g_hash_table_insert (hash, "end-indent", &fo_property_end_indent_get_type);
  g_hash_table_insert (hash, "extent", &fo_property_extent_get_type);
  g_hash_table_insert (hash, "flow-name", &fo_property_flow_name_get_type);
  g_hash_table_insert (hash, "font-family", &fo_property_font_family_get_type);
  g_hash_table_insert (hash, "font-size", &fo_property_font_size_get_type);
  g_hash_table_insert (hash, "font-stretch", &fo_property_font_stretch_get_type);
  g_hash_table_insert (hash, "font-style", &fo_property_font_style_get_type);
  g_hash_table_insert (hash, "font-variant", &fo_property_font_variant_get_type);
  g_hash_table_insert (hash, "font-weight", &fo_property_font_weight_get_type);
  g_hash_table_insert (hash, "format", &fo_property_format_get_type);
  g_hash_table_insert (hash, "grouping-separator", &fo_property_grouping_separator_get_type);
  g_hash_table_insert (hash, "grouping-size", &fo_property_grouping_size_get_type);
  g_hash_table_insert (hash, "height", &fo_property_height_get_type);
  g_hash_table_insert (hash, "id", &fo_property_id_get_type);
  g_hash_table_insert (hash, "inline-progression-dimension", &fo_property_inline_progression_dimension_get_type);
  g_hash_table_insert (hash, "inline-progression-dimension.minimum", &fo_property_inline_progression_dimension_minimum_get_type);
  g_hash_table_insert (hash, "inline-progression-dimension.optimum", &fo_property_inline_progression_dimension_optimum_get_type);
  g_hash_table_insert (hash, "inline-progression-dimension.maximum", &fo_property_inline_progression_dimension_maximum_get_type);
  g_hash_table_insert (hash, "keep-together", &fo_property_keep_together_get_type);
  g_hash_table_insert (hash, "keep-together.within-column", &fo_property_keep_together_within_column_get_type);
  g_hash_table_insert (hash, "keep-together.within-line", &fo_property_keep_together_within_line_get_type);
  g_hash_table_insert (hash, "keep-together.within-page", &fo_property_keep_together_within_page_get_type);
  g_hash_table_insert (hash, "keep-with-next", &fo_property_keep_with_next_get_type);
  g_hash_table_insert (hash, "keep-with-next.within-column", &fo_property_keep_with_next_within_column_get_type);
  g_hash_table_insert (hash, "keep-with-next.within-line", &fo_property_keep_with_next_within_line_get_type);
  g_hash_table_insert (hash, "keep-with-next.within-page", &fo_property_keep_with_next_within_page_get_type);
  g_hash_table_insert (hash, "keep-with-previous", &fo_property_keep_with_previous_get_type);
  g_hash_table_insert (hash, "keep-with-previous.within-column", &fo_property_keep_with_previous_within_column_get_type);
  g_hash_table_insert (hash, "keep-with-previous.within-line", &fo_property_keep_with_previous_within_line_get_type);
  g_hash_table_insert (hash, "keep-with-previous.within-page", &fo_property_keep_with_previous_within_page_get_type);
  g_hash_table_insert (hash, "letter-value", &fo_property_letter_value_get_type);
  g_hash_table_insert (hash, "linefeed-treatment", &fo_property_linefeed_treatment_get_type);
  g_hash_table_insert (hash, "line-height", &fo_property_line_height_get_type);
  g_hash_table_insert (hash, "line-stacking-strategy", &fo_property_line_stacking_strategy_get_type);
  g_hash_table_insert (hash, "margin", &fo_property_margin_get_type);
  g_hash_table_insert (hash, "margin-bottom", &fo_property_margin_bottom_get_type);
  g_hash_table_insert (hash, "margin-left", &fo_property_margin_left_get_type);
  g_hash_table_insert (hash, "margin-right", &fo_property_margin_right_get_type);
  g_hash_table_insert (hash, "margin-top", &fo_property_margin_top_get_type);
  g_hash_table_insert (hash, "master-name", &fo_property_master_name_get_type);
  g_hash_table_insert (hash, "master-reference", &fo_property_master_reference_get_type);
  g_hash_table_insert (hash, "media-usage", &fo_property_media_usage_get_type);
  g_hash_table_insert (hash, "number-columns-repeated", &fo_property_number_columns_repeated_get_type);
  g_hash_table_insert (hash, "number-columns-spanned", &fo_property_number_columns_spanned_get_type);
  g_hash_table_insert (hash, "number-rows-spanned", &fo_property_number_rows_spanned_get_type);
  g_hash_table_insert (hash, "orphans", &fo_property_orphans_get_type);
  g_hash_table_insert (hash, "overflow", &fo_property_overflow_get_type);
  g_hash_table_insert (hash, "padding", &fo_property_padding_get_type);
  g_hash_table_insert (hash, "padding-after", &fo_property_padding_after_get_type);
  g_hash_table_insert (hash, "padding-after.length", &fo_property_padding_after_length_get_type);
  g_hash_table_insert (hash, "padding-after.conditionality", &fo_property_padding_after_condity_get_type);
  g_hash_table_insert (hash, "padding-before", &fo_property_padding_before_get_type);
  g_hash_table_insert (hash, "padding-before.length", &fo_property_padding_before_length_get_type);
  g_hash_table_insert (hash, "padding-before.conditionality", &fo_property_padding_before_condity_get_type);
  g_hash_table_insert (hash, "padding-bottom", &fo_property_padding_bottom_get_type);
  g_hash_table_insert (hash, "padding-end", &fo_property_padding_end_get_type);
  g_hash_table_insert (hash, "padding-end.length", &fo_property_padding_end_length_get_type);
  g_hash_table_insert (hash, "padding-end.conditionality", &fo_property_padding_end_condity_get_type);
  g_hash_table_insert (hash, "padding-left", &fo_property_padding_left_get_type);
  g_hash_table_insert (hash, "padding-right", &fo_property_padding_right_get_type);
  g_hash_table_insert (hash, "padding-start", &fo_property_padding_start_get_type);
  g_hash_table_insert (hash, "padding-start.length", &fo_property_padding_start_length_get_type);
  g_hash_table_insert (hash, "padding-start.conditionality", &fo_property_padding_start_condity_get_type);
  g_hash_table_insert (hash, "padding-top", &fo_property_padding_top_get_type);
  g_hash_table_insert (hash, "page-height", &fo_property_page_height_get_type);
  g_hash_table_insert (hash, "page-width", &fo_property_page_width_get_type);
  g_hash_table_insert (hash, "provisional-distance-between-starts", &fo_property_provisional_distance_between_starts_get_type);
  g_hash_table_insert (hash, "provisional-label-separation", &fo_property_provisional_label_separation_get_type);
  g_hash_table_insert (hash, "ref-id", &fo_property_ref_id_get_type);
  g_hash_table_insert (hash, "region-name", &fo_property_region_name_get_type);
  g_hash_table_insert (hash, "role", &fo_property_role_get_type);
  g_hash_table_insert (hash, "scaling", &fo_property_scaling_get_type);
  g_hash_table_insert (hash, "scaling-method", &fo_property_scaling_method_get_type);
  g_hash_table_insert (hash, "score-spaces", &fo_property_score_spaces_get_type);
  g_hash_table_insert (hash, "source-document", &fo_property_source_document_get_type);
  g_hash_table_insert (hash, "space-after", &fo_property_space_after_get_type);
  g_hash_table_insert (hash, "space-after.minimum", &fo_property_space_after_minimum_get_type);
  g_hash_table_insert (hash, "space-after.optimum", &fo_property_space_after_optimum_get_type);
  g_hash_table_insert (hash, "space-after.maximum", &fo_property_space_after_maximum_get_type);
  g_hash_table_insert (hash, "space-after.conditionality", &fo_property_space_after_condity_get_type);
  g_hash_table_insert (hash, "space-after.precedence", &fo_property_space_after_precedence_get_type);
  g_hash_table_insert (hash, "space-before", &fo_property_space_before_get_type);
  g_hash_table_insert (hash, "space-before.minimum", &fo_property_space_before_minimum_get_type);
  g_hash_table_insert (hash, "space-before.optimum", &fo_property_space_before_optimum_get_type);
  g_hash_table_insert (hash, "space-before.maximum", &fo_property_space_before_maximum_get_type);
  g_hash_table_insert (hash, "space-before.conditionality", &fo_property_space_before_condity_get_type);
  g_hash_table_insert (hash, "space-before.precedence", &fo_property_space_before_precedence_get_type);
  g_hash_table_insert (hash, "space-end", &fo_property_space_end_get_type);
  g_hash_table_insert (hash, "space-end.minimum", &fo_property_space_end_minimum_get_type);
  g_hash_table_insert (hash, "space-end.optimum", &fo_property_space_end_optimum_get_type);
  g_hash_table_insert (hash, "space-end.maximum", &fo_property_space_end_maximum_get_type);
  g_hash_table_insert (hash, "space-end.conditionality", &fo_property_space_end_condity_get_type);
  g_hash_table_insert (hash, "space-end.precedence", &fo_property_space_end_precedence_get_type);
  g_hash_table_insert (hash, "space-start", &fo_property_space_start_get_type);
  g_hash_table_insert (hash, "space-start.minimum", &fo_property_space_start_minimum_get_type);
  g_hash_table_insert (hash, "space-start.optimum", &fo_property_space_start_optimum_get_type);
  g_hash_table_insert (hash, "space-start.maximum", &fo_property_space_start_maximum_get_type);
  g_hash_table_insert (hash, "space-start.conditionality", &fo_property_space_start_condity_get_type);
  g_hash_table_insert (hash, "space-start.precedence", &fo_property_space_start_precedence_get_type);
  g_hash_table_insert (hash, "span", &fo_property_span_get_type);
  g_hash_table_insert (hash, "src", &fo_property_src_get_type);
  g_hash_table_insert (hash, "start-indent", &fo_property_start_indent_get_type);
  g_hash_table_insert (hash, "table-layout", &fo_property_table_layout_get_type);
  g_hash_table_insert (hash, "text-align", &fo_property_text_align_get_type);
  g_hash_table_insert (hash, "text-indent", &fo_property_text_indent_get_type);
  g_hash_table_insert (hash, "unicode-bidi", &fo_property_unicode_bidi_get_type);
  g_hash_table_insert (hash, "white-space-collapse", &fo_property_white_space_collapse_get_type);
  g_hash_table_insert (hash, "white-space-treatment", &fo_property_white_space_treatment_get_type);
  g_hash_table_insert (hash, "widows", &fo_property_widows_get_type);
  g_hash_table_insert (hash, "width", &fo_property_width_get_type);
  g_hash_table_insert (hash, "wrap-option", &fo_property_wrap_option_get_type);
  g_hash_table_insert (hash, "writing-mode", &fo_property_writing_mode_get_type);
  return hash;
}
