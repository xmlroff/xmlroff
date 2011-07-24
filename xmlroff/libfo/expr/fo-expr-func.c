/* Fo
 * fo-expr-func.c: XSL expression language functions
 *
 * Copyright (C) 1998-2002 Daniel Veillard.
 * Copyright (C) 2001-2002 Sun Microsystems.
 * Copyright (C) 2007 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 * All Rights Reserved.
 *
 * Based on an XSL expression language evaluator that was based on the
 * 'XML Path Language implementation' in 'xpath.c' from libxml2 by
 * Daniel Veillard.
 *
 * See COPYING for the status of this software.
 */

#include "fo-expr-eval.h"
#include "fo-expr-func-private.h"
#include "fo-expr-context-private.h"
#include "fo/fo-list-block.h"
#include "fo/fo-table.h"
#include "fo/fo-table-column.h"
#include "fo/fo-table-cell.h"
#include "datatype/fo-all-datatype.h"
#include <string.h>

#define CHECK_ARITY(context, x)			    \
    if (nargs != (x))				    \
        return fo_expr_eval_new_error((context), \
				      FO_EXPR_EVAL_ERROR_INVALID_ARITY)
/**
 * fo_expr_func_abs:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the abs() XSL function
 *
 *    numeric abs(numeric)
 *
 * The abs function returns the absolute value of the numeric
 * argument.  That is, if the numeric argument is negative, it returns
 * the negation of the argument.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_abs (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 1);

  arg = fo_expr_context_pop_stack (context);

  return fo_datatype_abs (arg);
}

/**
 * fo_expr_func_add:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the addition operation on XSL numerics.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_add (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg1;
  FoDatatype *arg2;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 2);

  arg2 = fo_expr_context_pop_stack (context);
  arg1 = fo_expr_context_pop_stack (context);

  return fo_datatype_add (arg1,
			  arg2);
}

/**
 * fo_expr_func_body_start:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the body-start() XSL function
 *
 *    numeric body-start()
 * 
 * The body-start function returns the calculated body-start value for
 * lists.  See the definition in Section 7.28.4,
 * "provisional-distance-between-starts", of the XSL 1.0
 * Recommendation.
 * 
 * NOTE: When this function is used outside of a list, it still
 * returns a calculated value as specified.
 *
 * Return value: Calculated body-start value
 **/
FoDatatype*
fo_expr_func_body_start (FoExprContext *context,
			 gint           nargs)
{
  const FoFo *current_fo = NULL;
  FoNode *fo_list_block = NULL;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (context != NULL, NULL);

  current_fo = fo_expr_context_get_current_fo (context);

  if (nargs == 0)
    {
      fo_list_block =
	fo_node_get_ancestor_or_self_by_type (FO_NODE (current_fo),
					      FO_TYPE_LIST_BLOCK);
      if (fo_list_block != NULL)
	{
	  result_datatype =
	    g_object_ref (fo_list_block_get_body_start (FO_FO (fo_list_block)));
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_NOT_LIST_BLOCK_OR_DESCENDANT);
	}
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_ARITY);
    }

  return result_datatype;
}

