cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
set(BUILD_SHARED_LIBS:BOOL=OFF)

project(superdrawapp VERSION ${PROJECT_VERSION})

add_executable(
    DrawApp
    src/main.cpp
)

add_library(
    DrawLib
    src/controller.cpp
    src/model.cpp
    src/view.cpp
    lib/api/Document.h
)

add_library(
    ShapesLib
    lib/shapes/Circle.h
    lib/shapes/Color.h
    lib/shapes/Line.h
    lib/shapes/Point.h
    lib/shapes/Rectangle.h
    lib/shapes/Shape.h
    lib/shapes/Triangle.h
    lib/fake.cpp
)

set_target_properties(
    DrawApp DrawLib ShapesLib PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    DrawApp PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(
    DrawLib PRIVATE ShapesLib
)

target_link_libraries(
    DrawApp PRIVATE DrawLib
)


if (MSVC)
    target_compile_options(DrawApp PRIVATE
        /W4
    )
    target_compile_options(DrawLib PRIVATE
        /W4
    )
    target_compile_options(ShapesLib PRIVATE
        /W4
    )
else ()
    target_compile_options(DrawApp PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(DrawLib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(ShapesLib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS DrawApp RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)