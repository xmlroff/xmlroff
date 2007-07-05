/* Fo
 * fo-initial-property-set-private.h: Structures private to 'initial-property-set' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_INITIAL_PROPERTY_SET_PRIVATE_H__
#define __FO_INITIAL_PROPERTY_SET_PRIVATE_H__

#include <libfo/fo/fo-fo.h>
#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-initial-property-set.h>

G_BEGIN_DECLS

struct _FoInitialPropertySet
{
  FoFo parent_instance;

  FoProperty *background_color;
  FoProperty *background_image;
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
  FoProperty *color;
  FoProperty *font_family;
  FoProperty *font_size;
  FoProperty *font_stretch;
  FoProperty *font_style;
  FoProperty *font_variant;
  FoProperty *font_weight;
  FoProperty *id;
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
  FoProperty *score_spaces;
  FoProperty *source_document;
};

struct _FoInitialPropertySetClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_INITIAL_PROPERTY_SET_PRIVATE_H__ */