/**
 * fo_expr_func_ceiling:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the ceiling() XSL function
 *
 *    number ceiling(number)
 *
 * The ceiling function returns the smallest (closest to negative
 * infinity) integer that is not less than the argument.  The numeric
 * argument to this function must be of unit power zero.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_ceiling (FoExprContext *context,
		      gint           nargs)
{
  FoDatatype *arg;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 1);

  arg = fo_expr_context_pop_stack (context);

  return fo_datatype_ceiling (arg);
}

/**
 * fo_expr_func_div:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the division operation on XSL numerics .
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_div (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg1;
  FoDatatype *arg2;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 2);

  arg2 = fo_expr_context_pop_stack (context);
  arg1 = fo_expr_context_pop_stack (context);

  return fo_datatype_div (arg1,
			  arg2);
}

/**
 * fo_expr_func_floor:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the floor() XSL function
 *
 *    numeric floor(numeric)
 *
 * The floor function returns the largest (closest to positive
 * infinity) integer that is not greater than the argument. The
 * numeric argument to this function must be of unit power zero.
 *
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_floor (FoExprContext *context,
		    gint           nargs)
{
  FoDatatype *arg;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 1);

  arg = fo_expr_context_pop_stack (context);

  return fo_datatype_floor (arg);
}

static gchar*
opt_arg_to_property_name (FoExprContext *context,
			  gint           nargs,
			  GError       **error)
{
  FoDatatype *arg = NULL;
  gchar *property_name = NULL;

  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  if (nargs == 0)
    {
      property_name =
	g_strdup (fo_expr_context_get_property_name (context));
    }
  else if (nargs == 1)
    {
      arg = fo_expr_context_pop_stack (context);

      if (FO_IS_STRING (arg))
	{
	  property_name = fo_string_get_value (arg);
	}
      else if (FO_IS_NAME (arg))
	{
	  property_name = fo_name_get_value (arg);
	}
      else
	{
	  g_set_error (error,
		       FO_EXPR_EVAL_ERROR,
		       FO_EXPR_EVAL_ERROR_INVALID_TYPE,
		       "%s",
		       fo_expr_eval_error_messages[FO_EXPR_EVAL_ERROR_INVALID_TYPE]);
	}

      g_object_unref (arg);
    }
  else
    {
	  g_set_error (error,
		       FO_EXPR_EVAL_ERROR,
		       FO_EXPR_EVAL_ERROR_INVALID_ARITY,
		       "%s",
		       fo_expr_eval_error_messages[FO_EXPR_EVAL_ERROR_INVALID_ARITY]);
    }

  return property_name;
}

/**
 * fo_expr_func_from_nearest_specified_value:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the from-nearest-specified-value() XSL function
 *
 *    object from-nearest-specified-value(NCName?)
 *
 * The from-nearest-specified-value function returns a computed value
 * of the property whose name matches the argument specified, or if
 * omitted for the property for which the expression is being
 * evaluated.  The value returned is that for the closest ancestor of
 * the formatting object for which the expression is evaluated on
 * which there is an assignment of the property in the XML result tree
 * in the fo namespace.  If there is no such ancestor, the value
 * returned is the initial value.  If the argument specifies a
 * shorthand property and if the expression only consists of the
 * from-nearest-specified-value function with an argument matching the
 * property being computed, it is interpreted as an expansion of the
 * shorthand with each property into which the shorthand expands, each
 * having a value of from-nearest-specified-value with an argument
 * matching the property.  It is an error if arguments matching a
 * shorthand property are used in any other way.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_from_nearest_specified_value (FoExprContext *context,
					   gint           nargs)
{
  FoProperty *property = NULL;
  FoDatatype *result_datatype = NULL;
  GError *error = NULL;
  gchar *property_name = NULL;

  property_name = opt_arg_to_property_name (context,
					    nargs,
					    &error);

  if (error != NULL)
    {
      if (property_name != NULL)
	{
	  g_free (property_name);
	}

      result_datatype =
	fo_expr_eval_propagate_error (context,
				      error);
    }
  else
    {
      if (g_type_from_name (property_name) != 0)
	{
	  g_object_get ((FoContext *) fo_expr_context_get_fo_context (context),
			property_name,
			&property,
			NULL);

	  result_datatype = g_object_ref (fo_property_get_value (property));
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
	}
    }

  g_free (property_name);

  return result_datatype;
}

/**
 * fo_expr_func_from_parent:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the from-parent() XSL function
 *
 *    object from-parent(NCName?)
 *
 * The from-parent function returns a computed value of the property
 * whose name matches the argument specified, or if omitted for the
 * property for which the expression is being evaluated.  The value
 * returned is that for the parent of the formatting object for which
 * the expression is evaluated.  If there is no parent, the value
 * returned is the initial value. If the argument specifies a
 * shorthand property and if the expression only consists of the
 * from-parent function with an argument matching the property being
 * computed, it is interpreted as an expansion of the shorthand with
 * each property into which the shorthand expands, each having a value
 * of from-parent with an argument matching the property.  It is an
 * error if arguments matching a shorthand property are used in any
 * other way.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_from_parent (FoExprContext *context,
			  gint           nargs)
{
  FoFo *use_from = NULL;
  FoFo *current_fo = NULL;
  FoProperty *property = NULL;
  FoDatatype *result_datatype = NULL;
  GError *error = NULL;
  const gchar *property_name = NULL;

  g_return_val_if_fail (context != NULL, NULL);

  property_name = opt_arg_to_property_name (context,
					    nargs,
					    &error);

  if (error != NULL)
    {
      result_datatype =
	fo_expr_eval_propagate_error (context,
				      error);
      goto error;
    }

  current_fo = (FoFo *) fo_expr_context_get_current_fo (context);
  if (fo_node_parent (FO_NODE (current_fo)) != NULL)
    {
      use_from =
	FO_FO (fo_node_parent (FO_NODE (current_fo)));
    }
  else if (fo_fo_get_tree (current_fo) != NULL)
    {
      use_from =
	FO_FO (fo_fo_get_tree (current_fo));
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_CANNOT_INHERIT);
      goto error;
    }

  if (fo_fo_get_context (use_from) != NULL &&
      g_object_class_find_property (G_OBJECT_GET_CLASS (use_from),
				    property_name))
    {
      g_object_get (fo_fo_get_context (use_from),
		    property_name,
		    &property,
		    NULL);

      result_datatype = g_object_ref (fo_property_get_value (property));
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
    }

 error:

  return result_datatype;
}

/**
 * fo_expr_func_from_table_column:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the from-table-column() XSL function
 *
 *    object from-table-column(NCName?)
 *
 * The from-table-column function returns the inherited value of the
 * property whose name matches the argument specified, or if omitted
 * for the property for which the expression is being evaluated, from
 * the fo:table-column whose column-number matches the column for
 * which this expression is evaluated and whose number-columns-spanned
 * also matches any span.  If there is no match for the
 * number-columns-spanned, it is matched against a span of 1. If there
 * is still no match, the initial value is returned.  It is an error
 * to use this function on formatting objects that are not an
 * fo:table-cell or its descendants.
 * 
 * Non-standard behaviour: return an error if the current property is
 * column-number or number-columns-spanned, since those properties
 * need to already be evaluated in order to determine the correct
 * table-column FO from which to inherit properties.
 *
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_from_table_column (FoExprContext *context,
				gint           nargs)
{
  FoNode *fo_node = NULL;
  FoFo *current_fo = NULL;
  FoFo *column = NULL;
  FoContext *use_fo_context = NULL;
  FoProperty *property = NULL;
  FoDatatype *result_datatype = NULL;
  GError *error = NULL;
  const gchar *property_name = NULL;
  const gchar *use_property_name = NULL;

  g_return_val_if_fail (context != NULL, NULL);

  /* from-table-column() is meaningless for 'column-number' and
     'number-columns-spanned' properties. */
  property_name = fo_expr_context_get_property_name (context);
  if ((strcmp (property_name, "column-number") == 0) ||
      (strcmp (property_name, "number-columns-spanned") == 0))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
      goto error;
    }

  current_fo = (FoFo *) fo_expr_context_get_current_fo (context);
  fo_node = fo_node_get_ancestor_or_self_by_type (FO_NODE (current_fo),
						  FO_TYPE_TABLE_CELL);
  if (fo_node == NULL)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_TABLE_CELL_OR_DESCENDANT);
      goto error;
    }

  property_name = opt_arg_to_property_name (context,
					    nargs,
					    &error);

  if (error != NULL)
    {
      result_datatype =
	fo_expr_eval_propagate_error (context,
				      error);
      goto error;
    }

  if (g_type_from_name (property_name) == 0)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
      goto error;
    }

  if (g_type_from_name (property_name) != 0)
    {
      FoPropertyClass *class =
	g_type_class_ref (g_type_from_name (property_name));

      if (FO_IS_PROPERTY_CLASS (class))
	{
	  if (!fo_property_class_is_inherited (class))
	    {
	      result_datatype =
		fo_expr_eval_new_error (context,
					FO_EXPR_EVAL_ERROR_NOT_INHERITED);
	      g_type_class_unref (class);
	      goto error;
	    }
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
	  g_type_class_unref (class);
	  goto error;
	}

      g_type_class_unref (class);
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
      goto error;
    }

  column = fo_table_cell_get_column (FO_FO (fo_node));

