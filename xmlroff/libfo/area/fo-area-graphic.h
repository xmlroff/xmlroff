/* Fo
 * fo-area-graphic.h: Graphic inline-area object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_GRAPHIC_H__
#define __FO_AREA_GRAPHIC_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

typedef struct _FoAreaGraphic      FoAreaGraphic;
typedef struct _FoAreaGraphicClass FoAreaGraphicClass;

#define FO_TYPE_AREA_GRAPHIC              (fo_area_graphic_get_type ())
#define FO_AREA_GRAPHIC(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_GRAPHIC, FoAreaGraphic))
#define FO_AREA_GRAPHIC_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_GRAPHIC, FoAreaGraphicClass))
#define FO_IS_AREA_GRAPHIC(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_GRAPHIC))
#define FO_IS_AREA_GRAPHIC_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_GRAPHIC))
#define FO_AREA_GRAPHIC_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_GRAPHIC, FoAreaGraphicClass))


GType    fo_area_graphic_get_type (void) G_GNUC_CONST;
FoArea * fo_area_graphic_new      (void);

G_END_DECLS

#endif /* !__FO_AREA_GRAPHIC_H__ */
