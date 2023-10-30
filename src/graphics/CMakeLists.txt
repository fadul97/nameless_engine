cmake_minimum_required(VERSION 3.22)

project(JOJGraphics)

add_library(JOJGraphics context.cpp)

target_include_directories(JOJGraphics
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include)