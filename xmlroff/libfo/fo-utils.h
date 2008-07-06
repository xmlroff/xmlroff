/* Fo
 * fo-utils.h: Utilities for internal functions and modules
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_UTILS_H__
#define __FO_UTILS_H__

#include <stdio.h>
#include <glib.h>
#include <glib-object.h>

G_BEGIN_DECLS

#ifndef _
#define _(String)	(String)
#endif
#ifndef N_
#define N_(String)	(String)
#endif

#define fo_propagate_and_return_if_error(src, dest) \
     if ((src) != NULL) \
	{ g_propagate_error ((src), (dest)); return; }

#define fo_propagate_and_return_val_if_error(src, dest, val) \
     if ((src) != NULL) \
	{ g_propagate_error ((src), (dest)); return ((val)); }

/**
 * FoDebugFlag:
 * @FO_DEBUG_NONE:   No debugging enabled
 * @FO_DEBUG_RESULT: Debug result tree
 * @FO_DEBUG_FO:     Debug FO tree
 * @FO_DEBUG_AREA:   Debug area tree
 * @FO_DEBUG_PANGO:  Debug Pango layouts
 * @FO_DEBUG_MAX:    Maximum possible value
 *
 * Debugging flags.
 */
typedef enum {
  FO_DEBUG_NONE = 0,
  FO_DEBUG_RESULT = 1 << 0,
  FO_DEBUG_FO = 1 << 1,
  FO_DEBUG_AREA = 1 << 2,
  FO_DEBUG_PANGO = 1 << 3,
  FO_DEBUG_MAX = ((1 << 4) - 1)
} FoDebugFlag;

/**
 * FoWarningFlag:
 * @FO_WARNING_NONE: No explicit control over warning message output
 * @FO_WARNING_FO:   Do not warn about FO errors
 * @FO_WARNING_PROPERTY: Do not warn about property errors
 * @FO_WARNING_UNSUPPORTED_PROPERTY: Do not warn about unsupported properties
 * @FO_WARNING_MAX: Maxemum possible value
 *
 * Warning flags.
 */
typedef enum {
  FO_WARNING_NONE = 0,
  FO_WARNING_FO = 1 << 0,
  FO_WARNING_PROPERTY = 1 << 1,
  FO_WARNING_UNSUPPORTED_PROPERTY = 1 << 2,
  FO_WARNING_MAX = ((1 << 3) - 1)
} FoWarningFlag;

typedef enum {
  FO_ENUM_AREA_DIRECTION_UNKNOWN,
  FO_ENUM_AREA_DIRECTION_LR,
  FO_ENUM_AREA_DIRECTION_RL,
  FO_ENUM_AREA_DIRECTION_TB,
  FO_ENUM_AREA_DIRECTION_BT
} FoEnumAreaDirection;


G_END_DECLS

#endif /* !__FO_UTILS_H__ */
