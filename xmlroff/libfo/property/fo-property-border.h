/* Fo
 * fo-property-border.h: 'border' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_H__
#define __FO_PROPERTY_BORDER_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* border */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* [ <border-width> || <border-style> || <color> ] | inherit */
/* Initial value: see individual properties */

#define FO_TYPE_PROPERTY_BORDER              (fo_property_border_get_type ())
#define FO_PROPERTY_BORDER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER, FoPropertyBorder))
#define FO_PROPERTY_BORDER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER, FoPropertyBorderClass))
#define FO_IS_PROPERTY_BORDER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER))
#define FO_IS_PROPERTY_BORDER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER))
#define FO_PROPERTY_BORDER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER, FoPropertyBorderClass))


typedef struct _FoPropertyBorder      FoPropertyBorder;
typedef struct _FoPropertyBorderClass FoPropertyBorderClass;

GType        fo_property_border_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_border_new         (void);
FoProperty * fo_property_border_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_H__ */
