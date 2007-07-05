/* Fo
 * fo-table-header-area.h: Generate area for 'table-header' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-table-header.h>

#ifndef __FO_TABLE_HEADER_AREA_H__
#define __FO_TABLE_HEADER_AREA_H__

G_BEGIN_DECLS

void fo_table_header_area_new2 (FoFo                *fo,
				FoFoAreaNew2Context *context,
				GError             **error);

G_END_DECLS

#endif /* !__FO_TABLE_HEADER_AREA_H__ */
