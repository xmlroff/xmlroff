/* Fo
 * fo-property-border-separation.h: 'border-separation' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-border-separation.h,v 1.3 2003/07/02 10:39:38 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_BORDER_SEPARATION_H__
#define __FO_PROPERTY_BORDER_SEPARATION_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* border-separation */
/* <length-bp-ip-direction> | inherit */
/* Initial value: .block-progression-direction="0pt" .inline-progression-direction="0pt" */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_BORDER_SEPARATION              (fo_property_border_separation_get_type ())
#define FO_PROPERTY_BORDER_SEPARATION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_BORDER_SEPARATION, FoPropertyBorderSeparation))
#define FO_PROPERTY_BORDER_SEPARATION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_BORDER_SEPARATION, FoPropertyBorderSeparationClass))
#define FO_IS_PROPERTY_BORDER_SEPARATION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_BORDER_SEPARATION))
#define FO_IS_PROPERTY_BORDER_SEPARATION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_BORDER_SEPARATION))
#define FO_PROPERTY_BORDER_SEPARATION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_BORDER_SEPARATION, FoPropertyBorderSeparationClass))


typedef struct _FoPropertyBorderSeparation      FoPropertyBorderSeparation;
typedef struct _FoPropertyBorderSeparationClass FoPropertyBorderSeparationClass;

GType       fo_property_border_separation_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_border_separation_new         (void);
FoProperty* fo_property_border_separation_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_BORDER_SEPARATION_H__ */
