/* Fo
 * fo-area-viewport-reference.h: Combined viewport and reference area object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-viewport-reference.h,v 1.2 2003/03/19 21:13:04 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_AREA_VIEWPORT_REFERENCE_H__
#define __FO_AREA_VIEWPORT_REFERENCE_H__

#include <libfo/fo-utils.h>
#include <fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaViewportReference      FoAreaViewportReference;
typedef struct _FoAreaViewportReferenceClass FoAreaViewportReferenceClass;

#define FO_TYPE_AREA_VIEWPORT_REFERENCE              (fo_area_viewport_reference_get_type ())
#define FO_AREA_VIEWPORT_REFERENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_VIEWPORT_REFERENCE, FoAreaViewportReference))
#define FO_AREA_VIEWPORT_REFERENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_VIEWPORT_REFERENCE, FoAreaViewportReferenceClass))
#define FO_IS_AREA_VIEWPORT_REFERENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_VIEWPORT_REFERENCE))
#define FO_IS_AREA_VIEWPORT_REFERENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_VIEWPORT_REFERENCE))
#define FO_AREA_VIEWPORT_REFERENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_VIEWPORT_REFERENCE, FoAreaViewportReferenceClass))


GType         fo_area_viewport_reference_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_viewport_reference_new (void);

G_END_DECLS

#endif /* !__FO_AREA_VIEWPORT_REFERENCE_H__ */
