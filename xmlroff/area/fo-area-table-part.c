/* Fo
 * fo-area-table-part.c: Area object for table-part formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-part.c,v 1.2 2003/03/19 21:12:55 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-area.h"
#include "fo-area-area-private.h"
#include "fo-area-table-part.h"
#include "fo-area-table-part-private.h"
#include "fo-area-table-cell.h"
#include "fo-table.h"
#include "fo-property-block-progression-dimension.h"

static void fo_area_table_part_class_init  (FoAreaTablePartClass *klass);
static void fo_area_table_part_finalize    (GObject           *object);

static gpointer parent_class;

/**
 * fo_area_table_part_get_type:
 * @void: 
 * 
 * Register the FoTablePart object type.
 * 
 * Return value: GType value of the FoTablePart object type.
 **/
GType
fo_area_table_part_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaTablePartClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_table_part_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaTablePart),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_AREA,
                                            "FoAreaTablePart",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_table_part_class_init:
 * @klass: FoTablePartClass object to initialise
 * 
 * Implements GClassInitFunc for FoTablePartClass
 **/
void
fo_area_table_part_class_init (FoAreaTablePartClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_table_part_finalize;
}

/**
 * fo_area_table_part_finalize:
 * @object: FoTablePart object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoTablePart
 **/
void
fo_area_table_part_finalize (GObject *object)
{
  FoAreaTablePart *fo_area_table_part;

  fo_area_table_part = FO_AREA_TABLE_PART (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_table_part_new:
 * 
 * Creates a new #FoAreaTablePart initialized to default value.
 * 
 * Return value: the new #FoAreaTablePart
 **/
FoArea*
fo_area_table_part_new (void)
{
  return FO_AREA (g_object_new (fo_area_table_part_get_type (), NULL));
}
