/* Fo
 * fo-external-graphic-area.c: Generate area for external-graphic formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#include "fo/fo-block-fo.h"
#include "area/fo-area-graphic.h"
#include "fo/fo-external-graphic-private.h"
#include "property/fo-property-text-property.h"
#include "fo-doc-commands.h"
#include "libfo-pango.h"

/* UTF-8 encoding of U+FFFC, OBJECT REPLACEMENT CHARACTER
 *
 * ORC = U+FFFC
 *     = 1111 1111 1111 1100 (UTF-16)
 *     = zzzz yyyy yyxx xxxx
 *     = 1110zzzz 10yyyyyy 10xxxxxx (UTF-8)
 *     = 11101111 10111111 10111100 (UTF-8)
 *     = 11 101 111  10 111 111  10 111 100 (UTF-8)
 *     = \357\277\274 (UTF-8)
 */
#define UTF8_STR_OBJECT_REPLACEMENT_CHAR "\357\277\274"  /* U+FFFC */

static void
fo_external_graphic_callback_test (gpointer data1,
				   gpointer data2 G_GNUC_UNUSED)
{
  FoExternalGraphic *external_graphic;
  gfloat xscale;
  gfloat yscale;

  g_return_if_fail (FO_IS_EXTERNAL_GRAPHIC (data1));

  external_graphic = FO_EXTERNAL_GRAPHIC (data1);

#if 0
  g_message ("Callback called back.");
  g_message ("callback_test:: object: %s",
	     fo_object_debug_sprintf (data1));
#endif

  xscale = external_graphic->area_width / fo_length_get_value (fo_image_get_width (external_graphic->fo_image));
  yscale = external_graphic->area_height / fo_length_get_value (fo_image_get_height (external_graphic->fo_image));

  fo_doc_place_image (external_graphic->fo_doc,
		      external_graphic->fo_image,
		      0.0,
		      0.0,
		      xscale,
		      yscale);
}

/**
 * fo_external_graphic_get_text_attr_list:
 * @fo_inline_fo: The #FoInlineFo object.
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO.
 * @attr_glist:   The list of #PangoAttribute for the inline FO.
 * @debug_level:  Debug level.
 * 
 * Gets the text of the inline FO and its associated list of #PangoAttribute.
 *
 * The 'text' of fo:external-graphic is U+FFFC, OBJECT REPLACEMENT
 * CHARACTER.  This is just a placeholder so there's something with
 * which to associate a #PangoAttribute.
 **/
void
fo_external_graphic_get_text_attr_list (FoFo    *fo_inline_fo,
					FoDoc   *fo_doc,
					GString *text,
					GList  **attr_glist,
					guint    debug_level G_GNUC_UNUSED)
{
  FoNode *fo_child_node;
  FoExternalGraphic *fo_external_graphic;
  PangoAttribute *pango_attr;
  PangoRectangle pango_rectangle;
  GClosure *closure;
  GList *my_attr_glist = NULL;
  gint start_index, end_index;

  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_EXTERNAL_GRAPHIC (fo_inline_fo));

  fo_external_graphic = FO_EXTERNAL_GRAPHIC (fo_inline_fo);

  fo_external_graphic->fo_doc = fo_doc;

  start_index = text->len;

  fo_child_node = fo_node_first_child (FO_NODE (fo_inline_fo));

  g_string_append (text, UTF8_STR_OBJECT_REPLACEMENT_CHAR);

  end_index = text->len;

  pango_rectangle.x = 0;
  pango_rectangle.y = 0;
  pango_rectangle.width = fo_external_graphic->area_width * PANGO_SCALE;
  /*fo_length_get_value (fo_property_get_value (fo_external_graphic->content_width)) * PANGO_SCALE;*/
  pango_rectangle.height = fo_external_graphic->area_height * PANGO_SCALE;
  /*fo_length_get_value (fo_property_get_value (fo_external_graphic->content_height)) * PANGO_SCALE;*/

  pango_attr =
    pango_attr_shape_new (&pango_rectangle,
			  &pango_rectangle);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

  closure = g_cclosure_new_swap ((GCallback) fo_external_graphic_callback_test,
				 fo_inline_fo,
				 NULL);
  g_closure_set_marshal (closure,
			 g_cclosure_marshal_VOID__VOID);

  pango_attr =
    libfo_pango_attr_callback_new (closure);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

  pango_attr =
    fo_property_text_property_new_attr (fo_external_graphic->baseline_shift);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

  /*
  pango_attr =
    fo_property_text_property_new_attr (fo_external_graphic->line_height);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
  */

  if (FO_IS_COLOR (fo_property_get_value (fo_external_graphic->background_color)))
    {
      pango_attr =
	fo_property_text_property_new_attr (fo_external_graphic->background_color);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
    }

  /*
  pango_attr =
    fo_property_text_property_new_attr (fo_external_graphic->alignment_adjust);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

  pango_attr =
    fo_property_text_property_new_attr (fo_external_graphic->alignment_baseline);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

  pango_attr =
    fo_property_text_property_new_attr_from_context (fo_external_graphic->dominant_baseline,
						     fo_fo_get_context (fo_inline_fo));
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

  pango_attr =
    fo_property_text_property_new_attr (fo_external_graphic->keep_with_next_within_line);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);

  pango_attr =
    fo_property_text_property_new_attr (fo_external_graphic->keep_with_previous_within_line);
  pango_attr->start_index = start_index;
  pango_attr->end_index = end_index;
  my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
  */

  *attr_glist = g_list_concat (my_attr_glist,
			       *attr_glist);
}
