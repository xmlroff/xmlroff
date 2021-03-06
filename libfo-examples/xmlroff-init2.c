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
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <stdlib.h>
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
main (gint    argc,
      gchar **argv)
{
  GError *error = NULL;
  /* Variables set from command-line options. */
  gchar *out_file = "layout.pdf";
  const gchar *xml_file = NULL;
  const gchar *xslt_file = NULL;
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

   GOptionContext *ctx = g_option_context_new (NULL);
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

  fo_libfo_init2 (&my_malloc,
		  &my_realloc,
		  &my_free);

  fo_libfo_format (xml_file,
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

  fo_libfo_shutdown ();

  return (0);
}
