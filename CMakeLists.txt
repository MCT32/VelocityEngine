cmake_minimum_required(VERSION 3.24.0)
project(COOM)

set(SDL2_LIBRARY_DIR lib)

include_directories(include)

add_executable(COOM main.cpp)
target_link_libraries(COOM -lmingw32 ${SDL2_LIBRARY_DIR}/libSDL2main.a ${SDL2_LIBRARY_DIR}/libSDL2.dll.a -mwindows)
