/* Fo
 * fo-property-border-right.h: 'border-right' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_RIGHT_H__
#define __FO_PROPERTY_BORDER_RIGHT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-right */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

#define FO_TYPE_PROPERTY_BORDER_RIGHT              (fo_property_border_right_get_type ())
#define FO_PROPERTY_BORDER_RIGHT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_RIGHT, FoPropertyBorderRight))
#define FO_PROPERTY_BORDER_RIGHT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_RIGHT, FoPropertyBorderRightClass))
#define FO_IS_PROPERTY_BORDER_RIGHT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_RIGHT))
#define FO_IS_PROPERTY_BORDER_RIGHT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_RIGHT))
#define FO_PROPERTY_BORDER_RIGHT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_RIGHT, FoPropertyBorderRightClass))


typedef struct _FoPropertyBorderRight      FoPropertyBorderRight;
typedef struct _FoPropertyBorderRightClass FoPropertyBorderRightClass;

GType        fo_property_border_right_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_right_new         (void);
FoProperty * fo_property_border_right_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_RIGHT_H__ */
