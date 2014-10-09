cmake_minimum_required(VERSION 2.8.4)
project(stormcpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_EXE_LINKER_FLAGS -lsqlite3)
include_directories("Storm Demo/Storm Demo")
set(SOURCE_FILES "Storm Demo/Storm Demo/Query.cpp" "Storm Demo/Storm Demo/Storm.cpp" "Storm Demo/Storm Demo/main.cpp")
add_executable(stormcpp ${SOURCE_FILES})