/* Fo
 * fo-layout.c: Object type for PangoLayout
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <pango/pango.h>
#include "fo-utils.h"
#include "fo-object.h"
#include "fo-layout-private.h"
#include "fo-doc-private.h"
#include "fo-font-desc-private.h"
#include "libfo-pango.h"

const char *fo_layout_error_messages [] = {
  N_("FoLayout error")
};

static void fo_layout_base_init  (FoLayoutClass *klass);
static void fo_layout_class_init (FoLayoutClass *klass);
static void fo_layout_finalize   (GObject       *object);
static void fo_layout_debug_dump (FoObject      *object,
				  gint           depth);

static void fo_layout_set_line_height_default (FoLayout *fo_layout,
					       gfloat    line_height);

static void fo_layout_set_line_stacking_strategy_default (FoLayout  *fo_layout,
							  FoEnumEnum line_stacking_strategy);

static gpointer parent_class;

/**
 * fo_layout_error_quark:
 * 
 * Get the error quark for #FoLayout.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: #GQuark associated with #FoLayout errors.
 **/
GQuark
fo_layout_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoLayout error");
  return quark;
}

/**
 * fo_layout_get_type:
 * 
 * Register the #FoLayout type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoLayout.
 **/
GType
fo_layout_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLayoutClass),
        (GBaseInitFunc) fo_layout_base_init,
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_layout_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLayout),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoLayout",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_layout_base_init:
 * @klass: #FoLayoutClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoLayoutClass.
 **/
void
fo_layout_base_init (FoLayoutClass *klass)
{
  klass->set_line_height = fo_layout_set_line_height_default;
  klass->set_line_stacking_strategy =
    fo_layout_set_line_stacking_strategy_default;
}
/**
 * fo_layout_class_init:
 * @klass: #FoLayout object to initialise.
 * 
 * Implements #GClassInitFunc for #FoLayoutClass.
 **/
void
fo_layout_class_init (FoLayoutClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_layout_finalize;

  FO_OBJECT_CLASS (klass)->debug_dump = fo_layout_debug_dump;
}

/**
 * fo_layout_finalize:
 * @object: #FoLayout object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoLayout.
 **/
void
fo_layout_finalize (GObject *object)
{
  FoLayout *fo_layout;

  fo_layout = FO_LAYOUT (object);

  /*g_object_unref (fo_layout->fo_doc);*/

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_layout_new:
 * 
 * Creates a new #FoLayout.
 * 
 * Return value: the newly created #FoLayout.
 **/
FoLayout *
fo_layout_new (void)
{
  FoLayout* fo_layout;

  fo_layout =
    g_object_new (fo_layout_get_type (),
		  NULL);

  return fo_layout;
}

/**
 * fo_layout_new_from_fo_doc:
 * @fo_doc: #FoDoc.
 * 
 * Creates a new #FoLayout.
 * 
 * Return value: the newly created #FoLayout.
 **/
FoLayout *
fo_layout_new_from_fo_doc (FoDoc *fo_doc)
{
  FoLayout* fo_layout;

  fo_layout =
    g_object_new (fo_layout_get_type (),
		  NULL);

  /* FIXME: should be g_object_ref (fo_doc) but uncertain what unrefs layout */
  fo_layout->fo_doc = fo_doc;
  fo_layout->pango_layout =
    pango_layout_new (fo_doc_get_pango_context (fo_doc));

  return fo_layout;
}

static void
fo_layout_pango_attr_list_add (gpointer data,
			       gpointer pango_attr_list)
{
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "pango_attr_list_add:: %d:%d:%d", ((PangoAttribute *) data)->klass->type,
	 ((PangoAttribute *)data)->start_index,
	 ((PangoAttribute *)data)->end_index);
#endif
  pango_attr_list_insert (pango_attr_list, data);
}


/**
 * fo_layout_set_attributes:
 * @fo_layout:  #FoLayout for which to set attributes.
 * @attr_glist: Attributes to apply to @fo_layout.
 * 
 * Sets the attributes of @fo_layout to @attr_glist.
 **/
void
fo_layout_set_attributes (FoLayout  *fo_layout,
			  GList     *attr_glist)
{
  PangoAttrList *attr_list = pango_attr_list_new ();

  g_return_if_fail (FO_IS_LAYOUT (fo_layout));

  g_list_foreach (attr_glist,
		  fo_layout_pango_attr_list_add,
		  attr_list);

  pango_layout_set_attributes (fo_layout->pango_layout,
			       attr_list);
}

