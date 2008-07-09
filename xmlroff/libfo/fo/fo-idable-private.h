/* Fo
 * fo-idable-private.h: Formatting object that is parent of possible fo:marker
 *
 * Copyright (C) 2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-idable.h>
#include <libfo/property/fo-property.h>

struct _FoIdable
{
  FoFo parent_instance;

  FoProperty *id;
};

struct _FoIdableClass
{
  FoFoClass parent_class;
};
