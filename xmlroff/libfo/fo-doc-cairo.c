/* Fo
 * fo-doc-cairo.c: libfo output document based on Cairo.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <cairo/cairo-pdf.h>
#include <cairo/cairo-ps.h>
#include <cairo/cairo-svg.h>
#include <pango/pango.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "area/fo-area-area.h"
#include "area/fo-area-layout.h"
#include "util/fo-pixbuf.h"
#include "fo-doc-cairo-private.h"
#include "fo-doc-commands.h"
#include "fo-layout-cairo-private.h"
#include "libfo-pango.h"
#include "datatype/fo-color.h"
#include <string.h>

#if HAVE_LIBRSVG
#include <librsvg/rsvg.h>
#include <librsvg/rsvg-cairo.h>
#endif

/**
 * SECTION:fo-doc-cairo
 * @short_description: Cairo backend
 *
 * Cairo backend.
 */

static void fo_doc_cairo_init          (FoDocCairo      *object);
static void fo_doc_cairo_base_init     (FoDocCairoClass *klass);
static void fo_doc_cairo_class_init    (FoDocCairoClass *klass);
static void fo_doc_cairo_finalize      (GObject         *object);

static const LibfoVersionInfo * _version_info ();

static FoLayout *    fo_doc_cairo_get_new_layout     (FoDoc        *fo_doc);

static void          fo_doc_cairo_begin_page         (FoDoc        *fo_doc,
						      gdouble       width,
						      gdouble       height,
						      GError      **error);
static void          fo_doc_cairo_end_page           (FoDoc        *fo_doc);
static FoDatatype *  fo_doc_cairo_get_fill_color     (FoDoc        *fo_doc);
static void          fo_doc_cairo_set_fill_color     (FoDoc        *fo_doc,
						      FoDatatype   *color);
static FoDatatype *  fo_doc_cairo_get_stroke_color   (FoDoc        *fo_doc);
static void          fo_doc_cairo_set_stroke_color   (FoDoc        *fo_doc,
						      FoDatatype   *color);
static void          fo_doc_cairo_translate          (FoDoc        *fo_doc,
						      gdouble       x,
						      gdouble       y);
static FoDocLineCap  fo_doc_cairo_get_line_cap       (FoDoc        *fo_doc);
static void          fo_doc_cairo_set_line_cap       (FoDoc        *fo_doc,
						      FoDocLineCap  line_cap);
static FoDocLineJoin fo_doc_cairo_get_line_join      (FoDoc        *fo_doc);
static void          fo_doc_cairo_set_line_join      (FoDoc        *fo_doc,
						      FoDocLineJoin line_join);
static gdouble       fo_doc_cairo_get_line_width      (FoDoc       *fo_doc);
static void          fo_doc_cairo_set_line_width      (FoDoc       *fo_doc,
						       gdouble      line_width);
static void          fo_doc_cairo_set_dash            (FoDoc       *fo_doc,
						       gdouble      b,
						       gdouble      w);
static void          fo_doc_cairo_translate           (FoDoc       *fo_doc,
						       gdouble      x,
						       gdouble      y);
static void          fo_doc_cairo_clip                (FoDoc       *fo_doc);
static void          fo_doc_cairo_save                (FoDoc       *fo_doc);
static void          fo_doc_cairo_restore             (FoDoc       *fo_doc);
static void          fo_doc_cairo_line_to             (FoDoc       *fo_doc,
						       gdouble      x,
						       gdouble      y);
static void          fo_doc_cairo_move_to             (FoDoc       *fo_doc,
						       gdouble      x,
						       gdouble      y);
static void          fo_doc_cairo_line_stroked        (FoDoc       *fo_doc,
						       gdouble      x0,
						       gdouble      y0,
						       gdouble      x1,
						       gdouble      y1);
static void          fo_doc_cairo_rect_stroked        (FoDoc       *fo_doc,
						       gdouble      x,
						       gdouble      y,
						       gdouble      width,
						       gdouble      height);
static void          fo_doc_cairo_rect_filled         (FoDoc       *fo_doc,
						       gdouble      x,
						       gdouble      y,
						       gdouble      width,
						       gdouble      height);
static void          fo_doc_cairo_fill                (FoDoc       *fo_doc);
static void          fo_doc_cairo_stroke              (FoDoc       *fo_doc);
static void          fo_doc_cairo_place_image         (FoDoc       *fo_doc,
						       FoImage     *fo_image,
						       gdouble      x,
						       gdouble      y,
						       gdouble      xscale,
						       gdouble      yscale);
static void          fo_doc_cairo_render_layout_lines (FoDoc       *fo_doc,
						       FoArea      *area_layout,
						       gdouble      x,
						       gdouble      y);
static void 	     fo_doc_cairo_render_layout       (FoDoc       *fo_doc,
						       FoArea      *area_layout,
						       gdouble      x,
						       gdouble      y);
static gpointer parent_class;

static LibfoVersionInfo version_info =
  {
    LIBFO_MODULE_BACKEND,
    "cairo",
    "FoDocCairo",
    CAIRO_VERSION,
    CAIRO_VERSION_STRING,
    0,
    NULL
  };

/**
 * fo_doc_cairo_error_quark:
 * 
 * Get the error quark for #FoDoc.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: Quark associated with #FoDoc errors.
 **/
