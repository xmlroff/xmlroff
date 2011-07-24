/* Fo
 * fo-cbpbp-fo.c: "Common Border, Padding, and Background Properties" FO interface
 *
 * Copyright (C) 2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "libfo/fo/fo-cbpbp-fo-private.h"

GType
fo_cbpbp_fo_get_type (void)
{
  static GType cbpbp_fo_type = 0;

  if (!cbpbp_fo_type)
    {
      static const GTypeInfo cbpbp_fo_info =
      {
        sizeof (FoCBPBPFoIface), /* class_size */
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

      cbpbp_fo_type = g_type_register_static (G_TYPE_INTERFACE,
					      "FoCBPBPFoIface",
					      &cbpbp_fo_info, 0);
      g_type_interface_add_prerequisite (cbpbp_fo_type, FO_TYPE_FO);
    }

  return cbpbp_fo_type;
}

/**
 * fo_cbpbp_fo_get_background_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #background-color property of @fo_cbpbp_fo
 *
 * Return value: The "background-color" property value
**/
FoProperty *
fo_cbpbp_fo_get_background_color (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_background_color (fo_cbpbp_fo);
}

/**
 * _set_background_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_background_color: The new "background-color" property value.
 * 
 * Sets the "background-color" property of @fo_cbpbp_fo to
 * @new_background_color.
 **/
static void
_set_background_color (FoFo *fo_cbpbp_fo,
		       FoProperty *new_background_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_background_color (fo_cbpbp_fo,
							     new_background_color);
}

/**
 * fo_cbpbp_fo_get_border_after_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-after-color property of @fo_cbpbp_fo
 *
 * Return value: The "border-after-color" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_after_color (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_after_color (fo_cbpbp_fo);
}

/**
 * _set_border_after_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_after_color: The new "border-after-color" property value.
 * 
 * Sets the "border-after-color" property of @fo_cbpbp_fo to
 * @new_border_after_color.
 **/
static void
_set_border_after_color (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_after_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_after_color (fo_cbpbp_fo,
							       new_border_after_color);
}

/**
 * fo_cbpbp_fo_get_border_after_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-after-style property of @fo_cbpbp_fo
 *
 * Return value: The "border-after-style" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_after_style (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_after_style (fo_cbpbp_fo);
}

/**
 * _set_border_after_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_after_style: The new "border-after-style" property value.
 * 
 * Sets the "border-after-style" property of @fo_cbpbp_fo to
 * @new_border_after_style.
 **/
static void
_set_border_after_style (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_after_style)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_after_style (fo_cbpbp_fo,
							       new_border_after_style);
}

/**
 * fo_cbpbp_fo_get_border_after_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-after-width property of @fo_cbpbp_fo
 *
 * Return value: The "border-after-width" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_after_width (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_after_width (fo_cbpbp_fo);
}

/**
 * _set_border_after_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_after_width: The new "border-after-width" property value.
 * 
 * Sets the "border-after-width" property of @fo_cbpbp_fo to
 * @new_border_after_width.
 **/
static void
_set_border_after_width (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_after_width)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_after_width (fo_cbpbp_fo,
							       new_border_after_width);
}

/**
 * fo_cbpbp_fo_get_border_before_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-before-color property of @fo_cbpbp_fo
 *
 * Return value: The "border-before-color" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_before_color (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_before_color (fo_cbpbp_fo);
}

/**
 * _set_border_before_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_before_color: The new "border-before-color" property value.
 * 
 * Sets the "border-before-color" property of @fo_cbpbp_fo to
 * @new_border_before_color.
 **/
static void
_set_border_before_color (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_before_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_before_color (fo_cbpbp_fo,
							       new_border_before_color);
}

/**
 * fo_cbpbp_fo_get_border_before_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-before-style property of @fo_cbpbp_fo
 *
 * Return value: The "border-before-style" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_before_style (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_before_style (fo_cbpbp_fo);
}

/**
 * _set_border_before_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_before_style: The new "border-before-style" property value.
 * 
 * Sets the "border-before-style" property of @fo_cbpbp_fo to
 * @new_border_before_style.
 **/
static void
_set_border_before_style (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_before_style)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_before_style (fo_cbpbp_fo,
							       new_border_before_style);
}

