/* Fo
 * fo-area-inline-private.h: Structures private to FoAreaInline object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-area-inline-private.h,v 1.1 2006/03/28 10:34:20 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_AREA_INLINE_PRIVATE_H__
#define __FO_AREA_INLINE_PRIVATE_H__

#include <fo-area-private.h>
#include <fo-area-inline.h>

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
