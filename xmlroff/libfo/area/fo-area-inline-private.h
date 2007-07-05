/* Fo
 * fo-area-inline-private.h: Structures private to FoAreaInline object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_INLINE_PRIVATE_H__
#define __FO_AREA_INLINE_PRIVATE_H__

#include <libfo/area/fo-area-private.h>
#include <libfo/area/fo-area-inline.h>

G_BEGIN_DECLS

struct _FoAreaInline
{
  FoArea parent_instance;
};

struct _FoAreaInlineClass
{
  FoAreaClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_INLINE_PRIVATE_H__ */
