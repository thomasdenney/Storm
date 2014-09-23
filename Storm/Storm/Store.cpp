#include "Store.h"

namespace Storm {
    Store::Store(const char * databaseName, bool readOnly) {
        bool dbOpenSuccessfully;
        if (readOnly) {
            dbOpenSuccessfully = sqlite3_open_v2(databaseName, &db, SQLITE_OPEN_READONLY, NULL) == SQLITE_OK;
        }
        else {
            dbOpenSuccessfully = sqlite3_open(databaseName, &db) == SQLITE_OK;
        }
        if (!dbOpenSuccessfully) {
            std::cout << "Warning: failed to successfully open database: " << sqlite3_errmsg(db) << std::endl;
        }
    }
    
    Store::~Store() {
        sqlite3_close(db);
    }
    
    sqlite3_int64 Store::LastInsertID() {
        //Can do some safety checks here but I don't need to yet
        return sqlite3_last_insert_rowid(db);
    }
}