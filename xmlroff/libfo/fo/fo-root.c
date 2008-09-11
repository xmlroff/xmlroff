/* Fo
 * fo-root.c: 'root' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-root-private.h"
#include "fo/fo-layout-master-set.h"
#include "fo/fo-declarations.h"
#include "fo/fo-page-sequence.h"
#include "property/fo-property-media-usage.h"

/**
 * SECTION:fo-root
 * @short_description: 'root' formatting object
 *
 * Definition: <ulink url="http://www.w3.org/TR/xsl11/&num;fo_root">http://www.w3.org/TR/xsl11/&num;fo_root</ulink>
 */

enum {
  PROP_0,
  PROP_MEDIA_USAGE
};

static void fo_root_class_init  (FoRootClass *klass);
static void fo_root_get_property (GObject      *object,
                                  guint         prop_id,
                                  GValue       *value,
                                  GParamSpec   *pspec);
static void fo_root_set_property (GObject      *object,
                                  guint         prop_id,
                                  const GValue *value,
                                  GParamSpec   *pspec);
static void fo_root_finalize    (GObject           *object);
static gboolean fo_root_validate_content (FoFo    *fo,
                                          GError **error);
static void fo_root_validate (FoFo      *fo,
                              FoContext *current_context,
                              FoContext *parent_context,
                              GError   **error);
static void fo_root_update_from_context (FoFo      *fo,
                                         FoContext *context);
static void fo_root_debug_dump_properties (FoFo *fo,
                                           gint  depth);

static gpointer parent_class;

/**
 * fo_root_get_type:
 * 
 * Register the #FoRoot object type.
 * 
 * Return value: #GType value of the #FoRoot object type.
 **/
GType
fo_root_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoRootClass),
	  NULL,           /* base_init */
	  NULL,           /* base_finalize */
	  (GClassInitFunc) fo_root_class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoRoot),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoRoot",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_root_class_init:
 * @klass: #FoRootClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoRootClass.
 **/
