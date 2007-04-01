/* Fo
 * fo-character.h: 'character' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-character.h,v 1.4 2004/03/30 22:45:41 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_CHARACTER_H__
#define __FO_CHARACTER_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

typedef struct _FoCharacter      FoCharacter;
typedef struct _FoCharacterClass FoCharacterClass;

#define FO_TYPE_CHARACTER              (fo_character_get_type ())
#define FO_CHARACTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_CHARACTER, FoCharacter))
#define FO_CHARACTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_CHARACTER, FoCharacterClass))
#define FO_IS_CHARACTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_CHARACTER))
#define FO_IS_CHARACTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_CHARACTER))
#define FO_CHARACTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_CHARACTER, FoCharacterClass))


GType         fo_character_get_type      (void) G_GNUC_CONST;
FoFo *fo_character_new (void);

FoProperty* fo_character_get_alignment_adjust (FoFo       *fo_fo);
void        fo_character_set_alignment_adjust (FoFo       *fo_fo,
                                               FoProperty *new_alignment_adjust);
FoProperty* fo_character_get_alignment_baseline (FoFo       *fo_fo);
void        fo_character_set_alignment_baseline (FoFo       *fo_fo,
                                                 FoProperty *new_alignment_baseline);
FoProperty * fo_character_get_background_color (FoFo       *fo_fo);
void         fo_character_set_background_color (FoFo       *fo_fo,
						FoProperty *new_background_color);
FoProperty* fo_character_get_background_image (FoFo       *fo_fo);
void        fo_character_set_background_image (FoFo       *fo_fo,
                                               FoProperty *new_background_image);
FoProperty* fo_character_get_baseline_shift (FoFo       *fo_fo);
void        fo_character_set_baseline_shift (FoFo       *fo_fo,
                                             FoProperty *new_baseline_shift);
FoProperty* fo_character_get_border_after_color (FoFo       *fo_fo);
void        fo_character_set_border_after_color (FoFo       *fo_fo,
                                                 FoProperty *new_border_after_color);
FoProperty* fo_character_get_border_after_style (FoFo       *fo_fo);
void        fo_character_set_border_after_style (FoFo       *fo_fo,
                                                 FoProperty *new_border_after_style);
FoProperty* fo_character_get_border_after_width (FoFo       *fo_fo);
void        fo_character_set_border_after_width (FoFo       *fo_fo,
                                                 FoProperty *new_border_after_width);
FoProperty* fo_character_get_border_before_color (FoFo       *fo_fo);
void        fo_character_set_border_before_color (FoFo       *fo_fo,
                                                  FoProperty *new_border_before_color);
FoProperty* fo_character_get_border_before_style (FoFo       *fo_fo);
void        fo_character_set_border_before_style (FoFo       *fo_fo,
                                                  FoProperty *new_border_before_style);
FoProperty* fo_character_get_border_before_width (FoFo       *fo_fo);
void        fo_character_set_border_before_width (FoFo       *fo_fo,
                                                  FoProperty *new_border_before_width);
FoProperty* fo_character_get_border_bottom_color (FoFo       *fo_fo);
void        fo_character_set_border_bottom_color (FoFo       *fo_fo,
                                                  FoProperty *new_border_bottom_color);
FoProperty* fo_character_get_border_bottom_style (FoFo       *fo_fo);
void        fo_character_set_border_bottom_style (FoFo       *fo_fo,
                                                  FoProperty *new_border_bottom_style);
FoProperty* fo_character_get_border_bottom_width (FoFo       *fo_fo);
void        fo_character_set_border_bottom_width (FoFo       *fo_fo,
                                                  FoProperty *new_border_bottom_width);
FoProperty* fo_character_get_border_end_color (FoFo       *fo_fo);
void        fo_character_set_border_end_color (FoFo       *fo_fo,
                                               FoProperty *new_border_end_color);
FoProperty* fo_character_get_border_end_style (FoFo       *fo_fo);
void        fo_character_set_border_end_style (FoFo       *fo_fo,
                                               FoProperty *new_border_end_style);
FoProperty* fo_character_get_border_end_width (FoFo       *fo_fo);
void        fo_character_set_border_end_width (FoFo       *fo_fo,
                                               FoProperty *new_border_end_width);
FoProperty* fo_character_get_border_left_color (FoFo       *fo_fo);
void        fo_character_set_border_left_color (FoFo       *fo_fo,
                                                FoProperty *new_border_left_color);
FoProperty* fo_character_get_border_left_style (FoFo       *fo_fo);
void        fo_character_set_border_left_style (FoFo       *fo_fo,
                                                FoProperty *new_border_left_style);
FoProperty* fo_character_get_border_left_width (FoFo       *fo_fo);
void        fo_character_set_border_left_width (FoFo       *fo_fo,
                                                FoProperty *new_border_left_width);
FoProperty* fo_character_get_border_right_color (FoFo       *fo_fo);
void        fo_character_set_border_right_color (FoFo       *fo_fo,
                                                 FoProperty *new_border_right_color);
FoProperty* fo_character_get_border_right_style (FoFo       *fo_fo);
void        fo_character_set_border_right_style (FoFo       *fo_fo,
                                                 FoProperty *new_border_right_style);
FoProperty* fo_character_get_border_right_width (FoFo       *fo_fo);
void        fo_character_set_border_right_width (FoFo       *fo_fo,
                                                 FoProperty *new_border_right_width);
FoProperty* fo_character_get_border_start_color (FoFo       *fo_fo);
void        fo_character_set_border_start_color (FoFo       *fo_fo,
                                                 FoProperty *new_border_start_color);
FoProperty* fo_character_get_border_start_style (FoFo       *fo_fo);
void        fo_character_set_border_start_style (FoFo       *fo_fo,
                                                 FoProperty *new_border_start_style);
FoProperty* fo_character_get_border_start_width (FoFo       *fo_fo);
void        fo_character_set_border_start_width (FoFo       *fo_fo,
                                                 FoProperty *new_border_start_width);
FoProperty* fo_character_get_border_top_color (FoFo       *fo_fo);
void        fo_character_set_border_top_color (FoFo       *fo_fo,
                                               FoProperty *new_border_top_color);
FoProperty* fo_character_get_border_top_style (FoFo       *fo_fo);
void        fo_character_set_border_top_style (FoFo       *fo_fo,
                                               FoProperty *new_border_top_style);
FoProperty* fo_character_get_border_top_width (FoFo       *fo_fo);
void        fo_character_set_border_top_width (FoFo       *fo_fo,
                                               FoProperty *new_border_top_width);
FoProperty* fo_character_get_character (FoFo       *fo_fo);
void        fo_character_set_character (FoFo       *fo_fo,
                                        FoProperty *new_character);
FoProperty* fo_character_get_color (FoFo       *fo_fo);
void        fo_character_set_color (FoFo       *fo_fo,
                                    FoProperty *new_color);
FoProperty* fo_character_get_dominant_baseline (FoFo       *fo_fo);
void        fo_character_set_dominant_baseline (FoFo       *fo_fo,
                                                FoProperty *new_dominant_baseline);
FoProperty* fo_character_get_font_family (FoFo       *fo_fo);
void        fo_character_set_font_family (FoFo       *fo_fo,
                                          FoProperty *new_font_family);
FoProperty* fo_character_get_font_size (FoFo       *fo_fo);
void        fo_character_set_font_size (FoFo       *fo_fo,
                                        FoProperty *new_font_size);
FoProperty* fo_character_get_font_stretch (FoFo       *fo_fo);
void        fo_character_set_font_stretch (FoFo       *fo_fo,
                                           FoProperty *new_font_stretch);
FoProperty* fo_character_get_font_style (FoFo       *fo_fo);
void        fo_character_set_font_style (FoFo       *fo_fo,
                                         FoProperty *new_font_style);
FoProperty* fo_character_get_font_variant (FoFo       *fo_fo);
void        fo_character_set_font_variant (FoFo       *fo_fo,
                                           FoProperty *new_font_variant);
FoProperty* fo_character_get_font_weight (FoFo       *fo_fo);
void        fo_character_set_font_weight (FoFo       *fo_fo,
                                          FoProperty *new_font_weight);
FoProperty* fo_character_get_id (FoFo       *fo_fo);
void        fo_character_set_id (FoFo       *fo_fo,
                                 FoProperty *new_id);
FoProperty* fo_character_get_keep_with_next (FoFo       *fo_fo);
void        fo_character_set_keep_with_next (FoFo       *fo_fo,
                                             FoProperty *new_keep_with_next);
FoProperty* fo_character_get_keep_with_next_within_column (FoFo       *fo_fo);
void        fo_character_set_keep_with_next_within_column (FoFo       *fo_fo,
                                                           FoProperty *new_keep_with_next_within_column);
FoProperty* fo_character_get_keep_with_next_within_line (FoFo       *fo_fo);
void        fo_character_set_keep_with_next_within_line (FoFo       *fo_fo,
                                                         FoProperty *new_keep_with_next_within_line);
FoProperty* fo_character_get_keep_with_next_within_page (FoFo       *fo_fo);
void        fo_character_set_keep_with_next_within_page (FoFo       *fo_fo,
                                                         FoProperty *new_keep_with_next_within_page);
FoProperty* fo_character_get_keep_with_previous (FoFo       *fo_fo);
void        fo_character_set_keep_with_previous (FoFo       *fo_fo,
                                                 FoProperty *new_keep_with_previous);
FoProperty* fo_character_get_keep_with_previous_within_column (FoFo       *fo_fo);
void        fo_character_set_keep_with_previous_within_column (FoFo       *fo_fo,
                                                               FoProperty *new_keep_with_previous_within_column);
FoProperty* fo_character_get_keep_with_previous_within_line (FoFo       *fo_fo);
void        fo_character_set_keep_with_previous_within_line (FoFo       *fo_fo,
                                                             FoProperty *new_keep_with_previous_within_line);
FoProperty* fo_character_get_keep_with_previous_within_page (FoFo       *fo_fo);
void        fo_character_set_keep_with_previous_within_page (FoFo       *fo_fo,
                                                             FoProperty *new_keep_with_previous_within_page);
FoProperty* fo_character_get_line_height (FoFo       *fo_fo);
void        fo_character_set_line_height (FoFo       *fo_fo,
                                          FoProperty *new_line_height);
FoProperty* fo_character_get_padding_after (FoFo       *fo_fo);
void        fo_character_set_padding_after (FoFo       *fo_fo,
                                            FoProperty *new_padding_after);
FoProperty* fo_character_get_padding_before (FoFo       *fo_fo);
void        fo_character_set_padding_before (FoFo       *fo_fo,
                                             FoProperty *new_padding_before);
FoProperty* fo_character_get_padding_bottom (FoFo       *fo_fo);
void        fo_character_set_padding_bottom (FoFo       *fo_fo,
                                             FoProperty *new_padding_bottom);
FoProperty* fo_character_get_padding_end (FoFo       *fo_fo);
void        fo_character_set_padding_end (FoFo       *fo_fo,
                                          FoProperty *new_padding_end);
FoProperty* fo_character_get_padding_left (FoFo       *fo_fo);
void        fo_character_set_padding_left (FoFo       *fo_fo,
                                           FoProperty *new_padding_left);
FoProperty* fo_character_get_padding_right (FoFo       *fo_fo);
void        fo_character_set_padding_right (FoFo       *fo_fo,
                                            FoProperty *new_padding_right);
FoProperty* fo_character_get_padding_start (FoFo       *fo_fo);
void        fo_character_set_padding_start (FoFo       *fo_fo,
                                            FoProperty *new_padding_start);
FoProperty* fo_character_get_padding_top (FoFo       *fo_fo);
void        fo_character_set_padding_top (FoFo       *fo_fo,
                                          FoProperty *new_padding_top);
FoProperty* fo_character_get_score_spaces (FoFo       *fo_fo);
void        fo_character_set_score_spaces (FoFo       *fo_fo,
                                           FoProperty *new_score_spaces);
FoProperty* fo_character_get_space_end (FoFo       *fo_fo);
void        fo_character_set_space_end (FoFo       *fo_fo,
                                        FoProperty *new_space_end);
FoProperty* fo_character_get_space_start (FoFo       *fo_fo);
void        fo_character_set_space_start (FoFo       *fo_fo,
                                          FoProperty *new_space_start);

G_END_DECLS

#endif /* !__FO_CHARACTER_H__ */
