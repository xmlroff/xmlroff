/* Fo
 * fo-doc-gp.c: 'GNOME Print'-specific child type of FoDoc
 *
 * Copyright (C) 2001-2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <pango/pango.h>
#include <libgnomeprint/gnome-print-job.h>
#include <libgnomeprint/gnome-print-pango.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "area/fo-area-area.h"
#include "area/fo-area-layout.h"
#include "util/fo-pixbuf.h"
#include "fo-doc-gp-private.h"
#include "fo-doc-commands.h"
#include "fo-layout-gp-private.h"
#include "libfo-pango.h"
#include "datatype/fo-color.h"
#include <string.h>

const char *fo_doc_gp_error_messages [] = {
  N_("FoDocGP error"),
  N_("Cannot open output document: '%s'")
};

static void fo_doc_gp_init          (FoDocGP      *object);
static void fo_doc_gp_base_init     (FoDocGPClass *klass);
static void fo_doc_gp_class_init    (FoDocGPClass *klass);
static void fo_doc_gp_finalize      (GObject      *object);

static FoLayout *    fo_doc_gp_get_new_layout   (FoDoc        *fo_doc);

static void          fo_doc_gp_begin_page       (FoDoc        *fo_doc,
						 gdouble        width,
						 gdouble        height,
						 GError       **error);
static void          fo_doc_gp_end_page         (FoDoc        *fo_doc);
static FoDatatype*   fo_doc_gp_get_fill_color   (FoDoc        *fo_doc);
static void          fo_doc_gp_set_fill_color   (FoDoc        *fo_doc,
						 FoDatatype   *color);
static FoDatatype*   fo_doc_gp_get_stroke_color (FoDoc        *fo_doc);
static void          fo_doc_gp_set_stroke_color (FoDoc        *fo_doc,
						 FoDatatype   *color);
static void          fo_doc_gp_translate        (FoDoc        *fo_doc,
						 gdouble        x,
						 gdouble        y);
static FoDocLineCap  fo_doc_gp_get_line_cap     (FoDoc        *fo_doc);
static void          fo_doc_gp_set_line_cap     (FoDoc        *fo_doc,
						 FoDocLineCap  line_cap);
static FoDocLineJoin fo_doc_gp_get_line_join    (FoDoc        *fo_doc);
static void          fo_doc_gp_set_line_join    (FoDoc        *fo_doc,
						 FoDocLineJoin line_join);
static gdouble        fo_doc_gp_get_line_width   (FoDoc        *fo_doc);
static void          fo_doc_gp_set_line_width   (FoDoc        *fo_doc,
						 gdouble        line_width);
static void          fo_doc_gp_set_dash         (FoDoc        *fo_doc,
						 gdouble        b,
						 gdouble        w);
static void          fo_doc_gp_clip             (FoDoc        *fo_doc);
static void          fo_doc_gp_save             (FoDoc        *fo_doc);
static void          fo_doc_gp_restore          (FoDoc        *fo_doc);
static void          fo_doc_gp_line_to          (FoDoc        *fo_doc,
						 gdouble        x,
						 gdouble        y);
static void          fo_doc_gp_move_to          (FoDoc        *fo_doc,
						 gdouble        x,
						 gdouble        y);
static void          fo_doc_gp_line_stroked     (FoDoc        *fo_doc,
						 gdouble        x0,
						 gdouble        y0,
						 gdouble        x1,
						 gdouble        y1);
static void          fo_doc_gp_rect_stroked     (FoDoc        *fo_doc,
						 gdouble        x,
						 gdouble        y,
						 gdouble        width,
						 gdouble        height);
static void          fo_doc_gp_rect_filled      (FoDoc        *fo_doc,
						 gdouble        x,
						 gdouble        y,
						 gdouble        width,
						 gdouble        height);
static void          fo_doc_gp_fill             (FoDoc        *fo_doc);
static void          fo_doc_gp_stroke           (FoDoc        *fo_doc);
static void          fo_doc_gp_fill_stroke      (FoDoc        *fo_doc);
static void          fo_doc_gp_place_image      (FoDoc        *fo_doc,
						 FoImage      *fo_image,
						 gdouble        x,
						 gdouble        y,
						 gdouble        xscale,
						 gdouble        yscale);
static void          fo_doc_gp_render_layout_lines (FoDoc   *fo_doc,
						    FoArea  *area_layout,
						    gdouble   x,
						    gdouble   y);
static void 	     fo_doc_gp_render_layout       (FoDoc   *fo_doc,
						    FoArea  *area_layout,
						    gdouble   x,
						    gdouble   y);
static gpointer parent_class;

/**
 * fo_doc_gp_error_quark:
 * 
 * Get the error quark for #FoDoc.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: Quark associated with #FoDoc errors.
 **/
GQuark
fo_doc_gp_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoDocGP error");
  return quark;
}


/**
 * fo_doc_gp_get_type:
 * 
 * Register the #FoDoc object type.
 * 
 * Return value: #GType value of the #FoDocGP object type.
 **/
GType
fo_doc_gp_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoDocGPClass),
        (GBaseInitFunc) fo_doc_gp_base_init,
        NULL,		/* base_finalize */
        (GClassInitFunc) fo_doc_gp_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoDocGP),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_doc_gp_init,
	NULL
      };
      
      object_type = g_type_register_static (FO_TYPE_DOC,
                                            "FoDocGP",
                                            &object_info,
					    0);
    }
  
  return object_type;
}

