/* Fo
 * fo-enum.c: Enum datatype
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#include "fo-utils.h"
#include "fo-datatype.h"
#include "fo-datatype-private.h"
#include "fo-enum.h"


enum {
  PROP_0,
  PROP_ENUM_CLASS,
  PROP_VALUE
};

struct _FoEnum
{
  FoDatatype parent_instance;

  GEnumClass *enum_class;
  FoEnumEnum  value;
};

struct _FoEnumClass
{
  FoDatatypeClass parent_class;
};

GType
fo_enum_enum_get_type (void)
{
  static GType etype = 0;
  if (etype == 0)
    {
      static const GEnumValue values[] = {
        { FO_ENUM_ENUM_UNSPECIFIED, "FO_ENUM_ENUM_UNSPECIFIED", "unspecified" },
	{ FO_ENUM_ENUM_0, "FO_ENUM_ENUM_0", "0" },
	{ FO_ENUM_ENUM_100, "FO_ENUM_ENUM_100", "100" },
	{ FO_ENUM_ENUM_180, "FO_ENUM_ENUM_180", "180" },
	{ FO_ENUM_ENUM_200, "FO_ENUM_ENUM_200", "200" },
	{ FO_ENUM_ENUM_270, "FO_ENUM_ENUM_270", "270" },
	{ FO_ENUM_ENUM_300, "FO_ENUM_ENUM_300", "300" },
	{ FO_ENUM_ENUM_400, "FO_ENUM_ENUM_400", "400" },
	{ FO_ENUM_ENUM_500, "FO_ENUM_ENUM_500", "500" },
	{ FO_ENUM_ENUM_600, "FO_ENUM_ENUM_600", "600" },
	{ FO_ENUM_ENUM_700, "FO_ENUM_ENUM_700", "700" },
	{ FO_ENUM_ENUM_800, "FO_ENUM_ENUM_800", "800" },
	{ FO_ENUM_ENUM_90, "FO_ENUM_ENUM_90", "90" },
	{ FO_ENUM_ENUM_900, "FO_ENUM_ENUM_900", "900" },
	{ FO_ENUM_ENUM_ABOVE, "FO_ENUM_ENUM_ABOVE", "above" },
	{ FO_ENUM_ENUM_ABSOLUTE, "FO_ENUM_ENUM_ABSOLUTE", "absolute" },
	{ FO_ENUM_ENUM_ABSOLUTE_COLORIMETRIC, "FO_ENUM_ENUM_ABSOLUTE_COLORIMETRIC", "absolute-colorimetric" },
	{ FO_ENUM_ENUM_ACTIVE, "FO_ENUM_ENUM_ACTIVE", "active" },
	{ FO_ENUM_ENUM_AFTER, "FO_ENUM_ENUM_AFTER", "after" },
	{ FO_ENUM_ENUM_AFTER_EDGE, "FO_ENUM_ENUM_AFTER_EDGE", "after-edge" },
	{ FO_ENUM_ENUM_ALL, "FO_ENUM_ENUM_ALL", "all" },
	{ FO_ENUM_ENUM_ALPHABETIC, "FO_ENUM_ENUM_ALPHABETIC", "alphabetic" },
	{ FO_ENUM_ENUM_ALWAYS, "FO_ENUM_ENUM_ALWAYS", "always" },
	{ FO_ENUM_ENUM_ANY, "FO_ENUM_ENUM_ANY", "any" },
	{ FO_ENUM_ENUM_AUTO, "FO_ENUM_ENUM_AUTO", "auto" },
	{ FO_ENUM_ENUM_AUTO_EVEN, "FO_ENUM_ENUM_AUTO_EVEN", "auto-even" },
	{ FO_ENUM_ENUM_AUTO_ODD, "FO_ENUM_ENUM_AUTO_ODD", "auto-odd" },
	{ FO_ENUM_ENUM_AVOID, "FO_ENUM_ENUM_AVOID", "avoid" },
	{ FO_ENUM_ENUM_BACKSLANT, "FO_ENUM_ENUM_BACKSLANT", "backslant" },
	{ FO_ENUM_ENUM_BASELINE, "FO_ENUM_ENUM_BASELINE", "baseline" },
	{ FO_ENUM_ENUM_BEFORE, "FO_ENUM_ENUM_BEFORE", "before" },
	{ FO_ENUM_ENUM_BEFORE_EDGE, "FO_ENUM_ENUM_BEFORE_EDGE", "before-edge" },
	{ FO_ENUM_ENUM_BEHIND, "FO_ENUM_ENUM_BEHIND", "behind" },
	{ FO_ENUM_ENUM_BELOW, "FO_ENUM_ENUM_BELOW", "below" },
	{ FO_ENUM_ENUM_BIDI_OVERRIDE, "FO_ENUM_ENUM_BIDI_OVERRIDE", "bidi-override" },
	{ FO_ENUM_ENUM_BLANK, "FO_ENUM_ENUM_BLANK", "blank" },
	{ FO_ENUM_ENUM_BLINK, "FO_ENUM_ENUM_BLINK", "blink" },
	{ FO_ENUM_ENUM_BLOCK, "FO_ENUM_ENUM_BLOCK", "block" },
	{ FO_ENUM_ENUM_BOLD, "FO_ENUM_ENUM_BOLD", "bold" },
	{ FO_ENUM_ENUM_BOLDER, "FO_ENUM_ENUM_BOLDER", "bolder" },
	{ FO_ENUM_ENUM_BOTH, "FO_ENUM_ENUM_BOTH", "both" },
	{ FO_ENUM_ENUM_BOTTOM, "FO_ENUM_ENUM_BOTTOM", "bottom" },
	{ FO_ENUM_ENUM_BOUNDED_IN_ONE_DIMENSION, "FO_ENUM_ENUM_BOUNDED_IN_ONE_DIMENSION", "bounded-in-one-dimension" },
	{ FO_ENUM_ENUM_CAPITALIZE, "FO_ENUM_ENUM_CAPITALIZE", "capitalize" },
	{ FO_ENUM_ENUM_CAPTION, "FO_ENUM_ENUM_CAPTION", "caption" },
	{ FO_ENUM_ENUM_CENTER, "FO_ENUM_ENUM_CENTER", "center" },
	{ FO_ENUM_ENUM_CENTER_LEFT, "FO_ENUM_ENUM_CENTER_LEFT", "center-left" },
	{ FO_ENUM_ENUM_CENTER_RIGHT, "FO_ENUM_ENUM_CENTER_RIGHT", "center-right" },
	{ FO_ENUM_ENUM_CENTRAL, "FO_ENUM_ENUM_CENTRAL", "central" },
	{ FO_ENUM_ENUM_CHARACTER_BY_CHARACTER, "FO_ENUM_ENUM_CHARACTER_BY_CHARACTER", "character-by-character" },
	{ FO_ENUM_ENUM_CODE, "FO_ENUM_ENUM_CODE", "code" },
	{ FO_ENUM_ENUM_COLLAPSE, "FO_ENUM_ENUM_COLLAPSE", "collapse" },
	{ FO_ENUM_ENUM_COLLAPSE_WITH_PRECEDENCE, "FO_ENUM_ENUM_COLLAPSE_WITH_PRECEDENCE", "collapse-with-precedence" },
	{ FO_ENUM_ENUM_COLUMN, "FO_ENUM_ENUM_COLUMN", "column" },
	{ FO_ENUM_ENUM_CONDENSED, "FO_ENUM_ENUM_CONDENSED", "condensed" },
	{ FO_ENUM_ENUM_CONSIDER_SHIFTS, "FO_ENUM_ENUM_CONSIDER_SHIFTS", "consider-shifts" },
	{ FO_ENUM_ENUM_CONTINUOUS, "FO_ENUM_ENUM_CONTINUOUS", "continuous" },
	{ FO_ENUM_ENUM_CURSIVE, "FO_ENUM_ENUM_CURSIVE", "cursive" },
	{ FO_ENUM_ENUM_DASHED, "FO_ENUM_ENUM_DASHED", "dashed" },
	{ FO_ENUM_ENUM_DIGITS, "FO_ENUM_ENUM_DIGITS", "digits" },
	{ FO_ENUM_ENUM_DISREGARD_SHIFTS, "FO_ENUM_ENUM_DISREGARD_SHIFTS", "disregard-shifts" },
	{ FO_ENUM_ENUM_DOCUMENT, "FO_ENUM_ENUM_DOCUMENT", "document" },
	{ FO_ENUM_ENUM_DOCUMENT_ROOT, "FO_ENUM_ENUM_DOCUMENT_ROOT", "document-root" },
	{ FO_ENUM_ENUM_DOTS, "FO_ENUM_ENUM_DOTS", "dots" },
	{ FO_ENUM_ENUM_DOTTED, "FO_ENUM_ENUM_DOTTED", "dotted" },
	{ FO_ENUM_ENUM_DOUBLE, "FO_ENUM_ENUM_DOUBLE", "double" },
	{ FO_ENUM_ENUM_EMBED, "FO_ENUM_ENUM_EMBED", "embed" },
	{ FO_ENUM_ENUM_EMPTY, "FO_ENUM_ENUM_EMPTY", "empty" },
	{ FO_ENUM_ENUM_END, "FO_ENUM_ENUM_END", "end" },
	{ FO_ENUM_ENUM_END_ON_EVEN, "FO_ENUM_ENUM_END_ON_EVEN", "end-on-even" },
	{ FO_ENUM_ENUM_END_ON_ODD, "FO_ENUM_ENUM_END_ON_ODD", "end-on-odd" },
	{ FO_ENUM_ENUM_ERROR_IF_OVERFLOW, "FO_ENUM_ENUM_ERROR_IF_OVERFLOW", "error-if-overflow" },
	{ FO_ENUM_ENUM_EVEN, "FO_ENUM_ENUM_EVEN", "even" },
	{ FO_ENUM_ENUM_EVEN_PAGE, "FO_ENUM_ENUM_EVEN_PAGE", "even-page" },
	{ FO_ENUM_ENUM_EXPANDED, "FO_ENUM_ENUM_EXPANDED", "expanded" },
	{ FO_ENUM_ENUM_EXTRA_CONDENSED, "FO_ENUM_ENUM_EXTRA_CONDENSED", "extra-condensed" },
	{ FO_ENUM_ENUM_EXTRA_EXPANDED, "FO_ENUM_ENUM_EXTRA_EXPANDED", "extra-expanded" },
	{ FO_ENUM_ENUM_FALSE, "FO_ENUM_ENUM_FALSE", "false" },
	{ FO_ENUM_ENUM_FANTASY, "FO_ENUM_ENUM_FANTASY", "fantasy" },
	{ FO_ENUM_ENUM_FAR_LEFT, "FO_ENUM_ENUM_FAR_LEFT", "far-left" },
	{ FO_ENUM_ENUM_FAR_RIGHT, "FO_ENUM_ENUM_FAR_RIGHT", "far-right" },
	{ FO_ENUM_ENUM_FAST, "FO_ENUM_ENUM_FAST", "fast" },
	{ FO_ENUM_ENUM_FASTER, "FO_ENUM_ENUM_FASTER", "faster" },
	{ FO_ENUM_ENUM_FIRST, "FO_ENUM_ENUM_FIRST", "first" },
	{ FO_ENUM_ENUM_FIRST_INCLUDING_CARRYOVER, "FO_ENUM_ENUM_FIRST_INCLUDING_CARRYOVER", "first-including-carryover" },
	{ FO_ENUM_ENUM_FIRST_STARTING_WITHIN_PAGE, "FO_ENUM_ENUM_FIRST_STARTING_WITHIN_PAGE", "first-starting-within-page" },
	{ FO_ENUM_ENUM_FIXED, "FO_ENUM_ENUM_FIXED", "fixed" },
	{ FO_ENUM_ENUM_FOCUS, "FO_ENUM_ENUM_FOCUS", "focus" },
	{ FO_ENUM_ENUM_FONT_HEIGHT, "FO_ENUM_ENUM_FONT_HEIGHT", "font-height" },
	{ FO_ENUM_ENUM_FORCE, "FO_ENUM_ENUM_FORCE", "force" },
	{ FO_ENUM_ENUM_GROOVE, "FO_ENUM_ENUM_GROOVE", "groove" },
	{ FO_ENUM_ENUM_HANGING, "FO_ENUM_ENUM_HANGING", "hanging" },
	{ FO_ENUM_ENUM_HIDDEN, "FO_ENUM_ENUM_HIDDEN", "hidden" },
	{ FO_ENUM_ENUM_HIDE, "FO_ENUM_ENUM_HIDE", "hide" },
	{ FO_ENUM_ENUM_HIGH, "FO_ENUM_ENUM_HIGH", "high" },
	{ FO_ENUM_ENUM_HIGHER, "FO_ENUM_ENUM_HIGHER", "higher" },
	{ FO_ENUM_ENUM_HOVER, "FO_ENUM_ENUM_HOVER", "hover" },
	{ FO_ENUM_ENUM_ICON, "FO_ENUM_ENUM_ICON", "icon" },
	{ FO_ENUM_ENUM_IDEOGRAPHIC, "FO_ENUM_ENUM_IDEOGRAPHIC", "ideographic" },
	{ FO_ENUM_ENUM_IGNORE, "FO_ENUM_ENUM_IGNORE", "ignore" },
	{ FO_ENUM_ENUM_IGNORE_IF_AFTER_LINEFEED, "FO_ENUM_ENUM_IGNORE_IF_AFTER_LINEFEED", "ignore-if-after-linefeed" },
	{ FO_ENUM_ENUM_IGNORE_IF_BEFORE_LINEFEED, "FO_ENUM_ENUM_IGNORE_IF_BEFORE_LINEFEED", "ignore-if-before-linefeed" },
	{ FO_ENUM_ENUM_IGNORE_IF_SURROUNDING_LINEFEED, "FO_ENUM_ENUM_IGNORE_IF_SURROUNDING_LINEFEED", "ignore-if-surrounding-linefeed" },
	{ FO_ENUM_ENUM_INDEFINITE, "FO_ENUM_ENUM_INDEFINITE", "indefinite" },
	{ FO_ENUM_ENUM_INDENT, "FO_ENUM_ENUM_INDENT", "indent" },
	{ FO_ENUM_ENUM_INSET, "FO_ENUM_ENUM_INSET", "inset" },
	{ FO_ENUM_ENUM_INSIDE, "FO_ENUM_ENUM_INSIDE", "inside" },
	{ FO_ENUM_ENUM_INTEGER_PIXELS, "FO_ENUM_ENUM_INTEGER_PIXELS", "integer-pixels" },
	{ FO_ENUM_ENUM_ITALIC, "FO_ENUM_ENUM_ITALIC", "italic" },
	{ FO_ENUM_ENUM_JUSTIFY, "FO_ENUM_ENUM_JUSTIFY", "justify" },
	{ FO_ENUM_ENUM_LANDSCAPE, "FO_ENUM_ENUM_LANDSCAPE", "landscape" },
	{ FO_ENUM_ENUM_LARGE, "FO_ENUM_ENUM_LARGE", "large" },
	{ FO_ENUM_ENUM_LARGER, "FO_ENUM_ENUM_LARGER", "larger" },
	{ FO_ENUM_ENUM_LAST, "FO_ENUM_ENUM_LAST", "last" },
	{ FO_ENUM_ENUM_LAST_ENDING_WITHIN_PAGE, "FO_ENUM_ENUM_LAST_ENDING_WITHIN_PAGE", "last-ending-within-page" },
	{ FO_ENUM_ENUM_LAST_STARTING_WITHIN_PAGE, "FO_ENUM_ENUM_LAST_STARTING_WITHIN_PAGE", "last-starting-within-page" },
	{ FO_ENUM_ENUM_LEFT, "FO_ENUM_ENUM_LEFT", "left" },
	{ FO_ENUM_ENUM_LEFTWARDS, "FO_ENUM_ENUM_LEFTWARDS", "leftwards" },
	{ FO_ENUM_ENUM_LEFT_SIDE, "FO_ENUM_ENUM_LEFT_SIDE", "left-side" },
	{ FO_ENUM_ENUM_LEVEL, "FO_ENUM_ENUM_LEVEL", "level" },
	{ FO_ENUM_ENUM_LIGHTER, "FO_ENUM_ENUM_LIGHTER", "lighter" },
	{ FO_ENUM_ENUM_LINE, "FO_ENUM_ENUM_LINE", "line" },
	{ FO_ENUM_ENUM_LINE_HEIGHT, "FO_ENUM_ENUM_LINE_HEIGHT", "line-height" },
	{ FO_ENUM_ENUM_LINE_THROUGH, "FO_ENUM_ENUM_LINE_THROUGH", "line-through" },
	{ FO_ENUM_ENUM_LINK, "FO_ENUM_ENUM_LINK", "link" },
	{ FO_ENUM_ENUM_LOUD, "FO_ENUM_ENUM_LOUD", "loud" },
	{ FO_ENUM_ENUM_LOW, "FO_ENUM_ENUM_LOW", "low" },
	{ FO_ENUM_ENUM_LOWER, "FO_ENUM_ENUM_LOWER", "lower" },
	{ FO_ENUM_ENUM_LOWERCASE, "FO_ENUM_ENUM_LOWERCASE", "lowercase" },
	{ FO_ENUM_ENUM_LR, "FO_ENUM_ENUM_LR", "lr" },
	{ FO_ENUM_ENUM_LR_TB, "FO_ENUM_ENUM_LR_TB", "lr-tb" },
	{ FO_ENUM_ENUM_LTR, "FO_ENUM_ENUM_LTR", "ltr" },
	{ FO_ENUM_ENUM_MATHEMATICAL, "FO_ENUM_ENUM_MATHEMATICAL", "mathematical" },
	{ FO_ENUM_ENUM_MAX_HEIGHT, "FO_ENUM_ENUM_MAX_HEIGHT", "max-height" },
	{ FO_ENUM_ENUM_MEDIUM, "FO_ENUM_ENUM_MEDIUM", "medium" },
	{ FO_ENUM_ENUM_MENU, "FO_ENUM_ENUM_MENU", "menu" },
	{ FO_ENUM_ENUM_MESSAGE_BOX, "FO_ENUM_ENUM_MESSAGE_BOX", "message-box" },
	{ FO_ENUM_ENUM_MIDDLE, "FO_ENUM_ENUM_MIDDLE", "middle" },
	{ FO_ENUM_ENUM_MIX, "FO_ENUM_ENUM_MIX", "mix" },
	{ FO_ENUM_ENUM_MONOSPACE, "FO_ENUM_ENUM_MONOSPACE", "monospace" },
	{ FO_ENUM_ENUM_NARROWER, "FO_ENUM_ENUM_NARROWER", "narrower" },
	{ FO_ENUM_ENUM_NEW, "FO_ENUM_ENUM_NEW", "new" },
	{ FO_ENUM_ENUM_NONE, "FO_ENUM_ENUM_NONE", "none" },
	{ FO_ENUM_ENUM_NON_UNIFORM, "FO_ENUM_ENUM_NON_UNIFORM", "non-uniform" },
	{ FO_ENUM_ENUM_NORMAL, "FO_ENUM_ENUM_NORMAL", "normal" },
	{ FO_ENUM_ENUM_NOT_BLANK, "FO_ENUM_ENUM_NOT_BLANK", "not-blank" },
	{ FO_ENUM_ENUM_NOWRAP, "FO_ENUM_ENUM_NOWRAP", "nowrap" },
	{ FO_ENUM_ENUM_NO_BLINK, "FO_ENUM_ENUM_NO_BLINK", "no-blink" },
	{ FO_ENUM_ENUM_NO_CHANGE, "FO_ENUM_ENUM_NO_CHANGE", "no-change" },
	{ FO_ENUM_ENUM_NO_FORCE, "FO_ENUM_ENUM_NO_FORCE", "no-force" },
	{ FO_ENUM_ENUM_NO_LIMIT, "FO_ENUM_ENUM_NO_LIMIT", "no-limit" },
	{ FO_ENUM_ENUM_NO_LINE_THROUGH, "FO_ENUM_ENUM_NO_LINE_THROUGH", "no-line-through" },
	{ FO_ENUM_ENUM_NO_OVERLINE, "FO_ENUM_ENUM_NO_OVERLINE", "no-overline" },
	{ FO_ENUM_ENUM_NO_REPEAT, "FO_ENUM_ENUM_NO_REPEAT", "no-repeat" },
	{ FO_ENUM_ENUM_NO_UNDERLINE, "FO_ENUM_ENUM_NO_UNDERLINE", "no-underline" },
	{ FO_ENUM_ENUM_NO_WRAP, "FO_ENUM_ENUM_NO_WRAP", "no-wrap" },
	{ FO_ENUM_ENUM_OBLIQUE, "FO_ENUM_ENUM_OBLIQUE", "oblique" },
	{ FO_ENUM_ENUM_ODD, "FO_ENUM_ENUM_ODD", "odd" },
	{ FO_ENUM_ENUM_ODD_PAGE, "FO_ENUM_ENUM_ODD_PAGE", "odd-page" },
	{ FO_ENUM_ENUM_ONCE, "FO_ENUM_ENUM_ONCE", "once" },
	{ FO_ENUM_ENUM_OUTSET, "FO_ENUM_ENUM_OUTSET", "outset" },
	{ FO_ENUM_ENUM_OUTSIDE, "FO_ENUM_ENUM_OUTSIDE", "outside" },
	{ FO_ENUM_ENUM_OVERLINE, "FO_ENUM_ENUM_OVERLINE", "overline" },
	{ FO_ENUM_ENUM_PAGE, "FO_ENUM_ENUM_PAGE", "page" },
	{ FO_ENUM_ENUM_PAGE_SEQUENCE, "FO_ENUM_ENUM_PAGE_SEQUENCE", "page-sequence" },
	{ FO_ENUM_ENUM_PAGINATE, "FO_ENUM_ENUM_PAGINATE", "paginate" },
	{ FO_ENUM_ENUM_PERCEPTUAL, "FO_ENUM_ENUM_PERCEPTUAL", "perceptual" },
	{ FO_ENUM_ENUM_PORTRAIT, "FO_ENUM_ENUM_PORTRAIT", "portrait" },
	{ FO_ENUM_ENUM_PRE, "FO_ENUM_ENUM_PRE", "pre" },
	{ FO_ENUM_ENUM_PRESERVE, "FO_ENUM_ENUM_PRESERVE", "preserve" },
	{ FO_ENUM_ENUM_REFERENCE_AREA, "FO_ENUM_ENUM_REFERENCE_AREA", "reference-area" },
	{ FO_ENUM_ENUM_RELATIVE, "FO_ENUM_ENUM_RELATIVE", "relative" },
	{ FO_ENUM_ENUM_RELATIVE_COLORIMETRIC, "FO_ENUM_ENUM_RELATIVE_COLORIMETRIC", "relative-colorimetric" },
	{ FO_ENUM_ENUM_REPEAT, "FO_ENUM_ENUM_REPEAT", "repeat" },
	{ FO_ENUM_ENUM_REPEAT_X, "FO_ENUM_ENUM_REPEAT_X", "repeat-x" },
	{ FO_ENUM_ENUM_REPEAT_Y, "FO_ENUM_ENUM_REPEAT_Y", "repeat-y" },
	{ FO_ENUM_ENUM_REPLACE, "FO_ENUM_ENUM_REPLACE", "replace" },
	{ FO_ENUM_ENUM_RESAMPLE_ANY_METHOD, "FO_ENUM_ENUM_RESAMPLE_ANY_METHOD", "resample-any-method" },
	{ FO_ENUM_ENUM_RESET_SIZE, "FO_ENUM_ENUM_RESET_SIZE", "reset-size" },
	{ FO_ENUM_ENUM_REST, "FO_ENUM_ENUM_REST", "rest" },
	{ FO_ENUM_ENUM_RETAIN, "FO_ENUM_ENUM_RETAIN", "retain" },
	{ FO_ENUM_ENUM_RIDGE, "FO_ENUM_ENUM_RIDGE", "ridge" },
	{ FO_ENUM_ENUM_RIGHT, "FO_ENUM_ENUM_RIGHT", "right" },
	{ FO_ENUM_ENUM_RIGHTWARDS, "FO_ENUM_ENUM_RIGHTWARDS", "rightwards" },
	{ FO_ENUM_ENUM_RIGHT_SIDE, "FO_ENUM_ENUM_RIGHT_SIDE", "right-side" },
	{ FO_ENUM_ENUM_RL, "FO_ENUM_ENUM_RL", "rl" },
	{ FO_ENUM_ENUM_RL_TB, "FO_ENUM_ENUM_RL_TB", "rl-tb" },
	{ FO_ENUM_ENUM_RTL, "FO_ENUM_ENUM_RTL", "rtl" },
	{ FO_ENUM_ENUM_RULE, "FO_ENUM_ENUM_RULE", "rule" },
	{ FO_ENUM_ENUM_SANS_SERIF, "FO_ENUM_ENUM_SANS_SERIF", "sans-serif" },
	{ FO_ENUM_ENUM_SATURATION, "FO_ENUM_ENUM_SATURATION", "saturation" },
	{ FO_ENUM_ENUM_SCALE_TO_FIT, "FO_ENUM_ENUM_SCALE_TO_FIT", "scale-to-fit" },
	{ FO_ENUM_ENUM_SCROLL, "FO_ENUM_ENUM_SCROLL", "scroll" },
	{ FO_ENUM_ENUM_SEMI_CONDENSED, "FO_ENUM_ENUM_SEMI_CONDENSED", "semi-condensed" },
	{ FO_ENUM_ENUM_SEMI_EXPANDED, "FO_ENUM_ENUM_SEMI_EXPANDED", "semi-expanded" },
	{ FO_ENUM_ENUM_SEPARATE, "FO_ENUM_ENUM_SEPARATE", "separate" },
	{ FO_ENUM_ENUM_SERIF, "FO_ENUM_ENUM_SERIF", "serif" },
	{ FO_ENUM_ENUM_SHOW, "FO_ENUM_ENUM_SHOW", "show" },
	{ FO_ENUM_ENUM_SILENT, "FO_ENUM_ENUM_SILENT", "silent" },
	{ FO_ENUM_ENUM_SLOW, "FO_ENUM_ENUM_SLOW", "slow" },
	{ FO_ENUM_ENUM_SLOWER, "FO_ENUM_ENUM_SLOWER", "slower" },
	{ FO_ENUM_ENUM_SMALL, "FO_ENUM_ENUM_SMALL", "small" },
	{ FO_ENUM_ENUM_SMALLER, "FO_ENUM_ENUM_SMALLER", "smaller" },
	{ FO_ENUM_ENUM_SMALL_CAPS, "FO_ENUM_ENUM_SMALL_CAPS", "small-caps" },
	{ FO_ENUM_ENUM_SMALL_CAPTION, "FO_ENUM_ENUM_SMALL_CAPTION", "small-caption" },
	{ FO_ENUM_ENUM_SOFT, "FO_ENUM_ENUM_SOFT", "soft" },
	{ FO_ENUM_ENUM_SOLID, "FO_ENUM_ENUM_SOLID", "solid" },
	{ FO_ENUM_ENUM_SPACE, "FO_ENUM_ENUM_SPACE", "space" },
	{ FO_ENUM_ENUM_SPELL_OUT, "FO_ENUM_ENUM_SPELL_OUT", "spell-out" },
	{ FO_ENUM_ENUM_START, "FO_ENUM_ENUM_START", "start" },
	{ FO_ENUM_ENUM_STATIC, "FO_ENUM_ENUM_STATIC", "static" },
	{ FO_ENUM_ENUM_STATUS_BAR, "FO_ENUM_ENUM_STATUS_BAR", "status-bar" },
	{ FO_ENUM_ENUM_STRING, "FO_ENUM_ENUM_STRING", "string" },
	{ FO_ENUM_ENUM_SUB, "FO_ENUM_ENUM_SUB", "sub" },
	{ FO_ENUM_ENUM_SUPER, "FO_ENUM_ENUM_SUPER", "super" },
	{ FO_ENUM_ENUM_SUPPRESS, "FO_ENUM_ENUM_SUPPRESS", "suppress" },
	{ FO_ENUM_ENUM_TB, "FO_ENUM_ENUM_TB", "tb" },
	{ FO_ENUM_ENUM_TB_RL, "FO_ENUM_ENUM_TB_RL", "tb-rl" },
	{ FO_ENUM_ENUM_TEXT_AFTER_EDGE, "FO_ENUM_ENUM_TEXT_AFTER_EDGE", "text-after-edge" },
	{ FO_ENUM_ENUM_TEXT_BEFORE_EDGE, "FO_ENUM_ENUM_TEXT_BEFORE_EDGE", "text-before-edge" },
	{ FO_ENUM_ENUM_TEXT_BOTTOM, "FO_ENUM_ENUM_TEXT_BOTTOM", "text-bottom" },
	{ FO_ENUM_ENUM_TEXT_TOP, "FO_ENUM_ENUM_TEXT_TOP", "text-top" },
	{ FO_ENUM_ENUM_THICK, "FO_ENUM_ENUM_THICK", "thick" },
	{ FO_ENUM_ENUM_THIN, "FO_ENUM_ENUM_THIN", "thin" },
	{ FO_ENUM_ENUM_TOP, "FO_ENUM_ENUM_TOP", "top" },
	{ FO_ENUM_ENUM_TRADITIONAL, "FO_ENUM_ENUM_TRADITIONAL", "traditional" },
	{ FO_ENUM_ENUM_TRANSPARENT, "FO_ENUM_ENUM_TRANSPARENT", "transparent" },
	{ FO_ENUM_ENUM_TREAT_AS_SPACE, "FO_ENUM_ENUM_TREAT_AS_SPACE", "treat-as-space" },
	{ FO_ENUM_ENUM_TREAT_AS_ZERO_WIDTH_SPACE, "FO_ENUM_ENUM_TREAT_AS_ZERO_WIDTH_SPACE", "treat-as-zero-width-space" },
	{ FO_ENUM_ENUM_TRUE, "FO_ENUM_ENUM_TRUE", "true" },
	{ FO_ENUM_ENUM_ULTRA_CONDENSED, "FO_ENUM_ENUM_ULTRA_CONDENSED", "ultra-condensed" },
	{ FO_ENUM_ENUM_ULTRA_EXPANDED, "FO_ENUM_ENUM_ULTRA_EXPANDED", "ultra-expanded" },
	{ FO_ENUM_ENUM_UNBOUNDED, "FO_ENUM_ENUM_UNBOUNDED", "unbounded" },
	{ FO_ENUM_ENUM_UNDERLINE, "FO_ENUM_ENUM_UNDERLINE", "underline" },
	{ FO_ENUM_ENUM_UNIFORM, "FO_ENUM_ENUM_UNIFORM", "uniform" },
	{ FO_ENUM_ENUM_UPPERCASE, "FO_ENUM_ENUM_UPPERCASE", "uppercase" },
	{ FO_ENUM_ENUM_USE_CONTENT, "FO_ENUM_ENUM_USE_CONTENT", "use-content" },
	{ FO_ENUM_ENUM_USE_FONT_METRICS, "FO_ENUM_ENUM_USE_FONT_METRICS", "use-font-metrics" },
	{ FO_ENUM_ENUM_USE_NORMAL_STYLESHEET, "FO_ENUM_ENUM_USE_NORMAL_STYLESHEET", "use-normal-stylesheet" },
	{ FO_ENUM_ENUM_USE_SCRIPT, "FO_ENUM_ENUM_USE_SCRIPT", "use-script" },
	{ FO_ENUM_ENUM_USE_TARGET_PROCESSING_CONTEXT, "FO_ENUM_ENUM_USE_TARGET_PROCESSING_CONTEXT", "use-target-processing-context" },
	{ FO_ENUM_ENUM_VISIBLE, "FO_ENUM_ENUM_VISIBLE", "visible" },
	{ FO_ENUM_ENUM_VISITED, "FO_ENUM_ENUM_VISITED", "visited" },
	{ FO_ENUM_ENUM_WIDER, "FO_ENUM_ENUM_WIDER", "wider" },
	{ FO_ENUM_ENUM_WRAP, "FO_ENUM_ENUM_WRAP", "wrap" },
	{ FO_ENUM_ENUM_XSL_ANY, "FO_ENUM_ENUM_XSL_ANY", "xsl-any" },
	{ FO_ENUM_ENUM_XSL_BEFORE_FLOAT_SEPARATOR, "FO_ENUM_ENUM_XSL_BEFORE_FLOAT_SEPARATOR", "xsl-before-float-separator" },
	{ FO_ENUM_ENUM_XSL_FOLLOWING, "FO_ENUM_ENUM_XSL_FOLLOWING", "xsl-following" },
	{ FO_ENUM_ENUM_XSL_FOOTNOTE_SEPARATOR, "FO_ENUM_ENUM_XSL_FOOTNOTE_SEPARATOR", "xsl-footnote-separator" },
	{ FO_ENUM_ENUM_XSL_PRECEDING, "FO_ENUM_ENUM_XSL_PRECEDING", "xsl-preceding" },
	{ FO_ENUM_ENUM_XSL_REGION_AFTER, "FO_ENUM_ENUM_XSL_REGION_AFTER", "xsl-region-after" },
	{ FO_ENUM_ENUM_XSL_REGION_BEFORE, "FO_ENUM_ENUM_XSL_REGION_BEFORE", "xsl-region-before" },
	{ FO_ENUM_ENUM_XSL_REGION_BODY, "FO_ENUM_ENUM_XSL_REGION_BODY", "xsl-region-body" },
	{ FO_ENUM_ENUM_XSL_REGION_END, "FO_ENUM_ENUM_XSL_REGION_END", "xsl-region-end" },
	{ FO_ENUM_ENUM_XSL_REGION_START, "FO_ENUM_ENUM_XSL_REGION_START", "xsl-region-start" },
	{ FO_ENUM_ENUM_XX_LARGE, "FO_ENUM_ENUM_XX_LARGE", "xx-large" },
	{ FO_ENUM_ENUM_XX_SMALL, "FO_ENUM_ENUM_XX_SMALL", "xx-small" },
	{ FO_ENUM_ENUM_X_FAST, "FO_ENUM_ENUM_X_FAST", "x-fast" },
	{ FO_ENUM_ENUM_X_HIGH, "FO_ENUM_ENUM_X_HIGH", "x-high" },
	{ FO_ENUM_ENUM_X_LARGE, "FO_ENUM_ENUM_X_LARGE", "x-large" },
	{ FO_ENUM_ENUM_X_LOUD, "FO_ENUM_ENUM_X_LOUD", "x-loud" },
	{ FO_ENUM_ENUM_X_LOW, "FO_ENUM_ENUM_X_LOW", "x-low" },
	{ FO_ENUM_ENUM_X_SLOW, "FO_ENUM_ENUM_X_SLOW", "x-slow" },
	{ FO_ENUM_ENUM_X_SMALL, "FO_ENUM_ENUM_X_SMALL", "x-small" },
	{ FO_ENUM_ENUM_X_SOFT, "FO_ENUM_ENUM_X_SOFT", "x-soft" },
	{ FO_ENUM_ENUM__180, "FO_ENUM_ENUM__180", "-180" },
	{ FO_ENUM_ENUM__270, "FO_ENUM_ENUM__270", "-270" },
	{ FO_ENUM_ENUM__90, "FO_ENUM_ENUM__90", "-90" },
	{ 0, NULL, NULL }
      };
      etype = g_enum_register_static ("FoEnumEnum", values);
    }
  return etype;
}

static void fo_enum_init         (FoEnum      *fo_enum);
static void fo_enum_class_init   (FoEnumClass *klass);
static void fo_enum_set_property (GObject       *object,
				    guint          prop_id,
				    const GValue  *value,
				    GParamSpec    *pspec);
static void fo_enum_get_property (GObject       *object,
				    guint          prop_id,
				    GValue        *value,
				    GParamSpec    *pspec);
static void fo_enum_finalize     (GObject       *object);

static FoDatatype * fo_enum_copy           (FoDatatype       *datatype);
static gchar*       fo_enum_sprintf        (FoObject         *object);
static void         fo_enum_set_enum_class (FoDatatype       *fo_enum,
					    const GEnumClass *new_enum_class);
static void         fo_enum_set_value      (FoDatatype       *fo_enum,
					    const FoEnumEnum  new_value);

static gpointer parent_class;

static FoDatatype *enums[FO_ENUM_ENUM_LIMIT];

static FoDatatype *enum_alphabetic = NULL;
static FoDatatype *enum_always = NULL;
static FoDatatype *enum_traditional = NULL;

/**
 * fo_enum_get_type:
 * 
 * Register the #FoEnum object type.
 * 
 * Return value: #GType value of the #FoEnum object type.
 **/
