#include "Storm.h"

namespace Storm {
    Store::Store(const char * databaseName) {
        bool dbOpenSuccessfully = sqlite3_open(databaseName, &db) == SQLITE_OK;
        if (!dbOpenSuccessfully) {
            std::cout << "Warning: failed to successfully open database" << std::endl;
        }
    }
    
    Store::~Store() {
        sqlite3_close(db);
    }
}