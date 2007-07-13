/* Fo
 * xmlroff-init2.c: Demonstration command line XSL formatter program
 *
 * This program uses the functions in fo-libfo-basic.h to format an
 * XML file into a PDF file without operating in terms of GObjects.
 *
 * This program uses fo_libfo_init2() to set memory allocation
 * functions.
 *
 * Copyright (C) 2001, 2002, 2003 Sun Microsystems
 *
 * $Id: xmlroff-init2.c,v 1.2 2003/07/07 21:10:56 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <stdlib.h>
#include <popt.h>
#include <glib.h>
#include <libfo/fo-libfo-basic.h>

static gpointer
my_malloc (gsize    n_bytes)
{
  return malloc (n_bytes);
}

static gpointer
my_realloc (gpointer mem,
	    gsize    n_bytes)
{
  return realloc (mem, n_bytes);
}

static void
my_free (gpointer mem)
{
  free (mem);
}

int
main (int          argc,
      const char **argv)
{
  poptContext optCon;   /* context for parsing command-line options */
  FoLibfoContext *libfo_context;
  GError *error = NULL;
  gchar *out_file = "layout.pdf";
  const gchar *xml_file, *xslt_file = NULL;
  gint version = 0;

  const struct poptOption optionsTable[] = {
    { "out-file",
      'o',
      POPT_ARG_STRING,
      &out_file,
      0,
      "Output file",
      "filename"
    },
    { "version",
      'v',
      POPT_ARG_NONE,
      &version,
      0,
      "Print version number",
      NULL
    },
    POPT_AUTOHELP
    { NULL, '\0', 0, NULL, 0, NULL, NULL}
  };

  optCon = poptGetContext (NULL, argc, argv, optionsTable, 0);
  poptSetOtherOptionHelp (optCon, "xml-file [stylesheet]");

  poptGetNextOpt (optCon);

  if (version != 0)
    {
      g_print ("%s\nSubmit bug reports to %s\n",
	       PACKAGE_STRING,
	       PACKAGE_BUGREPORT);
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
	  poptPrintUsage(optCon, stderr, 0);
	  exit (1);
	}
    }

  if (poptPeekArg (optCon))
    {
      xslt_file = poptGetArg (optCon);
    }

  if (poptPeekArg (optCon))
    {
      poptPrintUsage(optCon, stderr, 0);
      exit (1);
    }

  poptFreeContext (optCon);

  fo_libfo_init2 (&my_malloc,
		  &my_realloc,
		  &my_free);

  libfo_context = fo_libfo_context_new ();

  fo_libfo_format (libfo_context,
		   xml_file,
		   xslt_file,
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

  fo_libfo_context_close (libfo_context);
  fo_libfo_shutdown ();

  return (0);
}