GQuark
fo_doc_cairo_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoDocCairo error");
  return quark;
}


/**
 * fo_doc_cairo_get_type:
 * 
 * Register the #FoDoc object type.
 * 
 * Return value: #GType value of the #FoDocCairo object type.
 **/
GType
fo_doc_cairo_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoDocCairoClass),
        (GBaseInitFunc) fo_doc_cairo_base_init,
        NULL,		/* base_finalize */
        (GClassInitFunc) fo_doc_cairo_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoDocCairo),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_doc_cairo_init,
	NULL
      };
      
      object_type = g_type_register_static (FO_TYPE_DOC,
                                            "FoDocCairo",
                                            &object_info,
					    0);
    }
  
  return object_type;
}

/**
 * fo_doc_cairo_init:
 * @fo_doc_cairo: #FoDocCairo object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoDocCairo.
 **/
void
fo_doc_cairo_init (FoDocCairo *fo_doc_cairo)
{
  PangoFontMap *font_map = pango_cairo_font_map_get_default ();
  pango_cairo_font_map_set_resolution ((PangoCairoFontMap*) font_map, 72);
  FO_DOC (fo_doc_cairo)->pango_context =
    pango_cairo_font_map_create_context ((PangoCairoFontMap*) font_map);
}

/**
 * fo_doc_cairo_base_init:
 * @klass: #FoDocCairoClass base class object to initialise
 * 
 * Implements #GBaseInitFunc for #FoDocCairoClass
 **/
void
fo_doc_cairo_base_init (FoDocCairoClass *klass)
{
  FoLibfoModuleClass *fo_libfo_module_class =
    FO_LIBFO_MODULE_CLASS (klass);
  FoDocClass *fo_doc_class = FO_DOC_CLASS (klass);

  fo_libfo_module_class->version        = cairo_version;
  fo_libfo_module_class->version_string = cairo_version_string;
  fo_libfo_module_class->version_info   = _version_info;

  fo_doc_class->formats =
    FO_FLAG_FORMAT_PDF |
    FO_FLAG_FORMAT_POSTSCRIPT |
    FO_FLAG_FORMAT_SVG;

  fo_doc_class->open_file           = fo_doc_cairo_open_file;

  fo_doc_class->get_new_layout      = fo_doc_cairo_get_new_layout;

  fo_doc_class->begin_page          = fo_doc_cairo_begin_page;
  fo_doc_class->end_page            = fo_doc_cairo_end_page;
  fo_doc_class->get_fill_color      = fo_doc_cairo_get_fill_color;
  fo_doc_class->set_fill_color      = fo_doc_cairo_set_fill_color;
  fo_doc_class->get_stroke_color    = fo_doc_cairo_get_stroke_color;
  fo_doc_class->set_stroke_color    = fo_doc_cairo_set_stroke_color;
  fo_doc_class->get_line_cap        = fo_doc_cairo_get_line_cap;
  fo_doc_class->set_line_cap        = fo_doc_cairo_set_line_cap;
  fo_doc_class->get_line_join       = fo_doc_cairo_get_line_join;
  fo_doc_class->set_line_join       = fo_doc_cairo_set_line_join;
  fo_doc_class->get_line_width      = fo_doc_cairo_get_line_width;
  fo_doc_class->set_line_width      = fo_doc_cairo_set_line_width;
  fo_doc_class->set_dash            = fo_doc_cairo_set_dash;
  fo_doc_class->translate           = fo_doc_cairo_translate;
  fo_doc_class->clip                = fo_doc_cairo_clip;
  fo_doc_class->save                = fo_doc_cairo_save;
  fo_doc_class->restore             = fo_doc_cairo_restore;
  fo_doc_class->line_to             = fo_doc_cairo_line_to;
  fo_doc_class->move_to             = fo_doc_cairo_move_to;
  fo_doc_class->line_stroked        = fo_doc_cairo_line_stroked;
  fo_doc_class->rect_stroked        = fo_doc_cairo_rect_stroked;
  fo_doc_class->rect_filled         = fo_doc_cairo_rect_filled;
  fo_doc_class->fill                = fo_doc_cairo_fill;
  fo_doc_class->stroke              = fo_doc_cairo_stroke;
  fo_doc_class->place_image         = fo_doc_cairo_place_image;
  fo_doc_class->render_layout_lines = fo_doc_cairo_render_layout_lines;
  fo_doc_class->render_layout       = fo_doc_cairo_render_layout;
}

/**
 * fo_doc_cairo_class_init:
 * @klass: #FoDocCairoClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoDocCairoClass.
 **/
void
fo_doc_cairo_class_init (FoDocCairoClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_doc_cairo_finalize;
}

/**
 * fo_doc_cairo_finalize:
 * @object: #FoDocCairo object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoDocCairo.
 **/
