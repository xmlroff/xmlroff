/* Fo
 * fo-block.h: 'block' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_BLOCK_H__
#define __FO_BLOCK_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoBlock:
 *
 * Instance of the 'block' formatting object.
 **/
typedef struct _FoBlock      FoBlock;

/**
 * FoBlockClass:
 *
 * Class structure for the 'block' formatting object.
 **/
typedef struct _FoBlockClass FoBlockClass;

#define FO_TYPE_BLOCK              (fo_block_get_type ())
#define FO_BLOCK(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_BLOCK, FoBlock))
#define FO_BLOCK_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_BLOCK, FoBlockClass))
#define FO_IS_BLOCK(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_BLOCK))
#define FO_IS_BLOCK_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_BLOCK))
#define FO_BLOCK_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_BLOCK, FoBlockClass))


GType        fo_block_get_type (void) G_GNUC_CONST;
FoFo *       fo_block_new      (void);

FoProperty * fo_block_get_background_color (FoFo       *fo_fo);
void         fo_block_set_background_color (FoFo       *fo_fo,
                                            FoProperty *new_background_color);
FoProperty * fo_block_get_background_image (FoFo       *fo_fo);
void         fo_block_set_background_image (FoFo       *fo_fo,
                                            FoProperty *new_background_image);
FoProperty * fo_block_get_border_after_color (FoFo       *fo_fo);
void         fo_block_set_border_after_color (FoFo       *fo_fo,
                                              FoProperty *new_border_after_color);
FoProperty * fo_block_get_border_after_style (FoFo       *fo_fo);
void         fo_block_set_border_after_style (FoFo       *fo_fo,
                                              FoProperty *new_border_after_style);
FoProperty * fo_block_get_border_after_width (FoFo       *fo_fo);
void         fo_block_set_border_after_width (FoFo       *fo_fo,
                                              FoProperty *new_border_after_width);
FoProperty * fo_block_get_border_before_color (FoFo       *fo_fo);
void         fo_block_set_border_before_color (FoFo       *fo_fo,
                                               FoProperty *new_border_before_color);
FoProperty * fo_block_get_border_before_style (FoFo       *fo_fo);
void         fo_block_set_border_before_style (FoFo       *fo_fo,
                                               FoProperty *new_border_before_style);
FoProperty * fo_block_get_border_before_width (FoFo       *fo_fo);
void         fo_block_set_border_before_width (FoFo       *fo_fo,
                                               FoProperty *new_border_before_width);
FoProperty * fo_block_get_border_bottom_color (FoFo       *fo_fo);
void         fo_block_set_border_bottom_color (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_color);
FoProperty * fo_block_get_border_bottom_style (FoFo       *fo_fo);
void         fo_block_set_border_bottom_style (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_style);
FoProperty * fo_block_get_border_bottom_width (FoFo       *fo_fo);
void         fo_block_set_border_bottom_width (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_width);
FoProperty * fo_block_get_border_end_color (FoFo       *fo_fo);
void         fo_block_set_border_end_color (FoFo       *fo_fo,
                                            FoProperty *new_border_end_color);
FoProperty * fo_block_get_border_end_style (FoFo       *fo_fo);
void         fo_block_set_border_end_style (FoFo       *fo_fo,
                                            FoProperty *new_border_end_style);
FoProperty * fo_block_get_border_end_width (FoFo       *fo_fo);
void         fo_block_set_border_end_width (FoFo       *fo_fo,
                                            FoProperty *new_border_end_width);
FoProperty * fo_block_get_border_left_color (FoFo       *fo_fo);
void         fo_block_set_border_left_color (FoFo       *fo_fo,
                                             FoProperty *new_border_left_color);
FoProperty * fo_block_get_border_left_style (FoFo       *fo_fo);
void         fo_block_set_border_left_style (FoFo       *fo_fo,
                                             FoProperty *new_border_left_style);
