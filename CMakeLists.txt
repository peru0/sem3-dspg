cmake_minimum_required(VERSION 3.19)

set(CMAKE_CXX_STANDARD 20)

project(dspg)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES
        Catch2/2.6.0@catchorg/stable
        spdlog/1.8.5
        nlohmann_json/3.9.1
        BASIC_SETUP)

file(GLOB DSPG_PROJECT_LIST src/**/CMakeLists.txt)
foreach(DSPG_PROJECT_FILE ${DSPG_PROJECT_LIST})
    get_filename_component(DSPG_PROJECT_DIR ${DSPG_PROJECT_FILE} DIRECTORY)
    add_subdirectory(${DSPG_PROJECT_DIR})
endforeach()



