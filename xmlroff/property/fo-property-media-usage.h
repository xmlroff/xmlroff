/* Fo
 * fo-property-media-usage.h: 'media-usage' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-property-media-usage.h,v 1.5 2006/05/28 22:48:13 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_MEDIA_USAGE_H__
#define __FO_PROPERTY_MEDIA_USAGE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* media-usage */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | paginate | bounded-in-one-dimension | unbounded */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_MEDIA_USAGE              (fo_property_media_usage_get_type ())
#define FO_PROPERTY_MEDIA_USAGE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_MEDIA_USAGE, FoPropertyMediaUsage))
#define FO_PROPERTY_MEDIA_USAGE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_MEDIA_USAGE, FoPropertyMediaUsageClass))
#define FO_IS_PROPERTY_MEDIA_USAGE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_MEDIA_USAGE))
#define FO_IS_PROPERTY_MEDIA_USAGE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_MEDIA_USAGE))
#define FO_PROPERTY_MEDIA_USAGE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_MEDIA_USAGE, FoPropertyMediaUsageClass))


/**
 * FoPropertyMediaUsage:
 *
 * Instance of the 'media-usage' property.
 **/
typedef struct _FoPropertyMediaUsage      FoPropertyMediaUsage;

/**
 * FoPropertyMediaUsageClass:
 *
 * Class structure for the 'media-usage' property.
 **/
typedef struct _FoPropertyMediaUsageClass FoPropertyMediaUsageClass;

GType        fo_property_media_usage_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_media_usage_new         (void);
FoProperty * fo_property_media_usage_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_MEDIA_USAGE_H__ */
