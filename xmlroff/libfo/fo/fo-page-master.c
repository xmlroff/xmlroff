/* Fo
 * fo-page-master.c: Abstract 'page-master' formatting object
 *
 * Copyright (C) 2009 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo/fo-page-master-private.h"
#include "fo/fo-tree.h"
#include "fo/fo-single-page-master-reference.h"
#include "fo/fo-repeatable-page-master-reference.h"
#include "fo/fo-repeatable-page-master-alternatives.h"
#include "property/fo-property-master-name.h"

/**
 * SECTION:fo-page-master
 * @short_description: Abstract 'page-master' formatting object
 *
 * Abstract parent for #FoSimplePageMaster and #FoPageSequenceMaster.
 */

const char *fo_page_master_error_messages[] = {
  N_("Failed"),
  N_("Warning"),
  N_("No 'FoPageSequenceWalker' class for object: %s")
};

enum {
  PROP_0,
  PROP_MASTER_NAME
};

static void _base_class_init  (FoPageMasterClass *klass);
static void _class_init       (FoPageMasterClass *klass);
static void _get_property          (GObject      *object,
				    guint         prop_id,
				    GValue       *value,
				    GParamSpec   *pspec);
static void _set_property          (GObject      *object,
				    guint         prop_id,
				    const GValue *value,
				    GParamSpec   *pspec);
static void _dispose               (GObject      *object);
static void _validate              (FoFo         *fo,
				    FoContext    *current_context,
				    FoContext    *parent_context,
				    GError      **error);
static void _update_from_context   (FoFo         *fo,
				    FoContext    *context);
static void _debug_dump_properties (FoFo         *fo,
				    gint          depth);

static FoPageSequenceWalker * _new_walker_default (FoFo    *fo_fo,
						   GError **error);

static gpointer parent_class;

/**
 * fo_page_master_get_type:
 * 
 * Register the #FoPageMaster object type.
 * 
 * Return value: #GType value of the #FoPageMaster object type.
 **/
GType
fo_page_master_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
	{
	  sizeof (FoPageMasterClass),
	  (GBaseInitFunc) _base_class_init,
	  NULL,           /* base_finalize */
	  (GClassInitFunc) _class_init,
	  NULL,           /* class_finalize */
	  NULL,           /* class_data */
	  sizeof (FoPageMaster),
	  0,              /* n_preallocs */
	  NULL,		  /* instance_init */
	  NULL		  /* value_table */
	};

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoPageMaster",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * _base_class_init:
 * @klass: #FoPageMasterClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPageMasterClass.
 **/
static void
_base_class_init (FoPageMasterClass *klass)
{
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  fo_fo_class->debug_dump_properties = _debug_dump_properties;
  fo_fo_class->update_from_context = _update_from_context;
  fo_fo_class->validate2 = _validate;

  klass->new_walker = _new_walker_default;
}

/**
 * _class_init:
 * @klass: #FoPageMasterClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoPageMasterClass.
 **/
