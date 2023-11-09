cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(async VERSION ${PROJECT_VERSION})

set(bulk
    lib/interfaces/ICommand.cpp
    lib/headers/Command.h
    lib/Command.cpp
    lib/headers/Bulk.h
    lib/Bulk.cpp
)

set(printers 
    lib/interfaces/IPrinter.h
    lib/headers/printers/FilePrinter.h
    lib/headers/printers/OstreamPrinter.h
    lib/FilePrinter.cpp
    lib/OstreamPrinter.cpp
)

set(commandReceiver 
    lib/headers/CommandReceiver.h
    lib/CommandReceiver.cpp
)

set(bulkContainer
    lib/headers/BulkContainer.h
    lib/BulkContainer.cpp
)

set(moderator 
    lib/headers/Moderator.h
    lib/Moderator.cpp
)

add_library(libasync SHARED
    ${moderator}
    ${bulk}
    ${printers}
    ${commandReceiver}
    ${bulkContainer}
)

add_executable(async
    src/main.cpp
    src/async.h
    src/async.cpp

    ${moderator}
    ${bulk}
    ${printers}
    ${commandReceiver}
    ${bulkContainer}
)

# add_library(libasync SHARED
#     lib/headers/BulkContainer.h
#     lib/headers/Command.h
#     lib/headers/printers/FilePrinter.h
#     lib/headers/printers/OstreamPrinter.h
#     lib/headers/CommandReceiver.h
#     lib/headers/Moderator.h
#     lib/headers/utilities/Split.h

    
#     # lib/BulkContainer.cpp
#     lib/Command.cpp
#     # lib/FilePrinter.cpp
#     # lib/OstreamPrinter.cpp
#     # lib/CommandReceiver.cpp
#     # lib/Moderator.cpp
#     # lib/interfaces/ICommand.cpp
#     # lib/interfaces/IPrinter.h
# )


# add_executable(async
#     src/main.cpp
#     src/async.cpp
# )

set_target_properties(
    libasync async PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# target_include_directories(
#     async PRIVATE "${CMAKE_BINARY_DIR}"
# )



# target_link_libraries(
#     async PUBLIC libasync
# )

# target_include_directories(
#     async PRIVATE "${CMAKE_BINARY_DIR}"
# )

if (MSVC)
    target_compile_options(libasync PRIVATE
        /W4
    )
    target_compile_options(async PRIVATE
        /W4
    )
else ()
    target_compile_options(libasync PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(async PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS async libasync RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
