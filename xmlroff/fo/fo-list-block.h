/* Fo
 * fo-list_block.h: 'list-block' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-list-block.h,v 1.4 2004/03/30 22:45:41 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LIST_BLOCK_H__
#define __FO_LIST_BLOCK_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

typedef struct _FoListBlock      FoListBlock;
typedef struct _FoListBlockClass FoListBlockClass;

#define FO_TYPE_LIST_BLOCK              (fo_list_block_get_type ())
#define FO_LIST_BLOCK(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LIST_BLOCK, FoListBlock))
#define FO_LIST_BLOCK_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LIST_BLOCK, FoListBlockClass))
#define FO_IS_LIST_BLOCK(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LIST_BLOCK))
#define FO_IS_LIST_BLOCK_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LIST_BLOCK))
#define FO_LIST_BLOCK_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LIST_BLOCK, FoListBlockClass))


GType        fo_list_block_get_type      (void) G_GNUC_CONST;
FoFo *       fo_list_block_new (void);

FoDatatype * fo_list_block_get_body_start (FoFo       *fo_fo);
FoDatatype * fo_list_block_get_label_end (FoFo       *fo_fo);

FoProperty  * fo_list_block_get_background_color (FoFo       *fo_fo);
void          fo_list_block_set_background_color (FoFo       *fo_fo,
						  FoProperty *new_background_color);
FoProperty * fo_list_block_get_background_image (FoFo       *fo_fo);
void         fo_list_block_set_background_image (FoFo       *fo_fo,
                                                 FoProperty *new_background_image);
FoProperty * fo_list_block_get_border_after_color (FoFo       *fo_fo);
void         fo_list_block_set_border_after_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_after_color);
FoProperty * fo_list_block_get_border_after_style (FoFo       *fo_fo);
void         fo_list_block_set_border_after_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_after_style);
FoProperty * fo_list_block_get_border_after_width (FoFo       *fo_fo);
void         fo_list_block_set_border_after_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_after_width);
FoProperty * fo_list_block_get_border_before_color (FoFo       *fo_fo);
void         fo_list_block_set_border_before_color (FoFo       *fo_fo,
                                                    FoProperty *new_border_before_color);
FoProperty * fo_list_block_get_border_before_style (FoFo       *fo_fo);
void         fo_list_block_set_border_before_style (FoFo       *fo_fo,
                                                    FoProperty *new_border_before_style);
FoProperty * fo_list_block_get_border_before_width (FoFo       *fo_fo);
void         fo_list_block_set_border_before_width (FoFo       *fo_fo,
                                                    FoProperty *new_border_before_width);
FoProperty * fo_list_block_get_border_bottom_color (FoFo       *fo_fo);
void         fo_list_block_set_border_bottom_color (FoFo       *fo_fo,
                                                    FoProperty *new_border_bottom_color);
FoProperty * fo_list_block_get_border_bottom_style (FoFo       *fo_fo);
void         fo_list_block_set_border_bottom_style (FoFo       *fo_fo,
                                                    FoProperty *new_border_bottom_style);
FoProperty * fo_list_block_get_border_bottom_width (FoFo       *fo_fo);
void         fo_list_block_set_border_bottom_width (FoFo       *fo_fo,
                                                    FoProperty *new_border_bottom_width);
FoProperty * fo_list_block_get_border_end_color (FoFo       *fo_fo);
void         fo_list_block_set_border_end_color (FoFo       *fo_fo,
                                                 FoProperty *new_border_end_color);
FoProperty * fo_list_block_get_border_end_style (FoFo       *fo_fo);
void         fo_list_block_set_border_end_style (FoFo       *fo_fo,
                                                 FoProperty *new_border_end_style);
FoProperty * fo_list_block_get_border_end_width (FoFo       *fo_fo);
void         fo_list_block_set_border_end_width (FoFo       *fo_fo,
                                                 FoProperty *new_border_end_width);
FoProperty * fo_list_block_get_border_left_color (FoFo       *fo_fo);
void         fo_list_block_set_border_left_color (FoFo       *fo_fo,
                                                  FoProperty *new_border_left_color);
FoProperty * fo_list_block_get_border_left_style (FoFo       *fo_fo);
void         fo_list_block_set_border_left_style (FoFo       *fo_fo,
                                                  FoProperty *new_border_left_style);
FoProperty * fo_list_block_get_border_left_width (FoFo       *fo_fo);
void         fo_list_block_set_border_left_width (FoFo       *fo_fo,
                                                  FoProperty *new_border_left_width);
FoProperty * fo_list_block_get_border_right_color (FoFo       *fo_fo);
void         fo_list_block_set_border_right_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_right_color);
FoProperty * fo_list_block_get_border_right_style (FoFo       *fo_fo);
void         fo_list_block_set_border_right_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_right_style);
FoProperty * fo_list_block_get_border_right_width (FoFo       *fo_fo);
void         fo_list_block_set_border_right_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_right_width);
FoProperty * fo_list_block_get_border_start_color (FoFo       *fo_fo);
void         fo_list_block_set_border_start_color (FoFo       *fo_fo,
                                                   FoProperty *new_border_start_color);
FoProperty * fo_list_block_get_border_start_style (FoFo       *fo_fo);
void         fo_list_block_set_border_start_style (FoFo       *fo_fo,
                                                   FoProperty *new_border_start_style);
FoProperty * fo_list_block_get_border_start_width (FoFo       *fo_fo);
void         fo_list_block_set_border_start_width (FoFo       *fo_fo,
                                                   FoProperty *new_border_start_width);
FoProperty * fo_list_block_get_border_top_color (FoFo       *fo_fo);
void         fo_list_block_set_border_top_color (FoFo       *fo_fo,
                                                 FoProperty *new_border_top_color);
FoProperty * fo_list_block_get_border_top_style (FoFo       *fo_fo);
void         fo_list_block_set_border_top_style (FoFo       *fo_fo,
                                                 FoProperty *new_border_top_style);
FoProperty * fo_list_block_get_border_top_width (FoFo       *fo_fo);
void         fo_list_block_set_border_top_width (FoFo       *fo_fo,
                                                 FoProperty *new_border_top_width);
FoProperty * fo_list_block_get_break_after (FoFo       *fo_fo);
void         fo_list_block_set_break_after (FoFo       *fo_fo,
                                            FoProperty *new_break_after);
FoProperty * fo_list_block_get_break_before (FoFo       *fo_fo);
void         fo_list_block_set_break_before (FoFo       *fo_fo,
                                             FoProperty *new_break_before);
FoProperty * fo_list_block_get_end_indent (FoFo       *fo_fo);
void         fo_list_block_set_end_indent (FoFo       *fo_fo,
                                           FoProperty *new_end_indent);
FoProperty * fo_list_block_get_id (FoFo       *fo_fo);
void         fo_list_block_set_id (FoFo       *fo_fo,
                                   FoProperty *new_id);
FoProperty * fo_list_block_get_keep_together (FoFo       *fo_fo);
void         fo_list_block_set_keep_together (FoFo       *fo_fo,
                                              FoProperty *new_keep_together);
FoProperty * fo_list_block_get_keep_together_within_column (FoFo       *fo_fo);
void         fo_list_block_set_keep_together_within_column (FoFo       *fo_fo,
                                                            FoProperty *new_keep_together_within_column);
FoProperty * fo_list_block_get_keep_together_within_line (FoFo       *fo_fo);
void         fo_list_block_set_keep_together_within_line (FoFo       *fo_fo,
                                                          FoProperty *new_keep_together_within_line);
FoProperty * fo_list_block_get_keep_together_within_page (FoFo       *fo_fo);
void         fo_list_block_set_keep_together_within_page (FoFo       *fo_fo,
                                                          FoProperty *new_keep_together_within_page);
FoProperty * fo_list_block_get_keep_with_next (FoFo       *fo_fo);
void         fo_list_block_set_keep_with_next (FoFo       *fo_fo,
                                               FoProperty *new_keep_with_next);
FoProperty * fo_list_block_get_keep_with_next_within_column (FoFo       *fo_fo);
void         fo_list_block_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                             FoProperty *new_keep_with_next_within_column);
FoProperty * fo_list_block_get_keep_with_next_within_line (FoFo       *fo_fo);
void         fo_list_block_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                           FoProperty *new_keep_with_next_within_line);
FoProperty * fo_list_block_get_keep_with_next_within_page (FoFo       *fo_fo);
void         fo_list_block_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                           FoProperty *new_keep_with_next_within_page);
FoProperty * fo_list_block_get_keep_with_previous (FoFo       *fo_fo);
void         fo_list_block_set_keep_with_previous (FoFo       *fo_fo,
                                                   FoProperty *new_keep_with_previous);
FoProperty * fo_list_block_get_keep_with_previous_within_column (FoFo       *fo_fo);
void         fo_list_block_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                                 FoProperty *new_keep_with_previous_within_column);
FoProperty * fo_list_block_get_keep_with_previous_within_line (FoFo       *fo_fo);
void         fo_list_block_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                               FoProperty *new_keep_with_previous_within_line);
FoProperty * fo_list_block_get_keep_with_previous_within_page (FoFo       *fo_fo);
void         fo_list_block_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                               FoProperty *new_keep_with_previous_within_page);
FoProperty * fo_list_block_get_margin_bottom (FoFo       *fo_fo);
void         fo_list_block_set_margin_bottom (FoFo       *fo_fo,
                                              FoProperty *new_margin_bottom);
FoProperty * fo_list_block_get_margin_left (FoFo       *fo_fo);
void         fo_list_block_set_margin_left (FoFo       *fo_fo,
                                            FoProperty *new_margin_left);
FoProperty * fo_list_block_get_margin_right (FoFo       *fo_fo);
void         fo_list_block_set_margin_right (FoFo       *fo_fo,
                                             FoProperty *new_margin_right);
FoProperty * fo_list_block_get_margin_top (FoFo       *fo_fo);
void         fo_list_block_set_margin_top (FoFo       *fo_fo,
                                           FoProperty *new_margin_top);
FoProperty * fo_list_block_get_padding_after (FoFo       *fo_fo);
void         fo_list_block_set_padding_after (FoFo       *fo_fo,
                                              FoProperty *new_padding_after);
FoProperty * fo_list_block_get_padding_before (FoFo       *fo_fo);
void         fo_list_block_set_padding_before (FoFo       *fo_fo,
                                               FoProperty *new_padding_before);
FoProperty * fo_list_block_get_padding_bottom (FoFo       *fo_fo);
void         fo_list_block_set_padding_bottom (FoFo       *fo_fo,
                                               FoProperty *new_padding_bottom);
FoProperty * fo_list_block_get_padding_end (FoFo       *fo_fo);
void         fo_list_block_set_padding_end (FoFo       *fo_fo,
                                            FoProperty *new_padding_end);
FoProperty * fo_list_block_get_padding_left (FoFo       *fo_fo);
void         fo_list_block_set_padding_left (FoFo       *fo_fo,
                                             FoProperty *new_padding_left);
FoProperty * fo_list_block_get_padding_right (FoFo       *fo_fo);
void         fo_list_block_set_padding_right (FoFo       *fo_fo,
                                              FoProperty *new_padding_right);
FoProperty * fo_list_block_get_padding_start (FoFo       *fo_fo);
void         fo_list_block_set_padding_start (FoFo       *fo_fo,
                                              FoProperty *new_padding_start);
FoProperty * fo_list_block_get_padding_top (FoFo       *fo_fo);
void         fo_list_block_set_padding_top (FoFo       *fo_fo,
                                            FoProperty *new_padding_top);
FoProperty * fo_list_block_get_provisional_distance_between_starts (FoFo       *fo_fo);
void         fo_list_block_set_provisional_distance_between_starts (FoFo       *fo_fo,
                                                                    FoProperty *new_provisional_distance_between_starts);
FoProperty * fo_list_block_get_provisional_label_separation (FoFo       *fo_fo);
void         fo_list_block_set_provisional_label_separation (FoFo       *fo_fo,
                                                             FoProperty *new_provisional_label_separation);
FoProperty * fo_list_block_get_role (FoFo       *fo_fo);
void         fo_list_block_set_role (FoFo       *fo_fo,
                                     FoProperty *new_role);
FoProperty * fo_list_block_get_source_document (FoFo       *fo_fo);
void         fo_list_block_set_source_document (FoFo       *fo_fo,
                                                FoProperty *new_source_document);
FoProperty * fo_list_block_get_space_after (FoFo       *fo_fo);
void         fo_list_block_set_space_after (FoFo       *fo_fo,
                                            FoProperty *new_space_after);
FoProperty * fo_list_block_get_space_before (FoFo       *fo_fo);
void         fo_list_block_set_space_before (FoFo       *fo_fo,
                                             FoProperty *new_space_before);
FoProperty * fo_list_block_get_start_indent (FoFo       *fo_fo);
void         fo_list_block_set_start_indent (FoFo       *fo_fo,
                                             FoProperty *new_start_indent);

G_END_DECLS

#endif /* !__FO_LIST_BLOCK_H__ */
