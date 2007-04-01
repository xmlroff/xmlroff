/* Fo
 * fo-property-keep-with-next.h: 'keep-with-next' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-keep-with-next.h,v 1.3 2003/12/17 15:49:42 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_KEEP_WITH_NEXT_H__
#define __FO_PROPERTY_KEEP_WITH_NEXT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

#define FO_TYPE_PROPERTY_KEEP_WITH_NEXT              (fo_property_keep_with_next_get_type ())
#define FO_PROPERTY_KEEP_WITH_NEXT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_KEEP_WITH_NEXT, FoPropertyKeepWithNext))
#define FO_PROPERTY_KEEP_WITH_NEXT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_KEEP_WITH_NEXT, FoPropertyKeepWithNextClass))
#define FO_IS_PROPERTY_KEEP_WITH_NEXT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_KEEP_WITH_NEXT))
#define FO_IS_PROPERTY_KEEP_WITH_NEXT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_KEEP_WITH_NEXT))
#define FO_PROPERTY_KEEP_WITH_NEXT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_KEEP_WITH_NEXT, FoPropertyKeepWithNextClass))


typedef struct _FoPropertyKeepWithNext      FoPropertyKeepWithNext;
typedef struct _FoPropertyKeepWithNextClass FoPropertyKeepWithNextClass;

GType        fo_property_keep_with_next_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_keep_with_next_new         (void);
FoProperty * fo_property_keep_with_next_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_KEEP_WITH_NEXT_H__ */
