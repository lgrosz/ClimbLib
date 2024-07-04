cmake_minimum_required(VERSION 3.10)
project(ClimbLib C)

include(CTest)

set(CMAKE_C_STANDARD 11)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(ClimbLib
    grades_hueco.c
    grades_font.c
    climb.c
    graph.c
    str_util.c
    int_util.c
)

# Compiler warning flags
target_compile_options(ClimbLib PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Werror>
    $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
)

target_include_directories(ClimbLib
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
