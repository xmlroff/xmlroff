/* Fo
 * fo-pixbuf.c: Interface for getting GdkPixbuf contained by an object.
 *
 * Copyright (C) 2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-pixbuf.h"

static void        fo_pixbuf_base_class_init    (FoPixbufIface *klass);
static GdkPixbuf * fo_pixbuf_get_pixbuf_default (FoImage       *fo_image);
static void        fo_pixbuf_set_pixbuf_default (FoImage       *fo_image,
						 GdkPixbuf     *pixbuf);

/**
 * fo_pixbuf_get_type:
 *
 * Register the #FoPixbuf interface type.
 * 
 * Return value: #GType value of the #FoPixbuf interface type.
 **/
GType
fo_pixbuf_get_type (void)
{
  static GType pixbuf_type = 0;

  if (!pixbuf_type)
    {
      static const GTypeInfo pixbuf_info =
      {
        sizeof (FoPixbufIface), /* class_size */
	(GBaseInitFunc) fo_pixbuf_base_class_init,   	/* base_init */
	NULL,		/* base_finalize */
	NULL,
	NULL,		/* class_finalize */
	NULL,		/* class_data */
	0,
	0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      pixbuf_type = g_type_register_static (G_TYPE_INTERFACE,
					    "FoPixbufIface",
					    &pixbuf_info, 0);
      g_type_interface_add_prerequisite (pixbuf_type, FO_TYPE_OBJECT);
    }

  return pixbuf_type;
}

/**
 * fo_pixbuf_base_class_init:
 * @klass: #FoPixbufIface base interface object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoPixbufIface.
 **/
void
fo_pixbuf_base_class_init  (FoPixbufIface *klass)
{
  klass->get_pixbuf =
    fo_pixbuf_get_pixbuf_default;
  klass->set_pixbuf =
    fo_pixbuf_set_pixbuf_default;
}

/**
 * fo_pixbuf_get_pixbuf:
 * @fo_image: The @FoImage containing the pixbuf.
 * 
 * Gets the #GdkPixbuf contained by @fo_image.
 *
 * Return value: The #GdkPixbuf contained by @fo_image.
 **/
GdkPixbuf *
fo_pixbuf_get_pixbuf (FoImage *fo_image)
{
  g_return_val_if_fail (fo_image != NULL, NULL);
  g_return_val_if_fail (FO_IS_PIXBUF (fo_image), NULL);

  return FO_PIXBUF_GET_IFACE (fo_image)->get_pixbuf (fo_image);
}

GdkPixbuf *
fo_pixbuf_get_pixbuf_default (FoImage *fo_image)
{
  g_return_val_if_fail (FO_IS_PIXBUF (fo_image), NULL);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'get_pixbuf' function."),
	 fo_object_sprintf (FO_OBJECT (fo_image)));

  return NULL;
}

/**
 * fo_pixbuf_set_pixbuf:
 * @fo_image: The #FoImage containing the pixbuf.
 * @pixbuf:   #GdkPixbuf to be contained by @fo_image.
 * 
 * Sets the #GdkPixbuf contained by @fo_image.
 **/
void
fo_pixbuf_set_pixbuf (FoImage   *fo_image,
		      GdkPixbuf *pixbuf)
{
  g_return_if_fail (fo_image != NULL);
  g_return_if_fail (FO_IS_PIXBUF (fo_image));

  FO_PIXBUF_GET_IFACE (fo_image)->set_pixbuf (fo_image,
					       pixbuf);
}

void
fo_pixbuf_set_pixbuf_default (FoImage   *fo_image,
			      GdkPixbuf *pixbuf G_GNUC_UNUSED)
{
  g_return_if_fail (FO_IS_PIXBUF (fo_image));

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 _("%s does not have a 'set_pixbuf' function."),
	 fo_object_sprintf (FO_OBJECT (fo_image)));
}
