/* Fo
 * fo-doc-gp.h: Wrapper for libfo output document
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-doc-gp.h,v 1.5 2005/06/27 00:19:42 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_DOC_GP_H__
#define __FO_DOC_GP_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-doc.h>

G_BEGIN_DECLS

typedef struct _FoDocGP      FoDocGP;
typedef struct _FoDocGPClass FoDocGPClass;

#define FO_TYPE_DOC_GP            (fo_doc_gp_get_type ())
#define FO_DOC_GP(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_DOC_GP, FoDocGP))
#define FO_DOC_GP_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_DOC_GP, FoDocGPClass))
#define FO_IS_DOC_GP(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_DOC_GP))
#define FO_IS_DOC_GP_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_DOC_GP))
#define FO_DOC_GP_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_DOC_GP, FoDocGPClass))


GType   fo_doc_gp_get_type  (void);
FoDoc * fo_doc_gp_new       (void);

void    fo_doc_gp_open_file (FoDoc          *fo_doc,
			     const gchar    *filename,
			     FoLibfoContext *libfo_context,
			     GError        **error);

G_END_DECLS

#endif /* !__FO_DOC_GP_H__ */
