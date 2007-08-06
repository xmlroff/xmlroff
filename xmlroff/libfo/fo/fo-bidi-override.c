/* Fo
 * fo-bidi-override.c: Bidi Override formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-inline-fo.h"
#include "fo-bidi-override.h"
#include "fo-bidi-override-private.h"
#include "property/fo-property-common-font.h"
#include "property/fo-property-text-property.h"
#include "property/fo-property-color.h"
#include "property/fo-property-direction.h"
#include "property/fo-property-font-family.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-stretch.h"
#include "property/fo-property-font-style.h"
#include "property/fo-property-font-variant.h"
#include "property/fo-property-font-weight.h"
#include "property/fo-property-id.h"
#include "property/fo-property-line-height.h"
#include "property/fo-property-score-spaces.h"
#include "property/fo-property-unicode-bidi.h"

/* PDF = U+202C
 *     = 0010 0000 0010 1100 (UTF-16)
 *     = zzzz yyyy yyxx xxxx
 *     = 1110zzzz 10yyyyyy 10xxxxxx (UTF-8)
 *     = 11100010 10000000 10101100 (UTF-8)
 *     = 11 100 010  10 000 000  10 101 100 (UTF-8)
 *     = \342\200\254 (UTF-8)
 */
#define FO_UTF8_STR_PDF		"\342\200\254"	/* U+202C */
#define FO_UTF8_STR_RLO		"\342\200\256"	/* U+202E */
#define FO_UTF8_STR_LRO		"\342\200\255"	/* U+202D */
#define FO_UTF8_STR_RLE		"\342\200\253"	/* U+202B */
#define FO_UTF8_STR_LRE		"\342\200\252"	/* U+202A */

enum {
  PROP_0,
  PROP_COLOR,
  PROP_DIRECTION,
  PROP_FONT_FAMILY,
  PROP_FONT_SIZE,
  PROP_FONT_STRETCH,
  PROP_FONT_STYLE,
  PROP_FONT_VARIANT,
  PROP_FONT_WEIGHT,
  PROP_ID,
  PROP_LINE_HEIGHT,
  PROP_SCORE_SPACES,
  PROP_UNICODE_BIDI
};

static void fo_bidi_override_class_init  (FoBidiOverrideClass *klass);
static void fo_bidi_override_inline_fo_init (FoInlineFoIface *iface);
static void fo_bidi_override_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_bidi_override_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static void fo_bidi_override_finalize    (GObject           *object);
static gboolean fo_bidi_override_validate_content (FoFo    *fo,
                                                   GError **error);
static void fo_bidi_override_validate (FoFo      *fo,
                                       FoContext *current_context,
                                       FoContext *parent_context);
static void fo_bidi_override_update_from_context (FoFo      *fo,
                                                  FoContext *context);
static void fo_bidi_override_debug_dump_properties (FoFo *fo,
                                                    gint  depth);
static void fo_bidi_override_get_text_attr_list (FoFo *fo_inline_fo,
						 FoDoc   *fo_doc,
						 GString *text,
						 GList **attr_glist,
						 guint debug_level);

static gpointer parent_class;

/**
 * fo_bidi_override_get_type:
 * @void: 
 * 
 * Register the FoBidiOverride object type.
 * 
 * Return value: GType value of the FoBidiOverride object type.
 **/
GType
fo_bidi_override_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoBidiOverrideClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_bidi_override_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoBidiOverride),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      static const GInterfaceInfo fo_inline_fo_info =
      {
	(GInterfaceInitFunc) fo_bidi_override_inline_fo_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_MARKER_PARENT,
                                            "FoBidiOverride",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &fo_inline_fo_info);
    }
  
  return object_type;
}

/**
 * fo_bidi_override_class_init:
 * @klass: FoBidiOverrideClass object to initialise
 * 
 * Implements GClassInitFunc for FoBidiOverrideClass
 **/