/**
 * fo_layout_set_text:
 * @fo_layout: #FoLayout for which to set text.
 * @text:      New text of @fo_layout.
 * 
 * Sets the text of @fo_layout to @text.
 **/
void
fo_layout_set_text (FoLayout *fo_layout,
		    GString  *text)
{
  g_return_if_fail (FO_IS_LAYOUT (fo_layout));

  pango_layout_set_text (fo_layout->pango_layout,
			 text->str,
			 text->len);
}

/**
 * fo_layout_set_width:
 * @fo_layout: #FoLayout for which to set width.
 * @width:     New width, in points, of @fo_layout.
 * 
 * Sets the width of @fo_layout to @width.
 **/
void
fo_layout_set_width (FoLayout         *fo_layout,
		     gfloat            width)
{
  g_return_if_fail (FO_IS_LAYOUT (fo_layout));

  pango_layout_set_width (fo_layout->pango_layout,
			  width * PANGO_SCALE);
}

/**
 * fo_layout_set_font_desc:
 * @fo_layout: #FoLayout for which to set font desc.
 * @desc:      New #FoFontDesc of @fo_layout.
 * 
 * Sets the #FoFontDesc of @fo_layout to @desc.
 **/
void
fo_layout_set_font_desc (FoLayout         *fo_layout,
			 const FoFontDesc *desc)
{
  g_return_if_fail (FO_IS_LAYOUT (fo_layout));

  pango_layout_set_font_description (fo_layout->pango_layout,
				     fo_font_desc_get_font_description (desc));
}

/**
 * fo_layout_set_alignment:
 * @fo_layout: #FoLayout to have alignment set.
 * @alignment: #FoEnumAreaDirection value indicating new alignment.
 * 
 * Sets the alignment of @fo_layout.
 **/
void
fo_layout_set_alignment (FoLayout           *fo_layout,
			 FoEnumAreaDirection alignment)
{
  PangoAlignment pango_alignment = PANGO_ALIGN_LEFT;

  g_return_if_fail (FO_IS_LAYOUT (fo_layout));

  switch (alignment)
    {
    case FO_ENUM_AREA_DIRECTION_LR:
      pango_alignment = PANGO_ALIGN_LEFT;
      break;
    case FO_ENUM_AREA_DIRECTION_RL:
      pango_alignment = PANGO_ALIGN_RIGHT;
      break;
    case FO_ENUM_AREA_DIRECTION_TB:
    case FO_ENUM_AREA_DIRECTION_BT:
    case FO_ENUM_AREA_DIRECTION_UNKNOWN:
    default:
      g_assert_not_reached ();
    }

  pango_layout_set_alignment (fo_layout->pango_layout,
			      pango_alignment);
}

/**
 * fo_layout_set_indent:
 * @fo_layout: #FoLayout for which to set indent.
 * @indent:    New indent, in points, of @fo_layout.
 * 
 * Sets the indent of @fo_layout to @indent.
 **/
void
fo_layout_set_indent (FoLayout                   *fo_layout,
		      gfloat                      indent)
{
  g_return_if_fail (FO_IS_LAYOUT (fo_layout));

  pango_layout_set_indent (fo_layout->pango_layout,
			   indent * PANGO_SCALE);
}

/**
 * fo_layout_set_justify:
 * @fo_layout: #FoLayout for which to set justify.
 * @justify:   Sets whether or not to justify @fo_layout.
 * 
 * Sets whether or not to justify @fo_layout.
 **/
void
fo_layout_set_justify (FoLayout                   *fo_layout,
		       gboolean                    justify)
{
  g_return_if_fail (FO_IS_LAYOUT (fo_layout));

  pango_layout_set_justify (fo_layout->pango_layout,
			    justify);
}

/**
 * fo_layout_get_line_count:
 * @fo_layout: #FoLayout for which to get line count.
 * 
 * Gets the number of lines in @fo_layout.
 * 
 * Return value: Number of lines in @fo_layout.
 **/
gint
fo_layout_get_line_count (FoLayout    *fo_layout)
{
  g_return_val_if_fail (FO_IS_LAYOUT (fo_layout), 0);

  return pango_layout_get_line_count (fo_layout->pango_layout);
}

/**
 * fo_layout_get_extents:
 * @fo_layout:    #FoLayout for which to get extents
 * @logical_rect: #FoRectangle to hold extents
 * 
 * Gets the extents of @fo_layout and puts them in @logical_rect.
 **/
