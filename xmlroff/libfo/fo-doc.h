/* Fo
 * fo-doc.h: Wrapper for libfo output document
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_DOC_H__
#define __FO_DOC_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-libfo-context.h>

typedef struct _FoDoc      FoDoc;
typedef struct _FoDocClass FoDocClass;

#include <libfo/fo-layout.h>

G_BEGIN_DECLS

#define FO_DOC_ERROR fo_doc_error_quark ()
GQuark fo_doc_error_quark (void);

typedef enum
{
  FO_DOC_ERROR_FAILED,
  FO_DOC_ERROR_OPEN_FAILED,	     /* Cannot open output document */
  FO_DOC_ERROR_UNSUPPORTED_FORMAT,   /* Unsupported document format */
  FO_DOC_ERROR_LAST
} FoDocError;

extern const char *fo_doc_error_messages[FO_DOC_ERROR_LAST];

typedef enum
{
  FO_DOC_LINE_CAP_INVALID,
  FO_DOC_LINE_CAP_BUTT,
  FO_DOC_LINE_CAP_ROUND,
  FO_DOC_LINE_CAP_SQUARE,
  FO_DOC_LINE_CAP_LIMIT
} FoDocLineCap;

typedef enum
{
  FO_DOC_LINE_JOIN_INVALID,
  FO_DOC_LINE_JOIN_MITER,
  FO_DOC_LINE_JOIN_ROUND,
  FO_DOC_LINE_JOIN_BEVEL,
  FO_DOC_LINE_JOIN_LIMIT
} FoDocLineJoin;

#define FO_TYPE_DOC              (fo_doc_get_type ())
#define FO_DOC(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_DOC, FoDoc))
#define FO_DOC_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_DOC, FoDocClass))
#define FO_IS_DOC(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_DOC))
#define FO_IS_DOC_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_DOC))
#define FO_DOC_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_DOC, FoDocClass))


GType         fo_doc_get_type (void);
FoDoc *       fo_doc_new (void);
FoDoc *       fo_doc_new_from_type (const gchar *type);
FoFlagsFormat fo_doc_formats_from_name (const gchar *name);

void          fo_doc_open_file (FoDoc          *fo_doc,
				const gchar    *filename,
				FoLibfoContext *libfo_context,
				GError        **error);

FoLayout *    fo_doc_get_new_layout (FoDoc *fo_doc);

const gchar * fo_doc_get_language (FoDoc *fo_doc);
void          fo_doc_set_language (FoDoc *fo_doc,
				   const gchar    *language);
FoEnumAreaDirection fo_doc_get_base_dir (FoDoc      *fo_doc);
void                fo_doc_set_base_dir (FoDoc      *fo_doc,
					 FoEnumAreaDirection  base_dir);

G_END_DECLS

#endif /* !__FO_DOC_H__ */
