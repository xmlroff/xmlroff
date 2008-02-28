/* Fo
 * fo-doc-private.h: Wrapper for libfo output document
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_DOC_PRIVATE_H__
#define __FO_DOC_PRIVATE_H__

#include <pango/pango-context.h>
#include <datatype/fo-datatype.h>
#include <area/fo-area.h>
#include <libfo/fo-doc.h>
#include "fo-object.h"
#include "libfo/fo-font-desc.h"
#include "util/fo-image.h"

G_BEGIN_DECLS

struct _FoDoc
{
  FoObject parent_instance;

  FoDatatype   *fill_color;
  FoDatatype   *stroke_color;
  FoDocLineCap  line_cap;
  FoDocLineJoin line_join;
  gdouble        line_width;

  PangoContext  *pango_context;
};

struct _FoDocClass
{
  FoObjectClass parent_class;

  void           (* open_file)           (FoDoc          *fo_doc,
					  const gchar    *filename,
					  FoLibfoContext *libfo_context,
					  GError        **error);

  FoLayout *     (* get_new_layout)      (FoDoc        *fo_doc);

  void           (* begin_page)          (FoDoc        *fo_doc,
					  gdouble       width,
					  gdouble       height,
					  GError      **error);
  void           (* end_page)            (FoDoc        *fo_doc);
  FoDatatype*    (* get_fill_color)      (FoDoc        *fo_doc);
  void           (* set_fill_color)      (FoDoc        *fo_doc,
					  FoDatatype   *color);
  FoDatatype*    (* get_stroke_color)    (FoDoc        *fo_doc);
  void           (* set_stroke_color)    (FoDoc        *fo_doc,
					  FoDatatype   *color);
  FoDocLineCap   (* get_line_cap)        (FoDoc        *fo_doc);
  void           (* set_line_cap)        (FoDoc        *fo_doc,
					  FoDocLineCap  line_cap);
  FoDocLineJoin  (* get_line_join)       (FoDoc        *fo_doc);
  void           (* set_line_join)       (FoDoc        *fo_doc,
					  FoDocLineJoin line_join);
  gdouble        (* get_line_width)      (FoDoc        *fo_doc);
  void           (* set_line_width)      (FoDoc        *fo_doc,
					  gdouble       line_width);
  void           (* set_dash)            (FoDoc        *fo_doc,
					  gdouble       b,
					  gdouble       w);
  void           (* translate)           (FoDoc        *fo_doc,
					  gdouble       x,
					  gdouble       y);
  void           (* clip)                (FoDoc        *fo_doc);
  void           (* save)                (FoDoc        *fo_doc);
  void           (* restore)             (FoDoc        *fo_doc);
  void           (* line_to)             (FoDoc        *fo_doc,
					  gdouble       x,
					  gdouble       y);
  void           (* move_to)             (FoDoc        *fo_doc,
					  gdouble       x,
					  gdouble       y);
  void           (* line_stroked)        (FoDoc        *fo_doc,
					  gdouble       x0,
					  gdouble       y0,
					  gdouble       x1,
					  gdouble       y1);
  void           (* rect_stroked)        (FoDoc        *fo_doc,
					  gdouble       x,
					  gdouble       y,
					  gdouble       width,
					  gdouble       height);
  void           (* rect_filled)         (FoDoc        *fo_doc,
					  gdouble       x,
					  gdouble       y,
					  gdouble       width,
					  gdouble       height);
  void           (* fill)                (FoDoc        *fo_doc);
  void           (* stroke)              (FoDoc        *fo_doc);
  void           (* place_image)         (FoDoc        *fo_doc,
					  FoImage      *fo_image,
					  gdouble       x,
					  gdouble       y,
					  gdouble       xscale,
					  gdouble       yscale);
  gint           (* open_image_file)     (FoDoc        *fo_doc,
					  const char   *imagetype,
					  const char   *filename,
					  const char   *stringparam,
					  gint          intparam);
  void           (* close_image)         (FoDoc        *fo_doc,
					  gint          image);
  void 	         (* render_layout_lines) (FoDoc        *fo_doc,
					  FoArea       *area_layout,
					  gdouble       x,
					  gdouble       y);
  void 	         (* render_layout)       (FoDoc        *fo_doc,
					  FoArea       *area_layout,
					  gdouble       x,
					  gdouble       y);
};

PangoContext * fo_doc_get_pango_context (FoDoc *fo_doc);

G_END_DECLS

#endif /* !__FO_DOC_PRIVATE_H__ */
