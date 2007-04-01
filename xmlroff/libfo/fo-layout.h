/* Fo
 * fo-layout.h: Object type for PangoLayout
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-layout.h,v 1.4 2004/05/02 22:42:00 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LAYOUT_H__
#define __FO_LAYOUT_H__

#include <libfo/fo-utils.h>

typedef struct _FoLayout      FoLayout;
typedef struct _FoLayoutClass FoLayoutClass;

#include <libfo/fo-font-desc.h>
#include <libfo/fo-doc.h>
#include <datatype/fo-enum.h>

G_BEGIN_DECLS

#define FO_LAYOUT_ERROR fo_layout_error_quark ()
GQuark fo_layout_error_quark (void);

typedef enum
{
  FO_LAYOUT_ERROR_FAILED
} FoLayoutError;

typedef struct _FoRectangle FoRectangle;

struct _FoRectangle
{
  int x;
  int y;
  int width;
  int height;
};

#define FO_TYPE_LAYOUT              (fo_layout_get_type ())
#define FO_LAYOUT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_LAYOUT, FoLayout))
#define FO_LAYOUT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_LAYOUT, FoLayoutClass))
#define FO_IS_LAYOUT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_LAYOUT))
#define FO_IS_LAYOUT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_LAYOUT))
#define FO_LAYOUT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_LAYOUT, FoLayoutClass))

GType      fo_layout_get_type  (void);
FoLayout * fo_layout_new       (void);
FoLayout * fo_layout_new_from_fo_doc      (FoDoc   *fo_doc);

FoLayout * fo_layout_copy                 (FoLayout         *src);

void       fo_layout_set_attributes   (FoLayout           *fo_layout,
				       GList              *attr_glist);
void       fo_layout_set_text         (FoLayout           *fo_layout,
				       GString            *text);
void       fo_layout_set_width        (FoLayout           *fo_layout,
				       gfloat              width);
void       fo_layout_set_font_desc    (FoLayout           *fo_layout,
				       const FoFontDesc   *desc);
void       fo_layout_set_alignment    (FoLayout           *fo_layout,
				       FoEnumAreaDirection alignment);
void       fo_layout_set_indent       (FoLayout           *fo_layout,
				       gfloat              indent);
void       fo_layout_set_justify      (FoLayout           *fo_layout,
				       gboolean            justify);
gint       fo_layout_get_line_count   (FoLayout           *fo_layout);
void       fo_layout_get_extents      (FoLayout           *fo_layout,
				       FoRectangle        *logical_rect);
void       fo_layout_get_line_extents (FoLayout           *fo_layout,
				       gint                line_index,
				       FoRectangle        *logical_rect);

void fo_layout_set_line_height            (FoLayout  *fo_layout,
					   gfloat     line_height);
void fo_layout_set_line_stacking_strategy (FoLayout  *fo_layout,
					   FoEnumEnum line_stacking_strategy);


G_END_DECLS


#endif /* !__FO_LAYOUT_H__ */
