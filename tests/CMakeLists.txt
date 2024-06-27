find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

set(TestSources
    grade_font.c
    grade_hueco.c
    climb.c
    formation.c
    graph.c
)

create_test_sourcelist(Tests UnitTests.c ${TestSources})

add_executable(UnitTests ${Tests})
target_link_libraries(UnitTests ClimbLib ${CHECK_LIBRARIES})
target_link_directories(UnitTests PRIVATE ${CHECK_LIBDIR})
target_compile_options(UnitTests PRIVATE ${CHECK_CFLAGS_OTHER})
target_include_directories(UnitTests PRIVATE ${CHECK_INCLUDEDIR})

foreach(test ${TestSources})
    get_filename_component(Name ${test} NAME_WE)
    add_test(NAME ${Name} COMMAND UnitTests ${Name})
endforeach()
