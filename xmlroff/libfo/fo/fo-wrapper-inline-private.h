/* Fo
 * fo-wrapper-inline-private.h: Inline-level wrapper formatting object.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#ifndef __FO_WRAPPER_INLINE_PRIVATE_H__
#define __FO_WRAPPER_INLINE_PRIVATE_H__

#include <libfo/fo/fo-wrapper-private.h>
#include <libfo/fo/fo-wrapper-inline.h>

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
