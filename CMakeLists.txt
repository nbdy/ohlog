cmake_minimum_required(VERSION 3.0)
project(ohlog)

option(TESTS "Enable tests" OFF)

set(CMAKE_CXX_STANDARD 17)

add_library(ohlog SHARED ohlog.h)
add_library(ohlogstatic STATIC ohlog.h)
set_target_properties(ohlog PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(ohlogstatic PROPERTIES LINKER_LANGUAGE CXX)

add_executable(Logger main.cpp ohlog.h)
target_link_libraries(Logger pthread)

if(TESTS)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()

    add_executable(ohlog_tests tests.cpp)
    target_compile_definitions(ohlog_tests PRIVATE -DTESTS)
    target_link_libraries(ohlog_tests dl gtest_main)
    include(GoogleTest)
    gtest_discover_tests(ohlog_tests)
endif()

unset(TESTS CACHE)
