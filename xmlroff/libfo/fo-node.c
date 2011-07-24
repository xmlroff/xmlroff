/* Fo
 * fo-node.c: Base class for objects that are nodes in a tree
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-node-private.h"

/**
 * SECTION:fo-node
 * @short_description: Object for making trees
 *
 * #FoObject child type that makes trees.
 */

enum {
  PROP_0,
  PROP_PARENT,
  PROP_NEXT_SIBLING,
  PROP_FIRST_CHILD
};

static void     fo_node_init            (FoNode        *object);
static void     fo_node_base_class_init (FoNodeClass   *klass);
static void     fo_node_class_init      (FoNodeClass   *klass);
static void     fo_node_get_property    (GObject       *object,
					 guint          prop_id,
					 GValue        *value,
					 GParamSpec    *pspec);
static void     fo_node_set_property    (GObject       *object,
					 guint          prop_id,
					 const GValue  *value,
					 GParamSpec    *pspec);

static void     _dispose                   (GObject  *object);

static void     _debug_dump                        (FoObject *object,
						    gint      depth);
static void     _debug_dump_tree                   (FoNode   *fo_node,
						    gint      depth);
static gchar*   _sprintf                           (FoObject *object);
static FoNode*  _insert_default                    (FoNode   *parent,
						    gint      position,
						    FoNode   *fo_node);
static FoNode*  _insert_before_default             (FoNode   *parent,
						    FoNode   *sibling,
						    FoNode   *fo_node);
static FoNode*  _insert_after_default              (FoNode   *parent,
						    FoNode   *sibling,
						    FoNode   *fo_node);
static void     _unlink_with_next_siblings_default (FoNode   *fo_node);
static FoNode*  _insert_with_next_siblings_default (FoNode   *parent,
						    gint      position,
						    FoNode   *fo_node);
static FoNode*  _prepend_default                   (FoNode   *parent,
						    FoNode   *fo_node);
static FoNode*  _append_default                    (FoNode   *parent,
						    FoNode   *fo_node);
static void     _log_warning                (FoObject *object,
					     GError  **warning);
static void     _log_error                  (FoObject *object,
					     GError  **error);
static gboolean _log_or_propagate_error     (FoObject *fo_object,
					     GError  **dest,
					     GError   *src);
static gboolean _maybe_propagate_error      (FoObject *fo_object,
					     GError  **dest,
					     GError   *src,
					     gboolean  continue_after_error);

static gpointer parent_class;

/**
 * fo_node_get_type:
 * 
 * Register the #FoNode object type.
 * 
 * Return value: #GType value of the #FoNode object type.
 **/
GType
fo_node_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoNodeClass),
        (GBaseInitFunc) fo_node_base_class_init,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_node_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoNode),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_node_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoNode",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }
  
  return object_type;
}

/**
 * fo_node_init:
 * @fo_node: #FoNode object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoNode.
 **/
void
fo_node_init (FoNode *object)
{
  object->node = g_node_new ((gpointer *) object);
}

/**
 * fo_node_base_class_init:
 * @klass: #FoNodeClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoNodeClass.
 **/
void
fo_node_base_class_init (FoNodeClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);

  fo_object_class->debug_dump             = _debug_dump;
  fo_object_class->print_sprintf          = _sprintf;
  fo_object_class->log_warning            = _log_warning;
  fo_object_class->log_error              = _log_error;
  fo_object_class->log_or_propagate_error = _log_or_propagate_error;
  fo_object_class->maybe_propagate_error  = _maybe_propagate_error;

  klass->debug_dump_tree = _debug_dump_tree;
  klass->insert = _insert_default;
  klass->insert_before = _insert_before_default;
  klass->insert_after = _insert_after_default;
  klass->insert_with_next_siblings =
    _insert_with_next_siblings_default;
  klass->unlink_with_next_siblings =
    _unlink_with_next_siblings_default;
  klass->prepend = _prepend_default;
  klass->append = _append_default;
}

/**
 * fo_node_class_init:
 * @klass: #FoNodeClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoNodeClass.
 **/
