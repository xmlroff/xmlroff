/* Fo
 * fo-object.c: Base object of formatting object system
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-object.h"

/**
 * SECTION:fo-object
 * @short_description: libfo base object type
 *
 * Top of the object hierarchy for libfo.
 *
 * Extends #GObject to add some common debugging and logging
 * functions.
 */

static void     fo_object_base_class_init                (FoObjectClass *klass);
static void     fo_object_class_init                     (FoObjectClass *klass);
static void     fo_object_finalize                       (GObject       *object);

static void     fo_object_debug_dump_default             (FoObject      *object,
							  gint           depth);
static gchar*   fo_object_debug_sprintf_default          (FoObject      *object);
static gchar*   fo_object_sprintf_default                (FoObject      *object);
static void     fo_object_log_error_default              (FoObject      *object,
							  GError       **error);
static void     fo_object_log_warning_default            (FoObject      *object,
							  GError       **warning);
static void     fo_object_log_debug_default              (FoObject      *object,
							  GError       **warning);
static gboolean fo_object_log_or_propagate_error_default (FoObject *fo_object,
							  GError  **dest,
							  GError   *src);
static gboolean fo_object_maybe_propagate_error_default  (FoObject *fo_object,
							  GError  **dest,
							  GError   *src,
							  gboolean  continue_after_error);
static guint    fo_object_hash_func_default              (gconstpointer key);
static gboolean fo_object_equal_func_default             (gconstpointer a,
							  gconstpointer b);
static gpointer parent_class;

/**
 * fo_object_get_type:
 * 
 * Register the #FoObject object type.
 * 
 * Return value: #GType value of the #FoObject object type.
 **/
GType
fo_object_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoObjectClass),
        (GBaseInitFunc) fo_object_base_class_init,
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_object_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoObject),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (G_TYPE_OBJECT,
                                            "FoObject",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }
  
  return object_type;
}

/**
 * fo_object_base_init:
 * @klass: #FoObjectClass object to initialise.
 * 
 * Implements #GClassBaseInit for #FoObjectClass.
 **/
void
fo_object_base_class_init (FoObjectClass *klass)
{
  klass->debug_dump             = fo_object_debug_dump_default;
  klass->debug_sprintf          = fo_object_debug_sprintf_default;
  klass->print_sprintf          = fo_object_sprintf_default;
  klass->log_error              = fo_object_log_error_default;
  klass->log_warning            = fo_object_log_warning_default;
  klass->log_debug              = fo_object_log_debug_default;
  klass->log_or_propagate_error = fo_object_log_or_propagate_error_default;
  klass->maybe_propagate_error  = fo_object_maybe_propagate_error_default;
  klass->hash_func              = fo_object_hash_func_default;
  klass->equal_func             = fo_object_equal_func_default;
}

/**
 * fo_object_class_init:
 * @klass: #FoObjectClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoObjectClass.
 **/
void
fo_object_class_init (FoObjectClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_object_finalize;
}

/**
 * fo_object_finalize:
 * @object: #FoObject object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoObject.
 **/
void
fo_object_finalize (GObject *object)
{
  FoObject *fo_object;

  fo_object = FO_OBJECT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_object_new:
 * 
 * Creates a new #FoObject initialized to default value.
 * 
 * Return value: the new #FoObject.
 **/
FoObject *
fo_object_new (void)
{
  FoObject *object;

  object = FO_OBJECT (g_object_new (fo_object_get_type (),
				    NULL));
  
  return object;
}

/**
 * fo_object_debug_dump:
 * @object: The #FoObject object.
 * @depth:  Indent level to add to the output.
 * 
 * Calls debug_dump method of class of @object, if @object is an
 * #FoObject or descendant type of #FoObject.
 **/
void
fo_object_debug_dump (gpointer object,
		      gint     depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  if (object == NULL)
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%s(null)",
	     indent);
    }
  else if (!G_IS_OBJECT (object))
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%sNot a GObject: %p",
	     indent,
	     object);
    }
  else if (!FO_IS_OBJECT (object))
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%sGObject but not an FoObject:: %s (%p : %d)",
	     indent,
	     g_type_name (G_TYPE_FROM_INSTANCE (object)),
	     object,
	     ((GObject *) object)->ref_count);
    }
  else
    {
      FO_OBJECT_GET_CLASS (object)->debug_dump (FO_OBJECT (object), depth);
    }

  g_free (indent);
}