FoProperty * fo_block_get_border_left_width (FoFo       *fo_fo);
void         fo_block_set_border_left_width (FoFo       *fo_fo,
                                             FoProperty *new_border_left_width);
FoProperty * fo_block_get_border_right_color (FoFo       *fo_fo);
void         fo_block_set_border_right_color (FoFo       *fo_fo,
                                              FoProperty *new_border_right_color);
FoProperty * fo_block_get_border_right_style (FoFo       *fo_fo);
void         fo_block_set_border_right_style (FoFo       *fo_fo,
                                              FoProperty *new_border_right_style);
FoProperty * fo_block_get_border_right_width (FoFo       *fo_fo);
void         fo_block_set_border_right_width (FoFo       *fo_fo,
                                              FoProperty *new_border_right_width);
FoProperty * fo_block_get_border_start_color (FoFo       *fo_fo);
void         fo_block_set_border_start_color (FoFo       *fo_fo,
                                              FoProperty *new_border_start_color);
FoProperty * fo_block_get_border_start_style (FoFo       *fo_fo);
void         fo_block_set_border_start_style (FoFo       *fo_fo,
                                              FoProperty *new_border_start_style);
FoProperty * fo_block_get_border_start_width (FoFo       *fo_fo);
void         fo_block_set_border_start_width (FoFo       *fo_fo,
                                              FoProperty *new_border_start_width);
FoProperty * fo_block_get_border_top_color (FoFo       *fo_fo);
void         fo_block_set_border_top_color (FoFo       *fo_fo,
                                            FoProperty *new_border_top_color);
FoProperty * fo_block_get_border_top_style (FoFo       *fo_fo);
void         fo_block_set_border_top_style (FoFo       *fo_fo,
                                            FoProperty *new_border_top_style);
FoProperty * fo_block_get_border_top_width (FoFo       *fo_fo);
void         fo_block_set_border_top_width (FoFo       *fo_fo,
                                            FoProperty *new_border_top_width);
FoProperty * fo_block_get_break_after (FoFo       *fo_fo);
void         fo_block_set_break_after (FoFo       *fo_fo,
                                       FoProperty *new_break_after);
FoProperty * fo_block_get_break_before (FoFo       *fo_fo);
void         fo_block_set_break_before (FoFo       *fo_fo,
                                        FoProperty *new_break_before);
FoProperty * fo_block_get_color (FoFo       *fo_fo);
void         fo_block_set_color (FoFo       *fo_fo,
                                 FoProperty *new_color);
FoProperty * fo_block_get_end_indent (FoFo       *fo_fo);
void         fo_block_set_end_indent (FoFo       *fo_fo,
                                      FoProperty *new_end_indent);
FoProperty * fo_block_get_font_family (FoFo       *fo_fo);
void         fo_block_set_font_family (FoFo       *fo_fo,
                                       FoProperty *new_font_family);
FoProperty * fo_block_get_font_size (FoFo       *fo_fo);
void         fo_block_set_font_size (FoFo       *fo_fo,
                                     FoProperty *new_font_size);
FoProperty * fo_block_get_font_stretch (FoFo       *fo_fo);
void         fo_block_set_font_stretch (FoFo       *fo_fo,
                                        FoProperty *new_font_stretch);
FoProperty * fo_block_get_font_style (FoFo       *fo_fo);
void         fo_block_set_font_style (FoFo       *fo_fo,
                                      FoProperty *new_font_style);
FoProperty * fo_block_get_font_variant (FoFo       *fo_fo);
void         fo_block_set_font_variant (FoFo       *fo_fo,
                                        FoProperty *new_font_variant);
FoProperty * fo_block_get_font_weight (FoFo       *fo_fo);
void         fo_block_set_font_weight (FoFo       *fo_fo,
                                       FoProperty *new_font_weight);
FoProperty * fo_block_get_id (FoFo       *fo_fo);
void         fo_block_set_id (FoFo       *fo_fo,
                              FoProperty *new_id);
