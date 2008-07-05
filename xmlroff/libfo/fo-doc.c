/* Fo
 * fo-doc.c: Wrapper for libfo output document
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "config.h"
#include <string.h>
#include "fo-utils.h"
#include "fo-doc-private.h"
#include "fo-doc-commands.h"
#if ENABLE_CAIRO
#include "fo-doc-cairo.h"
#endif
#if ENABLE_GP
#include "fo-doc-gp.h"
#endif
#include "datatype/fo-color.h"
#include <pango/pango.h>
#if 0
#include <pango/pangoft2.h>
#include <pango/pango-context.h>
#endif
#include "fo-font-desc-private.h"
#include "fo-libfo-context.h"

/**
 * SECTION:fo-doc
 * @short_description: Abstract output document type
 *
 * #FoDoc provides the primitives for writing text, lines, rectangles,
 * etc., to the output.
 *
 * It is generalised so that libfo can support multiple backend
 * implementations (and add and remove backend implementations)
 * without having to restructure the rest of libfo.
 */

const char *fo_doc_error_messages [] = {
  N_("FoDoc error"),
  N_("Cannot open output document: '%s'"),
  N_("Unsupported document format.")
};

enum {
  PROP_0,
  PROP_FORMATS
};

static void          fo_doc_base_init    (FoDocClass *klass);
static void          fo_doc_class_init   (FoDocClass *klass);
static void          fo_doc_get_property (GObject    *object,
					  guint       param_id,
					  GValue     *value,
					  GParamSpec *pspec);

static void          fo_doc_open_file_default      (FoDoc          *fo_doc,
						    const gchar    *filename,
						    FoLibfoContext *libfo_context,
						    GError        **error);
static FoLayout *    fo_doc_get_new_layout_default (FoDoc        *fo_doc);
static void          fo_doc_begin_page_default     (FoDoc        *fo_doc,
						    gdouble        width,
						    gdouble        height,
						    GError       **error);
static void          fo_doc_end_page_default       (FoDoc        *fo_doc);
static FoDatatype *  fo_doc_get_fill_color_default (FoDoc        *fo_doc);
static void          fo_doc_set_fill_color_default (FoDoc        *fo_doc,
						    FoDatatype   *color);
static FoDatatype *  fo_doc_get_stroke_color_default (FoDoc        *fo_doc);
static void          fo_doc_set_stroke_color_default (FoDoc        *fo_doc,
						      FoDatatype   *color);
static FoDocLineCap  fo_doc_get_line_cap_default    (FoDoc        *fo_doc);
static void          fo_doc_set_line_cap_default    (FoDoc        *fo_doc,
						     FoDocLineCap  line_cap);
static FoDocLineJoin fo_doc_get_line_join_default   (FoDoc        *fo_doc);
static void          fo_doc_set_line_join_default   (FoDoc        *fo_doc,
						     FoDocLineJoin line_join);
static gdouble        fo_doc_get_line_width_default  (FoDoc        *fo_doc);
static void          fo_doc_set_line_width_default  (FoDoc        *fo_doc,
						     gdouble        line_width);
static void          fo_doc_set_dash_default        (FoDoc        *fo_doc,
						     gdouble        b,
						     gdouble        w);
static void          fo_doc_translate_default       (FoDoc        *fo_doc,
						     gdouble        x,
						     gdouble        y);
static void          fo_doc_clip_default            (FoDoc        *fo_doc);
static void          fo_doc_save_default            (FoDoc        *fo_doc);
static void          fo_doc_restore_default         (FoDoc        *fo_doc);
static void          fo_doc_line_to_default         (FoDoc        *fo_doc,
						     gdouble        x,
						     gdouble        y);
static void          fo_doc_move_to_default         (FoDoc        *fo_doc,
						     gdouble        x,
						     gdouble        y);
static void          fo_doc_line_stroked_default    (FoDoc        *fo_doc,
						     gdouble        x0,
						     gdouble        y0,
						     gdouble        x1,
						     gdouble        y1);
static void          fo_doc_rect_stroked_default    (FoDoc        *fo_doc,
						     gdouble        x,
						     gdouble        y,
						     gdouble        width,
						     gdouble        height);
static void          fo_doc_rect_filled_default     (FoDoc        *fo_doc,
						     gdouble        x,
						     gdouble        y,
						     gdouble        width,
						     gdouble        height);
static void          fo_doc_fill_default            (FoDoc        *fo_doc);
static void          fo_doc_stroke_default          (FoDoc        *fo_doc);
static void          fo_doc_place_image_default     (FoDoc        *fo_doc,
						     FoImage      *fo_image,
						     gdouble        x,
						     gdouble        y,
						     gdouble        xscale,
						     gdouble        yscale);
static void          fo_doc_render_layout_lines_default (FoDoc   *fo_doc,
							 FoArea  *area_layout,
							 gdouble   x,
							 gdouble   y);
static void 	     fo_doc_render_layout_default       (FoDoc   *fo_doc,
							 FoArea  *area_layout,
							 gdouble   x,
							 gdouble   y);

static gpointer parent_class;

