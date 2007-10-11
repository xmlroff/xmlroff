/* Fo
 * fo-text.c: Unofficial 'text' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

/*
 * Section 6.6.3, fo:character, of the XSL 1.0 Recommendation states:
 *
 *   When the result tree is interpreted as a tree of formatting
 *   objects, a character in the result tree is treated as if it were
 *   an empty element of type fo:character with a character attribute
 *   equal to the Unicode representation of the character.
 *
 * This "unofficial" formatting object represents a sequence of
 * characters.  It exists as a convenience mechanism to save having to
 * devolve every run of text into separate FoCharacter objects.
 *
 * Since the characters in the run of text all have the same
 * properties, using one FoText object instead of multiple FoCharacter
 * objects reduces the number of Pango attributes that need to be
 * created and managed.
 *
 * Also, since the characters in the run of text are not explicitly
 * marked up as fo:character FOs, all of the non-inherited properties
 * of fo:character have their default values.  Since the default
 * values are the "do-nothing" values, the non-inherited properties do
 * not need to be handled by the FoText object.
 *
 * The inherited properties of fo:character that do need to be handled
 * by FoText are:
 *
 *   color
 *   country
 *   font-family
 *   font-selection-strategy
 *   font-size
 *   font-size-adjust
 *   font-stretch
 *   font-style
 *   font-variant
 *   font-weight
 *   glyph-orientation-horizontal
 *   glyph-orientation-vertical
 *   hyphenate
 *   hyphenation-character
 *   hyphenation-push-character
 *   hyphenation-push-character-count
 *   hyphenation-remain-character-count
 *   language
 *   letter-spacing
 *   line-height
 *   score-spaces
 *   script
 *   text-decoration
 *   text-shadow
 *   visibility
 *   word-spacing
 */
 
#include "fo-utils.h"
#include "fo/fo-fo.h"
#include "fo/fo-fo-private.h"
#include "fo-inline-fo.h"
#include "fo-text.h"
#include "property/fo-property-color.h"
#include "property/fo-property-font-family.h"
#include "property/fo-property-font-size.h"
#include "property/fo-property-font-stretch.h"
#include "property/fo-property-font-style.h"
#include "property/fo-property-font-variant.h"
#include "property/fo-property-font-weight.h"
#include "property/fo-property-score-spaces.h"

enum {
  PROP_0,
  PROP_COLOR,
  PROP_FONT_FAMILY,
  PROP_FONT_SIZE,
  PROP_FONT_STRETCH,
  PROP_FONT_STYLE,
  PROP_FONT_VARIANT,
  PROP_FONT_WEIGHT,
  PROP_SCORE_SPACES,
  PROP_VALUE,
  PROP_WHITESPACE_ONLY
};

struct _FoText
{
  FoFo parent_instance;

  FoProperty *color;
  FoProperty *font_family;
  FoProperty *font_size;
  FoProperty *font_stretch;
  FoProperty *font_style;
  FoProperty *font_variant;
  FoProperty *font_weight;
  FoProperty *score_spaces;
  GString *value;
  gboolean whitespace_only;
};

struct _FoTextClass
{
  FoFoClass parent_class;
  
};

static void fo_text_class_init  (FoTextClass *klass);
static void fo_text_inline_fo_init (FoInlineFoIface *iface);
static void fo_text_set_property (GObject         *object,
                                  guint            prop_id,
                                  const GValue    *value,
                                  GParamSpec      *pspec);
static void fo_text_get_property   (GObject         *object,
                                       guint            prop_id,
                                       GValue          *value,
                                       GParamSpec      *pspec);
static gboolean fo_text_resolve_property_attributes (FoNode  *fo_node,
						     gpointer data);

static void fo_text_finalize    (GObject           *object);
static void fo_text_validate    (FoFo      *fo,
				 FoContext *current_context,
				 FoContext *parent_context,
				 GError   **error);
static void fo_text_update_from_context (FoFo *fo,
					 FoContext *context);
