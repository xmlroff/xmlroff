/* Fo
 * fo-property-break-before.h: 'break-before' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-break-before.h,v 1.4 2004/03/24 11:56:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BREAK_BEFORE_H__
#define __FO_PROPERTY_BREAK_BEFORE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* break-before */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | column | page | even-page | odd-page | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_BREAK_BEFORE              (fo_property_break_before_get_type ())
#define FO_PROPERTY_BREAK_BEFORE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BREAK_BEFORE, FoPropertyBreakBefore))
#define FO_PROPERTY_BREAK_BEFORE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BREAK_BEFORE, FoPropertyBreakBeforeClass))
#define FO_IS_PROPERTY_BREAK_BEFORE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BREAK_BEFORE))
#define FO_IS_PROPERTY_BREAK_BEFORE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BREAK_BEFORE))
#define FO_PROPERTY_BREAK_BEFORE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BREAK_BEFORE, FoPropertyBreakBeforeClass))


typedef struct _FoPropertyBreakBefore      FoPropertyBreakBefore;
typedef struct _FoPropertyBreakBeforeClass FoPropertyBreakBeforeClass;

GType        fo_property_break_before_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_break_before_new         (void);
FoProperty * fo_property_break_before_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BREAK_BEFORE_H__ */