/**
 * fo_doc_error_quark:
 * 
 * Get the error quark for #FoDoc.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: Quark associated with #FoDoc errors.
 **/
GQuark
fo_doc_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoDoc error");
  return quark;
}


/**
 * fo_doc_get_type:
 * 
 * Register the #FoDoc object type.
 * 
 * Return value: #GType value of the #FoDoc object type.
 **/
GType
fo_doc_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoDocClass),
        (GBaseInitFunc) fo_doc_base_init,
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_doc_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoDoc),
        0,              /* n_preallocs */
        NULL,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_LIBFO_MODULE,
                                            "FoDoc",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }
  
  return object_type;
}

/**
 * fo_doc_base_init:
 * @klass: #FoDocClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoDocClass.
 **/
void
fo_doc_base_init (FoDocClass *klass)
{
  klass->formats             = FO_FLAG_FORMAT_UNKNOWN;

  klass->open_file           = fo_doc_open_file_default;

  klass->get_new_layout = fo_doc_get_new_layout_default;

  klass->begin_page          = fo_doc_begin_page_default;
  klass->end_page            = fo_doc_end_page_default;
  klass->get_fill_color      = fo_doc_get_fill_color_default;
  klass->set_fill_color      = fo_doc_set_fill_color_default;
  klass->get_stroke_color    = fo_doc_get_stroke_color_default;
  klass->set_stroke_color    = fo_doc_set_stroke_color_default;
  klass->translate           = fo_doc_translate_default;
  klass->get_line_cap        = fo_doc_get_line_cap_default;
  klass->set_line_cap        = fo_doc_set_line_cap_default;
  klass->get_line_join       = fo_doc_get_line_join_default;
  klass->set_line_join       = fo_doc_set_line_join_default;
  klass->get_line_width      = fo_doc_get_line_width_default;
  klass->set_line_width      = fo_doc_set_line_width_default;
  klass->set_dash            = fo_doc_set_dash_default;
  klass->translate           = fo_doc_translate_default;
  klass->clip                = fo_doc_clip_default;
  klass->save                = fo_doc_save_default;
  klass->restore             = fo_doc_restore_default;
  klass->line_to             = fo_doc_line_to_default;
  klass->move_to             = fo_doc_move_to_default;
  klass->line_stroked        = fo_doc_line_stroked_default;
  klass->rect_stroked        = fo_doc_rect_stroked_default;
  klass->rect_filled         = fo_doc_rect_filled_default;
  klass->fill                = fo_doc_fill_default;
  klass->stroke              = fo_doc_stroke_default;
  klass->place_image         = fo_doc_place_image_default;
  klass->render_layout_lines = fo_doc_render_layout_lines_default;
  klass->render_layout       = fo_doc_render_layout_default;
}

/**
 * fo_doc_class_init:
 * @klass: #FoDocClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoDocClass.
 **/
void
fo_doc_class_init (FoDocClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->get_property = fo_doc_get_property;

  g_object_class_install_property
    (object_class,
     PROP_FORMATS,
     g_param_spec_flags ("formats",
			 _("Output formats"),
			 _("Supported output file formats"),
			 FO_TYPE_FLAGS_FORMAT,
			 FO_FLAG_FORMAT_UNKNOWN,
			 G_PARAM_READABLE));
}

/**
 * fo_doc_get_property:
 * @object:  #GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   #GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for #FoLibfoContext
 **/