/**
 * fo_object_debug_sprintf:
 * @object: The #FoObject object.
 * 
 * Calls debug_sprintf method of class of @object, if @object is an
 * #FoObject or descendant type of #FoObject.
 *
 * Return value: Result of debug_sprintf method of class of @object.
 **/
gchar*
fo_object_debug_sprintf (gpointer object)
{
  if (object == NULL)
    {
      return g_strdup ("(null)");
    }
  else if (!G_IS_OBJECT (object))
    {
      return g_strdup_printf ("Not a GObject: %p",
			      object);
    }
  else if (!FO_IS_OBJECT (object))
    {
      return g_strdup_printf ("GObject but not an FoObject:: %s (%p : %d)",
			      g_type_name (G_TYPE_FROM_INSTANCE (object)),
			      object,
			      ((GObject *) object)->ref_count);
    }
  else
    {
      return FO_OBJECT_GET_CLASS (object)->debug_sprintf (FO_OBJECT (object));
    }    
}

/**
 * fo_object_sprintf:
 * @object: The #FoObject object.
 * 
 * Calls sprintf method of class of @object, if @object is an
 * #FoObject or descendant type of #FoObject.
 *
 * Return value: Result of sprintf method of class of @object.
 **/
gchar*
fo_object_sprintf (gpointer object)
{
  if (object == NULL)
    {
      return g_strdup ("(null)");
    }
  else if (!G_IS_OBJECT (object))
    {
      return g_strdup_printf ("Not a GObject: %p",
			      object);
    }
  else if (!FO_IS_OBJECT (object))
    {
      return g_strdup_printf ("GObject but not an FoObject:: %s (%p : %d)",
			      g_type_name (G_TYPE_FROM_INSTANCE (object)),
			      object,
			      ((GObject *) object)->ref_count);
    }
  else
    {
      return FO_OBJECT_GET_CLASS (object)->print_sprintf (object);
    }
}

/**
 * fo_object_debug_dump_default:
 * @object: The #FoObject object.
 * @depth:  Indent level to add to the output.
 * 
 * Default debug_dump method.
 *
 * Return value: Result of debug_sprintf method of class of @object.
 **/
void
fo_object_debug_dump_default (FoObject *object,
			      gint      depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *object_sprintf;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_OBJECT (object));

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);
  g_free (indent);
}

/**
 * fo_object_debug_sprintf_default:
 * @object: The #FoObject object.
 * 
 * Default debug_sprintf method.
 *
 * Return value: Type name, address, and reference count of @object.
 **/
gchar*
fo_object_debug_sprintf_default (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_OBJECT (object), NULL);

  if (object == NULL)
    {
      return g_strdup ("(null)");
    }
  else
    {
      return g_strdup_printf ("%s (%p : %d)",
			      g_type_name (G_TYPE_FROM_INSTANCE (object)),
			      object,
			      ((GObject *) object)->ref_count);
    }
}

/**
 * fo_object_sprintf_default:
 * @object: The #FoObject object.
 * 
 * Default sprintf method.
 *
 * Return value: Text warning that @object does not have a 'sprintf' function.
 **/
gchar*
fo_object_sprintf_default (FoObject *object)
{
  return g_strdup_printf ("%s has no 'sprintf' function.",
			  g_type_name (G_TYPE_FROM_INSTANCE (object)));

}

/**
 * fo_object_log_error_default:
 * @object: #FoObject that is subject of @error.
 * @error:  #GError with information about error that occurred.
 * 
 * Logs a "critical warning" about @error.
 *
 * Clears @error.
 **/
void
fo_object_log_error_default (FoObject *object,
			     GError  **error)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_OBJECT (object));

  g_critical ("%s: %s",
	      g_quark_to_string ((*error)->domain),
	      (*error)->message);
  g_clear_error (error);
}

/**
 * fo_object_log_error:
 * @object: #FoObject that is subject of @error.
 * @error:  #GError with information about error that occurred.
 * 
 * Calls the 'log_error' method of the class of @object.
 *
 * The called method clears @error.
 **/
