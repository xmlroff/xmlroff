/* Fo
 * fo-marker-parent.h: Abstract formatting object that is parent of possible fo:marker
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_MARKER_PARENT_H__
#define __FO_MARKER_PARENT_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

typedef struct _FoMarkerParent      FoMarkerParent;
typedef struct _FoMarkerParentClass FoMarkerParentClass;

#define FO_TYPE_MARKER_PARENT              (fo_marker_parent_get_type ())
#define FO_MARKER_PARENT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_MARKER_PARENT, FoMarkerParent))
#define FO_MARKER_PARENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_MARKER_PARENT, FoMarkerParentClass))
#define FO_IS_MARKER_PARENT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_MARKER_PARENT))
#define FO_IS_MARKER_PARENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_MARKER_PARENT))
#define FO_MARKER_PARENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_MARKER_PARENT, FoMarkerParentClass))


GType  fo_marker_parent_get_type  (void) G_GNUC_CONST;
FoFo  *fo_marker_parent_new       (void);

void   fo_marker_parent_update_from_context (FoFo      *fo,
					     FoContext *context);

G_END_DECLS

#endif /* !__FO_MARKER_PARENT_H__ */
