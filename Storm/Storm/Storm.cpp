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
    
    //Query
    
    Query::Query(std::shared_ptr<Store> store, std::string query) {
        this->query = query;
        this->store = store;
        int status = sqlite3_prepare_v2(store->db, query.c_str(), -1, &statement, NULL);
        if (status != SQLITE_OK) {
            std::cout << "Error preparing statement" << std::endl;
        }
    }
    
    Query::~Query() {
        sqlite3_finalize(statement);
    }
    
    bool Query::Next() {
        //Could check for other values here, but I don't need to for Storm v0.0.1
        return sqlite3_step(statement) == SQLITE_ROW;
    }
    
    //Columns
    
    int Query::ColumnInt(int index) {
        return sqlite3_column_int(statement, index);
    }
    
    sqlite3_int64 Query::ColumnInt64(int index) {
        return sqlite3_column_int64(statement, index);
    }
    
    double Query::ColumnDouble(int index) {
        return sqlite3_column_double(statement, index);
    }
    
    std::string Query::ColumnString(int index) {
        //Should be unsigned char and 64-bit
        return std::string((char*)sqlite3_column_text(statement, index));
    }
    
    //Singles
    
    int Query::SingleInt() {
        return Next() ? ColumnInt(0) : 0;
    }
    
    sqlite3_int64 Query::SingleInt64() {
        return Next() ? ColumnInt64(0) : 0;
    }
    
    double Query::SingleDouble() {
        return Next() ? ColumnDouble(0) : 0;
    }
}