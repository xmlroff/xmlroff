/* Fo
 * fo-multi-switch-private.h: Structures private to 'multi-switch' formatting object
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-multi-switch-private.h,v 1.2 2005/08/18 09:48:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_MULTI_SWITCH_PRIVATE_H__
#define __FO_MULTI_SWITCH_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-multi-switch.h"

G_BEGIN_DECLS

struct _FoMultiSwitch
{
  FoFo parent_instance;

  FoProperty *id;
  FoProperty *role;
  FoProperty *source_document;
};

struct _FoMultiSwitchClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_MULTI_SWITCH_PRIVATE_H__ */
