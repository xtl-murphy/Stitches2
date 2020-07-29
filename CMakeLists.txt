cmake_minimum_required(VERSION 3.11.0)
project(Stitches VERSION 0.1.0 LANGUAGES CXX C)


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_REQUIRED_FLAGS "-std=c++17 -std=c11")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(LIB_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${LIB_DIR}/src)

include_directories(${SRC_DIR})

file(GLOB_RECURSE RES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.hpp" "${SRC_DIR}/*.inl")

add_executable(Stitches ${RES} main.cpp)