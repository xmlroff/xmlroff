/* Fo
 * fo-property-padding-start-conditionality.h: 'padding-start-condity' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PADDING_START_CONDITY_H__
#define __FO_PROPERTY_PADDING_START_CONDITY_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* padding-start-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* discard | retain */
/* Initial value: discard */

#define FO_TYPE_PROPERTY_PADDING_START_CONDITY              (fo_property_padding_start_condity_get_type ())
#define FO_PROPERTY_PADDING_START_CONDITY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_PADDING_START_CONDITY, FoPropertyPaddingStartCondity))
#define FO_PROPERTY_PADDING_START_CONDITY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_PADDING_START_CONDITY, FoPropertyPaddingStartCondityClass))
#define FO_IS_PROPERTY_PADDING_START_CONDITY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_PADDING_START_CONDITY))
#define FO_IS_PROPERTY_PADDING_START_CONDITY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_PADDING_START_CONDITY))
#define FO_PROPERTY_PADDING_START_CONDITY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_PADDING_START_CONDITY, FoPropertyPaddingStartCondityClass))


typedef struct _FoPropertyPaddingStartCondity      FoPropertyPaddingStartCondity;
typedef struct _FoPropertyPaddingStartCondityClass FoPropertyPaddingStartCondityClass;

GType        fo_property_padding_start_condity_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_padding_start_condity_new         (void);
FoProperty * fo_property_padding_start_condity_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_PADDING_START_CONDITY_H__ */
