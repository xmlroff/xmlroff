/* Fo
 * fo-property-padding-end.h: 'padding-end' property
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-property-padding-end.h,v 1.3 2003/05/16 10:40:07 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_END_H__
#define __FO_PROPERTY_PADDING_END_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-end */
/* <padding-width> | <length-conditional> | inherit */
/* Initial value: 0pt */
/* NO ENUMERATED VALUE */

#define FO_TYPE_PROPERTY_PADDING_END              (fo_property_padding_end_get_type ())
#define FO_PROPERTY_PADDING_END(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_END, FoPropertyPaddingEnd))
#define FO_PROPERTY_PADDING_END_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_END, FoPropertyPaddingEndClass))
#define FO_IS_PROPERTY_PADDING_END(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_END))
#define FO_IS_PROPERTY_PADDING_END_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_END))
#define FO_PROPERTY_PADDING_END_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_END, FoPropertyPaddingEndClass))


typedef struct _FoPropertyPaddingEnd      FoPropertyPaddingEnd;
typedef struct _FoPropertyPaddingEndClass FoPropertyPaddingEndClass;

GType       fo_property_padding_end_get_type    (void) G_GNUC_CONST;
FoProperty* fo_property_padding_end_new         (void);
FoProperty* fo_property_padding_end_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_END_H__ */
