/* Fo
 * fo-block-area.c: Block formatting object area creation
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <fo-inline-fo.h>
#include <area/fo-area-area.h>
#include <area/fo-area-layout.h>
#include <fo-text.h>
#include <fo-block-area.h>
#include <fo-block-private.h>
#include "property/fo-property-common-font.h"
#include "property/fo-property-text-property.h"
#include <property/fo-property-background-color.h>
#include <property/fo-property-dominant-baseline.h>
#include <property/fo-property-baseline-shift.h>
#include "property/fo-property-font-family.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-stretch.h"
#include <property/fo-property-space-after.h>
#include <property/fo-property-space-before.h>
#include <libfo/fo-doc.h>
#include <libfo/fo-doc-commands.h>
#include <libfo/fo-layout-private.h>

#if 0
static void
fo_block_debug_dump_item (gpointer data, gpointer user_data)
{
  const PangoItem *item = (const PangoItem *) data;
  const PangoEngine *engine = (const PangoEngine *) item->analysis.shape_engine;
  PangoFontDescription *font_desc = pango_font_describe (item->analysis.font);

  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_item:: offset: %d", item->offset);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_item:: length: %d", item->length);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_item:: num_chars: %d", item->num_chars);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_item:: shape_engine: %p", item->analysis.shape_engine);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_item:: shape_engine: %s", engine->id);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_item:: lang_engine: %p", item->analysis.lang_engine);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_item:: font: %p", item->analysis.font);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_item:: font: %s", pango_font_description_to_string (font_desc));
}

static void
fo_block_debug_dump_item_glist (GList *item_glist)
{
  g_list_foreach (item_glist,
		  fo_block_debug_dump_item,
		  NULL);
}

static gint
fo_block_area_glist_find_attr_type (gpointer pango_attr, gpointer attr_klass)
{
  /*
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "find_attr_type:: attr: %p; klass: %d", pango_attr, GPOINTER_TO_INT (attr_klass));
  */
  if (((PangoAttribute *) pango_attr)->klass->type == GPOINTER_TO_INT (attr_klass))
    {
      return 0;
    }
  else
    {
      return -1;
    }
}
#endif

static void
fo_block_area_get_text_attr_list2 (FoFo    *parent_fo,
				   FoDoc   *fo_doc,
				   GString *text,
				   GList  **attr_glist,
				   guint    debug_level)
{
  FoNode *fo_child_node;
  const FoBlock *fo_block = (const FoBlock *) parent_fo;
  gint start_index, end_index;

  start_index = text->len;

  fo_child_node = fo_node_first_child (FO_NODE (parent_fo));

  while (fo_child_node)
    {
      fo_inline_fo_get_text_attr_list (FO_FO (fo_child_node),
				       fo_doc,
				       text,
				       attr_glist,
				       debug_level);
      fo_child_node = fo_node_next_sibling (fo_child_node);
    }

  end_index = text->len;

  if (start_index != end_index)
    {
      PangoAttribute *pango_attr;

      *attr_glist =
	g_list_concat (fo_property_common_font_get_pango_attrs (fo_block->font_family,
								fo_block->font_size,
								fo_block->font_stretch,
								fo_block->font_style,
								fo_block->font_variant,
								fo_block->font_weight,
								start_index,
								end_index),
		       *attr_glist);
      /*
      pango_attr =
	fo_property_text_property_new_attr (fo_block->line_height);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      *attr_glist = g_list_prepend (*attr_glist, pango_attr);
      */
      pango_attr =
	fo_property_text_property_new_attr (fo_block->color);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      *attr_glist = g_list_prepend (*attr_glist, pango_attr);

      if (FO_IS_COLOR (fo_property_get_value (fo_block->background_color)))
	{
	  pango_attr =
	    fo_property_text_property_new_attr (fo_block->background_color);
	  pango_attr->start_index = start_index;
	  pango_attr->end_index = end_index;
	  *attr_glist = g_list_prepend (*attr_glist, pango_attr);
	}
      /*
      pango_attr =
	fo_property_text_property_new_attr (fo_block->keep_together_within_line);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      *attr_glist = g_list_prepend (*attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_block->keep_with_next_within_line);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      *attr_glist = g_list_prepend (*attr_glist, pango_attr);

      pango_attr =
	fo_property_text_property_new_attr (fo_block->keep_with_previous_within_line);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      *attr_glist = g_list_prepend (*attr_glist, pango_attr);
      */
    }

#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "block_area_new2:: text: %s",
	 text->str);
  if (*attr_glist)
    {
      PangoAttrList *attr_list = pango_attr_list_new ();
      g_list_foreach (*attr_glist,
		      fo_block_area_pango_attr_list_add,
		      attr_list);
      fo_block_debug_dump_attr_list (attr_list);
    }