void
fo_doc_cairo_finalize (GObject *object)
{
  FoDocCairo *fo_doc_cairo;

  fo_doc_cairo = FO_DOC_CAIRO (object);

  cairo_destroy (fo_doc_cairo->cr);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_doc_cairo_new:
 * 
 * Creates a new #FoDoc.
 * 
 * Return value: the newly created #FoDoc.
 **/
FoDoc *
fo_doc_cairo_new (void)
{
  return FO_DOC (g_object_new (fo_doc_cairo_get_type (),
			       NULL));
}

const LibfoVersionInfo *
_version_info ()
{
  version_info.runtime = cairo_version ();
  version_info.runtime_string = cairo_version_string ();

  return &version_info;
}


/**
 * fo_doc_cairo_open_file:
 * @fo_doc:        #FoDoc.
 * @filename:      File to open as output.
 * @libfo_context: #FoLibfoContext specifying file format.
 * @error:         #GError that is set if an error occurs.
 * 
 * Open @filename as the output file for @fo_doc.
 *
 * No reference to @libfo_context is kept.
 **/
void
fo_doc_cairo_open_file (FoDoc          *fo_doc,
			const gchar    *filename,
			FoLibfoContext *libfo_context,
			GError        **error)
{
  FoDocCairo *fo_doc_cairo;
  gint len;

  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (filename != NULL);
  g_return_if_fail (*filename != '\0');
  g_return_if_fail (error == NULL || *error == NULL);

  fo_doc_cairo = FO_DOC_CAIRO (fo_doc);

  fo_doc_cairo->base_filename = g_strdup (filename);
  fo_doc_cairo->current_filename = g_strdup (filename);
  fo_doc_cairo->format = fo_libfo_context_get_format (libfo_context);

  len = strlen (fo_doc_cairo->base_filename);
  switch (fo_doc_cairo->format)
    {
    case FO_FLAG_FORMAT_AUTO:
      if (g_ascii_strncasecmp (&(fo_doc_cairo->base_filename)[len-4], ".pdf", 4) == 0)
	{
	  fo_doc_cairo->surface_create = &cairo_pdf_surface_create;
	}
      else if (g_ascii_strncasecmp (&(fo_doc_cairo->base_filename)[len-3], ".ps", 3) == 0)
	{
	  fo_doc_cairo->surface_create = &cairo_ps_surface_create;
	}
      else if (g_ascii_strncasecmp (&(fo_doc_cairo->base_filename)[len-4], ".svg", 4) == 0)
	{
	  fo_doc_cairo->surface_create = &cairo_svg_surface_create;
	}
      else
	{
	  g_set_error (error,
		       FO_DOC_ERROR,
		       FO_DOC_ERROR_UNSUPPORTED_FORMAT,
		       "%s",
		       N_(fo_doc_error_messages[FO_DOC_ERROR_UNSUPPORTED_FORMAT]));
	}
      break;
    case FO_FLAG_FORMAT_PDF:
      fo_doc_cairo->surface_create = &cairo_pdf_surface_create;
      break;
    case FO_FLAG_FORMAT_POSTSCRIPT:
      fo_doc_cairo->surface_create = &cairo_ps_surface_create;
      break;
    case FO_FLAG_FORMAT_SVG:
      fo_doc_cairo->surface_create = &cairo_svg_surface_create;
      break;
    default:
      g_set_error (error,
		   FO_DOC_ERROR,
		   FO_DOC_ERROR_UNSUPPORTED_FORMAT,
		  "%s",
		   N_(fo_doc_error_messages[FO_DOC_ERROR_UNSUPPORTED_FORMAT]));

    }
}

/**
 * fo_doc_cairo_get_new_layout:
 * @fo_doc: #FoDoc.
 * 
 * Get a new #FoLayout for use with @fo_doc.
 *
 * Return value: New #FoLayout.
 **/
FoLayout *
fo_doc_cairo_get_new_layout (FoDoc *fo_doc)
{
  FoLayout *fo_layout;

  g_return_val_if_fail (FO_IS_DOC_CAIRO (fo_doc), NULL);

  fo_layout = fo_layout_cairo_new ();

  fo_layout->fo_doc = fo_doc;
  fo_layout->pango_layout =
    pango_layout_new (fo_doc->pango_context);

  return fo_layout;
}

static void
_fo_doc_cairo_create_cr (FoDocCairo   *fo_doc_cairo,
			 gdouble       width,
			 gdouble       height,
			 GError      **error)
{
  g_return_if_fail (error == NULL || *error == NULL);

  cairo_surface_t *surface = fo_doc_cairo->surface_create (fo_doc_cairo->current_filename,
							   width,
							   height);

  if (cairo_surface_status (surface) != CAIRO_STATUS_SUCCESS)
    {
      g_set_error (error,
		   FO_DOC_ERROR,
		   FO_DOC_ERROR_FAILED,
		   "%s",
		   N_(fo_doc_error_messages[FO_DOC_ERROR_FAILED]));
      return;
    }

  cairo_surface_set_fallback_resolution (surface,
					 PIXELS_PER_INCH,
					 PIXELS_PER_INCH);

  fo_doc_cairo->cr = cairo_create (surface);

  cairo_surface_destroy (surface);

  if (cairo_status (fo_doc_cairo->cr) != CAIRO_STATUS_SUCCESS)
    {
      g_set_error (error,
		   FO_DOC_ERROR,
		   FO_DOC_ERROR_FAILED,
		   "%s",
		   N_(fo_doc_error_messages[FO_DOC_ERROR_FAILED]));
      return;
    }

  pango_cairo_update_context (fo_doc_cairo->cr,
			      FO_DOC (fo_doc_cairo)->pango_context);

  fo_doc_cairo->page_width = width;
  fo_doc_cairo->page_height = height;
}

/**
 * fo_doc_cairo_begin_page:
 * @fo_doc: #FoDoc.
 * @width:  Width of the new page.
 * @height: Height of the new page.
 * 
 * Add a new page to @fo_doc.
 *
 * This must always be paired with a matching #fo_doc_cairo_end_page call.
 **/
void
fo_doc_cairo_begin_page (FoDoc   *fo_doc,
			 gdouble  width,
			 gdouble  height,
			 GError **error)
{
  FoDocCairo *fo_doc_cairo;
  GError *tmp_error = NULL;

  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_doc_cairo = FO_DOC_CAIRO (fo_doc);
  
  if (fo_doc_cairo->cr == NULL)
    {
      _fo_doc_cairo_create_cr (fo_doc_cairo,
			       width,
			       height,
			       &tmp_error);
      if (tmp_error != NULL)
	{
	  g_propagate_error (error,
			     tmp_error);
	  return;
	}
    }
  else if ((width != fo_doc_cairo->page_width) ||
	   (height != fo_doc_cairo->page_height))
    {
      cairo_destroy (fo_doc_cairo->cr);
      g_free (fo_doc_cairo->current_filename);

      fo_doc_cairo->output_sequence++;

      fo_doc_cairo->current_filename =
	g_strdup_printf ("%*s.%02d%s",
			 (int) (g_strrstr (fo_doc_cairo->base_filename, ".") -
			  fo_doc_cairo->base_filename),
			 fo_doc_cairo->base_filename,
			 fo_doc_cairo->output_sequence,
			 g_strrstr (fo_doc_cairo->base_filename, "."));      

      _fo_doc_cairo_create_cr (fo_doc_cairo,
			       width,
			       height,
			       &tmp_error);

      if (tmp_error != NULL)
	{
	  g_propagate_error (error,
			     tmp_error);
	  return;
	}
    }
}

/**
 * fo_doc_cairo_end_page:
 * @fo_doc: #FoDoc.
 * 
 * Finish the current page of @fo_doc.
 **/
void
fo_doc_cairo_end_page (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_show_page (FO_DOC_CAIRO (fo_doc)->cr);
}

/**
 * fo_doc_cairo_get_fill_color:
 * @fo_doc: #FoDoc.
 * 
 * Get the current fill color of @fo_doc.
 * 
 * Return value: #FoDatatype for the current fill color.
 **/
FoDatatype*
fo_doc_cairo_get_fill_color (FoDoc *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_CAIRO (fo_doc), NULL);

  return fo_doc->fill_color;
}

