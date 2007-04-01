/* Fo
 * fo-wrapper-inline.c: Inline-level wrapper formatting object.
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 *
 * $Id: fo-wrapper-inline.c,v 1.3 2006/03/21 23:21:38 tonygraham Exp $
 *
 * See COPYING for the status of this software.
 */

#include "fo-inline-fo.h"
#include "fo-wrapper-inline-private.h"
#include "property/fo-property-text-property.h"

enum {
  PROP_0
};

static void fo_wrapper_inline_class_init  (FoWrapperInlineClass *klass);
static void fo_wrapper_inline_finalize    (GObject           *object);
static void fo_wrapper_inline_update_from_context   (FoFo      *fo,
						     FoContext *context);
static void fo_wrapper_inline_debug_dump_properties (FoFo      *fo,
						     gint       depth);

static gpointer parent_class;

GType
fo_wrapper_inline_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoWrapperInlineClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_wrapper_inline_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoWrapperInline),
        0,              /* n_preallocs */
	NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      static const GInterfaceInfo fo_inline_fo_info =
      {
        NULL,
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_WRAPPER,
                                            "FoWrapperInline",
                                            &object_info, 0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_INLINE_FO,
                                   &fo_inline_fo_info);
    }
  
  return object_type;
}

static void
fo_wrapper_inline_class_init (FoWrapperInlineClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_wrapper_inline_finalize;

  FO_FO_CLASS (klass)->debug_dump_properties = fo_wrapper_inline_debug_dump_properties;
  FO_FO_CLASS (klass)->update_from_context = fo_wrapper_inline_update_from_context;
}

static void
fo_wrapper_inline_finalize (GObject *object)
{
  FoWrapperInline *fo_wrapper_inline;

  fo_wrapper_inline = FO_WRAPPER_INLINE (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_wrapper_inline_new:
 * 
 * Creates a new #FoWrapperInline initialized to default value.
 * 
 * Return value: the new #FoWrapperInline
 **/
FoFo*
fo_wrapper_inline_new (void)
{
  return FO_FO (g_object_new (fo_wrapper_inline_get_type (),
			      NULL));
}

void
fo_wrapper_inline_update_from_context (FoFo *fo, FoContext *context)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_WRAPPER (fo));

  FO_FO_CLASS (parent_class)->update_from_context (fo, context);
}

void
fo_wrapper_inline_debug_dump_properties (FoFo *fo, gint depth)
{
  g_return_if_fail (fo != NULL);
  g_return_if_fail (FO_IS_WRAPPER (fo));

  FO_FO_CLASS (parent_class)->debug_dump_properties (fo, depth + 1);
}

