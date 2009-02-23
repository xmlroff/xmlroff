/* Fo
 * fo-block-fo.c: Block formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2009 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-fo.h"
#include "fo-fo-private.h"
#include "fo-block-fo.h"
#include "fo-block-fo-private.h"
#include "area/fo-area-area.h"

GType
fo_block_fo_get_type (void)
{
  static GType block_fo_type = 0;

  if (!block_fo_type)
    {
      static const GTypeInfo block_fo_info =
      {
        sizeof (FoBlockFoIface), /* class_size */
	NULL,   	/* base_init */
	NULL,		/* base_finalize */
	NULL,
	NULL,		/* class_finalize */
	NULL,		/* class_data */
	0,
	0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      block_fo_type = g_type_register_static (G_TYPE_INTERFACE,
					      "FoBlockFoIface",
					      &block_fo_info, 0);
      g_type_interface_add_prerequisite (block_fo_type, FO_TYPE_FO);
    }

  return block_fo_type;
}

void
fo_block_fo_update_area (FoFo *fo,
			 FoArea *area)
{
  FoArea *use_child_area;
  gfloat total_child_height = 0;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BLOCK_FO (fo));
  g_return_if_fail (fo_area_get_generated_by (area) == fo);

  fo_area_area_set_border_after (area,
				 fo_length_get_value (fo_property_get_value (fo_block_fo_get_border_after_width (fo))));
  fo_area_area_set_border_before (area,
				  fo_length_get_value (fo_property_get_value (fo_block_fo_get_border_before_width (fo))));
  fo_area_area_set_border_end (area,
			       fo_length_get_value (fo_property_get_value (fo_block_fo_get_border_end_width (fo))));
  fo_area_area_set_border_start (area,
				 fo_length_get_value (fo_property_get_value (fo_block_fo_get_border_start_width (fo))));
  fo_area_area_set_padding_before (area,
				   fo_length_get_value (fo_property_get_value (fo_block_fo_get_padding_before (fo))));
  fo_area_area_set_padding_end (area,
				fo_length_get_value (fo_property_get_value (fo_block_fo_get_padding_end (fo))));
  fo_area_area_set_padding_after (area,
				  fo_length_get_value (fo_property_get_value (fo_block_fo_get_padding_after (fo))));
  fo_area_area_set_padding_start (area,
				  fo_length_get_value (fo_property_get_value (fo_block_fo_get_padding_start (fo))));
  fo_area_area_set_start_indent (area,
				 fo_length_get_value (fo_property_get_value (fo_block_fo_get_start_indent (fo))));
  fo_area_area_set_end_indent (area,
			       fo_length_get_value (fo_property_get_value (fo_block_fo_get_end_indent (fo))));
  fo_area_area_set_space_before (area,
				 fo_length_get_value (fo_property_get_value (fo_block_fo_get_space_before (fo))));
  fo_area_area_set_space_after (area,
				fo_length_get_value (fo_property_get_value (fo_block_fo_get_space_after (fo))));

  use_child_area = fo_area_first_child (area);

  while (use_child_area)
    {
      total_child_height += fo_area_area_get_height (use_child_area);
      use_child_area = fo_area_next_sibling (use_child_area);
    }

  fo_area_area_set_height (area,
			   total_child_height +
			   fo_area_area_get_space_before (area) +
			   fo_area_area_get_border_before (area) +
			   fo_area_area_get_padding_before (area) +
			   fo_area_area_get_padding_after (area) +
			   fo_area_area_get_border_after (area) +
			   fo_area_area_get_space_after (area));
}

/**
 * fo_block_fo_get_background_color:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #background-color property of @fo_block_fo
 *
 * Return value: The "background-color" property value
**/
FoProperty *
fo_block_fo_get_background_color (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_background_color (fo_block_fo);
}

/**
 * fo_block_fo_get_border_after_color:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-after-color property of @fo_block_fo
 *
 * Return value: The "border-after-color" property value
**/
FoProperty*
fo_block_fo_get_border_after_color (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_after_color (fo_block_fo);
}

/**
 * fo_block_fo_get_border_after_style:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-after-style property of @fo_block_fo
 *
 * Return value: The "border-after-style" property value
**/
FoProperty*
fo_block_fo_get_border_after_style (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_after_style (fo_block_fo);
}

/**
 * fo_block_fo_get_border_after_width:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-after-width property of @fo_block_fo
 *
 * Return value: The "border-after-width" property value
**/
FoProperty*
fo_block_fo_get_border_after_width (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_after_width (fo_block_fo);
}

/**
 * fo_block_fo_get_border_before_color:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-before-color property of @fo_block_fo
 *
 * Return value: The "border-before-color" property value
**/
FoProperty*
fo_block_fo_get_border_before_color (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_before_color (fo_block_fo);
}

/**
 * fo_block_fo_get_border_before_style:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-before-style property of @fo_block_fo
 *
 * Return value: The "border-before-style" property value
**/
FoProperty*
fo_block_fo_get_border_before_style (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_before_style (fo_block_fo);
}

