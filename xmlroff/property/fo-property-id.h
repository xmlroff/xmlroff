/* Fo
 * fo-property-id.h: 'id' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-property-id.h,v 1.3 2006/03/21 23:13:51 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_ID_H__
#define __FO_PROPERTY_ID_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* id */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <id> */
/* Initial value: see prose */

#define FO_TYPE_PROPERTY_ID              (fo_property_id_get_type ())
#define FO_PROPERTY_ID(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_ID, FoPropertyId))
#define FO_PROPERTY_ID_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_ID, FoPropertyIdClass))
#define FO_IS_PROPERTY_ID(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_ID))
#define FO_IS_PROPERTY_ID_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_ID))
#define FO_PROPERTY_ID_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_ID, FoPropertyIdClass))


/**
 * FoPropertyId:
 *
 * Instance of the 'id' property.
 **/
typedef struct _FoPropertyId      FoPropertyId;

/**
 * FoPropertyIdClass:
 *
 * Class structure for the 'id' property.
 **/
typedef struct _FoPropertyIdClass FoPropertyIdClass;

GType        fo_property_id_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_id_new         (void);
FoProperty * fo_property_id_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_ID_H__ */
