/* Fo
 * fo-area_tree.c: Formatting object area_tree root
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-tree.h"


struct _FoAreaTree
{
  FoArea parent_instance;
};

struct _FoAreaTreeClass
{
  FoAreaClass parent_class;
  
};

static void fo_area_tree_init        (FoAreaTree      *area_tree);
static void fo_area_tree_class_init  (FoAreaTreeClass *klass);
static void fo_area_tree_finalize    (GObject           *object);
static void fo_area_tree_debug_dump_properties (FoArea *area,
						gint depth);

static gpointer parent_class;

GType
fo_area_tree_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaTreeClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_tree_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaTree),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_area_tree_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA,
                                            "FoAreaTree",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_tree_init:
 * @media_usage: #FoAreaTree object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoAreaTree.
 **/
void
fo_area_tree_init (FoAreaTree *area_tree)
{
}

/**
 * fo_area_tree_class_init:
 * @klass: #FoAreaTreeClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoAreaTreeClass.
 **/
void
fo_area_tree_class_init (FoAreaTreeClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_tree_finalize;

  FO_AREA_CLASS (klass)->debug_dump_properties = fo_area_tree_debug_dump_properties;
}

/**
 * fo_area_tree_finalize:
 * @object: #FoAreaTree object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoAreaTree.
 **/
void
fo_area_tree_finalize (GObject *object)
{
  FoAreaTree *area_tree;

  area_tree = FO_AREA_TREE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_tree_new:
 * 
 * Creates a new #FoAreaTree initialized to default value.
 * 
 * Return value: the new #FoAreaTree
 **/
FoArea*
fo_area_tree_new (void)
{
  return FO_AREA (g_object_new (fo_area_tree_get_type (), NULL));
}

void
fo_area_tree_debug_dump_properties (FoArea *area, gint depth)
{
  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_TREE (area));

  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}
