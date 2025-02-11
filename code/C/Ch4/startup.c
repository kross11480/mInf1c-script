//
extern unsigned int _estack;  //Top of Stack
extern unsigned int _sdata;  //start .data in SRAM
extern unsigned int _edata; //end .data in SRAM
extern unsigned int _sidata; //start .data in FLASH
extern unsigned int _sbss; // start .bss (allocated in RAM)
extern unsigned int _ebss; // end .bss

extern void SysTick_Handler(void);
extern void TIM2_IRQHandler(void);
extern void TIM3_IRQHandler(void);
extern void TIM4_IRQHandler(void);
extern void TIM6_IRQHandler(void);
extern void TIM7_IRQHandler(void);

extern void main();

void Reset_Handler(void)
{
    unsigned int *init_data_flash = &_sidata;
    /*bss (better save stack) holds uninitialized global and static vars */
    for (unsigned int *data_bss = &_sbss; data_bss < &_ebss; data_bss++)
    {
        *data_bss = 0;
    }
    /* Copy init data from FLASH to RAM: otherwise initialized global var does not work */
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
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    /* --- non-core vectors --- */
	0,            /*   0 (0x00000040)  window watchdog interrupt */
	0,            /*   1 (0x00000044)  PVD through EXTI line 16 interrupt */
	0,            /*   2 (0x00000048)  RTC/TAMP/CSS on LSE through EXTI line 19 interrupt */
	0,            /*   3 (0x0000004C)  RTC Wakeup timer through EXTI line 20 interrupt */
	0,            /*   4 (0x00000050)  Flash global interrupt */
	0,            /*   5 (0x00000054)  RCC global interrupt */
	0,       /*   6 (0x00000058)  EXTI Line 0 interrupt */
	0,            /*   7 (0x0000005C)  EXTI Line 1 interrupt */
	0,            /*   8 (0x00000060)  EXTI Line 2 interrupt */
	0,            /*   9 (0x00000064)  EXTI Line 3 interrupt */
	0,            /*  10 (0x00000068)  EXTI Line 4 interrupt */
	0,            /*  11 (0x0000006C)  DMA1 channel 1 interrupt */
	0,            /*  12 (0x00000070)  DMA1 channel 2 interrupt */
	0,            /*  13 (0x00000074)  DMA1 channel 3 interrupt */
	0,            /*  14 (0x00000078)  DMA1 channel 4 interrupt */
	0,            /*  15 (0x0000007C)  DMA1 channel 5 interrupt */
	0,            /*  16 (0x00000080)  DMA1 channel 6 interrupt */
	0,            /*  17 (0x00000084)  DMA1 channel 7 interrupt */
	0,            /*  18 (0x00000088)  ADC1 + ADC2 global interrupt */
	0,            /*  19 (0x0000008C)  USB high priority interrupts */
	0,            /*  20 (0x00000090)  USB low priority interrupts */
	0,            /*  21 (0x00000094)  FDCAN1 interrupt 0 */
	0,            /*  22 (0x00000098)  FDCAN1 interrupt 1 */
	0,            /*  23 (0x0000009C)  EXTI line [9:5] interrupts */
	0,            /*  24 (0x000000A0)  TIM1 break + TIM15 global interrupts */
	0,            /*  25 (0x000000A4)  TIM1 update + TIM16 global interrupts */
	0,            /*  26 (0x000000A8)  TIM1 trigger, commutation, direction change, index  + TIM17 interrupts */
	0,            /*  27 (0x000000AC)  TIM1 capture compare interrupt */
	TIM2_IRQHandler,            /*  28 (0x000000B0)  TIM2 global interrupt */
	TIM3_IRQHandler,            /*  28 (0x000000B0)  TIM2 global interrupt */
	TIM4_IRQHandler,            /*  28 (0x000000B0)  TIM2 global interrupt */
	0,							/*  31 (0x000000BC)  I2C1 event + EXTI line 23 interrupts */
	0,							/*  32 (0x000000C0)  I2C1 error interrupt */
	0,							/*  34 (0x000000C8)  I2C2 error interrupt */
	0,							/*  35 (0x000000CC)  SPI1 global interrupt */
	0,							/*  36 (0x000000D0)  SPI2 global interrupt */
	0,							/*  37 (0x000000D4)  USART1 global + EXTI line 25 interrupts */
	0,							/*  38 (0x000000D8)  USART2 global + EXTI line 26 interrupts */
	0,							/*  39 (0x000000DC)  USART3 global + EXTI line 28 interrupts */
	0,							/*  40 (0x000000E0)  EXTI line [15:10] interrupts */
	0,							/*  41 (0x000000E4)  RTC alarms interrupts */
	0,							/*  42 (0x000000E8)  USB wakeup from suspend trough EXTI line 18 interrupt */
	0,            /*  43 (0x000000EC)  TIM8 break, transition error, index error interrupts */
	0,            /*  44 (0x000001F0)  TIM8 update interrupt */
	0,            /*  45 (0x000001F4)  TIM8 trigger, commutation, direction change, index interrupts */
	0,            /*  46 (0x000001F8)  TIM8 capture compare interrupt */
	0,            /*  47 (0x000001FC)  ADC3 global interrupt */
	0,            /*  48 (0x00000100)  FSMC global interrupt */
	0,            /*  49 (0x00000104)  LPTIM1 global interrupt */
	0,            /*  50 (0x00000108)  TIM5 global interrupt */
	0,            /*  51 (0x0000010C)  SPI3 global interrupt */
	0,            /*  52 (0x00000110)  UART4 global + EXTI line 34 interrupts */
	0,            /*  53 (0x00000114)  UART5 global + EXTI line 35 interrupts */
	TIM6_IRQHandler,            /*  54 (0x00000118)  TIM6 + DAC1/3 underrun global interrupts */
	TIM7_IRQHandler,            /*  55 (0x0000011C)  TIM7 + DAC2/4 underrun global interrupts */
};