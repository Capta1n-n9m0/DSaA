cmake_minimum_required(VERSION 3.22)
project(PW7 C)

set(CMAKE_C_STANDARD 23)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif ()

add_executable(PW7 main.c)
