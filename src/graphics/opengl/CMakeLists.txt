cmake_minimum_required(VERSION 3.22)

project(JOJOpenGLGraphics)

add_library(JOJOpenGLGraphics gl.c context_gl.cpp)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../)
# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../include/graphics/opengl/)

target_include_directories(JOJOpenGLGraphics
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/graphics/opengl/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../
)