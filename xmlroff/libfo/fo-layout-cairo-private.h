/* Fo
 * fo-layout-cairo-private.h: Object type for PangoLayoutCairo
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-layout-cairo-private.h,v 1.1 2006/03/07 23:35:29 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_LAYOUT_CAIRO_PRIVATE_H__
#define __FO_LAYOUT_CAIRO_PRIVATE_H__

#include "fo-layout-cairo.h"
#include "fo-layout-private.h"

G_BEGIN_DECLS

struct _FoLayoutCairo
{
  FoLayout     parent_instance;
};

struct _FoLayoutCairoClass
{
  FoLayoutClass parent_class;
};

#endif /* !__FO_LAYOUT_CAIRO_PRIVATE_H__ */
