/* Fo
 * fo-enum-factory-private.h: Structures private to the base class for objects
 *                    that are nodes in a tree.
 *
 * Copyright (C) 2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ENUM_FACTORY_PRIVATE_H__
#define __FO_ENUM_FACTORY_PRIVATE_H__

#include "fo-object.h"
#include "fo-enum-factory.h"

G_BEGIN_DECLS

struct _FoEnumFactory
{
  FoObject parent_instance;

  FoDatatype *enums[FO_ENUM_ENUM_LIMIT];

};

struct _FoEnumFactoryClass
{
  FoObjectClass parent_class;
};

G_END_DECLS

#endif /* !__FO_ENUM_FACTORY_PRIVATE_H__ */
