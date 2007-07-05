/* Fo
 * fo-simple-page-master-private.h: Structures private to 'simple-page-master' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_SIMPLE_PAGE_MASTER_PRIVATE_H__
#define __FO_SIMPLE_PAGE_MASTER_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-simple-page-master.h>

G_BEGIN_DECLS

struct _FoSimplePageMaster
{
  FoFo parent_instance;

  FoProperty *end_indent;
  FoProperty *margin_bottom;
  FoProperty *margin_left;
  FoProperty *margin_right;
  FoProperty *margin_top;
  FoProperty *master_name;
  FoProperty *page_height;
  FoProperty *page_width;
  FoProperty *space_after;
  FoProperty *space_before;
  FoProperty *start_indent;
  FoProperty *writing_mode;

  GHashTable *region_name_hash;
};

struct _FoSimplePageMasterClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_SIMPLE_PAGE_MASTER_PRIVATE_H__ */
