/* Fo
 * fo-layout-cairo.c: Object type for PangoCairoLayout
 *
 * Copyright (C) 2003-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <pango/pango.h>
#include "fo-utils.h"
#include "fo-object.h"
#include "fo-layout-cairo-private.h"
#include "fo-doc-private.h"
#include "fo-font-desc-private.h"

static void _class_init                 (FoLayoutCairoClass *klass);
static void _finalize                   (GObject   *object);

static void _set_line_height            (FoLayout  *fo_layout,
					 gfloat     line_height);

static void _set_line_stacking_strategy (FoLayout  *fo_layout,
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
        (GClassInitFunc) _class_init,
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
 * _class_init:
 * @klass: #FoLayoutCairo object to initialise.
 * 
 * Implements #GClassInitFunc for #FoLayoutCairoClass.
 **/
static void
_class_init (FoLayoutCairoClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  parent_class = g_type_class_peek_parent (klass);

  object_class->finalize = _finalize;

  FO_LAYOUT_CLASS (klass)->set_line_height = _set_line_height;
  FO_LAYOUT_CLASS (klass)->set_line_stacking_strategy =
    _set_line_stacking_strategy;
}

/**
 * _finalize:
 * @object: #FoLayoutCairo object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoLayoutCairo.
 **/
static void
_finalize (GObject *object)
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
  return g_object_new (fo_layout_cairo_get_type (),
		       NULL);
}

/**
 * _set_line_height:
 * @fo_layout:   #FoLayout.
 * @line_height: 'line-height' in points.
 * 
 * Set the 'line-height' of @fo_layout to @line_height.
 **/
static void
_set_line_height (FoLayout *fo_layout,
		  gfloat    line_height G_GNUC_UNUSED)
{
  g_return_if_fail (FO_IS_LAYOUT_CAIRO (fo_layout));

/*  pango_cairo_layout_set_line_height (fo_layout->pango_layout,
    line_height * PANGO_SCALE);*/
}

/**
 * _set_line_stacking_strategy:
 * @fo_layout:              #FoLayout.
 * @line_stacking_strategy: Line stacking strategy to use.
 * 
 * Set the 'line-stacking-strategy' property of @fo_layout to
 * @line_stacking_strategy.
 **/
static void
_set_line_stacking_strategy (FoLayout *fo_layout,
			     FoEnumEnum line_stacking_strategy G_GNUC_UNUSED)
{
  g_return_if_fail (FO_IS_LAYOUT_CAIRO (fo_layout));

/*  pango_cairo_layout_set_line_stacking_strategy (fo_layout->pango_layout,
    fo_layout_line_stacking_strategy_to_pango_line_stacking_strategy (line_stacking_strategy));*/
}
