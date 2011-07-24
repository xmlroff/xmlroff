/* Fo
 * fo-simple-page-master.c: 'simple-page-master' formatting object
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-simple-page-master-private.h"
#include "fo/fo-simple-page-master-area.h"
#include "fo/fo-tree.h"
#include "fo/fo-region-body.h"
#include "fo/fo-region-before.h"
#include "fo/fo-region-after.h"
#include "fo/fo-region-start.h"
#include "fo/fo-region-end.h"
#include "fo/fo-fixed-page-sequence-walker.h"
#include "area/fo-area.h"
#include "property/fo-property-end-indent.h"
#include "property/fo-property-margin-bottom.h"
#include "property/fo-property-margin-left.h"
#include "property/fo-property-margin-right.h"
#include "property/fo-property-margin-top.h"
#include "property/fo-property-master-name.h"
#include "property/fo-property-page-height.h"
#include "property/fo-property-page-width.h"
#include "property/fo-property-reference-orientation.h"
#include "property/fo-property-space-after.h"
#include "property/fo-property-space-before.h"
#include "property/fo-property-start-indent.h"
#include "property/fo-property-writing-mode.h"

enum {
  PROP_0,
  PROP_REGION_BODY,
  PROP_REGION_BEFORE,
  PROP_REGION_AFTER,
  PROP_REGION_START,
  PROP_REGION_END,
  PROP_END_INDENT,
  PROP_MARGIN_BOTTOM,
  PROP_MARGIN_LEFT,
  PROP_MARGIN_RIGHT,
  PROP_MARGIN_TOP,
  PROP_PAGE_HEIGHT,
  PROP_PAGE_WIDTH,
  PROP_REFERENCE_ORIENTATION,
  PROP_SPACE_AFTER,
  PROP_SPACE_BEFORE,
  PROP_START_INDENT,
  PROP_WRITING_MODE
};

static void _init        (FoSimplePageMaster      *fo_simple_page_master);
static void _class_init  (FoSimplePageMasterClass *klass);
static void fo_simple_page_master_get_property (GObject      *object,
                                                guint         prop_id,
                                                GValue       *value,
                                                GParamSpec   *pspec);
static void fo_simple_page_master_set_property (GObject      *object,
                                                guint         prop_id,
                                                const GValue *value,
                                                GParamSpec   *pspec);
static void _dispose    (GObject           *object);
static gboolean fo_simple_page_master_validate_content (FoFo    *fo,
                                                        GError **error);
static void fo_simple_page_master_validate (FoFo      *fo,
                                            FoContext *current_context,
                                            FoContext *parent_context,
                                            GError   **error);
static void _update_from_context (FoFo      *fo,
				  FoContext *context);
static void _debug_dump_properties (FoFo *fo,
				    gint  depth);

static void _free_hash_key (gpointer key,
			    gpointer value,
			    gpointer user_data);
static void _children_properties_resolve (FoFo       *this_fo,
					  FoArea     *this_fo_parent_area,
					  FoArea    **new_area,
					  GHashTable *prop_eval_hash,
					  FoDoc      *fo_doc,
					  gboolean    continue_after_error,
					  FoDebugFlag   debug_level,
					  FoWarningFlag warning_mode,
					  GError    **error);

static FoPageSequenceWalker * _new_walker (FoFo    *fo_fo,
					   GError **error);

static gpointer parent_class;

/**
 * fo_simple_page_master_get_type:
 * 
 * Register the #FoSimplePageMaster object type.
 * 
 * Return value: #GType value of the #FoSimplePageMaster object type.
 **/
GType
fo_simple_page_master_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoSimplePageMasterClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) _class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoSimplePageMaster),
        0,              /* n_preallocs */
        (GInstanceInitFunc) _init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_PAGE_MASTER,
                                            "FoSimplePageMaster",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * _init:
 * @fo_simple_page_master: FoSimplePageMaster object to initialise
 * 
 * Implements GInstanceInitFunc for FoSimplePageMaster
 **/
static void
_init (FoSimplePageMaster *fo_simple_page_master)
{
  fo_simple_page_master->region_name_hash =
    g_hash_table_new (g_str_hash, g_str_equal);
}

/**
 * _class_init:
 * @klass: #FoSimplePageMasterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoSimplePageMasterClass.
 **/
