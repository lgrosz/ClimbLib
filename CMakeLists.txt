cmake_minimum_required(VERSION 3.10)
project(ClimbLib C)

set(CMAKE_C_STANDARD 11)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_COVERAGE "Builds with coverage flags." OFF)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(ClimbLib
    grade_hueco.c
    grade_font.c
    climb.c
    graph.c
    str_util.c
    strarr_util.c
    int_util.c
)

if (BUILD_COVERAGE)
    target_compile_options(ClimbLib PRIVATE --coverage)
    target_link_options(ClimbLib PRIVATE --coverage)
endif()

# Compiler warning flags
target_compile_options(ClimbLib PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Werror>
    $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
)

target_include_directories(ClimbLib
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(TARGETS
    ClimbLib
    LIBRARY
    ARCHIVE
    RUNTIME
)

install(
    FILES
        climb.h
        grade_font.h
        grade_hueco.h
        graph.h
    DESTINATION include
)