FoProperty * fo_block_get_keep_together (FoFo       *fo_fo);
void         fo_block_set_keep_together (FoFo       *fo_fo,
                                         FoProperty *new_keep_together);
FoProperty * fo_block_get_keep_together_within_column (FoFo       *fo_fo);
void         fo_block_set_keep_together_within_column (FoFo       *fo_fo,
                                                       FoProperty *new_keep_together_within_column);
FoProperty * fo_block_get_keep_together_within_line (FoFo       *fo_fo);
void         fo_block_set_keep_together_within_line (FoFo       *fo_fo,
                                                     FoProperty *new_keep_together_within_line);
FoProperty * fo_block_get_keep_together_within_page (FoFo       *fo_fo);
void         fo_block_set_keep_together_within_page (FoFo       *fo_fo,
                                                     FoProperty *new_keep_together_within_page);
FoProperty * fo_block_get_keep_with_next (FoFo       *fo_fo);
void         fo_block_set_keep_with_next (FoFo       *fo_fo,
                                          FoProperty *new_keep_with_next);
FoProperty * fo_block_get_keep_with_next_within_column (FoFo       *fo_fo);
void         fo_block_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                        FoProperty *new_keep_with_next_within_column);
FoProperty * fo_block_get_keep_with_next_within_line (FoFo       *fo_fo);
void         fo_block_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                      FoProperty *new_keep_with_next_within_line);
FoProperty * fo_block_get_keep_with_next_within_page (FoFo       *fo_fo);
void         fo_block_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                      FoProperty *new_keep_with_next_within_page);
FoProperty * fo_block_get_keep_with_previous (FoFo       *fo_fo);
void         fo_block_set_keep_with_previous (FoFo       *fo_fo,
                                              FoProperty *new_keep_with_previous);
FoProperty * fo_block_get_keep_with_previous_within_column (FoFo       *fo_fo);
void         fo_block_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                            FoProperty *new_keep_with_previous_within_column);
FoProperty * fo_block_get_keep_with_previous_within_line (FoFo       *fo_fo);
void         fo_block_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                          FoProperty *new_keep_with_previous_within_line);
FoProperty * fo_block_get_keep_with_previous_within_page (FoFo       *fo_fo);
void         fo_block_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                          FoProperty *new_keep_with_previous_within_page);
FoProperty * fo_block_get_line_height (FoFo       *fo_fo);
void         fo_block_set_line_height (FoFo       *fo_fo,
                                       FoProperty *new_line_height);
FoProperty * fo_block_get_line_stacking_strategy (FoFo       *fo_fo);
void         fo_block_set_line_stacking_strategy (FoFo       *fo_fo,
                                                  FoProperty *new_line_stacking_strategy);
FoProperty * fo_block_get_linefeed_treatment (FoFo       *fo_fo);
void         fo_block_set_linefeed_treatment (FoFo       *fo_fo,
                                              FoProperty *new_linefeed_treatment);
FoProperty * fo_block_get_margin_bottom (FoFo       *fo_fo);
void         fo_block_set_margin_bottom (FoFo       *fo_fo,
                                         FoProperty *new_margin_bottom);
FoProperty * fo_block_get_margin_left (FoFo       *fo_fo);
void         fo_block_set_margin_left (FoFo       *fo_fo,
                                       FoProperty *new_margin_left);
FoProperty * fo_block_get_margin_right (FoFo       *fo_fo);
void         fo_block_set_margin_right (FoFo       *fo_fo,
                                        FoProperty *new_margin_right);
FoProperty * fo_block_get_margin_top (FoFo       *fo_fo);
void         fo_block_set_margin_top (FoFo       *fo_fo,
                                      FoProperty *new_margin_top);
FoProperty * fo_block_get_orphans (FoFo       *fo_fo);
void         fo_block_set_orphans (FoFo       *fo_fo,
                                   FoProperty *new_orphans);
