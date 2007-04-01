/* Fo
 * fo-footnote-private.h: Structures private to Footnote formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-footnote-private.h,v 1.1.1.1 2003/02/13 00:51:17 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-footnote.h"

struct _FoFootnote
{
  FoFo parent_instance;
  FoProperty *role;
  FoProperty *source_document;
};

struct _FoFootnoteClass
{
  FoFoClass parent_class;
};
