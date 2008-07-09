/* Fo
 * xmlroff.c: Demonstration command line XSL formatter program
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <libfo/fo-libfo.h>
#include <libfo/libfo-compat.h>
#include <libfo/libfo-version.h>
#if ENABLE_CAIRO
#include <libfo/fo-doc-cairo.h>
#endif
#if ENABLE_GP
#include <libfo/fo-doc-gp.h>
#endif

typedef enum
{
  XMLROFF_ERROR_FAILED,
  XMLROFF_ERROR_NO_FILE,	    /* No input file specified */
  XMLROFF_ERROR_ADDITIONAL_PARAM,   /* Unexpected additional parameter */
  XMLROFF_ERROR_UNSUPPORTED_FORMAT, /* Unsupported output format */
  XMLROFF_ERROR_UNSUPPORTED_BACKEND,/* Unsupported backend */
  XMLROFF_ERROR_NO_BACKEND,         /* No backend type by this libfo */
  XMLROFF_ERROR_LAST
} XmlroffError;

const char *xmlroff_error_messages [] = {
  N_("xmlroff error"),
  N_("No input file specified."),
  N_("Unexpected additional parameter: '%s'"),
  N_("Unsupported output format: '%s'"),
  N_("Unsupported backend: '%s'"),
  N_("No backend type is supported by this build of libfo.")
};

#define XMLROFF_ERROR xmlroff_error_quark ()

/**
 * xmlroff_error_quark:
 *
 * Get the error quark for xmlroff.
 *
 * If the quark does not yet exist, create it.
 *
 * Return value: Quark associated with xmlroff errors.
 **/
