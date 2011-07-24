/* Fo
 * fo-region-outer.h: Abstract 'outer region' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_OUTER_H__
#define __FO_REGION_OUTER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-region.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoRegionOuter:
 *
 * Instance of the 'outer region' formatting object.
 **/
typedef struct _FoRegionOuter      FoRegionOuter;

/**
 * FoRegionOuterClass:
 *
 * Class structure for the 'outer region' formatting object.
 **/
typedef struct _FoRegionOuterClass FoRegionOuterClass;

#define FO_TYPE_REGION_OUTER              (fo_region_outer_get_type ())
#define FO_REGION_OUTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REGION_OUTER, FoRegionOuter))
#define FO_REGION_OUTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REGION_OUTER, FoRegionOuterClass))
#define FO_IS_REGION_OUTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REGION_OUTER))
#define FO_IS_REGION_OUTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REGION_OUTER))
#define FO_REGION_OUTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REGION_OUTER, FoRegionOuterClass))


GType        fo_region_outer_get_type (void) G_GNUC_CONST;
FoFo *       fo_region_outer_new      (void);

FoProperty * fo_region_outer_get_extent (FoFo       *fo_fo);
void         fo_region_outer_set_extent (FoFo       *fo_fo,
					 FoProperty *new_extent);

G_END_DECLS

#endif /* !__FO_REGION_OUTER_H__ */
