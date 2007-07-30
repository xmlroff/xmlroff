/* Fo
 * fo-fo.c: Base formatting object of formatting object system
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "fo-utils.h"
#include "fo-xml-node-private.h"
#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo/fo-flow.h"
#include "fo/fo-tree.h"
#include "fo/fo-text.h"
#include "fo-all-fo.h"
#include "fo/fo-inline-fo.h"
#include "fo/fo-block-fo.h"
#include "fo/fo-neutral-fo.h"
#include "fo/fo-wrapper-whitespace.h"
#include "fo-context-util.h"
#include <libxml/tree.h>
#include <libxml/xmlversion.h>
#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>

struct _FoFoAreaIterator
{
  FoFo  *fo;
  GList *area_list;
};

const char *fo_fo_error_messages[] = {
  N_("Failed"),
  N_("Warning"),
  N_("%s must be empty"),
  N_("%s not allowed to be empty"),
  N_("%s can contain only %%block; and %%neutral; FOs"),
  N_("%s not allowed as child of %s"),
  N_("%s children do not match allowed content"),
  N_("Unrecognized %s enumeration token: %s"),
  N_("Invalid value datatype for '%s' property: %s (%s)"),
  N_("Invalid value datatype for '%s' property: %s (%s).  Using %s (%s)"),
  N_("Invalid value for '%s' property: NULL"),
  N_("Unsupported property: %s")
};

enum {
  PROP_0,
  PROP_TREE,
  PROP_FLOW,
  PROP_CONTEXT,
  PROP_GENERATE_REFERENCE_AREA,
  PROP_ALLOW_MIXED_CONTENT,
  PROP_ELEMENT
};

static void fo_fo_base_class_init  (FoFoClass *klass);
static void fo_fo_class_init  (FoFoClass *klass);
static void fo_fo_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_fo_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_fo_finalize    (GObject           *object);

static void fo_fo_debug_dump (FoObject *object, gint depth);
static void fo_fo_debug_dump_properties_default (FoFo *area,
						   gint depth);
static gchar* fo_fo_sprintf (FoObject *object);
static void   fo_fo_update_from_context_default (FoFo *fo,
						 FoContext *context);
static gboolean fo_fo_resolve_property_attributes_default (FoNode  *fo_node,
							   gpointer data);
static gboolean fo_fo_validate_content_default            (FoFo *fo,
							   GError **error);
static void   fo_fo_validate_default (FoFo *fo,
				      FoContext *current_context,
				      FoContext *parent_context);
static void   fo_fo_validate2_default (FoFo *fo,
				       FoContext *current_context,
				       FoContext *parent_context,
				       GError   **error);
static FoFo * fo_fo_clone_default    (FoFo         *original);
static void   fo_fo_update_after_clone_default (FoFo *clone,
						FoFo *original);
static void   fo_fo_area_new_default (FoFo    *fo,
				      FoDoc   *fo_doc,
				      FoArea  *parent_area,
				      FoArea **new_area,
				      guint    debug_level);
static void fo_fo_area_new2_default (FoFo *fo,
				     FoFoAreaNew2Context *context,
				     GError **error);
static FoNode* fo_fo_prepend (FoNode *parent,
			      FoNode *fo);
static FoNode* fo_fo_append (FoNode *parent,
			     FoNode *fo);

static gpointer parent_class;

/**
 * fo_fo_get_type:
 * 
 * Register the #FoFo object type.
 * 
 * Return value: #GType value of the #FoFo object type.
 **/
GType
fo_fo_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoFoClass),
        (GBaseInitFunc) fo_fo_base_class_init,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_fo_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoFo),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL
      };
      
      object_type = g_type_register_static (FO_TYPE_NODE,
                                            "FoFo",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }
  
  return object_type;
}

/**
 * fo_fo_base_class_init:
 * @klass: #FoFoClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoFoClass.
 **/
void
fo_fo_base_class_init (FoFoClass *klass)
{
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  FoNodeClass *fo_node_class = FO_NODE_CLASS (klass);

  fo_object_class->print_sprintf = fo_fo_sprintf;
  fo_object_class->debug_dump = fo_fo_debug_dump;

  fo_node_class->prepend = fo_fo_prepend;
  fo_node_class->append = fo_fo_append;

  klass->debug_dump_properties = fo_fo_debug_dump_properties_default;
  klass->clone = fo_fo_clone_default;
  klass->update_after_clone = fo_fo_update_after_clone_default;
  klass->update_from_context = fo_fo_update_from_context_default;
  klass->validate_content = fo_fo_validate_content_default;
  klass->validate = fo_fo_validate_default;
  klass->validate2 = fo_fo_validate2_default;
  klass->children_properties_resolve =
    fo_fo_children_properties_resolve_default;
  klass->resolve_property_attributes =
    fo_fo_resolve_property_attributes_default;
  klass->area_new = fo_fo_area_new_default;
  klass->area_new2 = fo_fo_area_new2_default;
  klass->generate_reference_area = FALSE;
  klass->allow_mixed_content = FALSE;
}

/**
 * fo_fo_class_init:
 * @klass: #FoFoClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoFoClass.
 **/
