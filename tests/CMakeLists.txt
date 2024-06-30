set(TestSources
    font.c
    hueco.c
    climb.c
    graph.c
)

create_test_sourcelist(Tests UnitTests.c ${TestSources})

add_executable(UnitTests ${Tests})
target_link_libraries(UnitTests ClimbLib)

foreach(test ${TestSources})
    get_filename_component(Name ${test} NAME_WE)
    add_test(NAME ${Name} COMMAND UnitTests ${Name})
endforeach()

# Tests using check framework
find_package(PkgConfig REQUIRED)
pkg_check_modules(CHECK REQUIRED check)

set(CheckSources
    grades_font.c
)

create_test_sourcelist(Checks UnitChecks.c ${CheckSources})

add_executable(UnitChecks ${Checks})
target_link_libraries(UnitChecks PRIVATE ClimbLib ${CHECK_LIBRARIES})
target_link_directories(UnitChecks PRIVATE ${CHECK_LIBDIR})
target_compile_options(UnitChecks PRIVATE ${CHECK_CFLAGS_OTHER})
target_include_directories(UnitChecks PRIVATE ${CHECK_INCLUDEDIR})

foreach(check ${CheckSources})
    get_filename_component(Name ${check} NAME_WE)
    add_test(NAME ${Name} COMMAND UnitChecks ${Name})
endforeach()
