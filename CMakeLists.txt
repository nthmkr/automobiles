cmake_minimum_required(VERSION 2.8)

project(automobiles)

set (CMAKE_CXX_STANDARD 11)

include_directories(${PROJECT_SOURCE_DIR})

add_executable(automobiles TextNumbers.cpp main.cpp)
