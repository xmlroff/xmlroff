/* Fo
 * fo-area-table-body.c: Area object for 'table-body' formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-body.c,v 1.2 2003/03/19 21:12:47 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-table-part.h"
#include "fo-area-table-part-private.h"
#include "fo-area-table-body.h"
#include "fo-area-table-cell.h"
#include "fo-table.h"
#include "fo-property-block-progression-dimension.h"

struct _FoAreaTableBody
{
  FoAreaTablePart parent_instance;
};

struct _FoAreaTableBodyClass
{
  FoAreaTablePartClass parent_class;
};

static void fo_area_table_body_class_init  (FoAreaTableBodyClass *klass);
static void fo_area_table_body_finalize    (GObject           *object);

static gpointer parent_class;

/**
 * fo_area_table_body_get_type:
 * @void: 
 * 
 * Register the FoTableBody object type.
 * 
 * Return value: GType value of the FoTableBody object type.
 **/
GType
fo_area_table_body_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaTableBodyClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_table_body_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaTableBody),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_TABLE_PART,
                                            "FoAreaTableBody",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_table_body_class_init:
 * @klass: FoTableBodyClass object to initialise
 * 
 * Implements GClassInitFunc for FoTableBodyClass
 **/
void
fo_area_table_body_class_init (FoAreaTableBodyClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_table_body_finalize;
}

/**
 * fo_area_table_body_finalize:
 * @object: FoTableBody object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoTableBody
 **/
void
fo_area_table_body_finalize (GObject *object)
{
  FoAreaTableBody *fo_area_table_body;

  fo_area_table_body = FO_AREA_TABLE_BODY (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_table_body_new:
 * 
 * Creates a new #FoAreaTableBody initialized to default value.
 * 
 * Return value: the new #FoAreaTableBody
 **/
FoArea*
fo_area_table_body_new (void)
{
  return FO_AREA (g_object_new (fo_area_table_body_get_type (), NULL));
}
