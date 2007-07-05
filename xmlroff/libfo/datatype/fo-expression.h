/* Fo
 * fo-expression.h: Expression datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_EXPRESSION_H__
#define __FO_EXPRESSION_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_EXPRESSION              (fo_expression_get_type ())
#define FO_EXPRESSION(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_EXPRESSION, FoExpression))
#define FO_EXPRESSION_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_EXPRESSION, FoExpressionClass))
#define FO_IS_EXPRESSION(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_EXPRESSION))
#define FO_IS_EXPRESSION_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_EXPRESSION))
#define FO_EXPRESSION_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_EXPRESSION, FoExpressionClass))


typedef struct _FoExpression      FoExpression;
typedef struct _FoExpressionClass FoExpressionClass;

GType       fo_expression_get_type      (void) G_GNUC_CONST;
FoDatatype *fo_expression_new           (void);

gchar* fo_expression_get_value (FoDatatype   *expression);
void   fo_expression_set_value (FoDatatype   *expression,
				const gchar*  new_value);

G_END_DECLS

#endif /* !__FO_EXPRESSION_H__ */
