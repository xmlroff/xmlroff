/* Fo
 * fo-property-border-private.h: Structures private to common border property definitions
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_PRIVATE_H__
#define __FO_PROPERTY_BORDER_PRIVATE_H__

#include <fo-property-private.h>
#include <fo-property-border.h>

G_BEGIN_DECLS

struct _FoPropertyBorder
{
  FoProperty parent_instance;
};

struct _FoPropertyBorderClass
{
  FoPropertyClass parent_class;
};

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_PRIVATE_H__ */
