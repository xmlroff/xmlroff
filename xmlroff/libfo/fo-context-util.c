/* Fo
 * fo-context-util.c: Utility functions for FoContext objects
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-context-util.h"
#include "fo-context-private.h"
#include "property/fo-property-block-progression-dimension.h"
#include "property/fo-property-border-after-color.h"
#include "property/fo-property-border-after-style.h"
#include "property/fo-property-border-after-width.h"
#include "property/fo-property-border-before-color.h"
#include "property/fo-property-border-before-style.h"
#include "property/fo-property-border-before-width.h"
#include "property/fo-property-border-bottom-color.h"
#include "property/fo-property-border-bottom-style.h"
#include "property/fo-property-border-bottom-width.h"
#include "property/fo-property-border-color.h"
#include "property/fo-property-border-end-color.h"
#include "property/fo-property-border-end-style.h"
#include "property/fo-property-border-end-width.h"
#include "property/fo-property-border-left-color.h"
#include "property/fo-property-border-left-style.h"
#include "property/fo-property-border-left-width.h"
#include "property/fo-property-border-right-color.h"
#include "property/fo-property-border-right-style.h"
#include "property/fo-property-border-right-width.h"
#include "property/fo-property-border-start-color.h"
#include "property/fo-property-border-start-style.h"
#include "property/fo-property-border-start-width.h"
#include "property/fo-property-border-top-color.h"
#include "property/fo-property-border-top-style.h"
#include "property/fo-property-border-top-width.h"
#include "property/fo-property-dominant-baseline.h"
#include "property/fo-property-end-indent.h"
#include "property/fo-property-height.h"
#include "property/fo-property-inline-progression-dimension.h"
#include "property/fo-property-keep-together.h"
#include "property/fo-property-keep-together-within-column.h"
#include "property/fo-property-keep-together-within-line.h"
#include "property/fo-property-keep-together-within-page.h"
#include "property/fo-property-keep-with-next.h"
#include "property/fo-property-keep-with-next-within-column.h"
#include "property/fo-property-keep-with-next-within-line.h"
#include "property/fo-property-keep-with-next-within-page.h"
#include "property/fo-property-keep-with-previous.h"
#include "property/fo-property-keep-with-previous-within-column.h"
#include "property/fo-property-keep-with-previous-within-line.h"
#include "property/fo-property-keep-with-previous-within-page.h"
#include "property/fo-property-margin-bottom.h"
#include "property/fo-property-margin-left.h"
#include "property/fo-property-margin-right.h"
#include "property/fo-property-margin-top.h"
#include "property/fo-property-padding-left.h"
#include "property/fo-property-padding-right.h"
#include "property/fo-property-padding-top.h"
#include "property/fo-property-padding-bottom.h"
#include "property/fo-property-padding-before.h"
#include "property/fo-property-padding-after.h"
#include "property/fo-property-padding-start.h"
#include "property/fo-property-padding-end.h"
#include "property/fo-property-start-indent.h"
#include "property/fo-property-space-after.h"
#include "property/fo-property-space-before.h"
#include "property/fo-property-space-end.h"
#include "property/fo-property-space-start.h"
#include "property/fo-property-width.h"
#include "property/fo-property-writing-mode.h"
#include "area/fo-area-area.h"
#include "area/fo-area-reference.h"
#include "datatype/fo-all-datatype.h"

/**
 * fo_context_util_height_width_resolve:
 * @current_context: #FoContext of the current #FoFo.
 * @parent_context:  #FoContext of the parent #FoFo of the current #FoFo.
 * 
 * Resolve "height", "width", "inline-progression-dimension", and
 * "block-progression-dimension" property values.
 **/
void
fo_context_util_height_width_resolve (FoContext *current_context,
				      FoContext *parent_context)
{
  FoEnumAreaDirection bpd;
  FoProperty *writing_mode;
  FoProperty *height;
  FoProperty *width;
  FoProperty *block_progression_dimension;
  FoProperty *inline_progression_dimension;

  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  height = current_context->height;
  width = current_context->width;
  block_progression_dimension =
    current_context->block_progression_dimension;
  inline_progression_dimension =
    current_context->inline_progression_dimension;

  if (current_context->writing_mode != NULL)
    writing_mode = current_context->writing_mode;
  else
    writing_mode = parent_context->writing_mode;

  bpd = fo_property_writing_mode_to_bpd (writing_mode, NULL);

  if (height == NULL &&
      width == NULL &&
      block_progression_dimension != NULL &&
      inline_progression_dimension != NULL)
    {
#if defined(LIBFO_DEBUG) && 0
      g_message ("height_width_resolve:: don't bother.");
#endif
      return;
    }

#if defined(LIBFO_DEBUG) && 0
  g_message ("height_width_resolve:: before:: bpd: %d", bpd);
  fo_object_debug_dump (writing_mode, 0);
  fo_object_debug_dump (height, 0);
  fo_object_debug_dump (width, 0);
  fo_object_debug_dump (block_progression_dimension, 0);
  fo_object_debug_dump (inline_progression_dimension, 0);
#endif

  if (block_progression_dimension == NULL)
    {
      block_progression_dimension =
	fo_property_block_progression_dimension_get_initial ();
    }

  if (inline_progression_dimension == NULL)
    {
      inline_progression_dimension =
	fo_property_inline_progression_dimension_get_initial ();
    }

  if (bpd == FO_ENUM_AREA_DIRECTION_TB ||
      bpd == FO_ENUM_AREA_DIRECTION_BT)
    {
      if (height != NULL)
	{
	  FoDatatype *height_value = fo_property_get_value (height);
	  FoDatatype *length_range = g_object_new (FO_TYPE_LENGTH_RANGE,
						   "minimum",
						   height_value,
						   "optimum",
						   height_value,
						   "maximum",
						   height_value,
						   NULL);
	  fo_property_set_value (block_progression_dimension,
				 length_range);
	}

      if (width != NULL)
	{
	  FoDatatype *width_value = fo_property_get_value (width);
	  FoDatatype *length_range = g_object_new (FO_TYPE_LENGTH_RANGE,
						   "minimum",
						   width_value,
						   "optimum",
						   width_value,
						   "maximum",
						   width_value,
						   NULL);
	  fo_property_set_value (inline_progression_dimension,
				 length_range);
	}
    }
  else if (bpd == FO_ENUM_AREA_DIRECTION_LR ||
	   bpd == FO_ENUM_AREA_DIRECTION_RL)
    {
      if (width != NULL)
	{
	  FoDatatype *width_value = fo_property_get_value (width);
	  FoDatatype *length_range = g_object_new (FO_TYPE_LENGTH_RANGE,
						   "minimum",
						   width_value,
						   "optimum",
						   width_value,
						   "maximum",
						   width_value,
						   NULL);
	  fo_property_set_value (block_progression_dimension,
				 length_range);
	}


      if (height != NULL)
	{
	  FoDatatype *height_value = fo_property_get_value (height);
	  FoDatatype *length_range = g_object_new (FO_TYPE_LENGTH_RANGE,
						   "minimum",
						   height_value,
						   "optimum",
						   height_value,
						   "maximum",
						   height_value,
						   NULL);
	  fo_property_set_value (inline_progression_dimension,
				 length_range);
	}

    }
  else
    {
      g_assert_not_reached ();
    }

  /* This may be setting the properties to the same values, but it may not,
     especially since block_progression_dimension and
     inline_progression_dimension may have been NULL initially. */
  fo_context_set_block_progression_dimension (current_context,
					      block_progression_dimension);
  fo_context_set_inline_progression_dimension (current_context,
					       inline_progression_dimension);

#if defined(LIBFO_DEBUG) && 0
  g_message ("height_width_resolve:: after:: bpd: %d", bpd);
  fo_object_debug_dump (height, 0),
    fo_object_debug_dump (width, 0),
    fo_object_debug_dump (block_progression_dimension, 0),
    fo_object_debug_dump (inline_progression_dimension, 0),
    fo_object_debug_dump (writing_mode, 0);
#endif
}

/**
 * fo_context_util_keeps_resolve:
 * @current_context: #FoContext of the current #FoFo.
 * @parent_context:  #FoContext of the parent #FoFo of the current #FoFo.
 * 
 * Resolve the components of the various keep properties.
 *
 * "keep-together" is inherited; "keep-with-next" and
 * "keep-with-previous" are not inherited.
 **/
