/* Fo
 * fo-expr-eval.c: XSL expression language evaluation module
 *
 * Copyright (C) 1998-2002 Daniel Veillard.
 * Copyright (C) 2007 Menteith Consulting Ltd
 * Copyright (C) 2001-2004 Sun Microsystems.
 *
 * Based on a previous xmlroff XSL expression language evaluator that
 * was based on the 'XML Path Language implementation' in 'xpath.c'
 * from libxml2 by Daniel Veillard.
 *
 * !See COPYING for the status of this software.
 **/

#include "fo-expr-eval.h"
#include "fo-expr-context-private.h"
#include "property/fo-property.h"
#include "property/fo-property-font-size.h"
#include "datatype/fo-all-datatype.h"
#include "fo-context.h"
#include "fo-xml-char-util.h"
#include "datatype/fo-wsc.h"
#include "property/fo-property-util.h"
#include <stdlib.h>
#include <string.h>

#define POINT2DEVICE(x)		(x)
#define PICA2DEVICE(x)		(x * 12)
#define INCH2DEVICE(x)		(x * 72)
#define CM2DEVICE(x)		(x * (72 / 2.54))
#define MM2DEVICE(x)		(x * (72 / 25.4))

#define IS_NUMERIC(context) \
		(g_ascii_isdigit (fo_expr_context_cur (context)) || \
		 fo_expr_context_cur (context) == '.')

#define RETURN_IF_ERROR	\
	if(fo_expr_context_peek_stack (context) != NULL && \
	   FO_IS_ERROR (fo_expr_context_peek_stack (context))) return

GQuark
fo_expr_eval_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("Expression evaluation error");
  return quark;
}

const gchar *fo_expr_eval_error_messages [] = {
  N_("Invalid expression."),
  N_("Unfinished literal."),
  N_("Expected start of literal."),
  N_("Invalid expression."),
  N_("Unregistered function."),
  N_("Invalid number of arguments."),
  N_("Invalid type for function argument."),
  N_("Property is not inherited."),
  N_("Invalid property name."),
  N_("Function invalid for property."),
  N_("Formatting object is not 'fo:table-cell' or a descendant of one."),
  N_("Ancestor 'fo:table-cell' does not have an associated 'fo:table-column'."),
  N_("Formatting object is not 'fo:list-block' or a descendant of one."),
  N_("Formatting object is not 'fo:table-column'."),
  N_("'proportional-column-width()' can only be used with 'column-width' property."),
  N_("'proportional-column-width()' can only be used with the 'fixed' table layout method."),
  N_("Invalid number of characters in color declaration."),
  N_("Unrecognized operator name."),
  N_("Function evaluation returned NULL result."),
  N_("No object from which to inherit property."),
  N_("Expression contains a percentage but no function to resolve percentages was provided."),
  N_("Unfinished URL.")
};

GQuark
fo_expr_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("Expression evaluation error");
  return quark;
}

const gchar *fo_expr_error_messages [] = {
  N_("Expression evaluation failed"),
  N_("No result"),
  N_("Evaluation resulted in an error"),
  N_("Object left on stack: '%s'"),
  N_("Expression not completely evaluated: '%s'"),
};

static void eval_additive_expr (FoExprContext *context);

static gchar*
parse_error_indication_string (FoExprContext *context)
{
  GString *string = g_string_new (NULL);
  gint n;
  const gchar *cur = fo_expr_context_cur_ptr (context);
  const gchar *base = fo_expr_context_string (context);

  while ((cur > base) && ((*cur == '\n') || (*cur == '\r')))
    {
      cur--;
    }
  n = 0;
  while ((n++ < 80) && (cur > base) && (*cur != '\n') && (*cur != '\r'))
    cur--;
  if ((*cur == '\n') || (*cur == '\r')) cur++;
  base = cur;
  n = 0;
  while ((*cur != 0) && (*cur != '\n') && (*cur != '\r') && (n < 79))
    {
      g_string_append_c (string, *cur++);
      n++;
    }
  g_string_append (string, "\n");
  cur = fo_expr_context_cur_ptr (context);
  while ((*cur == '\n') || (*cur == '\r'))
    cur--;
  n = 0;
  while ((cur != base) && (n++ < 80))
    {
      g_string_append (string, " ");
      base++;
    }
  g_string_append (string, "^");

  return g_string_free (string, FALSE);
}

/**
 * fo_expr_eval_new_error:
 * @context:    #FoExprContext for expression.
 * @error_type: Type of error.
 * 
 * Creates an #FoError based on @error_type and using information from
 * @context in the error message string.
 * 
 * Return value: An #FoError for an error of type @error_type.
 **/
FoDatatype*
fo_expr_eval_new_error (FoExprContext  *context,
			FoExprEvalError error_type)
{
  GError *error = NULL;
  gchar *error_indication = NULL;
  const gchar *error_string = NULL;

  g_return_val_if_fail (context != NULL, NULL);

  error_indication = parse_error_indication_string (context);

  if (error_indication != NULL)
    {
      error_string =
	g_strconcat (_(fo_expr_eval_error_messages[error_type]),
		     "\n",
		     error_indication,
		     NULL);
      g_free (error_indication);
    }
  else
    {
      error_string =
	_(fo_expr_eval_error_messages[error_type]);
    }

  error = g_error_new (FO_EXPR_EVAL_ERROR,
		       error_type,
		       error_string);

  return fo_error_new_with_value (error);
}

#define CHECK_ARITY(context, x)			    \
    if (nargs != (x))				    \
        return fo_expr_eval_new_error((context), \
					   FO_EXPR_EVAL_ERROR_INVALID_ARITY)

FoDatatype*
fo_expr_eval_propagate_error (FoExprContext *context,
			      GError        *error)
{
  GError *new_error = NULL;
  FoExprEvalError error_type = FO_EXPR_EVAL_ERROR_FAILED;
  gchar *error_indication = NULL;
  gchar *error_string = NULL;

  g_return_val_if_fail (context != NULL, NULL);
  g_return_val_if_fail (error != NULL, NULL);

  error_indication = parse_error_indication_string (context);

  if (error_indication != NULL)
    {
      error_string =
	g_strconcat (_(fo_expr_eval_error_messages[error_type]),
		     "\n",
		     g_quark_to_string (error->domain),
		     ": ",
		     error->message,
		     "\n",
		     error_indication,
		     NULL);
      g_free (error_indication);
    }
  else
    {
      error_string =
	g_strconcat (_(fo_expr_eval_error_messages[error_type]),
		     "\n",
		     g_quark_to_string (error->domain),
		     ": ",
		     error->message,
		     NULL);
    }

  g_error_free (error);

  new_error = g_error_new (FO_EXPR_EVAL_ERROR,
			   error_type,
			   error_string);

  return fo_error_new_with_value (new_error);
}

/**
 * is_ncnamechar:
 * @context: the #FoExprContext
 * 
 * Test whether the current character in @context is an NCNameChar
 * according to the "Namespaces in XML" Recommendation
 * 
 * [NS 4] NCNameChar ::= Letter | Digit | '.' | '-' | '_' |
 *                       CombiningChar | Extender
 * 
 * Return value: TRUE if the current character is an NCNameChar,
 *               otherwise FALSE
 **/
static gboolean
is_ncnamechar (FoExprContext *context)
{
  return ((IS_LETTER(g_utf8_get_char (fo_expr_context_cur_ptr (context)))) ||
	  (IS_DIGIT(g_utf8_get_char (fo_expr_context_cur_ptr (context)))) ||
	  (fo_expr_context_cur (context) == '.') ||
	  (fo_expr_context_cur (context) == '-') ||
	  (fo_expr_context_cur (context) == '_') ||
	  (IS_COMBINING(g_utf8_get_char (fo_expr_context_cur_ptr (context)))) ||
	  (IS_EXTENDER(g_utf8_get_char (fo_expr_context_cur_ptr (context)))));
}

