/* Fo
 * fo-xml-doc.c: Boxed object type for libxml2 xmlDoc document
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libxml/xmlIO.h>
#include "fo-utils.h"
#include "fo-xml-doc-private.h"

/**
 * SECTION:fo-xml-doc
 * @short_description: libxml2 xmlDoc document
 *
 * Boxed object type for libxml2 xmlDoc document.
 */

extern int xmlLoadExtDtdDefaultValue;

const char *fo_xml_doc_error_messages [] = {
  N_("FoXmlDoc error"),
  N_("Unable to parse XML file: %s"),
  N_("Unable to parse XML file from memory or string"),
  N_("Cannot open input document: '%s'")
};

struct _FoXmlDoc
{
  xmlDocPtr xml_doc;

  gchar    *filename;

  guint ref_count;
};

static LibfoVersionInfo version_info =
  {
    LIBFO_MODULE_XML_DOC,
    "libxml2",
    NULL,
    LIBXML_VERSION,
    LIBXML_VERSION_STRING,
    0,
    NULL
  };

/**
 * fo_xml_doc_error_quark:
 * 
 * Get the error quark for #FoXmlDoc.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: Quark associated with #FoXmlDoc errors.
 **/
GQuark
fo_xml_doc_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoXmlDoc error");
  return quark;
}


/**
 * fo_xml_doc_get_type:
 * 
 * Register the #FoXmlDoc object type.
 * 
 * Return value: #GType value of the #FoXmlDoc object type.
 **/
GType fo_xml_doc_get_type (void)
{
  static GType our_type = 0;
  
  if (our_type == 0)
    our_type = g_boxed_type_register_static ("FoXmlDoc",
					     (GBoxedCopyFunc) fo_xml_doc_ref,
					     (GBoxedFreeFunc) fo_xml_doc_unref);

  return our_type;
}

const LibfoVersionInfo *
fo_xml_doc_version_info (void)
{
  return &version_info;
}

/**
 * fo_xml_doc_new:
 * 
 * Creates a new #FoXmlDoc.
 * 
 * Return value: the newly created #FoXmlDoc. Use #fo_xml_doc_unref to free the
 * result.
 **/
FoXmlDoc *
fo_xml_doc_new (void)
{
  FoXmlDoc *fo_xml_doc = g_new0 (FoXmlDoc, 1);

  fo_xml_doc->ref_count = 1;

  return fo_xml_doc;
}

static gint
context_to_libxml2_options (FoLibfoContext *context)
{
  /* Begin with unchanging defaults. */
  gint options = XML_PARSE_NOENT;

  /* Set 'options' according to 'libfo_context' settings. */
  if (context != NULL)
    {
      if (fo_libfo_context_get_validation (context) == TRUE)
	{
	  options |= XML_PARSE_DTDVALID;
	}
    }

  return options;
}

/**
 * fo_xml_doc_new_from_filename:
 * @filename:      File or URL from which to create an #FoXmlDoc.
 * @libfo_context: #FoLibfoContext with parameters affecting parsing.
 * @error:         Indication of any error that occurred.
 * 
 * Creates a new #FoXmlDoc.
 * 
 * Return value: the newly created #FoXmlDoc. Use fo_xml_doc_unref to free the
 * result.
 **/
FoXmlDoc *
fo_xml_doc_new_from_filename (const gchar    *filename,
			      FoLibfoContext *libfo_context,
			      GError        **error)
{
  FoXmlDoc *fo_xml_doc = fo_xml_doc_new ();

  fo_xml_doc->xml_doc = xmlReadFile (filename,
				     NULL,
				     context_to_libxml2_options (libfo_context));

  if (fo_xml_doc->xml_doc == NULL)
    {
      g_free (fo_xml_doc);
      fo_xml_doc = NULL;

      g_set_error (error,
		   FO_XML_DOC_ERROR,
		   FO_XML_DOC_ERROR_FILENAME_PARSE_FAILED,
		   _(fo_xml_doc_error_messages[FO_XML_DOC_ERROR_FILENAME_PARSE_FAILED]),
		   filename);

    }

  return fo_xml_doc;
}

