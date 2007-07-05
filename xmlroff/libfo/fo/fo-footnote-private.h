/* Fo
 * fo-footnote-private.h: Structures private to Footnote formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-fo.h>
#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-footnote.h>

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
