/* Fo
 * fo-area-table-private.h: Private information for 'table' area objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-private.h,v 1.1.1.1 2003/02/13 00:51:17 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_AREA_TABLE_PRIVATE_H__
#define __FO_AREA_TABLE_PRIVATE_H__

#include <fo-area-reference.h>
#include "fo-area-reference-private.h"

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
