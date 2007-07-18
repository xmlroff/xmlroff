/* Fo
 * fo-libfo-context.c: 'FoLibfoContext' object type
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <string.h>
#include "libfo/fo-utils.h"
#include "libfo/fo-libfo-context.h"
#include "fo-object.h"

GType
fo_enum_format_get_type (void)
{
  static GType etype = 0;
  if (etype == 0)
    {
      static const GEnumValue values[] = {
        { FO_ENUM_FORMAT_UNKNOWN, "FO_ENUM_FORMAT_UNKNOWN", "unknown" },
        { FO_ENUM_FORMAT_AUTO, "FO_ENUM_FORMAT_AUTO", "auto" },
        { FO_ENUM_FORMAT_PDF, "FO_ENUM_FORMAT_PDF", "PDF" },
        { FO_ENUM_FORMAT_POSTSCRIPT, "FO_ENUM_FORMAT_POSTSCRIPT", "PostScript" },
        { FO_ENUM_FORMAT_SVG, "FO_ENUM_FORMAT_SVG", "SVG" },
        { 0, NULL, NULL }
      };
      etype = g_enum_register_static ("FoEnumFormat", values);
    }
  return etype;
}

GType
fo_enum_font_embed_get_type (void)
{
  static GType etype = 0;
  if (etype == 0)
    {
      static const GEnumValue values[] = {
        { FO_ENUM_FONT_EMBED_INVALID, "FO_ENUM_FONT_EMBED_INVALID", "invalid" },
        { FO_ENUM_FONT_EMBED_ALL, "FO_ENUM_FONT_EMBED_ALL", "all" },
        { FO_ENUM_FONT_EMBED_NONBASE, "FO_ENUM_FONT_EMBED_NONBASE", "nonbase" },
        { FO_ENUM_FONT_EMBED_NONE, "FO_ENUM_FONT_EMBED_NONE", "none" },
        { 0, NULL, NULL }
      };
      etype = g_enum_register_static ("FoEnumFontEmbed", values);
    }
  return etype;
}

struct _FoLibfoContext
{
  FoObject parent_instance;

  gboolean        validation;
  FoEnumFormat    format;
  FoEnumFontEmbed font_embed;
  FoWarningFlag   warning_mode;
  gboolean        continue_after_error;
  FoDebugFlag     debug_mode;
};

struct _FoLibfoContextClass
{
  FoObjectClass parent_class;
};

enum {
  PROP_0,
  PROP_XML,
  PROP_XSLT,
  PROP_FO_TREE,
  PROP_AREA_TREE,
  PROP_OUTPUT,
  PROP_FORMAT,
  PROP_FONT_EMBED,
  PROP_VALIDATION,
  PROP_CONTINUE,
  PROP_DEBUG_MODE,
  PROP_WARNING_MODE
};

static void fo_libfo_context_class_init   (FoLibfoContextClass *klass);
static void fo_libfo_context_get_property (GObject         *object,
					   guint            prop_id,
					   GValue          *value,
					   GParamSpec      *pspec);
static void fo_libfo_context_set_property (GObject         *object,
					   guint            prop_id,
					   const GValue    *value,
					   GParamSpec      *pspec);

static gpointer parent_class;

/**
 * fo_libfo_context_get_type:
 * 
 * Register the #FoLibfoContext type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoLibfoContext.
 **/
GType
fo_libfo_context_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLibfoContextClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_libfo_context_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLibfoContext),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoLibfoContext",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_libfo_context_class_init:
 * @klass: #FoLibfoContextClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoLibfoContextClass.
 **/
void
fo_libfo_context_class_init (FoLibfoContextClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->get_property = fo_libfo_context_get_property;
  object_class->set_property = fo_libfo_context_set_property;

  g_object_class_install_property
    (object_class,
     PROP_FORMAT,
     g_param_spec_enum ("format",
			_("Output format"),
			_("Output file format"),
			FO_TYPE_ENUM_FORMAT,
			FO_ENUM_FORMAT_PDF,
			G_PARAM_READWRITE));

  g_object_class_install_property
    (object_class,
     PROP_FORMAT,
     g_param_spec_enum ("font-embed",
			_("Font embed"),
			_("Font embedding mode"),
			FO_TYPE_ENUM_FONT_EMBED,
			FO_ENUM_FONT_EMBED_NONBASE,
			G_PARAM_READWRITE));

  g_object_class_install_property
    (object_class,
     PROP_VALIDATION,
     g_param_spec_boolean ("validation",
			   _("Validation enabled?"),
			   _("Is validation of the input XML source enabled?"),
			   TRUE,
			   G_PARAM_READWRITE));

  g_object_class_install_property
    (object_class,
     PROP_VALIDATION,
     g_param_spec_boolean ("continue",
			   _("Continue after error?"),
			   _("Continue formatting after any formatting errors?"),
			   FALSE,
			   G_PARAM_READWRITE));

  g_object_class_install_property
    (object_class,
     PROP_DEBUG_MODE,
     g_param_spec_int ("debug-mode",
		       _("Debug mode"),
		       _("Debugging mode"),
		       0,
		       FO_DEBUG_MAX,
		       0,
		       G_PARAM_READWRITE));

  g_object_class_install_property
    (object_class,
     PROP_WARNING_MODE,
     g_param_spec_int ("warning-mode",
		       _("Warning mode"),
		       _("Warning mode"),
		       0,
		       FO_WARNING_MAX,
		       0,
		       G_PARAM_READWRITE));
}

