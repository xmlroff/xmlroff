/* Fo
 * fo-area-list-item.c: Area object for list-item formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area.h"
#include "fo-area-area.h"
#include "fo-area-area-private.h"
#include "fo-area-list-item.h"

struct _FoAreaListItem
{
  FoAreaArea parent_instance;
};

struct _FoAreaListItemClass
{
  FoAreaAreaClass parent_class;
};

static void fo_area_list_item_class_init  (FoAreaListItemClass *klass);
static void fo_area_list_item_finalize    (GObject           *object);

static void fo_area_list_item_debug_dump_properties (FoArea *area,
							      gint depth);
static FoArea* fo_area_list_item_size_request (FoArea *child);
static FoArea* fo_area_list_item_split_before_height (FoArea *area,
						      gdouble max_height);
static gboolean fo_area_list_item_split_before_height_check (FoArea *area,
							     gdouble max_height);
static FoArea* fo_area_list_item_split_after_height (FoArea *area,
						     gdouble max_height);
static gboolean fo_area_list_item_split_after_height_check (FoArea *area,
							    gdouble max_height);

static gpointer parent_class;

GType
fo_area_list_item_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaListItemClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_list_item_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaListItem),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_AREA,
                                            "FoAreaListItem",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_area_list_item_class_init (FoAreaListItemClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_list_item_finalize;

  FO_AREA_CLASS (klass)->debug_dump_properties = fo_area_list_item_debug_dump_properties;
  FO_AREA_CLASS (klass)->size_request = fo_area_list_item_size_request;
  FO_AREA_CLASS (klass)->split_before_height = fo_area_list_item_split_before_height;
  FO_AREA_CLASS (klass)->split_before_height_check = fo_area_list_item_split_before_height_check;
  FO_AREA_CLASS (klass)->split_after_height = fo_area_list_item_split_after_height;
  FO_AREA_CLASS (klass)->split_after_height_check = fo_area_list_item_split_after_height_check;

}

static void
fo_area_list_item_finalize (GObject *object)
{
  FoAreaListItem *fo_area_list_item;

  fo_area_list_item = FO_AREA_LIST_ITEM (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_list_item_new:
 * 
 * Creates a new #FoAreaListItem initialized to default value.
 * 
 * Return value: the new #FoAreaListItem
 **/
FoArea*
fo_area_list_item_new (void)
{
  return FO_AREA (g_object_new (fo_area_list_item_get_type (), NULL));
}


void
fo_area_list_item_debug_dump_properties (FoArea *area, gint depth)
{
  FoAreaListItem *list_item;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_LIST_ITEM (area));

  list_item = FO_AREA_LIST_ITEM (area);

  g_free (indent);
  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

FoArea*
fo_area_list_item_add_child (FoArea *parent, FoArea *child)
{
  g_return_val_if_fail (parent != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_LIST_ITEM (parent), NULL);
  g_return_val_if_fail (child != NULL, NULL);

  g_return_val_if_fail (fo_area_n_children (parent) <= 1, NULL);

  return fo_area_real_add_child (parent, child);
}

/**
 * fo_area_list_item_size_request:
 * @child: Child area
 * 
 * Check that the parent area of @child has sufficient space for
 * @child.  If not enough space, request that the parent has
 * sufficient space allocated for it, then adjust @child and its
 * siblings as necessary to fit into the resized parent area.
 * 
 * Return value: Pointer to the last area generated from @child after
 * any reallocation and resizing
 **/
FoArea*
fo_area_list_item_size_request (FoArea *child)
{
  FoArea *use_child_area;
  FoArea *list_item;
  gdouble max_child_height = 0;
  gdouble list_item_child_available_bpdim;
  gdouble child_height;
  gdouble child_space_before, child_space_after;

  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (child), NULL);
  g_return_val_if_fail (!FO_AREA_IS_ROOT (child), NULL);
  g_return_val_if_fail (fo_area_parent (child) != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_LIST_ITEM (fo_area_parent (child)), NULL);

  child_height = fo_area_area_get_height (child);
  child_space_before = fo_area_area_get_space_before (child);
  child_space_after = fo_area_area_get_space_after (child);

  list_item = fo_area_parent (child);
  list_item_child_available_bpdim = fo_area_get_child_available_bpdim (list_item);

