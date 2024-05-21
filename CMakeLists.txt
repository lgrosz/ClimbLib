cmake_minimum_required(VERSION 3.10)
project(ClimbLib C)

include(CTest)

set(CMAKE_C_STANDARD 11)

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(grades
    grades_hueco.c
    grades_font.c
)

# Compiler warning flags
target_compile_options(grades PRIVATE
    $<$<C_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Werror>
    $<$<C_COMPILER_ID:MSVC>:/W4 /WX>
)

target_include_directories(grades
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