#if defined(LIBFO_DEBUG) && 0
  g_message ("from-table-column:: property: %s; column: %s; is-inherited: %d",
	     property_name,
	     fo_object_debug_sprintf (column),
	     fo_property_is_inherited (property));
#endif

  if (column != NULL)
    {
      use_fo_context = fo_fo_get_context (column);
    }
  else
    {
      FoFo *fo_tree =
	fo_fo_get_tree ((FoFo *) fo_expr_context_get_current_fo (context));

      use_fo_context =
	fo_fo_get_context (fo_tree);
    }

  if (g_object_class_find_property (G_OBJECT_GET_CLASS (use_fo_context),
				    property_name))
    {
      g_object_get (use_fo_context,
		    use_property_name,
		    &property,
		    NULL);

      result_datatype = fo_property_get_value (property);
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
    }

 error:

  return result_datatype;
}

/**
 * fo_expr_func_inherited_property_value:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the inherited-property-value() XSL function
 *
 *    object inherited-property-value(NCName?)
 *
 * The inherited-property-value function returns the inherited value
 * of the property whose name matches the argument specified, or if
 * omitted for the property for which the expression is being
 * evaluated.  It is an error if this property is not an inherited
 * property.
 *
 * The returned "inherited value" is the computed value of this
 * property on this object's parent. In particular, given the
 * following example:
 * 
 * <fo:list-block>
 *   ...
 *   <fo:list-item color="red">
 *     <fo:list-item-body background-color="green">
 *       <fo:block background-color="inherited-property-value(color)">
 *       </fo:block>
 *     </fo:list-item-body>
 *   </fo:list-item>
 * </fo:list-block>
 * 
 * The background-color property on the fo:block is assigned the value
 * "red" because the (computed, after inheritance) value of the color
 * (not background-color) property on the fo:list-item-body that is
 * the parent of fo:block is "red".
 *
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_inherited_property_value (FoExprContext *context,
				       gint           nargs)
{
  FoDatatype *arg = NULL;
  FoDatatype *result_datatype = NULL;
  const gchar *property_name = NULL;

  g_return_val_if_fail (context != NULL, NULL);

  if (nargs == 1)
    {
      arg = fo_expr_context_pop_stack (context);

      if (FO_IS_STRING (arg))
	{
	  property_name = fo_string_get_value (arg);
	}
      else if (FO_IS_NAME (arg))
	{
	  property_name = fo_name_get_value (arg);
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_INVALID_TYPE);
	  g_object_unref (arg);

	  goto error;
	}

      g_object_unref (arg);
    }
  else if (nargs == 0)
    {
      property_name = fo_expr_context_get_property_name (context);
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_TYPE);

      goto error;
    }


  if (g_type_from_name (property_name) != 0)
    {
      FoPropertyClass *class =
	g_type_class_ref (g_type_from_name (property_name));

      if (FO_IS_PROPERTY_CLASS (class))
	{
	  if (fo_property_class_is_inherited (class))
	    {
	      FoProperty *property = NULL;

	      g_object_get ((gpointer) fo_expr_context_get_fo_context (context),
			    property_name,
			    &property,
			    NULL);

	      result_datatype =
		g_object_ref (fo_property_get_value (property));

	      g_object_unref (property);
	    }
	  else
	    {
	      result_datatype =
		fo_expr_eval_new_error (context,
					FO_EXPR_EVAL_ERROR_NOT_INHERITED);
	    }
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
	}

      g_type_class_unref (class);
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_PROPERTY);
    }

 error:

  return result_datatype;
}

/**
 * fo_expr_func_label_end:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the label-end() XSL function
 *
 *    numeric label-end()
 *
 * The label-end function returns the calculated label-end value for
 * lists.  See the definition in Section 7.28.3,
 * "provisional-label-separation", of the XSL 1.0 Recommendation.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_label_end (FoExprContext *context,
			gint           nargs)
{
  const FoFo *current_fo = NULL;
  FoNode *fo_list_block = NULL;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (context != NULL, NULL);

  current_fo = fo_expr_context_get_current_fo (context);

  if (nargs == 0)
    {
      fo_list_block =
	fo_node_get_ancestor_or_self_by_type (FO_NODE (current_fo),
					      FO_TYPE_LIST_BLOCK);
      if (fo_list_block != NULL)
	{
	  result_datatype =
	    g_object_ref (fo_list_block_get_label_end (FO_FO (fo_list_block)));
	}
      else
	{
	  result_datatype =
	    fo_expr_eval_new_error (context,
				    FO_EXPR_EVAL_ERROR_NOT_LIST_BLOCK_OR_DESCENDANT);
	}
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_ARITY);
    }

  return result_datatype;
}

/**
 * fo_expr_func_max:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the max() XSL function
 *
 *    numeric max(numeric)
 *
 * The max function returns the maximum of two numeric
 * arguments. These arguments must have the same numeric power.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_max (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg1;
  FoDatatype *arg2;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 2);

  arg2 = fo_expr_context_pop_stack (context);
  arg1 = fo_expr_context_pop_stack (context);

  return fo_datatype_max (arg1,
			  arg2);
}

/**
 * fo_expr_func_min:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the min() XSL function
 *
 *    numeric min(numeric)
 *
 * The min function returns the minimum of two numeric
 * arguments. These arguments must have the same numeric power.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_min (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg1;
  FoDatatype *arg2;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 2);

  arg2 = fo_expr_context_pop_stack (context);
  arg1 = fo_expr_context_pop_stack (context);

  return fo_datatype_min (arg1,
			  arg2);
}

/**
 * fo_expr_func_mod:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the modulus operation on XSL numerics.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_mod (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg1;
  FoDatatype *arg2;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 2);

  arg2 = fo_expr_context_pop_stack (context);
  arg1 = fo_expr_context_pop_stack (context);

  return fo_datatype_mod (arg1,
			  arg2);
}

/**
 * fo_expr_func_mul:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the multiply operation on XSL numerics by calling
 * #fo_datatype_mul.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_mul (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg1;
  FoDatatype *arg2;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 2);

  arg2 = fo_expr_context_pop_stack (context);
  arg1 = fo_expr_context_pop_stack (context);

  return fo_datatype_mul (arg1,
			  arg2);
}

/**
 * fo_expr_func_pcw:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the proportional-column-width() XSL function
 *
 *    numeric proportional-column-width(numeric)
 *
 * This version just returns a zero length, or an error if the
 * function argument is the wrong type or the current FO is not a
 * 'table-column'.
 *
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_pcw (FoExprContext *context,
		  gint           nargs)
{
  FoFo *current_fo = NULL;
  FoFo *table = NULL;
  FoDatatype *arg = NULL;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 1);

  arg = fo_expr_context_pop_stack (context);

  if (!FO_IS_NUMBER (arg) &&
      !FO_IS_INTEGER (arg))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_TYPE);
      goto error;
    }

  if (!FO_IS_TABLE_COLUMN (fo_expr_context_get_current_fo (context)))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_TABLE_COLUMN);
      goto error;
    }

  if (strcmp (fo_expr_context_get_property_name (context),
	      "column-width") != 0)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_COLUMN_WIDTH);
      goto error;
    }

  current_fo = (FoFo *) fo_expr_context_get_current_fo (context);
  table = FO_FO (fo_node_get_ancestor_or_self_by_type (FO_NODE (current_fo),
						       FO_TYPE_TABLE));

  if (fo_table_get_layout_method (table) !=
      FO_ENUM_TABLE_LAYOUT_METHOD_FIXED)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_FIXED_METHOD);
      goto error;
    }

  result_datatype = g_object_ref (fo_length_get_length_zero ());

 error:

  g_object_unref (arg);
  return result_datatype;
}

/**
 * fo_expr_func_pcw_prop:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the proportional-column-width() XSL function
 *
 *    numeric proportional-column-width(numeric)
 *
 * This version returns an #FoPcw representing the proportional
 * measure, or an error if the function argument is the wrong type or
 * the current FO is not a 'table-column'.
 *
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_pcw_prop (FoExprContext *context,
		       gint           nargs)
{
  FoFo *current_fo = NULL;
  FoFo *table = NULL;
  FoDatatype *arg = NULL;
  FoDatatype *result_datatype = NULL;

  CHECK_ARITY (context, 1);

  arg = fo_expr_context_pop_stack (context);

  if (!FO_IS_TABLE_COLUMN (fo_expr_context_get_current_fo (context)))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_TABLE_COLUMN);
      goto error;
    }

  if (strcmp (fo_expr_context_get_property_name (context),
	      "column-width") != 0)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_COLUMN_WIDTH);
      goto error;
    }

  current_fo = (FoFo *) fo_expr_context_get_current_fo (context);
  table = FO_FO (fo_node_get_ancestor_or_self_by_type (FO_NODE (current_fo),
						       FO_TYPE_TABLE));

  if (fo_table_get_layout_method (table) !=
      FO_ENUM_TABLE_LAYOUT_METHOD_FIXED)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_FIXED_METHOD);
      goto error;
    }

  if (FO_IS_NUMBER (arg))
    {
      result_datatype = fo_pcw_new_with_value (fo_number_get_value (arg));
    }
  else if (FO_IS_INTEGER (arg))
    {
      result_datatype =
	fo_pcw_new_with_value ((gdouble) fo_integer_get_value (arg));
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_TYPE);
      goto error;
    }

 error:

  g_object_unref (arg);
  return result_datatype;
}

/**
 * fo_expr_func_pcw_prop_fixed:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the proportional-column-width() XSL function
 *
 *    numeric proportional-column-width(numeric)
 *
 * This version returns a length representing the resovled value of
 * the proportional measure, or an error if the function argument
 * is the wrong type or the current FO is not a 'table-column'.
 *
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_pcw_prop_fixed (FoExprContext *context,
			     gint           nargs)
{
  const FoFo *current_fo = NULL;
  FoFo *table = NULL;
  FoDatatype *arg = NULL;
  FoDatatype *result_datatype = NULL;

  CHECK_ARITY (context, 1);

  arg = fo_expr_context_pop_stack (context);

  if (!FO_IS_TABLE_COLUMN (fo_expr_context_get_current_fo (context)))
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_TABLE_COLUMN);
      goto error;
    }

  if (strcmp (fo_expr_context_get_property_name (context),
	      "column-width") != 0)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_COLUMN_WIDTH);
      goto error;
    }

  current_fo = fo_expr_context_get_current_fo (context);
  table = FO_FO (fo_node_get_ancestor_or_self_by_type (FO_NODE (current_fo),
						       FO_TYPE_TABLE));

  if (fo_table_get_layout_method (table) !=
      FO_ENUM_TABLE_LAYOUT_METHOD_FIXED)
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_NOT_FIXED_METHOD);
      goto error;
    }

  if (FO_IS_NUMBER (arg))
    {
      result_datatype =
	fo_length_new_with_value (fo_number_get_value (arg) *
				  fo_table_get_proportional_unit (table));
    }
  else if (FO_IS_INTEGER (arg))
    {
      result_datatype =
	fo_length_new_with_value (((gdouble) fo_integer_get_value (arg)) *
				  fo_table_get_proportional_unit (table));
    }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_TYPE);
      goto error;
    }

 error:

  g_object_unref (arg);
  return result_datatype;
}

/**
 * datatype_to_color_component:
 * @datatype: #FoDatatype representing one component of an #FoColor
 * @error:    #GError for reporting errors
 * 
 * Convert @datatype to a #guint in the range 0 to
 * #FO_COLOR_COMPONENT_MAX.
 * 
 * Sets @error if cannot convert @datatype.
 *
 * Return value: Unsigned integer in range 0 to
 * #FO_COLOR_COMPONENT_MAX
 **/
