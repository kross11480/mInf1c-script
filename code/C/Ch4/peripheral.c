#include "peripheral.h"
#include "util.h"

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

void peripheral_gpioA_enable()
{
    RCC->AHB2ENR |= BIT(0);
}

void peripheral_gpioB_enable()
{
    RCC->AHB2ENR |= BIT(1);
}

// Timer Enable
void peripheral_tim1_enable()
{
    RCC->APB2ENR |= BIT(11);
}

void peripheral_tim2_enable()
{
    RCC->APB1ENR |= BIT(0);
}

void peripheral_tim3_enable()
{
    RCC->APB1ENR |= BIT(1);
}

void peripheral_tim4_enable()
{
    RCC->APB1ENR |= BIT(2);
}

void peripheral_tim5_enable()
{
    RCC->APB1ENR |= BIT(3);
}

void peripheral_tim6_enable()
{
    RCC->APB1ENR |= BIT(4);
}

void peripheral_tim7_enable()
{
    RCC->APB1ENR |= BIT(5);
}

void peripheral_tim8_enable()
{
    RCC->APB2ENR |= BIT(13);
}

void peripheral_tim15_enable()
{
    RCC->APB2ENR |= BIT(16);
}

void peripheral_tim16_enable()
{
    RCC->APB2ENR |= BIT(17);
}

void peripheral_tim17_enable()
{
    RCC->APB2ENR |= BIT(18);
}
