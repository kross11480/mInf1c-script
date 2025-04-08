// Task: Empty Template: turning on LED1 on libstefi
#include <stdint.h>

#include "internal/gpio_internal.h"
#include "internal/rcc_internal.h"

void soft_delay_ms(uint32_t time_in_ms) {
    uint32_t count = time_in_ms * 1865; //Approx Factor
    while (count--)
        __asm__("NOP"); //6-8 Cycles per loop => @16 Mhz
}

#define BIT(num) (1 << num)

void main(){
    RCC->AHB2ENR |= BIT(2);
    GPIOC->MODER |= 1 << 8;
    GPIOC->MODER &= ~(1 << 9);
    while (1) {
        //Bare Metal Toggle: approx 10 Cycles.
        GPIOC->ODR ^= (1 << 4);
        soft_delay_ms(250);
    }
}