/**
 * fo_doc_cairo_set_fill_color:
 * @fo_doc: #FoDoc.
 * @color:  #FoDatatype for new fill color.
 * 
 * Set the fill color of @fo_doc to @color.
 **/
void
fo_doc_cairo_set_fill_color (FoDoc *fo_doc,
			     FoDatatype *color)
{
  guint16 red;
  guint16 green;
  guint16 blue;

  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);
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

  cairo_set_source_rgb (FO_DOC_CAIRO (fo_doc)->cr,
			(gdouble) red / FO_COLOR_COMPONENT_MAX,
			(gdouble) green / FO_COLOR_COMPONENT_MAX,
			(gdouble) blue / FO_COLOR_COMPONENT_MAX);
}

/**
 * fo_doc_cairo_get_stroke_color:
 * @fo_doc: #FoDoc.
 * 
 * Get the current stroke color of @fo_doc.
 * 
 * Return value: #FoDatatype for the current stroke color.
 **/
FoDatatype*
fo_doc_cairo_get_stroke_color (FoDoc *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_CAIRO (fo_doc), NULL);

  return fo_doc->stroke_color;
}

/**
 * fo_doc_cairo_set_stroke_color:
 * @fo_doc: #FoDoc.
 * @color:  #FoDatatype for new stroke color.
 * 
 * Set the stroke color of @fo_doc to @color.
 **/
void
fo_doc_cairo_set_stroke_color (FoDoc *fo_doc,
				FoDatatype *color)
{
  guint16 red;
  guint16 green;
  guint16 blue;

  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);
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

  cairo_set_source_rgb (FO_DOC_CAIRO (fo_doc)->cr,
			(gdouble) red / FO_COLOR_COMPONENT_MAX,
			(gdouble) green / FO_COLOR_COMPONENT_MAX,
			(gdouble) blue / FO_COLOR_COMPONENT_MAX);
}

/**
 * fo_doc_cairo_get_line_cap:
 * @fo_doc: #FoDoc.
 * 
 * Get the current "linecap" parameter value of @fo_doc.
 * 
 * Return value: Current "linecap" parameter value.
 **/
FoDocLineCap
fo_doc_cairo_get_line_cap (FoDoc        *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_CAIRO (fo_doc), FO_DOC_LINE_CAP_INVALID);

  return fo_doc->line_cap;
}

/**
 * fo_doc_cairo_set_line_cap:
 * @fo_doc:   #FoDoc.
 * @line_cap: New "linecap" parameter value.
 * 
 * Set the "linecap" parameter value of @fo_doc.
 **/
