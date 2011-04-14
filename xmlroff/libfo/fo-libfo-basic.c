/* Fo
 * fo-libfo-basic.c: 'Basic' (i.e., simple) high-level interface to libfo
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-libfo-basic.h"
#include "fo-libfo.h"
#include "fo-doc.h"
#include "area-to-pdf.h"
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>

const char *fo_libfo_basic_error_messages [] = {
  N_("FoLibfo error"),
  N_("Unknown file format"),
  N_("FoLibfo warning")
};

/**
 * fo_libfo_basic_error_quark:
 * 
 * Get the error quark for #FoLibfo.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: Quark associated with #FoLibfo errors.
 **/
GQuark
fo_libfo_basic_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoLibfoBasic error");
  return quark;
}

/**
 * fo_libfo_init:
 * 
 * Initialise the libfo formatter.
 *
 * Return value: %TRUE if successful.
 **/
gboolean
fo_libfo_init (void)
{
  g_type_init ();

  return TRUE;
}

/**
 * fo_libfo_init2:
 * @fo_malloc:  Function that allocates memory.
 * @fo_realloc: Function that reallocates memory.
 * @fo_free:    Function that frees memory.
 * 
 * Initialise the libfo formatter and provide functions for
 * allocating, reallocating, and freeing memory.
 *
 * Return value: %TRUE if successful.
 **/
gboolean
fo_libfo_init2 (FoMalloc  fo_malloc,
		FoRealloc fo_realloc,
		FoFree    fo_free)
{
  GMemVTable mem_vtable = {fo_malloc,
			   fo_realloc,
			   fo_free,
			   NULL,
			   NULL,
			   NULL};

  g_mem_set_vtable (&mem_vtable);

  return fo_libfo_init ();
}

/**
 * fo_libfo_shutdown:
 * 
 * Shutdown the libfo formatter.
 *
 * Return value: %TRUE if successful.
 **/
gboolean
fo_libfo_shutdown (void)
{
  xmlCleanupParser();
  xmlMemoryDump();

  return TRUE;
}

static void
fo_basic_bubble_up_error (GError     **dest,
			  GQuark       new_domain,
			  gint         new_code,
			  const gchar *new_message,
			  GError      *src)
{
  gchar *error_string = NULL;

  g_return_if_fail (dest == NULL || *dest == NULL);
  g_return_if_fail (new_domain != 0);
  g_return_if_fail (src != NULL);

  if (dest == NULL)
    {
      if (src != NULL)
        g_error_free (src);
      return;
    }

  error_string =
    g_strconcat (new_message,
		 "\n",
		 g_quark_to_string (src->domain),
		 ": ",
		 src->message,
		 NULL);

  g_error_free (src);

  if (*dest != NULL)
    {
      g_warning ("Can't override existing error message.\n"
		 "Existing error:: %s: %s\n"
		 "New error:: %s: %s",
		 g_quark_to_string ((*dest)->domain),
		 (*dest)->message,
		 g_quark_to_string (src->domain),
		 src->message);
      return;
    }

  g_set_error (dest,
	       new_domain,
	       new_code,
	       "%s",
	       error_string);

  g_free (error_string);
}

gboolean
fo_libfo_format (const gchar    *xml,
		 const gchar    *xslt,
		 const gchar    *out,
		 GError        **error)
{
  FoXmlDoc *result;
  FoXmlDoc *stylesheet_doc;
  FoXmlDoc *xml_doc;
  FoXslFormatter *fo_xsl_formatter;
  FoDoc *fo_doc;
  FoAreaToPDFData fo_area_to_pdf_data = {NULL, 0};
  GError *tmp_error = NULL;

  g_return_val_if_fail (xml != NULL, FALSE);
  g_return_val_if_fail (out != NULL, FALSE);
  g_return_val_if_fail (error == NULL || *error == NULL, FALSE);

  FoLibfoContext *libfo_context = fo_libfo_context_new ();

  xml_doc = fo_xml_doc_new_from_filename (xml,
					  libfo_context,
					  &tmp_error);

  if (tmp_error != NULL)
    {
      fo_basic_bubble_up_error (error,
				FO_LIBFO_BASIC_ERROR,
				FO_LIBFO_BASIC_ERROR_FAILED,
				_(fo_libfo_basic_error_messages[FO_LIBFO_BASIC_ERROR_FAILED]),
				tmp_error);
      return FALSE;
    }

  if (xslt == NULL)
    {
      result = xml_doc;
    }
  else
    {
      stylesheet_doc = fo_xml_doc_new_from_filename (xslt,
						     libfo_context,
						     &tmp_error);

      if (tmp_error != NULL)
	{
	  fo_basic_bubble_up_error (error,
				    FO_LIBFO_BASIC_ERROR,
				    FO_LIBFO_BASIC_ERROR_FAILED,
				    _(fo_libfo_basic_error_messages[FO_LIBFO_BASIC_ERROR_FAILED]),
				    tmp_error);
	  return FALSE;
	}

      result =
	fo_xml_doc_ref (fo_xslt_transformer_do_transform (xml_doc,
							  stylesheet_doc,
							  &tmp_error));

      if (tmp_error != NULL)
	{
	  fo_basic_bubble_up_error (error,
				    FO_LIBFO_BASIC_ERROR,
				    FO_LIBFO_BASIC_ERROR_FAILED,
				    _(fo_libfo_basic_error_messages[FO_LIBFO_BASIC_ERROR_FAILED]),
				    tmp_error);
	  return FALSE;
	}
    }

  fo_xsl_formatter = fo_xsl_formatter_new ();
  fo_xsl_formatter_set_result_tree (fo_xsl_formatter,
				    result);

  fo_doc = fo_doc_new_from_type (NULL);

  fo_doc_open_file (fo_doc,
		    out,
		    libfo_context,
		    &tmp_error);

  if (tmp_error != NULL)
    {
      fo_basic_bubble_up_error (error,
				FO_LIBFO_BASIC_ERROR,
				FO_LIBFO_BASIC_ERROR_FAILED,
				_(fo_libfo_basic_error_messages[FO_LIBFO_BASIC_ERROR_FAILED]),
				tmp_error);
      return FALSE;
    }

  fo_xsl_formatter_set_fo_doc (fo_xsl_formatter,
			       fo_doc);


  fo_xsl_formatter_format (fo_xsl_formatter,
			   libfo_context,
			   &tmp_error);
  if (tmp_error != NULL)
    {
      fo_basic_bubble_up_error (error,
				FO_LIBFO_BASIC_ERROR,
				FO_LIBFO_BASIC_ERROR_FAILED,
				_(fo_libfo_basic_error_messages[FO_LIBFO_BASIC_ERROR_FAILED]),
				tmp_error);
      return FALSE;
    }

  fo_area_to_pdf_data.fo_doc = fo_doc;

  fo_area_tree_to_pdf (FO_AREA (fo_xsl_formatter_get_area_tree (fo_xsl_formatter)),
		       &fo_area_to_pdf_data);

  g_object_unref (fo_xsl_formatter);
  g_object_unref (fo_doc);
  g_object_unref (libfo_context);
  fo_libfo_shutdown ();

  return TRUE;
}
