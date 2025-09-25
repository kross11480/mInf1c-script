cmake_minimum_required(VERSION 3.24)
project(rohmi C ASM)
set(CMAKE_C_STANDARD 11)

# Toolchain + MCU config
include(${CMAKE_SOURCE_DIR}/cmake/toolchain-arm.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/target-mcu.cmake)

add_subdirectory("${CMAKE_SOURCE_DIR}/libstefi")
# Executable
add_executable(rohmi rohmi.c ultrasonic.c movement.c navigation.c)

# Link prebuilt library
target_link_libraries(rohmi libstefi)