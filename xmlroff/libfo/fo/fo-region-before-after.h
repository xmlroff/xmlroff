/* Fo
 * fo-region-before-after.h: 'region-before-after' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_BEFORE_AFTER_H__
#define __FO_REGION_BEFORE_AFTER_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-region-outer.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoRegionBeforeAfter:
 *
 * Instance of the 'region-before-after' formatting object.
 **/
typedef struct _FoRegionBeforeAfter      FoRegionBeforeAfter;

/**
 * FoRegionBeforeAfterClass:
 *
 * Class structure for the 'region-before-after' formatting object.
 **/
typedef struct _FoRegionBeforeAfterClass FoRegionBeforeAfterClass;

#define FO_TYPE_REGION_BEFORE_AFTER              (fo_region_before_after_get_type ())
#define FO_REGION_BEFORE_AFTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REGION_BEFORE_AFTER, FoRegionBeforeAfter))
#define FO_REGION_BEFORE_AFTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REGION_BEFORE_AFTER, FoRegionBeforeAfterClass))
#define FO_IS_REGION_BEFORE_AFTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REGION_BEFORE_AFTER))
#define FO_IS_REGION_BEFORE_AFTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REGION_BEFORE_AFTER))
#define FO_REGION_BEFORE_AFTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REGION_BEFORE_AFTER, FoRegionBeforeAfterClass))


GType        fo_region_before_after_get_type (void) G_GNUC_CONST;
FoFo *       fo_region_before_after_new      (void);

FoProperty * fo_region_before_after_get_precedence (FoFo       *fo_fo);
void         fo_region_before_after_set_precedence (FoFo       *fo_fo,
						    FoProperty *new_precedence);

G_END_DECLS

#endif /* !__FO_REGION_BEFORE_AFTER_H__ */