GType
fo_enum_get_type (void)
{
  static GType object_type = 0;

  if (!object_type)
    {
      static const GTypeInfo object_info =
      {
        sizeof (FoEnumClass),
        NULL,           /* base_init */
        NULL,           /* base_finalize */
        (GClassInitFunc) fo_enum_class_init,
        NULL,           /* class_finalize */
        NULL,           /* class_data */
        sizeof (FoEnum),
        0,              /* n_preallocs */
        (GInstanceInitFunc) fo_enum_init,
	NULL		/* value_table */
      };

      object_type = g_type_register_static (FO_TYPE_DATATYPE,
                                            "FoEnum",
                                            &object_info, 0);
    }

  return object_type;
}

/**
 * fo_enum_init:
 * @fo_enum: #FoEnum object to initialise.
 * 
 * Implements #GInstanceInitFunc for #FoEnum.
 **/
void
fo_enum_init (FoEnum *fo_enum)
{
  fo_enum->enum_class = NULL;
  fo_enum->value = FO_ENUM_ENUM_UNSPECIFIED;
}

/**
 * fo_enum_class_init:
 * @klass: #FoEnumClass object to initialise.
 * 
 * Implements #GClassInitFunc for #FoEnumClass.
 **/
void
fo_enum_class_init (FoEnumClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  
  parent_class = g_type_class_peek_parent (klass);
  
  object_class->finalize = fo_enum_finalize;

  object_class->set_property = fo_enum_set_property;
  object_class->get_property = fo_enum_get_property;

  FO_OBJECT_CLASS (klass)->print_sprintf = fo_enum_sprintf;

  FO_DATATYPE_CLASS (klass)->copy = fo_enum_copy;

  int i;
  for (i = 0; i < FO_ENUM_ENUM_LIMIT; i++)
    {
      enums[i] = NULL;
    }

  g_object_class_install_property
    (object_class,
     PROP_ENUM_CLASS,
     g_param_spec_pointer ("enum-class",
			   _("enum-class"),
			   _("Enumeration class"),
			   G_PARAM_READWRITE |
			   G_PARAM_CONSTRUCT_ONLY));
  g_object_class_install_property
    (object_class,
     PROP_VALUE,
     g_param_spec_int ("value",
		       _("Value"),
		       _("Enum value"),
		       0,
		       FO_ENUM_ENUM_LIMIT,
		       FO_ENUM_ENUM_UNSPECIFIED,
		       G_PARAM_READWRITE |
		       G_PARAM_CONSTRUCT_ONLY));
}