void
fo_object_log_error (FoObject *object,
		     GError  **error)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_OBJECT (object));
  g_return_if_fail (error != NULL);

  FO_OBJECT_GET_CLASS (object)->log_error (object, error);
}

/**
 * fo_object_log_warning_default:
 * @object:  #FoObject that is subject of @error.
 * @warning: #GError with information about warning that occurred.
 * 
 * Logs a "warning" about @error.
 *
 * Clears @error.
 **/
void
fo_object_log_warning_default (FoObject *object,
			       GError  **warning)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_OBJECT (object));

  g_warning ("Warning: %s: %s",
	     g_quark_to_string ((*warning)->domain),
	     (*warning)->message);
  g_clear_error (warning);
}

/**
 * fo_object_log_warning:
 * @object: #FoObject that is subject of @error.
 * @warning: #GError with information about warning that occurred.
 * 
 * Calls the 'log_warning' method of the class of @object.
 *
 * The called method clears @error.
 **/
void
fo_object_log_warning (FoObject *object,
		       GError  **warning)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_OBJECT (object));
  g_return_if_fail (warning != NULL);

  FO_OBJECT_GET_CLASS (object)->log_warning (object, warning);
}

/**
 * fo_object_log_debug_default:
 * @object: #FoObject that is subject of @error.
 * @debug:  #GError with debugging information.
 * 
 * Logs a "debug" message about @error.
 *
 * Clears @error.
 **/
void
fo_object_log_debug_default (FoObject *object,
			     GError  **debug)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_OBJECT (object));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "Debug: %s: %s",
	 g_quark_to_string ((*debug)->domain),
	 (*debug)->message);
  g_clear_error (debug);
}

/**
 * fo_object_log_debug:
 * @object: #FoObject that is subject of @error.
 * @debug:  #GError with debugging information.
 * 
 * Calls the 'log_debug' method of the class of @object.
 *
 * The called method clears @error.
 **/
void
fo_object_log_debug (FoObject *object,
		     GError  **debug)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_OBJECT (object));
  g_return_if_fail (debug != NULL);

  FO_OBJECT_GET_CLASS (object)->log_debug (object, debug);
}

/**
 * fo_object_log_or_propagate_error_default:
 * @fo_object: #FoObject that is the subject of @src.
 * @dest:      #GError to which to propagate @src, or NULL.
 * @src:       #GError with information about error that occurred.
 * 
 * If can propagate @src to @dest, do so, otherwise log @src using
 * fo_object_log_error().
 * 
 * Return value: %TRUE if error propagated, otherwise %FALSE.
 **/
gboolean
fo_object_log_or_propagate_error_default (FoObject *fo_object,
					  GError  **dest,
					  GError   *src)
{
  g_return_val_if_fail (FO_IS_OBJECT (fo_object), TRUE);
  g_return_val_if_fail (dest == NULL || *dest == NULL, TRUE);
  g_return_val_if_fail (src != NULL, TRUE);

  if (dest != NULL)
    {
      g_propagate_error (dest,
			 src);
      return TRUE;
    }
  else
    {
      fo_object_log_error (fo_object,
			   &src);
      return FALSE;
    }
}


/**
 * fo_object_log_or_propagate_error:
 * @fo_object: #FoObject that is the subject of @src.
 * @dest:      #GError to which to propagate @src, or NULL.
 * @src:       #GError with information about error that occurred.
 * 
 * If can propagate @src to @dest, do so, otherwise log @src using
 * fo_object_log_error().
 * 
 * Return value: %TRUE if error propagated, otherwise %FALSE.
 **/
gboolean
fo_object_log_or_propagate_error (FoObject *fo_object,
				  GError  **dest,
				  GError   *src)
{
  g_return_val_if_fail (FO_IS_OBJECT (fo_object), TRUE);
  g_return_val_if_fail (dest == NULL || *dest == NULL, TRUE);
  g_return_val_if_fail (src != NULL, TRUE);

  return FO_OBJECT_GET_CLASS (fo_object)->maybe_propagate_error (fo_object,
								 dest,
								 src,
								 FALSE);
}

