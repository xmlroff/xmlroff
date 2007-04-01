/* Fo
 * fo-inline-fo.c: Inline formatting object interface
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-inline-fo.c,v 1.2 2003/06/30 13:21:08 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-inline-fo.h"

static void fo_inline_fo_base_class_init  (FoInlineFoIface *klass);
static void fo_inline_fo_get_text_attr_list_default (FoFo *fo_inline_fo,
						     FoDoc   *fo_doc,
						     GString *text,
						     GList **attr_glist,
						     guint debug_level);

GType
fo_inline_fo_get_type (void)
{
  static GType inline_fo_type = 0;

  if (!inline_fo_type)
    {
      static const GTypeInfo inline_fo_info =
      {
        sizeof (FoInlineFoIface), /* class_size */
	(GBaseInitFunc) fo_inline_fo_base_class_init,   	/* base_init */
	NULL,		/* base_finalize */
	NULL,
	NULL,		/* class_finalize */
	NULL,		/* class_data */
	0,
	0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      inline_fo_type = g_type_register_static (G_TYPE_INTERFACE,
					       "FoInlineFoIface",
					       &inline_fo_info, 0);
      g_type_interface_add_prerequisite (inline_fo_type, FO_TYPE_FO);
    }

  return inline_fo_type;
}

void
fo_inline_fo_base_class_init  (FoInlineFoIface *klass)
{
  klass->get_text_attr_list =
    fo_inline_fo_get_text_attr_list_default;
}

/**
 * fo_inline_fo_get_text_attr_list:
 * @fo_inline_fo: The @FoInlineFo object
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO
 * @attr_glist:   The list of Pango attributes for the inline FO
 * @debug_level:  Debug level
 * 
 * Gets the text of the inline FO and its associated list of Pango attributes
 **/
void
fo_inline_fo_get_text_attr_list (FoFo *fo_inline_fo,
				 FoDoc   *fo_doc,
				 GString *text,
				 GList **attr_glist,
				 guint debug_level)
{
  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_INLINE_FO (fo_inline_fo));

  FO_INLINE_FO_GET_IFACE (fo_inline_fo)->get_text_attr_list (fo_inline_fo,
							     fo_doc,
							     text,
							     attr_glist,
							     debug_level);
}

void
fo_inline_fo_get_text_attr_list_default (FoFo    *fo_inline_fo,
					 FoDoc   *fo_doc,
					 GString *text,
					 GList  **attr_glist,
					 guint    debug_level)
{
  FoNode *fo_child_node;
  GList *child_attr_glist = NULL;

  g_return_if_fail (FO_IS_INLINE_FO (fo_inline_fo));

#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'get_text_attr_list' function."),
	 fo_object_sprintf (FO_OBJECT (fo_inline_fo)));
#endif
  fo_child_node = fo_node_first_child (FO_NODE (fo_inline_fo));

  while (fo_child_node)
    {
      fo_inline_fo_get_text_attr_list (FO_FO (fo_child_node),
				       fo_doc,
				       text,
				       &child_attr_glist,
				       debug_level);
      fo_child_node = fo_node_next_sibling (fo_child_node);
    }

}