/**
 * fo_doc_gp_init:
 * @fo_doc_gp: #FoDocGP object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoDocGP.
 **/
void
fo_doc_gp_init (FoDocGP *fo_doc_gp)
{
  /*
  char *test;

  fo_doc_gp->job = gnome_print_job_new (NULL);

  if (fo_doc_gp->job == NULL)
    {
      g_error (_("Couldn't create GNOME Print job"));
    }

  fo_doc_gp->context = gnome_print_job_get_context (fo_doc_gp->job);

  if (fo_doc_gp->context == NULL)
    {
      g_error (_("Couldn't create GNOME Print context"));
    }

  fo_doc_gp->config = gnome_print_job_get_config (fo_doc_gp->job);

  if (fo_doc_gp->config == NULL)
    {
      g_error (_("Couldn't create GNOME Print config"));
    }

  if (!gnome_print_config_set (fo_doc_gp->config, "Printer", "PDF"))
    fprintf (stderr, "gnome_print_config_set Printer-PDF");
  test = gnome_print_config_get (fo_doc_gp->config, "Printer");
  if (!test)
    fprintf (stderr, "gnome_print_config_get Printer returned NULL\n");
  if (strcmp (test, "PDF") != 0)
    fprintf (stderr, "Could not set printer to PDF.\n");
  g_free (test);		
  */
/*
  FO_DOC (fo_doc_gp)->pango_context =
    pango_gp_get_context (fo_doc_gp->context);
*/
    FO_DOC (fo_doc_gp)->pango_context =
	gnome_print_pango_create_context (gnome_print_pango_get_default_font_map());
    /* gnome_print_pango_update_context() currently doesn't do anything,
       and calling it at this point with null context causes a warning message.
    */
    /*
    gnome_print_pango_update_context (FO_DOC (fo_doc_gp)->pango_context,
				      fo_doc_gp->context);
    */
}

/**
 * fo_doc_gp_base_init:
 * @klass: #FoDocGPClass base class object to initialise
 * 
 * Implements #GBaseInitFunc for #FoDocGPClass
 **/
void
fo_doc_gp_base_init (FoDocGPClass *klass)
{
  FoDocClass *fo_doc_class = FO_DOC_CLASS (klass);

  fo_doc_class->open_file        = fo_doc_gp_open_file;

  fo_doc_class->get_new_layout   = fo_doc_gp_get_new_layout;

  fo_doc_class->begin_page       = fo_doc_gp_begin_page;
  fo_doc_class->end_page         = fo_doc_gp_end_page;
  fo_doc_class->get_fill_color   = fo_doc_gp_get_fill_color;
  fo_doc_class->set_fill_color   = fo_doc_gp_set_fill_color;
  fo_doc_class->get_stroke_color = fo_doc_gp_get_stroke_color;
  fo_doc_class->set_stroke_color = fo_doc_gp_set_stroke_color;
  fo_doc_class->translate        = fo_doc_gp_translate;
  fo_doc_class->get_line_cap     = fo_doc_gp_get_line_cap;
  fo_doc_class->set_line_cap     = fo_doc_gp_set_line_cap;
  fo_doc_class->get_line_join    = fo_doc_gp_get_line_join;
  fo_doc_class->set_line_join    = fo_doc_gp_set_line_join;
  fo_doc_class->get_line_width   = fo_doc_gp_get_line_width;
  fo_doc_class->set_line_width   = fo_doc_gp_set_line_width;
  fo_doc_class->set_dash         = fo_doc_gp_set_dash;
  fo_doc_class->clip             = fo_doc_gp_clip;
  fo_doc_class->save             = fo_doc_gp_save;
  fo_doc_class->restore          = fo_doc_gp_restore;
  fo_doc_class->line_to          = fo_doc_gp_line_to;
  fo_doc_class->move_to          = fo_doc_gp_move_to;
  fo_doc_class->line_stroked     = fo_doc_gp_line_stroked;
  fo_doc_class->rect_stroked     = fo_doc_gp_rect_stroked;
  fo_doc_class->rect_filled      = fo_doc_gp_rect_filled;
  fo_doc_class->fill             = fo_doc_gp_fill;
  fo_doc_class->stroke           = fo_doc_gp_stroke;
  fo_doc_class->fill_stroke      = fo_doc_gp_fill_stroke;
  fo_doc_class->place_image      = fo_doc_gp_place_image;
  fo_doc_class->render_layout_lines = fo_doc_gp_render_layout_lines;
  fo_doc_class->render_layout       = fo_doc_gp_render_layout;
}

/**
 * fo_doc_gp_class_init:
 * @klass: #FoDocGPClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoDocGPClass.
 **/
void
fo_doc_gp_class_init (FoDocGPClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_doc_gp_finalize;
}

/**
 * fo_doc_gp_finalize:
 * @object: #FoDocGP object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoDocGP.
 **/
