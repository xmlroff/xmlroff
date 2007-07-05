/* Fo
 * fo-color-profile-private.h: Structures private to 'color-profile' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_COLOR_PROFILE_PRIVATE_H__
#define __FO_COLOR_PROFILE_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-color-profile.h>

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
