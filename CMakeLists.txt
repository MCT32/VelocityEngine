cmake_minimum_required(VERSION 3.24.0)
project(COOM)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(COOM main.cpp)
target_link_libraries(COOM ${SDL2_LIBRARIES})
