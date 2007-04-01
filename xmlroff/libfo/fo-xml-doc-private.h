/* Fo
 * fo-xml-doc-private.h: Boxed object type for libxml2 xmlDoc document
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-xml-doc-private.h,v 1.2 2006/04/16 20:39:42 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_XML_DOC_PRIVATE_H__
#define __FO_XML_DOC_PRIVATE_H__

#include <libxml/tree.h>
#include "fo-xml-doc.h"

G_BEGIN_DECLS

FoXmlDoc * fo_xml_doc_new         (void);
xmlDocPtr  fo_xml_doc_get_xml_doc (FoXmlDoc *fo_xml_doc);
void       fo_xml_doc_set_xml_doc (FoXmlDoc *fo_xml_doc,
				   xmlDocPtr xml_doc);

#endif /* !__FO_XML_DOC_PRIVATE_H__ */
