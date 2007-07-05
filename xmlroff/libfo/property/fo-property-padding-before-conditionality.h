/* Fo
 * fo-property-padding-before-conditionality.h: 'padding-before-condity' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_BEFORE_CONDITY_H__
#define __FO_PROPERTY_PADDING_BEFORE_CONDITY_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-before-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* discard | retain */
/* Initial value: discard */

#define FO_TYPE_PROPERTY_PADDING_BEFORE_CONDITY              (fo_property_padding_before_condity_get_type ())
#define FO_PROPERTY_PADDING_BEFORE_CONDITY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_BEFORE_CONDITY, FoPropertyPaddingBeforeCondity))
#define FO_PROPERTY_PADDING_BEFORE_CONDITY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_BEFORE_CONDITY, FoPropertyPaddingBeforeCondityClass))
#define FO_IS_PROPERTY_PADDING_BEFORE_CONDITY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_BEFORE_CONDITY))
#define FO_IS_PROPERTY_PADDING_BEFORE_CONDITY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_BEFORE_CONDITY))
#define FO_PROPERTY_PADDING_BEFORE_CONDITY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_BEFORE_CONDITY, FoPropertyPaddingBeforeCondityClass))


typedef struct _FoPropertyPaddingBeforeCondity      FoPropertyPaddingBeforeCondity;
typedef struct _FoPropertyPaddingBeforeCondityClass FoPropertyPaddingBeforeCondityClass;

GType        fo_property_padding_before_condity_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_padding_before_condity_new         (void);
FoProperty * fo_property_padding_before_condity_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_BEFORE_CONDITY_H__ */