void
fo_doc_get_property (GObject        *object,
		     guint           param_id,
		     GValue         *value,
		     GParamSpec     *pspec)
{
  switch (param_id)
    {
    case PROP_FORMATS:
      g_value_set_flags (value,
			 fo_doc_formats_from_name (G_OBJECT_CLASS_NAME (object)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_doc_new_from_type:
 * @type: Type of the new #FoDoc.
 * 
 * Creates a new #FoDoc.
 * 
 * Return value: the newly created #FoDoc.
 **/
FoDoc *
fo_doc_new_from_type (const gchar *type)
{
  FoDoc *fo_doc = NULL;

  if (type == NULL)
    {
#if ENABLE_GP
      fo_doc = fo_doc_gp_new ();
#else
#if ENABLE_CAIRO
      fo_doc = fo_doc_cairo_new ();
#else
      g_critical ("No output type is supported by this build of libfo.");
#endif /* ENABLE_CAIRO */
#endif /* ENABLE_GP */
    }
  else if (strcmp (type, "cairo") == 0)
    {
#if ENABLE_CAIRO
      fo_doc = fo_doc_cairo_new ();
#else
      g_critical ("Output using Cairo is not supported by this build of libfo.");
#endif /* ENABLE_CAIRO */
    }
  else if (strcmp (type, "gp") == 0)
    {
#if ENABLE_GP
      fo_doc = fo_doc_gp_new ();
#else
      g_critical ("Output using GNOME Print is not supported by this build of libfo.");
#endif /* ENABLE_GP */
    }
  else
    {
      g_critical ("Unknown output type: '%s'", type);
    }

  return fo_doc;
}

/**
 * fo_doc_new:
 * 
 * Creates a new #FoDoc.
 * 
 * Return value: the newly created #FoDoc.
 **/
FoDoc *
fo_doc_new (void)
{
  return fo_doc_new_from_type (NULL);
}

void
fo_doc_open_file_default (FoDoc          *fo_doc,
			  const gchar    *filename G_GNUC_UNUSED,
			  FoLibfoContext *libfo_context G_GNUC_UNUSED,
			  GError        **error G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'open_file' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_formats_from_name:
 * @name: Registered #FoObject type name, e.g., "FoDocCairo"
 * 
 * Gets the output formats supported by @name class.
 *
 * @name should not be #NULL.
 *
 * If @name does not implement any formats, returns
 * #FO_FLAG_FORMAT_UNKNOWN.
 * 
 * Returns: #FoFlagsFormat with zero or more bits set for the
 *   supported formats.
 **/
FoFlagsFormat
fo_doc_formats_from_name (const gchar *name)
{
  g_return_val_if_fail (name != NULL, FO_FLAG_FORMAT_UNKNOWN);

  FoFlagsFormat formats = FO_FLAG_FORMAT_UNKNOWN;
  GType type = g_type_from_name (name);

  if (g_type_is_a (type, fo_doc_get_type ()))
    {
      gpointer klass = g_type_class_ref (type);
      formats =
	((FoDocClass *) klass)->formats;
      g_type_class_unref (klass);
    }

  return formats;
}

/**
 * fo_doc_open_file:
 * @fo_doc:        #FoDoc for which to open an output file.
 * @filename:      Name of output file.
 * @libfo_context: #FoLibfoContext containing extra info.
 * @error:         Information about any error that occurred.
 * 
 *
 * No reference to @libfo_context is kept.
 **/
void
fo_doc_open_file (FoDoc          *fo_doc,
		  const gchar    *filename,
		  FoLibfoContext *libfo_context,
		  GError        **error)
{
  FO_DOC_GET_CLASS (fo_doc)->open_file (fo_doc,
					filename,
					libfo_context,
					error);
}

/**
 * fo_doc_get_new_layout_default:
 * @fo_doc: #FoDoc.
 * 
 * Get a new #FoLayout for use with @fo_doc.
 *
 * Return value: New #FoLayout.
 **/
FoLayout *
fo_doc_get_new_layout_default (FoDoc  *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'get_new_layout' function."),
	 fo_object_sprintf (fo_doc));
#endif

  return NULL;
}

/**
 * fo_doc_get_new_layout:
 * @fo_doc: #FoDoc.
 * 
 * Get a new #FoLayout for use with @fo_doc.
 *
 * Return value: New #FoLayout.
 **/
FoLayout *
fo_doc_get_new_layout (FoDoc *fo_doc)
{
  return FO_DOC_GET_CLASS (fo_doc)->get_new_layout (fo_doc);
}

/**
 * fo_doc_get_pango_context:
 * @fo_doc: #FoDoc
 * 
 * Get the #PangoContext in @fo_doc.
 * 
 * Return value: #PangoContext associated with @fo_doc.
 **/
PangoContext *
fo_doc_get_pango_context (FoDoc *fo_doc)
{
  g_return_val_if_fail (fo_doc != NULL, NULL);

  return fo_doc->pango_context;
}

/**
 * fo_doc_get_language:
 * @fo_doc: #FoDoc
 * 
 * Get the language in @fo_doc.
 * 
 * Return value: Language of file parsed to make @fo_doc.
 **/
const gchar *
fo_doc_get_language (FoDoc *fo_doc)
{
  g_return_val_if_fail (fo_doc != NULL, NULL);

  return pango_language_to_string (pango_context_get_language (fo_doc->pango_context));
}

/**
 * fo_doc_set_language:
 * @fo_doc:   #FoDoc.
 * @language: Language.
 * 
 * Set the language in @fo_doc.
 **/
void
fo_doc_set_language (FoDoc          *fo_doc,
		     const gchar    *language)
{
  g_return_if_fail (fo_doc != NULL);
  g_return_if_fail (language != NULL && *language != '\0');

  pango_context_set_language (fo_doc->pango_context,
			      pango_language_from_string (language));
}

/**
 * fo_doc_get_font_desc:
 * @fo_doc: #FoDoc.
 * 
 * Get the #PangoFontDescription in @fo_doc.
 * 
 * Return value: #PangoFontDescription in @fo_doc.
 **/
FoFontDesc *
fo_doc_get_font_desc (FoDoc *fo_doc)
{
  FoFontDesc *font_desc;

  g_return_val_if_fail (fo_doc != NULL, NULL);

  font_desc = fo_font_desc_new ();

  fo_font_desc_set_font_description (font_desc,
				     pango_context_get_font_description (fo_doc->pango_context));

  return font_desc;
}

/**
 * fo_doc_get_font_description:
 * @fo_doc: #FoDoc.
 * 
 * Get the #PangoFontDescription in @fo_doc.
 * 
 * Return value: #PangoFontDescription in @fo_doc.
 **/
PangoFontDescription *
fo_doc_get_font_description (FoDoc *fo_doc)
{
  g_return_val_if_fail (fo_doc != NULL, NULL);

  return pango_context_get_font_description (fo_doc->pango_context);
}

/**
 * fo_doc_set_font_description:
 * @fo_doc: #FoDoc.
 * @font_description: #PangoFontDescription.
 * 
 * Set the language in @fo_doc.
 **/
void
fo_doc_set_font_description (FoDoc *fo_doc,
			     const PangoFontDescription *desc)
{
  g_return_if_fail (fo_doc != NULL);
  g_return_if_fail (desc != NULL);

  pango_context_set_font_description (fo_doc->pango_context,
				      desc);
}

/**
 * fo_doc_get_base_dir:
 * @fo_doc: #FoDoc.
 * 
 * Get the #FoEnumAreaDirection used as input to @fo_doc.
 * 
 * Return value: #FoEnumAreaDirection used as input to @fo_doc.
 **/
FoEnumAreaDirection
fo_doc_get_base_dir (FoDoc *fo_doc)
{
  PangoDirection pango_direction;

  g_return_val_if_fail (fo_doc != NULL,
			FO_ENUM_AREA_DIRECTION_UNKNOWN);

  pango_direction =
    pango_context_get_base_dir (fo_doc->pango_context);

  switch (pango_direction)
    {
    case PANGO_DIRECTION_LTR:
    case PANGO_DIRECTION_WEAK_LTR:
	/* FIXME: Not sure how to handle neutral */
    case PANGO_DIRECTION_NEUTRAL:
      return FO_ENUM_AREA_DIRECTION_LR;
      break;
    case PANGO_DIRECTION_RTL:
    case PANGO_DIRECTION_WEAK_RTL:
      return FO_ENUM_AREA_DIRECTION_RL;
      break;
    case PANGO_DIRECTION_TTB_RTL:
    case PANGO_DIRECTION_TTB_LTR:
      return FO_ENUM_AREA_DIRECTION_TB;
      break;
    }

  return FO_ENUM_AREA_DIRECTION_UNKNOWN;
}

/**
 * fo_doc_set_base_dir:
 * @fo_doc:   #FoDoc.
 * @base_dir: #FoEnumAreaDirection value for new base direction.
 * 
 * Set the #FoEnumAreaDirection in @fo_doc.
 **/
void
fo_doc_set_base_dir (FoDoc      *fo_doc,
		     FoEnumAreaDirection  base_dir)
{
  PangoDirection pango_direction = PANGO_DIRECTION_LTR;

  g_return_if_fail (fo_doc != NULL);
  g_return_if_fail (base_dir != FO_ENUM_AREA_DIRECTION_UNKNOWN);

  switch (base_dir)
    {
    case FO_ENUM_AREA_DIRECTION_LR:
      pango_direction = PANGO_DIRECTION_LTR;
      break;
    case FO_ENUM_AREA_DIRECTION_RL:
      pango_direction = PANGO_DIRECTION_RTL;
      break;
    case FO_ENUM_AREA_DIRECTION_TB:
      pango_direction = PANGO_DIRECTION_TTB_RTL;
      break;
    case FO_ENUM_AREA_DIRECTION_UNKNOWN:
    default:
      g_assert_not_reached ();
    }

  pango_context_set_base_dir (fo_doc->pango_context,
			      pango_direction);
}

/**
 * fo_doc_begin_page_default:
 * @fo_doc: #FoDoc.
 * @width:  Width of the new page.
 * @height: Height of the new page.
 * @error:  Indication of any error that occurred.
 * 
 * Add a new page to @fo_doc.
 *
 * This must always be paired with a matching #fo_doc_end_page call.
 **/
void
fo_doc_begin_page_default (FoDoc   *fo_doc,
			   gdouble  width G_GNUC_UNUSED,
			   gdouble  height G_GNUC_UNUSED,
			   GError **error G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'begin_page' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_begin_page:
 * @fo_doc: #FoDoc.
 * @width:  Width of the new page.
 * @height: Height of the new page.
 * @error:  Indication of any error that occurred.
 * 
 * Add a new page to @fo_doc.
 *
 * This must always be paired with a matching #fo_doc_end_page call.
 **/
void
fo_doc_begin_page (FoDoc   *fo_doc,
		   gdouble  width,
		   gdouble  height,
		   GError **error)
{
  FO_DOC_GET_CLASS (fo_doc)->begin_page (fo_doc,
					 width,
					 height,
					 error);
}

/**
 * fo_doc_end_page_default:
 * @fo_doc: #FoDoc.
 * 
 * Finish the current page of @fo_doc.
 **/
void
fo_doc_end_page_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'end_page' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_end_page:
 * @fo_doc: #FoDoc.
 * 
 * Finish the current page of @fo_doc.
 **/
void
fo_doc_end_page (FoDoc        *fo_doc)
{
  FO_DOC_GET_CLASS (fo_doc)->end_page (fo_doc);
}

/**
 * fo_doc_get_fill_color_default:
 * @fo_doc: #FoDoc.
 * 
 * Get the current fill color of @fo_doc.
 * 
 * Return value: #FoDatatype for the current fill color.
 **/
FoDatatype *
fo_doc_get_fill_color_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'get_fill_color' function."),
	 fo_object_sprintf (fo_doc));
#endif

  return NULL;
}

/**
 * fo_doc_get_fill_color:
 * @fo_doc: #FoDoc.
 * 
 * Get the current fill color of @fo_doc.
 * 
 * Return value: #FoDatatype for the current fill color.
 **/
FoDatatype *
fo_doc_get_fill_color (FoDoc        *fo_doc)
{
  return FO_DOC_GET_CLASS (fo_doc)->get_fill_color (fo_doc);
}

/**
 * fo_doc_set_fill_color_default:
 * @fo_doc: #FoDoc.
 * @color:  #FoDatatype for new fill color.
 * 
 * Set the fill color of @fo_doc to @color.
 **/
void
fo_doc_set_fill_color_default (FoDoc        *fo_doc,
			       FoDatatype   *color G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_fill_color' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_set_fill_color:
 * @fo_doc: #FoDoc.
 * @color:  #FoDatatype for new fill color.
 * 
 * Set the fill color of @fo_doc to @color.
 **/
void
fo_doc_set_fill_color (FoDoc        *fo_doc,
		       FoDatatype   *color)
{
  FO_DOC_GET_CLASS (fo_doc)->set_fill_color (fo_doc,
					     color);
}

/**
 * fo_doc_get_stroke_color_default:
 * @fo_doc: #FoDoc.
 * 
 * Get the current stroke color of @fo_doc.
 * 
 * Return value: #FoDatatype for the current stroke color.
 **/
FoDatatype *
fo_doc_get_stroke_color_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'get_stroke_color' function."),
	 fo_object_sprintf (fo_doc));
#endif

  return NULL;
}


/**
 * fo_doc_get_stroke_color:
 * @fo_doc: #FoDoc.
 * 
 * Get the current stroke color of @fo_doc.
 * 
 * Return value: #FoDatatype for the current stroke color.
 **/
FoDatatype *
fo_doc_get_stroke_color (FoDoc        *fo_doc)
{
  return FO_DOC_GET_CLASS (fo_doc)->get_stroke_color (fo_doc);
}

/**
 * fo_doc_set_stroke_color_default:
 * @fo_doc: #FoDoc.
 * @color:  #FoDatatype for new stroke color.
 * 
 * Set the stroke color of @fo_doc to @color.
 **/
void
fo_doc_set_stroke_color_default (FoDoc        *fo_doc,
				 FoDatatype   *color G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_stroke_color' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_set_stroke_color:
 * @fo_doc: #FoDoc.
 * @color:  #FoDatatype for new stroke color.
 * 
 * Set the stroke color of @fo_doc to @color.
 **/
void
fo_doc_set_stroke_color (FoDoc        *fo_doc,
			 FoDatatype   *color)
{
  FO_DOC_GET_CLASS (fo_doc)->set_stroke_color (fo_doc,
					       color);
}

/**
 * fo_doc_get_line_cap_default:
 * @fo_doc: #FoDoc.
 * 
 * Get the current "linecap" parameter value of @fo_doc.
 * 
 * Return value: Current "linecap" parameter value.
 **/
FoDocLineCap
fo_doc_get_line_cap_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'get_line_cap' function."),
	 fo_object_sprintf (fo_doc));
#endif

  return FO_DOC_LINE_CAP_INVALID;
}

/**
 * fo_doc_get_line_cap:
 * @fo_doc: #FoDoc.
 * 
 * Get the current "linecap" parameter value of @fo_doc.
 * 
 * Return value: Current "linecap" parameter value.
 **/
FoDocLineCap
fo_doc_get_line_cap (FoDoc        *fo_doc)
{
  return FO_DOC_GET_CLASS (fo_doc)->get_line_cap (fo_doc);
}

/**
 * fo_doc_set_line_cap_default:
 * @fo_doc:   #FoDoc.
 * @line_cap: New "linecap" parameter value.
 * 
 * Set the "linecap" parameter value of @fo_doc.
 **/
void
fo_doc_set_line_cap_default (FoDoc        *fo_doc,
			     FoDocLineCap  line_cap G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_line_cap' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_set_line_cap:
 * @fo_doc:   #FoDoc.
 * @line_cap: New "linecap" parameter value.
 * 
 * Set the "linecap" parameter value of @fo_doc.
 **/
void
fo_doc_set_line_cap (FoDoc        *fo_doc,
		     FoDocLineCap  line_cap)
{
  FO_DOC_GET_CLASS (fo_doc)->set_line_cap (fo_doc,
					   line_cap);
}

/**
 * fo_doc_get_line_join_default:
 * @fo_doc: #FoDoc.
 * 
 * Get the current "linejoin" parameter value of @fo_doc.
 * 
 * Return value: Current "linejoin" parameter value.
 **/
FoDocLineJoin
fo_doc_get_line_join_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'get_line_join' function."),
	 fo_object_sprintf (fo_doc));
#endif

  return FO_DOC_LINE_JOIN_INVALID;
}

