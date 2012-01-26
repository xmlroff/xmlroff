/* Fo
 * fo-area-region.h: Region area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_REGION_H__
#define __FO_AREA_REGION_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-viewport-reference.h>

G_BEGIN_DECLS

typedef struct _FoAreaRegionNameAndArea
{
  const gchar *name;
  FoArea      *area;
} FoAreaRegionNameAndArea;

typedef struct _FoAreaRegion      FoAreaRegion;
typedef struct _FoAreaRegionClass FoAreaRegionClass;

#define FO_TYPE_AREA_REGION              (fo_area_region_get_type ())
#define FO_AREA_REGION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_REGION, FoAreaRegion))
#define FO_AREA_REGION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_REGION, FoAreaRegionClass))
#define FO_IS_AREA_REGION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_REGION))
#define FO_IS_AREA_REGION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_REGION))
#define FO_AREA_REGION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_REGION, FoAreaRegionClass))


GType    fo_area_region_get_type (void) G_GNUC_CONST;
FoArea * fo_area_region_new      (void);

void     fo_area_region_set_region_name    (FoArea      *fo_area_region,
					    const gchar* new_region_name);
gchar *  fo_area_region_get_region_name    (FoArea      *fo_area_region);

gboolean fo_area_region_is_named_region    (FoArea      *region,
					    gpointer     data);
G_END_DECLS

#endif /* !__FO_AREA_REGION_H__ */
