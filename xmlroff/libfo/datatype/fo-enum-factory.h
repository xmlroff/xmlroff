/* Fo
 * fo-enum-factory.h: Base class for objects that are nodes in a tree
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ENUM_FACTORY_H__
#define __FO_ENUM_FACTORY_H__

#include <libfo/fo-utils.h>
#include <libfo/datatype/fo-datatype.h>

G_BEGIN_DECLS

typedef enum {
  FO_ENUM_ENUM_UNSPECIFIED,
  FO_ENUM_ENUM_0,
  FO_ENUM_ENUM_100,
  FO_ENUM_ENUM_180,
  FO_ENUM_ENUM_200,
  FO_ENUM_ENUM_270,
  FO_ENUM_ENUM_300,
  FO_ENUM_ENUM_400,
  FO_ENUM_ENUM_500,
  FO_ENUM_ENUM_600,
  FO_ENUM_ENUM_700,
  FO_ENUM_ENUM_800,
  FO_ENUM_ENUM_90,
  FO_ENUM_ENUM_900,
  FO_ENUM_ENUM_ABOVE,
  FO_ENUM_ENUM_ABSOLUTE,
  FO_ENUM_ENUM_ABSOLUTE_COLORIMETRIC,
  FO_ENUM_ENUM_ACTIVE,
  FO_ENUM_ENUM_AFTER,
  FO_ENUM_ENUM_AFTER_EDGE,
  FO_ENUM_ENUM_ALL,
  FO_ENUM_ENUM_ALPHABETIC,
  FO_ENUM_ENUM_ALWAYS,
  FO_ENUM_ENUM_ANY,
  FO_ENUM_ENUM_AUTO,
  FO_ENUM_ENUM_AUTO_EVEN,
  FO_ENUM_ENUM_AUTO_ODD,
  FO_ENUM_ENUM_AVOID,
  FO_ENUM_ENUM_BACKSLANT,
  FO_ENUM_ENUM_BASELINE,
  FO_ENUM_ENUM_BEFORE,
  FO_ENUM_ENUM_BEFORE_EDGE,
  FO_ENUM_ENUM_BEHIND,
  FO_ENUM_ENUM_BELOW,
  FO_ENUM_ENUM_BIDI_OVERRIDE,
  FO_ENUM_ENUM_BLANK,
  FO_ENUM_ENUM_BLINK,
  FO_ENUM_ENUM_BLOCK,
  FO_ENUM_ENUM_BOLD,
  FO_ENUM_ENUM_BOLDER,
  FO_ENUM_ENUM_BOTH,
  FO_ENUM_ENUM_BOTTOM,
  FO_ENUM_ENUM_BOUNDED_IN_ONE_DIMENSION,
  FO_ENUM_ENUM_CAPITALIZE,
  FO_ENUM_ENUM_CAPTION,
  FO_ENUM_ENUM_CENTER,
  FO_ENUM_ENUM_CENTER_LEFT,
  FO_ENUM_ENUM_CENTER_RIGHT,
  FO_ENUM_ENUM_CENTRAL,
  FO_ENUM_ENUM_CHARACTER_BY_CHARACTER,
  FO_ENUM_ENUM_CODE,
  FO_ENUM_ENUM_COLLAPSE,
  FO_ENUM_ENUM_COLLAPSE_WITH_PRECEDENCE,
  FO_ENUM_ENUM_COLUMN,
  FO_ENUM_ENUM_CONDENSED,
  FO_ENUM_ENUM_CONSIDER_SHIFTS,
  FO_ENUM_ENUM_CONTINUOUS,
  FO_ENUM_ENUM_CURSIVE,
  FO_ENUM_ENUM_DASHED,
  FO_ENUM_ENUM_DIGITS,
  FO_ENUM_ENUM_DISREGARD_SHIFTS,
  FO_ENUM_ENUM_DOCUMENT,
  FO_ENUM_ENUM_DOCUMENT_ROOT,
  FO_ENUM_ENUM_DOTS,
  FO_ENUM_ENUM_DOTTED,
  FO_ENUM_ENUM_DOUBLE,
  FO_ENUM_ENUM_EMBED,
  FO_ENUM_ENUM_EMPTY,
  FO_ENUM_ENUM_END,
  FO_ENUM_ENUM_END_ON_EVEN,
  FO_ENUM_ENUM_END_ON_ODD,
  FO_ENUM_ENUM_ERROR_IF_OVERFLOW,
  FO_ENUM_ENUM_EVEN,
  FO_ENUM_ENUM_EVEN_PAGE,
  FO_ENUM_ENUM_EXPANDED,
  FO_ENUM_ENUM_EXTRA_CONDENSED,
  FO_ENUM_ENUM_EXTRA_EXPANDED,
  FO_ENUM_ENUM_FALSE,
  FO_ENUM_ENUM_FANTASY,
  FO_ENUM_ENUM_FAR_LEFT,
  FO_ENUM_ENUM_FAR_RIGHT,
  FO_ENUM_ENUM_FAST,
  FO_ENUM_ENUM_FASTER,
  FO_ENUM_ENUM_FIRST,
  FO_ENUM_ENUM_FIRST_INCLUDING_CARRYOVER,
  FO_ENUM_ENUM_FIRST_STARTING_WITHIN_PAGE,
  FO_ENUM_ENUM_FIXED,
  FO_ENUM_ENUM_FOCUS,
  FO_ENUM_ENUM_FONT_HEIGHT,
  FO_ENUM_ENUM_FORCE,
  FO_ENUM_ENUM_GROOVE,
  FO_ENUM_ENUM_HANGING,
  FO_ENUM_ENUM_HIDDEN,
  FO_ENUM_ENUM_HIDE,
  FO_ENUM_ENUM_HIGH,
  FO_ENUM_ENUM_HIGHER,
  FO_ENUM_ENUM_HOVER,
  FO_ENUM_ENUM_ICON,
  FO_ENUM_ENUM_IDEOGRAPHIC,
  FO_ENUM_ENUM_IGNORE,
  FO_ENUM_ENUM_IGNORE_IF_AFTER_LINEFEED,
  FO_ENUM_ENUM_IGNORE_IF_BEFORE_LINEFEED,
  FO_ENUM_ENUM_IGNORE_IF_SURROUNDING_LINEFEED,
  FO_ENUM_ENUM_INDEFINITE,
  FO_ENUM_ENUM_INDENT,
  FO_ENUM_ENUM_INSET,
  FO_ENUM_ENUM_INSIDE,
  FO_ENUM_ENUM_INTEGER_PIXELS,
  FO_ENUM_ENUM_ITALIC,
  FO_ENUM_ENUM_JUSTIFY,
  FO_ENUM_ENUM_LANDSCAPE,
  FO_ENUM_ENUM_LARGE,
  FO_ENUM_ENUM_LARGER,
  FO_ENUM_ENUM_LAST,
  FO_ENUM_ENUM_LAST_ENDING_WITHIN_PAGE,
  FO_ENUM_ENUM_LAST_STARTING_WITHIN_PAGE,
  FO_ENUM_ENUM_LEFT,
  FO_ENUM_ENUM_LEFTWARDS,
  FO_ENUM_ENUM_LEFT_SIDE,
  FO_ENUM_ENUM_LEVEL,
  FO_ENUM_ENUM_LIGHTER,
  FO_ENUM_ENUM_LINE,
  FO_ENUM_ENUM_LINE_HEIGHT,
  FO_ENUM_ENUM_LINE_THROUGH,
  FO_ENUM_ENUM_LINK,
  FO_ENUM_ENUM_LOUD,
  FO_ENUM_ENUM_LOW,
  FO_ENUM_ENUM_LOWER,
  FO_ENUM_ENUM_LOWERCASE,
  FO_ENUM_ENUM_LR,
  FO_ENUM_ENUM_LR_TB,
  FO_ENUM_ENUM_LTR,
  FO_ENUM_ENUM_MATHEMATICAL,
  FO_ENUM_ENUM_MAX_HEIGHT,
  FO_ENUM_ENUM_MEDIUM,
  FO_ENUM_ENUM_MENU,
  FO_ENUM_ENUM_MESSAGE_BOX,
  FO_ENUM_ENUM_MIDDLE,
  FO_ENUM_ENUM_MIX,
  FO_ENUM_ENUM_MONOSPACE,
  FO_ENUM_ENUM_NARROWER,
  FO_ENUM_ENUM_NEW,
  FO_ENUM_ENUM_NONE,
  FO_ENUM_ENUM_NON_UNIFORM,
  FO_ENUM_ENUM_NORMAL,
  FO_ENUM_ENUM_NOT_BLANK,
  FO_ENUM_ENUM_NOWRAP,
  FO_ENUM_ENUM_NO_BLINK,
  FO_ENUM_ENUM_NO_CHANGE,
  FO_ENUM_ENUM_NO_FORCE,
  FO_ENUM_ENUM_NO_LIMIT,
  FO_ENUM_ENUM_NO_LINE_THROUGH,
  FO_ENUM_ENUM_NO_OVERLINE,
  FO_ENUM_ENUM_NO_REPEAT,
  FO_ENUM_ENUM_NO_UNDERLINE,
  FO_ENUM_ENUM_NO_WRAP,
  FO_ENUM_ENUM_OBLIQUE,
  FO_ENUM_ENUM_ODD,
  FO_ENUM_ENUM_ODD_PAGE,
  FO_ENUM_ENUM_ONCE,
  FO_ENUM_ENUM_OUTSET,
  FO_ENUM_ENUM_OUTSIDE,
  FO_ENUM_ENUM_OVERLINE,
  FO_ENUM_ENUM_PAGE,
  FO_ENUM_ENUM_PAGE_SEQUENCE,
  FO_ENUM_ENUM_PAGINATE,
  FO_ENUM_ENUM_PERCEPTUAL,
  FO_ENUM_ENUM_PORTRAIT,
  FO_ENUM_ENUM_PRE,
  FO_ENUM_ENUM_PRESERVE,
  FO_ENUM_ENUM_REFERENCE_AREA,
  FO_ENUM_ENUM_RELATIVE,
  FO_ENUM_ENUM_RELATIVE_COLORIMETRIC,
  FO_ENUM_ENUM_REPEAT,
  FO_ENUM_ENUM_REPEAT_X,
  FO_ENUM_ENUM_REPEAT_Y,
  FO_ENUM_ENUM_REPLACE,
  FO_ENUM_ENUM_RESAMPLE_ANY_METHOD,
  FO_ENUM_ENUM_RESET_SIZE,
  FO_ENUM_ENUM_REST,
  FO_ENUM_ENUM_RETAIN,
  FO_ENUM_ENUM_RIDGE,
  FO_ENUM_ENUM_RIGHT,
  FO_ENUM_ENUM_RIGHTWARDS,
  FO_ENUM_ENUM_RIGHT_SIDE,
  FO_ENUM_ENUM_RL,
  FO_ENUM_ENUM_RL_TB,
  FO_ENUM_ENUM_RTL,
  FO_ENUM_ENUM_RULE,
  FO_ENUM_ENUM_SANS_SERIF,
  FO_ENUM_ENUM_SATURATION,
  FO_ENUM_ENUM_SCALE_TO_FIT,
  FO_ENUM_ENUM_SCROLL,
  FO_ENUM_ENUM_SEMI_CONDENSED,
  FO_ENUM_ENUM_SEMI_EXPANDED,
  FO_ENUM_ENUM_SEPARATE,
  FO_ENUM_ENUM_SERIF,
  FO_ENUM_ENUM_SHOW,
  FO_ENUM_ENUM_SILENT,
  FO_ENUM_ENUM_SLOW,
  FO_ENUM_ENUM_SLOWER,
  FO_ENUM_ENUM_SMALL,
  FO_ENUM_ENUM_SMALLER,
  FO_ENUM_ENUM_SMALL_CAPS,
  FO_ENUM_ENUM_SMALL_CAPTION,
  FO_ENUM_ENUM_SOFT,
  FO_ENUM_ENUM_SOLID,
  FO_ENUM_ENUM_SPACE,
  FO_ENUM_ENUM_SPELL_OUT,
  FO_ENUM_ENUM_START,
  FO_ENUM_ENUM_STATIC,
  FO_ENUM_ENUM_STATUS_BAR,
  FO_ENUM_ENUM_STRING,
  FO_ENUM_ENUM_SUB,
  FO_ENUM_ENUM_SUPER,
  FO_ENUM_ENUM_SUPPRESS,
  FO_ENUM_ENUM_TB,
  FO_ENUM_ENUM_TB_RL,
  FO_ENUM_ENUM_TEXT_AFTER_EDGE,
  FO_ENUM_ENUM_TEXT_BEFORE_EDGE,
  FO_ENUM_ENUM_TEXT_BOTTOM,
  FO_ENUM_ENUM_TEXT_TOP,
  FO_ENUM_ENUM_THICK,
  FO_ENUM_ENUM_THIN,
  FO_ENUM_ENUM_TOP,
  FO_ENUM_ENUM_TRADITIONAL,
  FO_ENUM_ENUM_TRANSPARENT,
  FO_ENUM_ENUM_TREAT_AS_SPACE,
  FO_ENUM_ENUM_TREAT_AS_ZERO_WIDTH_SPACE,
  FO_ENUM_ENUM_TRUE,
  FO_ENUM_ENUM_ULTRA_CONDENSED,
  FO_ENUM_ENUM_ULTRA_EXPANDED,
  FO_ENUM_ENUM_UNBOUNDED,
  FO_ENUM_ENUM_UNDERLINE,
  FO_ENUM_ENUM_UNIFORM,
  FO_ENUM_ENUM_UPPERCASE,
  FO_ENUM_ENUM_USE_CONTENT,
  FO_ENUM_ENUM_USE_FONT_METRICS,
  FO_ENUM_ENUM_USE_NORMAL_STYLESHEET,
  FO_ENUM_ENUM_USE_SCRIPT,
  FO_ENUM_ENUM_USE_TARGET_PROCESSING_CONTEXT,
  FO_ENUM_ENUM_VISIBLE,
  FO_ENUM_ENUM_VISITED,
  FO_ENUM_ENUM_WIDER,
  FO_ENUM_ENUM_WRAP,
  FO_ENUM_ENUM_XSL_ANY,
  FO_ENUM_ENUM_XSL_BEFORE_FLOAT_SEPARATOR,
  FO_ENUM_ENUM_XSL_FOLLOWING,
  FO_ENUM_ENUM_XSL_FOOTNOTE_SEPARATOR,
  FO_ENUM_ENUM_XSL_PRECEDING,
  FO_ENUM_ENUM_XSL_REGION_AFTER,
  FO_ENUM_ENUM_XSL_REGION_BEFORE,
  FO_ENUM_ENUM_XSL_REGION_BODY,
  FO_ENUM_ENUM_XSL_REGION_END,
  FO_ENUM_ENUM_XSL_REGION_START,
  FO_ENUM_ENUM_XX_LARGE,
  FO_ENUM_ENUM_XX_SMALL,
  FO_ENUM_ENUM_X_FAST,
  FO_ENUM_ENUM_X_HIGH,
  FO_ENUM_ENUM_X_LARGE,
  FO_ENUM_ENUM_X_LOUD,
  FO_ENUM_ENUM_X_LOW,
  FO_ENUM_ENUM_X_SLOW,
  FO_ENUM_ENUM_X_SMALL,
  FO_ENUM_ENUM_X_SOFT,
  FO_ENUM_ENUM__180,
  FO_ENUM_ENUM__270,
  FO_ENUM_ENUM__90,
  FO_ENUM_ENUM_LIMIT
} FoEnumEnum;

GType fo_enum_enum_get_type (void);
#define FO_TYPE_ENUM_ENUM fo_enum_enum_get_type ()

/**
 * FoEnumFactory:
 *
 * Instance of #FoEnumFactory.
 **/
typedef struct _FoEnumFactory      FoEnumFactory;

/**
 * FoEnumFactoryClass:
 *
 * Class structure for #FoEnumFactory.
 **/
typedef struct _FoEnumFactoryClass FoEnumFactoryClass;


#define FO_TYPE_ENUM_FACTORY              (fo_enum_factory_get_type ())
#define FO_ENUM_FACTORY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_ENUM_FACTORY, FoEnumFactory))
#define FO_ENUM_FACTORY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_ENUM_FACTORY, FoEnumFactoryClass))
#define FO_IS_ENUM_FACTORY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_ENUM_FACTORY))
#define FO_IS_ENUM_FACTORY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_ENUM_FACTORY))
#define FO_ENUM_FACTORY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_ENUM_FACTORY, FoEnumFactoryClass))


GType           fo_enum_factory_get_type          (void) G_GNUC_CONST;
FoEnumFactory * fo_enum_factory_new               (void);

FoDatatype *    fo_enum_factory_get_enum_by_value (FoEnumEnum   enum_value);
FoDatatype *    fo_enum_factory_get_enum_by_nick  (const gchar *name);

G_END_DECLS

#endif /* !__FO_ENUM_FACTORY_H__ */
