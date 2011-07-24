/* Fo
 * fo-simple-page-master-area.h: Generate area for 'simple-page-master' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

#ifndef __FO_SIMPLE_PAGE_MASTER_AREA_H__
#define __FO_SIMPLE_PAGE_MASTER_AREA_H__

G_BEGIN_DECLS

void fo_simple_page_master_area_new (FoFo                *fo_node,
				     FoFoAreaNew2Context *context,
				     GError             **error);

G_END_DECLS

#endif /* !__FO_SIMPLE_PAGE_MASTER_AREA_H__ */
