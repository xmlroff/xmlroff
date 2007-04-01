/* Fo
 * fo-root-private.h: Structures private to 'root' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-root-private.h,v 1.3 2003/05/16 13:45:14 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_ROOT_PRIVATE_H__
#define __FO_ROOT_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-root.h"

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
