/* Fo
 * fo-declarations-private.h: Structures private to 'declarations' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_DECLARATIONS_PRIVATE_H__
#define __FO_DECLARATIONS_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-declarations.h>

G_BEGIN_DECLS

struct _FoDeclarations
{
  FoFo parent_instance;
};

struct _FoDeclarationsClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_DECLARATIONS_PRIVATE_H__ */
