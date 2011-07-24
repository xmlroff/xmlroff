/* Fo
 * fo-conditional-page-master-reference-private.h: Structures private to 'conditional-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CONDITIONAL_PAGE_MASTER_REFERENCE_PRIVATE_H__
#define __FO_CONDITIONAL_PAGE_MASTER_REFERENCE_PRIVATE_H__

#include "fo/fo-page-master-reference-private.h"
#include "fo/fo-conditional-page-master-reference.h"

G_BEGIN_DECLS

struct _FoConditionalPageMasterReference
{
  FoFo parent_instance;

  FoProperty *blank_or_not_blank;
  FoProperty *odd_or_even;
  FoProperty *page_position;
};

struct _FoConditionalPageMasterReferenceClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_CONDITIONAL_PAGE_MASTER_REFERENCE_PRIVATE_H__ */
