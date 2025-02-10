//Task: Use Peripheral Timer (e.g. TIM0) to blink an LED
//Note: use non-blocking polling only with flank detection not level
#include "timer.h"
#include "gpio.h"
#include "peripheral.h"


uint32_t ticks = 0;
uint32_t led_red = A0;

void SysTick_Handler(void)
{
}

void TIM2_IRQHandler(void)
{

}

void led_init()
{
    peripheral_gpioA_enable(); //enable clock
    gpio_write(led_red, HIGH); //switch off led
    gpio_set_mode(led_red, MODER_OUTPUT); //set direction to output
}

void main(void){
    uint32_t t_now, t_prev=0;
    led_init();
    timer_init(2);
    timer_set_period(2, 16000, 250);
    timer_start(2);
    while(1)
    {
        t_now = timer_getcount(2);
        //Messy code to detect flank and avoid multiple toggles leading to heisenbug
        if( t_prev == 199 && t_now == 200)
        {
            gpio_toggle(led_red);
        }
        t_prev = t_now;
    }
}