void
fo_bidi_override_class_init (FoBidiOverrideClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_bidi_override_finalize;

  object_class->set_property = fo_bidi_override_set_property;
  object_class->get_property = fo_bidi_override_get_property;

  FO_FO_CLASS (klass)->validate_content = fo_bidi_override_validate_content;
  FO_FO_CLASS (klass)->validate = fo_bidi_override_validate;
  FO_FO_CLASS (klass)->update_from_context = fo_bidi_override_update_from_context;
  FO_FO_CLASS (klass)->debug_dump_properties = fo_bidi_override_debug_dump_properties;
  FO_FO_CLASS (klass)->allow_mixed_content = TRUE;

  g_object_class_install_property
    (object_class,
     PROP_COLOR,
     g_param_spec_object ("color",
			  _("Color"),
			  _("Color property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_DIRECTION,
     g_param_spec_object ("direction",
			  _("Direction"),
			  _("Direction property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_FAMILY,
     g_param_spec_object ("font-family",
			  _("Font Family"),
			  _("Font Family property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_SIZE,
     g_param_spec_object ("font-size",
			  _("Font Size"),
			  _("Font Size property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_STRETCH,
     g_param_spec_object ("font-stretch",
			  _("Font Stretch"),
			  _("Font Stretch property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_STYLE,
     g_param_spec_object ("font-style",
			  _("Font Style"),
			  _("Font Style property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_VARIANT,
     g_param_spec_object ("font-variant",
			  _("Font Variant"),
			  _("Font Variant property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_FONT_WEIGHT,
     g_param_spec_object ("font-weight",
			  _("Font Weight"),
			  _("Font Weight property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_ID,
     g_param_spec_object ("id",
			  _("Id"),
			  _("Id property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_LINE_HEIGHT,
     g_param_spec_object ("line-height",
			  _("Line Height"),
			  _("Line Height property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_SCORE_SPACES,
     g_param_spec_object ("score-spaces",
			  _("Score Spaces"),
			  _("Score Spaces property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_UNICODE_BIDI,
     g_param_spec_object ("unicode-bidi",
			  _("Unicode Bidi"),
			  _("Unicode Bidi property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
}

/**
 * fo_bidi_override_inline_fo_init:
 * @iface: FoInlineFoIFace structure for this class
 * 
 * Initialize FoInlineFoIface interface for this class
 **/
void
fo_bidi_override_inline_fo_init (FoInlineFoIface *iface)
{
  iface->get_text_attr_list = fo_bidi_override_get_text_attr_list;
}

/**
 * fo_bidi_override_finalize:
 * @object: FoBidiOverride object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoBidiOverride
 **/
void
fo_bidi_override_finalize (GObject *object)
{
  FoBidiOverride *fo_bidi_override;

  fo_bidi_override = FO_BIDI_OVERRIDE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_bidi_override_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoBidiOverride
 **/
void
fo_bidi_override_set_property (GObject      *object,
                               guint         prop_id,
                               const GValue *value,
                               GParamSpec   *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_COLOR:
      fo_bidi_override_set_color (fo_fo, g_value_get_object (value));
      break;
    case PROP_DIRECTION:
      fo_bidi_override_set_direction (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_FAMILY:
      fo_bidi_override_set_font_family (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_SIZE:
      fo_bidi_override_set_font_size (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_STRETCH:
      fo_bidi_override_set_font_stretch (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_STYLE:
      fo_bidi_override_set_font_style (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_VARIANT:
      fo_bidi_override_set_font_variant (fo_fo, g_value_get_object (value));
      break;
    case PROP_FONT_WEIGHT:
      fo_bidi_override_set_font_weight (fo_fo, g_value_get_object (value));
      break;
    case PROP_ID:
      fo_bidi_override_set_id (fo_fo, g_value_get_object (value));
      break;
    case PROP_LINE_HEIGHT:
      fo_bidi_override_set_line_height (fo_fo, g_value_get_object (value));
      break;
    case PROP_SCORE_SPACES:
      fo_bidi_override_set_score_spaces (fo_fo, g_value_get_object (value));
      break;
    case PROP_UNICODE_BIDI:
      fo_bidi_override_set_unicode_bidi (fo_fo, g_value_get_object (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_bidi_override_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoBidiOverride
 **/
void
fo_bidi_override_get_property (GObject    *object,
                               guint       prop_id,
                               GValue     *value,
                               GParamSpec *pspec)
{
  FoFo *fo_fo;

  fo_fo = FO_FO (object);

  switch (prop_id)
    {
    case PROP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_color (fo_fo)));
      break;
    case PROP_DIRECTION:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_direction (fo_fo)));
      break;
    case PROP_FONT_FAMILY:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_font_family (fo_fo)));
      break;
    case PROP_FONT_SIZE:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_font_size (fo_fo)));
      break;
    case PROP_FONT_STRETCH:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_font_stretch (fo_fo)));
      break;
    case PROP_FONT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_font_style (fo_fo)));
      break;
    case PROP_FONT_VARIANT:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_font_variant (fo_fo)));
      break;
    case PROP_FONT_WEIGHT:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_font_weight (fo_fo)));
      break;
    case PROP_ID:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_id (fo_fo)));
      break;
    case PROP_LINE_HEIGHT:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_line_height (fo_fo)));
      break;
    case PROP_SCORE_SPACES:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_score_spaces (fo_fo)));
      break;
    case PROP_UNICODE_BIDI:
      g_value_set_object (value, G_OBJECT (fo_bidi_override_get_unicode_bidi (fo_fo)));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_bidi_override_new:
 * 
 * Creates a new #FoBidiOverride initialized to default value.
 * 
 * Return value: the new #FoBidiOverride
 **/
FoFo*
fo_bidi_override_new (void)
{
  return FO_FO (g_object_new (fo_bidi_override_get_type (), NULL));
}

/**
 * fo_bidi_override_validate_content:
 * @fo:    FoBidiOverride object to validate
 * @error: GError indicating error condition, if any
 * 
 * Validate the content model, i.e., the structure, of the object.
 * Return value matches GNodeTraverseFunc model: FALSE indicates content
 * model is correct, or TRUE indicates an error.  When used with
 * fo_node_traverse(), returning TRUE stops the traversal.
 * 
 * Return value: FALSE if content model okay, TRUE if not
 **/
gboolean
fo_bidi_override_validate_content (FoFo    *fo,
                                   GError **error)
{
  /*GError *tmp_error;*/

  g_return_val_if_fail (fo != NULL, TRUE);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo), TRUE);
  g_return_val_if_fail (error == NULL || *error == NULL, TRUE);

  return FALSE;
  /*
 error:
  tmp_error = g_error_new (FO_FO_ERROR,
			   FO_FO_ERROR_INVALID_CONTENT,
			   _(fo_fo_error_messages[FO_FO_ERROR_INVALID_CONTENT]),
			   fo_object_sprintf (FO_OBJECT (fo)));

  return fo_object_log_or_propagate_error (FO_OBJECT (fo),
					   error,
					   tmp_error);
  */
}

/**
 * fo_bidi_override_validate:
 * @fo:              FoBidiOverride object to validate
 * @current_context: FoContext associated with current object
 * @parent_context:  FoContext associated with parent FO
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values
 **/
void
fo_bidi_override_validate (FoFo      *fo,
                           FoContext *current_context,
                           FoContext *parent_context)
{
  FoBidiOverride *fo_bidi_override;

  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo));
  g_return_if_fail (FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));

  fo_bidi_override = FO_BIDI_OVERRIDE (fo);

  fo_context_merge (current_context, parent_context);
  fo_fo_update_from_context (fo, current_context);
  fo_bidi_override_set_line_height (fo,
				    fo_property_line_height_resolve (fo_bidi_override->line_height,
								     fo_bidi_override->font_size));
}

/**
 * fo_bidi_override_update_from_context:
 * @fo:      The #FoFo object
 * @context: The #FoContext object from which to update the properties of @fo
 * 
 * Sets the properties of @fo to the corresponding property values in @context
 **/
void
fo_bidi_override_update_from_context (FoFo *fo,
                                      FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo));
  g_return_if_fail (FO_IS_CONTEXT (context));

  fo_bidi_override_set_color (fo,
			  fo_context_get_color (context));
  fo_bidi_override_set_direction (fo,
			  fo_context_get_direction (context));
  fo_bidi_override_set_font_family (fo,
			  fo_context_get_font_family (context));
  fo_bidi_override_set_font_size (fo,
			  fo_context_get_font_size (context));
  fo_bidi_override_set_font_stretch (fo,
			  fo_context_get_font_stretch (context));
  fo_bidi_override_set_font_style (fo,
			  fo_context_get_font_style (context));
  fo_bidi_override_set_font_variant (fo,
			  fo_context_get_font_variant (context));
  fo_bidi_override_set_font_weight (fo,
			  fo_context_get_font_weight (context));
  fo_bidi_override_set_id (fo,
			  fo_context_get_id (context));
  fo_bidi_override_set_line_height (fo,
			  fo_context_get_line_height (context));
  fo_bidi_override_set_score_spaces (fo,
			  fo_context_get_score_spaces (context));
  fo_bidi_override_set_unicode_bidi (fo,
			  fo_context_get_unicode_bidi (context));
}

/**
 * fo_bidi_override_debug_dump_properties:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_bidi_override_debug_dump_properties (FoFo *fo, gint depth)
{
  FoBidiOverride *fo_bidi_override;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo));

  fo_bidi_override = FO_BIDI_OVERRIDE (fo);

  fo_object_debug_dump (fo_bidi_override->color, depth);
  fo_object_debug_dump (fo_bidi_override->direction, depth);
  fo_object_debug_dump (fo_bidi_override->font_family, depth);
  fo_object_debug_dump (fo_bidi_override->font_size, depth);
  fo_object_debug_dump (fo_bidi_override->font_stretch, depth);
  fo_object_debug_dump (fo_bidi_override->font_style, depth);
  fo_object_debug_dump (fo_bidi_override->font_variant, depth);
  fo_object_debug_dump (fo_bidi_override->font_weight, depth);
  fo_object_debug_dump (fo_bidi_override->id, depth);
  fo_object_debug_dump (fo_bidi_override->line_height, depth);
  fo_object_debug_dump (fo_bidi_override->score_spaces, depth);
  fo_object_debug_dump (fo_bidi_override->unicode_bidi, depth);

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

/**
 * fo_bidi_override_get_text_attr_list:
 * @fo_inline_fo: The @FoInlineFo object
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO
 * @attr_glist:   The list of Pango attributes for the inline FO
 * @debug_level:  Debug level
 * 
 * Gets the text of the inline FO and its associated list of Pango attributes
 **/
void
fo_bidi_override_get_text_attr_list (FoFo *fo_inline_fo,
				     FoDoc   *fo_doc,
				     GString *text,
				     GList **attr_glist,
				     guint debug_level)
{
  FoNode *fo_child_node;
  FoBidiOverride *fo_bidi_override;
  GList *my_attr_glist = NULL;
  gint start_index, end_index;
  gint direction, unicode_bidi;

  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_inline_fo));

  fo_bidi_override = FO_BIDI_OVERRIDE (fo_inline_fo);

  start_index = text->len;

  direction =
    fo_enum_get_value (fo_property_get_value (fo_bidi_override->direction));
  unicode_bidi = fo_enum_get_value (fo_property_get_value (fo_bidi_override->unicode_bidi));

  if (unicode_bidi == FO_ENUM_ENUM_EMBED)
    {
      if (direction == FO_ENUM_ENUM_LTR)
	{
	  g_string_append (text, FO_UTF8_STR_LRE);
	}
      else
	{
	  g_string_append (text, FO_UTF8_STR_RLE);
	}
    }
  else if (unicode_bidi == FO_ENUM_ENUM_BIDI_OVERRIDE)
    {
      if (direction == FO_ENUM_ENUM_LTR)
	{
	  g_string_append (text, FO_UTF8_STR_LRO);
	}
      else
	{
	  g_string_append (text, FO_UTF8_STR_RLO);
	}
    }

  fo_child_node = fo_node_first_child (FO_NODE (fo_bidi_override));

  while (fo_child_node)
    {
      fo_inline_fo_get_text_attr_list (FO_FO (fo_child_node),
				       fo_doc,
				       text,
				       &my_attr_glist,
				       debug_level);
      fo_child_node = fo_node_next_sibling (fo_child_node);
    }

  g_string_append (text, FO_UTF8_STR_PDF);

  end_index = text->len;

  if (start_index != end_index)
    {
      PangoAttribute *pango_attr;

      my_attr_glist =
	g_list_concat (my_attr_glist,
		       fo_property_common_font_get_pango_attrs (fo_bidi_override->font_family,
								fo_bidi_override->font_size,
								fo_bidi_override->font_stretch,
								fo_bidi_override->font_style,
								fo_bidi_override->font_variant,
								fo_bidi_override->font_weight,
								start_index,
								end_index));
      /*
      pango_attr =
	fo_property_text_property_new_attr (fo_bidi_override->line_height);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
      */
      pango_attr =
	fo_property_text_property_new_attr (fo_bidi_override->color);
      pango_attr->start_index = start_index;
      pango_attr->end_index = end_index;
      my_attr_glist = g_list_prepend (my_attr_glist, pango_attr);
    }

  *attr_glist = g_list_concat (my_attr_glist,
			       *attr_glist);
}

/**
 * fo_bidi_override_set_color:
 * @fo_fo: The @FoFo object
 * @new_color: The new "color" property value
 * 
 * Sets the #color property of @bidi_override to @new_color
 **/
void
fo_bidi_override_set_color (FoFo *fo_fo,
		         FoProperty *new_color)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_COLOR (new_color));

  if (new_color)
    g_object_ref (G_OBJECT (new_color));
  if (fo_bidi_override->color)
    g_object_unref (G_OBJECT (fo_bidi_override->color));
  fo_bidi_override->color = new_color;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "color");*/
}

/**
 * fo_bidi_override_get_color:
 * @fo_fo: The @FoFo object
 *
 * Gets the #color property of @bidi_override
 *
 * Return value: The "color" property value
**/
FoProperty*
fo_bidi_override_get_color (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->color;
}

/**
 * fo_bidi_override_set_direction:
 * @fo_fo: The @FoFo object
 * @new_direction: The new "direction" property value
 * 
 * Sets the #direction property of @bidi_override to @new_direction
 **/
void
fo_bidi_override_set_direction (FoFo *fo_fo,
		         FoProperty *new_direction)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_DIRECTION (new_direction));

  if (new_direction)
    g_object_ref (G_OBJECT (new_direction));
  if (fo_bidi_override->direction)
    g_object_unref (G_OBJECT (fo_bidi_override->direction));
  fo_bidi_override->direction = new_direction;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "direction");*/
}

