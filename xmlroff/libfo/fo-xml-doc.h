/* Fo
 * fo-xml-doc.h: Boxed object type for libxml2 xmlDoc document
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_XML_DOC_H__
#define __FO_XML_DOC_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-libfo-context.h>
#include <libfo/libfo-version.h>

G_BEGIN_DECLS

#define FO_XML_DOC_ERROR fo_xml_doc_error_quark ()
GQuark fo_xml_doc_error_quark (void);

typedef enum
{
  FO_XML_DOC_ERROR_FAILED,
  FO_XML_DOC_ERROR_FILENAME_PARSE_FAILED,
  FO_XML_DOC_ERROR_MEMORY_PARSE_FAILED,
  FO_XML_DOC_ERROR_NO_FILENAME
} FoXmlDocError;

typedef struct _FoXmlDoc FoXmlDoc;

#define FO_TYPE_XML_DOC             (fo_xml_doc_get_type ())
#define FO_IS_XML_DOC(object)       (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_XML_DOC))

GType      fo_xml_doc_get_type          (void);

const LibfoVersionInfo * fo_xml_doc_version_info (void);

FoXmlDoc * fo_xml_doc_new_from_filename (const gchar    *filename,
					 FoLibfoContext *libfo_context,
					 GError        **error);
FoXmlDoc * fo_xml_doc_new_from_memory   (const gchar    *buffer,
					 gint            size,
					 const gchar    *URL,
					 const gchar    *encoding,
					 FoLibfoContext *libfo_context,
					 GError        **error);
FoXmlDoc * fo_xml_doc_new_from_string   (const gchar    *curr,
					 const gchar    *URL,
					 const gchar    *encoding,
					 FoLibfoContext *libfo_context,
					 GError        **error);
FoXmlDoc * fo_xml_doc_ref               (FoXmlDoc       *fo_xml_doc);
void       fo_xml_doc_unref             (FoXmlDoc       *fo_xml_doc);

gchar*     fo_xml_doc_get_base          (FoXmlDoc       *fo_xml_doc);
void       fo_xml_doc_set_base          (FoXmlDoc       *fo_xml_doc,
					 const gchar    *URL);
G_END_DECLS

#endif /* !__FO_XML_DOC_H__ */
