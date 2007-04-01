/* Fo
 * fo-property-padding-end-length.h: 'padding-end-length' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-padding-end-length.h,v 1.1 2004/05/29 04:42:15 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_END_LENGTH_H__
#define __FO_PROPERTY_PADDING_END_LENGTH_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-end-length */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <padding-width> | <length-conditional> | inherit */
/* Initial value: 0pt */

#define FO_TYPE_PROPERTY_PADDING_END_LENGTH              (fo_property_padding_end_length_get_type ())
#define FO_PROPERTY_PADDING_END_LENGTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_END_LENGTH, FoPropertyPaddingEndLength))
#define FO_PROPERTY_PADDING_END_LENGTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_END_LENGTH, FoPropertyPaddingEndLengthClass))
#define FO_IS_PROPERTY_PADDING_END_LENGTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_END_LENGTH))
#define FO_IS_PROPERTY_PADDING_END_LENGTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_END_LENGTH))
#define FO_PROPERTY_PADDING_END_LENGTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_END_LENGTH, FoPropertyPaddingEndLengthClass))


typedef struct _FoPropertyPaddingEndLength      FoPropertyPaddingEndLength;
typedef struct _FoPropertyPaddingEndLengthClass FoPropertyPaddingEndLengthClass;

GType        fo_property_padding_end_length_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_padding_end_length_new         (void);
FoProperty * fo_property_padding_end_length_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_END_LENGTH_H__ */
