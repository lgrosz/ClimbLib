cmake_minimum_required(VERSION 3.10)
project(Grades C)

set(CMAKE_C_STANDARD 11)

add_library(grades grades_hueco.c)
target_compile_options(grades PRIVATE -Wall -Werror)

add_executable(test-hueco tests_hueco.c)
target_link_libraries(test-hueco grades)
target_compile_options(test-hueco PRIVATE -Wall -Werror)


include (CTest)

add_test(NAME GradeHueco COMMAND test-hueco)
