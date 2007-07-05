/* Fo
 * fo-doc-cairo.h: libfo output document based on Cairo.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#ifndef __FO_DOC_CAIRO_H__
#define __FO_DOC_CAIRO_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-doc.h>

G_BEGIN_DECLS

typedef struct _FoDocCairo      FoDocCairo;
typedef struct _FoDocCairoClass FoDocCairoClass;

#define FO_TYPE_DOC_CAIRO            (fo_doc_cairo_get_type ())
#define FO_DOC_CAIRO(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_DOC_CAIRO, FoDocCairo))
#define FO_DOC_CAIRO_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_DOC_CAIRO, FoDocCairoClass))
#define FO_IS_DOC_CAIRO(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_DOC_CAIRO))
#define FO_IS_DOC_CAIRO_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_DOC_CAIRO))
#define FO_DOC_CAIRO_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_DOC_CAIRO, FoDocCairoClass))


GType   fo_doc_cairo_get_type  (void);
FoDoc * fo_doc_cairo_new       (void);

void    fo_doc_cairo_open_file (FoDoc          *fo_doc,
				const gchar    *filename,
				FoLibfoContext *libfo_context,
				GError        **error);

G_END_DECLS

#endif /* !__FO_DOC_CAIRO_H__ */