static void
_class_init (FoSimplePageMasterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);
  FoPageMasterClass *page_master_class = FO_PAGE_MASTER_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->dispose = _dispose;

  object_class->get_property = fo_simple_page_master_get_property;
  object_class->set_property = fo_simple_page_master_set_property;

  fo_fo_class->validate_content =
    fo_simple_page_master_validate_content;
  fo_fo_class->validate2 =
    fo_simple_page_master_validate;
  fo_fo_class->update_from_context = _update_from_context;
  fo_fo_class->debug_dump_properties = _debug_dump_properties;
  fo_fo_class->generate_reference_area = TRUE;
  fo_fo_class->area_new2 =
    fo_simple_page_master_area_new;
  fo_fo_class->children_properties_resolve =
    _children_properties_resolve;

  page_master_class->new_walker = _new_walker;

  g_object_class_install_property
    (object_class,
     PROP_REGION_BODY,
     g_param_spec_object ("region-body",
			  _("Region Body"),
			  _("REGION_BODY"),
			  FO_TYPE_REGION_BODY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_REGION_BEFORE,
     g_param_spec_object ("region-before",
			  _("Region Before"),
			  _("REGION_BEFORE"),
			  FO_TYPE_REGION_BEFORE,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_REGION_AFTER,
     g_param_spec_object ("region-after",
			  _("Region After"),
			  _("REGION_AFTER"),
			  FO_TYPE_REGION_AFTER,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_REGION_START,
     g_param_spec_object ("region-start",
			  _("Region Start"),
			  _("REGION_START"),
			  FO_TYPE_REGION_START,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_REGION_END,
     g_param_spec_object ("region-end",
			  _("Region End"),
			  _("REGION_END"),
			  FO_TYPE_REGION_END,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_END_INDENT,
     g_param_spec_object ("end-indent",
			  _("End Indent"),
			  _("End Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_BOTTOM,
     g_param_spec_object ("margin-bottom",
			  _("Margin Bottom"),
			  _("Margin Bottom property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_LEFT,
     g_param_spec_object ("margin-left",
			  _("Margin Left"),
			  _("Margin Left property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_RIGHT,
     g_param_spec_object ("margin-right",
			  _("Margin Right"),
			  _("Margin Right property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_MARGIN_TOP,
     g_param_spec_object ("margin-top",
			  _("Margin Top"),
			  _("Margin Top property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PAGE_HEIGHT,
     g_param_spec_object ("page-height",
			  _("Page Height"),
			  _("Page Height property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_PAGE_WIDTH,
     g_param_spec_object ("page-width",
			  _("Page Width"),
			  _("Page Width property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_REFERENCE_ORIENTATION,
     g_param_spec_object ("reference-orientation",
			  _("Reference Orientation"),
			  _("Reference Orientation property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_AFTER,
     g_param_spec_object ("space-after",
			  _("Space After"),
			  _("Space After property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SPACE_BEFORE,
     g_param_spec_object ("space-before",
			  _("Space Before"),
			  _("Space Before property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_START_INDENT,
     g_param_spec_object ("start-indent",
			  _("Start Indent"),
			  _("Start Indent property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WRITING_MODE,
     g_param_spec_object ("writing-mode",
			  _("Writing Mode"),
			  _("Writing Mode property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * _dispose:
 * @object: #FoSimplePageMaster object to dispose.
 * 
 * Implements dispose() for #FoSimplePageMaster.
 **/
static void
_dispose (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to the regions. */
  fo_simple_page_master_set_region_body (fo, NULL);
  fo_simple_page_master_set_region_before (fo, NULL);
  fo_simple_page_master_set_region_after (fo, NULL);
  fo_simple_page_master_set_region_start (fo, NULL);
  fo_simple_page_master_set_region_end (fo, NULL);

  /* Release references to all property objects. */
  fo_simple_page_master_set_end_indent (fo, NULL);
  fo_simple_page_master_set_margin_bottom (fo, NULL);
  fo_simple_page_master_set_margin_left (fo, NULL);
  fo_simple_page_master_set_margin_right (fo, NULL);
  fo_simple_page_master_set_margin_top (fo, NULL);
  fo_simple_page_master_set_page_height (fo, NULL);
  fo_simple_page_master_set_page_width (fo, NULL);
  fo_simple_page_master_set_reference_orientation (fo, NULL);
  fo_simple_page_master_set_space_after (fo, NULL);
  fo_simple_page_master_set_space_before (fo, NULL);
  fo_simple_page_master_set_start_indent (fo, NULL);
  fo_simple_page_master_set_writing_mode (fo, NULL);

  FoSimplePageMaster *fo_simple_page_master =
    FO_SIMPLE_PAGE_MASTER (object);

  if (fo_simple_page_master->region_name_hash != NULL)
    {
      g_hash_table_foreach (fo_simple_page_master->region_name_hash,
			    _free_hash_key,
			    NULL);
      g_hash_table_destroy (fo_simple_page_master->region_name_hash);

      fo_simple_page_master->region_name_hash = NULL;
    }

  if (fo_simple_page_master->area != NULL)
    {
      fo_area_release (fo_simple_page_master->area);
      fo_simple_page_master->area = NULL;
    }

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * fo_simple_page_master_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoSimplePageMaster.
 **/
void
fo_simple_page_master_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_END_INDENT:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_end_indent (fo_fo)));
      break;
    case PROP_MARGIN_BOTTOM:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_margin_bottom (fo_fo)));
      break;
    case PROP_MARGIN_LEFT:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_margin_left (fo_fo)));
      break;
    case PROP_MARGIN_RIGHT:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_margin_right (fo_fo)));
      break;
    case PROP_MARGIN_TOP:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_margin_top (fo_fo)));
      break;
    case PROP_PAGE_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_page_height (fo_fo)));
      break;
    case PROP_PAGE_WIDTH:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_page_width (fo_fo)));
      break;
    case PROP_REFERENCE_ORIENTATION:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_reference_orientation (fo_fo)));
      break;
    case PROP_SPACE_AFTER:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_space_after (fo_fo)));
      break;
    case PROP_SPACE_BEFORE:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_space_before (fo_fo)));
      break;
    case PROP_START_INDENT:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_start_indent (fo_fo)));
      break;
    case PROP_WRITING_MODE:
      g_value_set_object (value, G_OBJECT (fo_simple_page_master_get_writing_mode (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_simple_page_master_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoSimplePageMaster.
 **/
void
fo_simple_page_master_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_END_INDENT:
      fo_simple_page_master_set_end_indent (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_BOTTOM:
      fo_simple_page_master_set_margin_bottom (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_LEFT:
      fo_simple_page_master_set_margin_left (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_RIGHT:
      fo_simple_page_master_set_margin_right (fo_fo, g_value_get_object (value));
      break;
    case PROP_MARGIN_TOP:
      fo_simple_page_master_set_margin_top (fo_fo, g_value_get_object (value));
      break;
    case PROP_PAGE_HEIGHT:
      fo_simple_page_master_set_page_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_PAGE_WIDTH:
      fo_simple_page_master_set_page_width (fo_fo, g_value_get_object (value));
      break;
    case PROP_REFERENCE_ORIENTATION:
      fo_simple_page_master_set_reference_orientation (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_AFTER:
      fo_simple_page_master_set_space_after (fo_fo, g_value_get_object (value));
      break;
    case PROP_SPACE_BEFORE:
      fo_simple_page_master_set_space_before (fo_fo, g_value_get_object (value));
      break;
    case PROP_START_INDENT:
      fo_simple_page_master_set_start_indent (fo_fo, g_value_get_object (value));
      break;
    case PROP_WRITING_MODE:
      fo_simple_page_master_set_writing_mode (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_simple_page_master_new:
 * 
 * Creates a new #FoSimplePageMaster initialized to default value.
 * 
 * Return value: the new #FoSimplePageMaster.
 **/
FoFo*
fo_simple_page_master_new (void)
{
  return FO_FO (g_object_new (fo_simple_page_master_get_type (),
                              NULL));
}

/**
 * _new_walker:
 * @fo_fo: The #FoPageMaster object.
 * 
 * Gets a new #FoPageSequenceWalker for @fo.
 **/
static FoPageSequenceWalker *
_new_walker (FoFo  *fo_fo,
	     GError **error)
{
  g_return_val_if_fail (FO_IS_PAGE_MASTER (fo_fo), NULL);

  return FO_PAGE_SEQUENCE_WALKER (fo_fixed_page_sequence_walker_new (fo_fo));
}

/**
 * _free_hash_key:
 * @key:       The key
 * @value:     The value (unused)
 * @user_data: Extra data (unused)
 * 
 * Free a single hash key
 **/
static void
_free_hash_key (gpointer key,
		gpointer value G_GNUC_UNUSED,
		gpointer user_data G_GNUC_UNUSED)
{
  g_free (key);
}

/**
 * _region_name_add:
 * @simple_page_master: #FoSimplePageMaster
 * @fo:                 The page region object
 * 
 * Add a page region object to the page region name/object hash
 * maintained by @simple_page_master.
 **/
static void
_region_name_add (FoSimplePageMaster *simple_page_master,
		  FoFo *fo)
{
  g_return_if_fail (simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (simple_page_master));
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION (fo));

  gchar *name =
    fo_name_get_value (fo_property_get_value (fo_region_get_region_name (fo)));

  /*
  g_print ("Adding '%s'\n", name);
  */
  if (g_hash_table_lookup (simple_page_master->region_name_hash, name))
    {
      g_warning ("'%s' already in master name hash.", name);
    }
  else
    {
      g_hash_table_insert (simple_page_master->region_name_hash,
			   name,
			   fo);
    }
}

/**
 * _region_name_remove:
 * @simple_page_master: #FoSimplePageMaster
 * @fo:                 The page region object
 * 
 * Remove a page region object from the page region name/object hash
 * maintained by @simple_page_master.
 **/
static void
_region_name_remove (FoSimplePageMaster *simple_page_master,
		     FoFo *fo)
{
  g_return_if_fail (simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (simple_page_master));
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_REGION (fo));

  gchar *name =
    fo_name_get_value (fo_property_get_value (fo_region_get_region_name (fo)));

  /*
  g_print ("Adding '%s'\n", name);
  */
  if (!g_hash_table_lookup (simple_page_master->region_name_hash, name))
    {
      g_warning ("'%s' not in master name hash.", name);
    }
  else
    {
      g_hash_table_remove (simple_page_master->region_name_hash,
			   name);
    }
}

/**
 * fo_simple_page_master_region_name_get:
 * @simple_page_master: #FoSimplePageMaster that has hash of regions
 * @name:               Name of page region
 * 
 * Get the page region object for a page region name.
 * 
 * Return value: Page region object
 **/
FoFo*
fo_simple_page_master_region_name_get (FoFo *simple_page_master,
				       const gchar *name)
{
  g_return_val_if_fail (simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (simple_page_master), NULL);
  g_return_val_if_fail (name != NULL, NULL);

  return g_hash_table_lookup (FO_SIMPLE_PAGE_MASTER (simple_page_master)->region_name_hash,
			      name);
}

/**
 * fo_simple_page_master_validate_content:
 * @fo:    #FoSimplePageMaster object to validate.
 * @error: #GError indicating error condition, if any.
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches #GNodeTraverseFunc model: %FALSE indicates
 * content model is correct, or %TRUE indicates an error.  When used
 * with fo_node_traverse(), returning %TRUE stops the traversal.
 * 
 * Content model: (region-body, region-before?, region-after?,
 *                 region-start?, region-end?)
 *
 * Return value: %FALSE if content model okay, %TRUE if not.
 **/
gboolean
fo_simple_page_master_validate_content (FoFo    *fo,
                                        GError **error)
{
  GError *tmp_error = NULL;
  FoNode *fo_node;
  FoNode *child_node;
  gint n_children;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  fo_node = FO_NODE (fo);

  fo_fo_trim_whitespace_children (fo);

  n_children = fo_node_n_children (fo_node);

  if ((n_children < 1) ||
      (n_children > 5))
    {
      goto error;
    }

  child_node = fo_node_first_child (fo_node);

  if (!FO_IS_REGION_BODY (child_node))
    goto error;

  while (child_node)
    {
      FoNode *next_child = fo_node_next_sibling (child_node);

      if (FO_IS_REGION_BODY (child_node))
	{
	  if (!next_child ||
	      FO_IS_REGION_BEFORE (next_child) ||
	      FO_IS_REGION_AFTER (next_child) ||
	      FO_IS_REGION_START (next_child) ||
	      FO_IS_REGION_END (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_REGION_BEFORE (child_node))
	{
	  if (!next_child ||
	      FO_IS_REGION_AFTER (next_child) ||
	      FO_IS_REGION_START (next_child) ||
	      FO_IS_REGION_END (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_REGION_AFTER (child_node))
	{
	  if (!next_child ||
	      FO_IS_REGION_START (next_child) ||
	      FO_IS_REGION_END (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_REGION_START (child_node))
	{
	  if (!next_child ||
	      FO_IS_REGION_END (next_child))
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
	}
      else if (FO_IS_REGION_END (child_node))
	{
	  if (!next_child)
	    {
	      child_node = next_child;
	    }
	  else
	    {
	      goto error;
	    }
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

/**
 * fo_simple_page_master_validate:
 * @fo:              #FoSimplePageMaster object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_simple_page_master_validate (FoFo      *fo,
                                FoContext *current_context,
                                FoContext *parent_context,
                                GError   **error)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  FO_FO_CLASS (parent_class)->validate2 (fo,
					 current_context,
					 parent_context,
					 error);
}

static void
_children_properties_resolve (FoFo       *this_fo,
			      FoArea     *this_fo_parent_area,
			      FoArea    **new_area,
			      GHashTable *prop_eval_hash,
			      FoDoc      *fo_doc,
			      gboolean    continue_after_error,
			      FoDebugFlag   debug_level,
			      FoWarningFlag warning_mode,
			      GError    **error)
{
  GError *tmp_error = NULL;

  g_return_if_fail (FO_IS_FO (this_fo));
  g_return_if_fail (FO_IS_AREA (this_fo_parent_area));
  g_return_if_fail (*new_area == NULL);
  g_return_if_fail (error == NULL || *error == NULL);

#if defined(LIBFO_DEBUG) && 0
  g_message ("node_children_properties_resolve:: this_fo: %s; this_fo_parent_area: %s",
	     fo_object_debug_sprintf (this_fo),
	     fo_object_debug_sprintf (this_fo_parent_area));
#endif

  FoPropertyResolveContext prop_context;
  prop_context.reference_area       = fo_area_get_reference (this_fo_parent_area);
  prop_context.prop_eval_hash       = prop_eval_hash;
  prop_context.continue_after_error = continue_after_error;
  prop_context.debug_level          = debug_level;
  prop_context.warning_mode         = warning_mode;
  prop_context.error                = &tmp_error;

  gboolean resolve_attributes_halted =
    fo_fo_resolve_property_attributes (FO_NODE (this_fo),
				       &prop_context);

  if (resolve_attributes_halted)
    {
      fo_object_log_or_propagate_error (FO_OBJECT (this_fo),
					error,
					tmp_error);
      return;
    }

  FoSimplePageMaster *simple_page_master =
    FO_SIMPLE_PAGE_MASTER (this_fo);
  FoFoAreaNew2Context area_new2_context;
  area_new2_context.fo_doc               = fo_doc;
  area_new2_context.parent_area          = NULL;
  area_new2_context.new_area             = &(simple_page_master->area);
  area_new2_context.continue_after_error = continue_after_error;
  area_new2_context.debug_level          = debug_level;

  fo_fo_area_new2 (this_fo,
		   &area_new2_context,
		   &tmp_error);

  FoArea *child_fo_parent_area = simple_page_master->area;

#if defined(LIBFO_DEBUG) && 0
  g_message ("node_children_properties_resolve:: initial *new_area: %s",
	     fo_object_debug_sprintf (*new_area));
#endif

  FoNode *child_node = fo_node_first_child (FO_NODE (this_fo));
  while (child_node)
    {
      FoArea *area = NULL;

      fo_fo_children_properties_resolve (FO_FO (child_node),
					 child_fo_parent_area,
					 &area,
					 prop_eval_hash,
					 fo_doc,
					 continue_after_error,
					 debug_level,
					 warning_mode,
					 &tmp_error);

      if (tmp_error != NULL)
	{
	  g_propagate_error (/*FO_OBJECT (child_node),*/
					    error,
					    tmp_error);
	  return;
	}
#if defined(LIBFO_DEBUG) && 0
      g_message ("node_children_properties_resolve:: this_fo: %s; *new_area: %s; child_fo_parent_area: %s",
		 fo_object_debug_sprintf (this_fo),
		 *new_area ?
		 fo_object_debug_sprintf (*new_area) :
		 "(null)",
		 fo_object_debug_sprintf (child_fo_parent_area));
#endif
      if (area != NULL)
	{
	  fo_area_add_child (simple_page_master->area,
			     area);
	  area = fo_area_size_request (area);
	}

      child_node = fo_node_next_sibling (child_node);
    }
#if defined(LIBFO_DEBUG) && 0
  g_message ("node_children_properties_resolve:: this_fo: %s; final *new_area: %s",
	     fo_object_debug_sprintf (this_fo),
	     *new_area ?
	     fo_object_debug_sprintf (*new_area) :
	     "(null)");
#endif

  *new_area = NULL;
}

/**
 * _update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
static void
_update_from_context (FoFo      *fo,
		      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_simple_page_master_set_end_indent (fo,
			  fo_context_get_end_indent (context));
  fo_simple_page_master_set_margin_bottom (fo,
			  fo_context_get_margin_bottom (context));
  fo_simple_page_master_set_margin_left (fo,
			  fo_context_get_margin_left (context));
  fo_simple_page_master_set_margin_right (fo,
			  fo_context_get_margin_right (context));
  fo_simple_page_master_set_margin_top (fo,
			  fo_context_get_margin_top (context));
  fo_simple_page_master_set_page_height (fo,
			  fo_context_get_page_height (context));
  fo_simple_page_master_set_page_width (fo,
			  fo_context_get_page_width (context));
  fo_simple_page_master_set_reference_orientation (fo,
			  fo_context_get_reference_orientation (context));
  fo_simple_page_master_set_space_after (fo,
			  fo_context_get_space_after (context));
  fo_simple_page_master_set_space_before (fo,
			  fo_context_get_space_before (context));
  fo_simple_page_master_set_start_indent (fo,
			  fo_context_get_start_indent (context));
  fo_simple_page_master_set_writing_mode (fo,
			  fo_context_get_writing_mode (context));

  FO_FO_CLASS (parent_class)->update_from_context (fo,
						   context);
}

/**
 * _debug_dump_hash:
 * @key:   Key string
 * @value: Pointer as value
 * @data:  Indent cast as pointer
 * 
 * Log the key and value combination of a hash table entry.
 **/
static void
_debug_dump_hash (gpointer key,
		  gpointer value,
		  gpointer data)
{
  gchar *indent = g_strnfill (GPOINTER_TO_INT (data) * 2, ' ');

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s : %p",
	 indent, (gchar *) key, value);

  g_free (indent);
}

/**
 * _debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
_debug_dump_properties (FoFo *fo,
			gint  depth)
{
  FoSimplePageMaster *fo_simple_page_master;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo));

  fo_simple_page_master = FO_SIMPLE_PAGE_MASTER (fo);

  fo_object_debug_dump (fo_simple_page_master->end_indent, depth);
  fo_object_debug_dump (fo_simple_page_master->margin_bottom, depth);
  fo_object_debug_dump (fo_simple_page_master->margin_left, depth);
  fo_object_debug_dump (fo_simple_page_master->margin_right, depth);
  fo_object_debug_dump (fo_simple_page_master->margin_top, depth);
  fo_object_debug_dump (fo_simple_page_master->page_height, depth);
  fo_object_debug_dump (fo_simple_page_master->page_width, depth);
  fo_object_debug_dump (fo_simple_page_master->reference_orientation, depth);
  fo_object_debug_dump (fo_simple_page_master->space_after, depth);
  fo_object_debug_dump (fo_simple_page_master->space_before, depth);
  fo_object_debug_dump (fo_simple_page_master->start_indent, depth);
  fo_object_debug_dump (fo_simple_page_master->writing_mode, depth);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sarea:",
	 indent);
  fo_object_debug_dump (fo_simple_page_master->area, depth + 2);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sregion-name hash:",
	 indent);

  g_hash_table_foreach (fo_simple_page_master->region_name_hash,
			_debug_dump_hash,
			GINT_TO_POINTER (depth + 1));

  g_free (indent);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_simple_page_master_get_area:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the areas generated from @fo_fo.
 *
 * Return value: The areas generated from @fo_fo
**/
FoArea *
fo_simple_page_master_get_area (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->area;
}

/**
 * fo_simple_page_master_get_region_body:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "region-body" of @fo_fo.
 *
 * Return value: The "region-body" value.
**/
FoFo *
fo_simple_page_master_get_region_body (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master),
			NULL);

  return fo_simple_page_master->region_body;
}

/**
 * fo_simple_page_master_set_region_body:
 * @fo_fo: The #FoFo object.
 * @new_region_body: The new "region-body" value.
 * 
 * Sets the "region-body" of @fo_fo to @new_region_body.
 **/
void
fo_simple_page_master_set_region_body (FoFo *fo_fo,
		         FoFo *new_region_body)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_region_body == NULL) ||
		    FO_IS_REGION_BODY (new_region_body));

  if (new_region_body != NULL)
    {
      g_object_ref (new_region_body);
    }
  if (fo_simple_page_master->region_body != NULL)
    {
      _region_name_remove (fo_simple_page_master,
			   fo_simple_page_master->region_body);
      g_object_unref (fo_simple_page_master->region_body);
    }

  fo_simple_page_master->region_body = new_region_body;

  if (new_region_body != NULL)
    {
      _region_name_add (fo_simple_page_master,
			new_region_body);
    }
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "region-body");*/
}

/**
 * fo_simple_page_master_get_region_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "region-before" of @fo_fo.
 *
 * Return value: The "region-before" value.
**/
FoFo *
fo_simple_page_master_get_region_before (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master),
			NULL);

  return fo_simple_page_master->region_before;
}

/**
 * fo_simple_page_master_set_region_before:
 * @fo_fo: The #FoFo object.
 * @new_region_before: The new "region-before" value.
 * 
 * Sets the "region-before" of @fo_fo to @new_region_before.
 **/
void
fo_simple_page_master_set_region_before (FoFo *fo_fo,
		         FoFo *new_region_before)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_region_before == NULL) ||
		    FO_IS_REGION_BEFORE (new_region_before));

  if (new_region_before != NULL)
    {
      g_object_ref (new_region_before);
    }
  if (fo_simple_page_master->region_before != NULL)
    {
      _region_name_remove (fo_simple_page_master,
			   fo_simple_page_master->region_before);
      g_object_unref (fo_simple_page_master->region_before);
    }
  fo_simple_page_master->region_before = new_region_before;

  if (new_region_before != NULL)
    {
      _region_name_add (fo_simple_page_master,
			new_region_before);
    }
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "region-before");*/
}

/**
 * fo_simple_page_master_get_region_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "region-after" of @fo_fo.
 *
 * Return value: The "region-after" value.
**/
FoFo *
fo_simple_page_master_get_region_after (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master),
			NULL);

  return fo_simple_page_master->region_after;
}

/**
 * fo_simple_page_master_set_region_after:
 * @fo_fo: The #FoFo object.
 * @new_region_after: The new "region-after" value.
 * 
 * Sets the "region-after" of @fo_fo to @new_region_after.
 **/
void
fo_simple_page_master_set_region_after (FoFo *fo_fo,
		         FoFo *new_region_after)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_region_after == NULL) ||
		    FO_IS_REGION_AFTER (new_region_after));

  if (new_region_after != NULL)
    {
      g_object_ref (new_region_after);
    }
  if (fo_simple_page_master->region_after != NULL)
    {
      _region_name_remove (fo_simple_page_master,
			   fo_simple_page_master->region_after);
      g_object_unref (fo_simple_page_master->region_after);
    }
  fo_simple_page_master->region_after = new_region_after;

  if (new_region_after != NULL)
    {
      _region_name_add (fo_simple_page_master,
			new_region_after);
    }
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "region-after");*/
}

/**
 * fo_simple_page_master_get_region_start:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "region-start" of @fo_fo.
 *
 * Return value: The "region-start" value.
**/
FoFo *
fo_simple_page_master_get_region_start (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master),
			NULL);

  return fo_simple_page_master->region_start;
}