/**
 * fo_bidi_override_get_direction:
 * @fo_fo: The @FoFo object
 *
 * Gets the #direction property of @bidi_override
 *
 * Return value: The "direction" property value
**/
FoProperty*
fo_bidi_override_get_direction (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->direction;
}

/**
 * fo_bidi_override_set_font_family:
 * @fo_fo: The @FoFo object
 * @new_font_family: The new "font-family" property value
 * 
 * Sets the #font-family property of @bidi_override to @new_font_family
 **/
void
fo_bidi_override_set_font_family (FoFo *fo_fo,
		         FoProperty *new_font_family)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_FONT_FAMILY (new_font_family));

  if (new_font_family)
    g_object_ref (G_OBJECT (new_font_family));
  if (fo_bidi_override->font_family)
    g_object_unref (G_OBJECT (fo_bidi_override->font_family));
  fo_bidi_override->font_family = new_font_family;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "font-family");*/
}

/**
 * fo_bidi_override_get_font_family:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-family property of @bidi_override
 *
 * Return value: The "font-family" property value
**/
FoProperty*
fo_bidi_override_get_font_family (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->font_family;
}

/**
 * fo_bidi_override_set_font_size:
 * @fo_fo: The @FoFo object
 * @new_font_size: The new "font-size" property value
 * 
 * Sets the #font-size property of @bidi_override to @new_font_size
 **/