static void fo_text_debug_dump (FoObject *object, gint depth);
static void fo_text_get_text_attr_list (FoFo *fo_inline_fo,
					FoDoc   *fo_doc,
					GString *text,
					GList **attr_glist,
					guint debug_level);
static gpointer parent_class;

GType
fo_text_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoTextClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_text_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoText),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      static const GInterfaceInfo fo_inline_fo_info =
      {
	(GInterfaceInitFunc) fo_text_inline_fo_init,	 /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_FO,
                                            "FoText",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &fo_inline_fo_info);
    }
  
  return object_type;
}

/**
 * fo_text_class_init:
 * @klass: FoTextClass object to initialise
 * 
 * Implements GClassInitFunc for FoTextClass
 **/
static void
fo_text_class_init (FoTextClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoFoClass *fo_fo_class = FO_FO_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_text_finalize;

  object_class->set_property = fo_text_set_property;
  object_class->get_property = fo_text_get_property;

  FO_OBJECT_CLASS (klass)->debug_dump = fo_text_debug_dump;

  fo_fo_class->update_from_context = fo_text_update_from_context;
  fo_fo_class->resolve_property_attributes =
    fo_text_resolve_property_attributes;
  fo_fo_class->validate2 = fo_text_validate;

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
     PROP_SCORE_SPACES,
     g_param_spec_object ("score-spaces",
			  _("Score Spaces"),
			  _("Score Spaces property"),
			  FO_TYPE_PROPERTY,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_VALUE,
     g_param_spec_string ("value",
			  _("String value"),
			  _("String value property"),
			  NULL,
			  G_PARAM_READABLE));
  g_object_class_install_property
    (object_class,
     PROP_WHITESPACE_ONLY,
     g_param_spec_boolean ("whitespace-only",
			   _("Contains only whitespace characters"),
			   _("Whether or not the text object contains only whitespace characters"),
			   FALSE,
			   G_PARAM_READABLE));

}

/**
 * fo_text_inline_fo_init:
 * @iface: FoInlineFoIFace structure for this class
 * 
 * Initialize FoInlineFoIface interface for this class
 **/
void
fo_text_inline_fo_init (FoInlineFoIface *iface)
{
  iface->get_text_attr_list = fo_text_get_text_attr_list;
}

/**
 * fo_text_finalize:
 * @object: FoText object to finalize
 * 
 * Implements GObjectFinalizeFunc for FoText
 **/
