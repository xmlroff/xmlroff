/* Fo
 * fo-area-table-cell-proxy.c: Area object for table-cell-proxy formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
  * Copyright (C) 2007 Menteith Consulting Ltd
*
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_CELL_PROXY_H__
#define __FO_AREA_TABLE_CELL_PROXY_H__

#include <libfo/fo-utils.h>
#include <libfo/area/fo-area-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTableCellProxy      FoAreaTableCellProxy;
typedef struct _FoAreaTableCellProxyClass FoAreaTableCellProxyClass;

#define FO_TYPE_AREA_TABLE_CELL_PROXY              (fo_area_table_cell_proxy_get_type ())
#define FO_AREA_TABLE_CELL_PROXY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TABLE_CELL_PROXY, FoAreaTableCellProxy))
#define FO_AREA_TABLE_CELL_PROXY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TABLE_CELL_PROXY, FoAreaTableCellProxyClass))
#define FO_IS_AREA_TABLE_CELL_PROXY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TABLE_CELL_PROXY))
#define FO_IS_AREA_TABLE_CELL_PROXY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TABLE_CELL_PROXY))
#define FO_AREA_TABLE_CELL_PROXY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TABLE_CELL_PROXY, FoAreaTableCellProxyClass))


GType   fo_area_table_cell_proxy_get_type      (void) G_GNUC_CONST;
FoArea* fo_area_table_cell_proxy_new (void);

void    fo_area_table_cell_proxy_set_table_cell (FoArea *fo_area,
						 FoArea *new_table_cell);
FoArea* fo_area_table_cell_proxy_get_table_cell (FoArea *fo_area);
void    fo_area_table_cell_proxy_set_row_number (FoArea *fo_area,
						 gint    new_row_number);
gint    fo_area_table_cell_proxy_get_row_number (FoArea *fo_area);
void    fo_area_table_cell_proxy_set_min_height (FoArea *fo_area,
						 gfloat  new_min_height);
gfloat  fo_area_table_cell_proxy_get_min_height (FoArea *fo_area);

G_END_DECLS

#endif /* !__FO_AREA_TABLE_CELL_PROXY_H__ */
