/* Fo
 * fo-area-table-cell-proxy.c: Proxy area object for table-cell
 *                               formatting objects that span rows
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-cell-proxy.c,v 1.3 2003/07/02 11:00:27 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-area.h"
#include "fo-area-area-private.h"
#include "fo-area-table-cell-proxy.h"
#include "fo-area-spanning-table-cell.h"
#include "fo-table-cell.h"
#include "fo-property-block-progression-dimension.h"

struct _FoAreaTableCellProxy
{
  FoAreaArea parent_instance;

  FoArea *table_cell;
  gint    row_number;
  gfloat  min_height;
};

struct _FoAreaTableCellProxyClass
{
  FoAreaAreaClass parent_class;
};

static void fo_area_table_cell_proxy_class_init  (FoAreaTableCellProxyClass *klass);
static void fo_area_table_cell_proxy_finalize    (GObject           *object);

static void fo_area_table_cell_proxy_debug_dump_properties (FoArea *area,
							      gint depth);
static FoArea* fo_area_table_cell_proxy_size_request (FoArea *child);
static FoArea* fo_area_table_cell_proxy_split_before_height (FoArea *area,
						      gfloat max_height);
static gboolean fo_area_table_cell_proxy_split_before_height_check (FoArea *area,
							     gfloat max_height);

static gpointer parent_class;

/**
 * fo_area_table_cell_proxy_get_type:
 * @void: 
 * 
 * Register the FoTableCellProxy object type.
 * 
 * Return value: GType value of the FoTableCellProxy object type.
 **/
GType
fo_area_table_cell_proxy_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaTableCellProxyClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_table_cell_proxy_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaTableCellProxy),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_AREA,
                                            "FoAreaTableCellProxy",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_table_cell_proxy_class_init:
 * @klass: FoTableCellProxyClass object to initialise
 * 
 * Implements GClassInitFunc for FoTableCellProxyClass
 **/
void
fo_area_table_cell_proxy_class_init (FoAreaTableCellProxyClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoAreaClass *fo_area_class = FO_AREA_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_table_cell_proxy_finalize;

  fo_area_class->debug_dump_properties = fo_area_table_cell_proxy_debug_dump_properties;
  fo_area_class->size_request = fo_area_table_cell_proxy_size_request;
  fo_area_class->split_before_height = fo_area_table_cell_proxy_split_before_height;
  fo_area_class->split_before_height_check = fo_area_table_cell_proxy_split_before_height_check;
}

/**
 * fo_area_table_cell_proxy_finalize:
 * @object: FoTableCellProxy object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoTableCellProxy
 **/
void
fo_area_table_cell_proxy_finalize (GObject *object)
{
  FoAreaTableCellProxy *fo_area_table_cell_proxy;

  fo_area_table_cell_proxy = FO_AREA_TABLE_CELL_PROXY (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_table_cell_proxy_new:
 * 
 * Creates a new #FoAreaTableCellProxy initialized to default value.
 * 
 * Return value: the new #FoAreaTableCellProxy
 **/
FoArea*
fo_area_table_cell_proxy_new (void)
{
  return FO_AREA (g_object_new (fo_area_table_cell_proxy_get_type (), NULL));
}

/**
 * fo_area_table_cell_proxy_set_table_cell:
 * @fo_area:        The #FoAreaTableCellProxy object
 * @new_table_cell: The new "row-number" property value
 * 
 * Sets the #line-last property of @area_area to @new_table_cell
**/
void
fo_area_table_cell_proxy_set_table_cell (FoArea *fo_area,
					 FoArea *new_table_cell)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (fo_area));
  g_return_if_fail (FO_IS_AREA_SPANNING_TABLE_CELL (new_table_cell));

  FO_AREA_TABLE_CELL_PROXY (fo_area)->table_cell = new_table_cell;
  /* g_object_notify (G_OBJECT (fo_area), "table_cell");*/
}

/**
 * fo_area_table_cell_proxy_get_table_cell:
 * @fo_area: The #FoAreaTableCellProxy object
 * 
 * Gets the 'row-number' property of @area_table_cell_proxy
 *
 * Return value: The "row-number" property value
**/
FoArea*
fo_area_table_cell_proxy_get_table_cell (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (fo_area), 0);

  return FO_AREA_TABLE_CELL_PROXY (fo_area)->table_cell;
}

/**
 * fo_area_table_cell_proxy_set_row_number:
 * @fo_area:        The #FoAreaTableCellProxy object
 * @new_row_number: The new "row-number" property value
 * 
 * Sets the "row-number" property of @fo_area to @new_row_number
**/
void
fo_area_table_cell_proxy_set_row_number (FoArea *fo_area,
					 gint new_row_number)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (fo_area));

  FO_AREA_TABLE_CELL_PROXY (fo_area)->row_number = new_row_number;
  /* g_object_notify (G_OBJECT (fo_area), "row-number");*/
}

