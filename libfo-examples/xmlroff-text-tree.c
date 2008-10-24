/* Fo
 * xmlroff-libfo.c: Demonstration command line XSL formatter program
 *
 * This version demonstrates accessing the FO tree as FoNode objects.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <libfo/fo-libfo.h>
#include <libfo/fo-node.h>
#define GTK_ENABLE_BROKEN
#include <gtk/gtk.h>
#include <libfo/libfo-compat.h>
#if ENABLE_CAIRO
#include <libfo/fo-doc-cairo.h>
#endif
#if ENABLE_GP
#include <libfo/fo-doc-gp.h>
#endif

void close_application( GtkWidget *widget G_GNUC_UNUSED,
                        gpointer   data G_GNUC_UNUSED)
{
       gtk_main_quit ();
}

/**
 * insert_tree:
 * @text:   Text widget
 * @object: #FoObject to be dumped.
 * @depth:  Relative indent to add to the output.
 * 
 * Dumps node tree anchored at @object to @text.
 **/
static void
insert_tree (GtkWidget *text,
	     FoNode    *fo_node,
	     gint       depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *fo_node_sprintf, *text_string;
  FoNode *child;
  GdkFont *fixed_font =
    gdk_font_load ("-misc-fixed-medium-r-*-*-*-140-*-*-*-*-*-*");

  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_NODE (fo_node));

  fo_node_sprintf = fo_object_sprintf (fo_node);

  text_string =
    g_strdup_printf ("%s%s\n",
		     indent,
		     fo_node_sprintf);

  gtk_text_insert (GTK_TEXT (text), fixed_font, &text->style->black, NULL,
		   text_string, -1);

  g_free (text_string);
  g_free (fo_node_sprintf);
  g_free (indent);

  child = fo_node_first_child (fo_node);
  while (child)
    {
      insert_tree (text,
		   child,
		   depth + 1);

      child = fo_node_next_sibling (child);
    }
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
  /* Variables set from command-line options. */
  gchar *out_file = "layout.pdf";
  const gchar *xml_file = NULL;
  const gchar *xslt_file = NULL;
  const gchar *backend_string = NULL;
  const gchar *format_string = NULL;
  FoFlagsFormat format_mode = FO_FLAG_FORMAT_UNKNOWN;
  FoDebugFlag debug_mode = FO_DEBUG_NONE;
  FoWarningFlag warning_mode = FO_WARNING_FO | FO_WARNING_PROPERTY;
  gboolean continue_after_error = FALSE;
  gboolean validation = FALSE;
  gboolean version = FALSE;
  gchar** files = NULL;
  gboolean goption_success = FALSE;

  gtk_init (&argc, &argv);
 
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
      format_mode = FO_FLAG_FORMAT_AUTO;
    }
  else if (strcmp (format_string, "pdf") == 0)
    {
      format_mode = FO_FLAG_FORMAT_PDF;
    }
  else if (strcmp (format_string, "postscript") == 0)
    {
      format_mode = FO_FLAG_FORMAT_POSTSCRIPT;
    }
  else if (strcmp (format_string, "svg") == 0)
    {
      format_mode = FO_FLAG_FORMAT_SVG;
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

  FoNode *fo_tree = FO_NODE (fo_xsl_formatter_get_fo_tree (fo_xsl_formatter));

  GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window, 600, 500);
  gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, FALSE);  
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (close_application),
                    NULL);
  gtk_window_set_title (GTK_WINDOW (window), "Formatting Object Tree View");
  gtk_container_set_border_width (GTK_CONTAINER (window), 0);
  
  
  GtkWidget *box1 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), box1);
  gtk_widget_show (box1);
  
  
  GtkWidget *box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, TRUE, TRUE, 0);
  gtk_widget_show (box2);
  
  
  GtkWidget *table = gtk_table_new (2, 2, FALSE);
  gtk_table_set_row_spacing (GTK_TABLE (table), 0, 2);
  gtk_table_set_col_spacing (GTK_TABLE (table), 0, 2);
  gtk_box_pack_start (GTK_BOX (box2), table, TRUE, TRUE, 0);
  gtk_widget_show (table);
  
  /* Create the GtkText widget */
  GtkWidget *text = gtk_text_new (NULL, NULL);
  gtk_text_set_editable (GTK_TEXT (text), FALSE);
  gtk_table_attach (GTK_TABLE (table), text, 0, 1, 0, 1,
		    GTK_EXPAND | GTK_SHRINK | GTK_FILL,
		    GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (text);

  /* Add a vertical scrollbar to the GtkText widget */
  GtkWidget *vscrollbar = gtk_vscrollbar_new (GTK_TEXT (text)->vadj);
  gtk_table_attach (GTK_TABLE (table), vscrollbar, 1, 2, 0, 1,
		    GTK_FILL, GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (vscrollbar);

  /* Get the system color map and allocate the color red */
  GdkColormap *cmap = gdk_colormap_get_system ();
  GdkColor color;
  color.red = 0xffff;
  color.green = 0;
  color.blue = 0;
  if (!gdk_color_alloc (cmap, &color)) {
    g_error ("couldn't allocate color");
  }

  /* Realizing a widget creates a window for it,
   * ready for us to insert some text */
  gtk_widget_realize (text);

  /* Freeze the text widget, ready for multiple updates */
  gtk_text_freeze (GTK_TEXT (text));
  
  insert_tree (text, fo_tree, 0);

  /* Thaw the text widget, allowing the updates to become visible */  
  gtk_text_thaw (GTK_TEXT (text));
  
  GtkWidget *hbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (box2), hbox, FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, TRUE, 0);
  gtk_widget_show (box2);
  
  GtkWidget *button = gtk_button_new_with_label ("close");
  g_signal_connect (G_OBJECT (button), "clicked",
	            G_CALLBACK (close_application),
	            NULL);
  gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
  GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
  gtk_widget_grab_default (button);
  gtk_widget_show (button);

  gtk_widget_show (window);

  gtk_main ();

  g_object_unref (fo_xsl_formatter);
  g_object_unref (fo_doc);
  fo_libfo_shutdown ();

  return(0);
}
