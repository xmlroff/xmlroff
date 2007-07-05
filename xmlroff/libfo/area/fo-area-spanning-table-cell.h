/* Fo
 * fo-area-spanning-table-cell.c: Area object for spanning-table-cell formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_SPANNING_TABLE_CELL_H__
#define __FO_AREA_SPANNING_TABLE_CELL_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaSpanningTableCell      FoAreaSpanningTableCell;
typedef struct _FoAreaSpanningTableCellClass FoAreaSpanningTableCellClass;

#define FO_TYPE_AREA_SPANNING_TABLE_CELL              (fo_area_spanning_table_cell_get_type ())
#define FO_AREA_SPANNING_TABLE_CELL(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_SPANNING_TABLE_CELL, FoAreaSpanningTableCell))
#define FO_AREA_SPANNING_TABLE_CELL_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_SPANNING_TABLE_CELL, FoAreaSpanningTableCellClass))
#define FO_IS_AREA_SPANNING_TABLE_CELL(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_SPANNING_TABLE_CELL))
#define FO_IS_AREA_SPANNING_TABLE_CELL_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_SPANNING_TABLE_CELL))
#define FO_AREA_SPANNING_TABLE_CELL_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_SPANNING_TABLE_CELL, FoAreaSpanningTableCellClass))


GType   fo_area_spanning_table_cell_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_spanning_table_cell_new (void);
FoArea* fo_area_spanning_table_cell_new_with_rows_spanned (gint rows_spanned);

FoArea* fo_area_spanning_table_cell_get_nth_row_proxy (FoArea *fo_area,
						       gint    row_number);
gfloat  fo_area_spanning_table_cell_get_real_height   (FoArea *fo_area);
gfloat  fo_area_spanning_table_cell_get_real_available_height (FoArea *fo_area);
G_END_DECLS

#endif /* !__FO_AREA_SPANNING_TABLE_CELL_H__ */