/**
 * parse_ncname:
 * @context: the #FoExprContext
 *
 * parse an XML namespace non-qualified name.
 *
 * [NS 3] NCName ::= (Letter | '_') (NCNameChar)*
 *
 * [NS 4] NCNameChar ::= Letter | Digit | '.' | '-' | '_' |
 *                       CombiningChar | Extender
 *
 * Returns the name or NULL
 **/
static gchar *
parse_ncname (FoExprContext *context)
{
  const gchar *q;
  gchar *ret = NULL;

  if (!IS_LETTER(g_utf8_get_char (fo_expr_context_cur_ptr (context))) &&
      (fo_expr_context_cur (context) != '_'))
    {
      return (NULL);
    }

  q = fo_expr_context_cur_ptr (context);
  fo_expr_context_next (context);

  while (is_ncnamechar (context))
    {
      fo_expr_context_next (context);
    }

  ret = g_strndup (q, fo_expr_context_cur_ptr (context) - q);

  return ret;
}

/**
 * eval_inherit:
 * @context: the #FoExprContext
 *
 * Compile the inherited value.
 **/
static void
eval_inherit (FoExprContext *context)
{
  FoProperty *inherited_property = NULL;
  FoDatatype *result_datatype = NULL;

  g_object_get ((gpointer) fo_expr_context_get_fo_context (context),
		fo_expr_context_get_property_name (context),
		&inherited_property,
		NULL);

  if (inherited_property == NULL)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_INHERITED);
    }
  else
    {
      result_datatype =
	g_object_ref (fo_property_get_value (inherited_property));
    }

  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * is_unit_name:
 * @context:
 *
 * Tests whether the characters beginning at the current character in
 * @context make a unit name.

 * Return value: TRUE if the next characters are a unit name,
 *               otherwise FALSE
 */
