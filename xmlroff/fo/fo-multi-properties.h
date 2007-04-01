/* Fo
 * fo-multi_properties.h: 'multi-properties' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-multi-properties.h,v 1.3 2005/02/28 11:51:56 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_MULTI_PROPERTIES_H__
#define __FO_MULTI_PROPERTIES_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

typedef struct _FoMultiProperties      FoMultiProperties;
typedef struct _FoMultiPropertiesClass FoMultiPropertiesClass;

#define FO_TYPE_MULTI_PROPERTIES              (fo_multi_properties_get_type ())
#define FO_MULTI_PROPERTIES(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_MULTI_PROPERTIES, FoMultiProperties))
#define FO_MULTI_PROPERTIES_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_MULTI_PROPERTIES, FoMultiPropertiesClass))
#define FO_IS_MULTI_PROPERTIES(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_MULTI_PROPERTIES))
#define FO_IS_MULTI_PROPERTIES_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_MULTI_PROPERTIES))
#define FO_MULTI_PROPERTIES_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_MULTI_PROPERTIES, FoMultiPropertiesClass))


GType        fo_multi_properties_get_type (void) G_GNUC_CONST;
FoFo *       fo_multi_properties_new      (void);

FoProperty * fo_multi_properties_get_id (FoFo       *fo_fo);
void         fo_multi_properties_set_id (FoFo       *fo_fo,
                                         FoProperty *new_id);
FoProperty * fo_multi_properties_get_role (FoFo       *fo_fo);
void         fo_multi_properties_set_role (FoFo       *fo_fo,
                                           FoProperty *new_role);
FoProperty * fo_multi_properties_get_source_document (FoFo       *fo_fo);
void         fo_multi_properties_set_source_document (FoFo       *fo_fo,
                                                      FoProperty *new_source_document);

G_END_DECLS

#endif /* !__FO_MULTI_PROPERTIES_H__ */
