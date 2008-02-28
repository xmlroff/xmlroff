/* Fo
 * fo-area-spanning-table-cell.c: Area object for spanning-table-cell formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-reference.h"
#include "fo-area-reference-private.h"
#include "fo-area-table-cell.h"
#include "fo-area-spanning-table-cell.h"
#include "fo-area-spanning-table-cell-private.h"
#include "fo-area-table-cell-proxy.h"
#include "fo/fo-table-cell.h"
#include "fo/fo-block-fo.h"
#include "property/fo-property-block-progression-dimension.h"
#include "property/fo-property-inline-progression-dimension.h"
#include "property/fo-property-keep-with-next.h"
#include "property/fo-property-keep-with-previous.h"
#include "property/fo-property-keep-with-next-within-column.h"
#include "property/fo-property-keep-with-next-within-page.h"
#include "property/fo-property-keep-with-previous-within-column.h"
#include "property/fo-property-keep-with-previous-within-page.h"

static void fo_area_spanning_table_cell_class_init  (FoAreaSpanningTableCellClass *klass);
static void fo_area_spanning_table_cell_finalize    (GObject           *object);

static void fo_area_spanning_table_cell_debug_dump_properties (FoArea *area,
							      gint depth);
static FoArea* fo_area_spanning_table_cell_size_request (FoArea *child);
static FoArea* fo_area_spanning_table_cell_split_before_height (FoArea *area,
						      gfloat max_height);
static gboolean fo_area_spanning_table_cell_split_before_height_check (FoArea *area,
							     gfloat max_height);

static gpointer parent_class;

/**
 * fo_area_spanning_table_cell_get_type:
 * @void: 
 * 
 * Register the FoAreaSpanningTableCell object type.
 * 
 * Return value: GType value of the FoAreaSpanningTableCell object type.
 **/
GType
fo_area_spanning_table_cell_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaSpanningTableCellClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_spanning_table_cell_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaSpanningTableCell),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_REFERENCE,
                                            "FoAreaSpanningTableCell",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_area_spanning_table_cell_class_init (FoAreaSpanningTableCellClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_spanning_table_cell_finalize;

  FO_AREA_CLASS (klass)->debug_dump_properties = fo_area_spanning_table_cell_debug_dump_properties;
  FO_AREA_CLASS (klass)->size_request = fo_area_spanning_table_cell_size_request;
  FO_AREA_CLASS (klass)->split_before_height = fo_area_spanning_table_cell_split_before_height;
  FO_AREA_CLASS (klass)->split_before_height_check = fo_area_spanning_table_cell_split_before_height_check;
}

