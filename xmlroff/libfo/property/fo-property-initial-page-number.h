/* Fo
 * fo-property-initial-page-number.h: 'initial-page-number' property
 *
 * Copyright (C) 2001-2006 Sun Microsystems
 * Copyright (C) 2007-2010 Menteith Consulting Ltd
 * Copyright (C) 2011 Mentea
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_INITIAL_PAGE_NUMBER_H__
#define __FO_PROPERTY_INITIAL_PAGE_NUMBER_H__

#include <libfo/fo-utils.h>
#include <libfo/property/fo-property.h>

G_BEGIN_DECLS

/* initial-page-number */
/* Inherited: FALSE */
/* Shorthand: FALSE */
/* auto | auto-odd | auto-even | <number> | inherit */
/* Initial value: auto */

#define FO_TYPE_PROPERTY_INITIAL_PAGE_NUMBER              (fo_property_initial_page_number_get_type ())
#define FO_PROPERTY_INITIAL_PAGE_NUMBER(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_INITIAL_PAGE_NUMBER, FoPropertyInitialPageNumber))
#define FO_PROPERTY_INITIAL_PAGE_NUMBER_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_INITIAL_PAGE_NUMBER, FoPropertyInitialPageNumberClass))
#define FO_IS_PROPERTY_INITIAL_PAGE_NUMBER(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_INITIAL_PAGE_NUMBER))
#define FO_IS_PROPERTY_INITIAL_PAGE_NUMBER_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_INITIAL_PAGE_NUMBER))
#define FO_PROPERTY_INITIAL_PAGE_NUMBER_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_INITIAL_PAGE_NUMBER, FoPropertyInitialPageNumberClass))


/**
 * FoPropertyInitialPageNumber:
 *
 * Instance of the 'initial-page-number' property.
 **/
typedef struct _FoPropertyInitialPageNumber      FoPropertyInitialPageNumber;

/**
 * FoPropertyInitialPageNumberClass:
 *
 * Class structure for the 'initial-page-number' property.
 **/
typedef struct _FoPropertyInitialPageNumberClass FoPropertyInitialPageNumberClass;

GType        fo_property_initial_page_number_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_initial_page_number_new         (void);
FoProperty * fo_property_initial_page_number_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_INITIAL_PAGE_NUMBER_H__ */
