/* Fo
 * fo-neutral-fo.c: Neutral formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-neutral-fo.h"

GType
fo_neutral_fo_get_type (void)
{
  static GType neutral_fo_type = 0;

  if (!neutral_fo_type)
    {
      static const GTypeInfo neutral_fo_info =
      {
        sizeof (FoNeutralFoIface), /* class_size */
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

      neutral_fo_type = g_type_register_static (G_TYPE_INTERFACE,
						"FoNeutralIface",
						&neutral_fo_info, 0);
      g_type_interface_add_prerequisite (neutral_fo_type, FO_TYPE_FO);
    }

  return neutral_fo_type;
}
