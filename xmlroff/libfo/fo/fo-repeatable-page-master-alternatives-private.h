/* Fo
 * fo-repeatable-page-master-alternatives-private.h: Structures private to 'repeatable-page-master-alternatives' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_PRIVATE_H__
#define __FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-repeatable-page-master-alternatives.h"

G_BEGIN_DECLS

struct _FoRepeatablePageMasterAlternatives
{
  FoFo parent_instance;

  FoProperty *maximum_repeats;
};

struct _FoRepeatablePageMasterAlternativesClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_REPEATABLE_PAGE_MASTER_ALTERNATIVES_PRIVATE_H__ */
