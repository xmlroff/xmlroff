/* Fo
 * fo-property-border-before-precedence.h: 'border-before-precedence' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_BEFORE_PRECEDENCE_H__
#define __FO_PROPERTY_BORDER_BEFORE_PRECEDENCE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* border-before-precedence */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* force | <integer> | inherit */
/* Initial value: fo:table: 6, fo:table-cell: 5, fo:table-column: 4, fo:table-row: 3, fo:table-body: 2, fo:table-header: 1, fo:table-footer: 0 */

#define FO_TYPE_PROPERTY_BORDER_BEFORE_PRECEDENCE              (fo_property_border_before_precedence_get_type ())
#define FO_PROPERTY_BORDER_BEFORE_PRECEDENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_BEFORE_PRECEDENCE, FoPropertyBorderBeforePrecedence))
#define FO_PROPERTY_BORDER_BEFORE_PRECEDENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_BEFORE_PRECEDENCE, FoPropertyBorderBeforePrecedenceClass))
#define FO_IS_PROPERTY_BORDER_BEFORE_PRECEDENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_BEFORE_PRECEDENCE))
#define FO_IS_PROPERTY_BORDER_BEFORE_PRECEDENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_BEFORE_PRECEDENCE))
#define FO_PROPERTY_BORDER_BEFORE_PRECEDENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_BEFORE_PRECEDENCE, FoPropertyBorderBeforePrecedenceClass))


typedef struct _FoPropertyBorderBeforePrecedence      FoPropertyBorderBeforePrecedence;
typedef struct _FoPropertyBorderBeforePrecedenceClass FoPropertyBorderBeforePrecedenceClass;

GType        fo_property_border_before_precedence_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_before_precedence_new         (void);
FoProperty * fo_property_border_before_precedence_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_BEFORE_PRECEDENCE_H__ */
