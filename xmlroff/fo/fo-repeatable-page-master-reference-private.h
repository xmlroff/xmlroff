/* Fo
 * fo-repeatable-page-master-reference-private.h: Structures private to 'repeatable-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-repeatable-page-master-reference-private.h,v 1.2 2005/08/23 11:00:32 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_REPEATABLE_PAGE_MASTER_REFERENCE_PRIVATE_H__
#define __FO_REPEATABLE_PAGE_MASTER_REFERENCE_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-repeatable-page-master-reference.h"

G_BEGIN_DECLS

struct _FoRepeatablePageMasterReference
{
  FoFo parent_instance;

  FoProperty *master_reference;
};

struct _FoRepeatablePageMasterReferenceClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REPEATABLE_PAGE_MASTER_REFERENCE_PRIVATE_H__ */
