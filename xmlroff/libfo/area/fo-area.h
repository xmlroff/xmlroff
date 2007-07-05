/* Fo
 * fo-area.h: Base area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_AREA_H__
#define __FO_AREA_H__

#include <libfo/fo-utils.h>

/**
 * FoArea:
 *
 * Instance of the base class for area objects.
 **/
typedef struct _FoArea      FoArea;

/**
 * FoAreaClass:
 *
 * Class structure for the base class for area objects.
 **/
typedef struct _FoAreaClass FoAreaClass;


#include <libfo/fo-node.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

#define FO_TYPE_AREA              (fo_area_get_type ())
#define FO_AREA(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_AREA, FoArea))
#define FO_AREA_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_AREA, FoAreaClass))
#define FO_IS_AREA(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_AREA))
#define FO_IS_AREA_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_AREA))
#define FO_AREA_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_AREA, FoAreaClass))


#include "fo-area-private.h"

GType    fo_area_get_type      (void) G_GNUC_CONST;
FoArea*  fo_area_new           (void);
FoArea*  fo_area_get_page (FoArea *fo_area);
FoArea*  fo_area_get_reference (FoArea *fo_area);
FoArea*  fo_area_get_page_sequence (FoArea *fo_area);
gboolean fo_area_get_is_first (FoArea *fo_area);
gboolean fo_area_get_is_last (FoArea *fo_area);
gfloat   fo_area_get_next_x (FoArea *fo_area);
void     fo_area_set_next_x (FoArea *fo_area,
			     gfloat  new_next_x);
gfloat   fo_area_get_next_y (FoArea *fo_area);
void     fo_area_set_next_y (FoArea *fo_area,
			     gfloat  new_next_y);
gfloat   fo_area_get_available_width (FoArea *fo_area);
void     fo_area_set_available_width (FoArea *fo_area,
				      gfloat new_available_width);
gfloat   fo_area_get_available_height (FoArea *fo_area);
void     fo_area_set_available_height (FoArea *fo_area,
				       gfloat new_available_height);
gfloat   fo_area_get_child_available_ipdim (FoArea *fo_area);
void     fo_area_set_child_available_ipdim (FoArea *fo_area,
					    gfloat new_child_available_ipdim);
gfloat   fo_area_get_child_available_bpdim (FoArea *fo_area);
void     fo_area_set_child_available_bpdim (FoArea *fo_area,
					    gfloat new_child_available_bpdim);
FoFo*    fo_area_get_generated_by (FoArea *fo_area);
void     fo_area_set_generated_by (FoArea *fo_area,
				   FoFo   *new_fo);

FoArea*  fo_area_add_child (FoArea *parent, FoArea *child);
FoArea*  fo_area_size_request (FoArea *child);
void     fo_area_debug_dump_properties (FoArea *area,
					gint depth);
void     fo_area_border_padding_space_resolve (FoArea *parent_area,
					       FoArea *child_area);
FoArea*  fo_area_break_resolve (FoArea *parent_area,
				FoArea *new_area);
void     fo_area_set_height_from_children (FoArea *parent_area);
FoArea*  fo_area_clone (FoArea *original);
void     fo_area_update_after_clone (FoArea *clone,
				     FoArea *original);
FoArea*  fo_area_split_before_height (FoArea *area,
				      gfloat  height);
gboolean fo_area_split_before_height_check (FoArea *area,
					    gfloat  height);
void     fo_area_resolve_text_align (FoArea *area);

/* tree functions */
typedef gboolean	(*FoAreaTraverseFunc)	(FoArea	       *area,
						 gpointer	data);
typedef void		(*FoAreaForeachFunc)	(FoArea	       *area,
						 gpointer	data);

#define FO_AREA_IS_ROOT(area)    (FO_NODE_IS_ROOT(((FoNode*) (area))))
#define FO_AREA_IS_LEAF(area)    (FO_NODE_IS_LEAF(((FoNode*) (area))))
FoArea* fo_area_insert           (FoArea           *parent,
                                  gint              position,
                                  FoArea           *area);
FoArea* fo_area_insert_before    (FoArea           *parent,
                                  FoArea           *sibling,
                                  FoArea           *area);
FoArea* fo_area_insert_after     (FoArea           *parent,
                                  FoArea           *sibling,
                                  FoArea           *area); 
FoArea* fo_area_prepend          (FoArea           *parent,
                                  FoArea           *area);
guint   fo_area_n_areas          (FoArea            *root,
				  GTraverseFlags     flags);
FoArea*  fo_area_get_root        (FoArea             *area);
gboolean fo_area_is_ancestor     (FoArea             *area,
				  FoArea             *descendant);
guint   fo_area_depth            (FoArea             *area);
FoArea* fo_area_append           (FoArea             *parent,
                                  FoArea             *area);
void    fo_area_traverse         (FoArea 	     *root,
				  GTraverseType       order,
				  GTraverseFlags      flags,
				  gint                max_depth,
				  FoAreaTraverseFunc  func,
				  gpointer            data);
guint   fo_area_max_height       (FoArea *root);
void    fo_area_children_foreach (FoArea 	    *area,
				  GTraverseFlags     flags,
				  FoAreaForeachFunc  func,
				  gpointer           data);
void    fo_area_reverse_children (FoArea            *area);
guint   fo_area_n_children       (FoArea            *area);
FoArea* fo_area_nth_child        (FoArea            *area,
				  guint              n);
FoArea* fo_area_last_child       (FoArea            *area);
guint   fo_area_child_position   (FoArea            *area,
				  FoArea            *child);
FoArea* fo_area_first_sibling    (FoArea            *area);
FoArea* fo_area_last_sibling     (FoArea            *area);
FoArea* fo_area_prev_sibling     (FoArea            *area);
FoArea* fo_area_next_sibling     (FoArea            *area);
FoArea* fo_area_first_child      (FoArea            *area);
FoArea* fo_area_parent           (FoArea            *area);
void    fo_area_unlink           (FoArea            *area);
void    fo_area_unlink_with_next_siblings (FoArea *area);
FoArea* fo_area_insert_with_next_siblings (FoArea *parent,
					   gint    position,
					   FoArea *area);


G_END_DECLS

#endif /* !__FO_AREA_H__ */
