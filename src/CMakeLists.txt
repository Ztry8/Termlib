cmake_minimum_required(VERSION 3.2)
project(Termlib-App)

find_package(SDL2 REQUIRED)
include_directories(Termlib-App ${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES
    *.h
    *.hpp
    *.cpp
    *.c
)

add_executable(Termlib-App ${SOURCES})
target_link_libraries(Termlib-App ${SDL2_LIBRARIES})