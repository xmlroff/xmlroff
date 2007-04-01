/* Fo
 * fo-expr-env.c: XSL expression language environment module
 *
 * Copyright (C) 1998-2002 Daniel Veillard.
 * Copyright (C) 2001-2002 Sun Microsystems.
 * All Rights Reserved.
 *
 * Based on an XSL expression language evaluator that was based on the
 * 'XML Path Language implementation' in 'xpath.c' from libxml2 by
 * Daniel Veillard.
 *
 * $Id: fo-expr-env.c,v 1.2 2005/06/27 00:23:56 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#include "fo-expr-eval.h"
#include "fo-expr-func-private.h"

struct _FoExprEnv
{
  GHashTable *func_hash;
  gint        ref_count;
};

/**
 * fo_expr_env_get_global_env:
 * 
 * 
 * 
 * Return value: 
 **/
static FoExprEnv*
fo_expr_env_get_global_env (void)
{
  static FoExprEnv *global_env = NULL;

  if (global_env == NULL)
    {
      global_env = fo_expr_env_new ();

      fo_expr_env_register_func (global_env,
				 "+",
				 fo_expr_func_add);
      fo_expr_env_register_func (global_env,
				 "-",
				 fo_expr_func_sub);
      fo_expr_env_register_func (global_env,
				 "*",
				 fo_expr_func_mul);
      fo_expr_env_register_func (global_env,
				 "abs",
				 fo_expr_func_abs);
      fo_expr_env_register_func (global_env,
				 "body-start",
				 fo_expr_func_body_start);
      fo_expr_env_register_func (global_env,
				 "ceiling",
				 fo_expr_func_ceiling);
      fo_expr_env_register_func (global_env,
				 "div",
				 fo_expr_func_div);
      fo_expr_env_register_func (global_env,
				 "floor",
				 fo_expr_func_floor);
      fo_expr_env_register_func (global_env,
				 "from-nearest-specified-value",
				 fo_expr_func_from_nearest_specified_value);
      fo_expr_env_register_func (global_env,
				 "from-parent",
				 fo_expr_func_from_parent);
      fo_expr_env_register_func (global_env,
				 "from-table-column",
				 fo_expr_func_from_table_column);
      fo_expr_env_register_func (global_env,
				 "inherited-property-value",
				 fo_expr_func_inherited_property_value);
      fo_expr_env_register_func (global_env,
				 "label-end",
				 fo_expr_func_label_end);
      fo_expr_env_register_func (global_env,
				 "max",
				 fo_expr_func_max);
      fo_expr_env_register_func (global_env,
				 "min",
				 fo_expr_func_min);
      fo_expr_env_register_func (global_env,
				 "mod",
				 fo_expr_func_mod);
      fo_expr_env_register_func (global_env,
				 "proportional-column-width",
				 fo_expr_func_pcw);
      fo_expr_env_register_func (global_env,
				 "rgb",
				 fo_expr_func_rgb);
      fo_expr_env_register_func (global_env,
				 "round",
				 fo_expr_func_round);
    }

  return global_env;
}

FoExprEnv*
fo_expr_env_new (void)
{
  FoExprEnv *env = g_new0 (FoExprEnv, 1);

  env->func_hash = g_hash_table_new (g_str_hash,
				     g_str_equal);

  env->ref_count = 1;

  return env;
}

FoExprEnv*
fo_expr_env_ref (FoExprEnv   *env)
{
  g_return_val_if_fail (env != NULL, NULL);

  env->ref_count++;

  return env;
}

void
fo_expr_env_unref (FoExprEnv   *env)
{
  g_return_if_fail (env != NULL);
  g_return_if_fail (env->ref_count > 0);

  env->ref_count--;

  if (env->ref_count == 0)
    {
      g_hash_table_destroy (env->func_hash);
      g_free (env);
      env = NULL;
    }
}

FoExprEnv*
fo_expr_env_register_func (FoExprEnv   *env,
			   const gchar *name,
			   FoExprFunc   func)
{
  g_hash_table_insert (env->func_hash,
		       (gchar *) name,
		       func);
  return env;
}

FoExprFunc
fo_expr_env_get_func (FoExprEnv   *env,
		      const gchar *name)
{
  return (FoExprFunc) g_hash_table_lookup (env->func_hash,
					   name);
}

static gint
fo_expr_env_list_compare_func (gconstpointer a,
			       gconstpointer b)
{
  const FoExprEnv *env = (const FoExprEnv *) a;
  gchar *name = (gchar *) b;

  if (g_hash_table_lookup (env->func_hash,
			   name))
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

/**
 * fo_expr_env_list_new:
 * 
 * Get a new #FoExprEnvList that is preloaded with a copy of the
 * global environment.
 * 
 * The #FoExprEnvList must be freed by the caller using
 * fo_expr_env_list_free()
 *
 * Return value: A new, preloaded #FoExprEnvList
 **/
FoExprEnvList*
fo_expr_env_list_new (void)
{
  return fo_expr_env_list_prepend (NULL,
				   fo_expr_env_get_global_env ());
}

/**
 * fo_expr_env_list_free_item:
 * @data:      The item
 * @user_data: Unused
 * 
 * Free one item in an #FoExprEnvList
 **/
static void
fo_expr_env_list_free_item (gpointer data,
			    gpointer user_data)
{
  fo_expr_env_unref ((FoExprEnv *) data);
}

/**
 * fo_expr_env_list_free:
 * @env_list: The #FoExprEnvList to free
 * 
 * Free an #FoExprEnvList that was created with fo_expr_env_list_new()
 **/
void
fo_expr_env_list_free (FoExprEnvList   *env_list)
{
  g_return_if_fail (env_list != NULL);

  g_slist_foreach (env_list,
		   fo_expr_env_list_free_item,
		   NULL);
  g_slist_free (env_list);
}

/**
 * fo_expr_env_list_prepend:
 * @env_list: The #FoExprEnvList to which to prepend @env.
 * @env:      The new #FoExprEnv.
 * 
 * Prepend @env to @env_list so that when the returned @env_list is
 * used in evaluating XSL expressions, the functions in @env have
 * precedence over the functions in the environments, including the
 * global environment, that are already in @env_list.
 * 
 * Return value: The new start of the #FoExprEnvList.
 **/
FoExprEnvList*
fo_expr_env_list_prepend (FoExprEnvList   *env_list,
			  FoExprEnv *env)
{
  g_return_val_if_fail (env != NULL, env_list);

  env = fo_expr_env_ref (env);

  return g_slist_prepend (env_list, (gpointer) env);
}

/**
 * fo_expr_env_list_get_func:
 * @env_list: #FoExprEnvList
 * @name:     Name of a function
 * 
 * Get the function in @env_list with name matching @name.
 * 
 * Return value: #FoExprFunc corresponding to @name, or NULL.
 **/
FoExprFunc
fo_expr_env_list_get_func (const FoExprEnvList *env_list,
			   const gchar  *name)
{
  GSList *env_element =
    g_slist_find_custom ((FoExprEnvList *) env_list,
			 name,
			 (GCompareFunc) fo_expr_env_list_compare_func);

  if (env_element != NULL)
    {
      return fo_expr_env_get_func (env_element->data,
				   name);
    }
  else
    {
      return NULL;
    }
}
