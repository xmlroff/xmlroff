/* Fo
 * fo-basic-link-private.h: Structures private to 'basic-link' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_BASIC_LINK_PRIVATE_H__
#define __FO_BASIC_LINK_PRIVATE_H__

#include "fo/fo-marker-parent-private.h"
#include "fo/fo-basic-link.h"

G_BEGIN_DECLS

struct _FoBasicLink
{
  FoMarkerParent parent_instance;

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
  FoProperty *dominant_baseline;
  FoProperty *id;
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
  FoProperty *line_height;
  FoProperty *padding_after;
  FoProperty *padding_before;
  FoProperty *padding_bottom;
  FoProperty *padding_end;
  FoProperty *padding_left;
  FoProperty *padding_right;
  FoProperty *padding_start;
  FoProperty *padding_top;
  FoProperty *role;
  FoProperty *source_document;
  FoProperty *space_end;
  FoProperty *space_start;
};

struct _FoBasicLinkClass
{
  FoMarkerParentClass parent_class;
};

G_END_DECLS

#endif /* !__FO_BASIC_LINK_PRIVATE_H__ */
