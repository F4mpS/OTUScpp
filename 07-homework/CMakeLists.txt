cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk VERSION ${PROJECT_VERSION})

add_executable(
    bulk
    src/main.cpp
    lib/Bulk.cpp
    lib/BulkContainer.cpp
    lib/Command.cpp
    lib/FilePrinter.cpp
    lib/OstreamPrinter.cpp
    lib/ConsoleReader.cpp
    lib/Moderator.cpp
    lib/interfaces/ICommand.cpp
    lib/interfaces/IPrinter.h
)

set_target_properties(
    bulk PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    bulk PRIVATE "${CMAKE_BINARY_DIR}"
)

if (MSVC)
    target_compile_options(bulk PRIVATE
        /W4
    )
else ()
    target_compile_options(bulk PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
