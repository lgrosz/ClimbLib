cmake_minimum_required(VERSION 3.10)
project(Grades C)

set(CMAKE_C_STANDARD 11)

add_library(grades grades.c)
target_compile_options(grades PRIVATE -Wall -Werror)
add_executable(tests tests.c)
target_link_libraries(tests grades)
target_compile_options(tests PRIVATE -Wall -Werror)

include (CTest)

add_test(NAME tests COMMAND tests)
