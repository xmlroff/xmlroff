/* Fo
 * fo-area-viewport-reference-private.h: Structures private to Combined
 *                                         viewport and reference area object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-viewport-reference-private.h,v 1.3 2005/11/02 08:12:50 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_AREA_VIEWPORT_REFERENCE_PRIVATE_H__
#define __FO_AREA_VIEWPORT_REFERENCE_PRIVATE_H__

#include <fo-area-reference-private.h>
#include <fo-area-viewport-reference.h>

G_BEGIN_DECLS

struct _FoAreaViewportReference
{
  FoAreaReference parent_instance;
};

struct _FoAreaViewportReferenceClass
{
  FoAreaReferenceClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_VIEWPORT_REFERENCE_H__ */
