/* Fo
 * fo-property-content-type.h: 'content-type' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-content-type.h,v 1.4 2004/03/24 11:56:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_CONTENT_TYPE_H__
#define __FO_PROPERTY_CONTENT_TYPE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* content-type */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <string> | auto */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_CONTENT_TYPE              (fo_property_content_type_get_type ())
#define FO_PROPERTY_CONTENT_TYPE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_CONTENT_TYPE, FoPropertyContentType))
#define FO_PROPERTY_CONTENT_TYPE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_CONTENT_TYPE, FoPropertyContentTypeClass))
#define FO_IS_PROPERTY_CONTENT_TYPE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_CONTENT_TYPE))
#define FO_IS_PROPERTY_CONTENT_TYPE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_CONTENT_TYPE))
#define FO_PROPERTY_CONTENT_TYPE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_CONTENT_TYPE, FoPropertyContentTypeClass))


typedef struct _FoPropertyContentType      FoPropertyContentType;
typedef struct _FoPropertyContentTypeClass FoPropertyContentTypeClass;

GType        fo_property_content_type_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_content_type_new         (void);
FoProperty * fo_property_content_type_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_CONTENT_TYPE_H__ */
