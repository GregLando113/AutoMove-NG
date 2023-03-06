cmake_minimum_required(VERSION 3.18)

find_package(CommonLibSSE)


project(AutoMove)
include(GNUInstallDirs)

find_package(CommonLibSSE REQUIRED CONFIG)


add_library(AutoMove SHARED)


file(GLOB SOURCES
    src/*.cpp
)

file(GLOB HEADERS
    src/*.h
)


target_sources(AutoMove PRIVATE ${SOURCES} ${HEADERS})
target_link_libraries(AutoMove PRIVATE
    CommonLibSSE
)