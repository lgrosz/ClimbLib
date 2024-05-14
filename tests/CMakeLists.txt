add_executable(test-hueco hueco.c)
target_link_libraries(test-hueco grades)
target_compile_options(test-hueco PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

add_executable(test-font font.c)
target_link_libraries(test-font grades)
target_compile_options(test-font PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Werror>
    $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
)

include (CTest)

add_test(NAME GradeHueco COMMAND test-hueco)
add_test(NAME GradeFont COMMAND test-font)
