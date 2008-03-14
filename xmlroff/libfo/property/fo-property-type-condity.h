/* Fo
 * fo-property-type-condity.h: Abstract parent type of '.conditionality' components.
 *
 * Copyright (C) 2001-2004 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_TYPE_CONDITY_H__
#define __FO_PROPERTY_TYPE_CONDITY_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* type-condity */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* discard | retain */
/* Initial value: discard */

#define FO_TYPE_PROPERTY_TYPE_CONDITY              (fo_property_type_condity_get_type ())
#define FO_PROPERTY_TYPE_CONDITY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_TYPE_CONDITY, FoPropertyTypeCondity))
#define FO_PROPERTY_TYPE_CONDITY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_TYPE_CONDITY, FoPropertyTypeCondityClass))
#define FO_IS_PROPERTY_TYPE_CONDITY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_TYPE_CONDITY))
#define FO_IS_PROPERTY_TYPE_CONDITY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_TYPE_CONDITY))
#define FO_PROPERTY_TYPE_CONDITY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_TYPE_CONDITY, FoPropertyTypeCondityClass))


typedef struct _FoPropertyTypeCondity      FoPropertyTypeCondity;
typedef struct _FoPropertyTypeCondityClass FoPropertyTypeCondityClass;

GType       fo_property_type_condity_get_type    (void) G_GNUC_CONST;

G_END_DECLS

#endif /* !__FO_PROPERTY_TYPE_CONDITY_H__ */
