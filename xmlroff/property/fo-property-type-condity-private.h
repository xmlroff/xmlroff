/* Fo
 * fo-property-type-condity-private.h: Structures private to the FoPropertyTypeCondity superclass of all '.conditionality' property classes
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 *
 * $Id: fo-property-type-condity-private.h,v 1.1 2004/05/29 04:42:15 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_TYPE_CONDITY_PRIVATE_H__
#define __FO_PROPERTY_TYPE_CONDITY_PRIVATE_H__

#include "property/fo-property-type-condity.h"
#include "property/fo-property-private.h"

G_BEGIN_DECLS

struct _FoPropertyTypeCondity
{
  FoProperty parent_instance;
};

struct _FoPropertyTypeCondityClass
{
  FoPropertyClass parent_class;
};

void fo_property_type_condity_init (FoPropertyTypeCondity *property_type_condity);

G_END_DECLS

#endif /* !__FO_PROPERTY_TYPE_CONDITY_PRIVATE_H__ */
