cmake_minimum_required(VERSION 3.22)

project(JOJCore)

add_library(JOJCore error_list.c)

target_include_directories(JOJCore
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../../include)