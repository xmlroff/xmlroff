/* Fo
 * fo-xslt-transformer.c: Boxed object type for libxslt XSLT processor
 *
 * Copyright (C) 2003-2006 Sun Microsystems
 *
 * $Id: fo-xslt-transformer.c,v 1.7 2006/08/07 15:26:29 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include "libfo/fo-utils.h"
#include "fo-xml-doc-private.h"
#include "fo-xslt-transformer.h"

extern int xmlLoadExtDtdDefaultValue;

const char *fo_xslt_transformer_error_messages [] = {
  N_("FoXsltTransformer error"),
  N_("XSLT transform failed"),
  N_("No input stylesheet specified"),
  N_("No input XML document"),
  N_("Parsing stylesheet as stylesheet failed"),
};

/**
 * fo_xslt_transformer_error_quark:
 * 
 * Get the error quark for #FoXsltTransformer.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: #GQuark associated with #FoXsltTransformer errors.
 **/
GQuark
fo_xslt_transformer_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoXsltTransformer error");
  return quark;
}


FoXmlDoc *
fo_xslt_transformer_do_transform (FoXmlDoc          *xml_doc,
				  FoXmlDoc          *stylesheet_doc,
				  FoLibfoContext    *libfo_context,
				  GError           **error)
{
  xsltStylesheetPtr stylesheet;
  FoXmlDoc *result_tree = NULL;
  GError *tmp_error = NULL;

  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (stylesheet_doc == NULL)
    {
      g_set_error (error,
		   FO_XSLT_TRANSFORMER_ERROR,
		   FO_XSLT_TRANSFORMER_ERROR_NO_STYLESHEET_DOC,
		   _(fo_xslt_transformer_error_messages[FO_XSLT_TRANSFORMER_ERROR_NO_STYLESHEET_DOC]));
      return NULL;
    }

  if (xml_doc == NULL)
		
    {
      g_set_error (error,
		   FO_XSLT_TRANSFORMER_ERROR,
		   FO_XSLT_TRANSFORMER_ERROR_NO_XML_DOC,
		   _(fo_xslt_transformer_error_messages[FO_XSLT_TRANSFORMER_ERROR_NO_XML_DOC]));
      return NULL;
    }

  stylesheet =
    xsltParseStylesheetDoc (fo_xml_doc_get_xml_doc (stylesheet_doc));

  if (stylesheet == NULL)
    {
      g_set_error (error,
		   FO_XSLT_TRANSFORMER_ERROR,
		   FO_XSLT_TRANSFORMER_ERROR_PARSE_FAILED,
		   _(fo_xslt_transformer_error_messages[FO_XSLT_TRANSFORMER_ERROR_PARSE_FAILED]));

      return NULL;
    }
  else
    {
      xmlDocPtr result_doc;
      gchar *base = NULL;

      result_doc =
	xsltApplyStylesheet(stylesheet,
			    fo_xml_doc_get_xml_doc (xml_doc),
			    NULL);

      if (result_doc == NULL)
	{
	  g_set_error (error,
		       FO_XSLT_TRANSFORMER_ERROR,
		       FO_XSLT_TRANSFORMER_ERROR_TRANSFORM_FAILED,
		       _(fo_xslt_transformer_error_messages[FO_XSLT_TRANSFORMER_ERROR_TRANSFORM_FAILED]));

	  return NULL;
	}

      base = fo_xml_doc_get_base (xml_doc);

      result_tree = fo_xml_doc_new ();
      fo_xml_doc_set_xml_doc (result_tree,
			      result_doc);

      fo_xml_doc_set_base (result_tree,
			   base);
      g_free (base);


    }
  return result_tree;

}

