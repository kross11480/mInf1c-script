// Task: Empty Template: turning on LED1 on libstefi
#include "../../src/internal/gpio_internal.h"

typedef struct {
    uint32_t REGS_NOTNEEDEDNOW[19];
    uint32_t AHB2ENR;  // AHB2 peripheral clock enable register
    uint32_t AHB3ENR;  // AHB3 peripheral clock enable register
    uint32_t RESERVED;
    uint32_t APB1ENR;  // APB1 peripheral clock enable register
    uint32_t APB1ENR2;
    uint32_t APB2ENR;
} RCC_typeDef;

#define RCC ((RCC_typeDef *) 0x40021000) //Operator precedence remove ()

void soft_delay_ms(uint32_t time_in_ms) {
    uint32_t count = time_in_ms * 1865; //Approx Factor
    while (count--)
        __asm__("NOP"); //6-8 Cycles per loop => @16 Mhz
}

#define BIT(num) (1 << num)

void main(){
    RCC->AHB2ENR |= BIT(2);
    GPIOC->MODER |= 1 << 10;
    GPIOC->MODER &= ~(1 << 11);
    while (1) {
        GPIOC->ODR ^= (1 << 5);
        soft_delay_ms(250);
    }
}