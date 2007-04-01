/* Fo
 * fo-xml-node-private.h: Boxed object type for libxml2 xmlNode
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-xml-node-private.h,v 1.2 2006/04/07 11:05:33 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_XML_NODE_PRIVATE_H__
#define __FO_XML_NODE_PRIVATE_H__

#include <libxml/tree.h>
#include "fo-xml-node.h"

G_BEGIN_DECLS

xmlNodePtr fo_xml_node_get_xml_node (FoXmlNode *fo_xml_node);
void       fo_xml_node_set_xml_node (FoXmlNode *fo_xml_node,
				     xmlNodePtr xml_node);

#endif /* !__FO_XML_NODE_PRIVATE_H__ */
