/* Fo
 * fo-expr-context.c: XSL expression language context
 *
 * Copyright (C) 1998-2002 Daniel Veillard.
 * Copyright (C) 2001-2002 Sun Microsystems.
 * All Rights Reserved.
 *
 * Based on an XSL expression language evaluator that was based on the
 * 'XML Path Language implementation' in 'xpath.c' from libxml2 by
 * Daniel Veillard.
 *
 * $Id: fo-expr-context.c,v 1.3 2004/02/06 12:41:49 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#include "fo-expr-context-private.h"
#include "libfo/fo-utils.h"
#include "fo-property-font-size.h"
#include "fo-all-datatype.h"
#include "fo-context.h"
#include "fo-xml-char-util.h"
#include <stdlib.h>
#include <string.h>

typedef GQueue     FoDatatypeStack;

struct _FoExprContext
{
  const gchar      *cur;		/* the current char being parsed */
  const gchar      *base;		/* the full expression */

  const gchar      *property_name;	/* the current property's name */
  FoResolveEnumFunc resolve_enum_func;	/* function to resolve enumerations */
  FoResolvePercentFunc resolve_percent_func; /* function to resolve percents */

  const FoDatatype *font_size;		/* font-size property to use for 'em'*/
  const FoFo       *current_fo;		/* current formatting object */
  const FoContext  *fo_context;		/* context for 'inherit' keyword */

  const FoExprEnvList *env_list;	/* list of function environments */

  FoDatatypeStack  *stack;		/* stack of intermediate results */
};

/*
 * Macros for accessing the content. Those should be used only by the parser,
 * and not exported.
 *
 * Dirty macros, i.e. one need to make assumption on the context to use them
 *
 *   CUR_PTR return the current pointer to the gchar to be parsed.
 *   CUR     returns the current gchar value, i.e. a 8 bit value
 *           in ISO-Latin or UTF-8.
 *           This should be used internally by the parser
 *           only to compare to ASCII values otherwise it would break when
 *           running with UTF-8 encoding.
 *   NXT(n)  returns the n'th next gchar. Same as CUR, it should be used only
 *           to compare on ASCII based substring.
 *   SKIP(n) Skip n gchar, and must also be used only to skip ASCII defined
 *           strings within the parser.
 *   NEXT    Skip to the next character, this does the proper decoding
 *           in UTF-8 mode.
 */

#define IS_BLANK(c) (((c) == 0x20) || ((c) == 0x09) || ((c) == 0xA) ||	\
                     ((c) == 0x0D))

G_CONST_RETURN gchar*
fo_expr_context_string (FoExprContext *context)
{
  return context->base;
}

gchar
fo_expr_context_cur (FoExprContext *context)
{
  return *context->cur;
}

void
fo_expr_context_skip (FoExprContext *context,
		      gint           val)
{
  context->cur += val;
}

gchar
fo_expr_context_peek (FoExprContext *context,
		      gint           val)
{
  return context->cur[(val)];
}

G_CONST_RETURN
gchar*
fo_expr_context_cur_ptr (FoExprContext *context)
{
  return context->cur;
}

void
fo_expr_context_next (FoExprContext *context)
{
  if (*context->cur)
    {
      context->cur = g_utf8_next_char (context->cur);
    }
}

void
fo_expr_context_skip_blanks (FoExprContext *context)
{
  while (IS_BLANK (*(context->cur)))
    {
      fo_expr_context_next (context);
    }
}

void
fo_expr_context_push_stack (FoExprContext *context,
			    FoDatatype    *datatype)
{
  g_return_if_fail (context != NULL);
  g_return_if_fail (context->stack != NULL);
  g_return_if_fail (datatype != NULL);

  g_queue_push_head (context->stack,
		     datatype);
}

FoDatatype*
fo_expr_context_pop_stack (FoExprContext *context)
{
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (context->stack != NULL, NULL);

  return g_queue_pop_head (context->stack);
}

FoDatatype*
fo_expr_context_peek_stack (FoExprContext *context)
{
  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (context->stack != NULL, NULL);

  return g_queue_peek_head (context->stack);
}

