/* Fo
 * fo-block-container.h: 'block-container' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-block-container.h,v 1.4 2006/03/21 23:27:37 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_BLOCK_CONTAINER_H__
#define __FO_BLOCK_CONTAINER_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoBlockContainer:
 *
 * Instance of the 'block-container' formatting object.
 **/
typedef struct _FoBlockContainer      FoBlockContainer;

/**
 * FoBlockContainerClass:
 *
 * Class structure for the 'block-container' formatting object.
 **/
typedef struct _FoBlockContainerClass FoBlockContainerClass;

#define FO_TYPE_BLOCK_CONTAINER              (fo_block_container_get_type ())
#define FO_BLOCK_CONTAINER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_BLOCK_CONTAINER, FoBlockContainer))
#define FO_BLOCK_CONTAINER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_BLOCK_CONTAINER, FoBlockContainerClass))
#define FO_IS_BLOCK_CONTAINER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_BLOCK_CONTAINER))
#define FO_IS_BLOCK_CONTAINER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_BLOCK_CONTAINER))
#define FO_BLOCK_CONTAINER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_BLOCK_CONTAINER, FoBlockContainerClass))


GType        fo_block_container_get_type (void) G_GNUC_CONST;
FoFo *       fo_block_container_new      (void);

FoProperty * fo_block_container_get_background_color (FoFo       *fo_fo);
void         fo_block_container_set_background_color (FoFo       *fo_fo,
                                                      FoProperty *new_background_color);
FoProperty * fo_block_container_get_background_image (FoFo       *fo_fo);
void         fo_block_container_set_background_image (FoFo       *fo_fo,
                                                      FoProperty *new_background_image);
FoProperty * fo_block_container_get_block_progression_dimension (FoFo       *fo_fo);
void         fo_block_container_set_block_progression_dimension (FoFo       *fo_fo,
                                                                 FoProperty *new_block_progression_dimension);
FoProperty * fo_block_container_get_border_after_color (FoFo       *fo_fo);
void         fo_block_container_set_border_after_color (FoFo       *fo_fo,
                                                        FoProperty *new_border_after_color);
FoProperty * fo_block_container_get_border_after_style (FoFo       *fo_fo);
void         fo_block_container_set_border_after_style (FoFo       *fo_fo,
                                                        FoProperty *new_border_after_style);
FoProperty * fo_block_container_get_border_after_width (FoFo       *fo_fo);
void         fo_block_container_set_border_after_width (FoFo       *fo_fo,
                                                        FoProperty *new_border_after_width);
FoProperty * fo_block_container_get_border_before_color (FoFo       *fo_fo);
void         fo_block_container_set_border_before_color (FoFo       *fo_fo,
                                                         FoProperty *new_border_before_color);
FoProperty * fo_block_container_get_border_before_style (FoFo       *fo_fo);
void         fo_block_container_set_border_before_style (FoFo       *fo_fo,
                                                         FoProperty *new_border_before_style);
FoProperty * fo_block_container_get_border_before_width (FoFo       *fo_fo);
void         fo_block_container_set_border_before_width (FoFo       *fo_fo,
                                                         FoProperty *new_border_before_width);
FoProperty * fo_block_container_get_border_bottom_color (FoFo       *fo_fo);
void         fo_block_container_set_border_bottom_color (FoFo       *fo_fo,
                                                         FoProperty *new_border_bottom_color);
FoProperty * fo_block_container_get_border_bottom_style (FoFo       *fo_fo);
void         fo_block_container_set_border_bottom_style (FoFo       *fo_fo,
                                                         FoProperty *new_border_bottom_style);
FoProperty * fo_block_container_get_border_bottom_width (FoFo       *fo_fo);
void         fo_block_container_set_border_bottom_width (FoFo       *fo_fo,
                                                         FoProperty *new_border_bottom_width);
FoProperty * fo_block_container_get_border_end_color (FoFo       *fo_fo);
void         fo_block_container_set_border_end_color (FoFo       *fo_fo,
                                                      FoProperty *new_border_end_color);
FoProperty * fo_block_container_get_border_end_style (FoFo       *fo_fo);
void         fo_block_container_set_border_end_style (FoFo       *fo_fo,
                                                      FoProperty *new_border_end_style);
FoProperty * fo_block_container_get_border_end_width (FoFo       *fo_fo);
void         fo_block_container_set_border_end_width (FoFo       *fo_fo,
                                                      FoProperty *new_border_end_width);
FoProperty * fo_block_container_get_border_left_color (FoFo       *fo_fo);
void         fo_block_container_set_border_left_color (FoFo       *fo_fo,
                                                       FoProperty *new_border_left_color);
FoProperty * fo_block_container_get_border_left_style (FoFo       *fo_fo);
void         fo_block_container_set_border_left_style (FoFo       *fo_fo,
                                                       FoProperty *new_border_left_style);
