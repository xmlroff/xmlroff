/* Fo
 * fo-block-block-private.h: Block-level block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-block-private.h,v 1.2 2003/12/05 14:36:34 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-block-private.h"
#include "fo-block-block.h"

struct _FoBlockBlock
{
  FoBlock parent_instance;
};

struct _FoBlockBlockClass
{
  FoBlockClass parent_class;
};
