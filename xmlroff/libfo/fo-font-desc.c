/* Fo
 * fo-font-desc.c: Object type for a font description
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-font-desc.c,v 1.6 2006/03/08 00:22:30 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "libfo/fo-utils.h"
#include "fo-object.h"
#include "fo-font-desc-private.h"
#include "fo-libfo-context.h"

const char *fo_font_desc_error_messages [] = {
  N_("FoFontDesc error")
};

struct _FoFontDesc
{
  FoObject      parent_instance;

  const PangoFontDescription *font_desc;
};

struct _FoFontDescClass
{
  FoObjectClass parent_class;
};

static void fo_font_desc_class_init (FoFontDescClass *klass);
static void fo_font_desc_finalize   (GObject        *object);

static gpointer parent_class;

/**
 * fo_font_desc_error_quark:
 * 
 * Get the error quark for #FoFontDesc.
 *
 * If the quark does not yet exist, create it.
 * 
 * Return value: #GQuark associated with #FoFontDesc errors.
 **/
GQuark
fo_font_desc_error_quark (void)
{
  static GQuark quark = 0;
  if (quark == 0)
    quark = g_quark_from_static_string ("FoFontDesc error");
  return quark;
}

/**
 * fo_font_desc_get_type:
 * 
 * Register the #FoFontDesc type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoFontDesc.
 **/
GType
fo_font_desc_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoFontDescClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_font_desc_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoFontDesc),
        0,              /* n_preallocs */
	(GInstanceInitFunc) NULL,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoFontDesc",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_font_desc_class_init:
 * @klass: #FoFontDesc object to initialise.
 * 
 * Implements #GClassInitFunc for #FoFontDescClass.
 **/
void
fo_font_desc_class_init (FoFontDescClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_font_desc_finalize;
}

/**
 * fo_font_desc_finalize:
 * @object: #FoFontDesc object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoFontDesc.
 **/
void
fo_font_desc_finalize (GObject *object)
{
  FoFontDesc *fo_font_desc;

  fo_font_desc = FO_FONT_DESC (object);

  if (fo_font_desc->font_desc != NULL)
    {
      pango_font_description_free (fo_font_desc->font_desc);
      fo_font_desc->font_desc = NULL;
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_font_desc_new:
 * 
 * Creates a new #FoFontDesc.
 * 
 * Return value: the newly created #FoFontDesc.
 **/
FoFontDesc *
fo_font_desc_new (void)
{
  FoFontDesc* fo_font_desc;

  fo_font_desc =
    g_object_new (fo_font_desc_get_type (),
		  NULL);

  return fo_font_desc;
}

FoFontDesc *
fo_font_desc_copy (const FoFontDesc *font_desc)
{
  FoFontDesc *new_font_desc = NULL;

  g_return_val_if_fail (FO_IS_FONT_DESC (font_desc), NULL);

  new_font_desc = fo_font_desc_new ();

  new_font_desc->font_desc =
    pango_font_description_copy (font_desc->font_desc);

  return new_font_desc;
}

void
fo_font_desc_set_family (FoFontDesc *font_desc,
			 const char *family)
{
  g_return_if_fail (FO_IS_FONT_DESC (font_desc));

  pango_font_description_set_family (font_desc->font_desc,
				     family);
}

void
fo_font_desc_set_size (FoFontDesc *font_desc,
		       gfloat      size)
{
  g_return_if_fail (FO_IS_FONT_DESC (font_desc));

  pango_font_description_set_size (font_desc->font_desc,
				   size * PANGO_SCALE);
}

static PangoStyle
fo_font_style_to_pango_style (FoEnumFontStyle font_style)
{
  PangoStyle pango_font_style = PANGO_STYLE_NORMAL;

  /* Pango doesn't support 'backslant' styles so leave 'backslant' 
   * as 'normal'
   */
  if (font_style == FO_ENUM_FONT_STYLE_ITALIC)
    {
      pango_font_style = PANGO_STYLE_ITALIC;
    }
  else if (font_style == FO_ENUM_FONT_STYLE_OBLIQUE)
    {
      pango_font_style = PANGO_STYLE_OBLIQUE;
    }

  return pango_font_style;
}

void
fo_font_desc_set_style (FoFontDesc      *font_desc,
			FoEnumFontStyle  style)
{
  g_return_if_fail (FO_IS_FONT_DESC (font_desc));

  pango_font_description_set_style (font_desc->font_desc,
				    fo_font_style_to_pango_style (style));
}

#define fo_font_stretch_to_pango_stretch(font_stretch) (font_stretch)

void
fo_font_desc_set_stretch (FoFontDesc        *font_desc,
			  FoEnumFontStretch  stretch)
{
  g_return_if_fail (FO_IS_FONT_DESC (font_desc));

  pango_font_description_set_stretch (font_desc->font_desc,
				      fo_font_stretch_to_pango_stretch (stretch));
}

#define fo_font_variant_to_pango_variant(font_variant) (font_variant)

void
fo_font_desc_set_variant (FoFontDesc        *font_desc,
			  FoEnumFontVariant  variant)
{
  g_return_if_fail (FO_IS_FONT_DESC (font_desc));

  pango_font_description_set_variant (font_desc->font_desc,
				      fo_font_variant_to_pango_variant (variant));
}

void
fo_font_desc_set_weight (FoFontDesc *font_desc,
			 gint      weight)
{
  g_return_if_fail (FO_IS_FONT_DESC (font_desc));

  pango_font_description_set_weight (font_desc->font_desc,
				     weight);
}

/**
 * fo_font_desc_get_font_description:
 * @fo_font_desc: #FoFontDesc.
 * 
 * Get the #PangoFontDescription in @fo_font_desc.
 * 
 * Return value: #PangoFontDescription in @fo_font_desc.
 **/
PangoFontDescription *
fo_font_desc_get_font_description (const FoFontDesc *fo_font_desc)
{
  g_return_val_if_fail (fo_font_desc != NULL, NULL);

  return fo_font_desc->font_desc;
}

/**
 * fo_font_desc_set_font_description:
 * @fo_font_desc: #FoFontDesc.
 * @font_description: #PangoFontDescription.
 * 
 * Set the language in @fo_font_desc.
 **/
void
fo_font_desc_set_font_description (FoFontDesc *fo_font_desc,
				   const PangoFontDescription *desc)
{
  g_return_if_fail (fo_font_desc != NULL);
  g_return_if_fail (desc != NULL);

  fo_font_desc->font_desc = desc;
}
