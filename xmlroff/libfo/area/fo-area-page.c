/* Fo
 * fo-area-page.c: Page area object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-area.h"
#include "fo-area-viewport-reference-private.h"
#include "fo-area-page.h"
#include "fo-area-region.h"
#include "fo/fo-page-sequence-area.h"
#include "fo/fo-region-body.h"
#include "fo/fo-region-before.h"
#include "fo/fo-region-after.h"
#include "fo/fo-region-start.h"
#include "fo/fo-region-end.h"
#include "fo/fo-simple-page-master.h"

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
  gdouble page_height;
  gdouble page_width;
  gdouble margin_top;
  gdouble margin_bottom;
  gdouble margin_left;
  gdouble margin_right;
};

struct _FoAreaPageClass
{
  FoAreaViewportReferenceClass parent_class;
};

static void fo_area_page_init         (FoAreaPage      *fo_area_page);
static void fo_area_page_class_init   (FoAreaPageClass *klass);
static void fo_area_page_get_property (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_area_page_set_property (GObject         *object,
				       guint            prop_id,
				       const GValue    *value,
				       GParamSpec      *pspec);
static void _dispose    (GObject           *object);

static void     _debug_dump_properties (FoArea *area,
					gint    depth);
static void     _update_after_clone    (FoArea *clone,
					FoArea *original);
static FoArea * _add_child             (FoArea *parent,
					FoArea *child);
static FoArea * _size_request          (FoArea *child);

static gpointer parent_class;

/**
 * fo_area_page_get_type:
 * @void: 
 * 
 * Register the #FoAreaPage object type.
 * 
 * Return value: #GType value of the #FoAreaPage object type.
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
	  (GInstanceInitFunc) fo_area_page_init,
	  NULL		/* value_table */
	};
      
      object_type = g_type_register_static (FO_TYPE_AREA_VIEWPORT_REFERENCE,
                                            "FoAreaPage",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_page_init:
 * @fo_area_page: #FoAreaPage object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoAreaPage.
 **/
void
fo_area_page_init (FoAreaPage *fo_area_page)
{
  FO_AREA (fo_area_page)->class = FO_AREA_FLAG_CLASS_ABSOLUTE;
}

/**
 * fo_area_page_class_init:
 * @klass: #FoAreaPageClass object to initialise
 * 
 * Implements #GClassInitFunc for #FoAreaPageClass
 **/
void
fo_area_page_class_init (FoAreaPageClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->dispose = _dispose;

  object_class->set_property = fo_area_page_set_property;
  object_class->get_property = fo_area_page_get_property;

  FO_AREA_CLASS (klass)->debug_dump_properties =
    _debug_dump_properties;
  FO_AREA_CLASS (klass)->add_child = _add_child;
  FO_AREA_CLASS (klass)->size_request = _size_request;
  FO_AREA_CLASS (klass)->update_after_clone =
    _update_after_clone;

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
 * _dispose:
 * @object: FoAreaPage object to dispose
 * 
 * Implements #GObjectDisposeFunc for #FoAreaPage
 **/
static void
_dispose (GObject *object)
{
  FoAreaPage *fo_area_page;

  fo_area_page = FO_AREA_PAGE (object);

  G_OBJECT_CLASS (parent_class)->dispose (object);
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
 * fo_area_page_set_property:
 * @object:  #GObject whose property will be set
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
			     gdouble new_page_width)
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
gdouble
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
			      gdouble new_page_height)
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
gdouble
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
		         gdouble new_margin_top)
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
gdouble
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
		         gdouble new_margin_bottom)
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
gdouble
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
		         gdouble new_margin_left)
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
gdouble
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
		         gdouble new_margin_right)
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
gdouble
fo_area_page_get_margin_right (FoArea *fo_area_page)
{
  g_return_val_if_fail (fo_area_page != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_PAGE (fo_area_page), 0);

  return FO_AREA_PAGE (fo_area_page)->margin_right;
}

void
_debug_dump_properties (FoArea *area,
			gint    depth)
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

static void
_update_after_clone (FoArea *clone,
		     FoArea *original)
{
  FO_AREA_CLASS (parent_class)->update_after_clone (clone, original);

  FoAreaPage *original_page = (FoAreaPage *) original;
  FoAreaPage *clone_page = (FoAreaPage *) clone;

  clone_page->page_number   = original_page->page_number;
  fo_area_page_set_page_height (clone,
				original_page->page_height);
  fo_area_page_set_page_width (clone,
			       original_page->page_width);
  fo_area_page_set_margin_top (clone,
			       original_page->margin_top);
  fo_area_page_set_margin_bottom (clone, original_page->margin_bottom);
  fo_area_page_set_margin_left (clone,
				original_page->margin_left);
  fo_area_page_set_margin_right (clone,
				 original_page->margin_right);
}

