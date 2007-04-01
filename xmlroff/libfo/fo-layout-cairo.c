/* Fo
 * fo-layout-cairo.c: Object type for PangoCairoLayout
 *
 * Copyright (C) 2003-2006 Sun Microsystems
 *
 * $Id: fo-layout-cairo.c,v 1.1 2006/03/07 23:35:29 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include <pango/pango.h>
#include <pangoxsl/pango-xsl-attributes.h>
#include "libfo/fo-utils.h"
#include "fo-object.h"
#include "libfo/fo-layout-cairo-private.h"
#include "libfo/fo-doc-private.h"
#include "libfo/fo-font-desc-private.h"

static void fo_layout_cairo_class_init (FoLayoutCairoClass *klass);
static void fo_layout_cairo_finalize   (GObject       *object);

static void fo_layout_cairo_set_line_height (FoLayout *fo_layout,
					     gfloat    line_height);

static void fo_layout_cairo_set_line_stacking_strategy (FoLayout  *fo_layout,
							FoEnumEnum line_stacking_strategy);

static gpointer parent_class;

/**
 * fo_layout_cairo_get_type:
 * 
 * Register the #FoLayoutCairo type if not already registered and
 * return its #GType value.
 * 
 * Return value: #GType of #FoLayoutCairo.
 **/
GType
fo_layout_cairo_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLayoutCairoClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_layout_cairo_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLayoutCairo),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_LAYOUT,
                                            "FoLayoutCairo",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_layout_cairo_class_init:
 * @klass: #FoLayoutCairo object to initialise.
 * 
 * Implements #GClassInitFunc for #FoLayoutCairoClass.
 **/
void
fo_layout_cairo_class_init (FoLayoutCairoClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = fo_layout_cairo_finalize;

  FO_LAYOUT_CLASS (klass)->set_line_height = fo_layout_cairo_set_line_height;
  FO_LAYOUT_CLASS (klass)->set_line_stacking_strategy =
    fo_layout_cairo_set_line_stacking_strategy;
}

/**
 * fo_layout_cairo_finalize:
 * @object: #FoLayoutCairo object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoLayoutCairo.
 **/
void
fo_layout_cairo_finalize (GObject *object)
{
  FoLayoutCairo *fo_layout_cairo;

  fo_layout_cairo = FO_LAYOUT_CAIRO (object);

  /*g_object_unref (fo_layout_cairo->fo_doc);*/

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_layout_cairo_new:
 * 
 * Creates a new #FoLayoutCairo.
 * 
 * Return value: the newly created #FoLayoutCairo.
 **/
FoLayout *
fo_layout_cairo_new (void)
{
  FoLayout* fo_layout;

  fo_layout =
    g_object_new (fo_layout_cairo_get_type (),
		  NULL);

  return fo_layout;
}

/**
 * fo_layout_cairo_new_from_fo_doc:
 * @fo_doc: #FoDoc.
 * 
 * Creates a new #FoLayoutCairo.
 * 
 * Return value: the newly created #FoLayoutCairo.
 **/
FoLayout *
fo_layout_cairo_new_from_fo_doc (FoDoc *fo_doc)
{
  FoLayout* fo_layout;

  fo_layout =
    g_object_new (fo_layout_cairo_get_type (),
		  NULL);

  /* FIXME: should be g_object_ref (fo_doc) but uncertain what unrefs layout */
  fo_layout->fo_doc = fo_doc;
  fo_layout->pango_layout =
    pango_layout_new (fo_doc_get_pango_context (fo_doc));

  return fo_layout;
}

/**
 * fo_layout_cairo_set_line_height:
 * @fo_layout:   #FoLayout.
 * @line_height: 'line-height' in points.
 * 
 * Set the 'line-height' of @fo_layout to @line_height.
 **/
void
fo_layout_cairo_set_line_height (FoLayout *fo_layout,
				  gfloat    line_height)
{
  g_return_if_fail (FO_IS_LAYOUT_CAIRO (fo_layout));

/*  pango_cairo_layout_set_line_height (fo_layout->pango_layout,
    line_height * PANGO_SCALE);*/
}

/**
 * fo_layout_cairo_set_line_stacking_strategy:
 * @fo_layout:              #FoLayout.
 * @line_stacking_strategy: Line stacking strategy to use.
 * 
 * Set the 'line-stacking-strategy' property of @fo_layout to
 * @line_stacking_strategy.
 **/
void
fo_layout_cairo_set_line_stacking_strategy (FoLayout *fo_layout,
					 FoEnumEnum line_stacking_strategy)
{
  g_return_if_fail (FO_IS_LAYOUT_CAIRO (fo_layout));

/*  pango_cairo_layout_set_line_stacking_strategy (fo_layout->pango_layout,
    fo_layout_line_stacking_strategy_to_pango_line_stacking_strategy (line_stacking_strategy));*/
}