static void
fo_area_spanning_table_cell_finalize (GObject *object)
{
  FoAreaSpanningTableCell *fo_area_spanning_table_cell;

  fo_area_spanning_table_cell = FO_AREA_SPANNING_TABLE_CELL (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_spanning_table_cell_new:
 * 
 * Creates a new #FoAreaSpanningTableCell initialized to default value.
 * 
 * Return value: the new #FoAreaSpanningTableCell
 **/
FoArea*
fo_area_spanning_table_cell_new (void)
{
  return FO_AREA (g_object_new (fo_area_spanning_table_cell_get_type (), NULL));
}


static void
fo_area_spanning_table_cell_accumulate_proxy_available_height (gpointer value,
							       gpointer data)
{
  FoArea *proxy = FO_AREA (value);
  gfloat *total = (gfloat *) data;
  
  *total += fo_area_get_available_height (proxy);
}

#if 0
static void
fo_area_spanning_table_cell_debug_dump_proxy_height (gpointer value,
						     gpointer data)
{
  FoArea *proxy = FO_AREA (value);
  
  g_message ("proxy: %s; available_height: %f; height: %f",
	     fo_object_debug_sprintf (proxy),
	     fo_area_get_available_height (proxy),
	     fo_area_area_get_height (proxy));
}

static void
fo_area_spanning_table_cell_debug_dump_heights (FoArea *fo_area)
{
  g_message ("spanning_table_cell:: area: %s; available_height: %g; height: %g; real_height: %g; real_available_height: %g",
	     fo_object_debug_sprintf (fo_area),
	     fo_area_get_available_height (fo_area),
	     fo_area_area_get_height (fo_area),
	     FO_AREA_SPANNING_TABLE_CELL (fo_area)->real_height,
	     FO_AREA_SPANNING_TABLE_CELL (fo_area)->real_available_height);
  g_list_foreach (FO_AREA_SPANNING_TABLE_CELL (fo_area)->proxies,
		  fo_area_spanning_table_cell_debug_dump_proxy_height,
		  0);
}
#endif

/**
 * fo_area_spanning_table_cell_signal_test:
 * @signallee: 
 * @param: 
 * @signaller: 
 * 
 * Function to test how property value change signals work.
 **/
static void
fo_area_spanning_table_cell_signal_test (FoArea     *signallee,
					 GParamSpec *param G_GNUC_UNUSED,
					 FoArea     *signaller G_GNUC_UNUSED)
{
  gfloat old_real_available_height;
  gfloat new_real_available_height;
  gfloat real_height;

  old_real_available_height = FO_AREA_SPANNING_TABLE_CELL (signallee)->real_available_height;
  real_height = FO_AREA_SPANNING_TABLE_CELL (signallee)->real_height;

  new_real_available_height = fo_area_get_available_height (signallee);
  g_list_foreach (FO_AREA_SPANNING_TABLE_CELL (signallee)->proxies,
		  fo_area_spanning_table_cell_accumulate_proxy_available_height,
		  &new_real_available_height);

  FO_AREA_SPANNING_TABLE_CELL (signallee)->real_available_height = new_real_available_height;
  fo_area_set_child_available_bpdim (signallee,
				     new_real_available_height -
				     fo_area_area_get_border_before (signallee) -
				     fo_area_area_get_padding_before (signallee) -
				     fo_area_area_get_padding_after (signallee) -
				     fo_area_area_get_border_after (signallee));
#if defined(LIBFO_DEBUG) && 1
  g_message ("signal_test:: real_height: %g; old real_available_height: %g; new real_available_height: %g; child-available-bpdim: %g",
	     real_height,
	     old_real_available_height,
	     new_real_available_height,
	     fo_area_get_child_available_bpdim (signallee));
  fo_area_spanning_table_cell_debug_dump_heights (signallee);
#endif
#if defined(LIBFO_DEBUG) && 0
  if (real_height > 0 && real_height < new_real_available_height)
    {
      gfloat remaining_height = old_real_available_height;
      gint row_number;
      gint rows_spanned = FO_AREA_SPANNING_TABLE_CELL (signallee)->rows_spanned;

      fo_area_area_set_height (signallee,
			       fo_area_get_available_height (signallee));

      remaining_height -= fo_area_get_available_height (signallee);

      for (row_number = 2;
	   (row_number <= rows_spanned - 1) && remaining_height > 0;
	   row_number++)
	{
	  FoArea *proxy = fo_area_spanning_table_cell_get_nth_row_proxy (signallee, row_number);

	  fo_area_area_set_height (proxy,
				   fo_area_get_available_height (proxy));
	  
	  remaining_height -= fo_area_get_available_height (proxy);
	}

      if (remaining_height > 0)
	{
	  FoArea *last_proxy = fo_area_spanning_table_cell_get_nth_row_proxy (signallee, rows_spanned);

	  fo_area_area_set_height (last_proxy, remaining_height);
	  last_proxy = fo_area_size_request (last_proxy);
	}
    }
#endif
}

/**
 * fo_area_spanning_table_cell_new_with_rows_spanned:
 * @rows_spanned: Number of rows spanned by the new #FoAreaSpanningTableCell
 * 
 * Creates a new #FoAreaSpanningTableCell initialized to span @rows_spanned rows. 
 * 
 * Return value: the new #FoAreaSpanningTableCell
 **/
FoArea*
fo_area_spanning_table_cell_new_with_rows_spanned (gint rows_spanned)
{
  gint current_row;
  FoAreaSpanningTableCell *spanning_table_cell =
    FO_AREA_SPANNING_TABLE_CELL (fo_area_spanning_table_cell_new ());

  g_object_connect (spanning_table_cell,
		    "swapped_signal::notify::available-height",
		    fo_area_spanning_table_cell_signal_test,
		    spanning_table_cell,
		    NULL);

  spanning_table_cell->rows_spanned = rows_spanned;
  spanning_table_cell->row_info =
    g_new0 (FoAreaSpanningTableCellRowInfo, rows_spanned);

  for (current_row = 2; current_row <= rows_spanned; current_row++)
    {
      FoArea *proxy = fo_area_table_cell_proxy_new ();

      g_object_connect (proxy,
			"swapped_signal::notify::available-height",
			fo_area_spanning_table_cell_signal_test,
			spanning_table_cell,
			NULL);
      spanning_table_cell->proxies = g_list_append (spanning_table_cell->proxies,
					   proxy);
      fo_area_table_cell_proxy_set_row_number (proxy,
					       current_row);
      fo_area_table_cell_proxy_set_table_cell (proxy,
					       FO_AREA (spanning_table_cell));
    }

  return FO_AREA (spanning_table_cell);
}

/**
 * fo_area_spanning_table_cell_get_nth_row_proxy:
 * @fo_area:    The #FoAreaSpanningTableCell object
 * @row_number: The row number of proxy area to get
 * 
 * Gets the #FoSpanningTableCellProxy object at the @row_number row number.
 *
 * @row number should be in the range 2...rows-spanned, where
 * 'rows-spanned' is the number of rows spanned by @fo_area.
 *
 * When @fo_area spans only one row, this function always returns
 * NULL.
 *
 * Return value: The #FoSpanningTableCellProxy object, or NULL if no proxy
**/
FoArea*
fo_area_spanning_table_cell_get_nth_row_proxy (FoArea *fo_area,
				      gint    row_number)
{
  g_return_val_if_fail (fo_area != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_SPANNING_TABLE_CELL (fo_area), NULL);

  /* Subtract 2 from row_number since proxies' row numbers start at 2
     and g_list indexes start at 0 */
  return g_list_nth_data (FO_AREA_SPANNING_TABLE_CELL (fo_area)->proxies,
			  row_number - 2);
}

/**
 * fo_area_spanning_table_cell_debug_dump_proxy:
 * @value: Pointer to the proxy
 * @data:  Indent level
 * 
 * Logs debug dump info for one proxy of an #FoAreaSpanningTableCell.
 **/
static void
fo_area_spanning_table_cell_debug_dump_proxy (gpointer value, gpointer data)
{
  gchar *indent = g_strnfill (GPOINTER_TO_INT (data) * 2, ' ');
  gchar *string = fo_object_debug_sprintf (value);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 string);

  g_free (string);
  g_free (indent);
}

/**
 * fo_area_spanning_table_cell_debug_dump_properties:
 * @area:  The #FoArea object
 * @depth: Indent level to add to the output
 * 
 * Logs the value of each significant property of @area then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_area_spanning_table_cell_debug_dump_properties (FoArea *area,
					  gint depth)
{
  FoAreaSpanningTableCell *spanning_table_cell;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_SPANNING_TABLE_CELL (area));

  spanning_table_cell = FO_AREA_SPANNING_TABLE_CELL (area);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sproxies:",
	 indent);
  g_list_foreach (spanning_table_cell->proxies,
		  fo_area_spanning_table_cell_debug_dump_proxy,
		  GINT_TO_POINTER (depth + 1));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%srows-spanned:          %d",
	 indent,
	 spanning_table_cell->rows_spanned);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sreal-height:           %fpt",
	 indent,
	 spanning_table_cell->real_height);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sreal-available-height: %fpt",
	 indent,
	 spanning_table_cell->real_available_height);

  g_free (indent);
  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

/**
 * fo_area_spanning_table_cell_get_real_height:
 * @fo_area: The #FoAreaSpanningTableCell object
 *
 * Gets the #real-height property of @fo_area
 *
 * Return value: The "real_height" property value
**/
gfloat
fo_area_spanning_table_cell_get_real_height (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_SPANNING_TABLE_CELL (fo_area), 0);

  return FO_AREA_SPANNING_TABLE_CELL (fo_area)->real_height;
}

