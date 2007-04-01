/* Fo
 * fo-multi-properties-private.h: Structures private to 'multi-properties' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-multi-properties-private.h,v 1.2 2005/02/28 11:51:56 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_MULTI_PROPERTIES_PRIVATE_H__
#define __FO_MULTI_PROPERTIES_PRIVATE_H__

#include "fo/fo-fo-private.h"
#include "fo/fo-multi-properties.h"

G_BEGIN_DECLS

struct _FoMultiProperties
{
  FoFo parent_instance;

  FoProperty *id;
  FoProperty *role;
  FoProperty *source_document;
};

struct _FoMultiPropertiesClass
{
  FoFoClass parent_class;
};

G_END_DECLS

#endif /* !__FO_MULTI_PROPERTIES_PRIVATE_H__ */
