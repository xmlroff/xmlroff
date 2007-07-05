/* Fo
 * fo-property-padding-start-length.h: 'padding-start-length' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_START_LENGTH_H__
#define __FO_PROPERTY_PADDING_START_LENGTH_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-start-length */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* <padding-width> | <length-conditional> | inherit */
/* Initial value: 0pt */

#define FO_TYPE_PROPERTY_PADDING_START_LENGTH              (fo_property_padding_start_length_get_type ())
#define FO_PROPERTY_PADDING_START_LENGTH(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_START_LENGTH, FoPropertyPaddingStartLength))
#define FO_PROPERTY_PADDING_START_LENGTH_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_START_LENGTH, FoPropertyPaddingStartLengthClass))
#define FO_IS_PROPERTY_PADDING_START_LENGTH(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_START_LENGTH))
#define FO_IS_PROPERTY_PADDING_START_LENGTH_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_START_LENGTH))
#define FO_PROPERTY_PADDING_START_LENGTH_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_START_LENGTH, FoPropertyPaddingStartLengthClass))


typedef struct _FoPropertyPaddingStartLength      FoPropertyPaddingStartLength;
typedef struct _FoPropertyPaddingStartLengthClass FoPropertyPaddingStartLengthClass;

GType        fo_property_padding_start_length_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_padding_start_length_new         (void);
FoProperty * fo_property_padding_start_length_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_START_LENGTH_H__ */
