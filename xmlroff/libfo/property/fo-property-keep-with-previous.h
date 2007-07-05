/* Fo
 * fo-property-keep-with-previous.h: 'keep-with-previous' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_KEEP_WITH_PREVIOUS_H__
#define __FO_PROPERTY_KEEP_WITH_PREVIOUS_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

#define FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS              (fo_property_keep_with_previous_get_type ())
#define FO_PROPERTY_KEEP_WITH_PREVIOUS(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS, FoPropertyKeepWithPrevious))
#define FO_PROPERTY_KEEP_WITH_PREVIOUS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS, FoPropertyKeepWithPreviousClass))
#define FO_IS_PROPERTY_KEEP_WITH_PREVIOUS(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS))
#define FO_IS_PROPERTY_KEEP_WITH_PREVIOUS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS))
#define FO_PROPERTY_KEEP_WITH_PREVIOUS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS, FoPropertyKeepWithPreviousClass))


typedef struct _FoPropertyKeepWithPrevious      FoPropertyKeepWithPrevious;
typedef struct _FoPropertyKeepWithPreviousClass FoPropertyKeepWithPreviousClass;

GType        fo_property_keep_with_previous_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_keep_with_previous_new         (void);
FoProperty * fo_property_keep_with_previous_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_KEEP_WITH_PREVIOUS_H__ */