void
fo_doc_gp_finalize (GObject *object)
{
  FoDocGP *fo_doc_gp;

  fo_doc_gp = FO_DOC_GP (object);

  if (gnome_print_job_print_to_file (fo_doc_gp->job,
				     fo_doc_gp->current_filename)
      != GNOME_PRINT_OK)
    {
      g_error ("print_job_print_to_file");
    }

  if (gnome_print_job_close (fo_doc_gp->job) != GNOME_PRINT_OK)
    {
      g_error ("gnome_print_job_close");
    }

  if (gnome_print_job_print (fo_doc_gp->job) != GNOME_PRINT_OK)
    {
      g_error ("gnome_print_job_print");
    }

  if (fo_doc_gp->base_filename != NULL)
    {
      g_free (fo_doc_gp->base_filename);
    }

  if (fo_doc_gp->current_filename != NULL)
    {
      g_free (fo_doc_gp->current_filename);
    }

  if (fo_doc_gp->config != NULL)
    {
      g_object_unref (fo_doc_gp->config);
    }

  if (fo_doc_gp->context != NULL)
    {
      g_object_unref (fo_doc_gp->context);
    }

  if (fo_doc_gp->job != NULL)
    {
      g_object_unref (fo_doc_gp->job);
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_doc_gp_new:
 * 
 * Creates a new #FoDoc.
 * 
 * Return value: the newly created #FoDoc.
 **/
FoDoc *
fo_doc_gp_new (void)
{
  return FO_DOC (g_object_new (fo_doc_gp_get_type (),
			       NULL));
}

/**
 * fo_doc_gp_get_context:
 * @fo_doc: #FoDoc
 * 
 * Get the #GnomePrintContext in @fo_doc.
 * 
 * Return value: Pointer to #GnomePrintContext.
 **/
GnomePrintContext *
fo_doc_gp_get_context (FoDoc *fo_doc)
{
  g_return_val_if_fail (fo_doc != NULL, NULL);

  return FO_DOC_GP (fo_doc)->context;
}

/**
 * fo_doc_gp_open_file:
 * @fo_doc:        #FoDoc.
 * @filename:      File to open as output.
 * @libfo_context: #FoLibfoContext specifying file format.
 * @error:         #GError that is set if an error occurs.
 * 
 * Open @filename as the output file for @fo_doc.
 **/
void
fo_doc_gp_open_file (FoDoc          *fo_doc,
		     const gchar    *filename,
		     FoLibfoContext *libfo_context,
		     GError        **error)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  /*g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);*/
  g_return_if_fail (filename != NULL);
  g_return_if_fail (*filename != '\0');
  g_return_if_fail (error == NULL || *error == NULL);

  FO_DOC_GP (fo_doc)->base_filename = g_strdup (filename);
  FO_DOC_GP (fo_doc)->current_filename = g_strdup (filename);
  FO_DOC_GP (fo_doc)->format = fo_libfo_context_get_format (libfo_context);
}

/**
 * fo_doc_gp_get_new_layout:
 * @fo_doc: #FoDoc.
 * 
 * Get a new #FoLayout for use with @fo_doc.
 *
 * Return value: New #FoLayout.
 **/
FoLayout *
fo_doc_gp_get_new_layout (FoDoc *fo_doc)
{
  FoLayout *fo_layout;

  g_return_val_if_fail (FO_IS_DOC_GP (fo_doc), NULL);

  fo_layout = fo_layout_gp_new ();

  fo_layout->fo_doc = fo_doc;
  fo_layout->pango_layout =
    pango_layout_new (fo_doc->pango_context);

  return fo_layout;
}

/**
 * fo_doc_gp_begin_page:
 * @fo_doc: #FoDoc.
 * @width:  Width of the new page.
 * @height: Height of the new page.
 * 
 * Add a new page to @fo_doc.
 *
 * This must always be paired with a matching #fo_doc_gp_end_page call.
 **/
void
fo_doc_gp_begin_page (FoDoc  *fo_doc,
		      gdouble  width,
		      gdouble  height,
		      GError **error)
{
  FoDocGP *fo_doc_gp;

  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  /* g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL); */
  g_return_if_fail (error == NULL || *error == NULL);

  fo_doc_gp = FO_DOC_GP (fo_doc);
  
  if (fo_doc_gp->job == NULL)
    {
      fo_doc_gp->job = gnome_print_job_new (NULL);

      if (fo_doc_gp->job == NULL)
	{
	  g_error (_("Couldn't create GNOME Print job"));
	}

      fo_doc_gp->context = gnome_print_job_get_context (fo_doc_gp->job);

      if (fo_doc_gp->context == NULL)
	{
	  g_error (_("Couldn't create GNOME Print context"));
	}

      fo_doc_gp->config = gnome_print_job_get_config (fo_doc_gp->job);

      if (fo_doc_gp->config == NULL)
	{
	  g_error (_("Couldn't create GNOME Print config"));
	}

      // FIXME: There has to be a better way to do this.
      if (fo_doc_gp->format == FO_ENUM_FORMAT_AUTO)
	{
	  gint len = strlen (fo_doc_gp->base_filename);
	  if (g_ascii_strncasecmp (&(fo_doc_gp->base_filename)[len-4], ".pdf", 4) == 0)
	    {
	      if (!gnome_print_config_set (fo_doc_gp->config, "Printer", "PDF"))
		{
		  fprintf (stderr, "gnome_print_config_set Printer-PDF");
		}
	    }
	  else if (g_ascii_strncasecmp (&(fo_doc_gp->base_filename)[len-3], ".ps", 3) == 0)
	    {
	      if (!gnome_print_config_set (fo_doc_gp->config, "Printer", "GENERIC"))
		{
		  fprintf (stderr, "gnome_print_config_set Printer-POSTSCRIPT");
		}
	    }
	}
      else if (fo_doc_gp->format == FO_ENUM_FORMAT_PDF)
	{
	  if (!gnome_print_config_set (fo_doc_gp->config, "Printer", "PDF"))
	    {
	      fprintf (stderr, "gnome_print_config_set Printer-PDF");
	    }
	}
      else if (fo_doc_gp->format == FO_ENUM_FORMAT_POSTSCRIPT)
	{
	  if (!gnome_print_config_set (fo_doc_gp->config, "Printer", "GENERIC"))
	    {
	      fprintf (stderr, "gnome_print_config_set Printer-POSTSCRIPT");
	    }
	}
      else if (fo_doc_gp->format == FO_ENUM_FORMAT_SVG)
	{
	  if (!gnome_print_config_set (fo_doc_gp->config, "Settings.Engine.Backend.Driver", "gnome-print-svg"))
	    {
	      fprintf (stderr, "gnome_print_config_set Printer-SVG");
	    }
	}

      gnome_print_config_set_length (fo_doc_gp->config,
				     GNOME_PRINT_KEY_PAPER_WIDTH,
				     width,
				     GNOME_PRINT_PS_UNIT);
      gnome_print_config_set_length (fo_doc_gp->config,
				     GNOME_PRINT_KEY_PAPER_HEIGHT,
				     height,
				     GNOME_PRINT_PS_UNIT);

      fo_doc_gp->page_width = width;
      fo_doc_gp->page_height = height;

      FO_DOC (fo_doc_gp)->pango_context =
	  gnome_print_pango_create_context (gnome_print_pango_get_default_font_map());
      gnome_print_pango_update_context (FO_DOC (fo_doc_gp)->pango_context,
					fo_doc_gp->context);
      /*FO_DOC (fo_doc_gp)->pango_context =
	  pango_gp_get_context (fo_doc_gp->context);*/
    }
  else if ((width != fo_doc_gp->page_width) ||
	   (height != fo_doc_gp->page_height))
    {
      GnomePrintConfig *new_config;

      new_config = gnome_print_config_dup (fo_doc_gp->config);

      if (gnome_print_job_print_to_file (fo_doc_gp->job,
					 fo_doc_gp->current_filename)
	  != GNOME_PRINT_OK)
	{
	  g_error ("print_job_print_to_file");
	}

      if (gnome_print_job_close (fo_doc_gp->job) != GNOME_PRINT_OK)
	{
	  g_error ("gnome_print_job_close");
	}

      if (gnome_print_job_print (fo_doc_gp->job) != GNOME_PRINT_OK)
	{
	  g_error ("gnome_print_job_print");
	}

      g_object_unref (fo_doc_gp->config);
      g_object_unref (fo_doc_gp->context);
      g_object_unref (fo_doc_gp->job);

      gnome_print_config_set_length (new_config,
				     GNOME_PRINT_KEY_PAPER_WIDTH,
				     width,
				     GNOME_PRINT_PS_UNIT);
      gnome_print_config_set_length (new_config,
				     GNOME_PRINT_KEY_PAPER_HEIGHT,
				     height,
				     GNOME_PRINT_PS_UNIT);

      fo_doc_gp->job = gnome_print_job_new (new_config);

      if (fo_doc_gp->job == NULL)
	{
	  g_error (_("Couldn't create GNOME Print job"));
	}

      fo_doc_gp->context = gnome_print_job_get_context (fo_doc_gp->job);

      if (fo_doc_gp->context == NULL)
	{
	  g_error (_("Couldn't create GNOME Print context"));
	}

      FO_DOC (fo_doc_gp)->pango_context =
	  gnome_print_pango_create_context (gnome_print_pango_get_default_font_map());
      gnome_print_pango_update_context (FO_DOC (fo_doc_gp)->pango_context,
					fo_doc_gp->context);
      /*FO_DOC (fo_doc_gp)->pango_context =
	  pango_gp_get_context (fo_doc_gp->context);*/

      g_free (fo_doc_gp->current_filename);

      fo_doc_gp->output_sequence++;

      fo_doc_gp->current_filename =
	g_strdup_printf ("%*s.%02d%s",
			 (g_strrstr (fo_doc_gp->base_filename, ".") -
			  fo_doc_gp->base_filename),
			 fo_doc_gp->base_filename,
			 fo_doc_gp->output_sequence,
			 g_strrstr (fo_doc_gp->base_filename, "."));      
    }

  gnome_print_beginpage (fo_doc_gp->context,
			 NULL);
}

/**
 * fo_doc_gp_end_page:
 * @fo_doc: #FoDoc.
 * 
 * Finish the current page of @fo_doc.
 **/
void
fo_doc_gp_end_page (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_showpage (FO_DOC_GP (fo_doc)->context);
}

/**
 * fo_doc_gp_get_fill_color:
 * @fo_doc: #FoDoc.
 * 
 * Get the current fill color of @fo_doc.
 * 
 * Return value: #FoDatatype for the current fill color.
 **/
FoDatatype*
fo_doc_gp_get_fill_color (FoDoc *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_GP (fo_doc), NULL);

  return fo_doc->fill_color;
}

