/* Fo
 * fo-area.c: Base area object of area object system
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-node.h"
#include "property/fo-property-break-after.h"
#include "property/fo-property-break-before.h"
#include "property/fo-property-start-indent.h"
#include "property/fo-property-end-indent.h"
#include "property/fo-property-space-before.h"
#include "property/fo-property-space-after.h"
#include "property/fo-property-border-before-width.h"
#include "property/fo-property-border-after-width.h"
#include "property/fo-property-border-start-width.h"
#include "property/fo-property-border-end-width.h"
#include "property/fo-property-padding-before.h"
#include "property/fo-property-padding-after.h"
#include "property/fo-property-padding-start.h"
#include "property/fo-property-padding-end.h"
#include "fo/fo-block-fo.h"
#include "area/fo-area.h"
#include "area/fo-area-private.h"
#include "area/fo-area-area.h"
#include "area/fo-area-reference.h"
#include "area/fo-area-page.h"
/* FIXME: should be get and set functions for everything from FoFo */
#include "fo/fo-fo-private.h"

enum {
  PROP_0,
  PROP_PAGE_SEQUENCE,
  PROP_IS_FIRST,
  PROP_IS_LAST,
  PROP_NEXT_X,
  PROP_NEXT_Y,
  PROP_AVAILABLE_WIDTH,
  PROP_AVAILABLE_HEIGHT,
  PROP_CHILD_AVAILABLE_IPDIM,
  PROP_CHILD_AVAILABLE_BPDIM,
  PROP_GENERATED_BY
};

static void fo_area_init        (FoArea      *object);
static void fo_area_base_class_init  (FoAreaClass *klass);
static void fo_area_class_init  (FoAreaClass *klass);
static void fo_area_get_property (GObject         *object,
				  guint            prop_id,
				  GValue          *value,
				  GParamSpec      *pspec);
static void fo_area_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_area_finalize    (GObject           *object);

static void     fo_area_debug_dump (FoObject *object,
				    gint depth);
static gchar*   fo_area_sprintf (FoObject *object);
static void     fo_area_debug_dump_properties_default (FoArea *area,
						       gint depth);
static void     fo_area_draw (FoArea *area, gpointer output);
static FoArea*  fo_area_clone_default (FoArea *original);
static void     fo_area_update_after_clone_default        (FoArea *clone,
							   FoArea *original);
static FoArea*  fo_area_split_before_height_default       (FoArea *area,
							   gfloat  height);
static gboolean fo_area_split_before_height_check_default (FoArea *area,
							   gfloat  height);
static FoArea*  fo_area_split_after_height_default        (FoArea *area,
							   gfloat  height);
static gboolean fo_area_split_after_height_check_default  (FoArea *area,
							   gfloat  height);
static FoArea*  fo_area_size_request_default              (FoArea *child);
static void     fo_area_default_resolve_text_align        (FoArea *area);
static void     fo_area_node_unlink_with_next_siblings    (FoNode *area);
static FoNode*  fo_area_node_insert_with_next_siblings    (FoNode *parent,
							   gint    position,
							   FoNode *area);
static FoNode*  fo_area_node_insert (FoNode *parent,
				     gint    position,
				     FoNode *area);
static FoNode*  fo_area_node_insert_before (FoNode *parent,
					    FoNode *sibling,
					    FoNode *area);
static FoNode*  fo_area_node_insert_after (FoNode *parent,
					   FoNode *sibling,
					   FoNode *area);
static FoNode*  fo_area_node_prepend (FoNode *parent,
				      FoNode *area);
static FoNode*  fo_area_node_append (FoNode *parent,
				     FoNode *area);

static gpointer parent_class;

/**
 * fo_area_get_type:
 * 
 * Register the #FoArea object type.
 * 
 * Return value: #GType value of the #FoArea object type.
 **/
GType
fo_area_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaClass),
        (GBaseInitFunc) fo_area_base_class_init,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoArea),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_area_init,
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_NODE,
                                            "FoArea",
                                            &object_info,
					    0);
    }
  
  return object_type;
}

/**
 * fo_area_init:
 * @fo_area: #FoArea object to initialise
 * 
 * Implements #GInstanceInitFunc for #FoArea
 **/
void
fo_area_init (FoArea *object)
{
  object->is_first = TRUE;
  object->is_last = TRUE;
}

/**
 * fo_area_base_class_init:
 * @klass: #FoAreaClass base class object to initialise
 * 
 * Implements #GBaseInitFunc for #FoAreaClass
 **/
void
fo_area_base_class_init (FoAreaClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  FoNodeClass *fo_node_class = FO_NODE_CLASS (klass);

  fo_object_class->debug_dump = fo_area_debug_dump;
  fo_object_class->print_sprintf = fo_area_sprintf;

  fo_node_class->insert = fo_area_node_insert;
  fo_node_class->insert_before = fo_area_node_insert_before;
  fo_node_class->insert_after = fo_area_node_insert_after;
  fo_node_class->insert_with_next_siblings =
    fo_area_node_insert_with_next_siblings;
  fo_node_class->unlink_with_next_siblings =
    fo_area_node_unlink_with_next_siblings;
  fo_node_class->prepend = fo_area_node_prepend;
  fo_node_class->append = fo_area_node_append;

  klass->debug_dump_properties = fo_area_debug_dump_properties_default;
  klass->add_child = fo_area_real_add_child;
  klass->clone = fo_area_clone_default;
  klass->update_after_clone = fo_area_update_after_clone_default;
  klass->split_before_height = fo_area_split_before_height_default;
  klass->split_before_height_check = fo_area_split_before_height_check_default;
  klass->split_after_height = fo_area_split_after_height_default;
  klass->split_after_height_check = fo_area_split_after_height_check_default;
  klass->size_request = fo_area_size_request_default;
  klass->resolve_text_align = fo_area_default_resolve_text_align;
}

/**
 * fo_area_class_init:
 * @klass: #FoAreaClass object to initialise
 * 
 * Implements #GClassInitFunc for #FoAreaClass
 **/