/**
 * fo_xml_doc_new_from_memory:
 * @buffer:        Pointer to a char array.
 * @size:          Size of the array.
 * @URL:           Base URL to use for the document.
 * @encoding:      The encoding of the document, or NULL.
 * @libfo_context: #FoLibfoContext with parameters affecting parsing.
 * @error:         Indication of any error that occurred.
 * 
 * Creates a new #FoXmlDoc.
 * 
 * Return value: the newly created #FoXmlDoc. Use #fo_xml_doc_unref to free the
 * result.
 **/
FoXmlDoc *
fo_xml_doc_new_from_memory (const gchar    *buffer,
			    gint            size,
			    const gchar    *URL,
			    const gchar    *encoding,
			    FoLibfoContext *libfo_context,
			    GError        **error)
{
  FoXmlDoc *fo_xml_doc = fo_xml_doc_new ();

  fo_xml_doc->xml_doc = xmlReadMemory (buffer, 
				       size, 
				       URL, 
				       encoding, 
				       context_to_libxml2_options (libfo_context));

  if (fo_xml_doc->xml_doc == NULL)
    {
      g_free (fo_xml_doc);
      fo_xml_doc = NULL;

      g_set_error (error,
		   FO_XML_DOC_ERROR,
		   FO_XML_DOC_ERROR_MEMORY_PARSE_FAILED,
		   _(fo_xml_doc_error_messages[FO_XML_DOC_ERROR_MEMORY_PARSE_FAILED]));

    }

  return fo_xml_doc;
}

/**
 * fo_xml_doc_new_from_string:
 * @curr:          Pointer to a zero-terminated string.
 * @URL:           Base URL to use for the document.
 * @encoding:      The encoding of the document, or NULL.
 * @libfo_context: #FoLibfoContext with parameters affecting parsing.
 * @error:         Indication of any error that occurred.
 * 
 * Creates a new #FoXmlDoc.
 * 
 * Return value: the newly created #FoXmlDoc. Use #fo_xml_doc_unref to free the
 * result.
 **/
FoXmlDoc *
fo_xml_doc_new_from_string (const gchar    *curr,
			    const gchar    *URL,
			    const gchar    *encoding,
			    FoLibfoContext *libfo_context,
			    GError        **error)
{
  
  FoXmlDoc *fo_xml_doc = fo_xml_doc_new ();

  fo_xml_doc->xml_doc = xmlReadDoc ((xmlChar *) curr,
				    URL, 
				    encoding, 
				    context_to_libxml2_options (libfo_context));

  if (fo_xml_doc->xml_doc == NULL)
    {
      g_free (fo_xml_doc);
      fo_xml_doc = NULL;

      g_set_error (error,
		   FO_XML_DOC_ERROR,
		   FO_XML_DOC_ERROR_MEMORY_PARSE_FAILED,
		   _(fo_xml_doc_error_messages[FO_XML_DOC_ERROR_MEMORY_PARSE_FAILED]));

    }

  return fo_xml_doc;
}

/**
 * fo_xml_doc_ref:
 * @fo_xml_doc: a #FoXmlDoc
 * 
 * Make a copy of a #FoXmlDoc.
 * 
 * Return value: a newly allocated #FoXmlDoc. This value
 *               must be freed using #fo_xml_doc_unref().
 **/
FoXmlDoc *
fo_xml_doc_ref  (FoXmlDoc  *fo_xml_doc)
{
  g_return_val_if_fail (fo_xml_doc != NULL, NULL);
  g_return_val_if_fail (fo_xml_doc->ref_count > 0, NULL);

  fo_xml_doc->ref_count += 1;

  return fo_xml_doc;
}

/**
 * fo_xml_doc_unref:
 * @fo_xml_doc: #FoXmlDoc.
 * 
 * Unref and possibly free a #FoXmlDoc.
 **/