/**
 * fo_cbpbp_fo_get_border_before_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-before-width property of @fo_cbpbp_fo
 *
 * Return value: The "border-before-width" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_before_width (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_before_width (fo_cbpbp_fo);
}

/**
 * _set_border_before_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_before_width: The new "border-before-width" property value.
 * 
 * Sets the "border-before-width" property of @fo_cbpbp_fo to
 * @new_border_before_width.
 **/
static void
_set_border_before_width (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_before_width)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_before_width (fo_cbpbp_fo,
							       new_border_before_width);
}

/**
 * _set_border_bottom_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_bottom_color: The new "border-bottom-color" property value.
 * 
 * Sets the "border-bottom-color" property of @fo_cbpbp_fo to
 * @new_border_bottom_color.
 **/
static void
_set_border_bottom_color (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_bottom_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_bottom_color (fo_cbpbp_fo,
							       new_border_bottom_color);
}

/**
 * _set_border_bottom_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_bottom_style: The new "border-bottom-style" property value.
 * 
 * Sets the "border-bottom-style" property of @fo_cbpbp_fo to
 * @new_border_bottom_style.
 **/
static void
_set_border_bottom_style (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_bottom_style)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_bottom_style (fo_cbpbp_fo,
							       new_border_bottom_style);
}

/**
 * _set_border_bottom_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_bottom_width: The new "border-bottom-width" property value.
 * 
 * Sets the "border-bottom-width" property of @fo_cbpbp_fo to
 * @new_border_bottom_width.
 **/
static void
_set_border_bottom_width (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_bottom_width)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_bottom_width (fo_cbpbp_fo,
							       new_border_bottom_width);
}

/**
 * fo_cbpbp_fo_get_border_end_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-end-color property of @fo_cbpbp_fo
 *
 * Return value: The "border-end-color" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_end_color (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_end_color (fo_cbpbp_fo);
}

/**
 * _set_border_end_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_end: The new "border-end-color" property value.
 * 
 * Sets the "border-end-color" property of @fo_cbpbp_fo to
 * @new_border_end_color.
 **/
static void
_set_border_end_color (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_end_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_end_color (fo_cbpbp_fo,
							       new_border_end_color);
}

/**
 * fo_cbpbp_fo_get_border_end_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-end-style property of @fo_cbpbp_fo
 *
 * Return value: The "border-end-style" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_end_style (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_end_style (fo_cbpbp_fo);
}

/**
 * _set_border_end_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_end: The new "border-end-style" property value.
 * 
 * Sets the "border-end-style" property of @fo_cbpbp_fo to
 * @new_border_end_style.
 **/
static void
_set_border_end_style (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_end_style)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_end_style (fo_cbpbp_fo,
							       new_border_end_style);
}

/**
 * fo_cbpbp_fo_get_border_end_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-end-width property of @fo_cbpbp_fo
 *
 * Return value: The "border-end-width" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_end_width (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_end_width (fo_cbpbp_fo);
}

/**
 * _set_border_end_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_end_width: The new "border-end-width" property value.
 * 
 * Sets the "border-end-width" property of @fo_cbpbp_fo to
 * @new_border_end_width.
 **/
static void
_set_border_end_width (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_end_width)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_end_width (fo_cbpbp_fo,
							       new_border_end_width);
}

/**
 * _set_border_left_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_left_color: The new "border-left-color" property value.
 * 
 * Sets the "border-left-color" property of @fo_cbpbp_fo to
 * @new_border_left_color.
 **/
static void
_set_border_left_color (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_left_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_left_color (fo_cbpbp_fo,
							       new_border_left_color);
}

/**
 * _set_border_left_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_left_style: The new "border-left-style" property value.
 * 
 * Sets the "border-left-style" property of @fo_cbpbp_fo to
 * @new_border_left_style.
 **/
static void
_set_border_left_style (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_left_style)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_left_style (fo_cbpbp_fo,
							       new_border_left_style);
}

/**
 * _set_border_left_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_left_width: The new "border-left-width" property value.
 * 
 * Sets the "border-left-width" property of @fo_cbpbp_fo to
 * @new_border_left_width.
 **/
static void
_set_border_left_width (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_left_width)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_left_width (fo_cbpbp_fo,
							       new_border_left_width);
}

/**
 * _set_border_right_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_right_color: The new "border-right-color" property value.
 * 
 * Sets the "border-right-color" property of @fo_cbpbp_fo to
 * @new_border_right_color.
 **/
static void
_set_border_right_color (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_right_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_right_color (fo_cbpbp_fo,
							       new_border_right_color);
}

