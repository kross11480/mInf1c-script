
#ifndef INTERRUPTS_H
#define INTERRUPTS_H


#include <stdint.h>

#define NVIC_GlobalEnable() do { __asm volatile("cpsie i"); } while (0)
#define NVIC_GlobalDisable() do { __asm volatile("cpsid i"); } while(0)

typedef enum _interrupt_sources interrupt_source_t;

void NVIC_EnableIRQ(interrupt_source_t);       // enable interrupt in NVIC

enum _interrupt_sources {
    INTERRUPT_SOURCE_TIM2 = 28,
    INTERRUPT_SOURCE_TIM3 = 29,
    INTERRUPT_SOURCE_TIM4 = 30,
    INTERRUPT_SOURCE_TIM6 = 54,
    INTERRUPT_SOURCE_TIM7 = 55,
};

#endif