/* Fo
 * fo-utils.h: Utilities for internal functions and modules
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
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

typedef gint FoDebugFlag;

/**
 * FO_DEBUG_NONE: No debug
 **/
#define FO_DEBUG_NONE		0
#define FO_DEBUG_RESULT		1 << 0
#define FO_DEBUG_FO		1 << 1
#define FO_DEBUG_AREA		1 << 2
#define FO_DEBUG_PANGO		1 << 3
#define FO_DEBUG_PDF		1 << 4
#define FO_DEBUG_MAX		((1 << 5) - 1)

typedef gint FoWarningFlag;

/**
 * FO_WARNING_NONE:
 *
 * No explicit control over warning message output.
 **/
#define FO_WARNING_NONE			0
#define FO_WARNING_FO			1 << 0
#define FO_WARNING_PROPERTY		1 << 1
#define FO_WARNING_UNSUPPORTED_PROPERTY	1 << 2
#define FO_WARNING_MAX			((1 << 3) - 1)

typedef enum {
  FO_ENUM_AREA_DIRECTION_UNKNOWN,
  FO_ENUM_AREA_DIRECTION_LR,
  FO_ENUM_AREA_DIRECTION_RL,
  FO_ENUM_AREA_DIRECTION_TB,
  FO_ENUM_AREA_DIRECTION_BT
} FoEnumAreaDirection;

/* Reordered to match Pango enumerations for common values */
typedef enum {
  FO_ENUM_FONT_STRETCH_ULTRA_CONDENSED,
  FO_ENUM_FONT_STRETCH_EXTRA_CONDENSED,
  FO_ENUM_FONT_STRETCH_CONDENSED,
  FO_ENUM_FONT_STRETCH_SEMI_CONDENSED,
  FO_ENUM_FONT_STRETCH_NORMAL,
  FO_ENUM_FONT_STRETCH_SEMI_EXPANDED,
  FO_ENUM_FONT_STRETCH_EXPANDED,
  FO_ENUM_FONT_STRETCH_EXTRA_EXPANDED,
  FO_ENUM_FONT_STRETCH_ULTRA_EXPANDED,
  FO_ENUM_FONT_STRETCH_WIDER,
  FO_ENUM_FONT_STRETCH_NARROWER
} FoEnumFontStretch;

typedef enum {
  FO_ENUM_FONT_STYLE_NORMAL,
  FO_ENUM_FONT_STYLE_ITALIC,
  FO_ENUM_FONT_STYLE_OBLIQUE,
  FO_ENUM_FONT_STYLE_BACKSLANT
} FoEnumFontStyle;

G_END_DECLS

#endif /* !__FO_UTILS_H__ */
