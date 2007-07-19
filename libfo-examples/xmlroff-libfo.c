/* Fo
 * xmlroff-libfo.c: Demonstration command line XSL formatter program
 *
 * This version works with objects (typically boxed objects) for the
 * input XML document, the XSLT transformer, the XSL formatter, and
 * the output document.  This is at a finer granularity than the
 * functions in fo-libfo-basic.h, but working at this level allows
 * more control.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
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
      g_critical ("%s:: %s",
		  g_quark_to_string (error->domain),
		  error->message);
      g_error_free (error);
      exit (1);
    }
#else
  g_critical (_("Output using Cairo is not supported by this build of libfo."));
  exit (1);
#endif /* ENABLE_CAIRO */

  return fo_doc;
}

static FoDoc *
init_fo_doc_gp (const gchar    *out_file,
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

static void
exit_if_error (GError *error)
{
  if (error != NULL)
    {
      g_error ("%s:: %s",
	       g_quark_to_string (error->domain),
	       error->message);
      g_error_free (error);
      exit (1);
    }
}

int
main (gint    argc,
      gchar **argv)
{
  FoXmlDoc *xml_doc = NULL;
  FoXmlDoc *stylesheet_doc = NULL;
  FoXmlDoc *result_tree = NULL;
  FoXslFormatter *fo_xsl_formatter;
  FoDoc *fo_doc = NULL;
  GError *error = NULL;
  gchar *out_file = "layout.pdf";
  const gchar *xml_file = NULL;
  const gchar *xslt_file = NULL;
  const gchar *backend_string = NULL;
  const gchar *format_string = NULL;
  FoEnumFormat format_mode = FO_ENUM_FORMAT_UNKNOWN;
  FoDebugFlag debug_mode = FO_DEBUG_NONE;
  FoWarningFlag warning_mode = FO_WARNING_FO | FO_WARNING_PROPERTY;
  gboolean continue_after_error = FALSE;
  gboolean validation = FALSE;
  gboolean version = FALSE;
  gchar** files = NULL;
  gboolean goption_success = FALSE;

  const GOptionEntry options[] = {
    { "out-file",
      'o',
      0,
      G_OPTION_ARG_STRING,
      &out_file,
      _("Output file"),
      _("filename")
    },
    { "format",
      0,
      0,
      G_OPTION_ARG_STRING,
      &format_string,
      _("Format of output file"),
      _("{auto|pdf|postscript|svg}")
    },
    { "backend",
      0,
      0,
      G_OPTION_ARG_STRING,
      &backend_string,
      _("Backend to use"),
      _("{cairo|gp}")
    },
    { "continue",
      0,
      0,
      G_OPTION_ARG_NONE,
      &continue_after_error,
      _("Continue after any formatting errors"),
      NULL
    },
    { "valid",
      0,
      0,
      G_OPTION_ARG_NONE,
      &validation,
      /* Describe both --valid and --novalid since --novalid is hidden. */
      _("Do ('--valid') or do not ('--novalid') load the DTD "
	"(default is '--novalid')"),
      NULL
    },
    { "novalid",
      0,
      G_OPTION_FLAG_HIDDEN | G_OPTION_FLAG_REVERSE,
      G_OPTION_ARG_NONE,
      &validation,
      _("Skip the DTD loading phase"),
      NULL
    },
    { "version",
      'v',
      0,
      G_OPTION_ARG_NONE,
      &version,
      _("Print version number"),
      NULL
    },
    { "warn",
      'w',
      0,
      G_OPTION_ARG_INT,
      &warning_mode,
      _("Warning mode"),
      _("integer")
    },
    { "debug",
      'd',
      0,
      G_OPTION_ARG_INT,
      &debug_mode,
      _("Debug mode"),
      _("integer")
    },
    { G_OPTION_REMAINING,
      0,
      0,
      G_OPTION_ARG_FILENAME_ARRAY,
      &files,
      NULL,
      _("file [stylesheet]")
    },
    {NULL, 0, 0, 0, NULL, NULL, NULL}
  };

  GOptionContext *ctx = g_option_context_new (NULL);
  g_option_context_add_main_entries (ctx, options, PACKAGE);
  goption_success = g_option_context_parse (ctx, &argc, &argv, &error);
  /* Finished with parsing command-line arguments. */
  g_option_context_free(ctx);

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

  fo_libfo_context_set_validation (libfo_context,
				   validation);

  fo_libfo_context_set_continue_after_error (libfo_context,
					     continue_after_error);

  /* Need to do 'format' before 'backend'. */
  if ((format_string == NULL) ||
      (strcmp (format_string, "auto") == 0))
    {
      format_mode = FO_ENUM_FORMAT_AUTO;
    }
  else if (strcmp (format_string, "pdf") == 0)
    {
      format_mode = FO_ENUM_FORMAT_PDF;
    }
  else if (strcmp (format_string, "postscript") == 0)
    {
      format_mode = FO_ENUM_FORMAT_POSTSCRIPT;
    }
  else if (strcmp (format_string, "svg") == 0)
    {
      format_mode = FO_ENUM_FORMAT_SVG;
    }
  else
    {
      g_print("Unsupported output format: '%s'\n",
	      format_string);

      exit (1);
    }

  if (goption_success == TRUE)
    {
      fo_libfo_context_set_format (libfo_context,
				   format_mode);
    }

  if (backend_string == NULL)
    {
#if ENABLE_GP
      fo_doc = init_fo_doc_gp (out_file, libfo_context);
#else
#if ENABLE_CAIRO
      fo_doc = init_fo_doc_cairo (out_file, libfo_context);
#else
      g_print("No backend type is supported by this build of libfo.\n");

      exit (1);
#endif /* ENABLE_CAIRO */
#endif /* ENABLE_GP */
    }
  else if (strcmp (backend_string, "cairo") == 0)
    {
      fo_doc = init_fo_doc_cairo (out_file, libfo_context);
    }
  else if (strcmp (backend_string, "gp") == 0)
    {
      fo_doc = init_fo_doc_gp (out_file, libfo_context);
    }
  else
    {
      g_print ("Unrecognised output type: '%s'\n", backend_string);

      exit (1);
    }

  if (debug_mode != FO_DEBUG_NONE)
    {
      fo_libfo_context_set_debug_mode (libfo_context,
				       debug_mode);
    }

  fo_libfo_context_set_warning_mode (libfo_context,
				     warning_mode);

  if (xslt_file != NULL)
    {
      /* When there is an XSLT file specified, need to
	 do a transform before formatting result. */
      xml_doc = fo_xml_doc_new_from_filename (xml_file,
					      libfo_context,
					      &error);

      exit_if_error (error);

      stylesheet_doc = fo_xml_doc_new_from_filename (xslt_file,
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

  /* Make sure the FO XML document is safe for libfo to process. */
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

  exit_if_error (error);

  fo_xsl_formatter_draw (fo_xsl_formatter,
			 libfo_context,
			 &error);

  exit_if_error (error);

  g_object_unref (fo_xsl_formatter);
  g_object_unref (fo_doc);
  fo_libfo_shutdown ();

  return(0);
}
