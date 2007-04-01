/* Fo
 * fo-image.c: Object representing an image.
 *
 * Copyright (C) 2003 Sun Microsystems
 *
 * $Id: fo-image.c,v 1.7 2005/09/16 08:55:25 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#include "fo-image.h"
#include "util/fo-pixbuf.h"
#include "libfo/fo-utils.h"
#include "datatype/fo-length.h"
#include <libxml/uri.h>

struct _FoImage
{
  FoObject parent_instance;

  GdkPixbuf *pixbuf;
  gchar     *uri;

  FoDatatype *width;
  FoDatatype *height;
};

struct _FoImageClass
{
  FoObjectClass parent_class;
};

static void fo_image_class_init  (FoImageClass  *klass);
static void fo_image_pixbuf_init (FoPixbufIface *iface);
static void fo_image_finalize    (GObject       *object);
static void fo_image_debug_dump  (FoObject      *object,
				  gint           depth);

static void        fo_image_set_uri    (FoImage     *fo_image,
					const gchar *uri);
static GdkPixbuf * fo_image_get_pixbuf (FoImage     *fo_image);
static void        fo_image_set_pixbuf (FoImage     *fo_image,
					GdkPixbuf   *pixbuf);

static gpointer parent_class;

/**
 * fo_image_get_type:
 * 
 * Register the #FoImage object type.
 * 
 * Return value: #GType value of the #FoImage object type.
 **/
GType
fo_image_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoImageClass),
        (GBaseInitFunc) NULL,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) fo_image_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoImage),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };
      
      static const GInterfaceInfo fo_pixbuf_info =
      {
	(GInterfaceInitFunc) fo_image_pixbuf_init, /* interface_init */
        NULL,
        NULL
      };

      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoImage",
                                            &object_info,
					    0);
      g_type_add_interface_static (object_type,
                                   FO_TYPE_PIXBUF,
                                   &fo_pixbuf_info);
    }
  
  return object_type;
}

/**
 * fo_image_class_init:
 * @klass: #FoImageClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoHashTableClass.
 **/
void
fo_image_class_init (FoImageClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  FoObjectClass *fo_object_class = FO_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_image_finalize;

  fo_object_class->debug_dump = fo_image_debug_dump;
}

/**
 * fo_image_pixbuf_init:
 * @iface: #FoPixbufIFace structure for this class.
 * 
 * Initialize #FoPixbufIface interface for this class.
 **/
void
fo_image_pixbuf_init (FoPixbufIface *iface)
{
  iface->get_pixbuf = fo_image_get_pixbuf;
  iface->set_pixbuf = fo_image_set_pixbuf;
}

/**
 * fo_image_finalize:
 * @object: #FoImage object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoImage.
 **/
void
fo_image_finalize (GObject *object)
{
  FoImage *fo_image;

  fo_image = FO_IMAGE (object);

  g_free (fo_image->uri);

  if (fo_image->pixbuf != NULL)
    {
      g_object_unref (fo_image->pixbuf);
      fo_image->pixbuf = NULL;
    }

  if (fo_image->width != NULL)
    {
      g_object_unref (fo_image->width);
      fo_image->width = NULL;
    }

  if (fo_image->height != NULL)
    {
      g_object_unref (fo_image->height);
      fo_image->height = NULL;
    }

  G_OBJECT_CLASS (parent_class)->finalize (object);
}

/**
 * fo_image_new:
 * 
 * Creates a new #FoImage.
 * 
 * Return value: the newly created #FoImage.
 **/
FoImage *
fo_image_new (void)
{
  FoImage *fo_image;

  fo_image = FO_IMAGE (g_object_new (fo_image_get_type (),
				     NULL));

  return fo_image;
}

/**
 * fo_image_new_from_uri:
 * @uri:  URI of image.
 * @base: Base URI for resolving relative URI @uri values.
 * 
 * Creates a new #FoImage from the resource at @uri.
 *
 * If @uri is a relative URI, it is resolved relative to @base.
 * 
 * Return value: the newly created #FoImage.
 **/
FoImage *
fo_image_new_from_uri (const gchar *uri,
		       const gchar *base)
{
  FoImage *fo_image;
  gchar *resolved_uri;

  fo_image = FO_IMAGE (g_object_new (fo_image_get_type (),
				     NULL));

  resolved_uri = (gchar *) xmlBuildURI ((const xmlChar *) uri,
					(const xmlChar *) base);

  fo_image_set_uri (fo_image, resolved_uri);

  xmlFree ((xmlChar *) resolved_uri);

  return fo_image;
}

