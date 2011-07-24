/* Fo
 * fo-area-table-row.c: Area object for table-row formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-area.h"
#include "fo-area-area-private.h"
#include "fo-area-table-row.h"
#include "fo-area-table-cell.h"
#include "fo/fo-table-row.h"
#include "property/fo-property-block-progression-dimension.h"

struct _FoAreaTableRow
{
  FoAreaArea parent_instance;
};

struct _FoAreaTableRowClass
{
  FoAreaAreaClass parent_class;
};

static void fo_area_table_row_class_init  (FoAreaTableRowClass *klass);
static void fo_area_table_row_finalize    (GObject           *object);

static void fo_area_table_row_debug_dump_properties (FoArea *area,
							      gint depth);
static FoArea* fo_area_table_row_size_request (FoArea *child);
static FoArea* fo_area_table_row_split_before_height (FoArea *area,
						      gdouble max_height);
static gboolean fo_area_table_row_split_before_height_check (FoArea *area,
							     gdouble max_height);

static gpointer parent_class;

/**
 * fo_area_table_row_get_type:
 * @void: 
 * 
 * Register the FoTableRow object type.
 * 
 * Return value: GType value of the FoTableRow object type.
 **/
GType
fo_area_table_row_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaTableRowClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_table_row_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaTableRow),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_AREA,
                                            "FoAreaTableRow",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_table_row_class_init:
 * @klass: FoTableRowClass object to initialise
 * 
 * Implements GClassInitFunc for FoTableRowClass
 **/
void
fo_area_table_row_class_init (FoAreaTableRowClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoAreaClass *area_class = FO_AREA_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_table_row_finalize;

  area_class->debug_dump_properties = fo_area_table_row_debug_dump_properties;
  area_class->size_request = fo_area_table_row_size_request;
  area_class->split_before_height = fo_area_table_row_split_before_height;
  area_class->split_before_height_check =
    fo_area_table_row_split_before_height_check;

}

/**
 * fo_area_table_row_finalize:
 * @object: FoTableRow object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoTableRow
 **/
