/* Fo
 * fo-footnote.c: Footnote formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-footnote.c,v 1.3 2004/03/30 22:39:46 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-inline-fo.h"
#include "fo-footnote.h"
#include "fo-footnote-private.h"
#include "fo-property-role.h"
#include "fo-property-source-document.h"

enum {
  PROP_0,
  PROP_ROLE,
  PROP_SOURCE_DOCUMENT
};

static void fo_footnote_init        (FoFootnote      *fo_footnote);
static void fo_footnote_class_init  (FoFootnoteClass *klass);
static void fo_footnote_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_footnote_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_footnote_finalize    (GObject           *object);
static gboolean fo_footnote_validate_content (FoFo    *fo,
                                              GError **error);
static void fo_footnote_validate (FoFo      *fo,
                                  FoContext *current_context,
                                  FoContext *parent_context);
static void fo_footnote_update_from_context (FoFo      *fo,
                                             FoContext *context);
static void fo_footnote_debug_dump_properties (FoFo *fo,
                                               gint  depth);

static gpointer parent_class;

/**
 * fo_footnote_get_type:
 * @void: 
 * 
 * Register the FoFootnote object type.
 * 
 * Return value: GType value of the FoFootnote object type.
 **/
GType
fo_footnote_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoFootnoteClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_footnote_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoFootnote),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_footnote_init,
	NULL		/* value_table */
      };
      
      static const GInterfaceInfo fo_inline_fo_info =
      {
        NULL,
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoFootnote",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &fo_inline_fo_info);
    }
  
  return object_type;
}

/**
 * fo_footnote_init:
 * @fo_footnote: FoFootnote object to initialise
 * 
 * Implements GInstanceInitFunc for FoFootnote
 **/
void
fo_footnote_init (FoFootnote *fo_footnote)
{
}

/**
 * fo_footnote_class_init:
 * @klass: FoFootnoteClass object to initialise
 * 
 * Implements GClassInitFunc for FoFootnoteClass
 **/
