cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(allocator VERSION ${PROJECT_VERSION})

add_executable(
    allocator_cli
    src/main.cpp
    src/Allocator.h
    src/List.h
)

set_target_properties(
    allocator_cli PROPERTIES
    LINKER_LANGUAGE CXX
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    allocator_cli PRIVATE "${CMAKE_BINARY_DIR}"
)

# target_link_libraries(
#     allocator_cli PRIVATE allocator_lib
# )

if (MSVC)
    target_compile_options(allocator_cli PRIVATE
        /W4
    )
    # target_compile_options(allocator_lib PRIVATE
    #     /W4
    # )
else ()
    target_compile_options(allocator_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    # target_compile_options(allocator_lib PRIVATE
    #     -Wall -Wextra -pedantic -Werror
    # )
endif()

install(TARGETS allocator_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
