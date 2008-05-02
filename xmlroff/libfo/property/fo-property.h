/* Fo
 * fo-property.h: FoProperty superclass of all property classes
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_H__
#define __FO_PROPERTY_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-object.h>

typedef struct _FoProperty      FoProperty;
typedef struct _FoPropertyClass FoPropertyClass;

#include <libfo/datatype/fo-all-datatype.h>
#include <libfo/fo-context.h>

G_BEGIN_DECLS

#define FO_PROPERTY_ERROR fo_property_error_quark ()
GQuark fo_property_error_quark (void);

typedef enum
{
  FO_PROPERTY_ERROR_FAILED,
  FO_PROPERTY_ERROR_EXPRESSION,
  FO_PROPERTY_ERROR_NO_ENUMERATION,
  FO_PROPERTY_ERROR_ILLEGAL_NEGATIVE,
  FO_PROPERTY_ERROR_ZERO_LENGTH,
  FO_PROPERTY_ERROR_LAST
} FoPropertyError;

#define FO_TYPE_PROPERTY              (fo_property_get_type ())
#define FO_PROPERTY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY, FoProperty))
#define FO_PROPERTY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY, FoPropertyClass))
#define FO_IS_PROPERTY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY))
#define FO_IS_PROPERTY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY))
#define FO_PROPERTY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY, FoPropertyClass))

GType        fo_property_get_type      (void) G_GNUC_CONST;

FoDatatype * fo_property_get_value (FoProperty *property);
void         fo_property_set_value (FoProperty *property,
				    FoDatatype *new_value);

gboolean fo_property_class_is_inherited (FoPropertyClass *property_class);
gboolean fo_property_is_inherited       (FoProperty      *property);

gboolean fo_property_class_is_shorthand (FoPropertyClass *property_class);
gboolean fo_property_is_shorthand       (FoProperty      *property);

typedef FoDatatype* (*FoResolveEnumFunc)    (const gchar    *token,
					     FoContext      *context,
					     GError        **err);
typedef FoDatatype* (*FoResolvePercentFunc) (gdouble           percentage,
					     const FoDatatype *font_size,
					     const FoFo       *fo_node,
					     const FoContext  *context,
					     GError          **err);
FoProperty * fo_property_new_from_expr (FoPropertyClass *property_class,
					const gchar *expr,
					FoContext   *context,
					FoProperty    *current_font_size,
					FoFo *fo_node,
					GError **error);

G_END_DECLS

#endif /* !__FO_PROPERTY_H__ */
