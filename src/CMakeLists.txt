cmake_minimum_required(VERSION 3.25.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/sdl2)

project(COOM)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(COOM main.cpp color.cpp entity.cpp load.cpp logging.cpp player.cpp render.cpp util.cpp)
target_link_libraries(COOM ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

project(compmap)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

add_executable(compmap compmap.cpp)

target_link_libraries(compmap ${JSONCPP_LIBRARIES})