/**
 * fo_simple_page_master_set_region_start:
 * @fo_fo: The #FoFo object.
 * @new_region_start: The new "region-start" value.
 * 
 * Sets the "region-start" of @fo_fo to @new_region_start.
 **/
void
fo_simple_page_master_set_region_start (FoFo *fo_fo,
		         FoFo *new_region_start)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_region_start == NULL) ||
		    FO_IS_REGION_START (new_region_start));

  if (new_region_start != NULL)
    {
      g_object_ref (new_region_start);
    }
  if (fo_simple_page_master->region_start != NULL)
    {
      _region_name_remove (fo_simple_page_master,
			   fo_simple_page_master->region_start);
      g_object_unref (fo_simple_page_master->region_start);
    }
  fo_simple_page_master->region_start = new_region_start;

  if (new_region_start != NULL)
    {
      _region_name_add (fo_simple_page_master,
			new_region_start);
    }
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "region-start");*/
}

/**
 * fo_simple_page_master_get_region_end:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "region-end" of @fo_fo.
 *
 * Return value: The "region-end" value.
**/
FoFo *
fo_simple_page_master_get_region_end (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master),
			NULL);

  return fo_simple_page_master->region_end;
}

/**
 * fo_simple_page_master_set_region_end:
 * @fo_fo: The #FoFo object.
 * @new_region_end: The new "region-end" value.
 * 
 * Sets the "region-end" of @fo_fo to @new_region_end.
 **/