void
fo_fo_class_init (FoFoClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_fo_finalize;

  object_class->set_property = fo_fo_set_property;
  object_class->get_property = fo_fo_get_property;

  klass->debug_dump_properties = fo_fo_debug_dump_properties;

  g_object_class_install_property
    (object_class,
     PROP_TREE,
     g_param_spec_object ("tree",
			  _("tree node"),
			  _("Top of the formatting object tree"),
			  FO_TYPE_FO,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FLOW,
     g_param_spec_object ("flow",
			  _("fo:flow node"),
			  _("Ancestor fo:flow node in the formatting object tree"),
			  FO_TYPE_FO,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_CONTEXT,
     g_param_spec_object ("context",
			  _("Context"),
			  _("Set of current formatting object properties"),
			  FO_TYPE_CONTEXT,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_GENERATE_REFERENCE_AREA,
     g_param_spec_boolean ("generate-reference-area",
			   _("Generates a reference area"),
			   _("Whether or not the formatting object generates a reference area"),
			   FALSE,
			   G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ALLOW_MIXED_CONTENT,
     g_param_spec_boolean ("allow-mixed-content",
			   _("Allows mixed content"),
			   _("Whether or not the formatting object allows mixed content"),
			   FALSE,
			   G_PARAM_READABLE));
}

/**
 * fo_fo_finalize:
 * @object: #FoFo object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoFo.
 **/
void
fo_fo_finalize (GObject *object)
{
  FoFo *fo;

  fo = FO_FO (object);

  if (fo->element != NULL)
    {
      fo_xml_node_unref (fo->element);
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_fo_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoFo.
 **/
void
fo_fo_set_property (GObject      *object,
		    guint         param_id,
		    const GValue *value G_GNUC_UNUSED,
		    GParamSpec   *pspec)
{
  G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
}

/**
 * fo_fo_get_property:
 * @object:  #GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   #GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for #FoFo
 **/
void
fo_fo_get_property (GObject        *object,
		    guint           param_id,
		    GValue         *value,
		    GParamSpec     *pspec)
{
  FoFo *fo = FO_FO (object);
  
  switch (param_id)
    {
    case PROP_TREE:
      g_value_set_object (value, G_OBJECT (fo_fo_get_tree (fo)));
      break;
    case PROP_FLOW:
      g_value_set_object (value, G_OBJECT (fo_fo_get_flow (fo)));
      break;
    case PROP_CONTEXT:
      g_value_set_object (value, G_OBJECT (fo_fo_get_context (fo)));
      break;
    case PROP_GENERATE_REFERENCE_AREA:
      g_value_set_boolean (value, fo_fo_get_generate_reference_area (fo));
      break;
    case PROP_ALLOW_MIXED_CONTENT:
      g_value_set_boolean (value, fo_fo_get_allow_mixed_content (fo));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_fo_new:
 * 
 * Creates a new #FoFo initialized to default value.
 * 
 * Return value: the new #FoFo
 **/
FoFo *
fo_fo_new (void)
{
  FoFo *object;

  object = FO_FO (g_object_new (fo_fo_get_type (), NULL));
  
  return object;
}

/**
 * fo_fo_set_context:
 * @fo_fo: The #FoFo object
 * @new_context: The new context
 * 
 * Sets the #context of @fo_fo to @new_context
 **/
void
fo_fo_set_context (FoFo *fo_fo,
		   FoContext* new_context)
{
  g_return_if_fail (fo_fo != NULL);
  g_return_if_fail (FO_IS_FO (fo_fo));
  g_return_if_fail (new_context != NULL);
  g_return_if_fail (FO_IS_CONTEXT (new_context));

  if (new_context)
    g_object_ref (G_OBJECT (new_context));
  if (fo_fo->context)
    g_object_unref (G_OBJECT (fo_fo->context));
  fo_fo->context = new_context;
  /*g_object_notify (G_OBJECT (fo_fo), "context");*/
}

/**
 * fo_fo_get_context:
 * @fo_fo: The #FoFo object
 *
 * Gets the "context" of @fo_fo
 *
 * Return value: The context
**/
FoContext*
fo_fo_get_context (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_FO (fo_fo), NULL);

  return fo_fo->context;
}

/**
 * fo_fo_get_flow:
 * @fo_fo: The @FoFo object
 *
 * Gets the #flow of @fo_fo
 *
 * Return value: The flow
**/
FoFo*
fo_fo_get_flow (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_FO (fo_fo), NULL);

  return fo_fo->flow;
}

/**
 * fo_fo_get_tree:
 * @fo_fo: The @FoFo object
 *
 * Gets the tree of @fo_fo
 *
 * Return value: The tree
**/
FoFo*
fo_fo_get_tree (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_FO (fo_fo), NULL);

  return fo_fo->tree;
}

/**
 * fo_fo_get_element:
 * @fo_fo: The @FoFo object
 *
 * Gets the #element of @fo_fo
 *
 * Return value: The element
**/
FoXmlNode *
fo_fo_get_element (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_FO (fo_fo), NULL);

  return fo_fo->element;
}

/**
 * fo_fo_set_element:
 * @fo_fo:       The @FoFo object.
 * @new_element: The new #element value.
 * 
 * Sets the #element of @fo_fo.
**/
void
fo_fo_set_element (FoFo      *fo_fo,
		   FoXmlNode *new_element)
{
  g_return_if_fail (fo_fo != NULL);
  g_return_if_fail (FO_IS_FO (fo_fo));

  if (fo_fo->element != NULL)
    {
      g_object_unref (new_element);
    }

  fo_fo->element = fo_xml_node_ref (new_element);
}

/**
 * fo_fo_get_generate_reference_area:
 * @fo_fo: The @FoFo object
 *
 * Gets whether or not the FO generates reference areas.
 *
 * Return value: The generate-reference-area class property value
**/
gboolean
fo_fo_get_generate_reference_area (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, FALSE);
  g_return_val_if_fail (FO_IS_FO (fo_fo), FALSE);

  return FO_FO_GET_CLASS (fo_fo)->generate_reference_area;
}

/**
 * fo_fo_get_allow_mixed_content;
 * @fo_fo: The @FoFo object
 *
 * Gets whether or not the FO allows mixed content (i.e. text nodes).
 *
 * Return value: The allow_mixed_content class property value.
**/
gboolean
fo_fo_get_allow_mixed_content (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, FALSE);
  g_return_val_if_fail (FO_IS_FO (fo_fo), FALSE);

  return FO_FO_GET_CLASS (fo_fo)->allow_mixed_content;
}

/**
 * fo_fo_debug_dump:
 * @object: #FoObject to be dumped.
 * @depth:  Indent level to add to the output.
 * 
 * Implements #fo_object_debug_dump for #FoFo class.
 **/
void
fo_fo_debug_dump (FoObject *object,
		  gint      depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar* object_sprintf;
  FoNode *child;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_FO (object));

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (indent);
  g_free (object_sprintf);

  FO_FO_GET_CLASS (object)->debug_dump_properties (FO_FO (object),
						   depth + 2);

  child = fo_node_first_child (FO_NODE (object));

  while (child)
    {
      fo_object_debug_dump (child,
			    depth + 1);

      child = fo_node_next_sibling (child);
    }
}

/**
 * fo_fo_debug_dump_properties_default:
 * @fo: 
 * @depth: Indent level to add to the output.
 * 
 * 
 **/
void
fo_fo_debug_dump_properties_default (FoFo *fo,
				     gint  depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (FO_IS_FO (fo));

  fo_fo_debug_dump_properties (fo, depth + 1);

  g_free (indent);
}

/**
 * fo_fo_debug_dump_area:
 * @value: 
 * @data: 
 * 
 * 
 **/
static void
fo_fo_debug_dump_area (gpointer value,
		       gpointer data)
{
  gchar *indent = g_strnfill (GPOINTER_TO_INT (data) * 2, ' ');

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%p",
	 indent, value);

  g_free (indent);
}

