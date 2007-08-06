/* Fo
 * fo-table-border-fo.c: Table border properties formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-table-border-fo.h"
#include "fo-table-border-fo-private.h"
#include "area/fo-area-area.h"

GType
fo_table_border_fo_get_type (void)
{
  static GType table_border_fo_type = 0;

  if (!table_border_fo_type)
    {
      static const GTypeInfo table_border_fo_info =
      {
        sizeof (FoTableBorderFoIface), /* class_size */
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

      table_border_fo_type = g_type_register_static (G_TYPE_INTERFACE,
						     "FoTableBorderFoIface",
						     &table_border_fo_info,
						     0);
      g_type_interface_add_prerequisite (table_border_fo_type,
					 FO_TYPE_FO);
    }

  return table_border_fo_type;
}

/**
 * fo_table_border_fo_get_background_color:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #background-color property of @fo_table_border_fo
 *
 * Return value: The "background-color" property value
**/
FoProperty *
fo_table_border_fo_get_background_color (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_background_color (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_after_color:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-after-color property of @fo_table_border_fo
 *
 * Return value: The "border-after-color" property value
**/
FoProperty*
fo_table_border_fo_get_border_after_color (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_after_color (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_after_precedence:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the "border-after-precedence" property of @fo_table_border_fo
 *
 * Return value: The "border-after-precedence" property value
**/
FoProperty*
fo_table_border_fo_get_border_after_precedence (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_after_precedence (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_after_style:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-after-style property of @fo_table_border_fo
 *
 * Return value: The "border-after-style" property value
**/
FoProperty*
fo_table_border_fo_get_border_after_style (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_after_style (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_after_width:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-after-width property of @fo_table_border_fo
 *
 * Return value: The "border-after-width" property value
**/
FoProperty*
fo_table_border_fo_get_border_after_width (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_after_width (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_before_color:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-before-color property of @fo_table_border_fo
 *
 * Return value: The "border-before-color" property value
**/
FoProperty*
fo_table_border_fo_get_border_before_color (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_before_color (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_before_precedence:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the "border-before-precedence" property of @fo_table_border_fo
 *
 * Return value: The "border-before-precedence" property value
**/
FoProperty*
fo_table_border_fo_get_border_before_precedence (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_before_precedence (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_before_style:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-before-style property of @fo_table_border_fo
 *
 * Return value: The "border-before-style" property value
**/
FoProperty*
fo_table_border_fo_get_border_before_style (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_before_style (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_before_width:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-before-width property of @fo_table_border_fo
 *
 * Return value: The "border-before-width" property value
**/
FoProperty*
fo_table_border_fo_get_border_before_width (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_before_width (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_end_color:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-end-color property of @fo_table_border_fo
 *
 * Return value: The "border-end-color" property value
**/
FoProperty*
fo_table_border_fo_get_border_end_color (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_end_color (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_end_precedence:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the "border-end-precedence" property of @fo_table_border_fo
 *
 * Return value: The "border-end-precedence" property value
**/
FoProperty*
fo_table_border_fo_get_border_end_precedence (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_end_precedence (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_end_style:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-end-style property of @fo_table_border_fo
 *
 * Return value: The "border-end-style" property value
**/
FoProperty*
fo_table_border_fo_get_border_end_style (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_end_style (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_end_width:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-end-width property of @fo_table_border_fo
 *
 * Return value: The "border-end-width" property value
**/
FoProperty*
fo_table_border_fo_get_border_end_width (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_end_width (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_start_color:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-start-color property of @fo_table_border_fo
 *
 * Return value: The "border-start-color" property value
**/
FoProperty*
fo_table_border_fo_get_border_start_color (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_start_color (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_start_precedence:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the "border-start-precedence" property of @fo_table_border_fo
 *
 * Return value: The "border-start-precedence" property value
**/
FoProperty*
fo_table_border_fo_get_border_start_precedence (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_start_precedence (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_start_style:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-start-style property of @fo_table_border_fo
 *
 * Return value: The "border-start-style" property value
**/
FoProperty*
fo_table_border_fo_get_border_start_style (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_start_style (fo_table_border_fo);
}

/**
 * fo_table_border_fo_get_border_start_width:
 * @fo_table_border_fo: The @FoTableBorderFo object
 *
 * Gets the #border-start-width property of @fo_table_border_fo
 *
 * Return value: The "border-start-width" property value
**/
FoProperty*
fo_table_border_fo_get_border_start_width (FoFo *fo_table_border_fo)
{
  g_return_val_if_fail (fo_table_border_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TABLE_BORDER_FO (fo_table_border_fo), NULL);

  return FO_TABLE_BORDER_FO_GET_IFACE (fo_table_border_fo)->get_border_start_width (fo_table_border_fo);
}