void
fo_simple_page_master_set_region_end (FoFo *fo_fo,
		         FoFo *new_region_end)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_region_end == NULL) ||
		    FO_IS_REGION_END (new_region_end));

  if (new_region_end != NULL)
    {
      g_object_ref (new_region_end);
    }
  if (fo_simple_page_master->region_end != NULL)
    {
      _region_name_remove (fo_simple_page_master,
			   fo_simple_page_master->region_end);
      g_object_unref (fo_simple_page_master->region_end);
    }
  fo_simple_page_master->region_end = new_region_end;

  if (new_region_end != NULL)
    {
      _region_name_add (fo_simple_page_master,
			new_region_end);
    }
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "region-end");*/
}

/**
 * fo_simple_page_master_get_end_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "end-indent" property of @fo_fo.
 *
 * Return value: The "end-indent" property value.
**/
FoProperty *
fo_simple_page_master_get_end_indent (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->end_indent;
}

/**
 * fo_simple_page_master_set_end_indent:
 * @fo_fo: The #FoFo object.
 * @new_end_indent: The new "end-indent" property value.
 * 
 * Sets the "end-indent" property of @fo_fo to @new_end_indent.
 **/
void
fo_simple_page_master_set_end_indent (FoFo *fo_fo,
		         FoProperty *new_end_indent)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_end_indent == NULL) ||
		    FO_IS_PROPERTY_END_INDENT (new_end_indent));

  if (new_end_indent != NULL)
    {
      g_object_ref (new_end_indent);
    }
  if (fo_simple_page_master->end_indent != NULL)
    {
      g_object_unref (fo_simple_page_master->end_indent);
    }
  fo_simple_page_master->end_indent = new_end_indent;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "end-indent");*/
}

