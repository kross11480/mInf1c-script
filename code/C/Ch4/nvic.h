//NVIC: Check Pending Register
//Functions
#ifndef NVIC_H
#define NVIC_H

#define NVIC_GlobalEnable() do { __asm volatile("cpsie i"); } while (0)
#define NVIC_GlobalDisable() do { __asm volatile("cpsid i"); } while(0)

typedef enum _nvic_interrupt_sources nvic_source_t;
void NVIC_EnableIRQ(nvic_source_t irq);       // enable interrupt in NVIC

//Datatypes
enum _nvic_interrupt_sources {
    INTERRUPT_SOURCE_EXTI0 = 6,
    INTERRUPT_SOURCE_EXTI4 = 10,
    INTERRUPT_SOURCE_EXTI5_9 = 23,

    INTERRUPT_SOURCE_TIM2 = 28,
    INTERRUPT_SOURCE_TIM3 = 29,
    INTERRUPT_SOURCE_TIM4 = 30,
    INTERRUPT_SOURCE_TIM6 = 54,
    INTERRUPT_SOURCE_TIM7 = 55,
    INTERRUPT_SOURCE_TIM8 = 44,
    INTERRUPT_SOURCE_TIM15 = 24,
    INTERRUPT_SOURCE_TIM1_TIM16 = 25,
    INTERRUPT_SOURCE_TIM17 = 26,
};

#endif