/* Fo
 * xmlroff-gmodule.c: Demonstration command line XSL formatter program
 *
 * This version formats the input document to produce an area tree and
 * then loads a loadable module.  The loadable module in this
 * demonstration just shows the FO and area trees.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 *
 * $Id: xmlroff-gmodule.c,v 1.3 2004/10/20 23:34:07 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "config.h"
#include <gmodule.h>
#include <stdlib.h>
#include <string.h>
#include <popt.h>
#include <libfo/fo-libfo.h>
#if ENABLE_GP
#include <libfo/fo-doc-gp.h>
#endif

typedef void (*ModuleLoad)   ();
typedef void (*ModuleAdjust) (GObject *fo_tree,
			      GObject *area_tree);

static FoDoc *
init_fo_doc_gp (const gchar *out_file)
{
  FoDoc *fo_doc = NULL;
  GError *error = NULL;

#if ENABLE_GP
  fo_doc = fo_doc_gp_new ();

  fo_doc_open_file (fo_doc,
		    out_file,
		    &error);

  if (error != NULL)
    {
      g_critical ("%s:: %s",
		  g_quark_to_string (error->domain),
		  error->message);
      g_error_free (error);
      exit (1);
    }
#else
  g_critical ("Output using GNOME Print is not supported by this build of libfo.");
  exit (1);
#endif /* ENABLE_GP */

  return fo_doc;
}

