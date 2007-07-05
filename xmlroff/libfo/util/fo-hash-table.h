/* Fo
 * fo-hash_table.h: HashTable hash_table
 *
 * Copyright (C) 2001 Sun Microsystems
 * Copyright (C) 2007 Menteith Consulting Ltd
 *
 * See COPYING for the status of this software.
 */

#ifndef __FO_HASH_TABLE_H__
#define __FO_HASH_TABLE_H__

#include <libfo/fo-utils.h>
#include <libfo/fo-object.h>

G_BEGIN_DECLS

#define FO_TYPE_HASH_TABLE              (fo_hash_table_get_type ())
#define FO_HASH_TABLE(object)           (G_TYPE_CHECK_INSTANCE_CAST ((object), FO_TYPE_HASH_TABLE, FoHashTable))
#define FO_HASH_TABLE_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), FO_TYPE_HASH_TABLE, FoHashTableClass))
#define FO_IS_HASH_TABLE(object)        (G_TYPE_CHECK_INSTANCE_TYPE ((object), FO_TYPE_HASH_TABLE))
#define FO_IS_HASH_TABLE_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), FO_TYPE_HASH_TABLE))
#define FO_HASH_TABLE_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), FO_TYPE_HASH_TABLE, FoHashTableClass))

typedef struct _FoHashTable      FoHashTable;
typedef struct _FoHashTableClass FoHashTableClass;

#define FO_HASH_TABLE_ERROR fo_hash_table_error_quark ()
GQuark fo_hash_table_error_quark (void);

GType         fo_hash_table_get_type  (void) G_GNUC_CONST;
FoHashTable * fo_hash_table_new       (void);

void       fo_hash_table_insert  (FoHashTable *fo_hash_table,
				  FoObject    *key,
				  FoObject    *value,
				  GError     **error);
void       fo_hash_table_replace (FoHashTable *fo_hash_table,
				  FoObject    *key,
				  FoObject    *value,
				  GError     **error);
gboolean   fo_hash_table_remove  (FoHashTable *fo_hash_table,
				  FoObject    *key,
				  GError     **error);
FoObject * fo_hash_table_lookup  (FoHashTable *fo_hash_table,
				  FoObject    *key,
				  GError     **error);
guint      fo_hash_table_size    (FoHashTable *fo_hash_table);

G_END_DECLS

#endif /* !__FO_HASH_TABLE_H__ */