#endif
}

void
fo_block_area_new (FoFo *block,
		   FoDoc *fo_doc,
		   FoArea *parent_area,
		   FoArea **new_area,
		   guint debug_level)
{
  g_return_if_fail (block != NULL);
  g_return_if_fail (FO_IS_BLOCK (block));
  g_return_if_fail (FO_IS_DOC (fo_doc));

  gfloat parent_child_available_ipdim =
    fo_area_get_child_available_ipdim (parent_area);
  gfloat x = fo_area_get_next_x (parent_area);
  gfloat y = fo_area_get_next_y (parent_area);

  gfloat border_start_width =
    fo_length_get_value (fo_property_get_value (fo_block_get_border_start_width (block)));
  gfloat border_end_width =
    fo_length_get_value (fo_property_get_value (fo_block_get_border_end_width (block)));
  gfloat border_before_width =
    fo_length_get_value (fo_property_get_value (fo_block_get_border_before_width (block)));
  gfloat border_after_width =
    fo_length_get_value (fo_property_get_value (fo_block_get_border_after_width (block)));

  gfloat padding_start =
    fo_length_get_value (fo_property_get_value (fo_block_get_padding_start (block)));
  gfloat padding_end =
    fo_length_get_value (fo_property_get_value (fo_block_get_padding_end (block)));
  gfloat padding_before =
    fo_length_get_value (fo_property_get_value (fo_block_get_padding_before (block)));
  gfloat padding_after =
    fo_length_get_value (fo_property_get_value (fo_block_get_padding_after (block)));

  FoDatatype *start_indent_datatype =
    fo_property_get_value (fo_block_get_start_indent (block));
  gfloat start_indent;
  if (FO_IS_LENGTH (start_indent_datatype))
    {
      start_indent = fo_length_get_value (start_indent_datatype);
    }
  else
    {
      start_indent =
	fo_percentage_get_value (start_indent_datatype) * 0.01 *
	fo_area_area_get_width (parent_area);
#if defined(LIBFO_DEBUG) && 0
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "get_text_attr_list:: start-indent: %f, parent width: %f",
		 fo_percentage_get_value (start_indent_datatype),
		 fo_area_area_get_width (parent_area));
#endif
    }
  FoDatatype *end_indent_datatype =
    fo_property_get_value (fo_block_get_end_indent (block));
  gfloat end_indent;
  if (FO_IS_LENGTH (end_indent_datatype))
    {
      end_indent = fo_length_get_value (end_indent_datatype);
    }
  else
    {
      end_indent =
	fo_percentage_get_value (end_indent_datatype) * 0.01 *
	fo_area_area_get_width (parent_area);
#if defined(LIBFO_DEBUG) && 0
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "get_text_attr_list:: end-indent: %f, parent width: %f",
		 fo_percentage_get_value (end_indent_datatype),
		 fo_area_area_get_width (parent_area));