void
fo_area_class_init (FoAreaClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_finalize;

  object_class->get_property = fo_area_get_property;
  object_class->set_property = fo_area_set_property;

  klass->debug_dump_properties = fo_area_debug_dump_properties;
  klass->draw = fo_area_draw;

  g_object_class_install_property
    (object_class,
     PROP_PAGE_SEQUENCE,
     g_param_spec_object ("page_sequence",
			  _("fo:page_sequence node"),
			  _("Ancestor fo:page_sequence node in the formatting object tree"),
			  FO_TYPE_FO,
			  G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_PAGE_SEQUENCE,
     g_param_spec_object ("page",
			  _("Page area"),
			  _("Ancestor FoAreaPage node in the area tree"),
			  FO_TYPE_AREA,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_IS_FIRST,
     g_param_spec_boolean ("is-first",
			   _("Is first?"),
			   _("Is this the first area produced by the formatting object?"),
			   TRUE,
			   G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_IS_LAST,
     g_param_spec_boolean ("is-last",
			   _("Is last?"),
			   _("Is this the last area produced by the formatting object?"),
			   TRUE,
			   G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_NEXT_X,
     g_param_spec_float ("next-x",
			 _("next x"),
			 _("x-coordinate of next child area"),
			 0,
			 G_MAXFLOAT,
			 0,
			 G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_NEXT_Y,
     g_param_spec_float ("next-y",
			 _("next y"),
			 _("y-coordinate of next child area"),
			 0,
			 G_MAXFLOAT,
			 0,
			 G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_AVAILABLE_WIDTH,
     g_param_spec_float ("available-width",
			 _("Available width"),
			 _("Width available to child areas"),
			 0,
			 G_MAXFLOAT,
			 0,
			 G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_AVAILABLE_HEIGHT,
     g_param_spec_float ("available-height",
			 _("Available height"),
			 _("Height available to child areas"),
			 -G_MAXFLOAT,
			 G_MAXFLOAT,
			 0,
			 G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_CHILD_AVAILABLE_IPDIM,
     g_param_spec_float ("child-available-ipdim",
			 _("Child available IPDim"),
			 _("Inline-progression-dimension available to child areas"),
			 0,
			 G_MAXFLOAT,
			 0,
			 G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_CHILD_AVAILABLE_BPDIM,
     g_param_spec_float ("child-available-bpdim",
			 _("Child available BPDim"),
			 _("Block-progression-dimension available to child areas"),
			 0,
			 G_MAXFLOAT,
			 0,
			 G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_GENERATED_BY,
     g_param_spec_object ("generated-by",
			  _("Generated by"),
			  _("Formatting object that generated this area"),
			  FO_TYPE_FO,
			  G_PARAM_READWRITE));
}

/**
 * fo_area_finalize:
 * @object: #FoArea object to finalize
 * 
 * Implements #GObjectFinalizeFunc for #FoArea
 **/
void
fo_area_finalize (GObject *object)
{
  FoArea *area;

  area = FO_AREA (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_get_property:
 * @object:  #GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   #GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for #FoArea
 **/
void
fo_area_get_property (GObject        *object,
		      guint           param_id,
		      GValue         *value,
		      GParamSpec     *pspec)
{
  FoArea *area = FO_AREA (object);
  
  switch (param_id)
    {
    case PROP_PAGE_SEQUENCE:
      g_value_set_object (value,
                          area->page_sequence ? G_OBJECT (area->page_sequence) : NULL);
      break;
    case PROP_IS_FIRST:
      g_value_set_boolean (value, area->is_first);
      break;
    case PROP_IS_LAST:
      g_value_set_boolean (value, area->is_last);
      break;
    case PROP_NEXT_X:
      g_value_set_float (value, area->next_x);
      break;
    case PROP_NEXT_Y:
      g_value_set_float (value, area->next_y);
      break;
    case PROP_AVAILABLE_WIDTH:
      g_value_set_float (value, fo_area_get_available_width (area));
      break;
    case PROP_AVAILABLE_HEIGHT:
      g_value_set_float (value, fo_area_get_available_height (area));
      break;
    case PROP_CHILD_AVAILABLE_IPDIM:
      g_value_set_float (value, fo_area_get_child_available_ipdim (area));
      break;
    case PROP_CHILD_AVAILABLE_BPDIM:
      g_value_set_float (value, fo_area_get_child_available_bpdim (area));
      break;
    case PROP_GENERATED_BY:
      g_value_set_object (value,
                          area->generated_by ? G_OBJECT (area->generated_by) : NULL);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_area_set_property:
 * @object:  #GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for #FoArea
 **/
void
fo_area_set_property (GObject      *object,
		      guint         param_id,
		      const GValue *value,
		      GParamSpec   *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (param_id)
    {
    case PROP_PAGE_SEQUENCE:
      fo_area_set_page_sequence (fo_area, g_value_get_object (value));
      break;
    case PROP_IS_FIRST:
      fo_area_set_is_first (fo_area, g_value_get_boolean (value));
      break;
    case PROP_IS_LAST:
      fo_area_set_is_last (fo_area, g_value_get_boolean (value));
      break;
    case PROP_NEXT_X:
      fo_area_set_next_x (fo_area, g_value_get_float (value));
      break;
    case PROP_NEXT_Y:
      fo_area_set_next_y (fo_area, g_value_get_float (value));
      break;
    case PROP_AVAILABLE_WIDTH:
      fo_area_set_available_width (fo_area, g_value_get_float (value));
      break;
    case PROP_AVAILABLE_HEIGHT:
      fo_area_set_available_height (fo_area, g_value_get_float (value));
      break;
    case PROP_CHILD_AVAILABLE_IPDIM:
      fo_area_set_child_available_ipdim (fo_area, g_value_get_float (value));
      break;
    case PROP_CHILD_AVAILABLE_BPDIM:
      fo_area_set_child_available_bpdim (fo_area, g_value_get_float (value));
      break;
    case PROP_GENERATED_BY:
      fo_area_set_generated_by (fo_area, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_area_new:
 * 
 * Creates a new #FoArea initialized to default value.
 * 
 * Return value: the new #FoArea
 **/
FoArea *
fo_area_new (void)
{
  FoArea *object;

  object = FO_AREA (g_object_new (fo_area_get_type (),
				  NULL));
  
  return object;
}

/**
 * fo_area_get_is_first:
 * @fo_area: The @FoArea object
 *
 * Gets the #is_first property of @area
 *
 * Return value: The "is-first" property value
**/
gboolean
fo_area_get_is_first (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->is_first;
}

/**
 * fo_area_set_is_first:
 * @fo_area: The @FoArea object
 * @new_is_first: The new "is-first" property value
 * 
 * Sets the #is-first property of @fo_area to @new_is_first
**/
void
fo_area_set_is_first (FoArea *fo_area,
	       gboolean new_is_first)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->is_first = new_is_first;
  /*g_object_notify (G_OBJECT (fo_area), "is-first");*/
}

/**
 * fo_area_get_page:
 * @fo_area: The @FoArea object
 *
 * Gets the #page property of @area
 *
 * Return value: The "page" property value
**/
FoArea*
fo_area_get_page (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->page;
}

/**
 * fo_area_set_page:
 * @fo_area: The @FoArea object
 * @page_area: The new "page" property value
 * 
 * Sets the #page property of @fo_area to @page_area
**/
void
fo_area_set_page (FoArea *fo_area,
		  FoArea *page_area)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->page = page_area;
  /*g_object_notify (G_OBJECT (fo_area), "page");*/
}

/**
 * fo_area_get_reference:
 * @fo_area: The @FoArea object
 *
 * Gets the #reference property of @area
 *
 * Return value: The "reference" property value
**/
FoArea*
fo_area_get_reference (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->reference;
}

/**
 * fo_area_set_reference:
 * @fo_area: The @FoArea object
 * @reference_area: The new "reference" property value
 * 
 * Sets the #reference property of @fo_area to @reference_area
**/
void
fo_area_set_reference (FoArea *fo_area,
		       FoArea *reference_area)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->reference = reference_area;
  /*g_object_notify (G_OBJECT (fo_area), "reference");*/
}

/**
 * fo_area_get_page_sequence:
 * @fo_area: The @FoArea object
 *
 * Gets the #page_sequence property of @area
 *
 * Return value: The "page-sequence" property value
**/
FoArea*
fo_area_get_page_sequence (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->page_sequence;
}

/**
 * fo_area_set_page_sequence:
 * @fo_area: The @FoArea object
 * @page_sequence_area: The new "page_sequence" property value
 * 
 * Sets the "page-sequence" property of @area to @page_sequence_area
**/
void
fo_area_set_page_sequence (FoArea *fo_area,
			   FoArea *page_sequence_area)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->page_sequence = page_sequence_area;
  /*g_object_notify (G_OBJECT (fo_area), "page-sequence");*/
}

/**
 * fo_area_get_is_last:
 * @fo_area: The @FoArea object
 *
 * Gets the #is_last property of @area
 *
 * Return value: The "is-last" property value
**/
gboolean
fo_area_get_is_last (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->is_last;
}

/**
 * fo_area_set_is_last:
 * @fo_area: The @FoArea object
 * @new_is_last: The new "is-last" property value
 * 
 * Sets the #is-last property of @area to @new_is_last
**/
void
fo_area_set_is_last (FoArea *fo_area,
	       gboolean new_is_last)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->is_last = new_is_last;
  /*g_object_notify (G_OBJECT (fo_area), "is-last");*/
}

/**
 * fo_area_get_next_x:
 * @fo_area: The @FoArea object
 *
 * Gets the #next_x property of @area
 *
 * Return value: The "next_x" property value
**/
gfloat
fo_area_get_next_x (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->next_x;
}

/**
 * fo_area_set_next_x:
 * @fo_area: The @FoArea object
 * @new_next_x: The new "next_x" property value
 * 
 * Sets the #next-x property of @area to @new_next_x
**/
void
fo_area_set_next_x (FoArea *fo_area,
	       gfloat new_next_x)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->next_x = new_next_x;
  /*g_object_notify (G_OBJECT (fo_area), "next-x");*/
}

/**
 * fo_area_get_next_y:
 * @fo_area: The @FoArea object
 *
 * Gets the "next_y" property of @area
 *
 * Return value: The "next-y" property value
**/
gfloat
fo_area_get_next_y (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->next_y;
}

/**
 * fo_area_set_next_y:
 * @fo_area: The @FoArea object
 * @new_next_y: The new "next-y" property value
 * 
 * Sets the #next-y property of @area to @new_next_y
**/
void
fo_area_set_next_y (FoArea *fo_area,
	       gfloat new_next_y)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->next_y = new_next_y;
  /*g_object_notify (G_OBJECT (fo_area), "next-y");*/
}

/**
 * fo_area_get_available_width:
 * @fo_area: The @FoArea object
 *
 * Gets the "available-width" property of @area
 *
 * Return value: The "available-width" property value
**/
gfloat
fo_area_get_available_width (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->available_width;
}

/**
 * fo_area_set_available_width:
 * @fo_area: The @FoArea object
 * @new_available_width: The new "available-width" property value
 * 
 * Sets the "available-width" property of @area to @new_available_width
**/
void
fo_area_set_available_width (FoArea *fo_area,
			     gfloat new_available_width)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->available_width = new_available_width;
  /*g_object_notify (G_OBJECT (fo_area), "available-width");*/
}

/**
 * fo_area_get_available_height:
 * @fo_area: The @FoArea object
 *
 * Gets the #available-height property of @area
 *
 * Return value: The "available_height" property value
**/
gfloat
fo_area_get_available_height (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->available_height;
}

/**
 * fo_area_set_available_height:
 * @fo_area: The @FoArea object
 * @new_available_height: The new "available-height" property value
 * 
 * Sets the #available-height property of @area to @new_available_height
**/
void
fo_area_set_available_height (FoArea *fo_area,
			      gfloat new_available_height)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->available_height = new_available_height;
  g_object_notify (G_OBJECT (fo_area), "available-height");
}

/**
 * fo_area_get_child_available_ipdim:
 * @fo_area: The @FoArea object
 *
 * Gets the "child-available-ipdim" property of @area
 *
 * Return value: The "child-available-ipdim" property value
**/
gfloat
fo_area_get_child_available_ipdim (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->child_available_ipdim;
}

/**
 * fo_area_set_child_available_ipdim:
 * @fo_area: The @FoArea object
 * @new_child_available_ipdim: The new "child-available-ipdim" property value
 * 
 * Sets the "child-available-ipdim" property of @area to
 * @new_child_available_ipdim
**/
void
fo_area_set_child_available_ipdim (FoArea *fo_area,
				   gfloat new_child_available_ipdim)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->child_available_ipdim = new_child_available_ipdim;
  /*g_object_notify (G_OBJECT (fo_area), "child-available-ipdim");*/
}

/**
 * fo_area_get_child_available_bpdim:
 * @fo_area: The @FoArea object
 *
 * Gets the "child-available-bpdim" property of @area
 *
 * Return value: The "child-available-bpdim" property value
**/
gfloat
fo_area_get_child_available_bpdim (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->child_available_bpdim;
}

/**
 * fo_area_set_child_available_bpdim:
 * @fo_area: The @FoArea object
 * @new_child_available_bpdim: The new "child-available-bpdim" property value
 * 
 * Sets the "child-available-bpdim" property of @area to
 * @new_child_available_bpdim
**/
void
fo_area_set_child_available_bpdim (FoArea *fo_area,
				   gfloat new_child_available_bpdim)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->child_available_bpdim = new_child_available_bpdim;
  /*g_object_notify (G_OBJECT (fo_area), "child-available-bpdim");*/
}

/**
 * fo_area_get_generated_by:
 * @fo_area: The @FoArea object
 *
 * Gets the #generated-by property of @area
 *
 * Return value: The "generated-by" property value
**/
FoFo*
fo_area_get_generated_by (FoArea *fo_area)
{
  g_return_val_if_fail (fo_area != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA (fo_area), 0);

  return fo_area->generated_by;
}

/**
 * fo_area_set_generated_by:
 * @fo_area: The @FoArea object
 * @new_fo: The new "generated-by" property value
 * 
 * Sets the #generated-by property of @area to @new_fo
**/
void
fo_area_set_generated_by (FoArea *fo_area,
			  FoFo   *new_fo)
{
  g_return_if_fail (fo_area != NULL);
  g_return_if_fail (FO_IS_AREA (fo_area));

  fo_area->generated_by = new_fo;
  /*g_object_notify (G_OBJECT (fo_area), "generated-by");*/
}

/**
 * fo_area_debug_dump:
 * @object: #FoArea or subclass object instance to be dumped
 * @depth:  Relative indent to apply to the output
 * 
 * Dump information about @object and its properties
 **/
void
fo_area_debug_dump (FoObject *object,
		    gint      depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* object_sprintf;
  FoArea *child;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_AREA (object));

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);
  g_free (indent);

  FO_AREA_GET_CLASS (object)->debug_dump_properties (FO_AREA (object),
						       depth + 2);
  child = fo_area_first_child (FO_AREA (object));
  while (child)
    {
      fo_object_debug_dump (child,
			    depth + 1);

      child = fo_area_next_sibling (child);
    }
}

/**
 * fo_area_sprintf:
 * @object: 
 * 
 * 
 * 
 * Return value: 
 **/
gchar*
fo_area_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA (object), NULL);

  return (g_strdup_printf("%s",
			  g_type_name (G_TYPE_FROM_INSTANCE (object))));
}


/**
 * fo_area_real_add_child:
 * @parent: Parent area node
 * @child:  Child area node
 * 
 * Add @child as a child of @parent in the area tree and set @child's
 * page_sequence, page, and reference instance variables as
 * appropriate for both @parent and @child.
 * 
 * Does NOT modify any other properties -- including geometric
 * properties -- of either @child or @parent.
 *
 * Return value: @child
 **/
FoArea*
fo_area_real_add_child (FoArea *parent, FoArea *child)
{
  g_return_val_if_fail (parent != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA (parent), NULL);
  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA (child), NULL);

  fo_area_append (parent, child);

  if (parent->page_sequence != NULL)
    child->page_sequence = parent->page_sequence;
  if (parent->page != NULL)
    child->page = parent->page;
  if (FO_IS_AREA_REFERENCE (child))
    {
      child->reference = child;
    }
  else
    {
      child->reference = parent->reference;
    }

  return child;
}

/**
 * fo_area_add_child:
 * @parent: Parent area node
 * @child:  Child area node
 * 
 * Add @child to @parent by calling the _add_child() function for
 * @parent.
 * 
 * Return value: @child
 **/
FoArea*
fo_area_add_child (FoArea *parent, FoArea *child)
{
  if (parent == NULL)
    {
      g_error ("area_add_child:: parent is NULL");
      return NULL;
    }
  else if (!FO_IS_AREA (parent))
    {
      g_error ("area_add_child:: parent is not an area: %s",
	       fo_object_debug_sprintf (parent));
      return NULL;
    }
  else
    {
      return FO_AREA_GET_CLASS (parent)->add_child (parent, child);
    }
}

/**
 * fo_area_debug_dump_properties_default:
 * @area:  #FoArea or subclass object
 * @depth: Indent level to add to the output
 * 
 * Default _debug_dump_properties() procedure that is used when an
 * FoArea subclass does not override the debug_dump_properties class
 * method.
 **/
void
fo_area_debug_dump_properties_default (FoArea *area, gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (FO_IS_AREA (area));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s(No 'debug_dump_properties')",
	 indent);

  g_free (indent);

  fo_area_debug_dump_properties (area, depth + 1);
}

