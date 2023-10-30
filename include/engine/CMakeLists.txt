cmake_minimum_required(VERSION 3.22)

project(JOJCoreEngine)

# Added
add_library(JOJCoreEngine joj_window.cpp joj_engine.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../graphics/opengl)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../platform/x11/include)

# Added
target_include_directories(JOJCoreEngine
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../
    ${CMAKE_CURRENT_SOURCE_DIR}/../graphics/
    ${CMAKE_CURRENT_SOURCE_DIR}/../graphics/opengl/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../platform/x11/src/
)

# Added
target_link_libraries(JOJCoreEngine JOJPlatform JOJCore JOJGraphics)

# target_include_directories(JOJCoreEngine
#     PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}/../
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../
#     ${CMAKE_CURRENT_SOURCE_DIR}/../graphics/opengl
#     ${CMAKE_CURRENT_SOURCE_DIR}/../../platform/x11/include
# )

# target_link_libraries(JOJCoreEngine JOJPlatform JOJOpenGLGraphics)

# target_include_directories(JOJCoreEngine
#     PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}/../)