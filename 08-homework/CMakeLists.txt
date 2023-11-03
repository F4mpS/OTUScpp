cmake_minimum_required(VERSION 3.5)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(bayan VERSION ${PROJECT_VERSION})

find_package(Boost REQUIRED COMPONENTS program_options)

add_executable(bayan
    src/main.cpp
    lib/hashes/CRC32.h
    lib/interfaces/IFileParser.h
    lib/MaskFileParser.h
    lib/FilePathHasherator.h
    lib/BayanFileParser.h
)

set_target_properties(bayan PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(bayan PRIVATE "${CMAKE_BINARY_DIR}")
target_link_libraries(bayan PUBLIC Boost::program_options)

if(MSVC)
    target_compile_options(bayan PRIVATE
        /W4
    )
else()
    target_compile_options(PRIVATE
        -Werror -Wall -Wimplicit-fallthrough -pedantic-errors
    )
endif()


install(TARGETS bayan RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