FoArea*
_add_child (FoArea *parent,
	    FoArea *child)
{
  g_return_val_if_fail (parent != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_PAGE (parent), NULL);
  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_VIEWPORT_REFERENCE (child), NULL);

  return FO_AREA_CLASS (parent_class)->add_child (parent, child);
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
_last_leaf (FoArea *area)
{
  FoArea *use_area;

  /* Return HULL if can't use 'area'. */
  g_return_val_if_fail (area != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA (area), NULL);

  use_area = area;

  while (!FO_AREA_IS_LEAF (use_area))
    {
      use_area = fo_area_last_child (use_area);
    }

  return use_area;
}

static gboolean
fo_area_page_vr_adjust (FoArea  *area,
			gpointer data G_GNUC_UNUSED)
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
      fo_area_set_page (area,
			area);
    }
  else
    {
      fo_area_set_page (area,
			fo_area_get_page (parent));
    }

  return FALSE;
}

/**
 * _clone_child_region:
 * @region: 
 * @data: 
 *
 * 
 **/
static void
_clone_child_region (FoArea  *region,
		     gpointer data)
{
  FoAreaRegionNameAndArea *name_and_page =
    (FoAreaRegionNameAndArea *) data;

  if (g_strcmp0 (fo_area_region_get_region_name (region),
		 name_and_page->name) != 0)
    {
      /* Clone the region if it's not the one currently being split,
	 but keep a ref to it while it's not in any tree. */
      FoArea *clone_region = g_object_ref (fo_area_clone (region));
      fo_area_unlink (clone_region);
      fo_area_add_child (name_and_page->area,
			 clone_region);
      g_object_unref (clone_region);
    }
}

static FoArea *
_get_named_region (FoArea *page,
		   const gchar *region_name)
{
  /* Return HULL if can't use 'page' or 'region_name'. */
  g_return_val_if_fail (page != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_PAGE (page), NULL);
  g_return_val_if_fail (region_name != NULL, NULL);

  FoAreaRegionNameAndArea name_and_area =
    {
      region_name,
      NULL
    };

  fo_area_traverse (page,
		    G_POST_ORDER,
		    G_TRAVERSE_LEAVES,
		    2,
		    fo_area_region_is_named_region,
		    &name_and_area);

  /* name_and_area.area is non-NULL only if the region was found. */
  return name_and_area.area;
}

static FoArea *
_move_to_new_page (FoArea *page,
		   FoArea *region_body)
{
  FoArea *clone = fo_area_clone (page);
  /* Increment the page number on the clone. */
  fo_area_page_set_page_number (clone,
				fo_area_page_get_page_number (clone) + 1);

  FoArea *parent_area = fo_area_parent (page);
  g_object_ref (clone);
  fo_area_unlink (clone);
  fo_area_add_child (parent_area, clone);
  g_object_unref (clone);

  /* Also clone the regions on the page. */
  FoAreaRegionNameAndArea name_and_page =
    {
      fo_area_region_get_region_name (region_body),
      clone
    };

  fo_area_children_foreach (page,
			    G_TRAVERSE_ALL,
			    &_clone_child_region,
			    &name_and_page);

  g_object_ref (region_body);
  fo_area_unlink (region_body);
  fo_area_add_child (clone, region_body);
  g_object_unref (region_body);

  FoArea *use_region = region_body;
  while (use_region)
    {
      fo_area_traverse (use_region,
			G_PRE_ORDER,
			G_TRAVERSE_ALL,
			1,
			fo_area_page_vr_adjust,
			NULL);

      use_region = fo_area_next_sibling (use_region);
    }

#if defined(LIBFO_DEBUG) && 0
  g_message ("_move_to_new_page (%p):: page last leaf: %s; generated by: %s",
	     child,
	     fo_object_debug_sprintf (_last_leaf (page)),
	     fo_object_debug_sprintf (_last_leaf (page)->generated_by));
#endif
  /*
  fo_area_size_request (_last_leaf (use_region));
  */
  return clone;
}

static FoArea*
_region_body_size_request (FoArea *page,
			   FoArea *region_body)
{
  gdouble region_body_height = fo_area_area_get_height (region_body);

  gdouble page_region_body_available_bpdim =
    fo_area_get_child_available_bpdim (page);

  /* FIXME: Is this accurate when there are other regions on the
     page? */
  gdouble total_region_body_height = 0;
  fo_area_children_foreach (page,
			    G_TRAVERSE_ALL,
			    &fo_area_accumulate_height,
			    (gpointer) &total_region_body_height);

#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "page_size_request (%p):: region_body: %f; total %f; available: %f",
	 region_body,
	 region_body_height,
	 total_region_body_height,
	 page_region_body_available_bpdim);