static gboolean
is_unit_name (FoExprContext *context)
{
  if (((fo_expr_context_cur (context) == 'p') &&
       ((fo_expr_context_peek (context, 1) == 't') ||
	(fo_expr_context_peek (context, 1) == 'c') ||
	(fo_expr_context_peek (context, 1) == 'x'))) ||
      (((fo_expr_context_cur (context) == 'c') ||
	(fo_expr_context_cur (context) == 'm')) &&
       (fo_expr_context_peek (context, 1) == 'm')) ||
      ((fo_expr_context_cur (context) == 'i') &&
       (fo_expr_context_peek (context, 1) == 'n')) ||
      ((fo_expr_context_cur (context) == 'e') &&
       (fo_expr_context_peek (context, 1) == 'm')))
    {
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

static FoDatatype *
parse_length (FoExprContext *context,
	      gdouble        number)
{
  FoDatatype *length = NULL;

  if ((fo_expr_context_cur (context) == 'p') &&
	   (fo_expr_context_peek (context, 1) == 'x'))
    {
      length = fo_length_new_from_pixels ((gint) number);

      goto finish;
    }
  else if ((fo_expr_context_cur (context) == 'p') &&
      (fo_expr_context_peek (context, 1) == 't'))
    {
      number = POINT2DEVICE(number);
    }
  else if ((fo_expr_context_cur (context) == 'p') &&
	   (fo_expr_context_peek (context, 1) == 'c'))
    {
      number = PICA2DEVICE(number);
    }
  else if ((fo_expr_context_cur (context) == 'c') &&
	   (fo_expr_context_peek (context, 1) == 'm'))
    {
      number = CM2DEVICE(number);
    }
  else if ((fo_expr_context_cur (context) == 'm') &&
	   (fo_expr_context_peek (context, 1) == 'm'))
    {
      number = MM2DEVICE(number);
    }
  else if ((fo_expr_context_cur (context) == 'i') &&
	   (fo_expr_context_peek (context, 1) == 'n'))
    {
      number = INCH2DEVICE(number);
    }
  else if ((fo_expr_context_cur (context) == 'e') &&
	   (fo_expr_context_peek (context, 1) == 'm'))
    {
      number =
	number *
	fo_length_get_value ((FoDatatype *) fo_expr_context_get_font_size (context));
    }
  else
    {
      g_assert_not_reached();
    }

  length = fo_length_new_with_value (number);

 finish:
  fo_expr_context_skip (context, 2);

  return length;
}

/**
 * parse_percentage:
 * @context: #FoExprContext providing #FoResolvePercentFunc, etc.
 * @number:  Numeric value of percentage to be evaluated.
 *
 * Does not move expression context pointer.  Does not change the
 * stack.
 *
 * Return value: #FoDatatype representing evaluated percentage or an #FoError.
 */
static FoDatatype *
parse_percentage (FoExprContext *context,
		  gdouble        number)
{
  FoDatatype *result_datatype;
  FoResolvePercentFunc resolve_percent_func;

  if (fo_expr_context_cur (context) != '%')
    {
      g_assert_not_reached();
    }

  fo_expr_context_skip (context, 1);

  resolve_percent_func =
    fo_expr_context_get_resolve_percent_func (context);

  if (resolve_percent_func != NULL)
    {
      GError *tmp_error = NULL;

      result_datatype =
	resolve_percent_func (number,
			      fo_expr_context_get_font_size (context),
			      fo_expr_context_get_current_fo (context),
			      fo_expr_context_get_fo_context (context),
			      &tmp_error);
      if (tmp_error != NULL)
	{
	  if (result_datatype != NULL)
	    {
	      g_object_unref (result_datatype);
	    }

	  result_datatype = fo_error_new_with_value (tmp_error);
	}
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NO_RESOLVE_PERCENT_FUNC);
    }

  return result_datatype;
}

/**
 * parse_number:
 * @context: The #FoExprContext.
 *
 * Parse the current context as a number.
 *
 * Return value: The number.
 */
static gdouble
parse_number (FoExprContext *context)
{
  gdouble number = 0.0;
  gdouble mult = 1;
  gboolean ok = FALSE;

  if (!IS_NUMERIC (context))
    {
      g_assert_not_reached ();
    }

  while ((fo_expr_context_cur (context) >= '0') &&
	 (fo_expr_context_cur (context) <= '9'))
    {
      number = number * 10 + (fo_expr_context_cur (context) - '0');
      ok = TRUE;
      fo_expr_context_next (context);
    }
  if (fo_expr_context_cur (context) == '.')
    {
      fo_expr_context_next (context);
      if (((fo_expr_context_cur (context) < '0') ||
	   (fo_expr_context_cur (context) > '9')) && (!ok))
	{
	  g_assert_not_reached ();
	}
      while ((fo_expr_context_cur (context) >= '0') &&
	     (fo_expr_context_cur (context) <= '9'))
	{
	  mult /= 10;
	  number = number  + (fo_expr_context_cur (context) - '0') * mult;
	  fo_expr_context_next (context);
	}
    }

  return number;
}

/**
 * eval_numeric:
 * @context: the #FoExprContext
 *
 *  [5]   Numeric ::=         AbsoluteNumeric
 *                            | RelativeNumeric
 *
 *  [6]   AbsoluteNumeric ::= AbsoluteLength
 *
 *  [7]   AbsoluteLength ::=  Number AbsoluteUnitName?
 *
 *  [8]   RelativeNumeric ::= Percent
 *                            | RelativeLength
 *
 *  [9]   Percent ::=         Number '%'
 *
 *  [10]  RelativeLength ::=  Number RelativeUnitName
 *
 * Compile a Numeric, then push it on the stack
 *
 * Does not implement the productions in the order shown since that
 * would be inefficient.  For example, this code handles absolute and
 * relative units together, rather than as separate operations.
 **/
static void
eval_numeric (FoExprContext *context)
{
  FoDatatype *result_datatype = NULL;
  gdouble number;

  RETURN_IF_ERROR;

  number = parse_number (context);

  fo_expr_context_skip_blanks (context);
  if (fo_expr_context_cur (context) == '%')
    {
      result_datatype = parse_percentage (context, number);
    }
  else if (is_unit_name (context))
    {
      result_datatype = parse_length (context, number);
    }
  else {
    result_datatype = fo_number_new_with_value (number);
  }

  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * eval_color:
 * @context: the #FoExprContext
 *
 *  [18]  Color         ::= '#' AlphaOrDigits
 *
 *  [19]  AlphaOrDigits ::= [a-fA-F0-9]+
 *
 * Compile a color, then push it on the stack
 *
 **/
static void
eval_color (FoExprContext *context)
{
  FoDatatype *result_datatype = NULL;
  long long int full_color = 0;
  int ret_length = 0;
  guint16 redval = 0;
  guint16 greenval = 0;
  guint16 blueval = 0;

  RETURN_IF_ERROR;
  if (fo_expr_context_cur (context) != '#')
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				     FO_EXPR_EVAL_ERROR_EXPR_ERROR);
    }
  else {
    fo_expr_context_next (context);

    while (((fo_expr_context_cur (context) >= '0') &&
	    (fo_expr_context_cur (context) <= '9')) ||
	   ((fo_expr_context_cur (context) >= 'a') &&
	    (fo_expr_context_cur (context) <= 'f')) ||
	   ((fo_expr_context_cur (context) >= 'A') &&
	    (fo_expr_context_cur (context) <= 'F')))
      {
	/* Shift the current value */
	full_color <<= 4;
	/* Count the number of characters */
	ret_length++;
	if ((fo_expr_context_cur (context) >= '0') &&
	    (fo_expr_context_cur (context) <= '9'))
	  {
	    full_color += fo_expr_context_cur (context) - '0';
	  }
	else if ((fo_expr_context_cur (context) >= 'a') &&
		 (fo_expr_context_cur (context) <= 'f'))
	  {
	    full_color += fo_expr_context_cur (context) - ('a' - 10);
	  }
	else
	  {
	    full_color += fo_expr_context_cur (context) - ('A' - 10);
	  }
	fo_expr_context_next (context);
      }

    if ((ret_length == 3) ||
	(ret_length == 6) ||
	(ret_length == 12))
      {
	if (ret_length == 3)
	  {
	    redval = full_color >> 8;
	    greenval = (full_color >> 4) & 0xF;
	    blueval = full_color & 0xF;

	    /* Convert to 16-bit color by repeating the 4-bit value so
	       0x0 -> 0x0000 and 0xF -> 0xFFFF */
	    redval =
	      (redval << 12) | (redval << 8) | (redval << 4) | redval;
	    greenval =
	      (greenval << 12 ) | (greenval << 8) | (greenval << 4) | greenval;
	    blueval =
	      (blueval << 12) | (blueval << 8) | (blueval << 4) | blueval;
	  }
	else if (ret_length == 6)
	  {
	    redval = full_color >> 16;
	    greenval = (full_color >> 8) & 0xFF;
	    blueval = full_color & 0xFF;

	    redval = (redval << 8) | redval;
	    greenval = (greenval << 8) | greenval;
	    blueval = (blueval << 8) | blueval;
	  }
	else if (ret_length == 12)
	  {
	    redval = full_color >> 32;
	    greenval = (full_color >> 16) & 0xFFFF;
	    blueval = full_color & 0xFFFF;
	  }

	result_datatype = fo_color_new_with_value (redval, greenval, blueval);
      }
    else
      {
	result_datatype =
	  fo_expr_eval_new_error (context,
				  FO_EXPR_EVAL_ERROR_COLOR_DECL);
      }
  }

  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * eval_literal:
 * @context: the #FoExprContext
 *
 * Parse a Literal and push it on the stack.
 *
 *  [20]   Literal ::=   '"' [^"]* '"'
 *                       | "'" [^']* "'"
 *
 **/
static void
eval_literal (FoExprContext *context)
{
  FoDatatype *result_datatype = NULL;
  const gchar *q;
  gchar *ret = NULL;

  if (fo_expr_context_cur (context) == '"')
    {
      fo_expr_context_next (context);
      q = fo_expr_context_cur_ptr (context);
      while ((IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context)))) &&
	     (fo_expr_context_cur (context) != '"'))
	fo_expr_context_next (context);
      if (!IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context))))
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_UNFINISHED_LITERAL);
	}
      else
	{
	  ret = g_strndup (q, fo_expr_context_cur_ptr (context) - q);
	  fo_expr_context_next (context);
	}
    }
  else if (fo_expr_context_cur (context) == '\'')
    {
      fo_expr_context_next (context);
      q = fo_expr_context_cur_ptr (context);

      while ((IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context)))) &&
	     (fo_expr_context_cur (context) != '\''))
	{
	  fo_expr_context_next (context);
	}

      if (!IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context))))
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_UNFINISHED_LITERAL);
	}
      else
	{
	  ret = g_strndup (q, fo_expr_context_cur_ptr (context) - q);
	  fo_expr_context_next (context);
	}
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_START_LITERAL);
    }

  if (ret != NULL)
    {
      result_datatype = fo_string_new_with_value (ret);
      g_free (ret);
    }

  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * eval_enum:
 * @context: the #FoExprContext
 * @name:  the potential enumeration token name
 *
 *  [26]   EnumerationToken ::=   NCName
 *
 * Compile an enumeration token and push the result on the stack.
 *
 * If @name does not correspond to an allowed enumeration token, make
 * an #FoName and push that on the stack.
 **/
static void
eval_enum (FoExprContext *context,
	   gchar         *name)
{
  FoResolveEnumFunc resolve_enum_func = NULL;
  FoDatatype *object = NULL;
  FoDatatype *result_datatype = NULL;

  resolve_enum_func = fo_expr_context_get_resolve_enum_func (context);
  if (resolve_enum_func != NULL)
    {
      object =
	resolve_enum_func (name,
			   (FoContext *) fo_expr_context_get_fo_context (context),
			   NULL);
    }

  if (object != NULL)
    {
      /* there was a match */
      result_datatype = object;
    }
  else 
    {
      /* No match returned by lookup, so make it into a name */
      result_datatype = fo_name_new_with_value (name);
    }

  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * eval_function_call:
 * @context: the #FoExprContext
 *
 *  [3]   FunctionCall ::=   FunctionName '(' ( Argument ( ',' Argument)*)? ')'
 *  [4]   Argument ::=   Expr 
 *
 * Compile a function call, the evaluation of all arguments are
 * pushed on the stack
 **/
static void
eval_function_call (FoExprContext *context,
		    gchar         *name)
{
  FoExprFunc expr_func;
  FoDatatype *result_datatype = NULL;
  int nargs = 0;

  g_return_if_fail (context != NULL);
  g_return_if_fail (name != '\0');

  if (fo_expr_context_cur (context) != '(')
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_EXPR_ERROR);
    }
  else
    {
      fo_expr_context_next (context);
      fo_expr_context_skip_blanks (context);

      while (fo_expr_context_cur (context) != ')')
	{
	  eval_additive_expr (context);
	  nargs++;
	  if (fo_expr_context_cur (context) == ')') break;
	  if (fo_expr_context_cur (context) != ',')
	    {
	      result_datatype =
		fo_expr_eval_new_error (context,
					FO_EXPR_EVAL_ERROR_EXPR_ERROR);
	      goto error;
	    }
	  fo_expr_context_next (context);
	  fo_expr_context_skip_blanks (context);
	}

      expr_func = fo_expr_context_get_func (context, name);

      if (expr_func != NULL)
	{
	  result_datatype = expr_func (context, nargs);

	  if (result_datatype == NULL)
	    {
	      result_datatype =
		fo_expr_eval_new_error (context,
					FO_EXPR_EVAL_ERROR_FUNC_RETURN_NULL);
	    }
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_UNKNOWN_FUNC);
	}
      fo_expr_context_next (context);
      fo_expr_context_skip_blanks (context);
    }

 error:
  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * fo_expr_eval_url:
 * @context: The expression context
 * 
 * Implement the uri-specification XSL datatype
 *
 *    url(...)
 *
 * It's not really an XSL function, but it does look like one.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 */
