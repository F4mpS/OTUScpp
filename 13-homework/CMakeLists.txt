cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(fashio_mnist VERSION ${PROJECT_VERSION})

find_package(Eigen3)
find_package(Boost COMPONENTS COMPONENTS program_options system REQUIRED)

add_executable(fashio_mnist
    src/main.cpp

    lib/headers/AccuracyFinder.h
    lib/interfaces/classifier.h
    lib/headers/helpers.h
    lib/headers/mlp_classifier.h
    lib/sources/AccuracyFinder.cpp
    lib/sources/helpers.cpp
    lib/sources/mlp_classifier.cpp
)

set_target_properties(
    fashio_mnist PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(fashio_mnist PRIVATE "${CMAKE_BINARY_DIR}")

if (MSVC)
    target_compile_options(fashio_mnist PRIVATE
        /W4 
    )
else ()
    target_compile_options(fashio_mnist PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

install(TARGETS fashio_mnist RUNTIME DESTINATION bin)
target_link_libraries(fashio_mnist PRIVATE Boost::program_options Boost::system pthread stdc++fs Eigen3::Eigen)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
