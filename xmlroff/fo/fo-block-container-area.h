/* Fo
 * fo-block-container-area.h: Generate area for block-container formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-container-area.h,v 1.1 2003/12/05 17:08:02 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <fo-block-container.h>

#ifndef __FO_BLOCK_CONTAINER_AREA_H__
#define __FO_BLOCK_CONTAINER_AREA_H__

G_BEGIN_DECLS

void fo_block_container_area_new2 (FoFo         *fo_node,
				   FoFoAreaNew2Context *context,
				   GError **error);

G_END_DECLS

#endif /* !__FO_BLOCK_CONTAINER_AREA_H__ */
