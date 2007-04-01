/* Fo
 * fo-flow-private.h: Structures private to 'flow' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-flow-private.h,v 1.3 2005/11/23 21:45:31 tonygraham Exp $
 *
 * See Copying for the status of this software.
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
