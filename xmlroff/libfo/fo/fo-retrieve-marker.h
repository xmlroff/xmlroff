/* Fo
 * fo-retrieve_marker.h: Retrieve Marker formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_RETRIEVE_MARKER_H__
#define __FO_RETRIEVE_MARKER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

typedef struct _FoRetrieveMarker      FoRetrieveMarker;
typedef struct _FoRetrieveMarkerClass FoRetrieveMarkerClass;

#define FO_TYPE_RETRIEVE_MARKER              (fo_retrieve_marker_get_type ())
#define FO_RETRIEVE_MARKER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_RETRIEVE_MARKER, FoRetrieveMarker))
#define FO_RETRIEVE_MARKER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_RETRIEVE_MARKER, FoRetrieveMarkerClass))
#define FO_IS_RETRIEVE_MARKER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_RETRIEVE_MARKER))
#define FO_IS_RETRIEVE_MARKER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_RETRIEVE_MARKER))
#define FO_RETRIEVE_MARKER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_RETRIEVE_MARKER, FoRetrieveMarkerClass))


GType         fo_retrieve_marker_get_type      (void) G_GNUC_CONST;
FoFo *fo_retrieve_marker_new (void);

void fo_retrieve_marker_update_from_context (FoFo *fo,
				   FoContext *context);

G_END_DECLS

#endif /* !__FO_RETRIEVE_MARKER_H__ */
