/* Fo
 * fo-multi-toggle-private.h: Structures private to 'multi-toggle' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-multi-toggle-private.h,v 1.3 2005/08/23 11:00:32 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_MULTI_TOGGLE_PRIVATE_H__
#define __FO_MULTI_TOGGLE_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-multi-toggle.h"

G_BEGIN_DECLS

struct _FoMultiToggle
{
  FoFo parent_instance;

  FoProperty *id;
  FoProperty *role;
  FoProperty *source_document;
};

struct _FoMultiToggleClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_MULTI_TOGGLE_PRIVATE_H__ */
