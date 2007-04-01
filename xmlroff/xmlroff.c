/* Fo
 * xmlroff.c: Demonstration command line XSL formatter program
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: xmlroff.c,v 1.22 2006/04/16 20:28:57 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <popt.h>
#include <libfo/fo-libfo.h>
#include <libfo/libfo-compat.h>
#if ENABLE_CAIRO
#include <libfo/fo-doc-cairo.h>
#endif
#if ENABLE_GP
#include <libfo/fo-doc-gp.h>
#endif
#include "libfo/libfo-compat.h"

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
main (int          argc,
      const char **argv)
{
  poptContext optCon;   /* context for parsing command-line options */
  FoLibfoContext *libfo_context;
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
  const gchar *embed_string = NULL;
  FoEnumFontEmbed embed_mode = FO_ENUM_FONT_EMBED_INVALID;
  FoEnumFormat format_mode = FO_ENUM_FORMAT_UNKNOWN;
  FoDebugFlag debug_mode = FO_DEBUG_NONE;
  FoWarningFlag warning_mode = FO_WARNING_FO | FO_WARNING_PROPERTY;
  gint compat_stylesheet = 0;
  gint compat = 0;
  gint continue_after_error = 0;
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
    /*
    { "embed",
      '\0',
      POPT_ARG_STRING,
      &embed_string,
      0,
      _("Font embedding mode"),
      _("{none|nonbase|all}")
    },
    */
    { "novalid",
      '\0',
      POPT_ARG_NONE,
      &novalid,
      0,
      _("Skip the DTD loading phase"),
      NULL
    },
    { "compat",
      '\0',
      POPT_ARG_NONE,
      &compat,
      0,
      _("Make the input compatible with xmlroff"),
      NULL
    },
    { "compat-stylesheet",
      '\0',
      POPT_ARG_NONE,
      &compat_stylesheet,
      0,
      _("Output the compatibility stylesheet then exit"),
      NULL
    },
    { "continue",
      '\0',
      POPT_ARG_NONE,
      &continue_after_error,
      0,
      _("Continue after any formatting errors"),
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
      _("Backend to use"),
      _("{cairo|gp}")
    },
    { "format",
      '\0',
      POPT_ARG_STRING,
      &format_string,
      0,
      _("Format of output file"),
      _("{auto|pdf|postscript|svg}")
    },
    { "warn",
      'w',
      POPT_ARG_INT,
      &warning_mode,
      0,
      _("Warning mode"),
      _("integer")
    },
    POPT_AUTOHELP
    { NULL, '\0', 0, NULL, 0, NULL, NULL}
  };

  optCon = poptGetContext (NULL, argc, argv, optionsTable, 0);
  /* FIXME: Support xml-stylesheet PI in xml-file */
  poptSetOtherOptionHelp (optCon, _("xml-file [stylesheet]"));

  poptGetNextOpt (optCon);

  if (compat_stylesheet != 0)
    {
      printf (libfo_compat_get_stylesheet ());
      exit (0);
    }

  fo_libfo_init ();
  libfo_context = fo_libfo_context_new ();

  fo_libfo_context_set_warning_mode (libfo_context,
				     warning_mode);

  if (version != 0)
    {
      g_print (_("%s\nSubmit bug reports to %s\n"),
	       PACKAGE_STRING,
	       PACKAGE_BUGREPORT);
    }

  if (embed_string != NULL)
    {
      if (strcmp (embed_string, "none") == 0)
	{
	  embed_mode = FO_ENUM_FONT_EMBED_NONE;
	}
      else if (strcmp (embed_string, "nonbase") == 0)
	{
	  embed_mode = FO_ENUM_FONT_EMBED_NONBASE;
	}
      else if (strcmp (embed_string, "all") == 0)
	{
	  embed_mode = FO_ENUM_FONT_EMBED_ALL;
	}
      else
	{
	  popt_error = TRUE;
	}

      if (popt_error != TRUE)
	{
	  fo_libfo_context_set_font_embed (libfo_context,
					   embed_mode);
	}
    }


  if (novalid == 0)
    {
      fo_libfo_context_set_validation (libfo_context,
				       FALSE);
    }

  if (continue_after_error != 0)
    {
      fo_libfo_context_set_continue_after_error (libfo_context,
						 TRUE);
    }

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
      popt_error = TRUE;
    }

  if (popt_error != TRUE)
    {
      fo_libfo_context_set_format (libfo_context,
				   format_mode);
    }

  if (backend_string == NULL)
    {
#if ENABLE_GP
      fo_doc = init_fo_doc_gp (out_file, libfo_context);
#else
      g_critical ("No output type is supported by this build of libfo.");
      popt_error = TRUE;
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
      g_critical ("Unrecognised output type: '%s'", backend_string);
      popt_error = TRUE;
    }

  if (debug_mode != FO_DEBUG_NONE)
    {
      fo_libfo_context_set_debug_mode (libfo_context,
				       debug_mode);
    }

      fo_libfo_context_set_warning_mode (libfo_context,
					 warning_mode);

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

  if (xslt_file != NULL)
    {
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
						      libfo_context,
						      &error);
      exit_if_error (error);

      fo_xml_doc_unref (xml_doc);
      fo_xml_doc_unref (stylesheet_doc);
    }
  else
    {
      result_tree = fo_xml_doc_new_from_filename (xml_file,
						  libfo_context,
						  &error);

      exit_if_error (error);
    }

  if (compat != 0)
    {
      FoXmlDoc *old_result_tree = result_tree;

      result_tree = libfo_compat_make_compatible (old_result_tree,
						  libfo_context,
						  &error);

      fo_xml_doc_unref (old_result_tree);

      exit_if_error (error);
    }

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

  poptFreeContext (optCon);

  return(0);
}