void
fo_footnote_class_init (FoFootnoteClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_footnote_finalize;

  object_class->set_property = fo_footnote_set_property;
  object_class->get_property = fo_footnote_get_property;

  FO_FO_CLASS (klass)->validate_content = fo_footnote_validate_content;
  FO_FO_CLASS (klass)->validate = fo_footnote_validate;
  FO_FO_CLASS (klass)->update_from_context = fo_footnote_update_from_context;
  FO_FO_CLASS (klass)->debug_dump_properties = fo_footnote_debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_ROLE,
     g_param_spec_object ("role",
			  _("Role"),
			  _("Role property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SOURCE_DOCUMENT,
     g_param_spec_object ("source-document",
			  _("Source Document"),
			  _("Source Document property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_footnote_finalize:
 * @object: FoFootnote object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoFootnote
 **/
void
fo_footnote_finalize (GObject *object)
{
  FoFootnote *fo_footnote;

  fo_footnote = FO_FOOTNOTE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_footnote_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoFootnote
 **/
void
fo_footnote_set_property (GObject      *object,
                          guint         prop_id,
                          const GValue *value,
                          GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ROLE:
      fo_footnote_set_role (fo_fo, g_value_get_object (value));
      break;
    case PROP_SOURCE_DOCUMENT:
      fo_footnote_set_source_document (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_footnote_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoFootnote
 **/
void
fo_footnote_get_property (GObject    *object,
                          guint       prop_id,
                          GValue     *value,
                          GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_ROLE:
      g_value_set_object (value, G_OBJECT (fo_footnote_get_role (fo_fo)));
      break;
    case PROP_SOURCE_DOCUMENT:
      g_value_set_object (value, G_OBJECT (fo_footnote_get_source_document (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_footnote_new:
 * 
 * Creates a new #FoFootnote initialized to default value.
 * 
 * Return value: the new #FoFootnote
 **/
FoFo*
fo_footnote_new (void)
{
  return FO_FO (g_object_new (fo_footnote_get_type (), NULL));
}

/**
 * fo_footnote_validate_content:
 * @fo:    FoFootnote object to validate
 * @error: GError indicating error condition, if any
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches GNodeTraverseFunc model: FALSE indicates
 * content model is correct, or TRUE indicates an error.  When used
 * with fo_node_traverse(), returning TRUE stops the traversal.
 * 
 * Return value: FALSE if content model okay, TRUE if not
 **/
gboolean
fo_footnote_validate_content (FoFo    *fo,
                              GError **error)
{
  GError *tmp_error;

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_FOOTNOTE (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  return FALSE;

 error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (FO_OBJECT (fo)));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
}

/**
 * fo_footnote_validate:
 * @fo:              FoFootnote object to validate
 * @current_context: FoContext associated with current object
 * @parent_context:  FoContext associated with parent FO
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values
 **/
void
fo_footnote_validate (FoFo      *fo,
                      FoContext *current_context,
                      FoContext *parent_context)
{
  FoFootnote *fo_footnote;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FOOTNOTE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  fo_footnote = FO_FOOTNOTE (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
}

/**
 * fo_footnote_update_from_context:
 * @fo:      The #FoFo object
 * @context: The #FoContext object from which to update the properties of @fo
 * 
 * Sets the properties of @fo to the corresponding property values in @context
 **/
void
fo_footnote_update_from_context (FoFo *fo,
                                 FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FOOTNOTE (fo));
  g_return_if_fail (context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_footnote_set_role (fo,
			  fo_context_get_role (context));
  fo_footnote_set_source_document (fo,
			  fo_context_get_source_document (context));
}

/**
 * fo_footnote_debug_dump_properties:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_footnote_debug_dump_properties (FoFo *fo, gint depth)
{
  FoFootnote *fo_footnote;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FOOTNOTE (fo));

  fo_footnote = FO_FOOTNOTE (fo);

  fo_object_debug_dump (fo_footnote->role, depth);
  fo_object_debug_dump (fo_footnote->source_document, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_footnote_set_role:
 * @fo_fo: The @FoFo object
 * @new_role: The new "role" property value
 * 
 * Sets the #role property of @footnote to @new_role
 **/
void
fo_footnote_set_role (FoFo *fo_fo,
		         FoProperty *new_role)
{
  FoFootnote *fo_footnote = (FoFootnote *) fo_fo;

  g_return_if_fail (fo_footnote != NULL);
  g_return_if_fail (FO_IS_FOOTNOTE (fo_footnote));
  g_return_if_fail (FO_IS_PROPERTY_ROLE (new_role));

  if (new_role)
    g_object_ref (G_OBJECT (new_role));
  if (fo_footnote->role)
    g_object_unref (G_OBJECT (fo_footnote->role));
  fo_footnote->role = new_role;
  /*g_object_notify (G_OBJECT (fo_footnote), "role");*/
}

/**
 * fo_footnote_get_role:
 * @fo_fo: The @FoFo object
 *
 * Gets the #role property of @footnote
 *
 * Return value: The "role" property value
**/
FoProperty*
fo_footnote_get_role (FoFo *fo_fo)
{
  FoFootnote *fo_footnote = (FoFootnote *) fo_fo;

  g_return_val_if_fail (fo_footnote != NULL, NULL);
  g_return_val_if_fail (FO_IS_FOOTNOTE (fo_footnote), NULL);

  return fo_footnote->role;
}

/**
 * fo_footnote_set_source_document:
 * @fo_fo: The @FoFo object
 * @new_source_document: The new "source-document" property value
 * 
 * Sets the #source-document property of @footnote to @new_source_document
 **/
void
fo_footnote_set_source_document (FoFo *fo_fo,
		         FoProperty *new_source_document)
{
  FoFootnote *fo_footnote = (FoFootnote *) fo_fo;

  g_return_if_fail (fo_footnote != NULL);
  g_return_if_fail (FO_IS_FOOTNOTE (fo_footnote));
  g_return_if_fail (FO_IS_PROPERTY_SOURCE_DOCUMENT (new_source_document));

  if (new_source_document)
    g_object_ref (G_OBJECT (new_source_document));
  if (fo_footnote->source_document)
    g_object_unref (G_OBJECT (fo_footnote->source_document));
  fo_footnote->source_document = new_source_document;
  /*g_object_notify (G_OBJECT (fo_footnote), "source-document");*/
}

/**
 * fo_footnote_get_source_document:
 * @fo_fo: The @FoFo object
 *
 * Gets the #source-document property of @footnote
 *
 * Return value: The "source-document" property value
**/
FoProperty*
fo_footnote_get_source_document (FoFo *fo_fo)
{
  FoFootnote *fo_footnote = (FoFootnote *) fo_fo;

  g_return_val_if_fail (fo_footnote != NULL, NULL);
  g_return_val_if_fail (FO_IS_FOOTNOTE (fo_footnote), NULL);

  return fo_footnote->source_document;
}
