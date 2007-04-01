/* Fo
 * fo-area-layout.c: Layout area object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-area-layout.c,v 1.9 2006/05/28 23:00:24 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo-text.h"
#include "libfo/fo-utils.h"
#include "libfo/fo-layout-private.h"
#include "fo-area.h"
#include "fo-area-area.h"
#include "fo-area-layout.h"
#include "fo-area-layout-private.h"
#include "fo-area-page.h"
#include "fo-property-text-align.h"
#include "fo-property-orphans.h"
#include "fo-property-widows.h"

enum {
  PROP_0,
  PROP_LAYOUT
};


static void fo_area_layout_class_init   (FoAreaLayoutClass *klass);
static void fo_area_layout_get_property (GObject           *object,
					 guint              prop_id,
					 GValue            *value,
					 GParamSpec        *pspec);
static void fo_area_layout_set_property (GObject           *object,
					 guint              prop_id,
					 const GValue      *value,
					 GParamSpec        *pspec);
static void fo_area_layout_finalize     (GObject           *object);

static void fo_area_layout_debug_dump_properties  (FoArea *area,
						   gint   depth);
static void fo_area_layout_update_after_clone     (FoArea *clone,
						   FoArea *original);
static FoArea* fo_area_layout_split_before_height (FoArea *area,
						   gfloat  max_height);
static gboolean fo_area_layout_split_before_height_check (FoArea *area,
							  gfloat max_height);
static void fo_area_layout_resolve_text_align (FoArea *area);

static gpointer parent_class;

/**
 * fo_area_layout_get_type:
 * @void: 
 * 
 * Register the #FoAreaLayout object type.
 * 
 * Return value: #GType value of the #FoAreaLayout object type.
 **/
GType
fo_area_layout_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoAreaLayoutClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_area_layout_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoAreaLayout),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL
      };
      
      object_type = g_type_register_static (FO_TYPE_AREA_AREA,
                                            "FoAreaLayout",
                                            &object_info, 0);
    }
  
  return object_type;
}

/**
 * fo_area_layout_class_init:
 * @klass: FoAreaLayoutClass object to initialise.
 * 
 * Implements GClassInitFunc for FoAreaLayoutClass.
 **/
void
fo_area_layout_class_init (FoAreaLayoutClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoAreaClass *fo_area_class = FO_AREA_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_area_layout_finalize;

  object_class->set_property = fo_area_layout_set_property;
  object_class->get_property = fo_area_layout_get_property;

  fo_area_class->debug_dump_properties =
    fo_area_layout_debug_dump_properties;
  fo_area_class->update_after_clone = fo_area_layout_update_after_clone;
  fo_area_class->split_before_height =
    fo_area_layout_split_before_height;
  fo_area_class->split_before_height_check =
    fo_area_layout_split_before_height_check;
  fo_area_class->resolve_text_align =
    fo_area_layout_resolve_text_align;

  g_object_class_install_property
    (object_class,
     PROP_LAYOUT,
     g_param_spec_pointer ("layout",
			   _("FoLayout layout"),
			   _("FoLayout layout of formatted text of block"),
			   G_PARAM_READWRITE));
}

/**
 * fo_area_layout_finalize:
 * @object: FoAreaLayout object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoAreaLayout
 **/
