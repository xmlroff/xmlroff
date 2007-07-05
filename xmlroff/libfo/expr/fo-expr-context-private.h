/* Fo
 * fo-expr-context-private.h: XSL expression language context
 *
 * Copyright (C) 1998-2002 Daniel Veillard.
 * Copyright (C) 2001-2002 Sun Microsystems.
 * All Rights Reserved.
 *
 * Based on an XSL expression language evaluator that was based on the
 * 'XML Path Language implementation' in 'xpath.c' from libxml2 by
 * Daniel Veillard.
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * !See COPYING for the status of this software.
 */

#ifndef __FO_EXPR_CONTEXT_PRIVATE_H__
#define __FO_EXPR_CONTEXT_PRIVATE_H__

#include <libfo/expr/fo-expr-eval.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

FoExprContext* fo_expr_context_new (const gchar      *string,
				    const gchar      *property_name,
				    FoResolveEnumFunc resolve_enum_func,
				    FoResolvePercentFunc resolve_percent_func,
				    const FoProperty *font_size_prop,
				    const FoFo       *current_fo,
				    const FoContext  *fo_context,
				    const GSList     *env_list);
void            fo_expr_context_free       (FoExprContext *context);

gchar  fo_expr_context_cur         (FoExprContext *context);
void   fo_expr_context_skip        (FoExprContext *context,
				    gint           val);
void   fo_expr_context_skip_blanks (FoExprContext *context);
gchar  fo_expr_context_peek        (FoExprContext *context,
				    gint           val);
G_CONST_RETURN
gchar* fo_expr_context_cur_ptr     (FoExprContext *context);

void   fo_expr_context_next        (FoExprContext *context);
void   fo_expr_context_skip_blanks (FoExprContext *context);

G_CONST_RETURN
gchar*      fo_expr_context_string (FoExprContext *context);
G_CONST_RETURN
gchar*      fo_expr_context_get_property_name (FoExprContext *context);
G_CONST_RETURN
FoDatatype* fo_expr_context_get_font_size (FoExprContext *context);
G_CONST_RETURN
FoFo*       fo_expr_context_get_current_fo (FoExprContext *context);
G_CONST_RETURN
FoContext* fo_expr_context_get_fo_context (FoExprContext *context);
FoResolveEnumFunc fo_expr_context_get_resolve_enum_func (FoExprContext *context);
FoResolvePercentFunc fo_expr_context_get_resolve_percent_func (FoExprContext *context);

G_END_DECLS

#endif /* !__FO_EXPR_CONTEXT_PRIVATE_H__ */