/**
 * fo_enum_finalize:
 * @object: #FoEnum object to finalize.
 * 
 * Implements #GObjectFinalizeFunc for #FoEnum.
 **/
void
fo_enum_finalize (GObject *object)
{
  FoEnum *fo_enum;

  fo_enum = FO_ENUM (object);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}


/**
 * fo_enum_get_property:
 * @object:  #GObject whose property will be retrieved.
 * @prop_id: Property ID assigned when property registered.
 * @value:   #GValue to set with property value.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectGetPropertyFunc for #FoEnum.
 **/
void
fo_enum_get_property (GObject         *object,
		      guint            prop_id,
		      GValue          *value,
		      GParamSpec      *pspec)
{
  FoDatatype *fo_enum;

  fo_enum = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_ENUM_CLASS:
      g_value_set_pointer (value, fo_enum_get_enum_class (fo_enum));
      break;
    case PROP_VALUE:
      g_value_set_int (value, fo_enum_get_value (fo_enum));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_enum_set_property:
 * @object:  #GObject whose property will be set.
 * @prop_id: Property ID assigned when property registered.
 * @value:   New value for property.
 * @pspec:   Parameter specification for this property type.
 * 
 * Implements #GObjectSetPropertyFunc for #FoEnum.
 **/
void
fo_enum_set_property (GObject         *object,
		      guint            prop_id,
		      const GValue    *value,
		      GParamSpec      *pspec)
{
  FoDatatype *fo_enum;

  fo_enum = FO_DATATYPE (object);

  switch (prop_id)
    {
    case PROP_ENUM_CLASS:
      fo_enum_set_enum_class (fo_enum, g_value_get_pointer (value));
      break;
    case PROP_VALUE:
      fo_enum_set_value (fo_enum, g_value_get_int (value));
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

/**
 * fo_enum_new:
 * 
 * Creates a new #FoEnum initialized to default value.
 * 
 * Return value: The new #FoEnum.
 **/
FoDatatype *
fo_enum_new (void)
{
  FoDatatype *fo_enum;

  fo_enum = FO_DATATYPE (g_object_new (fo_enum_get_type (), NULL));
  
  return fo_enum;
}

/**
 * fo_enum_new_with_value:
 * @enum_class: #GEnumClass of the new #FoEnum.
 * @value:      Value of the new #FoEnum.
 * 
 * Creates a new #FoEnum set to @value and @enum_class.
 * 
 * Return value: The new #FoEnum.
 **/
FoDatatype*
fo_enum_new_with_value (const GEnumClass *enum_class,
			const FoEnumEnum  value)
{
  FoDatatype *fo_enum = fo_enum_new ();

  fo_enum_set_enum_class (fo_enum, enum_class);
  fo_enum_set_value (fo_enum, value);

  return fo_enum;
}

/**
 * fo_enum_get_enum_class:
 * @fo_enum: #FoEnum.
 * 
 * Get the enumeration class of @fo_enum.
 * 
 * Return value: Enumeration class of @fo_enum.
 **/
GEnumClass*
fo_enum_get_enum_class (FoDatatype *fo_enum)
{
  g_return_val_if_fail (fo_enum != NULL, 0);
  g_return_val_if_fail (FO_IS_ENUM (fo_enum), 0);

  return FO_ENUM (fo_enum)->enum_class;
}

/**
 * fo_enum_set_value:
 * @fo_enum:    #FoEnum.
 * @new_enum_class: New #GEnumClass for @fo_enum.
 * 
 * Set the #GEnumClass of @fo_enum.
 **/
void
fo_enum_set_enum_class (FoDatatype       *fo_enum,
			const GEnumClass *new_enum_class)
{
  g_return_if_fail (fo_enum != NULL);
  g_return_if_fail (FO_IS_ENUM (fo_enum));

  FO_ENUM (fo_enum)->enum_class = (GEnumClass *) new_enum_class;
  /*g_object_notify(G_OBJECT (fo_enum), "enum_class");*/
}

/**
 * fo_enum_get_value:
 * @fo_enum: #FoEnum.
 * 
 * Get the value of @fo_enum.
 * 
 * Return value: Numeric value of @fo_enum.
 **/
FoEnumEnum
fo_enum_get_value (FoDatatype *fo_enum)
{
  g_return_val_if_fail (fo_enum != NULL, 0);
  g_return_val_if_fail (FO_IS_ENUM (fo_enum), 0);

  return FO_ENUM (fo_enum)->value;
}

/**
 * fo_enum_get_nick:
 * @fo_enum: The #FoEnum.
 * 
 * Gets the 'nickname' string of @fo_enum.
 *
 * The result should not be freed.
 *
 * Return value: The 'nickname' of @fo_enum.
 **/
const gchar*
fo_enum_get_nick (FoDatatype *fo_enum)
{
  g_return_val_if_fail (fo_enum != NULL, 0);
  g_return_val_if_fail (FO_IS_ENUM (fo_enum), 0);

  return
    ((GEnumValue *) g_enum_get_value (FO_ENUM (fo_enum)->enum_class,
				      FO_ENUM (fo_enum)->value))->value_nick;
}

/**
 * fo_enum_set_value:
 * @fo_enum:    #FoEnum.
 * @new_value: New value for @fo_enum.
 * 
 * Set the value of @fo_enum.
 **/
void
fo_enum_set_value (FoDatatype      *fo_enum,
		   const FoEnumEnum new_value)
{
  g_return_if_fail (fo_enum != NULL);
  g_return_if_fail (FO_IS_ENUM (fo_enum));

  FO_ENUM (fo_enum)->value = new_value;
  /*g_object_notify(G_OBJECT (fo_enum), "value");*/
}

/**
 * fo_enum_copy:
 * @datatype: #FoEnum to be copied.
 * 
 * Create a copy of @datatype.
 * 
 * Return value: New #FoEnum.
 **/
FoDatatype*
fo_enum_copy(FoDatatype *datatype)
{
  FoDatatype* fo_enum;

  g_return_val_if_fail (datatype != NULL, NULL);
  g_return_val_if_fail (FO_IS_ENUM (datatype), NULL);

  fo_enum = fo_enum_new ();
  FO_ENUM (fo_enum)->value = FO_ENUM (datatype)->value;

  return (FO_DATATYPE (fo_enum));
}

/**
 * fo_enum_sprintf:
 * @object: #FoEnum to be printed.
 * 
 * Creates string representation of value of @object.
 *
 * String must be freed by caller.
 * 
 * Return value: String representation of @object.
 **/
gchar*
fo_enum_sprintf (FoObject *object)
{
  g_return_val_if_fail (object != NULL, NULL);
  g_return_val_if_fail (FO_IS_ENUM (object), NULL);

  return (g_strdup_printf("%s",
			  ((GEnumValue *) g_enum_get_value (FO_ENUM (object)->enum_class,
							    FO_ENUM (object)->value))
			   ->value_nick));
}

/**
 * fo_enum_get_enum_by_value:
 * @enum_value: Enumerated value from #FoEnumEnum.
 * 
 * Gets an #FoEnum corresponding to @enum_value, or %NULL if
 * @enum_value is not in the range of enumerated values.
 *
 * Return value: #FoEnum corresponding to @enum_value, or %NULL.
 **/
FoDatatype *
fo_enum_get_enum_by_value (FoEnumEnum enum_value)
{
  g_return_val_if_fail (enum_value > FO_ENUM_ENUM_UNSPECIFIED, NULL);
  g_return_val_if_fail (enum_value < FO_ENUM_ENUM_LIMIT, NULL);

  GEnumValue *enum_ptr =
    g_enum_get_value (g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      enum_value);

  if (enum_ptr != NULL)
    {
      if (enums[enum_value] == NULL)
	{
	  enums[enum_value] =
	    g_object_new (FO_TYPE_ENUM,
			  "enum-class",
			  g_type_class_ref (FO_TYPE_ENUM_ENUM),
			  "value",
			  enum_value,
			  NULL);
	}

      return enums[enum_value];
    }
  else
    {
      return NULL;
    }
}

/**
 * fo_enum_get_enum_by_nick:
 * @name: The 'nickname' of the #FoEnum.
 * 
 * Gets an #FoEnum corresponding to @name, or %NULL if
 * @name is not a 'nickname' of an #FoEnum
 *
 * Return value: #FoEnum corresponding to @name, or %NULL.
 **/
FoDatatype *
fo_enum_get_enum_by_nick (const gchar *name)
{
  g_return_val_if_fail (name != NULL, NULL);
  g_return_val_if_fail (*name != '\0', NULL);

  GEnumValue *enum_ptr =
    g_enum_get_value_by_nick (g_type_class_ref (FO_TYPE_ENUM_ENUM),
			      name);

  if (enum_ptr != NULL)
    {
      gint enum_value = enum_ptr->value;

      if (enums[enum_value] == NULL)
	{
	  enums[enum_value] =
	    g_object_new (FO_TYPE_ENUM,
			  "enum-class",
			  g_type_class_ref (FO_TYPE_ENUM_ENUM),
			  "value",
			  enum_value,
			  NULL);
	}

      return enums[enum_value];
    }
  else
    {
      return NULL;
    }
}

/**
 * fo_enum_get_enum_auto:
 * 
 * Return value: The #FoDatatype for the well-known value 'auto'.
 **/
FoDatatype*
fo_enum_get_enum_auto (void)
{
  FoDatatype *enum_auto = enums[FO_ENUM_ENUM_AUTO];

  if (enum_auto == NULL)
    {
      enum_auto =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_AUTO,
		      NULL);

      enums[FO_ENUM_ENUM_AUTO] = enum_auto;
    }

  return enum_auto;
}

/**
 * fo_enum_get_enum_baseline:
 * 
 * Return value: The #FoDatatype for the well-known value 'baseline'.
 **/
FoDatatype*
fo_enum_get_enum_baseline (void)
{
  FoDatatype *enum_baseline = enums[FO_ENUM_ENUM_BASELINE];

  if (enum_baseline == NULL)
    {
      enum_baseline =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_BASELINE,
		      NULL);

      enums[FO_ENUM_ENUM_BASELINE] = enum_baseline;
    }

  return enum_baseline;
}

/**
 * fo_enum_get_enum_ltr:
 * 
 * Return value: The #FoDatatype for the well-known value 'ltr'.
 **/
FoDatatype*
fo_enum_get_enum_ltr (void)
{
  FoDatatype *enum_ltr = enums[FO_ENUM_ENUM_LTR];

  if (enum_ltr == NULL)
    {
      enum_ltr =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_LTR,
		      NULL);

      enums[FO_ENUM_ENUM_LTR] = enum_ltr;
    }

  return enum_ltr;
}

