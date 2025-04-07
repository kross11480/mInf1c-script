/*********************************************************************/
/* SysTick Timer Hardware Abstraction layer*/
/*********************************************************************/
#include "libstefi/systick.h"
#include "internal/systick_internal.h"

void systick_init()
{
    SysTick->CTRL |= (1 << 2); //1: Clock 0: Clock/8.
    //SysTick->CTRL |= (1 << 1); //enable interrupt
    SysTick->LOAD = 0xFFFFFF; //System Core Clock=16MHz
}

void systick_start()
{
    SysTick->CTRL |= (1 << 0); //start timer
}

void systick_stop()
{
    SysTick->CTRL &= ~(1 << 0); //stop timer
}

void systick_restart()
{
    systick_stop();
    SysTick->VAL = 0; //Manual reset
    systick_start();
}

uint32_t systick_get_ms()
{
    uint32_t current_time = SysTick->VAL;
    uint32_t elapsed_time = (0xFFFFFF - current_time + 1);
    uint32_t elapsed_time_ms = (elapsed_time) / TICKS_PER_MS;
    return elapsed_time_ms;
}

void systick_delay_ms(uint32_t time_in_ms)
{
    while (systick_get_ms() < time_in_ms);
    systick_restart();
}

void systick_delay_s(uint32_t time_in_s)
{
    for(uint32_t i = 0 ; i < time_in_s; i++)
    {
        while(!(SysTick->CTRL & (1<<16)));
    }
}