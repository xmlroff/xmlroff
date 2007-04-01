/* Fo
 * fo-property-src.h: 'src' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-src.h,v 1.4 2005/06/13 22:19:12 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_SRC_H__
#define __FO_PROPERTY_SRC_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* src */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <uri-specification> | inherit */
/* Initial value: none, value required */

#define FO_TYPE_PROPERTY_SRC              (fo_property_src_get_type ())
#define FO_PROPERTY_SRC(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SRC, FoPropertySrc))
#define FO_PROPERTY_SRC_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SRC, FoPropertySrcClass))
#define FO_IS_PROPERTY_SRC(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SRC))
#define FO_IS_PROPERTY_SRC_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SRC))
#define FO_PROPERTY_SRC_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SRC, FoPropertySrcClass))


typedef struct _FoPropertySrc      FoPropertySrc;
typedef struct _FoPropertySrcClass FoPropertySrcClass;

GType        fo_property_src_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_src_new         (void);
FoProperty * fo_property_src_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SRC_H__ */