/**
 * fo_area_debug_dump_properties:
 * @area: The #FoArea object
 * @depth: Indent level to add to the output
 * 
 * Dump the properties of @area.
 **/
void
fo_area_debug_dump_properties (FoArea *area, gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *fo_sprintf;

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA (area));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sis-first:              %s",
	 indent,
	 area->is_first ? "true" : "false");

  fo_sprintf = fo_object_debug_sprintf (area->prev_part);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sprev-part:             %s",
	 indent,
	 fo_sprintf);
  g_free (fo_sprintf);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sis-last:               %s",
	 indent,
	 area->is_last ? "true" : "false");

  fo_sprintf = fo_object_debug_sprintf (area->next_part);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%snext-part:             %s",
	 indent,
	 fo_sprintf);
  g_free (fo_sprintf);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%snext-x:                %g pt",
	 indent,
	 area->next_x);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%snext-y:                %g pt",
	 indent,
	 area->next_y);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%savailable-width:       %g pt",
	 indent,
	 area->available_width);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%savailable-height:      %g pt",
	 indent,
	 area->available_height);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%schild-available-ipdim: %g pt",
	 indent,
	 area->child_available_ipdim);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%schild-available-bpdim: %g pt",
	 indent,
	 area->child_available_bpdim);

  fo_sprintf = fo_object_debug_sprintf (area->generated_by);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sgenerated-by:          %s",
	 indent,
	 fo_sprintf);
  g_free (fo_sprintf);

  fo_sprintf = fo_object_debug_sprintf (area->reference);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sreference:             %s",
	 indent,
	 fo_sprintf);
  g_free (fo_sprintf);

  fo_sprintf = fo_object_debug_sprintf (area->page);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spage:                  %s",
	 indent,
	 fo_sprintf);
  g_free (fo_sprintf);

  g_free (indent);
}

/**
 * fo_area_draw:
 * @area:   #FoArea to draw.
 * @output: Where to draw it.
 * 
 * Unused.
 **/
void
fo_area_draw (FoArea  *area,
	      gpointer output)
{
  g_return_if_fail (area != NULL);

  g_warning (_("Area has no 'draw' function."));
}

/**
 * fo_area_update_after_clone:
 * @clone:    New object cloned from @original.
 * @original: Original area object.
 * 
 * Update the instance variables of @clone to match those of @original.
 **/
void
fo_area_update_after_clone (FoArea *clone,
			    FoArea *original)
{
  if (original == NULL || clone == NULL)
    {
      return;
    }
  else
    {
      FO_AREA_GET_CLASS (clone)->update_after_clone (clone, original);
    }
}

/**
 * fo_area_update_after_clone_default:
 * @clone:    New object cloned from @original
 * @original: Original area object
 * 
 * Update the FoArea-specific instance variables of @clone to match
 * those of @original.
 **/