/**
 * fo_simple_page_master_get_margin_bottom:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-bottom" property of @fo_fo.
 *
 * Return value: The "margin-bottom" property value.
**/
FoProperty *
fo_simple_page_master_get_margin_bottom (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->margin_bottom;
}

/**
 * fo_simple_page_master_set_margin_bottom:
 * @fo_fo: The #FoFo object.
 * @new_margin_bottom: The new "margin-bottom" property value.
 * 
 * Sets the "margin-bottom" property of @fo_fo to @new_margin_bottom.
 **/
void
fo_simple_page_master_set_margin_bottom (FoFo *fo_fo,
		         FoProperty *new_margin_bottom)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_margin_bottom == NULL) ||
		    FO_IS_PROPERTY_MARGIN_BOTTOM (new_margin_bottom));

  if (new_margin_bottom != NULL)
    {
      g_object_ref (new_margin_bottom);
    }
  if (fo_simple_page_master->margin_bottom != NULL)
    {
      g_object_unref (fo_simple_page_master->margin_bottom);
    }
  fo_simple_page_master->margin_bottom = new_margin_bottom;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "margin-bottom");*/
}

/**
 * fo_simple_page_master_get_margin_left:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-left" property of @fo_fo.
 *
 * Return value: The "margin-left" property value.
**/
FoProperty *
fo_simple_page_master_get_margin_left (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->margin_left;
}

