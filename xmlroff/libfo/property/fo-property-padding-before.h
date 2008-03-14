/* Fo
 * fo-property-padding-before.h: 'padding-before' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_BEFORE_H__
#define __FO_PROPERTY_PADDING_BEFORE_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* padding-before */
/* <padding-width> | <length-conditional> | inherit */
/* Initial value: 0pt */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_PADDING_BEFORE              (fo_property_padding_before_get_type ())
#define FO_PROPERTY_PADDING_BEFORE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_BEFORE, FoPropertyPaddingBefore))
#define FO_PROPERTY_PADDING_BEFORE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_BEFORE, FoPropertyPaddingBeforeClass))
#define FO_IS_PROPERTY_PADDING_BEFORE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_BEFORE))
#define FO_IS_PROPERTY_PADDING_BEFORE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_BEFORE))
#define FO_PROPERTY_PADDING_BEFORE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_BEFORE, FoPropertyPaddingBeforeClass))


typedef struct _FoPropertyPaddingBefore      FoPropertyPaddingBefore;
typedef struct _FoPropertyPaddingBeforeClass FoPropertyPaddingBeforeClass;

GType       fo_property_padding_before_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_padding_before_new         (void);
FoProperty* fo_property_padding_before_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_BEFORE_H__ */
