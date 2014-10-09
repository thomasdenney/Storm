cmake_minimum_required(VERSION 2.8.4)
project(stormcpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#Linker flags to ensure that SQLite 3 is available (only tested on OS X)
set(CMAKE_EXE_LINKER_FLAGS -lsqlite3)
include_directories("src" "clion")
set(SOURCE_FILES "src/Query.cpp" "src/Storm.cpp" "main.cpp")
add_executable(stormcpp ${SOURCE_FILES})