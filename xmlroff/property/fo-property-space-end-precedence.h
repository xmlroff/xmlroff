/* Fo
 * fo-property-space-end-precedence.h: 'space-end-precedence' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-space-end-precedence.h,v 1.3 2004/03/23 11:59:24 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_SPACE_END_PRECEDENCE_H__
#define __FO_PROPERTY_SPACE_END_PRECEDENCE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* space-end-precedence */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <space> | inherit */
/* Initial value: space.minimum=0pt, .optimum=0pt, .maximum=0pt, .conditionality=discard, .precedence=0 */

#define FO_TYPE_PROPERTY_SPACE_END_PRECEDENCE              (fo_property_space_end_precedence_get_type ())
#define FO_PROPERTY_SPACE_END_PRECEDENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPACE_END_PRECEDENCE, FoPropertySpaceEndPrecedence))
#define FO_PROPERTY_SPACE_END_PRECEDENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPACE_END_PRECEDENCE, FoPropertySpaceEndPrecedenceClass))
#define FO_IS_PROPERTY_SPACE_END_PRECEDENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPACE_END_PRECEDENCE))
#define FO_IS_PROPERTY_SPACE_END_PRECEDENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPACE_END_PRECEDENCE))
#define FO_PROPERTY_SPACE_END_PRECEDENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPACE_END_PRECEDENCE, FoPropertySpaceEndPrecedenceClass))


typedef struct _FoPropertySpaceEndPrecedence      FoPropertySpaceEndPrecedence;
typedef struct _FoPropertySpaceEndPrecedenceClass FoPropertySpaceEndPrecedenceClass;

GType       fo_property_space_end_precedence_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_space_end_precedence_new         (void);
FoProperty* fo_property_space_end_precedence_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPACE_END_PRECEDENCE_H__ */
