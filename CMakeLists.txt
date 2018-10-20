cmake_minimum_required(VERSION 3.12)
project(Exem)

set(CMAKE_CXX_STANDARD 14)

add_library(optional
        optional.cpp
        optional.h)

add_executable(Exem
        main.cpp)

add_executable(test
        counted.cpp
        counted.h
        gtest/gtest-all.cc
        gtest/gtest.h
        gtest/gtest_main.cc
        tests.cpp)

target_link_libraries(Exem optional)
target_link_libraries(test optional)