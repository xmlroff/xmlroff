/* Fo
 * fo-image.h: Boxed object type for GDK image
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-image.h,v 1.2 2005/09/11 22:15:36 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_IMAGE_H__
#define __FO_IMAGE_H__

#include <libfo/fo-utils.h>
#include "fo-object.h"
#include "datatype/fo-datatype.h"

G_BEGIN_DECLS

#define FO_TYPE_IMAGE              (fo_image_get_type ())
#define FO_IMAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_IMAGE, FoImage))
#define FO_IMAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_IMAGE, FoImageClass))
#define FO_IS_IMAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_IMAGE))
#define FO_IS_IMAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_IMAGE))
#define FO_IMAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_IMAGE, FoImageClass))

typedef struct _FoImage      FoImage;
typedef struct _FoImageClass FoImageClass;

#define FO_TYPE_IMAGE             (fo_image_get_type ())
#define FO_IS_IMAGE(object)       (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_IMAGE))

GType     fo_image_get_type       (void);
FoImage * fo_image_new            (void);
FoImage * fo_image_new_from_uri   (const gchar   *uri,
				   const gchar   *base);

const gchar * fo_image_get_uri    (FoImage       *fo_image);
FoDatatype *  fo_image_get_width  (const FoImage *fo_image);
FoDatatype *  fo_image_get_height (const FoImage *fo_image);

G_END_DECLS

#endif /* !__FO_IMAGE_H__ */
