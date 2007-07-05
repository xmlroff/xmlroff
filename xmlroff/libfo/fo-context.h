/* Fo
 * fo-context.h: Context formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CONTEXT_H__
#define __FO_CONTEXT_H__

typedef struct _FoContext      FoContext;
typedef struct _FoContextClass FoContextClass;

#include <libfo/fo-utils.h>
#include <libfo/fo-object.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

#define FO_TYPE_CONTEXT              (fo_context_get_type ())
#define FO_CONTEXT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_CONTEXT, FoContext))
#define FO_CONTEXT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_CONTEXT, FoContextClass))
#define FO_IS_CONTEXT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_CONTEXT))
#define FO_IS_CONTEXT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_CONTEXT))
#define FO_CONTEXT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_CONTEXT, FoContextClass))


GType       fo_context_get_type      (void) G_GNUC_CONST;
FoContext * fo_context_new           (void);

void fo_context_initialize (FoContext *context);
void fo_context_merge (FoContext *primary,
		       FoContext *secondary);
void fo_context_update_from_slist (FoContext *context,
				   GSList *property_list);
void fo_context_debug_dump_properties (FoContext *fo_context,
                                       gint       depth);

FoProperty * fo_context_get_alignment_adjust (FoContext  *fo_context);
void         fo_context_set_alignment_adjust (FoContext  *fo_context,
                                              FoProperty *new_alignment_adjust);
FoProperty * fo_context_get_alignment_baseline (FoContext  *fo_context);
void         fo_context_set_alignment_baseline (FoContext  *fo_context,
                                                FoProperty *new_alignment_baseline);
FoProperty * fo_context_get_background_color (FoContext  *fo_context);
void         fo_context_set_background_color (FoContext  *fo_context,
                                              FoProperty *new_background_color);
FoProperty * fo_context_get_background_image (FoContext  *fo_context);
void         fo_context_set_background_image (FoContext  *fo_context,
                                              FoProperty *new_background_image);
FoProperty * fo_context_get_baseline_shift (FoContext  *fo_context);
void         fo_context_set_baseline_shift (FoContext  *fo_context,
                                            FoProperty *new_baseline_shift);
FoProperty * fo_context_get_block_progression_dimension (FoContext  *fo_context);
void         fo_context_set_block_progression_dimension (FoContext  *fo_context,
                                                         FoProperty *new_block_progression_dimension);
FoProperty * fo_context_get_block_progression_dimension_minimum (FoContext  *fo_context);
void         fo_context_set_block_progression_dimension_minimum (FoContext  *fo_context,
                                                                 FoProperty *new_block_progression_dimension_minimum);
FoProperty * fo_context_get_block_progression_dimension_optimum (FoContext  *fo_context);
void         fo_context_set_block_progression_dimension_optimum (FoContext  *fo_context,
                                                                 FoProperty *new_block_progression_dimension_optimum);
FoProperty * fo_context_get_block_progression_dimension_maximum (FoContext  *fo_context);
void         fo_context_set_block_progression_dimension_maximum (FoContext  *fo_context,
                                                                 FoProperty *new_block_progression_dimension_maximum);
FoProperty * fo_context_get_border (FoContext  *fo_context);
void         fo_context_set_border (FoContext  *fo_context,
                                    FoProperty *new_border);
FoProperty * fo_context_get_border_after_color (FoContext  *fo_context);
void         fo_context_set_border_after_color (FoContext  *fo_context,
                                                FoProperty *new_border_after_color);
FoProperty * fo_context_get_border_after_precedence (FoContext  *fo_context);
void         fo_context_set_border_after_precedence (FoContext  *fo_context,
                                                     FoProperty *new_border_after_precedence);
FoProperty * fo_context_get_border_after_style (FoContext  *fo_context);
void         fo_context_set_border_after_style (FoContext  *fo_context,
                                                FoProperty *new_border_after_style);
FoProperty * fo_context_get_border_after_width (FoContext  *fo_context);
void         fo_context_set_border_after_width (FoContext  *fo_context,
                                                FoProperty *new_border_after_width);
FoProperty * fo_context_get_border_before_color (FoContext  *fo_context);
void         fo_context_set_border_before_color (FoContext  *fo_context,
                                                 FoProperty *new_border_before_color);
FoProperty * fo_context_get_border_before_precedence (FoContext  *fo_context);
void         fo_context_set_border_before_precedence (FoContext  *fo_context,
                                                      FoProperty *new_border_before_precedence);
FoProperty * fo_context_get_border_before_style (FoContext  *fo_context);
void         fo_context_set_border_before_style (FoContext  *fo_context,
                                                 FoProperty *new_border_before_style);
FoProperty * fo_context_get_border_before_width (FoContext  *fo_context);
void         fo_context_set_border_before_width (FoContext  *fo_context,
                                                 FoProperty *new_border_before_width);
FoProperty * fo_context_get_border_bottom (FoContext  *fo_context);
void         fo_context_set_border_bottom (FoContext  *fo_context,
                                           FoProperty *new_border_bottom);
FoProperty * fo_context_get_border_bottom_color (FoContext  *fo_context);
void         fo_context_set_border_bottom_color (FoContext  *fo_context,
                                                 FoProperty *new_border_bottom_color);
FoProperty * fo_context_get_border_bottom_style (FoContext  *fo_context);
void         fo_context_set_border_bottom_style (FoContext  *fo_context,
                                                 FoProperty *new_border_bottom_style);
FoProperty * fo_context_get_border_bottom_width (FoContext  *fo_context);
void         fo_context_set_border_bottom_width (FoContext  *fo_context,
                                                 FoProperty *new_border_bottom_width);
FoProperty * fo_context_get_border_collapse (FoContext  *fo_context);
void         fo_context_set_border_collapse (FoContext  *fo_context,
                                             FoProperty *new_border_collapse);
FoProperty * fo_context_get_border_color (FoContext  *fo_context);
void         fo_context_set_border_color (FoContext  *fo_context,
                                          FoProperty *new_border_color);
FoProperty * fo_context_get_border_end_color (FoContext  *fo_context);
void         fo_context_set_border_end_color (FoContext  *fo_context,
                                              FoProperty *new_border_end_color);
FoProperty * fo_context_get_border_end_precedence (FoContext  *fo_context);
void         fo_context_set_border_end_precedence (FoContext  *fo_context,
                                                   FoProperty *new_border_end_precedence);
FoProperty * fo_context_get_border_end_style (FoContext  *fo_context);
void         fo_context_set_border_end_style (FoContext  *fo_context,
                                              FoProperty *new_border_end_style);
FoProperty * fo_context_get_border_end_width (FoContext  *fo_context);
void         fo_context_set_border_end_width (FoContext  *fo_context,
                                              FoProperty *new_border_end_width);
FoProperty * fo_context_get_border_left (FoContext  *fo_context);
void         fo_context_set_border_left (FoContext  *fo_context,
                                         FoProperty *new_border_left);
FoProperty * fo_context_get_border_left_color (FoContext  *fo_context);
void         fo_context_set_border_left_color (FoContext  *fo_context,
                                               FoProperty *new_border_left_color);
FoProperty * fo_context_get_border_left_style (FoContext  *fo_context);
void         fo_context_set_border_left_style (FoContext  *fo_context,
                                               FoProperty *new_border_left_style);
FoProperty * fo_context_get_border_left_width (FoContext  *fo_context);
void         fo_context_set_border_left_width (FoContext  *fo_context,
                                               FoProperty *new_border_left_width);
FoProperty * fo_context_get_border_right (FoContext  *fo_context);
void         fo_context_set_border_right (FoContext  *fo_context,
                                          FoProperty *new_border_right);
FoProperty * fo_context_get_border_right_color (FoContext  *fo_context);
void         fo_context_set_border_right_color (FoContext  *fo_context,
                                                FoProperty *new_border_right_color);
FoProperty * fo_context_get_border_right_style (FoContext  *fo_context);
void         fo_context_set_border_right_style (FoContext  *fo_context,
                                                FoProperty *new_border_right_style);
FoProperty * fo_context_get_border_right_width (FoContext  *fo_context);
void         fo_context_set_border_right_width (FoContext  *fo_context,
                                                FoProperty *new_border_right_width);
FoProperty * fo_context_get_border_separation (FoContext  *fo_context);
void         fo_context_set_border_separation (FoContext  *fo_context,
                                               FoProperty *new_border_separation);
FoProperty * fo_context_get_border_start_color (FoContext  *fo_context);
void         fo_context_set_border_start_color (FoContext  *fo_context,
                                                FoProperty *new_border_start_color);
FoProperty * fo_context_get_border_start_precedence (FoContext  *fo_context);
void         fo_context_set_border_start_precedence (FoContext  *fo_context,
                                                     FoProperty *new_border_start_precedence);
FoProperty * fo_context_get_border_start_style (FoContext  *fo_context);
void         fo_context_set_border_start_style (FoContext  *fo_context,
                                                FoProperty *new_border_start_style);
FoProperty * fo_context_get_border_start_width (FoContext  *fo_context);
void         fo_context_set_border_start_width (FoContext  *fo_context,
                                                FoProperty *new_border_start_width);
FoProperty * fo_context_get_border_style (FoContext  *fo_context);
void         fo_context_set_border_style (FoContext  *fo_context,
                                          FoProperty *new_border_style);
FoProperty * fo_context_get_border_top (FoContext  *fo_context);
void         fo_context_set_border_top (FoContext  *fo_context,
                                        FoProperty *new_border_top);
FoProperty * fo_context_get_border_top_color (FoContext  *fo_context);
void         fo_context_set_border_top_color (FoContext  *fo_context,
                                              FoProperty *new_border_top_color);
FoProperty * fo_context_get_border_top_style (FoContext  *fo_context);
void         fo_context_set_border_top_style (FoContext  *fo_context,
                                              FoProperty *new_border_top_style);
FoProperty * fo_context_get_border_top_width (FoContext  *fo_context);
void         fo_context_set_border_top_width (FoContext  *fo_context,
                                              FoProperty *new_border_top_width);
FoProperty * fo_context_get_border_width (FoContext  *fo_context);
void         fo_context_set_border_width (FoContext  *fo_context,
                                          FoProperty *new_border_width);
FoProperty * fo_context_get_break_after (FoContext  *fo_context);
void         fo_context_set_break_after (FoContext  *fo_context,
                                         FoProperty *new_break_after);
FoProperty * fo_context_get_break_before (FoContext  *fo_context);
void         fo_context_set_break_before (FoContext  *fo_context,
                                          FoProperty *new_break_before);
FoProperty * fo_context_get_character (FoContext  *fo_context);
void         fo_context_set_character (FoContext  *fo_context,
                                       FoProperty *new_character);
FoProperty * fo_context_get_clip (FoContext  *fo_context);
void         fo_context_set_clip (FoContext  *fo_context,
                                  FoProperty *new_clip);
FoProperty * fo_context_get_color (FoContext  *fo_context);
void         fo_context_set_color (FoContext  *fo_context,
                                   FoProperty *new_color);
FoProperty * fo_context_get_column_number (FoContext  *fo_context);
void         fo_context_set_column_number (FoContext  *fo_context,
                                           FoProperty *new_column_number);
FoProperty * fo_context_get_column_width (FoContext  *fo_context);
void         fo_context_set_column_width (FoContext  *fo_context,
                                          FoProperty *new_column_width);
FoProperty * fo_context_get_content_height (FoContext  *fo_context);
void         fo_context_set_content_height (FoContext  *fo_context,
                                            FoProperty *new_content_height);
FoProperty * fo_context_get_content_type (FoContext  *fo_context);
void         fo_context_set_content_type (FoContext  *fo_context,
                                          FoProperty *new_content_type);
FoProperty * fo_context_get_content_width (FoContext  *fo_context);
void         fo_context_set_content_width (FoContext  *fo_context,
                                           FoProperty *new_content_width);
FoProperty * fo_context_get_direction (FoContext  *fo_context);
void         fo_context_set_direction (FoContext  *fo_context,
                                       FoProperty *new_direction);
FoProperty * fo_context_get_display_align (FoContext  *fo_context);
void         fo_context_set_display_align (FoContext  *fo_context,
                                           FoProperty *new_display_align);
FoProperty * fo_context_get_dominant_baseline (FoContext  *fo_context);
void         fo_context_set_dominant_baseline (FoContext  *fo_context,
                                               FoProperty *new_dominant_baseline);
FoProperty * fo_context_get_end_indent (FoContext  *fo_context);
void         fo_context_set_end_indent (FoContext  *fo_context,
                                        FoProperty *new_end_indent);
FoProperty * fo_context_get_extent (FoContext  *fo_context);
void         fo_context_set_extent (FoContext  *fo_context,
                                    FoProperty *new_extent);
FoProperty * fo_context_get_flow_name (FoContext  *fo_context);
void         fo_context_set_flow_name (FoContext  *fo_context,
                                       FoProperty *new_flow_name);
FoProperty * fo_context_get_font_family (FoContext  *fo_context);
void         fo_context_set_font_family (FoContext  *fo_context,
                                         FoProperty *new_font_family);
FoProperty * fo_context_get_font_size (FoContext  *fo_context);
void         fo_context_set_font_size (FoContext  *fo_context,
                                       FoProperty *new_font_size);
FoProperty * fo_context_get_font_stretch (FoContext  *fo_context);
void         fo_context_set_font_stretch (FoContext  *fo_context,
                                          FoProperty *new_font_stretch);
FoProperty * fo_context_get_font_style (FoContext  *fo_context);
void         fo_context_set_font_style (FoContext  *fo_context,
                                        FoProperty *new_font_style);
FoProperty * fo_context_get_font_variant (FoContext  *fo_context);
void         fo_context_set_font_variant (FoContext  *fo_context,
                                          FoProperty *new_font_variant);
FoProperty * fo_context_get_font_weight (FoContext  *fo_context);
void         fo_context_set_font_weight (FoContext  *fo_context,
                                         FoProperty *new_font_weight);
FoProperty * fo_context_get_format (FoContext  *fo_context);
void         fo_context_set_format (FoContext  *fo_context,
                                    FoProperty *new_format);
FoProperty * fo_context_get_grouping_separator (FoContext  *fo_context);
void         fo_context_set_grouping_separator (FoContext  *fo_context,
                                                FoProperty *new_grouping_separator);
FoProperty * fo_context_get_grouping_size (FoContext  *fo_context);
void         fo_context_set_grouping_size (FoContext  *fo_context,
                                           FoProperty *new_grouping_size);
FoProperty * fo_context_get_height (FoContext  *fo_context);
void         fo_context_set_height (FoContext  *fo_context,
                                    FoProperty *new_height);
FoProperty * fo_context_get_id (FoContext  *fo_context);
void         fo_context_set_id (FoContext  *fo_context,
                                FoProperty *new_id);
FoProperty * fo_context_get_inline_progression_dimension (FoContext  *fo_context);
void         fo_context_set_inline_progression_dimension (FoContext  *fo_context,
                                                          FoProperty *new_inline_progression_dimension);
FoProperty * fo_context_get_inline_progression_dimension_minimum (FoContext  *fo_context);
void         fo_context_set_inline_progression_dimension_minimum (FoContext  *fo_context,
                                                                  FoProperty *new_inline_progression_dimension_minimum);
FoProperty * fo_context_get_inline_progression_dimension_optimum (FoContext  *fo_context);
void         fo_context_set_inline_progression_dimension_optimum (FoContext  *fo_context,
                                                                  FoProperty *new_inline_progression_dimension_optimum);
FoProperty * fo_context_get_inline_progression_dimension_maximum (FoContext  *fo_context);
void         fo_context_set_inline_progression_dimension_maximum (FoContext  *fo_context,
                                                                  FoProperty *new_inline_progression_dimension_maximum);
FoProperty * fo_context_get_keep_together (FoContext  *fo_context);
void         fo_context_set_keep_together (FoContext  *fo_context,
                                           FoProperty *new_keep_together);
FoProperty * fo_context_get_keep_together_within_column (FoContext  *fo_context);
void         fo_context_set_keep_together_within_column (FoContext  *fo_context,
                                                         FoProperty *new_keep_together_within_column);
FoProperty * fo_context_get_keep_together_within_line (FoContext  *fo_context);
void         fo_context_set_keep_together_within_line (FoContext  *fo_context,
                                                       FoProperty *new_keep_together_within_line);
FoProperty * fo_context_get_keep_together_within_page (FoContext  *fo_context);
void         fo_context_set_keep_together_within_page (FoContext  *fo_context,
                                                       FoProperty *new_keep_together_within_page);
FoProperty * fo_context_get_keep_with_next (FoContext  *fo_context);
void         fo_context_set_keep_with_next (FoContext  *fo_context,
                                            FoProperty *new_keep_with_next);
FoProperty * fo_context_get_keep_with_next_within_column (FoContext  *fo_context);
void         fo_context_set_keep_with_next_within_column (FoContext  *fo_context,
                                                          FoProperty *new_keep_with_next_within_column);
FoProperty * fo_context_get_keep_with_next_within_line (FoContext  *fo_context);
void         fo_context_set_keep_with_next_within_line (FoContext  *fo_context,
                                                        FoProperty *new_keep_with_next_within_line);
FoProperty * fo_context_get_keep_with_next_within_page (FoContext  *fo_context);
void         fo_context_set_keep_with_next_within_page (FoContext  *fo_context,
                                                        FoProperty *new_keep_with_next_within_page);
FoProperty * fo_context_get_keep_with_previous (FoContext  *fo_context);
void         fo_context_set_keep_with_previous (FoContext  *fo_context,
                                                FoProperty *new_keep_with_previous);
FoProperty * fo_context_get_keep_with_previous_within_column (FoContext  *fo_context);
void         fo_context_set_keep_with_previous_within_column (FoContext  *fo_context,
                                                              FoProperty *new_keep_with_previous_within_column);
FoProperty * fo_context_get_keep_with_previous_within_line (FoContext  *fo_context);
void         fo_context_set_keep_with_previous_within_line (FoContext  *fo_context,
                                                            FoProperty *new_keep_with_previous_within_line);
FoProperty * fo_context_get_keep_with_previous_within_page (FoContext  *fo_context);
void         fo_context_set_keep_with_previous_within_page (FoContext  *fo_context,
                                                            FoProperty *new_keep_with_previous_within_page);
FoProperty * fo_context_get_letter_value (FoContext  *fo_context);
void         fo_context_set_letter_value (FoContext  *fo_context,
                                          FoProperty *new_letter_value);
FoProperty * fo_context_get_line_height (FoContext  *fo_context);
void         fo_context_set_line_height (FoContext  *fo_context,
                                         FoProperty *new_line_height);
FoProperty * fo_context_get_line_stacking_strategy (FoContext  *fo_context);
void         fo_context_set_line_stacking_strategy (FoContext  *fo_context,
                                                    FoProperty *new_line_stacking_strategy);
FoProperty * fo_context_get_linefeed_treatment (FoContext  *fo_context);
void         fo_context_set_linefeed_treatment (FoContext  *fo_context,
                                                FoProperty *new_linefeed_treatment);
FoProperty * fo_context_get_margin (FoContext  *fo_context);
void         fo_context_set_margin (FoContext  *fo_context,
                                    FoProperty *new_margin);
FoProperty * fo_context_get_margin_bottom (FoContext  *fo_context);
void         fo_context_set_margin_bottom (FoContext  *fo_context,
                                           FoProperty *new_margin_bottom);
FoProperty * fo_context_get_margin_left (FoContext  *fo_context);
void         fo_context_set_margin_left (FoContext  *fo_context,
                                         FoProperty *new_margin_left);
FoProperty * fo_context_get_margin_right (FoContext  *fo_context);
void         fo_context_set_margin_right (FoContext  *fo_context,
                                          FoProperty *new_margin_right);
FoProperty * fo_context_get_margin_top (FoContext  *fo_context);
void         fo_context_set_margin_top (FoContext  *fo_context,
                                        FoProperty *new_margin_top);
FoProperty * fo_context_get_master_name (FoContext  *fo_context);
void         fo_context_set_master_name (FoContext  *fo_context,
                                         FoProperty *new_master_name);
FoProperty * fo_context_get_master_reference (FoContext  *fo_context);
void         fo_context_set_master_reference (FoContext  *fo_context,
                                              FoProperty *new_master_reference);
FoProperty * fo_context_get_media_usage (FoContext  *fo_context);
void         fo_context_set_media_usage (FoContext  *fo_context,
                                         FoProperty *new_media_usage);
FoProperty * fo_context_get_number_columns_repeated (FoContext  *fo_context);
void         fo_context_set_number_columns_repeated (FoContext  *fo_context,
                                                     FoProperty *new_number_columns_repeated);
FoProperty * fo_context_get_number_columns_spanned (FoContext  *fo_context);
void         fo_context_set_number_columns_spanned (FoContext  *fo_context,
                                                    FoProperty *new_number_columns_spanned);
FoProperty * fo_context_get_number_rows_spanned (FoContext  *fo_context);
void         fo_context_set_number_rows_spanned (FoContext  *fo_context,
                                                 FoProperty *new_number_rows_spanned);
FoProperty * fo_context_get_orphans (FoContext  *fo_context);
void         fo_context_set_orphans (FoContext  *fo_context,
                                     FoProperty *new_orphans);
FoProperty * fo_context_get_overflow (FoContext  *fo_context);
void         fo_context_set_overflow (FoContext  *fo_context,
                                      FoProperty *new_overflow);
FoProperty * fo_context_get_padding (FoContext  *fo_context);
void         fo_context_set_padding (FoContext  *fo_context,
                                     FoProperty *new_padding);
FoProperty * fo_context_get_padding_after (FoContext  *fo_context);
void         fo_context_set_padding_after (FoContext  *fo_context,
                                           FoProperty *new_padding_after);
FoProperty * fo_context_get_padding_after_length (FoContext  *fo_context);
void         fo_context_set_padding_after_length (FoContext  *fo_context,
                                                  FoProperty *new_padding_after_length);
FoProperty * fo_context_get_padding_after_condity (FoContext  *fo_context);
void         fo_context_set_padding_after_condity (FoContext  *fo_context,
                                                   FoProperty *new_padding_after_condity);
FoProperty * fo_context_get_padding_before (FoContext  *fo_context);
void         fo_context_set_padding_before (FoContext  *fo_context,
                                            FoProperty *new_padding_before);
FoProperty * fo_context_get_padding_before_length (FoContext  *fo_context);
void         fo_context_set_padding_before_length (FoContext  *fo_context,
                                                   FoProperty *new_padding_before_length);
FoProperty * fo_context_get_padding_before_condity (FoContext  *fo_context);
void         fo_context_set_padding_before_condity (FoContext  *fo_context,
                                                    FoProperty *new_padding_before_condity);
FoProperty * fo_context_get_padding_bottom (FoContext  *fo_context);
void         fo_context_set_padding_bottom (FoContext  *fo_context,
                                            FoProperty *new_padding_bottom);
FoProperty * fo_context_get_padding_end (FoContext  *fo_context);
void         fo_context_set_padding_end (FoContext  *fo_context,
                                         FoProperty *new_padding_end);
FoProperty * fo_context_get_padding_end_length (FoContext  *fo_context);
void         fo_context_set_padding_end_length (FoContext  *fo_context,
                                                FoProperty *new_padding_end_length);
FoProperty * fo_context_get_padding_end_condity (FoContext  *fo_context);
void         fo_context_set_padding_end_condity (FoContext  *fo_context,
                                                 FoProperty *new_padding_end_condity);
FoProperty * fo_context_get_padding_left (FoContext  *fo_context);
void         fo_context_set_padding_left (FoContext  *fo_context,
                                          FoProperty *new_padding_left);
FoProperty * fo_context_get_padding_right (FoContext  *fo_context);
void         fo_context_set_padding_right (FoContext  *fo_context,
                                           FoProperty *new_padding_right);
FoProperty * fo_context_get_padding_start (FoContext  *fo_context);
void         fo_context_set_padding_start (FoContext  *fo_context,
                                           FoProperty *new_padding_start);
FoProperty * fo_context_get_padding_start_length (FoContext  *fo_context);
void         fo_context_set_padding_start_length (FoContext  *fo_context,
                                                  FoProperty *new_padding_start_length);
FoProperty * fo_context_get_padding_start_condity (FoContext  *fo_context);
void         fo_context_set_padding_start_condity (FoContext  *fo_context,
                                                   FoProperty *new_padding_start_condity);
FoProperty * fo_context_get_padding_top (FoContext  *fo_context);
void         fo_context_set_padding_top (FoContext  *fo_context,
                                         FoProperty *new_padding_top);
FoProperty * fo_context_get_page_height (FoContext  *fo_context);
void         fo_context_set_page_height (FoContext  *fo_context,
                                         FoProperty *new_page_height);
FoProperty * fo_context_get_page_width (FoContext  *fo_context);
void         fo_context_set_page_width (FoContext  *fo_context,
                                        FoProperty *new_page_width);
FoProperty * fo_context_get_provisional_distance_between_starts (FoContext  *fo_context);
void         fo_context_set_provisional_distance_between_starts (FoContext  *fo_context,
                                                                 FoProperty *new_provisional_distance_between_starts);
FoProperty * fo_context_get_provisional_label_separation (FoContext  *fo_context);
void         fo_context_set_provisional_label_separation (FoContext  *fo_context,
                                                          FoProperty *new_provisional_label_separation);
FoProperty * fo_context_get_ref_id (FoContext  *fo_context);
void         fo_context_set_ref_id (FoContext  *fo_context,
                                    FoProperty *new_ref_id);
FoProperty * fo_context_get_region_name (FoContext  *fo_context);
void         fo_context_set_region_name (FoContext  *fo_context,
                                         FoProperty *new_region_name);
FoProperty * fo_context_get_role (FoContext  *fo_context);
void         fo_context_set_role (FoContext  *fo_context,
                                  FoProperty *new_role);
FoProperty * fo_context_get_scaling (FoContext  *fo_context);
void         fo_context_set_scaling (FoContext  *fo_context,
                                     FoProperty *new_scaling);
FoProperty * fo_context_get_scaling_method (FoContext  *fo_context);
void         fo_context_set_scaling_method (FoContext  *fo_context,
                                            FoProperty *new_scaling_method);
FoProperty * fo_context_get_score_spaces (FoContext  *fo_context);
void         fo_context_set_score_spaces (FoContext  *fo_context,
                                          FoProperty *new_score_spaces);
FoProperty * fo_context_get_source_document (FoContext  *fo_context);
void         fo_context_set_source_document (FoContext  *fo_context,
                                             FoProperty *new_source_document);
FoProperty * fo_context_get_space_after (FoContext  *fo_context);
void         fo_context_set_space_after (FoContext  *fo_context,
                                         FoProperty *new_space_after);
void         fo_context_set_space_after_minimum (FoContext  *fo_context,
                                                 FoProperty *new_space_after_minimum);
void         fo_context_set_space_after_optimum (FoContext  *fo_context,
                                                 FoProperty *new_space_after_optimum);
void         fo_context_set_space_after_maximum (FoContext  *fo_context,
                                                 FoProperty *new_space_after_maximum);
void         fo_context_set_space_after_precedence (FoContext  *fo_context,
                                                    FoProperty *new_space_after_precedence);
void         fo_context_set_space_after_condity (FoContext  *fo_context,
                                                 FoProperty *new_space_after_condity);
FoProperty * fo_context_get_space_before (FoContext  *fo_context);
void         fo_context_set_space_before (FoContext  *fo_context,
                                          FoProperty *new_space_before);
void         fo_context_set_space_before_minimum (FoContext  *fo_context,
                                                  FoProperty *new_space_before_minimum);
void         fo_context_set_space_before_optimum (FoContext  *fo_context,
                                                  FoProperty *new_space_before_optimum);
void         fo_context_set_space_before_maximum (FoContext  *fo_context,
                                                  FoProperty *new_space_before_maximum);
void         fo_context_set_space_before_precedence (FoContext  *fo_context,
                                                     FoProperty *new_space_before_precedence);
void         fo_context_set_space_before_condity (FoContext  *fo_context,
                                                  FoProperty *new_space_before_condity);
FoProperty * fo_context_get_space_end (FoContext  *fo_context);
void         fo_context_set_space_end (FoContext  *fo_context,
                                       FoProperty *new_space_end);
void         fo_context_set_space_end_minimum (FoContext  *fo_context,
                                               FoProperty *new_space_end_minimum);
void         fo_context_set_space_end_optimum (FoContext  *fo_context,
                                               FoProperty *new_space_end_optimum);
void         fo_context_set_space_end_maximum (FoContext  *fo_context,
                                               FoProperty *new_space_end_maximum);
void         fo_context_set_space_end_precedence (FoContext  *fo_context,
                                                  FoProperty *new_space_end_precedence);
void         fo_context_set_space_end_condity (FoContext  *fo_context,
                                               FoProperty *new_space_end_condity);
FoProperty * fo_context_get_space_start (FoContext  *fo_context);
void         fo_context_set_space_start (FoContext  *fo_context,
                                         FoProperty *new_space_start);
void         fo_context_set_space_start_minimum (FoContext  *fo_context,
                                                 FoProperty *new_space_start_minimum);
void         fo_context_set_space_start_optimum (FoContext  *fo_context,
                                                 FoProperty *new_space_start_optimum);
void         fo_context_set_space_start_maximum (FoContext  *fo_context,
                                                 FoProperty *new_space_start_maximum);
void         fo_context_set_space_start_precedence (FoContext  *fo_context,
                                                    FoProperty *new_space_start_precedence);
void         fo_context_set_space_start_condity (FoContext  *fo_context,
                                                 FoProperty *new_space_start_condity);
FoProperty * fo_context_get_span (FoContext  *fo_context);
void         fo_context_set_span (FoContext  *fo_context,
                                  FoProperty *new_span);
FoProperty * fo_context_get_src (FoContext  *fo_context);
void         fo_context_set_src (FoContext  *fo_context,
                                 FoProperty *new_src);
FoProperty * fo_context_get_start_indent (FoContext  *fo_context);
void         fo_context_set_start_indent (FoContext  *fo_context,
                                          FoProperty *new_start_indent);
FoProperty * fo_context_get_table_layout (FoContext  *fo_context);
void         fo_context_set_table_layout (FoContext  *fo_context,
                                          FoProperty *new_table_layout);
FoProperty * fo_context_get_text_align (FoContext  *fo_context);
void         fo_context_set_text_align (FoContext  *fo_context,
                                        FoProperty *new_text_align);
FoProperty * fo_context_get_text_indent (FoContext  *fo_context);
void         fo_context_set_text_indent (FoContext  *fo_context,
                                         FoProperty *new_text_indent);
FoProperty * fo_context_get_unicode_bidi (FoContext  *fo_context);
void         fo_context_set_unicode_bidi (FoContext  *fo_context,
                                          FoProperty *new_unicode_bidi);
FoProperty * fo_context_get_white_space_collapse (FoContext  *fo_context);
void         fo_context_set_white_space_collapse (FoContext  *fo_context,
                                                  FoProperty *new_white_space_collapse);
FoProperty * fo_context_get_white_space_treatment (FoContext  *fo_context);
void         fo_context_set_white_space_treatment (FoContext  *fo_context,
                                                   FoProperty *new_white_space_treatment);
FoProperty * fo_context_get_widows (FoContext  *fo_context);
void         fo_context_set_widows (FoContext  *fo_context,
                                    FoProperty *new_widows);
FoProperty * fo_context_get_width (FoContext  *fo_context);
void         fo_context_set_width (FoContext  *fo_context,
                                   FoProperty *new_width);
FoProperty * fo_context_get_wrap_option (FoContext  *fo_context);
void         fo_context_set_wrap_option (FoContext  *fo_context,
                                         FoProperty *new_wrap_option);
FoProperty * fo_context_get_writing_mode (FoContext  *fo_context);
void         fo_context_set_writing_mode (FoContext  *fo_context,
                                          FoProperty *new_writing_mode);


G_END_DECLS

#endif /* __FO_CONTEXT_H__ */