void
fo_context_util_keeps_resolve (FoContext *current_context,
			       FoContext *parent_context)
{
  FoProperty *shortform;
  FoProperty *within_line;
  FoProperty *within_column;
  FoProperty *within_page;
  FoDatatype *use_shortform;

  shortform = fo_context_get_keep_together (current_context);
  if (shortform == NULL)
    {
      shortform = fo_context_get_keep_together (parent_context);
    }
  within_line = fo_context_get_keep_together_within_line (current_context);
  within_column = fo_context_get_keep_together_within_column (current_context);
  within_page = fo_context_get_keep_together_within_page (current_context);

  use_shortform =
    fo_keep_resolve (fo_property_get_value (shortform),
		     within_line ? fo_property_get_value (within_line) : NULL,
		     within_column ? fo_property_get_value (within_column) : NULL,
		     within_page ? fo_property_get_value (within_page) : NULL,
		     NULL);

  fo_context_set_keep_together (current_context,
				g_object_new (FO_TYPE_PROPERTY_KEEP_TOGETHER,
					      "value",
					      use_shortform,
					      NULL));
  fo_context_set_keep_together_within_line (current_context, NULL);
  fo_context_set_keep_together_within_column (current_context, NULL);
  fo_context_set_keep_together_within_page (current_context, NULL);

  shortform =
    fo_context_get_keep_with_previous (current_context);
  if (shortform == NULL)
    {
      shortform = fo_property_keep_with_previous_get_initial ();
    }
  within_line =
    fo_context_get_keep_with_previous_within_line (current_context);
  within_column =
    fo_context_get_keep_with_previous_within_column (current_context);
  within_page =
    fo_context_get_keep_with_previous_within_page (current_context);

  use_shortform =
    fo_keep_resolve (fo_property_get_value (shortform),
		     within_line ? fo_property_get_value (within_line) : NULL,
		     within_column ? fo_property_get_value (within_column) : NULL,
		     within_page ? fo_property_get_value (within_page) : NULL,
		     NULL);

  fo_context_set_keep_with_previous (current_context,
				     g_object_new (FO_TYPE_PROPERTY_KEEP_WITH_PREVIOUS,
						   "value",
						   use_shortform,
						   NULL));
  fo_context_set_keep_with_previous_within_line (current_context, NULL);
  fo_context_set_keep_with_previous_within_column (current_context, NULL);
  fo_context_set_keep_with_previous_within_page (current_context, NULL);

  shortform =
    fo_context_get_keep_with_next (current_context);
  if (shortform == NULL)
    {
      shortform = fo_property_keep_with_next_get_initial ();
    }
  within_line =
    fo_context_get_keep_with_next_within_line (current_context);
  within_column =
    fo_context_get_keep_with_next_within_column (current_context);
  within_page =
    fo_context_get_keep_with_next_within_page (current_context);

  use_shortform =
    fo_keep_resolve (fo_property_get_value (shortform),
		     within_line ? fo_property_get_value (within_line) : NULL,
		     within_column ? fo_property_get_value (within_column) : NULL,
		     within_page ? fo_property_get_value (within_page) : NULL,
		     NULL);

  fo_context_set_keep_with_next (current_context,
				 g_object_new (FO_TYPE_PROPERTY_KEEP_WITH_NEXT,
					       "value",
					       use_shortform,
					       NULL));
  fo_context_set_keep_with_next_within_line (current_context, NULL);
  fo_context_set_keep_with_next_within_column (current_context, NULL);
  fo_context_set_keep_with_next_within_page (current_context, NULL);
}

/**
 * fo_context_util_length_ranges_resolve:
 * @context:        The #FoContext object whose spaces will be resolved
 * @reference_area: #FoAreaReference to use when resolving percentages
 * 
 * Resolve the components of the various length-range-valued
 * properties and set @context accordingly
 **/
void
fo_context_util_length_ranges_resolve (FoContext *context,
				       FoArea    *reference_area)
{
  GError *tmp_error = NULL;
  FoDatatype *length_range = NULL;
  FoDatatype *shorthand, *minimum, *optimum, *maximum;
  gfloat available_width = 0.0;
  gfloat available_height = 0.0;

  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));
  g_return_if_fail (reference_area == NULL ||
		    FO_IS_AREA_REFERENCE (reference_area));

#if defined(LIBFO_DEBUG) && 0
  g_message ("length_ranges_resolve:: bpdim:: shortform: %s; minimum: %s; optimum: %s; maximum: %s; reference: %s",
	     fo_object_sprintf (context->block_progression_dimension),
	     fo_object_sprintf (context->block_progression_dimension_minimum),
	     fo_object_sprintf (context->block_progression_dimension_optimum),
	     fo_object_sprintf (context->block_progression_dimension_maximum);
	     fo_object_sprintf (reference_area));
#endif

  if (reference_area != NULL)
    {
      available_width = fo_area_get_child_available_ipdim (reference_area);
      available_height = fo_area_get_child_available_bpdim (reference_area);
    }

  /* Block-progression-dimension, i.e., vertical */
  /* FIXME: won't always be vertical once can change reference orientation */
  shorthand =
    context->block_progression_dimension ?
    fo_property_get_value (context->block_progression_dimension) : NULL;
  minimum =
    context->block_progression_dimension_minimum ?
    fo_property_get_value (context->block_progression_dimension_minimum) : NULL;
  optimum =
    context->block_progression_dimension_optimum ?
    fo_property_get_value (context->block_progression_dimension_optimum) : NULL;
  maximum =
    context->block_progression_dimension_maximum ?
    fo_property_get_value (context->block_progression_dimension_maximum) : NULL;

  length_range = fo_length_range_resolve_allow_auto (shorthand,
						     minimum,
						     optimum,
						     maximum,
						     available_height,
						     &tmp_error);
#if defined(LIBFO_DEBUG) && 0
  g_message ("context_length_ranges_resolve:: bpdim::");
  fo_object_debug_dump (length_range, 0);
#endif

  if (length_range != NULL)
    {
      fo_context_set_block_progression_dimension (context,
						  g_object_new (FO_TYPE_PROPERTY_BLOCK_PROGRESSION_DIMENSION,
								"value",
								length_range,
								NULL));
      g_object_unref (length_range);
    }
  else
    {
      fo_context_set_block_progression_dimension (context, NULL);
    }

  fo_context_set_block_progression_dimension_minimum (context, NULL);
  fo_context_set_block_progression_dimension_optimum (context, NULL);
  fo_context_set_block_progression_dimension_maximum (context, NULL);

  shorthand =
    context->inline_progression_dimension ?
    fo_property_get_value (context->inline_progression_dimension) : NULL;
  minimum =
    context->inline_progression_dimension_minimum ?
    fo_property_get_value (context->inline_progression_dimension_minimum) : NULL;
  optimum =
    context->inline_progression_dimension_optimum ?
    fo_property_get_value (context->inline_progression_dimension_optimum) : NULL;
  maximum =
    context->inline_progression_dimension_maximum ?
    fo_property_get_value (context->inline_progression_dimension_maximum) : NULL;

  length_range = fo_length_range_resolve_allow_auto (shorthand,
						     minimum,
						     optimum,
						     maximum,
						     available_width,
						     &tmp_error);
#if defined(LIBFO_DEBUG) && 0
  g_message ("context_length_ranges_resolve:: ipdim::");
  fo_object_debug_dump (length_range, 0);
#endif

  if (length_range != NULL)
    {
      FoProperty *new_ipd = g_object_new (FO_TYPE_PROPERTY_INLINE_PROGRESSION_DIMENSION,
					  "value",
					  length_range,
					  NULL);
      fo_context_set_inline_progression_dimension (context, new_ipd);
      g_object_unref (new_ipd);
      g_object_unref (length_range);
    }
  else
    {
      fo_context_set_inline_progression_dimension (context, NULL);
    }

  fo_context_set_inline_progression_dimension_minimum (context, NULL);
  fo_context_set_inline_progression_dimension_optimum (context, NULL);
  fo_context_set_inline_progression_dimension_maximum (context, NULL);
}

/**
 * fo_context_util_spaces_resolve:
 * @context:        The #FoContext object whose spaces will be resolved.
 * @reference_area: Reference area used when resolving percentages.
 * 
 * Resolve the components of the various space-valued properties and
 * set @context accordingly.
 **/
