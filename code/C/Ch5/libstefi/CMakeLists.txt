cmake_minimum_required(VERSION 3.24)
include(${CMAKE_SOURCE_DIR}/cmake/toolchain-arm.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/target-mcu.cmake)

# project settings
project(examples C ASM)

add_library(libstefi
        src/gpio.c
        src/peripheral.c
        src/util.c
        src/uart.c
        src/startup.c
        src/syscalls.c
)

target_include_directories(libstefi PUBLIC include)

# Private implementation headers
target_include_directories(libstefi
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
)

#add example project
add_subdirectory(examples/1-Blinky)

#add test project for low level testing of register map
add_subdirectory(tests/1-LL_Blinky)
add_subdirectory(tests/2-Test_Gpio)