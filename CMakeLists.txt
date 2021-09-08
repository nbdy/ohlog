cmake_minimum_required(VERSION 3.0)
project(Logger)

set(CMAKE_CXX_STANDARD 17)

include_directories(ext)

add_library(ohlog SHARED ohlog.h)
add_library(ohlogstatic STATIC ohlog.h)
set_target_properties(ohlog PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(ohlogstatic PROPERTIES LINKER_LANGUAGE CXX)

add_executable(Logger main.cpp ohlog.h)
target_link_libraries(Logger pthread)