/**
 * fo_area_table_cell_proxy_get_row_number:
 * @fo_area: The #FoAreaTableCellProxy object
 * 
 * Gets the 'row-number' property of @area_table_cell_proxy
 *
 * Return value: The "row-number" property value
**/
gint
fo_area_table_cell_proxy_get_row_number (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (fo_area), 0);

  return FO_AREA_TABLE_CELL_PROXY (fo_area)->row_number;
}

/**
 * fo_area_table_cell_proxy_set_min_height:
 * @fo_area:        The #FoAreaTableCellProxy object
 * @new_min_height: The new "min-height" property value
 * 
 * Sets the "min-height" property of @fo_area to @new_min_height
**/
void
fo_area_table_cell_proxy_set_min_height (FoArea *fo_area,
					 gfloat new_min_height)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (fo_area));

  FO_AREA_TABLE_CELL_PROXY (fo_area)->min_height = new_min_height;
  /* g_object_notify (G_OBJECT (fo_area), "min-height");*/
}

/**
 * fo_area_table_cell_proxy_get_min_height:
 * @fo_area: The #FoAreaTableCellProxy object
 * 
 * Gets the 'min-height' property of @fo_area
 *
 * Return value: The "min-height" property value
**/
gfloat
fo_area_table_cell_proxy_get_min_height (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (fo_area), 0);

  return FO_AREA_TABLE_CELL_PROXY (fo_area)->min_height;
}

/**
 * fo_area_table_cell_proxy_debug_dump_properties:
 * @area:  The #FoArea object
 * @depth: Indent level to add to the output
 * 
 * Logs the value of each significant property of @area then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_area_table_cell_proxy_debug_dump_properties (FoArea *area, gint depth)
{
  FoAreaTableCellProxy *table_cell_proxy;
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *string;

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (area));

  table_cell_proxy = FO_AREA_TABLE_CELL_PROXY (area);

  string = fo_object_debug_sprintf (table_cell_proxy->table_cell);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%stable-cell area: %s",
	 indent,
	 string);
  g_free (string);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%srow-number:      %d",
	 indent,
	 table_cell_proxy->row_number);

  g_free (indent);
  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

FoArea*
fo_area_table_cell_proxy_add_child (FoArea *parent, FoArea *child)
{
  g_return_val_if_fail (parent != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (parent), NULL);
  g_return_val_if_fail (child != NULL, NULL);

  g_assert_not_reached ();
  return NULL;
}

/**
 * fo_area_table_cell_proxy_size_request:
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
fo_area_table_cell_proxy_size_request (FoArea *child)
{
  FoArea *use_child_area;
  FoArea *parent;
  FoDatatype *fo_row_bpdim;
  gfloat max_child_height = 0;
  gfloat parent_child_available_bpdim;
  gfloat parent_use_height = 0;
  gfloat child_height;

  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (child), NULL);
  g_return_val_if_fail (!FO_AREA_IS_ROOT (child), NULL);
  g_return_val_if_fail (fo_area_parent (child) != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (fo_area_parent (child)), NULL);

  child_height = fo_area_area_get_height (child);

  parent = fo_area_parent (child);
  parent_child_available_bpdim = fo_area_get_child_available_bpdim (parent);

  if (child_height <= parent_child_available_bpdim)
    {
      fo_area_set_available_height (child, parent_child_available_bpdim);
      return child;
    }

  use_child_area = fo_area_first_child (parent);

  while (use_child_area)
    {
      max_child_height =
	MAX (max_child_height,
	     fo_area_area_get_height (use_child_area));
      use_child_area = fo_area_next_sibling (use_child_area);
    }

  fo_row_bpdim =
    fo_property_get_value (fo_table_cell_get_block_progression_dimension (parent->generated_by));

  if (FO_IS_LENGTH_RANGE (fo_row_bpdim))
    {
      FoDatatype *min_datatype = fo_length_range_get_minimum (fo_row_bpdim);
      FoDatatype *opt_datatype = fo_length_range_get_optimum (fo_row_bpdim);
      FoDatatype *max_datatype = fo_length_range_get_maximum (fo_row_bpdim);

      if (FO_IS_LENGTH (min_datatype) &&
	  max_child_height <= fo_length_get_value (min_datatype))
	{
	  parent_use_height = fo_length_get_value (min_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_cell_proxy_size_request:: child: %g; min: %g",
		     max_child_height,
		     fo_length_get_value (min_datatype));
#endif
	}
      else if (FO_IS_LENGTH (opt_datatype) &&
	  fo_length_get_value (opt_datatype) < max_child_height)
	{
	  parent_use_height = fo_length_get_value (opt_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_cell_proxy_size_request:: child: %g; opt: %g",
		     max_child_height,
		     fo_length_get_value (opt_datatype));
#endif
	}
      else if (FO_IS_LENGTH (max_datatype) &&
	  fo_length_get_value (max_datatype) < max_child_height)
	{
	  parent_use_height = fo_length_get_value (max_datatype);

#if defined(LIBFO_DEBUG) && 0
	  g_message ("table_cell_proxy_size_request:: child: %g; max: %g",
		     max_child_height,
		     fo_length_get_value (max_datatype));
#endif
	}
      else
	{
	  parent_use_height = max_child_height;
	}
    }
  else
    {
      g_assert_not_reached ();
    }

  if (parent_child_available_bpdim < parent_use_height)
    {
      fo_area_area_set_height (parent, parent_use_height);
      parent = fo_area_size_request (parent);
      parent_child_available_bpdim = fo_area_get_child_available_bpdim (parent);
    }

  use_child_area = fo_area_first_child (parent);
  max_child_height = 0;

  while (use_child_area)
    {
      max_child_height =
	MAX (max_child_height,
	     fo_area_area_get_height (use_child_area));
      use_child_area = fo_area_next_sibling (use_child_area);
    }

  if (max_child_height <= parent_child_available_bpdim)
    {
      use_child_area = fo_area_first_child (parent);
  
      while (use_child_area)
	{
	  fo_area_set_available_height (use_child_area,
					parent_child_available_bpdim);
	  use_child_area = fo_area_next_sibling (use_child_area);
	}

      /* FIXME: Should this be last area in FO's glist of areas?
	 Currently is *not* the last area of child unless child is
	 the last child of parent (which is only true when child
	 appended to parent). */
      return fo_area_last_child (parent);
    }
  else
    {
      use_child_area = fo_area_first_child (parent);

      while (use_child_area)
	{
	  if (fo_area_area_get_height (use_child_area) <=
	      parent_child_available_bpdim)
	    {
	      fo_area_set_available_height (use_child_area,
					    parent_child_available_bpdim);

	      use_child_area = fo_area_next_sibling (use_child_area);
	    }
	  else
	    {
	      use_child_area =
		fo_area_split_before_height (use_child_area,
					     parent_child_available_bpdim);
	      parent = fo_area_parent (use_child_area);
	      parent_child_available_bpdim = fo_area_get_child_available_bpdim (parent);

	      /* Don't change use_child_area since need to test
		 again against parent_child_available_bpdim. */
	    }
	}
      return fo_area_last_child (parent);
    }
}