void
eval_url (FoExprContext *context)
{
  FoDatatype *result_datatype = NULL;
  const gchar *q;
  gchar *ret = NULL;

  g_return_if_fail (context != NULL);

  fo_expr_context_skip_blanks (context);

  /* Skip the leading '('. */
  fo_expr_context_next (context);

  if (fo_expr_context_cur (context) == '"')
    {
      fo_expr_context_next (context);
      q = fo_expr_context_cur_ptr (context);

      while ((IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context)))) &&
	     (fo_expr_context_cur (context) != '"'))
	{
	  fo_expr_context_next (context);
	}

      if (!IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context))))
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_UNFINISHED_URL);
	}
      else
	{
	  ret = g_strndup (q, fo_expr_context_cur_ptr (context) - q);
	  fo_expr_context_next (context);
	}
    }
  else if (fo_expr_context_cur (context) == '\'')
    {
      fo_expr_context_next (context);
      q = fo_expr_context_cur_ptr (context);

      while ((IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context)))) &&
	     (fo_expr_context_cur (context) != '\''))
	{
	  fo_expr_context_next (context);
	}

      if (!IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context))))
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_UNFINISHED_URL);
	}
      else
	{
	  ret = g_strndup (q, fo_expr_context_cur_ptr (context) - q);
	  fo_expr_context_next (context);
	}
    }
  else
    {
      q = fo_expr_context_cur_ptr (context);

      while ((IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context)))) &&
	     (fo_expr_context_cur (context) != ' ') &&
	     (fo_expr_context_cur (context) != '	') &&
	     (fo_expr_context_cur (context) != ')'))
	{
	  fo_expr_context_next (context);
	}

      if (!IS_CHAR (g_utf8_get_char (fo_expr_context_cur_ptr (context))))
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_UNFINISHED_URL);
	}
      else
	{
	  ret = g_strndup (q, fo_expr_context_cur_ptr (context) - q);
	}
    }

  fo_expr_context_skip_blanks (context);

  if (fo_expr_context_cur (context) == ')')
      {
	fo_expr_context_next (context);
      }
  else
      {
	result_datatype =
	  fo_expr_eval_new_error (context,
				  FO_EXPR_EVAL_ERROR_UNFINISHED_URL);
      }

  if (ret != NULL && result_datatype == NULL)
    {
      result_datatype = fo_uri_specification_new_with_value (ret);
      g_free (ret);
    }

  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * eval_primary_expr:
 * @context: 
 *
 * Compile a Primary expression:
 * 
 *  [2]    PrimaryExpr ::=   '(' Expr ')'
 *                   | Numeric
 *                   | Literal
 *                   | Color
 *                   | Keyword
 *                   | EnumerationToken
 *                   | FunctionCall
 **/
static void
eval_primary_expr (FoExprContext *context)
{
  fo_expr_context_skip_blanks (context);

  if (fo_expr_context_cur (context) == '(')
    {
      fo_expr_context_next (context);
      fo_expr_context_skip_blanks (context);
      eval_additive_expr (context);
      if (fo_expr_context_cur (context) != ')')
	{
	  /* FIXME: Do error reporting and/or recovery */
	  g_assert_not_reached ();
	}
      fo_expr_context_next (context);
      fo_expr_context_skip_blanks (context);
    }
  else if (fo_expr_context_cur (context) == '#')
    {
      eval_color (context);
    }
  else if (fo_expr_context_cur (context) == '+')
    {
      fo_expr_context_next (context);
      fo_expr_context_skip_blanks (context);

      if (g_ascii_isdigit (fo_expr_context_cur (context)) ||
	  fo_expr_context_cur (context) == '.')
	{
	  eval_numeric (context);
	}
      else
	{
	  FoDatatype *result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_FAILED);
	  fo_expr_context_push_stack (context, result_datatype);
	}
    }
  else if (IS_NUMERIC (context))
    {
      eval_numeric (context);
    }
  else if ((fo_expr_context_cur (context) == '\'') ||
	   (fo_expr_context_cur (context) == '"'))
    {
      eval_literal (context);
    }
  else
    {
      gchar *name = parse_ncname (context);

      if (name != NULL)
	{
	  if (strcmp (name, "inherit") == 0)
	    {
	      eval_inherit (context);
	    }
	  else
	    {
	      fo_expr_context_skip_blanks (context);
	      if (fo_expr_context_cur (context) != '(')
		{
		  eval_enum (context, name);
		}
	      else
		{
		  if (strcmp (name, "url") == 0)
		    {
		      eval_url (context);
		    }
		  else
		    {
		      eval_function_call (context, name);
		    }
		}
	    }

	  g_free (name);
	}
      else
	{
	  /*
	   * No name means expression doesn't match grammar since
	   * exhausted all other options.
	   */
	  FoDatatype *result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_FAILED);
	  fo_expr_context_push_stack (context, result_datatype);
	}
    }
  fo_expr_context_skip_blanks (context);
}

/**
 * eval_unary_expr:
 * @context: 
 *
 * Compile a Unary expression:
 * 
 *  [13]    UnaryExpr ::=   PrimaryExpr
 *                   | '-' UnaryExpr
 **/
static void
eval_unary_expr (FoExprContext *context)
{
  gboolean negate = FALSE;

  fo_expr_context_skip_blanks (context);

  while (fo_expr_context_cur (context) == '-')
    {
      negate = !negate;
      fo_expr_context_next (context);
      fo_expr_context_skip_blanks (context);
    }

  eval_primary_expr (context);
  RETURN_IF_ERROR;

  if (negate)
    {
      FoDatatype *arg = fo_expr_context_pop_stack (context);
      FoDatatype *result_datatype = NULL;
  
      result_datatype = fo_datatype_negate (arg);
      fo_expr_context_push_stack (context, result_datatype);
    }
}

/**
 * eval_multiplicative_expr:
 * @context: 
 *
 * Compile a Multiplicative expression:
 * 
 *  [12]   MultiplicativeExpr ::=   UnaryExpr 
 *                   | MultiplicativeExpr MultiplyOperator UnaryExpr 
 *                   | MultiplicativeExpr 'div' UnaryExpr 
 *                   | MultiplicativeExpr 'mod' UnaryExpr 
 *  [23]   MultiplyOperator ::=   '*'
 * 
 * Errors:
 *
 * Section 5.9.11, Lexical Structure:
 *
 *   If a NCName follows a numeric, it should be recognised as an
 *   OperatorName or it is an error.
 *
 * Handle this by checking that 'div' and 'mod' aren't followed by an
 * NCNameChar.
 **/
