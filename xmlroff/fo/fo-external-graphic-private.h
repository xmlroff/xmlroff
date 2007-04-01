/* Fo
 * fo-external-graphic-private.h: Structures private to 'external-graphic' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-external-graphic-private.h,v 1.9 2006/03/28 10:52:38 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_EXTERNAL_GRAPHIC_PRIVATE_H__
#define __FO_EXTERNAL_GRAPHIC_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-external-graphic.h"
#include "util/fo-image.h"

G_BEGIN_DECLS

struct _FoExternalGraphic
{
  FoFo        parent_instance;

  gchar      *base_uri;

  FoDoc      *fo_doc;
  FoImage    *fo_image;
  gdouble     area_width;
  gdouble     area_height;

  FoProperty *alignment_adjust;
  FoProperty *alignment_baseline;
  FoProperty *background_color;
  FoProperty *background_image;
  FoProperty *baseline_shift;
  FoProperty *block_progression_dimension;
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
  FoProperty *clip;
  FoProperty *content_height;
  FoProperty *content_type;
  FoProperty *content_width;
  FoProperty *display_align;
  FoProperty *dominant_baseline;
  FoProperty *height;
  FoProperty *id;
  FoProperty *inline_progression_dimension;
  FoProperty *keep_with_next;
  FoProperty *keep_with_next_within_column;
  FoProperty *keep_with_next_within_line;
  FoProperty *keep_with_next_within_page;
  FoProperty *keep_with_previous;
  FoProperty *keep_with_previous_within_column;
  FoProperty *keep_with_previous_within_line;
  FoProperty *keep_with_previous_within_page;
  FoProperty *line_height;
  FoProperty *overflow;
  FoProperty *padding_after;
  FoProperty *padding_before;
  FoProperty *padding_bottom;
  FoProperty *padding_end;
  FoProperty *padding_left;
  FoProperty *padding_right;
  FoProperty *padding_start;
  FoProperty *padding_top;
  FoProperty *role;
  FoProperty *scaling;
  FoProperty *scaling_method;
  FoProperty *source_document;
  FoProperty *space_end;
  FoProperty *space_start;
  FoProperty *src;
  FoProperty *text_align;
  FoProperty *width;
};

struct _FoExternalGraphicClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_EXTERNAL_GRAPHIC_PRIVATE_H__ */