void
fo_area_table_row_finalize (GObject *object)
{
  FoAreaTableRow *fo_area_table_row;

  fo_area_table_row = FO_AREA_TABLE_ROW (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_table_row_new:
 * 
 * Creates a new #FoAreaTableRow initialized to default value.
 * 
 * Return value: the new #FoAreaTableRow
 **/
FoArea*
fo_area_table_row_new (void)
{
  return FO_AREA (g_object_new (fo_area_table_row_get_type (), NULL));
}


/**
 * fo_area_table_row_debug_dump_properties:
 * @area:  The #FoArea object
 * @depth: Indent level to add to the output
 * 
 * Logs the value of each significant property of @area then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_area_table_row_debug_dump_properties (FoArea *area, gint depth)
{
  FoAreaTableRow *table_row;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_TABLE_ROW (area));

  table_row = FO_AREA_TABLE_ROW (area);

  g_free (indent);
  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

/**
 * fo_area_table_row_size_request:
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
fo_area_table_row_size_request (FoArea *child)
{
  FoArea *use_child_area;
  FoArea *table_row;
  FoDatatype *fo_row_bpdim;
  gdouble max_child_height = 0;
  gdouble table_row_child_available_ipdim;
  gdouble table_row_child_available_bpdim;
  gdouble table_row_use_height = 0;
  gdouble child_height;

  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (child), NULL);
  g_return_val_if_fail (!FO_AREA_IS_ROOT (child), NULL);
  g_return_val_if_fail (fo_area_parent (child) != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_TABLE_ROW (fo_area_parent (child)), NULL);

  child_height = fo_area_area_get_height (child);

  table_row = fo_area_parent (child);
  table_row_child_available_ipdim =
    MAX (fo_area_get_available_width (table_row),
	 0);
  table_row_child_available_bpdim =
    MAX (fo_area_get_available_height (table_row),
	 0);

  /* The simple case is when a cell needs less bpdim than was needed
     for a previous cell in the row. */
  if (child_height <= table_row_child_available_bpdim)
    {
      fo_area_set_available_height (child,
				    table_row_child_available_bpdim);
      return child;
    }

  use_child_area = fo_area_first_child (table_row);

  while (use_child_area)
    {
      max_child_height =
	MAX (max_child_height,
	     fo_area_area_get_height (use_child_area));
      use_child_area = fo_area_next_sibling (use_child_area);
    }

  fo_row_bpdim =
    fo_property_get_value (fo_table_row_get_block_progression_dimension (table_row->generated_by));

  if (FO_IS_LENGTH_RANGE (fo_row_bpdim))
    {
      FoDatatype *min_datatype = fo_length_range_get_minimum (fo_row_bpdim);
      FoDatatype *opt_datatype = fo_length_range_get_optimum (fo_row_bpdim);
      FoDatatype *max_datatype = fo_length_range_get_maximum (fo_row_bpdim);

      if (FO_IS_LENGTH (min_datatype) &&
	  max_child_height <= fo_length_get_value (min_datatype))
	{
	  table_row_use_height = fo_length_get_value (min_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_row_size_request:: child: %g; min: %g",
		     max_child_height,
		     fo_length_get_value (min_datatype));
#endif
	}
      else if (FO_IS_LENGTH (opt_datatype) &&
	  fo_length_get_value (opt_datatype) < max_child_height)
	{
	  table_row_use_height = fo_length_get_value (opt_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_row_size_request:: child: %g; opt: %g",
		     max_child_height,
		     fo_length_get_value (opt_datatype));
#endif
	}
      else if (FO_IS_LENGTH (max_datatype) &&
	  fo_length_get_value (max_datatype) < max_child_height)
	{
	  table_row_use_height = fo_length_get_value (max_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_row_size_request:: child: %g; max: %g",
		     max_child_height,
		     fo_length_get_value (max_datatype));
#endif
	}
      else
	{
	  table_row_use_height = max_child_height;
	}
    }
  else
    {
      g_assert_not_reached ();
    }

  if (table_row_child_available_bpdim < table_row_use_height)
    {
      fo_area_area_set_height (table_row, table_row_use_height);
      table_row = fo_area_size_request (table_row);
      table_row_child_available_ipdim = fo_area_get_available_width (table_row);
      fo_area_set_child_available_ipdim (table_row,
					 table_row_child_available_ipdim);
      table_row_child_available_bpdim = fo_area_get_available_height (table_row);
      fo_area_set_child_available_bpdim (table_row,
					 table_row_child_available_bpdim);
    }

  use_child_area = fo_area_first_child (table_row);
  max_child_height = 0;

  while (use_child_area)
    {
      max_child_height =
	MAX (max_child_height,
	     fo_area_area_get_height (use_child_area));
      use_child_area = fo_area_next_sibling (use_child_area);
    }

  if (max_child_height <= table_row_child_available_bpdim)
    {
      use_child_area = fo_area_first_child (table_row);
  
      while (use_child_area)
	{
	  fo_area_set_available_width (use_child_area,
				       table_row_child_available_ipdim);
	  fo_area_set_available_height (use_child_area,
					table_row_child_available_bpdim);
	  /* FIXME: Shouldn't setting available height set off something
	     in child to make it set its own height? */
	  fo_area_area_set_height (use_child_area,
				   table_row_child_available_bpdim);
	  use_child_area = fo_area_next_sibling (use_child_area);
	}

      /* FIXME: Should this be last area in FO's glist of areas?
	 Currently is *not* the last area of child unless child is
	 the last child of table_row (which is only true when child
	 appended to table_row). */
      return fo_area_last_child (table_row);
    }
  else
    {
      use_child_area = fo_area_first_child (table_row);

      while (use_child_area)
	{
	  if (fo_area_area_get_height (use_child_area) <=
	      table_row_child_available_bpdim)
	    {
	      fo_area_set_available_height (use_child_area,
					    table_row_child_available_bpdim);
	      fo_area_set_available_width (use_child_area,
					   table_row_child_available_ipdim);
	      fo_area_area_set_height (use_child_area,
				       table_row_child_available_bpdim);

	      use_child_area = fo_area_next_sibling (use_child_area);
	    }
	  else
	    {
	      use_child_area =
		fo_area_split_before_height (use_child_area,
					     table_row_child_available_bpdim);
	      table_row = fo_area_parent (use_child_area);
	      table_row_child_available_ipdim =
		fo_area_get_available_width (table_row);
	      fo_area_set_child_available_ipdim (table_row,
						 table_row_child_available_ipdim);
	      table_row_child_available_bpdim =
		fo_area_get_available_height (table_row);
	      fo_area_set_child_available_bpdim (table_row,
						 table_row_child_available_bpdim);

	      /* Don't change use_child_area since need to test
		 again against table_row_child_available_bpdim. */
	    }
	}
      return fo_area_last_child (table_row);
    }
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
FoArea*
fo_area_table_row_split_before_height (FoArea *area,
				       gdouble max_height)
{
  FoArea *use_child_area;
  gboolean can_split = TRUE;

  g_return_val_if_fail (FO_IS_AREA_TABLE_ROW (area), NULL);
  g_return_val_if_fail (fo_area_n_children (area) > 0, NULL);
  g_return_val_if_fail (max_height > 0, NULL);

  use_child_area = fo_area_first_child (area);

  while (use_child_area && can_split)
    {
      gdouble child_height = fo_area_area_get_height (use_child_area);

      can_split &= ((child_height <= max_height) ||
		    fo_area_split_before_height_check (use_child_area,
						       max_height));

      use_child_area = fo_area_next_sibling (use_child_area);
    }

  if (can_split)
    {
      FoArea *split_child;
      FoArea *clone = fo_area_clone (area);
      gdouble max_remaining_child_height = 0;
      gdouble max_split_child_height = 0;

      /*
      area->is_last = FALSE;

      clone->is_first = FALSE;
      ((FoAreaArea *)clone)->border_before = 0;
      */

      use_child_area = fo_area_first_child (area);

      while (use_child_area)
	{
	  split_child = fo_area_split_before_height (use_child_area,
						     max_height);

	  fo_area_unlink (split_child);
	  fo_area_append (clone, split_child);

	  max_remaining_child_height =
	    MAX (max_remaining_child_height,
		 fo_area_area_get_height (use_child_area));
	  max_split_child_height =
	    MAX (max_split_child_height,
		 fo_area_area_get_height (split_child));

	  use_child_area = fo_area_next_sibling (use_child_area);
	}

      fo_area_area_set_height (area, max_remaining_child_height);
      fo_area_area_set_height (clone, max_split_child_height);

      /*
      fo_area_size_request (area);
      fo_area_size_request (clone);
      */

      return clone;
    }
  else
    {
      return NULL;
    }
}
/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
gboolean
fo_area_table_row_split_before_height_check (FoArea *area,
					     gdouble max_height)
{
  FoArea *use_child_area;
  gboolean can_split = TRUE;

  g_return_val_if_fail (FO_IS_AREA_TABLE_ROW (area), FALSE);
  g_return_val_if_fail (fo_area_n_children (area) > 0, FALSE);
  g_return_val_if_fail (max_height > 0, FALSE);

  use_child_area = fo_area_first_child (area);

  while (use_child_area && can_split)
    {
      gdouble child_height = fo_area_area_get_height (use_child_area);

      can_split &= ((child_height <= max_height) ||
		    fo_area_split_before_height_check (use_child_area,
						       max_height));

      use_child_area = fo_area_next_sibling (use_child_area);
    }

  return can_split;
}
