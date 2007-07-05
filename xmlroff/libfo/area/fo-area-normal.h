/* Fo
 * fo-area-normal.h: Normal block-area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_NORMAL_H__
#define __FO_AREA_NORMAL_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaNormal      FoAreaNormal;
typedef struct _FoAreaNormalClass FoAreaNormalClass;

#define FO_TYPE_AREA_NORMAL              (fo_area_normal_get_type ())
#define FO_AREA_NORMAL(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_NORMAL, FoAreaNormal))
#define FO_AREA_NORMAL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_NORMAL, FoAreaNormalClass))
#define FO_IS_AREA_NORMAL(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_NORMAL))
#define FO_IS_AREA_NORMAL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_NORMAL))
#define FO_AREA_NORMAL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_NORMAL, FoAreaNormalClass))


GType         fo_area_normal_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_normal_new (void);

G_END_DECLS

#endif /* !__FO_AREA_NORMAL_H__ */
