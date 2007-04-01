/* Fo
 * fo-wrapper-block-area.h: Generate area for wrapper-block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-wrapper-block-area.h,v 1.2 2003/03/19 21:12:33 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <fo-wrapper-block.h>
#include <fo-area.h>

#ifndef __FO_WRAPPER_BLOCK_AREA_H__
#define __FO_WRAPPER_BLOCK_AREA_H__

G_BEGIN_DECLS

void fo_wrapper_block_area_new2 (FoFo                *fo_node,
				 FoFoAreaNew2Context *context,
				 GError             **error);

G_END_DECLS

#endif /* !__FO_WRAPPER_BLOCK_AREA_H__ */