#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_size_request (%p):: list_item: %s; generated by: %s; available_height: %f",
	     child,
	     fo_object_debug_sprintf (list_item),
	     fo_object_debug_sprintf (list_item->generated_by),
	     list_item_child_available_bpdim);
  g_message ("list_item_size_request (%p):: child: %s; generated by: %s; height: %f; space_before: %f; space_after: %f",
	     child,
	     fo_object_debug_sprintf (child),
	     fo_object_debug_sprintf (child->generated_by),
	     child_height,
	     child_space_before,
	     child_space_after);
#endif

  use_child_area = fo_area_first_child (list_item);

  while (use_child_area)
    {
#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_size_request (%p):: height: %f; child: %s; generated by: %s",
		 child,
		 fo_area_area_get_height (use_child_area),
		 fo_object_debug_sprintf (use_child_area),
		 fo_object_debug_sprintf (use_child_area->generated_by));
#endif
      max_child_height = MAX (max_child_height,
			      fo_area_area_get_height (use_child_area));

      use_child_area = fo_area_next_sibling (use_child_area);
    }

#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_size_request (%p):: max child height: %f",
	     child,
	     max_child_height);
#endif

  fo_area_area_set_height (list_item,
			   max_child_height +
			   fo_area_area_get_border_before (list_item) +
			   fo_area_area_get_padding_before (list_item) +
			   fo_area_area_get_padding_after (list_item) +
			   fo_area_area_get_border_after (list_item));

  /* Don't bother doing a size_request if still fit within
     available height */
  if (list_item_child_available_bpdim < fo_area_area_get_height (list_item))
    {
      list_item = fo_area_size_request (list_item);
      list_item_child_available_bpdim =
	MAX (fo_area_get_available_height (list_item) -
	     fo_area_area_get_border_before (list_item) -
	     fo_area_area_get_padding_before (list_item) -
	     fo_area_area_get_padding_after (list_item) -
	     fo_area_area_get_border_after (list_item),
	     0);
      fo_area_set_child_available_bpdim (list_item,
					 list_item_child_available_bpdim);
#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_size_request (%p):: new list_item: %s; generated by: %s; available_height: %f",
		 child,
		 fo_object_debug_sprintf (list_item),
		 fo_object_debug_sprintf (list_item->generated_by),
		 list_item_child_available_bpdim);
#endif
    }

  max_child_height = 0;
  use_child_area = fo_area_first_child (list_item);

  while (use_child_area)
    {
      max_child_height = MAX (max_child_height,
			      fo_area_area_get_height (use_child_area));

#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_size_request (%p):: new height: %f; child: %s; generated by: %s",
		 child,
		 fo_area_area_get_height (use_child_area),
		 fo_object_debug_sprintf (use_child_area),
		 fo_object_debug_sprintf (use_child_area->generated_by));
#endif

      use_child_area = fo_area_next_sibling (use_child_area);
    }

#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_size_request (%p):: new max child height: %f",
	     child,
	     max_child_height);
#endif
  fo_area_set_next_x (list_item,
		      fo_area_area_get_border_start (list_item) +
		      fo_area_area_get_padding_start (list_item));
  fo_area_set_next_y (list_item,
		      - (fo_area_area_get_border_before (list_item) +
			 fo_area_area_get_padding_before (list_item)));

  if (max_child_height <= list_item_child_available_bpdim)
    {
      use_child_area = fo_area_first_child (list_item);

      while (use_child_area)
	{
	  fo_area_area_set_x (use_child_area,
			      fo_area_get_next_x (list_item) +
			      fo_area_area_get_start_indent (use_child_area));
	  fo_area_area_set_y (use_child_area,
			      fo_area_get_next_y (list_item));
	  fo_area_set_available_height (use_child_area,
					fo_area_area_get_height (use_child_area));
	  fo_area_set_available_width (use_child_area,
				       fo_area_get_child_available_ipdim (list_item));

	  use_child_area = fo_area_next_sibling (use_child_area);
	}

#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_size_request (%p):: return:: list_item->last: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_last_child (list_item)),
		 fo_object_debug_sprintf (fo_area_last_child (list_item->generated_by)));