/**
 * fo_doc_gp_set_fill_color:
 * @fo_doc: #FoDoc.
 * @color:  #FoDatatype for new fill color.
 * 
 * Set the fill color of @fo_doc to @color.
 **/
void
fo_doc_gp_set_fill_color (FoDoc *fo_doc,
			  FoDatatype *color)
{
  guint16 red;
  guint16 green;
  guint16 blue;

  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);
  g_return_if_fail (FO_IS_COLOR (color));

  red = fo_color_get_red (color);
  green = fo_color_get_green (color);
  blue = fo_color_get_blue (color);

  if (color != NULL)
    {
      g_object_ref (color);
    }
  if (fo_doc->fill_color != NULL)
    {
      g_object_unref (fo_doc->fill_color);
    }
  fo_doc->fill_color = color;

  gnome_print_setrgbcolor (FO_DOC_GP (fo_doc)->context,
			   (gdouble) red / FO_COLOR_COMPONENT_MAX,
			   (gdouble) green / FO_COLOR_COMPONENT_MAX,
			   (gdouble) blue / FO_COLOR_COMPONENT_MAX);
}

/**
 * fo_doc_gp_get_stroke_color:
 * @fo_doc: #FoDoc.
 * 
 * Get the current stroke color of @fo_doc.
 * 
 * Return value: #FoDatatype for the current stroke color.
 **/
