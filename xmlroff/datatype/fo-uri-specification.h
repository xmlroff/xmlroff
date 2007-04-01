/* Fo
 * fo-uri-specification.h: Uri Specification datatype
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-uri-specification.h,v 1.4 2005/06/27 00:21:14 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_URI_SPECIFICATION_H__
#define __FO_URI_SPECIFICATION_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_URI_SPECIFICATION              (fo_uri_specification_get_type ())
#define FO_URI_SPECIFICATION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_URI_SPECIFICATION, FoUriSpecification))
#define FO_URI_SPECIFICATION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_URI_SPECIFICATION, FoUriSpecificationClass))
#define FO_IS_URI_SPECIFICATION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_URI_SPECIFICATION))
#define FO_IS_URI_SPECIFICATION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_URI_SPECIFICATION))
#define FO_URI_SPECIFICATION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_URI_SPECIFICATION, FoUriSpecificationClass))


typedef struct _FoUriSpecification      FoUriSpecification;
typedef struct _FoUriSpecificationClass FoUriSpecificationClass;

GType       fo_uri_specification_get_type       (void) G_GNUC_CONST;
FoDatatype *fo_uri_specification_new_with_value (const gchar* new_value);

gchar* fo_uri_specification_get_value (FoDatatype  *uri_specification);

G_END_DECLS

#endif /* !__FO_URI_SPECIFICATION_H__ */
