/* Fo
 * fo-property-space-after.h: 'space-after' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-space-after.h,v 1.3 2003/12/16 17:10:43 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_AFTER_H__
#define __FO_PROPERTY_SPACE_AFTER_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-after */
/* <space> | <percentage> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_SPACE_AFTER              (fo_property_space_after_get_type ())
#define FO_PROPERTY_SPACE_AFTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_AFTER, FoPropertySpaceAfter))
#define FO_PROPERTY_SPACE_AFTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_AFTER, FoPropertySpaceAfterClass))
#define FO_IS_PROPERTY_SPACE_AFTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_AFTER))
#define FO_IS_PROPERTY_SPACE_AFTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_AFTER))
#define FO_PROPERTY_SPACE_AFTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_AFTER, FoPropertySpaceAfterClass))


typedef struct _FoPropertySpaceAfter      FoPropertySpaceAfter;
typedef struct _FoPropertySpaceAfterClass FoPropertySpaceAfterClass;

GType       fo_property_space_after_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_after_new         (void);
FoProperty* fo_property_space_after_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_AFTER_H__ */