FoDatatype*
fo_doc_gp_get_stroke_color (FoDoc *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_GP (fo_doc), NULL);

  return fo_doc->stroke_color;
}

/**
 * fo_doc_gp_set_stroke_color:
 * @fo_doc: #FoDoc.
 * @color:  #FoDatatype for new stroke color.
 * 
 * Set the stroke color of @fo_doc to @color.
 **/
void
fo_doc_gp_set_stroke_color (FoDoc *fo_doc,
				FoDatatype *color)
{
  guint16 red;
  guint16 green;
  guint16 blue;

  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);
  g_return_if_fail (FO_IS_COLOR (color));

  red = fo_color_get_red (color);
  green = fo_color_get_green (color);
  blue = fo_color_get_blue (color);

  if (color != NULL)
    {
      g_object_ref (color);
    }
  if (fo_doc->stroke_color != NULL)
    {
      g_object_unref (fo_doc->stroke_color);
    }
  fo_doc->stroke_color = color;

  gnome_print_setrgbcolor (FO_DOC_GP (fo_doc)->context,
			   (gdouble) red / FO_COLOR_COMPONENT_MAX,
			   (gdouble) green / FO_COLOR_COMPONENT_MAX,
			   (gdouble) blue / FO_COLOR_COMPONENT_MAX);
}

/**
 * fo_doc_gp_get_line_cap:
 * @fo_doc: #FoDoc.
 * 
 * Get the current "linecap" parameter value of @fo_doc.
 * 
 * Return value: Current "linecap" parameter value.
 **/
FoDocLineCap
fo_doc_gp_get_line_cap (FoDoc        *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_GP (fo_doc), FO_DOC_LINE_CAP_INVALID);

  return fo_doc->line_cap;
}

/**
 * fo_doc_gp_set_line_cap:
 * @fo_doc:   #FoDoc.
 * @line_cap: New "linecap" parameter value.
 * 
 * Set the "linecap" parameter value of @fo_doc.
 **/
void
fo_doc_gp_set_line_cap (FoDoc       *fo_doc,
			FoDocLineCap line_cap)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);
  g_return_if_fail (line_cap < FO_DOC_LINE_CAP_LIMIT);

  /*if (line_cap != fo_doc->line_cap)
    {*/
      fo_doc->line_cap = line_cap;
      gnome_print_setlinecap (FO_DOC_GP (fo_doc)->context,
			      line_cap);
      /*}*/
}

/**
 * fo_doc_gp_get_line_join:
 * @fo_doc: #FoDoc.
 * 
 * Get the current "linejoin" parameter value of @fo_doc.
 * 
 * Return value: Current "linejoin" parameter value.
 **/
FoDocLineJoin
fo_doc_gp_get_line_join (FoDoc        *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_GP (fo_doc), FO_DOC_LINE_JOIN_INVALID);

  return fo_doc->line_join;
}

/**
 * fo_doc_gp_set_line_join:
 * @fo_doc:   #FoDoc.
 * @line_join: New "linejoin" parameter value.
 * 
 * Set the "linejoin" parameter value of @fo_doc.
 **/
void
fo_doc_gp_set_line_join (FoDoc        *fo_doc,
			     FoDocLineJoin line_join)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);
  g_return_if_fail (line_join < FO_DOC_LINE_JOIN_LIMIT);

  /*if (line_join != fo_doc->line_join)
    {*/
      fo_doc->line_join = line_join;
      gnome_print_setlinejoin (FO_DOC_GP (fo_doc)->context,
			       line_join);
      /*}*/
}

/**
 * fo_doc_gp_get_line_width:
 * @fo_doc: #FoDoc.
 * 
 * Get the current line width of @fo_doc.
 * 
 * Return value: Current line width.
 **/
gdouble
fo_doc_gp_get_line_width (FoDoc        *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_GP (fo_doc), 0);

  return fo_doc->line_width;
}

/**
 * fo_doc_gp_set_line_width:
 * @fo_doc:   #FoDoc.
 * @line_width: New line width value.
 * 
 * Set the line width of @fo_doc.
 **/
