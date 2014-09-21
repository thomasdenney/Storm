//
//  Query.cpp
//  Storm
//
//  Created by Thomas Denney on 21/09/2014.
//  Copyright (c) 2014 Programming Thomas. All rights reserved.
//

#include "Storm.h"

namespace Storm {
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
    
    //Parameter binding by index. This doesn't do any testing for the index being valid or all of the parameters being filled. I'm (dangerously) assuming that the programmer is smart enough to make sure that this is true
    
    int Query::NextBindingIndex() {
        bindingIndex++;
        return bindingIndex;
    }
    
    //These functions look stupid. There must be a sensible way to do this in C++
    
    void Query::Bind(int value) {
        Bind(NextBindingIndex(), value);
    }
    
    void Query::Bind(double value) {
        Bind(NextBindingIndex(), value);
    }
    
    void Query::Bind(sqlite3_int64 value) {
        Bind(NextBindingIndex(), value);
    }
    
    void Query::Bind(std::string value) {
        Bind(NextBindingIndex(), value);
    }
    
    //Binding by index
    
    void Query::Bind(int index, int value) {
        sqlite3_bind_int(statement, index, value);
    }
    
    void Query::Bind(int index, double value) {
        sqlite3_bind_double(statement, index, value);
    }
    
    void Query::Bind(int index, sqlite3_int64 value) {
        sqlite3_bind_int64(statement, index, value);
    }
    
    void Query::Bind(int index, std::string value) {
        //Using the same technique as FMDB here
        sqlite3_bind_text(statement, index, value.c_str(), -1, SQLITE_STATIC);
    }
    
    bool Query::Next() {
        //Could check for other values here, but I don't need to for Storm v0.0.1
        return sqlite3_step(statement) == SQLITE_ROW;
    }
    
    bool Query::Execute() {
        int result = sqlite3_step(statement);
        bool success = result == SQLITE_OK || result == SQLITE_DONE;
        if (!success) {
            std::cout << "Warning: Error executing statement '" << query << "'" << std::endl;
            std::cout << sqlite3_errmsg(store->db) << std::endl;
        }
        return success;
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