#endif
      return fo_area_last_child (list_item);
    }
  else
    {
      use_child_area = fo_area_first_child (list_item);

      while (use_child_area)
	{
	  if ((list_item_child_available_bpdim -
	       (fo_area_get_next_y (list_item) -
		fo_area_area_get_height (use_child_area))) >= 0)
	    {
	      fo_area_area_set_x (use_child_area,
				  fo_area_get_next_x (list_item) +
				  fo_area_area_get_start_indent (use_child_area));
	      fo_area_area_set_y (use_child_area,
				  fo_area_get_next_y (list_item));
	      fo_area_set_next_x (list_item, 0);
	      fo_area_set_next_y (list_item,
				  fo_area_get_next_y (list_item) -
				  fo_area_area_get_height (use_child_area));
	      fo_area_set_available_height (child,
					    fo_area_area_get_height (use_child_area));
	      fo_area_set_available_width (child,
					   fo_area_get_child_available_ipdim (list_item));

	      use_child_area = fo_area_next_sibling (use_child_area);
	    }
	  else
	    {
#if defined(LIBFO_DEBUG) && 0
	      g_message ("list_item_size_request:: splitting:: child: %s; generated by: %s",
			 fo_object_debug_sprintf (use_child_area),
			 fo_object_debug_sprintf (use_child_area->generated_by));
#endif
	      use_child_area = fo_area_split_before_height (use_child_area,
							    list_item_child_available_bpdim -
							    fo_area_area_get_height (list_item));
	      list_item = fo_area_parent (use_child_area);
	      list_item_child_available_bpdim = fo_area_get_child_available_bpdim (list_item);
	    }
	}

#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_size_request (%p):: max > available:: return:: list_item->last: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_last_child (list_item)),
		 fo_object_debug_sprintf (fo_area_last_child (list_item->generated_by)));
#endif
      return fo_area_last_child (list_item);
    }
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
FoArea*
fo_area_list_item_split_before_height (FoArea *area,
				       gdouble max_height)
{
  FoAreaArea *area_area;
  FoArea *clone = NULL;
  FoArea *child_0 = NULL;
  FoArea *split_child_0 = NULL;
  gdouble  child_0_height = 0;
  gdouble  child_0_minus_y = 0;
  gboolean child_0_will_split = FALSE;
  gboolean child_0_will_fit = TRUE;
  FoArea *child_1 = NULL;
  FoArea *split_child_1 = NULL;
  gdouble  child_1_height = 0;
  gdouble  child_1_minus_y = 0;
  gboolean child_1_will_split = FALSE;
  gboolean child_1_will_fit = TRUE;

  g_return_val_if_fail (FO_IS_AREA_LIST_ITEM (area), NULL);
  g_return_val_if_fail (fo_area_n_children (area) > 0, NULL);
  g_return_val_if_fail (fo_area_n_children (area) <= 2, NULL);
  g_return_val_if_fail (max_height > 0, NULL);

#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_split_before_height:: area: %s; generated by: %s; max_height: %f",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (area->generated_by),
	     max_height);
#endif
#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_split_before_height:: area: %s; parent: %s",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (fo_area_parent (area)));
#endif

  area_area = (FoAreaArea *) area;
  /* if the current area is less than max height, then no new area */
  if (fo_area_area_get_height (area) < max_height)
    return NULL;

  child_0 = fo_area_first_child (area);
  child_0_height = fo_area_area_get_height (child_0);
  child_0_minus_y = -fo_area_area_get_y (child_0);
  if (child_0_minus_y + child_0_height > max_height)
    {
      child_0_will_split = fo_area_split_before_height_check (child_0,
							      max_height -
							      child_0_minus_y);
      child_0_will_fit = FALSE;
    }

  child_1 = fo_area_nth_child (area, 1);
  if (child_1)
    {
      child_1_height = fo_area_area_get_height (child_1);
      child_1_minus_y = -fo_area_area_get_y (child_1);
      if (child_1_minus_y + child_1_height > max_height)
	{
	  child_1_will_split =
	    fo_area_split_before_height_check (child_1,
					       max_height -
					       child_1_minus_y);
	  child_1_will_fit = FALSE;
	}
    }

#if defined(LIBFO_DEBUG) && 0
  if (child_0_will_fit)
    {
      g_message ("list_item_split_before_height (%p):: child 0 will fit",
		 area);
    }
  else
    {
      if (child_0_will_split)
	{
	  g_message ("list_item_split_before_height (%p):: child 0 will split",
		     area);
	}
      else
	{
	  g_message ("list_item_split_before_height (%p):: child 0 will not split",
		     area);
	}
    }
  if (child_1)
    {
      if (child_1_will_fit)
	{
	  g_message ("list_item_split_before_height (%p):: child 1 will fit",
		     area);
	}
      else
	{
	  if (child_1_will_split)
	    {
	      g_message ("list_item_split_before_height (%p):: child 1 will split",
			 area);
	    }
	  else
	    {
	      g_message ("list_item_split_before_height (%p):: child 1 will not split",
			 area);
	    }
	}
    }
  else
    {
      g_message ("list_item_split_before_height (%p):: no child 1",
		 area);
    }
