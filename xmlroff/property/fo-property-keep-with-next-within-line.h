/* Fo
 * fo-property-keep-with-next-within-line.h: 'keep-with-next-within-line' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-keep-with-next-within-line.h,v 1.4 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE_H__
#define __FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* keep-with-next-within-line */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <keep> | inherit */
/* Initial value: .within-line=auto, .within-column=auto, .within-page=auto */

#define FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE              (fo_property_keep_with_next_within_line_get_type ())
#define FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE, FoPropertyKeepWithNextWithinLine))
#define FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE, FoPropertyKeepWithNextWithinLineClass))
#define FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE))
#define FO_IS_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE))
#define FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE, FoPropertyKeepWithNextWithinLineClass))


typedef struct _FoPropertyKeepWithNextWithinLine      FoPropertyKeepWithNextWithinLine;
typedef struct _FoPropertyKeepWithNextWithinLineClass FoPropertyKeepWithNextWithinLineClass;

GType       fo_property_keep_with_next_within_line_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_keep_with_next_within_line_new         (void);
FoProperty* fo_property_keep_with_next_within_line_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_KEEP_WITH_NEXT_WITHIN_LINE_H__ */