void
fo_node_class_init (FoNodeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->dispose = _dispose;

  object_class->set_property = fo_node_set_property;
  object_class->get_property = fo_node_get_property;

  g_object_class_install_property
    (object_class,
     PROP_PARENT,
     g_param_spec_object ("parent",
			  _("parent node"),
			  _("Parent node in the node tree"),
			  FO_TYPE_NODE,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_NEXT_SIBLING,
     g_param_spec_object ("next-sibling",
			  _("Next sibling node"),
			  _("Next sibling node in the node tree"),
			  FO_TYPE_NODE,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FIRST_CHILD,
     g_param_spec_object ("first-child",
			  _("first child node"),
			  _("First child node in the node tree"),
			  FO_TYPE_NODE,
			  G_PARAM_READABLE));
}

/**
 * _dispose:
 * @object: #FoNode object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoNode.
 **/
void
_dispose (GObject *object)
{
  FoNode *node;

  node = FO_NODE (object);
  /* Node should already be removed from the FoNode tree, since this
     destroys the GNode subtree remaining under node */
  if (node->node != NULL)
    {
      g_node_destroy (node->node);
      node->node = NULL;
    }

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * fo_node_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoNode.
 **/
void
fo_node_get_property (GObject        *object,
		      guint           param_id,
		      GValue         *value,
		      GParamSpec     *pspec)
{
  FoNode *fo_node = FO_NODE (object);

  switch (param_id)
    {
    case PROP_PARENT:
      g_value_set_object (value, G_OBJECT (fo_node_parent (fo_node)));
      break;
    case PROP_NEXT_SIBLING:
      g_value_set_object (value, G_OBJECT (fo_node_next_sibling (fo_node)));
      break;
    case PROP_FIRST_CHILD:
      g_value_set_object (value, G_OBJECT (fo_node_first_child (fo_node)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_node_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoNode.
 **/
void
fo_node_set_property (GObject      *object,
		      guint         param_id,
		      const GValue *value G_GNUC_UNUSED,
		      GParamSpec   *pspec)
{
  switch (param_id)
    {
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_node_new:
 * 
 * Creates a new #FoNode initialized to default value.
 * 
 * Return value: the new #FoNode
 **/
FoNode *
fo_node_new (void)
{
  FoNode *object;

  object = FO_NODE (g_object_new (fo_node_get_type (), NULL));
  
  return object;
}

/**
 * _debug_dump:
 * @object: #FoObject to be dumped.
 * @depth:  Relative indent to add to the output.
 * 
 * Implements #FoObject debug_dump method for #FoNode.
 **/
static void
_debug_dump (FoObject *object,
	     gint      depth)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_NODE (object));

  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);
  g_free (indent);

  FO_NODE_GET_CLASS (object)->debug_dump_properties (FO_NODE (object),
						     depth + 2);
  FoNode *child = fo_node_first_child (FO_NODE (object));
  while (child != NULL)
    {
      fo_object_debug_dump (child,
			    depth + 1);

      child = fo_node_next_sibling (child);
    }
}

/**
 * _debug_dump_tree:
 * @node:  #FoNode to be dumped.
 * @depth: Relative indent to add to the output.
 * 
 * Implements #FoNode debug_dump_tree method for #FoNode.
 **/
static void
_debug_dump_tree (FoNode *fo_node,
		  gint    depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* fo_node_sprintf;
  FoNode *child;

  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_NODE (fo_node));

  fo_node_sprintf = fo_object_debug_sprintf (fo_node);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 fo_node_sprintf);

  g_free (fo_node_sprintf);
  g_free (indent);

  child = fo_node_first_child (fo_node);
  while (child != NULL)
    {
      fo_node_debug_dump_tree (child,
			       depth + 1);

      child = fo_node_next_sibling (child);
    }
}

/**
 * fo_node_debug_dump_tree:
 * @fo_node: #FoNode to be dumped.
 * @depth:   Relative indent to add to the output.
 * 
 * Logs the tree structure beginning at @fo_node.
 **/
void
fo_node_debug_dump_tree (FoNode *fo_node,
			 gint    depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  if (fo_node == NULL)
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%s(null)",
	     indent);
    }
  else if (!G_IS_OBJECT (fo_node))
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%sNot a GObject: %p",
	     indent,
	     fo_node);
    }
  else if (!FO_IS_NODE (fo_node))
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%sGObject but not an FoFo_Node:: %s (%p : %d)",
	     indent,
	     g_type_name (G_TYPE_FROM_INSTANCE (fo_node)),
	     fo_node,
	     ((GObject *) fo_node)->ref_count);
    }
  else
    {
      FO_NODE_GET_CLASS (fo_node)->debug_dump_tree (fo_node, depth);
    }

  g_free (indent);
}

/**
 * _sprintf:
 * @object: #FoNode to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
static gchar*
_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_NODE (object), NULL);

  return (g_strdup_printf("%s",
			  g_type_name (G_TYPE_FROM_INSTANCE (object))));
}


/**
 * fo_node_get_ancestor_or_self_by_type:
 * @node: #FoNode at which to begin.
 * @type: Required #GType of ancestor node.
 * 
 * Find the nearest ancestor node, or @node itself, with the same
 * #GType as @type.
 *
 * Does not change the ref count of any node.
 * 
 * Return value: #FoNode ancestor (or self) with required #GType, or NULL.
 **/
