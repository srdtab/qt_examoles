cmake_minimum_required(VERSION 3.5)

project(05_snake_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(05_snake_game main.cpp)

target_link_libraries(05_snake_game ${CURSES_LIBRARIES})