void
fo_doc_cairo_set_line_cap (FoDoc       *fo_doc,
			   FoDocLineCap line_cap)
{
  cairo_line_cap_t cairo_line_cap = CAIRO_LINE_CAP_BUTT;

  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);
  g_return_if_fail (line_cap < FO_DOC_LINE_CAP_LIMIT);
  g_return_if_fail (line_cap != FO_DOC_LINE_CAP_INVALID);

  fo_doc->line_cap = line_cap;

  switch (line_cap)
    {
    case FO_DOC_LINE_CAP_BUTT:
      cairo_line_cap = CAIRO_LINE_CAP_BUTT;
      break;
    case FO_DOC_LINE_CAP_ROUND:
      cairo_line_cap = CAIRO_LINE_CAP_ROUND;
      break;
    case FO_DOC_LINE_CAP_SQUARE:
      cairo_line_cap = CAIRO_LINE_CAP_SQUARE;
      break;
    default:
      g_assert_not_reached ();
  }

  cairo_set_line_cap (FO_DOC_CAIRO (fo_doc)->cr,
		      cairo_line_cap);
}

/**
 * fo_doc_cairo_get_line_join:
 * @fo_doc: #FoDoc.
 * 
 * Get the current "linejoin" parameter value of @fo_doc.
 * 
 * Return value: Current "linejoin" parameter value.
 **/
FoDocLineJoin
fo_doc_cairo_get_line_join (FoDoc        *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_CAIRO (fo_doc), FO_DOC_LINE_JOIN_INVALID);

  return fo_doc->line_join;
}

/**
 * fo_doc_cairo_set_line_join:
 * @fo_doc:   #FoDoc.
 * @line_join: New "linejoin" parameter value.
 * 
 * Set the "linejoin" parameter value of @fo_doc.
 **/
void
fo_doc_cairo_set_line_join (FoDoc        *fo_doc,
			    FoDocLineJoin line_join)
{
  cairo_line_join_t cairo_line_join = CAIRO_LINE_JOIN_MITER;

  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);
  g_return_if_fail (line_join < FO_DOC_LINE_JOIN_LIMIT);

  fo_doc->line_join = line_join;

  switch (line_join)
    {
    case FO_DOC_LINE_JOIN_MITER:
      cairo_line_join = CAIRO_LINE_JOIN_MITER;
      break;
    case FO_DOC_LINE_JOIN_ROUND:
      cairo_line_join = CAIRO_LINE_JOIN_ROUND;
      break;
    case FO_DOC_LINE_JOIN_BEVEL:
      cairo_line_join = CAIRO_LINE_JOIN_BEVEL;
      break;
    default:
      g_assert_not_reached ();
  }

  cairo_set_line_join (FO_DOC_CAIRO (fo_doc)->cr,
		       cairo_line_join);
}

/**
 * fo_doc_cairo_get_line_width:
 * @fo_doc: #FoDoc.
 * 
 * Get the current line width of @fo_doc.
 * 
 * Return value: Current line width.
 **/
gdouble
fo_doc_cairo_get_line_width (FoDoc        *fo_doc)
{
  g_return_val_if_fail (FO_IS_DOC_CAIRO (fo_doc), 0);

  return fo_doc->line_width;
}

/**
 * fo_doc_cairo_set_line_width:
 * @fo_doc:   #FoDoc.
 * @line_width: New line width value.
 * 
 * Set the line width of @fo_doc.
 **/
void
fo_doc_cairo_set_line_width (FoDoc  *fo_doc,
			     gdouble line_width)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  fo_doc->line_width = line_width;
  cairo_set_line_width (FO_DOC_CAIRO (fo_doc)->cr,
			line_width);
}

/**
 * fo_doc_cairo_set_dash:
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
fo_doc_cairo_set_dash (FoDoc  *fo_doc,
		       gdouble b,
		       gdouble w)
{
  const gdouble values[] = {b,w};
  gint n = ((b == 0.0) && (w == 0.0))? 0 : 2;

  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_set_dash (FO_DOC_CAIRO (fo_doc)->cr,
		  values,
		  n,
		  0.0);
}

/**
 * fo_doc_cairo_line_to:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new current point.
 * @y:      Y-coordinate of the new current point.
 * 
 * Draw a line from the current point to another point.
 **/
void
fo_doc_cairo_line_to (FoDoc  *fo_doc,
		      gdouble x,
		      gdouble y)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_line_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x,
		 FO_DOC_CAIRO (fo_doc)->page_height - y);
}

/**
 * fo_doc_cairo_translate:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new origin of the coordinate system.
 * @y:      Y-coordinate of the new origin of the coordinate system.
 * 
 * Translate the origin of the coordinate system of @fo_doc.
 *
 * @x and @y are measured in the old coordinate system.
 **/
void
fo_doc_cairo_translate (FoDoc  *fo_doc,
			gdouble x,
			gdouble y)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_translate (FO_DOC_CAIRO (fo_doc)->cr, x, -y);
}

/**
 * fo_doc_cairo_clip:
 * @fo_doc: #FoDoc.
 * 
 * Use the current path of @fo_doc as its clipping path.
 **/
void
fo_doc_cairo_clip (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_clip (FO_DOC_CAIRO (fo_doc)->cr);
}

