cmake_minimum_required(VERSION 3.22)

# project(JOJOpenGLGraphics)

# Added
# add_library(JOJOpenGLGraphics gl.c context_gl.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../../platform/x11)

# Added
# target_include_directories(JOJOpenGLGraphics
#     PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}/../
# )

# target_include_directories(JOJOpenGLGraphics
#     PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}/../)