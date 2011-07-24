/* Fo
 * fo-region-before.h: 'region-before' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REGION_BEFORE_H__
#define __FO_REGION_BEFORE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-region-before-after.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/**
 * FoRegionBefore:
 *
 * Instance of the 'region-before' formatting object.
 **/
typedef struct _FoRegionBefore      FoRegionBefore;

/**
 * FoRegionBeforeClass:
 *
 * Class structure for the 'region-before' formatting object.
 **/
typedef struct _FoRegionBeforeClass FoRegionBeforeClass;

#define FO_TYPE_REGION_BEFORE              (fo_region_before_get_type ())
#define FO_REGION_BEFORE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_REGION_BEFORE, FoRegionBefore))
#define FO_REGION_BEFORE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_REGION_BEFORE, FoRegionBeforeClass))
#define FO_IS_REGION_BEFORE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_REGION_BEFORE))
#define FO_IS_REGION_BEFORE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_REGION_BEFORE))
#define FO_REGION_BEFORE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_REGION_BEFORE, FoRegionBeforeClass))


GType        fo_region_before_get_type (void) G_GNUC_CONST;
FoFo *       fo_region_before_new      (void);

FoProperty * fo_region_before_get_precedence (FoFo       *fo_fo);
void         fo_region_before_set_precedence (FoFo       *fo_fo,
                                              FoProperty *new_precedence);

G_END_DECLS

#endif /* !__FO_REGION_BEFORE_H__ */
