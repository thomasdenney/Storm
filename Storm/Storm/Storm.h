#ifndef PLTCPP_Storm_h
#define PLTCPP_Storm_h

#include <iostream>
#include <sqlite3.h>
#include <string>

namespace Storm {
    
    //General database access. Other APIs require that you use this as a shared_ptr, so please create one for it (doing this hugely simplifies memory management as well)
    class Store {
    public:
        sqlite3 * db;
        Store(const char * databaseName);
        //Closes the database
        ~Store();
        
        sqlite3_int64 LastInsertID();
    };
    
    //Used for carrying out SELECT queries on the database. A good accessing pattern here is:
    
    /*
     {
        Storm::Query query(store, "select * from table");
        while (query.Next()) {
            //Do something with query.Column*()
        }
     }
     */
    
    //By placing your access inside of curly brackets the query object will go out of scope and therefore SQLite will have the opportunity to free up resources
    
    class Query {
    private:
        int bindingIndex = 0;
        int NextBindingIndex();
    public:
        std::string query;
        sqlite3_stmt * statement;
        std::shared_ptr<Store> store;
        
        //Creates the SQLite prepared statement. *Please* use shared_ptr because it simplifies memory management massively
        Query(std::shared_ptr<Store> store, std::string query);
        
        //Destroys the SQLite prepared statement
        ~Query();
        
        //Parameter binding by index. Note that indexes begin at 1
        
        void Bind(int index, int value);
        void Bind(int index, double value);
        void Bind(int index, sqlite3_int64 value);
        void Bind(int index, std::string value);
        void Bind(int index, const char * value);

        template <typename T>
        void Bind(T value) {
            Bind(NextBindingIndex(), value);
        }
        
        //If you've used ?XYZ, :XYZ, @XYZ or $XYZ then the parameter name is that string
        int BindingIndex(std::string name);
        
        template <typename T>
        void Bind(std::string name, T value) {
            Bind(BindingIndex(name), value);
        }
        
        //Use for updates
        bool Execute();
        
        //Use for select queries
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
    
    //TODO: Strict single-thread concurrency mdoel
}

#endif
