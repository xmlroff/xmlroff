/* Fo
 * fo-wrapper.c: 'wrapper' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-wrapper.c,v 1.8 2006/03/29 17:41:12 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo/fo-wrapper-private.h"
#include "fo/fo-neutral-fo.h"
#include "fo/fo-block-fo.h"
#include "fo/fo-inline-fo.h"
#include "fo/fo-text.h"
#include "fo/fo-tree.h"
#include "fo/fo-wrapper.h"
#include "fo/fo-wrapper-block.h"
#include "fo/fo-wrapper-inline.h"
#include "fo/fo-wrapper-inline-empty.h"
#include "fo/fo-wrapper-whitespace.h"
#include "property/fo-property-id.h"

enum {
  PROP_0,
  PROP_ID
};

static void fo_wrapper_base_class_init (FoWrapperClass *klass);
static void fo_wrapper_class_init      (FoWrapperClass *klass);
static void fo_wrapper_get_property    (GObject      *object,
					guint         prop_id,
					GValue       *value,
					GParamSpec   *pspec);
static void fo_wrapper_set_property    (GObject      *object,
					guint         prop_id,
					const GValue *value,
					GParamSpec   *pspec);
static void fo_wrapper_finalize        (GObject      *object);
static gboolean fo_wrapper_validate_content (FoFo    *fo,
                                             GError **error);
static void fo_wrapper_validate (FoFo      *fo,
                                 FoContext *current_context,
                                 FoContext *parent_context,
                                 GError   **error);
static void fo_wrapper_update_from_context (FoFo      *fo,
                                            FoContext *context);
static void fo_wrapper_debug_dump_properties (FoFo *fo,
                                              gint  depth);

static gpointer parent_class;

/**
 * fo_wrapper_get_type:
 * 
 * Register the #FoWrapper object type.
 * 
 * Return value: #GType value of the #FoWrapper object type.
 **/
GType
fo_wrapper_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoWrapperClass),
        (GBaseInitFunc) fo_wrapper_base_class_init,
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_wrapper_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoWrapper),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      static const GInterfaceInfo fo_neutral_fo_info =
      {
        NULL,
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "wrapper",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_NEUTRAL_FO,
                                   &fo_neutral_fo_info);
    }

  return object_type;
}

/**
 * fo_wrapper_base_class_init:
 * @klass: #FoWrapperClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoWrapperClass.
 **/
void
fo_wrapper_base_class_init (FoWrapperClass *klass)
{
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  fo_fo_class->debug_dump_properties = fo_wrapper_debug_dump_properties;
  fo_fo_class->update_from_context = fo_wrapper_update_from_context;
  fo_fo_class->validate2 = fo_wrapper_validate;
  fo_fo_class->allow_mixed_content = TRUE;
}

/**
 * fo_wrapper_class_init:
 * @klass: #FoWrapperClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoWrapperClass.
 **/
