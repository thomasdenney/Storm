![Storm](artwork/storm.png)

Storm is an experimental C++ wrapper for SQLite. I'm writing it as part of development on [Play Time 2.0](http://programmingthomas.com/play-time/). It is far from feature complete and I'll probably break lots of things with the API. Please don't use it yet.

##Building with Xcode

* Add this repository as a git submodule
* Add the framework project to your Xcode workspace
* Link your app with either the iOS or OS X target
* `include <Storm/Storm.h>` in a .cpp or .mm file

##Building with CLion/other

* Build with *.cpp files in the `src` directory and ensure that you search for headers in this directory to
* Build with `-lsqlite3` option
* `include "Storm.h"` in a .cpp file

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

Apache v2, see LICENSE file.