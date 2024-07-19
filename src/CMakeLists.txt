cmake_minimum_required(VERSION 3.2)
project(ASCII-Engine)

find_package(SDL2 REQUIRED)
include_directories(ASCII-Engine ${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES
    *.h
    *.hpp
    *.cpp
    *.c
)

add_executable(ASCII-Engine ${SOURCES})
target_link_libraries(ASCII-Engine ${SDL2_LIBRARIES})