FoProperty * fo_block_container_get_border_left_width (FoFo       *fo_fo);
void         fo_block_container_set_border_left_width (FoFo       *fo_fo,
                                                       FoProperty *new_border_left_width);
FoProperty * fo_block_container_get_border_right_color (FoFo       *fo_fo);
void         fo_block_container_set_border_right_color (FoFo       *fo_fo,
                                                        FoProperty *new_border_right_color);
FoProperty * fo_block_container_get_border_right_style (FoFo       *fo_fo);
void         fo_block_container_set_border_right_style (FoFo       *fo_fo,
                                                        FoProperty *new_border_right_style);
FoProperty * fo_block_container_get_border_right_width (FoFo       *fo_fo);
void         fo_block_container_set_border_right_width (FoFo       *fo_fo,
                                                        FoProperty *new_border_right_width);
FoProperty * fo_block_container_get_border_start_color (FoFo       *fo_fo);
void         fo_block_container_set_border_start_color (FoFo       *fo_fo,
                                                        FoProperty *new_border_start_color);
FoProperty * fo_block_container_get_border_start_style (FoFo       *fo_fo);
void         fo_block_container_set_border_start_style (FoFo       *fo_fo,
                                                        FoProperty *new_border_start_style);
FoProperty * fo_block_container_get_border_start_width (FoFo       *fo_fo);
void         fo_block_container_set_border_start_width (FoFo       *fo_fo,
                                                        FoProperty *new_border_start_width);
FoProperty * fo_block_container_get_border_top_color (FoFo       *fo_fo);
void         fo_block_container_set_border_top_color (FoFo       *fo_fo,
                                                      FoProperty *new_border_top_color);
FoProperty * fo_block_container_get_border_top_style (FoFo       *fo_fo);
void         fo_block_container_set_border_top_style (FoFo       *fo_fo,
                                                      FoProperty *new_border_top_style);
FoProperty * fo_block_container_get_border_top_width (FoFo       *fo_fo);
void         fo_block_container_set_border_top_width (FoFo       *fo_fo,
                                                      FoProperty *new_border_top_width);
FoProperty * fo_block_container_get_break_after (FoFo       *fo_fo);
void         fo_block_container_set_break_after (FoFo       *fo_fo,
                                                 FoProperty *new_break_after);
FoProperty * fo_block_container_get_break_before (FoFo       *fo_fo);
void         fo_block_container_set_break_before (FoFo       *fo_fo,
                                                  FoProperty *new_break_before);
FoProperty * fo_block_container_get_clip (FoFo       *fo_fo);
void         fo_block_container_set_clip (FoFo       *fo_fo,
                                          FoProperty *new_clip);
FoProperty * fo_block_container_get_display_align (FoFo       *fo_fo);
void         fo_block_container_set_display_align (FoFo       *fo_fo,
                                                   FoProperty *new_display_align);
FoProperty * fo_block_container_get_end_indent (FoFo       *fo_fo);
void         fo_block_container_set_end_indent (FoFo       *fo_fo,
                                                FoProperty *new_end_indent);
FoProperty * fo_block_container_get_height (FoFo       *fo_fo);
void         fo_block_container_set_height (FoFo       *fo_fo,
                                            FoProperty *new_height);
FoProperty * fo_block_container_get_id (FoFo       *fo_fo);
void         fo_block_container_set_id (FoFo       *fo_fo,
                                        FoProperty *new_id);
FoProperty * fo_block_container_get_inline_progression_dimension (FoFo       *fo_fo);
void         fo_block_container_set_inline_progression_dimension (FoFo       *fo_fo,
                                                                  FoProperty *new_inline_progression_dimension);
FoProperty * fo_block_container_get_keep_together (FoFo       *fo_fo);
void         fo_block_container_set_keep_together (FoFo       *fo_fo,
                                                   FoProperty *new_keep_together);
FoProperty * fo_block_container_get_keep_together_within_column (FoFo       *fo_fo);
void         fo_block_container_set_keep_together_within_column (FoFo       *fo_fo,
                                                                 FoProperty *new_keep_together_within_column);
FoProperty * fo_block_container_get_keep_together_within_line (FoFo       *fo_fo);
void         fo_block_container_set_keep_together_within_line (FoFo       *fo_fo,
                                                               FoProperty *new_keep_together_within_line);
FoProperty * fo_block_container_get_keep_together_within_page (FoFo       *fo_fo);
void         fo_block_container_set_keep_together_within_page (FoFo       *fo_fo,
                                                               FoProperty *new_keep_together_within_page);
FoProperty * fo_block_container_get_keep_with_next (FoFo       *fo_fo);
void         fo_block_container_set_keep_with_next (FoFo       *fo_fo,
                                                    FoProperty *new_keep_with_next);
