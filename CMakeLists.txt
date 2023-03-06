cmake_minimum_required(VERSION 3.18)

project(AutoMove)

add_library(AutoMove SHARED)
file(GLOB SOURCES
    src/*.cpp
)
file(GLOB HEADERS
    src/*.h
)
target_sources(AutoMove PRIVATE ${SOURCES} ${HEADERS})

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/CommonLibSSE" CommonLibSSE EXCLUDE_FROM_ALL)
target_link_libraries(AutoMove PRIVATE
    CommonLibSSE::CommonLibSSE
)
