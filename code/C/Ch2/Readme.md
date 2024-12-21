1. Minimal Program
2. Peripheral Programming with Pointer: Switch on LED
3. Peripheral Programming with pointer of Structure
5. Blink an LED (delay counter in SW)
4. Blink an LED (delay counter in HW, Polling)
5. Blink an LED (delay counter in HW, interrupts)
6. Blink an LED on button press (Polling)
7. Blink an LED on button press (Interrupt)
8. Debouncing
9. Project: Knightrider lights

Concepts:
1. Tools to generate Binary (Machine Code) : What is the size of the binary?
2. Pointers and Pointers to Structure

Minimal program switching on an led in STefi-lite Platform
1. Startup Code to (Initialize Vector Table, Reset Handler)
2. using Pointers
3. using Pointer to Structure and Typedef
4. basic linker script 
5. Cmake and Makefile

# How do i compile the programs
## Do the hard way

* Compile: arm-none-eabi-gcc -mcpu=cortex-m4 1.c -c
* Link to get executable : arm-none-eabi-gcc -T link.ld -nostdlib 1.o -o firmware.elf
* Dump to see compiled code: arm-none-eabi-objdump -h 1.elf
* 
* Generate Binary to flash: arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
* Flash: st-flash --reset write firmware.bin 0x8000000

## Use Cmake on command line


## Clion

# How do i analyze the program

## Command Line Tools
arm-none-eabi-nm -S --size-sort 1.elf
arm-none-eabi-readelf -S 1.elf
arm-none-eabi-objdump -d --section=.text 1.elf