/**
 * fo_fo_debug_dump_properties:
 * @fo:    #FoFo whose properties to dump
 * @depth: Indication of relative depth to be applied to the output.
 * 
 * Log debug messages for most of the instance variables and some of
 * the class variables of @fo.
 **/
void
fo_fo_debug_dump_properties (FoFo *fo,
			     gint  depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_FO (fo));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sgenerate-reference-area: %s",
	 indent,
	 FO_FO_GET_CLASS (fo)->generate_reference_area ? "TRUE" : "FALSE");

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sallow-mixed-content: %s",
	 indent,
	 FO_FO_GET_CLASS (fo)->allow_mixed_content ? "TRUE" : "FALSE");

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%selement: %p",
	 indent,
	 fo->element);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%scontext: %p",
	 indent,
	 fo->context);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sareas:",
	 indent);

  if (fo->areas)
    {
      g_list_foreach (fo->areas,
		      fo_fo_debug_dump_area,
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
}

gchar*
fo_fo_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_FO (object), NULL);

  return (g_strdup_printf("%s",
			  g_type_name (G_TYPE_FROM_INSTANCE (object))));
}

/**
 * fo_fo_update_from_context_default:
 * @fo:      FoFo to be updated
 * @context: FoContext from which to update the FoFo
 * 
 * Default _update_from_context() function.  Set as the default for
 * the update_from_context class variable, but should be overridden by
 * every subclass of #FoFo.
 *
 * Logs a debug message that the class does not have an
 * 'update_from_context' function.
 **/
void
fo_fo_update_from_context_default (FoFo      *fo,
				   FoContext *context G_GNUC_UNUSED)
{
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have an 'update_from_context' function."),
	 fo_object_sprintf (FO_OBJECT (fo)));
}

/**
 * fo_fo_update_from_context:
 * @fo_fo:   #FoFo to be updated
 * @context: #FoContext from which to update the #FoFo
 * 
 * Calls the FoFo-specific _update_from_context() function to update
 * the FoFo's property values from the larger set of property values
 * maintained in the #FoContext.
 **/
void
fo_fo_update_from_context (FoFo      *fo_fo,
			   FoContext *context)
{
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "fo_fo_update_from_context:: %s",
	 fo_object_sprintf (FO_OBJECT (fo_fo)));
#endif  
  return FO_FO_GET_CLASS (fo_fo)->update_from_context (fo_fo, context);
}

/**
 * fo_fo_validate_content_default:
 * @fo:    FoFo whose content is to be validated
 * @error: GError
 * 
 * Default _validate_content() function that is used when the FO does
 * not have a specific _validate_content() function.
 *
 * Returns FALSE, which is the success value for a GNodeTraverseFunc
 * function.
 * 
 * Return value: FALSE
 **/
gboolean
fo_fo_validate_content_default (FoFo    *fo G_GNUC_UNUSED,
				GError **error G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'validate_content' function."),
	 fo_object_sprintf (FO_OBJECT (fo)));
#endif
  return FALSE;
}

/**
 * fo_fo_validate_content:
 * @fo:    FoFo whose content is to be validated
 * @error: GError
 * 
 * Calls the FoFo-specific _validate_content() function to validate
 * the FoFo's content model and returns the value returned by that
 * function.
 *
 *  Return value: FALSE if no content model error, otherwise TRUE
 **/
gboolean
fo_fo_validate_content (FoFo *fo,
			GError **error)
{
  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_FO (fo), TRUE);

#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "fo_fo_validate_content:: %s",
	 fo_object_sprintf (FO_OBJECT (fo)));
#endif

  return FO_FO_GET_CLASS (fo)->validate_content (fo, error);
}

/**
 * fo_fo_validate:
 * @fo:              #FoFo to validate.
 * @current_context: #FoContext of @fo.
 * @parent_context:  #FoContext of parent of @fo.
 * @error:           #GError indicating any error that occurs
 * 
 * Validate and/or munge the properties of @fo.
 **/
void
fo_fo_validate (FoFo *fo,
		FoContext *current_context,
		FoContext *parent_context,
		GError   **error)
{
  if (FO_FO_GET_CLASS (fo)->validate2 != NULL)
    FO_FO_GET_CLASS (fo)->validate2 (fo,
				     current_context,
				     parent_context,
				     error);
}

void
fo_fo_validate_default (FoFo *fo,
			FoContext *current_context,
			FoContext *parent_context)
{
  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'validate' function."),
	 fo_object_sprintf (FO_OBJECT (fo)));
#endif
  /*
  if (FO_FO_GET_CLASS (fo)->validate != NULL)
    FO_FO_GET_CLASS (fo)->validate (fo, current_context, parent_context);
  */
}

void
fo_fo_validate2_default (FoFo *fo,
			 FoContext *current_context,
			 FoContext *parent_context,
			 GError   **error G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'validate2' function."),
	 fo_object_sprintf (FO_OBJECT (fo)));
#endif
  if (FO_FO_GET_CLASS (fo)->validate != NULL)
    FO_FO_GET_CLASS (fo)->validate (fo, current_context, parent_context);
}

/**
 * fo_fo_clone:
 * @original: Fo object to be cloned
 * 
 * Make a clone of @original and insert the clone after @original in
 * the fo tree.  Set instance properties of the clone to match
 * @original.
 * 
 * Return value: Clone of @original
 **/
FoFo*
fo_fo_clone (FoFo *original)
{
  if (original != NULL)
    {
      return FO_FO_GET_CLASS (original)->clone (original);
    }
  else
    {
      return NULL;
    }
}

/**
 * fo_fo_clone_default:
 * @original: Fo object to be cloned
 * 
 * Make a clone of @original and insert the clone after @original in
 * the fo tree.  Set instance properties of the clone to match
 * @original.
 * 
 * Return value: Clone of @original
 **/