#endif

  if (region_body_height <= page_region_body_available_bpdim)
    {
      /* If it fits, adjust region_body within page. */
      fo_area_set_available_height (region_body,
				    page_region_body_available_bpdim);
      fo_area_area_set_x (region_body, fo_area_page_get_margin_left (page));
      fo_area_area_set_y (region_body,
			  fo_area_page_get_page_height (page) -
			  fo_area_page_get_margin_top (page));
      fo_area_set_available_width (region_body,
				   fo_area_get_child_available_ipdim (page));
      fo_area_area_set_width (region_body,
			      fo_area_get_child_available_ipdim (page));

      return region_body;
    }
  else
    {
      /*
       * The region-body may be big enough to be split over multiple pages.
       * Keep splitting onto new pages while the region-body remains too big
       * and can be split.
       */
      while ((region_body_height > page_region_body_available_bpdim) &&
	     fo_area_split_before_height_check (region_body, page_region_body_available_bpdim))
	{
	  /* Split off the part that won't fit on the page. */
	  FoArea *split_region_body =
	    fo_area_split_before_height (region_body,
					 page_region_body_available_bpdim);

#if defined(LIBFO_DEBUG) && 1
	  g_message ("page_size_request (%p):: region-body split:: region-body: %s; generated by: %s; split region-body: %s; generated by: %s; area %s; generated by: %s",
		     region_body,
		     fo_object_debug_sprintf (region_body),
		     fo_object_debug_sprintf (region_body->generated_by),
		     fo_object_debug_sprintf (split_region_body),
		     split_region_body? fo_object_debug_sprintf (split_region_body->generated_by) : "(null)",
		     fo_object_debug_sprintf (page),
		     fo_object_debug_sprintf (page->generated_by));
#endif

	  /* Move the overflow to a new page. */
	  FoArea *new_page = _move_to_new_page (page, split_region_body);

	  region_body = split_region_body;
	  /* Loop again with new page and new region-body. */
	  region_body_height = fo_area_area_get_height (region_body);
	  page_region_body_available_bpdim =
	    fo_area_get_child_available_bpdim (new_page);
	}
#if defined(LIBFO_DEBUG) && 0
      g_message ("page_size_request (%p):: new page first leaf: %s; generated by: %s",
		 region_body,
		 fo_object_debug_sprintf (fo_area_page_first_leaf (page)),
		 fo_object_debug_sprintf (fo_area_page_first_leaf (page->generated_by)));
#endif

      /* region_body may still be too big for the current page if it
	 wasn't possible to split. */
      if (region_body_height > page_region_body_available_bpdim)
	{
	  GError *error = g_error_new (FO_AREA_PAGE_ERROR,
				       FO_AREA_PAGE_ERROR_OVERFLOW,
				       "%s",
				       N_(fo_area_page_error_messages[FO_AREA_PAGE_ERROR_OVERFLOW]));

	  fo_object_log_warning (FO_OBJECT (region_body),
				 &error);

	  if (fo_area_child_position (page, region_body) != 0)
	    {
	      page = _move_to_new_page (page, region_body);
	    }

	  fo_area_area_set_x (region_body,
			      fo_area_page_get_margin_left (page));
	  fo_area_area_set_y (region_body,
			      fo_area_page_get_page_height (page) -
			      fo_area_page_get_margin_top (page));
	  fo_area_set_available_width (region_body,
				       fo_area_get_child_available_ipdim (page));
	  fo_area_area_set_width (region_body,
				  fo_area_get_child_available_ipdim (page));
	  fo_area_set_available_height (region_body,
					page_region_body_available_bpdim);
	}
      else
	{
	  fo_area_size_request (fo_area_page_first_leaf (page));
	}

      return region_body;
    }
}


static FoArea*
_region_before_size_request (FoArea *page,
			     FoArea *region,
			     FoFo   *region_fo,
			     FoFo   *simple_page_master_fo)
{
  gdouble extent =
    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_fo)));
  gboolean precedence =
    fo_boolean_get_value (fo_property_get_value (fo_region_before_after_get_precedence (region_fo)));

  fo_area_area_set_y (region,
		      fo_area_page_get_page_height (page));
  fo_area_area_set_height (region,
			   extent);

  gdouble x = 0;
  gdouble width = fo_area_page_get_page_width (page);
  /* Width may be reduced if precedence is false and there are side
     regions. */
  if (!precedence)
    {
      FoFo *region_start_fo =
	fo_simple_page_master_get_region_start (simple_page_master_fo);

      if (region_start_fo != NULL)
	{
	  gdouble start_extent =
	    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_start_fo)));
	  width = width - start_extent;
	  x = start_extent;
	}

      FoFo *region_end_fo =
	fo_simple_page_master_get_region_end (simple_page_master_fo);

      if (region_start_fo != NULL)
	{
	  gdouble end_extent =
	    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_end_fo)));
	  width = width - end_extent;
	}
    }
  fo_area_area_set_x (region, x);
  /* Set the resolved width. */
  fo_area_area_set_width (region,
			  width);
  fo_area_set_available_width (region,
			       width);
  fo_area_set_available_height (region,
				extent);

  return region;
}

