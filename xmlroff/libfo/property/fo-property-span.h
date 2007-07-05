/* Fo
 * fo-property-span.h: 'span' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SPAN_H__
#define __FO_PROPERTY_SPAN_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* span */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* none | all | inherit */
/* Initial value: none */

#define FO_TYPE_PROPERTY_SPAN              (fo_property_span_get_type ())
#define FO_PROPERTY_SPAN(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SPAN, FoPropertySpan))
#define FO_PROPERTY_SPAN_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SPAN, FoPropertySpanClass))
#define FO_IS_PROPERTY_SPAN(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SPAN))
#define FO_IS_PROPERTY_SPAN_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SPAN))
#define FO_PROPERTY_SPAN_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SPAN, FoPropertySpanClass))


/**
 * FoPropertySpan:
 *
 * Instance of the 'span' property.
 **/
typedef struct _FoPropertySpan      FoPropertySpan;

/**
 * FoPropertySpanClass:
 *
 * Class structure for the 'span' property.
 **/
typedef struct _FoPropertySpanClass FoPropertySpanClass;

GType        fo_property_span_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_span_new         (void);
FoProperty * fo_property_span_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SPAN_H__ */
