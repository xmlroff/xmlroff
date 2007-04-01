/* Fo
 * fo-property-border-after-precedence.h: 'border-after-precedence' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-after-precedence.h,v 1.4 2004/05/02 22:52:19 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_AFTER_PRECEDENCE_H__
#define __FO_PROPERTY_BORDER_AFTER_PRECEDENCE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-after-precedence */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* force | <integer> | inherit */
/* Initial value: fo:table: 6, fo:table-cell: 5, fo:table-column: 4, fo:table-row: 3, fo:table-body: 2, fo:table-header: 1, fo:table-footer: 0 */

#define FO_TYPE_PROPERTY_BORDER_AFTER_PRECEDENCE              (fo_property_border_after_precedence_get_type ())
#define FO_PROPERTY_BORDER_AFTER_PRECEDENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_AFTER_PRECEDENCE, FoPropertyBorderAfterPrecedence))
#define FO_PROPERTY_BORDER_AFTER_PRECEDENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_AFTER_PRECEDENCE, FoPropertyBorderAfterPrecedenceClass))
#define FO_IS_PROPERTY_BORDER_AFTER_PRECEDENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_AFTER_PRECEDENCE))
#define FO_IS_PROPERTY_BORDER_AFTER_PRECEDENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_AFTER_PRECEDENCE))
#define FO_PROPERTY_BORDER_AFTER_PRECEDENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_AFTER_PRECEDENCE, FoPropertyBorderAfterPrecedenceClass))


typedef struct _FoPropertyBorderAfterPrecedence      FoPropertyBorderAfterPrecedence;
typedef struct _FoPropertyBorderAfterPrecedenceClass FoPropertyBorderAfterPrecedenceClass;

GType        fo_property_border_after_precedence_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_after_precedence_new         (void);
FoProperty * fo_property_border_after_precedence_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_AFTER_PRECEDENCE_H__ */
