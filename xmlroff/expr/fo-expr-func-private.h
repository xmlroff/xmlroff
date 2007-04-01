/* Fo
 * fo-expr-func.h: XSL expression language functions
 *
 * Copyright (C) 1998-2002 Daniel Veillard.
 * Copyright (C) 2001-2002 Sun Microsystems.
 * All Rights Reserved.
 *
 * Based on an XSL expression language evaluator that was based on the
 * 'XML Path Language implementation' in 'xpath.c' from libxml2 by
 * Daniel Veillard.
 *
 * $Id: fo-expr-func-private.h,v 1.2 2003/03/19 21:13:39 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_EXPR_FUNC_PRIVATE_H__
#define __FO_EXPR_FUNC_PRIVATE_H__

#include "fo-expr-eval.h"
#include "fo-datatype.h"

G_BEGIN_DECLS

FoDatatype* fo_expr_func_abs         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_add         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_body_start  (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_ceiling     (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_div         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_floor       (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_from_nearest_specified_value (FoExprContext *context,
						       gint           nargs);
FoDatatype* fo_expr_func_from_parent (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_from_table_column (FoExprContext *context,
					    gint           nargs);
FoDatatype* fo_expr_func_inherited_property_value (FoExprContext *context,
						   gint           nargs);
FoDatatype* fo_expr_func_label_end   (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_max         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_min         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_mod         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_mul         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_pcw         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_pcw_prop    (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_pcw_prop_fixed (FoExprContext *context,
					 gint           nargs);
FoDatatype* fo_expr_func_rgb         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_round       (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_sub         (FoExprContext *context,
				      gint           nargs);
FoDatatype* fo_expr_func_url         (FoExprContext *context,
				      gint           nargs);

G_END_DECLS

#endif /* !__FO_EXPR_FUNC_PRIVATE_H__ */