/**
 * fo_simple_page_master_set_margin_left:
 * @fo_fo: The #FoFo object.
 * @new_margin_left: The new "margin-left" property value.
 * 
 * Sets the "margin-left" property of @fo_fo to @new_margin_left.
 **/
void
fo_simple_page_master_set_margin_left (FoFo *fo_fo,
		         FoProperty *new_margin_left)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_margin_left == NULL) ||
		    FO_IS_PROPERTY_MARGIN_LEFT (new_margin_left));

  if (new_margin_left != NULL)
    {
      g_object_ref (new_margin_left);
    }
  if (fo_simple_page_master->margin_left != NULL)
    {
      g_object_unref (fo_simple_page_master->margin_left);
    }
  fo_simple_page_master->margin_left = new_margin_left;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "margin-left");*/
}

/**
 * fo_simple_page_master_get_margin_right:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-right" property of @fo_fo.
 *
 * Return value: The "margin-right" property value.
**/
FoProperty *
fo_simple_page_master_get_margin_right (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->margin_right;
}

/**
 * fo_simple_page_master_set_margin_right:
 * @fo_fo: The #FoFo object.
 * @new_margin_right: The new "margin-right" property value.
 * 
 * Sets the "margin-right" property of @fo_fo to @new_margin_right.
 **/
