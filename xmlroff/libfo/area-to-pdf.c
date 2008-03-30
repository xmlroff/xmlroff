/* Fo
 * area-to-pdf.c: Convert area tree into PDF
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */


#include <string.h>
#include "area-to-pdf.h"
#include "area/fo-all-area.h"
#include "area/fo-area-table-continuation-private.h"
#include "property/fo-property-border.h"
#include "property/fo-property-border-bottom-style.h"
#include "property/fo-property-border-left-style.h"
#include "property/fo-property-border-right-style.h"
#include "property/fo-property-border-top-style.h"
#include "property/fo-property-color.h"
#include "property/fo-property-font-size.h"

typedef struct
{
  gdouble x1;	  /* X-coordinate of one corner. */
  gdouble y1;	  /* Y-coordinate of one corner. */
  gdouble x2;	  /* X-coordinate of the opposite corner. */
  gdouble y2;	  /* Y-coordinate of the opposite corder. */
  gdouble x1delta; /* Relative x-offset of interior corner nearest (x1,y1). */
  gdouble y1delta; /* Relative y-offset of interior corner nearest (x1,y1). */
  gdouble x2delta; /* Relative x-offset of interior corner nearest (x2,y2). */
  gdouble y2delta; /* Relative y-offset of interior corner nearest (x2,y2). */
} FoPdfOneBorderCoords;

/**
 * fo_pdf_draw_background:
 * @fo_doc: #FoDoc
 * @x:      X-coordinate of top-left corner.
 * @y:      Y-coordinate of top-left corner.
 * @width:  Width of background area
 * @height: Height of background area
 * @background_color: Background color, or an #FoEnum if background is
 *                    transparent.
 * 
 * If @background_color is an #FoColor, draw a rectangle of the
 * background color with top-left corner at (@x, @y) with width @width
 * and height @height.
 **/
static void
fo_pdf_draw_background (FoDoc *fo_doc,
			gdouble x,
			gdouble y,
			gdouble width,
			gdouble height,
			FoDatatype *background_color)
{

#if defined(LIBFO_DEBUG) && 0
  g_message ("draw_background:: x: %f; y; %f; width: %f; height: %f",
	     x,
	     y,
	     width,
	     height);
  fo_object_debug_dump (background_color, 0);
#endif

  if (FO_IS_COLOR (background_color))
    {
      fo_doc_set_fill_color (fo_doc,
			     background_color);

      fo_doc_rect_filled (fo_doc,
			  x,
			  y - height,
			  width,
			  height);
    }
}

/**
 * fo_pdf_clip_to_coords:
 * @fo_doc: #FoDoc.
 * @coords: Coordinates of one border of an area.
 * 
 * Clip the drawing area of @fo_doc to @coords
 **/
static void
fo_pdf_clip_to_coords (FoDoc *fo_doc,
		       FoPdfOneBorderCoords *coords)
{
  fo_doc_move_to (fo_doc,
		  coords->x1,
		  coords->y1);
  fo_doc_line_to (fo_doc,
		  coords->x2,
		  coords->y2);
  fo_doc_line_to (fo_doc,
		  coords->x2 + coords->x2delta,
		  coords->y2 + coords->y2delta);
  fo_doc_line_to (fo_doc,
		  coords->x1 + coords->x1delta,
		  coords->y1 + coords->y1delta);
  fo_doc_clip (fo_doc);
}

/**
 * fo_pdf_draw_border_two_tone_vertical:
 * @fo_doc:      #FoDoc
 * @inner_color: Color of the inner band
 * @outer_color: Color of the outer band
 * @coords:      Coordinates of one border of an area
 * 
 * Draw a left or right two-tone border.
 **/
static void
fo_pdf_draw_border_two_tone_vertical (FoDoc *fo_doc,
				      FoDatatype *inner_color,
				      FoDatatype *outer_color,
				      FoPdfOneBorderCoords *coords)
{
  fo_doc_set_line_width (fo_doc,
			 ABS (coords->x1delta) / 2);

  fo_doc_set_stroke_color (fo_doc, outer_color);
  fo_doc_move_to (fo_doc,
		  coords->x1 + coords->x1delta / 4.0,
		  coords->y1);
  fo_doc_line_to (fo_doc,
		  coords->x2 + coords->x2delta / 4.0,
		  coords->y2);
  fo_doc_stroke (fo_doc);

  fo_doc_set_stroke_color (fo_doc, inner_color);
  fo_doc_move_to (fo_doc,
		  coords->x1 + 3.0 * coords->x1delta / 4.0,
		  coords->y1);
  fo_doc_line_to (fo_doc,
		  coords->x2 + 3.0 * coords->x2delta / 4.0,
		  coords->y2);
  fo_doc_stroke (fo_doc);
}

/**
 * fo_pdf_draw_border_two_tone_horizontal:
 * @fo_doc:      #FoDoc
 * @inner_color: Color of the inner band
 * @outer_color: Color of the outer band
 * @coords:      Coordinates of one border of an area
 * 
 * Draw a top or bottom two-tone border.
 **/
