/* Fo
 * fo-conditional-page-master-reference-private.h: Structures private to 'conditional-page-master-reference' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_CONDITIONAL_PAGE_MASTER_REFERENCE_PRIVATE_H__
#define __FO_CONDITIONAL_PAGE_MASTER_REFERENCE_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-conditional-page-master-reference.h>

G_BEGIN_DECLS

struct _FoConditionalPageMasterReference
{
  FoFo parent_instance;

  FoProperty *master_reference;
};

struct _FoConditionalPageMasterReferenceClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_CONDITIONAL_PAGE_MASTER_REFERENCE_PRIVATE_H__ */
