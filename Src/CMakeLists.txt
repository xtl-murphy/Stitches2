cmake_minimum_required(VERSION 3.11.0)
project(Stitches VERSION 0.1.0 LANGUAGES CXX C)


set(LIB_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${LIB_DIR}/Resources)
set(THIRD_DIR ${LIB_DIR}/Third)

include_directories(${SRC_DIR})


file(GLOB_RECURSE RES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.hpp" "${SRC_DIR}/*.inl")

add_executable(Stitches ${RES} main.cpp)

