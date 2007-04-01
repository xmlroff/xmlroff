/* Fo
 * fo-wrapper-whitespace-private.h: Whitespace-only wrapper formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-wrapper-whitespace-private.h,v 1.1.1.1 2003/02/13 00:51:17 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-wrapper-private.h"

struct _FoWrapperWhitespace
{
  FoWrapper parent_instance;
};

struct _FoWrapperWhitespaceClass
{
  FoWrapperClass parent_class;
};
