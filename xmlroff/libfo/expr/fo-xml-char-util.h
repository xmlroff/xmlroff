/* Fo
 * fo-xml-char-util.h: Utility macros and functions for XML names, etc.
 *
 * Copyright (C) 1998-2002 Daniel Veillard.
 * Copyright (C) 2001-2002 Sun Microsystems.
 * All Rights Reserved.
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * Based on 'parserInternals.h' from libxml2 by Daniel Veillard.
 *
 * !See COPYING for the status of this software.
 **/

/************************************************************************
 *									*
 * UNICODE version of the macros.      					*
 *									*
 ************************************************************************/
/**
 * IS_CHAR:
 * @c:  an UNICODE value (gunichar)
 *
 * Macro to check the following production in the XML spec:
 *
 * [2] Char ::= #x9 | #xA | #xD | [#x20-#xD7FF] | [#xE000-#xFFFD]
 *                  | [#x10000-#x10FFFF]
 * any Unicode character, excluding the surrogate blocks, FFFE, and FFFF.
 */
#define IS_CHAR(c)							\
    ((((c) >= 0x20) && ((c) <= 0xD7FF)) ||				\
     ((c) == 0x09) || ((c) == 0x0A) || ((c) == 0x0D) ||			\
     (((c) >= 0xE000) && ((c) <= 0xFFFD)) ||				\
     (((c) >= 0x10000) && ((c) <= 0x10FFFF)))

/**
 * IS_BLANK:
 * @c:  an UNICODE value (gunichar)
 *
 * Macro to check the following production in the XML spec:
 *
 * [3] S ::= (#x20 | #x9 | #xD | #xA)+
 */
#define IS_BLANK(c) (((c) == 0x20) || ((c) == 0x09) || ((c) == 0xA) ||	\
                     ((c) == 0x0D))

/**
 * IS_BASECHAR:
 * @c:  an UNICODE value (gunichar)
 *
 * Macro to check the following production in the XML spec:
 *
 * [85] BaseChar ::= ... long list see REC ...
 */
#define IS_BASECHAR(c) fo_is_basechar(c)

/**
 * IS_DIGIT:
 * @c:  an UNICODE value (gunichar)
 *
 * Macro to check the following production in the XML spec:
 *
 * [88] Digit ::= ... long list see REC ...
 */
#define IS_DIGIT(c) fo_is_digit(c)

/**
 * IS_COMBINING:
 * @c:  an UNICODE value (gunichar)
 *
 * Macro to check the following production in the XML spec:
 *
 * [87] CombiningChar ::= ... long list see REC ...
 */
#define IS_COMBINING(c) fo_is_combining(c)

/**
 * IS_EXTENDER:
 * @c:  an UNICODE value (gunichar)
 *
 * Macro to check the following production in the XML spec:
 *
 *
 * [89] Extender ::= #x00B7 | #x02D0 | #x02D1 | #x0387 | #x0640 |
 *                   #x0E46 | #x0EC6 | #x3005 | [#x3031-#x3035] |
 *                   [#x309D-#x309E] | [#x30FC-#x30FE]
 */
#define IS_EXTENDER(c) fo_is_extender(c)

/**
 * IS_IDEOGRAPHIC:
 * @c:  an UNICODE value (gunichar)
 *
 * Macro to check the following production in the XML spec:
 *
 *
 * [86] Ideographic ::= [#x4E00-#x9FA5] | #x3007 | [#x3021-#x3029]
 */
#define IS_IDEOGRAPHIC(c) fo_is_ideographic(c)

/**
 * IS_LETTER:
 * @c:  an UNICODE value (gunichar)
 *
 * Macro to check the following production in the XML spec:
 *
 *
 * [84] Letter ::= BaseChar | Ideographic 
 */
#define IS_LETTER(c) (IS_BASECHAR(c) || IS_IDEOGRAPHIC(c))


/*
 * Function to finish the work of the macros where needed.
 */
gboolean fo_is_basechar    (gunichar c);
gboolean fo_is_blank	   (gunichar c);
gboolean fo_is_letter	   (gunichar c);
gboolean fo_is_digit	   (gunichar c);
gboolean fo_is_ideographic (gunichar c);
gboolean fo_is_extender	   (gunichar c);
gboolean fo_is_combining   (gunichar c);
gboolean fo_is_char	   (gunichar c);