/**
 * fo_libfo_context_get_property:
 * @object:  #GObject whose property will be retreived
 * @prop_id: Property ID assigned when property registered
 * @value:   #GValue to set with property value
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectGetPropertyFunc for #FoLibfoContext
 **/
void
fo_libfo_context_get_property (GObject        *object,
			       guint           param_id,
			       GValue         *value,
			       GParamSpec     *pspec)
{
  FoLibfoContext *libfo_context = FO_LIBFO_CONTEXT (object);
  
  switch (param_id)
    {
    case PROP_FORMAT:
      g_value_set_enum (value, libfo_context->format);
      break;
    case PROP_FONT_EMBED:
      g_value_set_enum (value, libfo_context->font_embed);
      break;
    case PROP_VALIDATION:
      g_value_set_boolean (value, libfo_context->validation);
      break;
    case PROP_CONTINUE:
      g_value_set_boolean (value, libfo_context->continue_after_error);
      break;
    case PROP_DEBUG_MODE:
      g_value_set_int (value, libfo_context->debug_mode);
      break;
    case PROP_WARNING_MODE:
      g_value_set_int (value, libfo_context->warning_mode);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_libfo_context_set_property:
 * @object:  #GObject whose property will be set
 * @prop_id: Property ID assigned when property registered
 * @value:   New value for property
 * @pspec:   Parameter specification for this property type
 * 
 * Implements #GObjectSetPropertyFunc for #FoLibfoContext
 **/
void
fo_libfo_context_set_property (GObject      *object,
			       guint         param_id,
			       const GValue *value,
			       GParamSpec   *pspec)
{
  FoLibfoContext *fo_libfo_context;

  fo_libfo_context = FO_LIBFO_CONTEXT (object);

  switch (param_id)
    {
    case PROP_FORMAT:
      fo_libfo_context_set_format (fo_libfo_context,
				   g_value_get_enum (value));
      break;
    case PROP_FONT_EMBED:
      fo_libfo_context_set_font_embed (fo_libfo_context,
				       g_value_get_enum (value));
      break;
    case PROP_VALIDATION:
      fo_libfo_context_set_validation (fo_libfo_context,
				       g_value_get_boolean (value));
      break;
    case PROP_CONTINUE:
      fo_libfo_context_set_continue_after_error (fo_libfo_context,
						 g_value_get_boolean (value));
      break;
    case PROP_DEBUG_MODE:
      fo_libfo_context_set_debug_mode (fo_libfo_context,
				       g_value_get_int (value));
      break;
    case PROP_WARNING_MODE:
      fo_libfo_context_set_warning_mode (fo_libfo_context,
					 g_value_get_int (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, param_id, pspec);
      break;
    }
}

/**
 * fo_libfo_context_new:
 * 
 * Creates a new #FoLibfoContext initialized to default value.
 * 
 * Return value: The new #FoLibfoContext.
 **/
FoLibfoContext *
fo_libfo_context_new (void)
{
  FoLibfoContext* libfo_context;

  libfo_context =
    g_object_new (fo_libfo_context_get_type (),
		  NULL);

  return libfo_context;
}

/**
 * fo_libfo_context_get_format:
 * @libfo_context: #FoLibfoContext.
 * 
 * Get the 'format' property of @libfo_context.
 *
 * Return value: Value of the 'format' property of @libfo_context.
 **/
FoEnumFormat
fo_libfo_context_get_format (FoLibfoContext *libfo_context)
{
  g_return_val_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context),
			FO_ENUM_FORMAT_UNKNOWN);

  return libfo_context->format;
}


/**
 * fo_libfo_context_set_format:
 * @libfo_context: #FoLibfoContext.
 * @format:        New 'format' value for @libfo_context.
 * 
 * Set the 'format' property of @libfo_context.
 **/
void
fo_libfo_context_set_format (FoLibfoContext *libfo_context,
			     FoEnumFormat    format)
{
  g_return_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context));
  g_return_if_fail (g_enum_get_value (g_type_class_peek (FO_TYPE_ENUM_FORMAT),
				      format) != NULL);

  libfo_context->format = format;
}

