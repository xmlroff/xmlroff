/* Fo
 * fo-property-height.h: 'height' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_HEIGHT_H__
#define __FO_PROPERTY_HEIGHT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* height */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <length> | <percentage> | auto | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_HEIGHT              (fo_property_height_get_type ())
#define FO_PROPERTY_HEIGHT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_HEIGHT, FoPropertyHeight))
#define FO_PROPERTY_HEIGHT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_HEIGHT, FoPropertyHeightClass))
#define FO_IS_PROPERTY_HEIGHT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_HEIGHT))
#define FO_IS_PROPERTY_HEIGHT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_HEIGHT))
#define FO_PROPERTY_HEIGHT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_HEIGHT, FoPropertyHeightClass))


/**
 * FoPropertyHeight:
 *
 * Instance of the 'height' property.
 **/
typedef struct _FoPropertyHeight      FoPropertyHeight;

/**
 * FoPropertyHeightClass:
 *
 * Class structure for the 'height' property.
 **/
typedef struct _FoPropertyHeightClass FoPropertyHeightClass;

GType        fo_property_height_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_height_new         (void);
FoProperty * fo_property_height_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_HEIGHT_H__ */
