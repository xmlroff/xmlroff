/* Fo
 * fo-block-layout-private.h: Layout-level block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-block-private.h>

struct _FoBlockLayout
{
  FoBlock parent_instance;
};

struct _FoBlockLayoutClass
{
  FoBlockClass parent_class;
};
