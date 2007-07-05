/* Fo
 * fo-multi_property_set.h: 'multi-property-set' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_MULTI_PROPERTY_SET_H__
#define __FO_MULTI_PROPERTY_SET_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoMultiPropertySet      FoMultiPropertySet;
typedef struct _FoMultiPropertySetClass FoMultiPropertySetClass;

#define FO_TYPE_MULTI_PROPERTY_SET              (fo_multi_property_set_get_type ())
#define FO_MULTI_PROPERTY_SET(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_MULTI_PROPERTY_SET, FoMultiPropertySet))
#define FO_MULTI_PROPERTY_SET_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_MULTI_PROPERTY_SET, FoMultiPropertySetClass))
#define FO_IS_MULTI_PROPERTY_SET(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_MULTI_PROPERTY_SET))
#define FO_IS_MULTI_PROPERTY_SET_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_MULTI_PROPERTY_SET))
#define FO_MULTI_PROPERTY_SET_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_MULTI_PROPERTY_SET, FoMultiPropertySetClass))


GType         fo_multi_property_set_get_type      (void) G_GNUC_CONST;
FoFo *fo_multi_property_set_new (void);

void fo_multi_property_set_set_id (FoFo *fo_fo,
                                   FoProperty *new_id);
FoProperty *fo_multi_property_set_get_id (FoFo *fo_fo);

G_END_DECLS

#endif /* !__FO_MULTI_PROPERTY_SET_H__ */