int
main (int          argc,
      const char **argv)
{
  poptContext optCon;   /* context for parsing command-line options */
  FoLibfoContext *libfo_context;
  FoXmlDoc *xml_doc = NULL;
  FoXmlDoc *result_tree = NULL;
  FoXsltTransformer *fo_xslt_transformer = NULL;
  FoXslFormatter *fo_xsl_formatter;
  FoDoc *fo_doc = NULL;
  GError *error = NULL;
  gchar *out_file = "layout.pdf";
  const gchar *xml_file = NULL;
  const gchar *xslt_file = NULL;
  const gchar *backend_string = NULL;
  gchar *module_string = NULL;
  FoDebugFlag debug_mode = FO_DEBUG_NONE;
  gint catalog = 0;
  gint novalid = 0;
  gint version = 0;
  gboolean popt_error = FALSE;

  const struct poptOption optionsTable[] = {
    { "out-file",
      'o',
      POPT_ARG_STRING,
      &out_file,
      0,
      _("Output file"),
      _("filename")
    },
    { "debug",
      'd',
      POPT_ARG_INT,
      &debug_mode,
      0,
      _("Debug mode"),
      _("integer")
    },
    { "catalogs",
      '\0',
      POPT_ARG_NONE,
      &catalog,
      0,
      _("Use SGML catalogs from $SGML_CATALOG_FILES instead of XML catalogs from file:///etc/xml/catalog"),
      NULL
    },
    { "novalid",
      '\0',
      POPT_ARG_NONE,
      &novalid,
      0,
      _("Skip the DTD loading phase"),
      NULL
    },
    { "version",
      'v',
      POPT_ARG_NONE,
      &version,
      0,
      _("Print version number"),
      NULL
    },
    { "backend",
      '\0',
      POPT_ARG_STRING,
      &backend_string,
      0,
      _("Pango backend"),
      _("{gp}")
    },
    { "module",
      '\0',
      POPT_ARG_STRING,
      &module_string,
      0,
      _("GModule to load"),
      _("filename")
    },
    POPT_AUTOHELP
    { NULL, '\0', 0, NULL, 0, NULL, NULL}
  };

  optCon = poptGetContext (NULL, argc, argv, optionsTable, 0);
  poptSetOtherOptionHelp (optCon, "xml-file [stylesheet]");

  poptGetNextOpt (optCon);

  fo_libfo_init ();
  libfo_context = fo_libfo_context_new ();

  if (version != 0)
    {
      g_print ("%s\nSubmit bug reports to %s\n",
	       PACKAGE_STRING,
	       PACKAGE_BUGREPORT);
    }

  if (novalid == 0)
    {
      fo_libfo_context_set_validation (libfo_context,
				       FALSE);
    }


  if (catalog != 0)
    {
      fo_libfo_context_set_sgml_catalogs (libfo_context,
					  TRUE);
    }

  if (backend_string == NULL)
    {
#if ENABLE_GP
      fo_doc = init_fo_doc_gp (out_file);
#else
      g_critical ("No output type is supported by this build of libfo.");
      popt_error = TRUE;
#endif /* ENABLE_GP */
    }
#if ENABLE_GP
  else if (strcmp (backend_string, "gp") == 0)
    {
      fo_doc = init_fo_doc_gp (out_file);
    }
#endif /* ENABLE_GP */
  else
    {
      g_critical ("Unrecognised output type: '%s'", backend_string);
      popt_error = TRUE;
    }

  if (debug_mode != FO_DEBUG_NONE)
    {
      fo_libfo_context_set_debug_mode (libfo_context,
				       debug_mode);
    }

  if (poptPeekArg (optCon))
    {
      xml_file = poptGetArg (optCon);
    }
  else
    {
      if (version != 0)
	{
	  exit (0);
	}
      else
	{
	  popt_error = TRUE;
	}
    }

  if (poptPeekArg (optCon))
    {
      xslt_file = poptGetArg (optCon);
    }

  if (poptPeekArg (optCon))
    {
      popt_error = TRUE;
    }

  if (popt_error == TRUE)
    {
      poptPrintUsage(optCon, stderr, 0);
      exit (1);
    }

  if (error != NULL)
    {
      g_critical ("%s:: %s",
		  g_quark_to_string (error->domain),
		  error->message);
      g_error_free (error);
      exit (1);
    }

  if (xslt_file != NULL)
    {
      xml_doc = fo_xml_doc_new ();
      fo_xml_doc_set_filename (xml_doc,
			       xml_file);

      fo_xml_doc_parse (xml_doc,
			libfo_context,
			&error);

      if (error != NULL)
	{
	  g_critical ("%s:: %s",
		      g_quark_to_string (error->domain),
		      error->message);
	  g_error_free (error);
	  exit (1);
	}

      fo_xslt_transformer = fo_xslt_transformer_new ();
      fo_xslt_transformer_set_filename (fo_xslt_transformer,
					xslt_file);
      fo_xslt_transformer_set_xml_doc (fo_xslt_transformer,
				       xml_doc);
      fo_xslt_transformer_transform (fo_xslt_transformer,
				    libfo_context,
				    &error);
      if (error != NULL)
	{
	  g_critical ("%s:: %s",
		      g_quark_to_string (error->domain),
		      error->message);
	  g_error_free (error);
	  exit (1);
	}

      fo_xml_doc_unref (xml_doc);
      result_tree =
	fo_xml_doc_ref (fo_xslt_transformer_get_result (fo_xslt_transformer));
      fo_xslt_transformer_unref (fo_xslt_transformer);
    }
  else
    {
      result_tree = fo_xml_doc_new ();
      fo_xml_doc_set_filename (result_tree,
			       xml_file);
      fo_xml_doc_parse (result_tree,
			libfo_context,
			&error);

      if (error != NULL)
	{
	  g_critical ("%s:: %s",
		      g_quark_to_string (error->domain),
		      error->message);
	  g_error_free (error);
	  exit (1);
	}
    }

  fo_xsl_formatter = fo_xsl_formatter_new ();

  fo_xsl_formatter_set_result_tree (fo_xsl_formatter,
				    result_tree);

  fo_xsl_formatter_set_fo_doc (fo_xsl_formatter,
			       fo_doc);

  fo_xsl_formatter_format (fo_xsl_formatter,
			   libfo_context,
			   &error);
  if (error != NULL)
    {
      g_message ("Error: %s", error->message);
      exit (1);
    }

  if (module_string != NULL)
    {
      GModule *module = g_module_open (module_string, 0);

      g_message ("Module: %p", module);

      if (module == NULL) {
	g_message ("Module error: %s", g_module_error ());
      }

      ModuleLoad module_load = NULL;

      gboolean success = g_module_symbol (module,
					  "load",
					  (gpointer) &module_load);
      g_message ("ModuleLoad: %p", module_load);

      if (module_load == NULL) {
	g_message ("Module error: %s", g_module_error ());
      }

      (module_load) ();

      ModuleAdjust module_adjust = NULL;

      success = g_module_symbol (module,
				 "adjust",
				 (gpointer) &module_adjust);
      g_message ("ModuleAdjust: %p", module_adjust);

      if (module_adjust == NULL) {
	g_message ("Module error: %s", g_module_error ());
      }

      (module_adjust) (fo_xsl_formatter_get_fo_tree (fo_xsl_formatter),
		       fo_xsl_formatter_get_area_tree (fo_xsl_formatter));
    }

  fo_xsl_formatter_draw (fo_xsl_formatter,
			 libfo_context,
			 &error);

  if (error != NULL)
    {
      g_message ("Error: %s", error->message);
      exit (1);
    }

  g_object_unref (fo_xsl_formatter);
  g_object_unref (fo_doc);
  fo_libfo_shutdown ();

  poptFreeContext (optCon);

  return(0);
}
