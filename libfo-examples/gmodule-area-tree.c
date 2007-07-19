/* Fo
 * gmodule-area-tree.c: Demonstration area-tree viewer as gmodule.
 *
 * This loadable module works with xmlroff-gmodule.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#define GTK_ENABLE_BROKEN
#include "config.h"
#include <stdlib.h>
#include <libfo/fo-libfo.h>
#include <gtk/gtk.h>

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
	     GObject   *object,
	     gint       depth)
{
  GValue value = { 0, {{0}, {0}} };
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *text_string;
  GObject *child;
  GdkFont *fixed_font =
    gdk_font_load ("-misc-fixed-medium-r-*-*-*-140-*-*-*-*-*-*");

  g_return_if_fail (object != NULL);
  g_return_if_fail (G_IS_OBJECT (object));

  g_value_init (&value, G_TYPE_OBJECT);

  text_string =
    g_strdup_printf ("%s%s\n",
		     indent,
		     g_type_name (G_TYPE_FROM_INSTANCE (object)));

  gtk_text_insert (GTK_TEXT (text), fixed_font, &text->style->black, NULL,
		   text_string, -1);

  g_free (text_string);
  g_free (indent);

  g_object_get_property (object,
			 "first-child",
			 &value);
  child = g_value_get_object (&value);
  while (child)
    {
      insert_tree (text,
		   child,
		   depth + 1);

      g_object_get_property (child,
			     "next-sibling",
			     &value);
      child = g_value_get_object (&value);
    }
}

void
adjust (GObject *fo_tree G_GNUC_UNUSED,
	GObject *area_tree)
{
  GtkWidget *window;
  GtkWidget *box1;
  GtkWidget *box2;
  GtkWidget *hbox;
  GtkWidget *button;
  GtkWidget *table;
  GtkWidget *vscrollbar;
  GtkWidget *text;
  GdkColormap *cmap;
  GdkColor color;
  GdkFont *fixed_font;


  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (window, 600, 500);
  gtk_window_set_policy (GTK_WINDOW (window), TRUE, TRUE, FALSE);  
  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (close_application),
                    NULL);
  gtk_window_set_title (GTK_WINDOW (window), "Area Tree View");
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
  
  insert_tree (text, area_tree, 0);

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
}

void
load()
{
  gtk_init (NULL, NULL);
}