/**
 * fo_doc_get_line_join:
 * @fo_doc: #FoDoc.
 * 
 * Get the current "linejoin" parameter value of @fo_doc.
 * 
 * Return value: Current "linejoin" parameter value.
 **/
FoDocLineJoin
fo_doc_get_line_join (FoDoc        *fo_doc)
{
  return FO_DOC_GET_CLASS (fo_doc)->get_line_join (fo_doc);
}

/**
 * fo_doc_set_line_join_default:
 * @fo_doc:   #FoDoc.
 * @line_join: New "linejoin" parameter value.
 * 
 * Set the "linejoin" parameter value of @fo_doc.
 **/
void
fo_doc_set_line_join_default (FoDoc        *fo_doc,
			      FoDocLineJoin line_join G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_line_join' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_set_line_join:
 * @fo_doc:   #FoDoc.
 * @line_join: New "linejoin" parameter value.
 * 
 * Set the "linejoin" parameter value of @fo_doc.
 **/
void
fo_doc_set_line_join (FoDoc        *fo_doc,
		      FoDocLineJoin line_join)
{
  FO_DOC_GET_CLASS (fo_doc)->set_line_join (fo_doc,
					    line_join);
}

/**
 * fo_doc_get_line_width_default:
 * @fo_doc: #FoDoc.
 * 
 * Get the current line width of @fo_doc.
 * 
 * Return value: Current line width.
 **/
gdouble
fo_doc_get_line_width_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'get_line_width' function."),
	 fo_object_sprintf (fo_doc));
