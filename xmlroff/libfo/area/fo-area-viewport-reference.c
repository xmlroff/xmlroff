/* Fo
 * fo-area-viewport-reference.c: Combined viewport and reference area object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area-viewport-reference-private.h"

static void fo_area_viewport_reference_class_init  (FoAreaViewportReferenceClass *klass);
static void fo_area_viewport_reference_finalize    (GObject           *object);

static void     _debug_dump_properties (FoArea *area,
					gint    depth);

static gpointer parent_class;

GType
fo_area_viewport_reference_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaViewportReferenceClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_viewport_reference_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaViewportReference),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_REFERENCE,
                                            "FoAreaViewportReference",
                                            &object_info, 0);
    }
  
  return object_type;
}

static void
fo_area_viewport_reference_class_init (FoAreaViewportReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoAreaClass *area_class = FO_AREA_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_viewport_reference_finalize;

  area_class->debug_dump_properties =
    _debug_dump_properties;
}

static void
fo_area_viewport_reference_finalize (GObject *object)
{
  FoAreaViewportReference *fo_area_viewport_reference;

  fo_area_viewport_reference = FO_AREA_VIEWPORT_REFERENCE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_viewport_reference_new:
 * 
 * Creates a new #FoAreaViewportReference initialized to default value.
 * 
 * Return value: the new #FoAreaViewportReference
 **/
FoArea*
fo_area_viewport_reference_new (void)
{
  return FO_AREA (g_object_new (fo_area_viewport_reference_get_type (), NULL));
}


void
_debug_dump_properties (FoArea *area, gint depth)
{
  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_VIEWPORT_REFERENCE (area));

  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}
