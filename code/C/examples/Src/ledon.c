// Task: Get your IDE (e.g. Clion) working (Programming, Flashing, Debugging)
/*
    Compile: arm-none-eabi-gcc -mcpu=cortex-m4 1.c -c
    Link: arm-none-eabi-gcc -T link.ld -nostdlib 1.o -o firmware.elf
    Dump: arm-none-eabi-objdump -h 1.elf
    Binary: arm-none-eabi-objcopy -O binary firmware.elf firmware.bin
    Flash: st-flash --reset write firmware.bin 0x8000000
    Concepts: libc, _start(warning: cannot find entry symbol _start; defaulting to 00008000)
 */
extern unsigned int _estack;  //Top of Stack
extern unsigned int _sdata;  //start .data in SRAM
extern unsigned int _edata; //end .data in SRAM
extern unsigned int _sidata; //start .data in FLASH

int main(void){

    unsigned int *rcc_ahb2enr = (unsigned int *) (0x40021000 + 0x4c);
    unsigned int *gpio_a_moder = (unsigned int *) 0x48000000;
    unsigned int *gpio_a_odr = (unsigned int *) (0x48000000 + 0x14);

    //initialize gpio
    *rcc_ahb2enr |= 0x1; //Enable Clock for GPIOA
    *gpio_a_moder &= ~(3<<2);
    *gpio_a_moder |= (0x1<<2); //Output Mode for GPIO


    //switch on led 0
    *gpio_a_odr &= ~(0x1<<1);
}

void Reset_Handler(void)
{
    /* Copy init data from FLASH to RAM */
    unsigned int *init_data_flash = &_sidata;

    /*
    for (unsigned int *data_sram = &_sdata; data_sram < &_edata;) {
        *data_sram++ = *init_data_flash++;
    }
    */
    /* Branch to main() function */
    main();

    /* infinite loop in case main() returns */
    while (1);
}
__attribute__ ((section (".isr_vector")))
void (* const paIsrFunc[16+102])(void) =
{/* --- core vectors --- */
    (void *)&_estack,       /*  00 (0x00000000)  initial stack pointer */
    (void *)&Reset_Handler, /*  01 (0x00000004)  initial program counter (leads to first command to execute) */
};