/**
 * fo_block_fo_get_border_before_width:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-before-width property of @fo_block_fo
 *
 * Return value: The "border-before-width" property value
**/
FoProperty*
fo_block_fo_get_border_before_width (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_before_width (fo_block_fo);
}

/**
 * fo_block_fo_get_border_end_color:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-end-color property of @fo_block_fo
 *
 * Return value: The "border-end-color" property value
**/
FoProperty*
fo_block_fo_get_border_end_color (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_end_color (fo_block_fo);
}

/**
 * fo_block_fo_get_border_end_style:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-end-style property of @fo_block_fo
 *
 * Return value: The "border-end-style" property value
**/
FoProperty*
fo_block_fo_get_border_end_style (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_end_style (fo_block_fo);
}

/**
 * fo_block_fo_get_border_end_width:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-end-width property of @fo_block_fo
 *
 * Return value: The "border-end-width" property value
**/
FoProperty*
fo_block_fo_get_border_end_width (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_end_width (fo_block_fo);
}

/**
 * fo_block_fo_get_border_start_color:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-start-color property of @fo_block_fo
 *
 * Return value: The "border-start-color" property value
**/
FoProperty*
fo_block_fo_get_border_start_color (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_start_color (fo_block_fo);
}

/**
 * fo_block_fo_get_border_start_style:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-start-style property of @fo_block_fo
 *
 * Return value: The "border-start-style" property value
**/
FoProperty*
fo_block_fo_get_border_start_style (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_start_style (fo_block_fo);
}

/**
 * fo_block_fo_get_border_start_width:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #border-start-width property of @fo_block_fo
 *
 * Return value: The "border-start-width" property value
**/
FoProperty*
fo_block_fo_get_border_start_width (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_border_start_width (fo_block_fo);
}

/**
 * fo_block_fo_get_keep_together:
 * @fo_block_fo: The #FoBlockFo object
 *
 * Gets the #keep-together property of @fo_block_fo
 *
 * Return value: The "keep-together" property value
**/
FoProperty*
fo_block_fo_get_keep_together (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_keep_together (fo_block_fo);
}

/**
 * fo_block_fo_get_keep_with_next:
 * @fo_block_fo: The #FoBlockFo object
 *
 * Gets the #keep-with-next property of @fo_block_fo
 *
 * Return value: The "keep-with-next" property value
**/
FoProperty*
fo_block_fo_get_keep_with_next (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_keep_with_next (fo_block_fo);
}

/**
 * fo_block_fo_get_keep_with_previous:
 * @fo_block_fo: The #FoBlockFo object
 *
 * Gets the #keep-with-previous property of @fo_block_fo
 *
 * Return value: The "keep-with-previous" property value
**/
FoProperty*
fo_block_fo_get_keep_with_previous (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_keep_with_previous (fo_block_fo);
}

/**
 * fo_block_fo_get_padding_after:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #padding-after-color property of @fo_block_fo
 *
 * Return value: The "padding-after-color" property value
**/
FoProperty*
fo_block_fo_get_padding_after (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_padding_after (fo_block_fo);
}

/**
 * fo_block_fo_get_padding_before:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #padding-before-color property of @fo_block_fo
 *
 * Return value: The "padding-before-color" property value
**/
FoProperty*
fo_block_fo_get_padding_before (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_padding_before (fo_block_fo);
}

/**
 * fo_block_fo_get_padding_end:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #padding-end-color property of @fo_block_fo
 *
 * Return value: The "padding-end-color" property value
**/
FoProperty*
fo_block_fo_get_padding_end (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_padding_end (fo_block_fo);
}

/**
 * fo_block_fo_get_padding_start:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #padding-start-color property of @fo_block_fo
 *
 * Return value: The "padding-start-color" property value
**/
FoProperty*
fo_block_fo_get_padding_start (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_padding_start (fo_block_fo);
}

/**
 * fo_block_fo_get_space_before:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #space-before property of @fo_block_fo
 *
 * Return value: The "space-before" property value
**/
FoProperty*
fo_block_fo_get_space_before (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_space_before (fo_block_fo);
}

/**
 * fo_block_fo_get_space_after:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #space-after property of @fo_block_fo
 *
 * Return value: The "space-after" property value
**/
FoProperty*
fo_block_fo_get_space_after (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_space_after (fo_block_fo);
}

/**
 * fo_block_fo_get_start_indent:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #start-indent property of @fo_block_fo
 *
 * Return value: The "start-indent" property value
**/
FoProperty*
fo_block_fo_get_start_indent (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_start_indent (fo_block_fo);
}

/**
 * fo_block_fo_get_end_indent:
 * @fo_block_fo: The @FoBlockFo object
 *
 * Gets the #end-indent property of @fo_block_fo
 *
 * Return value: The "end-indent" property value
**/
FoProperty*
fo_block_fo_get_end_indent (FoFo *fo_block_fo)
{
  g_return_val_if_fail (fo_block_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_BLOCK_FO (fo_block_fo), NULL);

  return FO_BLOCK_FO_GET_IFACE (fo_block_fo)->get_end_indent (fo_block_fo);
}
