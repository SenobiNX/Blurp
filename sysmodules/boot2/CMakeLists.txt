cmake_minimum_required(VERSION 3.16)

project(boot2)
include(config/config.cmake)

file(GLOB_RECURSE SOURCES_ASM ${CMAKE_CURRENT_SOURCE_DIR}/src/*.S)
file(GLOB_RECURSE SOURCES_C ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE SOURCES_CXX ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
set(SOURCES ${SOURCES_ASM} ${SOURCES_C} ${SOURCES_CXX})
add_executable(boot2 ${SOURCES})

apply_config(boot2)
include(../../cmake/module.cmake)
include(../../cmake/deploy.cmake)