#endif
    }

  gfloat layout_width =
    parent_child_available_ipdim -
    (border_start_width + border_end_width + padding_start + padding_end +
     start_indent + end_indent);

  FoFontDesc *font_desc =
    fo_font_desc_copy (fo_doc_get_font_desc (fo_doc));

  gchar *font_family =
    fo_string_get_value (fo_property_get_value (fo_block_get_font_family (block)));
  fo_font_desc_set_family (font_desc, font_family);
  g_free (font_family);

  fo_font_desc_set_size (font_desc,
    fo_length_get_value (fo_property_get_value (fo_block_get_font_size (block))));
  fo_font_desc_set_weight (font_desc,
    fo_integer_get_value (fo_property_get_value (fo_block_get_font_weight (block))));
  fo_font_desc_set_style (font_desc,
			  fo_enum_get_value (fo_property_get_value (fo_block_get_font_style (block))));
  fo_font_desc_set_stretch (font_desc,
			    fo_enum_get_value (fo_property_get_value (fo_block_get_font_stretch (block))));
  fo_font_desc_set_variant (font_desc,
			    fo_enum_get_value (fo_property_get_value (fo_block_get_font_variant (block))));

  FoLayout *fo_layout = fo_doc_get_new_layout (fo_doc);
  fo_layout_set_width (fo_layout,
		       layout_width);

  fo_layout_set_line_stacking_strategy (fo_layout,
					fo_enum_get_value (fo_property_get_value (fo_block_get_line_stacking_strategy (block))));
  fo_layout_set_font_desc (fo_layout,
			   font_desc);

  gfloat line_height =
    fo_length_get_value (fo_property_get_value (fo_block_get_line_height (block)));
  fo_layout_set_line_height (fo_layout,
			     line_height);

  /* FIXME: should be FO-specific dir enum */
  PangoDirection base_dir = fo_doc_get_base_dir (fo_doc);
  fo_layout_set_alignment (fo_layout,
			   base_dir);

  gfloat text_indent =
    fo_length_get_value (fo_property_get_value (fo_block_get_text_indent (block)));
  fo_layout_set_indent (fo_layout,
			text_indent);
  /*
    FIXME: Pango does not justify.
  fo_layout_set_justify (pango_layout, TRUE);
  */
  GString *text = g_string_new (NULL);
  GList *attr_glist = NULL;
  fo_block_area_get_text_attr_list2 (FO_FO (block),
				     fo_doc,
				     text,
				     &attr_glist,
				     debug_level);
  fo_layout_set_text (fo_layout,
		      text);
  fo_layout_set_attributes (fo_layout,
			    attr_glist);

  if (debug_level & FO_DEBUG_PANGO)
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "get_text_attr_list:: block text: '%s'", (gchar *) text->str);
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "get_text_attr_list:: attr_glist: %p", attr_glist);
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "get_text_attr_list:: attr_glist length: %d", g_list_length (attr_glist));

      fo_object_debug_dump (fo_layout, 0);
    }

  *new_area = fo_area_layout_new_with_layout (fo_layout);

  FoRectangle logical;
  fo_layout_get_extents (fo_layout,
			 &logical);

  fo_area_area_set_height (*new_area,
			   logical.height / PANGO_SCALE +
			   border_before_width + padding_before +
			   border_after_width + padding_after);

  fo_area_area_set_width (*new_area,
			  MAX (parent_child_available_ipdim -
			       start_indent -
			       end_indent,
			       0));
  fo_area_area_set_x (*new_area, x + start_indent);
  fo_area_area_set_y (*new_area, y);
  fo_area_area_set_border_after (*new_area, border_after_width);
  fo_area_area_set_border_before (*new_area, border_before_width);
  fo_area_area_set_border_end (*new_area, border_end_width);
  fo_area_area_set_border_start (*new_area, border_start_width);
  fo_area_area_set_padding_before (*new_area, padding_before);
  fo_area_area_set_padding_end (*new_area, padding_end);
  fo_area_area_set_padding_after (*new_area, padding_after);
  fo_area_area_set_padding_start (*new_area, padding_start);
  fo_area_area_set_start_indent (*new_area, start_indent);
  fo_area_area_set_end_indent (*new_area, end_indent);
  gfloat space_before =
    fo_length_get_value (fo_property_get_value (fo_block_get_space_before (block)));
  fo_area_area_set_space_before (*new_area, space_before);
  gfloat space_after =
    fo_length_get_value (fo_property_get_value (fo_block_get_space_after (block)));
  fo_area_area_set_space_after (*new_area, space_after);
  fo_area_set_generated_by (*new_area, FO_FO (block));
  FO_FO (block)->areas = g_list_append (FO_FO (block)->areas, *new_area);

  g_object_unref (font_desc);
}

void
fo_block_area_new3 (FoFo *block,
		    FoDoc *fo_doc,
		    FoArea *parent_area,
		    FoArea **new_area,
		    guint debug_level)
{
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "block_area_new3:: *** block parent before adding block:");
  fo_object_debug_dump (parent_area, 0);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "block_area_new3:: *** end block parent");
#endif

  fo_block_area_new (block,
		     fo_doc,
		     parent_area,
		     new_area,
		     debug_level);
  fo_area_add_child (parent_area, *new_area);
  *new_area = fo_area_size_request (*new_area);
  fo_area_resolve_text_align (*new_area);

#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "block_area_new3:: *new_area: %s; generated by: %s; parent: %s; generated by: %s",
	 fo_object_debug_sprintf (*new_area),
	 fo_object_debug_sprintf ((*new_area)->generated_by),
	 fo_object_debug_sprintf (fo_area_parent (*new_area)),
	 fo_object_debug_sprintf (fo_area_parent (*new_area->generated_by)));
#endif

#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "block_area_new3:: *** block parent after adding block:");
  fo_object_debug_dump (parent_area, 0);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "block_area_new3:: *** end block parent");
#endif
}

void
fo_block_area_new2 (FoFo         *fo_node,
		    FoFoAreaNew2Context *context,
		    GError **error)
{
  g_return_if_fail (FO_IS_FO (fo_node));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  fo_block_area_new (fo_node,
		     context->fo_doc,
		     context->parent_area,
		     context->new_area,
		     context->debug_level);
#if defined(LIBFO_DEBUG) && 0
  fo_object_debug_dump (*(context->new_area), 0);
#endif
  fo_area_add_child (context->parent_area, *(context->new_area));
  *(context->new_area) = fo_area_size_request (*(context->new_area));
  fo_area_resolve_text_align (*(context->new_area));
}