void
fo_layout_get_extents (FoLayout    *fo_layout,
		       FoRectangle *logical_rect)
{
  g_return_if_fail (FO_IS_LAYOUT (fo_layout));
  g_return_if_fail (logical_rect != NULL);

  pango_layout_get_extents (fo_layout->pango_layout,
			    NULL,
			    (PangoRectangle *) logical_rect);
}

/**
 * fo_layout_get_line_extents:
 * @fo_layout:    #FoLayout for which to get line extents.
 * @line_index:   Number of line for which to get extents.
 * @logical_rect: Holds result.
 * 
 * Puts the extents of the line of @fo_layout given by @line_index in
 * @logical_rect.
 *
 * The first line has @line_index value of 0.
 **/
void
fo_layout_get_line_extents (FoLayout    *fo_layout,
			    gint         line_index,
			    FoRectangle *logical_rect)
{
  g_return_if_fail (FO_IS_LAYOUT (fo_layout));
  g_return_if_fail (line_index >= 0);
  g_return_if_fail (logical_rect != NULL);

  pango_layout_line_get_extents (pango_layout_get_line (fo_layout->pango_layout,
							line_index),
				 NULL,
				 (PangoRectangle *) logical_rect);
}

/**
 * fo_layout_get_pango_layout:
 * @fo_layout: #FoLayout for which to get #PangoLayout
 * 
 * Gets the #PangoLayout contained by @fo_layout.
 * 
 * Return value: The #PangoLayout.
 **/
PangoLayout *
fo_layout_get_pango_layout (FoLayout *fo_layout)
{
  g_return_val_if_fail (FO_IS_LAYOUT (fo_layout), NULL);

  return fo_layout->pango_layout;
}


/**
 * fo_layout_set_line_height_default:
 * @fo_layout:   #FoLayout.
 * @line_height: 'line-height' in points.
 * 
 * Set the 'line-height' of @fo_layout to @line_height.
 **/
void
fo_layout_set_line_height_default (FoLayout *fo_layout,
				   gfloat    line_height)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_line_height' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_layout_set_line_height:
 * @fo_layout:   #FoLayout.
 * @line_height: 'line-height' in points.
 * 
 * Set the 'line-height' of @fo_layout to @line_height.
 **/
void
fo_layout_set_line_height (FoLayout *fo_layout,
			   gfloat    line_height)
{
  FO_LAYOUT_GET_CLASS (fo_layout)->set_line_height (fo_layout,
						    line_height);
}

/**
 * fo_layout_line_stacking_strategy_to_pango_line_stacking_strategy:
 * @line_stacking_strategy: Line stacking strategy value.
 * 
 * Converts @line_stacking_strategy to a #PangoLineStackingStrategy.
 * 
 * Return value: The #PangoLineStackingStrategy corresponding to
 * @line_stacking_strategy.
 **/
/*
PangoLineStackingStrategy
fo_layout_line_stacking_strategy_to_pango_line_stacking_strategy (FoEnumEnum line_stacking_strategy)
{
  switch (line_stacking_strategy)
    {
    case FO_ENUM_ENUM_LINE_HEIGHT:
      return PANGO_LINE_STACKING_STRATEGY_LINE_HEIGHT;
    case FO_ENUM_ENUM_FONT_HEIGHT:
      return PANGO_LINE_STACKING_STRATEGY_FONT_HEIGHT;
    case FO_ENUM_ENUM_MAX_HEIGHT:
      return PANGO_LINE_STACKING_STRATEGY_MAX_HEIGHT;
    default:
      return PANGO_LINE_STACKING_STRATEGY_INVALID;
    }
}
*/
/**
 * fo_layout_set_line_stacking_strategy:
 * @fo_layout:              #FoLayout.
 * @line_stacking_strategy: Line stacking strategy to use.
 * 
 * Set the 'line-stacking-strategy' property of @fo_layout to
 * @line_stacking_strategy.
 **/
void
fo_layout_set_line_stacking_strategy_default (FoLayout  *fo_layout,
					      FoEnumEnum line_stacking_strategy)
{
#if defined(LIBFO_DEBUG)
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_line_stacking_strategy' function."),
	 fo_object_sprintf (fo_doc));
#endif
}

/**
 * fo_layout_set_line_stacking_strategy:
 * @fo_layout:              #FoLayout.
 * @line_stacking_strategy: Line stacking strategy to use.
 * 
 * Set the 'line-stacking-strategy' property of @fo_layout to
 * @line_stacking_strategy.
 **/
