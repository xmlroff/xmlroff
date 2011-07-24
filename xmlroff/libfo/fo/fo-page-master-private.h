/* Fo
 * fo-page-master-private.h: Structures private to abstract 'page-master' formatting object
 *
 * Copyright (C) 2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_MASTER_PRIVATE_H__
#define __FO_PAGE_MASTER_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-page-master.h"

G_BEGIN_DECLS

struct _FoPageMaster
{
  FoFo parent_instance;

  FoProperty *master_name;
};

struct _FoPageMasterClass
{
  FoFoClass parent_class;

  FoPageSequenceWalker * (* new_walker) (FoFo    *fo_fo,
					 GError **error);
};

G_END_DECLS

#endif /* !__FO_PAGE_MASTER_PRIVATE_H__ */
