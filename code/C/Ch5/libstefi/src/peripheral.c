
#include "libstefi/peripheral.h"
#include "libstefi/util.h"
#include "../src/internal/rcc_internal.h"


void peripheral_gpioA_enable()
{
    RCC->AHB2ENR |= BIT(0);
}

void peripheral_gpioB_enable()
{
    RCC->AHB2ENR |= BIT(1);
}

void peripheral_gpioC_enable()
{
    RCC->AHB2ENR |= BIT(2);
}

void peripheral_exti_enable() {
    RCC->APB2ENR |= BIT(0);//SYSFG Enable
}

void peripheral_uart1_enable() {
    RCC->APB2ENR |= BIT(14); //UART1
}

void peripheral_uart2_enable() {
    RCC->APB1ENR |= BIT(17);
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
