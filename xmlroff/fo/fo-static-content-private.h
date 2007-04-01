/* Fo
 * fo-static-content-private.h: Structures private to 'static-content' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-static-content-private.h,v 1.2 2003/04/15 12:05:36 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_STATIC_CONTENT_PRIVATE_H__
#define __FO_STATIC_CONTENT_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-static-content.h"

G_BEGIN_DECLS

struct _FoStaticContent
{
  FoFo parent_instance;

  FoProperty *flow_name;
};

struct _FoStaticContentClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_STATIC_CONTENT_PRIVATE_H__ */