FoProperty * fo_block_get_padding_after (FoFo       *fo_fo);
void         fo_block_set_padding_after (FoFo       *fo_fo,
                                         FoProperty *new_padding_after);
FoProperty * fo_block_get_padding_before (FoFo       *fo_fo);
void         fo_block_set_padding_before (FoFo       *fo_fo,
                                          FoProperty *new_padding_before);
FoProperty * fo_block_get_padding_bottom (FoFo       *fo_fo);
void         fo_block_set_padding_bottom (FoFo       *fo_fo,
                                          FoProperty *new_padding_bottom);
FoProperty * fo_block_get_padding_end (FoFo       *fo_fo);
void         fo_block_set_padding_end (FoFo       *fo_fo,
                                       FoProperty *new_padding_end);
FoProperty * fo_block_get_padding_left (FoFo       *fo_fo);
void         fo_block_set_padding_left (FoFo       *fo_fo,
                                        FoProperty *new_padding_left);
FoProperty * fo_block_get_padding_right (FoFo       *fo_fo);
void         fo_block_set_padding_right (FoFo       *fo_fo,
                                         FoProperty *new_padding_right);
FoProperty * fo_block_get_padding_start (FoFo       *fo_fo);
void         fo_block_set_padding_start (FoFo       *fo_fo,
                                         FoProperty *new_padding_start);
FoProperty * fo_block_get_padding_top (FoFo       *fo_fo);
void         fo_block_set_padding_top (FoFo       *fo_fo,
                                       FoProperty *new_padding_top);
FoProperty * fo_block_get_role (FoFo       *fo_fo);
void         fo_block_set_role (FoFo       *fo_fo,
                                FoProperty *new_role);
FoProperty * fo_block_get_source_document (FoFo       *fo_fo);
void         fo_block_set_source_document (FoFo       *fo_fo,
                                           FoProperty *new_source_document);
FoProperty * fo_block_get_space_after (FoFo       *fo_fo);
void         fo_block_set_space_after (FoFo       *fo_fo,
                                       FoProperty *new_space_after);
FoProperty * fo_block_get_space_before (FoFo       *fo_fo);
void         fo_block_set_space_before (FoFo       *fo_fo,
                                        FoProperty *new_space_before);
FoProperty * fo_block_get_span (FoFo       *fo_fo);
void         fo_block_set_span (FoFo       *fo_fo,
                                FoProperty *new_span);
FoProperty * fo_block_get_start_indent (FoFo       *fo_fo);
void         fo_block_set_start_indent (FoFo       *fo_fo,
                                        FoProperty *new_start_indent);
FoProperty * fo_block_get_text_align (FoFo       *fo_fo);
void         fo_block_set_text_align (FoFo       *fo_fo,
                                      FoProperty *new_text_align);
FoProperty * fo_block_get_text_indent (FoFo       *fo_fo);
void         fo_block_set_text_indent (FoFo       *fo_fo,
                                       FoProperty *new_text_indent);
FoProperty * fo_block_get_white_space_collapse (FoFo       *fo_fo);
void         fo_block_set_white_space_collapse (FoFo       *fo_fo,
                                                FoProperty *new_white_space_collapse);
FoProperty * fo_block_get_white_space_treatment (FoFo       *fo_fo);
void         fo_block_set_white_space_treatment (FoFo       *fo_fo,
                                                 FoProperty *new_white_space_treatment);
FoProperty * fo_block_get_widows (FoFo       *fo_fo);
void         fo_block_set_widows (FoFo       *fo_fo,
                                  FoProperty *new_widows);
FoProperty * fo_block_get_wrap_option (FoFo       *fo_fo);
void         fo_block_set_wrap_option (FoFo       *fo_fo,
                                       FoProperty *new_wrap_option);

G_END_DECLS

#endif /* !__FO_BLOCK_H__ */