FoFo*
fo_fo_clone_default (FoFo *original)
{
  FoFo *clone;

  g_return_val_if_fail (original != NULL, NULL);
  g_return_val_if_fail (FO_IS_FO (original), NULL);

  clone = FO_FO (g_object_new (G_TYPE_FROM_INSTANCE (original), NULL));

  fo_fo_update_after_clone (clone, original);

  return clone;
}

/**
 * fo_fo_update_after_clone:
 * @clone:    New #FoFo object cloned from @original.
 * @original: Original #FoFo object.
 * 
 * Update the instance variables of @clone to match those of @original.
 **/
void
fo_fo_update_after_clone (FoFo *clone,
			  FoFo *original)
{
  if (original == NULL || clone == NULL)
    {
      return;
    }
  else
    {
      FO_FO_GET_CLASS (clone)->update_after_clone (clone, original);
    }
}

/**
 * fo_fo_update_after_clone_default:
 * @clone:    New #FoFo object cloned from @original.
 * @original: Original #FoFo object.
 * 
 * Update the FoFo-specific instance variables of @clone to match
 * those of @original.
 **/
void
fo_fo_update_after_clone_default (FoFo *clone,
				  FoFo *original)
{
  g_return_if_fail (clone != NULL);
  g_return_if_fail (FO_IS_FO (clone));
  g_return_if_fail (original != NULL);
  g_return_if_fail (FO_IS_FO (original));

  clone->element = original->element;

  clone->tree = g_object_ref (original->tree);
  clone->flow = g_object_ref (original->flow);
  clone->areas = NULL;

  clone->context = g_object_ref (original->context);
}

typedef struct _xslAttrListIterator xslAttrListIterator;
typedef xslAttrListIterator *xslAttrListIteratorPtr;
struct _xslAttrListIterator {
  xmlAttrPtr cur;
};

/**
 * xslAttrListGetIterator:
 * @node: #xmlNodePtr for which to get attribute iterator.
 * 
 * Gets a #xslAttrListIteratorPtr for iterating over the attributes of
 * @node.
 * 
 * Return value: New #xslAttrListIteratorPtr, or NULL if no attributes.
 **/
static xslAttrListIteratorPtr
xslAttrListGetIterator (xmlNodePtr node)
{
  xslAttrListIteratorPtr iterator;

  if (node->properties)
    {
      iterator = (xslAttrListIteratorPtr) xmlMalloc (sizeof (xslAttrListIterator));

      iterator->cur = node->properties;
    }
  else
    {
      iterator = NULL;
    }

  return (iterator);
}

/**
 * xslAttrListIteratorNext:
 * @iterator: #xslAttrListIteratorPtr to increment.
 * 
 * Increments @iterator to point to the next attribute of the node for
 * which it is the iterator.
 * 
 * Return value: %TRUE if incremented, %FALSE if no next attribute.
 **/
static gboolean
xslAttrListIteratorNext (xslAttrListIteratorPtr iterator)
{
  if (iterator->cur != NULL)
    {
      iterator->cur = iterator->cur->next;
    }
  return iterator->cur ? TRUE : FALSE;
}

/**
 * xslAttrListIteratorName:
 * @iterator: 
 * 
 * 
 * 
 * Return value: 
 **/
static xmlChar *
xslAttrListIteratorName (xslAttrListIteratorPtr iterator)
{
  return (xmlChar*) iterator->cur->name;
}

/**
 * xslAttrListIteratorValue:
 * @iterator: 
 * 
 * 
 * 
 * Return value: 
 **/
static xmlChar *
xslAttrListIteratorValue (xslAttrListIteratorPtr iterator)
{
  return (xmlChar*) iterator->cur->children->content;
}

/**
 * xslAttrListIteratorDestroy:
 * @iterator: 
 * 
 * 
 **/
static void
xslAttrListIteratorDestroy (xslAttrListIteratorPtr iterator)
{
  xmlFree (iterator);
}

typedef GType (*FoTypeFunc) (void);

/**
 * fo_fo_resolve_property_attributes_default:
 * @fo_node:      #FoFo
 * @data:         Context within which to resolve property expressions
 * 
 * Every #FoFo object was created from a result tree element that is
 * in the XSL FO namespace.  The object's specified property values
 * are created from the result tree element's attributes.
 *
 * This function evaluates each of the property attributes of the
 * result tree element for @fo_node.
 * 
 * Return value: %FALSE if completed successfully, %TRUE otherwise
 **/
