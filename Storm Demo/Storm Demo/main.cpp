//
//  main.cpp
//  Storm Demo
//
//  Created by Thomas Denney on 21/09/2014.
//  Copyright (c) 2014 Programming Thomas. All rights reserved.
//

#include <iostream>
#include <Storm/Storm.h>

int main(int argc, const char * argv[]) {
    //Testing with in memory database
    std::shared_ptr<Storm::Store> store(new Storm::Store(":memory:"));
    
    //Basic table creation
    Storm::Query(store, "create table if not exists notes(id integer primary key, note text)").Execute();
    
    //Couple of basic insertions
    Storm::Query insert(store, "insert into notes (note) values (:name)");
    insert.Bind(":name", std::string("Hello,world!"));
    insert.Execute();
    
    Storm::Query insert2(store, "insert into notes (note) values (:name)");
    insert2.Bind("My name is Thomas");
    insert2.Execute();
    
    //Present all results. The query is wrapped in curly brackets so that it gets finalized when it goes out of scope.
    {
        Storm::Query notes(store, "select * from notes");
        while (notes.Next()) {
            std::cout << notes.ColumnInt(0) << ": " << notes.ColumnString(1) << std::endl;
        }
    }
    return 0;
}