static void
fo_pdf_draw_border_two_tone_horizontal (FoDoc *fo_doc,
					FoDatatype *inner_color,
					FoDatatype *outer_color,
					FoPdfOneBorderCoords *coords)
{
  fo_doc_set_line_width (fo_doc,
			 ABS (coords->y1delta) / 2);

  fo_doc_set_stroke_color (fo_doc,
			   inner_color);
  fo_doc_move_to (fo_doc,
		  coords->x1,
		  coords->y1 + 3.0 * coords->y1delta / 4.0);
  fo_doc_line_to (fo_doc,
		  coords->x2,
		  coords->y2 + 3.0 * coords->y2delta / 4.0);
  fo_doc_stroke (fo_doc);

  fo_doc_set_stroke_color (fo_doc,
			   outer_color);
  fo_doc_move_to (fo_doc,
		  coords->x1,
		  coords->y1 + coords->y1delta / 4.0);
  fo_doc_line_to (fo_doc,
		  coords->x2,
		  coords->y2 + coords->y2delta / 4.0);
  fo_doc_stroke (fo_doc);
}

/**
 * fo_pdf_draw_border_solid:
 * @fo_doc: #FoDoc
 * @color:  Border color
 * @coords: Coordinates of one border of an area
 * 
 * Draw a solid border with color @color and coordinates @coords.
 **/
static void
fo_pdf_draw_border_solid (FoDoc *fo_doc,
			  FoDatatype *color,
			  FoPdfOneBorderCoords *coords)
{
  fo_doc_set_fill_color (fo_doc,
			 color);

  fo_doc_move_to (fo_doc,
		  coords->x1,
		  coords->y1);
  fo_doc_line_to (fo_doc,
		  coords->x2,
		  coords->y2);
  fo_doc_line_to (fo_doc,
		  coords->x2 + coords->x2delta,
		  coords->y2 + coords->y2delta);
  fo_doc_line_to (fo_doc,
		  coords->x1 + coords->x1delta,
		  coords->y1 + coords->y1delta);
  fo_doc_fill (fo_doc);
}

/**
 * fo_pdf_draw_border_double:
 * @fo_doc: #FoDoc
 * @color:  Border color
 * @coords: Coordinates of one border of an area
 * 
 * Draw a double border with color @color and coordinates @coords.
 **/
static void
fo_pdf_draw_border_double (FoDoc *fo_doc,
			   FoDatatype *color,
			   FoPdfOneBorderCoords *coords)
{
  fo_doc_set_fill_color (fo_doc,
			 color);

  fo_doc_move_to (fo_doc,
		  coords->x1,
		  coords->y1);
  fo_doc_line_to (fo_doc,
		  coords->x2,
		  coords->y2);
  fo_doc_line_to (fo_doc,
		  coords->x2 + coords->x2delta / 3,
		  coords->y2 + coords->y2delta / 3);
  fo_doc_line_to (fo_doc,
		  coords->x1 + coords->x1delta / 3,
		  coords->y1 + coords->y1delta / 3);
  fo_doc_fill (fo_doc);

  fo_doc_move_to (fo_doc,
		  coords->x1 + 2 * coords->x1delta / 3,
		  coords->y1 + 2 * coords->y1delta / 3);
  fo_doc_line_to (fo_doc,
		  coords->x2 + 2 * coords->x2delta / 3,
		  coords->y2 + 2 * coords->y2delta / 3);
  fo_doc_line_to (fo_doc,
		  coords->x2 + coords->x2delta,
		  coords->y2 + coords->y2delta);
  fo_doc_line_to (fo_doc,
		  coords->x1 + coords->x1delta,
		  coords->y1 + coords->y1delta);
  fo_doc_fill (fo_doc);
}

/**
 * fo_pdf_draw_border_dotted:
 * @fo_doc: #FoDoc
 * @color:  Border color
 * @coords: Coordinates of one border of an area
 * 
 * Draw a dotted border with color @color and coordinates @coords.
 **/
