/* Fo
 * fo-area-table.c: Area object for 'table' formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table.c,v 1.7 2005/11/20 13:41:55 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-reference.h"
#include "fo-area-reference-private.h"
#include "fo-area-table.h"
#include "fo-area-table-private.h"
#include "fo-area-table-continuation.h"
#include "fo-area-table-header.h"
#include "fo-block-fo.h"
#include "fo-table.h"
#include "fo-property-block-progression-dimension.h"
#include "fo-property-inline-progression-dimension.h"
#include "fo-property-keep-with-next.h"
#include "fo-property-keep-with-previous.h"
#include "fo-property-keep-with-next-within-column.h"
#include "fo-property-keep-with-next-within-page.h"
#include "fo-property-keep-with-previous-within-column.h"
#include "fo-property-keep-with-previous-within-page.h"

static void fo_area_table_class_init  (FoAreaTableClass *klass);
static void fo_area_table_finalize    (GObject           *object);

static void fo_area_table_debug_dump_properties (FoArea *area,
							      gint depth);
static FoArea* fo_area_table_size_request (FoArea *child);
static FoArea* fo_area_table_split_before_height (FoArea *area,
						  gfloat max_height);
static gboolean fo_area_table_split_before_height_check (FoArea *area,
							 gfloat max_height);
static void fo_area_table_size_adjust (FoArea *area,
				       gpointer data);
static void fo_area_table_set_or_split (FoArea *area,
					gpointer data);
static FoArea* fo_area_table_clone (FoArea *original);
static void fo_area_table_update_after_clone (FoArea *clone,
					      FoArea *original);

static gpointer parent_class;

/**
 * fo_area_table_get_type:
 * @void: 
 * 
 * Register the FoAreaTable object type.
 * 
 * Return value: GType value of the FoAreaTable object type.
 **/
GType
fo_area_table_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaTableClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_table_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaTable),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_REFERENCE,
                                            "FoAreaTable",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_area_table_class_init (FoAreaTableClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_table_finalize;

  FO_AREA_CLASS (klass)->debug_dump_properties = fo_area_table_debug_dump_properties;
  FO_AREA_CLASS (klass)->size_request = fo_area_table_size_request;
  FO_AREA_CLASS (klass)->split_before_height = fo_area_table_split_before_height;
  FO_AREA_CLASS (klass)->split_before_height_check = fo_area_table_split_before_height_check;
  FO_AREA_CLASS (klass)->clone = fo_area_table_clone;
  FO_AREA_CLASS (klass)->update_after_clone = 
    fo_area_table_update_after_clone;
}

