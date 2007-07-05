/* Fo
 * fo-area-table-cell-private.h: Private information for 'table-cell' area objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_CELL_PRIVATE_H__
#define __FO_AREA_TABLE_CELL_PRIVATE_H__

#include <libfo/area/fo-area-reference.h>
#include <libfo/area/fo-area-reference-private.h>

G_BEGIN_DECLS

struct _FoAreaTableCell
{
  FoAreaReference parent_instance;
};

struct _FoAreaTableCellClass
{
  FoAreaReferenceClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_TABLE_CELL_PRIVATE_H__ */