/**
 * fo_object_maybe_propagate_error_default:
 * @fo_object:            #FoObject that is the subject of @src.
 * @dest:                 #GError to which to propagate @src, or NULL.
 * @src:                  #GError with information about error that occurred.
 * @continue_after_error: Whether or not to continue after an error.
 * 
 * If @continue_after_error is %FALSE and can propagate @src to @dest,
 * then do so, otherwise log @src using fo_object_log_error().
 * 
 * Return value: %TRUE if error propagated, otherwise %FALSE.
 **/
gboolean
fo_object_maybe_propagate_error_default (FoObject *fo_object,
					 GError  **dest,
					 GError   *src,
					 gboolean  continue_after_error)
{
  g_return_val_if_fail (FO_IS_OBJECT (fo_object), TRUE);
  g_return_val_if_fail (dest == NULL || *dest == NULL, TRUE);
  g_return_val_if_fail (src != NULL, TRUE);

  if ((continue_after_error == FALSE) &&
      (dest != NULL))
    {
      g_propagate_error (dest,
			 src);
      return TRUE;
    }
  else
    {
      fo_object_log_error (fo_object,
			   &src);
      return FALSE;
    }
}


/**
 * fo_object_maybe_propagate_error:
 * @fo_object:            #FoObject that is the subject of @src.
 * @dest:                 #GError to which to propagate @src, or NULL.
 * @src:                  #GError with information about error that occurred.
 * @continue_after_error: Whether or not to continue after an error.
 * 
 * If @continue_after_error is %FALSE and can propagate @src to @dest,
 * then do so, otherwise log @src using fo_object_log_error().
 * 
 * Return value: %TRUE if error propagated, otherwise %FALSE.
 **/
gboolean
fo_object_maybe_propagate_error (FoObject *fo_object,
				 GError  **dest,
				 GError   *src,
				 gboolean  continue_after_error)
{
  g_return_val_if_fail (FO_IS_OBJECT (fo_object), TRUE);
  g_return_val_if_fail (dest == NULL || *dest == NULL, TRUE);
  g_return_val_if_fail (src != NULL, TRUE);

  return FO_OBJECT_GET_CLASS (fo_object)->maybe_propagate_error (fo_object,
								 dest,
								 src,
								 continue_after_error);
}

/**
 * fo_object_hash_func_default:
 * @key: Pointer to object to hash.
 * 
 * Default 'hash_func' which just returns object's address.
 * 
 * Return value: Hash code for object.
 **/
guint
fo_object_hash_func_default       (gconstpointer key)
{
    return g_direct_hash(key);
}

/**
 * fo_object_equal_func_default:
 * @a: First object to compare.
 * @b: Second object to compare.
 * 
 * Default 'equal_func' which just compares object addresses.
 * 
 * Return value: %TRUE if objects are equal.
 **/
gboolean
fo_object_equal_func_default (gconstpointer a,
			      gconstpointer b)
{
    return g_direct_equal(a, b);
}

/**
 * fo_object_hash:
 * @object: #FoObject for which to get hash value.
 * @error:  #GError with information about error that occurred.
 * 
 * Create a hash code for the object.
 * 
 * Return value: Hash code for the object.
 **/
guint
fo_object_hash        (FoObject *object,
		       GError  **error G_GNUC_UNUSED)
{
  g_return_val_if_fail (object != NULL, 0);
  g_return_val_if_fail (FO_IS_OBJECT (object), 0);

  return FO_OBJECT_GET_CLASS (object)->hash_func (object);
}

/**
 * fo_object_equal:
 * @a:     First object to compare.
 * @b:     Second object to compare.
 * @error: #GError with information about error that occurred.
 * 
 * Compare @a to @b using the 'equal_func' of the class of @a.
 * 
 * Return value: %TRUE if the objects are equal.
 **/
gboolean
fo_object_equal       (FoObject *a,
		       FoObject *b,
		       GError  **error G_GNUC_UNUSED)
{
  g_return_val_if_fail (a != NULL, FALSE);
  g_return_val_if_fail (FO_IS_OBJECT (a), FALSE);
  g_return_val_if_fail (b != NULL, FALSE);
  g_return_val_if_fail (FO_IS_OBJECT (b), FALSE);

  return FO_OBJECT_GET_CLASS (a)->equal_func (a, b);
}
