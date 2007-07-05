/* Fo
 * fo-block-layout.c: Layout-level block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-block-layout.h"
#include "fo-block-layout-private.h"

static void fo_block_layout_class_init  (FoBlockLayoutClass *klass);
static void fo_block_layout_finalize    (GObject           *object);
static void fo_block_layout_debug_dump_properties (FoFo *fo, gint depth);
static void fo_block_layout_children_properties_resolve (FoFo       *this_fo,
							 FoArea     *this_fo_parent_area,
							 FoArea    **new_area,
							 GHashTable *prop_eval_hash,
							 FoDoc      *fo_doc,
							 gboolean    continue_after_error,
							 FoDebugFlag   debug_level,
							 FoWarningFlag warning_mode,
							 GError    **error);

static gpointer parent_class;

GType
fo_block_layout_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoBlockLayoutClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_block_layout_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoBlockLayout),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_BLOCK,
                                            "FoBlockLayout",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_block_layout_class_init (FoBlockLayoutClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_block_layout_finalize;

  fo_fo_class->debug_dump_properties = fo_block_layout_debug_dump_properties;
  fo_fo_class->update_from_context = fo_block_layout_update_from_context;
  fo_fo_class->children_properties_resolve =
    fo_block_layout_children_properties_resolve;
}

static void
fo_block_layout_finalize (GObject *object)
{
  FoBlockLayout *fo_block_layout;

  fo_block_layout = FO_BLOCK_LAYOUT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_block_layout_new:
 * 
 * Creates a new #FoBlockLayout initialized to default value.
 * 
 * Return value: the new #FoBlockLayout
 **/
FoFo*
fo_block_layout_new (void)
{
  return FO_FO (g_object_new (fo_block_layout_get_type (), NULL));
}

void
fo_block_layout_update_from_context (FoFo *fo, FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);
}

void
fo_block_layout_debug_dump_properties (FoFo *fo, gint depth)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo));

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

void
fo_block_layout_children_properties_resolve (FoFo       *this_fo,
					     FoArea     *this_fo_parent_area,
					     FoArea    **new_area,
					     GHashTable *prop_eval_hash,
					     FoDoc      *fo_doc,
					     gboolean    continue_after_error,
					     FoDebugFlag   debug_level,
					     FoWarningFlag warning_mode,
					     GError    **error)
{
  GError *tmp_error = NULL;
  FoArea *this_fo_area = NULL;
  FoArea *child_fo_parent_area;
  FoFoAreaNew2Context area_new2_context;
  FoPropertyResolveContext prop_context;

  g_return_if_fail (FO_IS_FO (this_fo));
  g_return_if_fail (FO_IS_AREA (this_fo_parent_area));
  g_return_if_fail (*new_area == NULL);
  g_return_if_fail (error == NULL || *error == NULL);

  prop_context.reference_area       = fo_area_get_reference (this_fo_parent_area);
  prop_context.prop_eval_hash       = prop_eval_hash;
  prop_context.continue_after_error = continue_after_error;
  prop_context.debug_level          = debug_level;
  prop_context.warning_mode         = warning_mode;
  prop_context.error                = NULL;

  fo_node_traverse (FO_NODE (this_fo),
		    G_PRE_ORDER,
		    G_TRAVERSE_ALL,
		    -1,
		    fo_fo_resolve_property_attributes,
		    &prop_context);

  area_new2_context.fo_doc      = fo_doc;
  area_new2_context.parent_area = this_fo_parent_area;
  area_new2_context.new_area    = &this_fo_area;
  area_new2_context.debug_level = debug_level;

  fo_fo_area_new2 (this_fo,
		   &area_new2_context,
		   &tmp_error);

  *new_area = this_fo_area;

  if (*new_area != NULL)
    {
      child_fo_parent_area = *new_area;
    }
  else
    {
      child_fo_parent_area = this_fo_parent_area;
    }
}
