cmake_minimum_required(VERSION 3.19)

set(DSPG_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(DSPG_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/data)

set(CMAKE_CXX_STANDARD 20)

project(dspg)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(src)
