/* Fo
 * fo-flow-private.h: Structures private to 'flow' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_FLOW_PRIVATE_H__
#define __FO_FLOW_PRIVATE_H__

#include "fo/fo-marker-parent-private.h"
#include "fo/fo-flow.h"

G_BEGIN_DECLS

struct _FoFlow
{
  FoMarkerParent parent_instance;

  FoFo *region_master;

  FoProperty *flow_name;
};

struct _FoFlowClass
{
  FoMarkerParentClass parent_class;
};

G_END_DECLS

#endif /* !__FO_FLOW_PRIVATE_H__ */
