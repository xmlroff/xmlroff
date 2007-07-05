/* Fo
 * fo-root-private.h: Structures private to 'root' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ROOT_PRIVATE_H__
#define __FO_ROOT_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-root.h>

G_BEGIN_DECLS

struct _FoRoot
{
  FoFo parent_instance;

  FoProperty *media_usage;
};

struct _FoRootClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_ROOT_PRIVATE_H__ */
