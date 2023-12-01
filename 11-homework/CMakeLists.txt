cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})
project(join_server VERSION ${PROJECT_VERSION})


add_executable(join_server
    src/main.cpp

    lib/sourses/Command.cpp
    lib/sourses/Database.cpp
    lib/sourses/Message.cpp
    lib/sourses/Server.cpp
    lib/sourses/Session.cpp
    lib/sourses/ThreadPool.cpp
)

set_target_properties(
    join_server PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(join_server PRIVATE "${CMAKE_BINARY_DIR}")


if (MSVC)
    target_compile_options(join_server PRIVATE
        /W4 
    )
else ()
    target_compile_options(join_server PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

install(TARGETS join_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