static void
fo_pdf_draw_border_dotted (FoDoc *fo_doc,
			   FoDatatype *color,
			   FoPdfOneBorderCoords *coords)
{
  fo_doc_set_stroke_color (fo_doc,
			   color);

/*  fo_doc_set_line_cap (fo_doc,
    FO_DOC_LINE_CAP_ROUND);*/ /* round end caps */

  fo_doc_move_to (fo_doc,
		  coords->x1,
		  coords->y1);
  fo_doc_line_to (fo_doc,
		  coords->x2,
		  coords->y2);
  fo_doc_line_to (fo_doc,
		  coords->x2 + coords->x2delta,
		  coords->y2 + coords->y2delta);
  fo_doc_line_to (fo_doc,
		  coords->x1 + coords->x1delta,
		  coords->y1 + coords->y1delta);
  fo_doc_clip (fo_doc);

  if (coords->x1 == coords->x2)
    { /* vertical */
      fo_doc_set_dash (fo_doc,
		       ABS (coords->x1delta),
		       ABS (coords->x1delta));
      fo_doc_set_line_width (fo_doc,
			     ABS (coords->x1delta));

      fo_doc_move_to (fo_doc,
		      coords->x1 + coords->x1delta / 2,
		      coords->y1);
      fo_doc_line_to (fo_doc,
		      coords->x2 + coords->x2delta / 2,
		      coords->y2);
    }
  else
    { /* horizontal */
      fo_doc_set_dash (fo_doc,
		       ABS (coords->y1delta),
		       ABS (coords->y1delta));
      fo_doc_set_line_width (fo_doc,
			     ABS (coords->y1delta));

      fo_doc_move_to (fo_doc,
		      coords->x1,
		      coords->y1 + coords->y1delta / 2);
      fo_doc_line_to (fo_doc,
		      coords->x2,
		      coords->y2 + coords->y2delta / 2);
    }

  fo_doc_stroke (fo_doc);
}

/**
 * fo_pdf_draw_border_dashed:
 * @fo_doc: #FoDoc
 * @color:  Border color
 * @coords: Coordinates of one border of an area
 * 
 * Draw a dashed border with color @color and coordinates @coords.
 **/
static void
fo_pdf_draw_border_dashed (FoDoc *fo_doc,
			   FoDatatype *color,
			   FoPdfOneBorderCoords *coords)
{
/*  fo_doc_set_line_cap (fo_doc,
    FO_DOC_LINE_CAP_BUTT);*/ /* butt end caps */

  fo_pdf_clip_to_coords (fo_doc, coords);

  fo_doc_set_stroke_color (fo_doc,
			   color);

  if (coords->x1 == coords->x2)
    { /* vertical */
      fo_doc_set_dash (fo_doc,
		       ABS (coords->x1delta) * 3,
		       ABS (coords->x1delta) * 3);
      fo_doc_set_line_width (fo_doc,
			     ABS (coords->x1delta));

      fo_doc_move_to (fo_doc,
		      coords->x1 + coords->x1delta / 2,
		      coords->y1);
      fo_doc_line_to (fo_doc,
		      coords->x2 + coords->x2delta / 2,
		      coords->y2);
    }
  else
    { /* horizontal */
      fo_doc_set_dash (fo_doc,
		       ABS (coords->y1delta) * 3,
		       ABS (coords->y1delta) * 3);
      fo_doc_set_line_width (fo_doc,
			     ABS (coords->y1delta));

      fo_doc_move_to (fo_doc,
		      coords->x1,
		      coords->y1 + coords->y1delta / 2);
      fo_doc_line_to (fo_doc,
		      coords->x2,
		      coords->y2 + coords->y2delta / 2);
    }
  fo_doc_stroke (fo_doc);
}

/**
 * fo_pdf_draw_border_groove:
 * @fo_doc: #FoDoc
 * @color:  Border color
 * @coords: Coordinates of one border of an area
 * 
 * Draw a grooved border with colors based on @color and coordinates @coords.
 **/
static void
fo_pdf_draw_border_groove (FoDoc *fo_doc,
			   FoDatatype *color,
			   FoPdfOneBorderCoords *coords)
{
  fo_doc_set_dash (fo_doc, 0.0, 0.0);

  fo_pdf_clip_to_coords (fo_doc, coords);

  if (coords->x1 == coords->x2)
    { /* vertical */
      if (coords->x1delta >= 0)
	{ /* left */
	  fo_pdf_draw_border_two_tone_vertical (fo_doc,
						color,
						fo_color_get_color_one_quarter (color),
						coords);
	}
      else
	{ /* right */
	  fo_pdf_draw_border_two_tone_vertical (fo_doc,
						fo_color_get_color_one_quarter (color),
						color,
						coords);
	}
    }
  else
    { /* horizontal */
      if (coords->y1delta >= 0)
	{ /* bottom */
	  fo_pdf_draw_border_two_tone_horizontal (fo_doc,
						  fo_color_get_color_one_quarter (color),
						  color,
						  coords);
	}
      else
	{ /* top */
	  /* 3/4 color */
	  fo_pdf_draw_border_two_tone_horizontal (fo_doc,
						  color,
						  fo_color_get_color_one_quarter (color),
						  coords);
	}
    }
}

/**
 * fo_pdf_draw_border_ridge:
 * @fo_doc: #FoDoc
 * @color:  Border color
 * @coords: Coordinates of one border of an area
 * 
 * Draw a ridged border with colors based on @color and coordinates @coords.
 **/
