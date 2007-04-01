/* Fo
 * fo-page-number-citation.h: 'page-number-citation' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-page-number-citation.h,v 1.5 2006/03/21 23:24:49 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PAGE_NUMBER_CITATION_H__
#define __FO_PAGE_NUMBER_CITATION_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoPageNumberCitation:
 *
 * Instance of the 'page-number-citation' formatting object.
 **/
typedef struct _FoPageNumberCitation      FoPageNumberCitation;

/**
 * FoPageNumberCitationClass:
 *
 * Class structure for the 'page-number-citation' formatting object.
 **/
typedef struct _FoPageNumberCitationClass FoPageNumberCitationClass;

#define FO_TYPE_PAGE_NUMBER_CITATION              (fo_page_number_citation_get_type ())
#define FO_PAGE_NUMBER_CITATION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PAGE_NUMBER_CITATION, FoPageNumberCitation))
#define FO_PAGE_NUMBER_CITATION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PAGE_NUMBER_CITATION, FoPageNumberCitationClass))
#define FO_IS_PAGE_NUMBER_CITATION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PAGE_NUMBER_CITATION))
#define FO_IS_PAGE_NUMBER_CITATION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PAGE_NUMBER_CITATION))
#define FO_PAGE_NUMBER_CITATION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PAGE_NUMBER_CITATION, FoPageNumberCitationClass))


GType        fo_page_number_citation_get_type (void) G_GNUC_CONST;
FoFo *       fo_page_number_citation_new      (void);

FoProperty * fo_page_number_citation_get_alignment_adjust (FoFo       *fo_fo);
void         fo_page_number_citation_set_alignment_adjust (FoFo       *fo_fo,
                                                           FoProperty *new_alignment_adjust);
FoProperty * fo_page_number_citation_get_alignment_baseline (FoFo       *fo_fo);
void         fo_page_number_citation_set_alignment_baseline (FoFo       *fo_fo,
                                                             FoProperty *new_alignment_baseline);
FoProperty * fo_page_number_citation_get_background_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_background_color (FoFo       *fo_fo,
                                                           FoProperty *new_background_color);
FoProperty * fo_page_number_citation_get_background_image (FoFo       *fo_fo);
void         fo_page_number_citation_set_background_image (FoFo       *fo_fo,
                                                           FoProperty *new_background_image);
FoProperty * fo_page_number_citation_get_baseline_shift (FoFo       *fo_fo);
void         fo_page_number_citation_set_baseline_shift (FoFo       *fo_fo,
                                                         FoProperty *new_baseline_shift);
FoProperty * fo_page_number_citation_get_border_after_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_after_color (FoFo       *fo_fo,
                                                             FoProperty *new_border_after_color);
FoProperty * fo_page_number_citation_get_border_after_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_after_style (FoFo       *fo_fo,
                                                             FoProperty *new_border_after_style);
