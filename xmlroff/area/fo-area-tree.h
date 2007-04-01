/* Fo
 * fo-area-tree.h: Area tree root
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-tree.h,v 1.3 2003/03/19 21:13:02 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#ifndef __FO_AREA_TREE_H__
#define __FO_AREA_TREE_H__

#include <libfo/fo-utils.h>
#include <area/fo-area.h>

G_BEGIN_DECLS

typedef struct _FoAreaTree      FoAreaTree;
typedef struct _FoAreaTreeClass FoAreaTreeClass;

#define FO_TYPE_AREA_TREE              (fo_area_tree_get_type ())
#define FO_AREA_TREE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA_TREE, FoAreaTree))
#define FO_AREA_TREE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA_TREE, FoAreaTreeClass))
#define FO_IS_AREA_TREE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA_TREE))
#define FO_IS_AREA_TREE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA_TREE))
#define FO_AREA_TREE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA_TREE, FoAreaTreeClass))


GType         fo_area_tree_get_type      (void) G_GNUC_CONST;
FoArea *fo_area_tree_new (void);

G_END_DECLS

#endif /* !__FO_AREA_TREE_H__ */
