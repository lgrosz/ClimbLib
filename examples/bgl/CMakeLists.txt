set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost)

if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()

add_executable(bgl
    main.cc
)

target_link_libraries(bgl
    ClimbLib
)