void
fo_doc_gp_set_line_width (FoDoc       *fo_doc,
			  gdouble       line_width)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  /*if (line_width != fo_doc->line_width)
    {*/
      fo_doc->line_width = line_width;
      gnome_print_setlinewidth (FO_DOC_GP (fo_doc)->context,
				line_width);
      /*}*/
}

/**
 * fo_doc_gp_set_dash:
 * @fo_doc: #FoDoc.
 * @b:      Number of black units.
 * @w:      Number of white units.
 * 
 * Set the current dash pattern of @fo_doc.
 *
 * The dash pattern is the ratio of @b to @w.
 *
 * Set @b and @w to 0 to produce a solid line.
 *
 * The dash pattern is set to solid (@b = @w = 0) at the beginning of
 * each page.
 **/
void
fo_doc_gp_set_dash (FoDoc *fo_doc,
		    gdouble b,
		    gdouble w)
{
  const gdouble values[] = {b,w};
  gint n = ((b == 0.0) && (w == 0.0))? 0 : 2;

  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_setdash (FO_DOC_GP (fo_doc)->context,
		       n,
		       values,
		       0.0);
}

/**
 * fo_doc_gp_line_to:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new current point.
 * @y:      Y-coordinate of the new current point.
 * 
 * Draw a line from the current point to another point.
 **/
void
fo_doc_gp_line_to (FoDoc *fo_doc,
		   gdouble x,
		   gdouble y)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_lineto (FO_DOC_GP (fo_doc)->context, x, y);
}

/**
 * fo_doc_gp_translate:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new origin of the coordinate system.
 * @y:      Y-coordinate of the new origin of the coordinate system.
 * 
 * Translate the origin of the coordinate system of @fo_doc.
 *
 * @x and @y are measured in the old coordinate system.
 **/
void
fo_doc_gp_translate (FoDoc *fo_doc,
			 gdouble x,
			 gdouble y)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_translate (FO_DOC_GP (fo_doc)->context, x, y);
}

/**
 * fo_doc_gp_clip:
 * @fo_doc: #FoDoc.
 * 
 * Use the current path of @fo_doc as its clipping path.
 **/
void
fo_doc_gp_clip (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_clip (FO_DOC_GP (fo_doc)->context);
}

/**
 * fo_doc_gp_save:
 * @fo_doc: #FoDoc.
 * 
 * Save the current graphics state of @fo_doc.
 **/
void
fo_doc_gp_save (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_gsave (FO_DOC_GP (fo_doc)->context);
}

/**
 * fo_doc_gp_restore:
 * @fo_doc: #FoDoc.
 * 
 * Restore the most recently saved graphics state of @fo_doc.
 **/
void
fo_doc_gp_restore (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_grestore (FO_DOC_GP (fo_doc)->context);
}

/**
 * fo_doc_gp_move_to:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new current point.
 * @y:      Y-coordinate of the new current point.
 * 
 * Set the current point of @fo_doc to (@x, @y).
 **/
void
fo_doc_gp_move_to (FoDoc *fo_doc,
		       gdouble x,
		       gdouble y)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_moveto (FO_DOC_GP (fo_doc)->context, x, y);
}

/**
 * fo_doc_gp_line_stroked:
 * @fo_doc: #FoDoc.
 * @x0: X-coordinate of the start of the line.
 * @y0: Y-coordinate of the start of the line.
 * @x1: X-coordinate of the end of the line.
 * @y1: Y-coordinate of the end of the line.
 * 
 * Draw a line from (@x0,@y0) to (@x1,@y1).
 **/
void
fo_doc_gp_line_stroked (FoDoc *fo_doc,
			gdouble x0,
			gdouble y0,
			gdouble x1,
			gdouble y1)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_line_stroked (FO_DOC_GP (fo_doc)->context,
			    x0,
			    y0,
			    x1,
			    y1);
}

/**
 * fo_doc_gp_rect_stroked:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the lower-left corner of the rectangle.
 * @y:      Y-coordinate of the lower-left corner of the rectangle.
 * @width:  Width of the rectangle.
 * @height: Height of the rectangle.
 * 
 * Draw an outline rectangle.
 **/
void
fo_doc_gp_rect_stroked (FoDoc *fo_doc,
			gdouble x,
			gdouble y,
			gdouble width,
			gdouble height)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_rect_stroked (FO_DOC_GP (fo_doc)->context,
			    x,
			    y,
			    width,
			    height);
}

/**
 * fo_doc_gp_rect_filled:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the lower-left corner of the rectangle.
 * @y:      Y-coordinate of the lower-left corner of the rectangle.
 * @width:  Width of the rectangle.
 * @height: Height of the rectangle.
 * 
 * Draw a filled rectangle.
 **/
void
fo_doc_gp_rect_filled (FoDoc *fo_doc,
		       gdouble x,
		       gdouble y,
		       gdouble width,
		       gdouble height)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_rect_filled (FO_DOC_GP (fo_doc)->context,
			   x,
			   y,
			   width,
			   height);
}

/**
 * fo_doc_gp_fill:
 * @fo_doc: #FoDoc.
 * 
 * Fill the interior of the path of @fo_doc with the current fill color.
 **/
void
fo_doc_gp_fill (FoDoc *fo_doc)
{
  g_return_if_fail (fo_doc != NULL);
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_fill (FO_DOC_GP (fo_doc)->context);
}

/**
 * fo_doc_gp_stroke:
 * @fo_doc: #FoDoc.
 * 
 * Stroke the path of @fo_doc and clear the path.
 **/
