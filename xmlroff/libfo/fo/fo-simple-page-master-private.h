/* Fo
 * fo-simple-page-master-private.h: Structures private to 'simple-page-master' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_SIMPLE_PAGE_MASTER_PRIVATE_H__
#define __FO_SIMPLE_PAGE_MASTER_PRIVATE_H__

#include "fo/fo-page-master-private.h"
#include "fo/fo-simple-page-master.h"
#include "area/fo-area.h"

G_BEGIN_DECLS

struct _FoSimplePageMaster
{
  FoPageMaster parent_instance;

  FoFo *region_body;
  FoFo *region_before;
  FoFo *region_after;
  FoFo *region_start;
  FoFo *region_end;

  FoProperty *end_indent;
  FoProperty *margin_bottom;
  FoProperty *margin_left;
  FoProperty *margin_right;
  FoProperty *margin_top;
  FoProperty *page_height;
  FoProperty *page_width;
  FoProperty *reference_orientation;
  FoProperty *space_after;
  FoProperty *space_before;
  FoProperty *start_indent;
  FoProperty *writing_mode;

  GHashTable *region_name_hash;

  FoArea *area;
};

struct _FoSimplePageMasterClass
{
  FoPageMasterClass parent_class;
};

G_END_DECLS

#endif /* !__FO_SIMPLE_PAGE_MASTER_PRIVATE_H__ */
