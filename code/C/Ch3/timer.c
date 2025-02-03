#include "timer.h"

typedef struct {
    uint32_t CTRL;
    uint32_t LOAD;
    uint32_t VAL;
} SysTick_t;

#define SysTick ((SysTick_t *) 0xE000E010)

void soft_delay_ms(uint32_t time_in_ms) {
    uint32_t count = time_in_ms * 1865; //Approx Factor
    while (count--)
        __asm__("NOP"); //6-8 Cycles per loop => @16 Mhz
}

void _systick_init()
{
    SysTick->CTRL |= (1 << 2); //1: Clock 0: Clock/8.
    SysTick->LOAD = 0xFFFFFF; //System Core Clock=16MHz
}

void _systick_start()
{
    SysTick->VAL = 0;
    SysTick->CTRL |= (1 << 0); //start timer
}

void _systick_stop()
{
    SysTick->CTRL |= (0 << 0); //stop timer
}

void _systick_restart()
{
    _systick_stop();
    _systick_start();
}

uint32_t _systick_get_ms()
{
    uint32_t current_time = SysTick->VAL;
    return (0xFFFFFF - current_time)/TICKS_PER_MS;
}

void _systick_delay_ms(uint32_t time_in_ms)
{
    while (_systick_get_ms() < time_in_ms);
    _systick_restart();
}

void timer_init(){
    _systick_init(); //Intialize Systick Clock for 16 tick per us
}

void timer_start()
{
    _systick_start();
}

void timer_stop()
{
    _systick_stop();
}

uint32_t timer_elapsed_ms()
{
    return _systick_get_ms();
}

void timer_delay_ms(uint32_t time_in_ms)
{
    _systick_delay_ms(time_in_ms);
}

void timer_delay_s(uint32_t time_in_s)
{
    for(uint32_t i = 0 ; i < time_in_s; i++)
    {
        while(!(SysTick->CTRL & (1<<16)));
    }
}
