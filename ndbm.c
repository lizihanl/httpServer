#include <stdio.h>
#include <stdlib.h>
#include <db.h>

int main() {
    DB *db;
    int ret;
    if ((ret = db_create(&db, NULL, 0)) != 0) {
        fprintf(stderr, "Failed to create DB: %s\n", db_strerror(ret));
        exit(1);
    }
    if ((ret = db->open(db, NULL, "test.db", NULL, DB_HASH, DB_RDONLY, 0664)) != 0) {
        fprintf(stderr, "Failed to open DB: %s\n", db_strerror(ret));
        exit(1);
    }

    DBT key, value;
    memset(&key, 0, sizeof(key));
    memset(&value, 0, sizeof(value));
    datum dbkey, dbvalue;
    dbkey.dptr = key.data;
    dbkey.dsize = key.size;
    dbvalue.dptr = value.data;
    dbvalue.dsize = value.size;

    for (dbkey = dbm_firstkey(db); dbkey.dptr != NULL; dbkey = dbm_nextkey(db)) {
        dbvalue = dbm_fetch(db, dbkey);
        printf("%.*s: %.*s\n", (int)dbkey.dsize, (char *)dbkey.dptr, (int)dbvalue.dsize, (char *)dbvalue.dptr);
    }

    db->close(db, 0);
}