/**
 * _set_border_right_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_right_style: The new "border-right-style" property value.
 * 
 * Sets the "border-right-style" property of @fo_cbpbp_fo to
 * @new_border_right_style.
 **/
static void
_set_border_right_style (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_right_style)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_right_style (fo_cbpbp_fo,
							       new_border_right_style);
}

/**
 * _set_border_right_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_right_width: The new "border-right-width" property value.
 * 
 * Sets the "border-right-width" property of @fo_cbpbp_fo to
 * @new_border_right_width.
 **/
static void
_set_border_right_width (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_right_width)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_right_width (fo_cbpbp_fo,
							       new_border_right_width);
}

/**
 * fo_cbpbp_fo_get_border_start_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-start-color property of @fo_cbpbp_fo
 *
 * Return value: The "border-start-color" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_start_color (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_start_color (fo_cbpbp_fo);
}

/**
 * _set_border_start_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_start_color: The new "border-start-color" property value.
 * 
 * Sets the "border-start-color" property of @fo_cbpbp_fo to
 * @new_border_start_color.
 **/
static void
_set_border_start_color (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_start_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_start_color (fo_cbpbp_fo,
							       new_border_start_color);
}

/**
 * fo_cbpbp_fo_get_border_start_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-start-style property of @fo_cbpbp_fo
 *
 * Return value: The "border-start-style" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_start_style (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_start_style (fo_cbpbp_fo);
}

/**
 * _set_border_start_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_start_style: The new "border-start-style" property value.
 * 
 * Sets the "border-start-style" property of @fo_cbpbp_fo to
 * @new_border_start_style.
 **/
static void
_set_border_start_style (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_start_style)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_start_style (fo_cbpbp_fo,
							       new_border_start_style);
}

/**
 * fo_cbpbp_fo_get_border_start_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #border-start-width property of @fo_cbpbp_fo
 *
 * Return value: The "border-start-width" property value
**/
FoProperty*
fo_cbpbp_fo_get_border_start_width (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_border_start_width (fo_cbpbp_fo);
}

/**
 * _set_border_start_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_start_width: The new "border-start-width" property value.
 * 
 * Sets the "border-start-width" property of @fo_cbpbp_fo to
 * @new_border_start_width.
 **/
static void
_set_border_start_width (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_start_width)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_start_width (fo_cbpbp_fo,
							       new_border_start_width);
}

/**
 * _set_border_top_color:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_top_color: The new "border-top-color" property value.
 * 
 * Sets the "border-top-color" property of @fo_cbpbp_fo to
 * @new_border_top_color.
 **/
static void
_set_border_top_color (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_top_color)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_top_color (fo_cbpbp_fo,
							       new_border_top_color);
}

/**
 * _set_border_top_style:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_top_style: The new "border-top-style" property value.
 * 
 * Sets the "border-top-style" property of @fo_cbpbp_fo to
 * @new_border_top_style.
 **/
static void
_set_border_top_style (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_top_style)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_top_style (fo_cbpbp_fo,
							       new_border_top_style);
}

/**
 * _set_border_top_width:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_border_top_width: The new "border-top-width" property value.
 * 
 * Sets the "border-top-width" property of @fo_cbpbp_fo to
 * @new_border_top_width.
 **/
static void
_set_border_top_width (FoFo *fo_cbpbp_fo,
			 FoProperty *new_border_top_width)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_border_top_width (fo_cbpbp_fo,
							       new_border_top_width);
}

/**
 * fo_cbpbp_fo_get_padding_after:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #padding-after property of @fo_cbpbp_fo
 *
 * Return value: The "padding-after" property value
**/
FoProperty*
fo_cbpbp_fo_get_padding_after (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_padding_after (fo_cbpbp_fo);
}

/**
 * _set_padding_after:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_padding_after: The new "padding-after" property value.
 * 
 * Sets the "padding-after" property of @fo_cbpbp_fo to
 * @new_padding_after.
 **/
static void
_set_padding_after (FoFo *fo_cbpbp_fo,
		    FoProperty *new_padding_after)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_padding_after (fo_cbpbp_fo,
							  new_padding_after);
}

/**
 * fo_cbpbp_fo_get_padding_before:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #padding-before property of @fo_cbpbp_fo
 *
 * Return value: The "padding-before" property value
**/
FoProperty*
fo_cbpbp_fo_get_padding_before (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_padding_before (fo_cbpbp_fo);
}

