/* Fo
 * fo-flow-private.h: Structures private to 'flow' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_FLOW_PRIVATE_H__
#define __FO_FLOW_PRIVATE_H__

#include <libfo/fo/fo-marker-parent-private.h>
#include <libfo/fo/fo-flow.h>

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