gboolean
fo_expr_context_stack_is_empty (FoExprContext *context)
{
  g_return_val_if_fail (context != NULL, TRUE);
  g_return_val_if_fail (context->stack != NULL, TRUE);

  return g_queue_is_empty (context->stack);
}

static void
new_stack (FoExprContext *context)
{
  g_return_if_fail (context != NULL);
  g_return_if_fail (context->stack == NULL);

  context->stack = g_queue_new ();
}

static void
dump_stack_item (gpointer data,
		 gpointer user_data)
{
  fo_object_debug_dump (data, 0);
}

void
fo_expr_context_debug_dump_stack (FoExprContext *context)
{
  g_return_if_fail (context != NULL);
  g_return_if_fail (context->stack != NULL);

  g_list_foreach (context->stack->head,
		  dump_stack_item,
		  NULL);
}

static void
free_stack_item (gpointer data,
		 gpointer user_data)
{
  g_object_unref (data);
}

static void
free_stack (FoExprContext *context)
{
  g_return_if_fail (context != NULL);
  g_return_if_fail (context->stack != NULL);

  g_list_foreach (context->stack->head,
		  free_stack_item,
		  NULL);
  g_queue_free (context->stack);
  context->stack = NULL;
}

G_CONST_RETURN
gchar*
fo_expr_context_get_property_name (FoExprContext *context)
{
  return context->property_name;
}

G_CONST_RETURN
FoDatatype*
fo_expr_context_get_font_size (FoExprContext *context)
{
  return context->font_size;
}

G_CONST_RETURN
FoFo*
fo_expr_context_get_current_fo (FoExprContext *context)
{
  return context->current_fo;
}

G_CONST_RETURN
FoContext*
fo_expr_context_get_fo_context (FoExprContext *context)
{
  return context->fo_context;
}

FoResolveEnumFunc
fo_expr_context_get_resolve_enum_func (FoExprContext *context)
{
  return context->resolve_enum_func;
}

FoResolvePercentFunc
fo_expr_context_get_resolve_percent_func (FoExprContext *context)
{
  return context->resolve_percent_func;
}

FoExprFunc
fo_expr_context_get_func (FoExprContext *pctxt,
			  const gchar   *name)
{
  g_return_val_if_fail (pctxt != NULL, NULL);

  return fo_expr_env_list_get_func (pctxt->env_list,
				    name);
}

FoExprContext*
fo_expr_context_new (const gchar      *string,
		     const gchar      *property_name,
		     FoResolveEnumFunc resolve_enum_func,
		     FoResolvePercentFunc resolve_percent_func,
		     const FoProperty *font_size_prop,
		     const FoFo       *current_fo,
		     const FoContext  *fo_context,
		     const GSList     *env_list)
{
  FoExprContext *context;

  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (string)), NULL);
  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (property_name)), NULL);
  g_return_val_if_fail ((font_size_prop) == NULL ||
			FO_IS_PROPERTY_FONT_SIZE (font_size_prop),
			NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);
  g_return_val_if_fail (env_list != NULL, NULL);
  /* Can't make assertion about resolve_enum_func since it can be NULL */
  /* Can't make assertion about resolve_percent_func since it can be NULL */

  context = (FoExprContext *) g_new0 (FoExprContext, 1);

  context->base = string;
  context->cur = string;
  context->property_name = property_name;
  context->resolve_enum_func = resolve_enum_func;
  context->resolve_percent_func = resolve_percent_func;
  context->current_fo = current_fo;
  context->fo_context = fo_context;
  context->env_list = env_list;

  if (font_size_prop != NULL)
    {
      context->font_size =
	fo_property_get_value ((FoProperty *) font_size_prop);
    }
  else
    {
      context->font_size =
	fo_property_get_value (fo_context_get_font_size ((FoContext *) fo_context));
    }

  new_stack (context);

  return context;
}

void
fo_expr_context_free (FoExprContext *context)
{
  free_stack (context);
  g_free (context);
}