/**
 * fo_enum_get_enum_medium:
 * 
 * Return value: The #FoDatatype for the well-known value 'medium'.
 **/
FoDatatype*
fo_enum_get_enum_medium (void)
{
  FoDatatype *enum_medium = enums[FO_ENUM_ENUM_MEDIUM];

  if (enum_medium == NULL)
    {
      enum_medium =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_MEDIUM,
		      NULL);

      enums[FO_ENUM_ENUM_MEDIUM] = enum_medium;
    }

  return enum_medium;
}

/**
 * fo_enum_get_enum_none:
 * 
 * Return value: The #FoDatatype for the well-known value 'none'.
 **/
FoDatatype*
fo_enum_get_enum_none (void)
{
  FoDatatype *enum_none = enums[FO_ENUM_ENUM_NONE];

  if (enum_none == NULL)
    {
      enum_none =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_NONE,
		      NULL);

      enums[FO_ENUM_ENUM_NONE] = enum_none;
    }

  return enum_none;
}

/**
 * fo_enum_get_alphabetic:
 * 
 * Return value: The #FoDatatype for the well-known value 'alphabetic'.
 **/
FoDatatype*
fo_enum_get_alphabetic (void)
{
  if (enum_alphabetic == NULL)
    {
      enum_alphabetic =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_ALPHABETIC,
		      NULL);
    }

  return enum_alphabetic;
}

