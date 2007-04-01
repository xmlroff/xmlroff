/* Fo
 * fo-leader.h: 'leader' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-leader.h,v 1.4 2004/03/30 22:45:41 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LEADER_H__
#define __FO_LEADER_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

typedef struct _FoLeader      FoLeader;
typedef struct _FoLeaderClass FoLeaderClass;

#define FO_TYPE_LEADER              (fo_leader_get_type ())
#define FO_LEADER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LEADER, FoLeader))
#define FO_LEADER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LEADER, FoLeaderClass))
#define FO_IS_LEADER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LEADER))
#define FO_IS_LEADER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LEADER))
#define FO_LEADER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LEADER, FoLeaderClass))


GType        fo_leader_get_type      (void) G_GNUC_CONST;
FoFo *       fo_leader_new (void);

FoProperty * fo_leader_get_alignment_adjust (FoFo       *fo_fo);
void         fo_leader_set_alignment_adjust (FoFo       *fo_fo,
                                             FoProperty *new_alignment_adjust);
FoProperty * fo_leader_get_alignment_baseline (FoFo       *fo_fo);
void         fo_leader_set_alignment_baseline (FoFo       *fo_fo,
                                               FoProperty *new_alignment_baseline);
FoProperty  * fo_leader_get_background_color (FoFo       *fo_fo);
void          fo_leader_set_background_color (FoFo       *fo_fo,
					      FoProperty *new_background_color);
FoProperty * fo_leader_get_background_image (FoFo       *fo_fo);
void         fo_leader_set_background_image (FoFo       *fo_fo,
                                             FoProperty *new_background_image);
FoProperty * fo_leader_get_baseline_shift (FoFo       *fo_fo);
void         fo_leader_set_baseline_shift (FoFo       *fo_fo,
                                           FoProperty *new_baseline_shift);
FoProperty * fo_leader_get_border_after_color (FoFo       *fo_fo);
void         fo_leader_set_border_after_color (FoFo       *fo_fo,
                                               FoProperty *new_border_after_color);
FoProperty * fo_leader_get_border_after_style (FoFo       *fo_fo);
void         fo_leader_set_border_after_style (FoFo       *fo_fo,
                                               FoProperty *new_border_after_style);
FoProperty * fo_leader_get_border_after_width (FoFo       *fo_fo);
void         fo_leader_set_border_after_width (FoFo       *fo_fo,
                                               FoProperty *new_border_after_width);
FoProperty * fo_leader_get_border_before_color (FoFo       *fo_fo);
void         fo_leader_set_border_before_color (FoFo       *fo_fo,
                                                FoProperty *new_border_before_color);
FoProperty * fo_leader_get_border_before_style (FoFo       *fo_fo);
void         fo_leader_set_border_before_style (FoFo       *fo_fo,
                                                FoProperty *new_border_before_style);
FoProperty * fo_leader_get_border_before_width (FoFo       *fo_fo);
void         fo_leader_set_border_before_width (FoFo       *fo_fo,
                                                FoProperty *new_border_before_width);
FoProperty * fo_leader_get_border_bottom_color (FoFo       *fo_fo);
void         fo_leader_set_border_bottom_color (FoFo       *fo_fo,
                                                FoProperty *new_border_bottom_color);
FoProperty * fo_leader_get_border_bottom_style (FoFo       *fo_fo);
void         fo_leader_set_border_bottom_style (FoFo       *fo_fo,
                                                FoProperty *new_border_bottom_style);
FoProperty * fo_leader_get_border_bottom_width (FoFo       *fo_fo);
void         fo_leader_set_border_bottom_width (FoFo       *fo_fo,
                                                FoProperty *new_border_bottom_width);
FoProperty * fo_leader_get_border_end_color (FoFo       *fo_fo);
void         fo_leader_set_border_end_color (FoFo       *fo_fo,
                                             FoProperty *new_border_end_color);
FoProperty * fo_leader_get_border_end_style (FoFo       *fo_fo);
void         fo_leader_set_border_end_style (FoFo       *fo_fo,
                                             FoProperty *new_border_end_style);
FoProperty * fo_leader_get_border_end_width (FoFo       *fo_fo);
void         fo_leader_set_border_end_width (FoFo       *fo_fo,
                                             FoProperty *new_border_end_width);
FoProperty * fo_leader_get_border_left_color (FoFo       *fo_fo);
void         fo_leader_set_border_left_color (FoFo       *fo_fo,
                                              FoProperty *new_border_left_color);
FoProperty * fo_leader_get_border_left_style (FoFo       *fo_fo);
void         fo_leader_set_border_left_style (FoFo       *fo_fo,
                                              FoProperty *new_border_left_style);
FoProperty * fo_leader_get_border_left_width (FoFo       *fo_fo);
void         fo_leader_set_border_left_width (FoFo       *fo_fo,
                                              FoProperty *new_border_left_width);
FoProperty * fo_leader_get_border_right_color (FoFo       *fo_fo);
void         fo_leader_set_border_right_color (FoFo       *fo_fo,
                                               FoProperty *new_border_right_color);
FoProperty * fo_leader_get_border_right_style (FoFo       *fo_fo);
void         fo_leader_set_border_right_style (FoFo       *fo_fo,
                                               FoProperty *new_border_right_style);
FoProperty * fo_leader_get_border_right_width (FoFo       *fo_fo);
void         fo_leader_set_border_right_width (FoFo       *fo_fo,
                                               FoProperty *new_border_right_width);
FoProperty * fo_leader_get_border_start_color (FoFo       *fo_fo);
void         fo_leader_set_border_start_color (FoFo       *fo_fo,
                                               FoProperty *new_border_start_color);
FoProperty * fo_leader_get_border_start_style (FoFo       *fo_fo);
void         fo_leader_set_border_start_style (FoFo       *fo_fo,
                                               FoProperty *new_border_start_style);
FoProperty * fo_leader_get_border_start_width (FoFo       *fo_fo);
void         fo_leader_set_border_start_width (FoFo       *fo_fo,
                                               FoProperty *new_border_start_width);
FoProperty * fo_leader_get_border_top_color (FoFo       *fo_fo);
void         fo_leader_set_border_top_color (FoFo       *fo_fo,
                                             FoProperty *new_border_top_color);
FoProperty * fo_leader_get_border_top_style (FoFo       *fo_fo);
void         fo_leader_set_border_top_style (FoFo       *fo_fo,
                                             FoProperty *new_border_top_style);
FoProperty * fo_leader_get_border_top_width (FoFo       *fo_fo);
void         fo_leader_set_border_top_width (FoFo       *fo_fo,
                                             FoProperty *new_border_top_width);
FoProperty * fo_leader_get_color (FoFo       *fo_fo);
void         fo_leader_set_color (FoFo       *fo_fo,
                                  FoProperty *new_color);
FoProperty * fo_leader_get_dominant_baseline (FoFo       *fo_fo);
void         fo_leader_set_dominant_baseline (FoFo       *fo_fo,
                                              FoProperty *new_dominant_baseline);
FoProperty * fo_leader_get_font_family (FoFo       *fo_fo);
void         fo_leader_set_font_family (FoFo       *fo_fo,
                                        FoProperty *new_font_family);
FoProperty * fo_leader_get_font_size (FoFo       *fo_fo);
void         fo_leader_set_font_size (FoFo       *fo_fo,
                                      FoProperty *new_font_size);
FoProperty * fo_leader_get_font_stretch (FoFo       *fo_fo);
void         fo_leader_set_font_stretch (FoFo       *fo_fo,
                                         FoProperty *new_font_stretch);
FoProperty * fo_leader_get_font_style (FoFo       *fo_fo);
void         fo_leader_set_font_style (FoFo       *fo_fo,
                                       FoProperty *new_font_style);
FoProperty * fo_leader_get_font_variant (FoFo       *fo_fo);
void         fo_leader_set_font_variant (FoFo       *fo_fo,
                                         FoProperty *new_font_variant);
FoProperty * fo_leader_get_font_weight (FoFo       *fo_fo);
void         fo_leader_set_font_weight (FoFo       *fo_fo,
                                        FoProperty *new_font_weight);
FoProperty * fo_leader_get_id (FoFo       *fo_fo);
void         fo_leader_set_id (FoFo       *fo_fo,
                               FoProperty *new_id);
FoProperty * fo_leader_get_keep_with_next (FoFo       *fo_fo);
void         fo_leader_set_keep_with_next (FoFo       *fo_fo,
                                           FoProperty *new_keep_with_next);
FoProperty * fo_leader_get_keep_with_next_within_column (FoFo       *fo_fo);
void         fo_leader_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                         FoProperty *new_keep_with_next_within_column);
FoProperty * fo_leader_get_keep_with_next_within_line (FoFo       *fo_fo);
void         fo_leader_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                       FoProperty *new_keep_with_next_within_line);
FoProperty * fo_leader_get_keep_with_next_within_page (FoFo       *fo_fo);
void         fo_leader_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                       FoProperty *new_keep_with_next_within_page);
FoProperty * fo_leader_get_keep_with_previous (FoFo       *fo_fo);
void         fo_leader_set_keep_with_previous (FoFo       *fo_fo,
                                               FoProperty *new_keep_with_previous);
FoProperty * fo_leader_get_keep_with_previous_within_column (FoFo       *fo_fo);
void         fo_leader_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                             FoProperty *new_keep_with_previous_within_column);
FoProperty * fo_leader_get_keep_with_previous_within_line (FoFo       *fo_fo);
void         fo_leader_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                           FoProperty *new_keep_with_previous_within_line);
FoProperty * fo_leader_get_keep_with_previous_within_page (FoFo       *fo_fo);
void         fo_leader_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                           FoProperty *new_keep_with_previous_within_page);
FoProperty * fo_leader_get_line_height (FoFo       *fo_fo);
void         fo_leader_set_line_height (FoFo       *fo_fo,
                                        FoProperty *new_line_height);
FoProperty * fo_leader_get_padding_after (FoFo       *fo_fo);
void         fo_leader_set_padding_after (FoFo       *fo_fo,
                                          FoProperty *new_padding_after);
FoProperty * fo_leader_get_padding_before (FoFo       *fo_fo);
void         fo_leader_set_padding_before (FoFo       *fo_fo,
                                           FoProperty *new_padding_before);
FoProperty * fo_leader_get_padding_bottom (FoFo       *fo_fo);
void         fo_leader_set_padding_bottom (FoFo       *fo_fo,
                                           FoProperty *new_padding_bottom);
FoProperty * fo_leader_get_padding_end (FoFo       *fo_fo);
void         fo_leader_set_padding_end (FoFo       *fo_fo,
                                        FoProperty *new_padding_end);
FoProperty * fo_leader_get_padding_left (FoFo       *fo_fo);
void         fo_leader_set_padding_left (FoFo       *fo_fo,
                                         FoProperty *new_padding_left);
FoProperty * fo_leader_get_padding_right (FoFo       *fo_fo);
void         fo_leader_set_padding_right (FoFo       *fo_fo,
                                          FoProperty *new_padding_right);
FoProperty * fo_leader_get_padding_start (FoFo       *fo_fo);
void         fo_leader_set_padding_start (FoFo       *fo_fo,
                                          FoProperty *new_padding_start);
FoProperty * fo_leader_get_padding_top (FoFo       *fo_fo);
void         fo_leader_set_padding_top (FoFo       *fo_fo,
                                        FoProperty *new_padding_top);
FoProperty * fo_leader_get_role (FoFo       *fo_fo);
void         fo_leader_set_role (FoFo       *fo_fo,
                                 FoProperty *new_role);
FoProperty * fo_leader_get_source_document (FoFo       *fo_fo);
void         fo_leader_set_source_document (FoFo       *fo_fo,
                                            FoProperty *new_source_document);
FoProperty * fo_leader_get_space_end (FoFo       *fo_fo);
void         fo_leader_set_space_end (FoFo       *fo_fo,
                                      FoProperty *new_space_end);
FoProperty * fo_leader_get_space_start (FoFo       *fo_fo);
void         fo_leader_set_space_start (FoFo       *fo_fo,
                                        FoProperty *new_space_start);

G_END_DECLS

#endif /* !__FO_LEADER_H__ */