/**
 * fo_image_get_pixbuf:
 * @fo_image: #FoImage
 * 
 * Get the #GdkPixbuf in @fo_image.
 * 
 * Return value: #GdkPixbuf.
 **/
GdkPixbuf *
fo_image_get_pixbuf (FoImage *fo_image)
{
  g_return_val_if_fail (fo_image != NULL, NULL);

  return fo_image->pixbuf;
}

/**
 * fo_image_set_pixbuf:
 * @fo_image: #FoImage.
 * @pixbuf:   #GdkPixbuf.
 * 
 * Set the output #GdkPixbuf in @fo_image.
 **/
void
fo_image_set_pixbuf (FoImage   *fo_image,
		     GdkPixbuf *pixbuf)
{
  g_return_if_fail (fo_image != NULL);

  fo_image->pixbuf = pixbuf;
}

/**
 * fo_image_get_uri:
 * @fo_image: #FoImage
 * 
 * Get the URI in @fo_image.
 * 
 * Return value: URI of image to make @fo_image.
 **/
const gchar *
fo_image_get_uri (FoImage *fo_image)
{
  g_return_val_if_fail (fo_image != NULL, NULL);

  return fo_image->uri;
}

/**
 * fo_image_set_uri:
 * @fo_image: #FoImage
 * @uri:      URI of image.
 * 
 * Set the URI of image in @fo_image.
 **/
void
fo_image_set_uri (FoImage     *fo_image,
		  const gchar *uri)
{
  GError *error;

  g_return_if_fail (fo_image != NULL);

  fo_image->uri = g_strdup (uri);

  /* Load the image into a pixbuf */
  error = NULL;
  fo_image->pixbuf = gdk_pixbuf_new_from_file (uri, &error);
  if (error != NULL)
    {
      fo_object_log_error (FO_OBJECT (fo_image),
			   &error);
    }
  if (fo_image->pixbuf == NULL)
    {
      g_print ("Could not load image.\n");
    }

  fo_image->width = g_object_ref (fo_length_new_from_pixels (gdk_pixbuf_get_width (fo_image->pixbuf)));
  fo_image->height = g_object_ref (fo_length_new_from_pixels (gdk_pixbuf_get_height (fo_image->pixbuf)));
}

/**
 * fo_image_get_width:
 * @fo_image: #FoImage
 * 
 * Gets the intrinsic width of @fo_image.
 * 
 * Return value: The intrinsic width of @fo_image.
 **/
FoDatatype *
fo_image_get_width  (const FoImage *fo_image)
{
  g_return_val_if_fail (fo_image != NULL, 0);
  g_return_val_if_fail (FO_IS_IMAGE (fo_image), 0);
  g_return_val_if_fail (fo_image->pixbuf != NULL, 0);

  return fo_image->width;
}

/**
 * fo_image_get_height:
 * @fo_image: #FoImage.
 * 
 * Gets the intrinsic height of @fo_image.
 * 
 * Return value: The intrinsic height of @fo_image.
 **/
FoDatatype *
fo_image_get_height (const FoImage *fo_image)
{
  g_return_val_if_fail (fo_image != NULL, 0);
  g_return_val_if_fail (FO_IS_IMAGE (fo_image), 0);
  g_return_val_if_fail (fo_image->pixbuf != NULL, 0);

  return fo_image->height;
}

/**
 * fo_image_debug_dump:
 * @fo: The #FoFo object
 * @depth: Indent level to add to the output
 * 
 * Calls #fo_object_debug_dump on each property of @fo then calls
 * debug_dump_properties method of parent class
 **/
void
fo_image_debug_dump (FoObject *object,
		     gint      depth)
{
  FoImage *fo_image;
  gchar *indent = g_strnfill (depth * 2, ' ');

  g_return_if_fail (object != NULL);
  g_return_if_fail (FO_IS_IMAGE (object));

  fo_image = FO_IMAGE (object);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%suri : %s",
	 indent,
	 fo_image->uri);
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%spixbuf : %s",
	 indent,
	 fo_object_sprintf (fo_image->pixbuf));
  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%swidth :",
	 indent);
  fo_object_debug_dump (fo_image->width, depth + 1);

  g_log (G_LOG_DOMAIN,
	 G_LOG_LEVEL_DEBUG,
	 "%sheight :",
	 indent);
  fo_object_debug_dump (fo_image->height, depth + 1);

  g_free (indent);
}
