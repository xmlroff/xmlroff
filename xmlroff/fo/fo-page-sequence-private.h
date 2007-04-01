/* Fo
 * fo-page-sequence-private.h: Structures private to 'page-sequence' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-page-sequence-private.h,v 1.2 2006/04/07 11:06:57 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PAGE_SEQUENCE_PRIVATE_H__
#define __FO_PAGE_SEQUENCE_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-page-sequence.h"

G_BEGIN_DECLS

struct _FoPageSequence
{
  FoFo parent_instance;

  FoProperty *format;
  FoProperty *grouping_separator;
  FoProperty *grouping_size;
  FoProperty *id;
  FoProperty *letter_value;
  FoProperty *master_reference;

  FoFo *page_master;
  FoFo *region_body;
};

struct _FoPageSequenceClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_PRIVATE_H__ */