guint
datatype_to_color_component (FoDatatype *datatype,
			     GError    **error)
{
  guint component = 0;

  if (FO_IS_PERCENTAGE (datatype))
    {
      gdouble percentage = fo_percentage_get_value (datatype);

      percentage = MAX (percentage, 0.0);
      percentage = MIN (percentage, 100.0);

      component =
	(guint) ((percentage / 100.0) * FO_COLOR_COMPONENT_MAX);
    }
  else if (FO_IS_NUMBER (datatype))
    {
      gdouble number = fo_number_get_value (datatype);

      number = MAX (number, 0.0);
      number = MIN (number, 255.0);

      component =
	(guint) ((number / 255.0) * FO_COLOR_COMPONENT_MAX);
    }
  else if (FO_IS_INTEGER (datatype))
    {
      gint integer = fo_integer_get_value (datatype);

      integer = MAX (integer, 0);
      integer = MIN (integer, 255);

      component =
	(guint) ((((gdouble) integer) / 255.0) * FO_COLOR_COMPONENT_MAX);
    }
  else
    {
      g_set_error (error,
		   FO_EXPR_EVAL_ERROR,
		   FO_EXPR_EVAL_ERROR_INVALID_TYPE,
		   "%s",
		   fo_expr_eval_error_messages[FO_EXPR_EVAL_ERROR_INVALID_TYPE]);
    }

  return component;
}
/**
 * fo_expr_func_rgb:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 *
 * Implement the rgb() XSL function
 *
 *    color rgb(numeric, numeric, numeric)
 *
 * The rgb function returns a specific color from the RGB color
 * space. The parameters to this function must be numerics (real
 * numbers) with a length power of zero.
 *
 * CSS has the requirement that the numbers be all numeric or all
 * percentages, but that isn't apparent from the XSL Recommendation.
 **/