void
fo_xml_doc_unref  (FoXmlDoc  *fo_xml_doc)
{
  g_return_if_fail (fo_xml_doc != NULL);
  g_return_if_fail (fo_xml_doc->ref_count > 0);

  fo_xml_doc->ref_count -= 1;

  if (fo_xml_doc->ref_count == 0)
    {
      if (fo_xml_doc->filename != NULL)
	g_free (fo_xml_doc->filename);

      if (fo_xml_doc->xml_doc != NULL)
	xmlFreeDoc (fo_xml_doc->xml_doc);

      g_free (fo_xml_doc);
    }
}

/**
 * fo_xml_doc_get_xml_doc:
 * @fo_xml_doc: #FoXmlDoc
 * 
 * Get the xmlDocPtr in @fo_xml_doc.
 * 
 * Return value: #xmlDocPtr.
 **/
xmlDocPtr
fo_xml_doc_get_xml_doc (FoXmlDoc *fo_xml_doc)
{
  g_return_val_if_fail (fo_xml_doc != NULL, NULL);

  return fo_xml_doc->xml_doc;
}

/**
 * fo_xml_doc_set_xml_doc:
 * @fo_xml_doc: #FoXmlDoc.
 * @xml_doc:    #xmlDocPtr.
 * 
 * Set the output #xmlDocPtr in @fo_xml_doc.  Voids the parsed result.
 **/
void
fo_xml_doc_set_xml_doc (FoXmlDoc    *fo_xml_doc,
			xmlDocPtr    xml_doc)
{
  g_return_if_fail (fo_xml_doc != NULL);

  if (fo_xml_doc->filename != NULL)
    {
      g_free (fo_xml_doc->filename);
      fo_xml_doc->filename = NULL;
    }

  if (fo_xml_doc->xml_doc != NULL)
    {
      xmlFreeDoc (fo_xml_doc->xml_doc);
      fo_xml_doc->xml_doc = NULL;
    }

  fo_xml_doc->xml_doc = xml_doc;
}

/**
 * fo_xml_doc_set_filename:
 * @fo_xml_doc: #FoXmlDoc
 * @filename:   Filename of file to be parsed.
 * 
 * Set the filename in @fo_xml_doc.  Voids the parsed result.
 **/
void
fo_xml_doc_set_filename (FoXmlDoc    *fo_xml_doc,
			 const gchar *filename)
{
  g_return_if_fail (fo_xml_doc != NULL);

  if (fo_xml_doc->filename != NULL)
    g_free (fo_xml_doc->filename);

  if (fo_xml_doc->xml_doc != NULL)
    {
      xmlFreeDoc (fo_xml_doc->xml_doc);
      fo_xml_doc->xml_doc = NULL;
    }

  fo_xml_doc->filename = g_strdup (filename);
}

/**
 * fo_xml_doc_set_base:
 * @fo_xml_doc: #FoXmlDoc for which to get base URL.
 * 
 * Gets the base URL of @fo_xml_doc.
 **/
gchar*
fo_xml_doc_get_base (FoXmlDoc *fo_xml_doc)
{
  gchar *base = NULL;
  gchar *return_base = NULL;

  g_return_val_if_fail (fo_xml_doc != NULL, NULL);

  base = (gchar *) xmlNodeGetBase (NULL,
				   (xmlNodePtr) fo_xml_doc->xml_doc);

  return_base = g_strdup (base);

  xmlFree (base);

  return return_base;
}

/**
 * fo_xml_doc_set_base:
 * @fo_xml_doc: #FoXmlDoc for which to set base
 * @URL:        New xml:base URL
 * 
 * Sets the base URL of @fo_xml_doc.
 **/
void
fo_xml_doc_set_base (FoXmlDoc    *fo_xml_doc,
		     const gchar *URL)
{
  g_return_if_fail (fo_xml_doc != NULL);

  xmlNodeSetBase ((xmlNodePtr) fo_xml_doc->xml_doc,
		  (const xmlChar*) URL);
}