static void
fo_pdf_draw_border_ridge (FoDoc *fo_doc,
			  FoDatatype *color,
			  FoPdfOneBorderCoords *coords)
{
  fo_doc_set_dash (fo_doc, 0.0, 0.0);

  fo_pdf_clip_to_coords (fo_doc, coords);

  if (coords->x1 == coords->x2)
    { /* vertical */
      if (coords->x1delta >= 0)
	{ /* left */
	  fo_pdf_draw_border_two_tone_vertical (fo_doc,
					    fo_color_get_color_one_half (color),
					    fo_color_get_color_three_quarter (color),
					    coords);
	}
      else
	{ /* right */
	  fo_pdf_draw_border_two_tone_vertical (fo_doc,
					     fo_color_get_color_three_quarter (color),
					     fo_color_get_color_one_half (color),
					     coords);
	}
    }
  else
    { /* horizontal */
      if (coords->y1delta >= 0)
	{ /* bottom */
	  fo_pdf_draw_border_two_tone_horizontal (fo_doc,
					      fo_color_get_color_one_half (color),
					      fo_color_get_color_three_quarter (color),
					      coords);
	}
      else
	{ /* top */
	  /* 3/4 color */
	  fo_pdf_draw_border_two_tone_horizontal (fo_doc,
					   fo_color_get_color_three_quarter (color),
					   fo_color_get_color_one_half (color),
					   coords);
	}
    }
}

/**
 * fo_pdf_draw_border_inset:
 * @fo_doc: #FoDoc
 * @color:  Border color
 * @coords: Coordinates of one border of an area
 * 
 * Draw an inset border with colors based on @color and coordinates @coords.
 **/
static void
fo_pdf_draw_border_inset (FoDoc *fo_doc,
			  FoDatatype *color,
			  FoPdfOneBorderCoords *coords)
{
  fo_doc_set_dash (fo_doc, 0.0, 0.0);

  fo_pdf_clip_to_coords (fo_doc, coords);

  if (coords->x1 == coords->x2)
    { /* vertical */
      if (coords->x1delta >= 0)
	{ /* left */
	  fo_pdf_draw_border_two_tone_vertical (fo_doc,
					    fo_color_get_color_one_half (color),
					    fo_color_get_color_one_quarter (color),
					    coords);
	}
      else
	{ /* right */
	  fo_pdf_draw_border_two_tone_vertical (fo_doc,
					     fo_color_get_color_three_quarter (color),
					     color,
					     coords);
	}
    }
  else
    { /* horizontal */
      if (coords->y1delta >= 0)
	{ /* bottom */
	  fo_pdf_draw_border_two_tone_horizontal (fo_doc,
					      fo_color_get_color_three_quarter (color),
					      color,
					      coords);
	}
      else
	{ /* top */
	  /* 1/4 color */
	  fo_pdf_draw_border_two_tone_horizontal (fo_doc,
					      fo_color_get_color_one_half (color),
					      fo_color_get_color_one_quarter (color),
					      coords);
	}
    }
}

/**
 * fo_pdf_draw_border_outset:
 * @fo_doc: #FoDoc
 * @color:  Border color
 * @coords: Coordinates of one border of an area
 * 
 * Draw an outset border with colors based on @color and coordinates @coords.
 **/
static void
fo_pdf_draw_border_outset (FoDoc *fo_doc,
			   FoDatatype *color,
			   FoPdfOneBorderCoords *coords)
{
  fo_doc_set_dash (fo_doc, 0.0, 0.0);

  fo_pdf_clip_to_coords (fo_doc, coords);

  if (coords->x1 == coords->x2)
    { /* vertical */
      if (coords->x1delta >= 0)
	{ /* left */
	  fo_pdf_draw_border_two_tone_vertical (fo_doc,
					    color,
					    fo_color_get_color_three_quarter (color),
					    coords);
	}
      else
	{ /* right */
	  fo_pdf_draw_border_two_tone_vertical (fo_doc,
					     fo_color_get_color_one_quarter (color),
					     fo_color_get_color_one_half (color),
					     coords);
	}
    }
  else
    { /* horizontal */
      if (coords->y1delta >= 0)
	{ /* bottom */
	  fo_pdf_draw_border_two_tone_horizontal (fo_doc,
					      fo_color_get_color_one_quarter (color),
					      fo_color_get_color_one_half (color),
					      coords);
	}
      else
	{ /* top */
	  /* 3/4 color */
	  fo_pdf_draw_border_two_tone_horizontal (fo_doc,
						  color,
						  fo_color_get_color_three_quarter (color),
						  coords);
	}
    }
}

/**
 * fo_pdf_draw_one_border:
 * @fo_doc:           #FoDoc
 * @border_style:     Border style
 * @x1:               X-coordinate of one corner
 * @y1:               Y-coordinate of one corner
 * @x2:               X-coordinate of the opposite corner
 * @y2:               Y-coordinate of the opposite corner
 * @x1delta:          Relative x-offset of interior corner of border
                        closest to (x1, y1)
 * @y1delta:          Relative y-offset of interior corner of border
                        closest to (x1, y1)
 * @x2delta:          Relative x-offset of interior corner of border
                        closest to (x2, y2)
 * @y2delta:          Relative y-offset of interior corner of border
                        closest to (x2, y2)
 * 
 * Draw one border by outputting PDF statements to PDF document.
 *
 * Borders are mitred, i.e., the angle between the outer corner and
 * the inner corner at the end of one border depends on both the width
 * of the border and the width of the adjacent border that is at right
 * angles to the current border.
 **/
