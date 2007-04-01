/* Fo
 * fo-area-page.c: Page area object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-page.c,v 1.8 2005/11/10 14:45:32 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-area.h"
#include "fo-area-viewport-reference-private.h"
#include "fo-area-page.h"
#include "fo-page-sequence-area.h"

const char *fo_area_page_error_messages[] = {
  N_("Failed"),
  N_("Warning"),
  N_("Child area overflows parent area")
};

enum {
  PROP_0,
  PROP_PAGE_NUMBER,
  PROP_PAGE_WIDTH,
  PROP_PAGE_HEIGHT,
  PROP_MARGIN_TOP,
  PROP_MARGIN_BOTTOM,
  PROP_MARGIN_LEFT,
  PROP_MARGIN_RIGHT
};

struct _FoAreaPage
{
  FoAreaViewportReference parent_instance;

  gint page_number;

  /* Temporary properties */
  /* All of these should be obtainable by referencing page master */
  gfloat page_height;
  gfloat page_width;
  gfloat margin_top;
  gfloat margin_bottom;
  gfloat margin_left;
  gfloat margin_right;
};

struct _FoAreaPageClass
{
  FoAreaViewportReferenceClass parent_class;
};

static void fo_area_page_class_init  (FoAreaPageClass *klass);
static void fo_area_page_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_area_page_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_area_page_finalize    (GObject           *object);

static void fo_area_page_debug_dump_properties (FoArea *area,
						gint depth);
static FoArea* fo_area_page_clone (FoArea *original);
static FoArea* fo_area_page_add_child (FoArea *parent, FoArea *child);
static FoArea* fo_area_page_size_request (FoArea *child);

static gpointer parent_class;

/**
 * fo_area_page_get_type:
 * @void: 
 * 
 * Register the FoAreaPage object type.
 * 
 * Return value: GType value of the FoAreaPage object type.
 **/
GType
fo_area_page_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaPageClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_page_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaPage),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_VIEWPORT_REFERENCE,
                                            "FoAreaPage",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_page_class_init:
 * @klass: FoAreaPageClass object to initialise
 * 
 * Implements GClassInitFunc for FoAreaPageClass
 **/
