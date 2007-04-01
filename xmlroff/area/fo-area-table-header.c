/* Fo
 * fo-area-table-header.c: Area object for 'table-header' formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-header.c,v 1.2 2003/03/19 21:12:53 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-table-part.h"
#include "fo-area-table-part-private.h"
#include "fo-area-table-header.h"
#include "fo-area-table-cell.h"
#include "fo-table.h"
#include "fo-property-block-progression-dimension.h"

struct _FoAreaTableHeader
{
  FoAreaTablePart parent_instance;
};

struct _FoAreaTableHeaderClass
{
  FoAreaTablePartClass parent_class;
};

static void fo_area_table_header_class_init  (FoAreaTableHeaderClass *klass);
static void fo_area_table_header_finalize    (GObject           *object);

static gpointer parent_class;

/**
 * fo_area_table_header_get_type:
 * @void: 
 * 
 * Register the FoTableHeader object type.
 * 
 * Return value: GType value of the FoTableHeader object type.
 **/
GType
fo_area_table_header_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaTableHeaderClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_table_header_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaTableHeader),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_TABLE_PART,
                                            "FoAreaTableHeader",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_table_header_class_init:
 * @klass: FoTableHeaderClass object to initialise
 * 
 * Implements GClassInitFunc for FoTableHeaderClass
 **/
void
fo_area_table_header_class_init (FoAreaTableHeaderClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_table_header_finalize;
}

/**
 * fo_area_table_header_finalize:
 * @object: FoTableHeader object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoTableHeader
 **/
void
fo_area_table_header_finalize (GObject *object)
{
  FoAreaTableHeader *fo_area_table_header;

  fo_area_table_header = FO_AREA_TABLE_HEADER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_table_header_new:
 * 
 * Creates a new #FoAreaTableHeader initialized to default value.
 * 
 * Return value: the new #FoAreaTableHeader
 **/
FoArea*
fo_area_table_header_new (void)
{
  return FO_AREA (g_object_new (fo_area_table_header_get_type (), NULL));
}