static void
fo_pdf_draw_one_border (FoDoc *fo_doc,
			FoDatatype *color,
			FoEnumEnum border_style,
			FoPdfOneBorderCoords *coords)
{
  fo_doc_save (fo_doc);

#if defined(LIBFO_DEBUG) && 1
  g_message ("draw_one_border:: style: %d; x1: %f; y1; %f; x2: %f; y2: %f",
	     border_style, x1, y1, x2, y2);
  g_message ("                  x1delta: %f; y1delta: %f; x2delta: %f; y2delta: %f",
	     x1delta, y1delta, x2delta, y2delta);
#endif

  switch (border_style) {
  case FO_ENUM_ENUM_SOLID:
    fo_pdf_draw_border_solid (fo_doc,
			      color,
			      coords);
    break;
  case FO_ENUM_ENUM_DOUBLE:
    fo_pdf_draw_border_double (fo_doc,
			       color,
			       coords);
    break;
  case FO_ENUM_ENUM_DOTTED:
    fo_pdf_draw_border_dotted (fo_doc,
			       color,
			       coords);
    break;
  case FO_ENUM_ENUM_DASHED:
    fo_pdf_draw_border_dashed (fo_doc,
			       color,
			       coords);
    break;
  case FO_ENUM_ENUM_GROOVE:
    fo_pdf_draw_border_groove (fo_doc,
			       color,
			       coords);
    break;
  case FO_ENUM_ENUM_RIDGE:
    fo_pdf_draw_border_ridge (fo_doc,
			       color,
			       coords);
    break;
  case FO_ENUM_ENUM_INSET:
    fo_pdf_draw_border_inset (fo_doc,
			      color,
			      coords);
    break;
  case FO_ENUM_ENUM_OUTSET:
    fo_pdf_draw_border_outset (fo_doc,
			       color,
			       coords);
    break;
  default:
    g_error ("Unexpected enumeration.");
  }
  fo_doc_restore (fo_doc);
}

/**
 * fo_pdf_draw_borders:
 * @fo_doc:    #FoDoc document
 * @area_node: #FoArea node
 * 
 * Draw the borders appropriate to @area_node.
 *
 * FIXME: Does not work correctly for #FoAreaSpanningTableCell.
 **/
