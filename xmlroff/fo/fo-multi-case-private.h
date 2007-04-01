/* Fo
 * fo-multi-case-private.h: Structures private to 'multi-case' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-multi-case-private.h,v 1.2 2005/08/23 11:00:32 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_MULTI_CASE_PRIVATE_H__
#define __FO_MULTI_CASE_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-multi-case.h"

G_BEGIN_DECLS

struct _FoMultiCase
{
  FoFo parent_instance;

  FoProperty *id;
  FoProperty *role;
  FoProperty *source_document;
};

struct _FoMultiCaseClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_MULTI_CASE_PRIVATE_H__ */
