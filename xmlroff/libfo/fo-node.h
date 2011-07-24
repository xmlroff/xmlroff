/* Fo
 * fo-node.h: Base class for objects that are nodes in a tree
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_NODE_H__
#define __FO_NODE_H__

#include <libfo/fo-utils.h>

/**
 * FoNode:
 *
 * Instance of #FoNode.
 **/
typedef struct _FoNode      FoNode;

/**
 * FoNodeClass:
 *
 * Class structure for #FoNode.
 **/
typedef struct _FoNodeClass FoNodeClass;

#include "fo-object.h"

G_BEGIN_DECLS

#define FO_TYPE_NODE              (fo_node_get_type ())
#define FO_NODE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_NODE, FoNode))
#define FO_NODE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_NODE, FoNodeClass))
#define FO_IS_NODE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_NODE))
#define FO_IS_NODE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_NODE))
#define FO_NODE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_NODE, FoNodeClass))


GType         fo_node_get_type      (void) G_GNUC_CONST;
FoNode *fo_node_new           (void);
/* tree functions */
typedef gboolean	(*FoNodeTraverseFunc)	(FoNode	       *fo_node,
						 gpointer	data);
typedef void		(*FoNodeForeachFunc)	(FoNode	       *fo_node,
						 gpointer	data);

#define FO_NODE_IS_ROOT(fo_node)    (G_NODE_IS_ROOT(((FoNode*) (fo_node))->node))
#define FO_NODE_IS_LEAF(fo_node)    (G_NODE_IS_LEAF(((FoNode*) (fo_node))->node))

FoNode* fo_node_get_ancestor_or_self_by_type (FoNode     *node,
					      const GType type);
FoNode* fo_node_get_ancestor_or_self_by_name (FoNode      *node,
					      const gchar *name);
FoNode* fo_node_get_child_by_type (FoNode      *node,
				   const GType  type);
FoNode* fo_node_get_child_by_name (FoNode      *node,
				   const gchar *name);

FoNode* fo_node_insert           (FoNode           *parent,
                                  gint              position,
                                  FoNode           *fo_node);
FoNode* fo_node_insert_before    (FoNode           *parent,
                                  FoNode           *sibling,
                                  FoNode           *fo_node);
FoNode* fo_node_insert_after     (FoNode           *parent,
                                  FoNode           *sibling,
                                  FoNode           *fo_node); 
FoNode* fo_node_prepend          (FoNode           *parent,
                                  FoNode           *fo_node);
#define fo_node_n_nodes(root, flags) \
          g_node_n_nodes (((FoNode *) (root))->node, (flags))
#define fo_node_get_root(root)   \
          ((FoNode *) g_node_get_root (((FoNode *) (root))->node)->data)
#define fo_node_is_ancestor(fo_node, descendant) \
          g_node_is_ancestor(((FoNode *) (fo_node))->node, \
                             ((FoNode *) (descendant))->node)
#define fo_node_depth(fo_node)      \
          g_node_depth(((FoNode *) (fo_node))->node)
FoNode* fo_node_append           (FoNode *parent,
                                  FoNode *fo_node);
void    fo_node_traverse         (FoNode 	     *root,
				  GTraverseType       order,
				  GTraverseFlags      flags,
				  gint                max_depth,
				  FoNodeTraverseFunc  func,
				  gpointer            data);
#define fo_node_max_height(root)  \
          g_node_max_height(((FoNode *) (root))->node)
void    fo_node_children_foreach (FoNode 	    *fo_node,
				  GTraverseFlags     flags,
				  FoNodeForeachFunc  func,
				  gpointer           data);
#define fo_node_reverse_children(fo_node) \
          g_node_reverse_children(((FoNode *) (fo_node))->node)
#define fo_node_n_children(fo_node)  \
          g_node_n_children(((FoNode *) (fo_node))->node)
#define fo_node_nth_child(fo_node, n) \
          (g_node_nth_child (((FoNode *) (fo_node))->node, (n)) ? \
           ((FoNode *) g_node_nth_child (((FoNode *) (fo_node))->node, (n))->data) : NULL)
#define fo_node_last_child(fo_node)  \
          (g_node_last_child (((FoNode *) (fo_node))->node) ? \
           ((FoNode *) g_node_last_child (((FoNode *) (fo_node))->node)->data) : NULL)
#define fo_node_child_position(fo_node, child) \
          g_node_child_position(((FoNode *) (fo_node))->node, \
                                ((FoNode *) (child))->node)
#define fo_node_first_sibling(fo_node) \
          (g_node_first_sibling (((FoNode *) (fo_node))->node) ? \
           ((FoNode *) g_node_first_sibling (((FoNode *) (fo_node))->node)->data) : NULL)
#define fo_node_last_sibling(fo_node) \
          (g_node_last_sibling (((FoNode *) (fo_node))->node) ? \
           ((FoNode *) g_node_last_sibling (((FoNode *) (fo_node))->node)->data) : NULL)
#define fo_node_prev_sibling(fo_node) \
          (g_node_prev_sibling (((FoNode *) (fo_node))->node) ? \
           ((FoNode *) g_node_prev_sibling (((FoNode *) (fo_node))->node)->data) : NULL)
FoNode * fo_node_next_sibling (FoNode *fo_node);
FoNode * fo_node_first_child  (FoNode *fo_node);
FoNode * fo_node_parent       (FoNode *fo_node);
void     fo_node_unlink                    (FoNode *fo_node);
void     fo_node_unlink_with_next_siblings (FoNode *fo_node);
FoNode * fo_node_insert_with_next_siblings (FoNode *parent,
					    gint    position,
					    FoNode *fo_node);
void     fo_node_debug_dump_tree (FoNode *fo_node,
				 gint    depth);

G_END_DECLS

#endif /* !__FO_NODE_H__ */
