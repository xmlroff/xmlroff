/* Fo
 * fo-declarations-private.h: Structures private to 'declarations' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-declarations-private.h,v 1.2 2003/05/16 12:48:20 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_DECLARATIONS_PRIVATE_H__
#define __FO_DECLARATIONS_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-declarations.h"

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
