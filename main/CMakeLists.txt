cmake_minimum_required(VERSION 3.22)

project(JOJEngine)

add_executable(JOJEngine main.cpp)

target_include_directories(JOJEngine
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/engine/
    ${CMAKE_CURRENT_SOURCE_DIR}/../src/engine/
)

target_link_libraries(JOJEngine JOJCoreEngine)

# target_link_libraries(JOJEngine JOJPlatform JOJGraphics JOJCore)