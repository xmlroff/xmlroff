/* Fo
 * fo-single-page-master-reference-private.h: Structures private to 'single-page-master-reference' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-single-page-master-reference-private.h,v 1.2 2003/05/16 11:35:53 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_SINGLE_PAGE_MASTER_REFERENCE_PRIVATE_H__
#define __FO_SINGLE_PAGE_MASTER_REFERENCE_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-single-page-master-reference.h"

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
