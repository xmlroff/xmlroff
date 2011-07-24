/* Fo
 * fo-page-sequence-master-private.h: Structures private to 'page-sequence-master' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_SEQUENCE_MASTER_PRIVATE_H__
#define __FO_PAGE_SEQUENCE_MASTER_PRIVATE_H__

#include "fo/fo-page-master-private.h"
#include "fo/fo-page-sequence-master.h"

G_BEGIN_DECLS

struct _FoPageSequenceMaster
{
  FoPageMaster parent_instance;
};

struct _FoPageSequenceMasterClass
{
  FoPageMasterClass parent_class;
};

G_END_DECLS

#endif /* !__FO_PAGE_SEQUENCE_MASTER_PRIVATE_H__ */
