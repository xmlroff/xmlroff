/* Fo
 * fo-property-padding-before-length.h: 'padding-before-length' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-padding-before-length.h,v 1.1 2004/05/29 04:42:15 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_BEFORE_LENGTH_H__
#define __FO_PROPERTY_PADDING_BEFORE_LENGTH_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-before-length */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <padding-width> | <length-conditional> | inherit */
/* Initial value: 0pt */

#define FO_TYPE_PROPERTY_PADDING_BEFORE_LENGTH              (fo_property_padding_before_length_get_type ())
#define FO_PROPERTY_PADDING_BEFORE_LENGTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_BEFORE_LENGTH, FoPropertyPaddingBeforeLength))
#define FO_PROPERTY_PADDING_BEFORE_LENGTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_BEFORE_LENGTH, FoPropertyPaddingBeforeLengthClass))
#define FO_IS_PROPERTY_PADDING_BEFORE_LENGTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_BEFORE_LENGTH))
#define FO_IS_PROPERTY_PADDING_BEFORE_LENGTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_BEFORE_LENGTH))
#define FO_PROPERTY_PADDING_BEFORE_LENGTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_BEFORE_LENGTH, FoPropertyPaddingBeforeLengthClass))


typedef struct _FoPropertyPaddingBeforeLength      FoPropertyPaddingBeforeLength;
typedef struct _FoPropertyPaddingBeforeLengthClass FoPropertyPaddingBeforeLengthClass;

GType        fo_property_padding_before_length_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_padding_before_length_new         (void);
FoProperty * fo_property_padding_before_length_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_BEFORE_LENGTH_H__ */
