cmake_minimum_required(VERSION 3.25.0)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/sdl2)

project(VelEngine)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})

add_executable(VelEngine main.cpp entity.cpp load.cpp logging.cpp player.cpp render.cpp ui.cpp util.cpp)
target_link_libraries(VelEngine ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES})

project(compmap)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)

add_executable(compmap compmap.cpp)

target_link_libraries(compmap ${JSONCPP_LIBRARIES})
