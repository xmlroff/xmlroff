/* Fo
 * fo-property-space-end-maximum.h: 'space-end-maximum' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_END_MAXIMUM_H__
#define __FO_PROPERTY_SPACE_END_MAXIMUM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-end-maximum */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_END_MAXIMUM              (fo_property_space_end_maximum_get_type ())
#define FO_PROPERTY_SPACE_END_MAXIMUM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_END_MAXIMUM, FoPropertySpaceEndMaximum))
#define FO_PROPERTY_SPACE_END_MAXIMUM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_END_MAXIMUM, FoPropertySpaceEndMaximumClass))
#define FO_IS_PROPERTY_SPACE_END_MAXIMUM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_END_MAXIMUM))
#define FO_IS_PROPERTY_SPACE_END_MAXIMUM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_END_MAXIMUM))
#define FO_PROPERTY_SPACE_END_MAXIMUM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_END_MAXIMUM, FoPropertySpaceEndMaximumClass))


typedef struct _FoPropertySpaceEndMaximum      FoPropertySpaceEndMaximum;
typedef struct _FoPropertySpaceEndMaximumClass FoPropertySpaceEndMaximumClass;

GType       fo_property_space_end_maximum_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_end_maximum_new         (void);
FoProperty* fo_property_space_end_maximum_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_END_MAXIMUM_H__ */
