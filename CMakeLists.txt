cmake_minimum_required(VERSION 3.7)

project(tetris)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lSDL2_ttf -fsanitize=address")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(tetris main.c field.c field.h tetromino.c tetromino.h)
target_link_libraries(tetris ${SDL2_LIBRARIES})