void
fo_root_class_init (FoRootClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_root_finalize;

  object_class->get_property = fo_root_get_property;
  object_class->set_property = fo_root_set_property;

  fofo_class->validate_content =
    fo_root_validate_content;
  fofo_class->validate2 =
    fo_root_validate;
  fofo_class->update_from_context = fo_root_update_from_context;
  fofo_class->debug_dump_properties = fo_root_debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_MEDIA_USAGE,
     g_param_spec_object ("media-usage",
			  _("Media Usage"),
			  _("Media Usage property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_root_finalize:
 * @object: #FoRoot object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoRoot.
 **/
void
fo_root_finalize (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_root_set_media_usage (fo, NULL);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_root_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoRoot.
 **/
void
fo_root_get_property (GObject    *object,
                      guint       prop_id,
                      GValue     *value,
                      GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MEDIA_USAGE:
      g_value_set_object (value, G_OBJECT (fo_root_get_media_usage (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_root_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoRoot.
 **/
void
fo_root_set_property (GObject      *object,
                      guint         prop_id,
                      const GValue *value,
                      GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MEDIA_USAGE:
      fo_root_set_media_usage (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_root_new:
 * 
 * Creates a new #FoRoot initialized to default value.
 * 
 * Return value: the new #FoRoot.
 **/
FoFo*
fo_root_new (void)
{
  return FO_FO (g_object_new (fo_root_get_type (),
                              NULL));
}

/**
 * fo_root_validate_content:
 * @fo:    #FoRoot object to validate.
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
fo_root_validate_content (FoFo    *fo,
                          GError **error)
{
  FoNode *child_node;
  GError *tmp_error;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_ROOT (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_fo_trim_whitespace_children (fo);

  child_node = fo_node_first_child (FO_NODE (fo));

  if (!FO_IS_LAYOUT_MASTER_SET (child_node))
    goto error;

  while (child_node)
    {
      FoNode *next_child = fo_node_next_sibling (child_node);

      if (FO_IS_LAYOUT_MASTER_SET (child_node))
	{
	  if (FO_IS_DECLARATIONS (next_child) ||
	      FO_IS_PAGE_SEQUENCE (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_DECLARATIONS (child_node))
	{
	  if (FO_IS_PAGE_SEQUENCE (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_PAGE_SEQUENCE (child_node))
	{
	  if (!next_child ||
	      FO_IS_PAGE_SEQUENCE (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else
	{
	  goto error;
	}
    }

  return FALSE;

 error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (fo));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
}

static void
fo_root_resolve_media_usage (FoFo      *fo,
			     FoContext *current_context)
{
  FoProperty *media_usage = fo_context_get_media_usage (current_context);
  FoDatatype *datatype = NULL;

  if (media_usage != NULL)
    {
      datatype = fo_property_get_value (media_usage);
    }

  if (datatype == NULL)
    {
      FoDatatype *new_datatype =  g_object_ref (fo_enum_get_enum_by_nick ("paginate"));

      FoProperty *new_media_usage = fo_property_media_usage_new ();

      fo_property_set_value (new_media_usage, datatype);

      fo_context_set_media_usage (current_context, new_media_usage);

      g_object_unref (new_datatype);
    }
  else if (FO_IS_ENUM (datatype))
    {
      FoEnumEnum value = fo_enum_get_value (datatype);

      if (value != FO_ENUM_ENUM_PAGINATE)
	{
	  FoDatatype *new_datatype =  g_object_ref (fo_enum_get_enum_by_nick ("paginate"));
	  gchar *datatype_sprintf = fo_object_sprintf (datatype);
	  gchar *new_datatype_sprintf = fo_object_sprintf (new_datatype);
	  GError *datatype_warning =
	    g_error_new (FO_FO_ERROR,
			 FO_FO_ERROR_DATATYPE_REPLACE,
			 _(fo_fo_error_messages[FO_FO_ERROR_DATATYPE_REPLACE]),
			 "media-usage",
			 datatype_sprintf,
			 g_type_name (G_TYPE_FROM_INSTANCE (datatype)),
			 new_datatype_sprintf,
			 g_type_name (G_TYPE_FROM_INSTANCE (new_datatype)));

	  fo_object_log_warning (FO_OBJECT (fo),
				 &datatype_warning);

	  g_free (datatype_sprintf);
	  g_free (new_datatype_sprintf);

	  fo_property_set_value (media_usage, datatype);

	  g_object_unref (datatype);
	  g_object_unref (new_datatype);
	}
    }
}

/**
 * fo_root_validate:
 * @fo:              #FoRoot object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_root_validate (FoFo      *fo,
                  FoContext *current_context,
                  FoContext *parent_context,
                  GError   **error)
{
  FoRoot *fo_root;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_ROOT (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_root = FO_ROOT (fo);

  fo_root_resolve_media_usage (fo, current_context);
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_root_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_root_update_from_context (FoFo      *fo,
                             FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_ROOT (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_root_set_media_usage (fo,
			  fo_context_get_media_usage (context));
}

/**
 * fo_root_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_root_debug_dump_properties (FoFo *fo,
                               gint  depth)
{
  FoRoot *fo_root;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_ROOT (fo));

  fo_root = FO_ROOT (fo);

  fo_object_debug_dump (fo_root->media_usage, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_root_get_media_usage:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "media-usage" property of @fo_fo.
 *
 * Return value: The "media-usage" property value.
**/
FoProperty *
fo_root_get_media_usage (FoFo *fo_fo)
{
  FoRoot *fo_root = (FoRoot *) fo_fo;

  g_return_val_if_fail (fo_root != NULL, NULL);
  g_return_val_if_fail (FO_IS_ROOT (fo_root), NULL);

  return fo_root->media_usage;
}

/**
 * fo_root_set_media_usage:
 * @fo_fo: The #FoFo object.
 * @new_media_usage: The new "media-usage" property value.
 * 
 * Sets the "media-usage" property of @fo_fo to @new_media_usage.
 **/
void
fo_root_set_media_usage (FoFo *fo_fo,
		         FoProperty *new_media_usage)
{
  FoRoot *fo_root = (FoRoot *) fo_fo;

  g_return_if_fail (fo_root != NULL);
  g_return_if_fail (FO_IS_ROOT (fo_root));
  g_return_if_fail ((new_media_usage == NULL) ||
		    FO_IS_PROPERTY_MEDIA_USAGE (new_media_usage));

  if (new_media_usage != NULL)
    {
      g_object_ref (new_media_usage);
    }
  if (fo_root->media_usage != NULL)
    {
      g_object_unref (fo_root->media_usage);
    }
  fo_root->media_usage = new_media_usage;
  /*g_object_notify (G_OBJECT (fo_root), "media-usage");*/
}