void
fo_area_page_class_init (FoAreaPageClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_page_finalize;

  object_class->set_property = fo_area_page_set_property;
  object_class->get_property = fo_area_page_get_property;

  FO_AREA_CLASS (klass)->debug_dump_properties = fo_area_page_debug_dump_properties;
  FO_AREA_CLASS (klass)->add_child = fo_area_page_add_child;
  FO_AREA_CLASS (klass)->size_request = fo_area_page_size_request;
  FO_AREA_CLASS (klass)->clone = fo_area_page_clone;

  g_object_class_install_property
    (object_class,
     PROP_PAGE_NUMBER,
     g_param_spec_int ("page-number",
		       _("Page number"),
		       _("Page number property"),
		       0,
		       G_MAXINT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_PAGE_WIDTH,
     g_param_spec_float ("page-width",
		       _("Page width"),
		       _("Page width property"),
		       -G_MAXFLOAT,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_PAGE_HEIGHT,
     g_param_spec_float ("page-height",
		       _("Page height"),
		       _("Page height property"),
		       -G_MAXFLOAT,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_TOP,
     g_param_spec_float ("margin-top",
		       _("Margin top"),
		       _("Margin top property"),
		       -G_MAXFLOAT,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_BOTTOM,
     g_param_spec_float ("margin-bottom",
		       _("Margin bottom"),
		       _("Margin bottom property"),
		       -G_MAXFLOAT,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_LEFT,
     g_param_spec_float ("margin-left",
		       _("Margin left"),
		       _("Margin left property"),
		       -G_MAXFLOAT,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_RIGHT,
     g_param_spec_float ("margin-right",
		       _("Margin right"),
		       _("Margin right property"),
		       -G_MAXFLOAT,
		       G_MAXFLOAT,
		       0,
		       G_PARAM_READWRITE));
}

/**
 * fo_area_page_finalize:
 * @object: FoAreaPage object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoAreaPage
 **/
void
fo_area_page_finalize (GObject *object)
{
  FoAreaPage *fo_area_page;

  fo_area_page = FO_AREA_PAGE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_area_page_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoAreaPage
 **/
void
fo_area_page_set_property (GObject         *object,
			   guint            prop_id,
			   const GValue    *value,
			   GParamSpec      *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_PAGE_NUMBER:
      fo_area_page_set_page_number (fo_area, g_value_get_int (value));
      break;
    case PROP_PAGE_WIDTH:
      fo_area_page_set_page_width (fo_area, g_value_get_float (value));
      break;
    case PROP_PAGE_HEIGHT:
      fo_area_page_set_page_height (fo_area, g_value_get_float (value));
      break;
    case PROP_MARGIN_TOP:
      fo_area_page_set_margin_top (fo_area, g_value_get_float (value));
      break;
    case PROP_MARGIN_BOTTOM:
      fo_area_page_set_margin_bottom (fo_area, g_value_get_float (value));
      break;
    case PROP_MARGIN_LEFT:
      fo_area_page_set_margin_left (fo_area, g_value_get_float (value));
      break;
    case PROP_MARGIN_RIGHT:
      fo_area_page_set_margin_right (fo_area, g_value_get_float (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_area_page_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoAreaPage
 **/
void
fo_area_page_get_property (GObject         *object,
			   guint            prop_id,
			   GValue          *value,
			   GParamSpec      *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_PAGE_NUMBER:
      g_value_set_int (value, fo_area_page_get_page_number (fo_area));
      break;
    case PROP_PAGE_WIDTH:
      g_value_set_float (value, fo_area_page_get_page_width (fo_area));
      break;
    case PROP_PAGE_HEIGHT:
      g_value_set_float (value, fo_area_page_get_page_height (fo_area));
      break;
    case PROP_MARGIN_TOP:
      g_value_set_float (value, fo_area_page_get_margin_top (fo_area));
      break;
    case PROP_MARGIN_BOTTOM:
      g_value_set_float (value, fo_area_page_get_margin_bottom (fo_area));
      break;
    case PROP_MARGIN_LEFT:
      g_value_set_float (value, fo_area_page_get_margin_left (fo_area));
      break;
    case PROP_MARGIN_RIGHT:
      g_value_set_float (value, fo_area_page_get_margin_right (fo_area));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_area_page_new:
 * 
 * Creates a new #FoAreaPage initialized to default value.
 * 
 * Return value: the new #FoAreaPage
 **/
FoArea*
fo_area_page_new (void)
{
  return FO_AREA (g_object_new (fo_area_page_get_type (), NULL));
}


/**
 * fo_area_page_set_page_number:
 * @fo_area_page: The @FoAreaPage object
 * @new_page_number: The new "page-number" property value
 * 
 * Sets the #page_number property of @area_page to @new_page_number
**/
void
fo_area_page_set_page_number (FoArea *fo_area_page,
			      gint new_page_number)
{
  g_return_if_fail (fo_area_page != NULL);
  g_return_if_fail (FO_IS_AREA_PAGE (fo_area_page));

  FO_AREA_PAGE (fo_area_page)->page_number = new_page_number;
  /*g_object_notify (G_OBJECT (fo_area_page), "page-number");*/
}

/**
 * fo_area_page_get_page_number:
 * @fo_area_page: The @FoAreaPage object
 *
 * Gets the #page_number property of @area_page
 *
 * Return value: The "page-number" property value
**/
gint
fo_area_page_get_page_number (FoArea *fo_area_page)
{
  g_return_val_if_fail (fo_area_page != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_page), 0);

  return FO_AREA_PAGE (fo_area_page)->page_number;
}

/**
 * fo_area_page_set_page_width:
 * @fo_area_page: The @FoAreaPage object
 * @new_page_width: The new "page-width" property value
 * 
 * Sets the #page_width property of @area_page to @new_page_width
**/
void
fo_area_page_set_page_width (FoArea *fo_area_page,
		         gfloat new_page_width)
{
  g_return_if_fail (fo_area_page != NULL);
  g_return_if_fail (FO_IS_AREA_PAGE (fo_area_page));

  FO_AREA_PAGE (fo_area_page)->page_width = new_page_width;

  fo_area_set_available_width (fo_area_page,
			       MAX (FO_AREA_PAGE (fo_area_page)->page_width -
				    FO_AREA_PAGE (fo_area_page)->margin_left -
				    FO_AREA_PAGE (fo_area_page)->margin_right,
				    0));
  fo_area_set_child_available_ipdim (fo_area_page,
				     MAX (FO_AREA_PAGE (fo_area_page)->page_width -
					  FO_AREA_PAGE (fo_area_page)->margin_left -
					  FO_AREA_PAGE (fo_area_page)->margin_right,
					  0));

  /*g_object_notify (G_OBJECT (fo_area_page), "page-width");*/
}

/**
 * fo_area_page_get_page_width:
 * @fo_area_page: The @FoAreaPage object
 *
 * Gets the #page_width property of @area_page
 *
 * Return value: The "page-width" property value
**/
gfloat
fo_area_page_get_page_width (FoArea *fo_area_page)
{
  g_return_val_if_fail (fo_area_page != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_page), 0);

  return FO_AREA_PAGE (fo_area_page)->page_width;
}

/**
 * fo_area_page_set_page_height:
 * @fo_area_page: The @FoAreaPage object
 * @new_page_height: The new "page-height" property value
 * 
 * Sets the "page_height" property of @area_page to @new_page_height
**/
void
fo_area_page_set_page_height (FoArea *fo_area_page,
			      gfloat new_page_height)
{
  g_return_if_fail (fo_area_page != NULL);
  g_return_if_fail (FO_IS_AREA_PAGE (fo_area_page));

  FO_AREA_PAGE (fo_area_page)->page_height = new_page_height;
  fo_area_set_available_height (fo_area_page,
				MAX (new_page_height -
				     FO_AREA_PAGE (fo_area_page)->margin_top -
				     FO_AREA_PAGE (fo_area_page)->margin_bottom,
				     0));
  fo_area_set_child_available_bpdim (fo_area_page,
				     MAX (new_page_height -
					  FO_AREA_PAGE (fo_area_page)->margin_top -
					  FO_AREA_PAGE (fo_area_page)->margin_bottom,
					  0));
  /*g_object_notify (G_OBJECT (fo_area_page), "page-height");*/
}

/**
 * fo_area_page_get_page_height:
 * @fo_area_page: The @FoAreaPage object
 *
 * Gets the #page_height property of @area_page
 *
 * Return value: The "page-height" property value
**/
gfloat
fo_area_page_get_page_height (FoArea *fo_area_page)
{
  g_return_val_if_fail (fo_area_page != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_page), 0);

  return FO_AREA_PAGE (fo_area_page)->page_height;
}

/**
 * fo_area_page_set_margin_top:
 * @fo_area_page: The @FoAreaPage object
 * @new_margin_top: The new "margin-top" property value
 * 
 * Sets the #margin_top property of @area_page to @new_margin_top
**/
void
fo_area_page_set_margin_top (FoArea *fo_area_page,
		         gfloat new_margin_top)
{
  g_return_if_fail (fo_area_page != NULL);
  g_return_if_fail (FO_IS_AREA_PAGE (fo_area_page));

  FO_AREA_PAGE (fo_area_page)->margin_top = new_margin_top;

  fo_area_set_available_height (fo_area_page,
				MAX (FO_AREA_PAGE (fo_area_page)->page_height -
				     FO_AREA_PAGE (fo_area_page)->margin_top -
				     FO_AREA_PAGE (fo_area_page)->margin_bottom,
				     0));
  fo_area_set_child_available_bpdim (fo_area_page,
				     MAX (FO_AREA_PAGE (fo_area_page)->page_height -
					  FO_AREA_PAGE (fo_area_page)->margin_top -
					  FO_AREA_PAGE (fo_area_page)->margin_bottom,
					  0));

  /*g_object_notify (G_OBJECT (fo_area_page), "margin-top");*/
}

/**
 * fo_area_page_get_margin_top:
 * @fo_area_page: The @FoAreaPage object
 *
 * Gets the #margin_top property of @area_page
 *
 * Return value: The "margin-top" property value
**/
gfloat
fo_area_page_get_margin_top (FoArea *fo_area_page)
{
  g_return_val_if_fail (fo_area_page != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_page), 0);

  return FO_AREA_PAGE (fo_area_page)->margin_top;
}

/**
 * fo_area_page_set_margin_bottom:
 * @fo_area_page: The @FoAreaPage object
 * @new_margin_bottom: The new "margin-bottom" property value
 * 
 * Sets the #margin_bottom property of @area_page to @new_margin_bottom
**/
void
fo_area_page_set_margin_bottom (FoArea *fo_area_page,
		         gfloat new_margin_bottom)
{
  g_return_if_fail (fo_area_page != NULL);
  g_return_if_fail (FO_IS_AREA_PAGE (fo_area_page));

  FO_AREA_PAGE (fo_area_page)->margin_bottom = new_margin_bottom;

  fo_area_set_available_height (fo_area_page,
				MAX (FO_AREA_PAGE (fo_area_page)->page_height -
				     FO_AREA_PAGE (fo_area_page)->margin_top -
				     FO_AREA_PAGE (fo_area_page)->margin_bottom,
				     0));
  fo_area_set_child_available_bpdim (fo_area_page,
				     MAX (FO_AREA_PAGE (fo_area_page)->page_height -
					  FO_AREA_PAGE (fo_area_page)->margin_top -
					  FO_AREA_PAGE (fo_area_page)->margin_bottom,
					  0));

  /*g_object_notify (G_OBJECT (fo_area_page), "margin-bottom");*/
}

/**
 * fo_area_page_get_margin_bottom:
 * @fo_area_page: The @FoAreaPage object
 *
 * Gets the #margin_bottom property of @area_page
 *
 * Return value: The "margin-bottom" property value
**/
gfloat
fo_area_page_get_margin_bottom (FoArea *fo_area_page)
{
  g_return_val_if_fail (fo_area_page != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_page), 0);

  return FO_AREA_PAGE (fo_area_page)->margin_bottom;
}

/**
 * fo_area_page_set_margin_left:
 * @fo_area_page: The @FoAreaPage object
 * @new_margin_left: The new "margin-left" property value
 * 
 * Sets the #margin_left property of @area_page to @new_margin_left
**/
void
fo_area_page_set_margin_left (FoArea *fo_area_page,
		         gfloat new_margin_left)
{
  g_return_if_fail (fo_area_page != NULL);
  g_return_if_fail (FO_IS_AREA_PAGE (fo_area_page));

  FO_AREA_PAGE (fo_area_page)->margin_left = new_margin_left;

  fo_area_set_available_width (fo_area_page,
			       MAX (FO_AREA_PAGE (fo_area_page)->page_width -
				    FO_AREA_PAGE (fo_area_page)->margin_left -
				    FO_AREA_PAGE (fo_area_page)->margin_right,
				    0));
  fo_area_set_child_available_ipdim (fo_area_page,
				     MAX (FO_AREA_PAGE (fo_area_page)->page_width -
					  FO_AREA_PAGE (fo_area_page)->margin_left -
					  FO_AREA_PAGE (fo_area_page)->margin_right,
					  0));

  /*g_object_notify (G_OBJECT (fo_area_page), "margin-left");*/
}

/**
 * fo_area_page_get_margin_left:
 * @fo_area_page: The @FoAreaPage object
 *
 * Gets the #margin_left property of @area_page
 *
 * Return value: The "margin-left" property value
**/
gfloat
fo_area_page_get_margin_left (FoArea *fo_area_page)
{
  g_return_val_if_fail (fo_area_page != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_page), 0);

  return FO_AREA_PAGE (fo_area_page)->margin_left;
}

/**
 * fo_area_page_set_margin_right:
 * @fo_area_page: The @FoAreaPage object
 * @new_margin_right: The new "margin-right" property value
 * 
 * Sets the #margin_right property of @area_page to @new_margin_right
**/
void
fo_area_page_set_margin_right (FoArea *fo_area_page,
		         gfloat new_margin_right)
{
  g_return_if_fail (fo_area_page != NULL);
  g_return_if_fail (FO_IS_AREA_PAGE (fo_area_page));

  FO_AREA_PAGE (fo_area_page)->margin_right = new_margin_right;

  fo_area_set_available_width (fo_area_page,
			       MAX (FO_AREA_PAGE (fo_area_page)->page_width -
				    FO_AREA_PAGE (fo_area_page)->margin_left -
				    FO_AREA_PAGE (fo_area_page)->margin_right,
				    0));
  fo_area_set_child_available_ipdim (fo_area_page,
				     MAX (FO_AREA_PAGE (fo_area_page)->page_width -
					  FO_AREA_PAGE (fo_area_page)->margin_left -
					  FO_AREA_PAGE (fo_area_page)->margin_right,
					  0));

  /*g_object_notify (G_OBJECT (fo_area_page), "margin-right");*/
}

/**
 * fo_area_page_get_margin_right:
 * @fo_area_page: The @FoAreaPage object
 *
 * Gets the #margin_right property of @area_page
 *
 * Return value: The "margin-right" property value
**/
gfloat
fo_area_page_get_margin_right (FoArea *fo_area_page)
{
  g_return_val_if_fail (fo_area_page != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_page), 0);

  return FO_AREA_PAGE (fo_area_page)->margin_right;
}

void
fo_area_page_debug_dump_properties (FoArea *area, gint depth)
{
  FoAreaPage *page;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_PAGE (area));

  page = FO_AREA_PAGE (area);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spage-number:   %d", indent, page->page_number);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spage-width:    %g pt", indent, page->page_width);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spage-height:   %g pt", indent, page->page_height);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%smargin-top:    %g pt", indent, page->margin_top);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%smargin-bottom: %g pt", indent, page->margin_bottom);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%smargin-left:   %g pt", indent, page->margin_left);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%smargin-right:  %g pt", indent, page->margin_right);

  g_free (indent);

  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

static FoArea*
fo_area_page_clone (FoArea *original)
{
  FoArea *clone;

  g_return_val_if_fail (original != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_PAGE (original), NULL);

  fo_page_sequence_area_new (original->generated_by,
			     NULL,
			     original,
			     &clone,
			     0);
#if defined(LIBFO_DEBUG) && 0
  fo_object_debug_dump (clone, 0);
#endif
  return clone;
}

FoArea*
fo_area_page_add_child (FoArea *parent, FoArea *child)
{
  g_return_val_if_fail (parent != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_PAGE (parent), NULL);
  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_VIEWPORT_REFERENCE (child), NULL);

  return fo_area_real_add_child (parent, child);
}

