/* Fo
 * fo-hashtable.c: HashTable hashtable
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <math.h>
#include "fo-utils.h"
#include "fo-hash-table.h"

struct _FoHashTable
{
  FoObject parent_instance;

  GHashTable *hash_table;
};

struct _FoHashTableClass
{
  FoObjectClass parent_class;
};

static void     fo_hash_table_class_init         (FoHashTableClass *klass);
static void     fo_hash_table_finalize           (GObject          *object);

static guint    fo_hash_table_hash_func          (gconstpointer     key);
static gboolean fo_hash_table_key_equal_func     (gconstpointer     a,
						  gconstpointer     b);
static void     fo_hash_table_destroy_func   (gpointer data);

static gpointer parent_class;

/**
 * fo_hash_table_get_type:
 * 
 * Register the #FoHashTable object type.
 * 
 * Return value: #GType value of the #FoHashTable object type.
 **/
GType
fo_hash_table_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoHashTableClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_hash_table_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoHashTable),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoHashTable",
                                            &object_info,
					    0);
    }
  
  return object_type;
}

/**
 * fo_hash_table_class_init:
 * @klass: #FoHashTableClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoHashTableClass.
 **/
void
fo_hash_table_class_init (FoHashTableClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_hash_table_finalize;
}

/**
 * fo_hash_table_finalize:
 * @object: #FoHashTable object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoHashTable.
 **/