static void
fo_pdf_draw_borders (FoDoc  *fo_doc,
		     FoArea *area_node,
		     gdouble width,
		     gdouble height)
{
  GValue value = { 0, {{0}, {0}} };
  FoFo *fo = fo_area_get_generated_by (area_node);
  FoProperty *prop_color;
  FoProperty *prop_border_style;
  FoDatatype *color;
  FoEnumEnum border_style;
  gdouble x = fo_area_area_get_x (area_node);
  gdouble y = fo_area_area_get_y (area_node);
  gdouble border_before =
    fo_area_area_get_border_before (area_node);
  gdouble border_after =
    fo_area_area_get_border_after (area_node);
  gdouble border_start =
    fo_area_area_get_border_start (area_node);
  gdouble border_end =
    fo_area_area_get_border_end (area_node);

  g_value_init (&value, G_TYPE_OBJECT);

  /* before == top */
  if (border_before != 0.0)
    {
      g_object_get_property (G_OBJECT (fo),
			     "border-top-style",
			     &value);

      /*
	g_print ("%s\n", fo_object_sprintf (g_value_get_object (&value)));
      */
      prop_border_style = g_value_get_object (&value);
      border_style =
	fo_enum_get_value (fo_property_get_value (prop_border_style));

      if ((border_style != FO_ENUM_ENUM_NONE) &&
	  (border_style != FO_ENUM_ENUM_HIDDEN))
	{
	  FoPdfOneBorderCoords coords = {x,
					 y,
					 x + width,
					 y,
					 border_start,
					 -border_before,
					 -border_end,
					 -border_before};

	  g_object_get_property (G_OBJECT (fo),
				 "border-top-color",
				 &value);

	  prop_color = g_value_get_object (&value);

	  g_object_get_property (G_OBJECT (prop_color),
				 "value",
				 &value);

	  /*
	    g_print ("%s\n", fo_object_sprintf (g_value_get_object (&value)));
	  */
	  color = g_value_get_object (&value);

	  fo_pdf_draw_one_border (fo_doc,
				  color,
				  border_style,
				  &coords);
	}
    }	  
  /* start == left */
  if (border_start != 0.0)
    {
      g_object_get_property (G_OBJECT (fo),
			     "border-left-style",
			     &value);

      /*
	g_print ("%s", fo_object_sprintf (g_value_get_object (&value)));
      */
      prop_border_style = g_value_get_object (&value);
      border_style =
	fo_enum_get_value (fo_property_get_value (prop_border_style));

      if ((border_style != FO_ENUM_ENUM_NONE) &&
	  (border_style != FO_ENUM_ENUM_HIDDEN))
	{
	  FoPdfOneBorderCoords coords = {x,
					 y,
					 x,
					 y - height,
					 border_start,
					 -border_before,
					 border_start,
					 border_after};

	  g_object_get_property (G_OBJECT (fo),
				 "border-left-color",
				 &value);

	  prop_color = g_value_get_object (&value);

	  g_object_get_property (G_OBJECT (prop_color),
				 "value",
				 &value);

	  /*
	    g_print ("%s", fo_object_sprintf (g_value_get_object (&value)));
	  */
	  color = g_value_get_object (&value);

	  fo_pdf_draw_one_border (fo_doc,
				  color,
				  border_style,
				  &coords);
	}
    }
  /* end == right */
  if (border_end != 0.0)
    {
      g_object_get_property (G_OBJECT (fo),
			     "border-right-style",
			     &value);

      /*
	g_print ("%s", fo_object_sprintf (g_value_get_object (&value)));
      */
      prop_border_style = g_value_get_object (&value);
      border_style =
	fo_enum_get_value (fo_property_get_value (prop_border_style));

      if ((border_style != FO_ENUM_ENUM_NONE) &&
	  (border_style != FO_ENUM_ENUM_HIDDEN))
	{
	  FoPdfOneBorderCoords coords = {x + width,
					 y,
					 x + width,
					 y - height,
					 -border_end,
					 -border_before,
					 -border_end,
					 border_after};

	  g_object_get_property (G_OBJECT (fo),
				 "border-right-color",
				 &value);

	  prop_color = g_value_get_object (&value);

	  g_object_get_property (G_OBJECT (prop_color),
				 "value",
				 &value);

	  /*
	    g_print ("%s", fo_object_sprintf (g_value_get_object (&value)));
	  */
	  color = g_value_get_object (&value);

	  fo_pdf_draw_one_border (fo_doc,
				  color,
				  border_style,
				  &coords);
	}
    }
  /* after == bottom */
  if (border_after != 0.0)
    {
      g_object_get_property (G_OBJECT (fo),
			     "border-bottom-style",
			     &value);
      /*
	g_print ("%s", fo_object_sprintf (g_value_get_object (&value)));
      */
      prop_border_style = g_value_get_object (&value);
      border_style =
	fo_enum_get_value (fo_property_get_value (prop_border_style));

      if ((border_style != FO_ENUM_ENUM_NONE) &&
	  (border_style != FO_ENUM_ENUM_HIDDEN))
	{
	  FoPdfOneBorderCoords coords = {x,
					 y - height,
					 x + width,
					 y - height,
					 border_start,
					 border_after,
					 -border_end,
					 border_after};

	  g_object_get_property (G_OBJECT (fo),
				 "border-bottom-color",
				 &value);

	  prop_color = g_value_get_object (&value);

	  g_object_get_property (G_OBJECT (prop_color),
				 "value",
				 &value);

	  /*
	    g_print ("%s", fo_object_sprintf (g_value_get_object (&value)));
	  */
	  color = g_value_get_object (&value);

	  fo_pdf_draw_one_border (fo_doc,
				  color,
				  border_style,
				  &coords);
	}
    }
}

/**
 * fo_area_tree_to_pdf:
 * @area_node: #FoArea node to be output to PDF file
 * @data:      Pointer to #FoAreaToPDFData with additional data
 * 
 * Add @area_node and its descendants to the PDF document.  The PDF
 * document pointer and other required data is in @data.
 *
 * This conforms to FoAreaForeachFunc type so can use
 * fo_area_children_foreach() on any children of @area_node.
 **/
