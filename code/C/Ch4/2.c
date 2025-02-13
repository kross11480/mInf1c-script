//Task: Use Peripheral Timer (e.g. TIM0) to blink an LED
//Note: use non-blocking polling only with flank detection not level, get count may be useless
//Messy code to detect flank and avoid multiple toggles leading to heisenbug
//Using update flag is cleaner

#include "timer.h"
#include "gpio.h"
#include "peripheral.h"
#include "interrupts.h"

uint32_t ticks = 0;
uint32_t led_red = A2;

#define TIMER_ID TIM8
#define TIMER_ID_IT INTERRUPT_SOURCE_TIM8


void TIM3_IRQHandler(void)
{
    gpio_toggle(led_red);
    timer_clear_interruptflag(TIM3);
}

void TIM4_IRQHandler(void)
{
    gpio_toggle(led_red);
    timer_clear_interruptflag(TIM4);
}

void TIM6_IRQHandler(void)
{
    gpio_toggle(led_red);
    timer_clear_interruptflag(TIM6);
}

void TIM7_IRQHandler(void)
{
    gpio_toggle(led_red);
    timer_clear_interruptflag(TIM7);
}

void TIM8_IRQHandler(void)
{
    gpio_toggle(led_red);
    timer_clear_interruptflag(TIM8);
}

void TIM15_IRQHandler(void)
{
    gpio_toggle(led_red);
    timer_clear_interruptflag(TIM15);
}

void TIM16_IRQHandler(void)
{
    gpio_toggle(led_red);
    timer_clear_interruptflag(TIM1);
    timer_clear_interruptflag(TIM16);
}

void TIM17_IRQHandler(void)
{
    gpio_toggle(led_red);
    timer_clear_interruptflag(TIM17);
}

void led_init()
{
    peripheral_gpioA_enable(); //enable clock
    gpio_write(led_red, HIGH); //switch off led
    gpio_set_mode(led_red, MODER_OUTPUT); //set direction to output
}

void main(void){
    NVIC_GlobalDisable();

    led_init();
    timer_init(TIMER_ID);
    timer_set_period(TIMER_ID, 16000, 250);
    timer_enable_interrupt(TIMER_ID);

    NVIC_GlobalEnable();

    timer_start(TIMER_ID);
    NVIC_EnableIRQ(TIMER_ID_IT);
    while(1)
    {
    }
}