/* Fo
 * fo-region-after.c: 'region-after' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-region-after-private.h"
#include "fo/fo-region-after-area.h"
#include "fo-context-util.h"
#include "fo/fo-simple-page-master.h"
#include "property/fo-property-border.h"
#include "property/fo-property-padding.h"
#include "property/fo-property-margin.h"
#include "property/fo-property-precedence.h"
#include "property/fo-property-region-name.h"

/**
 * SECTION:fo-region-after
 * @short_description: 'region-after' formatting object
 *
 * Definition: <ulink url="http://www.w3.org/TR/xsl11/&num;fo_region-after">http://www.w3.org/TR/xsl11/&num;fo_region-after</ulink>
 */

enum {
  PROP_0,
  PROP_PRECEDENCE
};

static void _class_init (FoRegionAfterClass *klass);
static void _validate   (FoFo               *fo,
			 FoContext          *current_context,
			 FoContext          *parent_context,
			 GError            **error);

static gpointer parent_class;

/**
 * fo_region_after_get_type:
 * 
 * Register the #FoRegionAfter object type.
 * 
 * Return value: #GType value of the #FoRegionAfter object type.
 **/
GType
fo_region_after_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoRegionAfterClass),
	  NULL,           /* base_init */
	  NULL,           /* base_finalize */
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoRegionAfter),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_REGION_BEFORE_AFTER,
                                            "FoRegionAfter",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * _class_init:
 * @klass: #FoRegionAfterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRegionAfterClass.
 **/
void
_class_init (FoRegionAfterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  fofo_class->validate2 = _validate;
  fofo_class->area_new2 = fo_region_after_area_new;

}

/**
 * fo_region_after_new:
 * 
 * Creates a new #FoRegionAfter initialized to default value.
 * 
 * Return value: the new #FoRegionAfter.
 **/
FoFo*
fo_region_after_new (void)
{
  return FO_FO (g_object_new (fo_region_after_get_type (),
                              NULL));
}

/**
 * _validate:
 * @fo:              #FoRegionAfter object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
_validate (FoFo      *fo,
	   FoContext *current_context,
	   FoContext *parent_context,
	   GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION_AFTER (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_context_util_border_resolve (current_context, parent_context);
  fo_context_util_paddings_resolve (current_context, parent_context);
  fo_context_util_margins_indents_resolve (fo,
					   current_context,
					   parent_context);
  fo_context_util_margins_resolve (current_context, parent_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  FoDatatype *region_name_datatype =
    fo_property_get_value (fo_region_get_region_name (fo));

  gchar *region_name = NULL;
  if (region_name_datatype != NULL)
    {
      region_name =
	fo_name_get_value (region_name_datatype);
    }
  else
    {
      /* Need a freeable string because g_free() needed
	 if name had come from fo_name_get_value(). */
      region_name = g_strdup ("xsl-region-after");

      /* Also set the 'region-name' property to its default. */
      region_name_datatype =
	fo_name_new_with_value (region_name);
      FoProperty *region_name_prop =
	fo_property_region_name_new ();
      fo_property_set_value (region_name_prop,
			     region_name_datatype);
      fo_region_set_region_name (fo,
				 region_name_prop);
    }

  FoFo *simple_page_master = FO_FO (fo_node_parent (FO_NODE (fo)));

  if (simple_page_master != NULL)
    {
      fo_simple_page_master_set_region_after (simple_page_master,
					      fo);
    }
  else
    {
      g_assert_not_reached();
    }

  g_free (region_name);
}
