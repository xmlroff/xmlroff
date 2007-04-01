/* Fo
 * fo-context-util.c: Utility functions for FoContext objects
 *
 * Copyright (C) 2001 Sun Microsystems
 *
 * $Id: fo-context-util.h,v 1.4 2004/03/24 11:49:43 tonygraham Exp $
 *
 * See Copying for the status of this software.
 */

#ifndef __FO_CONTEXT_UTIL_H__
#define __FO_CONTEXT_UTIL_H__

#include <libfo/fo-utils.h>
#include <fo/fo-fo.h>
#include <fo-context.h>

void fo_context_util_height_width_resolve    (FoContext *current_context,
					      FoContext *parent_context);
void fo_context_util_keeps_resolve           (FoContext *current_context,
					      FoContext *parent_context);
void fo_context_util_paddings_resolve        (FoContext *current_context,
					      FoContext *parent_context);
void fo_context_util_spaces_resolve          (FoContext *context,
					      FoArea    *reference_area);
void fo_context_util_length_ranges_resolve   (FoContext *context,
					      FoArea    *reference_area);
void fo_context_util_margins_resolve         (FoContext *current_context,
					      FoContext *parent_context);
void fo_context_util_margins_indents_resolve (FoFo      *fo,
					      FoContext *current_context,
					      FoContext *parent_context);
void fo_context_util_border_resolve          (FoContext *current_context,
					      FoContext *parent_context);
void fo_context_util_dominant_baseline_resolve (FoContext *current_context,
						FoContext *parent_context);


G_END_DECLS

#endif /* __FO_CONTEXT_UTIL_H__ */
