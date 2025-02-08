//Task: Use Peripheral Timer (e.g. TIM0) to blink an LED
#include "timer.h"
#include "gpio.h"
#include "peripheral.h"


static volatile int ticks = 0;
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
    timer_init();
    timer_start();
    while(1)
    {
    }
}