static void
eval_multiplicative_expr (FoExprContext *context)
{
  eval_unary_expr (context);
  RETURN_IF_ERROR;
  fo_expr_context_skip_blanks (context);

  while ((fo_expr_context_cur (context) == '*') || 
	 ((fo_expr_context_cur (context) == 'd')
	  && (fo_expr_context_peek (context, 1) == 'i') &&
	  (fo_expr_context_peek (context, 2) == 'v')) ||
	 ((fo_expr_context_cur (context) == 'm') &&
	  (fo_expr_context_peek (context, 1) == 'o') &&
	  (fo_expr_context_peek (context, 2) == 'd')))
    {
      FoExprFunc expr_func = NULL;
      FoDatatype *result_datatype = NULL;

      if (fo_expr_context_cur (context) == '*')
	{
	  expr_func = fo_expr_context_get_func (context, "*");
	  fo_expr_context_next (context);
	}
      else if (fo_expr_context_cur (context) == 'd')
	{
	  fo_expr_context_skip (context, 3);

	  if (!is_ncnamechar (context))
	    {
	      expr_func = fo_expr_context_get_func (context, "div");
	    }
	}
      else if (fo_expr_context_cur (context) == 'm')
	{
	  fo_expr_context_skip (context, 3);

	  if (!is_ncnamechar (context))
	    {
	      expr_func = fo_expr_context_get_func (context, "mod");
	    }
	}

      if (expr_func != NULL)
	{
	  fo_expr_context_skip_blanks (context);

	  eval_unary_expr (context);
	  RETURN_IF_ERROR;

	  result_datatype = expr_func (context, 2);
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
					 FO_EXPR_EVAL_ERROR_UNKNOWN_OPERATOR);

	}

      fo_expr_context_push_stack (context, result_datatype);
      RETURN_IF_ERROR;
      fo_expr_context_skip_blanks (context);
    }
}

/**
 * eval_additive_expr:
 * @context:
 *
 * Compile an additive expression.
 *
 *  [11]   AdditiveExpr ::=   MultiplicativeExpr
 *                   | AdditiveExpr '+' MultiplicativeExpr
 *                   | AdditiveExpr '-' MultiplicativeExpr
 */
static void
eval_additive_expr (FoExprContext *context)
{
  eval_multiplicative_expr (context);
  RETURN_IF_ERROR;
  fo_expr_context_skip_blanks (context);

  while ((fo_expr_context_cur (context) == '+') ||
	 (fo_expr_context_cur (context) == '-'))
    {
      FoExprFunc expr_func = NULL;
      FoDatatype *result_datatype = NULL;

      if (fo_expr_context_cur (context) == '+')
	{
	  expr_func = fo_expr_context_get_func (context, "+");
	}
      else if (fo_expr_context_cur (context) == '-')
	{
	  expr_func = fo_expr_context_get_func (context, "-");
	}

      if (expr_func != NULL)
	{
	  fo_expr_context_next (context);
	  fo_expr_context_skip_blanks (context);

	  eval_multiplicative_expr (context);
	  RETURN_IF_ERROR;

	  result_datatype = expr_func (context, 2);
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_UNKNOWN_OPERATOR);
	}

      fo_expr_context_push_stack (context, result_datatype);
      RETURN_IF_ERROR;
      fo_expr_context_skip_blanks (context);
    }
}

/**
 * fo_expr_eval:
 * @string:               String form of expression.
 * @property_name:        Name of property being evaluated.
 * @resolve_enum_func:    Function used to resolve enumeration tokens.
 * @resolve_percent_func: Function used to resolve percentage values.
 * @font_size_prop:       Current font size property.
 * @current_fo:           Current formatting object.
 * @fo_context:           #FoContext for inherited values.
 * @env_list:             List of #FoExprEnv for evaluating expressions.
 * @error:                #GError for reporting errors.
 * 
 * Evaluates @string as an XSL expression.
 * 
 * Return value: The result of evaluating @string, or NULL if an error
 *               occurred
 **/
FoDatatype*
fo_expr_eval (const gchar         *string,
	      const gchar         *property_name,
	      FoResolveEnumFunc    resolve_enum_func,
	      FoResolvePercentFunc resolve_percent_func,
	      const FoProperty    *font_size_prop,
	      const FoFo          *current_fo,
	      const FoContext     *fo_context,
	      const GSList        *env_list,
	      GError             **error)
{
  FoExprContext *context;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (string != NULL &&
			IS_CHAR (g_utf8_get_char (string)),
			NULL);
  g_return_val_if_fail (property_name != NULL &&
			IS_CHAR (g_utf8_get_char (property_name)),
			NULL);
  g_return_val_if_fail ((font_size_prop) == NULL ||
			FO_IS_PROPERTY_FONT_SIZE (font_size_prop),
			NULL);
  g_return_val_if_fail (FO_IS_FO (current_fo), NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);
  g_return_val_if_fail (env_list != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);
  /* Can't make assertion about resolve_enum_func since it can be NULL */
  /* Can't make assertion about resolve_percent_func since it can be NULL */

  context = fo_expr_context_new (string,
				 property_name,
				 resolve_enum_func,
				 resolve_percent_func,
				 font_size_prop,
				 current_fo,
				 fo_context,
				 env_list);

  eval_additive_expr (context);

  result_datatype = fo_expr_context_pop_stack (context);

  /* Check for possible error conditions */
  if (result_datatype == NULL)
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_NULL_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_NULL_RESULT]));
    }
  else if (FO_IS_ERROR (result_datatype))
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_ERROR_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_ERROR_RESULT]));
    }
  else if (!fo_expr_context_stack_is_empty (context))
    {
      gchar *string = fo_object_sprintf (fo_expr_context_peek_stack (context));

      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_STACK,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_STACK]),
		   string);

      g_free (string);
    }
  else if (fo_expr_context_cur (context) != '\0')
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_EXPR,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_EXPR]),
		   fo_expr_context_cur_ptr (context));
    }

  fo_expr_context_free (context);
  context = NULL;

  return result_datatype;
}

/**
 * convert_to_tblr:
 * @context: #FoExprContext
 * 
 * Convert the stack of #FoDatatype in @context to a #FoTblr.
 **/
