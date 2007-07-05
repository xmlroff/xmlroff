/* Fo
 * fo-area-layout.h: Layout area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_LAYOUT_H__
#define __FO_AREA_LAYOUT_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaLayout      FoAreaLayout;
typedef struct _FoAreaLayoutClass FoAreaLayoutClass;

#define FO_TYPE_AREA_LAYOUT              (fo_area_layout_get_type ())
#define FO_AREA_LAYOUT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_LAYOUT, FoAreaLayout))
#define FO_AREA_LAYOUT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_LAYOUT, FoAreaLayoutClass))
#define FO_IS_AREA_LAYOUT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_LAYOUT))
#define FO_IS_AREA_LAYOUT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_LAYOUT))
#define FO_AREA_LAYOUT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_LAYOUT, FoAreaLayoutClass))


GType      fo_area_layout_get_type        (void) G_GNUC_CONST;
FoArea *   fo_area_layout_new             (void);
FoLayout * fo_area_layout_get_layout      (FoArea   *fo_area_layout);
void       fo_area_layout_set_layout      (FoArea   *fo_area_layout,
					   FoLayout *new_layout);
guint      fo_area_layout_get_line_first  (FoArea   *fo_area_layout);
void       fo_area_layout_set_line_first  (FoArea   *fo_area_layout,
					   guint     new_line_first);
guint      fo_area_layout_get_line_last   (FoArea   *fo_area_layout);
void       fo_area_layout_set_line_last   (FoArea   *fo_area_layout,
					   guint      new_line_last);
gdouble    fo_area_layout_get_line_height (FoArea   *fo_area_layout,
					   gint      line_number);
G_END_DECLS

#endif /* !__FO_AREA_LAYOUT_H__ */
