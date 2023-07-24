cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(ip_filter VERSION ${PROJECT_VERSION})

option(WITH_GOOGLETEST "Whether to build Google test" ON)

add_executable(
    ip_filter_cli
    src/main.cpp
)

add_library(
    ip
    src/ip.cpp
)
add_library(
    filter
    src/utilities/filter.cpp
)
add_library(
    split
    src/utilities/split.cpp
)
add_library(
    sort
    src/utilities/sort.cpp
)

set_target_properties(
    ip_filter_cli ip filter split sort PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    ip_filter_cli PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(
    filter PRIVATE ip
)
target_link_libraries(
    sort PRIVATE ip
)
target_link_libraries(
    ip_filter_cli PRIVATE ip filter split sort
)

if(WITH_GOOGLETEST)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    
    add_executable(
        test_version 
        test/test.cpp
    )

    target_include_directories(
        test_version
        PRIVATE "${CMAKE_BINARY_DIR}"
    )

    target_link_libraries(
        test_version 
        PRIVATE ip filter split sort GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(test_version)

    set_target_properties(test_version PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
    )

    target_include_directories(
        test_version PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/lib"
    )
endif()

if (MSVC)
    target_compile_options(ip_filter_cli PRIVATE
        /W4
    )
    target_compile_options(ip PRIVATE
        /W4
    )
    target_compile_options(filter PRIVATE
        /W4
    )
    target_compile_options(split PRIVATE
        /W4
    )
    target_compile_options(sort PRIVATE
        /W4
    )
    if(WITH_GOOGLE_TEST)
        target_compile_options(test_version PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ip PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(split PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(sort PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
include(CPack)

if(WITH_GOOGLE_TEST)
    enable_testing()
    add_test(test_version test_version)
endif()
