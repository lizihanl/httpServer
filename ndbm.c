#include <stdio.h>
#include <stdlib.h>
#include <ndbm.h>

int main() {
    DBM *db;
    datum key, value;

    db = dbm_open("test.db", O_RDONLY, 0);

    if (!db) {
        fprintf(stderr, "Cannot open database\n");
        return 1;
    }

    key = dbm_firstkey(db);

    while (key.dptr != NULL) {
        value = dbm_fetch(db, key);

        if (value.dptr != NULL) {
            printf("%s=%s\n", key.dptr, value.dptr);
        }

        key = dbm_nextkey(db);
    }

    dbm_close(db);

    return 0;
}