/**
 * _set_padding_before:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_padding_before: The new "padding-before" property value.
 * 
 * Sets the "padding-before" property of @fo_cbpbp_fo to
 * @new_padding_before.
 **/
static void
_set_padding_before (FoFo *fo_cbpbp_fo,
		    FoProperty *new_padding_before)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_padding_before (fo_cbpbp_fo,
							   new_padding_before);
}

/**
 * _set_padding_bottom:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_padding_bottom: The new "padding-bottom" property value.
 * 
 * Sets the "padding-bottom" property of @fo_cbpbp_fo to
 * @new_padding_bottom.
 **/
static void
_set_padding_bottom (FoFo *fo_cbpbp_fo,
		    FoProperty *new_padding_bottom)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_padding_bottom (fo_cbpbp_fo,
							   new_padding_bottom);
}

/**
 * fo_cbpbp_fo_get_padding_end:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #padding-end property of @fo_cbpbp_fo
 *
 * Return value: The "padding-end" property value
**/
FoProperty*
fo_cbpbp_fo_get_padding_end (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_padding_end (fo_cbpbp_fo);
}

/**
 * _set_padding_end:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_padding_end: The new "padding-end" property value.
 * 
 * Sets the "padding-end" property of @fo_cbpbp_fo to
 * @new_padding_end.
 **/
static void
_set_padding_end (FoFo *fo_cbpbp_fo,
		    FoProperty *new_padding_end)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_padding_end (fo_cbpbp_fo,
							new_padding_end);
}

/**
 * _set_padding_left:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_padding_left: The new "padding-left" property value.
 * 
 * Sets the "padding-left" property of @fo_cbpbp_fo to
 * @new_padding_left.
 **/
static void
_set_padding_left (FoFo *fo_cbpbp_fo,
		    FoProperty *new_padding_left)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_padding_left (fo_cbpbp_fo,
							   new_padding_left);
}

/**
 * _set_padding_right:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_padding_right: The new "padding-right" property value.
 * 
 * Sets the "padding-right" property of @fo_cbpbp_fo to
 * @new_padding_right.
 **/
static void
_set_padding_right (FoFo *fo_cbpbp_fo,
		    FoProperty *new_padding_right)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_padding_right (fo_cbpbp_fo,
							   new_padding_right);
}

/**
 * fo_cbpbp_fo_get_padding_start:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 *
 * Gets the #padding-start property of @fo_cbpbp_fo
 *
 * Return value: The "padding-start" property value
**/
FoProperty*
fo_cbpbp_fo_get_padding_start (FoFo *fo_cbpbp_fo)
{
  g_return_val_if_fail (fo_cbpbp_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo), NULL);

  return FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->get_padding_start (fo_cbpbp_fo);
}

/**
 * _set_padding_start:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_padding_start: The new "padding-start" property value.
 * 
 * Sets the "padding-start" property of @fo_cbpbp_fo to
 * @new_padding_start.
 **/
static void
_set_padding_start (FoFo *fo_cbpbp_fo,
		    FoProperty *new_padding_start)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_padding_start (fo_cbpbp_fo,
							  new_padding_start);
}

/**
 * _set_padding_top:
 * @fo_cbpbp_fo: The @FoCBPBPFo object
 * @new_padding_top: The new "padding-top" property value.
 * 
 * Sets the "padding-top" property of @fo_cbpbp_fo to
 * @new_padding_top.
 **/
static void
_set_padding_top (FoFo *fo_cbpbp_fo,
		    FoProperty *new_padding_top)
{
  g_return_if_fail (fo_cbpbp_fo != NULL);
  g_return_if_fail (FO_IS_CBPBP_FO (fo_cbpbp_fo));

  FO_CBPBP_FO_GET_IFACE (fo_cbpbp_fo)->set_padding_top (fo_cbpbp_fo,
							   new_padding_top);
}

/**
 * fo_cbpbp_fo_finalize:
 * @fo: #FoCBPBPFo object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoCBPBPFo.
 **/