static FoArea*
fo_area_page_first_leaf (FoArea *area)
{
  FoArea *use_area;

  g_return_val_if_fail (area != NULL, area);
  g_return_val_if_fail (FO_IS_AREA (area), area);

  use_area = area;

  while (!FO_AREA_IS_LEAF (use_area))
    {
      use_area = fo_area_first_child (use_area);
    }

  return use_area;
}

static FoArea*
fo_area_page_last_leaf (FoArea *area)
{
  FoArea *use_area;

  g_return_val_if_fail (area != NULL, area);
  g_return_val_if_fail (FO_IS_AREA (area), area);

  use_area = area;

  while (!FO_AREA_IS_LEAF (use_area))
    {
      use_area = fo_area_last_child (use_area);
    }

  return use_area;
}

static gboolean
fo_area_page_vr_adjust (FoArea *area,
			gpointer data)
{
  FoArea *parent = fo_area_parent (area);

  if (FO_IS_AREA_VIEWPORT_REFERENCE (area))
    {
      area->reference = area;
    }
  else
    {
      area->reference = parent->reference;
    }
  if (FO_IS_AREA_PAGE (area))
    {
      area->page = area;
    }
  else
    {
      area->page = parent->page;
    }

  return FALSE;
}

static FoArea *
move_to_new_page (FoArea *page,
		  FoArea *child)
{
  FoArea *clone = fo_area_clone (page);
  FoArea *use_child_area;

  fo_area_unlink_with_next_siblings (child);
  fo_area_insert_with_next_siblings (clone, 0, child);

  use_child_area = child;

  while (use_child_area)
    {
      fo_area_traverse (use_child_area,
			G_PRE_ORDER,
			G_TRAVERSE_ALL,
			-1,
			fo_area_page_vr_adjust,
			NULL);

      use_child_area = fo_area_next_sibling (use_child_area);
    }
#if defined(LIBFO_DEBUG) && 0
  g_message ("move_to_new_page (%p):: page last leaf: %s; generated by: %s",
	     child,
	     fo_object_debug_sprintf (fo_area_page_last_leaf (page)),
	     fo_object_debug_sprintf (fo_area_page_last_leaf (page)->generated_by));
#endif
  fo_area_size_request (fo_area_page_last_leaf (page));

  return clone;
}