FoNode*
fo_node_get_ancestor_or_self_by_type (FoNode     *node,
				      const GType type)
{
  FoNode *use_node;

  g_return_val_if_fail (FO_IS_NODE (node), NULL);

  if (type != 0)
    {
      use_node = node;

      while (use_node && !g_type_is_a (G_TYPE_FROM_INSTANCE (use_node), type))
	{
	  use_node = fo_node_parent (use_node);
	}
    }
  else
    {
      use_node = NULL;
    }

  return use_node;
}

/**
 * fo_node_get_ancestor_or_self_by_name:
 * @node: #FoNode at which to begin.
 * @name: Required name of ancestor node.
 * 
 * Find the nearest ancestor node, or @node itself, with the same
 * name as @name.
 *
 * Does not change the ref count of any node.
 * 
 * Return value: #FoNode ancestor (or self) with required #GType, or NULL.
 **/
FoNode*
fo_node_get_ancestor_or_self_by_name (FoNode      *node,
				      const gchar *name)
{
  GType type;

  g_return_val_if_fail (FO_IS_NODE (node), NULL);
  g_return_val_if_fail (name != NULL, NULL);

  type = g_type_from_name (name);

  return fo_node_get_ancestor_or_self_by_type (node,
					       type);
}

/**
 * fo_node_get_child_by_type:
 * @node: #FoNode that is parent of nodes to be tested for matching #GType.
 * @type: #GType value.
 *
 * Find the first child of @node with #GType matching @type value.
 *
 * Does not change the ref count of any node.
 * 
 * Allows 0 as value of @type since may have been called by
 * #fo_node_get_child_by_name for a type that has yet to be
 * instantiated.  Of course, if @type is 0, this function returns
 * NULL.
 * 
 * Return value: First child of specified type, or NULL.
 **/
FoNode*
fo_node_get_child_by_type (FoNode     *node,
			   const GType type)
{
  FoNode *child = NULL;

  g_return_val_if_fail (FO_IS_NODE (node), NULL);

  if (type != 0)
    {
      child = fo_node_first_child (node);

      while (child && G_TYPE_FROM_INSTANCE (child) != type)
	{
	  child = fo_node_next_sibling (child);
	}

      return child;
    }
  else
    {
      return NULL;
    }
}

/**
 * fo_node_get_child_by_name:
 * @node: #FoNode that is parent of nodes to be tested for type name.
 * @name: Name of type.
 *
 * Find the first child of @node with type name matching @name value.
 *
 * Does not change the ref count of any node.
 * 
 * Return value: First child of specified type, or NULL.
 **/
FoNode*
fo_node_get_child_by_name (FoNode      *node,
			   const gchar *name)
{
  GType type;

  g_return_val_if_fail (FO_IS_NODE (node), NULL);
  g_return_val_if_fail (name != NULL, NULL);

  type = g_type_from_name (name);

  return fo_node_get_child_by_type (node, type);
}

/**
 * fo_node_dump_path_to_root:
 * @node: #FoNode for which to dump path to root.
 * 
 * Dumps (i.e., logs messages with 'DEBUG' severity) the node path
 * from @node to the root of the #FoNode tree containing @node.
 **/
void
fo_node_dump_path_to_root (FoNode *node)
{
  FoNode *use_node;
  gint depth = 0;
  gchar *indent, *object_sprintf;

  use_node = node;

  while (!FO_NODE_IS_ROOT (use_node))
    {
      indent = g_strnfill (2 * depth++, ' ');
      object_sprintf = fo_object_debug_sprintf (use_node);

      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%s%s",
	     indent,
	     object_sprintf);

      g_free (object_sprintf);
      g_free (indent);

      use_node = fo_node_parent (use_node);
    }
}

/**
 * _insert_default:
 * @parent:   The #FoNode to place @fo_node under.
 * @position: The position to place @fo_node at, with respect to its
 *            siblings.  If @position is -1, @fo_node is inserted as
 *            the last child of @parent.
 * @fo_node:  The #FoNode to insert.
 * 
 * Inserts an #FoNode beneath the parent at the given position.
 * 
 * Return value: The inserted #FoNode.
 **/
static FoNode *
_insert_default (FoNode *parent,
		 gint    position,
		 FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  g_object_ref_sink (fo_node);

  return ((FoNode *) g_node_insert (parent->node,
				    position,
				    fo_node->node)->data);
}

