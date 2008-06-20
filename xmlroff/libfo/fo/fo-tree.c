/* Fo
 * fo-tree.c: Formatting object tree root
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "fo-utils.h"
#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-tree.h"
#include "fo-node.h"
#include "fo-root.h"

/**
 * SECTION:fo-tree
 * @short_description: Top of the FO tree
 *
 * #FoTree is above #FoRoot (which represents the fo:root formatting
 * object).  #FoTree is used for aspects such as id-FO mapping that
 * apply to the FO tree as a whole but are outside the definition of
 * XSL formatting objects.
 */

enum {
  PROP_0
};

struct _FoTree
{
  FoFo parent_instance;

  GHashTable *id_hash;
  GHashTable *master_name_hash;
  GHashTable *page_sequence_master_name_hash;
  FoFo *default_master;
};

struct _FoTreeClass
{
  FoFoClass parent_class;
  
};

static void fo_tree_init        (FoTree      *tree);
static void fo_tree_class_init  (FoTreeClass *klass);
static void fo_tree_finalize    (GObject           *object);
static void fo_tree_free_hash_key (gpointer key,
				   gpointer value,
				   gpointer user_data);
static void fo_tree_debug_dump_properties (FoFo *fo, gint depth);
static gboolean fo_tree_validate_content (FoFo *fo,
					  GError **error);

static gpointer parent_class;

/**
 * fo_tree_get_type:
 * 
 * Register the #FoTree object type.
 * 
 * Return value: #GType value of the #FoTree object type.
 **/
GType
fo_tree_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoTreeClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_tree_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoTree),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_tree_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoTree",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_tree_init:
 * @tree: #FoTree object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoTree.
 **/
void
fo_tree_init (FoTree *tree)
{
  tree->id_hash = g_hash_table_new (g_str_hash,
				    g_str_equal);
  tree->master_name_hash = g_hash_table_new (g_str_hash,
					     g_str_equal);
  tree->page_sequence_master_name_hash =
    g_hash_table_new (g_str_hash,
		      g_str_equal);
  tree->default_master = NULL;
}

/**
 * fo_tree_class_init:
 * @klass: #FoTreeClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoTreeClass.
 **/
void
fo_tree_class_init (FoTreeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_tree_finalize;

  fo_fo_class->debug_dump_properties = fo_tree_debug_dump_properties;
  fo_fo_class->validate_content = fo_tree_validate_content;
  /* No properties so no need to resolve property attributes. */
  fo_fo_class->resolve_property_attributes = NULL;
}

static void
fo_tree_finalize (GObject *object)
{
  FoTree *tree;

  tree = FO_TREE (object);

  g_hash_table_foreach (tree->id_hash,
			fo_tree_free_hash_key,
			NULL);
  g_hash_table_destroy (tree->id_hash);
  tree->id_hash = NULL;

  g_hash_table_foreach (tree->master_name_hash,
			fo_tree_free_hash_key,
			NULL);
  g_hash_table_destroy (tree->master_name_hash);
  tree->master_name_hash = NULL;

  g_hash_table_foreach (tree->page_sequence_master_name_hash,
			fo_tree_free_hash_key,
			NULL);
  g_hash_table_destroy (tree->page_sequence_master_name_hash);
  tree->page_sequence_master_name_hash = NULL;

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_tree_new:
 * 
 * Creates a new #FoTree initialized to default value.
 * 
 * Return value: the new #FoTree
 **/
FoFo*
fo_tree_new (void)
{
  return FO_FO (g_object_new (fo_tree_get_type (), NULL));
}

static void
fo_tree_free_hash_key (gpointer key,
		       gpointer value G_GNUC_UNUSED,
		       gpointer user_data G_GNUC_UNUSED)
{
  g_free (key);
}

/**
 * fo_tree_id_add:
 * @tree: #FoTree to which to add a #FoFo.
 * @id:   Id to use for the #FoFo.
 * @fo:   #FoFo to add.
 * 
 * Adds @fo to @tree under @name.
 **/
void
fo_tree_id_add (FoFo        *tree,
		const gchar *id,
		FoFo        *fo)
{
  g_return_if_fail (tree != NULL);
  g_return_if_fail (FO_IS_TREE (tree));
  g_return_if_fail (id != NULL);
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FO (fo));

  /*
  g_print ("Adding '%s'\n", id);
  */
  if (g_hash_table_lookup (FO_TREE (tree)->id_hash, id))
    {
      g_warning ("'%s' already in id hash.  Not adding.", id);
    }
  else
    {
      g_hash_table_insert (FO_TREE (tree)->id_hash,
			   g_strdup (id),
			   fo);
    }
}

