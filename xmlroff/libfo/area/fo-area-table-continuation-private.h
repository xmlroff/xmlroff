/* Fo
 * fo-area-table-continuation-private.h: Private information for non-standard
 *                                       'table-continuation' area objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_CONTINUATION_PRIVATE_H__
#define __FO_AREA_TABLE_CONTINUATION_PRIVATE_H__

#include <libfo/area/fo-area-table.h>
#include <libfo/area/fo-area-table-private.h>

G_BEGIN_DECLS

struct _FoAreaTableContinuation
{
  FoAreaTable parent_instance;

  FoArea *table;
  FoArea *table_header;
};

struct _FoAreaTableContinuationClass
{
  FoAreaTableClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_TABLE_CONTINUATION_PRIVATE_H__ */
