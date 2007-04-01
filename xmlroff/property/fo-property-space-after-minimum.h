/* Fo
 * fo-property-space-after-minimum.h: 'space-after-minimum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-space-after-minimum.h,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_AFTER_MINIMUM_H__
#define __FO_PROPERTY_SPACE_AFTER_MINIMUM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-after-minimum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_AFTER_MINIMUM              (fo_property_space_after_minimum_get_type ())
#define FO_PROPERTY_SPACE_AFTER_MINIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_AFTER_MINIMUM, FoPropertySpaceAfterMinimum))
#define FO_PROPERTY_SPACE_AFTER_MINIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_AFTER_MINIMUM, FoPropertySpaceAfterMinimumClass))
#define FO_IS_PROPERTY_SPACE_AFTER_MINIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_AFTER_MINIMUM))
#define FO_IS_PROPERTY_SPACE_AFTER_MINIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_AFTER_MINIMUM))
#define FO_PROPERTY_SPACE_AFTER_MINIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_AFTER_MINIMUM, FoPropertySpaceAfterMinimumClass))


typedef struct _FoPropertySpaceAfterMinimum      FoPropertySpaceAfterMinimum;
typedef struct _FoPropertySpaceAfterMinimumClass FoPropertySpaceAfterMinimumClass;

GType       fo_property_space_after_minimum_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_after_minimum_new         (void);
FoProperty* fo_property_space_after_minimum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_AFTER_MINIMUM_H__ */
