/* Fo
 * fo-wrapper-inline-private.h: Inline-level wrapper formatting object.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-wrapper-inline-private.h,v 1.2 2006/03/21 23:21:38 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_WRAPPER_INLINE_PRIVATE_H__
#define __FO_WRAPPER_INLINE_PRIVATE_H__

#include "fo/fo-wrapper-private.h"
#include "fo/fo-wrapper-inline.h"

G_BEGIN_DECLS

struct _FoWrapperInline
{
  FoWrapper parent_instance;
};

struct _FoWrapperInlineClass
{
  FoWrapperClass parent_class;
};

G_END_DECLS

#endif /* !__FO_WRAPPER_INLINE_PRIVATE_H__ */