FoProperty * fo_block_container_get_keep_with_next_within_column (FoFo       *fo_fo);
void         fo_block_container_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                                  FoProperty *new_keep_with_next_within_column);
FoProperty * fo_block_container_get_keep_with_next_within_line (FoFo       *fo_fo);
void         fo_block_container_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                                FoProperty *new_keep_with_next_within_line);
FoProperty * fo_block_container_get_keep_with_next_within_page (FoFo       *fo_fo);
void         fo_block_container_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                                FoProperty *new_keep_with_next_within_page);
FoProperty * fo_block_container_get_keep_with_previous (FoFo       *fo_fo);
void         fo_block_container_set_keep_with_previous (FoFo       *fo_fo,
                                                        FoProperty *new_keep_with_previous);
FoProperty * fo_block_container_get_keep_with_previous_within_column (FoFo       *fo_fo);
void         fo_block_container_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                                      FoProperty *new_keep_with_previous_within_column);
FoProperty * fo_block_container_get_keep_with_previous_within_line (FoFo       *fo_fo);
void         fo_block_container_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                                    FoProperty *new_keep_with_previous_within_line);
FoProperty * fo_block_container_get_keep_with_previous_within_page (FoFo       *fo_fo);
void         fo_block_container_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                                    FoProperty *new_keep_with_previous_within_page);
FoProperty * fo_block_container_get_margin_bottom (FoFo       *fo_fo);
void         fo_block_container_set_margin_bottom (FoFo       *fo_fo,
                                                   FoProperty *new_margin_bottom);
FoProperty * fo_block_container_get_margin_left (FoFo       *fo_fo);
void         fo_block_container_set_margin_left (FoFo       *fo_fo,
                                                 FoProperty *new_margin_left);
FoProperty * fo_block_container_get_margin_right (FoFo       *fo_fo);
void         fo_block_container_set_margin_right (FoFo       *fo_fo,
                                                  FoProperty *new_margin_right);
FoProperty * fo_block_container_get_margin_top (FoFo       *fo_fo);
void         fo_block_container_set_margin_top (FoFo       *fo_fo,
                                                FoProperty *new_margin_top);
FoProperty * fo_block_container_get_overflow (FoFo       *fo_fo);
void         fo_block_container_set_overflow (FoFo       *fo_fo,
                                              FoProperty *new_overflow);
FoProperty * fo_block_container_get_padding_after (FoFo       *fo_fo);
void         fo_block_container_set_padding_after (FoFo       *fo_fo,
                                                   FoProperty *new_padding_after);
FoProperty * fo_block_container_get_padding_before (FoFo       *fo_fo);
void         fo_block_container_set_padding_before (FoFo       *fo_fo,
                                                    FoProperty *new_padding_before);
FoProperty * fo_block_container_get_padding_bottom (FoFo       *fo_fo);
void         fo_block_container_set_padding_bottom (FoFo       *fo_fo,
                                                    FoProperty *new_padding_bottom);
FoProperty * fo_block_container_get_padding_end (FoFo       *fo_fo);
void         fo_block_container_set_padding_end (FoFo       *fo_fo,
                                                 FoProperty *new_padding_end);
FoProperty * fo_block_container_get_padding_left (FoFo       *fo_fo);
void         fo_block_container_set_padding_left (FoFo       *fo_fo,
                                                  FoProperty *new_padding_left);
FoProperty * fo_block_container_get_padding_right (FoFo       *fo_fo);
void         fo_block_container_set_padding_right (FoFo       *fo_fo,
                                                   FoProperty *new_padding_right);
FoProperty * fo_block_container_get_padding_start (FoFo       *fo_fo);
void         fo_block_container_set_padding_start (FoFo       *fo_fo,
                                                   FoProperty *new_padding_start);
FoProperty * fo_block_container_get_padding_top (FoFo       *fo_fo);
void         fo_block_container_set_padding_top (FoFo       *fo_fo,
                                                 FoProperty *new_padding_top);
FoProperty * fo_block_container_get_space_after (FoFo       *fo_fo);
void         fo_block_container_set_space_after (FoFo       *fo_fo,
                                                 FoProperty *new_space_after);
FoProperty * fo_block_container_get_space_before (FoFo       *fo_fo);
void         fo_block_container_set_space_before (FoFo       *fo_fo,
                                                  FoProperty *new_space_before);
FoProperty * fo_block_container_get_span (FoFo       *fo_fo);
void         fo_block_container_set_span (FoFo       *fo_fo,
                                          FoProperty *new_span);
FoProperty * fo_block_container_get_start_indent (FoFo       *fo_fo);
void         fo_block_container_set_start_indent (FoFo       *fo_fo,
                                                  FoProperty *new_start_indent);
FoProperty * fo_block_container_get_width (FoFo       *fo_fo);
void         fo_block_container_set_width (FoFo       *fo_fo,
                                           FoProperty *new_width);
FoProperty * fo_block_container_get_writing_mode (FoFo       *fo_fo);
void         fo_block_container_set_writing_mode (FoFo       *fo_fo,
                                                  FoProperty *new_writing_mode);

G_END_DECLS

#endif /* !__FO_BLOCK_CONTAINER_H__ */
