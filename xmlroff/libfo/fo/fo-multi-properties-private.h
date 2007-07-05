/* Fo
 * fo-multi-properties-private.h: Structures private to 'multi-properties' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_MULTI_PROPERTIES_PRIVATE_H__
#define __FO_MULTI_PROPERTIES_PRIVATE_H__

#include <libfo/fo/fo-fo-private.h>
#include <libfo/fo/fo-multi-properties.h>

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
