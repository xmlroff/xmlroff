/* Fo
 * fo-region-start.h: 'region-start' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_START_H__
#define __FO_REGION_START_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-region-outer.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoRegionStart:
 *
 * Instance of the 'region-start' formatting object.
 **/
typedef struct _FoRegionStart      FoRegionStart;

/**
 * FoRegionStartClass:
 *
 * Class structure for the 'region-start' formatting object.
 **/
typedef struct _FoRegionStartClass FoRegionStartClass;

#define FO_TYPE_REGION_START              (fo_region_start_get_type ())
#define FO_REGION_START(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REGION_START, FoRegionStart))
#define FO_REGION_START_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REGION_START, FoRegionStartClass))
#define FO_IS_REGION_START(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REGION_START))
#define FO_IS_REGION_START_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REGION_START))
#define FO_REGION_START_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REGION_START, FoRegionStartClass))


GType        fo_region_start_get_type (void) G_GNUC_CONST;
FoFo *       fo_region_start_new      (void);

G_END_DECLS

#endif /* !__FO_REGION_START_H__ */
