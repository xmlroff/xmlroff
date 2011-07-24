/* Fo
 * fo-context-private.h: Structures private to the FoContext formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CONTEXT_PRIVATE_H__
#define __FO_CONTEXT_PRIVATE_H__

#include "fo-object.h"
#include "property/fo-property.h"

G_BEGIN_DECLS

struct _FoContext
{
  FoObject parent_instance;

  FoProperty *alignment_adjust;
  FoProperty *alignment_baseline;
  FoProperty *background_color;
  FoProperty *background_image;
  FoProperty *baseline_shift;
  FoProperty *blank_or_not_blank;
  FoProperty *block_progression_dimension;
  FoProperty *block_progression_dimension_minimum;
  FoProperty *block_progression_dimension_optimum;
  FoProperty *block_progression_dimension_maximum;
  FoProperty *border;
  FoProperty *border_after_color;
  FoProperty *border_after_precedence;
  FoProperty *border_after_style;
  FoProperty *border_after_width;
  FoProperty *border_before_color;
  FoProperty *border_before_precedence;
  FoProperty *border_before_style;
  FoProperty *border_before_width;
  FoProperty *border_bottom;
  FoProperty *border_bottom_color;
  FoProperty *border_bottom_style;
  FoProperty *border_bottom_width;
  FoProperty *border_collapse;
  FoProperty *border_color;
  FoProperty *border_end_color;
  FoProperty *border_end_precedence;
  FoProperty *border_end_style;
  FoProperty *border_end_width;
  FoProperty *border_left;
  FoProperty *border_left_color;
  FoProperty *border_left_style;
  FoProperty *border_left_width;
  FoProperty *border_right;
  FoProperty *border_right_color;
  FoProperty *border_right_style;
  FoProperty *border_right_width;
  FoProperty *border_separation;
  FoProperty *border_start_color;
  FoProperty *border_start_precedence;
  FoProperty *border_start_style;
  FoProperty *border_start_width;
  FoProperty *border_style;
  FoProperty *border_top;
  FoProperty *border_top_color;
  FoProperty *border_top_style;
  FoProperty *border_top_width;
  FoProperty *border_width;
  FoProperty *break_after;
  FoProperty *break_before;
  FoProperty *character;
  FoProperty *clip;
  FoProperty *color;
  FoProperty *column_number;
  FoProperty *column_width;
  FoProperty *content_height;
  FoProperty *content_type;
  FoProperty *content_width;
  FoProperty *country;
  FoProperty *direction;
  FoProperty *display_align;
  FoProperty *dominant_baseline;
  FoProperty *end_indent;
  FoProperty *extent;
  FoProperty *flow_name;
  FoProperty *font_family;
  FoProperty *font_size;
  FoProperty *font_stretch;
  FoProperty *font_style;
  FoProperty *font_variant;
  FoProperty *font_weight;
  FoProperty *force_page_count;
  FoProperty *format;
  FoProperty *grouping_separator;
  FoProperty *grouping_size;
  FoProperty *height;
  FoProperty *id;
  FoProperty *initial_page_number;
  FoProperty *inline_progression_dimension;
  FoProperty *inline_progression_dimension_minimum;
  FoProperty *inline_progression_dimension_optimum;
  FoProperty *inline_progression_dimension_maximum;
  FoProperty *keep_together;
  FoProperty *keep_together_within_column;
  FoProperty *keep_together_within_line;
  FoProperty *keep_together_within_page;
  FoProperty *keep_with_next;
  FoProperty *keep_with_next_within_column;
  FoProperty *keep_with_next_within_line;
  FoProperty *keep_with_next_within_page;
  FoProperty *keep_with_previous;
  FoProperty *keep_with_previous_within_column;
  FoProperty *keep_with_previous_within_line;
  FoProperty *keep_with_previous_within_page;
  FoProperty *language;
  FoProperty *letter_value;
  FoProperty *line_height;
  FoProperty *line_stacking_strategy;
  FoProperty *linefeed_treatment;
  FoProperty *margin;
  FoProperty *margin_bottom;
  FoProperty *margin_left;
  FoProperty *margin_right;
  FoProperty *margin_top;
  FoProperty *master_name;
  FoProperty *master_reference;
  FoProperty *maximum_repeats;
  FoProperty *media_usage;
  FoProperty *number_columns_repeated;
  FoProperty *number_columns_spanned;
  FoProperty *number_rows_spanned;
  FoProperty *odd_or_even;
  FoProperty *orphans;
  FoProperty *overflow;
  FoProperty *padding;
  FoProperty *padding_after;
  FoProperty *padding_after_length;
  FoProperty *padding_after_condity;
  FoProperty *padding_before;
  FoProperty *padding_before_length;
  FoProperty *padding_before_condity;
  FoProperty *padding_bottom;
  FoProperty *padding_end;
  FoProperty *padding_end_length;
  FoProperty *padding_end_condity;
  FoProperty *padding_left;
  FoProperty *padding_right;
  FoProperty *padding_start;
  FoProperty *padding_start_length;
  FoProperty *padding_start_condity;
  FoProperty *padding_top;
  FoProperty *page_height;
  FoProperty *page_position;
  FoProperty *page_width;
  FoProperty *precedence;
  FoProperty *provisional_distance_between_starts;
  FoProperty *provisional_label_separation;
  FoProperty *ref_id;
  FoProperty *reference_orientation;
  FoProperty *region_name;
  FoProperty *role;
  FoProperty *scaling;
  FoProperty *scaling_method;
  FoProperty *score_spaces;
  FoProperty *source_document;
  FoProperty *space_after;
  FoProperty *space_after_minimum;
  FoProperty *space_after_optimum;
  FoProperty *space_after_maximum;
  FoProperty *space_after_precedence;
  FoProperty *space_after_condity;
  FoProperty *space_before;
  FoProperty *space_before_minimum;
  FoProperty *space_before_optimum;
  FoProperty *space_before_maximum;
  FoProperty *space_before_precedence;
  FoProperty *space_before_condity;
  FoProperty *space_end;
  FoProperty *space_end_minimum;
  FoProperty *space_end_optimum;
  FoProperty *space_end_maximum;
  FoProperty *space_end_precedence;
  FoProperty *space_end_condity;
  FoProperty *space_start;
  FoProperty *space_start_minimum;
  FoProperty *space_start_optimum;
  FoProperty *space_start_maximum;
  FoProperty *space_start_precedence;
  FoProperty *space_start_condity;
  FoProperty *span;
  FoProperty *src;
  FoProperty *start_indent;
  FoProperty *table_layout;
  FoProperty *text_align;
  FoProperty *text_indent;
  FoProperty *unicode_bidi;
  FoProperty *white_space_collapse;
  FoProperty *white_space_treatment;
  FoProperty *widows;
  FoProperty *width;
  FoProperty *wrap_option;
  FoProperty *writing_mode;
};

struct _FoContextClass
{
  FoObjectClass parent_class;
};

G_END_DECLS

#endif /* __FO_CONTEXT_PRIVATE_H__ */
