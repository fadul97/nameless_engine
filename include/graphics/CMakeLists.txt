cmake_minimum_required(VERSION 3.22)

project(JOJGraphics)

#add_library(JOJGraphics context.cpp)
add_library(JOJGraphics context.cpp opengl/gl.c opengl/context_gl.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
add_subdirectory(opengl)

target_include_directories(JOJGraphics
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../)

# target_include_directories(JOJGraphics
#     PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}/../)