void
fo_area_update_after_clone_default (FoArea *clone,
				    FoArea *original)
{
  g_return_if_fail (clone != NULL);
  g_return_if_fail (FO_IS_AREA (clone));
  g_return_if_fail (original != NULL);
  g_return_if_fail (FO_IS_AREA (original));

  fo_area_set_page_sequence (clone, original->page_sequence);
  fo_area_set_page (clone, original->page);
  fo_area_set_reference (clone, original->reference);
  clone->is_first = FALSE;
  clone->prev_part = original;
  original->is_last = FALSE;
  original->next_part = clone;
  clone->generated_by = original->generated_by;

  /* FIXME: should be get and set functions for everything from FoFo */
  clone->generated_by->areas =
    g_list_insert (clone->generated_by->areas,
		   clone,
		   g_list_index (clone->generated_by->areas,
				original) + 1);

  fo_area_insert_after (fo_area_parent (original), original, clone);
}


/**
 * fo_area_clone:
 * @original: Area object to be cloned.
 * 
 * Make a clone of @original and insert the clone after @original in
 * the area tree.  Set instance properties of the clone to match
 * @original.
 * 
 * Return value: Clone of @original.
 **/
FoArea*
fo_area_clone (FoArea *original)
{
  if (original != NULL)
    {
      return FO_AREA_GET_CLASS (original)->clone (original);
    }
  else
    {
      return NULL;
    }
}

/**
 * fo_area_clone_default:
 * @original: Area object to be cloned
 * 
 * Make a clone of @original and insert the clone after @original in
 * the area tree.  Set instance properties of the clone to match
 * @original.
 * 
 * Return value: Clone of @original
 **/
FoArea*
fo_area_clone_default (FoArea *original)
{
  FoArea *clone;

  g_return_val_if_fail (original != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA (original), NULL);

  clone = FO_AREA (g_object_new (G_TYPE_FROM_INSTANCE (original), NULL));

  fo_area_update_after_clone (clone, original);

  return clone;
}

/**
 * fo_area_dump_path_to_root:
 * @area: #FoArea for which to dump path to root.
 * 
 * Logs a representation of the area tree path from @area to the
 * tree's root.
 **/
static void
fo_area_dump_path_to_root (FoArea *area)
{
  FoArea *use_area;
  gint depth = 0;
  gchar *indent, *object_sprintf;

  use_area = area;

  while (!FO_AREA_IS_ROOT (use_area))
    {
      indent = g_strnfill (2 * depth++, ' ');
      object_sprintf = fo_object_debug_sprintf (use_area);

      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "%s%s",
	     indent,
	     object_sprintf);

      g_free (object_sprintf);
      g_free (indent);

      use_area = fo_area_parent (use_area);
    }
}

/**
 * fo_area_border_padding_space_resolve:
 * @parent_area: Parent area of @child_area.
 * @child_area:  #FoArea for which to resolve properties.
 * 
 * Resolves the border, padding, and space properties of @child_area.
 **/
void
fo_area_border_padding_space_resolve (FoArea *parent_area, FoArea *child_area)
{
  FoFo *child_fo;
  gfloat child_available_ipdim, child_available_bpdim;
  gfloat parent_next_x, parent_next_y;
  gfloat border_start_width = 0;
  gfloat border_end_width = 0;
  gfloat border_before_width = 0;
  gfloat border_after_width = 0;
  gfloat padding_start = 0;
  gfloat padding_end = 0;
  gfloat padding_before = 0;
  gfloat padding_after = 0;
  gfloat start_indent = 0, end_indent = 0;
  gfloat space_before = 0, space_after = 0;
  gboolean is_first, is_last;

  g_return_if_fail (parent_area != NULL);
  g_return_if_fail (FO_IS_AREA (parent_area));
  g_return_if_fail (child_area != NULL);
  g_return_if_fail (FO_IS_AREA (child_area));

  child_fo = child_area->generated_by;

  g_object_get (parent_area,
		"child-available-ipdim", &child_available_ipdim,
		"child-available-bpdim", &child_available_bpdim,
		"next-x", &parent_next_x,
		"next-y", &parent_next_y,
		NULL);

#if defined(LIBFO_DEBUG) && 0
  g_message ("bps_resolve:: area: %s; area fo: %s; parent: %s; parent fo: %s",
	     fo_object_debug_sprintf (child_area),
	     fo_object_debug_sprintf (child_fo),
	     fo_object_debug_sprintf (parent_area),
	     fo_object_debug_sprintf (parent_area->generated_by);
  g_message ("bps_resolve:: parent:: child-available-ipdim: %f; child-available-bpdim: %f; next-x: %f; next-y: %f",
	     child_available_ipdim,
	     child_available_bpdim,
	     parent_next_x,
	     parent_next_y);
#endif

  g_object_get (child_area,
		"is-first", &is_first,
		"is_last", &is_last,
		NULL);

  if (FO_IS_BLOCK_FO (child_fo))
    {
      border_start_width =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_border_start_width (child_fo)));
      border_end_width =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_border_end_width (child_fo)));
      border_before_width =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_border_before_width (child_fo)));
      border_after_width =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_border_after_width (child_fo)));

      padding_start =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_padding_start (child_fo)));
      padding_end =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_padding_end (child_fo)));
      padding_before =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_padding_before (child_fo)));
      padding_after =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_padding_after (child_fo)));

      start_indent =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_start_indent (child_fo)));
      end_indent =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_end_indent (child_fo)));

      space_before =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_space_before (child_fo)));
      space_after =
	fo_length_get_value (fo_property_get_value (fo_block_fo_get_space_after (child_fo)));

#if defined(LIBFO_DEBUG) && 0
      g_message ("bps_resolve:: borders:: start: %f; end: %f; before: %f; after: %f",
		 border_start_width,
		 border_end_width,
		 border_before_width,
		 border_after_width);

      g_message ("bps_resolve:: padding:: start: %f; end: %f; before: %f; after: %f",
		 padding_start,
		 padding_end,
		 padding_before,
		 padding_after);
      g_message ("bps_resolve:: indent:: start: %f; end: %f; space:: before: %f; after: %f",
		 start_indent,
		 end_indent,
		 space_before,
		 space_after);
#endif
    }

  fo_area_area_set_border_after (child_area,
				 is_last ? border_after_width : 0.0);
  fo_area_area_set_border_before (child_area,
				  is_first ? border_before_width: 0.0);
  fo_area_area_set_border_end (child_area,
			       border_end_width);
  fo_area_area_set_border_start (child_area,
				 border_start_width);
  fo_area_area_set_padding_before (child_area,
				   padding_before);
  fo_area_area_set_padding_end (child_area,
				padding_end);
  fo_area_area_set_padding_after (child_area,
				  padding_after);
  fo_area_area_set_padding_start (child_area,
				  padding_start);
  fo_area_area_set_start_indent (child_area,
				 start_indent);
  fo_area_area_set_end_indent (child_area,
			       end_indent);
  fo_area_area_set_space_before (child_area,
				 space_before);
  fo_area_area_set_space_after (child_area,
				space_after);

  fo_area_area_set_x (child_area,
		      parent_next_x + start_indent);
  fo_area_area_set_y (child_area,
		      parent_next_y);

  fo_area_area_set_height (child_area,
			   space_before +
			   border_before_width +
			   padding_before +
			   padding_after +
			   border_after_width +
			   space_after);
  fo_area_area_set_width (child_area,
			  start_indent + end_indent);
  fo_area_set_next_x (child_area,
		      start_indent);
  fo_area_set_next_y (child_area,
		      - (space_before + padding_before + border_before_width));
  fo_area_set_available_height (child_area,
				MAX (child_available_bpdim -
				     space_before -
				     space_after -
				     border_before_width -
				     border_after_width -
				     padding_before -
				     padding_after,
				     0));
  fo_area_set_available_width (child_area,
			       MAX (child_available_ipdim -
				    start_indent -
				    end_indent,
				    0));
}

/**
 * fo_area_break_resolve:
 * @parent_area: Parent area of @new_area.
 * @new_area:    #FoArea for which to resolve breaks.
 * 
 * Resolves the break properties of @new_area, which may result in
 * @new_area being split into multiple areas.
 * 
 * Return value: Last area resulting from resolving breaks.
 **/
