/* Fo
 * fo-expr-eval.h: XSL expression language evaluation module
 *
 * Copyright (C) 1998-2002 Daniel Veillard.
 * Copyright (C) 2001-2002 Sun Microsystems.
 * All Rights Reserved.
 *
 * Based on an XSL expression language evaluator that was based on the
 * 'XML Path Language implementation' in 'xpath.c' from libxml2 by
 * Daniel Veillard.
 *
 * $Id: fo-expr-eval.h,v 1.7 2005/06/27 00:22:21 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_EXPR_EVAL_H__
#define __FO_EXPR_EVAL_H__

#include <libfo/fo-utils.h>
#include "fo-property.h"
#include "fo-context.h"
#include "fo-datatype.h"

G_BEGIN_DECLS

typedef struct _FoExprEnv     FoExprEnv;
typedef GSList                FoExprEnvList;
typedef struct _FoExprContext FoExprContext;
typedef FoDatatype* (* FoExprFunc) (FoExprContext *context,
				    gint           nargs);

#define FO_EXPR_ERROR fo_expr_error_quark ()
GQuark fo_expr_error_quark (void);

typedef enum
{
  FO_EXPR_ERROR_FAILED,
  FO_EXPR_ERROR_NULL_RESULT,
  FO_EXPR_ERROR_ERROR_RESULT,
  FO_EXPR_ERROR_EXTRA_STACK,
  FO_EXPR_ERROR_EXTRA_EXPR
} FoExprError;

#define FO_EXPR_EVAL_ERROR fo_expr_eval_error_quark ()
GQuark fo_expr_eval_error_quark (void);

typedef enum
{
  FO_EXPR_EVAL_ERROR_FAILED,   /* Expression evaluation failed */
  FO_EXPR_EVAL_ERROR_UNFINISHED_LITERAL,
  FO_EXPR_EVAL_ERROR_START_LITERAL,
  FO_EXPR_EVAL_ERROR_EXPR_ERROR,
  FO_EXPR_EVAL_ERROR_UNKNOWN_FUNC,
  FO_EXPR_EVAL_ERROR_INVALID_ARITY,
  FO_EXPR_EVAL_ERROR_INVALID_TYPE,
  FO_EXPR_EVAL_ERROR_NOT_INHERITED,
  FO_EXPR_EVAL_ERROR_INVALID_PROPERTY,
  FO_EXPR_EVAL_ERROR_FUNCTION_INVALID_PROPERTY,
  FO_EXPR_EVAL_ERROR_NOT_TABLE_CELL_OR_DESCENDANT,
  FO_EXPR_EVAL_ERROR_NO_TABLE_CELL_COLUMN,
  FO_EXPR_EVAL_ERROR_NOT_LIST_BLOCK_OR_DESCENDANT,
  FO_EXPR_EVAL_ERROR_NOT_TABLE_COLUMN,
  FO_EXPR_EVAL_ERROR_NOT_COLUMN_WIDTH,
  FO_EXPR_EVAL_ERROR_NOT_FIXED_METHOD,
  FO_EXPR_EVAL_ERROR_COLOR_DECL,
  FO_EXPR_EVAL_ERROR_UNKNOWN_OPERATOR,
  FO_EXPR_EVAL_ERROR_FUNC_RETURN_NULL,
  FO_EXPR_EVAL_ERROR_CANNOT_INHERIT,
  FO_EXPR_EVAL_ERROR_NO_RESOLVE_PERCENT_FUNC,
  FO_EXPR_EVAL_ERROR_UNFINISHED_URL,
  FO_EXPR_EVAL_ERROR_LAST
} FoExprEvalError;

extern const gchar *fo_expr_eval_error_messages[FO_EXPR_EVAL_ERROR_LAST];

FoDatatype* fo_expr_eval (const gchar         *string,
			  const gchar         *property_name,
			  FoResolveEnumFunc    resolve_enum_func,
			  FoResolvePercentFunc resolve_percent_func,
			  const FoProperty    *font_size_prop,
			  const FoFo          *current_fo,
			  const FoContext     *fo_context,
			  const FoExprEnvList *env_list,
			  GError             **error);

FoDatatype* fo_expr_padding_eval       (const gchar         *string,
					const gchar         *property_name,
					FoResolveEnumFunc    resolve_enum_func,
					FoResolvePercentFunc resolve_percent_func,
					const FoProperty    *font_size_prop,
					const FoFo          *current_fo,
					const FoContext     *fo_context,
					const FoExprEnvList *env_list,
					GError             **error);

FoDatatype* fo_expr_border_color_eval  (const gchar         *string,
					const gchar         *property_name,
					FoResolveEnumFunc    resolve_enum_func,
					FoResolvePercentFunc resolve_percent_func,
					const FoProperty    *font_size_prop,
					const FoFo          *current_fo,
					const FoContext     *fo_context,
					const FoExprEnvList *env_list,
					GError             **error);

FoDatatype * fo_expr_border_style_eval (const gchar         *string,
					const gchar         *property_name,
					FoResolveEnumFunc    resolve_enum_func,
					FoResolvePercentFunc resolve_percent_func,
					const FoProperty    *font_size_prop,
					const FoFo          *current_fo,
					const FoContext     *fo_context,
					const FoExprEnvList *env_list,
					GError             **error);

FoDatatype * fo_expr_wsc_eval          (const gchar         *string,
					const gchar         *property_name,
					FoResolveEnumFunc    resolve_enum_func,
					FoResolvePercentFunc resolve_percent_func,
					const FoProperty    *font_size_prop,
					const FoFo          *current_fo,
					const FoContext     *fo_context,
					const FoExprEnvList *env_list,
					GError             **error);

FoDatatype * fo_expr_eval_new_error         (FoExprContext  *context,
					     FoExprEvalError error_type);
FoDatatype * fo_expr_eval_propagate_error   (FoExprContext *context,
					     GError        *error);

void         fo_expr_context_push_stack     (FoExprContext *context,
					     FoDatatype    *datatype);
FoDatatype * fo_expr_context_pop_stack      (FoExprContext *context);
FoDatatype * fo_expr_context_peek_stack     (FoExprContext *context);
gboolean     fo_expr_context_stack_is_empty (FoExprContext *context);
FoExprFunc   fo_expr_context_get_func       (FoExprContext *context,
					     const gchar   *name);
void         fo_expr_context_debug_dump_stack (FoExprContext *context);

FoExprEnv *     fo_expr_env_new (void);
FoExprEnv *     fo_expr_env_register_func (FoExprEnv   *env,
					   const gchar *name,
					   FoExprFunc   func);
FoExprFunc      fo_expr_env_get_func      (FoExprEnv   *env,
					   const gchar *name);

FoExprEnvList * fo_expr_env_list_new      (void);
void            fo_expr_env_list_free     (FoExprEnvList   *env_list);
FoExprEnvList * fo_expr_env_list_prepend  (FoExprEnvList *env_list,
					   FoExprEnv     *env);
FoExprFunc      fo_expr_env_list_get_func (const FoExprEnvList *env_list,
					   const gchar         *name);

G_END_DECLS

#endif /* !__FO_EXPR_EVAL_H__ */
