/* Fo
 * fo-property-table-layout.h: 'table-layout' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_TABLE_LAYOUT_H__
#define __FO_PROPERTY_TABLE_LAYOUT_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* table-layout */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | fixed | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_TABLE_LAYOUT              (fo_property_table_layout_get_type ())
#define FO_PROPERTY_TABLE_LAYOUT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_TABLE_LAYOUT, FoPropertyTableLayout))
#define FO_PROPERTY_TABLE_LAYOUT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_TABLE_LAYOUT, FoPropertyTableLayoutClass))
#define FO_IS_PROPERTY_TABLE_LAYOUT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_TABLE_LAYOUT))
#define FO_IS_PROPERTY_TABLE_LAYOUT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_TABLE_LAYOUT))
#define FO_PROPERTY_TABLE_LAYOUT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_TABLE_LAYOUT, FoPropertyTableLayoutClass))


typedef struct _FoPropertyTableLayout      FoPropertyTableLayout;
typedef struct _FoPropertyTableLayoutClass FoPropertyTableLayoutClass;

GType       fo_property_table_layout_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_table_layout_new         (void);
FoProperty* fo_property_table_layout_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_TABLE_LAYOUT_H__ */