static void
convert_to_tblr (FoExprContext *context)
{
  /*
   * There could be as few as one or as many as four items on the
   * stack.  The items will be on the stack in the order in which
   * they were evaluated.  For example, when the spec says "If
   * there are two values, the top and bottom paddings are set to
   * the first value and the right and left paddings are set to
   * the second.", the first value popped off the stack applies to
   * the left and right paddings, and the second, to the top and
   * bottom paddings.
   *
   * From the spec for 'border-padding':
   *
   *    If there is only one value, it applies to all sides. If
   *    there are two values, the top and bottom paddings are set
   *    to the first value and the right and left paddings are set
   *    to the second. If there are three values, the top is set
   *    to the first value, the left and right are set to the
   *    second, and the bottom is set to the third.  If there are
   *    four values, they apply to the top, right, bottom, and
   *    left, respectively.
   *
   * Popping entries off the stack until there's a null gives:
   *
   * First:	  All sides	Left, right	Bottom		Left
   * Second:  -		Top, bottom	Left, right	Bottom
   * Third:   -		-		Top		Right
   * Fourth:  -		-		-		Top
   *
   * Going from stack entries to components gives:
   *
   *          One entry	Two entries	Three entries	Four entries
   * Top:	Top		Second		Third		Fourth
   * Bottom:  Top		Second		First		Second
   * Left:    Top		First		Second		First
   * Right:   Top		First		Second		Third
   *
   * A fifth entry on the stack indicates an error.
   */

  FoDatatype *result_datatype = NULL;

  /* First stack entry */
  FoDatatype *stack_first = fo_expr_context_pop_stack (context);

  /* Handle possible conditions for top stack entry. */
  if (stack_first == NULL)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_NULL_RESULT);
      goto push;
    }
  else if (FO_IS_ERROR (stack_first))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_ERROR_RESULT);
      goto push;
    }

  /* Second stack entry */
  FoDatatype *stack_second = fo_expr_context_pop_stack (context);

  /* Handle possible conditions for second stack entry. */
  if (stack_second == NULL)
    {
      result_datatype = fo_tblr_new_from_values (stack_first,
						 stack_first,
						 stack_first,
						 stack_first);
      goto push;
    }
  else if (FO_IS_ERROR (stack_second))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_ERROR_RESULT);
      goto push;
    }

  /* third stack entry */
  FoDatatype *stack_third = fo_expr_context_pop_stack (context);

  /* Handle possible conditions for third stack entry. */
  if (stack_third == NULL)
    {
      result_datatype = fo_tblr_new_from_values (stack_second,
						 stack_second,
						 stack_first,
						 stack_first);
      goto push;
    }
  else if (FO_IS_ERROR (stack_third))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_ERROR_RESULT);
      goto push;
    }

  /* fourth stack entry */
  FoDatatype *stack_fourth = fo_expr_context_pop_stack (context);

  /* Handle possible conditions for fourth stack entry. */
  if (stack_fourth == NULL)
    {
      result_datatype = fo_tblr_new_from_values (stack_third,
						 stack_first,
						 stack_second,
						 stack_second);
      goto push;
    }
  else if (FO_IS_ERROR (stack_fourth))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_ERROR_RESULT);
      goto push;
    }
  else
    {
      result_datatype = fo_tblr_new_from_values (stack_fourth,
						 stack_second,
						 stack_first,
						 stack_third);
      goto push;
    }

 push:
  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * eval_padding_expr:
 *
 * <padding-width>{1,4} | inherit
 **/
static void
eval_padding_expr (FoExprContext *context)
{
  fo_expr_context_skip_blanks (context);

  gchar *name = parse_ncname (context);

  if (name == NULL)
    {
      /* If not a name, then one to four <padding-width> values. */

      do
	{
	  FoDatatype *intermediate_value = NULL;
	  gboolean negate = FALSE;

	  fo_expr_context_skip_blanks (context);

	  while (fo_expr_context_cur (context) == '-')
	    {
	      negate = !negate;
	      fo_expr_context_next (context);
	      fo_expr_context_skip_blanks (context);
	    }

	  if (IS_NUMERIC (context))
	    {
	      gdouble number = parse_number (context);

	      fo_expr_context_skip_blanks (context);

	      if (fo_expr_context_cur (context) == '%')
		{
		  intermediate_value = parse_percentage (context, number);
		}
	      else if (is_unit_name (context))
		{
		  intermediate_value = parse_length (context, number);
		}
	      else
		{
		  intermediate_value =
		    fo_expr_eval_new_error (context,
					    FO_EXPR_EVAL_ERROR_FAILED);
		}
	    }
	  else
	    {
	      intermediate_value =
		fo_expr_eval_new_error (context,
					FO_EXPR_EVAL_ERROR_FAILED);
	    }

	  RETURN_IF_ERROR;

	  fo_expr_context_push_stack (context, intermediate_value);

	  if (negate)
	    {
	      FoDatatype *arg = fo_expr_context_pop_stack (context);
  
	      intermediate_value = fo_datatype_negate (arg);
	      fo_expr_context_push_stack (context, intermediate_value);
	    }

	  RETURN_IF_ERROR;
	}
      while (g_ascii_isspace (fo_expr_context_cur (context)));

      convert_to_tblr(context);
    }
  else
    {
      FoDatatype *result_datatype = NULL;

      /* If the expression is a name, there's only one valid name: 'inherit'. */
      if (strcmp (name, "inherit") == 0)
	{
	  fo_expr_context_skip_blanks (context);

	  if (fo_expr_context_cur (context) == '\0')
	    {
	      eval_inherit (context);
	      g_free (name);
	    }
	  else
	    {
	      result_datatype =
		fo_expr_eval_new_error (context,
					FO_EXPR_EVAL_ERROR_FAILED);
	    }
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_FAILED);
	}

      fo_expr_context_push_stack (context, result_datatype);
    }
}

/**
 * fo_expr_padding_eval:
 * @string:               String form of expression.
 * @property_name:        Name of property being evaluated.
 * @resolve_enum_func:    Function used to resolve enumeration tokens.
 * @resolve_percent_func: Function used to resolve percentage values.
 * @font_size_prop:       Current font size property.
 * @current_fo:           Current formatting object.
 * @fo_context:           #FoContext for inherited values.
 * @env_list:             List of #FoExprEnv for evaluating expressions.
 * @error:                #GError for reporting errors.
 * 
 * Evaluates @string as an XSL expression.
 * 
 * Return value: The result of evaluating @string, or NULL if an error
 *               occurred
 **/
FoDatatype*
fo_expr_padding_eval (const gchar         *string,
		      const gchar         *property_name,
		      FoResolveEnumFunc    resolve_enum_func,
		      FoResolvePercentFunc resolve_percent_func,
		      const FoProperty    *font_size_prop,
		      const FoFo          *current_fo,
		      const FoContext     *fo_context,
		      const GSList        *env_list,
		      GError             **error)
{
  FoExprContext *context;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (string)), NULL);
  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (property_name)), NULL);
  g_return_val_if_fail ((font_size_prop) == NULL ||
			FO_IS_PROPERTY_FONT_SIZE (font_size_prop),
			NULL);
  g_return_val_if_fail (FO_IS_FO (current_fo), NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);
  g_return_val_if_fail (env_list != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);
  /* Can't make assertion about resolve_enum_func since it can be NULL */
  /* Can't make assertion about resolve_percent_func since it can be NULL */

  context = fo_expr_context_new (string,
				 property_name,
				 resolve_enum_func,
				 resolve_percent_func,
				 font_size_prop,
				 current_fo,
				 fo_context,
				 env_list);

  eval_padding_expr (context);

  result_datatype = fo_expr_context_pop_stack (context);

  /* Check for possible error conditions */
  if (result_datatype == NULL)
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_NULL_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_NULL_RESULT]));
    }
  else if (FO_IS_ERROR (result_datatype))
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_ERROR_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_ERROR_RESULT]));
    }
  else if (!fo_expr_context_stack_is_empty (context))
    {
      gchar *string = fo_object_sprintf (fo_expr_context_peek_stack (context));

      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_STACK,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_STACK]),
		   string);

      g_free (string);
    }
  else if (fo_expr_context_cur (context) != '\0')
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_EXPR,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_EXPR]),
		   fo_expr_context_cur_ptr (context));
    }

  fo_expr_context_free (context);
  context = NULL;

  return result_datatype;
}

/**
 * eval_border_color_expr:
 *
 * [<color>|transparent]{1,4} | inherit
 **/
static void
eval_border_color_expr (FoExprContext *context)
{
  /* If not 'inherit', then one to four <color> or 'transparent' values. */
  do
    {
      FoDatatype *intermediate_value = NULL;
  
      fo_expr_context_skip_blanks (context);

      if (fo_expr_context_cur (context) == '#')
	{
	  eval_color (context);
	}
      else if ((fo_expr_context_cur (context) == '\'') ||
	       (fo_expr_context_cur (context) == '"'))
	{
	  eval_literal (context);
	}
      else
	{
	  gchar *name = parse_ncname (context);

	  if (name != NULL)
	    {
	      eval_enum (context, name);

	      g_free (name);
	    }
	  else
	    {
	      /*
	       * No name means expression doesn't match grammar since
	       * exhausted all other options.
	       */
	      intermediate_value =
		fo_expr_eval_new_error (context,
					FO_EXPR_EVAL_ERROR_FAILED);
	      fo_expr_context_push_stack (context, intermediate_value);
	    }

	  RETURN_IF_ERROR;

	}
    }
  while (g_ascii_isspace (fo_expr_context_cur (context)));

  convert_to_tblr(context);
}

