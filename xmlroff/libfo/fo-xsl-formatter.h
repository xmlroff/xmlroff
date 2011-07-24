/* Fo
 * fo-xsl-formatter.h: Boxed object type for libfo XSL formatter
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_XSL_FORMATTER_H__
#define __FO_XSL_FORMATTER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-libfo-context.h>
#include <libfo/fo-doc.h>
#include <libfo/fo-xml-doc.h>

G_BEGIN_DECLS

#define FO_XSL_FORMATTER_ERROR fo_xsl_formatter_error_quark ()
GQuark fo_xsl_formatter_error_quark (void);

typedef enum
{
  FO_XSL_FORMATTER_ERROR_FAILED,
  FO_XSL_FORMATTER_ERROR_FORMAT_FAILED,
  FO_XSL_FORMATTER_ERROR_PARSE_FAILED,
  FO_XSL_FORMATTER_ERROR_NO_RESULT_TREE,
  FO_XSL_FORMATTER_ERROR_RESULT_TREE_NOT_FO,
  FO_XSL_FORMATTER_ERROR_NO_AREA_TREE,
  FO_XSL_FORMATTER_ERROR_NO_FO_DOC,
  FO_XSL_FORMATTER_ERROR_NOT_FO_DOC,
  FO_XSL_FORMATTER_ERROR_UNKNOWN_FO	/* Unknown FO element type */
} FoXslFormatterError;

typedef struct _FoXslFormatter      FoXslFormatter;
typedef struct _FoXslFormatterClass FoXslFormatterClass;

#define FO_TYPE_XSL_FORMATTER              (fo_xsl_formatter_get_type ())
#define FO_XSL_FORMATTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_XSL_FORMATTER, FoXslFormatter))
#define FO_XSL_FORMATTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_XSL_FORMATTER, FoXslFormatterClass))
#define FO_IS_XSL_FORMATTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_XSL_FORMATTER))
#define FO_IS_XSL_FORMATTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_XSL_FORMATTER))
#define FO_XSL_FORMATTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_XSL_FORMATTER, FoXslFormatterClass))


GType            fo_xsl_formatter_get_type (void);
FoXslFormatter * fo_xsl_formatter_new      (void);

gboolean         fo_xsl_formatter_format   (FoXslFormatter  *fo_xsl_formatter,
					    FoLibfoContext  *libfo_context,
					    GError         **error);
gboolean         fo_xsl_formatter_draw     (FoXslFormatter  *fo_xsl_formatter,
					    FoLibfoContext  *libfo_context,
					    GError         **error);
void      fo_xsl_formatter_set_result_tree (FoXslFormatter  *fo_xsl_formatter,
					    FoXmlDoc        *result_tree);
void      fo_xsl_formatter_set_fo_doc      (FoXslFormatter  *fo_xsl_formatter,
					    FoDoc           *fo_doc);

GObject * fo_xsl_formatter_get_fo_tree     (FoXslFormatter  *fo_xsl_formatter);
GObject * fo_xsl_formatter_get_area_tree   (FoXslFormatter  *fo_xsl_formatter);

G_END_DECLS

#endif /* !__FO_XSL_FORMATTER_H__ */
