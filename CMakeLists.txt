cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)

project(dspg)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB DSPG_PROJECT_LIST src/**/CMakeLists.txt)
foreach(DSPG_PROJECT_FILE ${DSPG_PROJECT_LIST})
    get_filename_component(DSPG_PROJECT_DIR ${DSPG_PROJECT_FILE} DIRECTORY)
    add_subdirectory(${DSPG_PROJECT_DIR})
endforeach()
