/* Fo
 * fo-xml-node.c: Boxed object type for libxml2 xmlNode nodeument
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-xml-node.c,v 1.2 2006/04/16 20:35:13 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <libxml/xmlIO.h>
#include "libfo/fo-utils.h"
#include "fo-xml-node-private.h"

extern int xmlLoadExtDtdDefaultValue;

const char *fo_xml_node_error_messages [] = {
  N_("FoXmlNode error"),
  N_("Unable to parse XML file: %s"),
  N_("Cannot open input nodeument: '%s'")
};

struct _FoXmlNode
{
  xmlNodePtr xml_node;

  guint ref_count;
};

/**
 * fo_xml_node_error_quark:
 * 
 * Get the error quark for #FoXmlNode.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: Quark associated with #FoXmlNode errors.
 **/
GQuark
fo_xml_node_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoXmlNode error");
  return quark;
}


/**
 * fo_xml_node_get_type:
 * 
 * Register the #FoXmlNode object type.
 * 
 * Return value: #GType value of the #FoXmlNode object type.
 **/
GType fo_xml_node_get_type (void)
{
  static GType our_type = 0;
  
  if (our_type == 0)
    our_type = g_boxed_type_register_static ("FoXmlNode",
					     (GBoxedCopyFunc) fo_xml_node_ref,
					     (GBoxedFreeFunc) fo_xml_node_unref);

  return our_type;
}

/**
 * fo_xml_node_new:
 * 
 * Creates a new #FoXmlNode.
 * 
 * Return value: the newly created #FoXmlNode. Use fo_xml_node_unref to free the
 * result.
 **/
FoXmlNode *
fo_xml_node_new (void)
{
  FoXmlNode *fo_xml_node = g_new0 (FoXmlNode, 1);

  fo_xml_node->ref_count = 1;

  return fo_xml_node;
}

/**
 * fo_xml_node_ref:
 * @fo_xml_node: a #FoXmlNode
 * 
 * Make a copy of a #FoXmlNode.
 * 
 * Return value: a newly allocated #FoXmlNode. This value
 *               must be freed using fo_xml_node_unref().
 **/
FoXmlNode *
fo_xml_node_ref  (FoXmlNode  *fo_xml_node)
{
  g_return_val_if_fail (fo_xml_node != NULL, NULL);
  g_return_val_if_fail (fo_xml_node->ref_count > 0, NULL);

  fo_xml_node->ref_count += 1;

  return fo_xml_node;
}

/**
 * fo_xml_node_unref:
 * @fo_xml_node: #FoXmlNode.
 * 
 * Unref and possibly free a #FoXmlNode.
 **/
void
fo_xml_node_unref  (FoXmlNode  *fo_xml_node)
{
  g_return_if_fail (fo_xml_node != NULL);
  g_return_if_fail (fo_xml_node->ref_count > 0);

  fo_xml_node->ref_count -= 1;

  if (fo_xml_node->ref_count == 0)
    {
      if (fo_xml_node->xml_node != NULL)
	xmlFreeNode (fo_xml_node->xml_node);

      g_free (fo_xml_node);
    }
}

/**
 * fo_xml_node_get_xml_node:
 * @fo_xml_node: #FoXmlNode
 * 
 * Get the xmlNodePtr in @fo_xml_node.
 * 
 * Return value: #xmlNodePtr.
 **/
xmlNodePtr
fo_xml_node_get_xml_node (FoXmlNode *fo_xml_node)
{
  g_return_val_if_fail (fo_xml_node != NULL, NULL);

  return fo_xml_node->xml_node;
}

/**
 * fo_xml_node_set_xml_node:
 * @fo_xml_node: #FoXmlNode.
 * @xml_node:    #xmlNodePtr.
 * 
 * Set the output #xmlNodePtr in @fo_xml_node.
 **/
void
fo_xml_node_set_xml_node (FoXmlNode    *fo_xml_node,
			  xmlNodePtr    xml_node)
{
  g_return_if_fail (fo_xml_node != NULL);

  if (fo_xml_node->xml_node != NULL)
    {
      xmlFreeNode (fo_xml_node->xml_node);
      fo_xml_node->xml_node = NULL;
    }

  fo_xml_node->xml_node = xml_node;
}
