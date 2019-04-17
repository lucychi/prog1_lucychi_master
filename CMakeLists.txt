cmake_minimum_required(VERSION 3.13)
project(prog1_lucychi_master)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(prog1_lucychi_master
        bst.hpp
        bst_test.cpp
        main.cpp)
