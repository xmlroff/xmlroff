/* Fo
 * fo-wrapper-private.h: Structures private to 'wrapper' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-wrapper-private.h,v 1.3 2006/03/21 23:19:14 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_WRAPPER_PRIVATE_H__
#define __FO_WRAPPER_PRIVATE_H__

#include "fo/fo-marker-parent-private.h"
#include "fo/fo-wrapper.h"

G_BEGIN_DECLS

struct _FoWrapper
{
  FoMarkerParent parent_instance;

  FoProperty *id;
};

struct _FoWrapperClass
{
  FoMarkerParentClass parent_class;
};

G_END_DECLS

#endif /* !__FO_WRAPPER_PRIVATE_H__ */