void
fo_text_finalize (GObject *object)
{
  FoText *fo_text;

  fo_text = FO_TEXT (object);
  g_string_free (fo_text->value, TRUE);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_text_set_property:
 * @object:  GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for FoText
 **/
void
fo_text_set_property (GObject         *object,
		      guint            prop_id,
		      const GValue    *value,
		      GParamSpec      *pspec)
{
  FoFo *fo_text;

  fo_text = FO_FO (object);

  switch (prop_id)
    {
    case PROP_COLOR:
      fo_text_set_color (fo_text, g_value_get_object (value));
      break;
    case PROP_FONT_FAMILY:
      fo_text_set_font_family (fo_text, g_value_get_object (value));
      break;
    case PROP_FONT_SIZE:
      fo_text_set_font_size (fo_text, g_value_get_object (value));
      break;
    case PROP_FONT_STRETCH:
      fo_text_set_font_stretch (fo_text, g_value_get_object (value));
      break;
    case PROP_FONT_STYLE:
      fo_text_set_font_style (fo_text, g_value_get_object (value));
      break;
    case PROP_FONT_VARIANT:
      fo_text_set_font_variant (fo_text, g_value_get_object (value));
      break;
    case PROP_FONT_WEIGHT:
      fo_text_set_font_weight (fo_text, g_value_get_object (value));
      break;
    case PROP_VALUE:
      fo_text_set_value (fo_text, g_value_get_string (value));
      break;
    case PROP_WHITESPACE_ONLY:
      /* fall through, since can't set whitespace-only property */
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_text_get_property:
 * @object:  GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for FoText
 **/
void
fo_text_get_property (GObject         *object,
		      guint            prop_id,
		      GValue          *value,
		      GParamSpec      *pspec)
{
  FoFo *fo_text;

  fo_text = FO_FO (object);

  switch (prop_id)
    {
    case PROP_COLOR:
      g_value_set_object (value, G_OBJECT (fo_text_get_color (fo_text)));
      break;
    case PROP_FONT_FAMILY:
      g_value_set_object (value, G_OBJECT (fo_text_get_font_family (fo_text)));
      break;
    case PROP_FONT_SIZE:
      g_value_set_object (value, G_OBJECT (fo_text_get_font_size (fo_text)));
      break;
    case PROP_FONT_STRETCH:
      g_value_set_object (value, G_OBJECT (fo_text_get_font_stretch (fo_text)));
      break;
    case PROP_FONT_STYLE:
      g_value_set_object (value, G_OBJECT (fo_text_get_font_style (fo_text)));
      break;
    case PROP_FONT_VARIANT:
      g_value_set_object (value, G_OBJECT (fo_text_get_font_variant (fo_text)));
      break;
    case PROP_FONT_WEIGHT:
      g_value_set_object (value, G_OBJECT (fo_text_get_font_weight (fo_text)));
      break;
    case PROP_VALUE:
      g_value_set_string (value, fo_text_get_value (fo_text));
      break;
    case PROP_WHITESPACE_ONLY:
      g_value_set_boolean (value, fo_text_get_whitespace_only (fo_text));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_text_new:
 * 
 * Creates a new #FoText initialized to default value.
 * 
 * Return value: the new #FoText
 **/
FoFo*
fo_text_new (void)
{
  return FO_FO (g_object_new (fo_text_get_type (), NULL));
}

/**
 * fo_text_resolve_property_attributes:
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
fo_text_resolve_property_attributes (FoNode     *fo_node,
				     gpointer    data)
{
  FoPropertyResolveContext *prop_context =
    (FoPropertyResolveContext *) data;
  GError *error = NULL;
  gboolean continue_after_error = prop_context->continue_after_error;

  g_return_val_if_fail (FO_IS_TEXT (fo_node), TRUE);
  g_return_val_if_fail (prop_context != NULL, TRUE);

  /* FoText is an convenience for not creating lots of FoCharacter
     FOs.  It doesn't have a context of its own, since all its
     property values are those of its containing FO.  So there is no
     current context of the FoText. */
  fo_fo_validate (FO_FO (fo_node),
		  NULL,
		  fo_fo_get_context (FO_FO (fo_node_parent (fo_node))),
		  &error);

  if (error != NULL)
    {
      fo_object_maybe_propagate_error (FO_OBJECT (fo_node),
				       prop_context->error,
				       error,
				       continue_after_error);
      return TRUE;
    }

  fo_fo_set_context (FO_FO (fo_node),
		     fo_fo_get_context (FO_FO (fo_node_parent (fo_node))));

  return FALSE;
}

/**
 * fo_text_validate:
 * @fo:              #FoInline object to validate.
 * @current_context: #FoContext associated with current object.
 * @parent_context:  #FoContext associated with parent FO.
 * @error:           Information about any error that has occurred.
 * 
 * Validate and possibly update interrelated property values in
 * @current_context, then update @fo property values.  Set @error if
 * an error occurred.
 **/
void
fo_text_validate (FoFo      *fo,
		  FoContext *current_context,
		  FoContext *parent_context,
		  GError   **error)
{
  FoText *fo_text;

  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TEXT (fo));
  g_return_if_fail ((current_context == NULL) ||
		    FO_IS_CONTEXT (current_context));
  g_return_if_fail (FO_IS_CONTEXT (parent_context));
  g_return_if_fail (error == NULL || *error == NULL);

  fo_text = FO_TEXT (fo);

  fo_fo_update_from_context (fo, parent_context);

  FoEnumEnum linefeed_treatment =
    fo_enum_get_value (fo_property_get_value (fo_context_get_linefeed_treatment (parent_context)));

  if (linefeed_treatment != FO_ENUM_ENUM_PRESERVE)
    {
      gchar **strings = g_strsplit_set (fo_text_get_value (fo),
					"\n",
					-1);
      gchar *separator = NULL;

      switch (linefeed_treatment)
	{
	case FO_ENUM_ENUM_IGNORE:
	  separator = NULL;
	  break;
	case FO_ENUM_ENUM_TREAT_AS_SPACE:
	  separator = " ";
	  break;
	case FO_ENUM_ENUM_TREAT_AS_ZERO_WIDTH_SPACE:
	  /* ZERO WIDTH SPACE = U+200B */
	  separator = "\xe2\x80\x8b";
	  break;
	default:
	  g_assert_not_reached ();
	}

      gchar *new_value = g_strjoinv (separator,
				     strings);

      fo_text_set_value (fo,
			 new_value);
      g_strfreev (strings);
      g_free (new_value);
    }
}

/**
 * fo_text_update_from_context:
 * @fo:      The #FoFo object
 * @context: The #FoContext object from which to update the properties of @fo
 * 
 * Sets the properties of @fo to the corresponding property values in @context
 **/
void
fo_text_update_from_context (FoFo      *fo,
			     FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_TEXT (fo));

  fo_text_set_color (fo,
			  fo_context_get_color (context));
  fo_text_set_font_family (fo,
			  fo_context_get_font_family (context));
  fo_text_set_font_size (fo,
			  fo_context_get_font_size (context));
  fo_text_set_font_stretch (fo,
			  fo_context_get_font_stretch (context));
  fo_text_set_font_style (fo,
			  fo_context_get_font_style (context));
  fo_text_set_font_variant (fo,
			  fo_context_get_font_variant (context));
  fo_text_set_font_weight (fo,
			  fo_context_get_font_weight (context));
  fo_text_set_score_spaces (fo,
			  fo_context_get_score_spaces (context));
}

void
fo_text_debug_dump (FoObject *object, gint depth)
{
  gchar *indent = g_strnfill (depth * 2, ' ');
  gchar *object_sprintf;
  gchar text[45];
  FoText *fo_text;

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_TEXT (object));

  fo_text = FO_TEXT (object);

  object_sprintf = fo_object_debug_sprintf (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 object_sprintf);

  g_free (object_sprintf);

  fo_object_debug_dump (fo_text->color, depth + 2);
  fo_object_debug_dump (fo_text->font_family, depth + 2);
  fo_object_debug_dump (fo_text->font_size, depth + 2);
  fo_object_debug_dump (fo_text->font_stretch, depth + 2);
  fo_object_debug_dump (fo_text->font_style, depth + 2);
  fo_object_debug_dump (fo_text->font_variant, depth + 2);
  fo_object_debug_dump (fo_text->font_weight, depth + 2);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s    whitespace-only: %s",
	 indent,
	 FO_TEXT (object)->whitespace_only ? "TRUE" : "FALSE");

  FO_FO_GET_CLASS (object)->debug_dump_properties (FO_FO (object),
						   depth + 2);

  g_utf8_strncpy (text,
		  fo_text->value->str,
		  g_utf8_strlen (fo_text->value->str, 40));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%s%s",
	 indent,
	 text);

  g_free (indent);
}

