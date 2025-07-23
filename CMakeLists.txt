cmake_minimum_required(VERSION 4.00)

project(Asteroids)

add_subdirectory(lib/raylib)

add_executable(Asteroids src/main.c)
target_link_libraries(Asteroids raylib)
target_include_directories(Asteroids PRIVATE lib/raylib/src)