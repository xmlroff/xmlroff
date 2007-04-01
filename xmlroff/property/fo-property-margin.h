/* Fo
 * fo-property-margin.h: 'margin' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-margin.h,v 1.4 2004/03/23 11:59:23 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_MARGIN_H__
#define __FO_PROPERTY_MARGIN_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* margin */
/* Inherited: FALSE */
/* Shorthand: TRUE */
/* <margin-width>{1,4} | inherit */
/* Initial value: not defined for shorthand properties */

#define FO_TYPE_PROPERTY_MARGIN              (fo_property_margin_get_type ())
#define FO_PROPERTY_MARGIN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_MARGIN, FoPropertyMargin))
#define FO_PROPERTY_MARGIN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_MARGIN, FoPropertyMarginClass))
#define FO_IS_PROPERTY_MARGIN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_MARGIN))
#define FO_IS_PROPERTY_MARGIN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_MARGIN))
#define FO_PROPERTY_MARGIN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_MARGIN, FoPropertyMarginClass))


typedef struct _FoPropertyMargin      FoPropertyMargin;
typedef struct _FoPropertyMarginClass FoPropertyMarginClass;

GType        fo_property_margin_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_margin_new         (void);
FoProperty * fo_property_margin_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_MARGIN_H__ */
