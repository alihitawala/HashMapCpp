cmake_minimum_required(VERSION 3.6)
project(HashMapCpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp my_unordered_map.cpp)
add_executable(HashMapCpp ${SOURCE_FILES})