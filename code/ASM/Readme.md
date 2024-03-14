For compiling assembler program
```
arm-none-eabi-as toggle_led.s -o toggle_led.o 
```
For linking
```
arm-none-eabi-ld -Ttext=0x8000000 toggle_led.o -o toggle_led.elf
```
For converting ELF to binary format
```
arm-none-eabi-objcopy binary toggle_led.elf firmware.bin
```
For flashing the compiled firmware
```
st-flash write firmware.bin 0x8000000
```
