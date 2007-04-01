/* Fo
 * fo-property-background-image.h: 'background-image' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-background-image.h,v 1.4 2004/03/23 11:59:22 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BACKGROUND_IMAGE_H__
#define __FO_PROPERTY_BACKGROUND_IMAGE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* background-image */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <uri-specification> | none | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_BACKGROUND_IMAGE              (fo_property_background_image_get_type ())
#define FO_PROPERTY_BACKGROUND_IMAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BACKGROUND_IMAGE, FoPropertyBackgroundImage))
#define FO_PROPERTY_BACKGROUND_IMAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BACKGROUND_IMAGE, FoPropertyBackgroundImageClass))
#define FO_IS_PROPERTY_BACKGROUND_IMAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BACKGROUND_IMAGE))
#define FO_IS_PROPERTY_BACKGROUND_IMAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BACKGROUND_IMAGE))
#define FO_PROPERTY_BACKGROUND_IMAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BACKGROUND_IMAGE, FoPropertyBackgroundImageClass))


typedef struct _FoPropertyBackgroundImage      FoPropertyBackgroundImage;
typedef struct _FoPropertyBackgroundImageClass FoPropertyBackgroundImageClass;

GType       fo_property_background_image_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_background_image_new         (void);
FoProperty* fo_property_background_image_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BACKGROUND_IMAGE_H__ */
