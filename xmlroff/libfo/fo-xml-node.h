/* Fo
 * fo-xml-node.h: Boxed object type for libxml2 xmlNode nodeument
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-xml-node.h,v 1.3 2006/04/16 20:35:13 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_XML_NODE_H__
#define __FO_XML_NODE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-libfo-context.h>

G_BEGIN_DECLS

#define FO_XML_NODE_ERROR fo_xml_node_error_quark ()
GQuark fo_xml_node_error_quark (void);

typedef enum
{
  FO_XML_NODE_ERROR_FAILED,
  FO_XML_NODE_ERROR_PARSE_FAILED,
  FO_XML_NODE_ERROR_NO_FILENAME
} FoXmlNodeError;

typedef struct _FoXmlNode FoXmlNode;

#define FO_TYPE_XML_NODE             (fo_xml_node_get_type ())
#define FO_IS_XML_NODE(object)       (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_XML_NODE))

GType       fo_xml_node_get_type (void);
FoXmlNode * fo_xml_node_new      (void);

FoXmlNode * fo_xml_node_ref      (FoXmlNode *fo_xml_node);
void        fo_xml_node_unref    (FoXmlNode *fo_xml_node);

G_END_DECLS

#endif /* !__FO_XML_NODE_H__ */