void
fo_doc_gp_stroke (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  gnome_print_stroke (FO_DOC_GP (fo_doc)->context);
}

/**
 * fo_doc_gp_fill_stroke:
 * @fo_doc: #FoDoc.
 * 
 * Fill and stroke the path of @fo_doc with the current fill and
 * stroke colors.
 **/
void
fo_doc_gp_fill_stroke (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);

  /*PDF_fill_stroke (FO_DOC_GP (fo_doc)->context);*/
}

static void
fo_doc_gp_place_image (FoDoc   *fo_doc,
		       FoImage *fo_image,
		       gdouble   x,
		       gdouble   y,
		       gdouble   xscale,
		       gdouble   yscale)
{
  GdkPixbuf *pixbuf = g_object_ref (fo_pixbuf_get_pixbuf (fo_image));
  guchar *raw_image;
  gboolean has_alpha;
  gint rowstride, height, width;
	
  raw_image = gdk_pixbuf_get_pixels (pixbuf);
  has_alpha = gdk_pixbuf_get_has_alpha (pixbuf);
  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  height    = gdk_pixbuf_get_height (pixbuf);
  width     = gdk_pixbuf_get_width (pixbuf);
	
  /*
  gnome_print_gsave (FO_DOC_GP (fo_doc)->context);
  gnome_print_translate (FO_DOC_GP (fo_doc)->context, 0, 0);
  gnome_print_translate (FO_DOC_GP (fo_doc)->context, -100.0, -100.0);
  gnome_print_show (FO_DOC_GP (fo_doc)->context, "fo_doc_gp_place_image()");
  gnome_print_moveto (FO_DOC_GP (fo_doc)->context, 0, 0);
*/
  /*
   */
  gnome_print_translate (FO_DOC_GP (fo_doc)->context, 0, -height * yscale * 72 / PIXELS_PER_INCH);
  gnome_print_scale (FO_DOC_GP (fo_doc)->context,
		     width * xscale * 72 / PIXELS_PER_INCH,
		     height * yscale * 72 / PIXELS_PER_INCH);
  if (has_alpha)
    gnome_print_rgbaimage (FO_DOC_GP (fo_doc)->context, (char *)raw_image, width, height, rowstride);
  else
    gnome_print_rgbimage (FO_DOC_GP (fo_doc)->context, (char *)raw_image, width, height, rowstride);
  /*
  gnome_print_grestore (FO_DOC_GP (fo_doc)->context);
  */

  g_object_unref (pixbuf);
}

void
fo_doc_gp_do_run_callbacks (GnomePrintContext *context,
			    PangoLayoutRun    *run,
			    gint               x, 
			    gint               y)
{
  /*PangoLayoutRunPrivate *prun = (PangoLayoutRunPrivate *) run;*/
  /*FT_UInt glyph_index;*/
  GSList *extra_attrs_list = run->item->analysis.extra_attrs;

  g_return_if_fail (context != NULL);
  g_return_if_fail (run != NULL);

  while (extra_attrs_list)
    {
      PangoAttribute *attr = extra_attrs_list->data;
      PangoAttrType attr_type = attr->klass->type;

      if (attr_type == libfo_pango_attr_callback_get_type ())
	{
	  GValue values[1] = { { 0, } };

	  g_value_init (&values[0], G_TYPE_POINTER);
	  g_value_set_pointer (&values[0], context);

#if 0
	  g_message ("Got a callback: callback: %p",
		     ((PangoAttrPointer *) attr)->pointer);
#endif

	  gnome_print_gsave (context);

	  gnome_print_translate (context,
				 x / PANGO_SCALE,
				 y / PANGO_SCALE);

	  g_closure_invoke (((GClosure *) libfo_pango_attr_callback_get_callback(attr)),
			     NULL,
			     1,
			     values,
			     NULL);
	  gnome_print_grestore (context);
	}

      extra_attrs_list = extra_attrs_list->next;
    }
}

void 
fo_doc_gp_do_line_callbacks (GnomePrintContext *context,
			     PangoLayoutLine   *line,
			     gint               x, 
			     gint               y)
{
  GSList *run_list;
  PangoRectangle overall_rect;
  PangoRectangle logical_rect;
  gint      x_off = 0;

  pango_layout_line_get_extents (line,
				 NULL,
				 &overall_rect);
  
  run_list = line->runs;
  while (run_list)
    {
      PangoLayoutRun *run = run_list->data;
      
      pango_glyph_string_extents (run->glyphs,
				  run->item->analysis.font,
				  NULL,
				  &logical_rect);

      fo_doc_gp_do_run_callbacks (context,
				  run,
				  x + x_off,
				  y);

      x_off += logical_rect.width;
      run_list = run_list->next;
    }
}

