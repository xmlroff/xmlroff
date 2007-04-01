/* Fo
 * fo-property-region-name.h: 'region-name' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-region-name.h,v 1.3 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_REGION_NAME_H__
#define __FO_PROPERTY_REGION_NAME_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* region-name */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* xsl-region-body | xsl-region-start | xsl-region-end | xsl-region-before | xsl-region-after | xsl-before-float-separator | xsl-footnote-separator | <name> */
/* Initial value: see prose */

#define FO_TYPE_PROPERTY_REGION_NAME              (fo_property_region_name_get_type ())
#define FO_PROPERTY_REGION_NAME(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_REGION_NAME, FoPropertyRegionName))
#define FO_PROPERTY_REGION_NAME_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_REGION_NAME, FoPropertyRegionNameClass))
#define FO_IS_PROPERTY_REGION_NAME(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_REGION_NAME))
#define FO_IS_PROPERTY_REGION_NAME_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_REGION_NAME))
#define FO_PROPERTY_REGION_NAME_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_REGION_NAME, FoPropertyRegionNameClass))


typedef struct _FoPropertyRegionName      FoPropertyRegionName;
typedef struct _FoPropertyRegionNameClass FoPropertyRegionNameClass;

GType       fo_property_region_name_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_region_name_new         (void);
FoProperty* fo_property_region_name_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_REGION_NAME_H__ */
