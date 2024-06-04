set(TestSources
    font.c
    hueco.c
    climb.c
    graph.c
)

create_test_sourcelist(Tests UnitTests.c ${TestSources})

add_executable(UnitTests ${Tests})
target_link_libraries(UnitTests grades)

foreach(test ${TestSources})
    get_filename_component(Name ${test} NAME_WE)
    add_test(NAME ${Name} COMMAND UnitTests ${Name})
endforeach()