gboolean
fo_fo_resolve_property_attributes_default (FoNode     *fo_node,
					   gpointer    data)
{
  FoPropertyResolveContext *prop_context =
    (FoPropertyResolveContext *) data;
  xmlNodePtr element;
  xslAttrListIteratorPtr iterator;
  FoProperty *font_size = NULL;
  FoFo *fo_fo;
  GSList *node_properties = NULL;
  FoContext *current_context = NULL;
  FoContext *parent_context = NULL;
  GError *error = NULL;
  FoArea *reference_area = prop_context->reference_area;
  FoWarningFlag warning_mode = prop_context->warning_mode;
  GHashTable *prop_eval_hash = prop_context->prop_eval_hash;
  gboolean continue_after_error = prop_context->continue_after_error;

  g_return_val_if_fail (FO_IS_FO (fo_node), TRUE);
  g_return_val_if_fail (prop_eval_hash != NULL, TRUE);

#if defined(LIBFO_DEBUG) && 0
  g_message ("fo_resolve_property_attributes:: fo_node: %s; reference: %s",
	     fo_object_debug_sprintf (fo_node),
	     fo_object_debug_sprintf (reference_area));
#endif

  fo_fo = FO_FO (fo_node);

  element = fo_xml_node_get_xml_node (fo_fo->element);
  parent_context =
    fo_fo_get_context (FO_FO (fo_node_parent (FO_NODE (fo_fo))));

  /* Special processing for FOs with special behaviour defined by the
     spec. */
  if (FO_IS_TABLE_CELL (fo_fo))
    {
      xmlAttrPtr column_number_attr = NULL;
      xmlAttrPtr number_columns_spanned_attr = NULL;
      xmlAttrPtr number_rows_spanned_attr = NULL;

      column_number_attr = xmlHasProp (element,
				       (xmlChar *) "column-number");
      if (column_number_attr)
	{
	  FoTypeFunc type_func =
	    g_hash_table_lookup (prop_eval_hash,
				 "column-number");

	  FoPropertyClass *property_class =
	    g_type_class_ref (type_func());

	  gchar *property_expression = (gchar *)
	    xmlNodeGetContent ((xmlNodePtr) column_number_attr);

	  FoProperty *column_number =
	    fo_property_new_from_expr (property_class,
				       (const gchar *) property_expression,
				       parent_context,
				       NULL,
				       fo_fo,
				       &error);

	  xmlFree (property_expression);

	  if (error != NULL)
	    {
	      fo_object_maybe_propagate_error (FO_OBJECT (fo_fo),
					       prop_context->error,
					       error,
					       continue_after_error);
	      return TRUE;
	    }

	  node_properties = g_slist_prepend (node_properties,
					     (gpointer) column_number);
	  fo_table_cell_set_column_number (fo_fo,
					   column_number);
	}

      number_columns_spanned_attr =
	xmlHasProp (element,
		    (xmlChar *) "number-columns-spanned");
      if (number_columns_spanned_attr)
	{
	  FoTypeFunc type_func =
	    g_hash_table_lookup (prop_eval_hash,
				 "number-columns-spanned");

	  FoPropertyClass *property_class =
	    g_type_class_ref (type_func());

	  gchar *property_expression = (gchar *)
	    xmlNodeGetContent ((xmlNodePtr) number_columns_spanned_attr);

	  FoProperty *number_columns_spanned =
	    fo_property_new_from_expr (property_class,
				       (const gchar *) property_expression,
				       parent_context,
				       NULL,
				       fo_fo,
				       &error);

	  xmlFree (property_expression);

	  if (error != NULL)
	    {
	      fo_object_maybe_propagate_error (FO_OBJECT (fo_fo),
					       prop_context->error,
					       error,
					       continue_after_error);
	      return TRUE;
	    }

	  node_properties = g_slist_prepend (node_properties,
					     (gpointer) number_columns_spanned);
	  fo_table_cell_set_number_columns_spanned (fo_fo,
						    number_columns_spanned);
	}

      number_rows_spanned_attr =
	xmlHasProp (element,
		    (xmlChar *) "number-rows-spanned");

      if (number_rows_spanned_attr)
	{
	  FoTypeFunc type_func =
	    g_hash_table_lookup (prop_eval_hash,
				 "number-rows-spanned");

	  FoPropertyClass *property_class =
	    g_type_class_ref (type_func());

	  gchar *property_expression = (gchar *)
	    xmlNodeGetContent ((xmlNodePtr) number_rows_spanned_attr);

	  FoProperty *number_rows_spanned =
	    fo_property_new_from_expr (property_class,
				       (const gchar *) property_expression,
				       parent_context,
				       NULL,
				       fo_fo,
				       &error);

	  xmlFree (property_expression);

	  if (error != NULL)
	    {
	      fo_object_maybe_propagate_error (FO_OBJECT (fo_fo),
					       prop_context->error,
					       error,
					       continue_after_error);
	      return TRUE;
	    }

	  node_properties = g_slist_prepend (node_properties,
					     (gpointer) number_rows_spanned);
	  fo_table_cell_set_number_rows_spanned (fo_fo,
						 number_rows_spanned);
	}
      fo_table_cell_resolve_number_columns_spanned (fo_fo);
      fo_table_cell_resolve_number_rows_spanned (fo_fo);
      fo_table_cell_resolve_column_number (fo_fo,
					   &error);
      if (error != NULL)
	{
	  fo_object_maybe_propagate_error (FO_OBJECT (fo_fo),
					   prop_context->error,
					   error,
					   continue_after_error);
	  return TRUE;
	}

      fo_table_cell_resolve_column (fo_fo);
    }

  /* Handle the 'font-size' property first since its value is part of
     the context for evaluating all other properties. */
  if (xmlHasProp (element, (xmlChar *) "font-size"))
    {
      xmlAttrPtr font_size_attr =
	xmlHasProp (element,
		    (xmlChar *) "font-size");

      FoTypeFunc type_func =
	g_hash_table_lookup (prop_eval_hash,
			     "font-size");

      FoPropertyClass *property_class =
	g_type_class_ref (type_func());

      gchar *property_expression = (gchar *)
	xmlNodeGetContent ((xmlNodePtr) font_size_attr);

      font_size =
	fo_property_new_from_expr (property_class,
				   (const gchar *) property_expression,
				   parent_context,
				   NULL,
				   fo_fo,
				   &error);

      xmlFree (property_expression);

      if (error != NULL)
	{
	  fo_object_maybe_propagate_error (FO_OBJECT (fo_fo),
					   prop_context->error,
					   error,
					   continue_after_error);
	  return TRUE;
	}
      else
	{
	  node_properties = g_slist_prepend (node_properties,
					     (gpointer) font_size);
	}
    }


  iterator = xslAttrListGetIterator (element);

  /* Iterate over the remaining attributes. */
  while (iterator)
    {
      FoProperty *property = NULL;

      /* Skip processing attributes that have already been handled. */
      if (strcmp ((gchar *) xslAttrListIteratorName (iterator),
		  "font-size") == 0 ||
	  (FO_IS_TABLE_CELL (fo_fo) &&
	   (strcmp ((gchar *) xslAttrListIteratorName (iterator),
		    "column-number") == 0 ||
	    strcmp ((gchar *) xslAttrListIteratorName (iterator),
		    "number-columns-spanned") == 0 ||
	    strcmp ((gchar *) xslAttrListIteratorName (iterator),
		    "number-rows-spanned") == 0)))
	{
	  if (xslAttrListIteratorNext (iterator))
	    {
	      continue;
	    }
	  else
	    {
	      break;
	    }
	}

      FoPropertyClass *property_class = NULL;
      FoTypeFunc type_func =
	g_hash_table_lookup (prop_eval_hash,
			     xslAttrListIteratorName (iterator));

      if (type_func != NULL)
	{
	  property_class =
	    g_type_class_ref (type_func());

	  const gchar *property_expression =
	    (const gchar *) xslAttrListIteratorValue (iterator);

	  property =
	    fo_property_new_from_expr (property_class,
				       property_expression,
				       parent_context,
				       font_size ? font_size : NULL,
				       fo_fo,
				       &error);
	  if (error != NULL)
	    {
	      fo_object_maybe_propagate_error (FO_OBJECT (fo_fo),
					       prop_context->error,
					       error,
					       continue_after_error);
	      return TRUE;
	    }

	  g_type_class_unref (property_class);
	  node_properties = g_slist_prepend (node_properties,
					     (gpointer) property);
	}
      else
	{
	  if (warning_mode & FO_WARNING_UNSUPPORTED_PROPERTY)
	    {
	      GError *unsupported_property_error =
		g_error_new (FO_FO_ERROR,
			     FO_FO_ERROR_UNSUPPORTED_PROPERTY,
			     _(fo_fo_error_messages[FO_FO_ERROR_UNSUPPORTED_PROPERTY]),
			     xslAttrListIteratorName (iterator));

	      fo_object_log_warning (FO_OBJECT (fo_fo),
				     &unsupported_property_error);
	    }
	}

    if (!xslAttrListIteratorNext (iterator))
      break;
  }

  xslAttrListIteratorDestroy (iterator);

  current_context = fo_context_new ();
  if (node_properties != NULL)
    {
      fo_context_update_from_slist (current_context, node_properties);
      g_slist_free (node_properties);
    }

  fo_context_util_spaces_resolve (current_context, reference_area);
  fo_context_util_length_ranges_resolve (current_context, reference_area);
  /* Validate property values and property interrations of FO tree. */
  fo_fo_validate (fo_fo,
		  current_context,
		  parent_context,
		  &error);

  if (error != NULL)
    {
      g_propagate_error (/*FO_OBJECT (fo_fo),*/
					prop_context->error,
					error);
      return TRUE;
    }

  fo_context_merge (current_context, parent_context);
  fo_fo_set_context (fo_fo, current_context);

  return FALSE;
}

