/* Fo
 * fo-area-table-part-private.h: Private information for 'table-part' area objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_TABLE_PART_PRIVATE_H__
#define __FO_AREA_TABLE_PART_PRIVATE_H__

#include <libfo/area/fo-area-area.h>
#include <libfo/area/fo-area-area-private.h>

G_BEGIN_DECLS

struct _FoAreaTablePart
{
  FoAreaArea parent_instance;
};

struct _FoAreaTablePartClass
{
  FoAreaAreaClass parent_class;
};

G_END_DECLS

#endif /* !__FO_AREA_TABLE_PART_PRIVATE_H__ */
