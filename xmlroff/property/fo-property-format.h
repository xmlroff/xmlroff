/* Fo
 * fo-property-format.h: 'format' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-format.h,v 1.3 2003/03/21 14:41:31 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_FORMAT_H__
#define __FO_PROPERTY_FORMAT_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"

G_BEGIN_DECLS

/* format */
/* <string> */
/* Initial value: 1 */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_FORMAT              (fo_property_format_get_type ())
#define FO_PROPERTY_FORMAT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_FORMAT, FoPropertyFormat))
#define FO_PROPERTY_FORMAT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_FORMAT, FoPropertyFormatClass))
#define FO_IS_PROPERTY_FORMAT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_FORMAT))
#define FO_IS_PROPERTY_FORMAT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_FORMAT))
#define FO_PROPERTY_FORMAT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_FORMAT, FoPropertyFormatClass))


typedef struct _FoPropertyFormat      FoPropertyFormat;
typedef struct _FoPropertyFormatClass FoPropertyFormatClass;

GType       fo_property_format_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_format_new         (void);
FoProperty* fo_property_format_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_FORMAT_H__ */