FoArea*
fo_area_break_resolve (FoArea *parent_area,
		       FoArea *new_area)
{
  gint break_before = FO_ENUM_ENUM_AUTO;
  gint prev_break_after = FO_ENUM_ENUM_AUTO;
  FoFo *fo;
  FoProperty *prev_break_after_prop = NULL;
  FoProperty *break_before_prop = NULL;
  gint page_number;

  g_return_val_if_fail (parent_area != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA (parent_area), NULL);
  g_return_val_if_fail (new_area != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA (new_area), NULL);

  fo = new_area->generated_by;

  if (g_object_class_find_property (G_OBJECT_GET_CLASS (fo),
				    "break-before"))
    {
      g_object_get (fo,
		    "break-before", &break_before_prop,
		    NULL);

      break_before =
	fo_enum_get_value (fo_property_get_value (break_before_prop));
    }
      
  if (!FO_AREA_IS_LEAF (parent_area) &&
      g_object_class_find_property (G_OBJECT_GET_CLASS (fo_area_last_child (parent_area)->generated_by),
				    "break-after"))
    {
      g_object_get (fo_area_last_child (parent_area)->generated_by,
		    "break-after", &prev_break_after_prop,
		    NULL);
      prev_break_after =
	fo_enum_get_value (fo_property_get_value (prev_break_after_prop));
    }

  page_number =
    fo_area_page_get_page_number (parent_area->page);

#if defined(LIBFO_DEBUG) && 0
  g_message ("break_resolve:: page_number: %d; break_before: %d; prev break_after: %d",
	     page_number, break_before, prev_break_after);
#endif

  if (((break_before == FO_ENUM_ENUM_PAGE) &&
       (!FO_AREA_IS_LEAF (parent_area))) ||
      ((break_before == FO_ENUM_ENUM_ODD_PAGE) &&
       ((!FO_AREA_IS_LEAF (parent_area)) ||
	(page_number % 2 == 0))) ||
      ((break_before == FO_ENUM_ENUM_EVEN_PAGE) &&
       ((!FO_AREA_IS_LEAF (parent_area)) ||
	(page_number % 2 == 1))) ||
      ((prev_break_after_prop != NULL) &&
       (((prev_break_after == FO_ENUM_ENUM_PAGE) &&
	 (!FO_AREA_IS_LEAF (parent_area))) ||
	((prev_break_after == FO_ENUM_ENUM_ODD_PAGE) &&
	 ((!FO_AREA_IS_LEAF (parent_area)) ||
	  (page_number % 2 == 1)))||
	((prev_break_after == FO_ENUM_ENUM_EVEN_PAGE) &&
	 ((!FO_AREA_IS_LEAF (parent_area)) ||
	  (page_number % 2 == 0))))))
    {
      FoArea *clone;

      g_message ("break_resolve:: make new page: %d", ++page_number);

      clone = fo_area_clone (parent_area);
      fo_area_dump_path_to_root (clone);

      /*
      parent_area = fo_add_to_new_page_area (fo_node, parent_area,
						 context, NULL,
						 debug_level);
      page_number =
	fo_area_page_get_page_number (parent_area->page);

      */
      if (((page_number % 2 == 1) &&
	   ((break_before == FO_ENUM_ENUM_PAGE) ||
	    ((prev_break_after_prop != NULL) &&
	     (prev_break_after == FO_ENUM_ENUM_EVEN_PAGE)))) ||
	  ((page_number % 2 == 0) &&
	   ((break_before == FO_ENUM_ENUM_ODD_PAGE) ||
	    ((prev_break_after_prop != NULL) &&
	     (prev_break_after == FO_ENUM_ENUM_ODD_PAGE)))))
	{
	  g_message ("break_resolve:: make another new page: %d", ++page_number);
	  clone = fo_area_clone (clone);
	  fo_area_dump_path_to_root (clone);
	  /*
	  parent_area =
	    fo_add_to_new_page_area (fo_node, parent_area,
				     context, NULL, debug_level);
	  */
	}
      g_message ("break_resolve:: clone: %p; parent_area: %p; new_area: %p",
		 clone, parent_area, new_area);
      return clone;
    }
  return parent_area;
}

/**
 * fo_area_split_before_height:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Split @area at or before @height.
 *
 * Return value: The part of @area spit from @area, or NULL if unsplit.
 **/
FoArea*
fo_area_split_before_height (FoArea *area, gfloat height)
{
  return FO_AREA_GET_CLASS (area)->split_before_height (area, height);
}

/**
 * fo_area_split_before_height_default:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Default function for split_before_height class method.
 *
 * Class method should be overridden by subclasses of #FoArea.
 *
 * Return value: NULL, indicating that @area was not split.
 **/
FoArea*
fo_area_split_before_height_default (FoArea *area, gfloat height)
{
  g_warning ("%s does not have a 'split_before_height' function.",
	     g_type_name (G_TYPE_FROM_INSTANCE (area)));
  return NULL;
}

/**
 * fo_area_split_before_height_check:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Check whether @area can split at or before @height.
 *
 * Return value: TRUE if can split, otherwise FALSE.
 **/
gboolean
fo_area_split_before_height_check (FoArea *area, gfloat height)
{
  return FO_AREA_GET_CLASS (area)->split_before_height_check (area,
							      height);
}

/**
 * fo_area_split_before_height_check_default:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Default function for split_before_height_check class method.
 *
 * Class method should be overridden by subclasses of #FoArea.
 *
 * Return value: %FALSE, indicating that @area cannot split
 **/
gboolean
fo_area_split_before_height_check_default (FoArea *area,
					   gfloat height)
{
  g_warning ("%s does not have a 'split_before_height_check' function.",
	     g_type_name (G_TYPE_FROM_INSTANCE (area)));
  return FALSE;
}

/**
 * fo_area_split_after_height:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Split @area at or after @height.
 *
 * Return value: The part of @area spit from @area, or NULL if unsplit.
 **/
FoArea*
fo_area_split_after_height (FoArea *area, gfloat height)
{
  return FO_AREA_GET_CLASS (area)->split_after_height (area, height);
}

/**
 * fo_area_split_after_height_default:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Default function for split_after_height class method.
 *
 * Class method should be overridden by subclasses of #FoArea.
 *
 * Return value: NULL, indicating that @area was not split.
 **/
FoArea*
fo_area_split_after_height_default (FoArea *area, gfloat height)
{
  g_warning ("%s does not have a 'split_after_height' function.",
	     g_type_name (G_TYPE_FROM_INSTANCE (area)));
  return NULL;
}

/**
 * fo_area_split_after_height_check:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Check whether @area can split at or after @height.
 *
 * Return value: TRUE if can split, otherwise FALSE.
 **/
gboolean
fo_area_split_after_height_check (FoArea *area, gfloat height)
{
  return FO_AREA_GET_CLASS (area)->split_after_height_check (area,
							      height);
}

/**
 * fo_area_split_after_height_check_default:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Default function for split_after_height_check class method.
 *
 * Class method should be overridden by subclasses of #FoArea.
 *
 * Return value: %FALSE, indicating that @area cannot split
 **/
gboolean
fo_area_split_after_height_check_default (FoArea *area,
					   gfloat height)
{
  g_warning ("%s does not have a 'split_after_height_check' function.",
	     g_type_name (G_TYPE_FROM_INSTANCE (area)));
  return FALSE;
}

/**
 * fo_area_default_resolve_text_align:
 * @area: #FoArea for which to resolve text alignment.
 * 
 * Resolves the text alignment value for @area and its descendants.
 **/
static void
fo_area_default_resolve_text_align (FoArea *area)
{
  FoArea *child_area;

  child_area = fo_area_first_child (area);

  while (child_area)
    {
      fo_area_resolve_text_align (child_area);
      child_area = fo_area_next_sibling (child_area);
    }
}

/**
 * fo_area_resolve_text_align:
 * @area: #FoArea for which to resolve text alignment.
 * 
 * Resolves the text alignment value for @area and its descendants.
 **/
void
fo_area_resolve_text_align (FoArea *area)
{
  if (area != NULL)
    {
      FO_AREA_GET_CLASS (area)->resolve_text_align (area);
    }
}

/**
 * fo_area_size_request:
 * @child: Child area
 * 
 * Checks that the parent area of @child has sufficient space for
 * @child.  If not enough space, requests that the parent has
 * sufficient space allocated for it, then adjusts @child and its
 * siblings as necessary to fit into the resized parent area.
 * 
 * You should call #fo_area_size_request() immediately after adding
 * an area to the area tree or making a change to the area's height.
 *
 * The child area's requested height is taken from the area's height
 * property value.  Its requested width is taken from its width
 * property value.
 *
 * The height allocated to the area is set in the area's
 * available_height property value.  Its width allocation is set in
 * its available_width property value.
 *
 * Immediately after calling this function, the child area should set
 * its height and width according to the available_height and
 * available_width property values.  How the child area resolves any
 * difference between the available height and width and the height
 * and width that it needs is up to the child area to work out.
 *
 * The child area's x and y property values may also have been
 * adjusted, but a child area doesn't set its own x and y property
 * values anyway.
 *
 * The area that is returned may be a different area object than the
 * child area that is passed as the argument to this function.  For
 * example, the parent area may not have been large enough to contain
 * the child area at its requested height, and the child area, the
 * parent area, and all ancestor areas up to an FoAreaPage may have
 * been split (possibly more than once) and the overflow placed on one
 * or more new pages.
 *
 * Return value: Pointer to the last area generated from @child after
 * any reallocation and resizing
 **/
