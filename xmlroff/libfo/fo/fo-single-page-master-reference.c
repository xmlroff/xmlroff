/* Fo
 * fo-single-page-master-reference.c: 'single-page-master-reference' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-single-page-master-reference-private.h"
#include "property/fo-property-master-reference.h"

enum {
  PROP_0
};

static void _class_init  (FoSinglePageMasterReferenceClass *klass);
static void _debug_dump_properties (FoFo *fo,
				    gint  depth);

static gpointer parent_class;

/**
 * fo_single_page_master_reference_get_type:
 * 
 * Register the #FoSinglePageMasterReference object type.
 * 
 * Return value: #GType value of the #FoSinglePageMasterReference object type.
 **/
GType
fo_single_page_master_reference_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoSinglePageMasterReferenceClass),
	  NULL,           /* base_init */
	  NULL,           /* base_finalize */
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoSinglePageMasterReference),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_PAGE_MASTER_REFERENCE,
                                            "FoSinglePageMasterReference",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * _class_init:
 * @klass: #FoSinglePageMasterReferenceClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoSinglePageMasterReferenceClass.
 **/
void
_class_init (FoSinglePageMasterReferenceClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  fofo_class->debug_dump_properties = _debug_dump_properties;
}

/**
 * fo_single_page_master_reference_new:
 * 
 * Creates a new #FoSinglePageMasterReference initialized to default value.
 * 
 * Return value: the new #FoSinglePageMasterReference.
 **/
FoFo*
fo_single_page_master_reference_new (void)
{
  return FO_FO (g_object_new (fo_single_page_master_reference_get_type (),
                              NULL));
}

/**
 * _debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
_debug_dump_properties (FoFo *fo,
			gint  depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_SINGLE_PAGE_MASTER_REFERENCE (fo));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s(No properties)",
	 indent);

  g_free (indent);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}
