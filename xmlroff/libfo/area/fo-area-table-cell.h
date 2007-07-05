/* Fo
 * fo-area-table-cell.c: Area object for table-cell formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_CELL_H__
#define __FO_AREA_TABLE_CELL_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTableCell      FoAreaTableCell;
typedef struct _FoAreaTableCellClass FoAreaTableCellClass;

#define FO_TYPE_AREA_TABLE_CELL              (fo_area_table_cell_get_type ())
#define FO_AREA_TABLE_CELL(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE_CELL, FoAreaTableCell))
#define FO_AREA_TABLE_CELL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE_CELL, FoAreaTableCellClass))
#define FO_IS_AREA_TABLE_CELL(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE_CELL))
#define FO_IS_AREA_TABLE_CELL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE_CELL))
#define FO_AREA_TABLE_CELL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE_CELL, FoAreaTableCellClass))


GType   fo_area_table_cell_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_table_cell_new (void);
G_END_DECLS

#endif /* !__FO_AREA_TABLE_CELL_H__ */