void
fo_bidi_override_set_font_size (FoFo *fo_fo,
		         FoProperty *new_font_size)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_FONT_SIZE (new_font_size));

  if (new_font_size)
    g_object_ref (G_OBJECT (new_font_size));
  if (fo_bidi_override->font_size)
    g_object_unref (G_OBJECT (fo_bidi_override->font_size));
  fo_bidi_override->font_size = new_font_size;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "font-size");*/
}

/**
 * fo_bidi_override_get_font_size:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-size property of @bidi_override
 *
 * Return value: The "font-size" property value
**/
FoProperty*
fo_bidi_override_get_font_size (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->font_size;
}

/**
 * fo_bidi_override_set_font_stretch:
 * @fo_fo: The @FoFo object
 * @new_font_stretch: The new "font-stretch" property value
 * 
 * Sets the #font-stretch property of @bidi_override to @new_font_stretch
 **/
void
fo_bidi_override_set_font_stretch (FoFo *fo_fo,
		         FoProperty *new_font_stretch)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_FONT_STRETCH (new_font_stretch));

  if (new_font_stretch)
    g_object_ref (G_OBJECT (new_font_stretch));
  if (fo_bidi_override->font_stretch)
    g_object_unref (G_OBJECT (fo_bidi_override->font_stretch));
  fo_bidi_override->font_stretch = new_font_stretch;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "font-stretch");*/
}

