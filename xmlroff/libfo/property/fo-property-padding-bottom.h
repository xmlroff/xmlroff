/* Fo
 * fo-property-padding-bottom.h: 'padding-bottom' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_BOTTOM_H__
#define __FO_PROPERTY_PADDING_BOTTOM_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-bottom */
/* <padding-width> | inherit */
/* Initial value: 0pt */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_PADDING_BOTTOM              (fo_property_padding_bottom_get_type ())
#define FO_PROPERTY_PADDING_BOTTOM(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_BOTTOM, FoPropertyPaddingBottom))
#define FO_PROPERTY_PADDING_BOTTOM_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_BOTTOM, FoPropertyPaddingBottomClass))
#define FO_IS_PROPERTY_PADDING_BOTTOM(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_BOTTOM))
#define FO_IS_PROPERTY_PADDING_BOTTOM_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_BOTTOM))
#define FO_PROPERTY_PADDING_BOTTOM_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_BOTTOM, FoPropertyPaddingBottomClass))


typedef struct _FoPropertyPaddingBottom      FoPropertyPaddingBottom;
typedef struct _FoPropertyPaddingBottomClass FoPropertyPaddingBottomClass;

GType       fo_property_padding_bottom_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_padding_bottom_new         (void);
FoProperty* fo_property_padding_bottom_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_BOTTOM_H__ */
