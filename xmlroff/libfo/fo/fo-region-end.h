/* Fo
 * fo-region-end.h: 'region-end' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_END_H__
#define __FO_REGION_END_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-region-outer.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoRegionEnd:
 *
 * Instance of the 'region-end' formatting object.
 **/
typedef struct _FoRegionEnd      FoRegionEnd;

/**
 * FoRegionEndClass:
 *
 * Class structure for the 'region-end' formatting object.
 **/
typedef struct _FoRegionEndClass FoRegionEndClass;

#define FO_TYPE_REGION_END              (fo_region_end_get_type ())
#define FO_REGION_END(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REGION_END, FoRegionEnd))
#define FO_REGION_END_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REGION_END, FoRegionEndClass))
#define FO_IS_REGION_END(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REGION_END))
#define FO_IS_REGION_END_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REGION_END))
#define FO_REGION_END_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REGION_END, FoRegionEndClass))


GType        fo_region_end_get_type (void) G_GNUC_CONST;
FoFo *       fo_region_end_new      (void);

G_END_DECLS

#endif /* !__FO_REGION_END_H__ */
