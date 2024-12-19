// Task: Get your IDE (e.g. Clion) working (Programming, Flashing, Debugging)
/*
    Compile: arm-none-eabi-gcc -mcpu=cortex-m4 1.c -c
    Link: arm-none-eabi-gcc -T link.ld -nostdlib 1.o -o firmware.elf
    Dump: arm-none-eabi-objdump -h 1.elf
    Binary: arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
    Flash: st-flash --reset write firmware.bin 0x8000000
    Concepts: libc, _start(warning: cannot find entry symbol _start; defaulting to 00008000)
 */
int main(void){

    unsigned int *rcc_ahb2enr = (unsigned int *) (0x40021000 + 0x4c);
    unsigned int *gpio_a_moder = (unsigned int *) 0x48000000;
    unsigned int *gpio_a_odr = (unsigned int *) (0x48000000 + 0x14);

    //initialize gpio
    *rcc_ahb2enr |= 0x1; //Enable Clock for GPIOA
    *gpio_a_moder &= ~(3<<0);
    *gpio_a_moder |= (0x1<<0); //Output Mode for GPIO


    //switch on led 0
    *gpio_a_odr &= ~(0x1<<0);
    while(1)
    {
    }
}

