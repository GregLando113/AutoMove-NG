cmake_minimum_required(VERSION 3.18)

project(AutoMove VERSION 0.1.0.0)

include(GNUInstallDirs)
find_package(CommonLibSSE CONFIG REQUIRED)

file(GLOB SOURCES
    src/*.cpp
)
file(GLOB HEADERS
    src/*.h
)

add_commonlibsse_plugin(AutoMove
    # The plugin's name, defaults to target.
    NAME "AutoMove AE"

    # The plugin's author, empty by default.
    AUTHOR "xILARTH"

    # The support email address, empty by default.
    EMAIL "kaos4d1@gmail.com"

    # Indicates the plugin is compatible with all runtimes via address library. This is the default if no
    # other compatibilility mode is specified. Can be used with USE_SIGNATURE_SCANNING but not
    # COMPATIBLE_RUNTIMES.
    USE_ADDRESS_LIBRARY

    # Indicates the plugin is compatible with all runtimes via signature scanning.  Can be used with
    # USE_ADDRESS_LIBRARY but not COMPATIBLE_RUNTIMES.
    USE_SIGNATURE_SCANNING

    # List of the sources to include in the target, as would be the parameters to add_library.
    SOURCES ${SOURCES} ${HEADERS}
)