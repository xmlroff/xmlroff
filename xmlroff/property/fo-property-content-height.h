/* Fo
 * fo-property-content-height.h: 'content-height' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-content-height.h,v 1.4 2004/03/24 11:56:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_CONTENT_HEIGHT_H__
#define __FO_PROPERTY_CONTENT_HEIGHT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* content-height */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | scale-to-fit | <length> | <percentage> | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_CONTENT_HEIGHT              (fo_property_content_height_get_type ())
#define FO_PROPERTY_CONTENT_HEIGHT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_CONTENT_HEIGHT, FoPropertyContentHeight))
#define FO_PROPERTY_CONTENT_HEIGHT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_CONTENT_HEIGHT, FoPropertyContentHeightClass))
#define FO_IS_PROPERTY_CONTENT_HEIGHT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_CONTENT_HEIGHT))
#define FO_IS_PROPERTY_CONTENT_HEIGHT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_CONTENT_HEIGHT))
#define FO_PROPERTY_CONTENT_HEIGHT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_CONTENT_HEIGHT, FoPropertyContentHeightClass))


typedef struct _FoPropertyContentHeight      FoPropertyContentHeight;
typedef struct _FoPropertyContentHeightClass FoPropertyContentHeightClass;

GType        fo_property_content_height_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_content_height_new         (void);
FoProperty * fo_property_content_height_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_CONTENT_HEIGHT_H__ */
