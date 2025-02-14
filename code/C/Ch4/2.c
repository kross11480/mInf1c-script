//Task: Use Peripheral Timer (e.g. TIM0) to blink an LED
//Note: use non-blocking polling only with flank detection not level, get count may be useless
//Messy code to detect flank and avoid multiple toggles leading to heisenbug
//Using update flag is cleaner

#include "timer.h"
#include "gpio.h"
#include "peripheral.h"
#include "nvic.h"

uint32_t ticks = 0;
uint32_t led = A1;

#define TIMER_ID TIM8
#define TIMER_ID_IT INTERRUPT_SOURCE_TIM8

void led_init()
{
    peripheral_gpioA_enable(); //enable clock
    gpio_write(led, HIGH); //switch off led
    gpio_set_mode(led, MODER_OUTPUT); //set direction to output
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