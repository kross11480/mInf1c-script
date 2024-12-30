//
extern unsigned int _estack;  //Top of Stack
extern unsigned int _sdata;  //start .data in SRAM
extern unsigned int _edata; //end .data in SRAM
extern unsigned int _sidata; //start .data in FLASH

extern void main();

void Reset_Handler(void)
{

    unsigned int *init_data_flash = &_sidata;
    /* Copy init data from FLASH to RAM: otherwise global var does not work */
    for (unsigned int *data_sram = &_sdata; data_sram < &_edata;) {
        *data_sram++ = *init_data_flash++;
    }

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