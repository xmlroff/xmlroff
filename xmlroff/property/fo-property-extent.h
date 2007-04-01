/* Fo
 * fo-property-extent.h: 'extent' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-extent.h,v 1.3 2006/01/16 11:54:45 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_EXTENT_H__
#define __FO_PROPERTY_EXTENT_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* extent */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <length> | <percentage> | inherit */
/* Initial value: 0.0pt */

#define FO_TYPE_PROPERTY_EXTENT              (fo_property_extent_get_type ())
#define FO_PROPERTY_EXTENT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_EXTENT, FoPropertyExtent))
#define FO_PROPERTY_EXTENT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_EXTENT, FoPropertyExtentClass))
#define FO_IS_PROPERTY_EXTENT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_EXTENT))
#define FO_IS_PROPERTY_EXTENT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_EXTENT))
#define FO_PROPERTY_EXTENT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_EXTENT, FoPropertyExtentClass))


/**
 * FoPropertyExtent:
 *
 * Instance of the 'extent' property.
 **/
typedef struct _FoPropertyExtent      FoPropertyExtent;

/**
 * FoPropertyExtentClass:
 *
 * Class structure for the 'extent' property.
 **/
typedef struct _FoPropertyExtentClass FoPropertyExtentClass;

GType        fo_property_extent_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_extent_new         (void);
FoProperty * fo_property_extent_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_EXTENT_H__ */
