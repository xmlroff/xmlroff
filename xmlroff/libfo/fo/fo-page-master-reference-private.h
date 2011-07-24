/* Fo
 * fo-page-master-reference-private.h: Structures private to abstract 'page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PAGE_MASTER_REFERENCE_PRIVATE_H__
#define __FO_PAGE_MASTER_REFERENCE_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-page-master-reference.h"

G_BEGIN_DECLS

struct _FoPageMasterReference
{
  FoFo parent_instance;

  FoProperty *master_reference;
};

struct _FoPageMasterReferenceClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_PAGE_MASTER_REFERENCE_PRIVATE_H__ */