/**
 * fo_doc_cairo_save:
 * @fo_doc: #FoDoc.
 * 
 * Save the current graphics state of @fo_doc.
 **/
void
fo_doc_cairo_save (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_save (FO_DOC_CAIRO (fo_doc)->cr);
}

/**
 * fo_doc_cairo_restore:
 * @fo_doc: #FoDoc.
 * 
 * Restore the most recently saved graphics state of @fo_doc.
 **/
void
fo_doc_cairo_restore (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_restore (FO_DOC_CAIRO (fo_doc)->cr);
}

/**
 * fo_doc_cairo_move_to:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new current point.
 * @y:      Y-coordinate of the new current point.
 * 
 * Set the current point of @fo_doc to (@x, @y).
 **/
void
fo_doc_cairo_move_to (FoDoc *fo_doc,
		       gdouble x,
		       gdouble y)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_move_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x,
		 FO_DOC_CAIRO (fo_doc)->page_height - y);
}

/**
 * fo_doc_cairo_line_stroked:
 * @fo_doc: #FoDoc.
 * @x0: X-coordinate of the start of the line.
 * @y0: Y-coordinate of the start of the line.
 * @x1: X-coordinate of the end of the line.
 * @y1: Y-coordinate of the end of the line.
 * 
 * Draw a line from (@x0,@y0) to (@x1,@y1).
 **/
void
fo_doc_cairo_line_stroked (FoDoc  *fo_doc,
			   gdouble x0,
			   gdouble y0,
			   gdouble x1,
			   gdouble y1)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_move_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x0,
		 FO_DOC_CAIRO (fo_doc)->page_height - y0);
  cairo_line_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x1,
		 FO_DOC_CAIRO (fo_doc)->page_height - y1);
}

/**
 * fo_doc_cairo_rect_stroked:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the lower-left corner of the rectangle.
 * @y:      Y-coordinate of the lower-left corner of the rectangle.
 * @width:  Width of the rectangle.
 * @height: Height of the rectangle.
 * 
 * Draw an outline rectangle.
 **/
void
fo_doc_cairo_rect_stroked (FoDoc *fo_doc,
			gdouble x,
			gdouble y,
			gdouble width,
			gdouble height)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_rectangle (FO_DOC_CAIRO (fo_doc)->cr,
		   x,
		   FO_DOC_CAIRO (fo_doc)->page_height - y,
		   width,
		   height);
}

/**
 * fo_doc_cairo_rect_filled:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the lower-left corner of the rectangle.
 * @y:      Y-coordinate of the lower-left corner of the rectangle.
 * @width:  Width of the rectangle.
 * @height: Height of the rectangle.
 * 
 * Draw a filled rectangle.
 **/
void
fo_doc_cairo_rect_filled (FoDoc *fo_doc,
		       gdouble x,
		       gdouble y,
		       gdouble width,
		       gdouble height)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_rectangle (FO_DOC_CAIRO (fo_doc)->cr,
		   x,
		   FO_DOC_CAIRO (fo_doc)->page_height - y - height,
		   width,
		   height);
  cairo_fill (FO_DOC_CAIRO (fo_doc)->cr);
}

/**
 * fo_doc_cairo_fill:
 * @fo_doc: #FoDoc.
 * 
 * Fill the interior of the path of @fo_doc with the current fill color.
 **/
void
fo_doc_cairo_fill (FoDoc *fo_doc)
{
  g_return_if_fail (fo_doc != NULL);
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_fill (FO_DOC_CAIRO (fo_doc)->cr);
}

/**
 * fo_doc_cairo_stroke:
 * @fo_doc: #FoDoc.
 * 
 * Stroke the path of @fo_doc and clear the path.
 **/
void
fo_doc_cairo_stroke (FoDoc *fo_doc)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);

  cairo_stroke (FO_DOC_CAIRO (fo_doc)->cr);
}

/**
 * fo_doc_cairo_place_image:
 * @fo_doc: 
 * @fo_image: 
 * @x: 
 * @y: 
 * @xscale: 
 * @yscale: 
 * 
 * 
 **/
