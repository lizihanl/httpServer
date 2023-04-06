#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <db.h>
#include <string.h>

int main() {
    DB* db;
    int ret = db_create(&db, NULL, 0);
    if (ret != 0) {
        // handle error
    }

// Open the database in read-only mode
    int flags = DB_RDONLY;
    ret = db->open(db, NULL, "mydb.db", NULL, DB_BTREE, flags, 0);
    if (ret != 0) {
        // handle error
    }

// Create a cursor to iterate over the key-value pairs
    DBC* cursor;
    ret = db->cursor(db, NULL, &cursor, 0);
    if (ret != 0) {
        // handle error
    }

// Iterate over the key-value pairs and print them
    DBT key, data;
    memset(&key, 0, sizeof(key));
    memset(&data, 0, sizeof(data));

    while ((ret = cursor->c_get(cursor, &key, &data, DB_NEXT)) == 0) {
        printf("Key: %.*s, Data: %.*s\n", (int)key.size, (char*)key.data, (int)data.size, (char*)data.data);
    }

    if (ret != DB_NOTFOUND) {
        // handle error
    }

// Close the cursor and the database
    cursor->c_close(cursor);
    db->close(db, 0);

    return 0;
}