/**
 * fo_fo_resolve_property_attributes:
 * @fo_node: #FoNode for which to resolve property attributes.
 * @data:    Context in which to resolve the properties.
 * 
 * Resolves the values of the properties of @fo_node.
 * 
 * Return value: %TRUE if an error occurred, %FALSE otherwise.
 **/
gboolean
fo_fo_resolve_property_attributes (FoNode  *fo_node,
				   gpointer data)
{
  FoNodeTraverseFunc func;

  g_return_val_if_fail (FO_IS_FO (fo_node), TRUE);

  func = FO_FO_GET_CLASS (fo_node)->resolve_property_attributes;

  if (func != NULL)
    {
      return func (fo_node,
		   data);
    }
  else
    {
      return FALSE;
    }
}

/**
 * fo_fo_children_properties_resolve_default:
 * @this_fo:              #FoFo for which to resolve properties.
 * @this_fo_parent_area:  Parent #FoArea to which to add new areas.
 * @new_area:             New area, if any.
 * @prop_eval_hash:       Map of property names to property eval functions.
 * @fo_doc:               Output #FoDoc.
 * @continue_after_error: Whether to continue after any formatting errors.
 * @debug_level:          Debug level.
 * @warning_mode:         Warning mode.
 * @error:                Indication of any error that occurred.
 * 
 * Resolves the properties of the children of @this_fo.
 **/
void
fo_fo_children_properties_resolve_default (FoFo         *this_fo,
					   FoArea       *this_fo_parent_area,
					   FoArea      **new_area,
					   GHashTable   *prop_eval_hash,
					   FoDoc        *fo_doc,
					   gboolean      continue_after_error,
					   FoDebugFlag   debug_level,
					   FoWarningFlag warning_mode,
					   GError      **error)
{
  FoNode *child_node;
  GError *tmp_error = NULL;
  FoArea *this_fo_area = NULL;
  FoArea *child_fo_parent_area;
  FoFoAreaNew2Context area_new2_context;
  FoPropertyResolveContext prop_context;
  gboolean resolve_attributes_halted;

  g_return_if_fail (FO_IS_FO (this_fo));
  g_return_if_fail (FO_IS_AREA (this_fo_parent_area));
  g_return_if_fail (*new_area == NULL);
  g_return_if_fail (error == NULL || *error == NULL);

#if defined(LIBFO_DEBUG) && 0
  g_message ("node_children_properties_resolve:: this_fo: %s; this_fo_parent_area: %s",
	     fo_object_debug_sprintf (this_fo),
	     fo_object_debug_sprintf (this_fo_parent_area));
#endif

  prop_context.reference_area       = fo_area_get_reference (this_fo_parent_area);
  prop_context.prop_eval_hash       = prop_eval_hash;
  prop_context.continue_after_error = continue_after_error;
  prop_context.debug_level          = debug_level;
  prop_context.warning_mode         = warning_mode;
  prop_context.error                = &tmp_error;

  resolve_attributes_halted =
    fo_fo_resolve_property_attributes (FO_NODE (this_fo),
				       &prop_context);

  if (resolve_attributes_halted)
    {
      fo_object_log_or_propagate_error (FO_OBJECT (this_fo),
					error,
					tmp_error);
      return;
    }

  area_new2_context.fo_doc               = fo_doc;
  area_new2_context.parent_area          = this_fo_parent_area;
  area_new2_context.new_area             = &this_fo_area;
  area_new2_context.continue_after_error = continue_after_error;
  area_new2_context.debug_level          = debug_level;

  fo_fo_area_new2 (this_fo,
		   &area_new2_context,
		   &tmp_error);

  *new_area = this_fo_area;

  if (*new_area != NULL)
    {
      child_fo_parent_area = *new_area;
    }
  else
    {
      child_fo_parent_area = this_fo_parent_area;
    }

#if defined(LIBFO_DEBUG) && 0
  g_message ("node_children_properties_resolve:: initial *new_area: %s",
	     fo_object_debug_sprintf (*new_area));
#endif

  child_node = fo_node_first_child (FO_NODE (this_fo));

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
	  child_fo_parent_area = fo_area_parent (area);
	  if (*new_area)
	    *new_area = child_fo_parent_area;
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
}

/**
 * fo_fo_children_properties_resolve:
 * @this_fo:              #FoFo for which to resolve properties.
 * @this_fo_parent_area:  Parent #FoArea to which to add new areas.
 * @new_area:             New area, if any.
 * @prop_eval_hash:       Map of property names to property eval functions.
 * @fo_doc:               Output #FoDoc.
 * @continue_after_error: Whether to continue after any formatting errors.
 * @debug_level:          Debug level.
 * @warning_mode:         Warning mode.
 * @error:                Indication of any error that occurred.
 * 
 * Resolves the properties of the children of @this_fo.
 **/
