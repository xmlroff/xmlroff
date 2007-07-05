/* Fo
 * fo-single-page-master-reference-private.h: Structures private to 'single-page-master-reference' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_SINGLE_PAGE_MASTER_REFERENCE_PRIVATE_H__
#define __FO_SINGLE_PAGE_MASTER_REFERENCE_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-single-page-master-reference.h>

G_BEGIN_DECLS

struct _FoSinglePageMasterReference
{
  FoFo parent_instance;

  FoProperty *master_reference;
};

struct _FoSinglePageMasterReferenceClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_SINGLE_PAGE_MASTER_REFERENCE_PRIVATE_H__ */
