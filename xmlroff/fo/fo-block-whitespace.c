/* Fo
 * fo-block-whitespace.c: Whitespace-only block formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-block-whitespace.c,v 1.2 2003/04/15 12:13:48 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-block-whitespace.h"
#include "fo-block-whitespace-private.h"

static void fo_block_whitespace_class_init  (FoBlockWhitespaceClass *klass);
static void fo_block_whitespace_finalize    (GObject           *object);
static void fo_block_whitespace_debug_dump_properties (FoFo *fo, gint depth);

static gpointer parent_class;

GType
fo_block_whitespace_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoBlockWhitespaceClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_block_whitespace_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoBlockWhitespace),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_BLOCK,
                                            "FoBlockWhitespace",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_block_whitespace_class_init (FoBlockWhitespaceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_block_whitespace_finalize;

  FO_FO_CLASS (klass)->debug_dump_properties = fo_block_whitespace_debug_dump_properties;
  FO_FO_CLASS (klass)->update_from_context = fo_block_whitespace_update_from_context;
}

static void
fo_block_whitespace_finalize (GObject *object)
{
  FoBlockWhitespace *fo_block_whitespace;

  fo_block_whitespace = FO_BLOCK_WHITESPACE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_block_whitespace_new:
 * 
 * Creates a new #FoBlockWhitespace initialized to default value.
 * 
 * Return value: the new #FoBlockWhitespace
 **/
FoFo*
fo_block_whitespace_new (void)
{
  return FO_FO (g_object_new (fo_block_whitespace_get_type (), NULL));
}

void
fo_block_whitespace_update_from_context (FoFo *fo, FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);
}

void
fo_block_whitespace_debug_dump_properties (FoFo *fo, gint depth)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK (fo));

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