/**
 * fo_text_set_color:
 * @fo_fo: The @FoFo object
 * @new_color: The new "color" property value
 * 
 * Sets the #color property of @text to @new_color
 **/
void
fo_text_set_color (FoFo *fo_fo,
		         FoProperty *new_color)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_if_fail (fo_text != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_text));
  g_return_if_fail (FO_IS_PROPERTY_COLOR (new_color));

  if (new_color)
    g_object_ref (G_OBJECT (new_color));
  if (fo_text->color)
    g_object_unref (G_OBJECT (fo_text->color));
  fo_text->color = new_color;
  /*g_object_notify (G_OBJECT (fo_text), "color");*/
}

/**
 * fo_text_get_color:
 * @fo_fo: The @FoFo object
 *
 * Gets the #color property of @text
 *
 * Return value: The "color" property value
**/
FoProperty*
fo_text_get_color (FoFo *fo_fo)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_val_if_fail (fo_text != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_text), NULL);

  return fo_text->color;
}

/**
 * fo_text_set_font_family:
 * @fo_fo: The @FoFo object
 * @new_font_family: The new "font-family" property value
 * 
 * Sets the #font-family property of @text to @new_font_family
 **/
void
fo_text_set_font_family (FoFo *fo_fo,
		         FoProperty *new_font_family)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_if_fail (fo_text != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_text));
  g_return_if_fail (FO_IS_PROPERTY_FONT_FAMILY (new_font_family));

  if (new_font_family)
    g_object_ref (G_OBJECT (new_font_family));
  if (fo_text->font_family)
    g_object_unref (G_OBJECT (fo_text->font_family));
  fo_text->font_family = new_font_family;
  /*g_object_notify (G_OBJECT (fo_text), "font-family");*/
}