void
fo_wrapper_class_init (FoWrapperClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_wrapper_finalize;

  object_class->get_property = fo_wrapper_get_property;
  object_class->set_property = fo_wrapper_set_property;

  fofo_class->validate_content =
    fo_wrapper_validate_content;

  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_wrapper_finalize:
 * @object: #FoWrapper object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoWrapper.
 **/
void
fo_wrapper_finalize (GObject *object)
{
  FoWrapper *fo_wrapper;

  fo_wrapper = FO_WRAPPER (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_wrapper_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoWrapper.
 **/
void
fo_wrapper_get_property (GObject    *object,
                         guint       prop_id,
                         GValue     *value,
                         GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_wrapper_get_id (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_wrapper_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoWrapper.
 **/
void
fo_wrapper_set_property (GObject      *object,
                         guint         prop_id,
                         const GValue *value,
                         GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ID:
      fo_wrapper_set_id (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_wrapper_new:
 * 
 * Creates a new #FoWrapper initialized to default value.
 * 
 * Return value: the new #FoWrapper.
 **/
FoFo*
fo_wrapper_new (void)
{
  return FO_FO (g_object_new (fo_wrapper_get_type (),
                              NULL));
}

static FoFo *
fo_wrapper_replace_parent (FoFo   *current_parent,
			   FoFo   *new_parent,
			   FoNode *child_node)
{
  fo_fo_set_element (new_parent,
		     fo_fo_get_element (current_parent));

  fo_node_insert_after (fo_node_parent (FO_NODE (current_parent)),
			FO_NODE (current_parent),
			FO_NODE (new_parent));

  if (child_node != NULL)
    {
      fo_node_unlink_with_next_siblings (child_node);
      fo_node_insert_with_next_siblings (FO_NODE (new_parent),
					 0,
					 child_node);
    }

  return new_parent;
}
/**
 * fo_wrapper_validate_content:
 * @fo:    #FoWrapper object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
fo_wrapper_validate_content (FoFo    *fo,
                             GError **error)
{
  GError *tmp_error = NULL;
  gboolean is_not_pcdata_or_inline = FALSE;
  gboolean is_not_pcdata_inline_block_neutral = FALSE;
  gboolean is_not_block_or_whitespace = FALSE;
  gboolean has_wrapper = FALSE;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_WRAPPER (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  /* FIXME: doesn't account for markers */
  fo_node_children_foreach (FO_NODE (fo),
			    G_TRAVERSE_ALL,
			    fo_fo_validate_pcdata_inline_block_neutral,
			    &is_not_pcdata_inline_block_neutral);

  if (is_not_pcdata_inline_block_neutral)
    {
      tmp_error = g_error_new (FO_FO_ERROR,
			       FO_FO_ERROR_INVALID_CONTENT,
			       _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			       fo_object_sprintf (FO_OBJECT (fo)));

      return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					       error,
					       tmp_error);
    }

  FoFo *use_parent = fo;

  if (fo_node_n_children (FO_NODE (fo)) == 0)
    {
      FoFo* new_parent = fo_wrapper_inline_empty_new ();

      use_parent = fo_wrapper_replace_parent (use_parent, new_parent, NULL);
      /*g_message ("wrapper_validate_content:: Wrapper has no children: wrapper: %s",
	fo_object_debug_sprintf (fo));*/
    }
  else
    {
      FoNode *child_node;

      child_node = fo_node_first_child (FO_NODE (fo));

      while (child_node)
	{
	  FoNode *next_node = fo_node_next_sibling (child_node);

	  if (FO_IS_TEXT (child_node) &&
	      fo_text_get_whitespace_only (FO_FO (child_node)))
	    {
	      if (!FO_IS_WRAPPER_INLINE (use_parent))
		{
		  FoFo *new_parent;

		  if (next_node &&
		      (FO_IS_INLINE_FO (next_node) ||
		       FO_IS_WRAPPER_INLINE (next_node)))
		    {
		      new_parent = fo_wrapper_inline_new ();
		    }
		  else
		    {
		      new_parent = fo_wrapper_whitespace_new ();
		    }

		  use_parent = fo_wrapper_replace_parent (use_parent, new_parent, child_node);
		}
	    }
	  else if (FO_IS_INLINE_FO (child_node) ||
		   FO_IS_WRAPPER_INLINE (child_node))
	    {
	      if (!FO_IS_WRAPPER_INLINE (use_parent))
		{
		  FoFo *new_parent = fo_wrapper_inline_new ();

		  use_parent = fo_wrapper_replace_parent (use_parent, new_parent, child_node);
		}
	    }
	  else if (FO_IS_BLOCK_FO (child_node) ||
		   FO_IS_WRAPPER_BLOCK (child_node))
	    {
	      if (!FO_IS_WRAPPER_BLOCK (use_parent))
		{
		  FoFo *new_parent = fo_wrapper_block_new ();

		  use_parent = fo_wrapper_replace_parent (use_parent, new_parent, child_node);
		}
	    }
	  else
	    {
	      g_assert_not_reached ();
	    }

	  child_node = next_node;
	}

      g_assert (fo_node_n_children (FO_NODE (fo)) == 0);
      fo_node_unlink (FO_NODE (fo));
      g_object_unref (fo);
    }

  return FALSE;
}

/**
 * fo_wrapper_validate:
 * @fo:              #FoWrapper object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_wrapper_validate (FoFo      *fo,
                     FoContext *current_context,
                     FoContext *parent_context,
                     GError   **error)
{
  FoWrapper *fo_wrapper;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_WRAPPER (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_wrapper = FO_WRAPPER (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_fo_register_id (fo,
                     fo_property_get_value (fo_wrapper->id));
}

/**
 * fo_wrapper_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_wrapper_update_from_context (FoFo      *fo,
                                FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_WRAPPER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_wrapper_set_id (fo,
			  fo_context_get_id (context));
}

/**
 * fo_wrapper_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_wrapper_debug_dump_properties (FoFo *fo,
                                  gint  depth)
{
  FoWrapper *fo_wrapper;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_WRAPPER (fo));

  fo_wrapper = FO_WRAPPER (fo);

  fo_object_debug_dump (fo_wrapper->id, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_wrapper_get_id:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "id" property of @fo_fo.
 *
 * Return value: The "id" property value.
**/
FoProperty *
fo_wrapper_get_id (FoFo *fo_fo)
{
  FoWrapper *fo_wrapper = (FoWrapper *) fo_fo;

  g_return_val_if_fail (fo_wrapper != NULL, NULL);
  g_return_val_if_fail (FO_IS_WRAPPER (fo_wrapper), NULL);

  return fo_wrapper->id;
}

/**
 * fo_wrapper_set_id:
 * @fo_fo: The #FoFo object.
 * @new_id: The new "id" property value.
 * 
 * Sets the "id" property of @fo_fo to @new_id.
 **/
void
fo_wrapper_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoWrapper *fo_wrapper = (FoWrapper *) fo_fo;

  g_return_if_fail (fo_wrapper != NULL);
  g_return_if_fail (FO_IS_WRAPPER (fo_wrapper));
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id != NULL)
    {
      g_object_ref (new_id);
    }
  if (fo_wrapper->id != NULL)
    {
      g_object_unref (fo_wrapper->id);
    }
  fo_wrapper->id = new_id;
  /*g_object_notify (G_OBJECT (fo_wrapper), "id");*/
}