/**
 * fo_node_insert:
 * @parent:   The #FoNode to place @fo_node under.
 * @position: The position to place @fo_node at, with respect to its
 *            siblings.  If @position is -1, @fo_node is inserted as
 *            the last child of @parent.
 * @fo_node:  The #FoNode to insert.
 * 
 * Inserts an #FoNode beneath the parent at the given position.
 * 
 * Return value: The inserted #FoNode.
 **/
FoNode *
fo_node_insert (FoNode *parent,
		gint    position,
		FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  return FO_NODE_GET_CLASS (parent)->insert (parent,
					     position,
					     fo_node);
}

/**
 * _insert_before_default:
 * @parent:  The #FoNode to place @fo_node under.
 * @sibling: The sibling #FoNode to place @fo_node before.  If
 *           @sibling is NULL, @fo_node is inserted as the last child
 *           of @parent.
 * @fo_node: The #FoNode to insert.
 * 
 * Inserts an #FoNode beneath the parent before the given sibling.
 * 
 * Return value: The inserted #FoNode.
 **/
static FoNode *
_insert_before_default (FoNode *parent,
			FoNode *sibling,
			FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (sibling == NULL || FO_IS_NODE (sibling), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  g_object_ref_sink (fo_node);

  return ((FoNode *) g_node_insert_before (parent->node,
					   sibling->node,
					   fo_node->node)->data);
}

/**
 * fo_node_insert_before:
 * @parent:  The #FoNode to place @fo_node under.
 * @sibling: The sibling #FoNode to place @fo_node before.  If
 *           @sibling is NULL, @fo_node is inserted as the last child
 *           of @parent.
 * @fo_node: The #FoNode to insert.
 * 
 * Inserts an #FoNode beneath the parent before the given sibling.
 * 
 * Return value: The inserted #FoNode.
 **/
FoNode*
fo_node_insert_before (FoNode *parent,
		       FoNode *sibling,
		       FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (sibling == NULL || FO_IS_NODE (sibling), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  return FO_NODE_GET_CLASS (parent)->insert_before (parent,
						    sibling,
						    fo_node);
}

/**
 * _insert_after_default:
 * @parent:  The #FoNode to place @fo_node under.
 * @sibling: The sibling #FoNode to place @fo_node after.  If
 *           @sibling is NULL, @fo_node is inserted as the first child
 *           of @parent.
 * @fo_node: The #FoNode to insert.
 * 
 * Inserts an #FoNode beneath the parent after the given sibling.
 * 
 * Return value: The inserted #FoNode.
 **/
static FoNode *
_insert_after_default (FoNode *parent,
		       FoNode *sibling,
		       FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (sibling == NULL || FO_IS_NODE (sibling), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  g_object_ref_sink (fo_node);

  return ((FoNode *) g_node_insert_after (parent->node,
					  sibling->node,
					  fo_node->node)->data);
}
 
/**
 * fo_node_insert_after:
 * @parent:  The #FoNode to place @fo_node under.
 * @sibling: The sibling #FoNode to place @fo_node after.  If
 *           @sibling is NULL, @fo_node is inserted as the first child
 *           of @parent.
 * @fo_node: The #FoNode to insert.
 * 
 * Inserts an #FoNode beneath the parent after the given sibling.
 * 
 * Return value: The inserted #FoNode.
 **/
FoNode *
fo_node_insert_after (FoNode *parent,
		      FoNode *sibling,
		      FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (sibling == NULL || FO_IS_NODE (sibling), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  return FO_NODE_GET_CLASS (parent)->insert_after (parent,
						   sibling,
						   fo_node);
}

/**
 * _prepend_default:
 * @parent:  The #FoNode to place @fo_node under.
 * @fo_node: The #FoNode to insert.
 * 
 * Inserts an #FoNode as the first child of the given parent.
 * 
 * Return value: The inserted #FoNode.
 **/
static FoNode *
_prepend_default (FoNode *parent,
		  FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  g_object_ref_sink (fo_node);

  return ((FoNode *) g_node_prepend (parent->node,
				     fo_node->node)->data);
}

/**
 * fo_node_prepend:
 * @parent:  The #FoNode to place @fo_node under.
 * @fo_node: The #FoNode to insert.
 * 
 * Inserts an #FoNode as the first child of the given parent.
 * 
 * Return value: The inserted #FoNode.
 **/
FoNode*
fo_node_prepend (FoNode *parent,
		 FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  return FO_NODE_GET_CLASS (parent)->prepend (parent,
					      fo_node);
}

/**
 * _append_default:
 * @parent:  The #FoNode to place @fo_node under.
 * @fo_node: The #FoNode to insert.
 * 
 * Inserts an #FoNode as the last child of the given parent.
 * 
 * Return value: The inserted #FoNode.
 **/
static FoNode*
_append_default (FoNode *parent,
		 FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  g_object_ref_sink (fo_node);

  return ((FoNode *) g_node_append (parent->node,
				    fo_node->node)->data);
}

/**
 * fo_node_append:
 * @parent:  The #FoNode to place @fo_node under.
 * @fo_node: The #FoNode to insert.
 * 
 * Inserts an #FoNode as the last child of the given parent.
 * 
 * Return value: The inserted #FoNode.
 **/
FoNode*
fo_node_append (FoNode *parent,
		FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  return FO_NODE_GET_CLASS (parent)->append (parent,
					     fo_node);
}

typedef struct _FoNodeFuncData
{
  FoNodeForeachFunc func;
  gpointer node_func_data;
} FoNodeFuncData;

/**
 * _g_node_children_foreach_func:
 * @node: The #GNode for an #FoNode.
 * @data: #FoNodeFuncData with #FoNodeForeachFunc and 'real' user data.
 * 
 * Calls the #FoNodeForeachFunc function with the #FoNode
 * corresponding to @node and the 'real' user data as arguments.
 **/
static void
_g_node_children_foreach_func (GNode    *node,
				      gpointer  data)
{
  const FoNodeFuncData *fo_node_func_data = (FoNodeFuncData *) data;

  fo_node_func_data->func (node->data,
			   fo_node_func_data->node_func_data);
}

/**
 * fo_node_children_foreach:
 * @fo_node:  An #FoNode.
 * @flags:    Which types of children are to be visited, one of
 *            G_TRAVERSE_ALL, G_TRAVERSE_LEAFS and G_TRAVERSE_NON_LEAFS.
 * @func:     The function to call for each visited node.
 * @data:     User data to pass to the function.
 * 
 * Calls a function for each of the children of an #FoNode. Note that
 * it doesn't descend beneath the child nodes.
 **/
void
fo_node_children_foreach (FoNode 	    *fo_node,
			  GTraverseFlags     flags,
			  FoNodeForeachFunc  func,
			  gpointer           data)
{
  FoNodeFuncData g_node_children_foreach_data = {func, data};

  g_node_children_foreach (fo_node->node,
			   flags,
			   _g_node_children_foreach_func,
			   &g_node_children_foreach_data);
}

typedef struct _FoNodeTraverseFuncData
{
  FoNodeTraverseFunc func;
  gpointer node_func_data;
} FoNodeTraverseFuncData;

/**
 * _g_node_traverse_func:
 * @node: The #GNode for an #FoNode.
 * @data: #FoNodeFuncData with #FoNodeTraverseFunc and 'real' user data.
 * 
 * Calls the #FoNodeTraverseFunc function with the #FoNode
 * corresponding to @node and the 'real' user data as arguments.
 * 
 * Return value: The value returned by the #FoNodeTraverseFunc.
 **/
static gboolean
_g_node_traverse_func (GNode    *node,
		       gpointer  data)
{
  const FoNodeTraverseFuncData *traverse_func_data =
    (FoNodeTraverseFuncData *) data;

  return traverse_func_data->func (node->data,
				   traverse_func_data->node_func_data);
}

/**
 * fo_node_traverse:
 * @root:      The root #FoNode of the tree to traverse.
 * @order:     The order in which nodes are visited - G_IN_ORDER,
 *             G_PRE_ORDER, G_POST_ORDER, or G_LEVEL_ORDER.
 * @flags:     Which types of children are to be visited, one of
 *             G_TRAVERSE_ALL, G_TRAVERSE_LEAFS and G_TRAVERSE_NON_LEAFS.
 * @max_depth: The maximum depth of the traversal. Nodes below this
 *             depth will not be visited. If max_depth is -1 all nodes
 *             in the tree are visited. If depth is 1, only the root
 *             is visited. If depth is 2, the root and its children
 *             are visited. And so on.
 * @func:      The function to call for each visited GNode.
 * @data:      User data to pass to the function.
 * 
 * Traverses a tree starting at the given root #FoNode. It calls the
 * given function for each node visited. The traversal can be halted
 * at any point by returning %TRUE from @func.
 **/
void
fo_node_traverse (FoNode 	     *root,
		  GTraverseType       order,
		  GTraverseFlags      flags,
		  gint                max_depth,
		  FoNodeTraverseFunc  func,
		  gpointer            data)
{
  FoNodeTraverseFuncData g_node_traverse_data = {func, data};

  if (root->node != NULL)
    {
      g_node_traverse (root->node,
		       order,
		       flags,
		       max_depth,
		       _g_node_traverse_func,
		       &g_node_traverse_data);
    }
}

/**
 * fo_node_next_sibling:
 * @fo_node: The #FoNode.
 * 
 * Gets the next sibling #FoNode of @fo_node.
 * 
 * Return value: The next sibling of @fo_node, or %NULL.
 **/
FoNode *
fo_node_next_sibling (FoNode *fo_node)
{
  g_return_val_if_fail (fo_node != NULL, NULL);
  g_return_val_if_fail (FO_IS_NODE (fo_node), NULL);

  return g_node_next_sibling (fo_node->node) ?
    ((FoNode *) g_node_next_sibling (fo_node->node)->data) : NULL;
}

/**
 * fo_node_first_child:
 * @fo_node: The #FoNode.
 * 
 * Gets the first child #FoNode of @fo_node.
 * 
 * Return value: The first child of @fo_node, or %NULL.
 **/
FoNode *
fo_node_first_child (FoNode *fo_node)
{
  g_return_val_if_fail (fo_node != NULL, NULL);
  g_return_val_if_fail (FO_IS_NODE (fo_node), NULL);

  return g_node_first_child (fo_node->node) ?
    ((FoNode *) g_node_first_child (fo_node->node)->data) : NULL;
}

/**
 * fo_node_parent:
 * @fo_node: The #FoNode.
 * 
 * Gets the parent #FoNode of @fo_node.
 * 
 * Return value: The parent of @fo_node.
 **/
FoNode *
fo_node_parent (FoNode *fo_node)
{
  g_return_val_if_fail (fo_node != NULL, NULL);
  g_return_val_if_fail (FO_IS_NODE (fo_node), NULL);

  return fo_node->node->parent ?
    FO_NODE (fo_node->node->parent->data) : NULL;
}

/**
 * _unlink_with_next_siblings_default:
 * @fo_node: First #FoNode to be unlinked
 * 
 * Unlink @fo_node and its next siblings (i.e., 'following siblings'
 * in XPath parlance) from their place in their current #FoNode tree.
 *
 * @fo_node and its next siblings remain linked together, and any of
 * those nodes keep their child nodes.  Neither @fo_node nor any of
 * its following siblings are valid roots since they each have a next
 * and/or a previous sibling, even if they don't have a parent.
 **/
static void
_unlink_with_next_siblings_default (FoNode *fo_node)
{
  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_NODE (fo_node));

  GNode *use_node = fo_node->node;

  if (use_node->prev != NULL)
    {
      use_node->prev->next = NULL;
      use_node->prev = NULL;
    }
  else if (use_node->parent != NULL)
    {
      /* If there was no 'prev', this could be the first child of a
	 parent. */
      use_node->parent->children = NULL;
    }

  while (use_node != NULL)
    {
      g_object_force_floating (use_node->data);

      use_node->parent = NULL;
      use_node = use_node->next;
    }
}

/**
 * fo_node_unlink_with_next_siblings:
 * @fo_node: First #FoNode to be unlinked
 * 
 * Unlink @fo_node and its next siblings (i.e., 'following siblings'
 * in XPath parlance) from their place in their current #FoNode tree.
 *
 * @fo_node and its next siblings remain linked together, and any of
 * those nodes keep their child nodes.  Neither @fo_node nor any of
 * its following siblings are valid roots since they each have a next
 * and/or a previous sibling, even if they don't have a parent.
 **/
void
fo_node_unlink_with_next_siblings (FoNode *fo_node)
{
  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_NODE (fo_node));

  FO_NODE_GET_CLASS (fo_node)->unlink_with_next_siblings (fo_node);
}

/**
 * fo_node_unlink:
 * @fo_node: the #FoNode to unlink, which becomes the root of a new
 *           tree
 *
 * Unlinks a #FoNode from a tree, resulting in two separate trees.
 **/
void
fo_node_unlink (FoNode *fo_node)
{
  /* Only unref fo_node if it's currently in a tree. */
  gboolean will_unref = (fo_node->node->prev != NULL) ||
    (fo_node->node->parent != NULL);

  g_node_unlink (fo_node->node);

  if (will_unref)
    {
      g_object_unref (fo_node);
    }
}

/**
 * fo_node_insert_with_next_siblings_default:
 * @parent:   The #FoNode to place @fo_node under.
 * @position: The position to place @fo_node at, with respect to its
 *            siblings.  If @position is -1, @fo_node is inserted as
 *            the last child of @parent.
 * @fo_node:  First #FoNode to be inserted.
 * 
 * Insert @fo_node and its next siblings (i.e., 'following siblings'
 * in XPath parlance) beneath @parent at the given position.
 *
 * @fo_node and its next siblings should not already have a parent
 * #FoNode.
 *
 * Return value: The inserted #FoNode.
 **/
static FoNode *
_insert_with_next_siblings_default (FoNode *parent,
				    gint    position,
				    FoNode *fo_node)
{
  g_return_val_if_fail (parent != NULL, fo_node);
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (fo_node != NULL, fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  FoNode *use_node = fo_node;

  while (use_node != NULL)
    {
      FoNode *next_sibling = fo_node_next_sibling (use_node);

      /* Keep a reference while use_node is unlinked. */
      g_object_ref_sink (use_node);

      fo_node_unlink (use_node);
      fo_node_insert (parent, position++, use_node);
      g_object_unref (use_node);

      use_node = next_sibling;
    }

  return fo_node;
}

/**
 * fo_node_insert_with_next_siblings:
 * @parent:   The #FoNode to place @fo_node under.
 * @position: The position to place @fo_node at, with respect to its
 *            siblings.  If @position is -1, @fo_node is inserted as
 *            the last child of @parent.
 * @fo_node:  First #FoNode to be inserted.
 * 
 * Insert @fo_node and its next siblings (i.e., 'following siblings'
 * in XPath parlance) beneath @parent at the given position.
 *
 * @fo_node and its next siblings should not already have a parent
 * #FoNode.
 *
 * Return value: The inserted #FoNode.
 **/
FoNode *
fo_node_insert_with_next_siblings (FoNode *parent,
				   gint    position,
				   FoNode *fo_node)
{
  g_return_val_if_fail (parent != NULL, fo_node);
  g_return_val_if_fail (FO_IS_NODE (parent), fo_node);
  g_return_val_if_fail (fo_node != NULL, fo_node);
  g_return_val_if_fail (FO_IS_NODE (fo_node), fo_node);

  return FO_NODE_GET_CLASS (parent)->insert_with_next_siblings (parent,
								position,
								fo_node);
}

/**
 * _path_step_sprintf:
 * @fo_node: The #FoNode
 * 
 * Creates a string representation of the XPath step for @fo_node.
 * 
 * The string should be freed by the calling function.
 *
 * Return value: String representing the XPath step for @fo_node.
 **/
static gchar*
_path_step_sprintf (FoNode *fo_node)
{
  g_return_val_if_fail (FO_IS_NODE (fo_node), NULL);

  gchar *node_name = fo_object_sprintf (FO_OBJECT (fo_node));

  FoNode *sibling_node = fo_node_prev_sibling (fo_node);

  gint count = 1;
  while (sibling_node != NULL)
    {
      if (G_TYPE_FROM_INSTANCE (sibling_node) ==
	  G_TYPE_FROM_INSTANCE (fo_node))
	count++;
      sibling_node = fo_node_prev_sibling (sibling_node);
    }

  GString *path_step = g_string_new (NULL);
  g_string_printf (path_step,
		   "/%s[%d%s]",
		   node_name,
		   count,
		   g_object_is_floating (fo_node) ? " (floating)" : "");

  g_free (node_name);

  return g_string_free (path_step, FALSE);
}

/**
 * fo_node_path_to_root_sprintf:
 * @fo_node: The #FoNode.
 * 
 * Creates a string representation of the path from @fo_node to the
 * root of its #FoNode tree.
 *
 * The string should be freed by the calling function.
 * 
 * Return value: String representation of path from @fo_node to its
 *               root.
 **/
static gchar*
fo_node_path_to_root_sprintf (FoNode *fo_node)
{
  g_return_val_if_fail (fo_node != NULL, NULL);
  g_return_val_if_fail (FO_IS_NODE (fo_node), NULL);

  gchar *node_name = _path_step_sprintf (fo_node);
  GString *path = g_string_new (node_name);
  g_free (node_name);
  
  FoNode *use_node = fo_node_parent (FO_NODE (fo_node));

  while (use_node != NULL)
    {
      gchar *old_path = g_strdup (path->str);

      node_name = _path_step_sprintf (use_node);

      g_string_printf (path,
		       "%s%s",
		       node_name,
		       old_path);

      g_free (node_name);
      g_free (old_path);

      use_node = fo_node_parent (use_node);
    }

  return g_string_free (path, FALSE);
}

/**
 * _log_warning:
 * @object: #FoNode that is subject of @warning.
 * @warning: #GError with information about warning that occurred.
 * 
 * Logs both the warning represented by @warning and the #FoNode path from
 * @object to the root of its #FoNode tree.
 **/
static void
_log_warning (FoObject *object,
	      GError  **warning)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_NODE (object));
  g_return_if_fail (warning != NULL && *warning != NULL);

  gchar *node_name = _path_step_sprintf (FO_NODE (object));
  GString *path = g_string_new (NULL);
  g_string_printf (path,
		   "%s",
		   node_name);
  g_free (node_name);
  
  FoNode *use_node = fo_node_parent (FO_NODE (object));

  while (use_node != NULL)
    {
      gchar *old_path = g_strdup (path->str);

      node_name = _path_step_sprintf (use_node);

      g_string_printf (path,
		       "%s%s",
		       node_name,
		       old_path);

      g_free (node_name);
      g_free (old_path);

      use_node = fo_node_parent (use_node);
    }

  g_warning ("%s: %s\nObject path: %s",
	      g_quark_to_string ((*warning)->domain),
	      (*warning)->message,
	      path->str);

  g_string_free (path, TRUE);
  g_clear_error (warning);
}

/**
 * _log_error:
 * @object: The #FoNode.
 * @error:  #GError indicating the error.
 * 
 * Logs both the error represented by @error and the #FoNode path from
 * @object to the root of its #FoNode tree.
 **/
static void
_log_error (FoObject *object,
	    GError  **error)
{
  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_NODE (object));
  g_return_if_fail (error != NULL && *error != NULL);

  gchar *node_name = _path_step_sprintf (FO_NODE (object));
  GString *path = g_string_new (NULL);
  g_string_printf (path,
		   "%s",
		   node_name);
  g_free (node_name);
  
  FoNode *use_node = fo_node_parent (FO_NODE (object));

  while (use_node != NULL)
    {
      gchar *old_path = g_strdup (path->str);

      node_name = _path_step_sprintf (use_node);

      g_string_printf (path,
		       "%s%s",
		       node_name,
		       old_path);

      g_free (node_name);
      g_free (old_path);

      use_node = fo_node_parent (use_node);
    }

  g_critical ("%s: %s\nObject path: %s",
	      g_quark_to_string ((*error)->domain),
	      (*error)->message,
	      path->str);

  g_string_free (path, TRUE);
  g_clear_error (error);
}

