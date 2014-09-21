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
    Storm::Query::Update(store, "create table notes(id integer primary key, note text, title text)");
    
    //Demonstrate the various ways that you can do an insertion
    //(I changed the API quite a bit during development, hence why there are several ways of doing it)
    Storm::Query insert(store, "insert into notes (note) values (:name)");
    insert.BindNamed(":name", std::string("Hello,world!"));
    insert.Execute();
    
    Storm::Query insert2(store, "insert into notes (note) values (:name)");
    insert2.BindValue("My name is Thomas");
    insert2.Execute();
    
    Storm::Query insert3(store, "insert into notes (note, title) values (?,?)");
    insert3.BindValue("Note content", "Note title");
    insert3.Execute();
    
    Storm::Query insert4(store, "insert into notes (note, title) values(?,?)", "Hello world", "This note is great");
    insert4.Execute();
    
    Storm::Query::Update(store, "insert into notes (note,title) values (?,?)", "Another note content", "Another note title");
    
    //Present all results. The query is wrapped in curly brackets so that it gets finalized when it goes out of scope.
    {
        Storm::Query notes(store, "select * from notes");
        while (notes.Next()) {
            std::cout << notes.ColumnInt(0) << ": " << notes.ColumnString(1) << " (" << notes.ColumnString(2) << ")" << std::endl;
        }
    }
    
    return 0;
}
