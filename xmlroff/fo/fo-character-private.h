/* Fo
 * fo-character-private.h: Structures private to 'character' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-character-private.h,v 1.5 2006/03/22 23:27:28 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_CHARACTER_PRIVATE_H__
#define __FO_CHARACTER_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-character.h"

G_BEGIN_DECLS

struct _FoCharacter
{
  FoFo parent_instance;

  FoProperty *alignment_adjust;
  FoProperty *alignment_baseline;
  FoProperty *background_color;
  FoProperty *background_image;
  FoProperty *baseline_shift;
  FoProperty *border_after_color;
  FoProperty *border_after_style;
  FoProperty *border_after_width;
  FoProperty *border_before_color;
  FoProperty *border_before_style;
  FoProperty *border_before_width;
  FoProperty *border_bottom_color;
  FoProperty *border_bottom_style;
  FoProperty *border_bottom_width;
  FoProperty *border_end_color;
  FoProperty *border_end_style;
  FoProperty *border_end_width;
  FoProperty *border_left_color;
  FoProperty *border_left_style;
  FoProperty *border_left_width;
  FoProperty *border_right_color;
  FoProperty *border_right_style;
  FoProperty *border_right_width;
  FoProperty *border_start_color;
  FoProperty *border_start_style;
  FoProperty *border_start_width;
  FoProperty *border_top_color;
  FoProperty *border_top_style;
  FoProperty *border_top_width;
  FoProperty *character;
  FoProperty *color;
  FoProperty *dominant_baseline;
  FoProperty *font_family;
  FoProperty *font_size;
  FoProperty *font_stretch;
  FoProperty *font_style;
  FoProperty *font_variant;
  FoProperty *font_weight;
  FoProperty *id;
  FoProperty *keep_with_next;
  FoProperty *keep_with_next_within_column;
  FoProperty *keep_with_next_within_line;
  FoProperty *keep_with_next_within_page;
  FoProperty *keep_with_previous;
  FoProperty *keep_with_previous_within_column;
  FoProperty *keep_with_previous_within_line;
  FoProperty *keep_with_previous_within_page;
  FoProperty *line_height;
  FoProperty *padding_after;
  FoProperty *padding_before;
  FoProperty *padding_bottom;
  FoProperty *padding_end;
  FoProperty *padding_left;
  FoProperty *padding_right;
  FoProperty *padding_start;
  FoProperty *padding_top;
  FoProperty *score_spaces;
  FoProperty *space_end;
  FoProperty *space_start;
};

struct _FoCharacterClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_CHARACTER_PRIVATE_H__ */