FoArea*
fo_area_size_request (FoArea *child)
{
  FoArea *parent = fo_area_parent (child);

  if (parent == NULL)
    {
      g_error ("area_size_request:: parent is NULL");
      return NULL;
    }
  else if (!FO_IS_AREA (parent))
    {
      g_error ("area_size_request:: parent is not an area: %s",
	       fo_object_debug_sprintf (parent));
      return NULL;
    }
  else
    {
      return FO_AREA_GET_CLASS (parent)->size_request (child);
    }
}

/**
 * fo_area_accumulate_height:
 * @area: #FoArea whose height to add.
 * @data: Total to which to add height of @area.
 * 
 * For use with #fo_area_children_foreach.
 **/
void
fo_area_accumulate_height (FoArea *area,
			   gpointer data)
{
  gfloat *total = (gfloat *) data;
#if defined(LIBFO_DEBUG) && 0
  g_message ("add_height:: height: %f; area: %s; generated by: %s",
	     fo_area_area_get_height (area),
	     fo_object_debug_sprintf (area),
	     fo_object_debug_sprintf (area->generated_by));
#endif
  *total += fo_area_area_get_height (area);

  /*if (fo_area_prev_sibling (area))*/
    *total += fo_area_area_get_space_before (area);

    /*if (fo_area_next_sibling (area))*/
    *total += fo_area_area_get_space_after (area);
}

/**
 * fo_area_size_adjust:
 * @area: #FoArea node to be placed within parent
 * @data: Not used
 * 
 * Place @area within its parent and adjust the parent's next-x and
 * next-y properties accordingly.
 **/
void
fo_area_size_adjust (FoArea *area,
		     gpointer data)
{
  FoArea *parent = fo_area_parent (area);

  fo_area_area_set_x (area,
		      fo_area_get_next_x (parent) +
		      fo_area_area_get_start_indent (area));
  fo_area_area_set_y (area,
		      fo_area_get_next_y (parent) -
		      fo_area_area_get_space_before (area));
  /* FIXME: 0 or border+padding? */
  fo_area_set_next_x (parent, 0);
  fo_area_set_next_y (parent,
		      fo_area_get_next_y (parent) -
		      fo_area_area_get_height (area) -
		      fo_area_area_get_space_before (area) -
		      fo_area_area_get_space_after (area));
  fo_area_set_available_height (area,
				fo_area_area_get_height (area));
  /* FIXME: Shouldn't child do its own accounting for indents? */
  fo_area_set_available_width (area,
                               MAX (fo_area_get_child_available_ipdim (parent) -
                                    fo_area_area_get_start_indent (area) -
                                    fo_area_area_get_end_indent (area),
                                    0));
}

/**
 * fo_area_set_or_split:
 * @area: #FoArea to be either placed within the parent area or split
 *        into two areas
 * @data: Not used
 * 
 * 
 **/
void
fo_area_set_or_split (FoArea *area,
		      gpointer data)
{
  FoArea *parent = fo_area_parent (area);
  gfloat child_available_bpdim = fo_area_get_child_available_bpdim (parent);

  if ((child_available_bpdim -
       (fo_area_get_next_y (parent) -
	fo_area_area_get_height (area))) >= 0)
    {
      fo_area_area_set_x (area,
			  fo_area_get_next_x (parent) +
			  fo_area_area_get_start_indent (area));
      fo_area_area_set_y (area,
			  fo_area_get_next_y (parent));
      /* FIXME: 0 or border+padding? */
      fo_area_set_next_x (parent, 0);
      fo_area_set_next_y (parent,
			  fo_area_get_next_y (parent) -
			  fo_area_area_get_height (area));
      fo_area_set_available_height (area,
				    fo_area_area_get_height (area));
      fo_area_set_available_width (area,
				   fo_area_get_child_available_ipdim (parent));
    }
  else
    {
#if defined(LIBFO_DEBUG) && 1
      g_message ("set_or_split:: splitting:: child: %s; generated by: %s",
		 fo_object_debug_sprintf (area) ,
		 fo_object_debug_sprintf (area->generated_by));
#endif
      area = fo_area_split_before_height (area,
					  child_available_bpdim -
					  fo_area_area_get_height (parent));
      parent = fo_area_parent (area);
      child_available_bpdim = fo_area_get_child_available_bpdim (parent);
    }
}

/**
 * fo_area_size_request_default:
 * @child: Child area
 * 
 * Check that the parent area of @child has sufficient space for
 * @child.  If not enough space, request that the parent has
 * sufficient space allocated for it, then adjust @child and its
 * siblings as necessary to fit into the resized parent area.
 * 
 * Return value: Pointer to the last area generated from @child after
 * any reallocation and resizing
 **/
FoArea*
fo_area_size_request_default (FoArea *child)
{
  FoArea *parent;
  FoArea *child_original_next_part;
  FoArea *return_child;
  gfloat total_child_height = 0;
  gfloat child_available_ipdim;
  gfloat child_available_bpdim;
  gfloat child_height;
  gfloat child_space_before, child_space_after;

  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (child), NULL);
  g_return_val_if_fail (!FO_AREA_IS_ROOT (child), NULL);
  g_return_val_if_fail (FO_IS_AREA_AREA (fo_area_parent (child)), NULL);

  child_original_next_part = child->next_part;

  child_height = fo_area_area_get_height (child);
  child_space_before = fo_area_area_get_space_before (child);
  child_space_after = fo_area_area_get_space_after (child);

  parent = fo_area_parent (child);
  child_available_bpdim = fo_area_get_child_available_bpdim (parent);

#if defined(LIBFO_DEBUG) && 1
  g_message ("size_request_default (%p):: parent: %s; generated by: %s; available_height: %g",
	     child,
	     fo_object_debug_sprintf (parent),
	     fo_object_debug_sprintf (parent->generated_by),
	     child_available_bpdim);
  g_message ("size_request_default (%p):: child: %s; generated by: %s; height: %g; space_before: %g; space_after: %g",
	     child,
	     fo_object_debug_sprintf (child),
	     fo_object_debug_sprintf (child->generated_by),
	     child_height,
	     child_space_before,
	     child_space_after);
#endif

  fo_area_children_foreach (parent,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    &total_child_height);
#if defined(LIBFO_DEBUG) && 1
  g_message ("size_request_default (%p):: child total: %g",
	     child,
	     total_child_height);
#endif

  fo_area_area_set_height (parent,
			   total_child_height +
			   fo_area_area_get_border_before (parent) +
			   fo_area_area_get_padding_before (parent) +
			   fo_area_area_get_padding_after (parent) +
			   fo_area_area_get_border_after (parent));

  /* Don't bother doing a size_request if still fit within
     available height */
  if (child_available_bpdim < fo_area_area_get_height (parent))
    {
      parent = fo_area_size_request (parent);
      child_available_ipdim =
	MAX (fo_area_get_available_width (parent) -
	     fo_area_area_get_border_start (parent) -
	     fo_area_area_get_padding_start (parent) -
	     fo_area_area_get_padding_end (parent) -
	     fo_area_area_get_border_end (parent),
	     0);
      fo_area_set_child_available_ipdim (parent, child_available_ipdim);
      child_available_bpdim =
	MAX (fo_area_get_available_height (parent) -
	     fo_area_area_get_border_before (parent) -
	     fo_area_area_get_padding_before (parent) -
	     fo_area_area_get_padding_after (parent) -
	     fo_area_area_get_border_after (parent),
	     0);
      fo_area_set_child_available_bpdim (parent, child_available_bpdim);
#if defined(LIBFO_DEBUG) && 1
      g_message ("size_request_default:: child: %s; new parent: %s; generated by: %s; available_height: %g; child_available_ipdim: %g; child_available_bpdim: %g",
		 fo_object_debug_sprintf (child),
		 fo_object_debug_sprintf (parent),
		 fo_object_debug_sprintf (parent->generated_by),
		 fo_area_get_available_height (parent),
		 child_available_ipdim,
		 child_available_bpdim);
#endif
  }

  total_child_height = 0;
  fo_area_children_foreach (parent,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    &total_child_height);
#if defined(LIBFO_DEBUG) && 1
  g_message ("size_request_default (%p):: new child total: %g",
	     child,
	     total_child_height);
#endif
  fo_area_set_next_x (parent,
		      fo_area_area_get_border_start (parent) +
		      fo_area_area_get_padding_start (parent));
  fo_area_set_next_y (parent,
		      - (fo_area_area_get_border_before (parent) +
			 fo_area_area_get_padding_before (parent)));

  if (total_child_height <= child_available_bpdim)
    {
      fo_area_children_foreach (parent,
				G_TRAVERSE_ALL,
				&fo_area_size_adjust,
				NULL);

#if defined(LIBFO_DEBUG) && 1
      g_message ("size_request_default (%p):: return:: parent->last: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_last_child (parent)),
		 fo_object_debug_sprintf (fo_area_last_child (parent)->generated_by));
#endif
      return_child = child;

      while ((return_child->next_part != NULL) &&
	     (return_child->next_part != child_original_next_part))
	{
	  return_child = return_child->next_part;
	}

      return return_child;
      /*
      return fo_area_last_child (parent);
      */
    }
  else
    {
      fo_area_children_foreach (parent,
				G_TRAVERSE_ALL,
				&fo_area_set_or_split,
				NULL);
#if defined(LIBFO_DEBUG) && 1
      g_message ("size_request_default (%p):: total > available:: return:: parent->last: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_last_child (parent)),
		 fo_object_debug_sprintf (fo_area_last_child (parent)->generated_by));
#endif
      return_child = child;

      while ((return_child->next_part != NULL) &&
	     (return_child->next_part != child_original_next_part))
	{
	  return_child = return_child->next_part;
	}

      return return_child;
      /*
      return fo_area_last_child (parent);
      */
    }
}

