/* LibFO
 * libfo-pango.c: Extra PangoAttribute types needed by LibFO.
 *
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "libfo-pango.h"

/**
 * libfo_pango_attr_callback_get_type:
 * 
 * Register the 'callback' PangoAttribute type.
 * 
 * Return value: The new #PangoAttrType.
 **/
PangoAttrType
libfo_pango_attr_callback_get_type (void)
{
  static PangoAttrType attr_callback = PANGO_ATTR_INVALID;

  if (attr_callback == PANGO_ATTR_INVALID)
    {
      attr_callback =
	pango_attr_type_register ("callback");
    }

  return attr_callback;
}

static PangoAttribute *
libfo_pango_attr_pointer_new (const PangoAttrClass *klass,
			gpointer              pointer)
{
  LibfoPangoAttrPointer *result = g_new (LibfoPangoAttrPointer, 1);
  result->attr.klass = klass;
  result->pointer = pointer;

  return (PangoAttribute *)result;
}

static PangoAttribute *
libfo_pango_attr_pointer_copy (const PangoAttribute *attr)
{
  const LibfoPangoAttrPointer *pointer_attr = (LibfoPangoAttrPointer *)attr;

  return libfo_pango_attr_pointer_new (attr->klass,
				       pointer_attr->pointer);
}

static void
libfo_pango_attr_pointer_destroy (PangoAttribute *attr)
{
  g_free (attr);
}

static gpointer
libfo_pango_attr_pointer_get_pointer (const PangoAttribute *attr)
{
  const LibfoPangoAttrPointer *pointer_attr = (LibfoPangoAttrPointer *)attr;
  
  return pointer_attr->pointer;
}

static gboolean
libfo_pango_attr_pointer_equal (const PangoAttribute *attr1,
				const PangoAttribute *attr2)
{
  const LibfoPangoAttrPointer *pointer_attr1 =
    (const LibfoPangoAttrPointer *)attr1;
  const LibfoPangoAttrPointer *pointer_attr2 =
    (const LibfoPangoAttrPointer *)attr2;
  
  return (pointer_attr1->pointer == pointer_attr2->pointer);
}

/**
 * libfo_pango_attr_callback_new:
 * @callback: the callback
 * 
 * Create a new callback attribute.
 * 
 * Return value: the new #PangoAttribute.
 **/
PangoAttribute *
libfo_pango_attr_callback_new (gpointer callback)
{
  static PangoAttrClass klass = {PANGO_ATTR_INVALID,
				 NULL,
				 NULL,
				 NULL};

  if (klass.type == PANGO_ATTR_INVALID)
    {
      klass.type = libfo_pango_attr_callback_get_type();
      klass.copy = libfo_pango_attr_pointer_copy;
      klass.destroy = libfo_pango_attr_pointer_destroy;
      klass.equal = libfo_pango_attr_pointer_equal;
    }

  return libfo_pango_attr_pointer_new (&klass, callback);
}

/**
 * libfo_pango_attr_callback_get_callback:
 * @attr: The 'callback' attribute.
 * 
 * Get the callback associated with @attr.
 * 
 * Return value: The callback.
 **/
gpointer
libfo_pango_attr_callback_get_callback (const PangoAttribute *attr)
{
  return libfo_pango_attr_pointer_get_pointer (attr);
}
