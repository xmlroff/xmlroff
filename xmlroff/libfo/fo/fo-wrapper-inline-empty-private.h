/* Fo
 * fo-wrapper-inline-empty-private.h: Empty Inline-level wrapper formatting object.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#ifndef __FO_WRAPPER_INLINE_EMPTY_PRIVATE_H__
#define __FO_WRAPPER_INLINE_EMPTY_PRIVATE_H__

#include <libfo/fo/fo-wrapper-private.h>
#include <libfo/fo/fo-wrapper-inline-empty.h>

G_BEGIN_DECLS

struct _FoWrapperInlineEmpty
{
  FoWrapper parent_instance;
};

struct _FoWrapperInlineEmptyClass
{
  FoWrapperClass parent_class;
};

G_END_DECLS

#endif /* !__FO_WRAPPER_INLINE_EMPTY_PRIVATE_H__ */