FoDatatype*
fo_expr_func_rgb (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *red;
  FoDatatype *green;
  FoDatatype *blue;
  FoDatatype *result_datatype = NULL;
  GError *error = NULL;
  guint16 result_red;
  guint16 result_green;
  guint16 result_blue;
  
  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 3);

  blue  = fo_expr_context_pop_stack (context);
  green = fo_expr_context_pop_stack (context);
  red   = fo_expr_context_pop_stack (context);

  result_red = datatype_to_color_component (red,
					    &error);
  if (error != NULL)
    {
      result_datatype =
	fo_expr_eval_propagate_error (context,
				      error);
      goto error;
    }

  result_green = datatype_to_color_component (green,
					      &error);
  if (error != NULL)
    {
      result_datatype =
	fo_expr_eval_propagate_error (context,
				      error);
      goto error;
    }

  result_blue = datatype_to_color_component (blue,
					     &error);
  if (error != NULL)
    {
      result_datatype =
	fo_expr_eval_propagate_error (context,
				      error);
      goto error;
    }

  result_datatype = fo_color_new_with_value (result_red, result_green, result_blue);

 error:

  g_object_unref (red);
  g_object_unref (green);
  g_object_unref (blue);
  return result_datatype;
}

/**
 * fo_expr_func_round:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the round() XSL function
 *
 *    numeric round(numeric)
 *
 * The round function returns the number that is closest to the
 * argument and that is an integer. If there are two such numbers,
 * then the one that is even is returned.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_round (FoExprContext *context,
		    gint           nargs)
{
  FoDatatype *arg;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 1);

  arg = fo_expr_context_pop_stack (context);

  return fo_datatype_round (arg);
}

/**
 * fo_expr_func_sub:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the subtraction operation on XSL numerics by calling
 * #fo_datatype_mul.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 **/