void
fo_fo_children_properties_resolve (FoFo         *this_fo,
				   FoArea       *this_fo_parent_area,
				   FoArea      **new_area,
				   GHashTable   *prop_eval_hash,
				   FoDoc        *fo_doc,
				   gboolean      continue_after_error,
				   FoDebugFlag   debug_level,
				   FoWarningFlag warning_mode,
				   GError      **error)
{
  FO_FO_GET_CLASS (this_fo)->children_properties_resolve (this_fo,
							  this_fo_parent_area,
							  new_area,
							  prop_eval_hash,
							  fo_doc,
							  continue_after_error,
							  debug_level,
							  warning_mode,
							  error);
}

/**
 * fo_fo_area_new:
 * @fo:          #FoFo for which to create a new area.
 * @fo_doc:      Output #FoDoc
 * @parent_area: #FoArea to which to add new area.
 * @new_area:    New area.
 * @debug_level: Debug level.
 * 
 * Creates a new #FoArea for @fo and adds it as the last child of
 * @parent_area.
 *
 * Deprecated: Use #fo_fo_area_new2 in new code.
 **/
void
fo_fo_area_new (FoFo    *fo,
		FoDoc   *fo_doc,
		FoArea  *parent_area,
		FoArea **new_area,
		guint    debug_level)
{
  FO_FO_GET_CLASS (fo)->area_new (fo,
				  fo_doc,
				  parent_area,
				  new_area,
				  debug_level);
}

/**
 * fo_fo_area_new_default:
 * @fo:          #FoFo for which to create a new area.
 * @fo_doc:      Output #FoDoc
 * @parent_area: #FoArea to which to add new area.
 * @new_area:    New area.
 * @debug_level: Debug level.
 * 
 * Creates a new #FoArea for @fo and adds it as the last child of
 * @parent_area.
 **/
static void
fo_fo_area_new_default (FoFo    *fo,
			FoDoc   *fo_doc G_GNUC_UNUSED,
			FoArea  *parent_area G_GNUC_UNUSED,
			FoArea **new_area,
			guint    debug_level G_GNUC_UNUSED)
{
  *new_area = NULL;

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have an 'area_new' function."),
	 fo_object_sprintf (FO_OBJECT (fo)));
}

/**
 * fo_fo_area_new2:
 * @fo:      #FoFo for which to create area.
 * @context: Context in which to create area.
 * @error:   Indication of any error that occurred.
 * 
 * Creates a new #FoArea corresponding to @fo.
 **/
void fo_fo_area_new2 (FoFo *fo,
		      FoFoAreaNew2Context *context,
		      GError **error)
{
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "fo_fo_area_new2:: %s",
	 fo_object_debug_sprintf (fo));
#endif  
  if (FO_FO_GET_CLASS (fo)->area_new2 != NULL)
    FO_FO_GET_CLASS (fo)->area_new2 (fo,
				     context,
				     error);
}

void fo_fo_area_new2_default (FoFo *fo G_GNUC_UNUSED,
			      FoFoAreaNew2Context *context G_GNUC_UNUSED,
			      GError **error G_GNUC_UNUSED)
{
#if defined(LIBFO_DEBUG) && 0
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have an 'area_new2' function."),
	 fo_object_sprintf (FO_OBJECT (fo)));
#endif
}

/* Tree-related functions */

FoNode*
fo_fo_prepend (FoNode *parent,
	       FoNode *fo)
{
  FoFo *parent_fo, *fo_fo;

  g_return_val_if_fail (FO_IS_FO (parent), fo);
  g_return_val_if_fail (FO_IS_FO (fo), fo);

  parent_fo = FO_FO (parent);
  fo_fo = FO_FO (fo);

  if (FO_IS_FLOW (fo_fo))
    fo_fo->flow = fo_fo;
  else
    fo_fo->flow = parent_fo->flow;

  return FO_NODE_CLASS (parent_class)->prepend (parent, fo);
}

FoNode*
fo_fo_append (FoNode *parent,
	      FoNode *fo)
{
  FoFo *parent_fo, *fo_fo;

  g_return_val_if_fail (FO_IS_FO (parent), fo);
  g_return_val_if_fail (FO_IS_FO (fo), fo);

  parent_fo = FO_FO (parent);
  fo_fo = FO_FO (fo);

  if (FO_IS_TREE (fo_fo))
    fo_fo->tree = fo_fo;
  else
    fo_fo->tree = parent_fo->tree;

  if (FO_IS_FLOW (fo_fo))
    fo_fo->flow = fo_fo;
  else
    fo_fo->flow = parent_fo->flow;

  /* FIXME: Is this either necessary or correct? */
  if (parent_fo->context)
    fo_fo->context = g_object_ref (parent_fo->context);

  return FO_NODE_CLASS (parent_class)->append (parent, fo);
}

/**
 * fo_fo_trim_whitespace_children:
 * @fo: #FoFo to trim
 * 
 * Remove any "whitespace" children of @fo. I.e., unlink and unref any
 * children that are FoText that contain only whitespace or are
 * FoWrapperWhitespace nodes.
 *
 * Leaves @fo with no "whitespace" children.
 **/
void
fo_fo_trim_whitespace_children (FoFo *fo)
{
  FoNode *fo_node;

  g_return_if_fail (FO_IS_FO (fo));

  fo_node = fo_node_first_child (FO_NODE (fo));

  while (fo_node)
    {
      FoNode *next_node = fo_node_next_sibling (fo_node);

      if (FO_IS_TEXT (fo_node) &&
	  fo_text_get_whitespace_only (FO_FO (fo_node)))
	{
	  fo_node_unlink (fo_node);
	  g_object_unref (fo_node);
	}
      else if (FO_IS_WRAPPER_WHITESPACE (fo_node))
	{
	  FoNode *whitespace_node = fo_node_first_child (fo_node);

	  g_assert (fo_node_n_children (fo_node) == 1);

	  fo_node_unlink (whitespace_node);
	  g_object_unref (whitespace_node);
	  fo_node_unlink (fo_node);
	  g_object_unref (fo_node);
	}

      fo_node = next_node;
    }
}

/**
 * fo_fo_validate_content_empty:
 * @fo:    #FoFo to validate.
 * @error: #GError indicating any error.
 * 
 * Validates that @fo does not contain any child #FoFo
 * 
 * Return value: %FALSE if @fo is empty.
 **/
