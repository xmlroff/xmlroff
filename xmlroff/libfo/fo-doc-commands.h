/* Fo
 * fo-doc-commands.h: Commands for an FoDoc
 *
 * Copyright (C) 2001-2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_DOC_COMMANDS_H__
#define __FO_DOC_COMMANDS_H__

#include <libfo/fo-doc.h>
#include <libfo/datatype/fo-datatype.h>
#include <libfo/fo-utils.h>
#include <libfo/fo-libfo-context.h>
#include <libfo/fo-font-desc.h>
#include <libfo/util/fo-image.h>
#include <libfo/area/fo-area.h>

G_BEGIN_DECLS

void          fo_doc_begin_page     (FoDoc        *fo_doc,
				     gdouble       width,
				     gdouble       height,
				     GError       **error);
void          fo_doc_end_page       (FoDoc        *fo_doc);
FoDatatype *  fo_doc_get_fill_color (FoDoc        *fo_doc);
void          fo_doc_set_fill_color (FoDoc        *fo_doc,
				     FoDatatype   *color);
FoDatatype *  fo_doc_get_stroke_color (FoDoc        *fo_doc);
void          fo_doc_set_stroke_color (FoDoc        *fo_doc,
				       FoDatatype   *color);
FoDocLineCap  fo_doc_get_line_cap   (FoDoc        *fo_doc);
void          fo_doc_set_line_cap   (FoDoc        *fo_doc,
				     FoDocLineCap  line_cap);
FoDocLineJoin fo_doc_get_line_join  (FoDoc        *fo_doc);
void          fo_doc_set_line_join  (FoDoc        *fo_doc,
				     FoDocLineJoin line_join);
gdouble       fo_doc_get_line_width (FoDoc        *fo_doc);
void          fo_doc_set_line_width (FoDoc        *fo_doc,
				     gdouble       line_width);
void          fo_doc_set_dash       (FoDoc        *fo_doc,
				     gdouble       b,
				     gdouble       w);
void          fo_doc_translate      (FoDoc        *fo_doc,
				     gdouble       x,
				     gdouble       y);
void          fo_doc_clip           (FoDoc        *fo_doc);
void          fo_doc_save           (FoDoc        *fo_doc);
void          fo_doc_restore        (FoDoc        *fo_doc);
void          fo_doc_line_to        (FoDoc        *fo_doc,
				     gdouble       x,
				     gdouble       y);
void          fo_doc_move_to        (FoDoc        *fo_doc,
				     gdouble       x,
				     gdouble       y);
void          fo_doc_line_stroked   (FoDoc        *fo_doc,
				     gdouble       x0,
				     gdouble       y0,
				     gdouble       x1,
				     gdouble       y1);
void          fo_doc_rect_stroked   (FoDoc        *fo_doc,
				     gdouble       x,
				     gdouble       y,
				     gdouble       width,
				     gdouble       height);
void          fo_doc_rect_filled    (FoDoc        *fo_doc,
				     gdouble       x,
				     gdouble       y,
				     gdouble       width,
				     gdouble       height);
void          fo_doc_fill           (FoDoc        *fo_doc);
void          fo_doc_stroke         (FoDoc        *fo_doc);

void          fo_doc_place_image     (FoDoc        *fo_doc,
				      FoImage      *fo_image,
				      gdouble       x,
				      gdouble       y,
				      gdouble       xscale,
				      gdouble       yscale);

FoFontDesc *  fo_doc_get_font_desc  (FoDoc *fo_doc);

void 	      fo_doc_render_layout_lines (FoDoc   *fo_doc,
					  FoArea  *area_layout,
					  gdouble  x,
					  gdouble  y);
void 	      fo_doc_render_layout       (FoDoc   *fo_doc,
					  FoArea  *area_layout,
					  gdouble  x,
					  gdouble  y);

G_END_DECLS

#endif /* !__FO_DOC_COMMANDS_H__ */
