/* Fo
 * fo-area-table-header.c: Area object for table-header formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_HEADER_H__
#define __FO_AREA_TABLE_HEADER_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTableHeader      FoAreaTableHeader;
typedef struct _FoAreaTableHeaderClass FoAreaTableHeaderClass;

#define FO_TYPE_AREA_TABLE_HEADER              (fo_area_table_header_get_type ())
#define FO_AREA_TABLE_HEADER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE_HEADER, FoAreaTableHeader))
#define FO_AREA_TABLE_HEADER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE_HEADER, FoAreaTableHeaderClass))
#define FO_IS_AREA_TABLE_HEADER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE_HEADER))
#define FO_IS_AREA_TABLE_HEADER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE_HEADER))
#define FO_AREA_TABLE_HEADER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE_HEADER, FoAreaTableHeaderClass))


GType   fo_area_table_header_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_table_header_new (void);

G_END_DECLS

#endif /* !__FO_AREA_TABLE_HEADER_H__ */