/**
 * fo_libfo_context_get_font_embed:
 * @libfo_context: #FoLibfoContext.
 * 
 * Get the 'font-embed' property of @libfo_context.
 *
 * Return value: Value of the 'font-embed' property of @libfo_context.
 **/
FoEnumFontEmbed
fo_libfo_context_get_font_embed (FoLibfoContext *libfo_context)
{
  g_return_val_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context),
			FO_ENUM_FONT_EMBED_INVALID);

  return libfo_context->font_embed;
}


/**
 * fo_libfo_context_set_font_embed:
 * @libfo_context: #FoLibfoContext.
 * @font_embed:    New 'font-embed' value for @libfo_context.
 * 
 * Set the 'font-embed' property of @libfo_context.
 **/
void
fo_libfo_context_set_font_embed (FoLibfoContext *libfo_context,
				 FoEnumFontEmbed font_embed)
{
  g_return_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context));
  g_return_if_fail (g_enum_get_value (g_type_class_peek (FO_TYPE_ENUM_FONT_EMBED),
				      font_embed) != NULL);

  libfo_context->font_embed = font_embed;
}

/**
 * fo_libfo_context_get_validation:
 * @libfo_context: #FoLibfoContext.
 * 
 * Get the 'validation' property of @libfo_context.
 *
 * Return value: Value of the 'validation' property of @libfo_context.
 **/
gboolean
fo_libfo_context_get_validation (FoLibfoContext *libfo_context)
{
  g_return_val_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context), FALSE);

  return libfo_context->validation;
}

/**
 * fo_libfo_context_set_validation:
 * @libfo_context: #FoLibfoContext.
 * @validation:    New 'validation' value for @libfo_context.
 * 
 * Set the 'validation' property of @libfo_context.
 **/
void
fo_libfo_context_set_validation (FoLibfoContext *libfo_context,
				 gboolean        validation)
{
  g_return_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context));

  libfo_context->validation = validation;
}

/**
 * fo_libfo_context_get_continue_after_error:
 * @libfo_context: #FoLibfoContext.
 * 
 * Get the 'continue' property of @libfo_context.
 *
 * Return value: Value of the 'continue' property of @libfo_context.
 **/
gboolean
fo_libfo_context_get_continue_after_error (FoLibfoContext *libfo_context)
{
  g_return_val_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context), FALSE);

  return libfo_context->continue_after_error;
}

/**
 * fo_libfo_context_set_continue_after_error:
 * @libfo_context:     #FoLibfoContext.
 * @continue_after_error: New 'continue' value for @libfo_context.
 * 
 * Set the 'continue' property of @libfo_context.
 **/
void
fo_libfo_context_set_continue_after_error (FoLibfoContext *libfo_context,
					   gboolean        continue_after_error)
{
  g_return_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context));

  libfo_context->continue_after_error = continue_after_error;
}

/**
 * fo_libfo_context_get_warning_mode:
 * @libfo_context: #FoLibfoContext.
 * 
 * Get the 'warning_mode' property of @libfo_context.
 *
 * Return value: Value of the 'warning_mode' property of @libfo_context.
 **/
FoWarningFlag
fo_libfo_context_get_warning_mode (FoLibfoContext *libfo_context)
{
  g_return_val_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context), 0);

  return libfo_context->warning_mode;
}

/**
 * fo_libfo_context_set_warning_mode:
 * @libfo_context: #FoLibfoContext.
 * @warning_mode:    New 'warning-mode' value for @libfo_context.
 * 
 * Set the 'warning-mode' property of @libfo_context.
 **/
void
fo_libfo_context_set_warning_mode (FoLibfoContext *libfo_context,
				   FoWarningFlag   warning_mode)
{
  g_return_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context));
  g_return_if_fail (warning_mode <= FO_WARNING_MAX);

  libfo_context->warning_mode = warning_mode;
}

/**
 * fo_libfo_context_get_debug_mode:
 * @libfo_context: #FoLibfoContext.
 * 
 * Get the 'debug_mode' property of @libfo_context.
 *
 * Return value: Value of the 'debug_mode' property of @libfo_context.
 **/
FoDebugFlag
fo_libfo_context_get_debug_mode (FoLibfoContext *libfo_context)
{
  g_return_val_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context), 0);

  return libfo_context->debug_mode;
}

/**
 * fo_libfo_context_set_debug_mode:
 * @libfo_context: #FoLibfoContext.
 * @debug_mode:    New 'debug-mode' value for @libfo_context.
 * 
 * Set the 'debug-mode' property of @libfo_context.
 **/
void
fo_libfo_context_set_debug_mode (FoLibfoContext *libfo_context,
				 FoDebugFlag     debug_mode)
{
  g_return_if_fail (FO_IS_LIBFO_CONTEXT (libfo_context));

  libfo_context->debug_mode = debug_mode;
}