static GQuark
xmlroff_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("xmlroff error");
  return quark;
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
      g_warning ("%s:: %s",
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
  GOptionContext *ctx;   /* context for parsing command-line options */
  FoLibfoContext *libfo_context;
  FoXmlDoc *xml_doc = NULL;
  FoXmlDoc *result_tree = NULL;
  FoXslFormatter *fo_xsl_formatter;
  FoDoc *fo_doc = NULL;
  GError *error = NULL;
  gchar *out_file = "layout.pdf";
  const gchar *xml_file = NULL;
  const gchar *xslt_file = NULL;
  const gchar *backend_string = NULL;
  const gchar *format_string = NULL;
  const gchar *id_file = NULL;
  FoFlagsFormat format_mode = FO_FLAG_FORMAT_UNKNOWN;
  FoDebugFlag debug_mode = FO_DEBUG_NONE;
  FoWarningFlag warning_mode = FO_WARNING_FO | FO_WARNING_PROPERTY;
  gboolean compat_stylesheet = FALSE;
  gboolean compat = TRUE;
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
    { "compat",
      0,
      0,
      G_OPTION_ARG_NONE,
      &compat,
      /* Describe both --compat and --nocompat since --nocompat is
	 hidden. */
      _("Do ('--compat') or do not ('--nocompat') preprocess with compatibility stylesheet "
	"(default is '--compat')"),
      NULL
    },
    { "nocompat",
      0,
      G_OPTION_FLAG_HIDDEN | G_OPTION_FLAG_REVERSE,
      G_OPTION_ARG_NONE,
      &compat,
      _("Do not use compatibility stylesheet"),
      NULL
    },
    { "compat-stylesheet",
      0,
      0,
      G_OPTION_ARG_NONE,
      &compat_stylesheet,
      _("Output the compatibility stylesheet then exit"),
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
    { "id-file",
      0,
      0,
      G_OPTION_ARG_STRING,
      &id_file,
      _("ID-page file"),
      _("filename")
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

  /* FIXME: Support xml-stylesheet PI in xml-file */

  ctx = g_option_context_new (NULL);

#ifdef HAVE_G_OPTION_CONTEXT_SET_SUMMARY
  g_option_context_set_summary(ctx,
    "xmlroff is a free, fast and high-quality XSL formatter that is\n"
    "useful for DocBook formatting. It produces PDF or PostScript output.\n"
    "It integrates easily with other programs and with scripting\n"
    "languages.\n\n"
    "xmlroff processes the XML-FO 'file', or an arbitrary\n"
    "XML file can optionally be first transformed via a specified XSLT\n"
    "'stylesheet'.");
#endif /* HAVE_G_OPTION_CONTEXT_SET_SUMMARY */

  g_option_context_add_main_entries (ctx, options, PACKAGE);
  goption_success = g_option_context_parse (ctx, &argc, &argv, &error);
  /* Finished with parsing command-line arguments. */
  g_option_context_free(ctx);
  ctx = NULL;

  if (goption_success == FALSE)
    {
      goto option_error;
    }

  if (compat_stylesheet == TRUE)
    {
      printf (libfo_compat_get_stylesheet ());
      exit (0);
    }

  if (version != 0)
    {
      g_print (_("%s\nlibfo version: %s\nSubmit bug reports to %s\n"),
	       PACKAGE_STRING,
	       libfo_version_string (),
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
      g_set_error(&error,
		  XMLROFF_ERROR,
		  XMLROFF_ERROR_NO_FILE,
		  xmlroff_error_messages [XMLROFF_ERROR_NO_FILE]);

      goto option_error;
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
	  g_set_error(&error,
		      XMLROFF_ERROR,
		      XMLROFF_ERROR_ADDITIONAL_PARAM,
		      xmlroff_error_messages [XMLROFF_ERROR_ADDITIONAL_PARAM],
		      files[2]);

	  goto option_error;
	}
    }

  fo_libfo_init ();
  libfo_context = fo_libfo_context_new ();

  fo_libfo_context_set_validation (libfo_context,
				   validation);

  fo_libfo_context_set_continue_after_error (libfo_context,
					     continue_after_error);

  /* Need to do 'format' before 'backend'. */
  if (format_string == NULL)
    {
      format_mode = FO_FLAG_FORMAT_AUTO;
    }
  else
    {
      gchar *lower_format = g_ascii_strdown (format_string,
					     -1);
      if (strcmp (lower_format, "auto") == 0)
	{
	  format_mode = FO_FLAG_FORMAT_AUTO;
	}
      else if (strcmp (lower_format, "pdf") == 0)
	{
	  format_mode = FO_FLAG_FORMAT_PDF;
	}
      else if (strcmp (lower_format, "postscript") == 0)
	{
	  format_mode = FO_FLAG_FORMAT_POSTSCRIPT;
	}
      else if (strcmp (lower_format, "svg") == 0)
	{
	  format_mode = FO_FLAG_FORMAT_SVG;
	}
      else
	{
	  g_set_error(&error,
		      XMLROFF_ERROR,
		      XMLROFF_ERROR_UNSUPPORTED_FORMAT,
		      xmlroff_error_messages [XMLROFF_ERROR_UNSUPPORTED_FORMAT],
		      lower_format);
	  g_free (lower_format);
	  goto option_error;
	}
      g_free (lower_format);
    }

  fo_libfo_context_set_format (libfo_context,
			       format_mode);

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
      g_set_error(&error,
		  XMLROFF_ERROR,
		  XMLROFF_ERROR_NO_BACKEND,
		  xmlroff_error_messages [XMLROFF_ERROR_NO_BACKEND]);

      goto option_error;
#endif /* ENABLE_CAIRO */
#endif /* ENABLE_GP */
    }
  else
    {
      gchar *lower_backend = g_ascii_strdown (backend_string,
					      -1);
      if (strcmp (lower_backend, "cairo") == 0)
	{
	  fo_doc = init_fo_doc_cairo (out_file, libfo_context);
	}
      else if (strcmp (lower_backend, "gp") == 0)
	{
	  fo_doc = init_fo_doc_gp (out_file, libfo_context);
	}
      else
	{
	  g_set_error(&error,
		      XMLROFF_ERROR,
		      XMLROFF_ERROR_UNSUPPORTED_BACKEND,
		      xmlroff_error_messages [XMLROFF_ERROR_UNSUPPORTED_BACKEND],
		      lower_backend);
	  g_free (lower_backend);
	  goto option_error;
	}
      g_free (lower_backend);
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
  if (compat == TRUE)
    {
      FoXmlDoc *old_result_tree = result_tree;

      /* Remove or rewrite what libfo can't yet handle. */
      result_tree = libfo_compat_make_compatible (old_result_tree,
						  libfo_context,
						  &error);

      fo_xml_doc_unref (old_result_tree);

      exit_if_error (error);
    }

  fo_xsl_formatter = fo_xsl_formatter_new ();

  fo_xsl_formatter_set_result_tree (fo_xsl_formatter,
				    result_tree);
  exit_if_error (error);

  fo_xsl_formatter_set_fo_doc (fo_xsl_formatter,
			       fo_doc);

  fo_xsl_formatter_format (fo_xsl_formatter,
			   libfo_context,
			   &error);

  exit_if_error (error);

  if (id_file != NULL)
    {
      fo_xsl_formatter_write_id_file (fo_xsl_formatter,
				      NULL,
				      NULL);
    }

  fo_xsl_formatter_draw (fo_xsl_formatter,
			 libfo_context,
			 &error);

  exit_if_error (error);

  g_object_unref (fo_xsl_formatter);
  g_object_unref (fo_doc);
  fo_libfo_shutdown ();

  return(0);

 option_error:
  /* To get to here, there must be an error in command-line arguments. */

  if (error != NULL)
    {
      g_print ("%s\n\n",
	       error->message);
      g_error_free (error);
    }

  /* Desperate effort to output the usage message. */
  gint fake_argc = 2;
  gchar *fake_argv[] = {"xmlroff", "--help"};
  gchar **fake_argv_ptr = fake_argv;
  ctx = g_option_context_new (NULL);
  g_option_context_add_main_entries (ctx, options, PACKAGE);
  g_option_context_parse (ctx, &fake_argc, &fake_argv_ptr, NULL);
  g_option_context_free(ctx);

  exit (1);

}
