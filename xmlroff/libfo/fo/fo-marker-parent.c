/* Fo
 * fo-marker-parent.c: Formatting object that is parent of possible fo:marker
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-marker-parent-private.h"
#include "fo-marker.h"

enum {
  PROP_0
};

static void     fo_marker_parent_class_init       (FoMarkerParentClass *klass);
static void     fo_marker_parent_finalize         (GObject             *object);
static gboolean fo_marker_parent_validate_content (FoFo                *fo,
						   GError             **error);
static void     fo_marker_parent_debug_dump_properties (FoFo *fo, gint depth);

static gpointer parent_class;

GType
fo_marker_parent_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoMarkerParentClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_marker_parent_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoMarkerParent),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_IDABLE,
                                            "FoMarkerParent",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * fo_marker_parent_class_init:
 * @klass: #FoMarkerParentClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoMarkerParent.
 **/
void
fo_marker_parent_class_init (FoMarkerParentClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_marker_parent_finalize;

  fo_fo_class->debug_dump_properties = fo_marker_parent_debug_dump_properties;
  fo_fo_class->update_from_context = fo_marker_parent_update_from_context;
  fo_fo_class->validate_content = fo_marker_parent_validate_content;
}

static void
fo_marker_parent_finalize (GObject *object)
{
  FoMarkerParent *fo_marker_parent;

  fo_marker_parent = FO_MARKER_PARENT (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_marker_parent_new:
 * 
 * Creates a new #FoMarkerParent initialized to default value.
 * 
 * Return value: the new #FoMarkerParent.
 **/
FoFo*
fo_marker_parent_new (void)
{
  return FO_FO (g_object_new (fo_marker_parent_get_type (),
			      NULL));
}

void
fo_marker_parent_update_from_context (FoFo *fo, FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MARKER_PARENT (fo));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);
}

/**
 * fo_marker_parent_debug_dump_marker:
 * @value: 
 * @data: 
 * 
 * 
 **/
static void
fo_marker_parent_debug_dump_marker (gpointer value,
				    gpointer data)
{
  gchar *indent = g_strnfill (GPOINTER_TO_INT (data) * 2, ' ');
  gchar *marker_sprintf;

  marker_sprintf = fo_object_debug_sprintf (value);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%p",
	 indent, value);

  g_free (marker_sprintf);
  g_free (indent);
}

void
fo_marker_parent_debug_dump_properties (FoFo *fo, gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_MARKER_PARENT (fo));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%smarkers:",
	 indent);

  if (FO_MARKER_PARENT (fo)->marker_list)
    {
      g_list_foreach (FO_MARKER_PARENT (fo)->marker_list,
		      fo_marker_parent_debug_dump_marker,
		      GINT_TO_POINTER (depth + 1));
    }
  else
    {
      g_log (G_LOG_DOMAIN,
	     G_LOG_LEVEL_DEBUG,
	     _("%s  (none)"),
	     indent);
    }

  g_free (indent);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_marker_parent_validate_content:
 * @fo:    #FoBlock object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: FALSE indicates
 * content model is correct, or TRUE indicates an error.  When used
 * with fo_node_traverse(), returning TRUE stops the traversal.
 * 
 * Return value: FALSE if content model okay, TRUE if not.
 **/
gboolean
fo_marker_parent_validate_content (FoFo    *fo,
				   GError **error)
{
  g_return_val_if_fail (FO_IS_MARKER_PARENT (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  gboolean parent_result =
    FO_FO_CLASS (parent_class)->validate_content (fo, error);

  if (parent_result == TRUE)
    {
      return parent_result;
    }

  if (fo_node_n_children (FO_NODE (fo)) != 0)
    {
      FoNode *child_node = fo_node_first_child (FO_NODE (fo));

      while (child_node)
	{
	  FoNode *next_node = fo_node_next_sibling (child_node);

	  if (FO_IS_MARKER (child_node))
	    {
	      fo_node_unlink (child_node);

	      FO_MARKER_PARENT (fo)->marker_list =
		g_list_append (FO_MARKER_PARENT (fo)->marker_list,
			       child_node);
	    }

	  child_node = next_node;
	}
    }

  return FALSE;
}