void
fo_layout_set_line_stacking_strategy (FoLayout *fo_layout,
				      FoEnumEnum line_stacking_strategy)
{
  FO_LAYOUT_GET_CLASS (fo_layout)->set_line_stacking_strategy (fo_layout,
							       line_stacking_strategy);
}

static const char* style[] = {
  "Normal",
  "Oblique",
  "Italic"
};

static const char* variant[] = {
  "Normal",
  "Small caps"
};

static const char* stretch[] = {
  "Ultra condensed",
  "Extra condensed",
  "Condensed",
  "Semi condensed",
  "Normal",
  "Semi expanded",
  "Expanded",
  "Extra expanded",
  "Ultra expanded"
};

static const char* baseline[] = {
  "Invalid",
  "Auto",
  "Reset Size",
  "Alphabetic",
  "Ideographic",
  "Hanging",
  "Mathematical",
  "Central",
  "Middle",
  "Text Before Edge",
  "Text After Edge",
  "Before Edge",
  "After Edge",
  "Length",
  "Use Script",
  "Baseline"
};

void
fo_layout_debug_dump (FoObject *object,
		      gint      depth)
{
  FoLayout *fo_layout;
  gint start, end;
  PangoAttribute *attr;
  PangoAttrList *attr_list;
  PangoAttrIterator *iterator;

  g_return_if_fail (FO_IS_LAYOUT (object));

  fo_layout = FO_LAYOUT (object);

  attr_list = pango_layout_get_attributes (fo_layout->pango_layout);

  iterator = pango_attr_list_get_iterator (attr_list);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "dump_attr_list:: String:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d", start, end);
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "dump_attr_list:: Font family:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_FAMILY))) {
      const PangoAttrString *font_family_attr =
	(const PangoAttrString *) attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; family: %s",
	     start, end, font_family_attr->value);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "dump_attr_list:: Font size:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_SIZE))) {
      const PangoAttrInt *font_size_attr = (const PangoAttrInt *)attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; size: %g",
	     start, end, ((float) font_size_attr->value) / PANGO_SCALE);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Font weight:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_WEIGHT))) {
      const PangoAttrInt *font_weight_attr = (const PangoAttrInt *)attr;
      gint weight = font_weight_attr->value;
      gchar *weight_string;

      switch (weight)
	{
	case PANGO_WEIGHT_ULTRALIGHT:
	  weight_string = g_strdup_printf ("%d (Ultralight)",
					   PANGO_WEIGHT_ULTRALIGHT);
	  break;
	case PANGO_WEIGHT_LIGHT:
	  weight_string = g_strdup_printf ("%d (Light)",
					   PANGO_WEIGHT_LIGHT);
	  break;
	case PANGO_WEIGHT_NORMAL:
	  weight_string = g_strdup_printf ("%d (Normal)",
					   PANGO_WEIGHT_NORMAL);
	  break;
	case PANGO_WEIGHT_BOLD:
	  weight_string = g_strdup_printf ("%d (Bold)",
					   PANGO_WEIGHT_BOLD);
	  break;
	case PANGO_WEIGHT_ULTRABOLD:
	  weight_string = g_strdup_printf ("%d (Ultrabold)",
					   PANGO_WEIGHT_ULTRABOLD);
	  break;
	case PANGO_WEIGHT_HEAVY:
	  weight_string = g_strdup_printf ("%d (Heavy)",
					   PANGO_WEIGHT_HEAVY);
	  break;
	default:
	  weight_string = g_strdup_printf ("%d", weight);
	}
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; weight: %s",
	     start, end, weight_string);
      g_free (weight_string);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Font style:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_STYLE))) {
      const PangoAttrInt *font_style_attr = (const PangoAttrInt *)attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; style: %d (%s)",
		 start, end, font_style_attr->value, style[font_style_attr->value]);
    }
  }
  while (pango_attr_iterator_next (iterator));

  iterator = pango_attr_list_get_iterator (attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Font stretch:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_STRETCH))) {
      const PangoAttrInt *font_stretch_attr = (const PangoAttrInt *)attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; stretch: %d (%s)",
		 start, end, font_stretch_attr->value, stretch[font_stretch_attr->value]);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Font variant:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_VARIANT))) {
      const PangoAttrInt *font_variant_attr = (const PangoAttrInt *)attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; variant: %d (%s)",
		 start, end, font_variant_attr->value, variant[font_variant_attr->value]);
    }
  }
  while (pango_attr_iterator_next(iterator));

  /* Commenting out attributes that were in PangoXSL. */
  /*
  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Baseline shift:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_RISE))) {
      const PangoAttrInt *baseline_shift_attr = (const PangoAttrInt *)attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; size: %d",
		 start, end, baseline_shift_attr->value / PANGO_SCALE);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Line height:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					pango_attr_line_height_get_type()))) {
      const PangoAttrInt *line_height_attr = (const PangoAttrInt *)attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; line-height: %d",
		 start, end, line_height_attr->value / PANGO_SCALE);
    }
  }
  while (pango_attr_iterator_next(iterator));
  */
  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Foreground:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_FOREGROUND))) {
      const PangoAttrColor *color_attr = (const PangoAttrColor *) attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; color: %04x%04x%04x",
		 start, end, color_attr->color.red, color_attr->color.green,
		 color_attr->color.blue);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Background:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_BACKGROUND))) {
      const PangoAttrColor *color_attr = (const PangoAttrColor *) attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; color: %04x%04x%04x",
		 start, end, color_attr->color.red, color_attr->color.green,
		 color_attr->color.blue);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Shape:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					PANGO_ATTR_SHAPE))) {
      const PangoAttrShape *shape_attr = (const PangoAttrShape *) attr;
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; ink: %g, %g, %g, %g; logical: %g, %g, %g, %g",
	     start,
	     end,
	     (float) shape_attr->ink_rect.x / PANGO_SCALE,
	     (float) shape_attr->ink_rect.y / PANGO_SCALE,
	     (float) shape_attr->ink_rect.width / PANGO_SCALE,
	     (float) shape_attr->ink_rect.height / PANGO_SCALE,
	     (float) shape_attr->logical_rect.x / PANGO_SCALE,
	     (float) shape_attr->logical_rect.y / PANGO_SCALE,
	     (float) shape_attr->logical_rect.width / PANGO_SCALE,
	     (float) shape_attr->logical_rect.height / PANGO_SCALE);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Callback:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get (iterator,
					 libfo_pango_attr_callback_get_type()))) {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; pointer: %p",
	     start,
	     end,
	     libfo_pango_attr_callback_get_callback (attr));
    }
  }
  while (pango_attr_iterator_next(iterator));

  /* Commenting out attributes that were in PangoXSL. */
  /*
  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Alignment Adjust:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get (iterator,
					 pango_attr_alignment_adjust_get_type()))) {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; alignment-adjust: %d (%s)",
	     start,
	     end,
	     ((PangoAttrInt *) attr)->value,
	     baseline[((PangoAttrInt *) attr)->value]);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Alignment Baseline:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get (iterator,
					 pango_attr_alignment_baseline_get_type()))) {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; alignment-baseline: %d (%s)",
	     start,
	     end,
	     ((PangoAttrInt *) attr)->value,
	     baseline[((PangoAttrInt *) attr)->value]);
    }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: Dominant Baseline:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					pango_attr_dominant_baseline_get_type())))
      {
	const PangoAttrInt *dominant_baseline_attr = (const PangoAttrInt *)attr;
	g_log (G_LOG_DOMAIN,
	       G_LOG_LEVEL_DEBUG,
	       "dump_attr_list:: start: %d; end: %d; dominant-baseline: %d (%s)",
	       start,
	       end,
	       dominant_baseline_attr->value,
	       baseline[dominant_baseline_attr->value]);
      }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: keep-together.within-line:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					pango_attr_keep_together_within_line_get_type())))
      {
	const PangoAttrInt *ktwl_attr = (const PangoAttrInt *)attr;
	g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; keep-together.within-line: %d",
		   start, end, ktwl_attr->value);
      }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: keep-with-next.within-line:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					pango_attr_keep_with_next_within_line_get_type())))
      {
	const PangoAttrInt *kwnwl_attr = (const PangoAttrInt *)attr;
	g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; keep-with-next.within-line: %d",
		   start, end, kwnwl_attr->value);
      }
  }
  while (pango_attr_iterator_next(iterator));

  iterator = pango_attr_list_get_iterator(attr_list);
  g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: keep-with-previous.within-line:");
  do {
    pango_attr_iterator_range(iterator, &start, &end);
    if ((attr = pango_attr_iterator_get(iterator,
					pango_attr_keep_with_previous_within_line_get_type())))
      {
	const PangoAttrInt *kwpwl_attr = (const PangoAttrInt *)attr;
	g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     "dump_attr_list:: start: %d; end: %d; keep-with-next.within-line: %d",
		   start, end, kwpwl_attr->value);
      }
  }
  while (pango_attr_iterator_next(iterator));
  */
}

