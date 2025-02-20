
#include "timer.h"
#include "gpio.h"
#include "peripheral.h"

static volatile ticks = 0;
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

void main(void){
    RCC->AHB2ENR |= (1 << 0);
    gpio_write(led_red, HIGH);
    gpio_set_mode(led_red, MODER_OUTPUT);

    timer_init();
    timer_start();

    while(1)
    {
    }
}