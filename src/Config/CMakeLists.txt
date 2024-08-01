cmake_minimum_required(VERSION 3.5)
project(BlenderRenderer-Config)

file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "../../include/Config/*.hpp")
add_library(${PROJECT_NAME} STATIC ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC ../../include ../../external/json/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json)