static void
fo_doc_cairo_place_image (FoDoc   *fo_doc,
			  FoImage *fo_image,
			  gdouble  x G_GNUC_UNUSED,
			  gdouble  y G_GNUC_UNUSED,
			  gdouble  xscale G_GNUC_UNUSED,
			  gdouble  yscale G_GNUC_UNUSED)
{
  GdkPixbuf *pixbuf = g_object_ref (fo_pixbuf_get_pixbuf (fo_image));
  gint width = gdk_pixbuf_get_width (pixbuf);
  gint height = gdk_pixbuf_get_height (pixbuf);
  guchar *gdk_pixels = gdk_pixbuf_get_pixels (pixbuf);
  int gdk_rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  int n_channels = gdk_pixbuf_get_n_channels (pixbuf);
  guchar *cairo_pixels;
  cairo_format_t format;
  cairo_surface_t *surface;
  static const cairo_user_data_key_t key;
  int j;

  cairo_translate (FO_DOC_CAIRO (fo_doc)->cr,
		   0,
		   FO_DOC_CAIRO(fo_doc)->page_height);
  cairo_save (FO_DOC_CAIRO(fo_doc)->cr);
  cairo_scale (FO_DOC_CAIRO (fo_doc)->cr,
	       xscale * 72.0 / PIXELS_PER_INCH,
	       yscale * 72.0 / PIXELS_PER_INCH);

#if HAVE_LIBRSVG
  if (g_str_has_suffix( fo_image_get_uri(fo_image), ".svg"))
    {
      RsvgHandle *rsvg;
      GError *error = NULL;
      g_log (G_LOG_DOMAIN,
             G_LOG_LEVEL_DEBUG,
             "rendering %s as SVG\n",
             fo_image_get_uri(fo_image));
      rsvg_init();
      rsvg_set_default_dpi_x_y (PIXELS_PER_INCH, PIXELS_PER_INCH);
      rsvg = rsvg_handle_new_from_file (fo_image_get_uri(fo_image), &error);
      rsvg_handle_render_cairo (rsvg, FO_DOC_CAIRO(fo_doc)->cr);
      rsvg_term();
      cairo_restore (FO_DOC_CAIRO(fo_doc)->cr);
      if (error) {
	g_log (G_LOG_DOMAIN,
	       G_LOG_LEVEL_ERROR,
	       error->message);
	g_error_free (error);
      }
      return;
    }
#endif

  if (n_channels == 3)
    {
      format = CAIRO_FORMAT_RGB24;
    }
  else
    {
      format = CAIRO_FORMAT_ARGB32;
    }

  cairo_pixels = g_malloc (4 * width * height);
  surface = cairo_image_surface_create_for_data ((unsigned char *)cairo_pixels,
						 format,
						 width, height, 4 * width);
  cairo_surface_set_user_data (surface, &key,
			       cairo_pixels, (cairo_destroy_func_t)g_free);

  for (j = height; j; j--)
    {
      guchar *p = gdk_pixels;
      guchar *q = cairo_pixels;

      if (n_channels == 3)
	{
	  guchar *end = p + 3 * width;
	  
	  while (p < end)
	    {
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
	      q[0] = p[2];
	      q[1] = p[1];
	      q[2] = p[0];
#else	  
	      q[1] = p[0];
	      q[2] = p[1];
	      q[3] = p[2];
#endif
	      p += 3;
	      q += 4;
	    }
	}
      else
	{
	  guchar *end = p + 4 * width;
	  guint t1,t2,t3;
	    
#define MULT(d,c,a,t) G_STMT_START { t = c * a + 0x7f; d = ((t >> 8) + t) >> 8; } G_STMT_END

	  while (p < end)
	    {
#if G_BYTE_ORDER == G_LITTLE_ENDIAN
	      MULT(q[0], p[2], p[3], t1);
	      MULT(q[1], p[1], p[3], t2);
	      MULT(q[2], p[0], p[3], t3);
	      q[3] = p[3];
#else	  
	      q[0] = p[3];
	      MULT(q[1], p[0], p[3], t1);
	      MULT(q[2], p[1], p[3], t2);
	      MULT(q[3], p[2], p[3], t3);
#endif
	      
	      p += 4;
	      q += 4;
	    }
	  
#undef MULT
	}

      gdk_pixels += gdk_rowstride;
      cairo_pixels += 4 * width;
    }

  cairo_surface_set_fallback_resolution (surface,
					 PIXELS_PER_INCH,
					 PIXELS_PER_INCH);
  cairo_set_source_surface (FO_DOC_CAIRO (fo_doc)->cr, surface, 0, 0);
  cairo_pattern_t *pattern = cairo_get_source (FO_DOC_CAIRO (fo_doc)->cr);
  cairo_pattern_set_extend (pattern,
			    CAIRO_EXTEND_NONE);
  cairo_paint (FO_DOC_CAIRO (fo_doc)->cr);
  cairo_surface_destroy (surface);
  g_object_unref (pixbuf);
  cairo_restore (FO_DOC_CAIRO(fo_doc)->cr);
}

void
fo_doc_cairo_do_run_callbacks (cairo_t        *cr,
			       PangoLayoutRun *run,
			       gint            x, 
			       gint            y)
{
  GSList *extra_attrs_list = run->item->analysis.extra_attrs;

  g_return_if_fail (cr != NULL);
  g_return_if_fail (run != NULL);

  while (extra_attrs_list)
    {
      PangoAttribute *attr = extra_attrs_list->data;
      PangoAttrType attr_type = attr->klass->type;

      if (attr_type == libfo_pango_attr_callback_get_type ())
	{
	  GValue values[1] = { { 0, { {0}, {0} } } };

	  g_value_init (&values[0], G_TYPE_POINTER);
	  g_value_set_pointer (&values[0], cr);

#if 0
	  g_message ("Got a callback: callback: %p",
		     ((PangoAttrPointer *) attr)->pointer);
#endif

	  cairo_save (cr);

	  cairo_translate (cr,
			   x / PANGO_SCALE,
			   -y / PANGO_SCALE);

	  g_closure_invoke (((GClosure *) libfo_pango_attr_callback_get_callback(attr)),
			     NULL,
			     1,
			     values,
			     NULL);
	  cairo_restore (cr);
	}

      extra_attrs_list = extra_attrs_list->next;
    }
}

