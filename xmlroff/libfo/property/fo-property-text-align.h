/* Fo
 * fo-property-text-align.h: 'text-align' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_TEXT_ALIGN_H__
#define __FO_PROPERTY_TEXT_ALIGN_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* text-align */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* start | center | end | justify | inside | outside | left | right | <string> | inherit */
/* Initial value: start */

#define FO_TYPE_PROPERTY_TEXT_ALIGN              (fo_property_text_align_get_type ())
#define FO_PROPERTY_TEXT_ALIGN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_TEXT_ALIGN, FoPropertyTextAlign))
#define FO_PROPERTY_TEXT_ALIGN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_TEXT_ALIGN, FoPropertyTextAlignClass))
#define FO_IS_PROPERTY_TEXT_ALIGN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_TEXT_ALIGN))
#define FO_IS_PROPERTY_TEXT_ALIGN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_TEXT_ALIGN))
#define FO_PROPERTY_TEXT_ALIGN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_TEXT_ALIGN, FoPropertyTextAlignClass))


typedef struct _FoPropertyTextAlign      FoPropertyTextAlign;
typedef struct _FoPropertyTextAlignClass FoPropertyTextAlignClass;

GType        fo_property_text_align_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_text_align_new         (void);
FoProperty * fo_property_text_align_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_TEXT_ALIGN_H__ */