void
fo_simple_page_master_set_margin_right (FoFo *fo_fo,
		         FoProperty *new_margin_right)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_margin_right == NULL) ||
		    FO_IS_PROPERTY_MARGIN_RIGHT (new_margin_right));

  if (new_margin_right != NULL)
    {
      g_object_ref (new_margin_right);
    }
  if (fo_simple_page_master->margin_right != NULL)
    {
      g_object_unref (fo_simple_page_master->margin_right);
    }
  fo_simple_page_master->margin_right = new_margin_right;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "margin-right");*/
}

/**
 * fo_simple_page_master_get_margin_top:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "margin-top" property of @fo_fo.
 *
 * Return value: The "margin-top" property value.
**/
FoProperty *
fo_simple_page_master_get_margin_top (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->margin_top;
}

/**
 * fo_simple_page_master_set_margin_top:
 * @fo_fo: The #FoFo object.
 * @new_margin_top: The new "margin-top" property value.
 * 
 * Sets the "margin-top" property of @fo_fo to @new_margin_top.
 **/
void
fo_simple_page_master_set_margin_top (FoFo *fo_fo,
		         FoProperty *new_margin_top)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_margin_top == NULL) ||
		    FO_IS_PROPERTY_MARGIN_TOP (new_margin_top));

  if (new_margin_top != NULL)
    {
      g_object_ref (new_margin_top);
    }
  if (fo_simple_page_master->margin_top != NULL)
    {
      g_object_unref (fo_simple_page_master->margin_top);
    }
  fo_simple_page_master->margin_top = new_margin_top;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "margin-top");*/
}

/**
 * fo_simple_page_master_get_page_height:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "page-height" property of @fo_fo.
 *
 * Return value: The "page-height" property value.
**/
FoProperty *
fo_simple_page_master_get_page_height (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->page_height;
}

/**
 * fo_simple_page_master_set_page_height:
 * @fo_fo: The #FoFo object.
 * @new_page_height: The new "page-height" property value.
 * 
 * Sets the "page-height" property of @fo_fo to @new_page_height.
 **/
void
fo_simple_page_master_set_page_height (FoFo *fo_fo,
		         FoProperty *new_page_height)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_page_height == NULL) ||
		    FO_IS_PROPERTY_PAGE_HEIGHT (new_page_height));

  if (new_page_height != NULL)
    {
      g_object_ref (new_page_height);
    }
  if (fo_simple_page_master->page_height != NULL)
    {
      g_object_unref (fo_simple_page_master->page_height);
    }
  fo_simple_page_master->page_height = new_page_height;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "page-height");*/
}

/**
 * fo_simple_page_master_get_page_width:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "page-width" property of @fo_fo.
 *
 * Return value: The "page-width" property value.
**/
FoProperty *
fo_simple_page_master_get_page_width (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->page_width;
}

/**
 * fo_simple_page_master_set_page_width:
 * @fo_fo: The #FoFo object.
 * @new_page_width: The new "page-width" property value.
 * 
 * Sets the "page-width" property of @fo_fo to @new_page_width.
 **/
void
fo_simple_page_master_set_page_width (FoFo *fo_fo,
		         FoProperty *new_page_width)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_page_width == NULL) ||
		    FO_IS_PROPERTY_PAGE_WIDTH (new_page_width));

  if (new_page_width != NULL)
    {
      g_object_ref (new_page_width);
    }
  if (fo_simple_page_master->page_width != NULL)
    {
      g_object_unref (fo_simple_page_master->page_width);
    }
  fo_simple_page_master->page_width = new_page_width;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "page-width");*/
}

/**
 * fo_simple_page_master_get_reference_orientation:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "reference-orientation" property of @fo_fo.
 *
 * Return value: The "reference-orientation" property value.
**/
FoProperty *
fo_simple_page_master_get_reference_orientation (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->reference_orientation;
}

