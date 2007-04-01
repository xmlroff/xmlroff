/* Fo
 * fo-property-ref-id.h: 'ref-id' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-property-ref-id.h,v 1.3 2006/03/21 23:33:46 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_REF_ID_H__
#define __FO_PROPERTY_REF_ID_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* ref-id */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <idref> | inherit */
/* Initial value: none, value required */

#define FO_TYPE_PROPERTY_REF_ID              (fo_property_ref_id_get_type ())
#define FO_PROPERTY_REF_ID(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_REF_ID, FoPropertyRefId))
#define FO_PROPERTY_REF_ID_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_REF_ID, FoPropertyRefIdClass))
#define FO_IS_PROPERTY_REF_ID(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_REF_ID))
#define FO_IS_PROPERTY_REF_ID_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_REF_ID))
#define FO_PROPERTY_REF_ID_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_REF_ID, FoPropertyRefIdClass))


/**
 * FoPropertyRefId:
 *
 * Instance of the 'ref-id' property.
 **/
typedef struct _FoPropertyRefId      FoPropertyRefId;

/**
 * FoPropertyRefIdClass:
 *
 * Class structure for the 'ref-id' property.
 **/
typedef struct _FoPropertyRefIdClass FoPropertyRefIdClass;

GType        fo_property_ref_id_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_ref_id_new         (void);
FoProperty * fo_property_ref_id_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_REF_ID_H__ */