/**
 * fo_area_update_child_after_insert:
 * @parent: 
 * @child: 
 * 
 * 
 **/
static void
fo_area_update_child_after_insert (FoArea *parent,
				   FoArea *child)
{
  g_return_if_fail (FO_IS_AREA (parent));
  g_return_if_fail (FO_IS_AREA (child));

  if (!FO_IS_AREA_PAGE (child))
    {
      child->page = parent->page;
    }

  if (!FO_IS_AREA_REFERENCE (child))
    {
      child->reference = parent->reference;
    }
}

/**
 * fo_area_node_insert:
 * @parent: 
 * @position: 
 * @area: 
 * 
 * 
 * 
 * Return value: 
 **/
FoNode*
fo_area_node_insert (FoNode *parent,
		     gint    position,
		     FoNode *area)
{
  return ((FoNode *) fo_area_insert (((FoArea *) parent),
				     position,
				     ((FoArea *) area)));
}

/**
 * fo_area_insert:
 * @parent: 
 * @position: 
 * @area: 
 * 
 * 
 * 
 * Return value: 
 **/
FoArea*
fo_area_insert (FoArea *parent,
		gint    position,
		FoArea *area)
{
  FoArea *new_area;

  g_return_val_if_fail (FO_IS_AREA (parent), area);
  g_return_val_if_fail (FO_IS_AREA (area), area);

  new_area =
    FO_AREA (FO_NODE_CLASS (parent_class)->insert (FO_NODE (parent),
						   position,
						   FO_NODE (area)));

  fo_area_update_child_after_insert (parent, new_area);

  return new_area;
}

/**
 * fo_area_node_insert_before:
 * @parent: 
 * @sibling: 
 * @area: 
 * 
 * 
 * 
 * Return value: 
 **/
FoNode*
fo_area_node_insert_before (FoNode *parent,
			    FoNode *sibling,
			    FoNode *area)
{
  return ((FoNode *) fo_area_insert_before (((FoArea *) parent),
					    ((FoArea *) sibling),
					    ((FoArea *) area)));
}

/**
 * fo_area_insert_before:
 * @parent: 
 * @sibling: 
 * @area: 
 * 
 * 
 * 
 * Return value: 
 **/
FoArea*
fo_area_insert_before (FoArea *parent,
		       FoArea *sibling,
		       FoArea *area)
{
  FoArea *new_area;

  g_return_val_if_fail (FO_IS_AREA (parent), area);
  g_return_val_if_fail (FO_IS_AREA (sibling), area);
  g_return_val_if_fail (FO_IS_AREA (area), area);

  new_area =
    FO_AREA (FO_NODE_CLASS (parent_class)->insert_before (FO_NODE (parent),
							  FO_NODE (sibling),
							  FO_NODE (area)));

  fo_area_update_child_after_insert (parent, new_area);

  return new_area;
}

/**
 * fo_area_node_insert_after:
 * @parent: 
 * @sibling: 
 * @area: 
 * 
 * 
 * 
 * Return value: 
 **/
FoNode*
fo_area_node_insert_after (FoNode *parent,
			   FoNode *sibling,
			   FoNode *area)
{
  return ((FoNode *) fo_area_insert_after (((FoArea *) parent),
					   ((FoArea *) sibling),
					   ((FoArea *) area)));
}

/**
 * fo_area_insert_after:
 * @parent: 
 * @sibling: 
 * @area: 
 * 
 * 
 * 
 * Return value: 
 **/
FoArea*
fo_area_insert_after (FoArea *parent,
		      FoArea *sibling,
		      FoArea *area)
{
  FoArea *new_area;

  g_return_val_if_fail (FO_IS_AREA (parent), area);
  g_return_val_if_fail (FO_IS_AREA (sibling), area);
  g_return_val_if_fail (FO_IS_AREA (area), area);

  new_area =
    FO_AREA (FO_NODE_CLASS (parent_class)->insert_after (FO_NODE (parent),
							 FO_NODE (sibling),
							 FO_NODE (area)));

  fo_area_update_child_after_insert (parent, new_area);

  return new_area;
}
/**
 * fo_area_node_prepend:
 * @parent: the #FoNode to place the new #FoNode under.
 * @area: the #FoNode to insert.
 * 
 * Inserts a #FoNode as the first child of the given parent.
 * 
 * Return value: the inserted #FoNode.
 **/
 
FoNode*
fo_area_node_prepend (FoNode *parent,
		      FoNode *area)
{
  return ((FoNode *) fo_area_prepend (((FoArea *) parent),
				      ((FoArea *) area)));
}

/**
 * fo_area_prepend:
 * @parent: the #FoArea to place the new #FoArea under.
 * @area: the #FoArea to insert.
 * 
 * Inserts a #FoArea as the first child of the given parent and
 * updates the inserted #FoArea.
 * 
 * Return value: the inserted #FoArea.
 **/
FoArea*
fo_area_prepend (FoArea *parent,
		 FoArea *area)
{
  FoArea *new_area;

  g_return_val_if_fail (FO_IS_AREA (parent), area);
  g_return_val_if_fail (FO_IS_AREA (area), area);

  new_area =
    FO_AREA (FO_NODE_CLASS (parent_class)->prepend (FO_NODE (parent),
						    FO_NODE (area)));

  fo_area_update_child_after_insert (parent, new_area);

  return new_area;
}

/**
 * fo_area_node_append:
 * @parent: the #FoNode to place the new #FoNode under.
 * @area: the #FoNode to insert.
 * 
 * Inserts a #FoNode as the last child of the given parent.
 * 
 * Return value: the inserted #FoNode.
 **/
FoNode*
fo_area_node_append (FoNode *parent,
		     FoNode *area)
{
  return ((FoNode *) fo_area_append (((FoArea *) parent),
				      ((FoArea *) area)));
}

/**
 * fo_area_append:
 * @parent: the #FoArea to place the new #FoArea under.
 * @area: the #FoArea to insert.
 * 
 * Inserts a #FoArea as the last child of the given parent and updates
 * the inserted #FoArea.
 * 
 * Return value: the inserted #FoArea.
 **/
FoArea*
fo_area_append (FoArea *parent,
		FoArea *area)
{
  FoArea *new_area;

  g_return_val_if_fail (FO_IS_AREA (parent), area);
  g_return_val_if_fail (FO_IS_AREA (area), area);

  new_area =
    FO_AREA (FO_NODE_CLASS (parent_class)->append (FO_NODE (parent),
						   FO_NODE (area)));

  fo_area_update_child_after_insert (parent, new_area);

  return new_area;
}

/**
 * fo_area_n_areas:
 * @root: a #FoArea.
 * @flags: which types of children are to be counted, one of
 *         %G_TRAVERSE_ALL, %G_TRAVERSE_LEAFS and
 *         %G_TRAVERSE_NON_LEAFS.
 * 
 * Gets the number of nodes in a tree.
 * 
 * Return value: the number of nodes in the tree.
 **/
guint
fo_area_n_areas (FoArea *root,
		 GTraverseFlags flags)
{
  return fo_node_n_nodes (FO_NODE (root),
			  flags);
}

/**
 * fo_area_get_root:
 * @area: 
 * 
 * 
 * 
 * Return value: 
 **/
FoArea*
fo_area_get_root (FoArea *area)
{
  return FO_AREA (fo_node_get_root (FO_NODE (area)));
}

/**
 * fo_area_is_ancestor:
 * @area: 
 * @descendant: 
 * 
 * 
 * 
 * Return value: 
 **/
gboolean
fo_area_is_ancestor (FoArea *area,
		     FoArea *descendant)
{
  return fo_node_is_ancestor (FO_NODE (area),
			      FO_NODE (descendant));
}

/**
 * fo_area_depth:
 * @area: a #FoArea.
 * 
 * Gets the depth of a #FoArea.
 *
 * If @area is %NULL the depth is 0. The root node has a depth of 1. For
 * the children of the root node the depth is 2. And so on.
 * 
 * Return value: the depth of the #FoArea.
 **/
guint
fo_area_depth (FoArea *area)
{
  return fo_node_depth (((FoNode *) area));
}

typedef struct _FoAreaFuncData
{
  FoAreaForeachFunc func;
  gpointer area_func_data;
} FoAreaFuncData;

