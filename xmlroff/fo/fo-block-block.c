/* Fo
 * fo-block-block.c: Block-level block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-block.c,v 1.2 2003/04/15 12:13:47 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-block-block.h"
#include "fo-block-block-private.h"
#include "fo-block-block-area.h"

static void fo_block_block_class_init  (FoBlockBlockClass *klass);
static void fo_block_block_finalize    (GObject           *object);

static gpointer parent_class;

GType
fo_block_block_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoBlockBlockClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_block_block_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoBlockBlock),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_BLOCK,
                                            "FoBlockBlock",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_block_block_class_init (FoBlockBlockClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_block_block_finalize;

  FO_FO_CLASS (klass)->area_new2 = fo_block_block_area_new2;
}

static void
fo_block_block_finalize (GObject *object)
{
  FoBlockBlock *fo_block_block;

  fo_block_block = FO_BLOCK_BLOCK (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_block_block_new:
 * 
 * Creates a new #FoBlockBlock initialized to default value.
 * 
 * Return value: the new #FoBlockBlock
 **/
FoFo*
fo_block_block_new (void)
{
  return FO_FO (g_object_new (fo_block_block_get_type (), NULL));
}
