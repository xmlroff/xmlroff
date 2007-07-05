/* Fo
 * fo-numeric.c: Numeric datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-numeric.h"
#include "fo-numeric-private.h"


static void fo_numeric_class_init  (FoNumericClass *klass);
static void fo_numeric_finalize    (GObject           *object);

gchar* fo_numeric_debug_sprintf(FoNumeric *numeric);

static gpointer parent_class;

GType
fo_numeric_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoNumericClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_numeric_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoNumeric),
        0,              /* n_preallocs */
        NULL,		/* init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoNumeric",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_numeric_class_init (FoNumericClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_numeric_finalize;

}

static void
fo_numeric_finalize (GObject *object)
{
  FoNumeric *numeric;

  numeric = FO_NUMERIC (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_numeric_new:
 * 
 * Creates a new #FoNumeric initialized to default value.
 * 
 * Return value: the new #FoNumeric
 **/
FoDatatype *
fo_numeric_new (void)
{
  FoDatatype *numeric;

  numeric = FO_DATATYPE (g_object_new (fo_numeric_get_type (), NULL));
  
  return numeric;
}