/**
 * fo_expr_border_color_eval:
 * @string:               String form of expression.
 * @property_name:        Name of property being evaluated.
 * @resolve_enum_func:    Function used to resolve enumeration tokens.
 * @resolve_percent_func: Function used to resolve percentage values.
 * @font_size_prop:       Current font size property.
 * @current_fo:           Current formatting object.
 * @fo_context:           #FoContext for inherited values.
 * @env_list:             List of #FoExprEnv for evaluating expressions.
 * @error:                #GError for reporting errors.
 * 
 * Evaluates @string as an XSL expression.
 * 
 * Return value: The result of evaluating @string, or NULL if an error
 *               occurred
 **/
FoDatatype *
fo_expr_border_color_eval (const gchar         *string,
			   const gchar         *property_name,
			   FoResolveEnumFunc    resolve_enum_func,
			   FoResolvePercentFunc resolve_percent_func,
			   const FoProperty    *font_size_prop,
			   const FoFo          *current_fo,
			   const FoContext     *fo_context,
			   const GSList        *env_list,
			   GError             **error)
{
  FoExprContext *context;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (string)), NULL);
  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (property_name)), NULL);
  g_return_val_if_fail ((font_size_prop) == NULL ||
			FO_IS_PROPERTY_FONT_SIZE (font_size_prop),
			NULL);
  g_return_val_if_fail (FO_IS_FO (current_fo), NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);
  g_return_val_if_fail (env_list != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);
  /* Can't make assertion about resolve_enum_func since it can be NULL */
  /* Can't make assertion about resolve_percent_func since it can be NULL */

  context = fo_expr_context_new (string,
				 property_name,
				 resolve_enum_func,
				 resolve_percent_func,
				 font_size_prop,
				 current_fo,
				 fo_context,
				 env_list);

  eval_border_color_expr (context);

  result_datatype = fo_expr_context_pop_stack (context);

  /* Check for possible error conditions */
  if (result_datatype == NULL)
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_NULL_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_NULL_RESULT]));
    }
  else if (FO_IS_ERROR (result_datatype))
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_ERROR_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_ERROR_RESULT]));
    }
  else if (!fo_expr_context_stack_is_empty (context))
    {
      gchar *string = fo_object_sprintf (fo_expr_context_peek_stack (context));

      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_STACK,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_STACK]),
		   string);

      g_free (string);
    }
  else if (fo_expr_context_cur (context) != '\0')
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_EXPR,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_EXPR]),
		   fo_expr_context_cur_ptr (context));
    }

  fo_expr_context_free (context);
  context = NULL;

  return result_datatype;
}

/**
 * eval_border_style_expr:
 *
 * <border-style>{1,4} | inherit
 **/
static void
eval_border_style_expr (FoExprContext *context)
{
    /* If not 'inherit', then one to four <color> or 'transparent' values. */
    do
    {
	FoDatatype *intermediate_value = NULL;
  
	fo_expr_context_skip_blanks (context);

	gchar *name = parse_ncname (context);

	if (name != NULL)
	  {
	      eval_enum (context, name);

	      g_free (name);
	  }
	else
	  {
	      /*
	       * No name means expression doesn't match grammar since
	       * exhausted all other options.
	       */
	      intermediate_value =
		  fo_expr_eval_new_error (context,
					  FO_EXPR_EVAL_ERROR_FAILED);
	      fo_expr_context_push_stack (context, intermediate_value);
	  }

	RETURN_IF_ERROR;
    }
    while (g_ascii_isspace (fo_expr_context_cur (context)));

    convert_to_tblr(context);
}

/**
 * fo_expr_border_style_eval:
 * @string:               String form of expression.
 * @property_name:        Name of property being evaluated.
 * @resolve_enum_func:    Function used to resolve enumeration tokens.
 * @resolve_percent_func: Function used to resolve percentage values.
 * @font_size_prop:       Current font size property.
 * @current_fo:           Current formatting object.
 * @fo_context:           #FoContext for inherited values.
 * @env_list:             List of #FoExprEnv for evaluating expressions.
 * @error:                #GError for reporting errors.
 * 
 * Evaluates @string as an XSL expression.
 * 
 * Return value: The result of evaluating @string, or NULL if an error
 *               occurred
 **/
FoDatatype *
fo_expr_border_style_eval (const gchar         *string,
			   const gchar         *property_name,
			   FoResolveEnumFunc    resolve_enum_func,
			   FoResolvePercentFunc resolve_percent_func,
			   const FoProperty    *font_size_prop,
			   const FoFo          *current_fo,
			   const FoContext     *fo_context,
			   const GSList        *env_list,
			   GError             **error)
{
  FoExprContext *context;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (string)), NULL);
  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (property_name)), NULL);
  g_return_val_if_fail ((font_size_prop) == NULL ||
			FO_IS_PROPERTY_FONT_SIZE (font_size_prop),
			NULL);
  g_return_val_if_fail (FO_IS_FO (current_fo), NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);
  g_return_val_if_fail (env_list != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);
  /* Can't make assertion about resolve_enum_func since it can be NULL */
  /* Can't make assertion about resolve_percent_func since it can be NULL */

  context = fo_expr_context_new (string,
				 property_name,
				 resolve_enum_func,
				 resolve_percent_func,
				 font_size_prop,
				 current_fo,
				 fo_context,
				 env_list);

  eval_border_style_expr (context);

  result_datatype = fo_expr_context_pop_stack (context);

  /* Check for possible error conditions */
  if (result_datatype == NULL)
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_NULL_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_NULL_RESULT]));
    }
  else if (FO_IS_ERROR (result_datatype))
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_ERROR_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_ERROR_RESULT]));
    }
  else if (!fo_expr_context_stack_is_empty (context))
    {
      gchar *string = fo_object_sprintf (fo_expr_context_peek_stack (context));

      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_STACK,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_STACK]),
		   string);

      g_free (string);
    }
  else if (fo_expr_context_cur (context) != '\0')
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_EXPR,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_EXPR]),
		   fo_expr_context_cur_ptr (context));
    }

  fo_expr_context_free (context);
  context = NULL;

  return result_datatype;
}

/**
 * convert_to_wsc:
 * @context: #FoExprContext
 * 
 * Convert the stack of #FoDatatype in @context to a #FoWsc.
 **/
