/* Fo
 * fo-wrapper-block.c: Block-level wrapper formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-wrapper-block.h"
#include "fo-wrapper-block-private.h"
#include "fo-wrapper-block-area.h"

static void fo_wrapper_block_class_init  (FoWrapperBlockClass *klass);
static void fo_wrapper_block_finalize    (GObject           *object);
static void fo_wrapper_block_debug_dump_properties (FoFo *fo, gint depth);

static gpointer parent_class;

GType
fo_wrapper_block_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoWrapperBlockClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_wrapper_block_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoWrapperBlock),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_WRAPPER,
                                            "FoWrapperBlock",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_wrapper_block_class_init (FoWrapperBlockClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_wrapper_block_finalize;

  FO_FO_CLASS (klass)->debug_dump_properties = fo_wrapper_block_debug_dump_properties;
  FO_FO_CLASS (klass)->update_from_context = fo_wrapper_block_update_from_context;
  FO_FO_CLASS (klass)->area_new2 = fo_wrapper_block_area_new2;
}

static void
fo_wrapper_block_finalize (GObject *object)
{
  FoWrapperBlock *fo_wrapper_block;

  fo_wrapper_block = FO_WRAPPER_BLOCK (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_wrapper_block_new:
 * 
 * Creates a new #FoWrapperBlock initialized to default value.
 * 
 * Return value: the new #FoWrapperBlock
 **/
FoFo*
fo_wrapper_block_new (void)
{
  return FO_FO (g_object_new (fo_wrapper_block_get_type (), NULL));
}

void
fo_wrapper_block_update_from_context (FoFo *fo, FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_WRAPPER (fo));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);
}

void
fo_wrapper_block_debug_dump_properties (FoFo *fo, gint depth)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_WRAPPER (fo));

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