static void
fo_area_table_finalize (GObject *object)
{
  FoAreaTable *fo_area_table;

  fo_area_table = FO_AREA_TABLE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_table_new:
 * 
 * Creates a new #FoAreaTable initialized to default value.
 * 
 * Return value: the new #FoAreaTable
 **/
FoArea*
fo_area_table_new (void)
{
  return FO_AREA (g_object_new (fo_area_table_get_type (), NULL));
}


/**
 * fo_area_table_debug_dump_properties:
 * @area:  The #FoArea object
 * @depth: Indent level to add to the output
 * 
 * Logs the value of each significant property of @area then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_area_table_debug_dump_properties (FoArea *area,
					  gint depth)
{
  FoAreaTable *table;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_TABLE (area));

  table = FO_AREA_TABLE (area);

  g_free (indent);
  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

FoArea*
fo_area_table_get_header (FoArea *table)
{
  g_return_val_if_fail (table != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_TABLE (table), NULL);

  return FO_AREA (fo_node_get_child_by_type (FO_NODE (table),
					     FO_TYPE_AREA_TABLE_HEADER));
}

/**
 * fo_area_table_size_adjust:
 * @area: #FoArea node to be placed within parent
 * @data: Not used
 * 
 * Place @area within its parent and adjust the parent's next-x and
 * next-y properties accordingly.
 **/
void
fo_area_table_size_adjust (FoArea *area,
			   gpointer data)
{
  FoArea *table;

  g_return_if_fail (FO_IS_AREA (area));
  g_return_if_fail (FO_IS_AREA_TABLE (fo_area_parent (area)));

  table = fo_area_parent (area);

  fo_area_area_set_x (area,
		      fo_area_get_next_x (table) +
		      fo_area_area_get_start_indent (area));
  fo_area_area_set_y (area,
		      fo_area_get_next_y (table) -
		      fo_area_area_get_space_before (area));
  fo_area_set_next_x (table,
		      fo_area_area_get_border_before (table) +
		      fo_area_area_get_padding_before (table));
  fo_area_set_next_y (table,
		      fo_area_get_next_y (table) -
		      fo_area_area_get_height (area));
  fo_area_set_available_height (area,
				fo_area_area_get_height (area));
  fo_area_set_available_width (area,
			       fo_area_get_child_available_ipdim (table));
}

/**
 * fo_area_table_set_or_split:
 * @area: #FoArea to be either placed within the parent area or split
 *        into two areas
 * @data: Not used
 * 
 * 
 **/
void
fo_area_table_set_or_split (FoArea *area,
			    gpointer data)
{
  FoArea *table;
  gfloat table_child_available_bpdim;

  g_return_if_fail (FO_IS_AREA (area));
  g_return_if_fail (FO_IS_AREA_TABLE (fo_area_parent (area)));

  table = fo_area_parent (area);
  table_child_available_bpdim = fo_area_get_child_available_bpdim (table);

  if ((table_child_available_bpdim -
       (fo_area_get_next_y (table) -
	fo_area_area_get_height (area))) >= 0)
    {
      fo_area_area_set_x (area,
			  fo_area_get_next_x (table) +
			  fo_area_area_get_start_indent (area));
      fo_area_area_set_y (area,
			  fo_area_get_next_y (table));
      fo_area_set_next_x (table,
			  fo_area_area_get_border_before (table) +
			  fo_area_area_get_padding_before (table));
      fo_area_set_next_y (table,
			  fo_area_get_next_y (table) -
			  fo_area_area_get_height (area));
      fo_area_set_available_height (area,
				    fo_area_area_get_height (area));
      fo_area_set_available_width (area,
				   fo_area_get_child_available_ipdim (table));
    }
  else
    {
#if defined(LIBFO_DEBUG) && 1
      g_message ("table_set_or_split:: splitting:: child: %s; generated by: %s",
		 fo_object_debug_sprintf (area) ,
		 fo_object_debug_sprintf (area->generated_by));
#endif
      area = fo_area_split_before_height (area,
					  table_child_available_bpdim -
					  fo_area_area_get_height (table));
      table = fo_area_parent (area);
      table_child_available_bpdim = fo_area_get_child_available_bpdim (table);
    }
}

/**
 * fo_area_table_size_request:
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
fo_area_table_size_request (FoArea *child)
{
  FoArea *table;
  FoArea *return_child;
  FoArea *child_original_next_part;
  FoDatatype *fo_bpdim;
  gfloat table_child_available_bpdim;
  gfloat table_use_height = 0.0;
  gfloat table_target_height = 0.0;
  gfloat child_height;
  gfloat total_child_height = 0.0;

  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (child), NULL);
  g_return_val_if_fail (!FO_AREA_IS_ROOT (child), NULL);
  g_return_val_if_fail (fo_area_parent (child) != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_TABLE (fo_area_parent (child)), NULL);

  child_original_next_part = child->next_part;

  child_height = fo_area_area_get_height (child);

  table = fo_area_parent (child);
  table_child_available_bpdim =
    fo_area_get_child_available_bpdim (table);

  fo_area_children_foreach (table,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    &total_child_height);

  table_target_height = total_child_height +
    fo_area_area_get_border_before (table) +
    fo_area_area_get_padding_before (table) +
    fo_area_area_get_padding_after (table) +
    fo_area_area_get_border_after (table);

  fo_bpdim =
    fo_property_get_value (fo_table_get_block_progression_dimension (table->generated_by));

  if (FO_IS_LENGTH_RANGE (fo_bpdim))
    {
      FoDatatype *min_datatype = fo_length_range_get_minimum (fo_bpdim);
      FoDatatype *opt_datatype = fo_length_range_get_optimum (fo_bpdim);
      FoDatatype *max_datatype = fo_length_range_get_maximum (fo_bpdim);

      if (FO_IS_LENGTH (min_datatype) &&
	  table_target_height <= fo_length_get_value (min_datatype))
	{
	  table_use_height = fo_length_get_value (min_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_size_request:: target: %g; min: %g",
		     table_target_height,
		     fo_length_get_value (min_datatype));
#endif
	}
      else if (FO_IS_LENGTH (opt_datatype) &&
	       table_target_height < fo_length_get_value (opt_datatype))
	{
	  table_use_height = fo_length_get_value (opt_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_size_request:: target: %g; opt: %g",
		     table_target_height,
		     fo_length_get_value (opt_datatype));
#endif
	}
      else if (FO_IS_LENGTH (max_datatype) &&
	       fo_length_get_value (max_datatype) < table_target_height)
	{
	  table_use_height = fo_length_get_value (max_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_size_request:: target: %g; max: %g",
		     table_target_height,
		     fo_length_get_value (max_datatype));
#endif
	}
      else
	{
	  table_use_height = table_target_height;
	}
    }
  else
    {
      g_assert_not_reached ();
    }

  if (table_child_available_bpdim < table_use_height)
    {
      fo_area_area_set_height (table, table_use_height);
      table = fo_area_size_request (table);
      /*
      table_child_available_ipdim =
	MAX (fo_area_get_available_width (table) -
	     fo_area_area_get_border_start (table) -
	     fo_area_area_get_padding_start (table) -
	     fo_area_area_get_padding_end (table) -
	     fo_area_area_get_border_end (table),
	     0);
      fo_area_set_child_available_ipdim (table,
					 table_child_available_ipdim);
      */
      table_child_available_bpdim =
	MAX (fo_area_get_available_height (table) -
	     fo_area_area_get_border_before (table) -
	     fo_area_area_get_padding_before (table) -
	     fo_area_area_get_padding_after (table) -
	     fo_area_area_get_border_after (table),
	     0);
      fo_area_set_child_available_bpdim (table,
					 table_child_available_bpdim);
    }

  total_child_height = 0;
  fo_area_children_foreach (table,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    &total_child_height);

  table_target_height =
    total_child_height +
    fo_area_area_get_border_before (table) +
    fo_area_area_get_padding_before (table) +
    fo_area_area_get_padding_after (table) +
    fo_area_area_get_border_after (table);

  fo_area_set_next_x (table,
		      fo_area_area_get_border_start (table) +
		      fo_area_area_get_padding_start (table));
  fo_area_set_next_y (table,
		      - (fo_area_area_get_border_before (table) +
			 fo_area_area_get_padding_before (table)));

  if (table_target_height <= table_child_available_bpdim)
    {
      fo_area_children_foreach (table,
				G_TRAVERSE_ALL,
				&fo_area_table_size_adjust,
				NULL);

      return_child = child;

      while ((return_child->next_part != NULL) &&
	     (return_child->next_part != child_original_next_part))
	{
	  return_child = return_child->next_part;
	}

      return return_child;
    }
  else
    {
      fo_area_children_foreach (table,
				G_TRAVERSE_ALL,
				&fo_area_table_set_or_split,
				NULL);
#if defined(LIBFO_DEBUG) && 0
      g_message ("table_size_request (%p):: total > available:: return:: table->last: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_last_child (table),
		 fo_object_debug_sprintf (fo_area_last_child (table)->generated_by);
#endif
      return_child = child;

      while ((return_child->next_part != NULL) &&
	     (return_child->next_part != child_original_next_part))
	{
	  return_child = return_child->next_part;
	}

      return return_child;
      /*
      return fo_area_last_child (table);
      */
    }
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
FoArea*
fo_area_table_split_before_height (FoArea *area,
				   gfloat max_height)
{
  FoArea *use_child_area;
  gfloat minus_child_y = 0.0;
  gfloat child_height = 0.0;

  g_return_val_if_fail (FO_IS_AREA_TABLE (area), NULL);
  g_return_val_if_fail (fo_area_n_children (area) > 0, NULL);
  g_return_val_if_fail (fo_area_n_children (area) <= 3, NULL);
  g_return_val_if_fail (max_height > 0, NULL);

  /* if the current area is less than max height, then no new area */
  if (fo_area_area_get_height (area) < max_height)
    return NULL;

  use_child_area = fo_area_first_child (area);

  while (use_child_area)
    {
      minus_child_y = -fo_area_area_get_y (use_child_area);
      child_height = fo_area_area_get_height (use_child_area);

      if (minus_child_y + child_height >= max_height)
	break;
      else
       use_child_area = fo_area_next_sibling (use_child_area);
    }

#if defined(LIBFO_DEBUG) && 1
  g_message ("table_split_before_height:: splitting: area: %s; generated by: %s; y: %f; height: %f",
	     fo_object_debug_sprintf (use_child_area),
	     fo_object_debug_sprintf (fo_area_get_generated_by (use_child_area)),
	     fo_area_area_get_y (use_child_area),
	     fo_area_area_get_height (use_child_area));
#endif

  if (use_child_area == NULL)
    return NULL;

  if (minus_child_y >= max_height)
    {
      /* max_height falls before use_child_area, i.e. in space between areas */

      if (use_child_area == fo_area_first_child (area))
	{
	  return NULL;
	}
      else
	{
	  FoFo *child_fo =
	    fo_area_get_generated_by (use_child_area);
	  FoDatatype *child_kwpwp_datatype =
	    fo_keep_get_within_page (fo_property_get_value (fo_block_fo_get_keep_with_previous (child_fo)));
	  FoDatatype *child_kwpwc_datatype =
	    fo_keep_get_within_column (fo_property_get_value (fo_block_fo_get_keep_with_previous (child_fo)));

	  FoFo *prev_child_fo =
	    fo_area_get_generated_by (fo_area_prev_sibling (use_child_area));
	  FoDatatype *prev_child_kwnwp_datatype =
	    fo_keep_get_within_page (fo_property_get_value (fo_block_fo_get_keep_with_next (prev_child_fo)));
	  FoDatatype *prev_child_kwnwc_datatype =
	    fo_keep_get_within_column (fo_property_get_value (fo_block_fo_get_keep_with_next (prev_child_fo)));

	  /* FIXME: Need to handle integer keeps */
	  if ((FO_IS_ENUM (prev_child_kwnwp_datatype) &&
	       fo_enum_get_value (prev_child_kwnwp_datatype) == FO_ENUM_ENUM_AUTO) &&
	      (FO_IS_ENUM (prev_child_kwnwc_datatype) &&
	       fo_enum_get_value (prev_child_kwnwc_datatype) == FO_ENUM_ENUM_AUTO)  &&
	      (FO_IS_ENUM (child_kwpwp_datatype) &&
	       fo_enum_get_value (child_kwpwp_datatype) == FO_ENUM_ENUM_AUTO) &&
	      (FO_IS_ENUM (child_kwpwc_datatype) &&
	       fo_enum_get_value (child_kwpwc_datatype) == FO_ENUM_ENUM_AUTO))
	    {
	      /* If got to here, all relevant keeps are 'auto' */
	      FoArea *clone = fo_area_clone (area);

	      fo_area_unlink_with_next_siblings (use_child_area);
	      fo_area_insert_with_next_siblings (clone,
						 0,
						 use_child_area);

	      return clone;
	    }
	  else
	    {
	      gfloat minus_prev_y =
		fo_area_area_get_y (fo_area_prev_sibling (use_child_area));
	      gfloat prev_height =
		fo_area_area_get_height (fo_area_prev_sibling (use_child_area));
	      /* If can't split between use_child_area and previous, maybe
		 can split at lower height */
	      return fo_area_table_split_before_height (area,
							     minus_prev_y +
							     prev_height);
	    }
	}
    }
  else
    {
      /* max_height falls within use_child_area */
      gboolean child_can_split = fo_area_split_before_height_check (use_child_area,
								    max_height -
								    minus_child_y);

      if (child_can_split)
	{
	  FoArea *clone = fo_area_clone (area);
	  FoArea *split_child = fo_area_split_before_height (use_child_area,
							     max_height -
							     minus_child_y);
	  fo_area_unlink_with_next_siblings (split_child);
	  fo_area_insert_with_next_siblings (clone,
					     0,
					     split_child);

	  return clone;
	}
      else
	{
	  /* If can't split use_child_area, maybe
	     can split at lower height */
	  return fo_area_table_split_before_height (area,
							 minus_child_y);
	}
    }
}

/* return %TRUE if the area will split within the height */
gboolean
fo_area_table_split_before_height_check (FoArea *area,
					 gfloat max_height)
{
  FoArea *use_child_area;
  gfloat minus_child_y = 0.0;
  gfloat child_height = 0.0;

  g_return_val_if_fail (FO_IS_AREA_TABLE (area), FALSE);
  g_return_val_if_fail (fo_area_n_children (area) > 0, FALSE);
  g_return_val_if_fail (max_height > 0, FALSE);

  /* if the current area is less than max height, then no new area */
  if (fo_area_area_get_height (area) < max_height)
    return FALSE;

  use_child_area = fo_area_first_child (area);

  while (use_child_area)
    {
      minus_child_y = -fo_area_area_get_y (use_child_area);
      child_height = fo_area_area_get_height (use_child_area);

      if (minus_child_y + child_height >= max_height)
	break;
      else
	use_child_area = fo_area_next_sibling (use_child_area);
    }

#if defined(LIBFO_DEBUG) && 1
  g_message ("table_split_before_height_check:: splitting: area: %s; generated by: %s; y: %f; height: %f",
	     fo_object_debug_sprintf (use_child_area),
	     fo_object_debug_sprintf (fo_area_get_generated_by (use_child_area)),
	     fo_area_area_get_y (use_child_area),
	     fo_area_area_get_height (use_child_area));
#endif

  if (use_child_area == NULL)
    return FALSE;

  if (minus_child_y >= max_height)
    {
      /* max_height falls before use_child_area, i.e. in space between areas */

      if (use_child_area == fo_area_first_child (area))
	{
	  return FALSE;
	}
      else
	{
	  FoFo *child_fo =
	    fo_area_get_generated_by (use_child_area);
	  FoDatatype *child_kwp_wp_datatype =
	    fo_keep_get_within_page (fo_property_get_value (fo_block_fo_get_keep_with_previous (child_fo)));
	  FoDatatype *child_kwp_wc_datatype =
	    fo_keep_get_within_column (fo_property_get_value (fo_block_fo_get_keep_with_previous (child_fo)));

	  FoFo *prev_child_fo =
	    fo_area_get_generated_by (fo_area_prev_sibling (use_child_area));
	  FoDatatype *prev_child_kwn_wp_datatype =
	    fo_keep_get_within_page (fo_property_get_value (fo_block_fo_get_keep_with_next (prev_child_fo)));
	  FoDatatype *prev_child_kwn_wc_datatype =
	    fo_keep_get_within_column (fo_property_get_value (fo_block_fo_get_keep_with_next (prev_child_fo)));

	  /* FIXME: Need to handle integer keeps */
	  if ((FO_IS_ENUM (prev_child_kwn_wp_datatype) &&
	       fo_enum_get_value (prev_child_kwn_wp_datatype) == FO_ENUM_ENUM_AUTO) &&
	      (FO_IS_ENUM (prev_child_kwn_wc_datatype) &&
	       fo_enum_get_value (prev_child_kwn_wc_datatype) == FO_ENUM_ENUM_AUTO)  &&
	      (FO_IS_ENUM (child_kwp_wp_datatype) &&
	       fo_enum_get_value (child_kwp_wp_datatype) == FO_ENUM_ENUM_AUTO) &&
	      (FO_IS_ENUM (child_kwp_wc_datatype) &&
	       fo_enum_get_value (child_kwp_wc_datatype) == FO_ENUM_ENUM_AUTO))
	    {
	      /* If got to here, all relevant keeps are 'auto' */
	      return TRUE;
	    }
	  else
	    {
	      gfloat minus_prev_y =
		fo_area_area_get_y (fo_area_prev_sibling (use_child_area));
	      gfloat prev_height =
		fo_area_area_get_height (fo_area_prev_sibling (use_child_area));
	      /* If can't split between use_child_area and previous, maybe
		 can split at lower height */
	      return fo_area_table_split_before_height_check (area,
							      minus_prev_y +
							      prev_height);
	    }
	}
    }
  else
    {
      /* max_height falls within use_child_area */
      gboolean child_can_split = fo_area_split_before_height_check (use_child_area,
								    max_height -
								    minus_child_y);

      if (child_can_split)
	{
	  return TRUE;
	}
      else
	{
	  /* If can't split use_child_area, maybe
	     can split at lower height */
	  return fo_area_table_split_before_height_check (area,
							  minus_child_y);
	}
    }
}

/**
 * fo_area_table_clone:
 * @original: Area object to be cloned
 * 
 * Make a clone of @original and insert the clone after @original in
 * the area tree.  Set instance properties of the clone to match
 * @original.
 * 
 * Return value: Clone of @original
 **/
FoArea*
fo_area_table_clone (FoArea *original)
{
  FoArea *clone;

  g_return_val_if_fail (original != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA (original), NULL);

  clone = FO_AREA (g_object_new (FO_TYPE_AREA_TABLE_CONTINUATION, NULL));

  fo_area_update_after_clone (clone, original);

  return clone;
}

/**
 * fo_area_table_update_after_clone:
 * @clone:    New object cloned from @original
 * @original: Original area object
 * 
 * Update the FoAreaTable-specific instance variables of @clone to
 * match those of @original
 **/
void
fo_area_table_update_after_clone (FoArea *clone,
				  FoArea *original)
{
  FO_AREA_CLASS (parent_class)->update_after_clone (clone, original);

  fo_area_set_child_available_ipdim (clone,
				     fo_area_get_child_available_ipdim (original));
  fo_area_area_set_width (clone,
			  fo_area_area_get_width (original));

}
