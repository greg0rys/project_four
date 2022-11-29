cmake_minimum_required(VERSION 3.23)
project(project_four)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)
add_executable(project_four BST.h BST.cpp driver.h driver.cpp website.h
        website.cpp)