/* return the new area containing what comes after the split */
/* leave @area as area remaining after split */
FoArea*
fo_area_table_cell_proxy_split_before_height (FoArea *area,
				       gfloat max_height)
{
  FoArea *use_child_area;
  gboolean can_split = TRUE;

  g_return_val_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (area), NULL);
  g_return_val_if_fail (fo_area_n_children (area) > 0, NULL);
  g_return_val_if_fail (max_height > 0, NULL);

  use_child_area = fo_area_first_child (area);

  while (use_child_area && can_split)
    {
      gfloat child_height = fo_area_area_get_height (use_child_area);

      can_split &= ((child_height <= max_height) ||
		    fo_area_split_before_height_check (use_child_area,
						       max_height));

      use_child_area = fo_area_next_sibling (use_child_area);
    }

  if (can_split)
    {
      FoArea *split_child;
      FoArea *clone = fo_area_clone (area);
      gfloat max_remaining_child_height = 0;
      gfloat max_split_child_height = 0;

      area->is_last = FALSE;

      clone->is_first = FALSE;
      ((FoAreaArea *)clone)->border_before = 0;

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
fo_area_table_cell_proxy_split_before_height_check (FoArea *area,
					     gfloat max_height)
{
  FoArea *use_child_area;
  gboolean can_split = TRUE;

  g_return_val_if_fail (FO_IS_AREA_TABLE_CELL_PROXY (area), FALSE);
  g_return_val_if_fail (fo_area_n_children (area) > 0, FALSE);
  g_return_val_if_fail (max_height > 0, FALSE);

  use_child_area = fo_area_first_child (area);

  while (use_child_area && can_split)
    {
      gfloat child_height = fo_area_area_get_height (use_child_area);

      can_split &= ((child_height <= max_height) ||
		    fo_area_split_before_height_check (use_child_area,
						       max_height));

      use_child_area = fo_area_next_sibling (use_child_area);
    }

  return can_split;
}