static void
convert_to_wsc (FoExprContext *context)
{
  /*
   * There could be as few as one or as many as three items on the
   * stack.  The items will be on the stack in the order in which
   * they were evaluated.
   *
   * A fourth entry on the stack indicates an error.
   */

  /* Result to return on stack. */
  FoDatatype *result_datatype = NULL;
  /* FoWsc as popped off stack. */
  FoDatatype *wsc_datatype = NULL;
  /*
   * Components of FoWsc (that will be returned if no errors
   * occur).
   */
  FoDatatype *width_datatype = NULL;
  FoDatatype *style_datatype = NULL;
  FoDatatype *color_datatype = NULL;

  /* First stack entry */
  FoDatatype *stack_first = fo_expr_context_pop_stack (context);

  /* Handle possible conditions for top stack entry. */
  if (stack_first == NULL)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_NULL_RESULT);
      goto push;
    }
  else if (FO_IS_ERROR (stack_first))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_ERROR_RESULT);
      goto push;
    }

  if (FO_IS_WSC (stack_first))
    {
      wsc_datatype = stack_first;

      if (fo_wsc_get_width (wsc_datatype) != NULL)
	{
	  width_datatype = fo_wsc_get_width (wsc_datatype);
	}
      else if (fo_wsc_get_style (wsc_datatype) != NULL)
	{
	  style_datatype = fo_wsc_get_style (wsc_datatype);
	}
      else if (fo_wsc_get_color (wsc_datatype) != NULL)
	{
	  color_datatype = fo_wsc_get_color (wsc_datatype);
	}
    }

  /* Second stack entry */
  FoDatatype *stack_second = fo_expr_context_pop_stack (context);

  /* Handle possible conditions for second stack entry. */
  if (stack_second == NULL)
    {
      goto push_wsc;
    }
  else if (FO_IS_WSC (stack_second))
    {
      wsc_datatype = stack_second;

      if ((width_datatype == NULL) &&
	  (fo_wsc_get_width (wsc_datatype) != NULL))
	{
	  width_datatype = fo_wsc_get_width (wsc_datatype);
	}
      else if ((style_datatype == NULL) &&
	       (fo_wsc_get_style (wsc_datatype) != NULL))
	{
	  style_datatype = fo_wsc_get_style (wsc_datatype);
	}
      else if ((color_datatype == NULL) &&
	       (fo_wsc_get_color (wsc_datatype) != NULL))
	{
	  color_datatype = fo_wsc_get_color (wsc_datatype);
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_EXPR_ERROR);
	  goto push;
	}
    }
  else if (FO_IS_ERROR (stack_second))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_ERROR_RESULT);
      goto push;
    }

  /* Third stack entry */
  FoDatatype *stack_third = fo_expr_context_pop_stack (context);

  /* Handle possible conditions for third stack entry. */
  if (stack_third == NULL)
    {
      goto push_wsc;
    }
  else if (FO_IS_WSC (stack_third))
    {
      wsc_datatype = stack_third;

      if ((width_datatype == NULL) &&
	  (fo_wsc_get_width (wsc_datatype) != NULL))
	{
	  width_datatype = fo_wsc_get_width (wsc_datatype);
	}
      else if ((style_datatype == NULL) &&
	       (fo_wsc_get_style (wsc_datatype) != NULL))
	{
	  style_datatype = fo_wsc_get_style (wsc_datatype);
	}
      else if ((color_datatype == NULL) &&
	       (fo_wsc_get_color (wsc_datatype) != NULL))
	{
	  color_datatype = fo_wsc_get_color (wsc_datatype);
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_EXPR_ERROR);
	  goto push;
	}
    }
  else if (FO_IS_ERROR (stack_third))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_ERROR_ERROR_RESULT);
      goto push;
    }

 push_wsc:

  if (width_datatype == NULL)
    {
      width_datatype = g_object_ref (fo_property_util_get_width_initial ());
    }

  if (style_datatype == NULL)
    {
      style_datatype = g_object_ref (fo_property_util_get_style_initial ());
    }

  if (color_datatype == NULL)
    {
      color_datatype = g_object_ref (fo_property_util_get_color_initial ());
    }

  result_datatype = g_object_ref (fo_wsc_new_from_values (width_datatype,
							  style_datatype,
							  color_datatype));

 push:
  fo_expr_context_push_stack (context, result_datatype);
}

/**
 * eval_width_style_color_expr:
 *
 * [ <border-width> || <border-style> || <color> ] | inherit
 **/
static void
eval_width_style_color_expr (FoExprContext *context)
{
    /* If not 'inherit', then one to four <color> or 'transparent' values. */
    do
    {
	FoDatatype *intermediate_value = NULL;
  
	fo_expr_context_skip_blanks (context);

	if (fo_expr_context_cur (context) == '#')
	{
	    eval_color (context);
	}
	else if ((fo_expr_context_cur (context) == '\'') ||
		 (fo_expr_context_cur (context) == '"'))
	{
	    eval_literal (context);
	}
	else
	  {
	      gchar *name = parse_ncname (context);

	      if (name != NULL)
	      {
		  eval_enum (context, name);

		  g_free (name);
	      }
	      else
	      {
		  /*
		   * No name means expression doesn't match grammar since
		   * exhausted all other options.
		   */
		  intermediate_value =
		      fo_expr_eval_new_error (context,
					      FO_EXPR_EVAL_ERROR_FAILED);
		  fo_expr_context_push_stack (context, intermediate_value);
	      }

	      RETURN_IF_ERROR;
	  }
    }
    while (g_ascii_isspace (fo_expr_context_cur (context)));

    convert_to_wsc(context);
}

/**
 * fo_expr_wsc_eval:
 * @string:               String form of expression.
 * @property_name:        Name of property being evaluated.
 * @resolve_enum_func:    Function used to resolve enumeration tokens.
 * @resolve_percent_func: Function used to resolve percentage values.
 * @font_size_prop:       Current font size property.
 * @current_fo:           Current formatting object.
 * @fo_context:           #FoContext for inherited values.
 * @env_list:             List of #FoExprEnv for evaluating expressions.
 * @error:                #GError for reporting errors.
 * 
 * Evaluates @string as an XSL expression.
 * 
 * Return value: The result of evaluating @string, or NULL if an error
 *               occurred
 **/
FoDatatype *
fo_expr_wsc_eval (const gchar         *string,
		  const gchar         *property_name,
		  FoResolveEnumFunc    resolve_enum_func,
		  FoResolvePercentFunc resolve_percent_func,
		  const FoProperty    *font_size_prop,
		  const FoFo          *current_fo,
		  const FoContext     *fo_context,
		  const GSList        *env_list,
		  GError             **error)
{
  FoExprContext *context;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (string)), NULL);
  g_return_val_if_fail (IS_CHAR (g_utf8_get_char (property_name)), NULL);
  g_return_val_if_fail ((font_size_prop) == NULL ||
			FO_IS_PROPERTY_FONT_SIZE (font_size_prop),
			NULL);
  g_return_val_if_fail (FO_IS_FO (current_fo), NULL);
  g_return_val_if_fail (FO_IS_CONTEXT (fo_context), NULL);
  g_return_val_if_fail (env_list != NULL, NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);
  /* Can't make assertion about resolve_enum_func since it can be NULL */
  /* Can't make assertion about resolve_percent_func since it can be NULL */

  context = fo_expr_context_new (string,
				 property_name,
				 resolve_enum_func,
				 resolve_percent_func,
				 font_size_prop,
				 current_fo,
				 fo_context,
				 env_list);

  eval_width_style_color_expr (context);
  result_datatype = fo_expr_context_pop_stack (context);

  /* Check for possible error conditions */
  if (result_datatype == NULL)
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_NULL_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_NULL_RESULT]));
    }
  else if (FO_IS_ERROR (result_datatype))
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_ERROR_RESULT,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_ERROR_RESULT]));
    }
  else if (!fo_expr_context_stack_is_empty (context))
    {
      gchar *string = fo_object_sprintf (fo_expr_context_peek_stack (context));

      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_STACK,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_STACK]),
		   string);

      g_free (string);
    }
  else if (fo_expr_context_cur (context) != '\0')
    {
      g_set_error (error,
		   FO_EXPR_ERROR,
		   FO_EXPR_ERROR_EXTRA_EXPR,
		   _(fo_expr_error_messages[FO_EXPR_ERROR_EXTRA_EXPR]),
		   fo_expr_context_cur_ptr (context));
    }

  fo_expr_context_free (context);
  context = NULL;

  return result_datatype;
}