/**
 * fo_simple_page_master_set_reference_orientation:
 * @fo_fo: The #FoFo object.
 * @new_reference_orientation: The new "reference-orientation" property value.
 * 
 * Sets the "reference-orientation" property of @fo_fo to @new_reference_orientation.
 **/
void
fo_simple_page_master_set_reference_orientation (FoFo *fo_fo,
		         FoProperty *new_reference_orientation)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_reference_orientation == NULL) ||
		    FO_IS_PROPERTY_REFERENCE_ORIENTATION (new_reference_orientation));

  if (new_reference_orientation != NULL)
    {
      g_object_ref (new_reference_orientation);
    }
  if (fo_simple_page_master->reference_orientation != NULL)
    {
      g_object_unref (fo_simple_page_master->reference_orientation);
    }
  fo_simple_page_master->reference_orientation = new_reference_orientation;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "reference-orientation");*/
}

/**
 * fo_simple_page_master_get_space_after:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-after" property of @fo_fo.
 *
 * Return value: The "space-after" property value.
**/
FoProperty *
fo_simple_page_master_get_space_after (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->space_after;
}

/**
 * fo_simple_page_master_set_space_after:
 * @fo_fo: The #FoFo object.
 * @new_space_after: The new "space-after" property value.
 * 
 * Sets the "space-after" property of @fo_fo to @new_space_after.
 **/
void
fo_simple_page_master_set_space_after (FoFo *fo_fo,
		         FoProperty *new_space_after)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_space_after == NULL) ||
		    FO_IS_PROPERTY_SPACE_AFTER (new_space_after));

  if (new_space_after != NULL)
    {
      g_object_ref (new_space_after);
    }
  if (fo_simple_page_master->space_after != NULL)
    {
      g_object_unref (fo_simple_page_master->space_after);
    }
  fo_simple_page_master->space_after = new_space_after;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "space-after");*/
}

/**
 * fo_simple_page_master_get_space_before:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "space-before" property of @fo_fo.
 *
 * Return value: The "space-before" property value.
**/
FoProperty *
fo_simple_page_master_get_space_before (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->space_before;
}

/**
 * fo_simple_page_master_set_space_before:
 * @fo_fo: The #FoFo object.
 * @new_space_before: The new "space-before" property value.
 * 
 * Sets the "space-before" property of @fo_fo to @new_space_before.
 **/
void
fo_simple_page_master_set_space_before (FoFo *fo_fo,
		         FoProperty *new_space_before)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_space_before == NULL) ||
		    FO_IS_PROPERTY_SPACE_BEFORE (new_space_before));

  if (new_space_before != NULL)
    {
      g_object_ref (new_space_before);
    }
  if (fo_simple_page_master->space_before != NULL)
    {
      g_object_unref (fo_simple_page_master->space_before);
    }
  fo_simple_page_master->space_before = new_space_before;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "space-before");*/
}

/**
 * fo_simple_page_master_get_start_indent:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "start-indent" property of @fo_fo.
 *
 * Return value: The "start-indent" property value.
**/
FoProperty *
fo_simple_page_master_get_start_indent (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->start_indent;
}

/**
 * fo_simple_page_master_set_start_indent:
 * @fo_fo: The #FoFo object.
 * @new_start_indent: The new "start-indent" property value.
 * 
 * Sets the "start-indent" property of @fo_fo to @new_start_indent.
 **/
void
fo_simple_page_master_set_start_indent (FoFo *fo_fo,
		         FoProperty *new_start_indent)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_start_indent == NULL) ||
		    FO_IS_PROPERTY_START_INDENT (new_start_indent));

  if (new_start_indent != NULL)
    {
      g_object_ref (new_start_indent);
    }
  if (fo_simple_page_master->start_indent != NULL)
    {
      g_object_unref (fo_simple_page_master->start_indent);
    }
  fo_simple_page_master->start_indent = new_start_indent;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "start-indent");*/
}

/**
 * fo_simple_page_master_get_writing_mode:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "writing-mode" property of @fo_fo.
 *
 * Return value: The "writing-mode" property value.
**/
FoProperty *
fo_simple_page_master_get_writing_mode (FoFo *fo_fo)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_val_if_fail (fo_simple_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master), NULL);

  return fo_simple_page_master->writing_mode;
}

/**
 * fo_simple_page_master_set_writing_mode:
 * @fo_fo: The #FoFo object.
 * @new_writing_mode: The new "writing-mode" property value.
 * 
 * Sets the "writing-mode" property of @fo_fo to @new_writing_mode.
 **/
void
fo_simple_page_master_set_writing_mode (FoFo *fo_fo,
		         FoProperty *new_writing_mode)
{
  FoSimplePageMaster *fo_simple_page_master = (FoSimplePageMaster *) fo_fo;

  g_return_if_fail (fo_simple_page_master != NULL);
  g_return_if_fail (FO_IS_SIMPLE_PAGE_MASTER (fo_simple_page_master));
  g_return_if_fail ((new_writing_mode == NULL) ||
		    FO_IS_PROPERTY_WRITING_MODE (new_writing_mode));

  if (new_writing_mode != NULL)
    {
      g_object_ref (new_writing_mode);
    }
  if (fo_simple_page_master->writing_mode != NULL)
    {
      g_object_unref (fo_simple_page_master->writing_mode);
    }
  fo_simple_page_master->writing_mode = new_writing_mode;
  /*g_object_notify (G_OBJECT (fo_simple_page_master), "writing-mode");*/
}
