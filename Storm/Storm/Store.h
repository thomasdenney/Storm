//
//  Store.h
//  Storm
//
//  Created by Thomas Denney on 21/09/2014.
//  Copyright (c) 2014 Programming Thomas. All rights reserved.
//

#ifndef Storm_Store_h
#define Storm_Store_h

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

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
}

#endif
