/* Fo
 * fo-declarations.h: 'declarations' formatting object
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_DECLARATIONS_H__
#define __FO_DECLARATIONS_H__

#include <libfo/fo-utils.h>
#include <libfo/fo/fo-fo.h>

G_BEGIN_DECLS

typedef struct _FoDeclarations      FoDeclarations;
typedef struct _FoDeclarationsClass FoDeclarationsClass;

#define FO_TYPE_DECLARATIONS              (fo_declarations_get_type ())
#define FO_DECLARATIONS(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_DECLARATIONS, FoDeclarations))
#define FO_DECLARATIONS_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_DECLARATIONS, FoDeclarationsClass))
#define FO_IS_DECLARATIONS(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_DECLARATIONS))
#define FO_IS_DECLARATIONS_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_DECLARATIONS))
#define FO_DECLARATIONS_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_DECLARATIONS, FoDeclarationsClass))


GType        fo_declarations_get_type (void) G_GNUC_CONST;
FoFo *       fo_declarations_new      (void);


G_END_DECLS

#endif /* !__FO_DECLARATIONS_H__ */
