/* Fo
 * fo-area-region.c: Region area object
 *
 * Copyright (C) 2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area-viewport-reference-private.h"
#include "fo-area-region.h"

enum {
  PROP_0,
  PROP_REGION_NAME
};

struct _FoAreaRegion
{
  FoAreaViewportReference parent_instance;

  gchar *region_name;
};

struct _FoAreaRegionClass
{
  FoAreaViewportReferenceClass parent_class;
};

static void _init         (FoAreaRegion      *fo_area_region);
static void _class_init   (FoAreaRegionClass *klass);
static void _get_property (GObject           *object,
			   guint              prop_id,
			   GValue            *value,
			   GParamSpec        *pspec);
static void _set_property (GObject           *object,
			   guint              prop_id,
			   const GValue      *value,
			   GParamSpec        *pspec);
static void fo_area_region_finalize     (GObject           *object);

static void _debug_dump_properties (FoArea *area,
				    gint    depth);
static void _debug_dump_tree       (FoNode *fo_node,
				    gint    depth);
static void _update_after_clone    (FoArea *clone,
				    FoArea *original);

static gpointer parent_class;

/**
 * fo_area_region_get_type:
 * @void: 
 * 
 * Register the #FoAreaRegion object type.
 * 
 * Return value: #GType value of the #FoAreaRegion object type.
 **/
GType
fo_area_region_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoAreaRegionClass),
	  (GBaseInitFunc) NULL,
	  (GBaseFinalizeFunc) NULL,
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoAreaRegion),
	  0,              /* n_preallocs */
	  (GInstanceInitFunc) _init,
	  NULL		  /* value_table */
	};
      
      object_type = g_type_register_static (FO_TYPE_AREA_VIEWPORT_REFERENCE,
                                            "FoAreaRegion",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_region_init:
 * @fo_area_region: #FoAreaRegion object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoAreaRegion.
 **/
static void
_init (FoAreaRegion *fo_area_region)
{
  fo_area_region->region_name = NULL;

  FO_AREA (fo_area_region)->class = FO_AREA_FLAG_CLASS_ABSOLUTE;
}

/**
 * fo_area_region_class_init:
 * @klass: #FoAreaRegionClass object to initialise
 * 
 * Implements #GClassInitFunc for #FoAreaRegionClass
 **/
static void
_class_init (FoAreaRegionClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_region_finalize;

  object_class->set_property = _set_property;
  object_class->get_property = _get_property;

  FO_AREA_CLASS (klass)->debug_dump_properties =
    _debug_dump_properties;
  FO_AREA_CLASS (klass)->update_after_clone =
    _update_after_clone;

  FO_NODE_CLASS (klass)->debug_dump_tree = _debug_dump_tree;

  g_object_class_install_property
    (object_class,
     PROP_REGION_NAME,
     g_param_spec_string ("region-name",
			  _("Region name"),
			  _("Pegion name"),
			  NULL,
			  G_PARAM_READWRITE));
}

/**
 * fo_area_region_finalize:
 * @object: FoAreaRegion object to finalize
 * 
 * Implements #GObjectFinalizeFunc for #FoAreaRegion
 **/
void
fo_area_region_finalize (GObject *object)
{
  FoAreaRegion *fo_area_region;

  fo_area_region = FO_AREA_REGION (object);

  g_free (fo_area_region->region_name);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * _get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoAreaRegion
 **/
void
_get_property (GObject         *object,
	       guint            prop_id,
	       GValue          *value,
	       GParamSpec      *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_REGION_NAME:
      g_value_set_string (value,
			  fo_area_region_get_region_name (fo_area));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * _set_property:
 * @object:  #GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoAreaRegion
 **/
void
_set_property (GObject         *object,
	       guint            prop_id,
	       const GValue    *value,
	       GParamSpec      *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_REGION_NAME:
      fo_area_region_set_region_name (fo_area,
				      (const gchar *) g_value_get_string (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_area_region_new:
 * 
 * Creates a new #FoAreaRegion initialized to default value.
 * 
 * Return value: the new #FoAreaRegion
 **/
FoArea*
fo_area_region_new (void)
{
  return FO_AREA (g_object_new (fo_area_region_get_type (),
				NULL));
}

void
_debug_dump_properties (FoArea *area, gint depth)
{
  FoAreaRegion *region;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_REGION (area));

  region = FO_AREA_REGION (area);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sregion-name: %s", indent, region->region_name);

  g_free (indent);

  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

/**
 * _debug_dump_tree:
 * @node:  #FoNode to be dumped.
 * @depth: Relative indent to add to the output.
 * 
 * Implements #FoNode debug_dump_tree method for #FoNode.
 **/
static void
_debug_dump_tree (FoNode *fo_node,
		  gint    depth)
{
  FoNode *child;

  g_return_if_fail (fo_node != NULL);
  g_return_if_fail (FO_IS_AREA_REGION (fo_node));

  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *fo_node_sprintf = fo_object_debug_sprintf (fo_node);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 fo_node_sprintf);

  g_free (fo_node_sprintf);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    region-name: %s", indent, FO_AREA_REGION (fo_node)->region_name);

  g_free (indent);

  child = fo_node_first_child (fo_node);
  while (child != NULL)
    {
      fo_node_debug_dump_tree (child,
			       depth + 1);

      child = fo_node_next_sibling (child);
    }
}

static void
_update_after_clone (FoArea *clone,
		     FoArea *original)
{
  FO_AREA_CLASS (parent_class)->update_after_clone (clone, original);

  FoAreaRegion *original_region = (FoAreaRegion *) original;

  fo_area_region_set_region_name (clone,
				  original_region->region_name);
}

/**
 * fo_area_region_is_named_region:
 * @region: #FoAreaRegion to test
 * @data:   #FoAreaRegionNameAndArea containing name
 *
 * FIXME: Tries to do too many things at once.
 *
 * Returns: %TRUE if the name matches and sets @data
 **/
gboolean
fo_area_region_is_named_region (FoArea  *region,
				gpointer data)
{
  FoAreaRegionNameAndArea * name_and_area =
    (FoAreaRegionNameAndArea *) data;

  g_return_val_if_fail (FO_IS_AREA_REGION (region), TRUE);

  if (g_strcmp0 (name_and_area->name,
		 fo_area_region_get_region_name (region)) == 0)
    {
      name_and_area->area = region;
      return TRUE;
    }
  else
    {
      return FALSE;
    }
}

/**
 * fo_area_region_get_region_name:
 * @fo_area_region: The @FoAreaRegion object
 *
 * Gets the #region_name property of @area_region
 *
 * Return value: The "region-name" property value
**/
gchar *
fo_area_region_get_region_name (FoArea *fo_area_region)
{
  g_return_val_if_fail (fo_area_region != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_REGION (fo_area_region), 0);

  return FO_AREA_REGION (fo_area_region)->region_name;
}

/**
 * fo_area_region_set_region_name:
 * @fo_area_region: The @FoAreaRegion object
 * @new_region_name: The new "region-name" property value
 * 
 * Sets the #region_name property of @area_region to @new_region_name
**/
void
fo_area_region_set_region_name (FoArea *fo_area_region,
				const gchar* new_region_name)
{
  g_return_if_fail (fo_area_region != NULL);
  g_return_if_fail (FO_IS_AREA_REGION (fo_area_region));

  g_free (FO_AREA_REGION (fo_area_region)->region_name);
  FO_AREA_REGION (fo_area_region)->region_name = g_strdup (new_region_name);
  /*g_object_notify (G_OBJECT (fo_area_region), "region-name");*/
}