FoDatatype*
fo_expr_func_sub (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg1;
  FoDatatype *arg2;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 2);

  arg2 = fo_expr_context_pop_stack (context);
  arg1 = fo_expr_context_pop_stack (context);

  return fo_datatype_sub (arg1,
			  arg2);
}

/**
 * fo_expr_func_url:
 * @context: The expression context
 * @nargs:   Number of arguments provided in the function call
 * 
 * Implement the uri-specification XSL datatype
 *
 *    url(...)
 *
 * It's not really an XSL function, but it does look like one.
 * 
 * Return value: #FoDatatype, which could be an #FoError
 */
FoDatatype*
fo_expr_func_url (FoExprContext *context,
		  gint           nargs)
{
  FoDatatype *arg;
  FoDatatype *result_datatype = NULL;

  g_return_val_if_fail (context != NULL, NULL);

  CHECK_ARITY (context, 1);

  arg = fo_expr_context_pop_stack (context);

  if (FO_IS_STRING (arg))
    {
      result_datatype = fo_uri_specification_new_with_value (fo_string_get_value (arg));
    }
  else if (FO_IS_NAME (arg))
    {
      result_datatype = fo_uri_specification_new_with_value (fo_name_get_value (arg));
   }
  else
    {
      result_datatype =
	fo_expr_eval_new_error (context,
				FO_EXPR_EVAL_ERROR_INVALID_TYPE);
    }
  
  return result_datatype;
}
