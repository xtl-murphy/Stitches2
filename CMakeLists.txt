cmake_minimum_required(VERSION 3.11.0)
project(Stitches VERSION 0.1.0 LANGUAGES CXX C)


set(CMAKE_MODULE_PATH
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules"
        "${CMAKE_MODULE_PATH}"
        )
set(GLES_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Third/gles)

find_package(GLES REQUIRED)
#find_package(GLEW REQUIRED)

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
set(SRC_DIR ${LIB_DIR}/Resources)
set(THIRD_DIR ${LIB_DIR}/Third)
set(TEST_DIR ${LIB_DIR}/Test)

include_directories(${SRC_DIR})

include_directories(${THIRD_DIR}/glfw/include)
include_directories(${THIRD_DIR}/gles/include)
include_directories(${THIRD_DIR}/glad/include)

file(GLOB_RECURSE RES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.hpp" "${SRC_DIR}/*.inl" "${TEST_DIR}/*.cpp")


add_subdirectory(Test)

add_executable(Stitches ${RES} main.cpp ${THIRD_DIR}/glad/src/glad.c)

#GLFW
add_library(libglfw STATIC IMPORTED)
set_target_properties(libglfw PROPERTIES IMPORTED_LOCATION ${THIRD_DIR}/glfw/libglfw3.a)

target_link_libraries(Stitches libglfw ${GLES_LIBRARIES})

configure_file(${GLES_ROOT_DIR}/bin/libGLES_CM.dll ${CMAKE_CURRENT_BINARY_DIR}/libGLES_CM.dll COPYONLY)
configure_file(${GLES_ROOT_DIR}/bin/libGLESv2.dll ${CMAKE_CURRENT_BINARY_DIR}/libGLESv2.dll COPYONLY)
configure_file(${GLES_ROOT_DIR}/bin/libEGL.dll ${CMAKE_CURRENT_BINARY_DIR}/libEGL.dll COPYONLY)