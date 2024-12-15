/* Task: replace delay with Systick Timer*/

// 1. Datasheet: pg 246 Programming Manual
// 2. Init: reload reg
// 3. Function
// todo: better tick handling, use volatile, define or assign base address, function prototypes, void (*const vector_table[])(void)

#include<stdint.h>
#include<stm32g431xx.h>

typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
} SysTick_t;


#define SysTick ((SysTick_t *) 0xE000E010)

uint32_t SysTick_Init(uint32_t delay){
    SysTick->CTRL |= 0x3;
    SysTick->LOAD = delay;
    return 0;
}

/* SysTick interrupt Handler. */
void SysTick_Handler(void)  {
    GPIOA->ODR ^= 0x2;
}

void setup(){
    //initialize gpio
    RCC->AHB2ENR |= 0x1; //Enable Clock for GPIOA
    GPIOA->MODER &= ~(0xC);
    GPIOA->MODER |= (0x4);

    SysTick_Config(500 * 2000000/1000);
}


int main(){
    setup();
    while(1){
    }
}

extern void* _estack;
extern void* Reset_Handler;     // exception handler from startup code

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
	SysTick_Handler,/*  15 (0x0000003C)  SysTick exception */
};