#endif

  if ((child_0_will_split &&
       !(child_1 && !child_1_will_fit && !child_1_will_split)) ||
      (child_1 && child_1_will_split &&
       !(!child_0_will_fit && !child_0_will_split)))
    {
      gdouble max_remaining_child_height = 0;
      gdouble max_split_child_height = 0;

#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_split_before_height (%p):: will split list-item",
		 area);
#endif
      clone = fo_area_clone (area);

      area->is_last = FALSE;
      area_area->border_after = 0;

      clone->is_first = FALSE;
      ((FoAreaArea *)clone)->border_before = 0;

      /* Do child_1 first so since may or may not be a split child_0
	 put before it in the tree */
      if (child_1_will_split)
	{
	  split_child_1 = fo_area_split_before_height (child_1,
						       max_height -
						       child_1_minus_y);

	  fo_area_unlink_with_next_siblings (split_child_1);
	  fo_area_insert_with_next_siblings (clone, 0, split_child_1);

	  max_remaining_child_height = ((FoAreaArea *) child_1)->height;
	  max_split_child_height = ((FoAreaArea *) split_child_1)->height;
	}

      if (child_0_will_split)
	{
	  split_child_0 = fo_area_split_before_height (child_0,
						       max_height -
						       child_0_minus_y);

	  fo_area_unlink_with_next_siblings (split_child_0);
	  fo_area_insert_with_next_siblings (clone, 0, split_child_0);

	  max_remaining_child_height = MAX (max_remaining_child_height,
					    ((FoAreaArea *) child_0)->height);
	  max_split_child_height = MAX (max_split_child_height,
					((FoAreaArea *) split_child_0)->height);
	}

      /* Do not include area_area->border_after in height since
	 area_area is not last */
      area_area->height =
	max_remaining_child_height +
	area_area->border_before +
	area_area->padding_before +
	area_area->padding_after;

      /* Do not include clone->border_before in height since
	 clone is not first */
      ((FoAreaArea *) clone)->height =
	max_split_child_height +
	((FoAreaArea *) clone)->padding_before +
	((FoAreaArea *) clone)->padding_after +
	((FoAreaArea *) clone)->border_after;
	  
      fo_area_set_next_y (clone, max_split_child_height);
      fo_area_set_available_height (clone, 0);

      return clone;
    }
  else
    {
#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_split_before_height (%p):: won't split list-item",
		 area);
#endif
      return NULL;
    }
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
gboolean
fo_area_list_item_split_before_height_check (FoArea *area,
					     gdouble max_height)
{
  FoArea *child_0 = NULL;
  gdouble  child_0_height = 0;
  gdouble  child_0_minus_y = 0;
  gboolean child_0_will_split = FALSE;
  gboolean child_0_will_fit = TRUE;
  FoArea *child_1 = NULL;
  gdouble  child_1_height = 0;
  gdouble  child_1_minus_y = 0;
  gboolean child_1_will_split = FALSE;
  gboolean child_1_will_fit = TRUE;

  g_return_val_if_fail (FO_IS_AREA_LIST_ITEM (area), FALSE);
  g_return_val_if_fail (fo_area_n_children (area) > 0, FALSE);
  g_return_val_if_fail (fo_area_n_children (area) <= 2, FALSE);
  g_return_val_if_fail (max_height > 0, FALSE);

#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_split_before_height_check:: area: %s; generated by: %s; max_height: %f",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (area->generated_by),
	     max_height);
