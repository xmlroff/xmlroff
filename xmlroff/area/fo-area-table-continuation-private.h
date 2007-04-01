/* Fo
 * fo-area-table-continuation-private.h: Private information for non-standard
 *                                       'table-continuation' area objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-continuation-private.h,v 1.1.1.1 2003/02/13 00:51:17 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_AREA_TABLE_CONTINUATION_PRIVATE_H__
#define __FO_AREA_TABLE_CONTINUATION_PRIVATE_H__

#include <fo-area-table.h>
#include "fo-area-table-private.h"

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