#endif

  return 0.0;
}

/**
 * fo_doc_get_line_width:
 * @fo_doc: #FoDoc.
 * 
 * Get the current line width of @fo_doc.
 * 
 * Return value: Current line width.
 **/
gdouble
fo_doc_get_line_width (FoDoc        *fo_doc)
{
  return FO_DOC_GET_CLASS (fo_doc)->get_line_width (fo_doc);
}

/**
 * fo_doc_set_line_width_default:
 * @fo_doc:   #FoDoc.
 * @line_width: New line width value.
 * 
 * Set the line width of @fo_doc.
 **/
void
fo_doc_set_line_width_default (FoDoc        *fo_doc,
			       gdouble        line_width G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_line_width' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_set_line_width:
 * @fo_doc:   #FoDoc.
 * @line_width: New line width value.
 * 
 * Set the line width of @fo_doc.
 **/
void
fo_doc_set_line_width (FoDoc        *fo_doc,
		       gdouble        line_width)
{
  FO_DOC_GET_CLASS (fo_doc)->set_line_width (fo_doc,
					     line_width);
}

/**
 * fo_doc_set_dash_default:
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
fo_doc_set_dash_default (FoDoc        *fo_doc,
			 gdouble        b G_GNUC_UNUSED,
			 gdouble        w G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_dash' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_set_dash:
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
fo_doc_set_dash (FoDoc        *fo_doc,
		 gdouble        b,
		 gdouble        w)
{
  FO_DOC_GET_CLASS (fo_doc)->set_dash (fo_doc,
				       b,
				       w);
}

/**
 * fo_doc_translate_default:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new origin of the coordinate system.
 * @y:      Y-coordinate of the new origin of the coordinate system.
 * 
 * Translate the origin of the coordinate system of @fo_doc.
 *
 * @x and @y are measured in the old coordinate system.
 **/
void
fo_doc_translate_default (FoDoc        *fo_doc,
			  gdouble        x G_GNUC_UNUSED,
			  gdouble        y G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'translate' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_translate:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new origin of the coordinate system.
 * @y:      Y-coordinate of the new origin of the coordinate system.
 * 
 * Translate the origin of the coordinate system of @fo_doc.
 *
 * @x and @y are measured in the old coordinate system.
 **/
void
fo_doc_translate (FoDoc        *fo_doc,
		  gdouble        x,
		  gdouble        y)
{
  FO_DOC_GET_CLASS (fo_doc)->translate (fo_doc,
					x,
					y);
}

/**
 * fo_doc_clip_default:
 * @fo_doc: #FoDoc.
 * 
 * Use the current path of @fo_doc as its clipping path.
 **/
void
fo_doc_clip_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'clip' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_clip:
 * @fo_doc: #FoDoc.
 * 
 * Use the current path of @fo_doc as its clipping path.
 **/
void
fo_doc_clip (FoDoc        *fo_doc)
{
  FO_DOC_GET_CLASS (fo_doc)->clip (fo_doc);
}

/**
 * fo_doc_save_default:
 * @fo_doc: #FoDoc.
 * 
 * Save the current graphics state of @fo_doc.
 **/
void
fo_doc_save_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'save' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_save:
 * @fo_doc: #FoDoc.
 * 
 * Save the current graphics state of @fo_doc.
 **/
void
fo_doc_save (FoDoc        *fo_doc)
{
  FO_DOC_GET_CLASS (fo_doc)->save (fo_doc);
}

/**
 * fo_doc_restore_default:
 * @fo_doc: #FoDoc.
 * 
 * Restore the most recently saved graphics state of @fo_doc.
 **/
void
fo_doc_restore_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'restore' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_restore:
 * @fo_doc: #FoDoc.
 * 
 * Restore the most recently saved graphics state of @fo_doc.
 **/
void
fo_doc_restore (FoDoc        *fo_doc)
{
  FO_DOC_GET_CLASS (fo_doc)->restore (fo_doc);
}

/**
 * fo_doc_line_to_default:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new current point.
 * @y:      Y-coordinate of the new current point.
 * 
 * Draw a line from the current point to another point.
 **/
void
fo_doc_line_to_default (FoDoc        *fo_doc,
			gdouble        x G_GNUC_UNUSED,
			gdouble        y G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'line_to' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_line_to:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new current point.
 * @y:      Y-coordinate of the new current point.
 * 
 * Draw a line from the current point to another point.
 **/
void
fo_doc_line_to (FoDoc        *fo_doc,
		gdouble        x,
		gdouble        y)
{
  FO_DOC_GET_CLASS (fo_doc)->line_to (fo_doc,
				      x,
				      y);
}

/**
 * fo_doc_move_to_default:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new current point.
 * @y:      Y-coordinate of the new current point.
 * 
 * Set the current point of @fo_doc to (@x, @y).
 **/
void
fo_doc_move_to_default (FoDoc        *fo_doc,
			gdouble        x G_GNUC_UNUSED,
			gdouble        y G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'move_to' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_move_to:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the new current point.
 * @y:      Y-coordinate of the new current point.
 * 
 * Set the current point of @fo_doc to (@x, @y).
 **/
void
fo_doc_move_to (FoDoc        *fo_doc,
		gdouble        x,
		gdouble        y)
{
  FO_DOC_GET_CLASS (fo_doc)->move_to (fo_doc,
				      x,
				      y);
}

/**
 * fo_doc_line_stroked_default:
 * @fo_doc: #FoDoc.
 * @x0: X-coordinate of the start of the line.
 * @y0: Y-coordinate of the start of the line.
 * @x1: X-coordinate of the end of the line.
 * @y1: Y-coordinate of the end of the line.
 * 
 * Draw a line from (@x0,@y0) to (@x1,@y1).
 **/
void
fo_doc_line_stroked_default (FoDoc *fo_doc,
			     gdouble x0 G_GNUC_UNUSED,
			     gdouble y0 G_GNUC_UNUSED,
			     gdouble x1 G_GNUC_UNUSED,
			     gdouble y1 G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'rect_stroked' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_line_stroked:
 * @fo_doc: #FoDoc.
 * @x0: X-coordinate of the start of the line.
 * @y0: Y-coordinate of the start of the line.
 * @x1: X-coordinate of the end of the line.
 * @y1: Y-coordinate of the end of the line.
 * 
 * Draw a line from (@x0,@y0) to (@x1,@y1).
 **/
void
fo_doc_line_stroked (FoDoc *fo_doc,
		     gdouble x0,
		     gdouble y0,
		     gdouble x1,
		     gdouble y1)
{
  FO_DOC_GET_CLASS (fo_doc)->line_stroked (fo_doc,
					   x0,
					   y0,
					   x1,
					   y1);
}


/**
 * fo_doc_rect_stroked_default:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the lower-left corner of the rectangle.
 * @y:      Y-coordinate of the lower-left corner of the rectangle.
 * @width:  Width of the rectangle.
 * @height: Height of the rectangle.
 * 
 * Draw an outline rectangle.
 **/
void
fo_doc_rect_stroked_default (FoDoc        *fo_doc,
			     gdouble        x G_GNUC_UNUSED,
			     gdouble        y G_GNUC_UNUSED,
			     gdouble        width G_GNUC_UNUSED,
			     gdouble        height G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'rect_stroked' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_rect_stroked:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the lower-left corner of the rectangle.
 * @y:      Y-coordinate of the lower-left corner of the rectangle.
 * @width:  Width of the rectangle.
 * @height: Height of the rectangle.
 * 
 * Draw an outline rectangle.
 **/
void
fo_doc_rect_stroked (FoDoc        *fo_doc,
		     gdouble        x,
		     gdouble        y,
		     gdouble        width,
		     gdouble        height)
{
  FO_DOC_GET_CLASS (fo_doc)->rect_stroked (fo_doc,
					   x,
					   y,
					   width,
					   height);
}

/**
 * fo_doc_rect_filled_default:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the lower-left corner of the rectangle.
 * @y:      Y-coordinate of the lower-left corner of the rectangle.
 * @width:  Width of the rectangle.
 * @height: Height of the rectangle.
 * 
 * Draw a filled rectangle.
 **/
void
fo_doc_rect_filled_default (FoDoc        *fo_doc,
			     gdouble        x G_GNUC_UNUSED,
			     gdouble        y G_GNUC_UNUSED,
			     gdouble        width G_GNUC_UNUSED,
			     gdouble        height G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'rect_filled' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_rect_filled:
 * @fo_doc: #FoDoc.
 * @x:      X-coordinate of the lower-left corner of the rectangle.
 * @y:      Y-coordinate of the lower-left corner of the rectangle.
 * @width:  Width of the rectangle.
 * @height: Height of the rectangle.
 * 
 * Draw a filled rectangle.
 **/
void
fo_doc_rect_filled (FoDoc        *fo_doc,
		    gdouble        x,
		    gdouble        y,
		    gdouble        width,
		    gdouble        height)
{
  FO_DOC_GET_CLASS (fo_doc)->rect_filled (fo_doc,
					  x,
					  y,
					  width,
					  height);
}

/**
 * fo_doc_fill_default:
 * @fo_doc: #FoDoc.
 * 
 * Fill the interior of the path of @fo_doc with the current fill color.
 **/
void
fo_doc_fill_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'fill' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_fill:
 * @fo_doc: #FoDoc.
 * 
 * Fill the interior of the path of @fo_doc with the current fill color.
 **/
void
fo_doc_fill (FoDoc        *fo_doc)
{
  FO_DOC_GET_CLASS (fo_doc)->fill (fo_doc);
}

/**
 * fo_doc_stroke_default:
 * @fo_doc: #FoDoc.
 * 
 * Stroke the path of @fo_doc and clear the path.
 **/
void
fo_doc_stroke_default (FoDoc        *fo_doc)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'stroke' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_stroke:
 * @fo_doc: #FoDoc.
 * 
 * Stroke the path of @fo_doc and clear the path.
 **/
void
fo_doc_stroke (FoDoc        *fo_doc)
{
  FO_DOC_GET_CLASS (fo_doc)->stroke (fo_doc);
}

/**
 * fo_doc_place_image_default:
 * @fo_doc:   #FoDoc in which to place image
 * @fo_image: #FoImage
 * @x:        X-offset
 * @y:        Y-offset
 * @xscale:   Scale to apply to X dimension of @image
 * @yscale:   Scale to apply to Y dimension of @image
 * 
 * Places @fo_image in @fo_doc at position given by @x and @y with image
 * scaled by @xscale and @yscale.
 **/
void
fo_doc_place_image_default (FoDoc   *fo_doc,
			    FoImage *image G_GNUC_UNUSED,
			    gdouble   x G_GNUC_UNUSED,
			    gdouble   y G_GNUC_UNUSED,
			    gdouble   xscale G_GNUC_UNUSED,
			    gdouble   yscale G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'place_image' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_place_image:
 * @fo_doc:   #FoDoc in which to place image
 * @fo_image: #FoImage
 * @x:        X-offset
 * @y:        Y-offset
 * @xscale:   Scale to apply to X dimension of @image
 * @yscale:   Scale to apply to Y dimension of @image
 * 
 * Places @fo_image in @fo_doc at position given by @x and @y with image
 * scaled by @xscale and @yscale.
 **/
void
fo_doc_place_image (FoDoc   *fo_doc,
		    FoImage *fo_image,
		    gdouble   x,
		    gdouble   y,
		    gdouble   xscale,
		    gdouble   yscale)
{
  FO_DOC_GET_CLASS (fo_doc)->place_image (fo_doc,
					  fo_image,
					  x,
					  y,
					  xscale,
					  yscale);
}

/**
 * fo_doc_render_layout_lines_default:
 * @fo_doc:      #FoDoc for which to render lines.
 * @area_layout: #FoArea containing lines.
 * @x:           X-offset
 * @y:           Y-offset
 * 
 * Renders the lines in @area_layout at position (@x, @y) on current
 * page of @fo_doc.
 **/
void
fo_doc_render_layout_lines_default (FoDoc   *fo_doc,
				    FoArea  *area_layout G_GNUC_UNUSED,
				    gdouble   x G_GNUC_UNUSED,
				    gdouble   y G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'render_layout_lines' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_render_layout_lines:
 * @fo_doc:      #FoDoc for which to render lines.
 * @area_layout: #FoArea containing lines.
 * @x:           X-offset
 * @y:           Y-offset
 * 
 * Renders the lines in @area_layout at position (@x, @y) on current
 * page of @fo_doc.
 **/
void
fo_doc_render_layout_lines (FoDoc   *fo_doc,
			    FoArea  *area_layout,
			    gdouble   x,
			    gdouble   y)
{
  FO_DOC_GET_CLASS (fo_doc)->render_layout_lines (fo_doc,
						  area_layout,
						  x,
						  y);
}

/**
 * fo_doc_render_layout_default:
 * @fo_doc:      #FoDoc to which to render.
 * @area_layout: #FoArea containing lines.
 * @x:           X-offset
 * @y:           Y-offset
 * 
 * Renders @area_layout at position (@x, @y) on current page of
 * @fo_doc.
 **/
void
fo_doc_render_layout_default (FoDoc   *fo_doc,
			      FoArea  *area_layout G_GNUC_UNUSED,
			      gdouble   x G_GNUC_UNUSED,
			      gdouble   y G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'render_layout' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_doc_render_layout:
 * @fo_doc:      #FoDoc to which to render.
 * @area_layout: #FoArea containing lines.
 * @x:           X-offset
 * @y:           Y-offset
 * 
 * Renders @area_layout at position (@x, @y) on current page of
 * @fo_doc.
 **/
void
fo_doc_render_layout (FoDoc   *fo_doc,
		      FoArea  *area_layout,
		      gdouble   x,
		      gdouble   y)
{
  FO_DOC_GET_CLASS (fo_doc)->render_layout (fo_doc,
					    area_layout,
					    x,
					    y);
}
