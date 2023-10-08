cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(BUILD_SHARED_LIBS:BOOL=OFF)

project(matrix VERSION ${PROJECT_VERSION})

add_executable(
    matrix_cli
    src/main.cpp
)

add_library(
    matrix_lib
    src/matrix.h
    src/fake.cpp
)

set_target_properties(
    matrix_cli matrix_lib PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    matrix_cli PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(
    matrix_cli PRIVATE matrix_lib
)

if (MSVC)
    target_compile_options(matrix_cli PRIVATE
        /W4
    )
    target_compile_options(matrix_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(matrix_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(matrix_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS matrix_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)