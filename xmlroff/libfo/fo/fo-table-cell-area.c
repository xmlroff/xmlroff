/* Fo
 * fo-table-cell-area.c: Generate area for 'table-cell' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-block-fo.h"
#include "fo-table.h"
#include "fo-table-column.h"
#include "property/fo-property-column-width.h"
#include "property/fo-property-writing-mode.h"
#include "area/fo-area.h"
#include "area/fo-area-reference.h"
#include "area/fo-area-table-cell.h"
#include "area/fo-area-spanning-table-cell.h"
#include "fo/fo-table-cell-private.h"

void
fo_table_cell_area_new2 (FoFo                *fo_node,
			 FoFoAreaNew2Context *context,
			 GError             **error)
{
  FoArea *new_area;
  gfloat cell_width = 0.0;

  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_TABLE_CELL (fo_node));
  g_return_if_fail (context != NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  FoTableCell *table_cell = FO_TABLE_CELL (fo_node);

  /* fo:table/fo:table-body/fo:table-row/fo:table-cell */
  FoFo *table =
    FO_FO (fo_node_parent (fo_node_parent (fo_node_parent (FO_NODE (fo_node)))));

  gint column_number =
    fo_integer_get_value (fo_property_get_value (table_cell->column_number));
  gint number_columns_spanned =
    fo_integer_get_value (fo_property_get_value (table_cell->number_columns_spanned));
  gint number_rows_spanned =
    fo_integer_get_value (fo_property_get_value (table_cell->number_rows_spanned));

  gint span;
  for (span = 1;
       span <= number_columns_spanned;
       span++)
    {
      FoFo *column = fo_table_get_column (table,
					  column_number + span - 1,
					  1);

      cell_width +=
	fo_length_get_value (fo_property_get_value (fo_table_column_get_column_width (column)));
    }

  if (number_rows_spanned == 1)
    {
      new_area = fo_area_table_cell_new ();
    }
  else
    {
      new_area =
	fo_area_spanning_table_cell_new_with_rows_spanned (number_rows_spanned);
    }
  FoArea *use_parent_area = context->parent_area;

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** table-cell parent before new area:");
  fo_object_debug_dump (use_parent_area, 0);
  g_warning ("*** end table-cell parent");
#endif

  fo_area_set_generated_by (new_area, fo_node);
  FO_FO (fo_node)->areas = g_list_append (FO_FO (fo_node)->areas, new_area);

  fo_area_add_child (use_parent_area,
		     new_area);

  if (number_rows_spanned > 1)
    {
      FoArea *use_row = fo_area_next_sibling (use_parent_area);
      gint current_row;

      for (current_row = 2; current_row <= number_rows_spanned; current_row++)
	{
	  FoArea *proxy = fo_area_spanning_table_cell_get_nth_row_proxy (new_area,
									 current_row);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_cell_area_new2:: current_row: %d; row: %s; proxy: %s",
		     current_row,
		     fo_object_debug_sprintf (use_row),
		     fo_object_debug_sprintf (proxy));
#endif
	  fo_area_set_generated_by (proxy, fo_node);
	  fo_area_add_child (use_row,
			     proxy);

	  use_row = fo_area_next_sibling (use_row);
	}
    }

  /*
    fo_block_fo_update_area (fo_node, new_area);
  */
  fo_area_area_set_border_after (new_area,
				 fo_length_get_value (fo_property_get_value (table_cell->border_after_width)));
  fo_area_area_set_border_before (new_area,
				  fo_length_get_value (fo_property_get_value (table_cell->border_before_width)));
  fo_area_area_set_border_end (new_area,
			       fo_length_get_value (fo_property_get_value (table_cell->border_end_width)));
  fo_area_area_set_border_start (new_area,
				 fo_length_get_value (fo_property_get_value (table_cell->border_start_width)));

  fo_area_area_set_padding_after (new_area,
				 fo_length_get_value (fo_property_get_value (table_cell->padding_after)));
  fo_area_area_set_padding_before (new_area,
				  fo_length_get_value (fo_property_get_value (table_cell->padding_before)));
  fo_area_area_set_padding_end (new_area,
			       fo_length_get_value (fo_property_get_value (table_cell->padding_end)));
  fo_area_area_set_padding_start (new_area,
				 fo_length_get_value (fo_property_get_value (table_cell->padding_start)));

  use_parent_area = fo_area_break_resolve (use_parent_area, new_area);
  /*
  fo_area_border_padding_space_resolve (use_parent_area, new_area);
  */
  fo_area_area_set_width (new_area,
			  cell_width);
  fo_area_area_set_x (new_area,
		      fo_table_column_get_offset (fo_table_get_column (table,
								       column_number,
								       1)));
  fo_area_area_set_y (new_area,
		      0);
  fo_area_set_available_width (new_area,
			       fo_area_area_get_width (new_area));


  new_area = fo_area_size_request (new_area);
  fo_area_area_set_height (new_area,
			   fo_area_get_available_height (new_area));

  FoProperty *writing_mode
    = fo_table_get_writing_mode (table);
  fo_area_reference_set_bpd (new_area,
			     fo_property_writing_mode_to_bpd (writing_mode,
							      NULL));
  fo_area_reference_set_ipd (new_area,
			     fo_property_writing_mode_to_ipd (writing_mode,
							      NULL));
  fo_area_reference_set_sd (new_area,
			    fo_property_writing_mode_to_sd (writing_mode,
							    NULL));

#if defined(LIBFO_DEBUG) && 0
  g_warning ("*** table-cell parent after new area:");
  fo_object_debug_dump (parent_area, 0);
  g_warning ("*** end table-cell parent");
#endif

  *(context->new_area) = new_area;
}