static FoArea*
_region_after_size_request (FoArea *page,
			    FoArea *region,
			    FoFo   *region_fo,
			    FoFo   *simple_page_master_fo)
{
  gdouble extent =
    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_fo)));
  gboolean precedence =
    fo_boolean_get_value (fo_property_get_value (fo_region_before_after_get_precedence (region_fo)));

  fo_area_area_set_y (region,
		      extent);
  fo_area_area_set_height (region,
			   extent);

  gdouble x = 0;
  gdouble width = fo_area_page_get_page_width (page);
  /* Width may be reduced if precedence is false and there are side
     regions. */
  if (!precedence)
    {
      FoFo *region_start_fo =
	fo_simple_page_master_get_region_start (simple_page_master_fo);

      if (region_start_fo != NULL)
	{
	  gdouble start_extent =
	    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_start_fo)));
	  width = width - start_extent;
	  x = start_extent;
	}

      FoFo *region_end_fo =
	fo_simple_page_master_get_region_end (simple_page_master_fo);

      if (region_start_fo != NULL)
	{
	  gdouble end_extent =
	    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_end_fo)));
	  width = width - end_extent;
	}
    }
  fo_area_area_set_x (region, x);
  /* Set the resolved width. */
  fo_area_area_set_width (region,
			  width);
  fo_area_set_available_width (region,
			       width);
  fo_area_set_available_height (region,
				extent);

  return region;
}

static FoArea*
_region_start_end_size_request (FoArea  *page,
				FoArea  *region,
				FoFo    *region_fo,
				FoFo    *simple_page_master_fo,
				gdouble x)
{
  gdouble extent =
    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_fo)));

  fo_area_area_set_x (region, x);

  gdouble y = fo_area_page_get_page_height (page);
  gdouble height = y;

  FoFo *region_before_fo =
    fo_simple_page_master_get_region_before (simple_page_master_fo);

  if (region_before_fo != NULL)
    {
      gboolean before_precedence =
	fo_boolean_get_value (fo_property_get_value (fo_region_before_after_get_precedence (region_before_fo)));

      if (before_precedence)
	{
	  gdouble before_extent =
	    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_before_fo)));
	  y = y - before_extent;
	  height = y;
	}
    }

  FoFo *region_after_fo =
    fo_simple_page_master_get_region_after (simple_page_master_fo);

  if (region_after_fo != NULL)
    {
      gboolean after_precedence =
	fo_boolean_get_value (fo_property_get_value (fo_region_before_after_get_precedence (region_before_fo)));

      if (after_precedence)
	{
	  gdouble after_extent =
	    fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (region_before_fo)));
	  height = height - after_extent;
	}
    }
  fo_area_area_set_y (region,
		      y);
  fo_area_area_set_width (region,
			  extent);
  fo_area_set_available_width (region,
			       extent);
  fo_area_set_available_height (region,
				height);
  fo_area_area_set_height (region,
			   height);

  return region;
}

FoArea*
_size_request (FoArea *child)
{
  g_return_val_if_fail (child != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_REGION (child), NULL);

  FoArea *page = fo_area_parent (child);

  g_return_val_if_fail (page != NULL, NULL);
  g_return_val_if_fail (FO_IS_AREA_PAGE (page), NULL);

  FoFo *area_fo = fo_fo_get_area_fo (fo_area_get_generated_by (child));
  FoFo *simple_page_master_fo =
    FO_FO (fo_node_parent (FO_NODE (area_fo)));

  if (FO_IS_REGION_BODY (area_fo))
    {
      return _region_body_size_request (page, child);
    }
  else if (FO_IS_REGION_BEFORE (area_fo))
    {
      return _region_before_size_request (page,
					  child,
					  area_fo,
					  simple_page_master_fo);
    }
  else if (FO_IS_REGION_AFTER (area_fo))
    {
      return _region_after_size_request (page,
					 child,
					 area_fo,
					 simple_page_master_fo);
    }
  else if (FO_IS_REGION_START (area_fo))
    {
      return _region_start_end_size_request (page,
					     child,
					     area_fo,
					     simple_page_master_fo,
					     0);
    }
  else if (FO_IS_REGION_END (area_fo))
    {
      gdouble extent =
	fo_length_get_value (fo_property_get_value (fo_region_outer_get_extent (area_fo)));

      return _region_start_end_size_request (page,
					     child,
					     area_fo,
					     simple_page_master_fo,
					     fo_area_page_get_page_width (page) - extent);
    }
  else
    {
      g_assert_not_reached ();
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
