cmake_minimum_required(VERSION 3.30.5)

project(surgen)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)

add_subdirectory(lib/raylib)
add_subdirectory(src)