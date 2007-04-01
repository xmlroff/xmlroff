/* Fo
 * fo-area-table-footer.c: Area object for 'table-footer' formatting objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-table-footer.c,v 1.2 2003/03/19 21:12:52 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-area.h"
#include "fo-area-private.h"
#include "fo-area-table-part.h"
#include "fo-area-table-part-private.h"
#include "fo-area-table-footer.h"
#include "fo-area-table-cell.h"
#include "fo-table.h"
#include "fo-property-block-progression-dimension.h"

struct _FoAreaTableFooter
{
  FoAreaTablePart parent_instance;
};

struct _FoAreaTableFooterClass
{
  FoAreaTablePartClass parent_class;
};

static void fo_area_table_footer_class_init  (FoAreaTableFooterClass *klass);
static void fo_area_table_footer_finalize    (GObject           *object);

static gpointer parent_class;

/**
 * fo_area_table_footer_get_type:
 * @void: 
 * 
 * Register the FoTableFooter object type.
 * 
 * Return value: GType value of the FoTableFooter object type.
 **/
GType
fo_area_table_footer_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaTableFooterClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_table_footer_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaTableFooter),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_TABLE_PART,
                                            "FoAreaTableFooter",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_table_footer_class_init:
 * @klass: FoTableFooterClass object to initialise
 * 
 * Implements GClassInitFunc for FoTableFooterClass
 **/
void
fo_area_table_footer_class_init (FoAreaTableFooterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_table_footer_finalize;
}

/**
 * fo_area_table_footer_finalize:
 * @object: FoTableFooter object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoTableFooter
 **/
void
fo_area_table_footer_finalize (GObject *object)
{
  FoAreaTableFooter *fo_area_table_footer;

  fo_area_table_footer = FO_AREA_TABLE_FOOTER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_table_footer_new:
 * 
 * Creates a new #FoAreaTableFooter initialized to default value.
 * 
 * Return value: the new #FoAreaTableFooter
 **/
FoArea*
fo_area_table_footer_new (void)
{
  return FO_AREA (g_object_new (fo_area_table_footer_get_type (), NULL));
}