void
fo_area_tree_to_pdf (FoArea  *area_node,
		     gpointer data)
{
  FoAreaToPDFData *fo_area_to_pdf_data = (FoAreaToPDFData *) data;
  FoDoc *fo_doc;
  FoFo *fo;
  FoProperty *prop_background_color;
  FoDatatype *background_color;

  GValue value = { 0, {{0}, {0}} };

  g_value_init (&value, G_TYPE_OBJECT);

  g_return_if_fail (area_node != NULL);
  g_return_if_fail (FO_IS_AREA (area_node));

  fo_doc = fo_area_to_pdf_data->fo_doc;

  fo = fo_area_get_generated_by (area_node);

  if (FO_IS_AREA_PAGE (area_node))
    {
      fo_doc_begin_page (fo_doc,
			 fo_area_page_get_page_width (area_node),
			 fo_area_page_get_page_height (area_node),
			 NULL);

      fo_area_children_foreach (area_node,
				G_TRAVERSE_ALL,
				&fo_area_tree_to_pdf,
				(gpointer) fo_area_to_pdf_data);

      fo_doc_end_page (fo_doc);
    }
  else if (FO_IS_AREA_LAYOUT (area_node))
    {
      FoPropertyColor *prop_color;
      FoPropertyFontSize *prop_font_size;
      FoDatatype *color;
      FoDatatype *length;
      gdouble x = fo_area_area_get_x (area_node);
      gdouble y = fo_area_area_get_y (area_node);
      gdouble width = fo_area_area_get_width (area_node);
      gdouble height = fo_area_area_get_height (area_node);
      gdouble border_before =
	fo_area_area_get_border_before (area_node);
      gdouble border_start =
	fo_area_area_get_border_start (area_node);
      gdouble padding_before =
	fo_area_area_get_padding_before (area_node);
      gdouble padding_start =
	fo_area_area_get_padding_start (area_node);

      fo_doc_save (fo_doc);

      /* font-size */
      g_object_get_property (G_OBJECT (fo),
			     "font-size",
			     &value);

      prop_font_size = g_value_get_object (&value);

      g_object_get_property (G_OBJECT (prop_font_size),
			     "value",
			     &value);

      length = g_value_get_object (&value);

      /* background-color */
      g_object_get_property (G_OBJECT (fo),
			     "background-color",
			     &value);

      prop_background_color = g_value_get_object (&value);

      g_object_get_property (G_OBJECT (prop_background_color),
			     "value",
			     &value);

      background_color = g_value_get_object (&value);

      fo_pdf_draw_background (fo_doc,
			      x,
			      y,
			      width,
			      height,
			      background_color);

      /* color */
      g_object_get_property (G_OBJECT (fo),
			     "color",
			     &value);

      prop_color = g_value_get_object (&value);

      g_object_get_property (G_OBJECT (prop_color),
			     "value",
			     &value);

      color = g_value_get_object (&value);

      fo_doc_set_fill_color (fo_doc,
			     color);

#if defined(LIBFO_DEBUG) && 0
      fo_object_debug_dump (area_node, 0);
#endif

      fo_doc_render_layout_lines (fo_doc,
				  area_node,
				  x + border_start + padding_start,
				  y - border_before - padding_before);

      /* borders */
      fo_pdf_draw_borders (fo_doc, area_node, width, height);

      fo_doc_restore (fo_doc);
    }
  else if (FO_IS_AREA_NORMAL (area_node))
    {
      gdouble width = fo_area_area_get_width (area_node);
      gdouble height = fo_area_area_get_height (area_node);

      fo_pdf_draw_borders (fo_doc, area_node, width, height);

      fo_doc_translate (fo_doc,
			fo_area_area_get_x (area_node),
			fo_area_area_get_y (area_node));

      fo_area_children_foreach (area_node,
				G_TRAVERSE_ALL,
				&fo_area_tree_to_pdf,
				fo_area_to_pdf_data);
      fo_doc_translate (fo_doc,
			- fo_area_area_get_x (area_node),
			- fo_area_area_get_y (area_node));
    }
  else if (FO_IS_AREA_VIEWPORT_REFERENCE (area_node))
    {
      FoProperty *prop_overflow;
      FoEnumEnum overflow;
      gdouble x = fo_area_area_get_x (area_node);
      gdouble y = fo_area_area_get_y (area_node);
      gdouble width = fo_area_get_available_width (area_node);
      gdouble height = fo_area_get_available_height (area_node);

      /* background-color */
      g_object_get_property (G_OBJECT (fo),
			     "background-color",
			     &value);

      prop_background_color = g_value_get_object (&value);

      g_object_get_property (G_OBJECT (prop_background_color),
			     "value",
			     &value);

      background_color = g_value_get_object (&value);

      fo_pdf_draw_background (fo_doc,
			      x,
			      y,
			      width,
			      height,
			      background_color);

      /* borders */
      fo_pdf_draw_borders (fo_doc, area_node, width, height);

      fo_doc_save (fo_doc);
      fo_doc_translate (fo_doc,
			fo_area_area_get_x (area_node),
			fo_area_area_get_y (area_node));

      /* overflow */
      g_object_get_property (G_OBJECT (fo),
			     "overflow",
			     &value);
      prop_overflow = g_value_get_object (&value);
      overflow =
	fo_enum_get_value (fo_property_get_value (prop_overflow));
      if ((overflow == FO_ENUM_ENUM_HIDDEN) ||
	  (overflow == FO_ENUM_ENUM_SCROLL))
	{
	  fo_doc_move_to (fo_doc,
			  0,
			  0);
	  fo_doc_line_to (fo_doc,
			  0,
			  -height);
	  fo_doc_line_to (fo_doc,
			  width,
			  -height);
	  fo_doc_line_to (fo_doc,
			  width,
			  0);
	  fo_doc_clip (fo_doc);
	}

      fo_area_children_foreach (area_node,
				G_TRAVERSE_ALL,
				&fo_area_tree_to_pdf,
				fo_area_to_pdf_data);

      fo_doc_restore (fo_doc);
    }
  else if (FO_IS_AREA_SPANNING_TABLE_CELL (area_node))
    {
      gdouble x = fo_area_area_get_x (area_node);
      gdouble y = fo_area_area_get_y (area_node);
      gdouble width = fo_area_area_get_width (area_node);
      gdouble height = fo_area_spanning_table_cell_get_real_available_height (area_node);

      fo_doc_save (fo_doc);

      /* background-color */
      g_object_get_property (G_OBJECT (fo),
			     "background-color",
			     &value);

      prop_background_color = g_value_get_object (&value);

      g_object_get_property (G_OBJECT (prop_background_color),
			     "value",
			     &value);

      background_color = g_value_get_object (&value);

      fo_pdf_draw_background (fo_doc,
			      x,
			      y,
			      width,
			      height,
			      background_color);

      /* borders */
      fo_pdf_draw_borders (fo_doc, area_node, width, height);

      fo_doc_translate (fo_doc,
			fo_area_area_get_x (area_node),
			fo_area_area_get_y (area_node));

      fo_area_children_foreach (area_node,
				G_TRAVERSE_ALL,
				&fo_area_tree_to_pdf,
				fo_area_to_pdf_data);

      fo_doc_restore (fo_doc);
    }
  else if (FO_IS_AREA_TABLE_CONTINUATION (area_node))
    {
      FoArea *table_header = FO_AREA_TABLE_CONTINUATION (area_node)->table_header;
      gdouble x = fo_area_area_get_x (area_node);
      gdouble y = fo_area_area_get_y (area_node);
      gdouble width = fo_area_area_get_width (area_node);
      gdouble height = fo_area_area_get_height (area_node);

      if (table_header != NULL)
	{
	  fo_doc_save (fo_doc);
	  fo_doc_translate (fo_doc,
			    fo_area_area_get_x (area_node),
			    fo_area_area_get_y (area_node));

	  fo_area_tree_to_pdf (table_header,
			       fo_area_to_pdf_data);

	  fo_doc_restore (fo_doc);
	}

      fo_doc_save (fo_doc);

      /* background-color */
      g_object_get_property (G_OBJECT (fo),
			     "background-color",
			     &value);

      prop_background_color = g_value_get_object (&value);

      g_object_get_property (G_OBJECT (prop_background_color),
			     "value",
			     &value);

      background_color = g_value_get_object (&value);

      fo_pdf_draw_background (fo_doc,
			      x,
			      y -
			      (table_header ? fo_area_area_get_height (table_header) : 0.0),
			      width,
			      height,
			      background_color);

      /* borders */
      fo_pdf_draw_borders (fo_doc, area_node, width, height);

      fo_doc_translate (fo_doc,
			fo_area_area_get_x (area_node),
			fo_area_area_get_y (area_node) -
			(table_header ? fo_area_area_get_height (table_header) : 0.0) -
			(table_header ? fo_area_area_get_height (table_header) : 0.0));

      fo_area_children_foreach (area_node,
				G_TRAVERSE_ALL,
				&fo_area_tree_to_pdf,
				fo_area_to_pdf_data);

      fo_doc_restore (fo_doc);
    }
  else if (FO_IS_AREA_REFERENCE (area_node))
    {
      gdouble x = fo_area_area_get_x (area_node);
      gdouble y = fo_area_area_get_y (area_node);
      gdouble width = fo_area_area_get_width (area_node);
      gdouble height = fo_area_area_get_height (area_node);

      fo_doc_save (fo_doc);

      /* background-color */
      g_object_get_property (G_OBJECT (fo),
			     "background-color",
			     &value);

      prop_background_color = g_value_get_object (&value);

      g_object_get_property (G_OBJECT (prop_background_color),
			     "value",
			     &value);

      background_color = g_value_get_object (&value);

      fo_pdf_draw_background (fo_doc,
			      x,
			      y,
			      width,
			      height,
			      background_color);

      /* borders */
      fo_pdf_draw_borders (fo_doc, area_node, width, height);

      fo_doc_translate (fo_doc,
			fo_area_area_get_x (area_node),
			fo_area_area_get_y (area_node));

      fo_area_children_foreach (area_node,
				G_TRAVERSE_ALL,
				&fo_area_tree_to_pdf,
				fo_area_to_pdf_data);

      fo_doc_restore (fo_doc);
    }
  else if (FO_IS_AREA_AREA (area_node))
    {
      gdouble width = fo_area_area_get_width (area_node);
      gdouble height = fo_area_area_get_height (area_node);

      /* borders */
      fo_pdf_draw_borders (fo_doc, area_node, width, height);

      /* No fo_doc_save().  Instead, do reverse translate after
	 drawing children. */
      fo_doc_translate (fo_doc,
			fo_area_area_get_x (area_node),
			fo_area_area_get_y (area_node));

      fo_area_children_foreach (area_node,
				G_TRAVERSE_ALL,
				&fo_area_tree_to_pdf,
				fo_area_to_pdf_data);

      fo_doc_translate (fo_doc,
			- fo_area_area_get_x (area_node),
			- fo_area_area_get_y (area_node));
    }
  else
    {
      fo_area_children_foreach (area_node,
				G_TRAVERSE_ALL,
				&fo_area_tree_to_pdf,
				fo_area_to_pdf_data);
    }
}

