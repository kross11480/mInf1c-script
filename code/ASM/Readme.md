Program Description
* toggle_led toggles the blue led

For compiling assembler program
```
arm-none-eabi-as -g toggle_led.s -o toggle_led.o 
```
For linking
```
arm-none-eabi-ld -g -Ttext=0x8000000 toggle_led.o -o toggle_led.elf
```
For converting ELF to binary format
```
arm-none-eabi-objcopy -O binary toggle_led.elf firmware.bin
```
For flashing the compiled firmware
```
st-flash write firmware.bin 0x8000000
```
Do not forget to press reset after flashing
