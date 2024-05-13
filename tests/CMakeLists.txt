add_executable(test-hueco hueco.c)
target_link_libraries(test-hueco grades)
target_compile_options(test-hueco PRIVATE -Wall -Werror)

add_executable(test-font font.c)
target_link_libraries(test-font grades)
target_compile_options(test-font PRIVATE -Wall -Werror)

include (CTest)

add_test(NAME GradeHueco COMMAND test-hueco)
add_test(NAME GradeFont COMMAND test-font)
