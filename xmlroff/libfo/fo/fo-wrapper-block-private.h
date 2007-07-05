/* Fo
 * fo-wrapper-block-private.h: Block-level wrapper formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-wrapper-private.h>

struct _FoWrapperBlock
{
  FoWrapper parent_instance;
};

struct _FoWrapperBlockClass
{
  FoWrapperClass parent_class;
};
