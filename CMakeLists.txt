cmake_minimum_required(VERSION 3.6)
project(2017_03_20_Supertree)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Tree.cpp Tree.h CartesianTree.cpp CartesianTree.h)
add_executable(2017_03_20_Supertree ${SOURCE_FILES})