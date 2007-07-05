/* Fo
 * fo-layout-gp-private.h: Object type for PangoLayoutGP
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_LAYOUT_GP_PRIVATE_H__
#define __FO_LAYOUT_GP_PRIVATE_H__

#include "fo-layout-gp.h"
#include "fo-layout-private.h"

G_BEGIN_DECLS

struct _FoLayoutGP
{
  FoLayout     parent_instance;
};

struct _FoLayoutGPClass
{
  FoLayoutClass parent_class;
};

#endif /* !__FO_LAYOUT_GP_PRIVATE_H__ */