/**
 * fo_bidi_override_get_font_stretch:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-stretch property of @bidi_override
 *
 * Return value: The "font-stretch" property value
**/
FoProperty*
fo_bidi_override_get_font_stretch (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->font_stretch;
}

/**
 * fo_bidi_override_set_font_style:
 * @fo_fo: The @FoFo object
 * @new_font_style: The new "font-style" property value
 * 
 * Sets the #font-style property of @bidi_override to @new_font_style
 **/
void
fo_bidi_override_set_font_style (FoFo *fo_fo,
		         FoProperty *new_font_style)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_FONT_STYLE (new_font_style));

  if (new_font_style)
    g_object_ref (G_OBJECT (new_font_style));
  if (fo_bidi_override->font_style)
    g_object_unref (G_OBJECT (fo_bidi_override->font_style));
  fo_bidi_override->font_style = new_font_style;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "font-style");*/
}

/**
 * fo_bidi_override_get_font_style:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-style property of @bidi_override
 *
 * Return value: The "font-style" property value
**/
FoProperty*
fo_bidi_override_get_font_style (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->font_style;
}

/**
 * fo_bidi_override_set_font_variant:
 * @fo_fo: The @FoFo object
 * @new_font_variant: The new "font-variant" property value
 * 
 * Sets the #font-variant property of @bidi_override to @new_font_variant
 **/
