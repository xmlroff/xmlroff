/* Fo
 * fo-block-whitespace-private.h: Whitespace-only block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-block-private.h>

struct _FoBlockWhitespace
{
  FoBlock parent_instance;
};

struct _FoBlockWhitespaceClass
{
  FoBlockClass parent_class;
};
