/* Fo
 * fo-wrapper-inline-empty.c: Inline-level wrapper formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-wrapper-inline-empty.c,v 1.2 2006/03/28 11:14:47 tonygraham Exp $
 *
 * See Copyright for the status of this software.
 */

#include "fo-inline-fo.h"
#include "fo-wrapper-inline-empty-private.h"
#include "property/fo-property-text-property.h"

/* ZWSP = U+200B
 *      = 0010 0000 0000 1011 (UTF-16)
 *      = zzzz yyyy yyxx xxxx
 *      = 1110zzzz 10yyyyyy 10xxxxxx (UTF-8)
 *      = 11100010 10000000 10001011 (UTF-8)
 *      = 11 110 010  10 000 000  10 001 011 (UTF-8)
 *      = \352\200\213 (UTF-8)
 */
#define UTF8_STR_ZERO_WIDTH_SPACE "\352\200\212"  /* U+200B */

enum {
  PROP_0
};

static void fo_wrapper_inline_empty_class_init     (FoWrapperInlineEmptyClass *klass);
static void fo_wrapper_inline_empty_inline_fo_init (FoInlineFoIface           *iface);
static void fo_wrapper_inline_empty_finalize       (GObject                   *object);

static void fo_wrapper_inline_empty_get_text_attr_list    (FoFo      *fo_inline_fo,
							   FoDoc     *fo_doc,
							   GString   *text,
							   GList    **attr_glist,
							   guint      debug_level);

static gpointer parent_class;

GType
fo_wrapper_inline_empty_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoWrapperInlineEmptyClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_wrapper_inline_empty_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoWrapperInlineEmpty),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      static const GInterfaceInfo fo_inline_fo_info =
      {
	(GInterfaceInitFunc) fo_wrapper_inline_empty_inline_fo_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_WRAPPER,
                                            "FoWrapperInlineEmpty",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &fo_inline_fo_info);
    }
  
  return object_type;
}

/**
 * fo_wrapper_inline_empty_class_init:
 * @klass: #FoWrapperInlineEmptyClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoWrapperInlineEmptyClass.
 **/
static void
fo_wrapper_inline_empty_class_init (FoWrapperInlineEmptyClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_wrapper_inline_empty_finalize;
}

/**
 * fo_wrapper_inline_empty_inline_fo_init:
 * @iface: #FoInlineFoIFace structure for this class.
 * 
 * Initialize #FoInlineFoIface interface for this class.
 **/
void
fo_wrapper_inline_empty_inline_fo_init (FoInlineFoIface *iface)
{
  iface->get_text_attr_list = fo_wrapper_inline_empty_get_text_attr_list;
}

static void
fo_wrapper_inline_empty_finalize (GObject *object)
{
  FoWrapperInlineEmpty *fo_wrapper_inline_empty;

  fo_wrapper_inline_empty = FO_WRAPPER_INLINE_EMPTY (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_wrapper_inline_empty_new:
 * 
 * Creates a new #FoWrapperInlineEmpty initialized to default value.
 * 
 * Return value: the new #FoWrapperInlineEmpty.
 **/
FoFo*
fo_wrapper_inline_empty_new (void)
{
  return FO_FO (g_object_new (fo_wrapper_inline_empty_get_type (),
			      NULL));
}

/**
 * fo_wrapper_inline_empty_get_text_attr_list:
 * @fo_inline_fo: The #FoInlineFo object.
 * @fo_doc:       The #FoDoc that will render @fo_inline_fo.
 * @text:         The text of the inline FO.
 * @attr_glist:   The list of #PangoAttribute for the inline FO.
 * @debug_level:  Debug level.
 * 
 * Gets the text of the inline FO and its associated list of #PangoAttribute.
 **/
void
fo_wrapper_inline_empty_get_text_attr_list (FoFo    *fo_inline_fo,
					    FoDoc   *fo_doc,
					    GString *text,
					    GList  **attr_glist,
					    guint    debug_level)
{
  FoNode *fo_child_node;
  FoWrapperInlineEmpty *fo_wrapper_inline_empty;
  PangoAttribute *pango_attr;
  GList *my_attr_glist = NULL;
  gint start_index, end_index;

  g_return_if_fail (fo_inline_fo != NULL);
  g_return_if_fail (FO_IS_WRAPPER_INLINE_EMPTY (fo_inline_fo));

  fo_wrapper_inline_empty = FO_WRAPPER_INLINE_EMPTY (fo_inline_fo);

  start_index = text->len;

  g_string_append (text, UTF8_STR_ZERO_WIDTH_SPACE);

  end_index = text->len;
}
