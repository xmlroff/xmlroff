/* Fo
 * fo-color-profile.c: 'color-profile' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */ 

#include "fo/fo-color-profile-private.h"
#include "property/fo-property-src.h"

enum {
  PROP_0,
  PROP_SRC
};

static void fo_color_profile_class_init  (FoColorProfileClass *klass);
static void fo_color_profile_get_property (GObject      *object,
                                           guint         prop_id,
                                           GValue       *value,
                                           GParamSpec   *pspec);
static void fo_color_profile_set_property (GObject      *object,
                                           guint         prop_id,
                                           const GValue *value,
                                           GParamSpec   *pspec);
static void fo_color_profile_finalize    (GObject           *object);
static gboolean fo_color_profile_validate_content (FoFo    *fo,
                                                   GError **error);
static void fo_color_profile_validate (FoFo      *fo,
                                       FoContext *current_context,
                                       FoContext *parent_context,
                                       GError   **error);
static void fo_color_profile_update_from_context (FoFo      *fo,
                                                  FoContext *context);
static void fo_color_profile_debug_dump_properties (FoFo *fo,
                                                    gint  depth);

static gpointer parent_class;

/**
 * fo_color_profile_get_type:
 * 
 * Register the #FoColorProfile object type.
 * 
 * Return value: #GType value of the #FoColorProfile object type.
 **/
GType
fo_color_profile_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoColorProfileClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_color_profile_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoColorProfile),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoColorProfile",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_color_profile_class_init:
 * @klass: #FoColorProfileClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoColorProfileClass.
 **/
void
fo_color_profile_class_init (FoColorProfileClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fofo_class = FO_FO_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_color_profile_finalize;

  object_class->get_property = fo_color_profile_get_property;
  object_class->set_property = fo_color_profile_set_property;

  fofo_class->validate_content = fo_color_profile_validate_content;
  fofo_class->validate2 = fo_color_profile_validate;
  fofo_class->update_from_context = fo_color_profile_update_from_context;
  fofo_class->debug_dump_properties = fo_color_profile_debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_SRC,
     g_param_spec_object ("src",
			  _("Src"),
			  _("Src property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_color_profile_finalize:
 * @object: #FoColorProfile object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoColorProfile.
 **/
void
fo_color_profile_finalize (GObject *object)
{
  FoColorProfile *fo_color_profile;

  fo_color_profile = FO_COLOR_PROFILE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_color_profile_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoColorProfile.
 **/
void
fo_color_profile_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_SRC:
      g_value_set_object (value, G_OBJECT (fo_color_profile_get_src (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_color_profile_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoColorProfile.
 **/
void
fo_color_profile_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_SRC:
      fo_color_profile_set_src (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_color_profile_new:
 * 
 * Creates a new #FoColorProfile initialized to default value.
 * 
 * Return value: the new #FoColorProfile.
 **/
FoFo*
fo_color_profile_new (void)
{
  return FO_FO (g_object_new (fo_color_profile_get_type (),
                              NULL));
}

/**
 * fo_color_profile_validate_content:
 * @fo:    #FoColorProfile object to validate.
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
fo_color_profile_validate_content (FoFo    *fo,
                                   GError **error)
{
  /*GError *tmp_error = NULL;*/

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_COLOR_PROFILE (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  return FALSE;

/*
error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (fo));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
*/
}

/**
 * fo_color_profile_validate:
 * @fo:              #FoColorProfile object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_color_profile_validate (FoFo      *fo,
                           FoContext *current_context,
                           FoContext *parent_context,
                           GError   **error)
{
  FoColorProfile *fo_color_profile;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_COLOR_PROFILE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_color_profile = FO_COLOR_PROFILE (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_color_profile_update_from_context:
 * @fo:      The #FoFo object.
 * @context: The #FoContext object from which to update the properties of @fo.
 * 
 * Sets the properties of @fo to the corresponding property values in @context.
 **/
void
fo_color_profile_update_from_context (FoFo      *fo,
                                      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_COLOR_PROFILE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_color_profile_set_src (fo,
			  fo_context_get_src (context));
}

/**
 * fo_color_profile_debug_dump_properties:
 * @fo:    The #FoFo object.
 * @depth: Indent level to add to the output.
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class.
 **/
void
fo_color_profile_debug_dump_properties (FoFo *fo,
                                        gint  depth)
{
  FoColorProfile *fo_color_profile;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_COLOR_PROFILE (fo));

  fo_color_profile = FO_COLOR_PROFILE (fo);

  fo_object_debug_dump (fo_color_profile->src, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_color_profile_get_src:
 * @fo_fo: The @FoFo object.
 * 
 * Gets the "src" property of @fo_fo.
 *
 * Return value: The "src" property value.
**/
FoProperty*
fo_color_profile_get_src (FoFo *fo_fo)
{
  FoColorProfile *fo_color_profile = (FoColorProfile *) fo_fo;

  g_return_val_if_fail (fo_color_profile != NULL, NULL);
  g_return_val_if_fail (FO_IS_COLOR_PROFILE (fo_color_profile), NULL);

  return fo_color_profile->src;
}

/**
 * fo_color_profile_set_src:
 * @fo_fo: The #FoFo object
 * @new_src: The new "src" property value
 * 
 * Sets the "src" property of @fo_fo to @new_src
 **/
void
fo_color_profile_set_src (FoFo *fo_fo,
		         FoProperty *new_src)
{
  FoColorProfile *fo_color_profile = (FoColorProfile *) fo_fo;

  g_return_if_fail (fo_color_profile != NULL);
  g_return_if_fail (FO_IS_COLOR_PROFILE (fo_color_profile));
  g_return_if_fail (FO_IS_PROPERTY_SRC (new_src));

  if (new_src != NULL)
    {
      g_object_ref (new_src);
    }
  if (fo_color_profile->src != NULL)
    {
      g_object_unref (fo_color_profile->src);
    }
  fo_color_profile->src = new_src;
  /*g_object_notify (G_OBJECT (fo_color_profile), "src");*/
}
