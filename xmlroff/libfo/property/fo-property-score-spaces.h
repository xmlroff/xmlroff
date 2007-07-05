/* Fo
 * fo-property-score-spaces.h: 'score-spaces' property
 *
 * Copyright (C) 2001-2005 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_PROPERTY_SCORE_SPACES_H__
#define __FO_PROPERTY_SCORE_SPACES_H__

#include <libfo/fo-utils.h>
#include <property/fo-property.h>

G_BEGIN_DECLS

/* score-spaces */
/* Inherited: TRUE */
/* Shorthand: FALSE */
/* true | false | inherit */
/* Initial value: true */

#define FO_TYPE_PROPERTY_SCORE_SPACES              (fo_property_score_spaces_get_type ())
#define FO_PROPERTY_SCORE_SPACES(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_PROPERTY_SCORE_SPACES, FoPropertyScoreSpaces))
#define FO_PROPERTY_SCORE_SPACES_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_PROPERTY_SCORE_SPACES, FoPropertyScoreSpacesClass))
#define FO_IS_PROPERTY_SCORE_SPACES(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_PROPERTY_SCORE_SPACES))
#define FO_IS_PROPERTY_SCORE_SPACES_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_PROPERTY_SCORE_SPACES))
#define FO_PROPERTY_SCORE_SPACES_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_PROPERTY_SCORE_SPACES, FoPropertyScoreSpacesClass))


/**
 * FoPropertyScoreSpaces:
 *
 * Instance of the 'score-spaces' property.
 **/
typedef struct _FoPropertyScoreSpaces      FoPropertyScoreSpaces;

/**
 * FoPropertyScoreSpacesClass:
 *
 * Class structure for the 'score-spaces' property.
 **/
typedef struct _FoPropertyScoreSpacesClass FoPropertyScoreSpacesClass;

GType        fo_property_score_spaces_get_type    (void) G_GNUC_CONST;
FoProperty * fo_property_score_spaces_new         (void);
FoProperty * fo_property_score_spaces_get_initial (void);

G_END_DECLS

#endif /* !__FO_PROPERTY_SCORE_SPACES_H__ */