/**
 * fo_text_get_font_family:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-family property of @text
 *
 * Return value: The "font-family" property value
**/
FoProperty*
fo_text_get_font_family (FoFo *fo_fo)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_val_if_fail (fo_text != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_text), NULL);

  return fo_text->font_family;
}

/**
 * fo_text_set_font_size:
 * @fo_fo: The @FoFo object
 * @new_font_size: The new "font-size" property value
 * 
 * Sets the #font-size property of @text to @new_font_size
 **/
void
fo_text_set_font_size (FoFo *fo_fo,
		         FoProperty *new_font_size)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_if_fail (fo_text != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_text));
  g_return_if_fail (FO_IS_PROPERTY_FONT_SIZE (new_font_size));

  if (new_font_size)
    g_object_ref (G_OBJECT (new_font_size));
  if (fo_text->font_size)
    g_object_unref (G_OBJECT (fo_text->font_size));
  fo_text->font_size = new_font_size;
  /*g_object_notify (G_OBJECT (fo_text), "font-size");*/
}

/**
 * fo_text_get_font_size:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-size property of @text
 *
 * Return value: The "font-size" property value
**/
FoProperty*
fo_text_get_font_size (FoFo *fo_fo)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_val_if_fail (fo_text != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_text), NULL);

  return fo_text->font_size;
}

/**
 * fo_text_set_font_stretch:
 * @fo_fo: The @FoFo object
 * @new_font_stretch: The new "font-stretch" property value
 * 
 * Sets the #font-stretch property of @text to @new_font_stretch
 **/
void
fo_text_set_font_stretch (FoFo *fo_fo,
		         FoProperty *new_font_stretch)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_if_fail (fo_text != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_text));
  g_return_if_fail (FO_IS_PROPERTY_FONT_STRETCH (new_font_stretch));

  if (new_font_stretch)
    g_object_ref (G_OBJECT (new_font_stretch));
  if (fo_text->font_stretch)
    g_object_unref (G_OBJECT (fo_text->font_stretch));
  fo_text->font_stretch = new_font_stretch;
  /*g_object_notify (G_OBJECT (fo_text), "font-stretch");*/
}

/**
 * fo_text_get_font_stretch:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-stretch property of @text
 *
 * Return value: The "font-stretch" property value
**/
FoProperty*
fo_text_get_font_stretch (FoFo *fo_fo)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_val_if_fail (fo_text != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_text), NULL);

  return fo_text->font_stretch;
}

/**
 * fo_text_set_font_style:
 * @fo_fo: The @FoFo object
 * @new_font_style: The new "font-style" property value
 * 
 * Sets the #font-style property of @text to @new_font_style
 **/