FoProperty * fo_page_number_citation_get_border_after_width (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_after_width (FoFo       *fo_fo,
                                                             FoProperty *new_border_after_width);
FoProperty * fo_page_number_citation_get_border_before_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_before_color (FoFo       *fo_fo,
                                                              FoProperty *new_border_before_color);
FoProperty * fo_page_number_citation_get_border_before_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_before_style (FoFo       *fo_fo,
                                                              FoProperty *new_border_before_style);
FoProperty * fo_page_number_citation_get_border_before_width (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_before_width (FoFo       *fo_fo,
                                                              FoProperty *new_border_before_width);
FoProperty * fo_page_number_citation_get_border_bottom_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_bottom_color (FoFo       *fo_fo,
                                                              FoProperty *new_border_bottom_color);
FoProperty * fo_page_number_citation_get_border_bottom_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_bottom_style (FoFo       *fo_fo,
                                                              FoProperty *new_border_bottom_style);
FoProperty * fo_page_number_citation_get_border_bottom_width (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_bottom_width (FoFo       *fo_fo,
                                                              FoProperty *new_border_bottom_width);
FoProperty * fo_page_number_citation_get_border_end_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_end_color (FoFo       *fo_fo,
                                                           FoProperty *new_border_end_color);
FoProperty * fo_page_number_citation_get_border_end_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_end_style (FoFo       *fo_fo,
                                                           FoProperty *new_border_end_style);
FoProperty * fo_page_number_citation_get_border_end_width (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_end_width (FoFo       *fo_fo,
                                                           FoProperty *new_border_end_width);
FoProperty * fo_page_number_citation_get_border_left_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_left_color (FoFo       *fo_fo,
                                                            FoProperty *new_border_left_color);
FoProperty * fo_page_number_citation_get_border_left_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_left_style (FoFo       *fo_fo,
                                                            FoProperty *new_border_left_style);
FoProperty * fo_page_number_citation_get_border_left_width (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_left_width (FoFo       *fo_fo,
                                                            FoProperty *new_border_left_width);
FoProperty * fo_page_number_citation_get_border_right_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_right_color (FoFo       *fo_fo,
                                                             FoProperty *new_border_right_color);
FoProperty * fo_page_number_citation_get_border_right_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_right_style (FoFo       *fo_fo,
                                                             FoProperty *new_border_right_style);
FoProperty * fo_page_number_citation_get_border_right_width (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_right_width (FoFo       *fo_fo,
                                                             FoProperty *new_border_right_width);
FoProperty * fo_page_number_citation_get_border_start_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_start_color (FoFo       *fo_fo,
                                                             FoProperty *new_border_start_color);
FoProperty * fo_page_number_citation_get_border_start_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_start_style (FoFo       *fo_fo,
                                                             FoProperty *new_border_start_style);
FoProperty * fo_page_number_citation_get_border_start_width (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_start_width (FoFo       *fo_fo,
                                                             FoProperty *new_border_start_width);
FoProperty * fo_page_number_citation_get_border_top_color (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_top_color (FoFo       *fo_fo,
                                                           FoProperty *new_border_top_color);
FoProperty * fo_page_number_citation_get_border_top_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_top_style (FoFo       *fo_fo,
                                                           FoProperty *new_border_top_style);
FoProperty * fo_page_number_citation_get_border_top_width (FoFo       *fo_fo);
void         fo_page_number_citation_set_border_top_width (FoFo       *fo_fo,
                                                           FoProperty *new_border_top_width);
FoProperty * fo_page_number_citation_get_dominant_baseline (FoFo       *fo_fo);
void         fo_page_number_citation_set_dominant_baseline (FoFo       *fo_fo,
                                                            FoProperty *new_dominant_baseline);
FoProperty * fo_page_number_citation_get_font_family (FoFo       *fo_fo);
void         fo_page_number_citation_set_font_family (FoFo       *fo_fo,
                                                      FoProperty *new_font_family);
FoProperty * fo_page_number_citation_get_font_size (FoFo       *fo_fo);
void         fo_page_number_citation_set_font_size (FoFo       *fo_fo,
                                                    FoProperty *new_font_size);
FoProperty * fo_page_number_citation_get_font_stretch (FoFo       *fo_fo);
void         fo_page_number_citation_set_font_stretch (FoFo       *fo_fo,
                                                       FoProperty *new_font_stretch);
FoProperty * fo_page_number_citation_get_font_style (FoFo       *fo_fo);
void         fo_page_number_citation_set_font_style (FoFo       *fo_fo,
                                                     FoProperty *new_font_style);
FoProperty * fo_page_number_citation_get_font_variant (FoFo       *fo_fo);
void         fo_page_number_citation_set_font_variant (FoFo       *fo_fo,
                                                       FoProperty *new_font_variant);
FoProperty * fo_page_number_citation_get_font_weight (FoFo       *fo_fo);
void         fo_page_number_citation_set_font_weight (FoFo       *fo_fo,
                                                      FoProperty *new_font_weight);
FoProperty * fo_page_number_citation_get_id (FoFo       *fo_fo);
void         fo_page_number_citation_set_id (FoFo       *fo_fo,
                                             FoProperty *new_id);
FoProperty * fo_page_number_citation_get_keep_with_next (FoFo       *fo_fo);
void         fo_page_number_citation_set_keep_with_next (FoFo       *fo_fo,
                                                         FoProperty *new_keep_with_next);
FoProperty * fo_page_number_citation_get_keep_with_next_within_column (FoFo       *fo_fo);
void         fo_page_number_citation_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                                       FoProperty *new_keep_with_next_within_column);
FoProperty * fo_page_number_citation_get_keep_with_next_within_line (FoFo       *fo_fo);
void         fo_page_number_citation_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                                     FoProperty *new_keep_with_next_within_line);
FoProperty * fo_page_number_citation_get_keep_with_next_within_page (FoFo       *fo_fo);
void         fo_page_number_citation_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                                     FoProperty *new_keep_with_next_within_page);
FoProperty * fo_page_number_citation_get_keep_with_previous (FoFo       *fo_fo);
void         fo_page_number_citation_set_keep_with_previous (FoFo       *fo_fo,
                                                             FoProperty *new_keep_with_previous);
FoProperty * fo_page_number_citation_get_keep_with_previous_within_column (FoFo       *fo_fo);
void         fo_page_number_citation_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                                           FoProperty *new_keep_with_previous_within_column);
FoProperty * fo_page_number_citation_get_keep_with_previous_within_line (FoFo       *fo_fo);
void         fo_page_number_citation_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                                         FoProperty *new_keep_with_previous_within_line);
FoProperty * fo_page_number_citation_get_keep_with_previous_within_page (FoFo       *fo_fo);
void         fo_page_number_citation_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                                         FoProperty *new_keep_with_previous_within_page);
FoProperty * fo_page_number_citation_get_line_height (FoFo       *fo_fo);
void         fo_page_number_citation_set_line_height (FoFo       *fo_fo,
                                                      FoProperty *new_line_height);
FoProperty * fo_page_number_citation_get_padding_after (FoFo       *fo_fo);
void         fo_page_number_citation_set_padding_after (FoFo       *fo_fo,
                                                        FoProperty *new_padding_after);
FoProperty * fo_page_number_citation_get_padding_before (FoFo       *fo_fo);
void         fo_page_number_citation_set_padding_before (FoFo       *fo_fo,
                                                         FoProperty *new_padding_before);
FoProperty * fo_page_number_citation_get_padding_bottom (FoFo       *fo_fo);
void         fo_page_number_citation_set_padding_bottom (FoFo       *fo_fo,
                                                         FoProperty *new_padding_bottom);
FoProperty * fo_page_number_citation_get_padding_end (FoFo       *fo_fo);
void         fo_page_number_citation_set_padding_end (FoFo       *fo_fo,
                                                      FoProperty *new_padding_end);
FoProperty * fo_page_number_citation_get_padding_left (FoFo       *fo_fo);
void         fo_page_number_citation_set_padding_left (FoFo       *fo_fo,
                                                       FoProperty *new_padding_left);
FoProperty * fo_page_number_citation_get_padding_right (FoFo       *fo_fo);
void         fo_page_number_citation_set_padding_right (FoFo       *fo_fo,
                                                        FoProperty *new_padding_right);
FoProperty * fo_page_number_citation_get_padding_start (FoFo       *fo_fo);
void         fo_page_number_citation_set_padding_start (FoFo       *fo_fo,
                                                        FoProperty *new_padding_start);
FoProperty * fo_page_number_citation_get_padding_top (FoFo       *fo_fo);
void         fo_page_number_citation_set_padding_top (FoFo       *fo_fo,
                                                      FoProperty *new_padding_top);
FoProperty * fo_page_number_citation_get_ref_id (FoFo       *fo_fo);
void         fo_page_number_citation_set_ref_id (FoFo       *fo_fo,
                                                 FoProperty *new_ref_id);
FoProperty * fo_page_number_citation_get_role (FoFo       *fo_fo);
void         fo_page_number_citation_set_role (FoFo       *fo_fo,
                                               FoProperty *new_role);
FoProperty * fo_page_number_citation_get_score_spaces (FoFo       *fo_fo);
void         fo_page_number_citation_set_score_spaces (FoFo       *fo_fo,
                                                       FoProperty *new_score_spaces);
FoProperty * fo_page_number_citation_get_source_document (FoFo       *fo_fo);
void         fo_page_number_citation_set_source_document (FoFo       *fo_fo,
                                                          FoProperty *new_source_document);
FoProperty * fo_page_number_citation_get_space_end (FoFo       *fo_fo);
void         fo_page_number_citation_set_space_end (FoFo       *fo_fo,
                                                    FoProperty *new_space_end);
FoProperty * fo_page_number_citation_get_space_start (FoFo       *fo_fo);
void         fo_page_number_citation_set_space_start (FoFo       *fo_fo,
                                                      FoProperty *new_space_start);
FoProperty * fo_page_number_citation_get_wrap_option (FoFo       *fo_fo);
void         fo_page_number_citation_set_wrap_option (FoFo       *fo_fo,
                                                      FoProperty *new_wrap_option);

G_END_DECLS

#endif /* !__FO_PAGE_NUMBER_CITATION_H__ */
