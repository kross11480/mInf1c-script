cmake_minimum_required(VERSION 3.24)
include(${CMAKE_SOURCE_DIR}/cmake/toolchain-arm.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/target-mcu.cmake)

# project settings
project(examples C ASM)

add_library(libstefi src/gpio.c src/peripheral.c src/util.c)
target_include_directories(libstefi PUBLIC include)

#add example project
add_subdirectory(examples/1-Blinky)
