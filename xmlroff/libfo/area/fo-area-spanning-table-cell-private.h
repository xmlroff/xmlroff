/* Fo
 * fo-area-spanning-table-cell-private.h: Private information for spanning-table-cell area objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_SPANNING_TABLE_CELL_PRIVATE_H__
#define __FO_AREA_SPANNING_TABLE_CELL_PRIVATE_H__

#include <libfo/area/fo-area-reference.h>
#include <libfo/area/fo-area-table-cell.h>
#include <libfo/area/fo-area-table-cell-private.h>

G_BEGIN_DECLS

typedef struct _FoAreaSpanningTableCellRowInfo FoAreaSpanningTableCellRowInfo;

struct _FoAreaSpanningTableCellRowInfo
{
  FoArea *row;
  gboolean fixed_bpdim;
  gboolean non_spanning_siblings;
};

struct _FoAreaSpanningTableCell
{
  FoAreaTableCell parent_instance;

  gfloat real_height;
  gfloat real_available_height;
  gint   rows_spanned;
  GList *proxies;
  FoAreaSpanningTableCellRowInfo *row_info;
};

struct _FoAreaSpanningTableCellClass
{
  FoAreaTableCellClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_SPANNING_TABLE_CELL_PRIVATE_H__ */