void
fo_text_set_font_style (FoFo *fo_fo,
		         FoProperty *new_font_style)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_if_fail (fo_text != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_text));
  g_return_if_fail (FO_IS_PROPERTY_FONT_STYLE (new_font_style));

  if (new_font_style)
    g_object_ref (G_OBJECT (new_font_style));
  if (fo_text->font_style)
    g_object_unref (G_OBJECT (fo_text->font_style));
  fo_text->font_style = new_font_style;
  /*g_object_notify (G_OBJECT (fo_text), "font-style");*/
}

/**
 * fo_text_get_font_style:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-style property of @text
 *
 * Return value: The "font-style" property value
**/
FoProperty*
fo_text_get_font_style (FoFo *fo_fo)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_val_if_fail (fo_text != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_text), NULL);

  return fo_text->font_style;
}

/**
 * fo_text_set_font_variant:
 * @fo_fo: The @FoFo object
 * @new_font_variant: The new "font-variant" property value
 * 
 * Sets the #font-variant property of @text to @new_font_variant
 **/
void
fo_text_set_font_variant (FoFo *fo_fo,
		         FoProperty *new_font_variant)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_if_fail (fo_text != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_text));
  g_return_if_fail (FO_IS_PROPERTY_FONT_VARIANT (new_font_variant));

  if (new_font_variant)
    g_object_ref (G_OBJECT (new_font_variant));
  if (fo_text->font_variant)
    g_object_unref (G_OBJECT (fo_text->font_variant));
  fo_text->font_variant = new_font_variant;
  /*g_object_notify (G_OBJECT (fo_text), "font-variant");*/
}

/**
 * fo_text_get_font_variant:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-variant property of @text
 *
 * Return value: The "font-variant" property value
**/
FoProperty*
fo_text_get_font_variant (FoFo *fo_fo)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_val_if_fail (fo_text != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_text), NULL);

  return fo_text->font_variant;
}

/**
 * fo_text_set_font_weight:
 * @fo_fo: The @FoFo object
 * @new_font_weight: The new "font-weight" property value
 * 
 * Sets the #font-weight property of @text to @new_font_weight
 **/
void
fo_text_set_font_weight (FoFo *fo_fo,
		         FoProperty *new_font_weight)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_if_fail (fo_text != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_text));
  g_return_if_fail (FO_IS_PROPERTY_FONT_WEIGHT (new_font_weight));

  if (new_font_weight)
    g_object_ref (G_OBJECT (new_font_weight));
  if (fo_text->font_weight)
    g_object_unref (G_OBJECT (fo_text->font_weight));
  fo_text->font_weight = new_font_weight;
  /*g_object_notify (G_OBJECT (fo_text), "font-weight");*/
}

/**
 * fo_text_get_font_weight:
 * @fo_fo: The @FoFo object
 *
 * Gets the #font-weight property of @text
 *
 * Return value: The "font-weight" property value
**/
FoProperty*
fo_text_get_font_weight (FoFo *fo_fo)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_val_if_fail (fo_text != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_text), NULL);

  return fo_text->font_weight;
}

/**
 * fo_text_set_score_spaces:
 * @fo_fo: The @FoFo object
 * @new_score_spaces: The new "score-spaces" property value
 * 
 * Sets the #score-spaces property of @text to @new_score_spaces
 **/
void
fo_text_set_score_spaces (FoFo *fo_fo,
		         FoProperty *new_score_spaces)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_if_fail (fo_text != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_text));
  g_return_if_fail (FO_IS_PROPERTY_SCORE_SPACES (new_score_spaces));

  if (new_score_spaces)
    g_object_ref (G_OBJECT (new_score_spaces));
  if (fo_text->score_spaces)
    g_object_unref (G_OBJECT (fo_text->score_spaces));
  fo_text->score_spaces = new_score_spaces;
  /*g_object_notify (G_OBJECT (fo_text), "score-spaces");*/
}

