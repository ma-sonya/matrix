cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(matrix)

set(PROJECT_HEADER 
    include/matrix.hpp)

set(PROJECT_SOURCE 
    src/matrix.cpp
    src/main.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE} ${PROJECT_HEADER})