/* Fo
 * fo-table-cell-area.h: Generate area for table-cell formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

#ifndef __FO_TABLE_CELL_AREA_H__
#define __FO_TABLE_CELL_AREA_H__

G_BEGIN_DECLS

void fo_table_cell_area_new2 (FoFo                *fo_node,
			      FoFoAreaNew2Context *context,
			      GError             **error);

G_END_DECLS

#endif /* !__FO_TABLE_CELL_AREA_H__ */
