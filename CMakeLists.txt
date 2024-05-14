cmake_minimum_required(VERSION 3.10)
project(ClimbLib C)

enable_testing()

set(CMAKE_C_STANDARD 11)

add_subdirectory(tests)

add_library(grades grades_hueco.c grades_font.c)

# Compiler warning flags
target_compile_options(grades PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

target_include_directories(grades INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