/**
 * fo_tree_id_get:
 * @tree: #FoTree for which to get a #FoFo.
 * @id:   Id of the #FoFo to get.
 * 
 * Gets the #FoFo of @tree corresponding to @id.
 * 
 * Return value: #FoFo matching @id, or NULL.
 **/
FoFo*
fo_tree_id_get (FoFo        *tree,
		const gchar *id)
{
  g_return_val_if_fail (tree != NULL, NULL);
  g_return_val_if_fail (FO_IS_TREE (tree), NULL);
  g_return_val_if_fail (id != NULL, NULL);

  return g_hash_table_lookup (FO_TREE (tree)->id_hash,
			      id);
}

/**
 * fo_tree_master_name_add:
 * @tree: #FoTree to which to add a #FoPageMaster.
 * @name: Name to use for the #FoPageMaster.
 * @fo:   #FoPageMaster to add.
 * 
 * Adds @fo to @tree under @name.
 **/
void
fo_tree_master_name_add (FoFo *tree,
			 const gchar *name,
			 FoFo *fo)
{
  g_return_if_fail (tree != NULL);
  g_return_if_fail (FO_IS_TREE (tree));
  g_return_if_fail (name != NULL);
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FO (fo));

  /*
  g_print ("Adding '%s'\n", name);
  */
  if (g_hash_table_lookup (FO_TREE (tree)->master_name_hash, name))
    {
      g_warning ("'%s' already in master name hash.", name);
    }
  else
    {
      g_hash_table_insert (FO_TREE (tree)->master_name_hash,
			   g_strdup (name),
			   fo);
    }

  if (FO_TREE (tree)->default_master == NULL)
    FO_TREE (tree)->default_master = fo;
}

/**
 * fo_tree_master_name_get:
 * @tree: #FoTree for which to get a #FoPageMaster.
 * @name: Name of the #FoPageMaster to get.
 * 
 * Gets the #FoPageMaster of @tree corresponding to @name.
 * 
 * Return value: #FoPageMaster matching @name, or NULL.
 **/
FoFo*
fo_tree_master_name_get (FoFo        *tree,
			 const gchar *name)
{
  g_return_val_if_fail (tree != NULL, NULL);
  g_return_val_if_fail (FO_IS_TREE (tree), NULL);
  g_return_val_if_fail (name != NULL, NULL);

  return g_hash_table_lookup (FO_TREE (tree)->master_name_hash,
			      name);
}

/**
 * fo_tree_page_sequence_master_name_add:
 * @tree: #FoTree for which to add a #FoPageSequenceMaster.
 * @name: Name of the #FoPageSequenceMaster.
 * @fo:   #FoPageSequenceMaster to add.
 * 
 * Adds @fo to to @tree.
 **/
void
fo_tree_page_sequence_master_name_add (FoFo *tree,
				       const gchar *name,
				       FoFo *fo)
{
  g_return_if_fail (tree != NULL);
  g_return_if_fail (FO_IS_TREE (tree));
  g_return_if_fail (name != NULL);
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FO (fo));

  if (g_hash_table_lookup (FO_TREE (tree)->page_sequence_master_name_hash,
			   name))
    {
      g_warning ("'%s' already in page-sequence-master name hash.", name);
    }
  else
    {
      g_hash_table_insert (FO_TREE (tree)->page_sequence_master_name_hash,
			   g_strdup (name),
			   fo);
    }
}

/**
 * fo_tree_page_sequence_master_name_get:
 * @tree: #FoTree for which to get a named #FoPageSequenceMaster.
 * @name: Name of the #FoPageSequenceMaster.
 * 
 * Gets the #FoPageSequenceMaster of @tree with name matching @name.
 * 
 * Return value: #FoPageSequenceMaster corresponding to @name, or NULL.
 **/
