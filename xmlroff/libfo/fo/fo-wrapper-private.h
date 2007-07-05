/* Fo
 * fo-wrapper-private.h: Structures private to 'wrapper' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_WRAPPER_PRIVATE_H__
#define __FO_WRAPPER_PRIVATE_H__

#include <libfo/fo/fo-marker-parent-private.h>
#include <libfo/fo/fo-wrapper.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

struct _FoWrapper
{
  FoMarkerParent parent_instance;

  FoProperty *id;
};

struct _FoWrapperClass
{
  FoMarkerParentClass parent_class;
};

G_END_DECLS

#endif /* !__FO_WRAPPER_PRIVATE_H__ */
