#ifndef PLTCPP_Query_h
#define PLTCPP_Query_h

#include "Store.h"

namespace Storm {
    //Used for carrying out queries on the database. A good accessing pattern here is:

    /*
     {
        Storm::Query query(store, "select * from table");
        while (query.Next()) {
            //Do something with query.Column*()
        }
     }

     //Or:

     {
        Storm::Query query(store, "select * from table");
        std::vector<Model> results = query.MapResults<Model>([](Storm::Query * row) {
            return //Some model object based on row columns;
        //});
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

        //Alternative, using variadic template stuff
        template <typename... Args>
        Query(std::shared_ptr<Store> store, std::string query, Args... args) : Query(store, query) {
            BindValue(args...);
        }

        //Shortcut method for executing updates on the database more simply
        template <typename... Args>
        static bool Update(std::shared_ptr<Store> store, std::string query, Args... args) {
            return Query(store, query, args...).Execute();
        }

        //Destroys the SQLite prepared statement
        ~Query();

        //Parameter binding by index. Note that indexes begin at 1

        void BindIndex(int index, int value);
        void BindIndex(int index, double value);
        void BindIndex(int index, sqlite3_int64 value);
        void BindIndex(int index, std::string value);
        void BindIndex(int index, const char * value);

        template <typename T>
        void BindValue(T value) {
            BindIndex(NextBindingIndex(), value);
        }

        template <typename T, typename... Args>
        void BindValue(T value, Args... args) {
            BindValue(value);
            BindValue(args...);
        }

        //If you've used ?XYZ, :XYZ, @XYZ or $XYZ then the parameter name is that string
        int BindingIndex(std::string name);

        template <typename T>
        void BindNamed(std::string name, T value) {
            BindIndex(BindingIndex(name), value);
        }

        //Use for updates
        bool Execute();

        //Use for select queries
        bool Next();

        //Use for executing batch updates.
        bool Reset();

        //Column values
        int ColumnInt(int index);
        sqlite3_int64 ColumnInt64(int index);
        double ColumnDouble(int index);
        std::string ColumnString(int index);

        //A quick way of just getting a single double value back from the first column of the first result
        double SingleDouble();
        int SingleInt();
        sqlite3_int64 SingleInt64();

        template <typename T, typename Func>
        std::vector<T> MapResults(Func mapper) {
            std::vector<T> results;
            while (Next()) {
                results.push_back(mapper(this));
            }
            return results;
        }
    };
}

#endif
