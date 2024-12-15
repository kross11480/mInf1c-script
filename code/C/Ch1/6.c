/*replace delay with Systick Timer*/
// 1. Datasheet: pg 246 Programming Manual
// 2. Init: reload reg
// 3. Function

//
typedef unsigned int uint32_t;

typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
} SysTick_t;

typedef struct {
    volatile uint32_t MODER;    // GPIO mode register
    volatile uint32_t OTYPER;   // GPIO output type register
    volatile uint32_t OSPEEDR;  // GPIO output speed register
    volatile uint32_t PUPDR;    // GPIO pull-up/pull-down register
    volatile uint32_t IDR;      // GPIO input data register
    volatile uint32_t ODR;      // GPIO output data register
    volatile uint32_t BSRR;     // GPIO bit set/reset register
    volatile uint32_t LCKR;     // GPIO lock register
    volatile uint32_t AFR[2];   // GPIO alternate function registers
} GPIO;

typedef struct {
    uint32_t REGS_NOTNEEDEDNOW[19];
    uint32_t AHB2ENR;  // AHB2 peripheral clock enable register
} RCC_typeDef;

#define SysTick ((SysTick_t *) 0xE000E010)

/* Base Address of Peripheral */
GPIO *GPIOA = (GPIO *) 0x48000000;
RCC_typeDef *RCC = (RCC_typeDef *) 0x40021000;

void SysTick_Config(unsigned int one_ms){
    SysTick->CTRL |= 0x1;
    SysTick->LOAD = one_ms;
}

volatile uint32_t msTicks = 0;                              /* Variable to store millisecond ticks */

void SysTick_Handler(void)  {                               /* SysTick interrupt Handler. */
    msTicks++;                                                /* See startup file startup_LPC17xx.s for SysTick vector */
}

void setup(){
    //initialize gpio
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    GPIOA->MODER &= ~(0xC);
    GPIOA->MODER |= (0x4);

    SysTick_Config(2000000/1000);
}


int main(){
    setup();
    while(1){
        if(msticks == 500)
            GPIOA->ODR ^= 0x2;
    }
}

__attribute__ ((section (".isr_vector")))
void (* const paIsrFunc[16+102])(void) =
{/* --- core vectors --- */
    (void *)&_estack,       /*  00 (0x00000000)  initial stack pointer */
    (void *)&Reset_Handler, /*  01 (0x00000004)  (prio: -3) initial program counter (leads to first command to execute) */
    0,              /*  02 (0x00000008)  (prio: -2) non-maskable interrupt */
    0,              /*  03 (0x0000000C)  (prio: -1) hard fault exception */
    0,              /*  04 (0x00000010)  memory management */
    0,              /*  05 (0x00000014)  bus fault - pre-fetch fault, memory access fault */
    0,              /*  06 (0x00000018)  usage fault - undefined instruction or illegal state */
    0,              /*  07 (0x0000001C)  reserved vector 7 */
    0,              /*  08 (0x00000020)  reserved vector 8 */
    0,              /*  09 (0x00000024)  reserved vector 9 */
    0,              /*  10 (0x00000028)  reserved vector 10 */
    0,              /*  11 (0x0000002C)  system service call via SWI instruction */
    0,              /*  12 (0x00000030)  monitor */
    0,              /*  13 (0x00000034)  reserved vector 13 */
    0,              /*  14 (0x00000038)  pendable service call exception  */
    SysTick_Handler,              /*  15 (0x0000003C)  SysTick exception */
};