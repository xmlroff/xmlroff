/* Fo
 * fo-region-before--after-private.h: Structures private to abstract 'region-before-after' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_BEFORE_AFTER_PRIVATE_H__
#define __FO_REGION_BEFORE_AFTER_PRIVATE_H__

#include "fo/fo-region-outer-private.h"
#include "fo/fo-region-before-after.h"

G_BEGIN_DECLS

struct _FoRegionBeforeAfter
{
  FoRegionOuter parent_instance;

  FoProperty *precedence;
};

struct _FoRegionBeforeAfterClass
{
  FoRegionOuterClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REGION_BEFORE_AFTER_PRIVATE_H__ */
