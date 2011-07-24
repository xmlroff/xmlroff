/* Fo
 * fo-single-page-master-reference-private.h: Structures private to 'single-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_SINGLE_PAGE_MASTER_REFERENCE_PRIVATE_H__
#define __FO_SINGLE_PAGE_MASTER_REFERENCE_PRIVATE_H__

#include "fo/fo-page-master-reference-private.h"
#include "fo/fo-single-page-master-reference.h"

G_BEGIN_DECLS

struct _FoSinglePageMasterReference
{
  FoPageMasterReference parent_instance;
};

struct _FoSinglePageMasterReferenceClass
{
  FoPageMasterReferenceClass parent_class;
};

G_END_DECLS

#endif /* !__FO_SINGLE_PAGE_MASTER_REFERENCE_PRIVATE_H__ */
