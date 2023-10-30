cmake_minimum_required(VERSION 3.22)

project(JOJPlatform)

add_subdirectory(include)
add_subdirectory(src)

target_include_directories(JOJPlatform
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include)