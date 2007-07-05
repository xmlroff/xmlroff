/* Fo
 * fo-multi-property-set-private.h: Structures private to 'multi-property-set' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-fo.h>
#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-multi-property-set.h>

struct _FoMultiPropertySet
{
  FoFo parent_instance;
  FoProperty *id;
};

struct _FoMultiPropertySetClass
{
  FoFoClass parent_class;
};
