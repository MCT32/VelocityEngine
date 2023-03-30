cmake_minimum_required(VERSION 3.25.0)
project(COOM)

find_package(SDL2 REQUIRED)
include_directories(COOM ${SDL2_INCLUDE_DIRS})

add_executable(COOM main.cpp color.cpp draw.cpp load.cpp logging.cpp player.cpp render.cpp util.cpp)
target_link_libraries(COOM ${SDL2_LIBRARIES})