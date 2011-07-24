/* Fo
 * fo-region-outer-private.h: Structures private to abstract 'outer region' formatting object
 *
 * Copyright (C) 2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_OUTER_PRIVATE_H__
#define __FO_REGION_OUTER_PRIVATE_H__

#include "fo/fo-region-private.h"
#include "fo/fo-region-outer.h"

G_BEGIN_DECLS

struct _FoRegionOuter
{
  FoRegion parent_instance;

  FoProperty *extent;
};

struct _FoRegionOuterClass
{
  FoRegionClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REGION_OUTER_PRIVATE_H__ */