static void
_class_init (FoPageMasterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->dispose = _dispose;

  object_class->get_property = _get_property;
  object_class->set_property = _set_property;

  fo_fo_class->update_from_context = _update_from_context;
  FO_FO_CLASS (klass)->area_new2 = NULL;

  g_object_class_install_property
    (object_class,
     PROP_MASTER_NAME,
     g_param_spec_object ("master-name",
			  _("Master Name"),
			  _("Master Name property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * _dispose:
 * @object: #FoPageMaster object to dispose.
 * 
 * Implements #GObjectDisposeFunc for #FoPageMaster.
 **/
static void
_dispose (GObject *object)
{
  FoFo *fo = FO_FO (object);

  /* Release references to all property objects. */
  fo_page_master_set_master_name (fo, NULL);

  G_OBJECT_CLASS (parent_class)->dispose (object);
}

/**
 * _get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoPageMaster.
 **/
void
_get_property (GObject    *object,
	       guint       prop_id,
	       GValue     *value,
	       GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MASTER_NAME:
      g_value_set_object (value, G_OBJECT (fo_page_master_get_master_name (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * _set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoPageMaster.
 **/
void
_set_property (GObject      *object,
	       guint         prop_id,
	       const GValue *value,
	       GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_MASTER_NAME:
      fo_page_master_set_master_name (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_page_master_new:
 * 
 * Creates a new #FoPageMaster initialized to default value.
 * 
 * Return value: the new #FoPageMaster.
 **/
FoFo*
fo_page_master_new (void)
{
  return FO_FO (g_object_new (fo_page_master_get_type (),
                              NULL));
}

/**
 * _validate:
 * @fo:              #FoPageMaster object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
static void
_validate (FoFo      *fo,
	   FoContext *current_context,
	   FoContext *parent_context,
	   GError   **error)
{
  FoPageMaster *fo_page_master;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_MASTER (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_page_master = FO_PAGE_MASTER (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);

  FoFo *tree = fo->tree;

  if (tree != NULL)
    {
      gchar *master_name =
	fo_name_get_value
	(fo_property_get_value
	 (fo_page_master_get_master_name (fo)));

      fo_tree_page_sequence_master_name_add (tree,
					     master_name,
					     fo);
      g_free (master_name);
    }
  else
    {
      g_assert_not_reached();
    }
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
  g_return_if_fail (FO_IS_PAGE_MASTER (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_page_master_set_master_name (fo,
			  fo_context_get_master_name (context));
}

/**
 * _debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
static void
_debug_dump_properties (FoFo *fo,
			gint  depth)
{
  FoPageMaster *fo_page_master;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_PAGE_MASTER (fo));

  fo_page_master = FO_PAGE_MASTER (fo);

  fo_object_debug_dump (fo_page_master->master_name, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * _new_walker_default:
 * @fo_fo: The #FoPageMaster object.
 * 
 * Gets a new #FoPageSequenceWalker for @fo.
 **/
static FoPageSequenceWalker *
_new_walker_default (FoFo  *fo_fo,
		     GError **error)
{
  g_return_val_if_fail (FO_IS_PAGE_MASTER (fo_fo), NULL);

  GError *no_page_sequence_walker_error =
    g_error_new (FO_PAGE_MASTER_ERROR,
		 FO_PAGE_MASTER_ERROR_NO_WALKER,
		 _(fo_page_master_error_messages[FO_PAGE_MASTER_ERROR_NO_WALKER]),
		 fo_object_sprintf (FO_OBJECT (fo_fo)));
  fo_object_log_warning (FO_OBJECT (fo_fo),
			 &no_page_sequence_walker_error);
  return NULL;
}

/**
 * fo_page_master_new_walker:
 * @fo_fo: The #FoPageMaster object.
 * 
 * Gets a new #FoPageSequenceWalker for @fo.
 **/
FoPageSequenceWalker *
fo_page_master_new_walker (FoFo    *fo_fo,
			   GError **error)
{
  g_return_val_if_fail (FO_IS_PAGE_MASTER (fo_fo), NULL);
  g_return_val_if_fail (error == NULL || *error == NULL, NULL);

  return FO_PAGE_MASTER_GET_CLASS (fo_fo)->new_walker (fo_fo,
						       error);
}

/**
 * fo_page_master_error_quark:
 * 
 * Gets the #GQuark identifying #FoPageMaster errors.
 * 
 * Return value: #GQuark identifying #FoPageMaster errors.
 **/
GQuark
fo_page_master_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("fo-page-master-error");
  return quark;
}

/*
 * The remainder of this file is completely auto-generated.
 */

/**
 * fo_page_master_get_master_name:
 * @fo_fo: The #FoFo object.
 * 
 * Gets the "master-name" property of @fo_fo.
 *
 * Return value: The "master-name" property value.
**/
FoProperty *
fo_page_master_get_master_name (FoFo *fo_fo)
{
  FoPageMaster *fo_page_master = (FoPageMaster *) fo_fo;

  g_return_val_if_fail (fo_page_master != NULL, NULL);
  g_return_val_if_fail (FO_IS_PAGE_MASTER (fo_page_master), NULL);

  return fo_page_master->master_name;
}

/**
 * fo_page_master_set_master_name:
 * @fo_fo: The #FoFo object.
 * @new_master_name: The new "master-name" property value.
 * 
 * Sets the "master-name" property of @fo_fo to @new_master_name.
 **/
void
fo_page_master_set_master_name (FoFo *fo_fo,
		         FoProperty *new_master_name)
{
  FoPageMaster *fo_page_master = (FoPageMaster *) fo_fo;

  g_return_if_fail (fo_page_master != NULL);
  g_return_if_fail (FO_IS_PAGE_MASTER (fo_page_master));
  g_return_if_fail ((new_master_name == NULL) ||
		    FO_IS_PROPERTY_MASTER_NAME (new_master_name));

  if (new_master_name != NULL)
    {
      g_object_ref (new_master_name);
    }
  if (fo_page_master->master_name != NULL)
    {
      g_object_unref (fo_page_master->master_name);
    }
  fo_page_master->master_name = new_master_name;
  /*g_object_notify (G_OBJECT (fo_page_master), "master-name");*/
}

