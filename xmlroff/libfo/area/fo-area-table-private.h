/* Fo
 * fo-area-table-private.h: Private information for 'table' area objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_PRIVATE_H__
#define __FO_AREA_TABLE_PRIVATE_H__

#include "area/fo-area-table.h"
#include "area/fo-area-reference-private.h"

G_BEGIN_DECLS

struct _FoAreaTable
{
  FoAreaReference parent_instance;
};

struct _FoAreaTableClass
{
  FoAreaReferenceClass parent_class;
};

G_END_DECLS

FoArea* fo_area_table_get_header (FoArea *table);

#endif /* !__FO_AREA_TABLE_PRIVATE_H__ */
