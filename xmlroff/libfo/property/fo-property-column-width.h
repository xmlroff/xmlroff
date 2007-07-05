/* Fo
 * fo-property-column-width.h: 'column-width' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_COLUMN_WIDTH_H__
#define __FO_PROPERTY_COLUMN_WIDTH_H__

#include <libfo/fo-utils.h>
#include "fo-context.h"

G_BEGIN_DECLS

/* column-width */
/* <length> | <percentage> */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_COLUMN_WIDTH              (fo_property_column_width_get_type ())
#define FO_PROPERTY_COLUMN_WIDTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_COLUMN_WIDTH, FoPropertyColumnWidth))
#define FO_PROPERTY_COLUMN_WIDTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_COLUMN_WIDTH, FoPropertyColumnWidthClass))
#define FO_IS_PROPERTY_COLUMN_WIDTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_COLUMN_WIDTH))
#define FO_IS_PROPERTY_COLUMN_WIDTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_COLUMN_WIDTH))
#define FO_PROPERTY_COLUMN_WIDTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_COLUMN_WIDTH, FoPropertyColumnWidthClass))


typedef struct _FoPropertyColumnWidth      FoPropertyColumnWidth;
typedef struct _FoPropertyColumnWidthClass FoPropertyColumnWidthClass;

GType       fo_property_column_width_get_type      (void) G_GNUC_CONST;
FoProperty* fo_property_column_width_new           (void);
FoProperty* fo_property_column_width_get_initial (void);
FoDatatype* fo_property_column_width_resolve_percent (gdouble           percentage,
						      const FoDatatype *font_size,
						      const FoFo       *fo_node,
						      const FoContext  *context,
						      GError          **error);

G_END_DECLS

#endif /* !__FO_PROPERTY_COLUMN_WIDTH_H__ */
