/* Fo
 * fo-multi-property-set-private.h: Structures private to 'multi-property-set' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-multi-property-set-private.h,v 1.1.1.1 2003/02/13 00:51:17 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-multi-property-set.h"

struct _FoMultiPropertySet
{
  FoFo parent_instance;
  FoProperty *id;
};

struct _FoMultiPropertySetClass
{
  FoFoClass parent_class;
};
