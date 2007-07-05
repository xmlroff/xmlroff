/* Fo
 * fo-property-padding-after.h: 'padding-after' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_AFTER_H__
#define __FO_PROPERTY_PADDING_AFTER_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-after */
/* <padding-width> | <length-conditional> | inherit */
/* Initial value: 0pt */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_PADDING_AFTER              (fo_property_padding_after_get_type ())
#define FO_PROPERTY_PADDING_AFTER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_AFTER, FoPropertyPaddingAfter))
#define FO_PROPERTY_PADDING_AFTER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_AFTER, FoPropertyPaddingAfterClass))
#define FO_IS_PROPERTY_PADDING_AFTER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_AFTER))
#define FO_IS_PROPERTY_PADDING_AFTER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_AFTER))
#define FO_PROPERTY_PADDING_AFTER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_AFTER, FoPropertyPaddingAfterClass))


typedef struct _FoPropertyPaddingAfter      FoPropertyPaddingAfter;
typedef struct _FoPropertyPaddingAfterClass FoPropertyPaddingAfterClass;

GType       fo_property_padding_after_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_padding_after_new         (void);
FoProperty* fo_property_padding_after_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_AFTER_H__ */
