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
include_directories(${THIRD_DIR}/physfs/src)
include_directories(${THIRD_DIR})

file(GLOB_RECURSE RES "${SRC_DIR}/*.cpp" "${SRC_DIR}/*.hpp" "${SRC_DIR}/*.inl" "${TEST_DIR}/*.cpp")
file(GLOB_RECURSE STB "${THIRD_DIR}/stb/*.c" "${THIRD_DIR}/stb/*.h")

add_subdirectory(Test)

add_executable(Stitches ${RES} main.cpp ${THIRD_DIR}/glad/src/glad.c)

#GLFW
add_library(libglfw STATIC IMPORTED)
set_target_properties(libglfw PROPERTIES IMPORTED_LOCATION ${THIRD_DIR}/glfw/libglfw3.a)

#physys
set(PHYSFS_BUILD_STATIC NOT${BUILD_SHARED_LIBS} CACHE INTERNAL "")
set(PHYSFS_BUILD_SHARED ${BUILD_SHARED_LIBS} CACHE INTERNAL "")
set(PHYSFS_BUILD_TEST OFF CACHE INTERNAL "")
set(PHYSFS_TARGETNAME_DOCS "physfs-docs" CACHE INTERNAL STRING)
set(PHYSFS_TARGETNAME_DIST "physfs-dist" CACHE INTERNAL STRING)
set(PHYSFS_TARGETNAME_UNINSTALL "physfs-uninstall" CACHE INTERNAL STRING)
set(CMAKE_DISABLE_FIND_PACKAGE_Doxygen TRUE)
add_subdirectory(${THIRD_DIR}/physfs)
set_target_properties(physfs-static PROPERTIES FOLDER External/physfs)

target_link_libraries(Stitches libglfw ${GLES_LIBRARIES} ${STB} physfs-static)

configure_file(${GLES_ROOT_DIR}/bin/libGLES_CM.dll ${CMAKE_CURRENT_BINARY_DIR}/libGLES_CM.dll COPYONLY)
configure_file(${GLES_ROOT_DIR}/bin/libGLESv2.dll ${CMAKE_CURRENT_BINARY_DIR}/libGLESv2.dll COPYONLY)
configure_file(${GLES_ROOT_DIR}/bin/libEGL.dll ${CMAKE_CURRENT_BINARY_DIR}/libEGL.dll COPYONLY)