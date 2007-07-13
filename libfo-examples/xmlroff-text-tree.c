/* Fo
 * xmlroff-libfo.c: Demonstration command line XSL formatter program
 *
 * This version demonstrates accessing the FO tree as FoNode objects.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 *
 * $Id: xmlroff-text-tree.c,v 1.4 2004/10/20 23:34:07 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#define GTK_ENABLE_BROKEN
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <popt.h>
#include <libfo/fo-libfo.h>
#include <fo-node.h>
#include <gtk/gtk.h>
#if ENABLE_GP
#include <libfo/fo-doc-gp.h>
#endif

void close_application( GtkWidget *widget,
                        gpointer   data )
{
       gtk_main_quit ();
}

/**
 * fo_node_debug_dump:
 * @object: #FoObject to be dumped.
 * @depth:  Relative indent to add to the output.
 * 
 * Implements #FoObject debug_dump method for #FoNode.
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
main (int    argc,
      char **argv)
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
  FoDebugFlag debug_mode = FO_DEBUG_NONE;
  gint catalog = 0;
  gint novalid = 0;
  gint version = 0;
  gboolean popt_error = FALSE;
  GtkWidget *window;
  GtkWidget *box1;
  GtkWidget *box2;
  GtkWidget *hbox;
  GtkWidget *button;
  GtkWidget *check;
  GtkWidget *separator;
  GtkWidget *table;
  GtkWidget *vscrollbar;
  GtkWidget *text;
  GdkColormap *cmap;
  GdkColor color;
  GdkFont *fixed_font;

  FILE *infile;

  gtk_init (&argc, &argv);
 
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
    POPT_AUTOHELP
    { NULL, '\0', 0, NULL, 0, NULL, NULL}
  };

  optCon = poptGetContext (NULL, argc, (const char **) argv, optionsTable, 0);
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

  fo_xsl_formatter_draw (fo_xsl_formatter,
			 libfo_context,
			 &error);

  if (error != NULL)
    {
      g_message ("Error: %s", error->message);
      exit (1);
    }

  FoNode *fo_tree = FO_NODE (fo_xsl_formatter_get_fo_tree (fo_xsl_formatter));

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window, 600, 500);
  gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, FALSE);  
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (close_application),
                    NULL);
  gtk_window_set_title (GTK_WINDOW (window), "Formatting Object Tree View");
  gtk_container_set_border_width (GTK_CONTAINER (window), 0);
  
  
  box1 = gtk_vbox_new (FALSE, 0);
  gtk_container_add (GTK_CONTAINER (window), box1);
  gtk_widget_show (box1);
  
  
  box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, TRUE, TRUE, 0);
  gtk_widget_show (box2);
  
  
  table = gtk_table_new (2, 2, FALSE);
  gtk_table_set_row_spacing (GTK_TABLE (table), 0, 2);
  gtk_table_set_col_spacing (GTK_TABLE (table), 0, 2);
  gtk_box_pack_start (GTK_BOX (box2), table, TRUE, TRUE, 0);
  gtk_widget_show (table);
  
  /* Create the GtkText widget */
  text = gtk_text_new (NULL, NULL);
  gtk_text_set_editable (GTK_TEXT (text), FALSE);
  gtk_table_attach (GTK_TABLE (table), text, 0, 1, 0, 1,
		    GTK_EXPAND | GTK_SHRINK | GTK_FILL,
		    GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (text);

  /* Add a vertical scrollbar to the GtkText widget */
  vscrollbar = gtk_vscrollbar_new (GTK_TEXT (text)->vadj);
  gtk_table_attach (GTK_TABLE (table), vscrollbar, 1, 2, 0, 1,
		    GTK_FILL, GTK_EXPAND | GTK_SHRINK | GTK_FILL, 0, 0);
  gtk_widget_show (vscrollbar);

  /* Get the system color map and allocate the color red */
  cmap = gdk_colormap_get_system ();
  color.red = 0xffff;
  color.green = 0;
  color.blue = 0;
  if (!gdk_color_alloc (cmap, &color)) {
    g_error ("couldn't allocate color");
  }

  /* Load a fixed font */
  fixed_font = gdk_font_load ("-misc-fixed-medium-r-*-*-*-140-*-*-*-*-*-*");

  /* Realizing a widget creates a window for it,
   * ready for us to insert some text */
  gtk_widget_realize (text);

  /* Freeze the text widget, ready for multiple updates */
  gtk_text_freeze (GTK_TEXT (text));
  
  insert_tree (text, fo_tree, 0);

  /* Thaw the text widget, allowing the updates to become visible */  
  gtk_text_thaw (GTK_TEXT (text));
  
  hbox = gtk_hbutton_box_new ();
  gtk_box_pack_start (GTK_BOX (box2), hbox, FALSE, FALSE, 0);
  gtk_widget_show (hbox);

  box2 = gtk_vbox_new (FALSE, 10);
  gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
  gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, TRUE, 0);
  gtk_widget_show (box2);
  
  button = gtk_button_new_with_label ("close");
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

  poptFreeContext (optCon);

  return(0);
}
