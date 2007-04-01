/* Fo
 * fo-property-master-reference.h: 'master-reference' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-master-reference.h,v 1.3 2003/05/16 11:35:53 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_MASTER_REFERENCE_H__
#define __FO_PROPERTY_MASTER_REFERENCE_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* master-reference */
/* <name> */
/* Initial value: an empty name */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_MASTER_REFERENCE              (fo_property_master_reference_get_type ())
#define FO_PROPERTY_MASTER_REFERENCE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_MASTER_REFERENCE, FoPropertyMasterReference))
#define FO_PROPERTY_MASTER_REFERENCE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_MASTER_REFERENCE, FoPropertyMasterReferenceClass))
#define FO_IS_PROPERTY_MASTER_REFERENCE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_MASTER_REFERENCE))
#define FO_IS_PROPERTY_MASTER_REFERENCE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_MASTER_REFERENCE))
#define FO_PROPERTY_MASTER_REFERENCE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_MASTER_REFERENCE, FoPropertyMasterReferenceClass))


typedef struct _FoPropertyMasterReference      FoPropertyMasterReference;
typedef struct _FoPropertyMasterReferenceClass FoPropertyMasterReferenceClass;

GType       fo_property_master_reference_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_master_reference_new         (void);
FoProperty* fo_property_master_reference_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_MASTER_REFERENCE_H__ */
