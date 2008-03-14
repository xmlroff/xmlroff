/* Fo
 * fo-property-space-after-maximum.h: 'space-after-maximum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_AFTER_MAXIMUM_H__
#define __FO_PROPERTY_SPACE_AFTER_MAXIMUM_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* space-after-maximum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_AFTER_MAXIMUM              (fo_property_space_after_maximum_get_type ())
#define FO_PROPERTY_SPACE_AFTER_MAXIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_AFTER_MAXIMUM, FoPropertySpaceAfterMaximum))
#define FO_PROPERTY_SPACE_AFTER_MAXIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_AFTER_MAXIMUM, FoPropertySpaceAfterMaximumClass))
#define FO_IS_PROPERTY_SPACE_AFTER_MAXIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_AFTER_MAXIMUM))
#define FO_IS_PROPERTY_SPACE_AFTER_MAXIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_AFTER_MAXIMUM))
#define FO_PROPERTY_SPACE_AFTER_MAXIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_AFTER_MAXIMUM, FoPropertySpaceAfterMaximumClass))


typedef struct _FoPropertySpaceAfterMaximum      FoPropertySpaceAfterMaximum;
typedef struct _FoPropertySpaceAfterMaximumClass FoPropertySpaceAfterMaximumClass;

GType       fo_property_space_after_maximum_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_after_maximum_new         (void);
FoProperty* fo_property_space_after_maximum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_AFTER_MAXIMUM_H__ */
