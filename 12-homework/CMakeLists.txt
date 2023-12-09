cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(mapreduce VERSION ${PROJECT_VERSION})
find_package(Boost COMPONENTS COMPONENTS program_options system REQUIRED)

add_executable(mapreduce
    src/main.cpp

    lib/headers/Mapreduce.h
    lib/headers/Block.h
    lib/headers/Maper.h 
    lib/headers/Reducer.h 
    lib/headers/PrefixFinder.h
    lib/sources/ThreadPool.cpp
)

set_target_properties(
    mapreduce PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(mapreduce PRIVATE "${CMAKE_BINARY_DIR}")


if (MSVC)
    target_compile_options(mapreduce PRIVATE
        /W4 
    )
else ()
    target_compile_options(mapreduce PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

install(TARGETS mapreduce RUNTIME DESTINATION bin)
target_link_libraries(mapreduce PRIVATE Boost::program_options Boost::system pthread stdc++fs)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)