/* Fo
 * fo-static-content-private.h: Structures private to 'static-content' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_STATIC_CONTENT_PRIVATE_H__
#define __FO_STATIC_CONTENT_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-static-content.h>

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