#if 0
static void
fo_area_g_node_children_foreach_func (GNode    *node,
				      gpointer  data)
{
  const FoAreaFuncData *fo_area_func_data = (FoAreaFuncData *) data;

  fo_area_func_data->func (node->data,
			   fo_area_func_data->area_func_data);
}
#endif

/**
 * fo_area_children_foreach:
 * @area: a #FoArea.
 * @flags: which types of children are to be visited, one of
 *         %G_TRAVERSE_ALL, %G_TRAVERSE_LEAFS and
 *         %G_TRAVERSE_NON_LEAFS.
 * @func: the function to call for each visited node.
 * @data: user data to pass to the function.
 * 
 * Calls a function for each of the children of a #FoArea. Note that
 * it doesn't descend beneath the child nodes.
 **/
void
fo_area_children_foreach (FoArea 	    *area,
			  GTraverseFlags     flags,
			  FoAreaForeachFunc  func,
			  gpointer           data)
{
  fo_node_children_foreach (((FoNode *) area),
			    flags,
			    (FoNodeForeachFunc) func,
			    data);
}

/**
 * fo_area_reverse_children:
 * @area: a #FoArea.
 * 
 * Reverses the order of the children of a #FoArea. (It doesn't change
 * the order of the grandchildren.)
 **/
void
fo_area_reverse_children (FoArea *area)
{
  fo_node_reverse_children (((FoNode *) area));
}

/**
 * fo_area_n_children:
 * @area: a #FoArea.
 * 
 * Gets the number of children of a #FoArea.
 * 
 * Return value: the number of children of @area.
 **/
guint
fo_area_n_children (FoArea *area)
{
  return fo_node_n_children (((FoNode *) area));
}

/**
 * fo_area_nth_child:
 * @area: a #FoArea.
 * @n: the index of the desired child.
 * 
 * Gets a child of a #FoArea, using the given index. The first child
 * is at index 0. If the index is too big, %NULL is returned.
 * 
 * Return value: the child of @area at index @n.
 **/
FoArea*
fo_area_nth_child (FoArea *area,
		   guint   n)
{
  return ((FoArea *) fo_node_nth_child (((FoNode *) area), n));
}

/**
 * fo_area_last_child:
 * @area: a #FoArea (nust not be %NULL).
 * 
 * Gets the last child of a #FoArea.
 * 
 * Return value: the last child of @area, or %NULL if @area has no
 * children.
 **/
FoArea*
fo_area_last_child (FoArea *area)
{
  return ((FoArea *) fo_node_last_child (((FoNode *) area)));
}

/**
 * fo_area_child_position:
 * @area: a #FoArea.
 * @child: a child of @area.
 * 
 * Gets the position of a #FoArea with respect to its siblings. @child
 * must be a child of @area. The first child is numbered 0, the second
 * 1, and so on.
 * 
 * Return value: the position of @child with respect to its siblings.
 **/
guint
fo_area_child_position (FoArea *area,
			FoArea *child)
{
  return fo_node_child_position (((FoNode *) area),
				 ((FoNode *) child));
}

/**
 * fo_area_first_sibling:
 * @area: a #FoArea.
 * 
 * Gets the first sibling of a #FoArea. This could possibly be the
 * node itself.
 * 
 * Return value: the first sibling of @area.
 **/
FoArea*
fo_area_first_sibling (FoArea *area)
{
  return ((FoArea *) fo_node_first_sibling ((FoNode *) area));
}

/**
 * fo_area_last_sibling:
 * @area: a #FoArea.
 * 
 * Gets the last sibling of a #FoArea. This could possibly be the node
 * itself.
 * 
 * Return value: the last sibling of @area.
 **/
FoArea*
fo_area_last_sibling (FoArea *area)
{
  return ((FoArea *) fo_node_last_sibling (((FoNode *) area)));
}

/**
 * fo_area_prev_sibling:
 * @area: a #FoArea.
 * 
 * Gets the previous sibling of a #FoArea.
 * 
 * Return value: the previous sibling of @area, or %NULL if @area is
 * %NULL.
 **/
FoArea*
fo_area_prev_sibling (FoArea *area)
{
  return ((FoArea *) fo_node_prev_sibling (((FoNode *) area)));
}

/**
 * fo_area_next_sibling:
 * @area: a #FoArea.
 * 
 * Gets the next sibling of a #FoArea.
 * 
 * Return value: the next sibling of @area, or %NULL if @area is %NULL.
 **/
FoArea*
fo_area_next_sibling (FoArea *area)
{
  return ((FoArea *) fo_node_next_sibling (((FoNode *) area)));
}

/**
 * fo_area_first_child:
 * @area: A #FoArea.
 * 
 * Gets the first child of a #FoArea.
 * 
 * Return value: the first child of @area, or %NULL if @area is %NULL or
 * has no children.
 **/
FoArea*
fo_area_first_child (FoArea *area)
{
  return ((FoArea *) fo_node_first_child (((FoNode *) area)));
}

/**
 * fo_area_parent:
 * @area: a #FoArea.
 * 
 * Gets the parent of a #FoArea.
 * 
 * Return value: the parent of @area, or %NULL if @area is the root of
 * the tree.
 **/
FoArea*
fo_area_parent (FoArea *area)
{
  return ((FoArea *) fo_node_parent (((FoNode *) area)));
}

/**
 * fo_area_unlink:
 * @area: the #FoArea to unlink, which becomes the root of a new tree.
 * 
 * Unlinks an #FoArea from an #FoArea tree, resulting in two separate
 * trees.
 **/
void
fo_area_unlink (FoArea *area)
{
  fo_node_unlink (((FoNode *) area));
}

/**
 * fo_area_max_height:
 * @root: Root node of a #FoArea tree.
 * 
 * Gets the maximum height of all branches beneath a #FoArea. This is
 * the maximum distance from the #FoArea to all leaf nodes.
 *
 * If @root is %NULL, 0 is returned. If @root has no children, 1 is
 * returned. If @root has children, 2 is returned. And so on.
 * 
 * Return value: the maximum height of the tree beneath @root.
 **/
guint
fo_area_max_height (FoArea *root)
{
  return fo_node_max_height (((FoNode *) root));
}

typedef struct _FoAreaTraverseFuncData
{
  FoAreaTraverseFunc func;
  gpointer area_func_data;
} FoAreaTraverseFuncData;

/**
 * fo_area_traverse:
 * @root: 
 * @order: 
 * @flags: 
 * @max_depth: 
 * @func: 
 * @data: 
 * 
 * 
 **/
void
fo_area_traverse (FoArea 	     *root,
		  GTraverseType       order,
		  GTraverseFlags      flags,
		  gint                max_depth,
		  FoAreaTraverseFunc  func,
		  gpointer            data)
{
  fo_node_traverse (((FoNode *) root),
		    order,
		    flags,
		    max_depth,
		    (FoNodeTraverseFunc) func,
		    data);
}

/**
 * fo_area_node_unlink_with_next_siblings:
 * @area: First #FoNode to unlink.
 * 
 * Unlinks @area and its following siblings.
 *
 * #FoArea implementation of fo_node_unlink_with_next_siblings().
 **/
void
fo_area_node_unlink_with_next_siblings (FoNode *area)
{
  fo_area_unlink_with_next_siblings (((FoArea *) area));
}

/**
 * fo_area_unlink_with_next_siblings:
 * @area: First #FoArea to unlink.
 * 
 * Unlinks @area and its following siblings.
 **/
void
fo_area_unlink_with_next_siblings (FoArea *area)
{
  FO_NODE_CLASS (parent_class)->unlink_with_next_siblings (((FoNode *) area));
}

/**
 * fo_area_node_insert_with_next_siblings:
 * @parent:   #FoNode to be parent of @area and its siblings.
 * @position: Offset at which to insert @area and its siblings.
 * @area:     #FoNode, possibly with following siblings.
 * 
 * Implements fo_node_insert_with_next_siblings for #FoArea.
 * 
 * Return value: @parent with @area and siblings inserted.
 **/
FoNode*
fo_area_node_insert_with_next_siblings (FoNode *parent,
					gint    position,
					FoNode *area)
{
  return ((FoNode *) fo_area_insert_with_next_siblings (((FoArea *) parent),
							position,
							((FoArea *) area)));
}

/**
 * fo_area_insert_with_next_siblings:
 * @parent:   #FoArea to be parent of @area and its siblings.
 * @position: Offset at which to insert @area and its siblings.
 * @area:     #FoArea, possibly with following siblings.
 * 
 * Implements fo_node_insert_with_next_siblings for #FoArea.
 * 
 * Return value: @parent with @area and siblings inserted.
 **/
FoArea*
fo_area_insert_with_next_siblings (FoArea *parent,
				   gint    position,
				   FoArea *area)
{
  return FO_AREA (FO_NODE_CLASS (parent_class)->insert_with_next_siblings (FO_NODE (parent),
									   position,
									   FO_NODE (area)));
}
