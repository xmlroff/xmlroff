/* Fo
 * fo-property-padding-end-conditionality.h: 'padding-end-condity' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_END_CONDITY_H__
#define __FO_PROPERTY_PADDING_END_CONDITY_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* padding-end-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* discard | retain */
/* Initial value: discard */

#define FO_TYPE_PROPERTY_PADDING_END_CONDITY              (fo_property_padding_end_condity_get_type ())
#define FO_PROPERTY_PADDING_END_CONDITY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_END_CONDITY, FoPropertyPaddingEndCondity))
#define FO_PROPERTY_PADDING_END_CONDITY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_END_CONDITY, FoPropertyPaddingEndCondityClass))
#define FO_IS_PROPERTY_PADDING_END_CONDITY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_END_CONDITY))
#define FO_IS_PROPERTY_PADDING_END_CONDITY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_END_CONDITY))
#define FO_PROPERTY_PADDING_END_CONDITY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_END_CONDITY, FoPropertyPaddingEndCondityClass))


typedef struct _FoPropertyPaddingEndCondity      FoPropertyPaddingEndCondity;
typedef struct _FoPropertyPaddingEndCondityClass FoPropertyPaddingEndCondityClass;

GType        fo_property_padding_end_condity_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_padding_end_condity_new         (void);
FoProperty * fo_property_padding_end_condity_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_END_CONDITY_H__ */
