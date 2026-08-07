cmake_minimum_required(VERSION 3.28)

project(Q-Maths
        VERSION 1.0.0
        DESCRIPTION "Library for quantum mathematical operations"
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
