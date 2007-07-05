/* Fo
 * fo-property-space-after-conditionality.h: 'space-after.conditionality' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_AFTER_CONDITY_H__
#define __FO_PROPERTY_SPACE_AFTER_CONDITY_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-after-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_AFTER_CONDITY              (fo_property_space_after_condity_get_type ())
#define FO_PROPERTY_SPACE_AFTER_CONDITY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_AFTER_CONDITY, FoPropertySpaceAfterCondity))
#define FO_PROPERTY_SPACE_AFTER_CONDITY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_AFTER_CONDITY, FoPropertySpaceAfterCondityClass))
#define FO_IS_PROPERTY_SPACE_AFTER_CONDITY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_AFTER_CONDITY))
#define FO_IS_PROPERTY_SPACE_AFTER_CONDITY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_AFTER_CONDITY))
#define FO_PROPERTY_SPACE_AFTER_CONDITY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_AFTER_CONDITY, FoPropertySpaceAfterCondityClass))


typedef struct _FoPropertySpaceAfterCondity      FoPropertySpaceAfterCondity;
typedef struct _FoPropertySpaceAfterCondityClass FoPropertySpaceAfterCondityClass;

GType       fo_property_space_after_condity_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_after_condity_new         (void);
FoProperty* fo_property_space_after_condity_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_AFTER_CONDITY_H__ */
