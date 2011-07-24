/* Fo
 * fo-libfo-module.c: Formatting object that is module of possible fo:libfo
 *
 * Copyright (C) 2003 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#include "fo-libfo-module-private.h"
#include "fo-libfo.h"

enum {
  PROP_0
};

static void     fo_libfo_module_base_init (FoLibfoModuleClass *klass);

static gint                     _version_default        (void);
static const gchar *            _version_string_default (void);
static const LibfoVersionInfo * _version_info_default   (void);


GType
fo_libfo_module_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoLibfoModuleClass),
        (GBaseInitFunc) fo_libfo_module_base_init,
        (GBaseFinalizeFunc) NULL,
        (GClassInitFunc) NULL,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoLibfoModule),
        0,              /* n_preallocs */
        NULL,		/* instance_init */
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_OBJECT,
                                            "FoLibfoModule",
                                            &object_info,
					    G_TYPE_FLAG_ABSTRACT);
    }

  return object_type;
}

/**
 * fo_libfo_module_base_init:
 * @klass: #FoLibfoModuleClass base class object to initialise.
 * 
 * Implements #GBaseInitFunc for #FoLibfoModuleClass.
 **/
void
fo_libfo_module_base_init (FoLibfoModuleClass *klass)
{
  klass->version             = _version_default;
  klass->version_string      = _version_string_default;
  klass->version_info        = _version_info_default;
}

gint
_version_default ()
{
  return 0;
}

/**
 * fo_libfo_module_version_from_name:
 * @name: Registered #FoObject type name, e.g., "FoDocCairo"
 * 
 * Gets the runtime version of the library underlying the
 * #FoLibfoModule implementation.
 *
 * This function just returns what the underlying library provides, if
 * anything, so version numbers can only meaningfully be compared
 * against version numbers of the same library implementation.
 * 
 * Returns: Library version, or 0 if the underlying library does not
 *   make its version number available at runtime
 **/
gint
fo_libfo_module_version_from_name (const gchar *name)
{
  g_return_val_if_fail (name != NULL, 0);

  gint version = 0;
  GType type = g_type_from_name (name);

  if (g_type_is_a (type, fo_libfo_module_get_type ()))
    {
      gpointer klass = g_type_class_ref (type);
      version =
	((FoLibfoModuleClass *) klass)->version ();
      g_type_class_unref (klass);
    }

  return version;
}

const gchar *
_version_string_default ()
{
  return NULL;
}

/**
 * fo_libfo_module_version_string_from_name:
 * @name: Registered #FoObject type name, e.g., "FoDocCairo"
 * 
 * Gets the runtime version of the library underlying the
 * #FoLibfoModule implementation as a human-readable string.
 * 
 * The string is likely to be of the form "X.Y.Z", e.g., "1.0.0", but
 * this function just returns what the underlying library provides, so
 * nothing is guaranteed.
 * 
 * Returns: Library version, or %NULL if the underlying library does
 *   not make its version number available at runtime
 **/
const gchar *
fo_libfo_module_version_string_from_name (const gchar *name)
{
  g_return_val_if_fail (name != NULL, NULL);

  const gchar *version = NULL;
  GType type = g_type_from_name (name);

  if (g_type_is_a (type, fo_libfo_module_get_type ()))
    {
      gpointer klass = g_type_class_ref (type);
      version =
	((FoLibfoModuleClass *) klass)->version_string ();
      g_type_class_unref (klass);
    }

  return version;
}

const LibfoVersionInfo *
_version_info_default ()
{
  return NULL;
}


/**
 * fo_libfo_module_version_info_from_name:
 * @name: Registered #FoObject type name, e.g., "FoDocCairo"
 * 
 * Gets the #LibfoVersionInfo for @name.
 * 
 * Returns: #LibfoVersionInfo for @name.
 **/
const LibfoVersionInfo *
fo_libfo_module_version_info_from_name (const gchar *name)
{
  g_return_val_if_fail (name != NULL, NULL);

  const LibfoVersionInfo *version_info = NULL;
  GType type = g_type_from_name (name);

  if (g_type_is_a (type, fo_libfo_module_get_type ()))
    {
      gpointer klass = g_type_class_ref (type);
      version_info =
	((FoLibfoModuleClass *) klass)->version_info ();
      g_type_class_unref (klass);
    }

  return version_info;
}