void
fo_hash_table_finalize (GObject *object)
{
  FoHashTable *fo_hash_table;

  fo_hash_table = FO_HASH_TABLE (object);

  g_hash_table_destroy(fo_hash_table->hash_table);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_hash_table_new:
 * 
 * Creates a new #FoHashTable initialized to default value.
 * 
 * Return value: the new #FoHashTable
 **/
FoHashTable *
fo_hash_table_new (void)
{
  FoHashTable *fo_hash_table;

  fo_hash_table = FO_HASH_TABLE (g_object_new (fo_hash_table_get_type (), NULL));
  
  fo_hash_table->hash_table = g_hash_table_new_full(fo_hash_table_hash_func,
						    fo_hash_table_key_equal_func,
						    fo_hash_table_destroy_func,
						    fo_hash_table_destroy_func);

  return fo_hash_table;
}

/**
 * fo_hash_table_destroy_func:
 * @data: Data to be destroyed.
 * 
 * #GDestroyNotify function called when a key or value is removed from
 * a #FoHashTable.
 **/
void
fo_hash_table_destroy_func (gpointer data)
{
  if ((data != NULL) &&
      FO_IS_OBJECT (data))
      {
	  g_object_unref(data);
      }
}

/**
 * fo_hash_table_hash_func:
 * @key: Key to hash.
 * 
 * Creates the hash code for @key using the 'hash' function for the
 * #FoObject class type of @key.
 * 
 * Return value: Hash code for @key.
 **/
guint
fo_hash_table_hash_func   (gconstpointer     key)
{
    guint result = 0;

  if ((key != NULL) &&
      (FO_IS_OBJECT (key)))
  {
      result = FO_OBJECT_GET_CLASS (key)->hash_func (key);
  }

      return result;
}

/**
 * fo_hash_table_key_equal_func:
 * @a: First key to compare.
 * @b: Second key to compare.
 * 
 * Compares @a and @b using the 'equal' function of the #FoObject
 * class type of @a.
 * 
 * Return value: %TRUE if @a and @b are equal.
 **/
gboolean
fo_hash_table_key_equal_func  (gconstpointer     a,
			       gconstpointer     b)
{
    return FO_OBJECT_GET_CLASS (a)->equal_func (a, b);
}

/**
 * fo_hash_table_insert:
 * @fo_hash_table: #FoHashTable in which to insert.
 * @key:           Key at which to insert.
 * @value:         Value to insert.
 * @error:         #GError with information about error that occurred.
 * 
 * Inserts @value as the value corresponding to @key in
 * @fo_hash_table.
 **/
void
fo_hash_table_insert (FoHashTable *fo_hash_table,
		      FoObject    *key,
		      FoObject    *value,
		      GError     **error)
{
  g_return_if_fail (fo_hash_table != NULL);
  g_return_if_fail (FO_IS_HASH_TABLE (fo_hash_table));
  g_return_if_fail (key != NULL);
  g_return_if_fail (FO_IS_OBJECT (value));

  g_hash_table_insert (fo_hash_table->hash_table,
		       g_object_ref(key),
		       g_object_ref(value));
}

/**
 * fo_hash_table_replace:
 * @fo_hash_table: #FoHashTable in which to replace.
 * @key:           Key of key-value pair to replace.
 * @value:         New value.
 * @error:         #GError with information about error that occurred.
 * 
 * Replaces the key-value pair in @fo_hash_table that has a key
 * matching @key.
 **/
void
fo_hash_table_replace (FoHashTable *fo_hash_table,
		       FoObject    *key,
		       FoObject    *value,
		       GError     **error)
{
  g_return_if_fail (fo_hash_table != NULL);
  g_return_if_fail (FO_IS_HASH_TABLE (fo_hash_table));
  g_return_if_fail (key != NULL);
  g_return_if_fail (FO_IS_OBJECT (key));

  g_hash_table_replace (fo_hash_table->hash_table,
			g_object_ref(key),
			g_object_ref(value));
}

/**
 * fo_hash_table_remove:
 * @fo_hash_table: #FoHashTable from which to remove a key-value pair.
 * @key:           Key of pair to remove.
 * @error:         #GError with information about error that occurred.
 * 
 * Removes the key-value pair with key matching @key from
 * @fo_hash_table.
 * 
 * Return value: %TRUE is successful.
 **/
gboolean
fo_hash_table_remove (FoHashTable *fo_hash_table,
		      FoObject   *key,
		      GError   **error)
{
  g_return_val_if_fail (fo_hash_table != NULL, FALSE);
  g_return_val_if_fail (FO_IS_HASH_TABLE (fo_hash_table), FALSE);
  g_return_val_if_fail (key != NULL, FALSE);
  g_return_val_if_fail (FO_IS_OBJECT (key), FALSE);

  return g_hash_table_remove (fo_hash_table->hash_table,
			      g_object_ref(key));
}

/**
 * fo_hash_table_lookup:
 * @fo_hash_table: #FoHashTable in which to look.
 * @key:           Key value against which to compare.
 * @error:         #GError with information about error that occurred.
 * 
 * Gets the value associated with @key in @fo_hash_table.
 * 
 * Return value: The value, or %NULL if no matching key.
 **/
FoObject *
fo_hash_table_lookup (FoHashTable *fo_hash_table,
		      FoObject    *key,
		      GError     **error)
{
  g_return_val_if_fail (fo_hash_table != NULL, NULL);
  g_return_val_if_fail (FO_IS_HASH_TABLE (fo_hash_table), NULL);
  g_return_val_if_fail (key != NULL, NULL);
  g_return_val_if_fail (FO_IS_OBJECT (key), NULL);

  return g_hash_table_lookup (fo_hash_table->hash_table,
			      key);
}

/**
 * fo_hash_table_size:
 * @fo_hash_table: #FoHashTable for which to get size.
 * 
 * Gets the number of key-value pairs in @fo_hash_table.
 * 
 * Return value: Number of key-value pairs.
 **/
guint
fo_hash_table_size (FoHashTable *fo_hash_table)
{
    return g_hash_table_size(fo_hash_table->hash_table);
}

/**
 * fo_hash_table_error_quark:
 * 
 * Get the error quark for #FoHashTable.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: Quark associated with #FoHashTable errors.
 **/
GQuark
fo_hash_table_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoHashTable error");
  return quark;
}

const char *fo_hash_table_error_messages [] = {
  N_("Invalid hash_table for context."),
};