/**
 * _log_or_propagate_error:
 * @fo_object: #FoObject that is the subject of @src.
 * @dest:      #GError to which to propagate @src, or NULL.
 * @src:       #GError with information about error that occurred.
 * 
 * If can propagate @src to @dest, do so, otherwise log @src using
 * fo_object_log_error().
 * 
 * Return value: %TRUE if error propagated, otherwise %FALSE.
 **/
static gboolean
_log_or_propagate_error (FoObject *fo_object,
			 GError  **dest,
			 GError   *src)
{
  GError *new_error;
  GString *new_message = g_string_new (NULL);
  gchar *path_to_root;

  g_return_val_if_fail (FO_IS_NODE (fo_object), TRUE);
  g_return_val_if_fail (dest == NULL || *dest == NULL, TRUE);
  g_return_val_if_fail (src != NULL, TRUE);

  path_to_root = fo_node_path_to_root_sprintf (FO_NODE (fo_object));

  g_string_printf (new_message,
		   "%s\nObject path: %s",
		   src->message,
		   path_to_root);

  new_error = g_error_new (src->domain,
			   src->code,
			   "%s",
			   new_message->str);

  g_string_free (new_message, TRUE);
  g_free (path_to_root);

  g_error_free (src);

  if (dest != NULL)
    {
      g_propagate_error (dest,
			 new_error);
      return TRUE;
    }
  else
    {
      fo_object_log_error (fo_object,
			   &new_error);
      return FALSE;
    }
}

/**
 * _maybe_propagate_error:
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
static gboolean
_maybe_propagate_error (FoObject *fo_object,
			GError  **dest,
			GError   *src,
			gboolean  continue_after_error)
{
  GError *new_error;
  GString *new_message = g_string_new (NULL);
  gchar *path_to_root;

  g_return_val_if_fail (FO_IS_NODE (fo_object), TRUE);
  g_return_val_if_fail (dest == NULL || *dest == NULL, TRUE);
  g_return_val_if_fail (src != NULL, TRUE);

  path_to_root = fo_node_path_to_root_sprintf (FO_NODE (fo_object));

  g_string_printf (new_message,
		   "%s\nObject path: %s",
		   src->message,
		   path_to_root);

  new_error = g_error_new (src->domain,
			   src->code,
			   "%s",
			   new_message->str);

  g_string_free (new_message, TRUE);
  g_free (path_to_root);

  g_error_free (src);

  if ((continue_after_error == FALSE) &&
      (dest != NULL))
    {
      g_propagate_error (dest,
			 new_error);
      return TRUE;
    }
  else
    {
      fo_object_log_error (fo_object,
			   &new_error);
      return FALSE;
    }
}