void
fo_bidi_override_set_font_variant (FoFo *fo_fo,
		         FoProperty *new_font_variant)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_FONT_VARIANT (new_font_variant));

  if (new_font_variant)
    g_object_ref (G_OBJECT (new_font_variant));
  if (fo_bidi_override->font_variant)
    g_object_unref (G_OBJECT (fo_bidi_override->font_variant));
  fo_bidi_override->font_variant = new_font_variant;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "font-variant");*/
}

/**
 * fo_bidi_override_get_font_variant:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-variant property of @bidi_override
 *
 * Return value: The "font-variant" property value
**/
FoProperty*
fo_bidi_override_get_font_variant (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->font_variant;
}

/**
 * fo_bidi_override_set_font_weight:
 * @fo_fo: The @FoFo object
 * @new_font_weight: The new "font-weight" property value
 * 
 * Sets the #font-weight property of @bidi_override to @new_font_weight
 **/
void
fo_bidi_override_set_font_weight (FoFo *fo_fo,
		         FoProperty *new_font_weight)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_FONT_WEIGHT (new_font_weight));

  if (new_font_weight)
    g_object_ref (G_OBJECT (new_font_weight));
  if (fo_bidi_override->font_weight)
    g_object_unref (G_OBJECT (fo_bidi_override->font_weight));
  fo_bidi_override->font_weight = new_font_weight;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "font-weight");*/
}

/**
 * fo_bidi_override_get_font_weight:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-weight property of @bidi_override
 *
 * Return value: The "font-weight" property value
**/
FoProperty*
fo_bidi_override_get_font_weight (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->font_weight;
}

/**
 * fo_bidi_override_set_id:
 * @fo_fo: The @FoFo object
 * @new_id: The new "id" property value
 * 
 * Sets the #id property of @bidi_override to @new_id
 **/