void
fo_context_util_spaces_resolve (FoContext *context,
				FoArea    *reference_area)
{
  GError *tmp_error = NULL;
  FoDatatype *space;
  FoDatatype *shorthand;
  FoDatatype *minimum;
  FoDatatype *optimum;
  FoDatatype *maximum;
  FoDatatype *precedence;
  FoDatatype *condity;
  gdouble hundred_percent;

  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  /* Reference area is same for resolving all space properties. */
  hundred_percent =
    reference_area != NULL ?
    fo_area_get_child_available_bpdim (reference_area): 0.0;

  /* space-before */
  shorthand =
    context->space_before != NULL ?
    fo_property_get_value (context->space_before) : NULL;
  minimum =
    context->space_before_minimum != NULL ?
    fo_property_get_value (context->space_before_minimum) : NULL;
  optimum =
    context->space_before_optimum != NULL ?
    fo_property_get_value (context->space_before_optimum) : NULL;
  maximum =
    context->space_before_maximum != NULL ?
    fo_property_get_value (context->space_before_maximum) : NULL;
  precedence =
    context->space_before_precedence != NULL ?
    fo_property_get_value (context->space_before_precedence) : NULL;
  condity =
    context->space_before_condity != NULL ?
    fo_property_get_value (context->space_before_condity) : NULL;

  space = fo_space_resolve (shorthand,
			    minimum,
			    optimum,
			    maximum,
			    precedence,
			    condity,
			    hundred_percent,
			    &tmp_error);

  if (space != NULL)
    {
      FoProperty *new_space_before = g_object_new (FO_TYPE_PROPERTY_SPACE_BEFORE,
						   "value",
						   space,
						   NULL);
      fo_context_set_space_before (context, new_space_before);
      g_object_unref (new_space_before);
    }
  else
    {
      fo_context_set_space_before (context, NULL);
    }

  g_object_unref (space);
  space = NULL;

  fo_context_set_space_before_minimum (context, NULL);
  fo_context_set_space_before_optimum (context, NULL);
  fo_context_set_space_before_maximum (context, NULL);
  fo_context_set_space_before_precedence (context, NULL);
  fo_context_set_space_before_condity (context, NULL);

  /* space-after */
  shorthand =
    context->space_after ?
    fo_property_get_value (context->space_after) : NULL;
  minimum =
    context->space_after_minimum ?
    fo_property_get_value (context->space_after_minimum) : NULL;
  optimum =
    context->space_after_optimum ?
    fo_property_get_value (context->space_after_optimum) : NULL;
  maximum =
    context->space_after_maximum ?
    fo_property_get_value (context->space_after_maximum) : NULL;
  precedence =
    context->space_after_precedence ?
    fo_property_get_value (context->space_after_precedence) : NULL;
  condity =
    context->space_after_condity ?
    fo_property_get_value (context->space_after_condity) : NULL;

  space = fo_space_resolve (shorthand,
			    minimum,
			    optimum,
			    maximum,
			    precedence,
			    condity,
			    hundred_percent,
			    &tmp_error);

  if (space != NULL)
    {
      FoProperty *new_space_after = g_object_new (FO_TYPE_PROPERTY_SPACE_AFTER,
						  "value",
						  space,
						  NULL);
      fo_context_set_space_after (context, new_space_after);
      g_object_unref (new_space_after);
    }
  else
    {
      fo_context_set_space_after (context, NULL);
    }

  g_object_unref (space);
  space = NULL;

  fo_context_set_space_after_minimum (context, NULL);
  fo_context_set_space_after_optimum (context, NULL);
  fo_context_set_space_after_maximum (context, NULL);
  fo_context_set_space_after_precedence (context, NULL);
  fo_context_set_space_after_condity (context, NULL);

  /* space-start */
  shorthand =
    context->space_start ?
    fo_property_get_value (context->space_start) : NULL;
  minimum =
    context->space_start_minimum ?
    fo_property_get_value (context->space_start_minimum) : NULL;
  optimum =
    context->space_start_optimum ?
    fo_property_get_value (context->space_start_optimum) : NULL;
  maximum =
    context->space_start_maximum ?
    fo_property_get_value (context->space_start_maximum) : NULL;
  precedence =
    context->space_start_precedence ?
    fo_property_get_value (context->space_start_precedence) : NULL;
  condity =
    context->space_start_condity ?
    fo_property_get_value (context->space_start_condity) : NULL;

  space = fo_space_resolve (shorthand,
			    minimum,
			    optimum,
			    maximum,
			    precedence,
			    condity,
			    hundred_percent,
			    &tmp_error);

  if (space != NULL)
    {
      FoProperty *new_space_start = g_object_new (FO_TYPE_PROPERTY_SPACE_START,
						  "value",
						  space,
						  NULL);
      fo_context_set_space_start (context, new_space_start);
      g_object_unref (new_space_start);
    }
  else
    {
      fo_context_set_space_start (context, NULL);
    }

  g_object_unref (space);
  space = NULL;

  /* space-end */
  shorthand =
    context->space_end ?
    fo_property_get_value (context->space_end) : NULL;
  minimum =
    context->space_end_minimum ?
    fo_property_get_value (context->space_end_minimum) : NULL;
  optimum =
    context->space_end_optimum ?
    fo_property_get_value (context->space_end_optimum) : NULL;
  maximum =
    context->space_end_maximum ?
    fo_property_get_value (context->space_end_maximum) : NULL;
  precedence =
    context->space_end_precedence ?
    fo_property_get_value (context->space_end_precedence) : NULL;
  condity =
    context->space_end_condity ?
    fo_property_get_value (context->space_end_condity) : NULL;

  space = fo_space_resolve (shorthand,
			    minimum,
			    optimum,
			    maximum,
			    precedence,
			    condity,
			    hundred_percent,
			    &tmp_error);

  if (space != NULL)
    {
      FoProperty *new_space_end = g_object_new (FO_TYPE_PROPERTY_SPACE_END,
						"value",
						space,
						NULL);
      fo_context_set_space_end (context, new_space_end);
      g_object_unref (new_space_end);
    }
  else
    {
      fo_context_set_space_end (context, NULL);
    }

  g_object_unref (space);
  space = NULL;
}

/**
 * fo_context_util_margins_indents_resolve:
 * @fo:              Current #FoFo.
 * @current_context: #FoContext of the current #FoFo.
 * @parent_context:  #FoContext of the parent #FoFo of the current #FoFo.
 * 
 * Resolve the 'margin-left', 'start-indent', 'margin-right', and
 * 'end-indent' property values of @fo.
 **/
void
fo_context_util_margins_indents_resolve (FoFo *fo,
					 FoContext *current_context,
					 FoContext *parent_context)
{
  FoProperty *current_indent_prop, *current_margin_prop;
  gfloat current_indent = 0;
  gfloat current_margin = 0;
  gfloat parent_indent, padding, border_width;

  g_return_if_fail (current_context != NULL);
  g_return_if_fail (parent_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  /* FIXME: Doesn't handle case of absolute margin from shorthand
     since shorthands not supported yet. */

#if defined(LIBFO_DEBUG) && 0
  if (fo_fo_get_generate_reference_area (fo))
    {
      g_message ("margin_indent_resolve:: generates reference area: %s",
		 fo_object_debug_sprintf (fo));
    }
#endif
  

  /* left margin and start indent/padding/border-width */
  padding =
    fo_length_get_value (fo_property_get_value (fo_context_get_padding_start (current_context)));
  border_width =
    fo_length_get_value (fo_property_get_value (fo_context_get_border_start_width (current_context)));


  current_margin_prop = fo_context_get_margin_left (current_context);
  if (current_margin_prop != NULL)
    {
      current_margin =
	fo_length_get_value (fo_property_get_value (current_margin_prop));

      if (fo_fo_get_generate_reference_area (fo))
	{
	  current_indent =
	    current_margin + padding + border_width;
	}
      else
	{
	  parent_indent =
	    fo_length_get_value (fo_property_get_value (fo_context_get_start_indent (parent_context)));

	  current_indent =
	    parent_indent + current_margin + padding + border_width;
	}

      current_indent_prop =
	g_object_new (FO_TYPE_PROPERTY_START_INDENT,
		      "value",
		      g_object_new (FO_TYPE_LENGTH,
				    "value",
				    current_indent,
				    NULL),
		      NULL);
      fo_context_set_start_indent (current_context, current_indent_prop);
    }
  else /* current_margin_prop == NULL */
    {
      parent_indent =
	fo_length_get_value (fo_property_get_value (fo_context_get_start_indent (parent_context)));

      current_indent_prop = fo_context_get_start_indent (current_context);
      if (current_indent_prop == NULL)
	{
	  current_indent = parent_indent;
	}
      else
	{
	  current_indent =
	    fo_length_get_value (fo_property_get_value (current_indent_prop));
	}

      current_margin =
	current_indent - parent_indent - padding - border_width;

      current_margin_prop =
	g_object_new (FO_TYPE_PROPERTY_MARGIN_LEFT,
		      "value",
		      g_object_new (FO_TYPE_LENGTH,
				    "value",
				    current_margin,
				    NULL),
		      NULL);
      fo_context_set_margin_left (current_context, current_margin_prop);
    }
  
  /* right margin and end indent/padding/border-width */
  parent_indent =
    fo_length_get_value (fo_property_get_value (fo_context_get_end_indent (parent_context)));
  padding =
    fo_length_get_value (fo_property_get_value (fo_context_get_padding_end (current_context)));
  border_width =
    fo_length_get_value (fo_property_get_value (fo_context_get_border_end_width (current_context)));

  current_margin_prop = fo_context_get_margin_right (current_context);
  if (current_margin_prop != NULL)
    {
      current_margin =
	fo_length_get_value (fo_property_get_value (current_margin_prop));

      if (fo_fo_get_generate_reference_area (fo))
	{
	  current_indent =
	    current_margin + padding + border_width;
	}
      else
	{
	  parent_indent =
	    fo_length_get_value (fo_property_get_value (fo_context_get_end_indent (parent_context)));

	  current_indent =
	    parent_indent + current_margin + padding + border_width;
	}

      current_indent_prop =
	g_object_new (FO_TYPE_PROPERTY_END_INDENT,
		      "value",
		      g_object_new (FO_TYPE_LENGTH,
				    "value",
				    current_indent,
				    NULL),
		      NULL);
      fo_context_set_end_indent (current_context, current_indent_prop);
    }
  else /* current_margin_prop == NULL */
    {
      parent_indent =
	fo_length_get_value (fo_property_get_value (fo_context_get_end_indent (parent_context)));

      current_indent_prop = fo_context_get_end_indent (current_context);
      if (current_indent_prop == NULL)
	{
	  current_indent = parent_indent;
	}
      else
	{
	  current_indent =
	    fo_length_get_value (fo_property_get_value (current_indent_prop));
	}

      current_margin =
	current_indent - parent_indent - padding - border_width;

      current_margin_prop =
	g_object_new (FO_TYPE_PROPERTY_MARGIN_RIGHT,
		      "value",
		      g_object_new (FO_TYPE_LENGTH,
				    "value",
				    current_margin,
				    NULL),
		      NULL);
      fo_context_set_margin_right (current_context, current_margin_prop);
    }
}

typedef FoProperty* (*FoPropertyTypeNew)       ();
typedef FoProperty* (*FoPropertyTypeInitial)   ();
typedef FoProperty* (*FoContextPropertyGetter) (FoContext  *context);

typedef void        (*FoContextPropertySetter) (FoContext  *context,
						FoProperty *new_property);
typedef FoDatatype* (*FoPropertyGetter)        (FoProperty *property);


typedef struct _FoContextPropertyFunc
{
  FoPropertyTypeNew       new;
  FoPropertyTypeInitial   initial;
  FoContextPropertyGetter getter;
  FoContextPropertySetter setter;
  FoContextPropertyGetter length_getter;
  FoContextPropertyGetter condity_getter;
} FoContextPropertyFunc;

/**
 * resolve_absolute_relative_padding:
 * @context:       #FoContext of the current #FoFo.
 * @absolute_func:
 * @relative_func:
 * 
 * Resolve padding property values.
 **/
static void
resolve_absolute_relative_padding (FoContext               *context,
				   FoContextPropertyFunc   *absolute_func,
				   FoContextPropertyFunc   *relative_func,
				   FoDatatype              *shorthand_component)
{				   
  FoProperty *absolute;
  FoProperty *relative;
  FoProperty *length;
  FoProperty *condity;
  FoDatatype *datatype;

  absolute = absolute_func->getter (context);

  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = relative_func->new ();
      fo_property_set_value (relative, datatype);
      relative_func->setter (context, relative);
    }
  else if (shorthand_component != NULL)
    {
      relative = relative_func->new ();
      fo_property_set_value (relative, shorthand_component);
      relative_func->setter (context, relative);

      absolute = absolute_func->new ();
      fo_property_set_value (absolute, shorthand_component);
      absolute_func->setter (context, absolute);
    }
  else
    {
      relative = relative_func->getter (context);
      length = relative_func->length_getter (context);
      condity = relative_func->condity_getter (context);

      if (relative != NULL || length != NULL || condity != NULL)
	{
	  FoDatatype *relative_datatype =
	    relative == NULL ? NULL : fo_property_get_value (relative);
	  FoDatatype *length_datatype =
	    length == NULL ? NULL : fo_property_get_value (length);
	  FoDatatype *condity_datatype =
	    condity == NULL ? NULL : fo_property_get_value (condity);

	  datatype = fo_length_cond_resolve (relative_datatype,
					     length_datatype,
					     condity_datatype,
					     NULL);

	  relative = relative_func->new ();
	  fo_property_set_value (relative, datatype);
	  relative_func->setter (context, relative);
	  absolute = absolute_func->new ();
	  fo_property_set_value (absolute, datatype);
	  absolute_func->setter (context, absolute);
	}
      else
	{
	  absolute = absolute_func->initial ();
	  absolute_func->setter (context, absolute);
	  relative = relative_func->initial ();
	  relative_func->setter (context, relative);
	}
    }
}

