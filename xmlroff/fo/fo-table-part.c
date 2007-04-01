/* Fo
 * fo-table-part.c: Table header/footer/body formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-table-part.c,v 1.10 2006/03/28 15:21:51 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-table.h"
#include "fo-table-part.h"
#include "fo-table-part-private.h"
#include "fo-table-row.h"

enum {
  PROP_0
};

static void fo_table_part_base_class_init  (FoTablePartClass *klass);
static void fo_table_part_class_init  (FoTablePartClass *klass);
static void fo_table_part_finalize    (GObject           *object);
static void fo_table_part_debug_dump_properties (FoFo *fo, gint depth);
static void fo_table_part_children_properties_resolve (FoFo       *this_fo,
						       FoArea     *this_fo_parent_area,
						       FoArea    **new_area,
						       GHashTable *prop_eval_hash,
						       FoDoc      *fo_doc,
						       gboolean    continue_after_error,
						       FoDebugFlag   debug_level,
						       FoWarningFlag warning_mode,
						       GError      **error);

static gpointer parent_class;

GType
fo_table_part_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoTablePartClass),
        (GBaseInitFunc) fo_table_part_base_class_init,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_table_part_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoTablePart),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL
      };

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "FoTablePart",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * fo_table_part_base_class_init:
 * @klass: #FoTablePartClass base class object to initialise
 * 
 * Implements #GBaseInitFunc for #FoTablePart
 **/
void
fo_table_part_base_class_init (FoTablePartClass *klass)
{
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  fo_fo_class->children_properties_resolve =
    fo_table_part_children_properties_resolve;
}

/**
 * fo_table_part_class_init:
 * @klass: #FoTablePartClass object to initialise
 * 
 * Implements #GClassInitFunc for #FoTablePart
 **/
void
fo_table_part_class_init (FoTablePartClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_table_part_finalize;

  fo_fo_class->debug_dump_properties = fo_table_part_debug_dump_properties;
  fo_fo_class->update_from_context = fo_table_part_update_from_context;
}