gboolean
fo_fo_validate_content_empty (FoFo *fo,
			      GError **error)
{
  GError *tmp_error;

  g_return_val_if_fail (FO_IS_FO (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  if (fo_node_n_children (FO_NODE (fo)) > 0)
    {
      tmp_error = g_error_new (FO_FO_ERROR,
			       FO_FO_ERROR_NOT_EMPTY,
			       "Not empty");
      return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					       error,
					       tmp_error);
    }
  else
    {
      return FALSE;
    }
}

/**
 * fo_fo_validate_content_block_plus:
 * @fo:    #FoFo to validate.
 * @error: #GError indicating any error.
 * 
 * Validates the @fo contains one or more #FoBlockFo formatting objects.
 * 
 * Return value: %FALSE if content matches.
 **/
gboolean
fo_fo_validate_content_block_plus (FoFo *fo,
				   GError **error)
{
  GError *tmp_error;

  g_return_val_if_fail (FO_IS_FO (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  if (fo_node_n_children (FO_NODE (fo)) == 0)
    {
      tmp_error = g_error_new (FO_FO_ERROR,
			       FO_FO_ERROR_NOT_EMPTY,
			       _(fo_fo_error_messages[FO_FO_ERROR_NOT_EMPTY]),
			       fo_object_sprintf (FO_OBJECT (fo)));

      return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					       error,
					       tmp_error);
    }
  else
    {
      FoNode *child_node = fo_node_first_child (FO_NODE (fo));

      while (child_node)
	{
	  if (!FO_IS_BLOCK_FO (FO_FO (child_node)) &&
	      !FO_IS_NEUTRAL_FO (FO_FO (child_node)))
	    {
	      tmp_error = g_error_new (FO_FO_ERROR,
				       FO_FO_ERROR_NOT_BLOCK,
				       _(fo_fo_error_messages[FO_FO_ERROR_NOT_BLOCK]),
				       fo_object_sprintf (FO_OBJECT (fo)));

	      return fo_object_log_or_propagate_error (FO_OBJECT (fo),
						       error,
						       tmp_error);
	    }

	  child_node = fo_node_next_sibling (child_node);
	}
      return FALSE;
    }
}

#if 0
void
fo_fo_validate_pcdata_or_inline (FoNode *fo_node,
				 gboolean *is_not_pcdata_inline)
{
  if (!FO_IS_INLINE_FO (FO_FO (fo_node)))
    *is_not_pcdata_inline = TRUE;
}

void
fo_fo_validate_block_or_whitespace (FoNode *fo_node,
				    gboolean *is_not_block_or_whitespace)
{
  if (!FO_IS_BLOCK_FO (FO_FO (fo_node)) &&
      !FO_IS_NEUTRAL_FO (FO_FO (fo_node)) &&
      !(FO_IS_TEXT (FO_FO (fo_node))
	&& fo_text_get_whitespace_only (FO_FO (fo_node))))
    *is_not_block_or_whitespace = TRUE;
}
#endif

/**
 * fo_fo_validate_pcdata_inline_block_neutral:
 * @fo_node: #FoFo to validate
 * @data:    Pointer to #gboolean storing result
 * 
 * Validates that the content of @fo_node is only ##PCDATA or #FoInline or
 * #FoNeutral formatting objects.
 **/
void
fo_fo_validate_pcdata_inline_block_neutral (FoNode  *fo_node,
					    gpointer data)
{
  gboolean *is_not_pcdata_inline_block_neutral = (gboolean *) data;
  if (!FO_IS_INLINE_FO (FO_FO (fo_node)) &&
      !FO_IS_NEUTRAL_FO (FO_FO (fo_node)) &&
      !FO_IS_BLOCK_FO (FO_FO (fo_node)))
    {
      GError *error = g_error_new (FO_FO_ERROR,
				   FO_FO_ERROR_INVALID_CHILD,
				   fo_fo_error_messages[FO_FO_ERROR_INVALID_CHILD],
				   fo_object_sprintf (FO_OBJECT (fo_node)),
				   fo_object_sprintf (FO_OBJECT (fo_node_parent (fo_node))));

      *is_not_pcdata_inline_block_neutral = TRUE;

      fo_object_log_error (FO_OBJECT (fo_node),
			   &error);

    }
}

/**
 * fo_fo_error_quark:
 * 
 * Gets the #GQuark identifying #FoFo errors.
 * 
 * Return value: #GQuark identifying #FoFo errors.
 **/
GQuark
fo_fo_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("fo-fo-error");
  return quark;
}


/**
 * fo_fo_get_area_iterator:
 * @fo: #FoFo for which to get iterator.
 * 
 * Gets a #FoFoAreaIterator for iterating over the areas generated by @fo.
 * 
 * Return value: A #FoFoAreaIterator.
 **/
FoFoAreaIterator*
fo_fo_get_area_iterator (FoFo *fo)
{
  FoFoAreaIterator *iterator;

  g_return_val_if_fail (FO_IS_FO (fo), NULL);

  iterator = g_new (FoFoAreaIterator, 1);

  iterator->fo = fo;
  iterator->area_list = fo->areas;

  return iterator;
}

/**
 * fo_fo_area_iterator_get_area:
 * @iterator: #FoFoAreaIterator for which to get current area.
 * 
 * Gets the current #FoArea pointed to by @iterator.
 * 
 * Return value: The current #FoArea.
 **/
FoArea*
fo_fo_area_iterator_get_area (const FoFoAreaIterator *iterator)
{
  g_return_val_if_fail (iterator != NULL, NULL);

  return iterator->area_list->data;
}

/**
 * fo_fo_area_iterator_next:
 * @iterator: #FoFoAreaIterator to modify
 * 
 * Makes @iterator point to the next #FoArea in its list.
 * 
 * Return value: %TRUE if there is a next #FoArea, %FALSE if not.
 **/
gboolean
fo_fo_area_iterator_next (FoFoAreaIterator *iterator)
{
  g_return_val_if_fail (iterator != NULL, FALSE);

  iterator->area_list = g_list_next (iterator->area_list);

  return (iterator->area_list != NULL) ? TRUE : FALSE;
}

void
fo_fo_register_id (FoFo       *fo,
		   FoDatatype *id)
{
  g_return_if_fail (FO_IS_FO (fo));
  g_return_if_fail (FO_IS_ID (id));

  fo_tree_id_add (fo->tree,
		  fo_id_get_value (id),
		  fo);
}
