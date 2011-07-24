/* Fo
 * fo-region-end-private.h: Structures private to 'region-end' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_END_PRIVATE_H__
#define __FO_REGION_END_PRIVATE_H__

#include "fo/fo-region-outer-private.h"
#include "fo/fo-region-end.h"

G_BEGIN_DECLS

struct _FoRegionEnd
{
  FoRegionOuter parent_instance;
};

struct _FoRegionEndClass
{
  FoRegionOuterClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REGION_END_PRIVATE_H__ */
