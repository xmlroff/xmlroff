/* Fo
 * fo-area-viewport-reference-private.h: Structures private to Combined
 *                                         viewport and reference area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_VIEWPORT_REFERENCE_PRIVATE_H__
#define __FO_AREA_VIEWPORT_REFERENCE_PRIVATE_H__

#include <libfo/area/fo-area-reference-private.h>
#include <libfo/area/fo-area-viewport-reference.h>

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
