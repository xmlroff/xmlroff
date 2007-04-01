/* Fo
 * fo-block-block-area.h: Generate area for block-block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-block-area.h,v 1.2 2003/03/19 21:10:41 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <fo-block-block.h>
#include <fo-area.h>

#ifndef __FO_BLOCK_BLOCK_AREA_H__
#define __FO_BLOCK_BLOCK_AREA_H__

G_BEGIN_DECLS

void fo_block_block_area_new2 (FoFo         *fo_node,
			       FoFoAreaNew2Context *context,
			       GError **error);

G_END_DECLS

#endif /* !__FO_BLOCK_BLOCK_AREA_H__ */
