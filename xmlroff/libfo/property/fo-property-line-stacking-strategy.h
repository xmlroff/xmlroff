/* Fo
 * fo-property-line-stacking-strategy.h: 'line-stacking-strategy' property
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007-2008 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_LINE_STACKING_STRATEGY_H__
#define __FO_PROPERTY_LINE_STACKING_STRATEGY_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* line-stacking-strategy */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* line-height | font-height | max-height | inherit */
/* Initial value: max-height */

#define FO_TYPE_PROPERTY_LINE_STACKING_STRATEGY              (fo_property_line_stacking_strategy_get_type ())
#define FO_PROPERTY_LINE_STACKING_STRATEGY(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_LINE_STACKING_STRATEGY, FoPropertyLineStackingStrategy))
#define FO_PROPERTY_LINE_STACKING_STRATEGY_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_LINE_STACKING_STRATEGY, FoPropertyLineStackingStrategyClass))
#define FO_IS_PROPERTY_LINE_STACKING_STRATEGY(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_LINE_STACKING_STRATEGY))
#define FO_IS_PROPERTY_LINE_STACKING_STRATEGY_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_LINE_STACKING_STRATEGY))
#define FO_PROPERTY_LINE_STACKING_STRATEGY_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_LINE_STACKING_STRATEGY, FoPropertyLineStackingStrategyClass))


typedef struct _FoPropertyLineStackingStrategy      FoPropertyLineStackingStrategy;
typedef struct _FoPropertyLineStackingStrategyClass FoPropertyLineStackingStrategyClass;

GType        fo_property_line_stacking_strategy_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_line_stacking_strategy_new         (void);
FoProperty * fo_property_line_stacking_strategy_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_LINE_STACKING_STRATEGY_H__ */
