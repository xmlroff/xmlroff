/* Fo
 * fo-color-profile-private.h: Structures private to 'color-profile' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-color-profile-private.h,v 1.1 2003/04/15 11:43:26 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_COLOR_PROFILE_PRIVATE_H__
#define __FO_COLOR_PROFILE_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-color-profile.h"

G_BEGIN_DECLS

struct _FoColorProfile
{
  FoFo parent_instance;

  FoProperty *src;
};

struct _FoColorProfileClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_COLOR_PROFILE_PRIVATE_H__ */
