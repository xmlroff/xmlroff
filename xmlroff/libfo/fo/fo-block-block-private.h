/* Fo
 * fo-block-block-private.h: Block-level block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-block-private.h>
#include <libfo/fo/fo-block-block.h>

struct _FoBlockBlock
{
  FoBlock parent_instance;
};

struct _FoBlockBlockClass
{
  FoBlockClass parent_class;
};
