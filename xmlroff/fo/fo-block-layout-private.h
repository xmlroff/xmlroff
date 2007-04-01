/* Fo
 * fo-block-layout-private.h: Layout-level block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-layout-private.h,v 1.1.1.1 2003/02/13 00:51:16 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-block-private.h"

struct _FoBlockLayout
{
  FoBlock parent_instance;
};

struct _FoBlockLayoutClass
{
  FoBlockClass parent_class;
};
