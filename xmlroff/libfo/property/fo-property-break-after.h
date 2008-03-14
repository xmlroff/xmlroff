/* Fo
 * fo-property-break-after.h: 'break-after' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BREAK_AFTER_H__
#define __FO_PROPERTY_BREAK_AFTER_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* break-after */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | column | page | even-page | odd-page | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_BREAK_AFTER              (fo_property_break_after_get_type ())
#define FO_PROPERTY_BREAK_AFTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BREAK_AFTER, FoPropertyBreakAfter))
#define FO_PROPERTY_BREAK_AFTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BREAK_AFTER, FoPropertyBreakAfterClass))
#define FO_IS_PROPERTY_BREAK_AFTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BREAK_AFTER))
#define FO_IS_PROPERTY_BREAK_AFTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BREAK_AFTER))
#define FO_PROPERTY_BREAK_AFTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BREAK_AFTER, FoPropertyBreakAfterClass))


typedef struct _FoPropertyBreakAfter      FoPropertyBreakAfter;
typedef struct _FoPropertyBreakAfterClass FoPropertyBreakAfterClass;

GType        fo_property_break_after_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_break_after_new         (void);
FoProperty * fo_property_break_after_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BREAK_AFTER_H__ */
