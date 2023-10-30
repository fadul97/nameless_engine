cmake_minimum_required(VERSION 3.22)

project(JOJCore)

# Added
add_library(JOJCore error_list.c)

# Added
target_include_directories(JOJCore
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../
)

# add_library(JOJCore error_list.c)