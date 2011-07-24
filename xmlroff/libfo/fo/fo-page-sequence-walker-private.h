/* Fo
 * fo-page-sequence-walker.c: Walker for a page sequence
 *
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_SEQUENCE_WALKER_PRIVATE_H__
#define __FO_PAGE_SEQUENCE_WALKER_PRIVATE_H__

#include "fo-page-sequence-walker.h"
#include "fo-page-master.h"

G_BEGIN_DECLS

struct _FoPageSequenceWalker
{
  FoObject parent_instance;

  FoPageSequence *page_sequence;
  FoPageMaster   *page_master;
};

struct _FoPageSequenceWalkerClass
{
  FoObjectClass parent_class;

  FoFo * (* next_page_master) (FoPageSequenceWalker *walker,
			       GError              **error);
  FoFo * (* end_page_masters) (FoPageSequenceWalker *walker,
			       GError              **error);

};

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_WALKER_PRIVATE_H__ */