void
fo_cbpbp_fo_finalize (FoFo *fo)
{
  /* Release references to all CBPBP property objects. */
  fo_region_set_background_color (fo, NULL);
  fo_region_set_border_after_color (fo, NULL);
  fo_region_set_border_after_style (fo, NULL);
  fo_region_set_border_after_width (fo, NULL);
  fo_region_set_border_before_color (fo, NULL);
  fo_region_set_border_before_style (fo, NULL);
  fo_region_set_border_before_width (fo, NULL);
  fo_region_set_border_bottom_color (fo, NULL);
  fo_region_set_border_bottom_style (fo, NULL);
  fo_region_set_border_bottom_width (fo, NULL);
  fo_region_set_border_end_color (fo, NULL);
  fo_region_set_border_end_style (fo, NULL);
  fo_region_set_border_end_width (fo, NULL);
  fo_region_set_border_left_color (fo, NULL);
  fo_region_set_border_left_style (fo, NULL);
  fo_region_set_border_left_width (fo, NULL);
  fo_region_set_border_right_color (fo, NULL);
  fo_region_set_border_right_style (fo, NULL);
  fo_region_set_border_right_width (fo, NULL);
  fo_region_set_border_start_color (fo, NULL);
  fo_region_set_border_start_style (fo, NULL);
  fo_region_set_border_start_width (fo, NULL);
  fo_region_set_border_top_color (fo, NULL);
  fo_region_set_border_top_style (fo, NULL);
  fo_region_set_border_top_width (fo, NULL);
  fo_region_set_padding_after (fo, NULL);
  fo_region_set_padding_before (fo, NULL);
  fo_region_set_padding_bottom (fo, NULL);
  fo_region_set_padding_end (fo, NULL);
  fo_region_set_padding_left (fo, NULL);
  fo_region_set_padding_right (fo, NULL);
  fo_region_set_padding_start (fo, NULL);
  fo_region_set_padding_top (fo, NULL);
}

/**
 * fo_cbpbp_fo_update_from_context:
 * @fo: 
 * @context: 
 *
 * 
 **/
void fo_cbpbp_fo_update_from_context (FoFo      *fo,
				      FoContext *context)
{
  _set_background_color (fo,
			 fo_context_get_background_color (context));
  _set_border_after_color (fo,
			   fo_context_get_border_after_color (context));
  _set_border_after_style (fo,
			   fo_context_get_border_after_style (context));
  _set_border_after_width (fo,
			   fo_context_get_border_after_width (context));
  _set_border_before_color (fo,
			    fo_context_get_border_before_color (context));
  _set_border_before_style (fo,
			    fo_context_get_border_before_style (context));
  _set_border_before_width (fo,
			    fo_context_get_border_before_width (context));
  _set_border_bottom_color (fo,
			    fo_context_get_border_bottom_color (context));
  _set_border_bottom_style (fo,
			    fo_context_get_border_bottom_style (context));
  _set_border_bottom_width (fo,
			    fo_context_get_border_bottom_width (context));
  _set_border_end_color (fo,
			 fo_context_get_border_end_color (context));
  _set_border_end_style (fo,
			 fo_context_get_border_end_style (context));
  _set_border_end_width (fo,
			 fo_context_get_border_end_width (context));
  _set_border_left_color (fo,
			  fo_context_get_border_left_color (context));
  _set_border_left_style (fo,
			  fo_context_get_border_left_style (context));
  _set_border_left_width (fo,
			  fo_context_get_border_left_width (context));
  _set_border_right_color (fo,
			   fo_context_get_border_right_color (context));
  _set_border_right_style (fo,
			   fo_context_get_border_right_style (context));
  _set_border_right_width (fo,
			   fo_context_get_border_right_width (context));
  _set_border_start_color (fo,
			   fo_context_get_border_start_color (context));
  _set_border_start_style (fo,
			   fo_context_get_border_start_style (context));
  _set_border_start_width (fo,
			   fo_context_get_border_start_width (context));
  _set_border_top_color (fo,
			 fo_context_get_border_top_color (context));
  _set_border_top_style (fo,
			 fo_context_get_border_top_style (context));
  _set_border_top_width (fo,
			 fo_context_get_border_top_width (context));
  _set_padding_after (fo,
		      fo_context_get_padding_after (context));
  _set_padding_before (fo,
		       fo_context_get_padding_before (context));
  _set_padding_bottom (fo,
		       fo_context_get_padding_bottom (context));
  _set_padding_end (fo,
		    fo_context_get_padding_end (context));
  _set_padding_left (fo,
		     fo_context_get_padding_left (context));
  _set_padding_right (fo,
		      fo_context_get_padding_right (context));
  _set_padding_start (fo,
		      fo_context_get_padding_start (context));
  _set_padding_top (fo,
		    fo_context_get_padding_top (context));
}
