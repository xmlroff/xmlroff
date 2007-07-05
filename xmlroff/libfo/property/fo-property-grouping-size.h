/* Fo
 * fo-property-grouping-size.h: 'grouping-size' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_GROUPING_SIZE_H__
#define __FO_PROPERTY_GROUPING_SIZE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* grouping-size */
/* <number> */
/* Initial value: no grouping */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_GROUPING_SIZE              (fo_property_grouping_size_get_type ())
#define FO_PROPERTY_GROUPING_SIZE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_GROUPING_SIZE, FoPropertyGroupingSize))
#define FO_PROPERTY_GROUPING_SIZE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_GROUPING_SIZE, FoPropertyGroupingSizeClass))
#define FO_IS_PROPERTY_GROUPING_SIZE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_GROUPING_SIZE))
#define FO_IS_PROPERTY_GROUPING_SIZE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_GROUPING_SIZE))
#define FO_PROPERTY_GROUPING_SIZE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_GROUPING_SIZE, FoPropertyGroupingSizeClass))


typedef struct _FoPropertyGroupingSize      FoPropertyGroupingSize;
typedef struct _FoPropertyGroupingSizeClass FoPropertyGroupingSizeClass;

GType       fo_property_grouping_size_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_grouping_size_new         (void);
FoProperty* fo_property_grouping_size_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_GROUPING_SIZE_H__ */
