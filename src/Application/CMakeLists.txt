cmake_minimum_required(VERSION 3.5)
project(BlenderRenderer-Application)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "../../include/Application/*.hpp")
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ../../include ../../external ../../external/GArgs/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE BlenderRenderer-Config GArgs)