void
fo_bidi_override_set_id (FoFo *fo_fo,
		         FoProperty *new_id)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_ID (new_id));

  if (new_id)
    g_object_ref (G_OBJECT (new_id));
  if (fo_bidi_override->id)
    g_object_unref (G_OBJECT (fo_bidi_override->id));
  fo_bidi_override->id = new_id;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "id");*/
}

/**
 * fo_bidi_override_get_id:
 * @fo_fo: The @FoFo object
 *
 * Gets the #id property of @bidi_override
 *
 * Return value: The "id" property value
**/
FoProperty*
fo_bidi_override_get_id (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->id;
}

/**
 * fo_bidi_override_set_line_height:
 * @fo_fo: The @FoFo object
 * @new_line_height: The new "line-height" property value
 * 
 * Sets the #line-height property of @bidi_override to @new_line_height
 **/
void
fo_bidi_override_set_line_height (FoFo *fo_fo,
		         FoProperty *new_line_height)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_LINE_HEIGHT (new_line_height));

  if (new_line_height)
    g_object_ref (G_OBJECT (new_line_height));
  if (fo_bidi_override->line_height)
    g_object_unref (G_OBJECT (fo_bidi_override->line_height));
  fo_bidi_override->line_height = new_line_height;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "line-height");*/
}

/**
 * fo_bidi_override_get_line_height:
 * @fo_fo: The @FoFo object
 *
 * Gets the #line-height property of @bidi_override
 *
 * Return value: The "line-height" property value
**/
FoProperty*
fo_bidi_override_get_line_height (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->line_height;
}

/**
 * fo_bidi_override_set_score_spaces:
 * @fo_fo: The @FoFo object
 * @new_score_spaces: The new "score-spaces" property value
 * 
 * Sets the #score-spaces property of @bidi_override to @new_score_spaces
 **/
void
fo_bidi_override_set_score_spaces (FoFo *fo_fo,
		         FoProperty *new_score_spaces)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_SCORE_SPACES (new_score_spaces));

  if (new_score_spaces)
    g_object_ref (G_OBJECT (new_score_spaces));
  if (fo_bidi_override->score_spaces)
    g_object_unref (G_OBJECT (fo_bidi_override->score_spaces));
  fo_bidi_override->score_spaces = new_score_spaces;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "score-spaces");*/
}

/**
 * fo_bidi_override_get_score_spaces:
 * @fo_fo: The @FoFo object
 *
 * Gets the #score-spaces property of @bidi_override
 *
 * Return value: The "score-spaces" property value
**/
FoProperty*
fo_bidi_override_get_score_spaces (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->score_spaces;
}

/**
 * fo_bidi_override_set_unicode_bidi:
 * @fo_fo: The @FoFo object
 * @new_unicode_bidi: The new "unicode-bidi" property value
 * 
 * Sets the #unicode-bidi property of @bidi_override to @new_unicode_bidi
 **/
void
fo_bidi_override_set_unicode_bidi (FoFo *fo_fo,
		         FoProperty *new_unicode_bidi)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_if_fail (fo_bidi_override != NULL);
  g_return_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override));
  g_return_if_fail (FO_IS_PROPERTY_UNICODE_BIDI (new_unicode_bidi));

  if (new_unicode_bidi)
    g_object_ref (G_OBJECT (new_unicode_bidi));
  if (fo_bidi_override->unicode_bidi)
    g_object_unref (G_OBJECT (fo_bidi_override->unicode_bidi));
  fo_bidi_override->unicode_bidi = new_unicode_bidi;
  /*g_object_notify (G_OBJECT (fo_bidi_override), "unicode-bidi");*/
}

/**
 * fo_bidi_override_get_unicode_bidi:
 * @fo_fo: The @FoFo object
 *
 * Gets the #unicode-bidi property of @bidi_override
 *
 * Return value: The "unicode-bidi" property value
**/
FoProperty*
fo_bidi_override_get_unicode_bidi (FoFo *fo_fo)
{
  FoBidiOverride *fo_bidi_override = (FoBidiOverride *) fo_fo;

  g_return_val_if_fail (fo_bidi_override != NULL, NULL);
  g_return_val_if_fail (FO_IS_BIDI_OVERRIDE (fo_bidi_override), NULL);

  return fo_bidi_override->unicode_bidi;
}
