/* Fo
 * fo-page-sequence-private.h: Structures private to 'page-sequence' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_SEQUENCE_PRIVATE_H__
#define __FO_PAGE_SEQUENCE_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-page-sequence.h"
#include "fo/fo-page-sequence-walker.h"

G_BEGIN_DECLS

struct _FoPageSequence
{
  FoFo parent_instance;

  FoProperty *country;
  FoProperty *force_page_count;
  FoProperty *format;
  FoProperty *grouping_separator;
  FoProperty *grouping_size;
  FoProperty *id;
  FoProperty *initial_page_number;
  FoProperty *language;
  FoProperty *letter_value;
  FoProperty *master_reference;

  FoFo *page_master;
  FoFo *region_body;
  FoPageSequenceWalker *walker;
};

struct _FoPageSequenceClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_PRIVATE_H__ */
