/* Fo
 * fo-property-space-start-optimum.h: 'space-start-optimum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_START_OPTIMUM_H__
#define __FO_PROPERTY_SPACE_START_OPTIMUM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-start-optimum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_START_OPTIMUM              (fo_property_space_start_optimum_get_type ())
#define FO_PROPERTY_SPACE_START_OPTIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_START_OPTIMUM, FoPropertySpaceStartOptimum))
#define FO_PROPERTY_SPACE_START_OPTIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_START_OPTIMUM, FoPropertySpaceStartOptimumClass))
#define FO_IS_PROPERTY_SPACE_START_OPTIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_START_OPTIMUM))
#define FO_IS_PROPERTY_SPACE_START_OPTIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_START_OPTIMUM))
#define FO_PROPERTY_SPACE_START_OPTIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_START_OPTIMUM, FoPropertySpaceStartOptimumClass))


typedef struct _FoPropertySpaceStartOptimum      FoPropertySpaceStartOptimum;
typedef struct _FoPropertySpaceStartOptimumClass FoPropertySpaceStartOptimumClass;

GType       fo_property_space_start_optimum_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_start_optimum_new         (void);
FoProperty* fo_property_space_start_optimum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_START_OPTIMUM_H__ */
