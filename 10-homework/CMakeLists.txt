cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(bulk_server VERSION ${PROJECT_VERSION})

set(network
    lib/sources/Session.cpp
    lib/sources/Server.cpp
)

set(bulk
    lib/interfaces/ICommand.cpp
    lib/headers/Command.h
    lib/sources/Command.cpp
    lib/headers/Bulk.h
    lib/sources/Bulk.cpp
)

set(printers 
    lib/interfaces/IPrinter.h
    lib/headers/printers/FilePrinter.h
    lib/headers/printers/OstreamPrinter.h
    lib/sources/FilePrinter.cpp
    lib/sources/OstreamPrinter.cpp
)

set(commandReceiver 
    lib/headers/CommandReceiver.h
    lib/sources/CommandReceiver.cpp
)

set(bulkContainer
    lib/headers/BulkContainer.h
    lib/sources/BulkContainer.cpp
)

set(moderator 
    lib/headers/Moderator.h
    lib/sources/Moderator.cpp
)

add_executable(bulk_server
    src/main.cpp

    ${moderator}
    ${bulk}
    ${printers}
    ${commandReceiver}
    ${bulkContainer}
    ${network}
)

set_target_properties(
    bulk_server PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

if (MSVC)
    target_compile_options(bulk_server PRIVATE
        /W4
    )
else ()
    target_compile_options(bulk_server PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install(TARGETS bulk_server RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
