/* Fo
 * fo-repeatable-page-master-reference-private.h: Structures private to 'repeatable-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REPEATABLE_PAGE_MASTER_REFERENCE_PRIVATE_H__
#define __FO_REPEATABLE_PAGE_MASTER_REFERENCE_PRIVATE_H__

#include "fo/fo-page-master-reference-private.h"
#include "fo/fo-repeatable-page-master-reference.h"

G_BEGIN_DECLS

struct _FoRepeatablePageMasterReference
{
  FoPageMasterReference parent_instance;

  FoProperty *maximum_repeats;
};

struct _FoRepeatablePageMasterReferenceClass
{
  FoPageMasterReferenceClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REPEATABLE_PAGE_MASTER_REFERENCE_PRIVATE_H__ */
