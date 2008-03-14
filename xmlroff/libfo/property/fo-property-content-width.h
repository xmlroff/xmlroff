/* Fo
 * fo-property-content-width.h: 'content-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_CONTENT_WIDTH_H__
#define __FO_PROPERTY_CONTENT_WIDTH_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* content-width */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | scale-to-fit | <length> | <percentage> | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_CONTENT_WIDTH              (fo_property_content_width_get_type ())
#define FO_PROPERTY_CONTENT_WIDTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_CONTENT_WIDTH, FoPropertyContentWidth))
#define FO_PROPERTY_CONTENT_WIDTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_CONTENT_WIDTH, FoPropertyContentWidthClass))
#define FO_IS_PROPERTY_CONTENT_WIDTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_CONTENT_WIDTH))
#define FO_IS_PROPERTY_CONTENT_WIDTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_CONTENT_WIDTH))
#define FO_PROPERTY_CONTENT_WIDTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_CONTENT_WIDTH, FoPropertyContentWidthClass))


typedef struct _FoPropertyContentWidth      FoPropertyContentWidth;
typedef struct _FoPropertyContentWidthClass FoPropertyContentWidthClass;

GType        fo_property_content_width_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_content_width_new         (void);
FoProperty * fo_property_content_width_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_CONTENT_WIDTH_H__ */
