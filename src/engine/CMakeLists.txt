cmake_minimum_required(VERSION 3.22)

project(JOJCoreEngine)

add_library(JOJCoreEngine joj_window.cpp joj_engine.cpp)

target_include_directories(JOJCoreEngine
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

target_link_directories(JOJCoreEngine JOJPlatform JOJCore JOJGraphics JOJOpenGLGraphics)