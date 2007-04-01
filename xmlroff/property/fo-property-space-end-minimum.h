/* Fo
 * fo-property-space-end-minimum.h: 'space-end-minimum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-space-end-minimum.h,v 1.3 2004/03/23 11:59:24 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_END_MINIMUM_H__
#define __FO_PROPERTY_SPACE_END_MINIMUM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-end-minimum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_END_MINIMUM              (fo_property_space_end_minimum_get_type ())
#define FO_PROPERTY_SPACE_END_MINIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_END_MINIMUM, FoPropertySpaceEndMinimum))
#define FO_PROPERTY_SPACE_END_MINIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_END_MINIMUM, FoPropertySpaceEndMinimumClass))
#define FO_IS_PROPERTY_SPACE_END_MINIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_END_MINIMUM))
#define FO_IS_PROPERTY_SPACE_END_MINIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_END_MINIMUM))
#define FO_PROPERTY_SPACE_END_MINIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_END_MINIMUM, FoPropertySpaceEndMinimumClass))


typedef struct _FoPropertySpaceEndMinimum      FoPropertySpaceEndMinimum;
typedef struct _FoPropertySpaceEndMinimumClass FoPropertySpaceEndMinimumClass;

GType       fo_property_space_end_minimum_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_end_minimum_new         (void);
FoProperty* fo_property_space_end_minimum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_END_MINIMUM_H__ */
