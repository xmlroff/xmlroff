/* Fo
 * fo-region-after-private.h: Structures private to 'region-after' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_AFTER_PRIVATE_H__
#define __FO_REGION_AFTER_PRIVATE_H__

#include "fo/fo-region-before-after-private.h"
#include "fo/fo-region-after.h"

G_BEGIN_DECLS

struct _FoRegionAfter
{
  FoRegionBeforeAfter parent_instance;

  FoProperty *precedence;
};

struct _FoRegionAfterClass
{
  FoRegionBeforeAfterClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REGION_AFTER_PRIVATE_H__ */
