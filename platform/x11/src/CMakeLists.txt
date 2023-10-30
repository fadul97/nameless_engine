cmake_minimum_required(VERSION 3.22)

project(JOJPlatform)

add_library(JOJPlatform window_x11.cpp input_x11.cpp)

target_include_directories(JOJPlatform
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/engine)

if(UNIX)
	target_link_libraries(JOJPlatform -lX11 -lGL JOJCoreEngine)
endif()