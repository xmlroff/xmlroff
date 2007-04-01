/* Fo
 * fo-property-space-after-precedence.h: 'space-after-precedence' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-space-after-precedence.h,v 1.3 2004/03/31 21:12:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_AFTER_PRECEDENCE_H__
#define __FO_PROPERTY_SPACE_AFTER_PRECEDENCE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-after-precedence */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_AFTER_PRECEDENCE              (fo_property_space_after_precedence_get_type ())
#define FO_PROPERTY_SPACE_AFTER_PRECEDENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_AFTER_PRECEDENCE, FoPropertySpaceAfterPrecedence))
#define FO_PROPERTY_SPACE_AFTER_PRECEDENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_AFTER_PRECEDENCE, FoPropertySpaceAfterPrecedenceClass))
#define FO_IS_PROPERTY_SPACE_AFTER_PRECEDENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_AFTER_PRECEDENCE))
#define FO_IS_PROPERTY_SPACE_AFTER_PRECEDENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_AFTER_PRECEDENCE))
#define FO_PROPERTY_SPACE_AFTER_PRECEDENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_AFTER_PRECEDENCE, FoPropertySpaceAfterPrecedenceClass))


typedef struct _FoPropertySpaceAfterPrecedence      FoPropertySpaceAfterPrecedence;
typedef struct _FoPropertySpaceAfterPrecedenceClass FoPropertySpaceAfterPrecedenceClass;

GType        fo_property_space_after_precedence_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_space_after_precedence_new         (void);
FoProperty * fo_property_space_after_precedence_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_AFTER_PRECEDENCE_H__ */
