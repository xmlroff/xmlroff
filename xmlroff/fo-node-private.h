/* Fo
 * fo-node-private.h: Structures private to the base class for objects
 *                    that are nodes in a tree.
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-node-private.h,v 1.2 2003/03/19 21:10:33 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_NODE_PRIVATE_H__
#define __FO_NODE_PRIVATE_H__

#include "fo-object.h"
#include "fo-node.h"

G_BEGIN_DECLS

struct _FoNode
{
  FoObject parent_instance;

  GNode *node;
};

struct _FoNodeClass
{
  FoObjectClass parent_class;

  void     (* debug_dump_properties)     (FoNode   *fo_node,
					  gint     depth);
  /* tree functions that may be restricted */
  FoNode*  (* insert)                    (FoNode *parent,
					  gint    position,
					  FoNode *fo_node);
  FoNode*  (* insert_before)	         (FoNode *parent,
					  FoNode *sibling,
					  FoNode *fo_node);
  FoNode*  (* insert_after)              (FoNode *parent,
					  FoNode *sibling,
					  FoNode *fo_node); 
  void     (* unlink_with_next_siblings) (FoNode *fo_node);
  FoNode*  (* insert_with_next_siblings) (FoNode *parent,
					  gint    position,
					  FoNode *fo_node);
  FoNode*  (* prepend)		         (FoNode *parent,
					  FoNode *fo_node);
  FoNode*  (* append)                    (FoNode *parent,
					  FoNode *fo_node);
};

G_END_DECLS

#endif /* !__FO_NODE_PRIVATE_H__ */
