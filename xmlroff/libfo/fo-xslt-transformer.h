/* Fo
 * fo-xslt-transformer.h: Boxed object type for libxslt XSLT processor
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_XSLT_TRANSFORMER_H__
#define __FO_XSLT_TRANSFORMER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-xml-doc.h>
#include <libfo/libfo-version.h>

G_BEGIN_DECLS

#define FO_XSLT_TRANSFORMER_ERROR fo_xslt_transformer_error_quark ()
GQuark fo_xslt_transformer_error_quark (void);

typedef enum
{
  FO_XSLT_TRANSFORMER_ERROR_FAILED,
  FO_XSLT_TRANSFORMER_ERROR_TRANSFORM_FAILED,
  FO_XSLT_TRANSFORMER_ERROR_NO_STYLESHEET_DOC,
  FO_XSLT_TRANSFORMER_ERROR_NO_XML_DOC,
  FO_XSLT_TRANSFORMER_ERROR_PARSE_FAILED
} FoXsltTransformerError;

const LibfoVersionInfo * fo_xslt_transformer_version_info (void);

FoXmlDoc * fo_xslt_transformer_do_transform (FoXmlDoc          *xml_doc,
					     FoXmlDoc          *stylesheet_doc,
					     GError           **error);

G_END_DECLS

#endif /* !__FO_XSLT_TRANSFORMER_H__ */
