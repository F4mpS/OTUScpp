cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(BUILD_SHARED_LIBS:BOOL=OFF)

project(print_ip VERSION ${PROJECT_VERSION})

add_executable(
    print_ip_cli
    src/main.cpp
)

add_library(
    print
    src/PrintIp.h
    src/PrintTuple.h
    src/Meta.h
    src/fake.cpp
)

set_target_properties(
    print_ip_cli print PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    print_ip_cli PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(
    print_ip_cli PRIVATE print
)

if (MSVC)
    target_compile_options(print_ip_cli PRIVATE
        /W4
    )
    target_compile_options(print PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(print PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS print_ip_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
