/* Fo
 * fo-multi-case-private.h: Structures private to 'multi-case' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_MULTI_CASE_PRIVATE_H__
#define __FO_MULTI_CASE_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-multi-case.h>

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
