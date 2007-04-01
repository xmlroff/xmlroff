/* Fo
 * fo-property-role.h: 'role' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 *
 * $Id: fo-property-role.h,v 1.4 2005/08/14 19:31:56 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_ROLE_H__
#define __FO_PROPERTY_ROLE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* role */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <string> | <uri-specification> | none | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_ROLE              (fo_property_role_get_type ())
#define FO_PROPERTY_ROLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_ROLE, FoPropertyRole))
#define FO_PROPERTY_ROLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_ROLE, FoPropertyRoleClass))
#define FO_IS_PROPERTY_ROLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_ROLE))
#define FO_IS_PROPERTY_ROLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_ROLE))
#define FO_PROPERTY_ROLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_ROLE, FoPropertyRoleClass))


typedef struct _FoPropertyRole      FoPropertyRole;
typedef struct _FoPropertyRoleClass FoPropertyRoleClass;

GType        fo_property_role_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_role_new         (void);
FoProperty * fo_property_role_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_ROLE_H__ */
