/* Fo
 * fo-inline.h: 'inline' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_INLINE_H__
#define __FO_INLINE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoInline      FoInline;
typedef struct _FoInlineClass FoInlineClass;

#define FO_TYPE_INLINE              (fo_inline_get_type ())
#define FO_INLINE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_INLINE, FoInline))
#define FO_INLINE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_INLINE, FoInlineClass))
#define FO_IS_INLINE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_INLINE))
#define FO_IS_INLINE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_INLINE))
#define FO_INLINE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_INLINE, FoInlineClass))


GType         fo_inline_get_type      (void) G_GNUC_CONST;
FoFo *fo_inline_new (void);

FoProperty* fo_inline_get_alignment_adjust (FoFo       *fo_fo);
void        fo_inline_set_alignment_adjust (FoFo       *fo_fo,
                                            FoProperty *new_alignment_adjust);
FoProperty* fo_inline_get_alignment_baseline (FoFo       *fo_fo);
void        fo_inline_set_alignment_baseline (FoFo       *fo_fo,
                                              FoProperty *new_alignment_baseline);
FoProperty * fo_inline_get_background_color (FoFo       *fo_fo);
void         fo_inline_set_background_color (FoFo       *fo_fo,
					     FoProperty *new_background_color);
FoProperty* fo_inline_get_background_image (FoFo       *fo_fo);
void        fo_inline_set_background_image (FoFo       *fo_fo,
                                            FoProperty *new_background_image);
FoProperty* fo_inline_get_baseline_shift (FoFo       *fo_fo);
void        fo_inline_set_baseline_shift (FoFo       *fo_fo,
                                          FoProperty *new_baseline_shift);
FoProperty* fo_inline_get_block_progression_dimension (FoFo       *fo_fo);
void        fo_inline_set_block_progression_dimension (FoFo       *fo_fo,
                                                       FoProperty *new_block_progression_dimension);
FoProperty* fo_inline_get_border_after_color (FoFo       *fo_fo);
void        fo_inline_set_border_after_color (FoFo       *fo_fo,
                                              FoProperty *new_border_after_color);
FoProperty* fo_inline_get_border_after_style (FoFo       *fo_fo);
void        fo_inline_set_border_after_style (FoFo       *fo_fo,
                                              FoProperty *new_border_after_style);
FoProperty* fo_inline_get_border_after_width (FoFo       *fo_fo);
void        fo_inline_set_border_after_width (FoFo       *fo_fo,
                                              FoProperty *new_border_after_width);
FoProperty* fo_inline_get_border_before_color (FoFo       *fo_fo);
void        fo_inline_set_border_before_color (FoFo       *fo_fo,
                                               FoProperty *new_border_before_color);
FoProperty* fo_inline_get_border_before_style (FoFo       *fo_fo);
void        fo_inline_set_border_before_style (FoFo       *fo_fo,
                                               FoProperty *new_border_before_style);
FoProperty* fo_inline_get_border_before_width (FoFo       *fo_fo);
void        fo_inline_set_border_before_width (FoFo       *fo_fo,
                                               FoProperty *new_border_before_width);
FoProperty* fo_inline_get_border_bottom_color (FoFo       *fo_fo);
void        fo_inline_set_border_bottom_color (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_color);
FoProperty* fo_inline_get_border_bottom_style (FoFo       *fo_fo);
void        fo_inline_set_border_bottom_style (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_style);
FoProperty* fo_inline_get_border_bottom_width (FoFo       *fo_fo);
void        fo_inline_set_border_bottom_width (FoFo       *fo_fo,
                                               FoProperty *new_border_bottom_width);
FoProperty* fo_inline_get_border_end_color (FoFo       *fo_fo);
void        fo_inline_set_border_end_color (FoFo       *fo_fo,
                                            FoProperty *new_border_end_color);
FoProperty* fo_inline_get_border_end_style (FoFo       *fo_fo);
void        fo_inline_set_border_end_style (FoFo       *fo_fo,
                                            FoProperty *new_border_end_style);
FoProperty* fo_inline_get_border_end_width (FoFo       *fo_fo);
void        fo_inline_set_border_end_width (FoFo       *fo_fo,
                                            FoProperty *new_border_end_width);
FoProperty* fo_inline_get_border_left_color (FoFo       *fo_fo);
void        fo_inline_set_border_left_color (FoFo       *fo_fo,
                                             FoProperty *new_border_left_color);
FoProperty* fo_inline_get_border_left_style (FoFo       *fo_fo);
void        fo_inline_set_border_left_style (FoFo       *fo_fo,
                                             FoProperty *new_border_left_style);
FoProperty* fo_inline_get_border_left_width (FoFo       *fo_fo);
void        fo_inline_set_border_left_width (FoFo       *fo_fo,
                                             FoProperty *new_border_left_width);
FoProperty* fo_inline_get_border_right_color (FoFo       *fo_fo);
void        fo_inline_set_border_right_color (FoFo       *fo_fo,
                                              FoProperty *new_border_right_color);
FoProperty* fo_inline_get_border_right_style (FoFo       *fo_fo);
void        fo_inline_set_border_right_style (FoFo       *fo_fo,
                                              FoProperty *new_border_right_style);
FoProperty* fo_inline_get_border_right_width (FoFo       *fo_fo);
void        fo_inline_set_border_right_width (FoFo       *fo_fo,
                                              FoProperty *new_border_right_width);
FoProperty* fo_inline_get_border_start_color (FoFo       *fo_fo);
void        fo_inline_set_border_start_color (FoFo       *fo_fo,
                                              FoProperty *new_border_start_color);
FoProperty* fo_inline_get_border_start_style (FoFo       *fo_fo);
void        fo_inline_set_border_start_style (FoFo       *fo_fo,
                                              FoProperty *new_border_start_style);
FoProperty* fo_inline_get_border_start_width (FoFo       *fo_fo);
void        fo_inline_set_border_start_width (FoFo       *fo_fo,
                                              FoProperty *new_border_start_width);
FoProperty* fo_inline_get_border_top_color (FoFo       *fo_fo);
void        fo_inline_set_border_top_color (FoFo       *fo_fo,
                                            FoProperty *new_border_top_color);
FoProperty* fo_inline_get_border_top_style (FoFo       *fo_fo);
void        fo_inline_set_border_top_style (FoFo       *fo_fo,
                                            FoProperty *new_border_top_style);
FoProperty* fo_inline_get_border_top_width (FoFo       *fo_fo);
void        fo_inline_set_border_top_width (FoFo       *fo_fo,
                                            FoProperty *new_border_top_width);
FoProperty* fo_inline_get_color (FoFo       *fo_fo);
void        fo_inline_set_color (FoFo       *fo_fo,
                                 FoProperty *new_color);
FoProperty* fo_inline_get_dominant_baseline (FoFo       *fo_fo);
void        fo_inline_set_dominant_baseline (FoFo       *fo_fo,
                                             FoProperty *new_dominant_baseline);
FoProperty* fo_inline_get_font_family (FoFo       *fo_fo);
void        fo_inline_set_font_family (FoFo       *fo_fo,
                                       FoProperty *new_font_family);
FoProperty* fo_inline_get_font_size (FoFo       *fo_fo);
void        fo_inline_set_font_size (FoFo       *fo_fo,
                                     FoProperty *new_font_size);
FoProperty* fo_inline_get_font_stretch (FoFo       *fo_fo);
void        fo_inline_set_font_stretch (FoFo       *fo_fo,
                                        FoProperty *new_font_stretch);
FoProperty* fo_inline_get_font_style (FoFo       *fo_fo);
void        fo_inline_set_font_style (FoFo       *fo_fo,
                                      FoProperty *new_font_style);
FoProperty* fo_inline_get_font_variant (FoFo       *fo_fo);
void        fo_inline_set_font_variant (FoFo       *fo_fo,
                                        FoProperty *new_font_variant);
FoProperty* fo_inline_get_font_weight (FoFo       *fo_fo);
void        fo_inline_set_font_weight (FoFo       *fo_fo,
                                       FoProperty *new_font_weight);
FoProperty* fo_inline_get_height (FoFo       *fo_fo);
void        fo_inline_set_height (FoFo       *fo_fo,
                                  FoProperty *new_height);
FoProperty* fo_inline_get_id (FoFo       *fo_fo);
void        fo_inline_set_id (FoFo       *fo_fo,
                              FoProperty *new_id);
FoProperty* fo_inline_get_inline_progression_dimension (FoFo       *fo_fo);
void        fo_inline_set_inline_progression_dimension (FoFo       *fo_fo,
                                                        FoProperty *new_inline_progression_dimension);
FoProperty* fo_inline_get_keep_together (FoFo       *fo_fo);
void        fo_inline_set_keep_together (FoFo       *fo_fo,
                                         FoProperty *new_keep_together);
FoProperty* fo_inline_get_keep_together_within_column (FoFo       *fo_fo);
void        fo_inline_set_keep_together_within_column (FoFo       *fo_fo,
                                                       FoProperty *new_keep_together_within_column);
FoProperty* fo_inline_get_keep_together_within_line (FoFo       *fo_fo);
void        fo_inline_set_keep_together_within_line (FoFo       *fo_fo,
                                                     FoProperty *new_keep_together_within_line);
FoProperty* fo_inline_get_keep_together_within_page (FoFo       *fo_fo);
void        fo_inline_set_keep_together_within_page (FoFo       *fo_fo,
                                                     FoProperty *new_keep_together_within_page);
FoProperty* fo_inline_get_keep_with_next (FoFo       *fo_fo);
void        fo_inline_set_keep_with_next (FoFo       *fo_fo,
                                          FoProperty *new_keep_with_next);
FoProperty* fo_inline_get_keep_with_next_within_column (FoFo       *fo_fo);
void        fo_inline_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                        FoProperty *new_keep_with_next_within_column);
FoProperty* fo_inline_get_keep_with_next_within_line (FoFo       *fo_fo);
void        fo_inline_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                      FoProperty *new_keep_with_next_within_line);
FoProperty* fo_inline_get_keep_with_next_within_page (FoFo       *fo_fo);
void        fo_inline_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                      FoProperty *new_keep_with_next_within_page);
FoProperty* fo_inline_get_keep_with_previous (FoFo       *fo_fo);
void        fo_inline_set_keep_with_previous (FoFo       *fo_fo,
                                              FoProperty *new_keep_with_previous);
FoProperty* fo_inline_get_keep_with_previous_within_column (FoFo       *fo_fo);
void        fo_inline_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                            FoProperty *new_keep_with_previous_within_column);
FoProperty* fo_inline_get_keep_with_previous_within_line (FoFo       *fo_fo);
void        fo_inline_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                          FoProperty *new_keep_with_previous_within_line);
FoProperty* fo_inline_get_keep_with_previous_within_page (FoFo       *fo_fo);
void        fo_inline_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                          FoProperty *new_keep_with_previous_within_page);
FoProperty* fo_inline_get_line_height (FoFo       *fo_fo);
void        fo_inline_set_line_height (FoFo       *fo_fo,
                                       FoProperty *new_line_height);
FoProperty* fo_inline_get_padding_after (FoFo       *fo_fo);
void        fo_inline_set_padding_after (FoFo       *fo_fo,
                                         FoProperty *new_padding_after);
FoProperty* fo_inline_get_padding_before (FoFo       *fo_fo);
void        fo_inline_set_padding_before (FoFo       *fo_fo,
                                          FoProperty *new_padding_before);
FoProperty* fo_inline_get_padding_bottom (FoFo       *fo_fo);
void        fo_inline_set_padding_bottom (FoFo       *fo_fo,
                                          FoProperty *new_padding_bottom);
FoProperty* fo_inline_get_padding_end (FoFo       *fo_fo);
void        fo_inline_set_padding_end (FoFo       *fo_fo,
                                       FoProperty *new_padding_end);
FoProperty* fo_inline_get_padding_left (FoFo       *fo_fo);
void        fo_inline_set_padding_left (FoFo       *fo_fo,
                                        FoProperty *new_padding_left);
FoProperty* fo_inline_get_padding_right (FoFo       *fo_fo);
void        fo_inline_set_padding_right (FoFo       *fo_fo,
                                         FoProperty *new_padding_right);
FoProperty* fo_inline_get_padding_start (FoFo       *fo_fo);
void        fo_inline_set_padding_start (FoFo       *fo_fo,
                                         FoProperty *new_padding_start);
FoProperty* fo_inline_get_padding_top (FoFo       *fo_fo);
void        fo_inline_set_padding_top (FoFo       *fo_fo,
                                       FoProperty *new_padding_top);
FoProperty* fo_inline_get_role (FoFo       *fo_fo);
void        fo_inline_set_role (FoFo       *fo_fo,
                                FoProperty *new_role);
FoProperty* fo_inline_get_source_document (FoFo       *fo_fo);
void        fo_inline_set_source_document (FoFo       *fo_fo,
                                           FoProperty *new_source_document);
FoProperty* fo_inline_get_space_end (FoFo       *fo_fo);
void        fo_inline_set_space_end (FoFo       *fo_fo,
                                     FoProperty *new_space_end);
FoProperty* fo_inline_get_space_start (FoFo       *fo_fo);
void        fo_inline_set_space_start (FoFo       *fo_fo,
                                       FoProperty *new_space_start);
FoProperty* fo_inline_get_width (FoFo       *fo_fo);
void        fo_inline_set_width (FoFo       *fo_fo,
                                 FoProperty *new_width);
FoProperty* fo_inline_get_wrap_option (FoFo       *fo_fo);
void        fo_inline_set_wrap_option (FoFo       *fo_fo,
                                       FoProperty *new_wrap_option);

G_END_DECLS

#endif /* !__FO_INLINE_H__ */
