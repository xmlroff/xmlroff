/* Fo
 * fo-property-private.h: Structures private to the FoProperty superclass of all property classes
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_PRIVATE_H__
#define __FO_PROPERTY_PRIVATE_H__

#include "property/fo-property.h"
#include "datatype/fo-all-datatype.h"
#include "expr/fo-expr-eval.h"

G_BEGIN_DECLS

extern const gchar *fo_property_error_messages [FO_PROPERTY_ERROR_LAST];

struct _FoProperty
{
  FoObject parent_instance;

  FoDatatype *value;
};

struct _FoPropertyClass
{
  FoObjectClass parent_class;

  gboolean    is_inherited;
  gboolean    is_shorthand;
  FoExprEnvList *expr_env_list;
  FoProperty * (* new_from_expr)       (FoPropertyClass *property_class,
					const gchar *expr,
					FoContext   *context,
					FoProperty  *font_size,
					FoFo        *fo_node,
					GError     **error);
  FoDatatype * (* expr_eval)           (const gchar         *string,
					const gchar         *property_name,
					FoResolveEnumFunc    resolve_enum_func,
					FoResolvePercentFunc resolve_percent_func,
					const FoProperty    *font_size_prop,
					const FoFo          *current_fo,
					const FoContext     *fo_context,
					const GSList        *env_list,
					GError             **error);
  FoProperty * (* get_initial)         (void);
  FoDatatype * (* resolve_enum)        (const gchar *token,
					FoContext   *context,
					GError     **err);
  FoDatatype * (* resolve_percent)     (gdouble            percentage,
					const FoDatatype  *font_size,
					const FoFo        *fo_node,
					const FoContext   *context,
					GError           **err);
  FoDatatype * (* validate)            (FoDatatype  *datatype,
					FoContext   *context,
					GError     **error);
  void         (* set_value)           (FoProperty  *property,
					FoDatatype  *new_value);
  FoDatatype * (* get_value)           (FoProperty  *property);
};

FoProperty * fo_property_new_from_string (FoPropertyClass *property_class,
					  const gchar *expr,
					  FoContext   *context,
					  FoProperty    *current_font_size,
					  FoFo *fo_node,
					  GError **error);

G_END_DECLS

#endif /* !__FO_PROPERTY_PRIVATE_H__ */
