/* Fo
 * fo-repeatable-page-master-alternatives-private.h: Structures private to 'repeatable-page-master-alternatives' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-repeatable-page-master-alternatives-private.h,v 1.1 2005/11/04 14:19:52 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_PRIVATE_H__
#define __FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-repeatable-page-master-alternatives.h"

G_BEGIN_DECLS

struct _FoRepeatablePageMasterAlternatives
{
  FoFo parent_instance;
};

struct _FoRepeatablePageMasterAlternativesClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_PRIVATE_H__ */
