/* Fo
 * fo-table-area.h: Generate area for table formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-area.h,v 1.2 2003/03/19 21:12:14 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <fo-fo.h>
#include <fo-area.h>

#ifndef __FO_TABLE_AREA_H__
#define __FO_TABLE_AREA_H__

G_BEGIN_DECLS

void fo_table_area_new2 (FoFo         *fo_node,
			 FoFoAreaNew2Context *context,
			 GError **error);

G_END_DECLS

#endif /* !__FO_TABLE_AREA_H__ */
