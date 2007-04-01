/* Fo
 * fo-property-grouping-separator.h: 'grouping-separator' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-grouping-separator.h,v 1.3 2003/06/30 13:10:33 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_GROUPING_SEPARATOR_H__
#define __FO_PROPERTY_GROUPING_SEPARATOR_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* grouping-separator */
/* <character> */
/* Initial value: no separator */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_GROUPING_SEPARATOR              (fo_property_grouping_separator_get_type ())
#define FO_PROPERTY_GROUPING_SEPARATOR(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_GROUPING_SEPARATOR, FoPropertyGroupingSeparator))
#define FO_PROPERTY_GROUPING_SEPARATOR_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_GROUPING_SEPARATOR, FoPropertyGroupingSeparatorClass))
#define FO_IS_PROPERTY_GROUPING_SEPARATOR(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_GROUPING_SEPARATOR))
#define FO_IS_PROPERTY_GROUPING_SEPARATOR_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_GROUPING_SEPARATOR))
#define FO_PROPERTY_GROUPING_SEPARATOR_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_GROUPING_SEPARATOR, FoPropertyGroupingSeparatorClass))


typedef struct _FoPropertyGroupingSeparator      FoPropertyGroupingSeparator;
typedef struct _FoPropertyGroupingSeparatorClass FoPropertyGroupingSeparatorClass;

GType       fo_property_grouping_separator_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_grouping_separator_new         (void);
FoProperty* fo_property_grouping_separator_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_GROUPING_SEPARATOR_H__ */
