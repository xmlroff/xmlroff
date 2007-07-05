/* Fo
 * fo-layout-master-set-private.h: Structures private to 'layout-master-set' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LAYOUT_MASTER_SET_PRIVATE_H__
#define __FO_LAYOUT_MASTER_SET_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-layout-master-set.h>

G_BEGIN_DECLS

struct _FoLayoutMasterSet
{
  FoFo parent_instance;

};

struct _FoLayoutMasterSetClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_LAYOUT_MASTER_SET_PRIVATE_H__ */