void 
fo_doc_cairo_do_line_callbacks (cairo_t         *cr,
				PangoLayoutLine *line,
				gint             x, 
				gint             y)
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

      fo_doc_cairo_do_run_callbacks (cr,
				  run,
				  x + x_off,
				  y);

      x_off += logical_rect.width;
      run_list = run_list->next;
    }
}

static void
fo_doc_cairo_do_callbacks (cairo_t     *cr,
			   PangoLayout *layout,
			   gint         line_first,
			   gint         line_last,
			   gint         x,
			   gint         y)
{
  PangoLayoutIter *iter;
  
  g_return_if_fail (cr != NULL);
  g_return_if_fail (PANGO_IS_LAYOUT (layout));
  g_return_if_fail (line_first >= 0);
  /*g_return_if_fail (line_last >= line_first &&
    line_last <= g_slist_length (pango_layout_get_lines (layout)) - 1);*/

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
      
      fo_doc_cairo_do_line_callbacks (cr,
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
 * fo_doc_cairo_render_layout_lines:
 * @fo_doc: 
 * @area_layout: 
 * @x: 
 * @y: 
 * 
 * 
 **/
void
fo_doc_cairo_render_layout_lines (FoDoc   *fo_doc,
				  FoArea  *area_layout,
				  gdouble   x,
				  gdouble   y)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (area_layout));

  /* Since Cairo doesn't support rendering only some lines from
   * a layout, firstly move the current point so the first line to be
   * rendered is positioned at (x, y) and, secondly, save the current
   * graphics state and then crop to only the area covered by the
   * lines that are to be rendered.
   */

  gdouble y1 = y;

  gint line_first = fo_area_layout_get_line_first (area_layout);
  if (line_first > 0)
    {
      y1 =
	y + fo_area_layout_get_line_height (area_layout,
					    line_first - 1);
    }

  gint line_last = fo_area_layout_get_line_last (area_layout);
#if ENABLE_CLIP
  gdouble y2 =
      y1 - fo_area_layout_get_line_height (area_layout,
					   line_last);

  gdouble x2 =
      x + fo_area_area_get_width (area_layout);

  cairo_save (FO_DOC_CAIRO (fo_doc)->cr);

  cairo_move_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x, FO_DOC_CAIRO (fo_doc)->page_height - y);
  cairo_line_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x2, FO_DOC_CAIRO (fo_doc)->page_height - y);
  cairo_line_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x2, FO_DOC_CAIRO (fo_doc)->page_height - y2);
  cairo_line_to (FO_DOC_CAIRO(fo_doc)->cr,
		 x, FO_DOC_CAIRO (fo_doc)->page_height - y2);

  cairo_clip (FO_DOC_CAIRO (fo_doc)->cr);
#endif

  cairo_move_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x,
		 FO_DOC_CAIRO (fo_doc)->page_height - y1);
  pango_cairo_show_layout (FO_DOC_CAIRO (fo_doc)->cr,
			   fo_layout_get_pango_layout (fo_area_layout_get_layout (area_layout)));

  fo_doc_cairo_do_callbacks (FO_DOC_CAIRO (fo_doc)->cr,
			     fo_layout_get_pango_layout (fo_area_layout_get_layout (area_layout)),
			     line_first,
			     line_last,
			     x * PANGO_SCALE,
			     y * PANGO_SCALE);

#if ENABLE_CLIP
  cairo_restore (FO_DOC_CAIRO(fo_doc)->cr);
#endif
}

/**
 * fo_doc_cairo_render_layout:
 * @fo_doc: 
 * @area_layout: 
 * @x: 
 * @y: 
 * 
 * 
 **/
void
fo_doc_cairo_render_layout (FoDoc   *fo_doc,
			    FoArea  *area_layout,
			    gdouble  x,
			    gdouble  y)
{
  g_return_if_fail (FO_IS_DOC_CAIRO (fo_doc));
  g_return_if_fail (FO_DOC_CAIRO (fo_doc)->cr != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (area_layout));

  cairo_move_to (FO_DOC_CAIRO (fo_doc)->cr,
		 x,
		 FO_DOC_CAIRO (fo_doc)->page_height - y);
  pango_cairo_show_layout (FO_DOC_CAIRO (fo_doc)->cr,
			   fo_layout_get_pango_layout (fo_area_layout_get_layout (area_layout)));

}

/**
 * fo_doc_cairo_debug_dump:
 * @object: #FoObject to be dumped.
 * @depth:  Relative indent to add to the output.
 * 
 * Implements #FoObject debug_dump method for #FoDocCairo.
 **/
void
fo_doc_cairo_debug_dump (FoObject *object,
			  gint      depth)
{
  FoDocCairo *fo_doc_cairo;
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* object_sprintf;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_DOC_CAIRO (object));

  fo_doc_cairo = FO_DOC_CAIRO (object);

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);

  object_sprintf = fo_object_debug_sprintf (fo_doc_cairo->cr);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    cr: %s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    base_filename: %s",
	 indent,
	 fo_doc_cairo->base_filename);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    output_sequence: %d",
	 indent,
	 fo_doc_cairo->output_sequence);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    current_filename: %s",
	 indent,
	 fo_doc_cairo->current_filename);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    page_width: %g",
	 indent,
	 fo_doc_cairo->page_width);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    page_height: %g",
	 indent,
	 fo_doc_cairo->page_height);

  g_free (indent);

}
