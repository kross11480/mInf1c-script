cmake_minimum_required(VERSION 3.24)
include(${CMAKE_SOURCE_DIR}/cmake/toolchain-arm.cmake)
include(${CMAKE_SOURCE_DIR}/cmake/target-mcu.cmake)
# project settings
project(examples C ASM)
set(TARGET_NAME 1)

add_executable(1.elf 1.c startup.c gpio.c timer.c nvic.c)
add_executable(2.elf 2.c startup.c timer.c peripheral.c gpio.c nvic.c)
add_executable(3.elf 3.c startup.c timer.c peripheral.c gpio.c nvic.c interrupts.c)
add_executable(4.elf 4.c startup.c timer.c peripheral.c gpio.c nvic.c interrupts.c)
add_executable(5.elf 5.c startup.c timer.c peripheral.c gpio.c nvic.c interrupts.c button.c board.c)
add_executable(6.elf 6.c startup.c timer.c peripheral.c gpio.c nvic.c interrupts.c button.c led.c board.c)
add_executable(7.elf 7.c startup.c timer.c peripheral.c gpio.c nvic.c interrupts.c button.c led.c board.c syscalls.c uart.c)
add_executable(8.elf 8.c startup.c timer.c peripheral.c gpio.c nvic.c interrupts.c button.c led.c board.c syscalls.c uart.c debounce.c)
add_executable(9.elf 9.c startup.c timer.c peripheral.c gpio.c nvic.c interrupts.c button.c led.c board.c systick.c)


set(HEX_FILE ${PROJECT_BINARY_DIR}/${TARGET_NAME}.hex)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${TARGET_NAME}.bin)

add_custom_command(TARGET ${TARGET_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${TARGET_NAME}.elf> ${HEX_FILE}
        COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${TARGET_NAME}.elf> ${BIN_FILE}
        COMMENT "Building ${HEX_FILE}
Building ${BIN_FILE}")

add_custom_target(flash ALL
        COMMAND        arm-none-eabi-objcopy -O binary ${TARGET_NAME}.elf firmware.bin
        COMMAND        st-flash --reset write firmware.bin 0x8000000
        DEPENDS        ${TARGET_NAME}.elf
        COMMENT        "Flashing firmware")
