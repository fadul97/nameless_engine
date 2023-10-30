cmake_minimum_required(VERSION 3.22)

project(JOJEngine)

add_subdirectory(core)
add_subdirectory(engine)
add_subdirectory(graphics)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../graphics/opengl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../platform/x11/include)
