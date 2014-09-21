#ifndef PLTCPP_Storm_h
#define PLTCPP_Storm_h

#include <iostream>
#include <sqlite3.h>
#include <string>

//Storm header
namespace Storm {
    class Store {
    public:
        sqlite3 * db;
        Store(const char * databaseName);
        //Closes the database
        ~Store();
    };
    
    class Query {
    public:
        //Properties (should be immutable, need to work out how to do that)
        
        //This needs to be a shared_ptr because I needed to make it explicit that the Query needs a strong reference, rather than just a pointer that could be freed. (Actually, does it need a strong reference?)
//        std::shared_ptr<Store> database;
        std::string query;
        sqlite3_stmt * statement;
        
        //Creates the SQLite prepared statement
        Query(std::shared_ptr<Store> database, std::string query);
        //Destroys the SQLite prepared statement
        ~Query();
        
        bool Next();
        
        //Column values
        int ColumnInt(int index);
        sqlite3_int64 ColumnInt64(int index);
        double ColumnDouble(int index);
        std::string ColumnString(int index);
        
        //A quick way of just getting a single double value back from the first column of the first result
        double SingleDouble();
        int SingleInt();
        sqlite3_int64 SingleInt64();
    };
}

#endif
