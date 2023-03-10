cmake_minimum_required(VERSION 3.18)

project(AutoMove VERSION 0.1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)


include(GNUInstallDirs)
find_package(CommonLibSSE CONFIG REQUIRED)

file(GLOB SOURCES
    src/*.cpp
    src/Hooks/*.cpp
)
file(GLOB HEADERS
    src/*.h
    src/Hooks/*.h
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

target_compile_features(
    AutoMove
    PUBLIC
        cxx_std_23
)

target_precompile_headers(
    ${PROJECT_NAME}
    PRIVATE
        src/PCH.h
)

target_compile_definitions(
    AutoMove
    PUBLIC
        WINVER=0x0601	# windows 7, minimum supported version by skyrim special edition
        _WIN32_WINNT=0x0601
        "$<$<BOOL:${SKSE_SUPPORT_XBYAK}>:SKSE_SUPPORT_XBYAK=1>"
        "$<$<BOOL:${ENABLE_SKYRIM_SE}>:ENABLE_SKYRIM_SE=1>"
        "$<$<BOOL:${ENABLE_SKYRIM_AE}>:ENABLE_SKYRIM_AE=1>"
        "$<$<BOOL:${ENABLE_SKYRIM_VR}>:ENABLE_SKYRIM_VR=0>"
)

add_custom_command(
    TARGET AutoMove
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "$ENV{AUTOMOVE_OUTPUT_ROOT}/SKSE/Plugins/"
)

find_package(PythonInterp)
find_package(Python)
install(CODE "execute_process(COMMAND \"${PYTHON_EXECUTABLE}\" \"${CMAKE_CURRENT_SOURCE_DIR}/scripts/mkrelease.py\" -v ${PROJECT_VERSION} -f \"$<TARGET_FILE:${PROJECT_NAME}>\")")
