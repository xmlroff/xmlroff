/* Fo
 * xmlroff-gmodule.c: Demonstration command line XSL formatter program
 *
 * This version formats the input document to produce an area tree and
 * then loads a loadable module.  The loadable module in this
 * demonstration just shows the FO and area trees.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <gmodule.h>
#include <stdlib.h>
#include <string.h>
#include <libfo/fo-libfo.h>
#include <libfo/libfo-compat.h>
#if ENABLE_CAIRO
#include <libfo/fo-doc-cairo.h>
#endif
#if ENABLE_GP
#include <libfo/fo-doc-gp.h>
#endif

typedef void (*ModuleLoad)   ();
typedef void (*ModuleAdjust) (GObject *fo_tree,
			      GObject *area_tree);

static FoDoc *
init_fo_doc_gp (const gchar       *out_file,
		   FoLibfoContext *libfo_context)
{
  FoDoc *fo_doc = NULL;
  GError *error = NULL;

#if ENABLE_GP
  fo_doc = fo_doc_gp_new ();

  fo_doc_open_file (fo_doc,
		    out_file,
		    libfo_context,
		    &error);

  if (error != NULL)
    {
      g_message ("Error: %s", error->message);
      exit (1);
    }
#else
  g_critical ("Output using GNOME Print is not supported by this build of libfo.");
  exit (1);
#endif /* ENABLE_GP */

  return fo_doc;
}

static FoDoc *
init_fo_doc_cairo (const gchar    *out_file,
		   FoLibfoContext *libfo_context)
{
  FoDoc *fo_doc = NULL;
  GError *error = NULL;

#if ENABLE_CAIRO
  fo_doc = fo_doc_cairo_new ();

  fo_doc_open_file (fo_doc,
		    out_file,
		    libfo_context,
		    &error);

  if (error != NULL)
    {
      g_message ("Error: %s", error->message);
      exit (1);
    }
#else
  g_critical ("Output using Cairo is not supported by this build of libfo.");
  exit (1);
#endif /* ENABLE_CAIRO */

  return fo_doc;
}

static void
exit_if_error (GError *error)
{
  if (error != NULL)
    {
      g_message ("Error: %s", error->message);
      exit (1);
    }
}

int
main (gint    argc,
      gchar **argv)
{
  GOptionContext *ctx;   /* context for parsing command-line options */
  FoXmlDoc *xml_doc = NULL;
  FoXmlDoc *result_tree = NULL;
  FoXslFormatter *fo_xsl_formatter;
  FoDoc *fo_doc = NULL;
  GError *error = NULL;
  gchar *out_file = "layout.pdf";
  const gchar *xml_file = NULL;
  const gchar *xslt_file = NULL;
  const gchar *backend_string = NULL;
  const gchar *module_string = NULL;
  gboolean version = FALSE;
  gchar** files = NULL;
  gboolean goption_success = FALSE;

  const GOptionEntry options[] = {
    { "out-file",
      'o',
      0,
      G_OPTION_ARG_STRING,
      &out_file,
      "Output file",
      "filename"
    },
    { "version",
      'v',
      0,
      G_OPTION_ARG_NONE,
      &version,
      "Print version number",
      NULL
    },
    { "backend",
      0,
      0,
      G_OPTION_ARG_STRING,
      &backend_string,
      _("Backend to use"),
      _("{cairo|gp}")
    },
    { "module",
      0,
      0,
      G_OPTION_ARG_STRING,
      &module_string,
      _("GModule to load"),
      _("filename")
    },
    { G_OPTION_REMAINING,
      0,
      0,
      G_OPTION_ARG_FILENAME_ARRAY,
      &files,
      NULL,
      "file [stylesheet]"
    },
    {NULL, 0, 0, 0, NULL, NULL, NULL}
  };

  ctx = g_option_context_new (NULL);
  g_option_context_add_main_entries (ctx, options, PACKAGE);
  goption_success = g_option_context_parse (ctx, &argc, &argv, &error);
  /* Finished with parsing command-line arguments. */
  g_option_context_free(ctx);
  ctx = NULL;

  if (goption_success == FALSE)
    {
      exit (1);
    }

  if (version != 0)
    {
      g_print ("%s\nSubmit bug reports to %s\n",
	       PACKAGE_STRING,
	       PACKAGE_BUGREPORT);
      if (files == NULL)
	{
	  /* Nothing to do if just asking for version. */
	  exit (0);
	}
    }

  if ((files == NULL) ||
      (files[0] == NULL))
    {
      g_print ("No input file specified.\n");
		  
      exit (1);
    }
  else
    {
      xml_file = files[0];
    }

  if (files[1] != NULL)
    {
      xslt_file = files[1];

      if (files[2] != NULL)
	{
	  g_print("Unexpected additional parameter: '%s'\n",
		      files[2]);
		  
	  exit (1);
	}
    }

  fo_libfo_init ();

  FoLibfoContext *libfo_context = fo_libfo_context_new ();

  if (backend_string == NULL)
    {
#if ENABLE_GP
      fo_doc = init_fo_doc_gp (out_file,
			       libfo_context);
#else
#if ENABLE_CAIRO
      fo_doc = init_fo_doc_cairo (out_file,
				  libfo_context);
#else
      g_message ("No backend type is supported by this build of libfo.");
      exit (1);
#endif /* ENABLE_CAIRO */
#endif /* ENABLE_GP */
    }
  else if (strcmp (backend_string, "cairo") == 0)
    {
      fo_doc = init_fo_doc_cairo (out_file,
				  libfo_context);
    }
  else if (strcmp (backend_string, "gp") == 0)
    {
      fo_doc = init_fo_doc_gp (out_file,
			       libfo_context);
    }
  else
    {
      g_message ("Unsupported output format: '%s'",
		 backend_string);
      exit (1);
    }

  if (xslt_file != NULL)
    {
      /* When there is an XSLT file specified, need to
	 do a transform before formatting result. */
      xml_doc = fo_xml_doc_new_from_filename (xml_file,
					      libfo_context,
					      &error);

      exit_if_error (error);

      FoXmlDoc *stylesheet_doc =
	fo_xml_doc_new_from_filename (xslt_file,
				      libfo_context,
				      &error);

      exit_if_error (error);

      result_tree = fo_xslt_transformer_do_transform (xml_doc,
						      stylesheet_doc,
						      &error);
      exit_if_error (error);

      fo_xml_doc_unref (xml_doc);
    }
  else
    {
      /* When there is no XSLT file specified, the XML file
	 is expected to be in the FO vocabulary, so just use it. */
      result_tree = fo_xml_doc_new_from_filename (xml_file,
						  libfo_context,
						  &error);

      exit_if_error (error);
    }

  /* Maybe make sure the FO XML document is safe for libfo to
     process. */
  FoXmlDoc *old_result_tree = result_tree;

  /* Remove or rewrite what libfo can't yet handle. */
  result_tree = libfo_compat_make_compatible (old_result_tree,
					      libfo_context,
					      &error);

  fo_xml_doc_unref (old_result_tree);

  exit_if_error (error);

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

  return(0);
}