FoArea*
fo_area_page_size_request (FoArea *child)
{
  FoArea *page;
  gfloat total_child_height = 0;
  gfloat child_height;
  gfloat page_child_available_bpdim;

  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_VIEWPORT_REFERENCE (child), NULL);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_parent (child)), NULL);

  page = fo_area_parent (child);

  g_return_val_if_fail (page != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_PAGE (page), NULL);

  child_height = fo_area_area_get_height (child);
  page_child_available_bpdim = fo_area_get_child_available_bpdim (page);

  fo_area_children_foreach (page,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    (gpointer) &total_child_height);

#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "page_size_request (%p):: child: %f; total %f; available: %f",
	 child,
	 child_height,
	 total_child_height,
	 page_child_available_bpdim);
#endif

  if (child_height <= page_child_available_bpdim)
    {
      fo_area_set_available_height (child, page_child_available_bpdim);
      fo_area_area_set_x (child, fo_area_page_get_margin_left (page));
      fo_area_area_set_y (child,
			  fo_area_page_get_page_height (page) -
			  fo_area_page_get_margin_top (page));
      fo_area_set_available_width (child, fo_area_get_child_available_ipdim (page));
      fo_area_area_set_width (child, fo_area_get_child_available_ipdim (page));

      return child;
    }
  else
    {
      /*
       * The child may be big enough to be split over multiple pages.
       * Keep splitting onto new pages while the child remains too big
       * and can be split.
       */
      while ((child_height > page_child_available_bpdim) &&
	     fo_area_split_before_height_check (child, page_child_available_bpdim))
	{
	  FoArea *split_child;

	  split_child =
	    fo_area_split_before_height (child, page_child_available_bpdim);

#if defined(LIBFO_DEBUG) && 1
	  g_message ("page_size_request (%p):: child split:: child: %s; generated by: %s; split child: %s; generated by: %s; area %s; generated by: %s",
		     child,
		     fo_object_debug_sprintf (child),
		     fo_object_debug_sprintf (child->generated_by),
		     fo_object_debug_sprintf (split_child),
		     split_child? fo_object_debug_sprintf (split_child->generated_by) : "(null)",
		     fo_object_debug_sprintf (page),
		     fo_object_debug_sprintf (page->generated_by));
#endif


	  page = move_to_new_page (page, split_child);
	  child = split_child;

	  child_height = fo_area_area_get_height (child);
	  page_child_available_bpdim = fo_area_get_child_available_bpdim (page);
	}
#if defined(LIBFO_DEBUG) && 0
      g_message ("page_size_request (%p):: new page first leaf: %s; generated by: %s",
		 child,
		 fo_object_debug_sprintf (fo_area_page_first_leaf (page)),
		 fo_object_debug_sprintf (fo_area_page_first_leaf (page->generated_by)));
#endif

      /* child may still be too big for the current page. */
      if (child_height > page_child_available_bpdim)
	{
	  GError *error = g_error_new (FO_AREA_PAGE_ERROR,
				       FO_AREA_PAGE_ERROR_OVERFLOW,
				       fo_area_page_error_messages[FO_AREA_PAGE_ERROR_OVERFLOW]);

	  fo_object_log_warning (FO_OBJECT (child),
				 &error);

	  if (fo_area_child_position (page, child) != 0)
	    {
	      page = move_to_new_page (page, child);
	    }

	  fo_area_area_set_x (child, fo_area_page_get_margin_left (page));
	  fo_area_area_set_y (child,
			      fo_area_page_get_page_height (page) -
			      fo_area_page_get_margin_top (page));
	  fo_area_set_available_width (child, fo_area_get_child_available_ipdim (page));
	  fo_area_area_set_width (child, fo_area_get_child_available_ipdim (page));
	  fo_area_set_available_height (child, page_child_available_bpdim);
	}
      else
	{
	  fo_area_size_request (fo_area_page_first_leaf (page));
	}

      return child;
    }
}

/**
 * fo_area_page_error_quark:
 * 
 * Gets the #GQuark identifying #FoAreaPage errors.
 * 
 * Return value: #GQuark identifying #FoAreaPage errors.
 **/
GQuark
fo_area_page_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("fo-area-page-error");
  return quark;
}