/**
 * fo_context_util_paddings_resolve:
 * @current_context: #FoContext of the current #FoFo.
 * @parent_context:  #FoContext of the parent #FoFo of the current #FoFo.
 * 
 * Resolve padding property values.
 **/
void
fo_context_util_paddings_resolve (FoContext *current_context,
				  FoContext *parent_context)
{
  FoContextPropertyFunc absolute_func;
  FoContextPropertyFunc relative_func;
  FoDatatype *shorthand_component;

  g_return_if_fail (current_context != NULL);
  g_return_if_fail (parent_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  /*
  fo_object_debug_dump (fo_context_get_padding (current_context),
			0);
  */

  FoDatatype *padding_tblr = NULL;

  FoProperty *padding = fo_context_get_padding (current_context);

  if (padding != NULL)
    {
      padding_tblr = fo_property_get_value (padding);
    }

  /* top <--> before */

  if (padding_tblr != NULL)
    {
      shorthand_component = fo_tblr_get_top (padding_tblr);
    }
  else
    {
      shorthand_component = NULL;
    }

  absolute_func.new     = fo_property_padding_top_new;
  absolute_func.initial = fo_property_padding_top_get_initial;
  absolute_func.getter  = fo_context_get_padding_top;
  absolute_func.setter  = fo_context_set_padding_top;

  relative_func.new            = fo_property_padding_before_new;
  relative_func.initial        = fo_property_padding_before_get_initial;
  relative_func.getter         = fo_context_get_padding_before;
  relative_func.setter         = fo_context_set_padding_before;
  relative_func.length_getter  = fo_context_get_padding_before_length;
  relative_func.condity_getter = fo_context_get_padding_before_condity;

  resolve_absolute_relative_padding (current_context,
				     &absolute_func,
				     &relative_func,
				     shorthand_component);

  /* bottom <--> after */

  if (padding_tblr != NULL)
    {
      shorthand_component = fo_tblr_get_bottom (padding_tblr);
    }
  else
    {
      shorthand_component = NULL;
    }

  absolute_func.new     = fo_property_padding_bottom_new;
  absolute_func.initial = fo_property_padding_bottom_get_initial;
  absolute_func.getter  = fo_context_get_padding_bottom;
  absolute_func.setter  = fo_context_set_padding_bottom;

  relative_func.new            = fo_property_padding_after_new;
  relative_func.initial        = fo_property_padding_after_get_initial;
  relative_func.getter         = fo_context_get_padding_after;
  relative_func.setter         = fo_context_set_padding_after;
  relative_func.length_getter  = fo_context_get_padding_after_length;
  relative_func.condity_getter = fo_context_get_padding_after_condity;

  resolve_absolute_relative_padding (current_context,
				     &absolute_func,
				     &relative_func,
				     shorthand_component);

  /* left <--> start */

  if (padding_tblr != NULL)
    {
      shorthand_component = fo_tblr_get_left (padding_tblr);
    }
  else
    {
      shorthand_component = NULL;
    }

  absolute_func.new     = fo_property_padding_left_new;
  absolute_func.initial = fo_property_padding_left_get_initial;
  absolute_func.getter  = fo_context_get_padding_left;
  absolute_func.setter  = fo_context_set_padding_left;

  relative_func.new            = fo_property_padding_start_new;
  relative_func.initial        = fo_property_padding_start_get_initial;
  relative_func.getter         = fo_context_get_padding_start;
  relative_func.setter         = fo_context_set_padding_start;
  relative_func.length_getter  = fo_context_get_padding_start_length;
  relative_func.condity_getter = fo_context_get_padding_start_condity;

  resolve_absolute_relative_padding (current_context,
				     &absolute_func,
				     &relative_func,
				     shorthand_component);

  /* right <--> end */

  if (padding_tblr != NULL)
    {
      shorthand_component = fo_tblr_get_right (padding_tblr);
    }
  else
    {
      shorthand_component = NULL;
    }

  absolute_func.new     = fo_property_padding_right_new;
  absolute_func.initial = fo_property_padding_right_get_initial;
  absolute_func.getter  = fo_context_get_padding_right;
  absolute_func.setter  = fo_context_set_padding_right;

  relative_func.new            = fo_property_padding_end_new;
  relative_func.initial        = fo_property_padding_end_get_initial;
  relative_func.getter         = fo_context_get_padding_end;
  relative_func.setter         = fo_context_set_padding_end;
  relative_func.length_getter  = fo_context_get_padding_end_length;
  relative_func.condity_getter = fo_context_get_padding_end_condity;

  resolve_absolute_relative_padding (current_context,
				     &absolute_func,
				     &relative_func,
				     shorthand_component);
}

/**
 * fo_context_util_margins_resolve:
 * @current_context: #FoContext of the current #FoFo.
 * @parent_context:  #FoContext of the parent #FoFo of the current #FoFo.
 * 
 * Resolve padding property values.
 **/
void
fo_context_util_margins_resolve (FoContext *current_context,
				 FoContext *parent_context)
{
  FoProperty *absolute, *relative;
  FoDatatype *datatype;

  g_return_if_fail (current_context != NULL);
  g_return_if_fail (parent_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  /* left = start*/
  absolute = fo_context_get_margin_left (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_space_start_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_space_start (current_context, relative);
    }
  else
    {
      relative = fo_context_get_space_start (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_margin_left_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_margin_left (current_context, absolute);
	}
      else
	{
	  absolute = fo_property_margin_left_new ();
	  fo_context_set_margin_left (current_context, absolute);
	  relative = fo_property_space_start_get_initial ();
	  fo_context_set_space_start (current_context, relative);
	}
    }
  /* right = end*/
  absolute = fo_context_get_margin_right (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_space_end_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_space_end (current_context, relative);
    }
  else
    {
      relative = fo_context_get_space_end (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_margin_right_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_margin_right (current_context, absolute);
	}
      else
	{
	  absolute = fo_property_margin_right_get_initial ();
	  fo_context_set_margin_right (current_context, absolute);
	  relative = fo_property_space_end_get_initial ();
	  fo_context_set_space_end (current_context, relative);
	}
    }
  /* top = before*/
  absolute = fo_context_get_margin_top (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_space_before_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_space_before (current_context, relative);
    }
  else
    {
      relative = fo_context_get_space_before (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_margin_top_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_margin_top (current_context, absolute);
	}
      else
	{
	  absolute = fo_property_margin_top_get_initial ();
	  fo_context_set_margin_top (current_context, absolute);
	  relative = fo_property_space_before_get_initial ();
	  fo_context_set_space_before (current_context, relative);
	}
    }
  /* bottom = after*/
  absolute = fo_context_get_margin_bottom (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_space_after_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_space_after (current_context, relative);
    }
  else
    {
      relative = fo_context_get_space_after (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_margin_bottom_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_margin_bottom (current_context, absolute);
	}
      else
	{
	  absolute = fo_property_margin_bottom_get_initial ();
	  fo_context_set_margin_bottom (current_context, absolute);
	  relative = fo_property_space_after_get_initial ();
	  fo_context_set_space_after (current_context, relative);
	}
    }
}

/**
 * fo_context_util_border_resolve:
 * @current_context: #FoContext of the current #FoFo.
 * @parent_context:  #FoContext of the parent #FoFo of the current #FoFo.
 * 
 * Resolve the border properties of @current_context.
 *
 * @parent_context is needed to get the 'color' property value if it
 * is NULL in @current_context.
 **/
void
fo_context_util_border_resolve (FoContext *current_context,
				FoContext *parent_context)
{
  FoProperty *absolute, *relative;
  FoDatatype *datatype;
  FoProperty *prop_color;
  FoDatatype *initial_color;

  g_return_if_fail (current_context != NULL);
  g_return_if_fail (parent_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  /* If neither the absolute nor relative color is specified, use the
   * same color as is used for text.
   */
  prop_color = fo_context_get_color (current_context);
  if (prop_color == NULL)
    {
      prop_color = fo_context_get_color (parent_context);
    }

  initial_color = fo_property_get_value (prop_color);

  FoProperty *border_color = fo_context_get_border_color (current_context);

  FoDatatype *border_color_tblr = NULL;

  if (border_color != NULL)
    {
      border_color_tblr = fo_property_get_value (border_color);
    }

  FoDatatype *border_color_component;

  FoProperty *border_style = fo_context_get_border_style (current_context);

  FoDatatype *border_style_tblr = NULL;

  if (border_style != NULL)
    {
      border_style_tblr = fo_property_get_value (border_style);
    }

  FoDatatype *border_style_component;

  FoProperty *border_width = fo_context_get_border_width (current_context);

  FoDatatype *border_width_tblr = NULL;

  if (border_width != NULL)
    {
      border_width_tblr = fo_property_get_value (border_width);
    }

  FoDatatype *border_width_component;

  FoProperty *border = fo_context_get_border (current_context);

  FoDatatype *border_wsc = NULL;

  if (border != NULL)
    {
      border_wsc = fo_property_get_value (border);
    }

  FoDatatype *border_component;

  FoProperty *border_bottom = fo_context_get_border_bottom (current_context);

  FoDatatype *border_bottom_wsc = NULL;

  if (border_bottom != NULL)
    {
      border_bottom_wsc = fo_property_get_value (border_bottom);
    }

  FoDatatype *border_bottom_component;

  FoProperty *border_left = fo_context_get_border_left (current_context);

  FoDatatype *border_left_wsc = NULL;

  if (border_left != NULL)
    {
      border_left_wsc = fo_property_get_value (border_left);
    }

  FoDatatype *border_left_component;

  FoProperty *border_right = fo_context_get_border_right (current_context);

  FoDatatype *border_right_wsc = NULL;

  if (border_right != NULL)
    {
      border_right_wsc = fo_property_get_value (border_right);
    }

  FoDatatype *border_right_component;

  FoProperty *border_top = fo_context_get_border_top (current_context);

  FoDatatype *border_top_wsc = NULL;

  if (border_top != NULL)
    {
      border_top_wsc = fo_property_get_value (border_top);
    }

  FoDatatype *border_top_component;

  /* left = start*/
  /* style */
  absolute = fo_context_get_border_left_style (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_border_start_style_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_border_start_style (current_context, relative);
    }
  else
    {
      relative = fo_context_get_border_start_style (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_border_left_style_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_border_left_style (current_context, absolute);
	}
      else
	{
	  if (border_left_wsc != NULL)
	    {
	      border_left_component = fo_wsc_get_style (border_left_wsc);
	    }
	  else
	    {
	      border_left_component = NULL;
	    }
	  if (border_left_component != NULL)
	    {
	      absolute = fo_property_border_left_style_new ();
	      fo_property_set_value (absolute, border_left_component);
	      fo_context_set_border_left_style (current_context, absolute);
	      relative = fo_property_border_start_style_new ();
	      fo_property_set_value (relative, border_left_component);
	      fo_context_set_border_start_style (current_context, relative);
	    }
	  else
	    {
	      if (border_style_tblr != NULL)
		{
		  border_style_component = fo_tblr_get_left (border_style_tblr);
		}
	      else
		{
		  border_style_component = NULL;
		}
	      if (border_style_component != NULL)
		{
		  absolute = fo_property_border_left_style_new ();
		  fo_property_set_value (absolute, border_style_component);
		  fo_context_set_border_left_style (current_context, absolute);
		  relative = fo_property_border_start_style_new ();
		  fo_property_set_value (relative, border_style_component);
		  fo_context_set_border_start_style (current_context, relative);
		}
	      else
		{
		  if (border_wsc != NULL)
		    {
		      border_component = fo_wsc_get_style (border_wsc);
		    }
		  else
		    {
		      border_component = NULL;
		    }
		  if (border_component != NULL)
		    {
		      absolute = fo_property_border_left_style_new ();
		      fo_property_set_value (absolute, border_component);
		      fo_context_set_border_left_style (current_context, absolute);
		      relative = fo_property_border_start_style_new ();
		      fo_property_set_value (relative, border_component);
		      fo_context_set_border_start_style (current_context, relative);
		    }
		  else
		    {
		      absolute = fo_property_border_left_style_get_initial ();
		      fo_context_set_border_left_style (current_context, absolute);
		      relative = fo_property_border_start_style_get_initial ();
		      fo_context_set_border_start_style (current_context, relative);
		    }
		}
	    }
	}
    }
  /* width */
  datatype = fo_property_get_value (absolute);
  if ((fo_enum_get_value (datatype) == FO_ENUM_ENUM_NONE) ||
      (fo_enum_get_value (datatype) == FO_ENUM_ENUM_HIDDEN))
    {
      absolute = g_object_new (FO_TYPE_PROPERTY_BORDER_LEFT_WIDTH,
			       "value",
			       fo_length_get_length_zero (),
			       NULL);
      fo_context_set_border_left_width (current_context, absolute);
      relative = g_object_new (FO_TYPE_PROPERTY_BORDER_START_WIDTH,
			       "value",
			       fo_length_get_length_zero (),
			       NULL);
      fo_context_set_border_start_width (current_context, relative);
    }
  else
    {
      absolute = fo_context_get_border_left_width (current_context);
      if (absolute != NULL)
	{
	  datatype = fo_property_get_value (absolute);
	  relative = fo_property_border_start_width_new ();
	  fo_property_set_value (relative, datatype);
	  fo_context_set_border_start_width (current_context, relative);
	}
      else
	{
	  relative = fo_context_get_border_start_width (current_context);
	  if (relative != NULL)
	    {
	      datatype = fo_property_get_value (relative);
	      absolute = fo_property_border_left_width_new ();
	      fo_property_set_value (absolute, datatype);
	      fo_context_set_border_left_width (current_context, absolute);
	    }
	  else
	    {
	      if (border_left_wsc != NULL)
		{
		  border_left_component = fo_wsc_get_width (border_left_wsc);
		}
	      else
		{
		  border_left_component = NULL;
		}
	      if (border_left_component != NULL)
		{
		  absolute = fo_property_border_left_width_new ();
		  fo_property_set_value (absolute, border_left_component);
		  fo_context_set_border_left_width (current_context, absolute);
		  relative = fo_property_border_start_width_new ();
		  fo_property_set_value (relative, border_left_component);
		  fo_context_set_border_start_width (current_context, relative);
		}
	      else
		{
		  if (border_width_tblr != NULL)
		    {
		      border_width_component = fo_tblr_get_left (border_width_tblr);
		    }
		  else
		    {
		      border_width_component = NULL;
		    }
		  if (border_width_component != NULL)
		    {
		      absolute = fo_property_border_left_width_new ();
		      fo_property_set_value (absolute, border_width_component);
		      fo_context_set_border_left_width (current_context, absolute);
		      relative = fo_property_border_start_width_new ();
		      fo_property_set_value (relative, border_width_component);
		      fo_context_set_border_start_width (current_context, relative);
		    }
		  else
		    {
		      if (border_wsc != NULL)
			{
			  border_component = fo_wsc_get_width (border_wsc);
			}
		      else
			{
			  border_component = NULL;
			}
		      if (border_component != NULL)
			{
			  absolute = fo_property_border_left_width_new ();
			  fo_property_set_value (absolute, border_component);
			  fo_context_set_border_left_width (current_context, absolute);
			  relative = fo_property_border_start_width_new ();
			  fo_property_set_value (relative, border_component);
			  fo_context_set_border_start_width (current_context, relative);
			}
		      else
			{
			  absolute = fo_property_border_left_width_get_initial ();
			  fo_context_set_border_left_width (current_context, absolute);
			  relative = fo_property_border_start_width_get_initial ();
			  fo_context_set_border_start_width (current_context, relative);
			}
		    }
		}
	    }
	}
    }
  /* color */
  absolute = fo_context_get_border_left_color (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_border_start_color_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_border_start_color (current_context, relative);
    }
  else
    {
      relative = fo_context_get_border_start_color (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_border_left_color_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_border_left_color (current_context, absolute);
	}
      else
	{
	  if (border_left_wsc != NULL)
	    {
	      border_left_component = fo_wsc_get_color (border_left_wsc);
	    }
	  else
	    {
	      border_left_component = NULL;
	    }
	  if (border_left_component != NULL)
	    {
	      absolute = fo_property_border_left_color_new ();
	      fo_property_set_value (absolute, border_left_component);
	      fo_context_set_border_left_color (current_context, absolute);
	      relative = fo_property_border_start_color_new ();
	      fo_property_set_value (relative, border_left_component);
	      fo_context_set_border_start_color (current_context, relative);
	    }
	  else
	    {
	      if (border_color_tblr != NULL)
		{
		  border_color_component = fo_tblr_get_left (border_color_tblr);
		}
	      else
		{
		  border_color_component = NULL;
		}
	      if (border_color_component != NULL)
		{
		  absolute = fo_property_border_left_color_new ();
		  fo_property_set_value (absolute, border_color_component);
		  fo_context_set_border_left_color (current_context, absolute);
		  relative = fo_property_border_start_color_new ();
		  fo_property_set_value (relative, border_color_component);
		  fo_context_set_border_start_color (current_context, relative);
		}
	      else
		{
		  if (border_wsc != NULL)
		    {
		      border_component = fo_wsc_get_color (border_wsc);
		    }
		  else
		    {
		      border_component = NULL;
		    }
		  if (border_component != NULL)
		    {
		      absolute = fo_property_border_left_color_new ();
		      fo_property_set_value (absolute, border_component);
		      fo_context_set_border_left_color (current_context, absolute);
		      relative = fo_property_border_start_color_new ();
		      fo_property_set_value (relative, border_component);
		      fo_context_set_border_start_color (current_context, relative);
		    }
		  else
		    {
		      prop_color = g_object_new (FO_TYPE_PROPERTY_BORDER_LEFT_COLOR,
						 "value",
						 initial_color,
						 NULL);
		      fo_context_set_border_left_color (current_context, prop_color);
		      prop_color = g_object_new (FO_TYPE_PROPERTY_BORDER_START_COLOR,
						 "value",
						 initial_color,
						 NULL);
		      fo_context_set_border_start_color (current_context, prop_color);
		    }
		}
	    }
	}
    }
  /* right = end*/
  /* style */
  absolute = fo_context_get_border_right_style (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_border_end_style_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_border_end_style (current_context, relative);
    }
  else
    {
      relative = fo_context_get_border_end_style (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_border_right_style_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_border_right_style (current_context, absolute);
	}
      else
	{
	  if (border_right_wsc != NULL)
	    {
	      border_right_component = fo_wsc_get_style (border_right_wsc);
	    }
	  else
	    {
	      border_right_component = NULL;
	    }
	  if (border_right_component != NULL)
	    {
	      absolute = fo_property_border_right_style_new ();
	      fo_property_set_value (absolute, border_right_component);
	      fo_context_set_border_right_style (current_context, absolute);
	      relative = fo_property_border_end_style_new ();
	      fo_property_set_value (relative, border_right_component);
	      fo_context_set_border_end_style (current_context, relative);
	    }
	  else
	    {
	      if (border_style_tblr != NULL)
		{
		  border_style_component = fo_tblr_get_right (border_style_tblr);
		}
	      else
		{
		  border_style_component = NULL;
		}
	      if (border_style_component != NULL)
		{
		  absolute = fo_property_border_right_style_new ();
		  fo_property_set_value (absolute, border_style_component);
		  fo_context_set_border_right_style (current_context, absolute);
		  relative = fo_property_border_end_style_new ();
		  fo_property_set_value (relative, border_style_component);
		  fo_context_set_border_end_style (current_context, relative);
		}
	      else
		{
		  if (border_wsc != NULL)
		    {
		      border_component = fo_wsc_get_style (border_wsc);
		    }
		  else
		    {
		      border_component = NULL;
		    }
		  if (border_component != NULL)
		    {
		      absolute = fo_property_border_right_style_new ();
		      fo_property_set_value (absolute, border_component);
		      fo_context_set_border_right_style (current_context, absolute);
		      relative = fo_property_border_end_style_new ();
		      fo_property_set_value (relative, border_component);
		      fo_context_set_border_end_style (current_context, relative);
		    }
		  else
		    {
		      absolute = fo_property_border_right_style_get_initial ();
		      fo_context_set_border_right_style (current_context, absolute);
		      relative = fo_property_border_end_style_get_initial ();
		      fo_context_set_border_end_style (current_context, relative);
		    }
		}
	    }
	}
    }
  /* width */
  datatype = fo_property_get_value (absolute);
  if ((fo_enum_get_value (datatype) == FO_ENUM_ENUM_NONE) ||
      (fo_enum_get_value (datatype) == FO_ENUM_ENUM_HIDDEN))
    {
      absolute = g_object_new (FO_TYPE_PROPERTY_BORDER_RIGHT_WIDTH,
			       "value",
			       fo_length_get_length_zero (),
			       NULL);
      fo_context_set_border_right_width (current_context, absolute);
      relative = g_object_new (FO_TYPE_PROPERTY_BORDER_END_WIDTH,
			       "value",
			       fo_length_get_length_zero (),
			       NULL);
      fo_context_set_border_end_width (current_context, relative);
    }
  else
    {
      absolute = fo_context_get_border_right_width (current_context);
      if (absolute != NULL)
	{
	  datatype = fo_property_get_value (absolute);
	  relative = fo_property_border_end_width_new ();
	  fo_property_set_value (relative, datatype);
	  fo_context_set_border_end_width (current_context, relative);
	}
      else
	{
	  relative = fo_context_get_border_end_width (current_context);
	  if (relative != NULL)
	    {
	      datatype = fo_property_get_value (relative);
	      absolute = fo_property_border_right_width_new ();
	      fo_property_set_value (absolute, datatype);
	      fo_context_set_border_right_width (current_context, absolute);
	    }
	  else
	    {
	      if (border_right_wsc != NULL)
		{
		  border_right_component = fo_wsc_get_width (border_right_wsc);
		}
	      else
		{
		  border_right_component = NULL;
		}
	      if (border_right_component != NULL)
		{
		  absolute = fo_property_border_right_width_new ();
		  fo_property_set_value (absolute, border_right_component);
		  fo_context_set_border_right_width (current_context, absolute);
		  relative = fo_property_border_end_width_new ();
		  fo_property_set_value (relative, border_right_component);
		  fo_context_set_border_end_width (current_context, relative);
		}
	      else
		{
		  if (border_width_tblr != NULL)
		    {
		      border_width_component = fo_tblr_get_right (border_width_tblr);
		    }
		  else
		    {
		      border_width_component = NULL;
		    }
		  if (border_width_component != NULL)
		    {
		      absolute = fo_property_border_right_width_new ();
		      fo_property_set_value (absolute, border_width_component);
		      fo_context_set_border_right_width (current_context, absolute);
		      relative = fo_property_border_end_width_new ();
		      fo_property_set_value (relative, border_width_component);
		      fo_context_set_border_end_width (current_context, relative);
		    }
		  else
		    {
		      if (border_wsc != NULL)
			{
			  border_component = fo_wsc_get_width (border_wsc);
			}
		      else
			{
			  border_component = NULL;
			}
		      if (border_component != NULL)
			{
			  absolute = fo_property_border_right_width_new ();
			  fo_property_set_value (absolute, border_component);
			  fo_context_set_border_right_width (current_context, absolute);
			  relative = fo_property_border_end_width_new ();
			  fo_property_set_value (relative, border_component);
			  fo_context_set_border_end_width (current_context, relative);
			}
		      else
			{
			  absolute = fo_property_border_right_width_get_initial ();
			  fo_context_set_border_right_width (current_context, absolute);
			  relative = fo_property_border_end_width_get_initial ();
			  fo_context_set_border_end_width (current_context, relative);
			}
		    }
		}
	    }
	}
    }
  /* color */
  absolute = fo_context_get_border_right_color (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_border_end_color_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_border_end_color (current_context, relative);
    }
  else
    {
      relative = fo_context_get_border_end_color (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_border_right_color_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_border_right_color (current_context, absolute);
	}
      else
	{
	  if (border_right_wsc != NULL)
	    {
	      border_right_component = fo_wsc_get_color (border_right_wsc);
	    }
	  else
	    {
	      border_right_component = NULL;
	    }
	  if (border_right_component != NULL)
	    {
	      absolute = fo_property_border_right_color_new ();
	      fo_property_set_value (absolute, border_right_component);
	      fo_context_set_border_right_color (current_context, absolute);
	      relative = fo_property_border_end_color_new ();
	      fo_property_set_value (relative, border_right_component);
	      fo_context_set_border_end_color (current_context, relative);
	    }
	  else
	    {
	      if (border_color_tblr != NULL)
		{
		  border_color_component = fo_tblr_get_right (border_color_tblr);
		}
	      else
		{
		  border_color_component = NULL;
		}
	      if (border_color_component != NULL)
		{
		  absolute = fo_property_border_right_color_new ();
		  fo_property_set_value (absolute, border_color_component);
		  fo_context_set_border_right_color (current_context, absolute);
		  relative = fo_property_border_end_color_new ();
		  fo_property_set_value (relative, border_color_component);
		  fo_context_set_border_end_color (current_context, relative);
		}
	      else
		{
		  if (border_wsc != NULL)
		    {
		      border_component = fo_wsc_get_color (border_wsc);
		    }
		  else
		    {
		      border_component = NULL;
		    }
		  if (border_component != NULL)
		    {
		      absolute = fo_property_border_right_color_new ();
		      fo_property_set_value (absolute, border_component);
		      fo_context_set_border_right_color (current_context, absolute);
		      relative = fo_property_border_end_color_new ();
		      fo_property_set_value (relative, border_component);
		      fo_context_set_border_end_color (current_context, relative);
		    }
		  else
		    {
		      prop_color = g_object_new (FO_TYPE_PROPERTY_BORDER_RIGHT_COLOR,
						 "value",
						 initial_color,
						 NULL);
		      fo_context_set_border_right_color (current_context, prop_color);
		      prop_color = g_object_new (FO_TYPE_PROPERTY_BORDER_END_COLOR,
						 "value",
						 initial_color,
						 NULL);
		      fo_context_set_border_end_color (current_context, prop_color);
		    }
		}
	    }
	}
    }
  /* top = before*/
  /* style */
  absolute = fo_context_get_border_top_style (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_border_before_style_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_border_before_style (current_context, relative);
    }
  else
    {
      relative = fo_context_get_border_before_style (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_border_top_style_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_border_top_style (current_context, absolute);
	}
      else
	{
	  if (border_top_wsc != NULL)
	    {
	      border_top_component = fo_wsc_get_style (border_top_wsc);
	    }
	  else
	    {
	      border_top_component = NULL;
	    }
	  if (border_top_component != NULL)
	    {
	      absolute = fo_property_border_top_style_new ();
	      fo_property_set_value (absolute, border_top_component);
	      fo_context_set_border_top_style (current_context, absolute);
	      relative = fo_property_border_before_style_new ();
	      fo_property_set_value (relative, border_top_component);
	      fo_context_set_border_before_style (current_context, relative);
	    }
	  else
	    {
	      if (border_style_tblr != NULL)
		{
		  border_style_component = fo_tblr_get_top (border_style_tblr);
		}
	      else
		{
		  border_style_component = NULL;
		}
	      if (border_style_component != NULL)
		{
		  absolute = fo_property_border_top_style_new ();
		  fo_property_set_value (absolute, border_style_component);
		  fo_context_set_border_top_style (current_context, absolute);
		  relative = fo_property_border_before_style_new ();
		  fo_property_set_value (relative, border_style_component);
		  fo_context_set_border_before_style (current_context, relative);
		}
	      else
		{
		  if (border_wsc != NULL)
		    {
		      border_component = fo_wsc_get_style (border_wsc);
		    }
		  else
		    {
		      border_component = NULL;
		    }
		  if (border_component != NULL)
		    {
		      absolute = fo_property_border_top_style_new ();
		      fo_property_set_value (absolute, border_component);
		      fo_context_set_border_top_style (current_context, absolute);
		      relative = fo_property_border_before_style_new ();
		      fo_property_set_value (relative, border_component);
		      fo_context_set_border_before_style (current_context, relative);
		    }
		  else
		    {
		      absolute = fo_property_border_top_style_get_initial ();
		      fo_context_set_border_top_style (current_context, absolute);
		      relative = fo_property_border_before_style_get_initial ();
		      fo_context_set_border_before_style (current_context, relative);
		    }
		}
	    }
	}
    }
  /* width */
  datatype = fo_property_get_value (absolute);
  if ((fo_enum_get_value (datatype) == FO_ENUM_ENUM_NONE) ||
      (fo_enum_get_value (datatype) == FO_ENUM_ENUM_HIDDEN))
   {
      absolute = g_object_new (FO_TYPE_PROPERTY_BORDER_TOP_WIDTH,
			       "value",
			       fo_length_get_length_zero (),
			       NULL);
      fo_context_set_border_top_width (current_context, absolute);
      relative = g_object_new (FO_TYPE_PROPERTY_BORDER_BEFORE_WIDTH,
			       "value",
			       fo_length_get_length_zero (),
			       NULL);
      fo_context_set_border_before_width (current_context, relative);
    }
  else
    {
      absolute = fo_context_get_border_top_width (current_context);
      if (absolute != NULL)
	{
	  datatype = fo_property_get_value (absolute);
	  relative = fo_property_border_before_width_new ();
	  fo_property_set_value (relative, datatype);
	  fo_context_set_border_before_width (current_context, relative);
	}
      else
	{
	  relative = fo_context_get_border_before_width (current_context);
	  if (relative != NULL)
	    {
	      datatype = fo_property_get_value (relative);
	      absolute = fo_property_border_top_width_new ();
	      fo_property_set_value (absolute, datatype);
	      fo_context_set_border_top_width (current_context, absolute);
	    }
	  else
	    {
	      if (border_top_wsc != NULL)
		{
		  border_top_component = fo_wsc_get_width (border_top_wsc);
		}
	      else
		{
		  border_top_component = NULL;
		}
	      if (border_top_component != NULL)
		{
		  absolute = fo_property_border_top_width_new ();
		  fo_property_set_value (absolute, border_top_component);
		  fo_context_set_border_top_width (current_context, absolute);
		  relative = fo_property_border_before_width_new ();
		  fo_property_set_value (relative, border_top_component);
		  fo_context_set_border_before_width (current_context, relative);
		}
	      else
		{
		  if (border_width_tblr != NULL)
		    {
		      border_width_component = fo_tblr_get_top (border_width_tblr);
		    }
		  else
		    {
		      border_width_component = NULL;
		    }
		  if (border_width_component != NULL)
		    {
		      absolute = fo_property_border_top_width_new ();
		      fo_property_set_value (absolute, border_width_component);
		      fo_context_set_border_top_width (current_context, absolute);
		      relative = fo_property_border_before_width_new ();
		      fo_property_set_value (relative, border_width_component);
		      fo_context_set_border_before_width (current_context, relative);
		    }
		  else
		    {
		      if (border_wsc != NULL)
			{
			  border_component = fo_wsc_get_width (border_wsc);
			}
		      else
			{
			  border_component = NULL;
			}
		      if (border_component != NULL)
			{
			  absolute = fo_property_border_top_width_new ();
			  fo_property_set_value (absolute, border_component);
			  fo_context_set_border_top_width (current_context, absolute);
			  relative = fo_property_border_before_width_new ();
			  fo_property_set_value (relative, border_component);
			  fo_context_set_border_before_width (current_context, relative);
			}
		      else
			{
			  absolute = fo_property_border_top_width_get_initial ();
			  fo_context_set_border_top_width (current_context, absolute);
			  relative = fo_property_border_before_width_get_initial ();
			  fo_context_set_border_before_width (current_context, relative);
			}
		    }
		}
	    }
	}
    }
  /* color */
  absolute = fo_context_get_border_top_color (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_border_before_color_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_border_before_color (current_context, relative);
    }
  else
    {
      relative = fo_context_get_border_before_color (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_border_top_color_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_border_top_color (current_context, absolute);
	}
      else
	{
	  if (border_top_wsc != NULL)
	    {
	      border_top_component = fo_wsc_get_color (border_top_wsc);
	    }
	  else
	    {
	      border_top_component = NULL;
	    }
	  if (border_top_component != NULL)
	    {
	      absolute = fo_property_border_top_color_new ();
	      fo_property_set_value (absolute, border_top_component);
	      fo_context_set_border_top_color (current_context, absolute);
	      relative = fo_property_border_before_color_new ();
	      fo_property_set_value (relative, border_top_component);
	      fo_context_set_border_before_color (current_context, relative);
	    }
	  else
	    {
	      if (border_color_tblr != NULL)
		{
		  border_color_component = fo_tblr_get_top (border_color_tblr);
		}
	      else
		{
		  border_color_component = NULL;
		}
	      if (border_color_component != NULL)
		{
		  absolute = fo_property_border_top_color_new ();
		  fo_property_set_value (absolute, border_color_component);
		  fo_context_set_border_top_color (current_context, absolute);
		  relative = fo_property_border_before_color_new ();
		  fo_property_set_value (relative, border_color_component);
		  fo_context_set_border_before_color (current_context, relative);
		}
	      else
		{
		  if (border_wsc != NULL)
		    {
		      border_component = fo_wsc_get_color (border_wsc);
		    }
		  else
		    {
		      border_component = NULL;
		    }
		  if (border_component != NULL)
		    {
		      absolute = fo_property_border_top_color_new ();
		      fo_property_set_value (absolute, border_component);
		      fo_context_set_border_top_color (current_context, absolute);
		      relative = fo_property_border_before_color_new ();
		      fo_property_set_value (relative, border_component);
		      fo_context_set_border_before_color (current_context, relative);
		    }
		  else
		    {
		      prop_color = g_object_new (FO_TYPE_PROPERTY_BORDER_TOP_COLOR,
						 "value",
						 initial_color,
						 NULL);
		      fo_context_set_border_top_color (current_context, prop_color);
		      prop_color = g_object_new (FO_TYPE_PROPERTY_BORDER_BEFORE_COLOR,
						 "value",
						 initial_color,
						 NULL);
		      fo_context_set_border_before_color (current_context, prop_color);
		    }
		}
	    }
	}
    }
  /* bottom = after*/
  /* style */
  absolute = fo_context_get_border_bottom_style (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_border_after_style_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_border_after_style (current_context, relative);
    }
  else
    {
      relative = fo_context_get_border_after_style (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_border_bottom_style_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_border_bottom_style (current_context, absolute);
	}
      else
	{
	  if (border_bottom_wsc != NULL)
	    {
	      border_bottom_component = fo_wsc_get_style (border_bottom_wsc);
	    }
	  else
	    {
	      border_bottom_component = NULL;
	    }
	  if (border_bottom_component != NULL)
	    {
	      absolute = fo_property_border_bottom_style_new ();
	      fo_property_set_value (absolute, border_bottom_component);
	      fo_context_set_border_bottom_style (current_context, absolute);
	      relative = fo_property_border_after_style_new ();
	      fo_property_set_value (relative, border_bottom_component);
	      fo_context_set_border_after_style (current_context, relative);
	    }
	  else
	    {
	      if (border_style_tblr != NULL)
		{
		  border_style_component = fo_tblr_get_bottom (border_style_tblr);
		}
	      else
		{
		  border_style_component = NULL;
		}
	      if (border_style_component != NULL)
		{
		  absolute = fo_property_border_bottom_style_new ();
		  fo_property_set_value (absolute, border_style_component);
		  fo_context_set_border_bottom_style (current_context, absolute);
		  relative = fo_property_border_after_style_new ();
		  fo_property_set_value (relative, border_style_component);
		  fo_context_set_border_after_style (current_context, relative);
		}
	      else
		{
		  if (border_wsc != NULL)
		    {
		      border_component = fo_wsc_get_style (border_wsc);
		    }
		  else
		    {
		      border_component = NULL;
		    }
		  if (border_component != NULL)
		    {
		      absolute = fo_property_border_bottom_style_new ();
		      fo_property_set_value (absolute, border_component);
		      fo_context_set_border_bottom_style (current_context, absolute);
		      relative = fo_property_border_after_style_new ();
		      fo_property_set_value (relative, border_component);
		      fo_context_set_border_after_style (current_context, relative);
		    }
		  else
		    {
		      absolute = fo_property_border_bottom_style_get_initial ();
		      fo_context_set_border_bottom_style (current_context, absolute);
		      relative = fo_property_border_after_style_get_initial ();
		      fo_context_set_border_after_style (current_context, relative);
		    }
		}
	    }
	}
    }
  /* width */
  datatype = fo_property_get_value (absolute);
  if ((fo_enum_get_value (datatype) == FO_ENUM_ENUM_NONE) ||
      (fo_enum_get_value (datatype) == FO_ENUM_ENUM_HIDDEN))
    {
      absolute = g_object_new (FO_TYPE_PROPERTY_BORDER_BOTTOM_WIDTH,
			       "value",
			       fo_length_get_length_zero (),
			       NULL);
      fo_context_set_border_bottom_width (current_context, absolute);
      relative = g_object_new (FO_TYPE_PROPERTY_BORDER_AFTER_WIDTH,
			       "value",
			       fo_length_get_length_zero (),
			       NULL);
      fo_context_set_border_after_width (current_context, relative);
    }
  else
    {
      absolute = fo_context_get_border_bottom_width (current_context);
      if (absolute != NULL)
	{
	  datatype = fo_property_get_value (absolute);
	  relative = fo_property_border_after_width_new ();
	  fo_property_set_value (relative, datatype);
	  fo_context_set_border_after_width (current_context, relative);
	}
      else
	{
	  relative = fo_context_get_border_after_width (current_context);
	  if (relative != NULL)
	    {
	      datatype = fo_property_get_value (relative);
	      absolute = fo_property_border_bottom_width_new ();
	      fo_property_set_value (absolute, datatype);
	      fo_context_set_border_bottom_width (current_context, absolute);
	    }
	  else
	    {
	      if (border_bottom_wsc != NULL)
		{
		  border_bottom_component = fo_wsc_get_width (border_bottom_wsc);
		}
	      else
		{
		  border_bottom_component = NULL;
		}
	      if (border_bottom_component != NULL)
		{
		  absolute = fo_property_border_bottom_width_new ();
		  fo_property_set_value (absolute, border_bottom_component);
		  fo_context_set_border_bottom_width (current_context, absolute);
		  relative = fo_property_border_after_width_new ();
		  fo_property_set_value (relative, border_bottom_component);
		  fo_context_set_border_after_width (current_context, relative);
		}
	      else
		{
		  if (border_width_tblr != NULL)
		    {
		      border_width_component = fo_tblr_get_bottom (border_width_tblr);
		    }
		  else
		    {
		      border_width_component = NULL;
		    }
		  if (border_width_component != NULL)
		    {
		      absolute = fo_property_border_bottom_width_new ();
		      fo_property_set_value (absolute, border_width_component);
		      fo_context_set_border_bottom_width (current_context, absolute);
		      relative = fo_property_border_after_width_new ();
		      fo_property_set_value (relative, border_width_component);
		      fo_context_set_border_after_width (current_context, relative);
		    }
		  else
		    {
		      if (border_wsc != NULL)
			{
			  border_component = fo_wsc_get_width (border_wsc);
			}
		      else
			{
			  border_component = NULL;
			}
		      if (border_component != NULL)
			{
			  absolute = fo_property_border_bottom_width_new ();
			  fo_property_set_value (absolute, border_component);
			  fo_context_set_border_bottom_width (current_context, absolute);
			  relative = fo_property_border_after_width_new ();
			  fo_property_set_value (relative, border_component);
			  fo_context_set_border_after_width (current_context, relative);
			}
		      else
			{
			  absolute = fo_property_border_bottom_width_get_initial ();
			  fo_context_set_border_bottom_width (current_context, absolute);
			  relative = fo_property_border_after_width_get_initial ();
			  fo_context_set_border_after_width (current_context, relative);
			}
		    }
		}
	    }
	}
    }
  /* color */
  absolute = fo_context_get_border_bottom_color (current_context);
  if (absolute != NULL)
    {
      datatype = fo_property_get_value (absolute);
      relative = fo_property_border_after_color_new ();
      fo_property_set_value (relative, datatype);
      fo_context_set_border_after_color (current_context, relative);
    }
  else
    {
      relative = fo_context_get_border_after_color (current_context);
      if (relative != NULL)
	{
	  datatype = fo_property_get_value (relative);
	  absolute = fo_property_border_bottom_color_new ();
	  fo_property_set_value (absolute, datatype);
	  fo_context_set_border_bottom_color (current_context, absolute);
	}
      else
	{
	  if (border_bottom_wsc != NULL)
	    {
	      border_bottom_component = fo_wsc_get_color (border_bottom_wsc);
	    }
	  else
	    {
	      border_bottom_component = NULL;
	    }
	  if (border_bottom_component != NULL)
	    {
	      absolute = fo_property_border_bottom_color_new ();
	      fo_property_set_value (absolute, border_bottom_component);
	      fo_context_set_border_bottom_color (current_context, absolute);
	      relative = fo_property_border_after_color_new ();
	      fo_property_set_value (relative, border_bottom_component);
	      fo_context_set_border_after_color (current_context, relative);
	    }
	  else
	    {
	      if (border_color_tblr != NULL)
		{
		  border_color_component = fo_tblr_get_bottom (border_color_tblr);
		}
	      else
		{
		  border_color_component = NULL;
		}
	      if (border_color_component != NULL)
		{
		  absolute = fo_property_border_bottom_color_new ();
		  fo_property_set_value (absolute, border_color_component);
		  fo_context_set_border_bottom_color (current_context, absolute);
		  relative = fo_property_border_after_color_new ();
		  fo_property_set_value (relative, border_color_component);
		  fo_context_set_border_after_color (current_context, relative);
		}
	      else
		{
		  if (border_wsc != NULL)
		    {
		      border_component = fo_wsc_get_color (border_wsc);
		    }
		  else
		    {
		      border_component = NULL;
		    }
		  if (border_component != NULL)
		    {
		      absolute = fo_property_border_bottom_color_new ();
		      fo_property_set_value (absolute, border_component);
		      fo_context_set_border_bottom_color (current_context, absolute);
		      relative = fo_property_border_after_color_new ();
		      fo_property_set_value (relative, border_component);
		      fo_context_set_border_after_color (current_context, relative);
		    }
		  else
		    {
		      prop_color = g_object_new (FO_TYPE_PROPERTY_BORDER_BOTTOM_COLOR,
						 "value",
						 initial_color,
						 NULL);
		      fo_context_set_border_bottom_color (current_context, prop_color);
		      prop_color = g_object_new (FO_TYPE_PROPERTY_BORDER_AFTER_COLOR,
						 "value",
						 initial_color,
						 NULL);
		      fo_context_set_border_after_color (current_context, prop_color);
		    }
		}
	    }
	}
    }
}

/* FIXME: Why is this necessary?  This should happen in fo_context_merge() */
void
fo_context_util_dominant_baseline_resolve (FoContext *current_context,
					   FoContext *parent_context)
{
  g_return_if_fail (current_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (parent_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  if (fo_context_get_dominant_baseline (current_context) == NULL)
    {
      fo_context_set_dominant_baseline (current_context,
					fo_property_dominant_baseline_get_initial ());
    }
}
