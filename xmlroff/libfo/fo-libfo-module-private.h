/* Fo
 * fo-libfo-module-private.h: Formatting object that is module of possible fo:libfo
 *
 * Copyright (C) 2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include <libfo/fo-object.h>
#include <libfo/fo-libfo-module.h>

struct _FoLibfoModule
{
  FoObject module_instance;
};

struct _FoLibfoModuleClass
{
  FoObjectClass module_class;

  gint                     (*version)        (void);
  const gchar*             (*version_string) (void);
  const LibfoVersionInfo * (*version_info)   (void);
};
