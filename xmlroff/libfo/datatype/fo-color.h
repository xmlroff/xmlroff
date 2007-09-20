/* Fo
 * fo-color.h: Color datatype
 *
 * Copyright (C) 2001, 2002 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_COLOR_H__
#define __FO_COLOR_H__

#include <libfo/fo-utils.h>
#include <libfo/datatype/fo-datatype.h>

G_BEGIN_DECLS

#define FO_TYPE_COLOR	           (fo_color_get_type ())
#define FO_COLOR(object)  (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_COLOR, FoColor))
#define FO_COLOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_COLOR, FoColorClass))
#define FO_IS_COLOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_COLOR))
#define FO_IS_COLOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_COLOR))
#define FO_COLOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_COLOR, FoColorClass))


typedef struct _FoColor      FoColor;
typedef struct _FoColorClass FoColorClass;

GType        fo_color_get_type       (void) G_GNUC_CONST;
FoDatatype * fo_color_new_with_value (guint red,
				      guint green,
				      guint blue);

#define FO_COLOR_COMPONENT_MAX 65535

guint16 fo_color_get_red (FoDatatype *color);
guint16 fo_color_get_green (FoDatatype *color);
guint16 fo_color_get_blue (FoDatatype *color);

FoDatatype* fo_color_get_color_black (void);
FoDatatype* fo_color_get_color_silver (void);
FoDatatype* fo_color_get_color_gray (void);
FoDatatype* fo_color_get_color_white (void);
FoDatatype* fo_color_get_color_maroon (void);
FoDatatype* fo_color_get_color_red (void);
FoDatatype* fo_color_get_color_purple (void);
FoDatatype* fo_color_get_color_fuchsia (void);
FoDatatype* fo_color_get_color_green (void);
FoDatatype* fo_color_get_color_lime (void);
FoDatatype* fo_color_get_color_olive (void);
FoDatatype* fo_color_get_color_yellow (void);
FoDatatype* fo_color_get_color_navy (void);
FoDatatype* fo_color_get_color_blue (void);
FoDatatype* fo_color_get_color_teal (void);
FoDatatype* fo_color_get_color_aqua (void);

FoDatatype* fo_color_get_color_one_quarter   (FoDatatype *color);
FoDatatype* fo_color_get_color_one_half      (FoDatatype *color);
FoDatatype* fo_color_get_color_three_quarter (FoDatatype *color);

G_END_DECLS

#endif /* !__FO_COLOR_H__ */