#endif

  /* if the current area is less than max height, then no new area */
  if (fo_area_area_get_height (area) < max_height)
    return FALSE;

  child_0 = fo_area_first_child (area);
  child_0_height = fo_area_area_get_height (child_0);
  child_0_minus_y = -fo_area_area_get_y (child_0);
  if (child_0_minus_y + child_0_height > max_height)
    {
      child_0_will_split = fo_area_split_before_height_check (child_0,
							      max_height -
							      child_0_minus_y);
      child_0_will_fit = FALSE;
    }

  child_1 = fo_area_nth_child (area, 1);
  if (child_1)
    {
      child_1_height = fo_area_area_get_height (child_1);
      child_1_minus_y = -fo_area_area_get_y (child_1);
      if (child_1_minus_y + child_1_height > max_height)
	{
	  child_1_will_split =
	    fo_area_split_before_height_check (child_1,
					       max_height -
					       child_1_minus_y);
	  child_1_will_fit = FALSE;
	}
    }

  if ((child_0_will_split &&
       !(child_1 && !child_1_will_fit && !child_1_will_split)) ||
      (child_1 && child_1_will_split &&
       !(!child_0_will_fit && !child_0_will_split)))
    {
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
FoArea*
fo_area_list_item_split_after_height (FoArea *area,
				      gdouble max_height)
{
  FoAreaArea *area_area;
  FoArea *clone = NULL;
  FoArea *child_0 = NULL;
  FoArea *split_child_0 = NULL;
  gdouble  child_0_height = 0;
  gdouble  child_0_minus_y = 0;
  gboolean child_0_will_split = FALSE;
  gboolean child_0_will_fit = TRUE;
  FoArea *child_1 = NULL;
  FoArea *split_child_1 = NULL;
  gdouble  child_1_height = 0;
  gdouble  child_1_minus_y = 0;
  gboolean child_1_will_split = FALSE;
  gboolean child_1_will_fit = TRUE;

  g_return_val_if_fail (FO_IS_AREA_LIST_ITEM (area), NULL);
  g_return_val_if_fail (fo_area_n_children (area) > 0, NULL);
  g_return_val_if_fail (fo_area_n_children (area) <= 2, NULL);
  g_return_val_if_fail (max_height > 0, NULL);

#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_split_before_height:: area: %s; generated by: %s; max_height: %f",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (area->generated_by),
	     max_height);
#endif
#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_split_before_height:: area: %s; parent: %s",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (fo_area_parent (area)));
#endif

  area_area = (FoAreaArea *) area;
  /* if the current area is less than max height, then no new area */
  if (fo_area_area_get_height (area) < max_height)
    return NULL;

  child_0 = fo_area_first_child (area);
  child_0_height = fo_area_area_get_height (child_0);
  child_0_minus_y = -fo_area_area_get_y (child_0);
  if (child_0_minus_y + child_0_height > max_height)
    {
      child_0_will_split = fo_area_split_before_height_check (child_0,
							      max_height -
							      child_0_minus_y);
      child_0_will_fit = FALSE;
    }

  child_1 = fo_area_nth_child (area, 1);
  if (child_1)
    {
      child_1_height = fo_area_area_get_height (child_1);
      child_1_minus_y = -fo_area_area_get_y (child_1);
      if (child_1_minus_y + child_1_height > max_height)
	{
	  child_1_will_split =
	    fo_area_split_before_height_check (child_1,
					       max_height -
					       child_1_minus_y);
	  child_1_will_fit = FALSE;
	}
    }

#if defined(LIBFO_DEBUG) && 0
  if (child_0_will_fit)
    {
      g_message ("list_item_split_before_height (%p):: child 0 will fit",
		 area);
    }
  else
    {
      if (child_0_will_split)
	{
	  g_message ("list_item_split_before_height (%p):: child 0 will split",
		     area);
	}
      else
	{
	  g_message ("list_item_split_before_height (%p):: child 0 will not split",
		     area);
	}
    }
  if (child_1)
    {
      if (child_1_will_fit)
	{
	  g_message ("list_item_split_before_height (%p):: child 1 will fit",
		     area);
	}
      else
	{
	  if (child_1_will_split)
	    {
	      g_message ("list_item_split_before_height (%p):: child 1 will split",
			 area);
	    }
	  else
	    {
	      g_message ("list_item_split_before_height (%p):: child 1 will not split",
			 area);
	    }
	}
    }
  else
    {
      g_message ("list_item_split_before_height (%p):: no child 1",
		 area);
    }
#endif

  if ((child_0_will_split &&
       !(child_1 && !child_1_will_fit && !child_1_will_split)) ||
      (child_1 && child_1_will_split &&
       !(!child_0_will_fit && !child_0_will_split)))
    {
      gdouble max_remaining_child_height = 0;
      gdouble max_split_child_height = 0;

#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_split_before_height (%p):: will split list-item",
		 area);
#endif
      clone = fo_area_clone (area);

      area->is_last = FALSE;
      area_area->border_after = 0;

      clone->is_first = FALSE;
      ((FoAreaArea *)clone)->border_before = 0;

      /* Do child_1 first so since may or may not be a split child_0
	 put before it in the tree */
      if (child_1_will_split)
	{
	  split_child_1 = fo_area_split_before_height (child_1,
						       max_height -
						       child_1_minus_y);

	  fo_area_unlink_with_next_siblings (split_child_1);
	  fo_area_insert_with_next_siblings (clone, 0, split_child_1);

	  max_remaining_child_height = ((FoAreaArea *) child_1)->height;
	  max_split_child_height = ((FoAreaArea *) split_child_1)->height;
	}

      if (child_0_will_split)
	{
	  split_child_0 = fo_area_split_before_height (child_0,
						       max_height -
						       child_0_minus_y);

	  fo_area_unlink_with_next_siblings (split_child_0);
	  fo_area_insert_with_next_siblings (clone, 0, split_child_0);

	  max_remaining_child_height = MAX (max_remaining_child_height,
					    ((FoAreaArea *) child_0)->height);
	  max_split_child_height = MAX (max_split_child_height,
					((FoAreaArea *) split_child_0)->height);
	}

      /* Do not include area_area->border_after in height since
	 area_area is not last */
      area_area->height =
	max_remaining_child_height +
	area_area->border_before +
	area_area->padding_before +
	area_area->padding_after;

      /* Do not include clone->border_before in height since
	 clone is not first */
      ((FoAreaArea *) clone)->height =
	max_split_child_height +
	((FoAreaArea *) clone)->padding_before +
	((FoAreaArea *) clone)->padding_after +
	((FoAreaArea *) clone)->border_after;
	  
      fo_area_set_next_y (clone, max_split_child_height);
      fo_area_set_available_height (clone, 0);

      return clone;
    }
  else
    {
#if defined(LIBFO_DEBUG) && 0
      g_message ("list_item_split_before_height (%p):: won't split list-item",
		 area);
#endif
      return NULL;
    }
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
gboolean
fo_area_list_item_split_after_height_check (FoArea *area,
					    gdouble max_height)
{
  FoArea *child_0 = NULL;
  gdouble  child_0_height = 0;
  gdouble  child_0_minus_y = 0;
  gboolean child_0_will_split = FALSE;
  gboolean child_0_will_fit = TRUE;
  FoArea *child_1 = NULL;
  gdouble  child_1_height = 0;
  gdouble  child_1_minus_y = 0;
  gboolean child_1_will_split = FALSE;
  gboolean child_1_will_fit = TRUE;

  g_return_val_if_fail (FO_IS_AREA_LIST_ITEM (area), FALSE);
  g_return_val_if_fail (fo_area_n_children (area) > 0, FALSE);
  g_return_val_if_fail (fo_area_n_children (area) <= 2, FALSE);
  g_return_val_if_fail (max_height > 0, FALSE);

#if defined(LIBFO_DEBUG) && 0
  g_message ("list_item_split_before_height_check:: area: %s; generated by: %s; max_height: %f",
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (area->generated_by),
	     max_height);
#endif

  /* if the current area is less than max height, then no new area */
  if (fo_area_area_get_height (area) < max_height)
    return FALSE;

  child_0 = fo_area_first_child (area);
  child_0_height = fo_area_area_get_height (child_0);
  child_0_minus_y = -fo_area_area_get_y (child_0);
  if (child_0_minus_y + child_0_height > max_height)
    {
      child_0_will_split = fo_area_split_before_height_check (child_0,
							      max_height -
							      child_0_minus_y);
      child_0_will_fit = FALSE;
    }

  child_1 = fo_area_nth_child (area, 1);
  if (child_1)
    {
      child_1_height = fo_area_area_get_height (child_1);
      child_1_minus_y = -fo_area_area_get_y (child_1);
      if (child_1_minus_y + child_1_height > max_height)
	{
	  child_1_will_split =
	    fo_area_split_before_height_check (child_1,
					       max_height -
					       child_1_minus_y);
	  child_1_will_fit = FALSE;
	}
    }

  if ((child_0_will_split &&
       !(child_1 && !child_1_will_fit && !child_1_will_split)) ||
      (child_1 && child_1_will_split &&
       !(!child_0_will_fit && !child_0_will_split)))
    {
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}
