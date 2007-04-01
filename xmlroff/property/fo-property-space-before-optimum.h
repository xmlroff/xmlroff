/* Fo
 * fo-property-space-before-optimum.h: 'space-before-optimum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-space-before-optimum.h,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_BEFORE_OPTIMUM_H__
#define __FO_PROPERTY_SPACE_BEFORE_OPTIMUM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-before-optimum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_BEFORE_OPTIMUM              (fo_property_space_before_optimum_get_type ())
#define FO_PROPERTY_SPACE_BEFORE_OPTIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_BEFORE_OPTIMUM, FoPropertySpaceBeforeOptimum))
#define FO_PROPERTY_SPACE_BEFORE_OPTIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_BEFORE_OPTIMUM, FoPropertySpaceBeforeOptimumClass))
#define FO_IS_PROPERTY_SPACE_BEFORE_OPTIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_BEFORE_OPTIMUM))
#define FO_IS_PROPERTY_SPACE_BEFORE_OPTIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_BEFORE_OPTIMUM))
#define FO_PROPERTY_SPACE_BEFORE_OPTIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_BEFORE_OPTIMUM, FoPropertySpaceBeforeOptimumClass))


typedef struct _FoPropertySpaceBeforeOptimum      FoPropertySpaceBeforeOptimum;
typedef struct _FoPropertySpaceBeforeOptimumClass FoPropertySpaceBeforeOptimumClass;

GType       fo_property_space_before_optimum_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_before_optimum_new         (void);
FoProperty* fo_property_space_before_optimum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_BEFORE_OPTIMUM_H__ */
