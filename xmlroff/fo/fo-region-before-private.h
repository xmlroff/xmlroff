/* Fo
 * fo-region-before-private.h: Structures private to 'region-before' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-region-before-private.h,v 1.4 2006/01/16 11:54:45 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_REGION_BEFORE_PRIVATE_H__
#define __FO_REGION_BEFORE_PRIVATE_H__

#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-region-before.h"

G_BEGIN_DECLS

struct _FoRegionBefore
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
  FoProperty *clip;
  FoProperty *display_align;
  FoProperty *extent;
  FoProperty *overflow;
  FoProperty *padding_after;
  FoProperty *padding_before;
  FoProperty *padding_bottom;
  FoProperty *padding_end;
  FoProperty *padding_left;
  FoProperty *padding_right;
  FoProperty *padding_start;
  FoProperty *padding_top;
  FoProperty *region_name;
  FoProperty *writing_mode;
};

struct _FoRegionBeforeClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REGION_BEFORE_PRIVATE_H__ */