/**
 * fo_enum_get_always:
 * 
 * Return value: The #FoDatatype for the well-known value 'always'.
 **/
FoDatatype*
fo_enum_get_always (void)
{
  if (enum_always == NULL)
    {
      enum_always =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_ALWAYS,
		      NULL);
    }

  return enum_always;
}

/**
 * fo_enum_get_traditional:
 * 
 * Return value: The #FoDatatype for the well-known value 'traditional'.
 **/
FoDatatype*
fo_enum_get_traditional (void)
{
  if (enum_traditional == NULL)
    {
      enum_traditional =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_TRADITIONAL,
		      NULL);
    }

  return enum_traditional;
}

/**
 * fo_enum_get_traditional:
 * 
 * Return value: The #FoDatatype for the well-known value 'traditional'.
 **/
FoDatatype*
fo_enum_get_hidden (void)
{
  if (enum_traditional == NULL)
    {
      enum_traditional =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_TRADITIONAL,
		      NULL);
    }

  return enum_traditional;
}

/**
 * fo_enum_get_enum_uniform:
 * 
 * Return value: The #FoDatatype for the well-known value 'uniform'.
 **/
FoDatatype*
fo_enum_get_enum_uniform (void)
{
  FoDatatype *enum_uniform = enums[FO_ENUM_ENUM_UNIFORM];

  if (enum_uniform == NULL)
    {
      enum_uniform =
	g_object_new (FO_TYPE_ENUM,
		      "enum-class",
		      g_type_class_ref (FO_TYPE_ENUM_ENUM),
		      "value",
		      FO_ENUM_ENUM_UNIFORM,
		      NULL);

      enums[FO_ENUM_ENUM_UNIFORM] = enum_uniform;
    }

  return enum_uniform;
}
