//Task: Use Peripheral Timer (e.g. TIM0) to blink an LED
#include "timer.h"
#include "gpio.h"

uint32_t ticks = 0;
uint32_t led_red = A0;

void SysTick_Handler(void)
{
    ticks++;
    if(ticks == 500)
    {
        gpio_toggle(led_red);
        ticks = 0;
    }
}

void led_init()
{
    peripheral_gpioA_enable(); //enable clock
    gpio_write(led_red, HIGH); //switch off led
    gpio_set_mode(led_red, MODER_OUTPUT); //set direction to output
}

void main(void){
    // led_init();
    timer_init(4);
    timer_set_period(4, 16000, 250);
    timer_start(4);
    while(1)
    {
    }
}