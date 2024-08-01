cmake_minimum_required(VERSION 3.5)
project(BlenderRenderer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory("external/json")
add_subdirectory("external/GArgs")

add_subdirectory("src/Config")
add_subdirectory("src/Application")
