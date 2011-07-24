/* Fo
 * fo-region-body-private.h: Structures private to 'region-body' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_BODY_PRIVATE_H__
#define __FO_REGION_BODY_PRIVATE_H__

#include "fo/fo-region-private.h"
#include "fo/fo-region-body.h"

G_BEGIN_DECLS

struct _FoRegionBody
{
  FoRegion parent_instance;

  FoProperty *display_align;
  FoProperty *end_indent;
  FoProperty *margin_bottom;
  FoProperty *margin_left;
  FoProperty *margin_right;
  FoProperty *margin_top;
  FoProperty *space_after;
  FoProperty *space_before;
  FoProperty *start_indent;
};

struct _FoRegionBodyClass
{
  FoRegionClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REGION_BODY_PRIVATE_H__ */
