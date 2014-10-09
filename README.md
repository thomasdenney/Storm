![Storm](storm.png)

Storm is an experimental C++ wrapper for SQLite. I'm writing it as part of development on [Play Time 2.0](http://programmingthomas.com/play-time/). It is far from feature complete and I'll probably break lots of things with the API. Please don't use it yet.

##Building

* Add this repository as a git submodule
* Add the framework project to your Xcode workspace
* Link your app with either the iOS or OS X target

##Current features

* C++11
* Opening/closing SQLite database safely
* Basic querying
* Basic data access
* Parameter binding with variadic access

##Todo

The development process is currently just working out as me adding things as I need them...

* Strict concurrent only access to the database (will be implemented using C++11 threads and lambdas rather than GCD and blocks)
* Fully support all data types

##License

Apache v2, check LICENSE file.