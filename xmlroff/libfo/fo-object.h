/* Fo
 * fo-object.h: Base object of formatting object system
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_OBJECT_H__
#define __FO_OBJECT_H__

#include <libfo/fo-utils.h>

G_BEGIN_DECLS

#define FO_TYPE_OBJECT              (fo_object_get_type ())
#define FO_OBJECT(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_OBJECT, FoObject))
#define FO_OBJECT_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_OBJECT, FoObjectClass))
#define FO_IS_OBJECT(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_OBJECT))
#define FO_IS_OBJECT_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_OBJECT))
#define FO_OBJECT_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_OBJECT, FoObjectClass))


typedef struct _FoObject      FoObject;
typedef struct _FoObjectClass FoObjectClass;

struct _FoObject
{
  GObject parent_instance;

};

struct _FoObjectClass
{
  GObjectClass parent_class;

  void     (* debug_dump)	      (FoObject     *object,
				       gint          depth);
  char*    (* debug_sprintf)	      (FoObject     *object);
  char*    (* print_sprintf)	      (FoObject     *object);
  void     (* log_error)              (FoObject     *object,
				       GError      **error);
  void     (* log_warning)            (FoObject     *object,
				       GError      **warning);
  void     (* log_debug)              (FoObject     *object,
				       GError      **debug);
  gboolean (* log_or_propagate_error) (FoObject     *fo_object,
				       GError      **dest,
				       GError       *src);
  gboolean (* maybe_propagate_error)  (FoObject     *fo_object,
				       GError      **dest,
				       GError       *src,
				       gboolean      continue_after_error);
  guint    (* hash_func)              (gconstpointer key);
  gboolean (* equal_func)             (gconstpointer a,
				       gconstpointer b);
};

GType      fo_object_get_type               (void) G_GNUC_CONST;
FoObject * fo_object_new                    (void);

void       fo_object_debug_dump             (gpointer  object,
					     gint      depth);
gchar*     fo_object_debug_sprintf          (gpointer  object);
gchar*     fo_object_sprintf                (gpointer  object);
void       fo_object_log_error              (FoObject  *object,
					     GError  **error);
void       fo_object_log_warning            (FoObject *object,
					     GError  **warning);
void       fo_object_log_debug              (FoObject *object,
					     GError  **debug);
gboolean   fo_object_log_or_propagate_error (FoObject *fo_object,
					     GError  **dest,
					     GError   *src);
gboolean   fo_object_maybe_propagate_error  (FoObject *fo_object,
					     GError  **dest,
					     GError   *src,
					     gboolean  continue_after_error);
guint      fo_object_hash                   (FoObject *object,
					     GError  **error);
gboolean   fo_object_equal                  (FoObject *a,
					     FoObject *b,
					     GError  **error);
G_END_DECLS

#endif /* __FO_OBJECT_H__ */