/**
 * fo_area_spanning_table_cell_get_real_available_height:
 * @fo_area: The #FoAreaSpanningTableCell object
 *
 * Gets the "real-available-height" property of @fo_area
 *
 * Return value: The "real-available-height" property value
**/
gfloat
fo_area_spanning_table_cell_get_real_available_height (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_SPANNING_TABLE_CELL (fo_area), 0);

  return FO_AREA_SPANNING_TABLE_CELL (fo_area)->real_available_height;
}

/**
 * fo_area_spanning_table_cell_size_request:
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
fo_area_spanning_table_cell_size_request (FoArea *child)
{
  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (child), NULL);
  g_return_val_if_fail (!FO_AREA_IS_ROOT (child), NULL);
  g_return_val_if_fail (fo_area_parent (child) != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_SPANNING_TABLE_CELL (fo_area_parent (child)), NULL);

  /* The area that is the return value of this procedure. */
  FoArea *return_child;
  /* Used when determining the return value. */
  FoArea *child_original_next_part = child->next_part;

  /* The table cell containing the area that issued this request. */
  FoArea *parent = fo_area_parent (child);
  gfloat parent_available_height =
    fo_area_get_available_height (parent);

  /* Find the total height of all children. */
  gfloat total_child_height = 0.0;
  fo_area_children_foreach (parent,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    &total_child_height);

  /* Ideally, this table cell would be just big enough for its borders
     and padding plus the height needed for its children. */
  gfloat parent_target_height = total_child_height +
    fo_area_area_get_border_before (parent) +
    fo_area_area_get_padding_before (parent) +
    fo_area_area_get_padding_after (parent) +
    fo_area_area_get_border_after (parent);

  FO_AREA_SPANNING_TABLE_CELL (parent)->real_height = parent_target_height;

  /* The FoFo that generated this table cell may have set the allowed
     height. */
  FoDatatype *fo_cell_bpdim =
    fo_property_get_value (fo_table_cell_get_block_progression_dimension (parent->generated_by));

  gfloat parent_use_height = 0.0;
  if (FO_IS_LENGTH_RANGE (fo_cell_bpdim))
    {
      FoDatatype *min_datatype =
	fo_length_range_get_minimum (fo_cell_bpdim);
      FoDatatype *opt_datatype =
	fo_length_range_get_optimum (fo_cell_bpdim);
      FoDatatype *max_datatype =
	fo_length_range_get_maximum (fo_cell_bpdim);

      if (FO_IS_LENGTH (min_datatype) &&
	  parent_target_height <= fo_length_get_value (min_datatype))
	{
	  parent_use_height = fo_length_get_value (min_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("spanning_table_cell_size_request:: target: %g; min: %g",
		     parent_target_height,
		     fo_length_get_value (min_datatype));
#endif
	}
      else if (FO_IS_LENGTH (opt_datatype) &&
	       parent_target_height < fo_length_get_value (opt_datatype))
	{
	  parent_use_height = fo_length_get_value (opt_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("spanning_table_cell_size_request:: target: %g; opt: %g",
		     parent_target_height,
		     fo_length_get_value (opt_datatype));
#endif
	}
      else if (FO_IS_LENGTH (max_datatype) &&
	       fo_length_get_value (max_datatype) < parent_target_height)
	{
	  parent_use_height = fo_length_get_value (max_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("spanning_table_cell_size_request:: target: %g; max: %g",
		     parent_target_height,
		     fo_length_get_value (max_datatype));
#endif
	}
      else
	{
	  parent_use_height = parent_target_height;
	}
    }
  else
    {
      /* The 'block_progression_dimension' property should only ever
	 be a length-range. */
      g_assert_not_reached ();
    }

  gfloat parent_real_available_height =
    fo_area_get_available_height (parent);

  g_list_foreach (FO_AREA_SPANNING_TABLE_CELL (parent)->proxies,
		  fo_area_spanning_table_cell_accumulate_proxy_available_height,
		  &parent_real_available_height);
  gint rows_spanned = FO_AREA_SPANNING_TABLE_CELL (parent)->rows_spanned;

#if defined(LIBFO_DEBUG) && 1
  fo_area_spanning_table_cell_debug_dump_heights (parent);
  g_message ("spanning_table_cell_size_request:: parent_available: %g; parent_use: %g",
	     parent_available_height,
	     parent_use_height);
#endif

  /* The available height may be less than what is required (or what
     is allowed by the FoFo). */
  if (parent_real_available_height < parent_use_height)
    {
      gfloat remaining_height = parent_use_height;
      gint row_number;

      fo_area_area_set_height (parent,
			       fo_area_get_available_height (parent));

      remaining_height -= fo_area_get_available_height (parent);

      for (row_number = 2;
	   (row_number <= rows_spanned - 1) && remaining_height > 0;
	   row_number++)
	{
	  FoArea *proxy =
	    fo_area_spanning_table_cell_get_nth_row_proxy (parent,
							   row_number);

	  fo_area_area_set_height (proxy,
				   fo_area_get_available_height (proxy));
	  
	  remaining_height -= fo_area_get_available_height (proxy);
	}

      if (remaining_height > 0)
	{
	  FoArea *last_proxy =
	    fo_area_spanning_table_cell_get_nth_row_proxy (parent,
							   rows_spanned);

	  fo_area_area_set_height (last_proxy, remaining_height);
	  last_proxy = fo_area_size_request (last_proxy);
	}
    }

  /* Work out the total child height again because this area's parent
     area may have adjusted the children. */
  total_child_height = 0;
  fo_area_children_foreach (parent,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    &total_child_height);

  /* Work out the new target height. */
  parent_target_height =
    total_child_height +
    fo_area_area_get_border_before (parent) +
    fo_area_area_get_padding_before (parent) +
    fo_area_area_get_padding_after (parent) +
    fo_area_area_get_border_after (parent);

  /* In the absence of 'display-align', the first child is placed just
     inside the borders and padding of this table cell. */
  fo_area_set_next_x (parent,
		      fo_area_area_get_border_start (parent) +
		      fo_area_area_get_padding_start (parent));
  fo_area_set_next_y (parent,
		      - (fo_area_area_get_border_before (parent) +
			 fo_area_area_get_padding_before (parent)));

  if (parent_target_height <= parent_available_height)
    {
      /* Since the children all fit within the allowed height, adjust
	 their sizes and positions in sequence. */
      fo_area_children_foreach (parent,
				G_TRAVERSE_ALL,
				&fo_area_size_adjust,
				NULL);
    }
  else
    {
      /* Since the children don't all fit, place the ones that fit in
	 the available height, and split at or before the allowed
	 height. */
      fo_area_children_foreach (parent,
				G_TRAVERSE_ALL,
				&fo_area_set_or_split,
				NULL);
#if defined(LIBFO_DEBUG) && 0
      g_message ("spanning_table_cell_size_request (%p):: total > available:: return:: parent->last: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_last_child (parent)),
		 fo_object_debug_sprintf (fo_area_last_child (parent)->generated_by));
#endif
    }

  /* The result will be the current child unless the child has been
     split, in which case the result is the portion after the last
     split. */
  return_child = child;

  while ((return_child->next_part != NULL) &&
	 (return_child->next_part != child_original_next_part))
    {
      return_child = return_child->next_part;
    }

  return return_child;
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
FoArea*
fo_area_spanning_table_cell_split_before_height (FoArea *area,
					gfloat max_height)
{
  FoArea *use_child_area;
  gfloat minus_child_y = 0.0;
  gfloat child_height = 0.0;

  g_return_val_if_fail (FO_IS_AREA_SPANNING_TABLE_CELL (area), NULL);
  g_return_val_if_fail (fo_area_n_children (area) > 0, NULL);
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
  g_message ("spanning_table_cell_split_before_height:: splitting: area: %s; generated by: %s; y: %f; height: %f",
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
	      fo_area_insert_with_next_siblings (clone, 0, use_child_area);

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
	      return fo_area_spanning_table_cell_split_before_height (area,
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
	  fo_area_insert_with_next_siblings (clone, 0, split_child);

	  return clone;
	}
      else
	{
	  /* If can't split use_child_area, maybe
	     can split at lower height */
	  return fo_area_spanning_table_cell_split_before_height (area,
							 minus_child_y);
	}
    }
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
gboolean
fo_area_spanning_table_cell_split_before_height_check (FoArea *area,
					     gfloat max_height)
{
  FoArea *use_child_area;
  gfloat minus_child_y = 0.0;
  gfloat child_height = 0.0;

  g_return_val_if_fail (FO_IS_AREA_SPANNING_TABLE_CELL (area), FALSE);
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
  g_message ("spanning_table_cell_split_before_height_check:: splitting: area: %s; generated by: %s; y: %f; height: %f",
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
	      return fo_area_spanning_table_cell_split_before_height_check (area,
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
	  return fo_area_spanning_table_cell_split_before_height_check (area,
							       minus_child_y);
	}
    }
}
