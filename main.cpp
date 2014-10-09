//
//  main.cpp
//  Storm Demo
//
//  Created by Thomas Denney on 21/09/2014.
//  Copyright (c) 2014 Programming Thomas. All rights reserved.
//

#include <iostream>
#include <Storm/Storm.h>

class NoteViewModel {
public:
    int id;
    std::string title;
    std::string contents;
    void Log();
};

void NoteViewModel::Log() {
    std::cout << id << ":\t" << title << "\t" << contents << std::endl;
}

int main(int argc, const char * argv[]) {
    //Testing with in memory database
    std::shared_ptr<Storm::Store> store(new Storm::Store(":memory:"));
    
    //Basic table creation
    Storm::Query::Update(store, "create table notes(id integer primary key, title text, note text)");
    
    //Demonstrate the various ways that you can do an insertion
    //(I changed the API quite a bit during development, hence why there are several ways of doing it)
    store->InTransaction([&]() {
        Storm::Query insert(store, "insert into notes (title, note) values (:title, :note)");
        insert.BindNamed(":title", "Title 1");
        insert.BindNamed(":note", "Contents 1");
        insert.Execute();
    });
    
    Storm::Query insert2(store, "insert into notes (title, note) values (?,?)");
    insert2.BindValue("Title 2");
    insert2.BindValue("Contents 2");
    insert2.Execute();
    
    Storm::Query insert3(store, "insert into notes (title, note) values (?,?)");
    insert3.BindValue("Title 3", "Contents 3");
    insert3.Execute();
    
    Storm::Query insert4(store, "insert into notes (title, note) values(?,?)", "Title 4", "Contents 4");
    insert4.Execute();
    
    Storm::Query::Update(store, "insert into notes (title, note) values (?,?)", "Title 5", "Contents 5");
    
    {
        /*
         This will probably seem unfamiliar. What is happening here is that each row in the query is iterated over and that result is parsed to the lambda, which will then return the appropriate view model (or model). The main reason for doing this is provides an easy way of getting your own model objects without the need for writing factories or dealing with duplicate code.
         */
        Storm::Query noteQuery(store, "select * from notes");
        auto noteList = noteQuery.MapResults<NoteViewModel>([](Storm::Query * row) {
            NoteViewModel viewModel;
            
            viewModel.id = row->ColumnInt(0);
            viewModel.title = row->ColumnString(1);
            viewModel.contents = row->ColumnString(2);
            
            return viewModel;
        });
        
        //Then we just display the result, nothing fancy here
        for (auto note : noteList) {
            note.Log();
        }
    }
    
    return 0;
}