static void
fo_table_part_finalize (GObject *object)
{
  FoTablePart *fo_table_part;

  fo_table_part = FO_TABLE_PART (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_table_part_new:
 * 
 * Creates a new #FoTablePart initialized to default value.
 * 
 * Return value: the new #FoTablePart
 **/
FoFo*
fo_table_part_new (void)
{
  return FO_FO (g_object_new (fo_table_part_get_type (), NULL));
}

/**
 * fo_table_part_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_table_part_update_from_context (FoFo *fo, FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE_PART (fo));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);
}

void
fo_table_part_debug_dump_properties (FoFo *fo, gint depth)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TABLE_PART (fo));

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

void
fo_table_part_children_properties_resolve (FoFo       *this_fo,
					   FoArea     *this_fo_parent_area,
					   FoArea    **new_area,
					   GHashTable *prop_eval_hash,
					   FoDoc        *fo_doc,
					   gboolean      continue_after_error,
					   FoDebugFlag   debug_level,
					   FoWarningFlag warning_mode,
					   GError      **error)
{
  FoNode *row_child = NULL;
  GError *tmp_error = NULL;
  FoArea *this_fo_area = NULL;
  FoArea *child_fo_parent_area;
  FoFoAreaNew2Context area_new2_context;
  FoPropertyResolveContext prop_context;

  g_return_if_fail (FO_IS_FO (this_fo));
  g_return_if_fail (FO_IS_AREA (this_fo_parent_area));
  g_return_if_fail (*new_area == NULL);
  g_return_if_fail (error == NULL || *error == NULL);

#if defined(LIBFO_DEBUG) && 0
  g_message ("node_children_properties_resolve:: this_fo: %s; this_fo_parent_area: %s",
	     fo_object_debug_sprintf (this_fo),
	     fo_object_debug_sprintf (this_fo_parent_area));
#endif

  prop_context.reference_area       = fo_area_get_reference (this_fo_parent_area);
  prop_context.prop_eval_hash       = prop_eval_hash;
  prop_context.continue_after_error = continue_after_error;
  prop_context.debug_level          = debug_level;
  prop_context.warning_mode         = warning_mode;
  prop_context.error                = NULL;

  fo_fo_resolve_property_attributes (FO_NODE (this_fo),
				     &prop_context);

  area_new2_context.fo_doc               = fo_doc;
  area_new2_context.parent_area          = this_fo_parent_area;
  area_new2_context.new_area             = &this_fo_area;
  area_new2_context.continue_after_error = continue_after_error;
  area_new2_context.debug_level          = debug_level;

  fo_fo_area_new2 (this_fo,
		   &area_new2_context,
		   &tmp_error);

  if (tmp_error != NULL)
    {
      fo_object_log_or_propagate_error (FO_OBJECT (row_child),
					error,
					tmp_error);
      return;
    }

  *new_area = this_fo_area;

  if (*new_area != NULL)
    {
      child_fo_parent_area = *new_area;
    }
  else
    {
      child_fo_parent_area = this_fo_parent_area;
    }

  /* table-row */
  row_child = fo_node_first_child (FO_NODE (this_fo));
  while (row_child != NULL)
    {
      FoFoAreaNew2Context row_area_new2_context;
      FoPropertyResolveContext row_prop_context;
      FoArea *row_area = NULL;

      row_prop_context.reference_area =
	fo_area_get_reference (child_fo_parent_area);
      row_prop_context.prop_eval_hash       = prop_eval_hash;
      row_prop_context.continue_after_error = continue_after_error;
      row_prop_context.debug_level          = debug_level;
      row_prop_context.warning_mode         = warning_mode;
      row_prop_context.error                = NULL;

      fo_fo_resolve_property_attributes (row_child,
					 &prop_context);

      row_area_new2_context.fo_doc      = fo_doc;
      row_area_new2_context.parent_area = child_fo_parent_area;
      row_area_new2_context.new_area    = &row_area;
      row_area_new2_context.debug_level = debug_level;

      fo_fo_area_new2 (FO_FO (row_child),
		       &row_area_new2_context,
		       &tmp_error);

      if (tmp_error != NULL)
	{
	  fo_object_log_or_propagate_error (FO_OBJECT (row_child),
					    error,
					    tmp_error);
	  return;
	}

      if (row_area != NULL)
	{
	  child_fo_parent_area = fo_area_parent (row_area);
	  if (*new_area != NULL)
	    *new_area = child_fo_parent_area;
	}

      row_child = fo_node_next_sibling (row_child);
    }

  /* table-row */
  row_child = fo_node_first_child (FO_NODE (this_fo));
  while (row_child != NULL)
    {
      FoNode *cell_grandchild = fo_node_first_child (row_child);
      FoArea *row_area = FO_FO (row_child)->areas->data;

      fo_table_span_info_start_row (FO_FO (fo_node_parent (FO_NODE (this_fo))),
				    &tmp_error);

      if (tmp_error != NULL)
	{
	  fo_object_log_or_propagate_error (FO_OBJECT (row_child),
					    error,
					    tmp_error);
	  return;
	}

      /* table-cell */
      while (cell_grandchild != NULL)
	{
	  FoArea *cell_area = NULL;

	  fo_fo_children_properties_resolve (FO_FO (cell_grandchild),
					     row_area,
					     &cell_area,
					     prop_eval_hash,
					     fo_doc,
					     continue_after_error,
					     debug_level,
					     warning_mode,
					     &tmp_error);

	  if (tmp_error != NULL)
	    {
	      fo_object_log_or_propagate_error (FO_OBJECT (row_child),
						error,
						tmp_error);
	      return;
	    }

	  if (cell_area != NULL)
	    {
	      row_area = fo_area_parent (cell_area);
	    }

	  cell_grandchild = fo_node_next_sibling (cell_grandchild);
	}

      if (row_area != NULL && *new_area != NULL)
	{
	  *new_area = fo_area_parent (row_area);
	}

      row_child = fo_node_next_sibling (row_child);
    }
}