/**
 * fo_text_get_score_spaces:
 * @fo_fo: The @FoFo object
 *
 * Gets the #score-spaces property of @text
 *
 * Return value: The "score-spaces" property value
**/
FoProperty*
fo_text_get_score_spaces (FoFo *fo_fo)
{
  FoText *fo_text = (FoText *) fo_fo;

  g_return_val_if_fail (fo_text != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_text), NULL);

  return fo_text->score_spaces;
}

/**
 * fo_text_set_value:
 * @fo_fo: The #FoText object
 * @new_value: The new "value" property value
 * 
 * Sets the #value property of @fo_fo to @new_value
**/
void
fo_text_set_value (FoFo *fo_fo,
		   const gchar* new_value)
{
  FoText *fo_text;
  gboolean whitespace_only;
  guint offset;

  g_return_if_fail (fo_fo != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_fo));

  fo_text = FO_TEXT (fo_fo);

  if (fo_text->value)
    g_string_free (fo_text->value, TRUE);

  fo_text->value = g_string_new (new_value);

  whitespace_only = TRUE;
  for (offset = 0; offset < fo_text->value->len; offset++)
    {
      if (!g_ascii_isspace (fo_text->value->str[offset]))
	{
	  whitespace_only = FALSE;
	  break;
	}
    }

  fo_text->whitespace_only = whitespace_only;
  /*g_object_notify (G_OBJECT (fo_text), "value");*/
}

/**
 * fo_text_get_value:
 * @fo_fo: The #FoText object
 *
 * Gets the "value" property of @fo_text
 *
 * Return value: The "value" property value
**/
const gchar*
fo_text_get_value (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, NULL);
  g_return_val_if_fail (FO_IS_TEXT (fo_fo), NULL);

  return FO_TEXT (fo_fo)->value->str;
}

/**
 * fo_text_get_whitespace_only:
 * @fo_fo: The #FoText object
 *
 * Gets the "whitespace_only" property of @fo_fo
 *
 * Return value: The "whitespace_only" property value
**/
gboolean
fo_text_get_whitespace_only (FoFo *fo_fo)
{
  g_return_val_if_fail (fo_fo != NULL, FALSE);
  g_return_val_if_fail (FO_IS_TEXT (fo_fo), FALSE);

  return FO_TEXT (fo_fo)->whitespace_only;
}

/**
 * fo_text_get_text_attr_list:
 * @fo_inline_fo: The #FoInlineFo object.
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO.
 * @attr_glist:   The list of #PangoAttribute for the inline FO.
 * @debug_level:  Debug level.
 * 
 * Gets the text of the inline FO and its associated list of #PangoAttribute.
 **/
void
fo_text_get_text_attr_list (FoFo    *fo_inline_fo,
			    FoDoc   *fo_doc G_GNUC_UNUSED,
			    GString *text,
			    GList  **attr_glist G_GNUC_UNUSED,
			    guint    debug_level G_GNUC_UNUSED)
{
  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_TEXT (fo_inline_fo));

  FoEnumEnum whitespace_collapse =
    fo_enum_get_value (fo_property_get_value (fo_context_get_white_space_collapse (fo_fo_get_context (fo_inline_fo))));

  if (whitespace_collapse == FO_ENUM_ENUM_TRUE)
    {
      const gchar *string = fo_text_get_value (fo_inline_fo);
      const gchar *p = string;

      while (*p != '\0')
	{
	  if (!(fo_inline_fo_is_non_linefeed_white_space (p) &&
		(fo_inline_fo_is_white_space (g_utf8_find_prev_char (string,
								     p))
		 ||
		 fo_inline_fo_is_linefeed (g_utf8_find_next_char (p,
								  NULL)))))
	    {
	      g_string_append_unichar (text, g_utf8_get_char (p));
	    }
	  p = g_utf8_next_char (p);
	}
    }
  else
    {
      g_string_append (text, fo_text_get_value (fo_inline_fo));
    }
}
