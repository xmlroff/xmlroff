/* Fo
 * fo-block-whitespace-private.h: Whitespace-only block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-whitespace-private.h,v 1.1.1.1 2003/02/13 00:51:16 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-block-private.h"

struct _FoBlockWhitespace
{
  FoBlock parent_instance;
};

struct _FoBlockWhitespaceClass
{
  FoBlockClass parent_class;
};