void
fo_area_layout_finalize (GObject *object)
{
  FoAreaLayout *fo_area_layout;

  fo_area_layout = FO_AREA_LAYOUT (object);

  g_object_unref (fo_area_layout->layout);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_area_layout_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoAreaLayout
 **/
void
fo_area_layout_get_property (GObject         *object,
			   guint            prop_id,
			   GValue          *value,
			   GParamSpec      *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_LAYOUT:
      g_value_set_pointer (value, (gpointer) fo_area_layout_get_layout (fo_area));
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_area_layout_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoAreaLayout
 **/
void
fo_area_layout_set_property (GObject         *object,
			   guint            prop_id,
			   const GValue    *value,
			   GParamSpec      *pspec)
{
  FoArea *fo_area;

  fo_area = FO_AREA (object);

  switch (prop_id)
    {
    case PROP_LAYOUT:
      fo_area_layout_set_layout (fo_area,
				 (FoLayout *) g_value_get_pointer (value));
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_area_layout_new:
 * 
 * Creates a new #FoAreaLayout initialized to default value.
 * 
 * Return value: the new #FoAreaLayout
 **/
FoArea*
fo_area_layout_new (void)
{
  return FO_AREA (g_object_new (fo_area_layout_get_type (),
				NULL));
}

/**
 * fo_area_layout_get_layout:
 * @fo_area_layout: The #FoAreaLayout object
 *
 * Gets the #layout property of @area_layout
 *
 * Return value: The "layout" property value
**/
FoLayout*
fo_area_layout_get_layout (FoArea *fo_area_layout)
{
  g_return_val_if_fail (fo_area_layout != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_LAYOUT (fo_area_layout), 0);

  return FO_AREA_LAYOUT (fo_area_layout)->layout;
}

/**
 * fo_area_area_set_layout:
 * @fo_area_layout: The #FoAreaLayout object
 * @new_layout: The new "layout" property value
 * 
 * Sets the #layout property of @area_area to @new_layout
**/
void
fo_area_layout_set_layout (FoArea   *fo_area_layout,
			   FoLayout *new_layout)
{
  g_return_if_fail (fo_area_layout != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (fo_area_layout));

  if (FO_AREA_LAYOUT (fo_area_layout)->layout != NULL)
    {
      g_object_unref (FO_AREA_LAYOUT (fo_area_layout)->layout);
    }

  FO_AREA_LAYOUT (fo_area_layout)->layout = g_object_ref (new_layout);
  /*g_object_notify (G_OBJECT (fo_area_layout), "layout");*/
}

/**
 * fo_area_layout_get_line_first:
 * @fo_area_layout: The #FoAreaLayout object
 *
 * Gets the #line-first property of @area_layout
 *
 * Return value: The "line_first" property value
**/
guint
fo_area_layout_get_line_first (FoArea *fo_area_layout)
{
  g_return_val_if_fail (fo_area_layout != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_LAYOUT (fo_area_layout), 0);

  return FO_AREA_LAYOUT (fo_area_layout)->line_first;
}

/**
 * fo_area_area_set_line_first:
 * @fo_area_layout: The #FoAreaLayout object
 * @new_line_first: The new "line_first" property value
 * 
 * Sets the #line-first property of @area_area to @new_line_first
**/
void
fo_area_layout_set_line_first (FoArea *fo_area_layout,
			       guint   new_line_first)
{
  g_return_if_fail (fo_area_layout != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (fo_area_layout));

  FO_AREA_LAYOUT (fo_area_layout)->line_first = new_line_first;
  /* g_object_notify (G_OBJECT (fo_area_layout), "line_first"); */
}

/**
 * fo_area_layout_get_line_last:
 * @fo_area_layout: The #FoAreaLayout object.
 *
 * Gets the #line-last property of @fo_area_layout.
 *
 * Return value: The "line_last" property value.
**/
guint
fo_area_layout_get_line_last (FoArea *fo_area_layout)
{
  g_return_val_if_fail (fo_area_layout != NULL, 0);
  g_return_val_if_fail (FO_IS_AREA_LAYOUT (fo_area_layout), 0);

  return FO_AREA_LAYOUT (fo_area_layout)->line_last;
}

/**
 * fo_area_layout_set_line_last:
 * @fo_area_layout: The #FoAreaLayout object.
 * @new_line_last:  The new "line_last" property value.
 * 
 * Sets the #line-last property of @fo_area_layout to @new_line_last.
**/
void
fo_area_layout_set_line_last (FoArea *fo_area_layout,
			      guint   new_line_last)
{
  g_return_if_fail (fo_area_layout != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (fo_area_layout));

  FO_AREA_LAYOUT (fo_area_layout)->line_last = new_line_last;
  /* g_object_notify (G_OBJECT (fo_area_layout), "line-last");*/
}

static void
fo_area_layout_debug_dump_line_height (gpointer value, gpointer data)
{
  gchar *indent = g_strnfill (GPOINTER_TO_INT (data) * 2, ' ');

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%1.1f",
	 indent, (float) GPOINTER_TO_INT (value) / PANGO_SCALE);

  g_free (indent);
}

/**
 * fo_area_layout_debug_dump_properties:
 * @area:  The #FoArea object
 * @depth: Indent level to add to the output
 * 
 * Logs the value of each significant property of @area then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_area_layout_debug_dump_properties (FoArea *area,
				      gint depth)
{
  FoAreaLayout *layout;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (area));

  layout = FO_AREA_LAYOUT (area);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sline heights: %p",
	 indent, layout->line_heights);
  g_slist_foreach (layout->line_heights,
		   fo_area_layout_debug_dump_line_height,
		   GINT_TO_POINTER (depth + 1));
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sline-first:   %d",
	 indent,
	 layout->line_first);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sline-last:    %d",
	 indent,
	 layout->line_last);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sFoLayout: %p",
	 indent,
	 layout->layout);

  g_free (indent);

  FO_AREA_CLASS (parent_class)->debug_dump_properties (area, depth + 1);
}

/**
 * fo_area_area_update_after_clone:
 * @clone:    New object cloned from @original
 * @original: Original area object
 * 
 * Update the FoAreaArea-specific instance variables of @clone to
 * match those of @original
 **/
void
fo_area_layout_update_after_clone (FoArea *clone,
				   FoArea *original)
{
  FoAreaLayout *original_layout, *clone_layout;

  g_return_if_fail (clone != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (clone));
  g_return_if_fail (original != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (original));

  FO_AREA_CLASS (parent_class)->update_after_clone (clone, original);

  original_layout = FO_AREA_LAYOUT (original);
  clone_layout = FO_AREA_LAYOUT (clone);

  clone_layout->layout = g_object_ref (original_layout->layout);
  clone_layout->text = original_layout->text;
  clone_layout->line_first = original_layout->line_first;
  clone_layout->line_last = original_layout->line_last;
  clone_layout->prev_portion = original_layout->prev_portion;
  clone_layout->next_portion = original_layout->next_portion;
  clone_layout->line_heights = g_slist_copy (original_layout->line_heights);
}

/**
 * fo_area_layout_split_before_height:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Split @area at or before @height.
 *
 * Return value: The part of @area spit from @area, or NULL if unsplit.
 **/
FoArea*
fo_area_layout_split_before_height (FoArea *area, gfloat max_height)
{
  FoAreaLayout *layout;
  FoArea *new_area;
  GSList *line_heights;
  gint line_count;
  gint line_first, line_last;
  gint widows, orphans;
  gint pre_widow_max;
  gfloat line_first_pre_height = 0;

  g_return_val_if_fail (FO_IS_AREA_LAYOUT (area), area);

#if defined(LIBFO_DEBUG) && 0
  g_message ("layout_split_before_height:: %p", area);
#endif
  layout = (FoAreaLayout *) area;

  line_heights = layout->line_heights;
  line_first = layout->line_first;
  line_last = layout->line_last;
  line_count = line_last - line_first + 1;
  if (line_first > 0)
    line_first_pre_height =
      (float) GPOINTER_TO_INT (g_slist_nth_data (line_heights,
						 line_first - 1)) /
      PANGO_SCALE;
			       
  widows =
    fo_integer_get_value (fo_property_get_value (fo_block_get_widows (area->generated_by)));
  orphans =
    fo_integer_get_value (fo_property_get_value (fo_block_get_orphans (area->generated_by)));

  pre_widow_max = line_last - widows;

#if defined(LIBFO_DEBUG) && 0
  g_message ("layout_split_before_height:: layout: %p; line_first: %d; line_first_pre_height: %1.1f; line_count: %d; widows: %d; orphans: %d",
	     area,
	     line_first,
	     line_first_pre_height,
	     line_count,
	     widows,
	     orphans);
#endif

  if (line_count < widows + orphans)
    {
#if defined(LIBFO_DEBUG) && 0
      g_message ("layout_split_before_height:: Not enough lines (%p): %d < %d + %d + %d",
		 area,
		 line_count,
		 widows,
		 orphans,
		 line_first);
#endif
      return NULL;
    }
  else if (max_height <
	   ((float) GPOINTER_TO_INT (g_slist_nth_data (line_heights,
						       orphans + line_first)) /
	    PANGO_SCALE) - line_first_pre_height)
    {
#if defined(LIBFO_DEBUG) && 0
      g_message ("Post-orphans exceeds available height (%p): %1.1f - %1.1f > %1.1f",
		 area,
		 (float) GPOINTER_TO_INT (g_slist_nth_data (line_heights, orphans + line_first))  / PANGO_SCALE,
		 line_first_pre_height,
		 max_height);
#endif
      return NULL;
    }
  else
    {
      gint line_index = 0;

      while (line_heights != NULL)
	{
	  if (line_index < line_first)
	    {
#if defined(LIBFO_DEBUG) && 0
	      g_message ("layout_split_before_height:: ignore:: line_index: %d; line_first: %d",
			 line_index,
			 line_first);
#endif
	    }
	  else if (line_index < orphans + line_first)
	    {
#if defined(LIBFO_DEBUG) && 0
	      g_message ("layout_split_before_height:: Can't break - orphans:: line_index: %d; line_first: %d; orphans: %d",
			 line_index,
			 line_first,
			 orphans);
#endif
	    }
	  else if (line_index >= pre_widow_max)
	    {
#if defined(LIBFO_DEBUG) && 0
	      g_message ("layout_split_before_height:: Can't break - widows:: line_index: %d; orphans: %d",
			 line_index,
			 pre_widow_max);
#endif
	      return NULL;
	    }
	  else
	    {
	      if (max_height >
		  ((float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE) - line_first_pre_height)
		{
#if defined(LIBFO_DEBUG) && 0
		  g_message ("layout_split_before_height:: fits:: line_index: %d; line height: %f; line height - line_first_pre_height: %f; max height: %f",
			     line_index,
			     (float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE,
			     (float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE - line_first_pre_height,
			     max_height);
#endif
		  if ((max_height <
		       (float) GPOINTER_TO_INT (line_heights->next->data) /
		       PANGO_SCALE - line_first_pre_height) ||
		      line_index == pre_widow_max - 1)
		    {
#if defined(LIBFO_DEBUG) && 0
		      g_message ("layout_split_before_height:: Break:: line: %d",
				 line_index);
#endif

		      new_area = fo_area_clone (area);

		      fo_area_set_is_first (new_area, FALSE);
		      fo_area_set_is_last (area, FALSE);
		      /* FIXME: handle padding */
		      /* FIXME: handle conditionality of borders and padding */
		      fo_area_area_set_border_after (area,
						     0.0);
		      fo_area_area_set_border_before (new_area,
						      0.0);
		      gboolean retain_padding_before =
			fo_length_cond_get_condity (fo_property_get_value (fo_block_get_padding_before (area->generated_by)));

		      if (!retain_padding_before)
			{
			  fo_area_area_set_padding_before (new_area,
							   0.0);
			}
		      fo_area_layout_set_line_first (new_area,
						     line_index + 1);
		      fo_area_layout_set_line_last (area,
						    line_index);
		      fo_area_area_set_height (new_area,
					       ((float) GPOINTER_TO_INT (g_slist_last (line_heights)->data)) / PANGO_SCALE -
					       (float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE + fo_area_area_get_padding_before (new_area));
		      fo_area_area_set_height (area,
					       (float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE - line_first_pre_height + fo_area_area_get_padding_before (area));
		      fo_area_resolve_text_align (area);
#if defined(LIBFO_DEBUG) && 0
		      g_message ("layout_split_before_height:: area height: %f; new_area height: %f",
				 fo_area_area_get_height (area),
				 fo_area_area_get_height (new_area));
#endif
		      /*
		      fo_area_size_request (area);
		      */
		      return new_area;
		    }
		}
	      else
		{
#if defined(LIBFO_DEBUG) && 0
		  g_message ("Line %d doesn't fit: %1.1f > %1.1f",
			     line_index,
			     (float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE,
			     max_height);
#endif
		}
	    }      
	  line_index++;
	  line_heights = line_heights->next;
	}
    }
  return NULL;
}

/**
 * fo_area_layout_split_before_height_check:
 * @area:   #FoArea to be split
 * @height: Maximum block-progression-dimension of @area
 * 
 * Check whether @area can split at or before @height.
 *
 * Return value: TRUE if can split, otherwise FALSE.
 **/
gboolean
fo_area_layout_split_before_height_check (FoArea *area, gfloat max_height)
{
  FoAreaLayout *layout;
  GSList *line_heights;
  gint line_count;
  gint line_first, line_last;
  gint widows, orphans;
  gint pre_widow_max;
  gfloat line_first_pre_height = 0;

  g_return_val_if_fail (FO_IS_AREA_LAYOUT (area), FALSE);

#if defined(LIBFO_DEBUG) && 0
  g_message ("layout_split_before_height_check:: %p", area);
#endif
  layout = (FoAreaLayout *) area;

  line_heights = layout->line_heights;
  line_first = layout->line_first;
  line_last = layout->line_last;
  line_count = line_last - line_first + 1;
  if (line_first > 0)
    line_first_pre_height =
      (float) GPOINTER_TO_INT (g_slist_nth_data (line_heights,
						 line_first - 1)) /
      PANGO_SCALE;
			       
  widows =
    fo_integer_get_value (fo_property_get_value (FO_PROPERTY (fo_block_get_widows (area->generated_by))));
  orphans =
    fo_integer_get_value (fo_property_get_value (FO_PROPERTY (fo_block_get_orphans (area->generated_by))));

  pre_widow_max = line_last - widows;

#if defined(LIBFO_DEBUG) && 0
  g_message ("layout_split_before_height_check:: layout: %p; line_first: %d; line_first_pre_height: %1.1f; line_count: %d; widows: %d; orphans: %d",
	     area,
	     line_first,
	     line_first_pre_height,
	     line_count,
	     widows,
	     orphans);
#endif
  if (line_count < widows + orphans)
    {
#if defined(LIBFO_DEBUG) && 0
      g_message ("layout_split_before_height_check:: Not enough lines (%p): %d < %d + %d + %d",
		 area,
		 line_count,
		 widows,
		 orphans,
		 line_first);
#endif
      return FALSE;
    }
  else if (max_height <
	   ((float) GPOINTER_TO_INT (g_slist_nth_data (line_heights,
						       orphans + line_first)) /
	    PANGO_SCALE) - line_first_pre_height)
    {
#if defined(LIBFO_DEBUG) && 0
      g_message ("Post-orphans exceeds available height (%p): %1.1f - %1.1f > %1.1f",
		 area,
		 (float) GPOINTER_TO_INT (g_slist_nth_data (line_heights, orphans + line_first))  / PANGO_SCALE,
		 line_first_pre_height,
		 max_height);
#endif
      return FALSE;
    }
  else
    {
      gint line_index = 0;

      while (line_heights != NULL)
	{
	  if (line_index < line_first)
	    {
#if defined(LIBFO_DEBUG) && 0
	      g_message ("layout_split_before_height_check:: ignore:: line_index: %d; line_first: %d",
			 line_index,
			 line_first);
#endif
	    }
	  else if (line_index < orphans + line_first)
	    {
#if defined(LIBFO_DEBUG) && 0
	      g_message ("layout_split_before_height_check:: Can't break - orphans:: line_index: %d; line_first: %d; orphans: %d",
			 line_index,
			 line_first,
			 orphans);
#endif
	    }
	  else if (line_index >= pre_widow_max)
	    {
#if defined(LIBFO_DEBUG) && 0
	      g_message ("layout_split_before_height_check:: Can't break - widows:: line_index: %d; orphans: %d",
			 line_index,
			 pre_widow_max);
#endif
	      return FALSE;
	    }
	  else
	    {
	      if (max_height >
		  ((float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE) - line_first_pre_height)
		{
#if defined(LIBFO_DEBUG) && 0
		  g_message ("layout_split_before_height_check:: fits:: line_index: %d; line height: %f; line height - line_first_pre_height: %f; max height: %f",
			     line_index,
			     (float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE,
			     (float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE - line_first_pre_height,
			     max_height);
#endif
		  if ((max_height <
		       (float) GPOINTER_TO_INT (line_heights->next->data) /
		       PANGO_SCALE - line_first_pre_height) ||
		      line_index == pre_widow_max - 1)
		    {
#if defined(LIBFO_DEBUG) && 0
		      g_message ("layout_split_before_height_check:: Break:: line: %d",
				 line_index);
#endif

		      return TRUE;
		    }
		}
	      else
		{
#if defined(LIBFO_DEBUG) && 0
		  g_message ("Line %d doesn't fit: %1.1f > %1.1f",
			     line_index,
			     (float) GPOINTER_TO_INT (line_heights->data) / PANGO_SCALE,
			     max_height);
#endif
		}
	    }      
	  line_index++;
	  line_heights = line_heights->next;
	}
    }
  return FALSE;
}

/**
 * fo_area_layout_resolve_text_align:
 * @area:   #FoArea.
 * 
 * Determine the Pango alignment from the XSL 'text-align' property.
 **/
static void
fo_area_layout_resolve_text_align (FoArea *area)
{
  FoAreaLayout *area_layout;
  FoEnumEnum area_align;
  PangoAlignment pango_align;
  PangoDirection base_dir;
  gint page_number_mod_2;

  g_return_if_fail (area != NULL);
  g_return_if_fail (FO_IS_AREA_LAYOUT (area));

  area_layout = FO_AREA_LAYOUT (area);

  area_align = fo_enum_get_value (fo_property_get_value (fo_block_get_text_align (area->generated_by)));

  page_number_mod_2 = fo_area_page_get_page_number (area->page) % 2;
  base_dir =
    pango_context_get_base_dir (pango_layout_get_context (fo_layout_get_pango_layout (area_layout->layout)));
  /* FIXME this will get more complicated when necessary to support
     orientation and tb writing direction */
  if (area_align == FO_ENUM_ENUM_CENTER)
    {
      pango_align = PANGO_ALIGN_CENTER;
    }
  else if ((area_align == FO_ENUM_ENUM_RIGHT) ||
      ((page_number_mod_2 == 0) &&
       (area_align == FO_ENUM_ENUM_INSIDE)) ||
      ((page_number_mod_2 == 1) &&
       (area_align == FO_ENUM_ENUM_OUTSIDE)) ||
      ((base_dir == PANGO_DIRECTION_LTR) &&
       (area_align == FO_ENUM_ENUM_END)) ||
      ((base_dir == PANGO_DIRECTION_RTL) &&
       ((area_align == FO_ENUM_ENUM_START))))
    {
      pango_align = PANGO_ALIGN_RIGHT;
    }
  else
    {
      pango_align = PANGO_ALIGN_LEFT;
    }

  pango_layout_set_alignment (fo_layout_get_pango_layout (area_layout->layout),
			      pango_align);
  pango_layout_set_auto_dir (fo_layout_get_pango_layout (area_layout->layout),
			     FALSE);
}

/**
 * fo_area_layout_get_line_height:
 * @fo_area_layout: #FoArea.
 * @line_number:    Number of the line for which to get the height.
 * 
 * Get the height of line @line_number.
 *
 * Return value: The line height in points.
 **/
gdouble
fo_area_layout_get_line_height (FoArea *fo_area_layout,
				gint    line_number)
{
  g_return_val_if_fail (fo_area_layout != NULL, 0.0);
  g_return_val_if_fail (FO_IS_AREA_LAYOUT (fo_area_layout), 0.0);

  FoAreaLayout *layout = FO_AREA_LAYOUT (fo_area_layout);

  return
    (gdouble) GPOINTER_TO_INT (g_slist_nth_data (layout->line_heights,
						 line_number)) /
    PANGO_SCALE;
}