static void
fo_doc_gp_do_callbacks (GnomePrintContext *context,
			PangoLayout       *layout,
			guint              line_first,
			guint              line_last,
			gint               x,
			gint               y)
{
  PangoLayoutIter *iter;
  
  g_return_if_fail (context != NULL);
  g_return_if_fail (PANGO_IS_LAYOUT (layout));
  g_return_if_fail (line_last >= line_first &&
		    line_last <= g_slist_length (pango_layout_get_lines (layout)) - 1);

  iter = pango_layout_get_iter (layout);

  gint line_number = -1;
  do
    {
      PangoRectangle   logical_rect;
      PangoLayoutLine *line;
      int              baseline;
      
      line_number++;

      if (line_number < line_first)
	{
	  continue;
	}

      line = pango_layout_iter_get_line (iter);
      
      pango_layout_iter_get_line_extents (iter, NULL, &logical_rect);
      baseline = pango_layout_iter_get_baseline (iter);
      
      fo_doc_gp_do_line_callbacks (context,
				   line,
				   x + logical_rect.x,
				   y - baseline);

      if (line_number >= line_last)
	{
	  break;
	}
    }
  while (pango_layout_iter_next_line (iter));

  pango_layout_iter_free (iter);
}


/**
 * fo_doc_gp_render_layout_lines:
 * @fo_doc:      #FoDoc for which to render lines.
 * @area_layout: #FoArea containing lines.
 * @x:           X-offset
 * @y:           Y-offset
 * 
 * Renders the lines in @area_layout at position (@x, @y) on current
 * page of @fo_doc.
 **/
void
fo_doc_gp_render_layout_lines (FoDoc   *fo_doc,
			       FoArea  *area_layout,
			       gdouble   x,
			       gdouble   y)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (area_layout));

  /* Since GNOME Print doesn't support rendering only some lines from
   * a layout, firstly move the current point so the first line to be
   * rendered is positioned at (x, y) and, secondly, save the current
   * graphics state and then crop to only the area covered by the
   * lines that are to be rendered.
   */

  gdouble y1 = y;

  guint line_first = fo_area_layout_get_line_first (area_layout);
  if (line_first > 0)
    {
      y1 =
	y + fo_area_layout_get_line_height (area_layout,
					    line_first - 1);
    }

  guint line_last = fo_area_layout_get_line_last (area_layout);
  gdouble y2 =
      y1 - fo_area_layout_get_line_height (area_layout,
					   line_last);

  gdouble x2 =
      x + fo_area_area_get_width (area_layout);

#if ENABLE_CLIP
  gnome_print_gsave (FO_DOC_GP(fo_doc)->context);

  gnome_print_moveto (FO_DOC_GP(fo_doc)->context,
		      x, y);
  gnome_print_lineto (FO_DOC_GP(fo_doc)->context,
		      x2, y);
  gnome_print_lineto (FO_DOC_GP(fo_doc)->context,
		      x2, y2);
  gnome_print_lineto (FO_DOC_GP(fo_doc)->context,
		      x, y2);

  gnome_print_clip (FO_DOC_GP(fo_doc)->context);
#endif

  gnome_print_moveto (FO_DOC_GP(fo_doc)->context,
		      x,
		      y1);
  gnome_print_pango_layout (FO_DOC_GP(fo_doc)->context,
			    fo_layout_get_pango_layout (fo_area_layout_get_layout (area_layout)));

  fo_doc_gp_do_callbacks (FO_DOC_GP(fo_doc)->context,
			  fo_layout_get_pango_layout (fo_area_layout_get_layout (area_layout)),
			  line_first,
			  line_last,
			  x * PANGO_SCALE,
			  y * PANGO_SCALE);

#if ENABLE_CLIP
  gnome_print_grestore (FO_DOC_GP(fo_doc)->context);
#endif
}

/**
 * fo_doc_gp_render_layout:
 * @fo_doc:      #FoDoc to which to render.
 * @area_layout: #FoArea containing lines.
 * @x:           X-offset
 * @y:           Y-offset
 * 
 * Renders @area_layout at position (@x, @y) on current page of
 * @fo_doc.
 **/
void
fo_doc_gp_render_layout (FoDoc   *fo_doc,
			 FoArea  *area_layout,
			 gdouble   x,
			 gdouble   y)
{
  g_return_if_fail (FO_IS_DOC_GP (fo_doc));
  g_return_if_fail (FO_DOC_GP (fo_doc)->context != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (area_layout));

  gnome_print_moveto (FO_DOC_GP(fo_doc)->context,
		      x,
		      y);
  gnome_print_pango_layout (FO_DOC_GP(fo_doc)->context,
			    fo_layout_get_pango_layout (fo_area_layout_get_layout (area_layout)));

}

/**
 * fo_doc_gp_debug_dump:
 * @object: #FoObject to be dumped.
 * @depth:  Relative indent to add to the output.
 * 
 * Implements #FoObject debug_dump method for #FoDocGP.
 **/
void
fo_doc_gp_debug_dump (FoObject *object,
			  gint      depth)
{
  FoDocGP *fo_doc_gp;
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* object_sprintf;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_DOC_GP (object));

  fo_doc_gp = FO_DOC_GP (object);

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);

  object_sprintf = fo_object_debug_sprintf (fo_doc_gp->job);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    job:     %s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);

  object_sprintf = fo_object_debug_sprintf (fo_doc_gp->context);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    context: %s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);

  object_sprintf = fo_object_debug_sprintf (fo_doc_gp->config);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    config:  %s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    base_filename: %s",
	 indent,
	 fo_doc_gp->base_filename);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    output_sequence: %d",
	 indent,
	 fo_doc_gp->output_sequence);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    current_filename: %s",
	 indent,
	 fo_doc_gp->current_filename);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    page_width: %g",
	 indent,
	 fo_doc_gp->page_width);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    page_height: %g",
	 indent,
	 fo_doc_gp->page_height);

  g_free (indent);

}
