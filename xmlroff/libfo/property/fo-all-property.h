/* Fo
 * fo-all-property.h: Header file that includes all property header files
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_ALL_PROPERTY_H__
#define __FO_ALL_PROPERTY_H__

G_BEGIN_DECLS

#include <libfo/property/fo-property.h>

/* Property objects */

/* font-size goes first because the various new_from_expression()
   functions need to know about the 'font-size' property */
#include <libfo/property/fo-property-font-size.h>

#include <libfo/property/fo-property-alignment-adjust.h>
#include <libfo/property/fo-property-alignment-baseline.h>
#include <libfo/property/fo-property-background-color.h>
#include <libfo/property/fo-property-background-image.h>
#include <libfo/property/fo-property-baseline-shift.h>
#include <libfo/property/fo-property-block-progression-dimension.h>
#include <libfo/property/fo-property-block-progression-dimension-minimum.h>
#include <libfo/property/fo-property-block-progression-dimension-optimum.h>
#include <libfo/property/fo-property-block-progression-dimension-maximum.h>
#include <libfo/property/fo-property-border.h>
#include <libfo/property/fo-property-border-after-color.h>
#include <libfo/property/fo-property-border-after-precedence.h>
#include <libfo/property/fo-property-border-after-style.h>
#include <libfo/property/fo-property-border-after-width.h>
#include <libfo/property/fo-property-border-before-color.h>
#include <libfo/property/fo-property-border-before-precedence.h>
#include <libfo/property/fo-property-border-before-style.h>
#include <libfo/property/fo-property-border-before-width.h>
#include <libfo/property/fo-property-border-bottom.h>
#include <libfo/property/fo-property-border-bottom-color.h>
#include <libfo/property/fo-property-border-bottom-style.h>
#include <libfo/property/fo-property-border-bottom-width.h>
#include <libfo/property/fo-property-border-collapse.h>
#include <libfo/property/fo-property-border-color.h>
#include <libfo/property/fo-property-border-end-color.h>
#include <libfo/property/fo-property-border-end-precedence.h>
#include <libfo/property/fo-property-border-end-style.h>
#include <libfo/property/fo-property-border-end-width.h>
#include <libfo/property/fo-property-border-left.h>
#include <libfo/property/fo-property-border-left-color.h>
#include <libfo/property/fo-property-border-left-style.h>
#include <libfo/property/fo-property-border-left-width.h>
#include <libfo/property/fo-property-border-right.h>
#include <libfo/property/fo-property-border-right-color.h>
#include <libfo/property/fo-property-border-right-style.h>
#include <libfo/property/fo-property-border-right-width.h>
#include <libfo/property/fo-property-border-separation.h>
#include <libfo/property/fo-property-border-start-color.h>
#include <libfo/property/fo-property-border-start-precedence.h>
#include <libfo/property/fo-property-border-start-style.h>
#include <libfo/property/fo-property-border-start-width.h>
#include <libfo/property/fo-property-border-style.h>
#include <libfo/property/fo-property-border-top.h>
#include <libfo/property/fo-property-border-top-color.h>
#include <libfo/property/fo-property-border-top-style.h>
#include <libfo/property/fo-property-border-top-width.h>
#include <libfo/property/fo-property-border-width.h>
#include <libfo/property/fo-property-break-after.h>
#include <libfo/property/fo-property-break-before.h>
#include <libfo/property/fo-property-character.h>
#include <libfo/property/fo-property-clip.h>
#include <libfo/property/fo-property-color.h>
#include <libfo/property/fo-property-column-number.h>
#include <libfo/property/fo-property-column-width.h>
#include <libfo/property/fo-property-content-height.h>
#include <libfo/property/fo-property-content-type.h>
#include <libfo/property/fo-property-content-width.h>
#include <libfo/property/fo-property-direction.h>
#include <libfo/property/fo-property-display-align.h>
#include <libfo/property/fo-property-dominant-baseline.h>
#include <libfo/property/fo-property-end-indent.h>
#include <libfo/property/fo-property-extent.h>
#include <libfo/property/fo-property-flow-name.h>
#include <libfo/property/fo-property-font-family.h>
/* 'font-size' property already included above. */
#include <libfo/property/fo-property-font-stretch.h>
#include <libfo/property/fo-property-font-style.h>
#include <libfo/property/fo-property-font-variant.h>
#include <libfo/property/fo-property-font-weight.h>
#include <libfo/property/fo-property-format.h>
#include <libfo/property/fo-property-grouping-separator.h>
#include <libfo/property/fo-property-grouping-size.h>
#include <libfo/property/fo-property-height.h>
#include <libfo/property/fo-property-id.h>
#include <libfo/property/fo-property-inline-progression-dimension.h>
#include <libfo/property/fo-property-inline-progression-dimension-minimum.h>
#include <libfo/property/fo-property-inline-progression-dimension-optimum.h>
#include <libfo/property/fo-property-inline-progression-dimension-maximum.h>
#include <libfo/property/fo-property-keep-together.h>
#include <libfo/property/fo-property-keep-together-within-column.h>
#include <libfo/property/fo-property-keep-together-within-line.h>
#include <libfo/property/fo-property-keep-together-within-page.h>
#include <libfo/property/fo-property-keep-with-next.h>
#include <libfo/property/fo-property-keep-with-next-within-column.h>
#include <libfo/property/fo-property-keep-with-next-within-line.h>
#include <libfo/property/fo-property-keep-with-next-within-page.h>
#include <libfo/property/fo-property-keep-with-previous.h>
#include <libfo/property/fo-property-keep-with-previous-within-column.h>
#include <libfo/property/fo-property-keep-with-previous-within-line.h>
#include <libfo/property/fo-property-keep-with-previous-within-page.h>
#include <libfo/property/fo-property-letter-value.h>
#include <libfo/property/fo-property-linefeed-treatment.h>
#include <libfo/property/fo-property-line-height.h>
#include <libfo/property/fo-property-line-stacking-strategy.h>
#include <libfo/property/fo-property-margin.h>
#include <libfo/property/fo-property-margin-bottom.h>
#include <libfo/property/fo-property-margin-left.h>
#include <libfo/property/fo-property-margin-right.h>
#include <libfo/property/fo-property-margin-top.h>
#include <libfo/property/fo-property-master-name.h>
#include <libfo/property/fo-property-master-reference.h>
#include <libfo/property/fo-property-media-usage.h>
#include <libfo/property/fo-property-number-columns-repeated.h>
#include <libfo/property/fo-property-number-columns-spanned.h>
#include <libfo/property/fo-property-number-rows-spanned.h>
#include <libfo/property/fo-property-orphans.h>
#include <libfo/property/fo-property-overflow.h>
#include <libfo/property/fo-property-padding.h>
#include <libfo/property/fo-property-padding-after.h>
#include <libfo/property/fo-property-padding-after-conditionality.h>
#include <libfo/property/fo-property-padding-after-length.h>
#include <libfo/property/fo-property-padding-before.h>
#include <libfo/property/fo-property-padding-before-conditionality.h>
#include <libfo/property/fo-property-padding-before-length.h>
#include <libfo/property/fo-property-padding-bottom.h>
#include <libfo/property/fo-property-padding-end.h>
#include <libfo/property/fo-property-padding-end-conditionality.h>
#include <libfo/property/fo-property-padding-end-length.h>
#include <libfo/property/fo-property-padding-left.h>
#include <libfo/property/fo-property-padding-right.h>
#include <libfo/property/fo-property-padding-start.h>
#include <libfo/property/fo-property-padding-start-conditionality.h>
#include <libfo/property/fo-property-padding-start-length.h>
#include <libfo/property/fo-property-padding-top.h>
#include <libfo/property/fo-property-page-height.h>
#include <libfo/property/fo-property-page-width.h>
#include <libfo/property/fo-property-provisional-distance-between-starts.h>
#include <libfo/property/fo-property-provisional-label-separation.h>
#include <libfo/property/fo-property-ref-id.h>
#include <libfo/property/fo-property-region-name.h>
#include <libfo/property/fo-property-role.h>
#include <libfo/property/fo-property-scaling.h>
#include <libfo/property/fo-property-scaling-method.h>
#include <libfo/property/fo-property-score-spaces.h>
#include <libfo/property/fo-property-source-document.h>
#include <libfo/property/fo-property-space-after.h>
#include <libfo/property/fo-property-space-after-minimum.h>
#include <libfo/property/fo-property-space-after-optimum.h>
#include <libfo/property/fo-property-space-after-maximum.h>
#include <libfo/property/fo-property-space-after-precedence.h>
#include <libfo/property/fo-property-space-after-conditionality.h>
#include <libfo/property/fo-property-space-before.h>
#include <libfo/property/fo-property-space-before-minimum.h>
#include <libfo/property/fo-property-space-before-optimum.h>
#include <libfo/property/fo-property-space-before-maximum.h>
#include <libfo/property/fo-property-space-before-precedence.h>
#include <libfo/property/fo-property-space-before-conditionality.h>
#include <libfo/property/fo-property-space-end.h>
#include <libfo/property/fo-property-space-end-minimum.h>
#include <libfo/property/fo-property-space-end-optimum.h>
#include <libfo/property/fo-property-space-end-maximum.h>
#include <libfo/property/fo-property-space-end-precedence.h>
#include <libfo/property/fo-property-space-end-conditionality.h>
#include <libfo/property/fo-property-space-start.h>
#include <libfo/property/fo-property-space-start-minimum.h>
#include <libfo/property/fo-property-space-start-optimum.h>
#include <libfo/property/fo-property-space-start-maximum.h>
#include <libfo/property/fo-property-space-start-precedence.h>
#include <libfo/property/fo-property-space-start-conditionality.h>
#include <libfo/property/fo-property-span.h>
#include <libfo/property/fo-property-src.h>
#include <libfo/property/fo-property-start-indent.h>
#include <libfo/property/fo-property-table-layout.h>
#include <libfo/property/fo-property-text-align.h>
#include <libfo/property/fo-property-text-indent.h>
#include <libfo/property/fo-property-unicode-bidi.h>
#include <libfo/property/fo-property-white-space-collapse.h>
#include <libfo/property/fo-property-white-space-treatment.h>
#include <libfo/property/fo-property-widows.h>
#include <libfo/property/fo-property-width.h>
#include <libfo/property/fo-property-wrap-option.h>
#include <libfo/property/fo-property-writing-mode.h>

G_END_DECLS

#endif /* !__FO_ALL_PROPERTY_H__ */
