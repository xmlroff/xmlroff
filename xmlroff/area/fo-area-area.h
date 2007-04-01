/* Fo
 * fo-area-area.h: Area area object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-area.h,v 1.2 2003/03/19 21:12:40 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_AREA_AREA_H__
#define __FO_AREA_AREA_H__

#include <libfo/fo-utils.h>
#include <fo-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaArea      FoAreaArea;
typedef struct _FoAreaAreaClass FoAreaAreaClass;

#define FO_TYPE_AREA_AREA              (fo_area_area_get_type ())
#define FO_AREA_AREA(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_AREA, FoAreaArea))
#define FO_AREA_AREA_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_AREA, FoAreaAreaClass))
#define FO_IS_AREA_AREA(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_AREA))
#define FO_IS_AREA_AREA_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_AREA))
#define FO_AREA_AREA_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_AREA, FoAreaAreaClass))


GType         fo_area_area_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_area_new (void);

void fo_area_area_set_x (FoArea *fo_area,
			 gfloat new_x);
gfloat fo_area_area_get_x (FoArea *fo_area);
void fo_area_area_set_y (FoArea *fo_area,
			 gfloat new_y);
gfloat fo_area_area_get_y (FoArea *fo_area);
void fo_area_area_set_width (FoArea *fo_area,
			     gfloat new_width);
gfloat fo_area_area_get_width (FoArea *fo_area);
void fo_area_area_set_height (FoArea *fo_area,
			      gfloat new_height);
gfloat fo_area_area_get_height (FoArea *fo_area);
void fo_area_area_set_border_before (FoArea *fo_area,
				     gfloat new_border_before);
gfloat fo_area_area_get_border_before (FoArea *fo_area);
void fo_area_area_set_border_after (FoArea *fo_area,
				    gfloat new_border_after);
gfloat fo_area_area_get_border_after (FoArea *fo_area);
void fo_area_area_set_border_start (FoArea *fo_area,
				    gfloat new_border_start);
gfloat fo_area_area_get_border_start (FoArea *fo_area);
void fo_area_area_set_border_end (FoArea *fo_area,
				  gfloat new_border_end);
gfloat fo_area_area_get_border_end (FoArea *fo_area);
void fo_area_area_set_padding_before (FoArea *fo_area,
				      gfloat new_padding_before);
gfloat fo_area_area_get_padding_before (FoArea *fo_area);
void fo_area_area_set_padding_after (FoArea *fo_area,
				     gfloat new_padding_after);
gfloat fo_area_area_get_padding_after (FoArea *fo_area);
void fo_area_area_set_padding_start (FoArea *fo_area,
				     gfloat new_padding_start);
gfloat fo_area_area_get_padding_start (FoArea *fo_area);
void fo_area_area_set_padding_end (FoArea *fo_area,
				   gfloat new_padding_end);
gfloat fo_area_area_get_padding_end (FoArea *fo_area);
void fo_area_area_set_start_indent (FoArea *fo_area,
				    gfloat new_start_indent);
gfloat fo_area_area_get_start_indent (FoArea *fo_area);
void fo_area_area_set_end_indent (FoArea *fo_area,
				  gfloat new_end_indent);
gfloat fo_area_area_get_end_indent (FoArea *fo_area);
void fo_area_area_set_space_before (FoArea *fo_area,
				    gfloat new_space_before);
gfloat fo_area_area_get_space_before (FoArea *fo_area);
void fo_area_area_set_space_after (FoArea *fo_area,
				   gfloat new_space_after);
gfloat fo_area_area_get_space_after (FoArea *fo_area);

G_END_DECLS

#endif /* !__FO_AREA_AREA_H__ */
