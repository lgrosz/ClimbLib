cmake_minimum_required(VERSION 3.10)
project(ClimbLib C)

set(CMAKE_C_STANDARD 11)

option(BUILD_DOCS "Builds documentation" OFF)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_COVERAGE "Builds with coverage flags." OFF)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_library(ClimbLib
    allocator.c
    grade_hueco.c
    grade_font.c
    climb.c
    formation.c
    str_util.c
    strarr_util.c
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
        allocator.h
        climb.h
        formation.h
        grade_font.h
        grade_hueco.h
        graph.h
    DESTINATION include
)

if (BUILD_DOCS)
    find_package(Doxygen REQUIRED)

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(docs ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Building documentation"
        VERBATIM
    )
endif()
