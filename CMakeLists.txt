cmake_minimum_required(VERSION 3.0)

project(niftigl)

find_package(OpenGL REQUIRED)

add_subdirectory(vendor)

add_library(niftigl_a STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/niftigl.c)

add_library(niftigl++_a STATIC ${CMAKE_CURRENT_SOURCE_DIR}/src/niftigl.c ${CMAKE_CURRENT_SOURCE_DIR}/src/niftigl.cpp)

target_include_directories(niftigl_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS})

target_include_directories(niftigl++_a PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${OPENGL_INCLUDE_DIRS})

target_link_libraries(niftigl_a ${OPENGL_LIBRARIES})

target_link_libraries(niftigl++_a ${OPENGL_LIBRARIES})