FoFo*
fo_tree_page_sequence_master_name_get (FoFo *tree,
				       const gchar *name)
{
  g_return_val_if_fail (tree != NULL, NULL);
  g_return_val_if_fail (FO_IS_TREE (tree), NULL);
  g_return_val_if_fail (name != NULL, NULL);

  return g_hash_table_lookup (FO_TREE (tree)->page_sequence_master_name_hash,
			      name);
}

/**
 * fo_tree_default_master_get:
 * @tree: #FoTree for which to get the default master.
 * 
 * Gets the default page master of @tree.
 * 
 * Return value: The default page sequence master of @fo.
 **/
FoFo*
fo_tree_default_master_get (FoFo *tree)
{
  g_return_val_if_fail (tree != NULL, NULL);
  g_return_val_if_fail (FO_IS_TREE (tree), NULL);

  return FO_TREE (tree)->default_master;
}

typedef struct _FoTreeSortedHashDumpData
{
  GHashTable  *hash;
  GSList      *keys;
  const gchar *indent;
} FoTreeSortedHashDumpData;

static void
fo_tree_hash_key_to_list (gpointer key,
			  gpointer value G_GNUC_UNUSED,
			  gpointer data)
{
  FoTreeSortedHashDumpData *hash_dump_data =
    (FoTreeSortedHashDumpData *) data;

  hash_dump_data->keys =
    g_slist_prepend (hash_dump_data->keys,
		     key);
}

static void
fo_tree_debug_dump_hash_from_keys (gpointer data,
				   gpointer user_data)
{
  FoTreeSortedHashDumpData *hash_dump_data =
    (FoTreeSortedHashDumpData *) user_data;

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s : %p",
	 hash_dump_data->indent,
	 (gchar *) data,
	 (gchar *) g_hash_table_lookup (hash_dump_data->hash,
					data));
}

static void
fo_tree_debug_dump_sorted_hash (GHashTable *hash,
				gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  FoTreeSortedHashDumpData hash_dump_data = { hash, NULL, indent };

  g_hash_table_foreach (hash,
			fo_tree_hash_key_to_list,
			&hash_dump_data);

  hash_dump_data.keys = g_slist_sort (hash_dump_data.keys,
				      (GCompareFunc) strcmp);

  g_slist_foreach (hash_dump_data.keys,
		   fo_tree_debug_dump_hash_from_keys,
		   (gpointer) &hash_dump_data);

  g_slist_free (hash_dump_data.keys);
  g_free (indent);
}

void
fo_tree_debug_dump_properties (FoFo *fo, gint depth)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TREE (fo));

  FoTree *fo_tree = FO_TREE (fo);

  gchar *indent = g_strnfill (depth * 2, ' ');
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sdefault-master:   %p",
	 indent,
	 fo_tree->default_master);
  if (fo_tree->master_name_hash != NULL)
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%smaster-name hash:",
	     indent);
      fo_tree_debug_dump_sorted_hash (fo_tree->master_name_hash,
				      depth + 1);
    }

  if (fo_tree->page_sequence_master_name_hash != NULL)
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%spage-sequence-master-name hash:",
	     indent);
      fo_tree_debug_dump_sorted_hash (fo_tree->page_sequence_master_name_hash,
				      depth + 1);
    }

  if (fo_tree->id_hash != NULL)
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%sid hash:",
	     indent);
      fo_tree_debug_dump_sorted_hash (fo_tree->id_hash,
				      depth + 1);
    }

  g_free (indent);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 2);
}

gboolean
fo_tree_validate_content (FoFo *fo,
			  GError **error)
{
  GError *tmp_error;

  g_return_val_if_fail (FO_IS_TREE (fo), TRUE);

  if ((fo_node_n_children (FO_NODE (fo)) == 1) &&
      FO_IS_ROOT (fo_node_first_child (FO_NODE (fo))))
    return FALSE;
  else
    {
      tmp_error = g_error_new (FO_FO_ERROR,
			       FO_FO_ERROR_INVALID_CONTENT,
			       _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			       fo_object_sprintf (FO_OBJECT (fo)));

      return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					       error,
					       tmp_error);
    }
}
