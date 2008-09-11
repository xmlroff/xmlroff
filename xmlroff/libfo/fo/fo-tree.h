/* Fo
 * fo-tree.h: Formatting object tree root
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_TREE_H__
#define __FO_TREE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

typedef struct _FoTree      FoTree;
typedef struct _FoTreeClass FoTreeClass;

#define FO_TYPE_TREE              (fo_tree_get_type ())
#define FO_TREE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_TREE, FoTree))
#define FO_TREE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_TREE, FoTreeClass))
#define FO_IS_TREE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_TREE))
#define FO_IS_TREE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_TREE))
#define FO_TREE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_TREE, FoTreeClass))


GType  fo_tree_get_type                      (void) G_GNUC_CONST;
FoFo * fo_tree_new                           (void);
void   fo_tree_id_add                        (FoFo        *tree,
					      const gchar *id,
					      FoFo        *fo);
FoFo * fo_tree_id_get                        (FoFo        *tree,
					      const gchar *id);
void   fo_tree_master_name_add               (FoFo        *tree,
					      const gchar *name,
					      FoFo        *fo);
FoFo * fo_tree_master_name_get               (FoFo        *tree,
					      const gchar *name);
void   fo_tree_page_sequence_master_name_add (FoFo        *tree,
					      const gchar *name,
					      FoFo        *fo);
FoFo * fo_tree_page_sequence_master_name_get (FoFo        *tree,
					      const gchar *name);
FoFo * fo_tree_default_master_get            (FoFo        *tree);

G_END_DECLS

#endif /* !__FO_TREE_H__ */
